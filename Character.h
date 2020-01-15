#pragma once

#include <QVariant>
#include <QVector>
#include "CharacterModel.h"
#include "Weapon.h"

class Character
{
public: 
	Character(QObject* parent = nullptr);
	~Character();

	void insertChild(QPair<CharacterNode::Type, QVariant> data, QModelIndex& root = QModelIndex());
	void setProperty(CharacterNode::Type t, QVariant& value);
	bool addWeapon(Weapon* w);

	CharacterModel* getModel();

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;

private:
	CharacterModel* model;
};

