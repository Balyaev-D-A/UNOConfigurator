#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectForm = new ConnectForm(this);
    m_device = new Device(this);
    connect(ui->connectAction, &QAction::triggered, this, &MainWindow::onConnectActionClicked);
    connect(ui->disconnectAction, &QAction::triggered, this, &MainWindow::onDisconnectActionClicked);
    connect(connectForm, &ConnectForm::connChoosed, this, &MainWindow::onConnectFormConnChoosed);
    connect(&updateInfoTimer, &QTimer::timeout, this, &MainWindow::onUpdateInfoTimerTimeout);
    connect(ui->updateButton, &QPushButton::clicked, this, &MainWindow::onUpdateInfoTimerTimeout);
    m_configWigets.append(ui->widget_1);
    m_configWigets.append(ui->widget_2);
    m_configWigets.append(ui->widget_3);
    m_configWigets.append(ui->widget_4);
    m_configWigets.append(ui->widget_5);
    m_configWigets.append(ui->widget_6);
    m_configWigets.append(ui->widget_7);
    m_configWigets.append(ui->widget_8);
    m_configWigets.append(ui->widget_9);
    m_configWigets.append(ui->widget_10);
    m_configWigets.append(ui->widget_11);
    m_configWigets.append(ui->widget_12);
    m_configWigets.append(ui->widget_13);
    m_configWigets.append(ui->widget_14);
    m_configWigets.append(ui->widget_15);
    m_configWigets.append(ui->widget_16);

    m_chanLabels.append(ui->chan1Label);
    m_chanLabels.append(ui->chan2Label);
    m_chanLabels.append(ui->chan3Label);
    m_chanLabels.append(ui->chan4Label);
    m_chanLabels.append(ui->chan5Label);
    m_chanLabels.append(ui->chan6Label);
    m_chanLabels.append(ui->chan7Label);
    m_chanLabels.append(ui->chan8Label);
    m_chanLabels.append(ui->chan9Label);
    m_chanLabels.append(ui->chan10Label);
    m_chanLabels.append(ui->chan11Label);
    m_chanLabels.append(ui->chan12Label);
    m_chanLabels.append(ui->chan13Label);
    m_chanLabels.append(ui->chan14Label);
    m_chanLabels.append(ui->chan15Label);
    m_chanLabels.append(ui->chan16Label);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onConnectActionClicked()
{
    connectForm->show();
}

void MainWindow::onDisconnectActionClicked()
{
    m_device->disconnectDevice();
}

void MainWindow::onConnectFormConnChoosed(ConnectForm::ConnectionInfo ci)
{
    if (!m_device->connectToDevice(ci.port, ci.address)) {
        appendToLog(QString("<span style=\"color:red\">Ошибка подключения к устройству: %1<br/></span>").arg(m_device->errorString()));
        return;
    }
    if (!m_device->getCurrentConfig(&m_devConf)) {
        appendToLog(QString("<span style=\"color:red\">Ошибка получения информации: %1<br/></span>").arg(m_device->errorString()));
        return;
    }
    processConfig();
    //updateInfoTimer.start(1000);
}

void MainWindow::onUpdateInfoTimerTimeout()
{
    if (!m_device->getCurrentInfo(&m_devInfo))
        appendToLog(QString("<span style=\"color:red\">Ошибка получения информации: %1<br/></span>").arg(m_device->errorString()));
    processInfo();
}

void MainWindow::processConfig()
{
    for (int i=0; i<16; i++)
    {
        m_configWigets[i]->setConfig(m_devConf.ChanConf[i]);
        m_configWigets[i]->setSignalers(m_devConf.SignConf[i]);
        m_configWigets[i]->setContacts(m_devConf.ContConf[i]);
    }
}

void MainWindow::processInfo()
{
    QString detName;
    QString uomString;
    for (int i=0; i<16; i++)
    {
        m_chanLabels[i]->setText(QString("%1").arg(m_devInfo.m_cInfo[0][i].m_fsValue, 0, 'E', 3));
    }
}

QString MainWindow::detectorString(quint16 code)
{
    switch(code) {
    case 255:
        return "";
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

QString MainWindow::uomString(quint16 code)
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

void MainWindow::appendToLog(QString logStr)
{
    m_log.append(logStr);
    ui->logEdit->document()->setHtml(m_log);
}

void MainWindow::on_readDeviceButton_clicked()
{
    if (!m_device->getCurrentConfig(&m_devConf)) {
        appendToLog(QString("<span style=\"color:red\">Ошибка получения информации: %1<br/></span>").arg(m_device->errorString()));
        return;
    }
    processConfig();
}

