#pragma once

#include <QWidget>
#include "ui_AbilityWidget.h"
#include "Ability.h"

class AbilityWidget : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(Ability* ability READ getAbility WRITE setAbility NOTIFY abilityChanged)

public:
	AbilityWidget(QWidget *parent = Q_NULLPTR);
	~AbilityWidget();

	void setAbility(Ability* a);
	Ability* getAbility() const;

signals:
	void abilityChanged(Ability*);

private:
	Ui::AbilityWidget ui;
	Ability* ability;
};
