#pragma once

#include <QJsonObject>
#include <QString>

class Item
{
public: 
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

private:
	QString name;
	int level, price;
	double bulk;
};