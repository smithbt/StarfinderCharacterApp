#include "CharacterDelegate.h"

CharacterDelegate::CharacterDelegate(QWidget *parent)
	: QStyledItemDelegate(parent)
{
}

void CharacterDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	const int column = index.column();
	if (column == CharacterModel::ClassData) {
		ClassWidget* cWdgt = qobject_cast<ClassWidget*>(editor);
		QString className = index.data(CharacterModel::Class_NameRole).toString();
		cWdgt->setClassName(className);
		int level = index.data(CharacterModel::Class_LevelRole).toInt();
		cWdgt->setLevel(level);
	}
	else if (column == CharacterModel::Stamina ||
		column == CharacterModel::HitPoints) 
	{
		ResourceWidget* rWdgt = qobject_cast<ResourceWidget*>(editor);
		int current = index.data(CharacterModel::Resource_CurrentRole).toInt();
		rWdgt->setCurrent(current);
		int max = index.data(CharacterModel::Resource_MaxRole).toInt();
		rWdgt->setMax(max);
		int step = index.data(CharacterModel::Resource_StepRole).toInt();
		rWdgt->setStep(step);
	}
	else if (column == CharacterModel::Strength ||
		column == CharacterModel::Dexterity ||
		column == CharacterModel::Constitution ||
		column == CharacterModel::Intelligence ||
		column == CharacterModel::Wisdom ||
		column == CharacterModel::Charisma) 
	{
		AbilityWidget* aWdgt = qobject_cast<AbilityWidget*>(editor);
		int score = index.data(CharacterModel::Ability_ScoreRole).toInt();
		aWdgt->setScore(score);
		int mod = index.data(CharacterModel::Ability_ModifierRole).toInt();
		aWdgt->setModifier(mod);
		int base = index.data(CharacterModel::Ability_BaseRole).toInt();
		aWdgt->setBase(base);
		int upgrade = index.data(CharacterModel::Ability_UpgradeRole).toInt();
		aWdgt->setUpgrade(upgrade);
		connect(aWdgt, &AbilityWidget::editDone, this, &CharacterDelegate::commitData);
	}
	else
		QStyledItemDelegate::setEditorData(editor, index);
}

void CharacterDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	const int column = index.column();
	if (column == CharacterModel::ClassData) {
		ClassWidget* cWdgt = qobject_cast<ClassWidget*>(editor);
		int level = cWdgt->getLevel();
		model->setData(index, level, CharacterModel::Class_LevelRole);
	}
	else if (column == CharacterModel::Stamina ||
		column == CharacterModel::HitPoints) 
	{
		ResourceWidget* rWdgt = qobject_cast<ResourceWidget*>(editor);
		int current = rWdgt->getCurrentValue();
		model->setData(index, current, CharacterModel::Resource_CurrentRole);
	}
	else if (column == CharacterModel::Strength ||
		column == CharacterModel::Dexterity ||
		column == CharacterModel::Constitution ||
		column == CharacterModel::Intelligence ||
		column == CharacterModel::Wisdom ||
		column == CharacterModel::Charisma)
	{
		AbilityWidget* aWdgt = qobject_cast<AbilityWidget*>(editor);
		int base = aWdgt->base();
		int upgrade = aWdgt->upgrade();
		model->setItemData(index, {
			{CharacterModel::Ability_BaseRole, base},
			{CharacterModel::Ability_UpgradeRole, upgrade} });
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