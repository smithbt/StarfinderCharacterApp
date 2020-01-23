#include "CharacterDialog.h"

CharacterDialog::CharacterDialog(QWidget* parent)
	: QDialog(parent),
	asbWdgts(6),
	asuWdgts(6)
{
	ui.setupUi(this);

	QMetaEnum classes = QMetaEnum::fromType<ClassType::Name>();
	for (int c = 0; c < classes.keyCount(); ++c) {
		ui.class_comboBox->addItem(classes.key(c), classes.value(c));
	}

	asbWdgts.replace(static_cast<int>(Ability::Score::Strength), ui.STR_score);
	asbWdgts.replace(static_cast<int>(Ability::Score::Dexterity), ui.DEX_score);
	asbWdgts.replace(static_cast<int>(Ability::Score::Constitution), ui.CON_score);
	asbWdgts.replace(static_cast<int>(Ability::Score::Intelligence), ui.INT_score);
	asbWdgts.replace(static_cast<int>(Ability::Score::Wisdom), ui.WIS_score);
	asbWdgts.replace(static_cast<int>(Ability::Score::Charisma), ui.CHA_score);

	asuWdgts.replace(static_cast<int>(Ability::Score::Strength), ui.STRupgrade_spinBox);
	asuWdgts.replace(static_cast<int>(Ability::Score::Dexterity), ui.DEXupgrade_spinBox);
	asuWdgts.replace(static_cast<int>(Ability::Score::Constitution), ui.CONupgrade_spinBox);
	asuWdgts.replace(static_cast<int>(Ability::Score::Intelligence), ui.INTupgrade_spinBox);
	asuWdgts.replace(static_cast<int>(Ability::Score::Wisdom), ui.WISupgrade_spinBox);
	asuWdgts.replace(static_cast<int>(Ability::Score::Charisma), ui.CHAupgrade_spinBox);
}

CharacterDialog::~CharacterDialog()
{
	qDeleteAll(asbWdgts);
	qDeleteAll(asuWdgts);
}

void CharacterDialog::newCharacter(Character* pc)
{
	pc->setProperty(CharacterModel::Name, QVariant(ui.name_field->text()));

	ClassType* ct = new ClassType(pc->model);
	ct->setName(ui.class_comboBox->currentData().value<ClassType::Name>());
	ct->setLevel(ui.level_spinBox->value());
	pc->setProperty(CharacterModel::Classes, QVariant::fromValue(ct));

	QMetaEnum aEnum = QMetaEnum::fromType<Ability::Score>();
	for (int i = 0; i < aEnum.keyCount(); ++i) {
		Ability::Score score = static_cast<Ability::Score>(aEnum.value(i));
		Ability* a = new Ability(score, asbWdgts.at(i)->value(), asuWdgts.at(i)->value());
		pc->setAbility(a);
	}
}
