#include "WeaponWidget.h"

WeaponWidget::WeaponWidget(QWidget* parent)
	: QWidget(parent),
	weapon(nullptr),
	fireAction(new QAction(tr("Fire"), this)),
	reloadAction(new QAction(tr("Reload"), this)),
	editAction(new QAction(tr("Edit"), this)),
	deleteAction(new QAction(tr("Delete"), this))
{
	ui.setupUi(this);

	connect(fireAction, &QAction::triggered, this, &WeaponWidget::shootWeapon);
	ui.fireButton->setDefaultAction(fireAction);
	connect(reloadAction, &QAction::triggered, this, &WeaponWidget::reloadWeapon);
	ui.fireButton->addAction(reloadAction);

	// connect to dialog popup
	connect(editAction, &QAction::triggered, this, &WeaponWidget::openWeaponDialog);
	// signal to remove from Character.
	ui.toolButton->addActions({ editAction, deleteAction });
}

WeaponWidget::~WeaponWidget()
{
	delete fireAction;
	delete reloadAction;
	delete editAction;
	delete deleteAction;
}

Weapon* WeaponWidget::getWeapon() const
{
	return weapon;
}

void WeaponWidget::setWeapon(Weapon* w)
{
	if (w != weapon) {
		if (weapon)
			disconnect(weapon->ammo, &Resource::currentChanged, ui.capUseProgressBar, &QProgressBar::setValue);
		weapon = w;
		if (weapon) {
			ui.name_label->setText(weapon->name);
			ui.level_label->setNum(weapon->level);
			QString atkString = QString::asprintf("%+i", weapon->attackMod);
			QString dmgString = QString::asprintf("%1%+i %3", weapon->damageMod).arg(weapon->damage->dice(), weapon->damage->type);
			ui.atkLabel->setText(atkString);
			ui.dmgLabel->setText(dmgString);
			ui.crit_label->setText(weapon->crit);
			ui.range_label->setText(QString("%1 ft.").arg(weapon->range));
			ui.capUseProgressBar->setMaximum(weapon->capacity());
			ui.capUseProgressBar->setValue(weapon->ammo->current());
			fireAction->setText(QString("Fire [%2]").arg(weapon->usage()));
			ui.special_label->setText(weapon->special.join(", "));
			connect(weapon->ammo, &Resource::currentChanged, ui.capUseProgressBar, &QProgressBar::setValue);
		}
		emit weaponChanged(weapon);
	}
}

void WeaponWidget::shootWeapon()
{
	weapon->ammo->adjustCurrent(-1);
	if (!weapon->ammo->current())
		ui.fireButton->setDefaultAction(reloadAction);
}

void WeaponWidget::reloadWeapon()
{
	weapon->ammo->setCurrent(weapon->capacity());
	if (ui.fireButton->defaultAction() != fireAction)
		ui.fireButton->setDefaultAction(fireAction);
}

void WeaponWidget::openWeaponDialog()
{
	WeaponDialog* dialog = new WeaponDialog(this, weapon);
	dialog->setAttribute(Qt::WA_DeleteOnClose);
	connect(dialog, &WeaponDialog::weaponReady, this, &WeaponWidget::setWeapon);
	dialog->open();
}
