#include "CharacterModel.h"

CharacterModel::CharacterModel(QObject *parent)
	: QAbstractListModel(parent),
	map(rows, QVariant())
{
}

CharacterModel::~CharacterModel()
{
	map.clear();
}

void CharacterModel::read(const QJsonObject& json)
{
	beginResetModel();
	map.clear();

	// Parse Strings
	if (json.contains("CharacterName") && json.value("CharacterName").isString()) {
		map.replace(CharacterName, json.value("CharacterName").toString());
	}
	// Parse Ints
	for (int iValue = BAB; iValue <= Will; ++iValue) {
		QString iKey = QMetaEnum::fromType<RowIndex>().valueToKey(iValue);
		if (json.contains(iKey) && json.value(iKey).isDouble())
			map.replace(iValue, json.value(iKey).toInt());
	}

	// Parse Resources
	if (json.contains("Stamina") && json.value("Stamina").isObject()) {
		QJsonObject staminaObject = json.value("Stamina").toObject();
		Resource* stamina = new Resource(this);
		stamina->read(staminaObject);
		map.replace(Stamina, QVariant::fromValue(stamina));
	}

	// Parse Abilities
	for (int aValue = Strength; aValue <= Charisma; ++aValue) {
		QString aKey = QMetaEnum::fromType<RowIndex>().valueToKey(aValue);
		if (json.contains(aKey) && json.value(aKey).isObject()) {
			QJsonObject aObj = json.value(aKey).toObject();
			Ability* a = new Ability(this);
			a->read(aObj);
			map.replace(aValue, QVariant::fromValue(a));
		}
	}

	endResetModel();
}

void CharacterModel::write(QJsonObject& json) const
{
	for (int i = 0; i < map.size(); ++i) {
		QString key = QMetaEnum::fromType<RowIndex>().valueToKey(i);
		if (map.at(i).canConvert<QString>()) {
			if (i == CharacterName)
				json.insert(key, map.at(i).toString());
		}
		if (map.at(i).canConvert<int>()) {
			if (i >= BAB && i <= Will) {
				json.insert(key, map.at(i).toInt());
			}
		}
		if (map.at(i).canConvert<Resource*>()) {
			if (i == Stamina) {
				QJsonObject rObject;
				map.at(i).value<Resource*>()->write(rObject);
				json.insert(key, rObject);
			}
		}
		if (map.at(i).canConvert<Ability*>()) {
			if (i >= Strength && i <= Charisma) {
				QJsonObject aObject;
				map.at(i).value<Ability*>()->write(aObject);
				json.insert(key, aObject);
			}
		}
	}
}

QVariant CharacterModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid()) // invalid index
		return QVariant();

	const int key = index.row();
	if (key >= map.size() || key < 0) // out of range
		return QVariant();

	if (role == Qt::DisplayRole || role == Qt::EditRole)
		return map.at(key);

	if (role == Resource_MaxRole && map.at(key).canConvert<Resource*>()) {
		return map.at(key).value<Resource*>()->max();
	}

	if (role == Resource_CurrentRole && map.at(key).canConvert<Resource*>()) {
		return map.at(key).value<Resource*>()->current();
	}

	return QVariant();
}

Qt::ItemFlags CharacterModel::flags(const QModelIndex& index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	return Qt::ItemIsEditable | QAbstractListModel::flags(index);
}

int CharacterModel::rowCount(const QModelIndex& parent) const
{
	return map.size();
}

bool CharacterModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (!index.isValid())
		return false;

	const int key = index.row();
	if (key > map.size() || key < 0)
		return false;

	if (role == Qt::EditRole || Qt::DisplayRole) {
		map.replace(index.row(), value);
		emit dataChanged(index, index, { Qt::DisplayRole, Qt::EditRole });
		return true;
	}

	if (map.at(key).canConvert<Resource*>()) {
		Resource* rsrc = map.at(key).value<Resource*>();
		if (role == Resource_MaxRole && rsrc->max() != value.toInt()) {
			rsrc->setMax(value.toInt());
			map.replace(key, QVariant::fromValue(rsrc));
			emit dataChanged(index, index, { Qt::DisplayRole, Qt::EditRole, Resource_MaxRole });
			return true;
		}
		if (role == Resource_CurrentRole && rsrc->current() != value.toInt()) {
			rsrc->setCurrent(value.toInt());
			map.replace(key, QVariant::fromValue(rsrc));
			emit dataChanged(index, index, { Qt::DisplayRole, Qt::EditRole, Resource_CurrentRole });
			return true;
		}
	}

	return false;
}
