#pragma once

#include <cmath>
#include <QMetaEnum>
#include <QObject>
#include <QJsonObject>
#include <QStringList>

class Ability : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int base READ getBase WRITE setBase NOTIFY baseChanged)
	Q_PROPERTY(int upgrade READ getUpgrade WRITE setUpgrade NOTIFY upgradeChanged)
	Q_PROPERTY(int score READ score STORED false NOTIFY scoreChanged)

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

	Ability(QObject* parent = nullptr);

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;
	QJsonObject toJsonObject() const;

	int score() const;
	int modifier() const;
	QString name() const;

	int getBase() const;
	int getUpgrade() const;
	Score type;

	QString toString() const;
	static Score scoreFromString(QString s);

public slots:
	void setBase(int b);
	void setUpgrade(int u);

signals:
	void scoreChanged(int);
	void baseChanged(int);
	void upgradeChanged(int);

private:
	int base;
	int upgrade;
};