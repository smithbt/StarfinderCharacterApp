#include "ClassType.h"

ClassType::ClassType(QObject *parent)
	: QObject(parent),
	keyAbility(Ability::Score::Charisma),
	m_name(Envoy),
	m_level(0),
	m_bab(1),
	m_fort(0),
	m_ref(0),
	m_will(0),
	m_stamina(6),
	m_hp(6),
	m_skill(6)
{
	connect(this, &ClassType::nameChanged, &ClassType::updateClassReference);
}

ClassType::~ClassType()
{
}

ClassType::Name ClassType::getName()
{
	return m_name;
}

void ClassType::setName(Name name)
{
	m_name = name;
	emit nameChanged(m_name);
}

int ClassType::getLevel()
{
	return m_level;
}

void ClassType::setLevel(int level)
{
	m_level = level;
	emit levelChanged(m_level);
}

int ClassType::fort()
{
	return calcSave(m_fort);
}

int ClassType::ref()
{
	return calcSave(m_ref);
}

int ClassType::will()
{
	return calcSave(m_will);
}

int ClassType::bab()
{
	return m_bab * m_level;
}

int ClassType::stamina()
{
	return m_stamina * m_level;
}

int ClassType::hp()
{
	return m_hp * m_level;
}

int ClassType::skills()
{
	return m_skill * m_level;
}

void ClassType::read(const QJsonObject& json)
{
	if (json.contains("Name") && json.value("Name").isString())
		m_name = nameValue(json.value("Name").toString());
	if (json.contains("Level") && json.value("Level").isDouble())
		m_level = json.value("Level").toInt();
}

void ClassType::write(QJsonObject& json) const
{
	json.insert("Name", nameString(m_name));
	json.insert("Level", m_level);
}

QString ClassType::toString()
{
	return QString("%1 %2: +%3 BAB, +%4 Fort, +%5 Ref, +%6 Will")
		.arg(nameString(m_name)).arg(m_level).arg(bab()).arg(fort()).arg(ref()).arg(will());
}


void ClassType::updateLeveledNumbers()
{

}

void ClassType::updateClassReference()
{
	QString path = QString(":/StarfinderCharacterApp/Resources/%1.json").arg(nameString(m_name));
	QFile classFile(path);

	if (!classFile.open(QIODevice::ReadOnly)) {
		qWarning("Error opening file.");
	}

	QByteArray classData = classFile.readAll();

	QJsonDocument classDoc(QJsonDocument::fromJson(classData));

	QJsonObject classObj = classDoc.object();
	if (classObj.contains("Key Ability") && classObj.value("Key Ability").isString())
		keyAbility = Ability::scoreFromString(classObj.value("Key Ability").toString());
	if (classObj.contains("BAB Rate") && classObj.value("BAB Rate").isDouble())
		m_bab = classObj.value("BAB Rate").toDouble();
	if (classObj.contains("Fort Rate") && classObj.value("Fort Rate").isBool())
		m_fort = classObj.value("Fort Rate").toBool();
	if (classObj.contains("Ref Rate") && classObj.value("Ref Rate").isBool())
		m_fort = classObj.value("Ref Rate").toBool();
	if (classObj.contains("Will Rate") && classObj.value("Will Rate").isBool())
		m_fort = classObj.value("Will Rate").toBool();
	if (classObj.contains("Stamina Rate") && classObj.value("Stamina Rate").isDouble())
		m_stamina = classObj.value("Stamina Rate").toInt();
	if (classObj.contains("HP Rate") && classObj.value("HP Rate").isDouble())
		m_hp = classObj.value("HP Rate").toInt();
	if (classObj.contains("Skill Rate") && classObj.value("Skill Rate").isDouble())
		m_skill = classObj.value("Skill Rate").toInt();
	classFile.close();
}

int ClassType::calcSave(bool isGood)
{
	return (isGood ? (2 + (m_level / 2)) : (m_level / 3));
}

ClassType::Name ClassType::nameValue(QString n)
{
	return static_cast<Name>(QMetaEnum::fromType<Name>().keyToValue(n.toUtf8()));
}

QString ClassType::nameString(Name n)
{
	return QMetaEnum::fromType<Name>().valueToKey(n);
}
