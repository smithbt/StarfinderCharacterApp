#include "StarfinderCharacterApp.h"

StarfinderCharacterApp::StarfinderCharacterApp(QWidget* parent)
	: QMainWindow(parent),
	pc(new Character(this))
{
	ui.setupUi(this);
	connect(ui.weaponList,
		SIGNAL(customContextMenuRequested(QPoint)), 
		SLOT(customWeaponMenu(QPoint)));

	asWdgts.insert(Ability::Score::Strength, ui.STR_widget);
	asWdgts.insert(Ability::Score::Dexterity, ui.DEX_widget);
	asWdgts.insert(Ability::Score::Constitution, ui.CON_widget);
	asWdgts.insert(Ability::Score::Intelligence, ui.INT_widget);
	asWdgts.insert(Ability::Score::Wisdom, ui.WIS_widget);
	asWdgts.insert(Ability::Score::Charisma, ui.CHA_widget);

	updateModelViews();

}

void StarfinderCharacterApp::customWeaponMenu(QPoint pos) {

	QMenu* menu = new QMenu(this);
	menu->addAction(ui.actionAdd_Weapon);
	menu->popup(ui.weaponList->viewport()->mapToGlobal(pos));
}

void StarfinderCharacterApp::updateModelViews()
{
	ui.weaponList->setModel(pc->getModel());
	ui.weaponList->setModelColumn(1);
	ui.weaponList->setRootIndex(pc->getModel()->listTypeRoot(CharacterNode::Type::Weapon));
	ui.weaponList->setContextMenuPolicy(Qt::CustomContextMenu);
	ui.weaponList->setItemDelegate(new WeaponDelegate());

	QMetaEnum aEnum = QMetaEnum::fromType<Ability::Score>();
	for (int i = 0; i < aEnum.keyCount(); ++i) {
		Ability::Score score = static_cast<Ability::Score>(aEnum.value(i));
		Ability* a = pc->getAbility(score);
		asWdgts.value(score)->setAbility(a);
	}
}

void StarfinderCharacterApp::on_actionAdd_Weapon_triggered() {
	WeaponDialog dialog(this);
	if (dialog.exec()) {
		Weapon* w = dialog.getWeapon();
		pc->addWeapon(w);
	}
}

void StarfinderCharacterApp::on_actionCharacter_New_triggered()
{
	CharacterDialog dialog(this);
	if (dialog.exec()) {
		dialog.saveToModel(pc);
	}
	updateModelViews();
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
	updateModelViews();
	return true;
}

bool StarfinderCharacterApp::on_actionCharacter_Save_triggered()
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

bool StarfinderCharacterApp::on_actionCharacter_SaveAs_triggered()
{
	fileName.clear();
	on_actionCharacter_Save_triggered();
	return false;
}

bool StarfinderCharacterApp::on_actionQuit_triggered()
{
	QApplication::quit();
	return true;
}
