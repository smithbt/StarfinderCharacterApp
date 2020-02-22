#pragma once

#include <QHash>
#include <QJsonArray>
#include <QJsonObject>
#include <QObject>
#include <QVector>
#include "Ability.h"
#include "Race.h"
#include "Resource.h"
#include "Weapon.h"

class Character : public QObject
{
	Q_OBJECT

private:
	QString characterName;
	Race* race;
	int bab;
	Resource* stamina;
	QHash<QString, Ability*> abilities;
	QVector<Weapon*> weapons;

public:

	Character(QObject* parent = nullptr);
	~Character();

	// Getters
	QString getCharacterName() const;
	Race* getRace() const;
	int getBAB() const;
	int getFortitude() const;
	int getReflex() const;
	int getWill() const;
	Resource* getStamina() const;
	Ability* getAbility(const QString abilityName) const;
	QVariant getAbilityProperty(const QString abilityName, const QString propertyName) const;
	
	// Setters
	void setCharacterName(const QString name);
	void setRace(Race* race);
	void setStamina(Resource* s);
	void setAbility(const QString abilityName, Ability* a);
	bool setAbilityProperty(const QString abilityName, const QString propertyName, const QVariant& value);

	// Weapon Management Methods
	QVector<Weapon*> getWeapons() const;
	void setWeapons(const QVector<Weapon*> newWeapons);
	Weapon* getWeaponAt(int index) const;
	void setWeaponAt(int index, Weapon* weapon);
	void insertWeaponAt(int index, Weapon* weapon);
	void removeWeaponAt(int index);
	int getWeaponCount() const;

	// read/write methods
	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;
	QJsonObject toJsonObject() const;

signals:
	void weaponListChanged(QVector<Weapon*>);

};

