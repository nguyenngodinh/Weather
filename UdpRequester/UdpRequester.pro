TEMPLATE = app
CONFIG += console c++11 qt thread debug
CONFIG -= app_bundle

QT +=  core network

SOURCES += main.cpp \
    requester.cpp

HEADERS += \
    requester.h

