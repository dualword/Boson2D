TEMPLATE = app
TARGET = boson2d

DEPENDPATH += . ..
INCLUDEPATH += . .. ../visual ../common ../map

CONFIG += qt thread release
QT += svg qt3support

QMAKE_CXXFLAGS += -std=c++11

include (../common/common.pri)
include (../map/map.pri)
include (../visual/visual.pri)

HEADERS += boshot.h \
           boson.h \
           bosonBigDisplay.h \
           bosonCanvas.h \
           bosonTopLevel.h \
           #connect.h \
           #connectDlg.h \
           game.h \
           mainWidget.h \
           playerUnit.h \
           ressource.h \
           serverDlg.h
           
SOURCES += boshot.cpp \
           boson.cpp \
           bosonBigDisplay.cpp \
           bosonCanvas.cpp \
           #bosonField.cpp \
           bosonTopLevel.cpp \
           #connect.cpp \
           #connectDlg.cpp \
           game.cpp \
           main.cpp \
           mainWidget.cpp \
           miniDisplay.cpp \
           playerUnit.cpp \
           serverDlg.cpp

OBJECTS_DIR = .build/obj
MOC_DIR     = .build/moc
RCC_DIR     = .build/rcc
UI_DIR      = .build/ui
