#include "WeaponWidget.h"

WeaponWidget::WeaponWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

WeaponWidget::~WeaponWidget()
{
}

void WeaponWidget::setWeapon(Weapon* w)
{
	ui.name_label->setText(w->getName());
	ui.bulk_label->setText(QString::number(w->getBulk()));
	ui.level_label->setText(QString::number(w->getLevel()));
	ui.price_label->setText(QString::number(w->getPrice()));
	ui.special_label->setText(w->getProperties().join(", "));
}
