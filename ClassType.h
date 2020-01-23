#pragma once

#include <QObject>
#include "Ability.h"

class ClassType : public QObject
{
	Q_OBJECT

public:
	ClassType(QObject *parent);
	~ClassType();

	int level;
	Ability::Score keyAbility;
	int bab();
	int fortSave();
	int refSave();
	int willSave();
	int stamina();
	int hp();
	int skills();

private:
	int calcSave(bool isGood);

	bool fort;
	bool ref;
	bool will;
	double babRate;
	int staminaRate;
	int hpRate;
	int skillRate;
};
