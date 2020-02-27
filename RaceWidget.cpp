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
		ui.rSizeLabel->setText(m_race->size());
		ui.rTypeLabel->setText(m_race->type());
		ui.rHPLabel->setText(QString("<b>Hit Points</b>: %1").arg(m_race->hitPoints()));

		QString featureList;
		for (int i = 0; i < m_race->features().size(); ++i) {
			QStringList feature = m_race->features().at(i).split("|");
			featureList += QString("<b>%1</b><br>%2<br>").arg(feature.at(0), feature.at(1));
		}
		ui.rFeaturesLabel->setText(featureList);
	}
}

Race* RaceWidget::getRace() const
{
	return m_race;
}
