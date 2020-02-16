#include "StarfinderCharacterApp.h"

StarfinderCharacterApp::StarfinderCharacterApp(QWidget* parent)
	: QMainWindow(parent),
	pc(new Character(this)),
	proxy(new QIdentityProxyModel(this)),
	wProxy(new WeaponProxyModel(this)),
	mapper(new QDataWidgetMapper(this))
{
	ui.setupUi(this);
	proxy->setSourceModel(pc->model);
	mapper->setModel(proxy);
	mapper->setOrientation(Qt::Vertical);
	mapper->addMapping(ui.charName_field, CharacterModel::CharacterName);
	mapper->addMapping(ui.staminaWidget, CharacterModel::Stamina, "resource");
	mapper->addMapping(ui.str_widget, CharacterModel::Strength, "ability");
	mapper->addMapping(ui.dex_widget, CharacterModel::Dexterity, "ability");
	mapper->addMapping(ui.con_widget, CharacterModel::Constitution, "ability");
	mapper->addMapping(ui.int_widget, CharacterModel::Intelligence, "ability");
	mapper->addMapping(ui.wis_widget, CharacterModel::Wisdom, "ability");
	mapper->addMapping(ui.cha_widget, CharacterModel::Charisma, "ability");
	mapper->addMapping(ui.fortLabel, CharacterModel::Fortitude, "text");
	mapper->addMapping(ui.refLabel, CharacterModel::Reflex, "text");
	mapper->addMapping(ui.willLabel, CharacterModel::Will, "text");
	connect(proxy, &QIdentityProxyModel::modelReset, mapper, &QDataWidgetMapper::toFirst);
	
	wProxy->setSourceModel(pc->wModel);
	wProxy->setCharacterModel(pc->model);
	ui.weaponList->setModel(wProxy);
	ui.weaponList->setItemDelegate(new WeaponDelegate(this));

	readModelFromFile(":/StarfinderCharacterApp/Resources/default.json");
	
}

StarfinderCharacterApp::~StarfinderCharacterApp()
{
	delete pc;
	delete proxy;
	delete wProxy;
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

	pc->read(loadDoc.object());
	loadFile.close();
	return true;
}

void StarfinderCharacterApp::on_actionAdd_Weapon_triggered() {
	WeaponDialog dialog(this);
	if (dialog.exec()) {
		Weapon* w = dialog.newWeapon();
		if (w)
			pc->addWeapon(w);
	}
}

void StarfinderCharacterApp::on_actionCharacter_New_triggered()
{
	readModelFromFile(":/StarfinderCharacterApp/Resources/default.json");
	CreatorWizard creator;
	if (creator.exec()) {

	}
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
	pc->write(pcObj);
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
