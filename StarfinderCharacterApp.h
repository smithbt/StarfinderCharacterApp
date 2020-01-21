#pragma once

#include <QtWidgets/QMainWindow>
#include <QDataWidgetMapper>
#include <QFileDialog>
#include <QJsonDocument>
#include <QSortFilterProxyModel>
#include "ui_StarfinderCharacterApp.h"
#include "AbilityDelegate.h"
#include "AbilityWidget.h"
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
	Ui::StarfinderCharacterAppClass ui;
	QSortFilterProxyModel* wProxy;
	QSortFilterProxyModel* aProxy;
	Character* pc;
	QString fileName;
	QDataWidgetMapper* aMap;
	QDataWidgetMapper* wMap;
	QVector<AbilityWidget*> aWdgts;

	void readModelFromFile(QString path);


private slots:
	void customWeaponMenu(QPoint pos);
	void on_actionAdd_Weapon_triggered();
	void on_actionCharacter_New_triggered();
	bool on_actionCharacter_Open_triggered();
	bool on_actionCharacter_Save_triggered();
	bool on_actionCharacter_SaveAs_triggered();
	bool on_actionQuit_triggered();
};
