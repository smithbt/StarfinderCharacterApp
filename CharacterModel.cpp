#include "CharacterModel.h"

CharacterModel::CharacterModel(QObject* parent)
	: QAbstractTableModel(parent),
	pcs(),
	columns(QMetaEnum::fromType<Character::ColumnIndex>().keyCount())
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

	if (role == Qt::DisplayRole || role == Qt::EditRole)
		return QVariant::fromValue(pcs.at(row)->getProperty(index.column()));

	if (role == Qt::UserRole)
		return QVariant::fromValue(pcs.at(row));

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
		Character* thisPC = pcs.at(row);
		thisPC->setProperty(index.column(), value);
		emit dataChanged(index, index, { Qt::DisplayRole, Qt::EditRole });
		return true;
	}

	if (role == Qt::UserRole && value.canConvert<Character*>()) {
		pcs.insert(row, value.value<Character*>());
		emit dataChanged(this->index(row, 0), this->index(row, columns), { Qt::DisplayRole, Qt::EditRole, Qt::UserRole });
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
