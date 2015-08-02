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
CONFIG += qt c++11 thread debug


SOURCES += main.cpp\
    TinyXML/tinystr.cpp \
    TinyXML/tinyxml.cpp \
    TinyXML/tinyxmlerror.cpp \
    TinyXML/tinyxmlparser.cpp \
    BufferController.cpp \
    ConfigController.cpp \
    AR600MainWindow.cpp \
    Widgets/ConnectConfigDialog.cpp \
    Device.cpp \
    Sensor.cpp \
    Motor.cpp \
    Widgets/DeviceLogWidget.cpp \
    Widgets/MotorTableWidget.cpp \
    Widgets/SensorTableWidget.cpp \
    Widgets/MotorControlWidget.cpp \
    Widgets/CommandControlWidget.cpp \
    DeviceLogController.cpp \
    Widgets/PowerControlWidget.cpp \
    Widgets/CommandFilesWidget.cpp \
    CommandTableModel.cpp \
    Receiver.cpp \
    Sender.cpp \
    Logger.cpp \
    Mover.cpp \
    MoveController.cpp \
    BufferSend.cpp \
    BufferReceive.cpp \
    TableModelMotor.cpp \
    TableModelSensor.cpp

HEADERS  += \
    TinyXML/tinystr.h \
    TinyXML/tinyxml.h \
    BufferController.h \
    ConfigController.h \
    AR600MainWindow.h \
    Widgets/ConnectConfigDialog.h \
    Device.h \
    Sensor.h \
    ADefinition.h \
    Motor.h \
    Widgets/DeviceLogWidget.h \
    Widgets/MotorTableWidget.h \
    Widgets/SensorTableWidget.h \
    Widgets/MotorControlWidget.h \
    Widgets/CommandControlWidget.h \
    DeviceLogController.h \
    Widgets/PowerControlWidget.h \
    Widgets/CommandFilesWidget.h \
    CommandTableModel.h \
    Receiver.h \
    Sender.h \
    Logger.h \
    Mover.h \
    MoveController.h \
    BufferSend.h \
    BufferReceive.h \
    TableModelMotor.h \
    TableModelSensor.h

FORMS    += \
    AR600MainWindow.ui \
    Widgets/ConnectConfigDialog.ui \
    Widgets/DeviceLogWidget.ui \
    Widgets/SensorTableWidget.ui \
    Widgets/MotorTableWidget.ui \
    Widgets/MotorControlWidget.ui \
    Widgets/CommandControlWidget.ui \
    Widgets/PowerControlWidget.ui \
    Widgets/CommandFilesWidget.ui

win32 {
    RC_FILE += resource.rc
    OTHER_FILES += resource.rc
}
