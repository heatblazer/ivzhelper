TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.c \
        test_cases.c \
        utils.c

HEADERS += \
    adt_opq.h \
    dynarray_t.h \
    llist_t.h \
    test_cases.h \
    utils.h
