#pragma once

#include <QWidget>
#include "ui_AbilityWidget.h"
#include "Ability.h"

class AbilityWidget : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(QVector<Ability*> abilities READ getAbilityList WRITE setAbilityList NOTIFY abilityListChanged)

public:
	AbilityWidget(QWidget *parent = Q_NULLPTR);
	~AbilityWidget();

	void setAbilityList(QVector<Ability*> a);
	QVector<Ability*> getAbilityList() const;

signals:
	void abilityListChanged(QVector<Ability*>);

private:
	Ui::AbilityWidget ui;
	QVector<Ability*> abilities;
	QVector<QLabel*> aMods;
	QVector<QLabel*> aScores;
	QMetaEnum aEnum;
};
