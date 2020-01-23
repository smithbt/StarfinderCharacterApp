#include "ClassType.h"

ClassType::ClassType(QObject *parent)
	: QObject(parent),
	level(1),
	keyAbility(Ability::Score::Strength),
	fortIsGood(false),
	refIsGood(false),
	willIsGood(false),
	babRate(1),
	staminaRate(6),
	hpRate(6),
	skillRate(6)
{
}

ClassType::~ClassType()
{
}

int ClassType::bab()
{
	return (level * babRate);
}

int ClassType::fortSave()
{
	return calcSave(fortIsGood);
}

int ClassType::refSave()
{
	return calcSave(refIsGood);
}

int ClassType::willSave()
{
	return calcSave(willIsGood);
}

int ClassType::stamina()
{
	return (level * staminaRate);
}

int ClassType::hp()
{
	return (level * hpRate);
}

int ClassType::skills()
{
	return (level *skillRate);
}

void ClassType::read(const QJsonObject& json)
{
	if (json.contains("level") && json.value("level").isDouble())
		level = json.value("level").toInt();
	if (json.contains("keyAbility") && json.value("keyAbility").isString())
		keyAbility = Ability::scoreFromString(json.value("keyAbility").toString());
	if (json.contains("babRate") && json.value("babRate").isDouble())
		babRate = json.value("babRate").toDouble();
	if (json.contains("fortIsGood") && json.value("fortIsGood").isBool())
		fortIsGood = json.value("fortIsGood").toBool();
	if (json.contains("refIsGood") && json.value("refIsGood").isBool())
		refIsGood = json.value("refIsGood").toBool();
	if (json.contains("willIsGood") && json.value("willIsGood").isBool())
		willIsGood = json.value("willIsGood").toBool();
	if (json.contains("staminaRate") && json.value("staminaRate").isDouble())
		staminaRate = json.value("staminaRate").toInt();
	if (json.contains("hpRate") && json.value("hpRate").isDouble())
		hpRate = json.value("hpRate").toInt();
	if (json.contains("skillRate") && json.value("skillRate").isDouble())
		skillRate = json.value("skillRate").toInt();
}

void ClassType::write(QJsonObject& json) const
{
	json.insert("level", level);
	json.insert("keyAbility", QVariant::fromValue(keyAbility).toString());
	json.insert("babRate", babRate);
	json.insert("fortIsGood", fortIsGood);
	json.insert("refIsGood", refIsGood);
	json.insert("willIsGood", willIsGood);
	json.insert("staminaRate", staminaRate);
	json.insert("hpRate", hpRate);
	json.insert("skillRate", skillRate);
}

QString ClassType::toString()
{
	return QString();
}

int ClassType::calcSave(bool isGood)
{
	if (isGood)
		return (2 + (level / 2));
	else
		return (level / 3);
}
