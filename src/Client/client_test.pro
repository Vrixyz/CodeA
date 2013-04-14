#-------------------------------------------------
#
# Project created by QtCreator 2013-02-16T16:32:26
#
#-------------------------------------------------

QT       += core gui network webkit

LIBS = -lmsgpack

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

TARGET = client_test
TEMPLATE = app


SOURCES +=      GamesWindow.cpp \
                ClassWindow.cpp \
                AccWindow.cpp \
                MyWindow.cpp \
                SuWindow.cpp \
                MyItemLi.cpp \
                Network.cpp \
                Basic.cpp \
                Store.cpp \
                main.cpp \
                gameview.cpp \
                element.cpp \
                bullet.cpp \
                game.cpp \
                mage.cpp \
                unit.cpp \
                nm.cpp  \
                HudShooter.cpp \
                hudrts.cpp

HEADERS +=      GamesWindow.h \
                ClassWindow.h \
                AccWindow.h \
                MyWindow.h \
                SuWindow.h \
                MyItemLi.h \
                Network.h \
                Define.h \
                Store.h \
                element.h \
                bullet.h \
                gameview.h \
                game.h \
                mage.h \
                unit.h \
                nm.h \
                Achi.h \
                HudShooter.h \
                hudrts.h

