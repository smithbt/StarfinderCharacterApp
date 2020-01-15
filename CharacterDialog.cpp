#include "CharacterDialog.h"

CharacterDialog::CharacterDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

CharacterDialog::~CharacterDialog()
{
}

void CharacterDialog::saveToModel(Character* pc)
{
	pc->setProperty(CharacterNode::Type::Name, QVariant(ui.name_field->text()));
}
