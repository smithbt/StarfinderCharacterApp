#include "ClassInfo.h"

ClassInfo::ClassInfo(QObject *parent)
	: QObject(parent),
	m_name(QString()),
	m_keyAbility(QString()),
	m_level(0),
	bab_rate(0),
	fort_isGood(false),
	ref_isGood(false),
	will_isGood(false),
	stamina_rate(0),
	hp_rate(0),
	skill_rate(0)
{
}

ClassInfo::~ClassInfo()
{
}

QString ClassInfo::name() const
{
	return m_name;
}

int ClassInfo::level() const
{
	return m_level;
}

QString ClassInfo::keyAbility() const
{
	return m_keyAbility;
}

int ClassInfo::getPropertyValue(LevelStat propertyType) const
{
	switch (propertyType) {
	case BAB:
		return calcLeveledValue(bab_rate);
	case Fortitude:
		return calcSavingThrow(fort_isGood);
	case Reflex:
		return calcSavingThrow(ref_isGood);
	case Will:
		return calcSavingThrow(will_isGood);
	case Stamina:
		return calcLeveledValue(stamina_rate);
	case HP:
		return calcLeveledValue(hp_rate);
	case Skills:
		return calcLeveledValue(skill_rate);
	}
}

void ClassInfo::setName(QString name)
{
	if (name != m_name)
		m_name = name;
}

void ClassInfo::setLevel(int level)
{
	if (level != m_level) {
		m_level = level;
		emit levelChanged(m_level);
	}
}

void ClassInfo::setKeyAbility(QString keyAbility)
{
	if (keyAbility != m_keyAbility)
		m_keyAbility = keyAbility;
}

void ClassInfo::setPropertyRate(LevelStat propertyType, const QVariant& value)
{
	switch (propertyType) {
	case BAB:
		if (value.toDouble() != bab_rate)
			bab_rate = value.toDouble();
		break;
	case Fortitude:
		if (value.toBool() != fort_isGood)
			fort_isGood = value.toBool();
		break;
	case Reflex:
		if (value.toBool() != ref_isGood)
			ref_isGood = value.toBool();
		break;
	case Will:
		if (value.toBool() != will_isGood)
			will_isGood = value.toBool();
		break;
	case Stamina:
		if (value.toInt() != stamina_rate)
			stamina_rate = value.toInt();
		break;
	case HP:
		if (value.toInt() != hp_rate)
			hp_rate = value.toInt();
		break;
	case Skills:
		if (value.toInt() != skill_rate)
			skill_rate = value.toInt();
		break;
	}
}

int ClassInfo::calcSavingThrow(bool isGood) const
{
	return (isGood ? (2 + m_level / 2) : (m_level / 3));
}

int ClassInfo::calcLeveledValue(double rate) const
{
	return (m_level * rate);
}

void ClassInfo::read(const QJsonObject& json)
{
	if (json.contains("ClassName") && json.value("ClassName").isString())
		m_name = json.value("ClassName").toString();
	if (json.contains("Level") && json.value("Level").isDouble())
		m_level = json.value("Level").toInt();
	if (json.contains("KeyAbility") && json.value("KeyAbility").isString())
		m_keyAbility = json.value("KeyAbility").toString();
	if (json.contains("BAB_Rate") && json.value("BAB_Rate").isDouble())
		bab_rate = json.value("BAB_Rate").toDouble();
	if (json.contains("Fort_isGood") && json.value("Fort_isGood").isBool())
		fort_isGood = json.value("Fort_isGood").toBool();
	if (json.contains("Ref_isGood") && json.value("Ref_isGood").isBool())
		ref_isGood = json.value("Ref_isGood").toBool();
	if (json.contains("Will_isGood") && json.value("Will_isGood").isBool())
		will_isGood = json.value("Will_isGood").toBool();
	if (json.contains("Stamina_Rate") && json.value("Stamina_Rate").isDouble())
		stamina_rate = json.value("Stamina_Rate").toInt();
	if (json.contains("HP_Rate") && json.value("HP_Rate").isDouble())
		hp_rate = json.value("HP_Rate").toInt();
	if (json.contains("Skill_Rate") && json.value("Skill_Rate").isDouble())
		skill_rate = json.value("Skill_Rate").toInt();
}

void ClassInfo::write(QJsonObject& json) const
{
	json.insert("ClassName", m_name);
	json.insert("Level", m_level);
	json.insert("KeyAbility", m_keyAbility);
	json.insert("BAB_Rate", bab_rate);
	json.insert("Fort_isGood", fort_isGood);
	json.insert("Ref_isGood", ref_isGood);
	json.insert("Will_isGood", will_isGood);
	json.insert("Stamina_Rate", stamina_rate);
	json.insert("HP_Rate", hp_rate);
	json.insert("Skill_Rate", skill_rate);
}

QJsonObject ClassInfo::toJsonObject() const
{
	QJsonObject json;
	write(json);
	return json;
}
