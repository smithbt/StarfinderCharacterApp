#include "Weapon.h"

Weapon::Weapon()
{
	level = 0;
	price = 0;
	bulk = 0.0;
	name = QString();
	properties = QStringList();
}

Weapon::~Weapon()
{
}

Weapon::Weapon(const Weapon& other)
{
	this->level = other.level;
	this->price = other.price;
	this->bulk = other.bulk;
	this->name = other.name;
	this->properties = other.properties;
}

Weapon& Weapon::operator=(const Weapon& other)
{
	if (&other != this) {
		this->level = other.level;
		this->price = other.price;
		this->bulk = other.bulk;
		this->name = other.name;
		this->properties = other.properties;
	}
	return *this;
}

bool Weapon::operator==(const Weapon& other) const
{
	return this->level == other.level
		&& this->price == other.price
		&& this->bulk == other.bulk
		&& this->name == other.name
		&& this->properties == other.properties;
}

bool Weapon::operator!=(const Weapon& other) const
{
	return !(*this == other);
}

void Weapon::setLevel(int level)
{
	this->level = level;
}

void Weapon::setPrice(int price)
{
	this->price = price;
}

void Weapon::setBulk(double bulk)
{
	this->bulk = bulk;
}

void Weapon::setName(QString name)
{
	this->name = name;
}

void Weapon::setProperties(QStringList props)
{
	this->properties = props;
}

int Weapon::getLevel()
{
	return level;
}

int Weapon::getPrice()
{
	return price;
}

double Weapon::getBulk()
{
	return bulk;
}

QString Weapon::getName()
{
	return name;
}

QStringList Weapon::getProperties()
{
	return properties;
}

void Weapon::read(const QJsonObject& json)
{
	if (json.contains("level") && json["level"].isDouble())
		level = json["level"].toInt();
	if (json.contains("price") && json["price"].isDouble())
		price = json["price"].toInt();
	if (json.contains("bulk") && json["bulk"].isDouble())
		bulk = json["bulk"].toDouble();
	if (json.contains("name") && json["name"].isString())
		name = json["name"].toString();
	if (json.contains("properties") && json["properties"].isArray()) {
		QJsonArray wpnProps = json["properties"].toArray();
		properties.clear();
		for (int i = 0; i < wpnProps.size(); ++i) {
			QString s = wpnProps[i].toString();
			properties.append(s);
		}
		
	}

}

void Weapon::write(QJsonObject& json) const
{
	json["level"] = level;
	json["price"] = price;
	json["bulk"] = bulk;
	json["name"] = name;
	json["properties"] = QJsonArray::fromStringList(properties);
}

QString Weapon::toString() const
{
	return QString("[%3] %1 (%2 cr) (%4 bulk)").arg(name).arg(price).arg(level).arg(bulk);
}
