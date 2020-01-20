#include "StarfinderCharacterApp.h"

StarfinderCharacterApp::StarfinderCharacterApp(QWidget* parent)
	: QMainWindow(parent),
	pc(new Character(this)),
	proxy(new QSortFilterProxyModel(this)),
	aMaps(QVector<QDataWidgetMapper*>(6, new QDataWidgetMapper(this)))
{
	ui.setupUi(this);
	proxy->setSourceModel(pc->model);
	ui.weaponList->setModel(proxy);
	connect(ui.weaponList,
		SIGNAL(customContextMenuRequested(QPoint)), 
		SLOT(customWeaponMenu(QPoint)));
	connect(pc->model, &CharacterModel::modelReset, ui.weaponList, [=]() {
			ui.weaponList->reset();
			ui.weaponList->setRootIndex(proxy->mapFromSource(
				pc->model->listTypeRoot(CharacterNode::Type::Weapon)));
		});
	QModelIndex wRoot = pc->model->listTypeRoot(CharacterNode::Type::Weapon);
	ui.weaponList->setRootIndex(proxy->mapFromSource(wRoot));
	ui.weaponList->setModelColumn(1);
	ui.weaponList->setContextMenuPolicy(Qt::CustomContextMenu);

	QDataWidgetMapper* wMap = new QDataWidgetMapper(this);
	wMap->setModel(proxy);
	wMap->setRootIndex(proxy->mapFromSource(wRoot));
	wMap->setItemDelegate(new WeaponDelegate());
	wMap->addMapping(ui.weapon_widget, 1);
	connect(pc->model, &CharacterModel::modelReset, wMap, [=]() {
		wMap->setRootIndex(proxy->mapFromSource(
			pc->model->listTypeRoot(CharacterNode::Type::Weapon)));
		});
	connect(ui.weaponList->selectionModel(), &QItemSelectionModel::currentRowChanged,
		wMap, &QDataWidgetMapper::setCurrentModelIndex);
	connect(wMap, &QDataWidgetMapper::currentIndexChanged, ui.weapon_widget,
		[=]() {
			Ability* a = pc->getAbility(ui.weapon_widget->getWeapon()->attackScore);
			ui.weapon_widget->setAttackModifiers(a->modifier(), 0); // TODO: replace hardcoded BAB with value from PC.
		});

	aWdgts.insert(static_cast<int>(Ability::Score::Strength), ui.STR_widget);
	aWdgts.insert(static_cast<int>(Ability::Score::Dexterity), ui.DEX_widget);
	aWdgts.insert(static_cast<int>(Ability::Score::Constitution), ui.CON_widget);
	aWdgts.insert(static_cast<int>(Ability::Score::Intelligence), ui.INT_widget);
	aWdgts.insert(static_cast<int>(Ability::Score::Wisdom), ui.WIS_widget);
	aWdgts.insert(static_cast<int>(Ability::Score::Charisma), ui.CHA_widget);
	QMetaEnum aEnum = QMetaEnum::fromType<Ability::Score>();
	QModelIndex aRoot = pc->model->listTypeRoot(CharacterNode::Type::Ability);
	for (int i = 0; i < aEnum.keyCount(); ++i) {
		connect(pc->model, &CharacterModel::modelReset,
			aMaps.at(i), [=]() {
				QModelIndex aRoot = pc->model->listTypeRoot(CharacterNode::Type::Ability);
				aMaps.at(i)->setRootIndex(proxy->mapFromSource(aRoot));
				aMaps.at(i)->setCurrentIndex(1);
			});
		aMaps.at(i)->setModel(proxy);
		aMaps.at(i)->setRootIndex(proxy->mapFromSource(aRoot));
		aMaps.at(i)->setOrientation(Qt::Vertical);
		aMaps.at(i)->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
		aMaps.at(i)->setItemDelegate(new AbilityDelegate());
		QModelIndex modelIdx = pc->getAbilityIndex(static_cast<Ability::Score>(aEnum.value(i)));
		aMaps.at(i)->addMapping(aWdgts.at(i), proxy->mapFromSource(modelIdx).row());
		aMaps.at(i)->setCurrentIndex(1);
	}

}

void StarfinderCharacterApp::customWeaponMenu(QPoint pos) {

	QMenu* menu = new QMenu(this);
	menu->addAction(ui.actionAdd_Weapon);
	menu->popup(ui.weaponList->viewport()->mapToGlobal(pos));
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
