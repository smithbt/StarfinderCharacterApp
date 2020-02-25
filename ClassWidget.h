#pragma once

#include <QWidget>
#include "ui_ClassWidget.h"

class ClassWidget : public QWidget
{
	Q_OBJECT

public:
	ClassWidget(QWidget *parent = Q_NULLPTR);
	~ClassWidget();

	int getLevel();

	void setClassName(QString className);
	void setLevel(int level);

private:
	Ui::ClassWidget ui;
};
