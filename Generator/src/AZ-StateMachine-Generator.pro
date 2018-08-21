#-------------------------------------------------
#
# Project created by QtCreator 2011-05-15T03:26:23
#
#-------------------------------------------------

lessThan(QT_MAJOR_VERSION, 5): error(This project must compiled on Qt version 5 or greater)

QT += core gui xml widgets

TARGET = AZ-StateMachine-Generator
TEMPLATE = app
# for debug (active qDebug() outuputs on console)
#CONFIG += console

PARENT_DIR	= ".."
BUILD_DIR	= "$${PARENT_DIR}/build"
BIN_DIR		= "$${PARENT_DIR}/bin"
CODE_DIR	= "$${PARENT_DIR}/src/app"
COTS_DIR	= "$${PARENT_DIR}/src/cots"

RCC_DIR		= "$$BUILD_DIR"
UI_DIR		= "$$BUILD_DIR"
MOC_DIR		= "$$BUILD_DIR"
OBJECTS_DIR = "$$BUILD_DIR"

include($${CODE_DIR}/app.pri)

# Add cots dll path to cots_dlls.files variable in order to copy them to the release directory
include($${COTS_DIR}/cots.pri)

CONFIG += debug_and_release
CONFIG(debug, debug|release) {

	DESTDIR = "$$BIN_DIR/debug"

} else:CONFIG(release, debug|release) {

    win32 {
        DESTDIR = "$$BIN_DIR/release/win32"

        # Copy usefull dll in the release directory
        # The windows "copy" command doesn't understand path with slashes, so we replace them by backslahes
        DESTDIR_WIN = $${DESTDIR}
        DESTDIR_WIN ~= s,/,\\,g     # convert slashes in backslashes

        # Qt5
        # windeployqt automatically get all the Qt5 required dll
        QMAKE_POST_LINK += windeployqt.exe "$$DESTDIR_WIN"

#        postbuild.target    = postbuild
#        postbuild.depends   += FORCE
#            # Qt4
#            # Copy commands for the required dll
#            postbuild.commands   =   copy "$$QMAKE_LIBDIR_QT\\QtGui4.dll" "$$DESTDIR_WIN"
#            postbuild.commands  += & copy "$$QMAKE_LIBDIR_QT\\QtCore4.dll" "$$DESTDIR_WIN"
#        PRE_TARGETDEPS            = postbuild
#        QMAKE_EXTRA_TARGETS      += postbuild

        # Copy 3rd party dlls
        cots_dlls.path = $${DESTDIR}
        INSTALLS += cots_dlls
    }

    macx {
        DESTDIR = "$$BIN_DIR/release/macx"
    }

} else {
    error(Unknown set of dependencies.)
}

