#include "CharacterModel.h"

CharacterModel::CharacterModel(QObject *parent)
	: QAbstractListModel(parent),
	map()
{
}

CharacterModel::~CharacterModel()
{
	map.clear();
}

void CharacterModel::read(const QJsonObject& json)
{
	beginResetModel();

	if (json.contains("Abilities") && json.value("Abilities").isArray()) {
		QVector<Ability*> abilities(6);
		QJsonArray aArray = json.value("Abilities").toArray();
		for (int i = 0; i < aArray.size(); ++i) {
			QJsonObject aObj = aArray.at(i).toObject();
			Ability* a = new Ability();
			a->read(aObj);
			int ai = static_cast<int>(a->type);
			abilities.replace(ai, a);
		}
		map.insert(Key::Abilities, QVariant::fromValue(abilities));
	}
	if (json.contains("Classes") && json.value("Classes").isObject()) {
		QJsonObject cObj = json.value("Classes").toObject();
		ClassType* ct = new ClassType(this);
		ct->read(cObj);
		map.insert(Key::Classes, QVariant::fromValue(ct));
	}
	if (json.contains("Weapons") && json.value("Weapons").isArray()) {
		WeaponModel* wModel = new WeaponModel(this);
		QJsonArray wArray = json.value("Weapons").toArray();
		wModel->read(wArray);
		map.insert(Key::Weapons, QVariant::fromValue(wModel));
	}
	if (json.contains("Name") && json.value("Name").isString()) {
		map.insert(Key::Name, json.value("Name").toString());
	}
	endResetModel();
}

void CharacterModel::write(QJsonObject& json) const
{
	for (QMap<int, QVariant>::const_iterator i = map.cbegin(); i != map.cend(); ++i) {
		QString keyString = QMetaEnum::fromType<Key>().valueToKey(i.key());
		if (i.key() == Key::Name)
			json.insert(keyString, i.value().toString());
		if (i.key() == Key::Weapons) {
			QJsonArray weaponArray;
			i.value().value<WeaponModel*>()->write(weaponArray);
			json.insert(keyString, weaponArray);
		}
		if (i.key() == Key::Classes) {
			QJsonObject cObj;
			i.value().value<ClassType*>()->write(cObj);
			json.insert(keyString, cObj);
		}
		if (i.key() == Key::Abilities) {
			QJsonArray abilityArray;
			for (Ability* a : i.value().value<QVector<Ability*>>()) {
				QJsonObject aObj;
				a->write(aObj);
				abilityArray.insert(static_cast<int>(a->type), aObj);
			}
			json.insert(keyString, abilityArray);
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


	if (role == Qt::UserRole)
		return map.value(key);

	return QVariant();
}

Qt::ItemFlags CharacterModel::flags(const QModelIndex& index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	return Qt::ItemIsEditable | QAbstractListModel::flags(index);
}

QVariant CharacterModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return "Value";

	return QVariant();
}

int CharacterModel::rowCount(const QModelIndex& parent) const
{
	return map.size();
}

bool CharacterModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (index.isValid() && role == Qt::UserRole) {
		map.insert(index.row(), value);
		emit dataChanged(index, index, { Qt::DisplayRole, Qt::UserRole });
		return true;
	}
	return false;
}

bool CharacterModel::insertRows(int position, int rows, const QModelIndex& parent)
{
	Q_UNUSED(parent);
	beginInsertRows(QModelIndex(), position, position + rows - 1);

	for (QMap<int, QVariant>::const_iterator i = map.lowerBound(position); i != map.upperBound(position + rows); ++i) {
		map.insert(i.key(), QVariant());
	}

	endInsertRows();
	return true;
}

bool CharacterModel::removeRows(int position, int rows, const QModelIndex& parent)
{
	Q_UNUSED(parent);
	beginRemoveRows(QModelIndex(), position, position + rows - 1);

	for (QMap<int, QVariant>::const_iterator i = map.lowerBound(position); i != map.upperBound(position + rows); ++i) {
		map.remove(i.key());
	}

	endRemoveRows();
	return true;
}
