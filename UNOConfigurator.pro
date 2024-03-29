QT       += core gui serialport serialbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    channelconfigwidget.cpp \
    channelinfowidget.cpp \
    connectform.cpp \
    device.cpp \
    main.cpp \
    mainwindow.cpp \
    settings.cpp

HEADERS += \
    channelconfigwidget.h \
    channelinfowidget.h \
    connectform.h \
    device.h \
    mainwindow.h \
    util.h \
    settings.h

FORMS += \
    channelconfigwidget.ui \
    channelinfowidget.ui \
    connectform.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
