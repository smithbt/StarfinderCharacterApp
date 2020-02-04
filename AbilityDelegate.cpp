#include "AbilityDelegate.h"

AbilityDelegate::AbilityDelegate(QObject *parent)
	: QStyledItemDelegate(parent)
{
}

AbilityDelegate::~AbilityDelegate()
{
}

QSize AbilityDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.data().canConvert<Ability*>())
		return AbilityWidget(0).sizeHint();
	return QStyledItemDelegate::sizeHint(option, index);
}

void AbilityDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	if (index.data().canConvert<Ability*>()) {
		Ability* a = index.data().value<Ability*>();
		AbilityWidget* aW = qobject_cast<AbilityWidget*>(editor);
		aW->setAbility(a);
	}
	else {
		QStyledItemDelegate::setEditorData(editor, index);
	}
}

void AbilityDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	if (index.data().canConvert<Ability*>()) {
		AbilityWidget* aW = qobject_cast<AbilityWidget*>(editor);
		model->setData(index, QVariant::fromValue(aW->getAbility()));
	}
	else {
		QStyledItemDelegate::setModelData(editor, model, index);
	}
}

void AbilityDelegate::commitAndCloseEditor()
{
	AbilityWidget* editor = qobject_cast<AbilityWidget*>(sender());
	emit commitData(editor);
	emit closeEditor(editor);
}
