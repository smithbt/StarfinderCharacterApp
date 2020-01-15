#pragma once

#include <QDialog>
#include "ui_WeaponDialog.h"
#include "Weapon.h"

class WeaponDialog : public QDialog
{
	Q_OBJECT

public:
	WeaponDialog(QWidget *parent = Q_NULLPTR);
	~WeaponDialog();

	Weapon* getWeapon();

private:
	Ui::WeaponDialog ui;
};
