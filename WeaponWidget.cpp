#include "WeaponWidget.h"

WeaponWidget::WeaponWidget(QWidget* parent)
	: QWidget(parent),
	weapon(new Weapon()),
	attackMod(0)
{
	ui.setupUi(this);
	connect(this, &WeaponWidget::weaponChanged, &WeaponWidget::updateLabels);
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
	ui.price_label->setNum(weapon->price);
	ui.bulk_label->setNum(weapon->bulk);
	ui.special_label->setText(weapon->special.join(", "));
}