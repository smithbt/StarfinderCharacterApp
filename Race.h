#pragma once

#include <QJsonArray>
#include <QJsonObject>
#include <QMap>
#include <QObject>

class Race : public QObject
{
	Q_OBJECT

public:
	Race(QObject *parent);
	~Race();

	// Getters
	QString name() const;
	int hitPoints() const;
	QMap<QString, QString> features() const;

	//Setters
	void setName(QString name);
	void setHitPoints(int hitPoints);
	void setFeatures(QMap<QString, QString> features);

	void addFeature(QString name, QString description);

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;
	QJsonObject toJsonObject() const;

private:
	QString m_name;
	int m_hitPoints;
	QMap<QString, QString> m_features;
};
