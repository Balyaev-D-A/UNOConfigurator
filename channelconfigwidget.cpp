#include "channelconfigwidget.h"
#include "ui_channelconfigwidget.h"

ChannelConfigWidget::ChannelConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChannelConfigWidget)
{
    ui->setupUi(this);
    doubleValidator.setDecimals(3);
    doubleValidator.setNotation(QDoubleValidator::ScientificNotation);
    ui->lowEdit->setValidator(&doubleValidator);
    ui->highEdit->setValidator(&doubleValidator);
    ui->maxcpsEdit->setValidator(&doubleValidator);
    ui->coeffEdit->setValidator(&doubleValidator);
    ui->backgroundEdit->setValidator(&doubleValidator);
    ui->deadtimeEdit->setValidator(&doubleValidator);
    ui->controltimeEdit->setValidator(&intValidator);
    ui->maxmeastimeEdit->setValidator(&intValidator);
    ui->alarmEdit->setValidator(&doubleValidator);
    ui->emergencyEdit->setValidator(&doubleValidator);
}

ChannelConfigWidget::~ChannelConfigWidget()
{
    delete ui;
}

void ChannelConfigWidget::setConfig(Device::TChannelConfig config)
{
    ui->typeBox->setCurrentIndex(ui->typeBox->findData(config.m_wDetCode));
    ui->uomBox->setCurrentIndex(ui->uomBox->findData(config.m_wUOMCode));
    ui->lowEdit->setText(QString("%1").arg(config.m_fMinValue,0, 'E', 3));
    ui->highEdit->setText(QString("%1").arg(config.m_fMaxValue, 0, 'E', 3));
    ui->maxcpsEdit->setText(QString("%1").arg(config.m_fMaxRate, 0, 'E', 3));
    ui->coeffEdit->setText(QString("%1").arg(config.m_fScaleCoeff, 0, 'E', 3));
    ui->backgroundEdit->setText(QString("%1").arg(config.m_fBackground, 0, 'E', 3));
    ui->deadtimeEdit->setText(QString("%1").arg(config.m_fDeadTime, 0, 'E', 3));
    ui->controltimeEdit->setText(QString("%1").arg(config.m_wCheckTime));
    ui->maxmeastimeEdit->setText(QString("%1").arg(config.m_wMaximTime));
    ui->alarmEdit->setText(QString("%1").arg(config.m_fThreshold1, 0, 'E', 3));
    ui->emergencyEdit->setText(QString("%1").arg(config.m_fThreshold2, 0, 'E', 3));
}

void ChannelConfigWidget::setSignalers(quint16 signalers)
{
    ui->sign1Box->setChecked(signalers & 0x01);
    ui->sign2Box->setChecked(signalers & 0x02);
    ui->sign3Box->setChecked(signalers & 0x04);
    ui->sign4Box->setChecked(signalers & 0x08);
    ui->sign5Box->setChecked(signalers & 0x10);
    ui->sign6Box->setChecked(signalers & 0x20);
    ui->sign7Box->setChecked(signalers & 0x40);
    ui->sign8Box->setChecked(signalers & 0x80);
    ui->sign9Box->setChecked(signalers & 0x100);
    ui->sign10Box->setChecked(signalers & 0x200);
    ui->sign11Box->setChecked(signalers & 0x400);
    ui->sign12Box->setChecked(signalers & 0x800);
    ui->sign13Box->setChecked(signalers & 0x1000);
    ui->sign14Box->setChecked(signalers & 0x2000);
    ui->sign15Box->setChecked(signalers & 0x4000);
    ui->sign16Box->setChecked(signalers & 0x8000);

}

void ChannelConfigWidget::setContacts(quint16 contacts)
{
    ui->cont1Box->setChecked(contacts & 0x01);
    ui->cont2Box->setChecked(contacts & 0x02);
    ui->cont3Box->setChecked(contacts & 0x04);
    ui->cont4Box->setChecked(contacts & 0x08);
    ui->cont5Box->setChecked(contacts & 0x10);
    ui->cont6Box->setChecked(contacts & 0x20);
    ui->cont7Box->setChecked(contacts & 0x40);
    ui->cont8Box->setChecked(contacts & 0x80);
    ui->cont9Box->setChecked(contacts & 0x100);
    ui->cont10Box->setChecked(contacts & 0x200);
    ui->cont11Box->setChecked(contacts & 0x400);
    ui->cont12Box->setChecked(contacts & 0x800);
    ui->cont13Box->setChecked(contacts & 0x1000);
    ui->cont14Box->setChecked(contacts & 0x2000);
    ui->cont15Box->setChecked(contacts & 0x4000);
    ui->cont16Box->setChecked(contacts & 0x8000);
}

Device::TChannelConfig ChannelConfigWidget::getConfig()
{
    Device::TChannelConfig result;
    result.m_wDetCode = ui->typeBox->currentData().toUInt();
}
