#pragma once

#include <QObject>
#include <QJsonObject>
#include <QString>

class Item : public QObject
{
	Q_OBJECT

public: 
	Item(QObject* parent = nullptr);
	virtual ~Item();

	QString name;
	int level, price;
	double bulk;
	QString description;

	virtual void read(const QJsonObject& json);
	virtual void write(QJsonObject& json) const;
	virtual QString toString() const;
};