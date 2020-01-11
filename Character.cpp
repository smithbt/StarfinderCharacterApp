#include "Character.h"

Character::Character()
{
	name = QString();
	charLevel = 0;
	bab = 0;
	currentHP = 0;
	maxHP = 0;
	currentStamina = 0;
	maxStamina = 0;
	currentResolve = 0;
	maxResolve = 0;
}

Character::Character(QString name)
{
	this->name = name;
	charLevel = 0;
	bab = 0;
	currentHP = 0;
	maxHP = 0;
	currentStamina = 0;
	maxStamina = 0;
	currentResolve = 0;
	maxResolve = 0;
}

void Character::setName(QString name)
{
	this->name = name;
}

QString Character::getName()
{
	return name;
}

void Character::setCharLevel(int lvl)
{
	charLevel = lvl;
}

int Character::getCharLevel()
{
	return charLevel;
}

void Character::setBAB(int bab)
{
	this->bab = bab;
}

int Character::getBAB()
{
	return bab;
}

void Character::setMaxHP(int max)
{
	maxHP = max;
}

int Character::getMaxHP()
{
	return maxHP;
}

void Character::setCurrentHP(int current)
{
	currentHP = current;
}

int Character::getCurrentHP()
{
	return currentHP;
}

void Character::setMaxStamina(int max)
{
	maxStamina = max;
}

int Character::getMaxStamina()
{
	return maxStamina;
}

void Character::setCurrentStamina(int current)
{
	currentStamina = current;
}

int Character::getCurrentStamina()
{
	return currentStamina;
}

void Character::setMaxResolve(int max)
{
	maxResolve = max;
}

int Character::getMaxResolve()
{
	return maxResolve;
}

void Character::setCurrentResolve(int current)
{
	currentResolve = current;
}

int Character::getCurrentResolve()
{
	return currentResolve;
}

void Character::addWeapon(const Weapon& w)
{
	weapons.append(w);
}

QList<Weapon> Character::getWeaponList()
{
	return weapons;
}

void Character::read(const QJsonObject& json)
{
	if (json.contains("name") && json["name"].isString())
		name = json["name"].toString();
	if (json.contains("abilities") && json["abilities"].isArray()) {
		
	}
	if (json.contains("weapons") && json["weapons"].isArray()) {
		QJsonArray jsonWpns = json["weapons"].toArray();
		weapons.clear();
		for (int i = 0; i < jsonWpns.size(); ++i) {
			Weapon w;
			w.read(jsonWpns[i].toObject());
			addWeapon(w);
		}
	}
}

void Character::write(QJsonObject& json) const
{
	json["name"] = name;
	QJsonArray wpnArray;
	for (int i = 0; i < weapons.size(); ++i) {
		QJsonObject wpnObj;
		weapons[i].write(wpnObj);
		wpnArray.append(wpnObj);
	}
	json["weapons"] = wpnArray;
}
