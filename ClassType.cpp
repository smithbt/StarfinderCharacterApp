#include "ClassType.h"

ClassType::ClassType(QObject *parent)
	: QObject(parent),
	level(1),
	keyAbility(Ability::Score::Strength),
	fort(false),
	ref(false),
	will(false),
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
	return calcSave(fort);
}

int ClassType::refSave()
{
	return calcSave(ref);
}

int ClassType::willSave()
{
	return calcSave(will);
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

int ClassType::calcSave(bool isGood)
{
	if (isGood)
		return (2 + (level / 2));
	else
		return (level / 3);
}
