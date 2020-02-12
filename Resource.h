#pragma once

#include <QObject>
#include <QJsonObject>
#include <QString>

class Resource : public QObject
{
	Q_OBJECT

public:
	Resource(QObject* parent = nullptr);

	int current;
	int max;
	int step;

	void adjustCurrent(int change);

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;
	QString toString() const;
};

