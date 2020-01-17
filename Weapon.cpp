#include "Weapon.h"

void Weapon::read(const QJsonObject& json)
{
	Item::read(json);
	if (json.contains("special") && json["special"].isArray()) {
		QJsonArray wpnProps = json["special"].toArray();
		special.clear();
		for (int i = 0; i < wpnProps.size(); ++i) {
			QString s = wpnProps[i].toString();
			special.append(s);
		}
	}

}

void Weapon::write(QJsonObject& json) const
{
	Item::write(json);
	json.insert("special", QJsonArray::fromStringList(special));
}

QString Weapon::toString() const
{
	return Item::toString() + QString("\nSpecial: %1").arg(special.join(", "));
}
