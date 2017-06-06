QT += widgets testlib

TEMPLATE = app

CONFIG += c++14 debug


INCLUDEPATH = "../src"
LIBS += -L ../src/app -lapp

QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
QMAKE_LDFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov

SOURCES += TestCommands.cpp
TARGET = test
