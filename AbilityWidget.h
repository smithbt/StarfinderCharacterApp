#pragma once

#include <QWidget>
#include "ui_AbilityWidget.h"
#include "Ability.h"

class AbilityWidget : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(Ability* ability READ getAbility WRITE setAbility)

public:
	AbilityWidget(QWidget *parent = Q_NULLPTR);
	~AbilityWidget();

	void setAbility(Ability* a);
	Ability* getAbility() const;

	void setLabelText(QString name);

private:
	Ui::AbilityWidget ui;
	Ability* ability;
};
