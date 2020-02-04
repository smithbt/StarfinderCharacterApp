#pragma once

#include <cmath>
#include <QMetaEnum>
#include <QJsonObject>
#include <QStringList>

class Ability
{
	Q_GADGET
public:
	enum Score : int { 
		Strength = 0, 
		Dexterity, 
		Constitution, 
		Intelligence, 
		Wisdom, 
		Charisma 
	};
	Q_ENUM(Score)

	Ability(Score s = Score::Strength, int base = 10, int upgrade = 0);

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;

	int score() const;
	int modifier() const;
	QString name() const;

	QString toString() const;

	Score type;
	int base;
	int upgrade;

	static Score scoreFromString(QString s);
};

Q_DECLARE_METATYPE(Ability*)
Q_DECLARE_OPAQUE_POINTER(Ability*)