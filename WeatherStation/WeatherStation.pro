#-------------------------------------------------
#
# Project created by QtCreator 2017-09-16T20:19:31
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WeatherStation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    weatherstation.cpp

HEADERS  += mainwindow.h \
    weatherstation.h

FORMS    += mainwindow.ui
