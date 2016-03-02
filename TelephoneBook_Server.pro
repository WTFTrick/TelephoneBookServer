QT += core
QT -= gui
QT += network

TARGET = TelephoneBook_Server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp

HEADERS += \
    server.h

