#include "WeaponWidget.h"

WeaponWidget::WeaponWidget(QWidget* parent)
	: QWidget(parent),
	weapon(new Weapon()),
	attackMod(0),
	damageMod(0)
{
	ui.setupUi(this);

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

void WeaponWidget::setModifiers(int atkMod, int dmgMod)
{
	attackMod = atkMod;
	damageMod = dmgMod;
}

void WeaponWidget::updateLabels()
{
	ui.name_label->setText(weapon->name);
	ui.level_label->setNum(weapon->level);
	ui.attack_label->setText(QString::asprintf("%+i", attackMod));
	QString dmgString = QString::asprintf("%1%+i %3", damageMod).arg(weapon->damage->dice()).arg(weapon->damage->type);
	ui.damagelabel->setText(dmgString);
	ui.crit_label->setText(weapon->crit);
	ui.range_label->setText(QString("%1 ft.").arg(weapon->range));
	ui.capUse_progressBar->setMaximum(weapon->ammo->max);
	ui.capUse_progressBar->setValue(weapon->ammo->current);
	ui.price_label->setNum(weapon->price);
	ui.bulk_label->setNum(weapon->bulk);
	ui.special_label->setText(weapon->special.join(", "));
}