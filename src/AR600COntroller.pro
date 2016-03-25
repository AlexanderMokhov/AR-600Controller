#-------------------------------------------------
#
# Project created by QtCreator 2014-12-16T11:13:47
#
#-------------------------------------------------

QT       += core\
            gui \
            network \
            printsupport \
            opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AR600COntroller
TEMPLATE = app
CONFIG += qt c++11 thread

SOURCES += main.cpp\
    Widgets/ConnectConfigDialog.cpp \
    Widgets/MotorTableWidget.cpp \
    Widgets/SensorTableWidget.cpp \
    Widgets/MotorControlWidget.cpp \
    Models/CommandTableModel.cpp \
    Models/MotorTableModel.cpp \
    Models/SensorTableModel.cpp \
    Buffers/BufferController.cpp \
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
    Management/MoveController.cpp \
    Management/Mover.cpp \
    MainWindow.cpp \
    Management/MoveCorrector.cpp \
    Widgets/MoveControlWidget.cpp \
    Management/RecordController.cpp \
    Management/Recorder.cpp \
    Widgets/RecordWidget.cpp \
    Widgets/MoveFilesWidget.cpp \
    Widgets/PowerWidget.cpp \
    Libs/Sockets/Socket.cpp \
    Widgets/SetLimitsDialog.cpp \
    Widgets/StdMovesWidget.cpp \
    Connection/ConsoleReceiver.cpp \
    Management/SettingsStorage.cpp \
    Management/MovesStorage.cpp \
    Devices/PIDGates.cpp \
    Buffers/BufferRecv.cpp \
    Libs/QCustomPlot/qcustomplot.cpp \
    Widgets/PlotWidget.cpp \
    Widgets/modelWidget.cpp \
    Widgets/GLWidget.cpp \
    Connection/FrundTransiver.cpp

HEADERS  += \
    Widgets/ConnectConfigDialog.h \
    Widgets/MotorTableWidget.h \
    Widgets/SensorTableWidget.h \
    Widgets/MotorControlWidget.h \
    Models/CommandTableModel.h \
    Models/MotorTableModel.h \
    Models/SensorTableModel.h \
    Buffers/BufferController.h \
    Buffers/BufferSend.h \
    Connection/Receiver.h \
    Connection/Sender.h \
    Devices/Device.h \
    Devices/Motor.h \
    Devices/Sensor.h \
    Libs/TinyXML/tinystr.h \
    Libs/TinyXML/tinyxml.h \
    Management/MoveController.h \
    Management/Mover.h \
    MainWindow.h \
    Buffers/BufferDefinition.h \
    Management/MoveCorrector.h \
    Widgets/MoveControlWidget.h \
    Management/RecordController.h \
    Management/Recorder.h \
    Widgets/RecordWidget.h \
    Widgets/MoveFilesWidget.h \
    Widgets/PowerWidget.h \
    Libs/Sockets/Socket.h \
    Widgets/SetLimitsDialog.h \
    Widgets/StdMovesWidget.h \
    Connection/ConsoleReceiver.h \
    Management/SettingsStorage.h \
    Management/MovesStorage.h \
    Devices/PIDGates.h \
    Buffers/BufferRecv.h \
    Libs/QCustomPlot/qcustomplot.h \
    Widgets/PlotWidget.h \
    Widgets/modelWidget.h \
    Widgets/GLWidget.h \
    Connection/FrundTransiver.h

FORMS    += \
    Widgets/ConnectConfigDialog.ui \
    Widgets/SensorTableWidget.ui \
    Widgets/MotorTableWidget.ui \
    Widgets/MotorControlWidget.ui \
    MainWindow.ui \
    Widgets/MoveControlWidget.ui \
    Widgets/RecordWidget.ui \
    Widgets/MoveFilesWidget.ui \
    Widgets/PowerWidget.ui \
    Widgets/SetLimitsDialog.ui \
    Widgets/StdMovesWidget.ui \
    Widgets/PlotWidget.ui \
    Widgets/modelWidget.ui

win32 {
    RC_FILE += resource.rc
    OTHER_FILES += resource.rc
    LIBS += -lws2_32
    LIBS += -lglu32 -lopengl32
}

RESOURCES += \
    MyResources.qrc
