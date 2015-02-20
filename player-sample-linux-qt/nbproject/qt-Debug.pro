# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux-x86
TARGET = player-sample-linux-qt
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets
SOURCES += PlayerForm.cpp main.cpp
HEADERS += PlayerForm.h
FORMS += PlayerForm.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += /home/ycastonguay/Sources/libssp_player/player 
LIBS += -L. -lssp_player -L../bass/linux -L../bass/linux/x64 -lbass -lbassmix -lbass_fx -lbassenc  
