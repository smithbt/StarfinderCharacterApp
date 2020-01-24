#include "Character.h"

Character::Character(QObject* parent)
	: model(new CharacterModel(parent)),
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

void Character::setProperty(CharacterModel::Key k, QVariant& value) 
{
	QModelIndex index = model->index(k);
	if (!index.isValid())
		model->insertRow(0);
	model->setData(index, value);
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
