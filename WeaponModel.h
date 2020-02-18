#pragma once

#include <QAbstractListModel>
#include <QStyledItemDelegate>
#include <QPainter>
#include "Character.h"
#include "WeaponWidget.h"
#include "Weapon.h"

class WeaponModel : public QAbstractListModel
{
	Q_OBJECT
	
public:
	WeaponModel(QObject *parent);

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

	bool insertRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;
	bool removeRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;

	void setWeaponList(QVector<Weapon*> list);

private:
	QVector<Weapon*> weapons;
};

class WeaponDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	WeaponDelegate(QWidget* parent = Q_NULLPTR);

	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
	QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
	QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
	void setEditorData(QWidget* editor, const QModelIndex& index) const override;
	void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;

private slots:
	void commitAndCloseEditor();
};
