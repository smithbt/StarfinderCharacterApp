#pragma once

#include <QDialog>
#include "ui_CharacterDialog.h"
#include "Character.h"

class CharacterDialog : public QDialog
{
	Q_OBJECT

public:
	CharacterDialog(QWidget *parent = Q_NULLPTR);
	~CharacterDialog();

	Character getCharacter();

private:
	Ui::CharacterDialog ui;
};
