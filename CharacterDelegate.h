#pragma once

#include <QStyledItemDelegate>
#include "AbilityWidget.h"
#include "CharacterModel.h"
#include "ClassWidget.h"
#include "ResourceWidget.h"

class CharacterDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	CharacterDelegate(QWidget* parent = Q_NULLPTR);

	void setEditorData(QWidget* editor, const QModelIndex& index) const override;
	void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;

private slots:
	void commitAndCloseEditor();
};
