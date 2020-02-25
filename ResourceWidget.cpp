#include "ResourceWidget.h"

ResourceWidget::ResourceWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

ResourceWidget::~ResourceWidget()
{
}

int ResourceWidget::getCurrentValue() const
{
	return ui.currentSpinBox->value();
}

void ResourceWidget::setCurrent(int current)
{
	if (current != ui.currentSpinBox->value())
		ui.currentSpinBox->setValue(current);
}

void ResourceWidget::setMax(int max)
{ 
	if (max != ui.maxLabel->text().toInt()) {
		ui.maxLabel->setNum(max);
		ui.currentSpinBox->setMaximum(max);
	}
}

void ResourceWidget::setStep(int step)
{
	if (step != ui.currentSpinBox->singleStep())
		ui.currentSpinBox->setSingleStep(step);
}
