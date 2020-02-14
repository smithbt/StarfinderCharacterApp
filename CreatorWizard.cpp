#include "CreatorWizard.h"

CreatorWizard::CreatorWizard(QWidget *parent)
	: QWizard(parent)
{
	ui.setupUi(this);
}

CreatorWizard::~CreatorWizard()
{
}

void CreatorWizard::setClassList(QStringList classes)
{
	ui.classComboBox->addItems(classes);
}

void CreatorWizard::accept()
{
}
