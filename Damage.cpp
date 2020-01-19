#include "Damage.h"

Damage::Damage(int count, int size)
	: dieCount(count), dieSize(size), type(QString(""))
{

}

Damage::Damage(int count, int size, QString type)
	: dieCount(count), dieSize(size), type(type)
{

}

void Damage::read(const QJsonObject& json)
{
	if (json.contains("DieCount") && json.value("DieCount").isDouble())
		dieCount = json.value("DieCount").toInt();
	if (json.contains("DieSize") && json.value("DieSize").isDouble())
		dieSize = json.value("DieSize").toInt();
	if (json.contains("TypeString") && json.value("TypeString").isString())
		type = json.value("TypeString").toString();
}

void Damage::write(QJsonObject& json) const
{
	json.insert("DieCount", dieCount);
	json.insert("DieSize", dieSize);
	json.insert("TypeString", type);
}

QString Damage::toString() const
{
	return QString("%1d%2 %3").arg(dieCount).arg(dieSize).arg(type);
}
