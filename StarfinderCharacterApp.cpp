#include "StarfinderCharacterApp.h"

StarfinderCharacterApp::StarfinderCharacterApp(QWidget* parent)
	: QMainWindow(parent),
	wModel(new WeaponModel(this)),
	pcModel(new CharacterModel(this)),
	mapper(new QDataWidgetMapper(this))
{
	ui.setupUi(this);
	mapper->setModel(pcModel);
	mapper->addMapping(ui.charName_field, Character::CharacterName);
	mapper->addMapping(ui.staminaWidget, Character::Stamina, "resource");
	mapper->addMapping(ui.str_widget, Character::Strength, "ability");
	mapper->addMapping(ui.dex_widget, Character::Dexterity, "ability");
	mapper->addMapping(ui.con_widget, Character::Constitution, "ability");
	mapper->addMapping(ui.int_widget, Character::Intelligence, "ability");
	mapper->addMapping(ui.wis_widget, Character::Wisdom, "ability");
	mapper->addMapping(ui.cha_widget, Character::Charisma, "ability");
	mapper->addMapping(ui.fortLabel, Character::Fortitude, "text");
	mapper->addMapping(ui.refLabel, Character::Reflex, "text");
	mapper->addMapping(ui.willLabel, Character::Will, "text");
	connect(mapper, &QDataWidgetMapper::currentIndexChanged, wModel, [=](int index) {
		wModel->setCharacter(pcModel->index(index, Character::Weapons).data(Qt::UserRole).value<Character*>()); });
	ui.weaponList->setModel(wModel);
	ui.weaponList->setItemDelegate(new WeaponDelegate(this));

	connect(pcModel, &CharacterModel::modelReset, mapper, &QDataWidgetMapper::toFirst);

	readModelFromFile(":/StarfinderCharacterApp/Resources/default.json");
	
}

StarfinderCharacterApp::~StarfinderCharacterApp()
{
	delete pcModel;
	delete wModel;
	delete mapper;
}

bool StarfinderCharacterApp::readModelFromFile(QString path)
{
	QFile loadFile(path);

	if (!loadFile.open(QIODevice::ReadOnly)) {
		qWarning("Error opening file.");
		return false;
	}

	QByteArray loadData = loadFile.readAll();

	QJsonParseError *error = new QJsonParseError();
	QJsonDocument loadDoc(QJsonDocument::fromJson(loadData, error));
	qDebug() << error->errorString();
	
	Character* pc = new Character(pcModel);
	pc->read(loadDoc.object());
	pcModel->insertRow(0);
	pcModel->setData(pcModel->index(0, 0), QVariant::fromValue(pc), Qt::UserRole);
	mapper->setCurrentIndex(0);
	loadFile.close();
	return true;
}

void StarfinderCharacterApp::on_actionAdd_Weapon_triggered() {
	WeaponDialog dialog(this);
	if (dialog.exec()) {
		Weapon* w = dialog.newWeapon();
		if (w) {
			QModelIndex weaponNode = pcModel->index(mapper->currentIndex(), Character::Weapons);
			QVector<Weapon*> ws = weaponNode.data().value<QVector<Weapon*>>();
			ws.append(w);
			pcModel->setData(weaponNode, QVariant::fromValue(ws));
		}
	}
}

void StarfinderCharacterApp::on_actionCharacter_New_triggered()
{
	readModelFromFile(":/StarfinderCharacterApp/Resources/default.json");
	CreatorWizard* creator = new CreatorWizard(this);
	creator->open();
	fileName.clear();
}

bool StarfinderCharacterApp::on_actionCharacter_Open_triggered()
{
	fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "..", tr("JSON Files (*.json)"));
	return readModelFromFile(fileName);
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
	pcModel->index(mapper->currentIndex(), 0).data(Qt::UserRole).value<Character*>()->write(pcObj);
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
