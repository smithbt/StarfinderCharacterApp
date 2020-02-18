#include "ResourceWidget.h"

ResourceWidget::ResourceWidget(QWidget *parent)
	: QWidget(parent),
	m_resource(nullptr)
{
	ui.setupUi(this);
}

ResourceWidget::~ResourceWidget()
{
}

Resource* ResourceWidget::getResource() const
{
	return m_resource;
}

void ResourceWidget::setResource(Resource* resource)
{
	if (resource != m_resource) {
		if (m_resource) 
			m_resource->disconnect();

		m_resource = resource;

		if (m_resource) {
			connect(m_resource, &Resource::currentChanged, ui.currentSpinBox, &QSpinBox::setValue);
			connect(ui.currentSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), m_resource, &Resource::setCurrent);
			
			ui.maxLabel->setNum(m_resource->max());
			ui.currentSpinBox->setMaximum(m_resource->max());
			ui.currentSpinBox->setValue(m_resource->current());
			ui.currentSpinBox->setSingleStep(m_resource->step());
		}
	}
}
