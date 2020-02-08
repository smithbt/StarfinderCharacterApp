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
	if (index.data(WeaponProxyModel::WeaponRole).canConvert<Weapon*>()) {
		Weapon* w = index.data(WeaponProxyModel::WeaponRole).value<Weapon*>();
		int aMod = index.data(WeaponProxyModel::AttackRole).toInt();
		int dMod = index.data(WeaponProxyModel::DamageRole).toInt();
		WeaponWidget ww;
		ww.setModifiers(aMod, dMod);
		ww.setWeapon(w);
		ww.setGeometry(option.rect);
		
		if (option.state & QStyle::State_Selected)
			painter->fillRect(option.rect, option.palette.highlight());
		else
			painter->fillRect(option.rect, option.palette.background());

		painter->save();
		painter->drawPixmap(option.rect, ww.grab());
		painter->restore();
	}
	else QStyledItemDelegate::paint(painter, option, index);
}

QSize WeaponDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.data(WeaponProxyModel::WeaponRole).canConvert<Weapon*>())
		return WeaponWidget(0).sizeHint();
	return QStyledItemDelegate::sizeHint(option, index);
}

QWidget* WeaponDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.data(WeaponProxyModel::WeaponRole).canConvert<Weapon*>()) {
		WeaponWidget* editor = new WeaponWidget(parent);
		connect(editor, &WeaponWidget::editingFinished,
			this, &WeaponDelegate::commitAndCloseEditor);
		return editor;
	}
	return QStyledItemDelegate::createEditor(parent, option, index);
}

void WeaponDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	if (index.data(WeaponProxyModel::WeaponRole).canConvert<Weapon*>()) {
		Weapon* wpn = index.data(WeaponProxyModel::WeaponRole).value<Weapon*>();
		int aMod = index.data(WeaponProxyModel::AttackRole).toInt();
		int dMod = index.data(WeaponProxyModel::DamageRole).toInt();
		WeaponWidget* wpnEditor = qobject_cast<WeaponWidget*>(editor);
		wpnEditor->setModifiers(aMod, dMod);
		wpnEditor->setWeapon(wpn);
	}
	else {
		QStyledItemDelegate::setEditorData(editor, index);
	}
}

void WeaponDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	if (index.data(WeaponProxyModel::WeaponRole).canConvert<Weapon*>()) {
		WeaponWidget* wpnEditor = qobject_cast<WeaponWidget*>(editor);
		model->setData(index, QVariant::fromValue(wpnEditor->getWeapon()));
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