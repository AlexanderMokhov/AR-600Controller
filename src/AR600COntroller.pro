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
CONFIG += qt c++11 thread

SOURCES += main.cpp\
    Widgets/ConnectConfigDialog.cpp \
    Widgets/DeviceLogWidget.cpp \
    Widgets/MotorTableWidget.cpp \
    Widgets/SensorTableWidget.cpp \
    Widgets/MotorControlWidget.cpp \
    Widgets/CommandControlWidget.cpp \
    Widgets/PowerControlWidget.cpp \
    Widgets/CommandFilesWidget.cpp \
    Models/CommandTableModel.cpp \
    Models/MotorTableModel.cpp \
    Models/SensorTableModel.cpp \
    Buffers/BufferController.cpp \
    Buffers/BufferReceive.cpp \
    Buffers/BufferSend.cpp \
    Connection/Receiver.cpp \
    Connection/Sender.cpp \
    Devices/Device.cpp \
    Devices/Motor.cpp \
    Devices/Sensor.cpp \
    Libs/TinyXML/tinystr.cpp \
    Libs/TinyXML/tinyxml.cpp \
    Libs/TinyXML/tinyxmlerror.cpp \
    Libs/TinyXML/tinyxmlparser.cpp \
    Management/ConfigController.cpp \
    Management/DeviceLogController.cpp \
    Management/Logger.cpp \
    Management/MoveController.cpp \
    Management/Mover.cpp \
    MainWindow.cpp \
    Management/MoveCorrector.cpp

HEADERS  += \
    Widgets/ConnectConfigDialog.h \
    Widgets/DeviceLogWidget.h \
    Widgets/MotorTableWidget.h \
    Widgets/SensorTableWidget.h \
    Widgets/MotorControlWidget.h \
    Widgets/CommandControlWidget.h \
    Widgets/PowerControlWidget.h \
    Widgets/CommandFilesWidget.h \
    Models/CommandTableModel.h \
    Models/MotorTableModel.h \
    Models/SensorTableModel.h \
    Buffers/BufferController.h \
    Buffers/BufferReceive.h \
    Buffers/BufferSend.h \
    Connection/Receiver.h \
    Connection/Sender.h \
    Devices/Device.h \
    Devices/Motor.h \
    Devices/Sensor.h \
    Libs/TinyXML/tinystr.h \
    Libs/TinyXML/tinyxml.h \
    Management/ConfigController.h \
    Management/DeviceLogController.h \
    Management/Logger.h \
    Management/MoveController.h \
    Management/Mover.h \
    MainWindow.h \
    Buffers/BufferDefinition.h \
    Management/MoveCorrector.h

FORMS    += \
    Widgets/ConnectConfigDialog.ui \
    Widgets/DeviceLogWidget.ui \
    Widgets/SensorTableWidget.ui \
    Widgets/MotorTableWidget.ui \
    Widgets/MotorControlWidget.ui \
    Widgets/CommandControlWidget.ui \
    Widgets/PowerControlWidget.ui \
    Widgets/CommandFilesWidget.ui \
    MainWindow.ui

win32 {
    RC_FILE += resource.rc
    OTHER_FILES += resource.rc
}

RESOURCES += \
    MyResources.qrc
