#include "CharacterDelegate.h"

CharacterDelegate::CharacterDelegate(QWidget *parent)
	: QStyledItemDelegate(parent)
{
}

void CharacterDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	if (index.data().canConvert<ClassInfo*>()) {
		ClassWidget* cWdgt = qobject_cast<ClassWidget*>(editor);
		QString className = index.data(CharacterModel::Class_NameRole).toString();
		cWdgt->setClassName(className);
		int level = index.data(CharacterModel::Class_LevelRole).toInt();
		cWdgt->setLevel(level);
	}
	else if (index.data().canConvert<Resource*>()) {
		ResourceWidget* rWdgt = qobject_cast<ResourceWidget*>(editor);
		int current = index.data(CharacterModel::Resource_CurrentRole).toInt();
		rWdgt->setCurrent(current);
		int max = index.data(CharacterModel::Resource_MaxRole).toInt();
		rWdgt->setMax(max);
		int step = index.data(CharacterModel::Resource_StepRole).toInt();
		rWdgt->setStep(step);
	}
	else if (index.data().canConvert<Ability*>()) {
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
	if (index.data().canConvert<ClassInfo*>()) {
		ClassWidget* cWdgt = qobject_cast<ClassWidget*>(editor);
		int level = cWdgt->getLevel();
		model->setData(index, level, CharacterModel::Class_LevelRole);
	}
	else if (index.data().canConvert<Resource*>()) {
		ResourceWidget* rWdgt = qobject_cast<ResourceWidget*>(editor);
		int current = rWdgt->getCurrentValue();
		model->setData(index, current, CharacterModel::Resource_CurrentRole);
	}
	else if (index.data().canConvert<Ability*>()) {
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