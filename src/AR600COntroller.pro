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
    Models/CommandTableModel.cpp \
    Models/MotorTableModel.cpp \
    Models/SensorTableModel.cpp \
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
    Management/MoveCorrector.cpp \
    Management/RecordController.cpp \
    Management/Recorder.cpp \
    Libs/Sockets/Socket.cpp \
    Widgets/StdMovesWidget.cpp \
    Connection/ConsoleReceiver.cpp \
    Management/SettingsStorage.cpp \
    Management/MovesStorage.cpp \
    Devices/PIDGates.cpp \
    Libs/QCustomPlot/qcustomplot.cpp \
    Connection/FrundTransiver.cpp \
    Widgets/LogWidget.cpp \
    Management/FileLoader.cpp \
    Management/LogMaster.cpp \
    Packets/FPacketRecv.cpp \
    Packets/FPacketSend.cpp \
    Packets/ARPacketSend.cpp \
    Packets/ARPacketRecv.cpp \
    Packets/ARPacketManager.cpp \
    Widgets/PlotW.cpp \
    Widgets/ControlWidgets/AdditionalControlW.cpp \
    Widgets/ControlWidgets/ConnectionControlW.cpp \
    Widgets/ControlWidgets/MotionControlW.cpp \
    Widgets/ControlWidgets/MotorsControlW.cpp \
    Widgets/ControlWidgets/PowerControlW.cpp \
    Widgets/ControlWidgets/RecordControlW.cpp \
    Widgets/DialogWidgets/ConnectionSetupDialog.cpp \
    Widgets/DialogWidgets/SetLimitsDialog.cpp \
    Widgets/GridWidgets/MotorsGridW.cpp \
    Widgets/GridWidgets/MovesGridW.cpp \
    Widgets/GridWidgets/SensorsGridW.cpp \
    Widgets/MainWindow.cpp \
    Management/MotorController.cpp \
    Packets/FPacketManager.cpp

HEADERS  += \
    Models/CommandTableModel.h \
    Models/MotorTableModel.h \
    Models/SensorTableModel.h \
    Connection/Receiver.h \
    Connection/Sender.h \
    Devices/Device.h \
    Devices/Motor.h \
    Devices/Sensor.h \
    Libs/TinyXML/tinystr.h \
    Libs/TinyXML/tinyxml.h \
    Management/MoveController.h \
    Management/Mover.h \
    Management/MoveCorrector.h \
    Management/RecordController.h \
    Management/Recorder.h \
    Libs/Sockets/Socket.h \
    Widgets/StdMovesWidget.h \
    Connection/ConsoleReceiver.h \
    Management/SettingsStorage.h \
    Management/MovesStorage.h \
    Devices/PIDGates.h \
    Libs/QCustomPlot/qcustomplot.h \
    Connection/FrundTransiver.h \
    Management/FileLoader.h \
    Management/LogMaster.h \
    Packets/ARPacketDefinition.h \
    Packets/ARPacketRecv.h \
    Packets/ARPacketSend.h \
    Packets/ARPacketManager.h \
    Packets/FPacketRecv.h \
    Packets/FPacketSend.h \
    Widgets/PlotW.h \
    Widgets/LogOutputW.h \
    Widgets/ControlWidgets/AdditionalControlW.h \
    Widgets/ControlWidgets/ConnectionControlW.h \
    Widgets/ControlWidgets/MotionControlW.h \
    Widgets/ControlWidgets/MotorsControlW.h \
    Widgets/ControlWidgets/PowerControlW.h \
    Widgets/ControlWidgets/RecordControlW.h \
    Widgets/DialogWidgets/ConnectionSetupDialog.h \
    Widgets/DialogWidgets/SetLimitsDialog.h \
    Widgets/GridWidgets/MotorsGridW.h \
    Widgets/GridWidgets/MovesGridW.h \
    Widgets/GridWidgets/SensorsGridW.h \
    Widgets/MainWindow.h \
    Management/MotorController.h \
    Packets/FPacketDefinition.h \
    Packets/FPacketManager.h

FORMS    += \
    Widgets/MainWindow.ui \
    Widgets/StdMovesWidget.ui \
    Widgets/LogOutputW.ui \
    Widgets/PlotW.ui \
    Widgets/DialogWidgets/SetLimitsDialog.ui \
    Widgets/DialogWidgets/ConnectionSetupDialog.ui \
    Widgets/ControlWidgets/PowerControlW.ui \
    Widgets/ControlWidgets/ConnectionControlW.ui \
    Widgets/ControlWidgets/AdditionalControlW.ui \
    Widgets/ControlWidgets/MotorsControlW.ui \
    Widgets/ControlWidgets/MotionControlW.ui \
    Widgets/ControlWidgets/RecordControlW.ui \
    Widgets/GridWidgets/MotorsGridW.ui \
    Widgets/GridWidgets/MovesGridW.ui \
    Widgets/GridWidgets/SensorsGridW.ui

win32
{
    RC_FILE += resource.rc
    OTHER_FILES += resource.rc
    LIBS += -lws2_32
    LIBS += -lglu32 -lopengl32
}

RESOURCES += \
    MyResources.qrc
