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
	if (index.data(Qt::UserRole).canConvert<QVector<Ability*>>())
		return AbilityWidget(0).sizeHint();
	return QStyledItemDelegate::sizeHint(option, index);
}

void AbilityDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	if (index.data(Qt::UserRole).canConvert<QVector<Ability*>>()) {
		QVector<Ability*> a = index.data(Qt::UserRole).value<QVector<Ability*>>();
		AbilityWidget* aW = qobject_cast<AbilityWidget*>(editor);
		aW->setAbilityList(a);
	}
	else {
		QStyledItemDelegate::setEditorData(editor, index);
	}
}

void AbilityDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	if (index.data(Qt::UserRole).canConvert<QVector<Ability*>>()) {
		AbilityWidget* aW = qobject_cast<AbilityWidget*>(editor);
		model->setData(index, QVariant::fromValue(aW->getAbilityList()));
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
