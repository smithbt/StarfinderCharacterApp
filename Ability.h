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
	Q_PROPERTY(int modifier READ modifier STORED false NOTIFY modifierChanged)

public:

	Ability(QObject* parent = nullptr);

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;
	QJsonObject toJsonObject() const;

	int score() const;
	int modifier() const;

	int getBase() const;
	int getUpgrade() const;

public slots:
	void setBase(int b);
	void setUpgrade(int u);

signals:
	void scoreChanged(int);
	void modifierChanged(int);
	void baseChanged(int);
	void upgradeChanged(int);

private:
	int base;
	int upgrade;
};