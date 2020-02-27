#include "Race.h"

Race::Race(QObject* parent)
	: QObject(parent),
	m_name(QString()),
	m_size(QString()),
	m_type(QString()),
	m_hitPoints(0),
	m_features()
{
}

Race::~Race()
{
	m_features.clear();
}

QString Race::name() const
{
	return m_name;
}

QString Race::size() const
{
	return m_size;
}

QString Race::type() const
{
	return m_type;
}

int Race::hitPoints() const
{
	return m_hitPoints;
}

QVector<QString> Race::features() const
{
	return m_features;
}

void Race::setName(QString name)
{
	m_name = name;
}

void Race::setSize(QString size)
{
	m_size = size;
}

void Race::setType(QString type)
{
	m_type = type;
}

void Race::setHitPoints(int hitPoints)
{
	m_hitPoints = hitPoints;
}

void Race::setFeatures(QVector<QString> features)
{
	m_features = features;
}

void Race::addFeature(QString feature)
{
	m_features.append(feature);
}

void Race::read(const QJsonObject& json)
{
	if (json.contains("Name") && json.value("Name").isString())
		m_name = json.value("Name").toString();
	if (json.contains("Size") && json.value("Size").isString())
		m_size = json.value("Size").toString();
	if (json.contains("Type") && json.value("Type").isString())
		m_type = json.value("Type").toString();
	if (json.contains("HP") && json.value("HP").isDouble())
		m_hitPoints = json.value("HP").toInt();
	if (json.contains("Features") && json.value("Features").isArray()) {
		QJsonArray featureArray = json.value("Features").toArray();
		for (int i = 0; i < featureArray.size(); ++i) {
			if (featureArray.at(i).isString())
				m_features.append(featureArray.at(i).toString());
		}
	}
}

void Race::write(QJsonObject& json) const
{
	json.insert("Name", m_name);
	json.insert("Size", m_size);
	json.insert("Type", m_type);
	json.insert("HP", m_hitPoints);
	QJsonArray featureArray;
	for (int i = 0; i < m_features.size(); ++i) {
		featureArray.append(m_features.at(i));
	}
	json.insert("Features", featureArray);
}

QJsonObject Race::toJsonObject() const
{
	QJsonObject json;
	write(json);
	return json;
}
