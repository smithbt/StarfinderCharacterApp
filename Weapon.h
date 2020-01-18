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
		Melee,
		Ranged
	};
	Q_ENUM(Type)

	Weapon();
	virtual ~Weapon();

	QStringList special;
	Type type;

	virtual void read(const QJsonObject& json);
	virtual void write(QJsonObject& json) const;
	virtual QString toString() const;
};

Q_DECLARE_METATYPE(Weapon*)
Q_DECLARE_OPAQUE_POINTER(Weapon*)