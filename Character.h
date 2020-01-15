#pragma once

#include <QVariant>
#include <QVector>
#include "CharacterModel.h"
#include "Ability.h"
#include "Weapon.h"

class Character
{
public: 
	Character(QObject* parent = nullptr);
	~Character();

	void insertChild(QVariant& data, QModelIndex& root = QModelIndex());
	void setProperty(CharacterNode::Type t, QVariant& value);
	bool addWeapon(Weapon* w);

	Ability* getAbility(Ability::Score s);
	void setAbility(Ability* a);

	CharacterModel* getModel();

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;

private:
	CharacterModel* model;
};

