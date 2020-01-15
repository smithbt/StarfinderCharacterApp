#pragma once

#include <QJsonArray>
#include <QJsonObject>
#include <QMetaType>
#include <QString>
#include <QStringList>
#include "Item.h"

class Weapon : public Item
{
	Q_GADGET

public:
	enum class Type : int {
		Unknown = 0,
		AdvMelee = 1,
		BasicMelee = 2,
		Grenade = 3,
		Heavy = 4,
		LongArm = 5,
		SmallArm = 6,
		Sniper = 7,
		Special = 8
	};

	QStringList getProperties();
	void setProperties(QStringList props);

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;
	QString toString() const;

private:
	QStringList special;

};

Q_DECLARE_METATYPE(Weapon*)
Q_DECLARE_OPAQUE_POINTER(Weapon*)