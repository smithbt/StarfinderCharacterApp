#pragma once

#include <QJsonObject>
#include <QList>
#include <QString>
#include "Weapon.h"

class Character
{
public:

	Character();
	Character(QString name);

	void setName(QString name);
	QString getName();

	void setCharLevel(int lvl);
	int getCharLevel();

	void setBAB(int bab);
	int getBAB();

	void setMaxHP(int max);
	int getMaxHP();
	void setCurrentHP(int current);
	int getCurrentHP();

	void setMaxStamina(int max);
	int getMaxStamina();
	void setCurrentStamina(int current);
	int getCurrentStamina();

	void setMaxResolve(int max);
	int getMaxResolve();
	void setCurrentResolve(int current);
	int getCurrentResolve();

	void addWeapon(const Weapon& w);
	QList<Weapon> getWeaponList();

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;

private:
	QString name;
	int charLevel;
	int bab;
	int currentHP, maxHP;
	int currentStamina, maxStamina;
	int currentResolve, maxResolve;
	QList<Weapon> weapons;
};

