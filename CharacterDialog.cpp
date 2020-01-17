#include "CharacterDialog.h"

CharacterDialog::CharacterDialog(QWidget* parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	asWdgts.insert(static_cast<int>(Ability::Score::Strength), ui.STR_score);
	asWdgts.insert(static_cast<int>(Ability::Score::Dexterity), ui.DEX_score);
	asWdgts.insert(static_cast<int>(Ability::Score::Constitution), ui.CON_score);
	asWdgts.insert(static_cast<int>(Ability::Score::Intelligence), ui.INT_score);
	asWdgts.insert(static_cast<int>(Ability::Score::Wisdom), ui.WIS_score);
	asWdgts.insert(static_cast<int>(Ability::Score::Charisma), ui.CHA_score);
}

CharacterDialog::~CharacterDialog()
{
}

void CharacterDialog::saveToModel(Character* pc)
{
	pc->setProperty(CharacterNode::Type::Name, QVariant(ui.name_field->text()));

	QMetaEnum aEnum = QMetaEnum::fromType<Ability::Score>();
	for (int i = 0; i < aEnum.keyCount(); ++i) {
		Ability::Score score = static_cast<Ability::Score>(aEnum.value(i));
		Ability* a = new Ability(score, asWdgts[i]->value());
		pc->setAbility(a);
	}
}
