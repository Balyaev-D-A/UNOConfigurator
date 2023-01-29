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
    fillTypeBox();
    fillUOMBox();
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
    result.m_wUOMCode = ui->uomBox->currentData().toUInt();
    result.m_fMinValue = ui->lowEdit->text().toFloat();
    result.m_fMaxValue = ui->highEdit->text().toFloat();
    result.m_fMaxRate = ui->maxcpsEdit->text().toFloat();
    result.m_fScaleCoeff = ui->coeffEdit->text().toFloat();
    result.m_fBackground = ui->backgroundEdit->text().toFloat();
    result.m_fDeadTime = ui->deadtimeEdit->text().toFloat();
    result.m_wCheckTime = ui->controltimeEdit->text().toUInt();
    result.m_wMaximTime = ui->maxmeastimeEdit->text().toUInt();
    result.m_fThreshold1 = ui->alarmEdit->text().toFloat();
    result.m_fThreshold2 = ui->emergencyEdit->text().toFloat();

    return result;
}

quint16 ChannelConfigWidget::getSignalers()
{
    quint16 result = 0;
    result = result | ((quint16) ui->sign1Box->isChecked());
    result = result | ((quint16) ui->sign2Box->isChecked() << 1);
    result = result | ((quint16) ui->sign3Box->isChecked() << 2);
    result = result | ((quint16) ui->sign4Box->isChecked() << 3);
    result = result | ((quint16) ui->sign5Box->isChecked() << 4);
    result = result | ((quint16) ui->sign6Box->isChecked() << 5);
    result = result | ((quint16) ui->sign7Box->isChecked() << 6);
    result = result | ((quint16) ui->sign8Box->isChecked() << 7);
    result = result | ((quint16) ui->sign9Box->isChecked() << 8);
    result = result | ((quint16) ui->sign10Box->isChecked() << 9);
    result = result | ((quint16) ui->sign11Box->isChecked() << 10);
    result = result | ((quint16) ui->sign12Box->isChecked() << 11);
    result = result | ((quint16) ui->sign13Box->isChecked() << 12);
    result = result | ((quint16) ui->sign14Box->isChecked() << 13);
    result = result | ((quint16) ui->sign15Box->isChecked() << 14);
    result = result | ((quint16) ui->sign16Box->isChecked() << 15);

    return result;
}

quint16 ChannelConfigWidget::getContacts()
{
    quint16 result = 0;
    result = result | ((quint16) ui->cont1Box->isChecked());
    result = result | ((quint16) ui->cont2Box->isChecked() << 1);
    result = result | ((quint16) ui->cont3Box->isChecked() << 2);
    result = result | ((quint16) ui->cont4Box->isChecked() << 3);
    result = result | ((quint16) ui->cont5Box->isChecked() << 4);
    result = result | ((quint16) ui->cont6Box->isChecked() << 5);
    result = result | ((quint16) ui->cont7Box->isChecked() << 6);
    result = result | ((quint16) ui->cont8Box->isChecked() << 7);
    result = result | ((quint16) ui->cont9Box->isChecked() << 8);
    result = result | ((quint16) ui->cont10Box->isChecked() << 9);
    result = result | ((quint16) ui->cont11Box->isChecked() << 10);
    result = result | ((quint16) ui->cont12Box->isChecked() << 11);
    result = result | ((quint16) ui->cont13Box->isChecked() << 12);
    result = result | ((quint16) ui->cont14Box->isChecked() << 13);
    result = result | ((quint16) ui->cont15Box->isChecked() << 14);
    result = result | ((quint16) ui->cont16Box->isChecked() << 15);

    return result;
}

void ChannelConfigWidget::fillTypeBox()
{
    ui->typeBox->addItem("Отключено", 255);
    ui->typeBox->addItem("БДРГ-18С ч.", 1);
    ui->typeBox->addItem("БДРГ-18С г.", 2);
    ui->typeBox->addItem("БДРГ-15С", 3);
    ui->typeBox->addItem("БДБН-10С", 4);
    ui->typeBox->addItem("БДПН-22С", 5);
    ui->typeBox->addItem("БДГБ-21С ч.", 6);
    ui->typeBox->addItem("БДГБ-21С г.", 7);
    ui->typeBox->addItem("УДАБ-07С", 8);
    ui->typeBox->addItem("МН 5141", 9);
    ui->typeBox->addItem("КГС-ОУ", 10);
    ui->typeBox->addItem("КГС-ДУМ", 11);
    ui->typeBox->addItem("ТП 1141", 12);
    ui->typeBox->addItem("БДРГ-17С1", 13);
    ui->typeBox->addItem("БДРГ-17С2", 14);
    ui->typeBox->addItem("БДРГ-17С4 ч.", 15);
    ui->typeBox->addItem("БДРГ-17С4 г.", 16);
    ui->typeBox->addItem("БДГБ-21С3", 17);
    ui->typeBox->addItem("БДЖГ-13Р", 18);
    ui->typeBox->addItem("МН5141(0-30)", 19);
    ui->typeBox->addItem("БДРГ-17С3", 20);
    ui->typeBox->addItem("УДЖГ-35Р", 21);
    ui->typeBox->addItem("БДРГ-17С4К ч.", 22);
    ui->typeBox->addItem("БДРГ-17С4К г.", 23);
    ui->typeBox->addItem("ПФК-100Р04", 24);
    ui->typeBox->addItem("ПФК-99Р02", 25);
    ui->typeBox->addItem("ПФК-99Р1 т.", 26);
    ui->typeBox->addItem("ПФК-99Р1 в.", 27);
    ui->typeBox->addItem("БДГБ-40П", 28);
    ui->typeBox->addItem("БДРГ-17С1К", 29);
    ui->typeBox->addItem("БДРГ-17С2К", 30);
    ui->typeBox->addItem("УДГП-04Р 1к.", 31);
    ui->typeBox->addItem("УДГП-04Р 2к.", 32);
    ui->typeBox->addItem("БДГГ-02С 1к.", 33);
    ui->typeBox->addItem("БДГГ-02С 2к.", 34);
    ui->typeBox->addItem("УРСВ-530", 35);
    ui->typeBox->addItem("УРСВ-520", 36);
    ui->typeBox->addItem("УР", 37);
    ui->typeBox->addItem("УРСВ-510", 38);
    ui->typeBox->addItem("БДРГ-42Р ч.", 39);
    ui->typeBox->addItem("БДРГ-42Р г.", 40);
    ui->typeBox->addItem("x1", 100);
}

void ChannelConfigWidget::fillUOMBox()
{
    ui->uomBox->addItem("Гр/ч", 1);
    ui->uomBox->addItem("Бэр/ч", 2);
    ui->uomBox->addItem("Зв/ч", 3);
    ui->uomBox->addItem("Р/ч", 4);
    ui->uomBox->addItem("Н/(м²*с)", 5);
    ui->uomBox->addItem("Бк/м³", 8);
    ui->uomBox->addItem("Ки/л", 9);
    ui->uomBox->addItem("1/(мин*см²)", 10);
    ui->uomBox->addItem("Гр", 16);
    ui->uomBox->addItem("Рад", 17);
    ui->uomBox->addItem("Зв", 18);
    ui->uomBox->addItem("мг/м³", 32);
    ui->uomBox->addItem("%", 48);
    ui->uomBox->addItem("имп/с", 49);
    ui->uomBox->addItem("°С", 50);
    ui->uomBox->addItem("Вт", 51);
    ui->uomBox->addItem("В", 52);
    ui->uomBox->addItem("сек", 53);
    ui->uomBox->addItem("м³", 54);
    ui->uomBox->addItem("м³/ч", 55);
    ui->uomBox->addItem("м³/с", 56);
    ui->uomBox->addItem("л/мин", 57);
}

void ChannelConfigWidget::on_typeBox_currentIndexChanged(int index)
{
    if (!index) {
        ui->uomBox->setVisible(false);
        ui->lowEdit->setVisible(false);
        ui->highEdit->setVisible(false);
        ui->coeffEdit->setVisible(false);
        ui->maxcpsEdit->setVisible(false);
        ui->backgroundEdit->setVisible(false);
        ui->deadtimeEdit->setVisible(false);
        ui->controltimeEdit->setVisible(false);
        ui->maxmeastimeEdit->setVisible(false);
        ui->alarmEdit->setVisible(false);
        ui->emergencyEdit->setVisible(false);
        ui->signalersGroup->setVisible(false);
        ui->contactsGroup->setVisible(false);
        ui->uomLabel->setVisible(false);
        ui->lowLabel->setVisible(false);
        ui->highLabel->setVisible(false);
        ui->coeffLabel->setVisible(false);
        ui->maxcpsLabel->setVisible(false);
        ui->backgroundLabel->setVisible(false);
        ui->deadtimeLabel->setVisible(false);
        ui->controltimeLabel->setVisible(false);
        ui->maxtimeLabel->setVisible(false);
        ui->alarmLabel->setVisible(false);
        ui->emergencyLabel->setVisible(false);
    }
    else {
        ui->uomBox->setVisible(true);
        ui->lowEdit->setVisible(true);
        ui->highEdit->setVisible(true);
        ui->coeffEdit->setVisible(true);
        ui->maxcpsEdit->setVisible(true);
        ui->backgroundEdit->setVisible(true);
        ui->deadtimeEdit->setVisible(true);
        ui->controltimeEdit->setVisible(true);
        ui->maxmeastimeEdit->setVisible(true);
        ui->alarmEdit->setVisible(true);
        ui->emergencyEdit->setVisible(true);
        ui->signalersGroup->setVisible(true);
        ui->contactsGroup->setVisible(true);
        ui->uomLabel->setVisible(true);
        ui->lowLabel->setVisible(true);
        ui->highLabel->setVisible(true);
        ui->coeffLabel->setVisible(true);
        ui->maxcpsLabel->setVisible(true);
        ui->backgroundLabel->setVisible(true);
        ui->deadtimeLabel->setVisible(true);
        ui->controltimeLabel->setVisible(true);
        ui->maxtimeLabel->setVisible(true);
        ui->alarmLabel->setVisible(true);
        ui->emergencyLabel->setVisible(true);
    }
}

