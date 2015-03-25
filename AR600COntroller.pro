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
    ChannelListitem.cpp \
    DriverCommand.cpp \
    CommandController.cpp

HEADERS  += \
    MBRead.h \
    MBWrite.h \
    AR600Controller.h \
    qcustomplot.h \
    dataplot.h \
    ChannelListitem.h \
    DriverCommand.h \
    CommandController.h

FORMS    += \
    AR600Controller.ui
