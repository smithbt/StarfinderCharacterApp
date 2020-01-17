#pragma once

#include "Damage.h"
#include "Resource.h"
#include "Weapon.h"

class RangedWeapon : public Weapon
{
public:
	Damage damage;
	QString critEffect;
	Resource ammo;
	int range;
	int capacity();
	int usage();

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;
	QString toString() const;
};

