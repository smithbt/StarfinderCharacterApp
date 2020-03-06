#pragma once

#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <QDataWidgetMapper>
#include <QFileDialog>
#include <QJsonDocument>
#include "ui_StarfinderCharacterApp.h"
#include "CharacterDelegate.h"
#include "CharacterModel.h"
#include "CreatorWizard.h"
#include "WeaponDelegate.h"
#include "WeaponDialog.h"
#include "WeaponModel.h"

class StarfinderCharacterApp : public QMainWindow
{
	Q_OBJECT

public:
	StarfinderCharacterApp(QWidget *parent = Q_NULLPTR);
	~StarfinderCharacterApp();

private slots:
	void on_actionAdd_Weapon_triggered();
	void on_actionCharacter_New_triggered();
	bool on_actionCharacter_Open_triggered();
	bool on_actionCharacter_Save_triggered();
	bool on_actionCharacter_SaveAs_triggered();
	bool on_actionQuit_triggered();

private:
	Ui::StarfinderCharacterAppClass ui;
	WeaponModel* wModel;
	CharacterModel* pcModel;
	QString fileName;
	QDataWidgetMapper* mapper;

};
