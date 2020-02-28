#include "WeaponWidget.h"

WeaponWidget::WeaponWidget(QWidget* parent)
	: QWidget(parent),
	weapon(nullptr)
{
	ui.setupUi(this);

	connect(ui.fire_pushButton, &QPushButton::clicked, this, [=]() { weapon->ammo->adjustCurrent(-1); });
	connect(ui.reload_pushButton, &QPushButton::clicked, this, [=]() { weapon->ammo->setCurrent(weapon->capacity()); });
	connect(weapon->ammo, &Resource::currentChanged, ui.currAmmoLabel, QOverload<int>::of(&QLabel::setNum));
	connect(this, &WeaponWidget::weaponChanged, &WeaponWidget::updateLabels);
}

WeaponWidget::~WeaponWidget()
{
}

Weapon* WeaponWidget::getWeapon() const
{
	return weapon;
}

void WeaponWidget::setWeapon(Weapon* w)
{
	weapon = w;
	emit weaponChanged(weapon);
}

void WeaponWidget::updateLabels()
{
	ui.name_label->setText(weapon->name);
	ui.level_label->setNum(weapon->level);
	ui.attack_label->setText(QString::asprintf("%+i", weapon->attackMod));
	QString dmgString = QString::asprintf("%1%+i %3", weapon->damageMod).arg(weapon->damage->dice()).arg(weapon->damage->type);
	ui.damagelabel->setText(dmgString);
	ui.crit_label->setText(weapon->crit);
	ui.range_label->setText(QString("%1 ft.").arg(weapon->range));
	ui.capUseLabel->setText(QString("%1 [Usage %2]").arg(weapon->capacity()).arg(weapon->usage()));
	ui.price_label->setNum(weapon->price);
	ui.bulk_label->setNum(weapon->bulk);
	ui.special_label->setText(weapon->special.join(", "));
}

void WeaponWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
}

void WeaponWidget::mouseMoveEvent(QMouseEvent* event)
{
	QWidget::mouseMoveEvent(event);
}

void WeaponWidget::mouseReleaseEvent(QMouseEvent* event)
{
	emit editingFinished();
	QWidget::mouseReleaseEvent(event);
}