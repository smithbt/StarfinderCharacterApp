#pragma once

#include <QDialog>
#include "ui_WeaponDialog.h"
#include "Weapon.h"
#include "RangedWeapon.h"

class WeaponDialog : public QDialog
{
	Q_OBJECT

public:
	WeaponDialog(QWidget *parent = Q_NULLPTR);
	~WeaponDialog();

	QVariant newWeapon();

private:
	Ui::WeaponDialog ui;
	QMetaEnum weaponTypes;
};
