#include "WeaponDialog.h"

WeaponDialog::WeaponDialog(QWidget *parent)
	: QDialog(parent), 
	weaponTypes(QMetaEnum::fromType<Weapon::Type>())
{
	ui.setupUi(this);
	QIntValidator* validPrice = new QIntValidator(ui.price_lineEdit);
	validPrice->setBottom(0);
	ui.price_lineEdit->setValidator(validPrice);
	damageRegEx = QRegularExpression("^(?<count>\\d+)[d,D](?<size>\\d+)\\s*(?<type>.*)$");
	QRegularExpressionValidator* validDice = new QRegularExpressionValidator(damageRegEx, ui.damage_lineEdit);
	ui.damage_lineEdit->setValidator(validDice);
	ui.damage_lineEdit->setPlaceholderText("e.g. 1d6 E & F");
	ui.damage_lineEdit->setCursorPosition(0);

	connect(ui.type_comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
		this, [=]() {this->updateFields(ui.type_comboBox->currentData().value<Weapon::Type>()); });
	for (int t = 0; t < weaponTypes.keyCount(); ++t) {
		ui.type_comboBox->addItem(
			weaponTypes.key(t), QVariant::fromValue<Weapon::Type>(
				static_cast<Weapon::Type>(weaponTypes.value(t))));
	}
	ui.type_comboBox->setCurrentIndex(0);
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

	if (wpn->type == Weapon::Type::Ranged) {
		RangedWeapon* rWpn = new RangedWeapon(wpn,
			ui.range_spinBox->value(), 
			parseDamageString(ui.damage_lineEdit->text()),
			ui.crit_lineEdit->text(),
			new Resource(0, ui.capacity_spinBox->value(), ui.usage_spinBox->value()));
		return QVariant::fromValue<RangedWeapon*>(rWpn);
	}
	else if (wpn->type == Weapon::Type::Melee) {
		MeleeWeapon* mWpn = new MeleeWeapon(wpn,
			parseDamageString(ui.damage_lineEdit->text()),
			ui.crit_lineEdit->text());
		return qVariantFromValue<MeleeWeapon*>(mWpn);
	}

	return QVariant::fromValue<Weapon*>(wpn);
}

Damage* WeaponDialog::parseDamageString(QString dmg)
{
	QRegularExpressionMatch dMatch = damageRegEx.match(dmg, 0, QRegularExpression::PartialPreferCompleteMatch);
	int count = 0;
	int size = 0;
	QString type = QString();
	if (dMatch.hasMatch() || dMatch.hasPartialMatch()) {
		count = dMatch.captured("count").toInt();
		size = dMatch.captured("size").toInt();
		type = dMatch.captured("type");
	}
	return new Damage(count, size, type);
}

void WeaponDialog::updateFields(Weapon::Type wt) 
{
	bool ranged = (wt == Weapon::Type::Ranged);
	bool melee = (wt == Weapon::Type::Melee);

	ui.rangedWeapon_fields->setVisible(ranged);
	ui.damage_fields->setVisible(ranged | melee);
}