#pragma once

#include <QAbstractTableModel>
#include <QJsonArray>
#include "Ability.h"

class AbilityModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	AbilityModel(QObject *parent);
	~AbilityModel();

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	bool setAbility(Ability* a);

private:
	QVector<Ability*> abilities;
};
