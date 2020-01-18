#include "StarfinderCharacterApp.h"

StarfinderCharacterApp::StarfinderCharacterApp(QWidget* parent)
	: QMainWindow(parent),
	pc(new Character(this))
{
	ui.setupUi(this);
	ui.weaponList->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.weaponList,
		SIGNAL(customContextMenuRequested(QPoint)), 
		SLOT(customWeaponMenu(QPoint)));
	connect(pc->model, &QAbstractItemModel::dataChanged,
		this, &StarfinderCharacterApp::updateWeaponView);
	connect(pc->model, &QAbstractItemModel::modelReset,
		this, &StarfinderCharacterApp::updateAbilityScores);
}

void StarfinderCharacterApp::customWeaponMenu(QPoint pos) {

	QMenu* menu = new QMenu(this);
	menu->addAction(ui.actionAdd_Weapon);
	menu->popup(ui.weaponList->viewport()->mapToGlobal(pos));
}

void StarfinderCharacterApp::updateAbilityScores()
{
	ui.STR_widget->linkToModel(Ability::Score::Strength, pc);
	ui.DEX_widget->linkToModel(Ability::Score::Dexterity, pc);
	ui.CON_widget->linkToModel(Ability::Score::Constitution, pc);
	ui.INT_widget->linkToModel(Ability::Score::Intelligence, pc);
	ui.WIS_widget->linkToModel(Ability::Score::Wisdom, pc);
	ui.CHA_widget->linkToModel(Ability::Score::Charisma, pc);
}

void StarfinderCharacterApp::updateWeaponView()
{
	ui.weaponList->setModel(pc->model);
	ui.weaponList->setModelColumn(1);
	ui.weaponList->setRootIndex(pc->model->listTypeRoot(CharacterNode::Type::Weapon));
	ui.weaponList->setItemDelegate(new WeaponDelegate());
}

void StarfinderCharacterApp::on_actionAdd_Weapon_triggered() {
	WeaponDialog dialog(this);
	if (dialog.exec()) {
		QVariant w = dialog.newWeapon();
		pc->addWeapon(w);
	}
}

void StarfinderCharacterApp::on_actionCharacter_New_triggered()
{
	CharacterDialog dialog(this);
	if (dialog.exec()) {
		pc = dialog.newCharacter();
		fileName.clear();
	}
}

bool StarfinderCharacterApp::on_actionCharacter_Open_triggered()
{
	fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "..", tr("JSON Files (*.json)"));
	QFile loadFile(fileName);

	if (!loadFile.open(QIODevice::ReadOnly)) {
		qWarning("Could not open file.");
		return false;
	}

	QByteArray loadData = loadFile.readAll();

	QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));

	pc->read(loadDoc.object());
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
