#include "Weapon.h"

Weapon::Weapon()
{
	level = 0;
	range = 0;
	capacity = 0;
	usage = 0;
	price = 0;
	type = Type::Unknown;
	bulk = 0.0;
	name = QString();
	damageDice = QString();
	damageType = QString(); 
	critical = QString();
	properties = QStringList();
}

Weapon::~Weapon()
{
}

Weapon::Weapon(const Weapon& other)
{
	this->level = other.level;
	this->range = other.range;
	this->capacity = other.capacity;
	this->usage = other.usage;
	this->price = other.price;
	this->type = other.type;
	this->bulk = other.bulk;
	this->name = other.name;
	this->damageDice = other.damageDice;
	this->damageType = other.damageType;
	this->critical = other.critical;
	this->properties = other.properties;
}

Weapon& Weapon::operator=(const Weapon&)
{
	return *this;
}

void Weapon::setLevel(int level)
{
	this->level = level;
}

void Weapon::setRange(int range)
{
	this->range = range;
}

void Weapon::setCapacity(int capacity)
{
	this->capacity = capacity;
}

void Weapon::setUsage(int usage)
{
	this->usage = usage;
}

void Weapon::setPrice(int price)
{
	this->price = price;
}

void Weapon::setType(Type type)
{
	this->type = type;
}

void Weapon::setBulk(double bulk)
{
	this->bulk = bulk;
}

void Weapon::setName(QString name)
{
	this->name = name;
}

void Weapon::setDamageDice(QString dmgDice)
{
	this->damageDice = dmgDice;
}

void Weapon::setDamageType(QString dmgType)
{
	this->damageType = dmgType;
}

void Weapon::setCritical(QString critical)
{
	this->critical = critical;
}

void Weapon::setProperties(QStringList props)
{
	this->properties = props;
}

int Weapon::getLevel()
{
	return level;
}

int Weapon::getRange()
{
	return range;
}

int Weapon::getCapacity()
{
	return capacity;
}

int Weapon::getUsage()
{
	return usage;
}

int Weapon::getPrice()
{
	return price;
}

Weapon::Type Weapon::getType()
{
	return type;
}

double Weapon::getBulk()
{
	return bulk;
}

QString Weapon::getName()
{
	return name;
}

QString Weapon::getDamageDice()
{
	return damageDice;
}

QString Weapon::getDamageType()
{
	return damageType;
}

QString Weapon::getCritical()
{
	return critical;
}

QStringList Weapon::getProperties()
{
	return properties;
}

void Weapon::paint(QPainter* painter, const QRect& rect, const QPalette& palette, EditMode mode) const
{
	painter->save();

	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->setPen(Qt::NoPen);
	painter->setBrush(mode == EditMode::Editable ?
		palette.highlight() :
		palette.windowText());

}

QSize Weapon::sizeHint() const
{
	return QSize();
}

void Weapon::read(const QJsonObject& json)
{
	if (json.contains("level") && json["level"].isDouble())
		level = json["level"].toInt();
	if (json.contains("range") && json["range"].isDouble())
		range = json["range"].toInt();
	if (json.contains("capacity") && json["capacity"].isDouble())
		capacity = json["capacity"].toInt();
	if (json.contains("usage") && json["usage"].isDouble())
		usage = json["usage"].toInt();
	if (json.contains("price") && json["price"].isDouble())
		price = json["price"].toInt();
	if (json.contains("type") && json["type"].isDouble())
		type = static_cast<Type>(json["type"].toInt());
	if (json.contains("bulk") && json["bulk"].isDouble())
		bulk = json["bulk"].toDouble();
	if (json.contains("name") && json["name"].isString())
		name = json["name"].toString();
	if (json.contains("damageDice") && json["damageDice"].isString())
		damageDice = json["damageDice"].toString();
	if (json.contains("damageType") && json["damageType"].isString())
		damageType = json["damageType"].toString();
	if (json.contains("critical") && json["critical"].isString())
		damageType = json["critical"].toString();
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
	json["range"] = range;
	json["capacity"] = capacity;
	json["usage"] = usage;
	json["price"] = price;
	json["type"] = static_cast<int>(type);
	json["bulk"] = bulk;
	json["name"] = name;
	json["damageDice"] = damageDice;
	json["damageType"] = damageType;
	json["critical"] = critical;
	QJsonArray wpnProps;
	foreach(QString prop, properties) {
		wpnProps.append(QJsonValue(prop));
	}
	json["properties"] = wpnProps;
}
