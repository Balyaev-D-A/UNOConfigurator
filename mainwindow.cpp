#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->connectAction, &QAction::triggered, this, &MainWindow::on_connectAction_clicked);
    connectForm = new ConnectForm(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectAction_clicked()
{
    connectForm->show();
}
