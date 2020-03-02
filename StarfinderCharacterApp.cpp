#include "StarfinderCharacterApp.h"

StarfinderCharacterApp::StarfinderCharacterApp(QWidget* parent)
	: QMainWindow(parent),
	wModel(new WeaponModel(this)),
	pcModel(new CharacterModel(this)),
	mapper(new QDataWidgetMapper(this))
{
	ui.setupUi(this);
	ui.str_widget->setLabelText("Strength");
	ui.dex_widget->setLabelText("Dexterity");
	ui.con_widget->setLabelText("Constitution");
	ui.int_widget->setLabelText("Intelligence");
	ui.wis_widget->setLabelText("Wisdom");
	ui.cha_widget->setLabelText("Charisma");

	mapper->setModel(pcModel);
	mapper->setItemDelegate(new CharacterDelegate());
	mapper->addMapping(ui.rWidget, CharacterModel::RaceData, "race");
	mapper->addMapping(ui.classWidget, CharacterModel::ClassData);
	mapper->addMapping(ui.charName_field, CharacterModel::CharacterName);
	mapper->addMapping(ui.staminaWidget, CharacterModel::Stamina);
	mapper->addMapping(ui.hpWidget, CharacterModel::HitPoints);
	mapper->addMapping(ui.resolveWidget, CharacterModel::Resolve);
	mapper->addMapping(ui.str_widget, CharacterModel::Strength);
	mapper->addMapping(ui.dex_widget, CharacterModel::Dexterity);
	mapper->addMapping(ui.con_widget, CharacterModel::Constitution);
	mapper->addMapping(ui.int_widget, CharacterModel::Intelligence);
	mapper->addMapping(ui.wis_widget, CharacterModel::Wisdom);
	mapper->addMapping(ui.cha_widget, CharacterModel::Charisma);
	mapper->addMapping(ui.fortLabel, CharacterModel::Fortitude, "text");
	mapper->addMapping(ui.refLabel, CharacterModel::Reflex, "text");
	mapper->addMapping(ui.willLabel, CharacterModel::Will, "text");
	connect(mapper, &QDataWidgetMapper::currentIndexChanged, wModel, [=](int index) {
		wModel->setCharacter(pcModel->index(index, CharacterModel::FullObject).data().value<Character*>()); });
	ui.weaponList->setModel(wModel);
	ui.weaponList->setItemDelegate(new WeaponDelegate(this));
	
	connect(pcModel, &CharacterModel::modelReset, mapper, &QDataWidgetMapper::toFirst);
	
}

StarfinderCharacterApp::~StarfinderCharacterApp()
{
	delete pcModel;
	delete wModel;
	delete mapper;
}

void StarfinderCharacterApp::on_actionAdd_Weapon_triggered() {
	WeaponDialog* dialog = new WeaponDialog(this);
	dialog->setAttribute(Qt::WA_DeleteOnClose);
	connect(dialog, &WeaponDialog::weaponReady, [this](Weapon* weapon) {
		weapon->ammo->setCurrent(weapon->capacity());
		weapon->setParent(pcModel);
		wModel->insertRow(0);
		wModel->setData(wModel->index(0), QVariant::fromValue(weapon));
		});
	dialog->setModal(true);
	dialog->open();
}

void StarfinderCharacterApp::on_actionCharacter_New_triggered()
{
	CreatorWizard* creator = new CreatorWizard(this);
	connect(creator, &CreatorWizard::characterReady, [=](Character* pc) {
		pc->setParent(pcModel);
		pcModel->insertRow(0);
		pcModel->setData(pcModel->index(0, CharacterModel::FullObject), QVariant::fromValue(pc));
		mapper->setCurrentIndex(0);
		});
	creator->open();
	fileName.clear();
}

bool StarfinderCharacterApp::on_actionCharacter_Open_triggered()
{
	fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "..", tr("JSON Files (*.json)"));
	QFile loadFile(fileName);

	if (!loadFile.open(QIODevice::ReadOnly)) {
		qWarning("Error opening file.");
		return false;
	}

	QByteArray loadData = loadFile.readAll();

	QJsonParseError* error = new QJsonParseError();
	QJsonDocument loadDoc(QJsonDocument::fromJson(loadData, error));
	qDebug() << error->errorString();

	Character* pc = new Character(pcModel);
	pc->read(loadDoc.object());
	pcModel->insertRow(0);
	pcModel->setData(pcModel->index(0, CharacterModel::FullObject), QVariant::fromValue(pc));
	mapper->setCurrentIndex(0);
	loadFile.close();
	return true;
}

bool StarfinderCharacterApp::on_actionCharacter_Save_triggered()
{
	if (fileName.isEmpty())
		fileName = QFileDialog::getSaveFileName(this, tr("Save file"), "..", tr("JSON Files (*.json)"));
	QFile saveFile(fileName);

	if (!saveFile.open(QIODevice::WriteOnly)) {
		qWarning("Could not open file.");
		return false;
	}

	QJsonObject pcObj;
	pcModel->index(mapper->currentIndex(), CharacterModel::FullObject).data().value<Character*>()->write(pcObj);
	QJsonDocument saveDoc(pcObj);
	saveFile.write(saveDoc.toJson());
	saveFile.close();
	return true;
}

bool StarfinderCharacterApp::on_actionCharacter_SaveAs_triggered()
{
	fileName.clear();
	return on_actionCharacter_Save_triggered();
}

bool StarfinderCharacterApp::on_actionQuit_triggered()
{
	QApplication::quit();
	return true;
}
