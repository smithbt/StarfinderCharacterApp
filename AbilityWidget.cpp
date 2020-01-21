#include "AbilityWidget.h"

AbilityWidget::AbilityWidget(QWidget *parent)
	: QWidget(parent),
	abilities(),
	aMods(),
	aScores(),
	aEnum(QMetaEnum::fromType<Ability::Score>())
{
	ui.setupUi(this);

	
	aMods.insert(static_cast<int>(Ability::Score::Strength), ui.str_mod);
	aMods.insert(static_cast<int>(Ability::Score::Dexterity), ui.dex_mod);
	aMods.insert(static_cast<int>(Ability::Score::Constitution), ui.con_mod);
	aMods.insert(static_cast<int>(Ability::Score::Intelligence), ui.int_mod);
	aMods.insert(static_cast<int>(Ability::Score::Wisdom), ui.wis_mod);
	aMods.insert(static_cast<int>(Ability::Score::Charisma), ui.cha_mod);

	aScores.insert(static_cast<int>(Ability::Score::Strength), ui.str_score);
	aScores.insert(static_cast<int>(Ability::Score::Dexterity), ui.dex_score);
	aScores.insert(static_cast<int>(Ability::Score::Constitution), ui.con_score);
	aScores.insert(static_cast<int>(Ability::Score::Intelligence), ui.int_score);
	aScores.insert(static_cast<int>(Ability::Score::Wisdom), ui.wis_score);
	aScores.insert(static_cast<int>(Ability::Score::Charisma), ui.cha_score);

	connect(this, &AbilityWidget::abilityListChanged, [=]() {
			for (int i = 0; i < aEnum.keyCount(); ++i) {
				aScores.at(i)->setNum(abilities.at(i)->score());
				aMods.at(i)->setText(QString::asprintf("%+i", (abilities.at(i)->modifier())));
			}
		});
}

AbilityWidget::~AbilityWidget()
{
}

void AbilityWidget::setAbilityList(QVector<Ability*> a)
{
	abilities = a;
	emit abilityListChanged(abilities);
}

QVector<Ability*> AbilityWidget::getAbilityList() const
{
	return abilities;
}
