#ifndef CHANNELCONFIGWIDGET_H
#define CHANNELCONFIGWIDGET_H

#include <QWidget>

namespace Ui {
class ChannelConfigWidget;
}

class ChannelConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChannelConfigWidget(QWidget *parent = nullptr);
    ~ChannelConfigWidget();

private:
    Ui::ChannelConfigWidget *ui;
};

#endif // CHANNELCONFIGWIDGET_H
