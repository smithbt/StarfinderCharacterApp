#pragma once

#include <cmath>
#include <QString>
#include <QStringList>

class Ability
{
public:
	enum class Score { Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma };

	Ability(int base = 10, int upgrade = 0);
	Ability(QString s);

	void setBase(int base);
	void setUpgrade(int upgrade);
	void fromString(QString s);

	int fullScore();
	int modifier();
	QString toString();

	QString getScoreName(Score s);
private:
	int base;
	int upgrade;
};

