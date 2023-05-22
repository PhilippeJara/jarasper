#-------------------------------------------------
#
# Project created by QtCreator 2017-08-17T17:32:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jarasper
TEMPLATE = app
CONFIG += c++14
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#QMAKE_CFLAGS += `ecl-config --cflags`
#QMAKE_CXXFLAGS += `ecl-config --cflags`
#QMAKE_LFLAGS += `ecl-config --ldflags`
#LIBS += -lecl
#LIBS += ./lisp_files/runtime/runtime--all-systems.a



SOURCES += \
        main.cpp \
        mwin.cpp \
    atoms.cpp \
    opcode_interpreter.cpp \
    styles.cpp \
    scene.cpp \
    customrectitem.cpp \
    custom_bus_item.cpp \



HEADERS += \
        mwin.h \
    atoms.h \
    opmap.hpp \
    container.hpp \
    styles.hpp \
    customrectitem.h \
    scene.h \
    custom_bus_item.h \
    opcode_def.hpp

FORMS += \
        mwin.ui

