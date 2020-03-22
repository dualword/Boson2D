TEMPLATE = app
TARGET = boeditor

DEPENDPATH += . ..
INCLUDEPATH += . .. visual ../visual common map

CONFIG += qt thread release
QT += svg qt3support

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -fpermissive

include (../common/common.pri)
include (../map/map.pri)
include (../visual/visual.pri)
include (editor.pri)

OBJECTS_DIR = .build/obj
MOC_DIR     = .build/moc
RCC_DIR     = .build/rcc
UI_DIR      = .build/ui
