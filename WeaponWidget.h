#pragma once

#include <QWidget>
#include <QPainter>
#include "ui_WeaponWidget.h"
#include "Weapon.h"
#include "WeaponDialog.h"

class WeaponWidget : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(Weapon* weapon READ getWeapon WRITE setWeapon NOTIFY weaponChanged)

public:
	WeaponWidget(QWidget *parent = Q_NULLPTR);
	~WeaponWidget();

	Weapon* getWeapon() const;
	void setWeapon(Weapon* w);

private slots:
	void shootWeapon();
	void reloadWeapon();
	void openWeaponDialog();

signals:
	void weaponChanged(Weapon*);
	void editingFinished();

private:
	Ui::WeaponWidget ui;
	Weapon* weapon;
	QAction* fireAction;
	QAction* reloadAction;
	QAction* editAction;
	QAction* deleteAction;
};
