#include "AbilityWidget.h"

AbilityWidget::AbilityWidget(QWidget *parent)
	: QWidget(parent),
	ability(nullptr)
{
	ui.setupUi(this);
	ui.edit_frame->setVisible(false);

	connect(this, &AbilityWidget::abilityChanged, [=]() {
		ui.ability_pushButton->setText(ability->name());
		ui.score_label->setNum(ability->score());
		ui.mod_label->setText(QString::asprintf("%+i", (ability->modifier())));
		ui.base_spinBox->setValue(ability->getBase());
		ui.upgrade_spinBox->setValue(ability->getUpgrade());
	});

	connect(ability, &Ability::upgradeChanged, ui.upgrade_spinBox, &QSpinBox::setValue);
	connect(ui.upgrade_spinBox, QOverload<int>::of(&QSpinBox::valueChanged), ability, &Ability::setUpgrade);

	connect(ability, &Ability::baseChanged, ui.base_spinBox, &QSpinBox::setValue);
	connect(ui.base_spinBox, QOverload<int>::of(&QSpinBox::valueChanged), ability, &Ability::setBase);

	connect(ability, &Ability::scoreChanged, ui.score_label, [=](){
		ui.score_label->setNum(ability->score()); });
	connect(ability, &Ability::scoreChanged, ui.mod_label, [=]() {
		ui.mod_label->setText(QString::asprintf("%+i", (ability->modifier()))); });
}

AbilityWidget::~AbilityWidget()
{
}

void AbilityWidget::setAbility(Ability* a)
{
	if (a != ability) {
		ability = a;
		emit abilityChanged(ability);
	}
}

Ability* AbilityWidget::getAbility() const
{
	return ability;
}
