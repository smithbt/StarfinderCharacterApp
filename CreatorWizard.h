#pragma once

#include <QStringList>
#include <QWizard>
#include "ui_CreatorWizard.h"
#include "Character.h"

class CreatorWizard : public QWizard
{
	Q_OBJECT

public:
	CreatorWizard(QWidget *parent = Q_NULLPTR);
	~CreatorWizard();

	void accept() override;

signals:
	void characterReady(Character*);

protected slots:
	void on_rAdjButton_clicked();
	void on_rAdjResetButton_clicked();
	void on_rAddFeatureButton_clicked();
	void on_rRemoveFeatureButton_clicked();

private:
	Ui::CreatorWizard ui;
	QHash<QString, QSpinBox*> abilitySpinBoxes;
};
