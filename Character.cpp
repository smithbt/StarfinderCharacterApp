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

WeaponModel* Character::getWeaponModel()
{
	QModelIndex wRoot = model->index(CharacterModel::Weapons);
	if (model->data(wRoot).canConvert<WeaponModel*>())
		return model->data(wRoot).value<WeaponModel*>();
	return nullptr;
}

void Character::addWeapon(Weapon* w)
{
	QModelIndex wRoot = model->index(CharacterModel::Weapons);
	if (model->data(wRoot).canConvert<WeaponModel*>()) {
		WeaponModel* wm = model->data(wRoot).value<WeaponModel*>();
		wm->insertRow(0);
		wm->setData(wm->index(0), QVariant::fromValue(w));
		model->setData(wRoot, QVariant::fromValue(wm));
	}
}

Ability* Character::getAbility(Ability::Score s)
{
	QVector<Ability*> abilities = model->index(CharacterModel::Abilities).data(Qt::UserRole).value<QVector<Ability*>>();
	return abilities.at(static_cast<int>(s));
}

void Character::setAbility(Ability* a)
{
	QModelIndex aIndex =  model->index(CharacterModel::Abilities);
	QVector<Ability*> abilities = model->data(aIndex).value<QVector<Ability*>>();
	abilities.replace(static_cast<int>(a->type), a);
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
