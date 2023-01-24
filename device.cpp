#include "device.h"
#include "util.h"
#include <QVariant>
#include <QTextCodec>

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
    if (m_ModbusReply->error()) return;
    switch (m_currentOperation) {
    case CONNECT:
        m_failedRequestCount = 0;
        m_connected = true;
        m_pCommandThread->create(&Device::commandFunc);
        m_pCommandThread->start();
        emit connectSuccess(cp1251_to_utf((char*)m_ModbusReply->result().values().data()));
        break;
    default:
        return;
    }
}

void Device::commandFunc()
{
    forever {
        if (!m_commandQueue.count() || m_currentOperation != NONE) continue;
        m_currentOperation = m_commandQueue.dequeue();
        switch (m_currentOperation){
        case READINFO:
            processReadInfo();
            break;
        case READCONFIG:
            processReadConfig();
            break;
        case WRITECONFIG:
            processWriteConfig();
        }
    }
}

void Device::processReadInfo()
{

}
