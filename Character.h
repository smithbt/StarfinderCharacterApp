#pragma once

#include <QObject>
#include "Ability.h"
#include "Resource.h"
#include "Weapon.h"
#include "ClassModel.h"

class Character : public QObject
{
	Q_OBJECT

private:
	QString characterName;
	int bab;
	int fortitude;
	int reflex;
	int will;
	Resource* stamina;
	QHash<QString, Ability*> abilities;
	QVector<Weapon*> weapons;

public:

	Character(QObject* parent = nullptr);
	~Character();

	// Getters
	QString getCharacterName() const;
	int getBAB() const;
	int getFortitude() const;
	int getReflex() const;
	int getWill() const;
	Resource* getStamina() const;
	Ability* getAbility(const QString abilityName) const;
	
	// Setters
	void setCharacterName(const QString name);
	//void setBAB() const;
	//void setFortitude() const;
	//void setReflex() const;
	//void setWill() const;
	void setStamina(Resource* s);
	void setAbility(const QString abilityName, Ability* a);

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

