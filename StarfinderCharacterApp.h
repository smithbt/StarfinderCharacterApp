#pragma once

#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <QDataWidgetMapper>
#include <QFileDialog>
#include <QJsonDocument>
#include <QIdentityProxyModel>
#include "ui_StarfinderCharacterApp.h"
#include "Character.h"
#include "Weapon.h"
#include "WeaponDelegate.h"
#include "WeaponDialog.h"
#include "WeaponProxyModel.h"

class StarfinderCharacterApp : public QMainWindow
{
	Q_OBJECT

public:
	StarfinderCharacterApp(QWidget *parent = Q_NULLPTR);
	~StarfinderCharacterApp();

private:
	Ui::StarfinderCharacterAppClass ui;
	QIdentityProxyModel* proxy;
	WeaponProxyModel* wProxy;
	Character* pc;
	QString fileName;
	QDataWidgetMapper* mapper;

	bool readModelFromFile(QString path);

private slots:
	void on_actionAdd_Weapon_triggered();
	void on_actionCharacter_New_triggered();
	bool on_actionCharacter_Open_triggered();
	bool on_actionCharacter_Save_triggered();
	bool on_actionCharacter_SaveAs_triggered();
	bool on_actionQuit_triggered();
};
