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

	void setLevel(int level);
	void setRange(int range);
	void setCapacity(int capacity);
	void setUsage(int usage);
	void setPrice(int price);
	void setType(Type type);
	void setBulk(double bulk);
	void setName(QString name);
	void setDamageDice(QString dmgDice);
	void setDamageType(QString dmgType);
	void setCritical(QString critical);
	void setProperties(QStringList props);

	int getLevel();
	int getRange();
	int getCapacity();
	int getUsage();
	int getPrice();
	Type getType();
	double getBulk();
	QString getName();
	QString getDamageDice();
	QString getDamageType();
	QString getCritical();
	QStringList getProperties();

	void paint(QPainter* painter, const QRect& rect, const QPalette& palette, EditMode mode) const;
	QSize sizeHint() const;
	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;

private:
	int level, range, capacity, usage, price;
	Type type;
	double bulk;
	QString name, damageDice, damageType, critical;
	QStringList properties;

};

Q_DECLARE_OPAQUE_POINTER(Weapon);
Q_DECLARE_METATYPE(Weapon);