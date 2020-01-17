#include "WeaponDialog.h"

WeaponDialog::WeaponDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

WeaponDialog::~WeaponDialog()
{
}

Weapon* WeaponDialog::newWeapon()
{
	Weapon *wpn = new Weapon();
	wpn->level = ui.level_field->value();
	wpn->price = ui.price_field->value();
	wpn->bulk  = ui.bulk_field->value();
	wpn->name = ui.name_field->text();
	wpn->special = ui.properties_field->text().split(", ");
	return wpn;
}
