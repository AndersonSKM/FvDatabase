#-------------------------------------------------
#
# Project created by QtCreator 2015-10-10T10:52:08
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FvDatabase
TEMPLATE = app


SOURCES += main.cpp\
        databaseconfig.cpp \
    tools/SQL.cpp \
    tools/tools.cpp \
    inifile.cpp

HEADERS  += databaseconfig.h \
    tools/SQL.h \
    tools/tools.h \
    inifile.h

FORMS    += databaseconfig.ui

RESOURCES += \
    resources/Resources.qrc
