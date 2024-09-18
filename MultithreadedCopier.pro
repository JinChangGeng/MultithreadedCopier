#-------------------------------------------------
#
# Project created by QtCreator 2024-09-16T13:58:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MultithreadedCopier
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    threadcopy.cpp

HEADERS  += dialog.h \
    threadcopy.h

FORMS    += dialog.ui
QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    res.qrc
