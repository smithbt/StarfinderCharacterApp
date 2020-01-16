#include "WeaponEditor.h"

WeaponEditor::WeaponEditor(QWidget *parent)
	: QWidget(parent),
	wpn(new Weapon())
{
	ui.setupUi(this);
	setMouseTracking(true);
	setAutoFillBackground(true);
	QIntValidator* validInt = new QIntValidator(this);
	validInt->setBottom(0);
	ui.price_lineEdit->setValidator(validInt);
}

WeaponEditor::~WeaponEditor()
{
}

void WeaponEditor::setWeapon(Weapon* w)
{
	wpn = w;
	ui.level_spinBox->setValue(wpn->getLevel());
	ui.name_lineEdit->setText(wpn->getName());
	ui.price_lineEdit->setText(QString::number(wpn->getLevel()));
}

Weapon* WeaponEditor::getWeapon()
{
	wpn->setLevel(ui.level_spinBox->value());
	wpn->setName(ui.name_lineEdit->text());
	wpn->setPrice(ui.price_lineEdit->text().toInt());
	return wpn;
}

void WeaponEditor::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
}

void WeaponEditor::mouseMoveEvent(QMouseEvent* event)
{
	QWidget::mouseMoveEvent(event);
}

void WeaponEditor::mouseReleaseEvent(QMouseEvent* event)
{
	emit editingFinished();
	QWidget::mouseReleaseEvent(event);
}
