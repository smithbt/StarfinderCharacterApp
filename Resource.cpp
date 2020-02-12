#include "Resource.h"

Resource::Resource(QObject* parent)
	: QObject(parent), m_current(1), m_max(1), m_step(1)
{

}

void Resource::adjustCurrent(int change)
{
	m_current += (m_step * change);
	emit currentChanged(m_current);
}

void Resource::read(const QJsonObject& json)
{
	if (json.contains("Current") && json.value("Current").isDouble())
		setCurrent(json.value("Current").toInt());
	if (json.contains("Maximum") && json.value("Maximum").isDouble())
		setMax(json.value("Maximum").toInt());
	if (json.contains("Step") && json.value("Step").isDouble())
		setStep(json.value("Step").toInt());
}

void Resource::write(QJsonObject& json) const
{
	json.insert("Current", m_current);
	json.insert("Maximum", m_max);
	json.insert("Step", m_step);
}

QString Resource::toString() const
{
	return QString("%1/%2 [step=%3]").arg(m_current).arg(m_max).arg(m_step);
}

int Resource::max() const
{
	return m_max;
}

void Resource::setMax(const int max)
{
	if (max != m_max) {
		m_max = max;
		emit maxChanged(m_max);
	}
}

int Resource::current() const
{
	return m_current;
}

void Resource::setCurrent(const int current)
{
	if (current != m_current) {
		m_current = current;
		emit currentChanged(m_current);
	}
}

int Resource::step() const
{
	return m_step;
}

void Resource::setStep(const int step)
{
	if (step != m_step) {
		m_step = step;
	}
}
