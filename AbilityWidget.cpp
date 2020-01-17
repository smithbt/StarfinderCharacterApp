#include "AbilityWidget.h"

AbilityWidget::AbilityWidget(QWidget *parent)
	: QWidget(parent),
	ability(new Ability())
{
	ui.setupUi(this);
	connect(this, &AbilityWidget::abilityChanged, [=]() {
			ui.name_label->setText(ability->name());
			ui.score_label->setNum(ability->score());
			ui.mod_label->setText(QString::asprintf("%+i", ability->modifier()));
		});
}

AbilityWidget::~AbilityWidget()
{
}

void AbilityWidget::setAbility(Ability* a)
{
	ability = a;
	emit abilityChanged(ability);
}

Ability* AbilityWidget::getAbility() const
{
	return ability;
}