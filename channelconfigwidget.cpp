#include "channelconfigwidget.h"
#include "ui_channelconfigwidget.h"

ChannelConfigWidget::ChannelConfigWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChannelConfigWidget)
{
    ui->setupUi(this);
}

ChannelConfigWidget::~ChannelConfigWidget()
{
    delete ui;
}
