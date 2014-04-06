TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c

INCLUDEPATH += /usr/include/gtk-2.0 \
/usr/include/glib-2.0 \
/usr/lib/i386-linux-gnu/glib-2.0/include/ \
/usr/include/cairo/ \
/usr/include/pango-1.0/ \
/usr/lib/i386-linux-gnu/gtk-2.0/include/ \
/usr/include/gdk-pixbuf-2.0/ \
/usr/include/atk-1.0/


unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += gtk+-2.0

QMAKE_CFLAGS += -Wno-unused-parameter

HEADERS += \
    callbacks.h \
    mainwindow.h \
    addstudent.h \
    helpers.h \
    dialogs.h \
    results.h
