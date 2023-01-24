#include "device.h"
#include <QVariant>

Device::Device(QObject *parent)
    : QObject{parent}
{
    m_pDevice = new QModbusRtuSerialMaster();
    m_pCommandThread = new QThread(this);
}

Device::~Device()
{
    m_pDevice->deleteLater();
    m_pCommandThread->deleteLater();
}

void Device::Connect(QString port, uchar address)
{
    if (m_pDevice->state() == QModbusDevice::ConnectedState) return;
    m_pDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter, port);
    m_pDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
    m_pDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud19200);
    m_pDevice->setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
    m_pDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
    m_pDevice->setTimeout(100);
    if (!m_pDevice->connectDevice()) {
        emit connectFail(m_pDevice->errorString());
        return;
    }
    m_address = address;
    m_ModbusReply =  m_pDevice->sendReadRequest(makeConnectRequest(), address);
    if (!m_ModbusReply->isFinished()){
        m_currentOperation = CONNECT;
        connect(m_ModbusReply, &QModbusReply::finished, this, &Device::onModbusReplyFinished);
        connect(m_ModbusReply, &QModbusReply::errorOccurred, this, &Device::onModbusReplyErrorOccured);
    }
}

void Device::onModbusReplyFinished()
{
    switch (m_currentOperation) {
    case CONNECT:
        if (!m_ModbusReply->error()){
            m_failedRequestCount = 0;
            m_connected = true;
            emit connectSuccess(QString::fromLocal8Bit((char*)m_ModbusReply->result().values().data()));
        }
        break;
    default:
        return;
    }
}
