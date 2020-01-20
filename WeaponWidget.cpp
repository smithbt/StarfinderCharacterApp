#include "WeaponWidget.h"

WeaponWidget::WeaponWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(this, SIGNAL(weaponChanged), SLOT(updateLabels));
}

WeaponWidget::~WeaponWidget()
{
}

Weapon* WeaponWidget::getWeapon()
{
	return weapon;
}

void WeaponWidget::setWeapon(Weapon* w)
{
	weapon = w;
}

void WeaponWidget::updateLabels()
{
	ui.name_label->setText(weapon->name);
	ui.level_label->setNum(weapon->level);
	ui.price_label->setNum(weapon->price);
	ui.bulk_label->setNum(weapon->bulk);
	ui.special_label->setText(weapon->special.join(", "));
}