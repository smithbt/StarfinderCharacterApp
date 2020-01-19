#pragma once

#include "Damage.h"
#include "Weapon.h"

class MeleeWeapon : public Weapon
{
	Q_GADGET
public:
	MeleeWeapon();
	MeleeWeapon(Weapon* base, Damage* dmg, QString crit);

	Damage* damage;
	QString critEffect;

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;
	QString toString() const;
};

Q_DECLARE_METATYPE(MeleeWeapon*)
Q_DECLARE_OPAQUE_POINTER(MeleeWeapon*)