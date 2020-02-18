#include "Weapon.h"


Weapon::Weapon(QObject* parent)
	: Item(parent), 
	type(Type::Melee), 
	damage(new Damage()), 
	crit(), 
	ammo(new Resource(this)),
	range(0),
	special()
{}

Weapon::~Weapon()
{
	delete damage;
	delete ammo;
}

int Weapon::capacity()
{
	return ammo->max();
}

int Weapon::usage()
{
	return ammo->step();
}

void Weapon::read(const QJsonObject& json)
{
	Item::read(json);
	if (json.contains("Type") && json.value("Type").isString()) {
		QString t = json.value("Type").toString();
		type = static_cast<Type>(QMetaEnum::fromType<Type>().keyToValue(t.toLocal8Bit()));
	}
	if (json.contains("special") && json.value("special").isArray()) {
		QJsonArray wpnProps = json.value("special").toArray();
		special.clear();
		for (int i = 0; i < wpnProps.size(); ++i) {
			QString s = wpnProps.at(i).toString();
			special.append(s);
		}
	}
	if (json.contains("Range") && json.value("Range").isDouble())
		range = json.value("Range").toInt();
	if (json.contains("Ammo") && json.value("Ammo").isObject())
		ammo->read(json.value("Ammo").toObject());
	if (json.contains("Damage") && json.value("Damage").isObject())
		damage->read(json.value("Damage").toObject());
	if (json.contains("Crit") && json.value("Crit").isString())
		crit = json.value("Crit").toString();

}

void Weapon::write(QJsonObject& json) const
{
	Item::write(json);
	json.insert("Type", QVariant::fromValue(type).toString());
	json.insert("special", QJsonArray::fromStringList(special));
	json.insert("Range", range);
	QJsonObject ammoObj;
	ammo->write(ammoObj);
	json.insert("Ammo", ammoObj);
	QJsonObject dmgObj;
	damage->write(dmgObj);
	json.insert("Damage", dmgObj);
	json.insert("Crit", crit);
}

QJsonObject Weapon::toJsonObject() const
{
	QJsonObject json;
	write(json);
	return json;
}

QString Weapon::toString() const
{
	QString output = Item::toString();
	switch (type) {
	case Type::Melee:
		output += QString("\n%1 damage (Critical %2)").arg(damage->toString()).arg(crit);
		break;
	case Type::Ranged:
		output += QString("\n%1 damage (Critical %2); Range: %3; Usage/Capacity: %4")
			.arg(damage->toString()).arg(crit).arg(range).arg(ammo->toString());
		break;
	}
	output += QString("\nSpecial: %1").arg(special.join(", "));
	return output;
}
