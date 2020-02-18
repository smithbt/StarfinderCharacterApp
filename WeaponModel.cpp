#include "WeaponModel.h"

WeaponModel::WeaponModel(QObject* parent)
	: QAbstractListModel(parent),
	weapons()
{
}

QVariant WeaponModel::data(const QModelIndex& index, int role) const
{
	const int idx = index.row();
	if (!index.isValid()) // invalid index
		return QVariant();

	if (idx >= weapons.size() || idx < 0) // out of range
		return QVariant();

	if (role == Qt::UserRole)
		return QVariant::fromValue(weapons.at(idx));

	const Weapon* w = weapons.at(idx);
	if (role == Qt::DisplayRole) {
		QString attack = QString::asprintf("%+i", w->attackMod);
		QString damage = w->damage->dice() + QString::asprintf("%+i ", w->damageMod) + w->damage->type;
		QString listing = QString("%1: %2 / %3").arg(w->name).arg(attack).arg(damage);
		return listing;
	}

	return QVariant();
}

Qt::ItemFlags WeaponModel::flags(const QModelIndex& index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	return Qt::ItemIsEditable | QAbstractListModel::flags(index);
}

int WeaponModel::rowCount(const QModelIndex& parent) const
{
	return weapons.size();
}

bool WeaponModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (index.isValid() && role == Qt::EditRole && value.canConvert<Weapon*>()) {
		weapons.replace(index.row(), value.value<Weapon*>());
		emit dataChanged(index, index, { Qt::DisplayRole, Qt::EditRole });
		return true;
	}
	return false;
}

bool WeaponModel::insertRows(int position, int rows, const QModelIndex& parent)
{
	Q_UNUSED(parent);
	beginInsertRows(QModelIndex(), position, position + rows - 1);

	for (int i = position; i < (position + rows); ++i) {
		weapons.insert(i, nullptr);
	}

	endInsertRows();
	return true;
}

bool WeaponModel::removeRows(int position, int rows, const QModelIndex& parent)
{
	Q_UNUSED(parent);
	beginRemoveRows(QModelIndex(), position, position + rows - 1);

	for (int i = position; i < (position + rows); ++i) {
		weapons.removeAt(i);
	}

	endRemoveRows();
	return true;
}

void WeaponModel::setWeaponList(QVector<Weapon*> list)
{
	if (list != weapons) {
		beginResetModel();
		weapons = list;
		endResetModel();
	}
}

WeaponDelegate::WeaponDelegate(QWidget* parent)
	: QStyledItemDelegate(parent)
{
}

void WeaponDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.data(Qt::UserRole).canConvert<Weapon*>()) {
		Weapon* w = index.data(Qt::UserRole).value<Weapon*>();
		WeaponWidget ww;
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
	if (index.data(Qt::UserRole).canConvert<Weapon*>())
		return WeaponWidget(0).sizeHint();
	return QStyledItemDelegate::sizeHint(option, index);
}

QWidget* WeaponDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.data(Qt::UserRole).canConvert<Weapon*>()) {
		WeaponWidget* editor = new WeaponWidget(parent);
		connect(editor, &WeaponWidget::editingFinished,
			this, &WeaponDelegate::commitAndCloseEditor);
		return editor;
	}
	return QStyledItemDelegate::createEditor(parent, option, index);
}

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
	if (index.data(Qt::UserRole).canConvert<Weapon*>()) {
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