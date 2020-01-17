#include "AbilityDelegate.h"

AbilityDelegate::AbilityDelegate(QObject *parent)
	: QStyledItemDelegate(parent)
{
}

AbilityDelegate::~AbilityDelegate()
{
}

void AbilityDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.data(Qt::UserRole).canConvert<Ability*>()) {
		Ability* a = index.data(Qt::UserRole).value<Ability*>();

		if (option.state & QStyle::State_Selected)
			painter->fillRect(option.rect, option.palette.highlight());
		qDebug() << a->toString();

		painter->save();
		painter->translate(option.rect.topLeft());
		painter->drawText(option.rect, a->toString());
		painter->restore();
	}
	else QStyledItemDelegate::paint(painter, option, index);
}

QSize AbilityDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.data(Qt::UserRole).canConvert<Ability*>())
		return AbilityWidget(0).sizeHint();
	return QStyledItemDelegate::sizeHint(option, index);
}

QWidget* AbilityDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.data(Qt::UserRole).canConvert<Ability*>()) {
		//AbilityWidget* editor = new AbilityWidget(parent);
		//connect(editor, &AbilityWidget::editingFinished,
		//	this, &AbilityDelegate::commitAndCloseEditor);
		//return editor;
	}
	return QStyledItemDelegate::createEditor(parent, option, index);
}

void AbilityDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	if (index.data(Qt::UserRole).canConvert<Ability*>()) {
		Ability* a = index.data(Qt::UserRole).value<Ability*>();
		AbilityWidget* aW = qobject_cast<AbilityWidget*>(editor);
		aW->setAbility(a);
	}
	else {
		QStyledItemDelegate::setEditorData(editor, index);
	}
}

void AbilityDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	if (index.data(Qt::UserRole).canConvert<Ability*>()) {
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
