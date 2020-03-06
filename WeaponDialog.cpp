#include "WeaponDialog.h"

WeaponDialog::WeaponDialog(QWidget *parent)
	: QDialog(parent),
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
	
	QStringList types = { "Melee", "Ranged" };
	ui.type_comboBox->insertItems(0, types);
	ui.type_comboBox->setCurrentIndex(0);
	connect(ui.type_comboBox, &QComboBox::currentTextChanged, this, &WeaponDialog::updateFields);
}

WeaponDialog::~WeaponDialog()
{
}

void WeaponDialog::setName(const QString name)
{
	ui.name_lineEdit->setText(name);
}

void WeaponDialog::setLevel(const int level)
{
	ui.level_spinBox->setValue(level);
}

void WeaponDialog::setBulk(const double bulk)
{
	ui.bulk_doubleSpinBox->setValue(bulk);
}

void WeaponDialog::setPrice(const int price)
{
	ui.price_lineEdit->setText(QString::number(price));
}

void WeaponDialog::setType(const QString type)
{
	ui.type_comboBox->setCurrentText(type);
}

void WeaponDialog::setDamage(const QString damage)
{
	ui.damage_lineEdit->setText(damage);
}

void WeaponDialog::setCrit(const QString crit)
{
	ui.crit_lineEdit->setText(crit);
}

void WeaponDialog::setRange(const int range)
{
	ui.range_spinBox->setValue(range);
}

void WeaponDialog::setCapacity(const int capacity)
{
	ui.capacity_spinBox->setValue(capacity);
}

void WeaponDialog::setUsage(const int usage)
{
	ui.usage_spinBox->setValue(usage);
}

void WeaponDialog::setSpecial(const QStringList special)
{
	ui.special_lineEdit->setText(special.join(", "));
}

QString WeaponDialog::getName() const
{
	return ui.name_lineEdit->text();
}

int WeaponDialog::getLevel() const
{
	return ui.level_spinBox->value();
}

double WeaponDialog::getBulk() const
{
	return ui.bulk_doubleSpinBox->value();
}

int WeaponDialog::getPrice() const
{
	return ui.price_lineEdit->text().toInt();
}

QString WeaponDialog::getType() const
{
	return ui.type_comboBox->currentText();
}

QVariantList WeaponDialog::getDamage() const
{
	QRegularExpressionMatch dMatch = damageRegEx.match(
		ui.damage_lineEdit->text(), 0, QRegularExpression::PartialPreferCompleteMatch);
	int count = 0;
	int size = 0;
	QString type = QString();
	if (dMatch.hasMatch() || dMatch.hasPartialMatch()) {
		count = dMatch.captured("count").toInt();
		size = dMatch.captured("size").toInt();
		type = dMatch.captured("type");
	}
	return { count, size, type };
}

QString WeaponDialog::getCrit() const
{
	return ui.crit_lineEdit->text();
}

int WeaponDialog::getRange() const
{
	return ui.range_spinBox->value();
}

int WeaponDialog::getCapacity() const
{
	return ui.capacity_spinBox->value();
}

int WeaponDialog::getUsage() const
{
	return ui.usage_spinBox->value();
}

QStringList WeaponDialog::getSpecial() const
{
	return ui.special_lineEdit->text().split(", ");
}

void WeaponDialog::updateFields(const QString wt)
{
	bool ranged = (wt == "Ranged");
	bool melee = (wt == "Melee");

	ui.rangedWeapon_fields->setVisible(ranged);
	ui.damage_fields->setVisible(ranged | melee);
}