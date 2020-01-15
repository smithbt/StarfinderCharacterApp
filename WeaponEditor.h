#pragma once

#include <QWidget>
#include "ui_WeaponEditor.h"
#include "Weapon.h"

class WeaponEditor : public QWidget
{
	Q_OBJECT

public:
	WeaponEditor(QWidget *parent = Q_NULLPTR);
	~WeaponEditor();

	void setWeapon(Weapon* w);
	Weapon* getWeapon();

private:
	Weapon* wpn;
	Ui::WeaponEditor ui;

signals:
	void editingFinished();

protected:
	void paintEvent(QPaintEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override; 
};
