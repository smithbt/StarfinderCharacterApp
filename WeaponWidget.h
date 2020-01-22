#pragma once

#include <QWidget>
#include "ui_WeaponWidget.h"
#include "Weapon.h"

class WeaponWidget : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(Weapon* weapon READ getWeapon WRITE setWeapon NOTIFY weaponChanged)

public:
	WeaponWidget(QWidget *parent = Q_NULLPTR);
	~WeaponWidget();

	Weapon* getWeapon() const;
	void setWeapon(Weapon* w);

	void setModifiers(int atkMod, int dmgMod);

public slots:
	void updateLabels();

signals:
	void weaponChanged(Weapon*);

private:
	Ui::WeaponWidget ui;
	Weapon* weapon;
	int attackMod;
	int damageMod;
};
