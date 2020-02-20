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
		case RaceData: return QVariant::fromValue(pcs.at(index.row())->getRace());
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
		switch (index.column()) {
		case Object:
			if (value.canConvert<Character*>()) {
				pcs.replace(row, value.value<Character*>());
				emit dataChanged(this->index(row, 0), this->index(row, (columns - 1)), { Qt::DisplayRole, Qt::EditRole });
				return true;
			}
			break;
		case RaceData:
			if (value.canConvert<Race*>())
				pcs[row]->setRace(value.value<Race*>());
			else return false;
			break;
		case CharacterName:
			pcs[row]->setCharacterName(value.toString());
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
			if (value.canConvert<Resource*>())
				pcs[row]->setStamina(value.value<Resource*>());
			else return false;
			break;
		case Strength:
			if (value.canConvert<Ability*>())
				pcs[row]->setAbility("Strength", value.value<Ability*>());
			else return false;
			break;
		case Dexterity:
			if (value.canConvert<Ability*>())
				pcs[row]->setAbility("Dexterity", value.value<Ability*>());
			else return false;
			break;
		case Constitution:
			if (value.canConvert<Ability*>())
				pcs[row]->setAbility("Constitution", value.value<Ability*>());
			else return false;
			break;
		case Intelligence:
			if (value.canConvert<Ability*>())
				pcs[row]->setAbility("Intelligence", value.value<Ability*>());
			else return false;
			break;
		case Wisdom:
			if (value.canConvert<Ability*>())
				pcs[row]->setAbility("Wisdom", value.value<Ability*>());
			else return false;
			break;
		case Charisma:
			if (value.canConvert<Ability*>())
				pcs[row]->setAbility("Charisma", value.value<Ability*>());
			else return false;
			break;
		case Weapons:
			if (value.canConvert<QVector<Weapon*>>())
				pcs[row]->setWeapons(value.value<QVector<Weapon*>>());
			else return false;
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
