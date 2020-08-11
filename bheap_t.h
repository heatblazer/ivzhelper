#ifndef BHEAP_T_H
#define BHEAP_T_H
#include "dynarray_t.h"

#define BHEAP(NS, T, N, INITSIZE)                                               \
    DARRAY(NS, T, N##_arr, INITSIZE)                                            \
    typedef struct NS##_##N##_t {                                               \
        NS##_##N##_arr_t* array;                                                    \
    } NS##_##N##_t;                                                             \
                                                                                \
    static NS##_##N##_t* NS##_##N##_init(void)                                  \
    {                                                                           \
        NS##_##N##_t* bh = (NS##_##N##_t*)calloc(1, sizeof(NS##_##N##_t));      \
        if (bh) {                                                               \
            bh->array = NS##_##N##_arr_t_init();                                    \
            if (!bh->array) return NULL;                                        \
        }                                                                       \
        return bh;                                                              \
    }

#endif // BHEAP_T_H
