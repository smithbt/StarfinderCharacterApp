#include "WeaponDialog.h"

WeaponDialog::WeaponDialog(QWidget *parent, Weapon* weapon)
	: QDialog(parent), 
	weaponTypes(QMetaEnum::fromType<Weapon::Type>()),
	damageRegEx("^(?<count>\\d+)[d,D](?<size>\\d+)\\s*(?<type>.*)$")
{
	ui.setupUi(this);
	
	QIntValidator* validPrice = new QIntValidator(ui.price_lineEdit);
	validPrice->setBottom(0);
	ui.price_lineEdit->setValidator(validPrice);

	QRegularExpressionValidator* validDice = new QRegularExpressionValidator(damageRegEx, ui.damage_lineEdit);
	ui.damage_lineEdit->setValidator(validDice);
	ui.damage_lineEdit->setPlaceholderText("e.g. 1d6 E & F");
	ui.damage_lineEdit->setCursorPosition(0);

	for (int t = 0; t < weaponTypes.keyCount(); ++t) {
		ui.type_comboBox->addItem(
			weaponTypes.key(t), QVariant::fromValue<Weapon::Type>(
				static_cast<Weapon::Type>(weaponTypes.value(t))));
	}
	ui.type_comboBox->setCurrentIndex(0);
	connect(ui.type_comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &WeaponDialog::updateFields);

	if (weapon)
		setWeapon(weapon);
	else
		m_weapon = nullptr;

}

WeaponDialog::~WeaponDialog()
{
}

void WeaponDialog::setWeapon(Weapon* weapon)
{
	if (weapon != m_weapon) {
		m_weapon = weapon;
		ui.type_comboBox->setCurrentText(weaponTypes.valueToKey(static_cast<int>(m_weapon->type)));
		ui.range_spinBox->setValue(m_weapon->range);
		ui.damage_lineEdit->setText(m_weapon->damage->toString());
		ui.crit_lineEdit->setText(m_weapon->crit);
		ui.capacity_spinBox->setValue(m_weapon->capacity());
		ui.usage_spinBox->setValue(m_weapon->usage());
		ui.level_spinBox->setValue(m_weapon->level);
		ui.price_lineEdit->setText(QString::number(m_weapon->price));
		ui.bulk_doubleSpinBox->setValue(m_weapon->bulk);
		ui.name_lineEdit->setText(m_weapon->name);
		ui.special_lineEdit->setText(m_weapon->special.join(", "));
	}
}

Weapon* WeaponDialog::getWeapon()
{
	return m_weapon;
}

void WeaponDialog::accept() 
{
	if (!m_weapon)
		m_weapon = new Weapon();
	m_weapon->type = ui.type_comboBox->currentData(Qt::UserRole).value<Weapon::Type>();
	m_weapon->range = ui.range_spinBox->value();
	m_weapon->damage = parseDamageString(ui.damage_lineEdit->text());
	m_weapon->crit = ui.crit_lineEdit->text();
	m_weapon->ammo->setMax(ui.capacity_spinBox->value());
	m_weapon->ammo->setStep(ui.usage_spinBox->value());
	m_weapon->level = ui.level_spinBox->value();
	m_weapon->price = ui.price_lineEdit->text().toInt();
	m_weapon->bulk = ui.bulk_doubleSpinBox->value();
	m_weapon->name = ui.name_lineEdit->text();
	m_weapon->special = ui.special_lineEdit->text().split(", ");

	emit weaponReady(m_weapon);
	QDialog::accept();
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

void WeaponDialog::updateFields()
{
	Weapon::Type wt = ui.type_comboBox->currentData().value<Weapon::Type>();

	bool ranged = (wt == Weapon::Type::Ranged);
	bool melee = (wt == Weapon::Type::Melee);

	ui.rangedWeapon_fields->setVisible(ranged);
	ui.damage_fields->setVisible(ranged | melee);
}