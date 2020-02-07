#include "Ability.h"

Ability::Ability(QObject* parent)
	: QObject(parent), 
	type(Strength), base(10), upgrade(0)
{
}

void Ability::read(const QJsonObject& json)
{
	if (json.contains("Name") && json["Name"].isString())
		type = scoreFromString(json.value("Name").toString());
	if (json.contains("Base Score") && json["Base Score"].isDouble())
		base = json["Base Score"].toInt();
	if (json.contains("Personal Upgrade") && json["Personal Upgrade"].isDouble())
		upgrade = json["Personal Upgrade"].toInt();
}

void Ability::write(QJsonObject& json) const
{
	json.insert("Name", name());
	json.insert("Base Score", base);
	json.insert("Personal Upgrade", upgrade);
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
	return QVariant::fromValue(type).toString();
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

Ability::Score Ability::scoreFromString(QString s)
{
	return static_cast<Score>(QMetaEnum::fromType<Score>().keyToValue(s.toUtf8()));
}
