TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    handling.c \
    any_modules.c \
    i_o_data.c \
#    tests/test_getDataStream.c

HEADERS += \
    main.h \
    global_data.h \
    any_modules.h

DISTFILES += \
    Navig
