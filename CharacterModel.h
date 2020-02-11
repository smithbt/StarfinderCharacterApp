#pragma once

#include <QAbstractListModel>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMetaEnum>
#include <QString>
#include <QVector>
#include <QVariant>

class CharacterModel : public QAbstractListModel
{
	Q_OBJECT

public:
	enum Key : int {
		Name = 0
	};
	Q_ENUM(Key)

	CharacterModel(QObject *parent = nullptr);
	~CharacterModel();

	void read(const QJsonObject& json);
	void write(QJsonObject& json) const;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

	bool insertRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;
	bool removeRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;

private:
	QVector<QVariant> map;
};

