#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon()
	: Weapon(Weapon(Weapon::Type::Melee)), damage(new Damage()), critEffect(QString())
{}

MeleeWeapon::MeleeWeapon(Weapon* base, Damage* dmg, QString crit)
	: Weapon(*base), damage(dmg), critEffect(crit)
{}

void MeleeWeapon::read(const QJsonObject& json)
{
	Weapon::read(json);
	if (json.contains("Damage") && json.value("Damage").isObject())
		damage->read(json.value("Damage").toObject());
	if (json.contains("Crit") && json.value("Crit").isString())
		critEffect = json.value("Crit").toString();

}

void MeleeWeapon::write(QJsonObject& json) const
{
	Weapon::write(json);
	QJsonObject dmgObj;
	damage->write(dmgObj);
	json.insert("Damage", dmgObj);
	json.insert("Crit", critEffect);
}

QString MeleeWeapon::toString() const
{
	return Weapon::toString()
		+ QString("\n%1 damage (Critical %2)").arg(damage->toString()).arg(critEffect);
}
