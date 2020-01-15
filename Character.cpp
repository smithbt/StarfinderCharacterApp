#include "Character.h"

Character::Character(QObject* parent)
	: model(new CharacterModel(parent))
{
}

Character::~Character()
{
	delete model;
}

void Character::insertChild(QPair<CharacterNode::Type, QVariant> data, QModelIndex& root)
{
	model->insertRows(0, 1, root);
	QModelIndex index = model->index(0, 0, root);
	model->setData(index, QVariant::fromValue(data.first));
	index = model->index(0, 1, root);
	model->setData(index, data.second);
}

void Character::setProperty(CharacterNode::Type t, QVariant& value) {
	if (t != CharacterNode::Type::List) {
		int row = model->typeRow(t);
		if (row) {
			QModelIndex index = model->index(row, 1);
			model->setData(index, value);
		}
	}
}

bool Character::addWeapon(Weapon* w)
{
	QModelIndex wpnRoot = model->getWeaponList();
	insertChild({ CharacterNode::Type::Weapon, QVariant::fromValue<Weapon*>(w) }, wpnRoot);
	return true;
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
