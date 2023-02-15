#ifndef CHANNELINFOWIDGET_H
#define CHANNELINFOWIDGET_H

#include <QWidget>
#include "device.h"

namespace Ui {
class ChannelInfoWidget;
}

class ChannelInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChannelInfoWidget(QWidget *parent = nullptr);
    ~ChannelInfoWidget();
    void setChannelNumber(int chanNum);
    void setData(Device::TChannelConfig *config, Device::TChannelInfo *info);
    void updateData();

private:
    Ui::ChannelInfoWidget *ui;
    int m_chanNum = 0;
    Device::TChannelConfig *m_config = nullptr;
    Device::TChannelInfo * m_info = nullptr;
    QString detectorString(quint16 code);
    QString uomString(quint16 code);
    void updateIndication();
};

#endif // CHANNELINFOWIDGET_H
