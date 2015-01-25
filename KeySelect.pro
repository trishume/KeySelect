#-------------------------------------------------
#
# Project created by QtCreator 2015-01-24T18:55:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KeySelect
TEMPLATE = app

LIBS += -L$$_PRO_FILE_PWD_/lib -lccv -framework Cocoa -L/usr/local/lib -lm -lblas -lpng -ljpeg -lfftw3 -lfftw3f -lpthread -framework Accelerate -framework ApplicationServices

SOURCES += main.cpp\
        debugwindow.cpp \
    textfinder.cpp \
    screensurface.cpp

HEADERS  += debugwindow.h \
    textfinder.h \
    include/ccv.h \
    screensurface.h \
    mousecontrol.h

FORMS    += debugwindow.ui

OBJECTIVE_SOURCES += \
    osxhacks.mm \
    mousecontrol.mm
