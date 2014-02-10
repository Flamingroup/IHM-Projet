#-------------------------------------------------
#
# Project created by QtCreator 2013-11-05T06:44:43
#
#-------------------------------------------------






QT += core gui
TARGET = IHM
TEMPLATE = app


# Libraries inclusions

    # QWT Library
    CONFIG += qwt
    #CONFIG += extserialport

    # QEXTSERIALPORT Library
    include(3rdparty/qextserialport/src/qextserialport.pri)


SOURCES += main.cpp\
        mainwindow.cpp \
    portselection.cpp \
    plot.cpp \
    serialport.cpp \
    wheatstoneplot.cpp \
    kalmanplot.cpp

HEADERS  += mainwindow.h \
    portselection.h \
    plot.h \
    serialport.h \
    wheatstoneplot.h \
    kalmanplot.h

