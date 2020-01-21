#include "Character.h"

Character::Character(QObject* parent)
	: model(new CharacterModel(parent))
{
}

Character::~Character()
{
	delete model;
}

void Character::setProperty(CharacterModel::Key k, QVariant& value) 
{
	QModelIndex index = model->index(k, 1);
	model->setData(index, value);
}

void Character::addWeapon(Weapon* w)
{
	QModelIndex wIndex = model->index(CharacterModel::Key::Weapons, 1);
	QVector<Weapon*> weapons = model->data(wIndex).value<QVector<Weapon*>>();
	weapons.append(w);
	model->setData(wIndex, QVariant::fromValue(weapons));
}

Ability* Character::getAbility(Ability::Score s)
{
	QVector<Ability*> abilities = model->data(model->index(CharacterModel::Key::Abilities, 1)).value<QVector<Ability*>>();
	return abilities.at(static_cast<int>(s));
}

void Character::setAbility(Ability* a)
{
	QModelIndex aIndex =  model->index(CharacterModel::Key::Abilities, 1);
	QVector<Ability*> abilities = model->data(aIndex).value<QVector<Ability*>>();
	abilities.insert(static_cast<int>(a->type), a);
	model->setData(aIndex, QVariant::fromValue(abilities));
}

void Character::read(const QJsonObject& json)
{
	model->read(json);
}

void Character::write(QJsonObject& json) const
{
	model->write(json);
}
