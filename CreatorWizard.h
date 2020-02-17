#pragma once

#include <QJsonArray>
#include <QJsonObject>
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

	QJsonObject jsonData();

private:
	Ui::CreatorWizard ui;
	QHash<QString, QSpinBox*> abilitySpinBoxes;
	QJsonObject json;
};
