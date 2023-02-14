#ifndef CHANNELINFOWIDGET_H
#define CHANNELINFOWIDGET_H

#include <QWidget>

namespace Ui {
class ChannelInfoWidget;
}

class ChannelInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChannelInfoWidget(QWidget *parent = nullptr);
    ~ChannelInfoWidget();

private:
    Ui::ChannelInfoWidget *ui;
};

#endif // CHANNELINFOWIDGET_H
