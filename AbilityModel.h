#pragma once

#include <QAbstractListModel>
#include <QJsonArray>
#include "Ability.h"

class AbilityModel : public QAbstractListModel
{
	Q_OBJECT

public:
	AbilityModel(QObject *parent);
	~AbilityModel();

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

private:
	QVector<Ability*> abilities;
};
