#include "CreatorWizard.h"

CreatorWizard::CreatorWizard(QWidget *parent)
	: QWizard(parent),
	abilitySpinBoxes()
{
	ui.setupUi(this);
	ui.rAdjResetButton->setVisible(false);
	ui.rAbilityAdjListLabel->setVisible(false);

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
	// set up race
	Race* r = pc->getRace();
	r->setName(ui.rNameLineEdit->text());
	r->setSize(ui.rSizeComboBox->currentText());
	r->setType(ui.rTypeLineEdit->text());
	r->setHitPoints(ui.rHPSpinBox->value());
	for (int i = 0; i < ui.rFeaturesListWidget->count(); ++i) {
		r->addFeature(ui.rFeaturesListWidget->item(i)->data(Qt::UserRole).toString());
	}
	pc->setRace(r);

	// set up class
	pc->setClassName(ui.classLineEdit->text());
	pc->setKeyAbility(ui.cKeyAbilityComboBox->currentText());
	pc->setClassProperties({
		{ ClassInfo::BAB, QVariant(ui.babSpinBox->value()) },
		{ ClassInfo::Fortitude, QVariant(ui.fortitudeComboBox->currentText() == "Good") },
		{ ClassInfo::Reflex, QVariant(ui.reflexComboBox->currentText() == "Good") },
		{ ClassInfo::Will, QVariant(ui.willComboBox->currentText() == "Good") },
		{ ClassInfo::Stamina, QVariant(ui.staminaSpinBox->value()) },
		{ ClassInfo::HP, QVariant(ui.cHPSpinBox->value()) },
		{ ClassInfo::Skills, QVariant(ui.cSkillsSpinBox->value()) } });
	pc->setClassLevel(ui.levelSpinBox->value());

	// loop over ability scores
	for (QHash<QString, QSpinBox*>::Iterator i = abilitySpinBoxes.begin(); i != abilitySpinBoxes.end(); ++i) {
		pc->setAbilityProperty(i.key(), "base", i.value()->value());
	}

	// final details
	pc->setCharacterName(ui.characterNameLineEdit->text());

	QDialog::accept();
	emit characterReady(pc);
}

void CreatorWizard::on_rAdjButton_clicked()
{
	QString score = ui.rAdjScoreComboBox->currentText();
	int value = ui.rAdjSpinBox->value();
	if (value != 0 && abilitySpinBoxes.contains(score)) {
		QString text = ui.rAbilityAdjListLabel->text();
		if (!text.isEmpty())
			text += "; ";
		text += QString::asprintf("%+i %2", value).arg(score);
		ui.rAbilityAdjListLabel->setText(text);
		abilitySpinBoxes[score]->stepBy(value);
		ui.rAdjScoreComboBox->setCurrentIndex(0);
		ui.rAdjSpinBox->setValue(0);
		if (!ui.rAdjResetButton->isVisible())
			ui.rAdjResetButton->setVisible(true);
		if (!ui.rAbilityAdjListLabel->isVisible())
			ui.rAbilityAdjListLabel->setVisible(true);
	}
}

void CreatorWizard::on_rAdjResetButton_clicked()
{
	// readjust abilities
	QStringList adjs = ui.rAbilityAdjListLabel->text().split("; ");
	for (QString adj : adjs) {
		QStringList abilityAdj = adj.split(" ");
		if (adj.at(0) == '+')
			abilityAdj[0].remove(0, 1);
		int value = abilityAdj.at(0).toInt();
		abilitySpinBoxes[abilityAdj.at(1)]->stepBy(value * -1);
	}

	// Clear label and hide button
	ui.rAbilityAdjListLabel->setText("");
	ui.rAdjResetButton->setVisible(false);
	ui.rAbilityAdjListLabel->setVisible(false);
}

void CreatorWizard::on_rAddFeatureButton_clicked()
{
	QString name = ui.rFeatureNameLineEdit->text();
	QString desc = ui.rFeatureDescriptionTextEdit->toPlainText();

	if (!name.isEmpty()) {
		QListWidgetItem* entry = new QListWidgetItem(ui.rFeaturesListWidget);
		entry->setText(QString("%1: %2").arg(name, desc));
		entry->setData(Qt::UserRole, QString("%1|%2").arg(name, desc));
	}
	ui.rFeatureNameLineEdit->setText("");
	ui.rFeatureDescriptionTextEdit->setText("");
}

void CreatorWizard::on_rRemoveFeatureButton_clicked()
{
	ui.rFeaturesListWidget->removeItemWidget(ui.rFeaturesListWidget->currentItem());
}
