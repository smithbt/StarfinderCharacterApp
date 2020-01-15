#include "CharacterModel.h"

CharacterModel::CharacterModel(QObject *parent)
	: QAbstractItemModel(parent)
{
	rootNode = new CharacterNode({ CharacterNode::Type::List, "Root"});
	
	setupModel(rootNode);
}

CharacterModel::~CharacterModel()
{
	delete rootNode;
}

void CharacterModel::read(const QJsonObject& json)
{
	rootNode->read(json);
}

void CharacterModel::write(QJsonObject& json) const
{
	rootNode->write(json);
}

QVariant CharacterModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role != Qt::DisplayRole)
		return QVariant();

	CharacterNode* item = static_cast<CharacterNode*>(index.internalPointer());

	return item->data(index.column());
}

Qt::ItemFlags CharacterModel::flags(const QModelIndex& index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

QVariant CharacterModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return rootNode->data(section);

	return QVariant();
}

QModelIndex CharacterModel::index(int row, int column, const QModelIndex& parent) const
{
	if (parent.isValid() && parent.column() != 0)
		return QModelIndex();

	CharacterNode* parentNode = getNode(parent);
	if (!parentNode)
		return QModelIndex();

	CharacterNode* childNode = parentNode->child(row);
	if (childNode)
		return createIndex(row, column, childNode);
	return QModelIndex();
}

QModelIndex CharacterModel::parent(const QModelIndex& index) const
{
	if (!index.isValid())
		return QModelIndex();

	CharacterNode* childNode = getNode(index);
	CharacterNode* parentNode = childNode ? childNode->parentNode() : nullptr;

	if (parentNode == rootNode || !parentNode)
		return QModelIndex();

	return createIndex(parentNode->row(), 0, parentNode);
}

QModelIndex CharacterModel::listTypeRoot(CharacterNode::Type t) const
{
	for (int i = 0; i < rootNode->childCount(); ++i) {
		CharacterNode* cn = rootNode->child(i);
		if (cn->data(0).value<CharacterNode::Type>() == CharacterNode::Type::List
			&& cn->data(1).value<CharacterNode::Type>() == t)
			return createIndex(i, 0, cn);
	}
	return QModelIndex();
}

int CharacterModel::typeRow(CharacterNode::Type type) const
{
	for (int i = 0; i < rootNode->childCount(); ++i) {
		if (rootNode->child(i)->data(0).value<CharacterNode::Type>() == type)
			return i;
	}
	return 0;
}

int CharacterModel::rowCount(const QModelIndex& parent) const
{
	const CharacterNode* parentNode = getNode(parent);

	return parentNode ? parentNode->childCount() : 0;
}

int CharacterModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent);
	return rootNode->columnCount();
}

bool CharacterModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (role != Qt::EditRole)
		return false;

	CharacterNode* node = getNode(index);
	bool result = node->setData(index.column(), value);

	if (result)
		emit dataChanged(index, index, { Qt::DisplayRole, Qt::EditRole });

	return result;
}

bool CharacterModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant& value, int role)
{
	if (role != Qt::EditRole || orientation != Qt::Horizontal)
		return false;

	const bool result = rootNode->setData(section, value);

	if (result)
		emit headerDataChanged(orientation, section, section);

	return result;
}

bool CharacterModel::insertRows(int position, int rows, const QModelIndex& parent)
{
	CharacterNode* parentNode = getNode(parent);
	if (!parentNode)
		return false;

	beginInsertRows(parent, position, position + rows - 1);
	const bool success = parentNode->insertChildren(position, rows, rootNode->columnCount());
	endInsertRows();

	return success;
}

bool CharacterModel::removeRows(int position, int rows, const QModelIndex& parent)
{
	CharacterNode* parentNode = getNode(parent);
	if (!parentNode)
		return false;

	beginRemoveRows(parent, position, position + rows - 1);
	const bool success = parentNode->removeChildren(position, rows);
	endRemoveRows();

	return success;
}

CharacterNode* CharacterModel::getNode(const QModelIndex& index) const
{
	if (index.isValid()) {
		CharacterNode* node = static_cast<CharacterNode*>(index.internalPointer());
		if (node)
			return node;
	}
	return rootNode;
}

void CharacterModel::setupModel(CharacterNode* parent)
{
	CharacterNode* node = new CharacterNode(
		{ CharacterNode::Type::List, QVariant::fromValue(CharacterNode::Type::Weapon) }, parent);
	parent->appendChild(node);

	node = new CharacterNode({ CharacterNode::Type::Name, QString() }, parent);
	parent->appendChild(node);

	node = new CharacterNode(
		{ CharacterNode::Type::List, QVariant::fromValue(CharacterNode::Type::Ability) }, parent);
	QMetaEnum aEnum = QMetaEnum::fromType<Ability::Score>();
	for (int i = 0; i < aEnum.keyCount(); ++i) {
		Ability* a = new Ability(static_cast<Ability::Score>(aEnum.value(i)));
		CharacterNode* aChild = new CharacterNode({ CharacterNode::Type::Ability, QVariant::fromValue(a) }, node);
		node->appendChild(aChild);
	}
	parent->appendChild(node);
}
