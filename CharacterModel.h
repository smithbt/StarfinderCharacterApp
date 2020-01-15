#pragma once

#include <QAbstractItemModel>
#include <QJsonObject>
#include <QList>
#include <QString>
#include <QVariant>
#include "CharacterNode.h"

class CharacterModel : public QAbstractItemModel
{
	Q_OBJECT

public:

	CharacterModel(QObject *parent = nullptr);
	~CharacterModel();

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
	QModelIndex parent(const QModelIndex& index) const override;
	QModelIndex listTypeRoot(CharacterNode::Type t) const;
	int typeRow(CharacterNode::Type type) const;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
	bool setHeaderData(int section, Qt::Orientation orientation, const QVariant& value, int role = Qt::EditRole) override;

	bool insertRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;
	bool removeRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;

private:
	void setupModel(CharacterNode* parent);
	CharacterNode* getNode(const QModelIndex& index) const;

	CharacterNode* rootNode;
};

