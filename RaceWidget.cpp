#include "RaceWidget.h"

RaceWidget::RaceWidget(QWidget *parent)
	: QWidget(parent),
	m_race(nullptr)
{
	ui.setupUi(this);
}

RaceWidget::~RaceWidget()
{
}

void RaceWidget::setRace(Race* race)
{
	if (race != m_race) {
		m_race = race;

		ui.rNameLabel->setText(m_race->name());
		ui.rHPLabel->setText(QString("Hit Points: %1").arg(m_race->hitPoints()));

		ui.rFeatureTableWidget->setRowCount(m_race->features().size());
		int row = 0;
		for (QMap<QString, QString>::ConstIterator ci = m_race->features().cbegin(); ci != m_race->features().cend(); ++ci) {
			ui.rFeatureTableWidget->setItem(row, 0, new QTableWidgetItem(ci.key()));
			ui.rFeatureTableWidget->setItem(row, 1, new QTableWidgetItem(ci.value()));
			++row;
		}
	}
}

Race* RaceWidget::getRace() const
{
	return m_race;
}
