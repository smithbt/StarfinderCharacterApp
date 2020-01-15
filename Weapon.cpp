#include "Weapon.h"

void Weapon::setProperties(QStringList props)
{
	this->special = props;
}

QStringList Weapon::getProperties()
{
	return special;
}

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
	json["special"] = QJsonArray::fromStringList(special);
}

QString Weapon::toString() const
{
	return QString("[%3] %1 (%2 cr) (%4 bulk)")
		.arg(getName()).arg(getPrice()).arg(getLevel()).arg(getBulk());
}
