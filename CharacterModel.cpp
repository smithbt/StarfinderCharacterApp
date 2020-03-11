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
		case FullObject: return QVariant::fromValue(pcs.at(index.row()));
		case RaceData: return QVariant::fromValue(pcs.at(index.row())->getRace());
		case CharacterName: return pcs.at(index.row())->getCharacterName();
		case BAB: return pcs.at(index.row())->getBAB();
		case Fortitude: return pcs.at(index.row())->getFortitude();
		case Reflex: return pcs.at(index.row())->getReflex();
		case Will: return pcs.at(index.row())->getWill();
		case Stamina: return QVariant::fromValue(pcs.at(index.row())->getStamina());
		case HitPoints: return QVariant::fromValue(pcs.at(row)->getHP());
		case Resolve: return QVariant::fromValue(pcs.at(row)->getResolve());
		case Strength: return QVariant::fromValue(pcs.at(index.row())->getAbility("Strength"));
		case Dexterity: return QVariant::fromValue(pcs.at(index.row())->getAbility("Dexterity"));
		case Constitution: return QVariant::fromValue(pcs.at(index.row())->getAbility("Constitution"));
		case Intelligence: return QVariant::fromValue(pcs.at(index.row())->getAbility("Intelligence"));
		case Wisdom: return QVariant::fromValue(pcs.at(index.row())->getAbility("Wisdom"));
		case Charisma: return QVariant::fromValue(pcs.at(index.row())->getAbility("Charisma"));
		case Weapons: return QVariant::fromValue(pcs.at(index.row())->getWeapons());
		}
	}

	if (role == Class_NameRole && index.column() == ClassData) {
		return pcs[row]->getClassName();
	}

	if (role == Class_LevelRole && index.column() == ClassData) {
		return pcs[row]->getClassLevel();
	}

	if (role == Resource_CurrentRole) {
		switch (index.column()) {
		case Stamina: return pcs.at(index.row())->getStamina()->current();
		case HitPoints: return pcs.at(index.row())->getHP()->current();
		case Resolve: return pcs.at(row)->getResolve()->current();
		}
	}

	if (role == Resource_MaxRole) {
		switch (index.column()) {
		case Stamina: return pcs.at(index.row())->getStamina()->max();
		case HitPoints: return pcs.at(index.row())->getHP()->max();
		case Resolve: return pcs.at(row)->getResolve()->max();
		}
	}

	if (role == Resource_StepRole) {
		switch (index.column()) {
		case Stamina: return pcs.at(index.row())->getStamina()->step();
		case HitPoints: return pcs.at(index.row())->getHP()->step();
		case Resolve: return pcs.at(row)->getResolve()->step();
		}
	}

	if (role == Ability_BaseRole) {
		QString ability = abilityNameFromColumn(index.column());
		if (!ability.isEmpty() && !ability.isNull())
			return pcs.at(row)->getAbilityProperty(ability, "base");
	}

	if (role == Ability_UpgradeRole) {
		QString ability = abilityNameFromColumn(index.column());
		if (!ability.isEmpty() && !ability.isNull())
			return pcs.at(row)->getAbilityProperty(ability, "upgrade");
	}

	if (role == Ability_ScoreRole) {
		QString ability = abilityNameFromColumn(index.column());
		if (!ability.isEmpty() && !ability.isNull())
			return pcs.at(row)->getAbilityProperty(ability, "score");
	}

	if (role == Ability_ModifierRole) {
		QString ability = abilityNameFromColumn(index.column());
		if (!ability.isEmpty() && !ability.isNull())
			return pcs.at(row)->getAbilityProperty(ability, "modifier");
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
		case FullObject:
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
		case Stamina:
			if (value.canConvert<Resource*>())
				pcs[row]->setStamina(value.value<Resource*>());
			else return false;
			break;
		case HitPoints:
			if (value.canConvert<Resource*>())
				pcs[row]->setHP(value.value<Resource*>());
			else return false;
			break;
		case Resolve:
			if (value.canConvert<Resource*>())
				pcs[row]->setResolve(value.value<Resource*>());
			else return false;
			break;
		case Strength:
			if (value.canConvert<Ability*>())
				pcs[row]->setAbility("Strength", value.value<Ability*>());
			else return false;
			break;
		case Dexterity:
			if (value.canConvert<Ability*>()) {
				pcs[row]->setAbility("Dexterity", value.value<Ability*>());
				emit dataChanged(this->index(row, Reflex), this->index(row, Reflex), { Qt::DisplayRole, Qt::EditRole });
			}
			else return false;
			break;
		case Constitution:
			if (value.canConvert<Ability*>()) {
				pcs[row]->setAbility("Constitution", value.value<Ability*>());
				emit dataChanged(this->index(row, Fortitude), this->index(row, Fortitude), { Qt::DisplayRole, Qt::EditRole });
				emit dataChanged(this->index(row, Stamina), this->index(row, Stamina), { Qt::DisplayRole, Qt::EditRole, Resource_MaxRole });
			}
			else return false;
			break;
		case Intelligence:
			if (value.canConvert<Ability*>())
				pcs[row]->setAbility("Intelligence", value.value<Ability*>());
			else return false;
			break;
		case Wisdom:
			if (value.canConvert<Ability*>()) {
				pcs[row]->setAbility("Wisdom", value.value<Ability*>());
				emit dataChanged(this->index(row, Will), this->index(row, Will), { Qt::DisplayRole, Qt::EditRole });
			}
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
		if (value.canConvert<Ability*>() && (pcs.at(row)->getKeyAbility() == abilityNameFromColumn(index.column())))
			emit dataChanged(this->index(row, Resolve), this->index(row, Resolve), { Qt::DisplayRole, Qt::EditRole, Resource_MaxRole });
		emit dataChanged(index, index, { Qt::DisplayRole, Qt::EditRole });
		return true;
	}

	if (role == Class_NameRole && index.column() == ClassData) {
		pcs[row]->setClassName(value.toString());
		emit dataChanged(index, index, { Qt::DisplayRole, Qt::EditRole, role });
	}

	if (role == Class_LevelRole && index.column() == ClassData) {
		pcs[row]->setClassLevel(value.toInt());
		emit dataChanged(this->index(row, BAB), this->index(row, Resolve), { Qt::DisplayRole, Qt::EditRole, Resource_MaxRole });
		emit dataChanged(index, index, { Qt::DisplayRole, Qt::EditRole, role });
	}

	if (role == Resource_CurrentRole) {
		switch (index.column()) {
		case Stamina:
			pcs[row]->getStamina()->setCurrent(value.toInt());
			break;
		case HitPoints:
			pcs[row]->getHP()->setCurrent(value.toInt());
			break;
		case Resolve:
			pcs[row]->getResolve()->setCurrent(value.toInt());
			break;
		default: return false;
		}
		emit dataChanged(index, index, { Qt::DisplayRole, Qt::EditRole, role });
		return true;
	}

	if (role == Resource_MaxRole) {
		switch (index.column()) {
		case Stamina:
			pcs[row]->getStamina()->setMax(value.toInt());
			break;
		case HitPoints:
			pcs[row]->getHP()->setMax(value.toInt());
			break;
		case Resolve:
			pcs[row]->getResolve()->setMax(value.toInt());
			break;
		default: return false;
		}
		emit dataChanged(index, index, { Qt::DisplayRole, Qt::EditRole, role });
		return true;
	}

	if (role == Resource_StepRole) {
		switch (index.column()) {
		case Stamina:
			pcs[row]->getStamina()->setStep(value.toInt());
			break;
		case HitPoints:
			pcs[row]->getHP()->setStep(value.toInt());
			break;
		case Resolve:
			pcs[row]->getResolve()->setStep(value.toInt());
			break;
		default: return false;
		}
		emit dataChanged(index, index, { Qt::DisplayRole, Qt::EditRole, role });
		return true;
	}

	if (role == Ability_BaseRole) {
		switch (index.column()) {
		case Strength:
			pcs[index.row()]->setAbilityProperty("Strength", "base", value.toInt());
			break;
		case Dexterity:
			pcs[index.row()]->setAbilityProperty("Dexterity", "base", value.toInt());
			emit dataChanged(this->index(row, Reflex), this->index(row, Reflex), { Qt::DisplayRole, Qt::EditRole });
			break;
		case Constitution:
			pcs[index.row()]->setAbilityProperty("Constitution", "base", value.toInt());
			emit dataChanged(this->index(row, Fortitude), this->index(row, Fortitude), { Qt::DisplayRole, Qt::EditRole });
			emit dataChanged(this->index(row, Stamina), this->index(row, Stamina), { Qt::DisplayRole, Qt::EditRole, Resource_MaxRole });
			break;
		case Intelligence:
			pcs[index.row()]->setAbilityProperty("Intelligence", "base", value.toInt());
			break;
		case Wisdom:
			pcs[index.row()]->setAbilityProperty("Wisdom", "base", value.toInt());
			emit dataChanged(this->index(row, Will), this->index(row, Will), { Qt::DisplayRole, Qt::EditRole });
			break;
		case Charisma:
			pcs[index.row()]->setAbilityProperty("Charisma", "base", value.toInt());
			break;
		default: return false;
		}
		if (pcs.at(row)->getKeyAbility() == abilityNameFromColumn(index.column()))
			emit dataChanged(this->index(row, Resolve), this->index(row, Resolve), { Qt::DisplayRole, Qt::EditRole, Resource_MaxRole });
		emit dataChanged(index, index, { Qt::DisplayRole, Qt::EditRole, Ability_BaseRole, Ability_ScoreRole, Ability_ModifierRole });
		return true;
	}

	if (role == Ability_UpgradeRole) {
		switch (index.column()) {
		case Strength:
			pcs[index.row()]->setAbilityProperty("Strength", "upgrade", value.toInt());
			break;
		case Dexterity:
			pcs[index.row()]->setAbilityProperty("Dexterity", "upgrade", value.toInt());
			emit dataChanged(this->index(row, Reflex), this->index(row, Reflex), { Qt::DisplayRole, Qt::EditRole });
			break;
		case Constitution:
			pcs[index.row()]->setAbilityProperty("Constitution", "upgrade", value.toInt());
			emit dataChanged(this->index(row, Fortitude), this->index(row, Fortitude), { Qt::DisplayRole, Qt::EditRole });
			emit dataChanged(this->index(row, Stamina), this->index(row, Stamina), { Qt::DisplayRole, Qt::EditRole, Resource_MaxRole });
			break;
		case Intelligence:
			pcs[index.row()]->setAbilityProperty("Intelligence", "upgrade", value.toInt());
			break;
		case Wisdom:
			pcs[index.row()]->setAbilityProperty("Wisdom", "upgrade", value.toInt());
			emit dataChanged(this->index(row, Will), this->index(row, Will), { Qt::DisplayRole, Qt::EditRole });
			break;
		case Charisma:
			pcs[index.row()]->setAbilityProperty("Charisma", "upgrade", value.toInt());
			break;
		default: return false;
		}
		if (pcs.at(row)->getKeyAbility() == abilityNameFromColumn(index.column()))
			emit dataChanged(this->index(row, Resolve), this->index(row, Resolve), { Qt::DisplayRole, Qt::EditRole, Resource_MaxRole });
		emit dataChanged(index, index, { Qt::DisplayRole, Qt::EditRole, Ability_UpgradeRole, Ability_ScoreRole, Ability_ModifierRole });
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

QString CharacterModel::abilityNameFromColumn(int column) const
{
	switch (column) {
	case Strength: return "Strength";
	case Dexterity: return "Dexterity";
	case Constitution: return "Constitution";
	case Intelligence: return "Intelligence";
	case Wisdom: return "Wisdom";
	case Charisma: return "Charisma";
	}
	return QString();
}
