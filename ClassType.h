#pragma once

#include <QObject>
#include <QSqlQueryModel>
#include "Ability.h"

class ClassType : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int m_level READ getLevel WRITE setLevel NOTIFY levelChanged)
	Q_PROPERTY(Name m_name READ getName WRITE setName NOTIFY nameChanged)

public:
	enum Name : int {
		Envoy = 0,
		Mechanic
	};
	Q_ENUM(Name)

	ClassType(QObject *parent);
	~ClassType();

	Name getName();
	void setName(Name name);

	int getLevel();
	void setLevel(int level);

	Ability::Score keyAbility;
	int bab();
	int fort();
	int ref();
	int will();
	int stamina();
	int hp();
	int skills();

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;
	QString toString();
	static QString nameString(Name n);

signals:
	void levelChanged(int);
	void nameChanged(Name);

private slots:
	void updateLeveledNumbers();
	void updateClassReference();

private:
	int calcSave(bool isGood);
	Name nameValue(QString n);

	QSqlQueryModel* model;
	QSqlDatabase db;

	Name m_name;

	int m_level;
	int m_fort;
	int m_ref;
	int m_will;
	int m_bab;
	int m_stamina;
	int m_hp;
	int m_skill;
};
