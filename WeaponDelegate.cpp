#include "WeaponDelegate.h"

WeaponDelegate::WeaponDelegate(QWidget *parent)
	: QStyledItemDelegate(parent)
{
}

WeaponDelegate::~WeaponDelegate()
{
}

//void WeaponDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
//{
//	if (index.data(Qt::UserRole).canConvert<Weapon*>()) {
//		Weapon* w;
//		if (index.data(Qt::UserRole).canConvert<MeleeWeapon*>())
//			w = index.data(Qt::UserRole).value<MeleeWeapon*>();
//		else if (index.data(Qt::UserRole).canConvert<RangedWeapon*>())
//			w = index.data(Qt::UserRole).value<RangedWeapon*>();
//		else
//			w = index.data(Qt::UserRole).value<Weapon*>();
//		
//		if (option.state & QStyle::State_Selected)
//			painter->fillRect(option.rect, option.palette.highlight());
//
//		painter->save();
//		painter->translate(option.rect.topLeft());
//		painter->drawText(option.rect, w->toString());
//		painter->restore();
//	}
//	else QStyledItemDelegate::paint(painter, option, index);
//}
//
//QSize WeaponDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
//{
//	if (index.data(Qt::UserRole).canConvert<RangedWeapon*>())
//		return WeaponWidget(0).sizeHint();
//	return QStyledItemDelegate::sizeHint(option, index);
//}
//
//QWidget* WeaponDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
//{
//	if (index.data(Qt::UserRole).canConvert<RangedWeapon*>()) {
//		WeaponWidget* editor = new WeaponWidget(parent);
//		connect(editor, &WeaponEditor::editingFinished,
//			this, &WeaponDelegate::commitAndCloseEditor);
//		return editor;
//	}
//	return QStyledItemDelegate::createEditor(parent, option, index);
//}

void WeaponDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	if (index.data(Qt::UserRole).canConvert<Weapon*>()) {
		Weapon* wpn = index.data(Qt::UserRole).value<Weapon*>();
		WeaponWidget* wpnEditor = qobject_cast<WeaponWidget*>(editor);
		wpnEditor->setWeapon(wpn);
	}
	else {
		QStyledItemDelegate::setEditorData(editor, index);
	}
}

void WeaponDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	if (index.data(Qt::UserRole).canConvert<RangedWeapon*>()) {
		WeaponWidget* wpnEditor = qobject_cast<WeaponWidget*>(editor);
		model->setData(index, QVariant::fromValue(wpnEditor->getWeapon()),Qt::UserRole);
	}
	else {
		QStyledItemDelegate::setModelData(editor, model, index);
	}
}

void WeaponDelegate::commitAndCloseEditor()
{
	WeaponWidget* editor = qobject_cast<WeaponWidget*>(sender());
	emit commitData(editor);
	emit closeEditor(editor);
}