#pragma once

#include <QWidget>
#include "ui_AbilityWidget.h"

class AbilityWidget : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(int score WRITE setScore STORED false)
	Q_PROPERTY(int modifier WRITE setModifier STORED false)
	Q_PROPERTY(int base READ base WRITE setBase USER true NOTIFY baseChanged)
	Q_PROPERTY(int upgrade READ upgrade WRITE setUpgrade USER true NOTIFY upgradeChanged)

public:
	AbilityWidget(QWidget* parent = Q_NULLPTR);
	~AbilityWidget();

	int base() const;
	int upgrade() const;

	void setLabelText(QString name);

signals:
	void baseChanged(int);
	void upgradeChanged(int);
	void editDone(AbilityWidget*);

public slots:
	void setScore(int score);
	void setModifier(int modifier);
	void setBase(int base);
	void setUpgrade(int upgrade);

private:
	Ui::AbilityWidget ui;
	int m_base;
	int m_upgrade;
};