INCLUDEPATH += $$PWD
#DEPENDPATH  += $$PWD

WIDGETS_DIR = "$$PWD/widgets"

SOURCES += \
    $$PWD/main.cpp \
    $$PWD/mainwindow.cpp \
    $$PWD/smdescription.cpp \
    $$PWD/dotfilegenerator.cpp \
    $$PWD/xmlhandler.cpp \
    $$PWD/sourcefilegenerator.cpp \
    $$PWD/docfilegenerator.cpp \
    $$PWD/xlsxfilegenerator.cpp

HEADERS += \
    $$PWD/mainwindow.h \
    $$PWD/smdescription.h \
    $$PWD/dotfilegenerator.h \
    $$PWD/xmlhandler.h \
    $$PWD/sourcefilegenerator.h \
    $$PWD/docfilegenerator.h \
    $$PWD/xlsxfilegenerator.h

FORMS += \
    $$PWD/mainwindow.ui

#RESOURCES += \
#    resources.qrc

include($${WIDGETS_DIR}/autoscaled_pix/autoscaled_pix.pri)

