#pragma once

#include <QWidget>
#include "ui_WeaponWidget.h"
#include "Weapon.h"

class WeaponWidget : public QWidget
{
	Q_OBJECT

public:
	WeaponWidget(QWidget *parent = Q_NULLPTR);
	~WeaponWidget();

	void setWeapon(Weapon* w);

private:
	Ui::WeaponWidget ui;
};
