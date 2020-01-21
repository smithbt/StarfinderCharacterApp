#include "WeaponWidget.h"

WeaponWidget::WeaponWidget(QWidget* parent)
	: QWidget(parent),
	weapon(new Weapon()),
	attackMod(0)
{
	ui.setupUi(this);
	connect(this, &WeaponWidget::weaponChanged, &WeaponWidget::updateLabels);

	connect(ui.fire_pushButton, &QPushButton::clicked, this, [=]() { 
		weapon->ammo->adjustCurrent(-1); emit weaponChanged(weapon); });
	connect(ui.reload_pushButton, &QPushButton::clicked, this, [=]() { 
		weapon->ammo->current = weapon->ammo->max; emit weaponChanged(weapon); });
}

WeaponWidget::~WeaponWidget()
{
}

Weapon* WeaponWidget::getWeapon() const
{
	return weapon;
}

void WeaponWidget::setWeapon(Weapon* w)
{
	weapon = w;
	emit weaponChanged(weapon);
}

void WeaponWidget::setAttackModifiers(int abilityMod, int bab, int misc)
{
	attackMod = abilityMod + bab + misc;
}

void WeaponWidget::updateLabels()
{
	ui.name_label->setText(weapon->name);
	ui.level_label->setNum(weapon->level);
	ui.attack_label->setText(QString::asprintf("%+i", attackMod));
	ui.damagelabel->setText(weapon->damage->toString());
	ui.crit_label->setText(weapon->crit);
	ui.range_label->setText(QString("%1 ft.").arg(weapon->range));
	ui.capUse_progressBar->setMaximum(weapon->ammo->max);
	ui.capUse_progressBar->setValue(weapon->ammo->current);
	ui.price_label->setNum(weapon->price);
	ui.bulk_label->setNum(weapon->bulk);
	ui.special_label->setText(weapon->special.join(", "));
}