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
		{"Charisma", ui.chaSpinBox}
		};
}

CreatorWizard::~CreatorWizard()
{
}

void CreatorWizard::setClassList(QStringList classes)
{
	ui.classComboBox->addItems(classes);
}

void CreatorWizard::accept()
{
	json.insert("CharacterName", ui.characterNameLineEdit->text());

	// loop over ability scores
	for (QHash<QString, QSpinBox*>::Iterator i = abilitySpinBoxes.begin(); i != abilitySpinBoxes.end(); ++i) {
		QJsonObject aObject;
		aObject.insert("Name", i.key());
		aObject.insert("Base", i.value()->value());
		json.insert(i.key(), aObject);
	}

	// class
	QJsonObject cObject;
	cObject.insert("Class", ui.classComboBox->currentText());
	cObject.insert("Level", ui.levelSpinBox->value());
	json.insert("Classes", QJsonArray { cObject });

	QDialog::accept();
}

QJsonObject CreatorWizard::jsonData()
{
	return json;
}
