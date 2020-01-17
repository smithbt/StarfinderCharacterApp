#pragma once

#include <QJsonObject>
#include <QString>

class Item
{
public: 
	Item();

	QString name;
	int level, price;
	double bulk;

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;
	QString toString() const;
};