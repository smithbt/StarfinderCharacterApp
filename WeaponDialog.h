#pragma once

#include <QDialog>
#include "ui_WeaponDialog.h"
#include "Weapon.h"

class WeaponDialog : public QDialog
{
	Q_OBJECT
	Q_PROPERTY(Weapon* weapon READ getWeapon WRITE setWeapon)

public:
	WeaponDialog(QWidget *parent = Q_NULLPTR, Weapon* weapon = nullptr);
	~WeaponDialog();

	void setWeapon(Weapon* weapon);
	Weapon* getWeapon();

public slots:
	void accept() override;

private slots:
	void updateFields();

signals:
	void weaponReady(Weapon*);

private:
	Ui::WeaponDialog ui;
	QRegularExpression damageRegEx;
	QMetaEnum weaponTypes;
	Weapon* m_weapon;

	Damage* parseDamageString(QString dmg);
};
