#-------------------------------------------------
#
# Project created by QtCreator 2015-12-18T21:20:25
#
#-------------------------------------------------

QT       += core websockets

QT       -= gui

TARGET = Fig
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11

TEMPLATE = app


SOURCES += main.cpp echoserver.cpp
HEADERS += \
    echoserver.h
