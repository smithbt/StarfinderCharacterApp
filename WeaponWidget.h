#pragma once

#include <QWidget>
#include <QPainter>
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

public slots:
	void updateLabels();

signals:
	void weaponChanged(Weapon*);
	void editingFinished();

protected:
	void paintEvent(QPaintEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	Ui::WeaponWidget ui;
	Weapon* weapon;
};
