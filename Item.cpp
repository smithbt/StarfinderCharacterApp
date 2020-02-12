#include "Item.h"

Item::Item(QObject* parent)
	: QObject(parent),
	name(QString()), level(0), price(0), bulk(0.0)
{
}

Item::~Item()
{
}



void Item::read(const QJsonObject& json)
{
	if (json.contains("level") && json.value("level").isDouble())
		level = json.value("level").toInt();
	if (json.contains("price") && json.value("price").isDouble())
		price = json.value("price").toInt();
	if (json.contains("bulk") && json.value("bulk").isDouble())
		bulk = json.value("bulk").toDouble();
	if (json.contains("name") && json.value("name").isString())
		name = json.value("name").toString();
	if (json.contains("Description") && json.value("Description").isString())
		description = json.value("Description").toString();
}

void Item::write(QJsonObject& json) const
{
	json.insert("level", level);
	json.insert("price", price);
	json.insert("bulk", bulk);
	json.insert("name", name);
	json.insert("Description", description);
}

QString Item::toString() const
{
	return QString("%1 [%3] (%2 cr) (%4 bulk)").arg(name).arg(price).arg(level).arg(bulk);
}
