#pragma once

#include <QStringList>
#include <QWizard>
#include "ui_CreatorWizard.h"

class CreatorWizard : public QWizard
{
	Q_OBJECT

public:
	CreatorWizard(QWidget *parent = Q_NULLPTR);
	~CreatorWizard();

	void setClassList(QStringList classes);

	void accept() override;

private:
	Ui::CreatorWizard ui;
};
