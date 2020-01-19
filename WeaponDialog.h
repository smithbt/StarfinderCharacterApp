#pragma once

#include <QDialog>
#include "ui_WeaponDialog.h"
#include "Weapon.h"
#include "MeleeWeapon.h"
#include "RangedWeapon.h"

class WeaponDialog : public QDialog
{
	Q_OBJECT

public:
	WeaponDialog(QWidget *parent = Q_NULLPTR);
	~WeaponDialog();

	QVariant newWeapon();

private slots:
	void updateFields(Weapon::Type);

private:
	Ui::WeaponDialog ui;
	QRegularExpression damageRegEx;
	QMetaEnum weaponTypes;

	Damage* parseDamageString(QString dmg);
};
