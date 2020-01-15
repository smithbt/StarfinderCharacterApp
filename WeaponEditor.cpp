#include "WeaponEditor.h"

WeaponEditor::WeaponEditor(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setMouseTracking(true);
	setAutoFillBackground(true);
}

WeaponEditor::~WeaponEditor()
{
}

void WeaponEditor::setWeapon(Weapon* w)
{
	wpn = w;
	ui.level_spinBox->setValue(wpn->getLevel());
	ui.name_lineEdit->setText(wpn->getName());
	ui.price_spinBox->setValue(wpn->getLevel());
}

Weapon* WeaponEditor::getWeapon()
{
	wpn->setLevel(ui.level_spinBox->value());
	wpn->setName(ui.name_lineEdit->text());
	wpn->setPrice(ui.price_spinBox->value());
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
