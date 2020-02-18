#pragma once

#include <QWidget>
#include "ui_ResourceWidget.h"
#include "Resource.h"

class ResourceWidget : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(Resource* resource READ getResource WRITE setResource)

public:
	ResourceWidget(QWidget *parent = Q_NULLPTR);
	~ResourceWidget();

	Resource* getResource() const;
	void setResource(Resource* resource);

private:
	Ui::ResourceWidget ui;
	Resource* m_resource;
};
