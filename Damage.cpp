#include "Damage.h"

Damage::Damage(int count, int size)
	: dieCount(count), dieSize(size), type(Type::Bludgeoning), typeString(QString(""))
{

}

Damage::Damage(int count, int size, QString type)
	: dieCount(count), dieSize(size), type(Type::Bludgeoning), typeString(type)
{

}

//QString Damage::typeString() const
//{
//	QMetaEnum typeE = QMetaEnum::fromType<Type>();
//	return typeE.valueToKey(static_cast<int>(type));
//}

void Damage::read(const QJsonObject& json)
{
	if (json.contains("DieCount") && json.value("DieCount").isDouble())
		dieCount = json.value("DieCount").toInt();
	if (json.contains("DieSize") && json.value("DieSize").isDouble())
		dieSize = json.value("DieSize").toInt();
	if (json.contains("Type") && json.value("Type").isDouble())
		type = static_cast<Type>(json.value("Type").toInt());
	if (json.contains("TypeString") && json.value("TypeString").isString())
		typeString = json.value("TypeString").toString();
}

void Damage::write(QJsonObject& json) const
{
	json.insert("DieCount", dieCount);
	json.insert("DieSize", dieSize);
	json.insert("Type", static_cast<int>(type));
	json.insert("TypeString", typeString);
}

QString Damage::toString() const
{
	return QString("%1d%2 %3").arg(dieCount).arg(dieSize).arg(typeString);
}
