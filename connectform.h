#ifndef CONNECTFORM_H
#define CONNECTFORM_H

#include <QWidget>
#include <QtSerialPort/QSerialPortInfo>
#include <QShowEvent>

namespace Ui {
class ConnectForm;
}

class ConnectForm : public QWidget
{
    typedef  struct {
        QString port;
        char address;
    } ConnInfo;

    Q_OBJECT

public:
    explicit ConnectForm(QWidget *parent = nullptr);
    ~ConnectForm();

private:
    Ui::ConnectForm *ui;
    QSerialPortInfo *spi;
private slots:
    void updatePorts();
    void on_cancelButton_clicked();
    void on_okButton_clicked();

    void on_portBox_currentIndexChanged(const QString &portName);

    void on_updateButton_clicked();

protected:
    void showEvent(QShowEvent *e);

signals:
    void connChoosed(ConnInfo ci);
};

#endif // CONNECTFORM_H
