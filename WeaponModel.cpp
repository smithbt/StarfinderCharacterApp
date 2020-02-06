#include "WeaponModel.h"

WeaponModel::WeaponModel(QObject* parent)
	: QAbstractListModel(parent),
	weapons()
{
}

WeaponModel::~WeaponModel()
{
	qDeleteAll(weapons);
}

void WeaponModel::read(const QJsonObject& json)
{
	beginResetModel();
	if (json.contains("Weapons") && json.value("Weapons").isArray()) {
		QJsonArray wArray = json.value("Weapons").toArray();
		for (int i = 0; i < wArray.size(); ++i) {
			QJsonObject wObj = wArray.at(i).toObject();
			Weapon* w = new Weapon();
			w->read(wObj);
			weapons.append(w);
		}
	}
	endResetModel();
}

void WeaponModel::write(QJsonObject& json) const
{
	QJsonArray wArray;
	for (Weapon* w : weapons) {
		QJsonObject wObj;
		w->write(wObj);
		wArray.append(wObj);
	}
	json.insert("Weapons", wArray);
}

QVariant WeaponModel::data(const QModelIndex& index, int role) const
{
	const int idx = index.row();
	if (!index.isValid()) // invalid index
		return QVariant();

	if (idx >= weapons.size() || idx < 0) // out of range
		return QVariant();

	if (role == Qt::DisplayRole || role == Qt::EditRole)
		return QVariant::fromValue(weapons.at(idx));

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
	return weapons.size();
}

bool WeaponModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (index.isValid() && role == Qt::EditRole && value.canConvert<Weapon*>()) {
		weapons.replace(index.row(), value.value<Weapon*>());
		emit dataChanged(index, index, { Qt::DisplayRole, Qt::EditRole });
		return true;
	}
	return false;
}

bool WeaponModel::insertRows(int position, int rows, const QModelIndex& parent)
{
	Q_UNUSED(parent);
	beginInsertRows(QModelIndex(), position, position + rows - 1);

	for (int i = position; i < (position + rows); ++i) {
		weapons.insert(i, nullptr);
	}

	endInsertRows();
	return true;
}

bool WeaponModel::removeRows(int position, int rows, const QModelIndex& parent)
{
	Q_UNUSED(parent);
	beginRemoveRows(QModelIndex(), position, position + rows - 1);

	for (int i = position; i < (position + rows); ++i) {
		weapons.removeAt(i);
	}

	endRemoveRows();
	return true;
}
