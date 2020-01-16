#include "WeaponDelegate.h"

WeaponDelegate::WeaponDelegate(QWidget *parent)
	: QStyledItemDelegate(parent),
	wWdgt(new WeaponWidget(parent))
{
	wWdgt->setAttribute(Qt::WA_DontShowOnScreen, true);
	wWdgt->show();
}

WeaponDelegate::~WeaponDelegate()
{
	delete wWdgt;
}

void WeaponDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.data().canConvert<Weapon*>()) {
		Weapon* w = index.data().value<Weapon*>();

		if (option.state & QStyle::State_Selected)
			painter->fillRect(option.rect, option.palette.highlight());

		wWdgt->setWeapon(w);
		painter->save();
		painter->translate(option.rect.topLeft());
		painter->drawText(option.rect, w->toString());
		//wWdgt->render(painter, QPoint(), QRegion(), QWidget::DrawChildren);
		painter->restore();
	}
	else QStyledItemDelegate::paint(painter, option, index);
}

QSize WeaponDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.data().canConvert<Weapon*>())
		return WeaponEditor(0).sizeHint();
	return QStyledItemDelegate::sizeHint(option, index);
}

QWidget* WeaponDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.data().canConvert<Weapon*>()) {
		WeaponEditor* editor = new WeaponEditor(parent);
		connect(editor, &WeaponEditor::editingFinished,
			this, &WeaponDelegate::commitAndCloseEditor);
		return editor;
	}
	return QStyledItemDelegate::createEditor(parent, option, index);
}

void WeaponDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	if (index.data().canConvert<Weapon*>()) {
		Weapon* wpn = index.data().value<Weapon*>();
		WeaponEditor* wpnEditor = qobject_cast<WeaponEditor*>(editor);
		wpnEditor->setWeapon(wpn);
	}
	else {
		QStyledItemDelegate::setEditorData(editor, index);
	}
}

void WeaponDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	if (index.data().canConvert<Weapon*>()) {
		WeaponEditor* wpnEditor = qobject_cast<WeaponEditor*>(editor);
		model->setData(index, QVariant::fromValue(wpnEditor->getWeapon()));
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