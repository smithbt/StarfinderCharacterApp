#pragma once

#include <QStyledItemDelegate>
#include <QPainter>
#include "WeaponDialog.h"
#include "WeaponModel.h"
#include "WeaponWidget.h"

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

