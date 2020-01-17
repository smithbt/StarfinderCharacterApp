#pragma once

#include <QJsonObject>
#include <QString>

class Resource
{
public:
	Resource(int current, int max, int step = 1);

	int current;
	int max;
	int step;

	void adjustCurrent(int change);

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;
	QString toString() const;
};

