#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QSerialPort>
#include <QtSerialBus/QModbusDataUnit>
#include <QtSerialBus/QModbusRtuSerialMaster>
#include <QQueue>
#include <QThread>

class Device : public QObject
{
// Статусные признаки
const quint32 ST_SWITCH		= 0x00000001;
const quint32 ST_FAILURE		= 0x00000002;
const quint32 ST_SIGNALIZATOR	= 0x00000004;
const quint32 ST_VALVE		= 0x00000008;
const quint32 ST_VALVE_STATE	= 0x00000010;
const quint32 ST_ACTIVE		= 0x00000040;
const quint32 ST_NOT_RELIABLE	= 0x00000100;
const quint32 ST_IMITATION	= 0x00000200;
const quint32 ST_NO_SIGNAL	= 0x00000400;
const quint32 ST_EX_RATE		= 0x00000800;
const quint32 ST_EX_COMP		= 0x00001000;
const quint32 ST_AIR_CONSUM	= 0x00002000;
const quint32 ST_EX_LO_RANGE	= 0x00004000;
const quint32 ST_EX_HI_RANGE	= 0x00008000;
const quint32 ST_EX_LO_LIM1 	= 0x00010000;
const quint32 ST_EX_HI_LIM1 	= 0x00020000;
const quint32 ST_EX_LO_LIM2 	= 0x00010000;
const quint32 ST_EX_HI_LIM2 	= 0x00020000;

enum {iChannelNumb = 16};

struct TChannelInfo {
    // Статусные признаки
    quint32		m_dwState;
    // Измеренное значение
    float		m_fsValue;
};

struct TDeviceInfo {
    // Код устройства
    char			m_chDeviceId[32];
    // Обобщенное состояние устройства
    quint8			m_byDeviceStatus;
    // Признаки обобщенной неисправности модулей
    quint8			m_byAllModErrors;
    // Признаки обобщенной неисправности каналов
    quint16			m_wAllChnErrors;
    // Текущее время в устройстве
    quint32			m_dwCurrTime;
    // Информация по основным и альтернативным каналам
    TChannelInfo	m_cInfo[2][iChannelNumb];
};

// Конфигурация измерительного канала
struct TChannelConfig {
    // Код размерности
    quint16        m_wUOMCode;
    // Код типа датчика
    quint16        m_wDetCode;
    // Максимально допустимая скорость счета
    float       m_fMaxRate;
    // Коэффициент масштабирования
    float       m_fScaleCoeff;
    // Собственный фон
    float       m_fBackground;
    // "Мертвое" время
    float       m_fDeadTime;
    // Нижняя граница диапазона измерения
    float       m_fMinValue;
    // Верхняя граница диапазона измерения
    float       m_fMaxValue;
    // Период контроля работоспособности
    quint16        m_wCheckTime;
    // Максимальное время измерения
    quint16        m_wMaximTime;
    // Порог 1
    float       m_fThreshold1;
    // Порог 2
    float       m_fThreshold2;
};

// Конфигурация устройства
struct TDeviceConf {
    // Конфигурация измерительных каналов
    TChannelConfig		ChanConf[iChannelNumb];
    // Конфигурация сигнализаторов
    quint16                SignConf[iChannelNumb];
    // Конфигурация "сухих" контактов
    quint16                ContConf[iChannelNumb];
    // Идентификатор устройства
    char                szDeviceId[32];
    // Адрес в сети
    quint16                wAddress;
};

typedef float EX_CONST[2][iChannelNumb];

typedef struct {
    quint8	byNumb;
    float	faCoef[6];
} TERM_COEFF;

enum OperationCode {
    NONE,
    CONNECT,
    READCONFIG,
    WRITECONFIG,
    READINFO
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////

    Q_OBJECT
public:
    explicit Device(QObject *parent = nullptr);
    ~Device();
    void Connect(QString port, quint8 address);
    void sendReadConfRequest();
    void sendReadInfoRequest();
    TDeviceConf currentConfig();
    TDeviceInfo currentInfo();
    void setCurrentConfig(const TDeviceConf&);
    bool isConnected();
private:
    void commandFunc();
    QModbusDataUnit makeReadConfRequest();
    QModbusDataUnit makeWriteConfRequest(TDeviceConf conf);
    QModbusDataUnit makeReadInfoRequest();
    QModbusDataUnit makeConnectRequest();
    void processReadInfo();
    void processReadConfig();
    void processWriteConfig();
    bool m_connected = false;
    quint8 m_address = 0;
    quint8 m_failedRequestCount = 0;
    OperationCode m_currentOperation = NONE;
    QModbusRtuSerialMaster *m_pDevice;
    QModbusReply *m_ModbusReply;
    TDeviceConf m_currentConfig;
    TDeviceInfo m_currentInfo;
    QQueue<OperationCode> m_commandQueue;
    QThread *m_pCommandThread;
private slots:
    void onModbusReplyFinished();
    void onModbusReplyErrorOccured(QModbusDevice::Error error);

signals:
    void connectSuccess(QString devName);
    void connectFail(QString message);
    void onDeviceConfRequestSuccess();
    void onDeviceConfRequestError();
    void onDeviceInfoRequestSuccess();
    void onDeviceInfoRequestError();
};

#endif // DEVICE_H
