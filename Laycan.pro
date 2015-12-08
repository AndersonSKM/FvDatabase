#-------------------------------------------------
#
# Project created by QtCreator 2015-10-10T10:52:08
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Laycan
TEMPLATE = app

SOURCES += lib/SQL.cpp \
    lib/tools.cpp \
    src/connection.cpp \
    src/databaseconfig.cpp \
    src/dictionary.cpp \
    src/dictxml.cpp \
    src/inifile.cpp \
    src/main.cpp

HEADERS  += lib/SQL.h \
    lib/tools.h \
    src/connection.h \
    src/databaseconfig.h \
    src/dictionary.h \
    src/dictxml.h \
    src/inifile.h

FORMS += src/databaseconfig.ui

RESOURCES += resources/Resources.qrc
