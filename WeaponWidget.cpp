#include "WeaponWidget.h"

WeaponWidget::WeaponWidget(QWidget* parent)
	: QFrame(parent),
	fireAction(new QAction(tr("Fire"), this)),
	reloadAction(new QAction(tr("Reload"), this)),
	editAction(new QAction(tr("Edit"), this)),
	deleteAction(new QAction(tr("Delete"), this))
{
	ui.setupUi(this);

	// Connect fire and reload Actions to button and output signals.
	connect(fireAction, &QAction::triggered, this, &WeaponWidget::weaponFired);
	connect(reloadAction, &QAction::triggered, this, &WeaponWidget::weaponReloaded);
	ui.fireButton->addActions({ fireAction, reloadAction });

	connect(editAction, &QAction::triggered, this, &WeaponWidget::editDialogRequested);
	// signal to remove from Character.
	ui.toolButton->addActions({ editAction, deleteAction });
	ui.toolButton->setDefaultAction(editAction);
}

WeaponWidget::~WeaponWidget()
{
	delete fireAction;
	delete reloadAction;
	delete editAction;
	delete deleteAction;
}

void WeaponWidget::setName(const QString name)
{
	ui.name_label->setText(name);
}

void WeaponWidget::setLevel(const int level)
{
	ui.level_label->setNum(level);
}

void WeaponWidget::setAttack(const QString attack)
{
	ui.atkLabel->setText(attack);
}

void WeaponWidget::setDamage(const QString damage)
{
	ui.dmgLabel->setText(damage);
}

void WeaponWidget::setCrit(const QString crit)
{
	ui.crit_label->setText(crit);
}

void WeaponWidget::setRange(const int range)
{
	ui.range_label->setText(QString("%1 ft.").arg(range));
}

void WeaponWidget::setCapacity(const int capacity)
{
	ui.capUseProgressBar->setMaximum(capacity);
}

void WeaponWidget::setUsage(const int usage)
{
	fireAction->setText(QString("Fire [%2]").arg(usage));
}

void WeaponWidget::setCurrentAmmo(const int current)
{
	ui.capUseProgressBar->setValue(current);
	if (current <= ui.capUseProgressBar->minimum())
		ui.fireButton->setDefaultAction(reloadAction);
	else if (ui.fireButton->defaultAction() != fireAction)
		ui.fireButton->setDefaultAction(fireAction);
}

void WeaponWidget::setSpecial(const QStringList special)
{
	ui.special_label->setText(special.join(", "));
}

int WeaponWidget::getCurrentAmmo() const
{
	return ui.capUseProgressBar->value();
}