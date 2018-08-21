#GraphViz library
DEFINES += WITH_CGRAPH
INCLUDEPATH += private
QMAKE_CXXFLAGS += -DQGVCORE_LIB

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += libcdt libgvc libcgraph
}
win32 {
    #Configure Windows GraphViz path here :
    GRAPHVIZ_PATH = "C:/Program Files (x86)/Graphviz/"
    DEFINES += WIN32_DLL
    DEFINES += GVDLL
    INCLUDEPATH += $$GRAPHVIZ_PATH/include/graphviz
    LIBS += -L$$GRAPHVIZ_PATH/lib/release/lib -lgvc -lcgraph -lcdt

    GRAPHVIZ_DLLS_PATH = "$${GRAPHVIZ_PATH}/bin/"
    cots_dlls.files += "$${GRAPHVIZ_DLLS_PATH}/*.dll"
    cots_dlls.files += "$${GRAPHVIZ_DLLS_PATH}/config6"

}
macx {
    # Enable pkg-config (pkg-config is disabled by default in the Qt package for mac)
    QT_CONFIG -= no-pkg-config
    # pkg-config location if your brew installation is standard
    PKG_CONFIG = /usr/local/bin/pkg-config
}
