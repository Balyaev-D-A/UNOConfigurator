#include "connectform.h"
#include "ui_connectform.h"

ConnectForm::ConnectForm(QWidget *parent) :
    QWidget(parent, Qt::Window),
    ui(new Ui::ConnectForm)
{
    ui->setupUi(this);

}

ConnectForm::~ConnectForm()
{
    delete ui;
}

void ConnectForm::showEvent(QShowEvent *e)
{
    updatePorts();
    QWidget::showEvent(e);
}

void ConnectForm::updatePorts()
{
    QList<QSerialPortInfo> portList = QSerialPortInfo::availablePorts();

    ui->portBox->clear();
    ui->portBox->blockSignals(true);
    foreach(QSerialPortInfo pi, portList)
        ui->portBox->addItem(pi.portName());
    ui->portBox->blockSignals(false);
    on_portBox_currentIndexChanged(ui->portBox->currentText());
}
void ConnectForm::on_cancelButton_clicked()
{
    close();
}

void ConnectForm::on_okButton_clicked()
{
    ConnInfo ci;
    ci.address = ui->addressBox->value();
    ci.port = ui->portBox->currentText();
    emit connChoosed(ci);
    close();
}

void ConnectForm::on_portBox_currentIndexChanged(const QString &portName)
{
    if (portName.isEmpty()) return;
    QSerialPortInfo spi(portName);
    QString info = "<b>Производитель:</b> %1<br/>"
                   "<b>Описание:</b> %2<br/>";
    info = info.arg(spi.manufacturer()).arg(spi.description());
    if (!spi.isBusy())
        info += "<span style=\"color: green;\"><b>Порт свободен</b></span>";
    else
        info += "<span style=\"color: red;\"><b>Порт занят</b></span>";
    ui->infoText->document()->setHtml(info);

}

void ConnectForm::on_updateButton_clicked()
{
    updatePorts();
}
