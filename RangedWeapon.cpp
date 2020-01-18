#include "RangedWeapon.h"

RangedWeapon::RangedWeapon()
	: Weapon(),
	range(0), damage(new Damage()), critEffect(QString("")), ammo(new Resource())
{
}

RangedWeapon::RangedWeapon(Weapon* base, int range, Damage* dmg, QString crit, Resource* ammo)
	: Weapon(*base),	range(range), damage(dmg), critEffect(crit), ammo(ammo)
{
}

int RangedWeapon::capacity()
{
	return ammo->max;
}

int RangedWeapon::usage()
{
	return ammo->step;
}

void RangedWeapon::read(const QJsonObject& json)
{
	Weapon::read(json);
	if (json.contains("Range") && json.value("Range").isDouble())
		range = json.value("Range").toInt();
	if (json.contains("Ammo") && json.value("Ammo").isObject())
		ammo->read(json.value("Ammo").toObject());
	if (json.contains("Damage") && json.value("Damage").isObject())
		damage->read(json.value("Damage").toObject());
	if (json.contains("Crit") && json.value("Crit").isString())
		critEffect = json.value("Crit").toString();

}

void RangedWeapon::write(QJsonObject& json) const
{
	Weapon::write(json);
	json.insert("Range", range);
	QJsonObject ammoObj;
	ammo->write(ammoObj);
	json.insert("Ammo", ammoObj);
	QJsonObject dmgObj;
	damage->write(dmgObj);
	json.insert("Damage", dmgObj);
	json.insert("Crit", critEffect);
}

QString RangedWeapon::toString() const
{
	return Weapon::toString() 
		+ QString("\nRange: %1; %2 damage (Critical %3); Usage/Capacity: %4")
		.arg(range).arg(damage->toString()).arg(critEffect).arg(ammo->toString());
}
