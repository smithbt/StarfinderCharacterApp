#pragma once

#include <QAbstractListModel>
#include <QJsonObject>
#include <QMetaEnum>
#include <QString>
#include <QVector>
#include <QVariant>
#include "Ability.h"
#include "Resource.h"

class CharacterModel : public QAbstractListModel
{
	Q_OBJECT

private:
	QVector<QVariant> map;
	const static int rows = 12;

public:
	enum RowIndex : int {
		// Strings
		CharacterName = 0,

		// Ints
		BAB,
		Fortitude,
		Reflex,
		Will,

		// Resources
		Stamina,

		// Ability Scores
		Strength,
		Dexterity,
		Constitution,
		Intelligence,
		Wisdom,
		Charisma
	};
	Q_ENUM(RowIndex)

	enum {
		Resource_CurrentRole = Qt::UserRole + 1,
		Resource_MaxRole,
		Ability_TypeRole,
		Ability_BaseRole,
		Ability_UpgradeRole
	};

	CharacterModel(QObject *parent = nullptr);
	~CharacterModel();

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

};

