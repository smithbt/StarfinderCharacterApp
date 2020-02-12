#include "CharacterModel.h"

CharacterModel::CharacterModel(QObject *parent)
	: QAbstractListModel(parent),
	map(keyCount, QVariant())
{
}

CharacterModel::~CharacterModel()
{
	map.clear();
}

void CharacterModel::read(const QJsonObject& json)
{
	beginResetModel();

	if (json.contains("Name") && json.value("Name").isString()) {
		map.replace(Key::Name, json.value("Name").toString());
	}
	if (json.contains("Stamina") && json.value("Stamina").isObject()) {
		QJsonObject staminaObject = json.value("Stamina").toObject();
		Resource* stamina = new Resource(this);
		stamina->read(staminaObject);
		map.replace(Key::Stamina, QVariant::fromValue(stamina));
	}
	endResetModel();
}

void CharacterModel::write(QJsonObject& json) const
{
	for (int i = 0; i < map.size(); ++i) {
		if (i == Name)
			json.insert("Name", map.at(i).toString());
		if (i == Stamina) {
			QJsonObject staminaObject;
			map.at(i).value<Resource*>()->write(staminaObject);
			json.insert("Stamina", staminaObject);
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
