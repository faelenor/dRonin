TEMPLATE = lib
TARGET = Stm
include(../../gcsplugin.pri)
include(../../plugins/uavobjects/uavobjects.pri)
include(../../plugins/coreplugin/coreplugin.pri)

OTHER_FILES += Stm.pluginspec

HEADERS += \
    stmplugin.h \
    flyingf3.h \
    discoveryf4.h \
    nucleo.h

SOURCES += \
    stmplugin.cpp \
    flyingf3.cpp \
    discoveryf4.cpp \
    nucleo.cpp

RESOURCES += \
    stm.qrc

