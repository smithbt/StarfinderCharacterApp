#pragma once

#include "Damage.h"
#include "Resource.h"
#include "Weapon.h"

class RangedWeapon : public Weapon
{
	Damage damage;
	Resource ammo;

	int capacity();
	int usage();

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;
	QString toString() const;
};

