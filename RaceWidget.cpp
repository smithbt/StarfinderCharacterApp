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
		for (QMap<QString, QString>::ConstIterator ci = m_race->features().cbegin(); ci != m_race->features().cend(); ++ci)
			featureList += QString("<b>%1</b><br>%2<br>").arg(ci.key(), ci.value());
		ui.rFeaturesLabel->setText(featureList);
	}
}

Race* RaceWidget::getRace() const
{
	return m_race;
}
