#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "connectform.h"
#include "device.h"
#include "channelconfigwidget.h"

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
        void onUpdateInfoTimerTimeout();

private:
    Ui::MainWindow *ui;
    ConnectForm *connectForm;
    Device *m_device;
    Device::TDeviceInfo m_devInfo;
    Device::TDeviceConf m_devConf;
    QTimer updateInfoTimer;
    QList<ChannelConfigWidget *> m_configWigets;
    void processConfig();
    void processInfo();

};
#endif // MAINWINDOW_H
