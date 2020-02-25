#include "AbilityWidget.h"

AbilityWidget::AbilityWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.edit_frame->setVisible(false);
	
	connect(ui.ability_pushButton, &QPushButton::toggled, [this](bool checked) { if (!checked) emit editDone(this); });
}

AbilityWidget::~AbilityWidget()
{
}

int AbilityWidget::base() const
{
	return ui.base_spinBox->value();
}

int AbilityWidget::upgrade() const
{
	return ui.upgrade_spinBox->value();
}

void AbilityWidget::setScore(int score)
{
	if (score != ui.score_label->text())
		ui.score_label->setNum(score);
}

void AbilityWidget::setModifier(int modifier)
{
	QString modText = QString::asprintf("%+i", (modifier));
	if (modText != ui.mod_label->text())
		ui.mod_label->setText(modText);
}

void AbilityWidget::setBase(int base)
{
	if (base != ui.base_spinBox->value()) {
		ui.base_spinBox->setValue(base);
	}
}

void AbilityWidget::setUpgrade(int upgrade)
{
	if (upgrade != ui.upgrade_spinBox->value()) {
		ui.upgrade_spinBox->setValue(upgrade);
	}
}

void AbilityWidget::setLabelText(QString name)
{
	ui.ability_pushButton->setText(name);
}
