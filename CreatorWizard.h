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

	void accept() override;

signals:
	void characterDataReady(QJsonObject);

protected slots:
	void on_rAdjButton_clicked();

private:
	Ui::CreatorWizard ui;
	QHash<QString, QSpinBox*> abilitySpinBoxes;
};
