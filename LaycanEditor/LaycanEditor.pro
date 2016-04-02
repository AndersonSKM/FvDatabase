#-------------------------------------------------
#
# Project created by QtCreator 2016-04-02T15:35:52
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LaycanEditor
TEMPLATE = app


SOURCES += main.cpp\
        laycaneditor.cpp \
    dlgopenfile.cpp

HEADERS  += laycaneditor.h \
    dlgopenfile.h

FORMS    += laycaneditor.ui \
    dlgopenfile.ui
