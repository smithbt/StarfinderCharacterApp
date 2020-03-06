#pragma once

#include <QDialog>
#include "ui_WeaponDialog.h"

class WeaponDialog : public QDialog
{
	Q_OBJECT

public:
	WeaponDialog(QWidget *parent = Q_NULLPTR);
	~WeaponDialog();

	void setName(const QString name);
	void setLevel(const int level);
	void setBulk(const double bulk);
	void setPrice(const int price);
	void setType(const QString type);
	void setDamage(const QString damage);
	void setCrit(const QString crit);
	void setRange(const int range);
	void setCapacity(const int capacity);
	void setUsage(const int usage);
	void setSpecial(const QStringList special);

	QString getName() const;
	int getLevel() const;
	double getBulk() const;
	int getPrice() const;
	QString getType() const;
	QVariantList getDamage() const;
	QString getCrit() const;
	int getRange() const;
	int getCapacity() const;
	int getUsage() const;
	QStringList getSpecial() const;

private:
	Ui::WeaponDialog ui;
	QRegularExpression damageRegEx;

	void updateFields(const QString wt);
};
