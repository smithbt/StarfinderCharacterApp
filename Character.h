#pragma once

#include <QObject>
#include "CharacterModel.h"
#include "AbilityModel.h"
#include "WeaponModel.h"
#include "ClassModel.h"

class Character : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int bab READ bab STORED false NOTIFY babChanged)
	Q_PROPERTY(int fortitude READ fortitude STORED false NOTIFY fortitudeChanged)
	Q_PROPERTY(int reflex READ reflex STORED false NOTIFY reflexChanged)
	Q_PROPERTY(int will READ will STORED false NOTIFY willChanged)

public: 
	Character(QObject* parent = nullptr);
	~Character();

	int bab();
	int fortitude();
	int reflex();
	int will();
	int stamina();

	void setProperty(CharacterModel::Key k, QVariant& value);
	void setClassLevelPair(QString name, int level);

	void addWeapon(Weapon* w);

	Ability* getAbility(Ability::Score s);
	void setAbility(Ability* a);

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;

	CharacterModel* model;
	AbilityModel* aModel;
	WeaponModel* wModel;
	ClassModel* cModel;

signals:
	void babChanged(int);
	void fortitudeChanged(int);
	void reflexChanged(int);
	void willChanged(int);
};

