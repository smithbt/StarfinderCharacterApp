#include "CreatorWizard.h"

CreatorWizard::CreatorWizard(QWidget *parent)
	: QWizard(parent),
	abilitySpinBoxes()
{
	ui.setupUi(this);

	QStringList abilityNames = { "Strength",  "Dexterity",  "Constitution",  "Intelligence",  "Wisdom",  "Charisma" };
	ui.rAdjScoreComboBox->addItems(abilityNames);
	ui.tAbilityComboBox->addItems(abilityNames);
	ui.cKeyAbilityComboBox->addItems(abilityNames);
	abilitySpinBoxes = {
		{"Strength", ui.strSpinBox},
		{"Dexterity", ui.dexSpinBox},
		{"Constitution", ui.conSpinBox},
		{"Intelligence", ui.intSpinBox},
		{"Wisdom", ui.wisSpinBox},
		{"Charisma", ui.chaSpinBox} };

	QStringList saveRates = { "Good", "Poor" };
	ui.fortitudeComboBox->addItems(saveRates);
	ui.reflexComboBox->addItems(saveRates);
	ui.willComboBox->addItems(saveRates);
}

CreatorWizard::~CreatorWizard()
{
}

void CreatorWizard::accept()
{
	Character* pc = new Character();
	Race* r = pc->getRace();
	r->setName(ui.rNameLineEdit->text());
	r->setHitPoints(ui.rHPSpinBox->value());
	for (int i = 0; i < ui.rFeaturesListWidget->count(); ++i) {
		QStringList entry = ui.rFeaturesListWidget->item(i)->text().split(": ");
		r->addFeature(entry.at(0), entry.at(1));
	}
	pc->setRace(r);

	pc->setCharacterName(ui.characterNameLineEdit->text());

	// loop over ability scores
	for (QHash<QString, QSpinBox*>::Iterator i = abilitySpinBoxes.begin(); i != abilitySpinBoxes.end(); ++i) {
		pc->setAbilityProperty(i.key(), "base", QVariant(i.value()->value()));
	}

	QDialog::accept();
	emit characterReady(pc);
}

void CreatorWizard::on_rAdjButton_clicked()
{
	QString score = ui.rAdjScoreComboBox->currentText();
	int value = ui.rAdjSpinBox->value();
	if (value != 0 && abilitySpinBoxes.contains(score)) {
		QString text = ui.rAbilityAdjWidget->text();
		if (!text.isEmpty())
			text += "; ";
		text += QString::asprintf("%+i %2", value).arg(score);
		ui.rAbilityAdjWidget->setText(text);
		abilitySpinBoxes[score]->stepBy(value);
	}
	ui.rAdjScoreComboBox->setCurrentIndex(0);
	ui.rAdjSpinBox->setValue(0);
}

void CreatorWizard::on_rAddFeatureButton_clicked()
{
	QString name = ui.rFeatureNameLineEdit->text();
	QString desc = ui.rFeatureDescriptionTextEdit->toPlainText();

	if (!name.isEmpty()) {
		QString entry = QString("%1: %2").arg(name, desc);
		ui.rFeaturesListWidget->addItem(entry);
	}
}