#include "CharacterModel.h"

CharacterModel::CharacterModel(QObject *parent)
	: QAbstractListModel(parent),
	map(2, QVariant())
{
}

CharacterModel::~CharacterModel()
{
	map.clear();
}

void CharacterModel::read(const QJsonObject& json)
{
	beginResetModel();

	if (json.contains("Classes") && json.value("Classes").isObject()) {
		QJsonObject cObj = json.value("Classes").toObject();
		ClassType* ct = new ClassType(this);
		ct->read(cObj);
		map.replace(Key::Classes, QVariant::fromValue(ct));
	}
	if (json.contains("Name") && json.value("Name").isString()) {
		map.replace(Key::Name, json.value("Name").toString());
	}
	endResetModel();
}

void CharacterModel::write(QJsonObject& json) const
{
	for (int i = 0; i < map.size(); ++i) {
		QString keyString = QMetaEnum::fromType<Key>().valueToKey(i);
		if (i == Key::Name)
			json.insert(keyString, map.at(i).toString());
		if (i == Key::Classes) {
			QJsonObject cObj;
			map.at(i).value<ClassType*>()->write(cObj);
			json.insert(keyString, cObj);
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

bool CharacterModel::insertRows(int position, int rows, const QModelIndex& parent)
{
	Q_UNUSED(parent);
	beginInsertRows(QModelIndex(), position, position + rows - 1);

	for (int i = (position); i < (position + rows); ++i) {
		map.insert(i, QVariant());
	}

	endInsertRows();
	return true;
}

bool CharacterModel::removeRows(int position, int rows, const QModelIndex& parent)
{
	Q_UNUSED(parent);
	beginRemoveRows(QModelIndex(), position, position + rows - 1);

	for (int i = (position); i < (position + rows); ++i) {
		map.remove(i);
	}

	endRemoveRows();
	return true;
}
