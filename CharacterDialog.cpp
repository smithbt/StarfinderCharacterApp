#include "CharacterDialog.h"

CharacterDialog::CharacterDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

CharacterDialog::~CharacterDialog()
{
}

Character CharacterDialog::getCharacter()
{
	Character pc;
	pc.setName(ui.name_field->text());
	return pc;
}
