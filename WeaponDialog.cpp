#include "WeaponDialog.h"

WeaponDialog::WeaponDialog(QWidget *parent)
	: QDialog(parent), 
	weaponTypes(QMetaEnum::fromType<Weapon::Type>())
{
	ui.setupUi(this);
	QIntValidator* validInt = new QIntValidator(this);
	validInt->setBottom(0);
	ui.price_lineEdit->setValidator(validInt);

	for (int t = 0; t < weaponTypes.keyCount(); ++t) {
		ui.type_comboBox->addItem(
			weaponTypes.key(t), QVariant::fromValue<Weapon::Type>(
				static_cast<Weapon::Type>(weaponTypes.value(t))));
	}
}

WeaponDialog::~WeaponDialog()
{
}

QVariant WeaponDialog::newWeapon()
{
	Weapon* wpn = new Weapon();
	wpn->level = ui.level_spinBox->value();
	wpn->price = ui.price_lineEdit->text().toInt();
	wpn->bulk = ui.bulk_doubleSpinBox->value();
	wpn->name = ui.name_lineEdit->text();
	wpn->special = ui.special_lineEdit->text().split(", ");
	if(ui.type_comboBox->currentData(Qt::UserRole).canConvert<Weapon::Type>())
		wpn->type = ui.type_comboBox->currentData(Qt::UserRole).value<Weapon::Type>();

	// hardcode values for testing
	if (wpn->type == Weapon::Type::Ranged) {
		RangedWeapon* rWpn = new RangedWeapon(wpn,
			40, new Damage(1, 8, "fire"), "burn",
			new Resource(20, 20, 1));
		return QVariant::fromValue<RangedWeapon*>(rWpn);
	}

	return QVariant::fromValue<Weapon*>(wpn);
}
