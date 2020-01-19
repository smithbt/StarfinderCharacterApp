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
    QMetaEnum tQME = QMetaEnum::fromType<Type>();
    if (json.contains("Ability") && json.value("Ability").isArray()) {
        CharacterNode* aRoot = new CharacterNode({ static_cast<Type>(tQME.keyToValue("List")), QVariant("Ability") }, this);
        QJsonArray aArray = json.value("Ability").toArray();
        for (int i = 0; i < aArray.size(); ++i) {
            QJsonObject aObj = aArray.at(i).toObject();
            Ability* a = new Ability();
            a->read(aObj);
            CharacterNode* cNode = new CharacterNode({ static_cast<Type>(tQME.keyToValue("Ability")), QVariant::fromValue(a) }, aRoot);
            aRoot->appendChild(cNode);
        }
        appendChild(aRoot);
    }
    if (json.contains("Weapon") && json.value("Weapon").isArray()) {
        CharacterNode* wRoot = new CharacterNode({ static_cast<Type>(tQME.keyToValue("List")), QVariant("Weapon") }, this);
        QJsonArray wArray = json.value("Weapon").toArray();
        for (int i = 0; i < wArray.size(); ++i) {
            QJsonObject wObj = wArray.at(i).toObject();
            if (wObj.contains("Type") && wObj.value("Type").isString()) {
                Weapon* w;
                Weapon::Type wType = static_cast<Weapon::Type>(
                    QMetaEnum::fromType<Weapon::Type>().keyToValue(wObj.value("Type").toString().toUtf8()));
                switch (wType) {
                case (Weapon::Type::Ranged):
                    w = new RangedWeapon();
                    break;
                case (Weapon::Type::Melee):
                    w = new MeleeWeapon();
                    break;
                default:
                    w = new Weapon();
                    break;
                }
                w->read(wObj);
                CharacterNode* cNode = new CharacterNode({ static_cast<Type>(tQME.keyToValue("Weapon")), QVariant::fromValue(w) }, wRoot);
                wRoot->appendChild(cNode);
            }
        }
        appendChild(wRoot);
    }
    if (json.contains("Name") && json.value("Name").isString()) {
        CharacterNode* cNode = new CharacterNode({ static_cast<Type>(tQME.keyToValue("Name")), json.value("Name").toString() }, this);
        appendChild(cNode);
    }
}

void CharacterNode::write(QJsonObject& json) const
{
    if (!parent) {
        for (CharacterNode* child : qAsConst(children))
            child->write(json);
    }
    else {
        QString tKey = QVariant::fromValue(itemData.first).toString();
        if (itemData.first == Type::Name)
            json.insert(tKey, itemData.second.toString());
        else if (itemData.first == Type::List) {
            // write childrem to JSON
            QJsonArray childArray;
            for (CharacterNode* child : qAsConst(children)) {
                QJsonObject cObj;
                child->write(cObj);
                childArray.append(cObj);
            }
            json.insert(itemData.second.toString(), childArray);
        }
        else if (itemData.first == Type::Ability && itemData.second.canConvert<Ability*>())
            itemData.second.value<Ability*>()->write(json);

        else if (itemData.first == Type::Weapon) {
            if (itemData.second.canConvert<RangedWeapon*>())
                itemData.second.value<RangedWeapon*>()->write(json);
            else if (itemData.second.canConvert<MeleeWeapon*>())
                itemData.second.value<MeleeWeapon*>()->write(json);
            else
                itemData.second.value<Weapon*>()->write(json);
        }
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

QVariant CharacterNode::data(int column, int role) const
{
	if (role == Qt::UserRole) {
		switch (column) {
		case 0: return QVariant::fromValue(itemData.first);
		case 1: return itemData.second;
		default: return QVariant();
		}
	}
	if (role == Qt::DisplayRole) {
		switch (column) {
		case 0: return QVariant::fromValue(itemData.first).toString();
		case 1: 
            switch (itemData.first) {
            case Type::Ability:
                return itemData.second.value<Ability*>()->toString();
            case Type::Weapon:
                if (itemData.second.canConvert<RangedWeapon*>())
                    return itemData.second.value<RangedWeapon*>()->toString();
                else if (itemData.second.canConvert<MeleeWeapon*>())
                    return itemData.second.value<MeleeWeapon*>()->toString();
            default:
                return itemData.second.toString();
            }
		}
		return QString();
	}
	return QVariant();
}

int CharacterNode::row() const
{
	if (parent)
		return parent->children.indexOf(const_cast<CharacterNode*>(this));

	return 0;
}

bool CharacterNode::insertChildren(int position, int count)
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

bool CharacterNode::setData(int column, const QVariant& value, int role)
{
	if (role == Qt::UserRole) {
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
	else return false;
}
