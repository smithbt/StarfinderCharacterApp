#include "AbilityWidget.h"

AbilityWidget::AbilityWidget(QWidget *parent)
	: QWidget(parent),
	a(new Ability())
{
	ui.setupUi(this);
}

AbilityWidget::~AbilityWidget()
{
}

void AbilityWidget::setAbility(Ability* as)
{
	a = as;
	ui.name_label->setText(a->name());
	ui.score_label->setText(QString::number(a->score()));
	ui.mod_label->setText(QString::asprintf("%+i", a->modifier()));
}

Ability* AbilityWidget::getAbility()
{
	return a;
}
