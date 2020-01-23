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

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;
	QString toString();

private:
	int calcSave(bool isGood);

	bool fortIsGood;
	bool refIsGood;
	bool willIsGood;
	double babRate;
	int staminaRate;
	int hpRate;
	int skillRate;
};
