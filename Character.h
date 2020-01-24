#pragma once

#include "CharacterModel.h"
#include "AbilityModel.h"
#include "WeaponModel.h"

class Character
{
public: 
	Character(QObject* parent = nullptr);
	~Character();

	int bab();
	int fort();
	int ref();
	int will();

	void setProperty(CharacterModel::Key k, QVariant& value);

	void addWeapon(Weapon* w);

	Ability* getAbility(Ability::Score s);
	void setAbility(Ability* a);

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;

	CharacterModel* model;
	AbilityModel* aModel;
	WeaponModel* wModel;
};

