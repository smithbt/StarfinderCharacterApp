#pragma once

#include <QAbstractListModel>
#include "Character.h"

class WeaponModel : public QAbstractListModel
{
	Q_OBJECT
	
public:
	enum roles {
		NameRole = Qt::UserRole + 1,
		LevelRole,
		BulkRole,
		PriceRole,
		AttackRole,
		DamageRole,
		CritRole,
		RangeRole,
		TypeRole,
		CurrentAmmoRole,
		CapacityRole,
		UsageRole,
		SpecialRole
	};

	WeaponModel(QObject *parent);

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

	bool insertRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;
	bool removeRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;

	void setCharacter(Character* pc);

private:
	Character* m_pc;
};