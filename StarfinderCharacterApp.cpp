#include "StarfinderCharacterApp.h"

StarfinderCharacterApp::StarfinderCharacterApp(QWidget* parent)
	: QMainWindow(parent),
	pc(new Character(this)),
	proxy(new QSortFilterProxyModel(this)),
	wProxy(new WeaponProxyModel(this)),
	aMap(new QDataWidgetMapper(this)),
	mapper(new QDataWidgetMapper(this))
{
	ui.setupUi(this);
	proxy->setSourceModel(pc->model);
	mapper->setModel(proxy);
	mapper->setOrientation(Qt::Vertical);
	mapper->addMapping(ui.charName_field, CharacterModel::Name);
	mapper->addMapping(ui.staminaWidget, CharacterModel::Stamina, "resource");
	connect(proxy, &QSortFilterProxyModel::modelReset, mapper, &QDataWidgetMapper::toFirst);

	aMap->setModel(pc->aModel);
	aMap->setOrientation(Qt::Vertical);
	aMap->addMapping(ui.str_widget, Ability::Strength, "ability");
	aMap->addMapping(ui.dex_widget, Ability::Dexterity, "ability");
	aMap->addMapping(ui.con_widget, Ability::Constitution, "ability");
	aMap->addMapping(ui.int_widget, Ability::Intelligence, "ability");
	aMap->addMapping(ui.wis_widget, Ability::Wisdom, "ability");
	aMap->addMapping(ui.cha_widget, Ability::Charisma, "ability");
	connect(pc->aModel, &QSortFilterProxyModel::modelReset, aMap, &QDataWidgetMapper::toFirst);
	
	wProxy->setSourceModel(pc->wModel);
	wProxy->setAbilityModel(pc->aModel);
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
	delete aMap;
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
	CharacterDialog dialog(this);
	if (dialog.exec()) {
		readModelFromFile(":/StarfinderCharacterApp/Resources/default.json");

		dialog.newCharacter(pc);
		fileName.clear();
	}
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
