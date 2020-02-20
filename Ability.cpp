#include "Ability.h"

Ability::Ability(QObject* parent)
	: QObject(parent), 
	base(10), upgrade(0)
{
}

void Ability::read(const QJsonObject& json)
{
	if (json.contains("Base") && json["Base"].isDouble())
		base = json.value("Base").toInt();
	if (json.contains("Upgrade") && json["Upgrade"].isDouble())
		upgrade = json.value("Upgrade").toInt();
}

void Ability::write(QJsonObject& json) const
{
	json.insert("Base", base);
	json.insert("Upgrade", upgrade);
}

QJsonObject Ability::toJsonObject() const
{
	QJsonObject json;
	write(json);
	return json;
}

int Ability::score() const
{
	return base + upgrade;
}

int Ability::modifier() const
{
	return floor((base + upgrade - 10) / 2);
}

int Ability::getBase() const
{
	return base;
}

int Ability::getUpgrade() const
{
	return upgrade;
}

void Ability::setBase(int b)
{
	if (b != base) {
		base = b;
		emit baseChanged(base);
		emit scoreChanged(score());
	}
}

void Ability::setUpgrade(int u)
{
	if (u != upgrade) {
		upgrade = u;
		emit upgradeChanged(upgrade);
		emit scoreChanged(score());
	}
}