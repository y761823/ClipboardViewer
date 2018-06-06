#-------------------------------------------------
#
# Project created by QtCreator 2018-03-01T10:44:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = clipboardviewer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

mac {
    LIBS += -framework AppKit
    SOURCES += clipboard/macclipboard.mm \
        clipviewer/opdfclipviewer.cpp
    HEADERS += clipboard/macclipboard.h \
        clipviewer/opdfclipviewer.h
}

SOURCES += main.cpp \
    clipboard/qtclipboard.cpp \
    clipboard/clipboardfactory.cpp \
    clipviewer/otextclipviewer.cpp \
    clipviewer/oimageclipviewer.cpp \
    clipviewer/ohtmlclipviewer.cpp \
    clipviewer/oexportclipviewer.cpp \
    viewer/oimageviewer.cpp \
    omainwindow.cpp \
    oclipboardediter.cpp

HEADERS  += \
    clipboard/clipboard_i.h \
    clipboard/qtclipboard.h \
    clipboard/clipboardfactory.h \
    clipviewer/clipviewer_i.h \
    clipviewer/otextclipviewer.h \
    clipviewer/oimageclipviewer.h \
    clipviewer/ohtmlclipviewer.h \
    clipviewer/oexportclipviewer.h \
    viewer/oimageviewer.h \
    omainwindow.h \
    oclipboardediter.h

FORMS += \
    clipviewer/oimageclipviewer.ui \
    omainwindow.ui \
    oclipboardediter.ui
