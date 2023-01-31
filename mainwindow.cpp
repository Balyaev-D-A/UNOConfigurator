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
        ui->logEdit->document()->setHtml(ui->logEdit->document()->toHtml() +
                                         QString("<span style=\"color:red\">Ошибка подключения к устройству: %1<br/></span>").arg(m_device->errorString()));
        return;
    }
    if (!m_device->getCurrentConfig(&m_devConf)) {
        return;
    }
    processConfig();
    updateInfoTimer.start(1000);
}

void MainWindow::onUpdateInfoTimerTimeout()
{
    if (!m_device->getCurrentInfo(&m_devInfo))
        ui->logEdit->document()->setHtml(ui->logEdit->document()->toHtml() +
                                         QString("<span style=\"color:red\">Ошибка получения информации: %1<br/></span>").arg(m_device->errorString()));
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
    default:
        return "";
    }
}
