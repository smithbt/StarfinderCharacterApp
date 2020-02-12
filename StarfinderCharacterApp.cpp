#include "StarfinderCharacterApp.h"

StarfinderCharacterApp::StarfinderCharacterApp(QWidget* parent)
	: QMainWindow(parent),
	pc(new Character(this)),
	proxy(new QSortFilterProxyModel(this)),
	wProxy(new WeaponProxyModel(this)),
	mapper(new QDataWidgetMapper(this))
{
	ui.setupUi(this);
	proxy->setSourceModel(pc->model);
	mapper->setModel(proxy);
	mapper->setOrientation(Qt::Vertical);
	mapper->addMapping(ui.charName_field, CharacterModel::Name);
	mapper->addMapping(ui.staminaWidget, CharacterModel::Stamina, "resource");
	mapper->addMapping(ui.str_widget, CharacterModel::Strength, "ability");
	mapper->addMapping(ui.dex_widget, CharacterModel::Dexterity, "ability");
	mapper->addMapping(ui.con_widget, CharacterModel::Constitution, "ability");
	mapper->addMapping(ui.int_widget, CharacterModel::Intelligence, "ability");
	mapper->addMapping(ui.wis_widget, CharacterModel::Wisdom, "ability");
	mapper->addMapping(ui.cha_widget, CharacterModel::Charisma, "ability");
	connect(proxy, &QSortFilterProxyModel::modelReset, mapper, &QDataWidgetMapper::toFirst);
	
	wProxy->setSourceModel(pc->wModel);
	wProxy->setCharacterModel(pc->model);
	ui.weaponList->setModel(wProxy);
	ui.weaponList->setItemDelegate(new WeaponDelegate(this));
	connect(pc, &Character::babChanged, wProxy, &WeaponProxyModel::setBAB);

	connect(pc, &Character::fortitudeChanged, ui.fortLabel, QOverload<int>::of(&QLabel::setNum));
	connect(pc, &Character::reflexChanged, ui.refLabel, QOverload<int>::of(&QLabel::setNum));
	connect(pc, &Character::willChanged, ui.willLabel, QOverload<int>::of(&QLabel::setNum));

	readModelFromFile(":/StarfinderCharacterApp/Resources/default.json");
	
}

StarfinderCharacterApp::~StarfinderCharacterApp()
{
	delete pc;
	delete proxy;
	delete wProxy;
	delete mapper;
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
	qWarning("New Character functions not implemented.");
	readModelFromFile(":/StarfinderCharacterApp/Resources/default.json");
	fileName.clear();
}

void StarfinderCharacterApp::readModelFromFile(QString path)
{
	QFile loadFile(path);

	if (!loadFile.open(QIODevice::ReadOnly)) {
		qWarning("Error opening file.");
	}

	QByteArray loadData = loadFile.readAll();

	QJsonParseError *error = new QJsonParseError();
	QJsonDocument loadDoc(QJsonDocument::fromJson(loadData, error));
	qDebug() << error->errorString();

	pc->read(loadDoc.object());
	loadFile.close();
}

bool StarfinderCharacterApp::on_actionCharacter_Open_triggered()
{
	fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "..", tr("JSON Files (*.json)"));
	readModelFromFile(fileName);
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
