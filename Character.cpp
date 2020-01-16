#include "Character.h"

Character::Character(QObject* parent)
	: model(new CharacterModel(parent))
{
}

Character::~Character()
{
	delete model;
}

void Character::insertChild(QVariant& data, QModelIndex& root)
{
	if (root.data(Qt::UserRole).value<CharacterNode::Type>() == CharacterNode::Type::List) {
		// Get child type from root
		QModelIndex listTypeIndex = model->index(root.row(), 1);
		QVariant type = listTypeIndex.data(Qt::UserRole);

		model->insertRows(0, 1, root);
		QModelIndex index = model->index(0, 0, root);
		model->setData(index, type);
		index = model->index(0, 1, root);
		model->setData(index, data);
	}
}

void Character::setProperty(CharacterNode::Type t, QVariant& value) {
	if (t != CharacterNode::Type::List) {
		int row = model->typeRow(t);
		if (!row) {
			model->insertRows(row, 1);
			model->setData(model->index(row, 0), QVariant::fromValue(t));
		}
		QModelIndex index = model->index(row, 1);
		model->setData(index, value);
	}
}

bool Character::addWeapon(Weapon* w)
{
	QModelIndex wpnRoot = model->listTypeRoot(CharacterNode::Type::Weapon);
	insertChild(QVariant::fromValue<Weapon*>(w), wpnRoot);
	return true;
}

Ability* Character::getAbility(Ability::Score s)
{
	QModelIndex aRoot = model->listTypeRoot(CharacterNode::Type::Ability);
	int count = model->rowCount(aRoot);
	for (int i = 0; i < count; ++i) {
		QModelIndex aIndex = model->index(i, 1, aRoot);
		Ability* a = aIndex.data(Qt::UserRole).value<Ability*>();
		if (a->getEnum() == s) {
			return a;
		}
	}
	return nullptr;
}

void Character::setAbility(Ability* a)
{
	bool updated = false;
	QModelIndex aRoot = model->listTypeRoot(CharacterNode::Type::Ability);
	int count = model->rowCount(aRoot);
	for (int i = 0; i < count; ++i) {
		QModelIndex aIndex = model->index(i, 1, aRoot);
		Ability* modelA = aIndex.data(Qt::UserRole).value<Ability*>();
		if (modelA->getEnum() == a->getEnum()) {
			updated = model->setData(aIndex, QVariant::fromValue(a));
			break;
		}
	}
	if (!updated) insertChild(QVariant::fromValue(a), aRoot);
}

CharacterModel* Character::getModel()
{
	return model;
}

void Character::read(const QJsonObject& json)
{
	model->read(json);
}

void Character::write(QJsonObject& json) const
{
	model->write(json);
}
