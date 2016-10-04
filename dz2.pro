TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS += -std=c99 -fpermissive -g

SOURCES += main.c matrix.c

HEADERS += matrix.h

