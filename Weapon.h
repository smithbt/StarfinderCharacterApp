#pragma once

#include <QJsonArray>
#include <QJsonObject>
#include <QMetaType>
#include <QPainter>
#include <QPalette>
#include <QString>
#include <QStringList>

class Weapon
{
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
	enum class EditMode { Editable, ReadOnly };

	Weapon();
	~Weapon();
	Weapon(const Weapon& other);
	Weapon& operator=(const Weapon&);

	void setName(QString name);
	void setLevel(int level);
	void setPrice(int price);
	void setBulk(double bulk);
	void setProperties(QStringList props);

	QString getName();
	int getLevel();
	int getPrice();
	double getBulk();
	QStringList getProperties();

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;

private:
	QString name;
	int level, price;
	double bulk;
	QStringList properties;

};

Q_DECLARE_OPAQUE_POINTER(Weapon);
Q_DECLARE_METATYPE(Weapon);