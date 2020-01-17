#include "StarfinderCharacterApp.h"

StarfinderCharacterApp::StarfinderCharacterApp(QWidget* parent)
	: QMainWindow(parent),
	pc(new Character(this)),
	aMappers(QVector<QDataWidgetMapper*>(6, new QDataWidgetMapper(this)))
{
	ui.setupUi(this);
	connect(ui.weaponList,
		SIGNAL(customContextMenuRequested(QPoint)), 
		SLOT(customWeaponMenu(QPoint)));
	connect(pc->getModel(), &QAbstractItemModel::modelReset,
		ui.weaponList, &QListView::reset);

	
	QMetaEnum aE = QMetaEnum::fromType<Ability::Score>();
	aWidgets.insert(static_cast<int>(Ability::Score::Strength), ui.STR_widget);
	aWidgets.insert(static_cast<int>(Ability::Score::Dexterity), ui.DEX_widget);
	aWidgets.insert(static_cast<int>(Ability::Score::Constitution), ui.CON_widget);
	aWidgets.insert(static_cast<int>(Ability::Score::Intelligence), ui.INT_widget);
	aWidgets.insert(static_cast<int>(Ability::Score::Wisdom), ui.WIS_widget);
	aWidgets.insert(static_cast<int>(Ability::Score::Charisma), ui.CHA_widget);
	for (int aIndex = 0; aIndex < aE.keyCount(); ++aIndex) {
		connect(pc->getModel(), &QAbstractItemModel::modelReset,
			aMappers[aIndex], &QDataWidgetMapper::revert);
		aMappers[aIndex]->setModel(pc->getModel());
		aMappers[aIndex]->setCurrentIndex(pc->getAbilityIndex(static_cast<Ability::Score>(aE.value(aIndex))).row());
		aMappers[aIndex]->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
		aMappers[aIndex]->setItemDelegate(new AbilityDelegate());
		aMappers[aIndex]->addMapping(aWidgets[aIndex], 1);
	}

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
	//updateModelViews();
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
