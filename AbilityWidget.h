#pragma once

#include <QWidget>
#include "ui_AbilityWidget.h"
#include "Ability.h"

class AbilityWidget : public QWidget
{
	Q_OBJECT

public:
	AbilityWidget(QWidget *parent = Q_NULLPTR);
	~AbilityWidget();

	void setAbility(Ability* as);
	Ability* getAbility();

private:
	Ui::AbilityWidget ui;
	Ability* a;
};
