#pragma once

#include <QAbstractListModel>
#include "Weapon.h"

class WeaponModel : public QAbstractListModel
{
	Q_OBJECT

public:
	WeaponModel(QObject *parent);
	~WeaponModel();

	void read(const QJsonArray& wArray);
	void write(QJsonArray& wArray) const;

	QVariant data(const QModelIndex& index, int role = Qt::UserRole) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::UserRole) override;

	bool insertRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;
	bool removeRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;

private:
	QVector<Weapon*> weapons;
};
