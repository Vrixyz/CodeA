#-------------------------------------------------
#
# Project created by QtCreator 2012-09-12T13:23:39
#
#-------------------------------------------------

QT       += core gui network

LIBS = -lboost_system -lmsgpack

TARGET = Code-A-Client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    nm.cpp \
    game.cpp \
    serverselection.cpp

HEADERS  += mainwindow.h \
    nm.h \
    game.h \
    serverselection.h

FORMS    += mainwindow.ui \
    serverselection.ui
