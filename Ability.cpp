#include "Ability.h"

Ability::Ability(int base, int upgrade)
{
	this->base = base;
	this->upgrade = upgrade;
}

Ability::Ability(QString s)
{
	fromString(s);
}

void Ability::setBase(int base)
{
	this->base = base;
}

void Ability::setUpgrade(int upgrade)
{
	this->upgrade = upgrade;
}

void Ability::fromString(QString s)
{
	auto parts = s.split("|");
	base = parts.at(1).toInt();
	upgrade = parts.at(2).toInt();
}

int Ability::fullScore()
{
	return base + upgrade;
}

int Ability::modifier()
{
	return floor((base + upgrade - 10) / 2);
}

QString Ability::toString()
{
	return (base + "|" + upgrade);
}

QString Ability::getScoreName(Score s)
{
	switch (s) {
	case Score::Strength: return "Strength";
	case Score::Dexterity: return "Dexterity";
	case Score::Constitution: return "Constitution";
	case Score::Intelligence: return "Intelligence";
	case Score::Wisdom: return "Wisdom";
	case Score::Charisma: return "Charisma";
	}
	return QString();
}
