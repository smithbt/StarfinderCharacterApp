#include "ClassWidget.h"

ClassWidget::ClassWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

ClassWidget::~ClassWidget()
{
}

int ClassWidget::getLevel()
{
	return ui.levelSpinBox->value();
}

void ClassWidget::setClassName(QString className)
{
	if (className != ui.classLabel->text())
		ui.classLabel->setText(className);
}

void ClassWidget::setLevel(int level)
{
	if (level != getLevel())
		ui.levelSpinBox->setValue(level);
}
