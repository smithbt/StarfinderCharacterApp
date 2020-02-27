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
	QString size() const;
	QString type() const;
	int hitPoints() const;
	QMap<QString, QString> features() const;

	//Setters
	void setName(QString name);
	void setSize(QString size);
	void setType(QString type);
	void setHitPoints(int hitPoints);
	void setFeatures(QMap<QString, QString> features);

	void addFeature(QString name, QString description);

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;
	QJsonObject toJsonObject() const;

private:
	QString m_name;
	QString m_size;
	QString m_type;
	int m_hitPoints;
	QMap<QString, QString> m_features;
};
