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

    m_infoWidgets.append(ui->infoWidget1);
    m_infoWidgets.append(ui->infoWidget2);
    m_infoWidgets.append(ui->infoWidget3);
    m_infoWidgets.append(ui->infoWidget4);
    m_infoWidgets.append(ui->infoWidget5);
    m_infoWidgets.append(ui->infoWidget6);
    m_infoWidgets.append(ui->infoWidget7);
    m_infoWidgets.append(ui->infoWidget8);
    m_infoWidgets.append(ui->infoWidget9);
    m_infoWidgets.append(ui->infoWidget10);
    m_infoWidgets.append(ui->infoWidget11);
    m_infoWidgets.append(ui->infoWidget12);
    m_infoWidgets.append(ui->infoWidget13);
    m_infoWidgets.append(ui->infoWidget14);
    m_infoWidgets.append(ui->infoWidget15);
    m_infoWidgets.append(ui->infoWidget16);

    for (int i=0; i<16; i++)
    {
        m_devConf.ChanConf[i].m_wDetCode = 255;
        m_infoWidgets[i]->setChannelNumber(i+1);
        m_infoWidgets[i]->setData(&m_devConf.ChanConf[i], &m_devInfo.m_cInfo[0][i]);
        m_infoWidgets[i]->updateData();
    }
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
    if (!m_device->getCurrentInfo(&m_devInfo)){
        appendToLog(QString("<span style=\"color:red\">Ошибка получения информации: %1<br/></span>").arg(m_device->errorString()));
        return;
    }
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
    QString logStr = "";
    for (int i=0; i<16; i++)
    {
        m_infoWidgets[1]->updateData();
        logStr += QString("%1 ").arg(m_devInfo.m_cInfo[0][i].m_dwState, 16, 2, QLatin1Char('0'));
    }
    appendToLog(logStr);
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

