#include "channelinfowidget.h"
#include "ui_channelinfowidget.h"

ChannelInfoWidget::ChannelInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChannelInfoWidget)
{
    ui->setupUi(this);
}

ChannelInfoWidget::~ChannelInfoWidget()
{
    delete ui;
}
