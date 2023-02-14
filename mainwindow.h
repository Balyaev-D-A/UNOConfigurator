#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include "connectform.h"
#include "device.h"
#include "channelconfigwidget.h"
#include "channelinfowidget.h"

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

private slots:
        void on_readDeviceButton_clicked();

private:
    Ui::MainWindow *ui;
    ConnectForm *connectForm;
    Device *m_device;
    Device::TDeviceInfo m_devInfo;
    Device::TDeviceConf m_devConf;
    QTimer updateInfoTimer;
    QList<ChannelConfigWidget *> m_configWigets;
    QList<ChannelInfoWidget *> m_infoWidgets;
    QString m_log;
    void processConfig();
    void processInfo();
    QString detectorString(quint16 code);
    QString uomString(quint16 code);
    void appendToLog(QString logStr);

};
#endif // MAINWINDOW_H
