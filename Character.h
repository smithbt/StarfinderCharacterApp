#pragma once

#include <QMetaEnum>
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
	Ability* strength;
	Ability* dexterity;
	Ability* constitution;
	Ability* intelligence;
	Ability* wisdom;
	Ability* charisma;
	QVector<Weapon*> weapons;

public:
	enum ColumnIndex : int {
		// Strings
		CharacterName = 0,

		// Ints
		BAB,
		Fortitude, Reflex, Will,

		// Resources
		Stamina,

		// Ability Scores
		Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma,

		// models, lists
		Weapons
	};
	Q_ENUM(ColumnIndex)

	enum {
		Resource_CurrentRole = Qt::UserRole + 1,
		Resource_MaxRole,
		Ability_TypeRole,
		Ability_BaseRole,
		Ability_UpgradeRole
	};

	Character(QObject* parent = nullptr);
	~Character();

	void setProperty(int prop, const QVariant& value, int role = Qt::EditRole);
	QVariant getProperty(int prop, int role = Qt::DisplayRole) const;

	void setClassLevelPair(QString name, int level);

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;
	QJsonObject toJsonObject() const;

	ClassModel* cModel;

};

