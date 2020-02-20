#include "Race.h"

Race::Race(QObject* parent)
	: QObject(parent),
	m_name(QString()),
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

int Race::hitPoints() const
{
	return m_hitPoints;
}

QMap<QString, QString> Race::features() const
{
	return m_features;
}

void Race::setName(QString name)
{
	m_name = name;
}

void Race::setHitPoints(int hitPoints)
{
	m_hitPoints = hitPoints;
}

void Race::setFeatures(QMap<QString, QString> features)
{
	m_features = features;
}

void Race::addFeature(QString name, QString description)
{
	m_features.insert(name, description);
}

void Race::read(const QJsonObject& json)
{
	if (json.contains("Name") && json.value("Name").isString())
		m_name = json.value("Name").toString();
	if (json.contains("HP") && json.value("HP").isDouble())
		m_hitPoints = json.value("HP").toInt();
	if (json.contains("Features") && json.value("Features").isArray()) {
		QJsonArray featureArray = json.value("Features").toArray();
		for (int i = 0; i < featureArray.size(); ++i) {
			if (featureArray.at(i).isObject()) {
				QJsonObject fObject = featureArray.at(i).toObject();
				if (fObject.contains("Name") && fObject.value("Name").isString() &&
					fObject.contains("Description") && fObject.value("Description").isString()) {
					QString key, value;
					key = fObject.value("Name").toString();
					value = fObject.value("Description").toString();
					m_features.insert(key, value);
				}
			}
		}
	}
}

void Race::write(QJsonObject& json) const
{
	json.insert("Name", m_name);
	json.insert("HP", m_hitPoints);
	QJsonArray featureArray;
	for (QMap<QString, QString>::ConstIterator i = m_features.cbegin(); i != m_features.cend(); ++i) {
		featureArray.append(QJsonObject{
			{"Name", i.key()},
			{"Description", i.value()} });
	}
	json.insert("Features", featureArray);
}

QJsonObject Race::toJsonObject() const
{
	QJsonObject json;
	write(json);
	return json;
}
