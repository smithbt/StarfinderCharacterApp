#pragma once

#include <QWidget>
#include "ui_ResourceWidget.h"
#include "Resource.h"

class ResourceWidget : public QWidget
{
	Q_OBJECT

public:
	ResourceWidget(QWidget *parent = Q_NULLPTR);
	~ResourceWidget();

	int getCurrentValue() const;

	void setCurrent(int current);
	void setMax(int max);
	void setStep(int step);

private:
	Ui::ResourceWidget ui;
	Resource* m_resource;
};
