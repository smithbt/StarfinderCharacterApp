#pragma once

#include <QFrame>
#include "ui_WeaponWidget.h"

class WeaponWidget : public QFrame
{
	Q_OBJECT

public:
	WeaponWidget(QWidget *parent = Q_NULLPTR);
	~WeaponWidget();

	void setName(const QString name);
	void setLevel(const int level);
	void setAttack(const QString attack);
	void setDamage(const QString damage);
	void setCrit(const QString crit);
	void setRange(const int range);
	void setCapacity(const int capacity);
	void setUsage(const int usage);
	void setCurrentAmmo(const int current);
	void setSpecial(const QStringList special);

	int getCurrentAmmo() const;

signals:
	void weaponFired();
	void weaponReloaded();
	void editDialogRequested();

private:
	Ui::WeaponWidget ui;
	QAction* fireAction;
	QAction* reloadAction;
	QAction* editAction;
	QAction* deleteAction;
};
