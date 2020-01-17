#include "AbilityWidget.h"

AbilityWidget::AbilityWidget(QWidget *parent)
	: QWidget(parent),
	ability(new Ability()),
	mapper(new QDataWidgetMapper(parent))
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

void AbilityWidget::linkToModel(Ability::Score s, Character* pc)
{
	connect(pc->model, &QAbstractItemModel::modelReset,
		mapper, &QDataWidgetMapper::revert);
	mapper->setModel(pc->model);
	mapper->setRootIndex(pc->model->listTypeRoot(CharacterNode::Type::Ability));
	mapper->setCurrentIndex(pc->getAbilityIndex(s).row());
	mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
	mapper->setItemDelegate(new AbilityDelegate());
	mapper->addMapping(this, 1);
}
