#include "Ability.h"

Ability::Ability(Score type, int base, int upgrade)
	: type(type), base(base), upgrade(upgrade)
{
}

void Ability::read(const QJsonObject& json)
{
	if (json.contains("Name") && json["Name"].isString()) {
		QString name = json["Name"].toString();
		type = static_cast<Score>(QMetaEnum::fromType<Score>().keyToValue(name.toUtf8()));
	}
	if (json.contains("Base Score") && json["Base Score"].isDouble())
		base = json["Base Score"].toInt();
	if (json.contains("Personal Upgrade") && json["Personal Upgrade"].isDouble())
		upgrade = json["Personal Upgrade"].toInt();
}

void Ability::write(QJsonObject& json) const
{
	json.insert("Name", name());
	json.insert("Base Score", base);
	json.insert("Personal Upgrade", upgrade);
}

int Ability::score() const
{
	return base + upgrade;
}

int Ability::modifier() const
{
	return floor((base + upgrade - 10) / 2);
}

QString Ability::name() const
{
	return QVariant::fromValue(type).toString();
}

QString Ability::toString() const
{
	return QString::asprintf("%1: %2 [%+i]", modifier()).arg(name()).arg(score());
}
