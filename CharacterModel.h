#pragma once

#include <QAbstractListModel>
#include <QJsonDocument>
#include <QMap>
#include <QString>
#include <QVariant>
#include "Ability.h"
#include "ClassType.h"
#include "Weapon.h"
#include "WeaponModel.h"

class CharacterModel : public QAbstractListModel
{
	Q_OBJECT

public:
	enum Key : int {
		Name = 0,
		Abilities,
		Weapons,
		Classes
	};
	Q_ENUM(Key)

	CharacterModel(QObject *parent = nullptr);
	~CharacterModel();

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;

	QVariant data(const QModelIndex& index, int role = Qt::UserRole) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::UserRole) override;

	bool insertRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;
	bool removeRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;

private:
	QMap<int, QVariant> map;
};

