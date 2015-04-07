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
    DriverLogController.cpp \
    ConfigController.cpp \
    DataPlot.cpp \
    ChannelTableController.cpp \
    Widgets/ChannelTableWidget.cpp \
    qcustomplot.cpp

HEADERS  += \
    MBRead.h \
    MBWrite.h \
    AR600Controller.h \
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
    DriverLogController.h \
    ConfigController.h \
    DataPlot.h \
    ChannelTableController.h \
    Widgets/ChanneTableWidget.h \
    qcustomplot.h

FORMS    += \
    AR600Controller.ui \
    Widgets/DriverControllerWidget.ui \
    Widgets/CommandControllerWidget.ui \
    Widgets/ChannelTableWidget.ui

