#pragma once

#include "Damage.h"
#include "Resource.h"
#include "Weapon.h"

class RangedWeapon : public Weapon
{
	Q_GADGET

public:
	RangedWeapon();
	RangedWeapon(Weapon* base, int range, Damage* dmg, QString crit, Resource* ammo);

	Damage* damage;
	QString critEffect;
	Resource* ammo;
	int range;
	int capacity();
	int usage();

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;
	QString toString() const;
};

Q_DECLARE_METATYPE(RangedWeapon*)
Q_DECLARE_OPAQUE_POINTER(RangedWeapon*)

