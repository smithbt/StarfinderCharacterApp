#include "CharacterDelegate.h"

CharacterDelegate::CharacterDelegate(QWidget *parent)
	: QStyledItemDelegate(parent)
{
}

void CharacterDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	if (index.column() == CharacterModel::Strength ||
		index.column() == CharacterModel::Dexterity ||
		index.column() == CharacterModel::Constitution ||
		index.column() == CharacterModel::Intelligence ||
		index.column() == CharacterModel::Wisdom ||
		index.column() == CharacterModel::Charisma) 
	{
		AbilityWidget* aWdgt = qobject_cast<AbilityWidget*>(editor);
		aWdgt->setScore(index.data(CharacterModel::Ability_ScoreRole).toInt());
		aWdgt->setModifier(index.data(CharacterModel::Ability_ModifierRole).toInt());
		aWdgt->setBase(index.data(CharacterModel::Ability_BaseRole).toInt());
		aWdgt->setUpgrade(index.data(CharacterModel::Ability_UpgradeRole).toInt());
		connect(aWdgt, &AbilityWidget::editDone, this, &CharacterDelegate::commitData);
	}
	else
		QStyledItemDelegate::setEditorData(editor, index);
}

void CharacterDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	if (index.column() == CharacterModel::Strength ||
		index.column() == CharacterModel::Dexterity ||
		index.column() == CharacterModel::Constitution ||
		index.column() == CharacterModel::Intelligence ||
		index.column() == CharacterModel::Wisdom ||
		index.column() == CharacterModel::Charisma)
	{
		AbilityWidget* aWdgt = qobject_cast<AbilityWidget*>(editor);
		model->setItemData(index, {
			{CharacterModel::Ability_BaseRole, aWdgt->base()},
			{CharacterModel::Ability_UpgradeRole, aWdgt->upgrade()} });
	}
	else
		QStyledItemDelegate::setModelData(editor, model, index);
}

void CharacterDelegate::commitAndCloseEditor()
{
	QWidget* editor = qobject_cast<QWidget*>(sender());
	emit commitData(editor);
	emit closeEditor(editor);
}