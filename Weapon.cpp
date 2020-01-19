#include "Weapon.h"


Weapon::Weapon()
	:Item(),
	special(), type(Type::Melee)
{

}

Weapon::Weapon(Type t)
	:Item(),
	special(), type(t)
{

}

Weapon::~Weapon()
{
}

void Weapon::read(const QJsonObject& json)
{
	Item::read(json);
	if (json.contains("Type") && json.value("Type").isString()) {
		QString t = json.value("Type").toString();
		type = static_cast<Type>(QMetaEnum::fromType<Type>().keyToValue(t.toUtf8()));
	}
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
	json.insert("Type", QVariant::fromValue(type).toString());
	json.insert("special", QJsonArray::fromStringList(special));
}

QString Weapon::toString() const
{
	return Item::toString() + QString("\nSpecial: %1").arg(special.join(", "));
}
