#pragma once

#include <QJsonObject>
#include <QString>

class Item
{

public: 
	Item();
	virtual ~Item();

	QString name;
	int level, price;
	double bulk;
	QString description;

	virtual void read(const QJsonObject& json);
	virtual void write(QJsonObject& json) const;
	virtual QString toString() const;
};