#include "RangedWeapon.h"

int RangedWeapon::capacity()
{
	return ammo.max;
}

int RangedWeapon::usage()
{
	return ammo.step;
}

void RangedWeapon::read(const QJsonObject& json)
{
	Weapon::read(json);
	if (json.contains("Range") && json.value("Range").isDouble())
		range = json.value("Range").toInt();
	if (json.contains("Ammo") && json.value("Ammo").isObject())
		ammo.read(json.value("Ammo").toObject());
	if (json.contains("Damage") && json.value("Damage").isObject())
		damage.read(json.value("Damage").toObject());
	if (json.contains("Crit") && json.value("crit").isString())
		critEffect = json.value("Crit").toString();

}

void RangedWeapon::write(QJsonObject& json) const
{
	Weapon::write(json);
	json.insert("Range", range);
	QJsonObject varObject;
	ammo.write(varObject);
	json.insert("Ammo", varObject);
	varObject.empty();
	damage.write(varObject);
	json.insert("Damage", varObject);
	json.insert("Crit", critEffect);
}

QString RangedWeapon::toString() const
{
	return Weapon::toString() 
		+ QString("\nRange: %1; %2 damage (Critical %3); Usage/Capacity: %4")
		.arg(QString::number(range), damage.toString(), critEffect, ammo.toString());
}
