#-------------------------------------------------
#
# Project created by QtCreator 2018-03-03T07:19:38
#
#-------------------------------------------------

QT       += core gui opengl
CONFIG   += C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = BanzaiTest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    figures/circle.cpp \
    figures/figure.cpp \
    figures/square.cpp \
    figures/triangle.cpp \
    glviewer.cpp \
    outlinermodel.cpp

HEADERS  += mainwindow.h \
    figures/circle.h \
    figures/figure.h \
    figures/square.h \
    figures/triangle.h \
    figures/figures.h \
    glviewer.h \
    outlinermodel.h

FORMS    += mainwindow.ui

DISTFILES += \
    changelog.txt
