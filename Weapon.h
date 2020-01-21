#pragma once

#include <QJsonArray>
#include <QJsonObject>
#include <QMetaEnum>
#include <QString>
#include <QStringList>
#include "Item.h"
#include "Ability.h"
#include "Damage.h"
#include "Resource.h"

class Weapon : public Item
{
	Q_GADGET

public:
	enum class Type : int {
		Melee = 0,
		Ranged
	};
	Q_ENUM(Type)

	Weapon();
	~Weapon();

	QStringList special;
	Damage* damage;
	QString crit;
	Resource* ammo;
	int range;
	int capacity();
	int usage();
	Type type;
	Ability::Score attackScore;

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;
	QString toString() const;
};

Q_DECLARE_METATYPE(Weapon*)
Q_DECLARE_OPAQUE_POINTER(Weapon*)