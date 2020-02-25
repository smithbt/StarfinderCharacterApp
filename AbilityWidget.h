#pragma once

#include <QWidget>
#include "ui_AbilityWidget.h"

class AbilityWidget : public QWidget
{
	Q_OBJECT

public:
	AbilityWidget(QWidget* parent = Q_NULLPTR);
	~AbilityWidget();

	int base() const;
	int upgrade() const;

	void setLabelText(QString name);

signals:
	void editDone(AbilityWidget*);

public slots:
	void setScore(int score);
	void setModifier(int modifier);
	void setBase(int base);
	void setUpgrade(int upgrade);

private:
	Ui::AbilityWidget ui;
};