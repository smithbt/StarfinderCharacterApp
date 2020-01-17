#pragma once

#include <QtWidgets/QMainWindow>
#include <QDataWidgetMapper>
#include <QFileDialog>
#include <QJsonDocument>
#include <QStandardItemModel>
#include "ui_StarfinderCharacterApp.h"
#include "AbilityDelegate.h"
#include "Character.h"
#include "CharacterDialog.h"
#include "Weapon.h"
#include "WeaponDelegate.h"
#include "WeaponDialog.h"

class StarfinderCharacterApp : public QMainWindow
{
	Q_OBJECT

public:
	StarfinderCharacterApp(QWidget *parent = Q_NULLPTR);

private:
	void updateModelViews();

	Ui::StarfinderCharacterAppClass ui;
	Character* pc;
	QString fileName;
	QVector<QDataWidgetMapper*> aMappers;
	QVector<AbilityWidget*> aWidgets;

private slots:
	void customWeaponMenu(QPoint pos);
	void on_actionAdd_Weapon_triggered();
	void on_actionCharacter_New_triggered();
	bool on_actionCharacter_Open_triggered();
	bool on_actionCharacter_Save_triggered();
	bool on_actionCharacter_SaveAs_triggered();
	bool on_actionQuit_triggered();
};
