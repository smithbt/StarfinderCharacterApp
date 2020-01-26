#include "AbilityModel.h"

AbilityModel::AbilityModel(QObject *parent)
	: QAbstractListModel(parent),
	abilities(6)
{
}

AbilityModel::~AbilityModel()
{
	qDeleteAll(abilities);
}

void AbilityModel::read(const QJsonObject& json)
{
	beginResetModel();

	if (json.contains("Abilities") && json.value("Abilities").isArray()) {
		QJsonArray aArray = json.value("Abilities").toArray();
		abilities.clear();
		for (int i = 0; i < aArray.size(); ++i) {
			QJsonObject aObj = aArray.at(i).toObject();
			Ability* a = new Ability();
			a->read(aObj);
			int ai = static_cast<int>(a->type);
			abilities.insert(ai, a);
		}
	}

	endResetModel();
}

void AbilityModel::write(QJsonObject& json) const
{
	QJsonArray aArray;
	for (Ability* a : abilities) {
		QJsonObject aObj;
		a->write(aObj);
		aArray.insert(static_cast<int>(a->type), aObj);
	}
	json.insert("Abilities", aArray);
}

QVariant AbilityModel::data(const QModelIndex& index, int role) const
{
	const int idx = index.row();
	if (!index.isValid()) // invalid index
		return QVariant();

	if (idx >= abilities.size() || idx < 0) // out of range
		return QVariant();

	if (role == Qt::UserRole)
		return QVariant::fromValue(abilities.at(idx));

	if (role == Qt::DisplayRole)
		return abilities.at(idx)->toString();

	return QVariant();
}

Qt::ItemFlags AbilityModel::flags(const QModelIndex& index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	return Qt::ItemIsEditable | QAbstractListModel::flags(index);
}

QVariant AbilityModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if (orientation == Qt::Horizontal)
		return "Ability: Score [Modifier]";

	return QVariant();
}

int AbilityModel::rowCount(const QModelIndex& parent) const
{
	return abilities.size();
}

bool AbilityModel::setAbility(Ability* a)
{
	const int row = static_cast<int>(a->type);
	abilities.replace(row, a);
	emit dataChanged(index(row, 0), index(row, 0), { Qt::DisplayRole, Qt::UserRole });
	return true;
}
