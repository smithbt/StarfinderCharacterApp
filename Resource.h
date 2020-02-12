#pragma once

#include <QObject>
#include <QJsonObject>
#include <QString>

class Resource : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int max READ max WRITE setMax NOTIFY maxChanged)
	Q_PROPERTY(int current READ current WRITE setCurrent NOTIFY currentChanged)
	Q_PROPERTY(int step READ step WRITE setStep)

public:
	Resource(QObject* parent = nullptr);

	void adjustCurrent(int change);

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;
	QString toString() const;

	int max() const;
	void setMax(const int max);

	int current() const;
	void setCurrent(const int current);

	int step() const;
	void setStep(const int step);

signals:
	void maxChanged(int);
	void currentChanged(int);

private:
	int m_current;
	int m_max;
	int m_step;
};

