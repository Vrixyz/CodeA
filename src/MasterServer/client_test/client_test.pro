#-------------------------------------------------
#
# Project created by QtCreator 2013-02-16T16:32:26
#
#-------------------------------------------------

QT       += core gui network

LIBS = -lmsgpack

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client_test
TEMPLATE = app


SOURCES +=      main.cpp \
                MyWindow.cpp \
                Network.cpp \
                Basic.cpp \
                AccWindow.cpp \
                Store.cpp \
                GamesWindow.cpp \
    ClassWindow.cpp

HEADERS +=      Network.h \
                MyWindow.h \ 
                AccWindow.h \
                Store.h \
                Define.h \
                GamesWindow.h \
    ClassWindow.h


FORMS    +=
