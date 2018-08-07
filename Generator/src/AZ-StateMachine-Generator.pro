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
BUILD_DIR	= "$${PARENT_DIR}/build"
BIN_DIR		= "$${PARENT_DIR}/bin"
CODE_DIR	= "$${PARENT_DIR}/src/app"
COTS_DIR	= "$${PARENT_DIR}/src/cots"

RCC_DIR		= "$$BUILD_DIR"
UI_DIR		= "$$BUILD_DIR"
MOC_DIR		= "$$BUILD_DIR"
OBJECTS_DIR = "$$BUILD_DIR"

CONFIG += debug_and_release
CONFIG(debug, debug|release) {
	DESTDIR = "$$BIN_DIR/debug"
} else:CONFIG(release, debug|release) {

    win32 {
        DESTDIR = "$$BIN_DIR/release/win32"

        # Copie des dll utiles dans le répertoire release
        # La commande "copy" de Windows n'accepte pas les chemins d'accès avec des slash, on les remplace donc par des backslash
        DESTDIR_WIN = $${DESTDIR}
        DESTDIR_WIN ~= s,/,\\,g

        postbuild.target    = postbuild
        postbuild.depends   += FORCE
        greaterThan(QT_MAJOR_VERSION, 4) {
            # Qt5
            # windeployqt récupère automatiquement toutes les dll requises
            QMAKE_POST_LINK = windeployqt.exe "$$DESTDIR_WIN"
        } else {
            # Qt4
            # Commande de copie des 4 dll requises
            postbuild.commands   =   copy "$$QMAKE_LIBDIR_QT\\QtGui4.dll" "$$DESTDIR_WIN"
            postbuild.commands  += & copy "$$QMAKE_LIBDIR_QT\\QtCore4.dll" "$$DESTDIR_WIN"
            postbuild.commands  += & copy "$$QMAKE_LIBDIR_QT\\..\\..\\..\\..\\..\\mingw\\bin\\mingwm10.dll" "$$DESTDIR_WIN"
            postbuild.commands  += & copy "$$QMAKE_LIBDIR_QT\\..\\..\\..\\..\\..\\mingw\\bin\\libgcc_s_dw2-1.dll" "$$DESTDIR_WIN"
        }

        PRE_TARGETDEPS            = postbuild
        QMAKE_EXTRA_TARGETS      += postbuild

    }

    macx {
        DESTDIR = "$$BIN_DIR/release/macx"
    }

} else {
    error(Unknown set of dependencies.)
}

include($${CODE_DIR}/app.pri)
include($${COTS_DIR}/cots.pri)
