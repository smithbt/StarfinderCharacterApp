#pragma once

#include <QAbstractListModel>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMetaEnum>
#include <QString>
#include <QVector>
#include <QVariant>
#include "Ability.h"
#include "Resource.h"

class CharacterModel : public QAbstractListModel
{
	Q_OBJECT

public:
	enum RowIndex : int {
		// Strings
		Name = 0,

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
	const static int rows = 12;

	CharacterModel(QObject *parent = nullptr);
	~CharacterModel();

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

private:
	QVector<QVariant> map;
};

