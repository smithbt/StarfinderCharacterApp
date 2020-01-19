#pragma once

#include <QJsonArray>
#include <QJsonObject>
#include <QMetaEnum>
#include <QString>
#include <QStringList>
#include "Item.h"

class Weapon : public Item
{
	Q_GADGET

public:
	enum class Type : int {
		Melee = 0,
		Ranged
	};
	Q_ENUM(Type)

	Weapon();
	Weapon(Type t);
	virtual ~Weapon();

	QStringList special;
	Type type;

	virtual void read(const QJsonObject& json);
	virtual void write(QJsonObject& json) const;
	virtual QString toString() const;
};

Q_DECLARE_METATYPE(Weapon*)
Q_DECLARE_OPAQUE_POINTER(Weapon*)