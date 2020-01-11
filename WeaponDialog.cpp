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
	wpn.setRange(ui.range_field->value());
	wpn.setCapacity(ui.capacity_field->value());
	wpn.setUsage(ui.usage_field->value());
	wpn.setPrice(ui.price_field->value());
	//wpn.setType(ui.type_field->currentText().toInt());
	wpn.setBulk(ui.bulk_field->value());
	wpn.setName(ui.name_field->text());
	wpn.setDamageDice(ui.damageDice_field->text());
	wpn.setDamageType(ui.damageType_field->text());
	wpn.setCritical(ui.critical_field->text());
	//wpn.setProperties();
	return wpn;
}
