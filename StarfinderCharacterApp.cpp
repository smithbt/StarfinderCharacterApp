#include "StarfinderCharacterApp.h"

StarfinderCharacterApp::StarfinderCharacterApp(QWidget* parent)
	: QMainWindow(parent),
	pc(new Character(this)),
	proxy(new QSortFilterProxyModel(this)),
	wProxy(new QSortFilterProxyModel(this)),
	aProxy(new QSortFilterProxyModel(this)),
	wMap(new QDataWidgetMapper(this)),
	aMap(new QDataWidgetMapper(this)),
	mapper(new QDataWidgetMapper(this))
{
	readModelFromFile(":/StarfinderCharacterApp/Resources/default.json");

	ui.setupUi(this);
	proxy->setSourceModel(pc->model);
	mapper->setModel(proxy);
	mapper->setOrientation(Qt::Vertical);
	mapper->addMapping(ui.charName_field, CharacterModel::Name);
	mapper->toFirst();
	//connect(ui.charName_field, &QLineEdit::textChanged, this, [=](QString text) {
	//	pc->setProperty(CharacterModel::Name, QVariant(text)); });

	aProxy->setSourceModel(pc->aModel);
	ui.listView->setModel(aProxy);
	
	wProxy->setSourceModel(pc->wModel);
	ui.weaponList->setModel(wProxy);

	wMap->setModel(wProxy);
	wMap->setItemDelegate(new WeaponDelegate());
	wMap->addMapping(ui.weapon_widget, 0);
	connect(ui.weaponList->selectionModel(), &QItemSelectionModel::currentRowChanged,
		wMap, &QDataWidgetMapper::setCurrentModelIndex);
	connect(ui.weapon_widget, &WeaponWidget::weaponChanged, 
		[=]() {
			int aMod = pc->bab(), dMod = 0;
			switch (ui.weapon_widget->getWeapon()->type) {
			case Weapon::Type::Melee:
				aMod += pc->getAbility(Ability::Score::Strength)->modifier();
				dMod += pc->getAbility(Ability::Score::Strength)->modifier();
				break;
			case Weapon::Type::Ranged:
				aMod += pc->getAbility(Ability::Score::Dexterity)->modifier();
				break;
			}
			ui.weapon_widget->setModifiers(aMod, dMod); 
			ui.weapon_widget->updateLabels();
		});

	
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

	QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));

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
