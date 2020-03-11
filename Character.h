#pragma once

#include <QHash>
#include <QJsonArray>
#include <QJsonObject>
#include <QObject>
#include <QVector>
#include "Ability.h"
#include "ClassInfo.h"
#include "Race.h"
#include "Resource.h"
#include "Weapon.h"

class Character : public QObject
{
	Q_OBJECT

private:
	QString characterName;
	Race* race;
	QString m_theme;
	ClassInfo* pcClass;
	Resource* stamina;
	Resource* hitpoints;
	Resource* resolve;
	QHash<QString, Ability*> abilities;
	QVector<Weapon*> weapons;

public:

	Character(QObject* parent = nullptr);
	~Character();

	// Getters
	QString getCharacterName() const;
	Race* getRace() const;
	QString theme() const;
	QString getClassName() const;
	int getClassLevel() const;
	QString getKeyAbility() const;
	int getBAB() const;
	int getFortitude() const;
	int getReflex() const;
	int getWill() const;
	Resource* getStamina() const;
	Resource* getHP() const;
	Resource* getResolve() const;
	Ability* getAbility(const QString abilityName) const;
	int getAbilityProperty(const QString abilityName, const QString propertyName) const;
	
	// Setters
	void setCharacterName(const QString name);
	void setRace(Race* race);
	void setTheme(QString theme);
	void setClassProperties(QHash<ClassInfo::LevelStat, QVariant> properties);
	void setClassName(QString name);
	void setClassLevel(int level);
	void setKeyAbility(QString keyAbility);
	void setStamina(Resource* s);
	void setHP(Resource* hp);
	void setResolve(Resource* resolve);
	void setAbility(const QString abilityName, Ability* a);
	bool setAbilityProperty(const QString abilityName, const QString propertyName, const int value);

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

private slots:
	void calcMaxStamina();
	void calcMaxHP();
	void calcMaxResolve();
};

