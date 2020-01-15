#include "Ability.h"

Ability::Ability(Score s, int base, int upgrade)
{
	this->sName = s;
	this->base = base;
	this->upgrade = upgrade;
}

void Ability::read(const QJsonObject& json)
{
	if (json.contains("AbilityScore") && json["AbilityScore"].isString()) {
		QStringList parts = json["AbilityScore"].toString().split("|");
		const char* key = parts.at(0).toStdString().c_str();
		auto meta = QMetaEnum::fromType<Score>();
		sName = static_cast<Score>(meta.keyToValue(key));
		base = parts.at(1).toInt();
		upgrade = parts.at(2).toInt();
	}
}

void Ability::write(QJsonObject& json) const
{
	json["AbilityScore"] = (name() + "|" + base + "|" + upgrade);
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
