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

	// Parse Strings
	if (json.contains("Name") && json.value("Name").isString()) {
		map.replace(Name, json.value("Name").toString());
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
			if (i == Name)
				json.insert(key, map.at(i).toString());
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
	const int key = index.row();
	if (!index.isValid()) // invalid index
		return QVariant();

	if (key >= map.size() || key < 0) // out of range
		return QVariant();


	if (role == Qt::DisplayRole || role == Qt::EditRole)
		return map.at(key);

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
	if (index.isValid() && role == Qt::EditRole) {
		map.replace(index.row(), value);
		emit dataChanged(index, index, { Qt::DisplayRole, Qt::EditRole });
		return true;
	}
	return false;
}
