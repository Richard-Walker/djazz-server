#-------------------------------------------------
#
# Project created by QtCreator 2014-01-17T13:15:50
#
#-------------------------------------------------

QT       -= core gui

TARGET = pirlib2
TEMPLATE = lib
unix:linux:QMAKE_CXXFLAGS = -std=c++0x -Wall
DEFINES += PIRLIB2_LIBRARY

SOURCES += \
    pirlib2.cpp \
    pt.c \
    pir.cpp \
    manager.cpp \
    sendirparser.cpp \
    iparser.cpp \
    irreceiveparser.cpp \
    buttonparser.cpp \
    irsend.cpp \
    boolsig.cpp \
    ipir.cpp \
    irlearnparser.cpp


win32:SOURCES+=hid.c
unix:linux:SOURCES+=hidlinux.c
unix:macx:SOURCES+=hidmac.c

win32:LIBS+=-lUser32 -lPsapi -lhid -lsetupapi
unix:linux:LIBS+=-lusb-1.0 -lrt -ludev
unix:macx:LIBS+=-framework IOKit -framework CoreFoundation

HEADERS += pirlib2.h\
    pirlib2_global.h \
    pt.h \
    pir.h \
    manager.h \
    sendirparser.h \
    iparser.h \
    irreceiveparser.h \
    buttonparser.h \
    irsend.h \
    boolsig.h \
    ipir.h \
    irlearnparser.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG(debug, debug|release) {
    OBJECTS_DIR = ./debug
}
else {
    OBJECTS_DIR = ./release
}

DESTDIR = ../bin/
