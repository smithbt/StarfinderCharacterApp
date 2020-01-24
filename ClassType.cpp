#include "ClassType.h"

ClassType::ClassType(QObject *parent)
	: QObject(parent),
	m_name(Envoy),
	model(new QSqlQueryModel),
	m_level(0),
	m_bab(1),
	m_fort(0),
	m_ref(0),
	m_will(0),
	m_stamina(6),
	m_hp(6),
	m_skill(6)
{
	db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(":/Resources/Starfinder.sqlite3");

	connect(this, &ClassType::nameChanged, &ClassType::updateClassReference);
	connect(this, &ClassType::levelChanged, &ClassType::updateLeveledNumbers);
}

void ClassType::updateLeveledNumbers()
{
	m_bab = m_level * model->index(0, 3).data().toDouble();
	m_fort = calcSave(model->index(0, 4).data().toBool());
	m_ref = calcSave(model->index(0, 5).data().toBool());
	m_will = calcSave(model->index(0, 6).data().toBool());
	m_stamina = m_level * model->index(0, 7).data().toInt();
	m_hp = m_level * model->index(0, 8).data().toInt();
	m_skill = m_level * model->index(0, 9).data().toInt();
}

ClassType::~ClassType()
{
	delete model;
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
	return m_fort;
}

int ClassType::ref()
{
	return m_ref;
}

int ClassType::will()
{
	return m_will;
}

int ClassType::bab()
{
	return m_bab;
}

int ClassType::stamina()
{
	return m_stamina;
}

int ClassType::hp()
{
	return m_hp;
}

int ClassType::skills()
{
	return m_skill;
}

void ClassType::read(const QJsonObject& json)
{
	if (json.contains("Name") && json.value("Name").isString())
		m_name = nameValue(json.value("Name").toString());
	if (json.contains("level") && json.value("level").isDouble())
		m_level = json.value("level").toInt();
}

void ClassType::write(QJsonObject& json) const
{
	json.insert("Name", nameString(m_name));
	json.insert("level", m_level);
}

QString ClassType::toString()
{
	return QString("%1 %2: +%3 BAB, +%4 Fort, +%5 Ref, +%6 Will")
		.arg(nameString(m_name)).arg(m_level).arg(bab()).arg(fort()).arg(ref()).arg(will());
}

void ClassType::updateClassReference()
{
	model->clear();
	QString query = QString("SELECT * FROM Classes WHERE Id = %1").arg(m_name);
	model->setQuery(query, db);

	keyAbility = Ability::scoreFromString(model->index(0, 2).data().toString());
}

int ClassType::calcSave(bool isGood)
{
	if (isGood)
		return (2 + (m_level / 2));
	else
		return (m_level / 3);
}

ClassType::Name ClassType::nameValue(QString n)
{
	return static_cast<Name>(QMetaEnum::fromType<Name>().keyToValue(n.toUtf8()));
}

QString ClassType::nameString(Name n)
{
	return QMetaEnum::fromType<Name>().valueToKey(n);
}
