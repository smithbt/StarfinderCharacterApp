#pragma once

#include <cmath>
#include <QMetaEnum>
#include <QJsonObject>
#include <QStringList>

class Ability
{
	Q_GADGET
public:
	enum class Score { Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma };
	Q_ENUM(Score)

	Ability(Score s = Score::Strength, int base = 10, int upgrade = 0);

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;

	void setType(Score s);
	void setBase(int base);
	void setUpgrade(int upgrade);

	int score() const;
	int modifier() const;
	Score getEnum() const;
	QString name() const;

	QString toString() const;

private:
	Score sName;
	int base;
	int upgrade;
};

Q_DECLARE_METATYPE(Ability*)
Q_DECLARE_OPAQUE_POINTER(Ability*)