#-------------------------------------------------
#
# Project created by QtCreator 2015-07-29T22:28:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HelloChess
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    iboard.cpp \
    ifigure.cpp \
    turnhistory.cpp \
    test_main.cpp \
    test_pointer_class.cpp \
    chessboard.cpp

HEADERS  += mainwindow.h \
    iboard.h \
    ifigure.h \
    turnhistory.h \
    test_pointer_class.h \
    chessboard.h \
    ifigurecreator.h

FORMS    += mainwindow.ui

DISTFILES += \
    tests
