#include "WeaponModel.h"

WeaponModel::WeaponModel(QObject* parent)
	: QAbstractListModel(parent),
	m_pc(nullptr)
{
}

QVariant WeaponModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid()) // invalid index
		return QVariant();

	const int row = index.row();
	if (row >= m_pc->getWeaponCount() || row < 0) // out of range
		return QVariant();

	if (role == Qt::DisplayRole) {
		return m_pc->getWeaponAt(row)->toString();
	}

	if (role >= Qt::UserRole) {
		Weapon* weapon = m_pc->getWeaponAt(row);
		switch (role) {
		case NameRole: return weapon->name;
		case LevelRole: return weapon->level;
		case BulkRole: return weapon->bulk;
		case PriceRole: return weapon->price;
		case AttackRole: {
			int attackMod = m_pc->getBAB();
			switch (weapon->type) {
			case Weapon::Type::Melee:
				attackMod += m_pc->getAbilityProperty("Strength", "modifier");
				break;
			case Weapon::Type::Ranged:
				attackMod += m_pc->getAbilityProperty("Dexterity", "modifier");
				break;
			}
			return QString::asprintf("%+i", attackMod);
		}
		case DamageRole: {
			int damageMod = 0;
			switch (weapon->type) {
			case Weapon::Type::Melee:
				damageMod += m_pc->getAbilityProperty("Strength", "modifier");
				break;
			case Weapon::Type::Ranged:
				damageMod += 0;
				break;
			}
			return QString::asprintf("%1%+i %3", damageMod).arg(weapon->damage->dice(), weapon->damage->type);
		}
		case CritRole: return weapon->crit;
		case RangeRole: return weapon->range;
		case TypeRole: return "Type";
		case CurrentAmmoRole: return weapon->ammo->current();
		case CapacityRole: return weapon->capacity();
		case UsageRole: return weapon->usage();
		case SpecialRole: return weapon->special;
		default: return QVariant::fromValue(m_pc->getWeaponAt(row));
		}
	}

	return QVariant();
}

Qt::ItemFlags WeaponModel::flags(const QModelIndex& index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	return Qt::ItemIsEditable | QAbstractListModel::flags(index);
}

int WeaponModel::rowCount(const QModelIndex& parent) const
{
	if (m_pc)
		return m_pc->getWeaponCount();
	return 0;
}

bool WeaponModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (!index.isValid()) // invalid index
		return false;

	const int row = index.row();
	if (row >= m_pc->getWeaponCount() || row < 0) // out of range
		return false;

	if (role >= Qt::UserRole) {
		Weapon* weapon = m_pc->getWeaponAt(row);
		switch (role) {
		case NameRole:
			weapon->name = value.toString();
			break;
		case LevelRole:
			weapon->level = value.toInt();
			break;
		case BulkRole:
			weapon->bulk = value.toDouble();
			break;
		case PriceRole:
			weapon->price = value.toInt();
			break;
		case DamageRole: {
			QVariantList dmgData = value.value<QVariantList>();
			weapon->damage->dieCount = dmgData.at(0).toInt();
			weapon->damage->dieSize = dmgData.at(1).toInt();
			weapon->damage->type = dmgData.at(2).toString();
		} break;
		case CritRole:
			weapon->crit = value.toString();
			break;
		case RangeRole:
			weapon->range = value.toInt();
			break;
		case TypeRole: break; // parse type
		case CurrentAmmoRole:
			weapon->ammo->setCurrent(value.toInt());
			break;
		case CapacityRole:
			weapon->ammo->setMax(value.toInt());
			break;
		case UsageRole:
			weapon->ammo->setStep(value.toInt());
			break;
		case SpecialRole:
			weapon->special = value.toStringList();
			break;
		default:
			if (value.canConvert<Weapon*>())
				weapon = value.value<Weapon*>();
			break;
		}
		m_pc->setWeaponAt(row, weapon);
		emit dataChanged(index, index, { Qt::DisplayRole, role });
		return true;
	}
	return false;
}

bool WeaponModel::insertRows(int position, int rows, const QModelIndex& parent)
{
	Q_UNUSED(parent);
	beginInsertRows(QModelIndex(), position, position + rows - 1);

	for (int i = position; i < (position + rows); ++i) {
		m_pc->insertWeaponAt(i, new Weapon(m_pc));
	}

	endInsertRows();
	return true;
}

bool WeaponModel::removeRows(int position, int rows, const QModelIndex& parent)
{
	Q_UNUSED(parent);
	beginRemoveRows(QModelIndex(), position, position + rows - 1);

	for (int i = position; i < (position + rows); ++i) {
		m_pc->removeWeaponAt(i);
	}

	endRemoveRows();
	return true;
}

void WeaponModel::setCharacter(Character* pc)
{
	if (pc != m_pc) {
		beginResetModel();
		m_pc = pc;
		endResetModel();
	}
}