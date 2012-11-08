#-------------------------------------------------
#
# Project created by QtCreator 2012-09-12T13:23:39
#
#-------------------------------------------------

QT       += core gui network webkit

LIBS = -lboost_system -lmsgpack -lm

TARGET = Code-A-Client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    nm.cpp \
    game.cpp \
    mainpage.cpp \
    mage.cpp \
    gameview.cpp

HEADERS  += mainwindow.h \
    nm.h \
    game.h \
    mainpage.h \
    mage.h \
    gameview.h

FORMS    += mainwindow.ui \
    mainpage.ui
