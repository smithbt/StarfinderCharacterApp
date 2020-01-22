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

	Weapon* newWeapon();

private slots:
	void updateFields();

private:
	Ui::WeaponDialog ui;
	QRegularExpression damageRegEx;
	QMetaEnum weaponTypes;

	Damage* parseDamageString(QString dmg);
};
