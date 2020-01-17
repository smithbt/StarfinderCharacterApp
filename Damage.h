#pragma once

#include <QJsonObject>
#include <QMetaEnum>
#include <QString>

class Damage
{
	Q_GADGET
public:
	enum class Type {
		Bludgeoning,
		Piercing,
		Slashing
	};
	Q_DECLARE_FLAGS(Types, Type)
	Q_FLAG(Type)

	Damage(int count, int size);

	int dieCount;
	int dieSize;
	Type type;
	QString typeString;
	//QString typeString() const;

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;
	QString toString() const;
};

