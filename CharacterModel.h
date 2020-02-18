#pragma once

#include <QAbstractTableModel>
#include <QVector>
#include "Character.h"

class CharacterModel : public QAbstractTableModel
{
	Q_OBJECT

private:
	QVector<Character*> pcs;
	int columns;

public:

	CharacterModel(QObject *parent = nullptr);
	~CharacterModel();

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

	bool insertRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;
	bool removeRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;

	bool insertCharacter(Character* pc);
	Character* getCharacter(int row);
};

