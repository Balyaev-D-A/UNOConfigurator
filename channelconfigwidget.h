#ifndef CHANNELCONFIGWIDGET_H
#define CHANNELCONFIGWIDGET_H

#include <QWidget>
#include <QIntValidator>
#include <QDoubleValidator>
#include "device.h"

namespace Ui {
class ChannelConfigWidget;
}

class ChannelConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChannelConfigWidget(QWidget *parent = nullptr);
    ~ChannelConfigWidget();
    void setConfig(Device::TChannelConfig config);
    void setSignalers(quint16 signalers);
    void setContacts(quint16 contacts);
    Device::TChannelConfig getConfig();
    quint16 getSignalers();
    quint16 getContacts();

private:
    Ui::ChannelConfigWidget *ui;
    QIntValidator intValidator;
    QDoubleValidator doubleValidator;
};

#endif // CHANNELCONFIGWIDGET_H
