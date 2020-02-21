#include "AbilityWidget.h"

AbilityWidget::AbilityWidget(QWidget *parent)
	: QWidget(parent),
	m_base(10),
	m_upgrade(0)
{
	ui.setupUi(this);
	ui.edit_frame->setVisible(false);

	connect(ui.upgrade_spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &AbilityWidget::setUpgrade); 
	connect(ui.base_spinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &AbilityWidget::setBase);

	connect(ui.ability_pushButton, &QPushButton::toggled, [this](bool checked) { if (!checked) emit editDone(this); });
}

AbilityWidget::~AbilityWidget()
{
}

int AbilityWidget::base() const
{
	return m_base;
}

int AbilityWidget::upgrade() const
{
	return m_upgrade;
}

void AbilityWidget::setScore(int score)
{
	if (score != ui.score_label->text())
		ui.score_label->setNum(score);
}

void AbilityWidget::setModifier(int modifier)
{
	QString modText = QString::asprintf("%+i", (modifier));
	if (modText != ui.mod_label->text())
		ui.mod_label->setText(modText);
}

void AbilityWidget::setBase(int base)
{
	if (base != m_base) {
		m_base = base;
		emit baseChanged(m_base);
	}
}

void AbilityWidget::setUpgrade(int upgrade)
{
	if (upgrade != m_upgrade) {
		m_upgrade = upgrade;
		emit upgradeChanged(m_upgrade);
	}
}

void AbilityWidget::setLabelText(QString name)
{
	ui.ability_pushButton->setText(name);
}
