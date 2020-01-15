#include "Ability.h"

Ability::Ability(Score s, int base, int upgrade)
{
	this->sName = s;
	this->base = base;
	this->upgrade = upgrade;
}

void Ability::read(const QJsonObject& json)
{
	if (json.contains("Name@Enum") && json["Name@Enum"].isString()) {
		QStringList parts = json["Name@Enum"].toString().split("#");
		sName = static_cast<Score>(parts.at(1).toInt());
	}
	if (json.contains("Base Score") && json["Base Score"].isDouble())
		base = json["Base Score"].toInt();
	if (json.contains("Personal Upgrade") && json["Personal Upgrade"].isDouble())
		base = json["Personal Upgrade"].toInt();
}

void Ability::write(QJsonObject& json) const
{
	json["Name@Enum"] = (name() + "@" + static_cast<int>(sName));
	json["Base Score"] = base;
	json["Personal Upgrade"] = upgrade;
}

void Ability::setType(Score s)
{
	sName = s;
}

void Ability::setBase(int base)
{
	this->base = base;
}

void Ability::setUpgrade(int upgrade)
{
	this->upgrade = upgrade;
}

int Ability::score() const
{
	return base + upgrade;
}

int Ability::modifier() const
{
	return floor((base + upgrade - 10) / 2);
}

Ability::Score Ability::getEnum() const
{
	return sName;
}

QString Ability::name() const
{
	switch (sName) {
	case Score::Strength: return "Strength";
	case Score::Dexterity: return "Dexterity";
	case Score::Constitution: return "Constitution";
	case Score::Intelligence: return "Intelligence";
	case Score::Wisdom: return "Wisdom";
	case Score::Charisma: return "Charisma";
	}
	return QString();
}

QString Ability::toString() const
{
	return QString::asprintf("%1: %2 [%+i]", modifier()).arg(name(), score());
}
