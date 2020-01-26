#include "Character.h"

Character::Character(QObject* parent)
	: QObject(parent),
	model(new CharacterModel(parent)),
	wModel(new WeaponModel(parent)),
	aModel(new AbilityModel(parent))
{
}

Character::~Character()
{
	delete model;
	delete aModel;
	delete wModel;
}

int Character::bab()
{
	return model->index(CharacterModel::Classes).data(Qt::UserRole).value<ClassType*>()->bab();
}

int Character::fort()
{
	return model->index(CharacterModel::Classes).data(Qt::UserRole).value<ClassType*>()->fort();
}

int Character::ref()
{
	return model->index(CharacterModel::Classes).data(Qt::UserRole).value<ClassType*>()->ref();
}

int Character::will()
{
	return model->index(CharacterModel::Classes).data(Qt::UserRole).value<ClassType*>()->will();
}

void Character::setProperty(CharacterModel::Key k, QVariant& value) 
{
	QModelIndex index = model->index(k);
	if (!index.isValid())
		model->insertRow(k);
	model->setData(model->index(k), value);
}

void Character::addWeapon(Weapon* w)
{
	wModel->insertRow(0);
	wModel->setData(wModel->index(0), QVariant::fromValue(w));
}

Ability* Character::getAbility(Ability::Score s)
{
	return aModel->index(static_cast<int>(s), 0).data(Qt::UserRole).value<Ability*>();
}

void Character::setAbility(Ability* a)
{
	aModel->setAbility(a);
}

void Character::read(const QJsonObject& json)
{
	model->read(json);
	wModel->read(json);
	aModel->read(json);
}

void Character::write(QJsonObject& json) const
{
	model->write(json);
	wModel->write(json);
	aModel->write(json);
}
