#include "Item.h"

QString Item::getName() const {
	return name;
}

void Item::setName(QString n) {
	name = n;
}

int Item::getLevel() const {
	return level;
}

void Item::setLevel(int lvl) {
	level = lvl;
}

int Item::getPrice() const {
	return price;
}

void Item::setPrice(int p) {
	price = p;
}

double Item::getBulk() const {
	return bulk;
}

void Item::setBulk(double b) {
	bulk = b;
}

void Item::read(const QJsonObject& json)
{
	if (json.contains("level") && json["level"].isDouble())
		level = json["level"].toInt();
	if (json.contains("price") && json["price"].isDouble())
		price = json["price"].toInt();
	if (json.contains("bulk") && json["bulk"].isDouble())
		bulk = json["bulk"].toDouble();
	if (json.contains("name") && json["name"].isString())
		name = json["name"].toString();
}

void Item::write(QJsonObject& json) const
{
	json["level"] = level;
	json["price"] = price;
	json["bulk"] = bulk;
	json["name"] = name;
}