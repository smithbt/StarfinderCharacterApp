#pragma once

#include <QJsonObject>
#include <QObject>
#include <QVariant>

class ClassInfo : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int level READ level WRITE setLevel NOTIFY levelChanged)

private:
	QString m_name;
	int m_level;
	QString keyAbility;
	double bab_rate;
	bool fort_isGood;
	bool ref_isGood;
	bool will_isGood;
	int stamina_rate;
	int hp_rate;
	int skill_rate;

	int calcSavingThrow(bool isGood) const;
	int calcLeveledValue(double rate) const;

public:
	enum LevelStat {
		BAB = 0,
		Fortitude, Reflex, Will,
		Stamina, HP, Skills
	};

	ClassInfo(QObject *parent);
	~ClassInfo();

	QString name() const;
	int level() const;
	int getPropertyValue(LevelStat propertyType) const;

	void setName(QString name);
	void setLevel(int level);
	void setPropertyRate(LevelStat propertyType, const QVariant& value);

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;
	QJsonObject toJsonObject() const;

signals:
	void levelChanged(int);
};
