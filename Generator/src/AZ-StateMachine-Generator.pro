#-------------------------------------------------
#
# Project created by QtCreator 2011-05-15T03:26:23
#
#-------------------------------------------------

QT += core gui
QT += xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets # For Qt5

TARGET = AZ-StateMachine-Generator
TEMPLATE = app

PARENT_DIR	= ".."
BUILD_DIR	= "$$PARENT_DIR/build"
BIN_DIR		= "$$PARENT_DIR/bin"

RCC_DIR		= "$$BUILD_DIR"
UI_DIR		= "$$BUILD_DIR"
MOC_DIR		= "$$BUILD_DIR"
OBJECTS_DIR = "$$BUILD_DIR"


CONFIG += debug_and_release
CONFIG(debug, debug|release) {
	DESTDIR = "$$BIN_DIR/debug"
} else {
	DESTDIR = "$$BIN_DIR/release"
}


SOURCES += main.cpp\
	mainwindow.cpp \
    smdescription.cpp \
    dotfilegenerator.cpp \
    xmlhandler.cpp \
    sourcefilegenerator.cpp \
	docfilegenerator.cpp

HEADERS  += mainwindow.h \
    smdescription.h \
    dotfilegenerator.h \
    xmlhandler.h \
    sourcefilegenerator.h \
	docfilegenerator.h

FORMS    += mainwindow.ui
