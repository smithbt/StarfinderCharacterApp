#include "Weapon.h"


Weapon::Weapon()
	:Item(),
	special(),
	type(Type::Melee)
{

}

Weapon::~Weapon()
{
}

void Weapon::read(const QJsonObject& json)
{
	Item::read(json);
	if (json.contains("Type") && json.value("Type").isDouble())
		Type type = static_cast<Type>(json.value("Type").toInt());
	if (json.contains("special") && json.value("special").isArray()) {
		QJsonArray wpnProps = json.value("special").toArray();
		special.clear();
		for (int i = 0; i < wpnProps.size(); ++i) {
			QString s = wpnProps.at(i).toString();
			special.append(s);
		}
	}

}

void Weapon::write(QJsonObject& json) const
{
	Item::write(json);
	json.insert("Type", static_cast<int>(type));
	json.insert("special", QJsonArray::fromStringList(special));
}

QString Weapon::toString() const
{
	return Item::toString() + QString("\nSpecial: %1").arg(special.join(", "));
}
