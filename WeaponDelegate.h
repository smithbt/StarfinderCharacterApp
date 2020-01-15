#pragma once

#include <QPainter>
#include <QStyledItemDelegate>
#include "Weapon.h"

class WeaponDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	WeaponDelegate(QWidget *parent = Q_NULLPTR);
	~WeaponDelegate();

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;

private slots:
    void commitAndCloseEditor();
};