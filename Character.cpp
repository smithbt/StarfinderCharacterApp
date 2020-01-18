#include "Character.h"

Character::Character(QObject* parent)
	: model(new CharacterModel(parent))
{
}

Character::~Character()
{
	delete model;
}

void Character::insertChild(QVariant& data, QModelIndex& parent)
{
	if (parent.data(Qt::UserRole).value<CharacterNode::Type>() == CharacterNode::Type::List) {
		// Get child type from root
		QModelIndex listTypeIndex = model->index(parent.row(), 1);
		QVariant type = listTypeIndex.data(Qt::UserRole);

		model->insertRow(0, parent);
		QModelIndex index = model->index(0, 0, parent);
		model->setData(index, type);
		index = model->index(0, 1, parent);
		model->setData(index, data);
	}
}

void Character::setProperty(CharacterNode::Type t, QVariant& value) {
	if (t != CharacterNode::Type::List) {
		int row = model->typeRow(t);
		if (row < 0) {
			model->insertRow(0);
			model->setData(model->index(0, 0), QVariant::fromValue(t));
		}
		QModelIndex index = model->index(row, 1);
		model->setData(index, value);
	}
}

bool Character::addWeapon(QVariant& value)
{
	QModelIndex wpnRoot = model->listTypeRoot(CharacterNode::Type::Weapon);
	insertChild(value, wpnRoot);
	return true;
}

QModelIndex Character::getAbilityIndex(Ability::Score s)
{
	QModelIndex aRoot = model->listTypeRoot(CharacterNode::Type::Ability);
	int count = model->rowCount(aRoot);
	for (int i = 0; i < count; ++i) {
		QModelIndex aIndex = model->index(i, 1, aRoot);
		if (aIndex.data(Qt::UserRole).canConvert<Ability*>() && 
			aIndex.data(Qt::UserRole).value<Ability*>()->type == s) {
			return aIndex;
		}
	}
	return QModelIndex();
}

Ability* Character::getAbility(Ability::Score s)
{
	QModelIndex aIndex = getAbilityIndex(s);
	return aIndex.data(Qt::UserRole).value<Ability*>();
}

void Character::setAbility(Ability* a)
{
	bool updated = false;
	QModelIndex aIndex = getAbilityIndex(a->type);
	updated = model->setData(aIndex, QVariant::fromValue(a));

	if (!updated) {
		QModelIndex aRoot = model->listTypeRoot(CharacterNode::Type::Ability);
		insertChild(QVariant::fromValue(a), aRoot);
	}
}

void Character::read(const QJsonObject& json)
{
	model->read(json);
}

void Character::write(QJsonObject& json) const
{
	model->write(json);
}
