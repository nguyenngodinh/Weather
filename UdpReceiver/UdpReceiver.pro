TEMPLATE = app
CONFIG += console c++11 qt thread debug
CONFIG -= app_bundle


QT +=  core network

SOURCES += main.cpp \
    receiver.cpp \
    receiverthread.cpp

HEADERS += \
    receiver.h \
    receiverthread.h

