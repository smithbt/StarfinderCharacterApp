#pragma once

#include <QObject>
#include "CharacterModel.h"
#include "WeaponModel.h"
#include "ClassModel.h"

class Character : public QObject
{
	Q_OBJECT

public: 
	Character(QObject* parent = nullptr);
	~Character();

	int stamina();

	void setProperty(CharacterModel::RowIndex row, QVariant& value, int role = Qt::EditRole);
	QVariant getProperty(CharacterModel::RowIndex row);

	void setClassLevelPair(QString name, int level);

	void addWeapon(Weapon* w);

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;

	CharacterModel* model;
	WeaponModel* wModel;
	ClassModel* cModel;

private:
	int bab();
	int fortitude();
	int reflex();
	int will();
};

