#include "Ability.h"

Ability::Ability(QObject* parent)
	: QObject(parent), 
	base(10), 
	upgrade(0)
{
}

void Ability::read(const QJsonObject& json)
{
	if (json.contains("Base") && json.value("Base").isDouble())
		base = json.value("Base").toInt();
	if (json.contains("Upgrade") && json.value("Upgrade").isDouble())
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
		int oldMod = modifier();
		base = b;
		emit baseChanged(base);
		emit scoreChanged(score());
		if (oldMod != modifier())
			emit modifierChanged(modifier());
	}
}

void Ability::setUpgrade(int u)
{
	if (u != upgrade) {
		int oldMod = modifier();
		upgrade = u;
		emit upgradeChanged(upgrade);
		emit scoreChanged(score());
		if (oldMod != modifier())
			emit modifierChanged(modifier());
	}
}