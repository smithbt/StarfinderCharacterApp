#include "WeaponDelegate.h"

WeaponDelegate::WeaponDelegate(QWidget* parent)
	: QStyledItemDelegate(parent)
{
}

void WeaponDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.data(Qt::UserRole).canConvert<Weapon*>()) {
		Weapon* w = index.data().value<Weapon*>();
		WeaponWidget ww;
		ww.setName(index.data(WeaponModel::NameRole).toString());
		ww.setLevel(index.data(WeaponModel::LevelRole).toInt());
		ww.setAttack(index.data(WeaponModel::AttackRole).toString());
		ww.setDamage(index.data(WeaponModel::DamageRole).toString());
		ww.setCrit(index.data(WeaponModel::CritRole).toString());
		ww.setRange(index.data(WeaponModel::RangeRole).toInt());
		ww.setCapacity(index.data(WeaponModel::CapacityRole).toInt());
		ww.setUsage(index.data(WeaponModel::UsageRole).toInt());
		ww.setCurrentAmmo(index.data(WeaponModel::CurrentAmmoRole).toInt());
		ww.setSpecial(index.data(WeaponModel::SpecialRole).toStringList());
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
	if (index.data(Qt::UserRole).canConvert<Weapon*>())
		return WeaponWidget(0).sizeHint();
	return QStyledItemDelegate::sizeHint(option, index);
}

QWidget* WeaponDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.data(Qt::UserRole).canConvert<Weapon*>()) {
		WeaponWidget* editor = new WeaponWidget(parent);
		return editor;
	}
	return QStyledItemDelegate::createEditor(parent, option, index);
}

void WeaponDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	if (index.data(Qt::UserRole).canConvert<Weapon*>()) {
		WeaponWidget* ww = qobject_cast<WeaponWidget*>(editor);
		ww->setName(index.data(WeaponModel::NameRole).toString());
		ww->setLevel(index.data(WeaponModel::LevelRole).toInt());
		ww->setAttack(index.data(WeaponModel::AttackRole).toString());
		ww->setDamage(index.data(WeaponModel::DamageRole).toString());
		ww->setCrit(index.data(WeaponModel::CritRole).toString());
		ww->setRange(index.data(WeaponModel::RangeRole).toInt());
		ww->setCapacity(index.data(WeaponModel::CapacityRole).toInt());
		ww->setUsage(index.data(WeaponModel::UsageRole).toInt());
		ww->setCurrentAmmo(index.data(WeaponModel::CurrentAmmoRole).toInt());
		ww->setSpecial(index.data(WeaponModel::SpecialRole).toStringList());
		connect(ww, &WeaponWidget::weaponFired, index.data(Qt::UserRole).value<Weapon*>(), &Weapon::fire);
		connect(ww, &WeaponWidget::weaponReloaded, index.data(Qt::UserRole).value<Weapon*>(), &Weapon::reload);
		connect(index.data(Qt::UserRole).value<Weapon*>(), &Weapon::currentAmmoChanged, ww, &WeaponWidget::setCurrentAmmo);
	}
	else {
		QStyledItemDelegate::setEditorData(editor, index);
	}
}

void WeaponDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	if (index.data(Qt::UserRole).canConvert<Weapon*>()) {
		WeaponDialog* dialog = qobject_cast<WeaponDialog*>(editor);
		//model->setItemData(index, {
		//	{WeaponModel::NameRole, dialog->getName()},
		//	{WeaponModel::LevelRole, dialog->getLevel()},
		//	{WeaponModel::DamageRole, dialog->getDamage()},
		//	{WeaponModel::BulkRole, dialog->getBulk()},
		//	{WeaponModel::PriceRole, dialog->getPrice()},
		//	{WeaponModel::CritRole, dialog->getCrit()},
		//	{WeaponModel::RangeRole, dialog->getRange()},
		//	{WeaponModel::TypeRole, dialog->getType()},
		//	{WeaponModel::CurrentAmmoRole, dialog->getCapacity()},
		//	{WeaponModel::CapacityRole, dialog->getCapacity()},
		//	{WeaponModel::UsageRole, dialog->getUsage()},
		//	{WeaponModel::SpecialRole, dialog->getSpecial()} });
	}
	else {
		QStyledItemDelegate::setModelData(editor, model, index);
	}
}

void WeaponDelegate::commitAndCloseEditor()
{
	WeaponDialog* editor = qobject_cast<WeaponDialog*>(sender());
	emit commitData(editor);
	emit closeEditor(editor);
}