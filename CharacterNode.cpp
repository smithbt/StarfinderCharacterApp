#include "CharacterNode.h"

CharacterNode::CharacterNode(const QPair<Type, QVariant>& data, CharacterNode* parentItem)
	: itemData(data), parent(parentItem)
{
}

CharacterNode::~CharacterNode()
{
	qDeleteAll(children);
}

void CharacterNode::read(const QJsonObject& json)
{
	if (!parent) {
		for (CharacterNode* child : qAsConst(children))
			child->read(json);
	}
	else {
		if (itemData.first == Type::Name) {
			if (json.contains("Name") && json["Name"].isString())
				itemData.second = json["Name"].toString();
		}
		else if (itemData.first == Type::List) {
			QString listName = itemData.second.toString();
			if (json.contains(listName) && json[listName].isArray()) {
				removeChildren(0, childCount());
				QJsonArray childArray = json[listName].toArray();
				for (int i = 0; i < childArray.size(); ++i) {
					Type listType = static_cast<Type>(itemData.second.toInt());
					CharacterNode* node = new CharacterNode({ listType, QVariant("") }, this);
					node->read(json);
					appendChild(node);
				}
			}
		}
		else if (itemData.first == Type::Weapon) {
			Weapon* w = new Weapon();
			w->read(json);
			itemData.second = QVariant::fromValue(w);
		}
		else if (itemData.first == Type::Ability) {
			Ability* a = new Ability();
			a->read(json);
			itemData.second = QVariant::fromValue(a);
		}
	}
}

void CharacterNode::write(QJsonObject& json) const
{
	if (!parent) {
		for (CharacterNode* child : qAsConst(children))
			child->write(json);
	}
	else {
		if (itemData.first == Type::Name)
			json["Name"] = itemData.second.toString();
		else if (itemData.first == Type::List) {
			QJsonArray childArray;
			for (CharacterNode* child : qAsConst(children)) {
				QJsonObject cObj;
				child->write(cObj);
				childArray.append(cObj);
			}
			json[itemData.second.toString()] = childArray;
		}
		else if (itemData.first == Type::Ability && itemData.second.canConvert<Ability*>())
				itemData.second.value<Ability*>()->write(json);
		else if (itemData.first == Type::Weapon && itemData.second.canConvert<Weapon*>())
				itemData.second.value<Weapon*>()->write(json);
	}
}

void CharacterNode::appendChild(CharacterNode* child)
{
	children.append(child);
}

CharacterNode* CharacterNode::child(int row)
{
	if (row < 0 || row >= children.size())
		return nullptr;
	return children.at(row);
}

int CharacterNode::childCount() const
{
	return children.size();
}

int CharacterNode::columnCount() const
{
	return 2;
}

QVariant CharacterNode::data(int column) const
{
	switch (column) {
	case 0: return QVariant::fromValue(itemData.first);
	case 1: return itemData.second;
	default: return QVariant();
	}
}

int CharacterNode::row() const
{
	if (parent)
		return parent->children.indexOf(const_cast<CharacterNode*>(this));

	return 0;
}

bool CharacterNode::insertChildren(int position, int count, int columns)
{
	if (position < 0 || position > children.size())
		return false;

	for (int row = 0; row < count; ++row) {
		CharacterNode* item = new CharacterNode(QPair<Type, QVariant>(), this);
		children.insert(position, item);
	}

	return true;
}

CharacterNode* CharacterNode::parentNode()
{
	return parent;
}

bool CharacterNode::removeChildren(int position, int count)
{
	if (position < 0 || position + count > children.size())
		return false;

	for (int row = 0; row < count; ++row)
		delete children.takeAt(position);

	return true;
}

bool CharacterNode::setData(int column, const QVariant& value)
{
	switch (column) {
	case 0: 
		itemData.first = value.value<Type>(); 
		break;
	case 1: 
		itemData.second = value; 
		break;
	default: return false;
	}
	return true;
}
