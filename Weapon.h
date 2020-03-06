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
	int attackMod;
	int damageMod;

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;
	QJsonObject toJsonObject() const;
	QString toString() const;

public slots:
	void fire();
	void reload();

signals:
	void currentAmmoChanged(int);
};