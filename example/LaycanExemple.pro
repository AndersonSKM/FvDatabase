#-------------------------------------------------
#
# Project created by QtCreator 2016-01-24T15:08:15
#
#-------------------------------------------------

QT += core
QT += gui
QT += sql

#lib Laycan
include(../src/Laycan.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Laycan
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp \
    connection.cpp \
    inifile.cpp \
    mainwindow.cpp \
    databaseconfig.cpp

HEADERS  += \
    databaseconfig.h \
    connection.h \
    inifile.h \
    inifile.h \
    mainwindow.h \
    databaseconfig.h

FORMS    += \
    mainwindow.ui \
    databaseconfig.ui

RESOURCES += \
    ../resources/Resources.qrc
