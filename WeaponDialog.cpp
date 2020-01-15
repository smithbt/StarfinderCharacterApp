#include "WeaponDialog.h"

WeaponDialog::WeaponDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

WeaponDialog::~WeaponDialog()
{
}

Weapon* WeaponDialog::getWeapon()
{
	Weapon *wpn = new Weapon();
	wpn->setLevel(ui.level_field->value());
	wpn->setPrice(ui.price_field->value());
	wpn->setBulk(ui.bulk_field->value());
	wpn->setName(ui.name_field->text());
	wpn->setProperties(ui.properties_field->text().split(", "));
	return wpn;
}
