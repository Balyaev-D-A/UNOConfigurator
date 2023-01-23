#ifndef CONNECTFORM_H
#define CONNECTFORM_H

#include <QWidget>
#include <QtSerialPort/QSerialPortInfo>

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

};

#endif // CONNECTFORM_H
