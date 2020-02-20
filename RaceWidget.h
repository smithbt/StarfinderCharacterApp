#pragma once

#include <QWidget>
#include "ui_RaceWidget.h"
#include "Race.h"

class RaceWidget : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(Race* race WRITE setRace READ getRace)

public:
	RaceWidget(QWidget *parent = Q_NULLPTR);
	~RaceWidget();

	void setRace(Race* race);
	Race* getRace() const;

private:
	Ui::RaceWidget ui;
	Race* m_race;
};
