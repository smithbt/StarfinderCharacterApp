#pragma once

#include <QStyledItemDelegate>
#include "Ability.h"
#include "AbilityWidget.h"

class AbilityDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	AbilityDelegate(QObject *parent = Q_NULLPTR);
	~AbilityDelegate();

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setEditorData(QWidget* editor, const QModelIndex& index) const override;
    void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;

private slots:
    void commitAndCloseEditor();

};