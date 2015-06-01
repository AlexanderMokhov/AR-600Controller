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
    MBRead.cpp \
    MBWrite.cpp \
    DriverCommand.cpp \
    CommandController.cpp \
    TinyXML/tinystr.cpp \
    TinyXML/tinyxml.cpp \
    TinyXML/tinyxmlerror.cpp \
    TinyXML/tinyxmlparser.cpp \
    ChannelListItem.cpp \
    DriverSettingsItem.cpp \
    ChannelTableModel.cpp \
    Widgets/DriverControllerWidget.cpp \
    BufferController.cpp \
    Widgets/CommandControllerWidget.cpp \
    ConfigController.cpp \
    Widgets/ChannelTableWidget.cpp \
    Widgets/DriverLogWidget.cpp \
    Widgets/PowerWidget.cpp \
    ThreadReceive.cpp \
    ThreadSend.cpp \
    AR600MainWindow.cpp \
    Widgets/ConnectConfigDialog.cpp \
    Device.cpp \
    Driver.cpp \
    FootSensor.cpp \
    GyroscopeSensor.cpp \
    Widgets/SensorsWidget.cpp \
    Sensor.cpp \
    SensorTableModel.cpp \
    SensorListItem.cpp \
    PreciseTimer.cpp \
    UDPLogController.cpp

HEADERS  += \
    MBRead.h \
    MBWrite.h \
    DriverCommand.h \
    CommandController.h \
    TinyXML/tinystr.h \
    TinyXML/tinyxml.h \
    ChannelListItem.h \
    DriverSettingsItem.h \
    ChannelTableModel.h \
    Widgets/DriverControllerWidget.h \
    BufferController.h \
    Widgets/CommandControllerWidget.h \
    ConfigController.h \
    Widgets/ChanneTableWidget.h \
    Widgets/DriverLogWidget.h \
    Widgets/PowerWidget.h \
    ThreadReceive.h \
    ThreadSend.h \
    AR600MainWindow.h \
    Widgets/ConnectConfigDialog.h \
    Device.h \
    Driver.h \
    FootSensor.h \
    GyroscopeSensor.h \
    Widgets/SensorsWidget.h \
    Sensor.h \
    SensorTableModel.h \
    SensorListItem.h \
    PreciseTimer.h \
    UDPLogController.h

FORMS    += \
    Widgets/DriverControllerWidget.ui \
    Widgets/CommandControllerWidget.ui \
    Widgets/ChannelTableWidget.ui \
    Widgets/DriverLogWidget.ui \
    Widgets/PowerWidget.ui \
    AR600MainWindow.ui \
    Widgets/ConnectConfigDialog.ui \
    Widgets/SensorsWidget.ui

win32 {
    RC_FILE += resource.rc
    OTHER_FILES += resource.rc
}
