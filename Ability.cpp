#include "Ability.h"

Ability::Ability(QObject* parent)
	: QObject(parent), 
	m_name("Strength"), base(10), upgrade(0)
{
}

void Ability::read(const QJsonObject& json)
{
	if (json.contains("Name") && json["Name"].isString())
		m_name = json.value("Name").toString();
	if (json.contains("Base") && json["Base"].isDouble())
		base = json.value("Base").toInt();
	if (json.contains("Upgrade") && json["Upgrade"].isDouble())
		upgrade = json.value("Upgrade").toInt();
}

void Ability::write(QJsonObject& json) const
{
	json.insert("Name", m_name);
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

QString Ability::name() const
{
	return m_name;
}

int Ability::getBase() const
{
	return base;
}

int Ability::getUpgrade() const
{
	return upgrade;
}

QString Ability::toString() const
{
    QString mod = QString::asprintf("%+i", modifier());
    return QString("%1: %2 [%3]").arg(name()).arg(score()).arg(mod);
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

void Ability::setName(QString name)
{
	m_name = name;
}
