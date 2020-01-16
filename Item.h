#pragma once

#include <QJsonObject>
#include <QString>

class Item
{
public: 
	Item();

	QString getName() const;
	void setName(QString n);

	int getLevel() const;
	void setLevel(int lvl);

	int getPrice() const;
	void setPrice(int p);

	double getBulk() const;
	void setBulk(double b);

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;

	QString toString() const;

private:
	QString name;
	int level, price;
	double bulk;
};