#include "StarfinderCharacterApp.h"

StarfinderCharacterApp::StarfinderCharacterApp(QWidget* parent)
	: QMainWindow(parent),
	pc(new Character(this)),
	wProxy(new QSortFilterProxyModel(this)),
	aProxy(new QSortFilterProxyModel(this)),
	wMap(new QDataWidgetMapper(this)),
	aMap(new QDataWidgetMapper(this))
{
	readModelFromFile(":/StarfinderCharacterApp/Resources/default.json");

	ui.setupUi(this);

	QMetaEnum aEnum = QMetaEnum::fromType<Ability::Score>();

	wProxy->setSourceModel(pc->getWeaponModel());
	ui.weaponList->setModel(wProxy);
	ui.weaponList->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.weaponList, SIGNAL(customContextMenuRequested(QPoint)), SLOT(customWeaponMenu(QPoint)));

	wMap->setModel(wProxy);
	wMap->setItemDelegate(new WeaponDelegate());
	wMap->addMapping(ui.weapon_widget, 0);
	connect(ui.weaponList->selectionModel(), &QItemSelectionModel::currentRowChanged,
		wMap, &QDataWidgetMapper::setCurrentModelIndex);
	connect(ui.weapon_widget, &WeaponWidget::weaponChanged, 
		[=]() {
			int aMod = 0, dMod = 0;
			switch (ui.weapon_widget->getWeapon()->type) {
			case Weapon::Type::Melee:
				aMod = pc->getAbility(Ability::Score::Strength)->modifier();
				dMod = pc->getAbility(Ability::Score::Strength)->modifier();
				break;
			case Weapon::Type::Ranged:
				aMod = pc->getAbility(Ability::Score::Dexterity)->modifier();
				break;
			}
			// TODO: replace hardcoded BAB with value from PC.
			ui.weapon_widget->setModifiers(aMod, dMod); 
			ui.weapon_widget->updateLabels();
		});

	aProxy->setSourceModel(pc->model);
	aMap->setModel(aProxy);
	aMap->setItemDelegate(new AbilityDelegate());
	aMap->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
	aMap->addMapping(ui.abilityList_widget, 0);
	aMap->setCurrentIndex(CharacterModel::Key::Abilities);


	connect(pc->model, &CharacterModel::modelReset, this,
		[=]() {
			wProxy->setSourceModel(pc->getWeaponModel());

			wMap->addMapping(ui.weapon_widget, 0);

			aMap->addMapping(ui.abilityList_widget, 0);
			aMap->setCurrentIndex(CharacterModel::Key::Abilities);
		});

}

void StarfinderCharacterApp::customWeaponMenu(QPoint pos) {

	QMenu* menu = new QMenu(this);
	menu->addAction(ui.actionAdd_Weapon);
	menu->popup(ui.weaponList->viewport()->mapToGlobal(pos));
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
