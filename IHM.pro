#-------------------------------------------------
#
# Project created by QtCreator 2013-11-05T06:44:43
#
#-------------------------------------------------






QT += core gui
TARGET = IHM
TEMPLATE = app

QMAKE_CXXFLAGS +=   -std=c++11

# Libraries inclusions

    # QWT Library
    CONFIG += qwt
    CONFIG += extserialport
    #include ( /usr/local/qwt-6.1.0/features/qwt.prf )
    # QEXTSERIALPORT Library
    include(3rdparty/qextserialport/src/qextserialport.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    portselection.cpp \
    plot.cpp

HEADERS  += mainwindow.h \
    portselection.h \
    plot.h

