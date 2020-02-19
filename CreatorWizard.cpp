#include "CreatorWizard.h"

CreatorWizard::CreatorWizard(QWidget *parent)
	: QWizard(parent),
	abilitySpinBoxes()
{
	ui.setupUi(this);

	abilitySpinBoxes = {
		{"Strength", ui.strSpinBox},
		{"Dexterity", ui.dexSpinBox},
		{"Constitution", ui.conSpinBox},
		{"Intelligence", ui.intSpinBox},
		{"Wisdom", ui.wisSpinBox},
		{"Charisma", ui.chaSpinBox} };
}

CreatorWizard::~CreatorWizard()
{
}

void CreatorWizard::accept()
{
	QJsonObject json;
	json.insert("CharacterName", ui.characterNameLineEdit->text());

	// loop over ability scores
	QJsonObject abilities;
	for (QHash<QString, QSpinBox*>::Iterator i = abilitySpinBoxes.begin(); i != abilitySpinBoxes.end(); ++i) {
		abilities.insert(i.key(), QJsonObject{
			{"Name", i.key()},
			{"Base", i.value()->value()} });
	}
	json.insert("Abilities", abilities);

	//// class
	//QJsonObject cObject;
	//cObject.insert("Class", ui.classComboBox->currentText());
	//cObject.insert("Level", ui.levelSpinBox->value());
	//json.insert("Classes", QJsonArray { cObject });

	QDialog::accept();
	emit characterDataReady(json);
}
