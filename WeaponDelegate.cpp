#include "WeaponDelegate.h"

WeaponDelegate::WeaponDelegate(QWidget *parent)
	: QStyledItemDelegate(parent)
{
}

WeaponDelegate::~WeaponDelegate()
{
}

void WeaponDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.data().canConvert<Weapon>()) {
		Weapon wpn = index.data().value<Weapon>();

		if (option.state & QStyle::State_Selected)
			painter->fillRect(option.rect, option.palette.highlight());

		wpn.paint(painter, option.rect, option.palette,	Weapon::EditMode::ReadOnly);
	}
	else QStyledItemDelegate::paint(painter, option, index);
}

QSize WeaponDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.data().canConvert<Weapon>()) {
		Weapon wpn = index.data().value<Weapon>();
		return wpn.sizeHint();
	}
	return QStyledItemDelegate::sizeHint(option, index);
}

QWidget* WeaponDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.data().canConvert<Weapon>()) {
		WeaponEditor* editor = new WeaponEditor(parent);
		connect(editor, &WeaponEditor::editingFinished,
			this, &WeaponDelegate::commitAndCloseEditor);
		return editor;
	}
	return QStyledItemDelegate::createEditor(parent, option, index);
}

void WeaponDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	if (index.data().canConvert<Weapon>()) {
		Weapon wpn = index.data().value<Weapon>();
		WeaponEditor* wpnEditor = qobject_cast<WeaponEditor*>(editor);
		//set Data
	}
	else {
		QStyledItemDelegate::setEditorData(editor, index);
	}
}

void WeaponDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	if (index.data().canConvert<Weapon>()) {
		WeaponEditor* wpnEditor = qobject_cast<WeaponEditor*>(editor);
		model->setData(index, QVariant::fromValue(wpnEditor->starRating()));
	}
	else {
		QStyledItemDelegate::setModelData(editor, model, index);
	}
}

void WeaponDelegate::commitAndCloseEditor()
{
	WeaponEditor* editor = qobject_cast<WeaponEditor*>(sender());
	emit commitData(editor);
	emit closeEditor(editor);
}