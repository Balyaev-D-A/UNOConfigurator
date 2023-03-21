#include "channelinfowidget.h"
#include "ui_channelinfowidget.h"

ChannelInfoWidget::ChannelInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChannelInfoWidget)
{
    ui->setupUi(this);
}

ChannelInfoWidget::~ChannelInfoWidget()
{
    delete ui;
}

void ChannelInfoWidget::setChannelNumber(int chanNum)
{
    m_chanNum = chanNum;
}

void ChannelInfoWidget::setData(Device::TChannelConfig *config, Device::TChannelInfo *info)
{
    m_config = config;
    m_info = info;
}

QString ChannelInfoWidget::detectorString(quint16 code)
{
    switch(code) {
    case 255:
        return "Откл.";
    case 1:
        return "БДРГ-18С ч.";
    case 2:
        return "БДРГ-18С г.";
    case 3:
        return "БДРГ-15С";
    case 4:
        return "БДБН-10С";
    case 5:
        return "БДПН-22С";
    case 6:
        return "БДГБ-21С ч.";
    case 7:
        return "БДГБ-21С г.";
    case 8:
        return "УДАБ-07С";
    case 9:
        return "МН 5141";
    case 10:
        return "КГС-ОУ";
    case 11:
        return "КГС-ДУМ";
    case 12:
        return "ТП 1141";
    case 13:
        return "БДРГ-17С1";
    case 14:
        return "БДРГ-17С2";
    case 15:
        return "БДРГ-17С4 ч.";
    case 16:
        return "БДРГ-17С4 г.";
    case 17:
        return "БДГБ-21С3";
    case 18:
        return "БДЖГ-13Р";
    case 19:
        return "МН5141(0-30)";
    case 20:
        return "БДРГ-17С3";
    case 21:
        return "УДЖГ-35Р";
    case 22:
        return "БДРГ-17С4К ч.";
    case 23:
        return "БДРГ-17С4К г.";
    case 24:
        return "ПФК-100Р04";
    case 25:
        return "ПФК-99Р02";
    case 26:
        return "ПФК-99Р1 т.";
    case 27:
        return "ПФК-99Р1 в.";
    case 28:
        return "БДГБ-40П";
    case 29:
        return "БДРГ-17С1К";
    case 30:
        return "БДРГ-17С2К";
    case 31:
        return "УДГП-04Р 1к.";
    case 32:
        return "УДГП-04Р 2к.";
    case 33:
        return "БДГГ-02С 1к.";
    case 34:
        return "БДГГ-02С 2к.";
    case 35:
        return "УРСВ-530";
    case 36:
        return "УРСВ-520";
    case 37:
        return "УР";
    case 38:
        return "УРСВ-510";
    case 39:
        return "БДРГ-42Р ч.";
    case 40:
        return "БДРГ-42Р г.";
    case 100:
        return "x1";
    default:
        return "";
    }
}

QString ChannelInfoWidget::uomString(quint16 code)
{
    switch (code) {
    case 1:
        return "Гр/ч";
    case 2:
        return "Бэр/ч";
    case 3:
        return "Зв/ч";
    case 4:
        return "Р/ч";
    case 5:
        return "Н/(м²*с)";
    case 8:
        return "Бк/м³";
    case 9:
        return "Ки/л";
    case 10:
        return "1/(мин*см²)";
    case 16:
        return "Гр";
    case 17:
        return "Рад";
    case 18:
        return "Зв";
    case 32:
        return "мг/м³";
    case 48:
        return "%";
    case 49:
        return "имп/с";
    case 50:
        return "°С";
    case 51:
        return "Вт";
    case 52:
        return "В";
    case 53:
        return "сек";
    case 54:
        return "м³";
    case 55:
        return "м³/ч";
    case 56:
        return "м³/с";
    case 57:
        return "л/мин";
    default:
        return "";
    }
}

void ChannelInfoWidget::updateIndication()
{
    if (m_config->m_wDetCode == 255) {
        ui->dataLabel->setStyleSheet("color: rgb(0, 0, 0);\nbackground-color: rgb(0, 0, 0);");
        return;
    }
    if (!(m_info->m_dwState & Device::ST_ACTIVE)) {
        ui->dataLabel->setStyleSheet("color: rgb(0, 0, 0);\nbackground-color: rgb(0, 0, 0);");
        return;
    }
    if (m_info->m_dwState & Device::ST_FAILURE)
        ui->dataLabel->setStyleSheet("color: yellow; background-color: blue;");
    else if (m_info->m_dwState & (Device::ST_EX_HI_LIM1 | Device::ST_EX_HI_LIM2))
        ui->dataLabel->setStyleSheet("color: black; background-color: red;");
    else if (m_info->m_dwState & (Device::ST_EX_LO_LIM1 | Device::ST_EX_LO_LIM2))
        ui->dataLabel->setStyleSheet("color: black; background-color: yellow;");
    else
        ui->dataLabel->setStyleSheet("color: rgb(0, 0, 0);\nbackground-color: rgb(85, 255, 127);");
    ui->dataLabel->setText(QString("%1 %2").arg(m_info->m_fsValue, 0, 'E', 3).arg(uomString(m_config->m_wUOMCode)));
}

void ChannelInfoWidget::updateData()
{
    ui->captionLabel->setText(QString("[%1]: %2").arg(m_chanNum).arg(detectorString(m_config->m_wDetCode)));
    updateIndication();
}
