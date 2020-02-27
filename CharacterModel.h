#pragma once

#include <QAbstractTableModel>
#include <QVector>
#include "Character.h"

class CharacterModel : public QAbstractTableModel
{
	Q_OBJECT

private:
	QVector<Character*> pcs;
	const static int columns = 18;

	QString abilityNameFromColumn(int column) const;

public:
	enum ColumnIndex : int {
		FullObject = 0,
		RaceData,
		ClassData,
		
		// Strings
		CharacterName,

		// Ints
		BAB,
		Fortitude, Reflex, Will,

		// Resources
		Stamina,
		HitPoints,
		Resolve,

		// Ability Scores
		Strength, Dexterity, Constitution, Intelligence, Wisdom, Charisma,

		// models, lists
		Weapons
	};

	enum {
		Class_NameRole = Qt::UserRole + 1,
		Class_LevelRole,

		Resource_CurrentRole,
		Resource_MaxRole,
		Resource_StepRole,

		Ability_BaseRole,
		Ability_UpgradeRole,
		Ability_ScoreRole,
		Ability_ModifierRole
	};

	CharacterModel(QObject *parent = nullptr);
	~CharacterModel();

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

	bool insertRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;
	bool removeRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;
};

