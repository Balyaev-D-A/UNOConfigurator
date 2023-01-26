#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectForm = new ConnectForm(this);
    device = new Device(this);
    connect(ui->connectAction, &QAction::triggered, this, &MainWindow::onConnectActionClicked);
    connect(ui->disconnectAction, &QAction::triggered, this, &MainWindow::onDisconnectActionClicked);
    connect(connectForm, &ConnectForm::connChoosed, this, &MainWindow::onConnectFormConnChoosed);
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
    device->disconnectDevice();
}

void MainWindow::onConnectFormConnChoosed(ConnectForm::ConnectionInfo ci)
{
    if (!device->connectToDevice(ci.port, ci.address)) {
        ui->logEdit->document()->setHtml(ui->logEdit->document()->toHtml() +
                                         QString("<span style=\"color:red\">Ошибка подключения к устройству: %1<br/></span>").arg(device->errorString()));
    }
}
