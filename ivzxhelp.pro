TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        linux-commands.c \
        main.c \
        test_cases.c \
        utils.c

HEADERS += \
    adt_opq.h \
    adt_t.h \
    algos.h \
    bheap_t.h \
    btree_t.h \
    dynarray_t.h \
    linux-commands.h \
    llist_t.h \
    test_cases.h \
    utils.h

DISTFILES += \
    TODO.md \
    valgrindreport.txt
