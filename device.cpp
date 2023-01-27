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
    quint16 buffer;
    if (!readHoldingRegisters(0x1170, 1, (char *)&buffer)) {
        m_pPort->close();
        return false;
    }
    if (buffer != address) {
        m_errorString = "Неподдерживаемое устройство.";
        m_pPort->close();
        return false;
    }
    m_connected = true;
    m_errorString = NOERROR;
    return true;
}

void Device::disconnectDevice()
{
    m_pPort->close();
    m_connected = false;
}

QString Device::errorString()
{
    return m_errorString;
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
    req.append(HiByte(start));
    req.append(LoByte(start));
    req.append(HiByte(count));
    req.append(LoByte(count));
    quint16 crc = CalculateCRC16(req.data(), 6);
    req.append(LoByte(crc));
    req.append(HiByte(crc));
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
    crc = MakeWord(response[response.length()-1], response[response.length()-2]);
    if (crc != CalculateCRC16(response.data(), response.length()-2)) {
        m_errorString = "Ошибка контрольной суммы.";
        return false;
    }
    if (response.data()[0] != m_address) {
        m_errorString = "Неправильный адрес устройства в ответе.";
        return false;
    }
    QString error;
    if (response.data()[1] & 0x80) {
        switch (response.data()[2]) {
        case 0x01:
            error = "Принятый код функции не может быть обработан.";
            break;
        case 0x02:
            error = "Адрес данных, указанный в запросе, недоступен.";
            break;
        case 0x03:
            error = "Значение, содержащееся в поле данных запроса, является недопустимой величиной.";
            break;
        case 0x04:
            error = "Невосстанавливаемая ошибка имела место, пока ведомое устройство пыталось выполнить затребованное действие.";
            break;
        case 0x05:
            error = "Ведомое устройство приняло запрос и обрабатывает его, но это требует много времени.";
            break;
        case 0x06:
            error = "Ведомое устройство занято обработкой команды.";
            break;
        case 0x07:
            error = "Ведомое устройство не может выполнить программную функцию, заданную в запросе.";
            break;
        case 0x08:
            error = "Ведомое устройство при чтении расширенной памяти обнаружило ошибку паритета.";
            break;
        case 0x10:
            error = "Шлюз неправильно настроен или перегружен запросами.";
            break;
        case 0x11:
            error = "Slave устройства нет в сети или от него нет ответа.";
            break;
        default:
            error = "Неизвестная ошибка.";
        }
        m_errorString = "Ошибка Modbus: " + error;
        return false;
    }
    if (response.data()[1] != 0x03) {
        m_errorString = "Неправильный код функции в ответе.";
        return false;
    }
    int data_count = response[2];
    if (data_count != count*2) {
        m_errorString = "Неверная длина ответа.";
        return false;
    }
    memcpy(result, response.data()+3, data_count);
    m_errorString = NOERROR;
    return true;
}

bool Device::writeHoldingRegisters(quint16 start, quint16 count, char* data)
{
    if (!m_pPort->isOpen()) {
        m_errorString = "Соединение не установлено";
        return false;
    }
    QByteArray req;
    req.append(m_address);
    req.append(0x10);
    req.append(HiByte(start));
    req.append(LoByte(start));
    req.append(HiByte(count));
    req.append(LoByte(count));
    req.append(count*2);
    req.append(data);
    quint16 crc = CalculateCRC16(req.data(), req.size());
    req.append(LoByte(crc));
    req.append(HiByte(crc));
    if (!m_pPort->write(req.data(), req.size())) {
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
    crc = ((quint16)(response[response.length()-1]) << 8) + response[response.length()-2];
    if (crc != CalculateCRC16(response.data(), response.length()-2)) {
        m_errorString = "Ошибка контрольной суммы.";
        return false;
    }
    if (response.data()[0] != m_address) {
        m_errorString = "Неправильный адрес устройства в ответе.";
        return false;
    }
    QString error;
    if (response.data()[1] & 0x80) {
        switch (response.data()[2]) {
        case 0x01:
            error = "Принятый код функции не может быть обработан.";
            break;
        case 0x02:
            error = "Адрес данных, указанный в запросе, недоступен.";
            break;
        case 0x03:
            error = "Значение, содержащееся в поле данных запроса, является недопустимой величиной.";
            break;
        case 0x04:
            error = "Невосстанавливаемая ошибка имела место, пока ведомое устройство пыталось выполнить затребованное действие.";
            break;
        case 0x05:
            error = "Ведомое устройство приняло запрос и обрабатывает его, но это требует много времени.";
            break;
        case 0x06:
            error = "Ведомое устройство занято обработкой команды.";
            break;
        case 0x07:
            error = "Ведомое устройство не может выполнить программную функцию, заданную в запросе.";
            break;
        case 0x08:
            error = "Ведомое устройство при чтении расширенной памяти обнаружило ошибку паритета.";
            break;
        case 0x10:
            error = "Шлюз неправильно настроен или перегружен запросами.";
            break;
        case 0x11:
            error = "Slave устройства нет в сети или от него нет ответа.";
            break;
        default:
            error = "Неизвестная ошибка.";
        }
        m_errorString = "Ошибка Modbus: " + error;
        return false;
    }
    if (response.data()[1] != 0x10) {
        m_errorString = "Неправильный код функции в ответе.";
        return false;
    }
    quint16 test = ((quint16)(response[2]) << 8) + response[3];
    if (test != start) {
        m_errorString = "Несовпадение стартового адреса в ответе.";
        return false;
    }
    test = ((quint16)(response[4]) << 8) + response[5];
    if (test != count) {
        m_errorString = "Несовпадение количества записанных регистров.";
        return false;
    }
    return true;
}

bool Device::executeCommand(quint16 *cmdData, quint16 cmdSize)
{
    if (!writeHoldingRegisters(0x4000, cmdSize, (char *)cmdData)) {
        return false;
    }
    delay(250);
    int tryCount = 3000;
    quint16 res;
    while (--tryCount)
    {
        if (!readHoldingRegisters(0x5000, 1, (char *)&res)) {
            return false;
        }
        if (res == 0) break;
        if (res == 0xFFFF) {
            m_errorString = "Ошибка устройства: неверный код операции";
            return false;
        }
        if (res == 0xFFFE) {
            m_errorString = "Ошибка устройства: нет связи по внутреннему каналу";
            return false;
        }
        delay(100);
    }
    if (!tryCount) {
        m_errorString = "Команда не выполнена, нет подтверждения от устройства";
        return false;
    }
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

bool Device::putConfig(Device::TDeviceConf *devConf)
{
    for (int i = 0; i < 32; ++i)
            if (!writeHoldingRegisters(0x1000+i*10, 0x000A, (char *)devConf+i*10)){
                return false;
            }
    if (!writeHoldingRegisters(0x1140, 0x0030, (char *)devConf + 0x0140))
    {
        return false;
    }
    return true;
}

bool Device::saveConfigToEEPROM()
{
    quint16 cmd = ccPutConfig;
    return executeCommand(&cmd, 1);
}
