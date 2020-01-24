#include "AbilityModel.h"

AbilityModel::AbilityModel(QObject *parent)
	: QAbstractTableModel(parent),
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
		switch (index.column()) {
		case 0: return abilities.at(idx)->name();
		case 1: return abilities.at(idx)->score();
		case 2: return abilities.at(idx)->modifier();
		}

	return QVariant();
}

Qt::ItemFlags AbilityModel::flags(const QModelIndex& index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

QVariant AbilityModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if (orientation == Qt::Horizontal)
		switch (section) {
		case 0: return "Ability";
		case 1: return "Score";
		case 2: return "Modifier";
		}

	return QVariant();
}

int AbilityModel::rowCount(const QModelIndex& parent) const
{
	return abilities.size();
}

int AbilityModel::columnCount(const QModelIndex& parent) const
{
	return 3;
}

bool AbilityModel::setAbility(Ability* a)
{
	const int row = static_cast<int>(a->type);
	abilities.replace(row, a);
	emit dataChanged(index(row, 0), index(row, columnCount()), { Qt::DisplayRole, Qt::UserRole });
	return true;
}
