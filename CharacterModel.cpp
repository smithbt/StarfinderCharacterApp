#include "CharacterModel.h"

CharacterModel::CharacterModel(QObject* parent)
	: QAbstractTableModel(parent),
	pcs()
{
}

CharacterModel::~CharacterModel()
{
	qDeleteAll(pcs);
}

QVariant CharacterModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid()) // invalid index
		return QVariant();

	const int row = index.row();
	if (row >= pcs.size() || row < 0) // out of range
		return QVariant();

	if (role == Qt::DisplayRole || role == Qt::EditRole) {
		switch (index.column()) {
		case Object: return QVariant::fromValue(pcs.at(index.row()));
		case CharacterName: return pcs.at(index.row())->getCharacterName();
		case BAB: return pcs.at(index.row())->getBAB();
		case Fortitude: return pcs.at(index.row())->getFortitude();
		case Reflex: return pcs.at(index.row())->getReflex();
		case Will: return pcs.at(index.row())->getWill();
		case Stamina: return QVariant::fromValue(pcs.at(index.row())->getStamina());
		case Strength: return QVariant::fromValue(pcs.at(index.row())->getAbility("Strength"));
		case Dexterity: return QVariant::fromValue(pcs.at(index.row())->getAbility("Dexterity"));
		case Constitution: return QVariant::fromValue(pcs.at(index.row())->getAbility("Constitution"));
		case Intelligence: return QVariant::fromValue(pcs.at(index.row())->getAbility("Intelligence"));
		case Wisdom: return QVariant::fromValue(pcs.at(index.row())->getAbility("Wisdom"));
		case Charisma: return QVariant::fromValue(pcs.at(index.row())->getAbility("Charisma"));
		case Weapons: return QVariant::fromValue(pcs.at(index.row())->getWeapons());
		}
	}
	return QVariant();
}

Qt::ItemFlags CharacterModel::flags(const QModelIndex& index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

int CharacterModel::rowCount(const QModelIndex& parent) const
{
	return pcs.size();
}

int CharacterModel::columnCount(const QModelIndex& parent) const
{
	return columns;
}

bool CharacterModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (!index.isValid())
		return false;

	const int row = index.row();
	if (row > pcs.size() || row < 0)
		return false;

	if (role == Qt::EditRole || Qt::DisplayRole) {
		Character* thisPC = pcs.at(row);
		switch (index.column()) {
		case Object:
			if (value.canConvert<Character*>()) {
				pcs.replace(row, value.value<Character*>());
				emit dataChanged(this->index(row, 0), this->index(row, (columns - 1)), { Qt::DisplayRole, Qt::EditRole });
				return true;
			}
			break;
		case CharacterName: 
			thisPC->setCharacterName(value.toString());
			break;
		case BAB:
			break;
		case Fortitude:
			break;
		case Reflex:
			break;
		case Will:
			break;
		case Stamina:
			thisPC->setStamina(value.value<Resource*>());
			break;
		case Strength:
			thisPC->setAbility("Strength", value.value<Ability*>());
			break;
		case Dexterity:
			thisPC->setAbility("Dexterity", value.value<Ability*>());
			break;
		case Constitution:
			thisPC->setAbility("Constitution", value.value<Ability*>());
			break;
		case Intelligence:
			thisPC->setAbility("Intelligence", value.value<Ability*>());
			break;
		case Wisdom:
			thisPC->setAbility("Wisdom", value.value<Ability*>());
			break;
		case Charisma:
			thisPC->setAbility("Charisma", value.value<Ability*>());
			break;
		case Weapons:
			thisPC->setWeapons(value.value<QVector<Weapon*>>());
			break;
		}
		emit dataChanged(index, index, { Qt::DisplayRole, Qt::EditRole });
		return true;
	}

	return false;
}

bool CharacterModel::insertRows(int position, int rows, const QModelIndex& parent)
{
	Q_UNUSED(parent);
	beginInsertRows(QModelIndex(), position, position + rows - 1);

	for (int i = position; i < (position + rows); ++i) {
		pcs.insert(i, nullptr);
	}

	endInsertRows();
	return true;
}

bool CharacterModel::removeRows(int position, int rows, const QModelIndex& parent)
{
	Q_UNUSED(parent);
	beginRemoveRows(QModelIndex(), position, position + rows - 1);

	for (int i = position; i < (position + rows); ++i) {
		Character* pc = pcs.takeAt(i);
		delete pc;
	}

	endRemoveRows();
	return true;
}
