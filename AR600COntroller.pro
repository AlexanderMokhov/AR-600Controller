#-------------------------------------------------
#
# Project created by QtCreator 2014-12-16T11:13:47
#
#-------------------------------------------------

QT       += core\
            gui \
            network \
            printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AR600COntroller
TEMPLATE = app


SOURCES += main.cpp\
    MBRead.cpp \
    MBWrite.cpp \
    AR600Controller.cpp \
    qcustomplot.cpp \
    dataplot.cpp \
    DriverCommand.cpp \
    CommandController.cpp \
    TinyXML/tinystr.cpp \
    TinyXML/tinyxml.cpp \
    TinyXML/tinyxmlerror.cpp \
    TinyXML/tinyxmlparser.cpp \
    AR600ControllerConf.cpp \
    ChannelListItem.cpp \
    DriverSettingsItem.cpp \
    ChannelTableModel.cpp \
    DriverControllerWidget.cpp \
    bufferController.cpp \
    logcontroller.cpp

HEADERS  += \
    MBRead.h \
    MBWrite.h \
    AR600Controller.h \
    qcustomplot.h \
    dataplot.h \
    DriverCommand.h \
    CommandController.h \
    TinyXML/tinystr.h \
    TinyXML/tinyxml.h \
    AR600ControllerConf.h \
    ChannelListItem.h \
    DriverSettingsItem.h \
    ChannelTableModel.h \
    DriverControllerWidget.h \
    BufferController.h \
    logcontroller.h

FORMS    += \
    AR600Controller.ui \
    DriverControllerWidget.ui
