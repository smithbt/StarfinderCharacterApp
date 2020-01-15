#include "StarfinderCharacterApp.h"

StarfinderCharacterApp::StarfinderCharacterApp(QWidget* parent)
	: QMainWindow(parent),
	pc(new Character(this))
{
	ui.setupUi(this);
	ui.weaponList->setModel(pc->getModel());
	ui.weaponList->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.weaponList,
		SIGNAL(customContextMenuRequested(QPoint)), 
		SLOT(customWeaponMenu(QPoint)));
}

void StarfinderCharacterApp::customWeaponMenu(QPoint pos) {

	QMenu* menu = new QMenu(this);
	menu->addAction(ui.actionAdd_Weapon);
	menu->popup(ui.weaponList->viewport()->mapToGlobal(pos));
}

void StarfinderCharacterApp::on_actionAdd_Weapon_triggered() {
	WeaponDialog dialog(this);
	if (dialog.exec()) {
		Weapon* w = dialog.getWeapon();
		pc->addWeapon(w);
	}
}

void StarfinderCharacterApp::on_actionNew_Character_triggered()
{
	CharacterDialog dialog(this);
	if (dialog.exec()) {
		dialog.saveToModel(pc);
	}
}

bool StarfinderCharacterApp::on_actionOpen_Character_triggered()
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

bool StarfinderCharacterApp::on_actionSave_Character_triggered()
{
	if (fileName.isEmpty()) {
		fileName = QFileDialog::getSaveFileName(this, tr("Save file"), "..", tr("JSON Files (*.json)"));
	}
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

bool StarfinderCharacterApp::on_actionQuit_triggered()
{
	QApplication::quit();
	return true;
}
