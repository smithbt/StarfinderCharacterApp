#pragma once

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QJsonDocument>
#include "ui_StarfinderCharacterApp.h"
#include "Character.h"
#include "CharacterDialog.h"
#include "Weapon.h"
#include "WeaponDialog.h"

class StarfinderCharacterApp : public QMainWindow
{
	Q_OBJECT

public:
	StarfinderCharacterApp(QWidget *parent = Q_NULLPTR);

private:
	Ui::StarfinderCharacterAppClass ui;
	Character pc;
	QString fileName;

private slots:
	void customWeaponMenu(QPoint pos);
	void on_actionAdd_Weapon_triggered();
	void on_actionNew_Character_triggered();
	bool on_actionOpen_Character_triggered();
	bool on_actionSave_Character_triggered();
};
