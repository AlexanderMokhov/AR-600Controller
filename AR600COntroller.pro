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
CONFIG += c++11


SOURCES += main.cpp\
    CommandController.cpp \
    TinyXML/tinystr.cpp \
    TinyXML/tinyxml.cpp \
    TinyXML/tinyxmlerror.cpp \
    TinyXML/tinyxmlparser.cpp \
    BufferController.cpp \
    ConfigController.cpp \
    ThreadReceive.cpp \
    ThreadSend.cpp \
    AR600MainWindow.cpp \
    Widgets/ConnectConfigDialog.cpp \
    Device.cpp \
    Sensor.cpp \
    SensorTableModel.cpp \
    Command.cpp \
    ReadBuffer.cpp \
    WriteBuffer.cpp \
    Motor.cpp \
    Widgets/DeviceLogWidget.cpp \
    MotorTableModel.cpp \
    Widgets/MotorTableWidget.cpp \
    Widgets/SensorTableWidget.cpp \
    Widgets/MotorControlWidget.cpp \
    Widgets/CommandControlWidget.cpp \
    DeviceLogController.cpp \
    Widgets/PowerControlWidget.cpp

HEADERS  += \
    CommandController.h \
    TinyXML/tinystr.h \
    TinyXML/tinyxml.h \
    BufferController.h \
    ConfigController.h \
    ThreadReceive.h \
    ThreadSend.h \
    AR600MainWindow.h \
    Widgets/ConnectConfigDialog.h \
    Device.h \
    Sensor.h \
    SensorTableModel.h \
    Command.h \
    ReadBuffer.h \
    WriteBuffer.h \
    ADefinition.h \
    Motor.h \
    Widgets/DeviceLogWidget.h \
    MotorTableModel.h \
    Widgets/MotorTableWidget.h \
    Widgets/SensorTableWidget.h \
    Widgets/MotorControlWidget.h \
    Widgets/CommandControlWidget.h \
    DeviceLogController.h \
    Widgets/PowerControlWidget.h

FORMS    += \
    AR600MainWindow.ui \
    Widgets/ConnectConfigDialog.ui \
    Widgets/DeviceLogWidget.ui \
    Widgets/SensorTableWidget.ui \
    Widgets/MotorTableWidget.ui \
    Widgets/MotorControlWidget.ui \
    Widgets/CommandControlWidget.ui \
    Widgets/PowerControlWidget.ui

win32 {
    RC_FILE += resource.rc
    OTHER_FILES += resource.rc
}
