#include <QApplication>
#include "settings.h"

Settings* Settings::m_inst = 0;

Settings* Settings::instance()
{
    if (!m_inst) {
        m_inst = new Settings();
        m_inst->init();
    }
    return m_inst;
}

void Settings::init()
{
    s = new QSettings(QApplication::applicationDirPath() + "/settings.ini", QSettings::IniFormat);
    s->beginGroup("connection");
    cs.port = s->value("port").toString();
    cs.address = s->value("address", 1).toUInt();
    cs.requestTimeout = s->value("requestTimeout", 500).toUInt();
    cs.packetTimeout = s->value("packetTimeout", 50).toUInt();
    s->endGroup();
}

void Settings::save()
{
    s->beginGroup("connection");
    s->setValue("port", cs.port);
    s->setValue("address", cs.address);
    s->setValue("requestTimeout", cs.requestTimeout);
    s->setValue("packetTimeout", cs.packetTimeout);
    s->endGroup();
    s->sync();
}
