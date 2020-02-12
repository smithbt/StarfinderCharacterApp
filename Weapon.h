#pragma once

#include <QJsonArray>
#include <QMetaEnum>
#include <QStringList>
#include "Item.h"
#include "Damage.h"
#include "Resource.h"

class Weapon : public Item
{
	Q_OBJECT

public:
	enum class Type : int {
		Melee = 0,
		Ranged
	};
	Q_ENUM(Type)

	Weapon(QObject* parent = nullptr);
	~Weapon();

	QStringList special;
	Damage* damage;
	QString crit;
	Resource* ammo;
	int range;
	int capacity();
	int usage();
	Type type;

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;
	QString toString() const;
};