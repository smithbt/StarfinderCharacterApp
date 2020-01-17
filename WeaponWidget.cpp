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
	ui.name_label->setText(w->name);
	ui.bulk_label->setText(QString::number(w->bulk));
	ui.level_label->setText(QString::number(w->level));
	ui.price_label->setText(QString::number(w->price));
	ui.special_label->setText(w->special.join(", "));
}
