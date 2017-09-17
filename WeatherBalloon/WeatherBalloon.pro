#-------------------------------------------------
#
# Project created by QtCreator 2017-09-16T20:11:14
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WeatherBalloon
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    weatherballoon.cpp

HEADERS  += mainwindow.h \
    weatherballoon.h

FORMS    += mainwindow.ui
