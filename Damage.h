#pragma once

#include <QJsonObject>
#include <QString>

class Damage
{
public:
	Damage(int count = 1, int size = 1);
	Damage(int count, int size, QString type);

	int dieCount;
	int dieSize;
	QString type;

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;
	QString toString() const;
};

