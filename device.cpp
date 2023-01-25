#include "device.h"
#include "util.h"
#include <QVariant>
#include <QTextCodec>

Device::Device(QObject *parent)
    : QObject{parent}
{
    m_pPort = new QSerialPort();
}

Device::~Device()
{
    m_pPort->deleteLater();
}



bool Device::connectToDevice(QString port, uchar address)
{
    m_pPort->setPortName(port);
    m_pPort->setBaudRate(QSerialPort::Baud19200);
    m_pPort->setDataBits(QSerialPort::Data8);
    m_pPort->setStopBits(QSerialPort::OneStop);
    m_pPort->setParity(QSerialPort::NoParity);
    m_pPort->setFlowControl(QSerialPort::NoFlowControl);
    if (!m_pPort->open(QIODevice::ReadWrite)){
        m_errorString = "Ошибка открытия порта: " + m_pPort->errorString();
        return false;
    }
    m_address = address;
    char *buffer = nullptr;
    if (!readHoldingRegisters(0x1170, 1, buffer)) {
        return false;
    }
    free(buffer);
    m_errorString = NOERROR;
    return true;
}

bool Device::readHoldingRegisters(quint16 start, quint16 count, char *result)
{
    if (!m_pPort->isOpen()) {
        m_errorString = "Соединение не установлено";
        return false;
    }

    QByteArray req;
    req.append(m_address);
    req.append(0x03);
    req.append((char) start >> 8);
    req.append((char) start & 0xFF);
    req.append((char) count >> 8);
    req.append((char) count & 0xFF);
    quint16 crc = CalculateCRC16(req.data(), 6);
    req.append((char) crc & 0xFF);
    req.append((char) crc >> 8);
    if (m_pPort->write(req) < 0){
        m_errorString = "Ошибка записи в порт: " + m_pPort->errorString();
        return false;
    }
    if (!m_pPort->waitForBytesWritten(100)){
        m_errorString = "Таймаут при записи в порт.";
        return false;
    }
    if (!m_pPort->waitForReadyRead(500)) {
        m_errorString = "Истекло время ожидания ответа от устройства.";
        return false;
    }
    QByteArray response = m_pPort->readAll();
    if (response.data()[0] != m_address) {
        m_errorString = "Неправильный адрес устройства в ответе.";
        return false;
    }
    if (response.data()[1] != 0x03) {
        m_errorString = "Неправильный код функции в ответе.";
        return false;
    }
    int data_count = response[2];
    if (data_count != count) {
        m_errorString = "Неверная длина ответа.";
        return false;
    }
    crc = ((quint16)(response[response.length()-1]) << 8) + response[response.length()-2];
    if (crc != CalculateCRC16(response.data(), response.length()-2)) {
        m_errorString = "Ошибка контрольной суммы.";
        return false;
    }
    result = (char *) malloc(data_count);
    memcpy(result, response.data()+3, data_count);
    m_errorString = NOERROR;
    return true;
}

bool Device::getCurrentInfo(Device::TDeviceInfo *devInfo)
{
    char* buff = (char *) devInfo;

    if (!readHoldingRegisters(0x00, 0x20, buff)) {
        return false;
    }
    if (!readHoldingRegisters(0x00, 0x20, buff+20)) {
        return false;
    }
    if (!readHoldingRegisters(0x00, 0x14, buff+40)) {
        return false;
    }
    if (!readHoldingRegisters(0x00, 0x20, buff+54)) {
        return false;
    }
    if (!readHoldingRegisters(0x00, 0x20, buff+74)) {
        return false;
    }

    return true;
}

bool Device::getCurrentConfig(Device::TDeviceConf *devConf)
{
    char* buff = (char *) devConf;
    for (int i = 0; i < 8; ++i)
        if (!readHoldingRegisters(0x1000+i*40, 0x0028, buff+i*40))
        {
            return false;
        }
    if (!readHoldingRegisters(0x1140, 0x0030, buff+0x140)) {
        return false;
    }
    return true;
}
