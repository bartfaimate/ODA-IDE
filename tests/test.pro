QT += widgets testlib core gui

SOURCES = unittests.cpp \
          ../settings.cpp

HEADERS = ../settings.h

# install
target.path = ./
INSTALLS += target
