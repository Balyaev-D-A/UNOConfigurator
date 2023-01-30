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
    m_configWigets.append(ui->)
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
