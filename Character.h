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

	void insertChild(QVariant& data, QModelIndex& parent = QModelIndex());
	void setProperty(CharacterNode::Type t, QVariant& value);
	bool addWeapon(QVariant& value);

	QModelIndex getAbilityIndex(Ability::Score s);
	Ability* getAbility(Ability::Score s);
	void setAbility(Ability* a);

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;

	CharacterModel* model;
};

