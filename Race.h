#pragma once

#include <QJsonArray>
#include <QJsonObject>
#include <QObject>
#include <QVector>

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
	QVector<QString> features() const;

	//Setters
	void setName(QString name);
	void setSize(QString size);
	void setType(QString type);
	void setHitPoints(int hitPoints);
	void setFeatures(QVector<QString> features);

	void addFeature(QString feature);

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;
	QJsonObject toJsonObject() const;

private:
	QString m_name;
	QString m_size;
	QString m_type;
	int m_hitPoints;
	QVector<QString> m_features;
};
