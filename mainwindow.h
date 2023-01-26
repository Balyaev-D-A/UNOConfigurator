#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connectform.h"
#include "device.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
        void onConnectActionClicked();
        void onDisconnectActionClicked();
        void onConnectFormConnChoosed(ConnectForm::ConnectionInfo ci);

private:
    Ui::MainWindow *ui;
    ConnectForm *connectForm;
    Device *device;

};
#endif // MAINWINDOW_H
