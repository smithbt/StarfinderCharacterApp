#include "WeaponDialog.h"

WeaponDialog::WeaponDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	wpn = Weapon();
}

WeaponDialog::~WeaponDialog()
{
}

Weapon& WeaponDialog::getWeapon()
{
	wpn.setLevel(ui.level_field->value());
	wpn.setPrice(ui.price_field->value());
	wpn.setBulk(ui.bulk_field->value());
	wpn.setName(ui.name_field->text());
	wpn.setProperties(QStringList(ui.properties_field->text()));
	return wpn;
}
