TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
        utils.c

HEADERS += \
    adt_opq.h \
    dynarray_t.h \
    llist_t.h \
    utils.h
