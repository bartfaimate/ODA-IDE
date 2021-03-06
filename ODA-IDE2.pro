#-------------------------------------------------
#
# Project created by QtCreator 2019-09-14T12:11:30
#
#-------------------------------------------------

QT       += core gui widgets testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ODA-IDE
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++1z

SOURCES += \
    filemanager.cpp \
    main.cpp \
    mainwindow.cpp \
    settings.cpp \
    tab.cpp \
    editor.cpp \
    highlighter.cpp \
    statusbar.cpp \
#    terminal.cpp
#    unittests/unittests.cpp
     \
    settingsdialog.cpp \
    fileextensionmapper.cpp \
    utilities.cpp

HEADERS += \
    filemanager.h \
    mainwindow.h \
    settings.h \
    tab.h \
    editor.h \
    highlighter.h \
    statusbar.h \
 \#    terminal.h
    utilities.h \
    settingsdialog.h \
    fileextensionmapper.h

LIBS += -lqtermwidget5
LIBS += -lstdc++fs
#INCLUDEPATH += /usr/include/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# SETTINGS or IDE
DEFINES += "IDE"
