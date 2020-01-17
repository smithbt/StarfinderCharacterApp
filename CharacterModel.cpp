#include "CharacterModel.h"

CharacterModel::CharacterModel(QObject *parent)
	: QAbstractItemModel(parent)
{
	rootNode = new CharacterNode({ CharacterNode::Type::List, "Root"});
	
	setupModel();
}

CharacterModel::~CharacterModel()
{
	delete rootNode;
}

void CharacterModel::read(const QJsonObject& json)
{
	beginResetModel();
	QMetaEnum tQME = QMetaEnum::fromType<CharacterNode::Type>();
	// For each CharacterNode::Type
	for (int tIdx = 0; tIdx < tQME.keyCount(); ++tIdx) {

		QString tKey = tQME.key(tIdx);
		CharacterNode* cNode;

		if (json.contains(tKey)) {
			CharacterNode::Type tValue = static_cast<CharacterNode::Type>(tQME.value(tIdx));
			if (tValue == CharacterNode::CharacterNode::Type::List) {
				if (json[tKey].isArray()) {

					// get lists and create children
					QJsonArray listArray = json[tKey].toArray(); 
					rootNode->insertChildren(0, listArray.size()); 

					// set child data
					for (int c = 0; c < listArray.size(); ++c) {
						cNode = rootNode->child(c);
						cNode->setData(0, QVariant::fromValue(tValue)); // set type as List
						if (listArray[c].isObject()) {
							QJsonObject listObj = listArray[c].toObject();
							QString subType = listObj.keys()[0];
							cNode->setData(1, subType); // set subtype
							cNode->read(listObj);
						}
					}
				}
			}
			if (tValue == CharacterNode::Type::Name) {
				if (json[tKey].isString()) {
					cNode = new CharacterNode({ tValue, json[tKey].toString() }, rootNode);
					rootNode->appendChild(cNode);
				}
			}
			if (tValue == CharacterNode::Type::Weapon) {
				if (json[tKey].isObject()) {
					cNode = new CharacterNode({ tValue, QVariant("") }, rootNode);
					cNode->read(json[tKey].toObject());
					rootNode->appendChild(cNode);
				}
					
			}
			if (tValue == CharacterNode::Type::Ability) {
				if (json[tKey].isObject()) {
					cNode = new CharacterNode({ tValue, QVariant("") }, rootNode);
					cNode->read(json[tKey].toObject());
					rootNode->appendChild(cNode);
				}
			}
		}
	}
	//rootNode->read(json);
	endResetModel();
}

void CharacterModel::write(QJsonObject& json) const
{
	rootNode->write(json);
}

QVariant CharacterModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role != Qt::DisplayRole && role != Qt::UserRole)
		return QVariant();

	CharacterNode* item = static_cast<CharacterNode*>(index.internalPointer());

	return item->data(index.column(), role);
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
	if (role != Qt::UserRole)
		return false;

	CharacterNode* node = getNode(index);
	bool result = node->setData(index.column(), value);

	if (result)
		emit dataChanged(index, index, { Qt::DisplayRole, Qt::UserRole });

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
	const bool success = parentNode->insertChildren(position, rows);
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

void CharacterModel::setupModel()
{
	QFile loadFile(":/StarfinderCharacterApp/Resources/default.json");

	if (!loadFile.open(QIODevice::ReadOnly)) {
		qWarning("Error opening file.");
	}

	QByteArray loadData = loadFile.readAll();

	QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));

	read(loadDoc.object());
	loadFile.close();
}
