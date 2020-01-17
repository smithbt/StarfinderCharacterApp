#include "Resource.h"

Resource::Resource(int current, int max, int step)
	: current(current), max(max), step(step)
{

}

void Resource::adjustCurrent(int change)
{
	current += (step * change);
}

void Resource::read(const QJsonObject& json)
{
	if (json.contains("Current") && json.value("Current").isDouble())
		current = json.value("Current").toInt();
	if (json.contains("Maximum") && json.value("Maximum").isDouble())
		max = json.value("Maximum").toInt();
	if (json.contains("Step") && json.value("Step").isDouble())
		step = json.value("Step").toInt();
}

void Resource::write(QJsonObject& json) const
{
	json.insert("Current", current);
	json.insert("Maximum", max);
	json.insert("Step", step);
}

QString Resource::toString() const
{
	return QString("%1/%2 [step=%3]").arg(current, max, step);
}
