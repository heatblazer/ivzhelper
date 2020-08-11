#ifndef BHEAP_T_H
#define BHEAP_T_H
#include "adt_opq.h"
#include "dynarray_t.h"

#define BHEAP(NS, T, N, INITSIZE)                                               \
    CMP_FNS(NS, T, N);                                                          \
    DARRAY(NS, T, N##_arr, INITSIZE)                                            \
    typedef struct NS##_##N##_t {                                               \
        NS##_##N##_arr_t* array;                                                \
    } NS##_##N##_t;                                                             \
                                                                                \
                                                                                \
    static NS##_##N##_t* NS##_##N##_init(void)                                  \
    {                                                                           \
        NS##_##N##_t* bh = (NS##_##N##_t*)calloc(1, sizeof(NS##_##N##_t));      \
        if (bh) {                                                               \
            bh->array = NS##_##N##_arr_init();                                  \
            if (!bh->array) {                                                   \
                free(bh);                                                       \
                return NULL;                                                    \
            }                                                                   \
         }                                                                      \
            return bh;                                                          \
    }                                                                           \
                                                                                \
                                                                                \
    static void NS##_##N##_max_heapify                                          \
    (size_t i, NS##_##N##_t* _this,NS##_##N##_CMP_##T cmpfn)                    \
    {                                                                           \
        size_t left = i * 2;                                                    \
        size_t right = (i  * 2) + 1;                                            \
        size_t largest = i;                                                     \
        if (left <= _this->array->count &&                                      \
            cmpfn.NS##_##N##__lt__(_this->array->pData[left],                   \
                                    _this->array->pData[right]))                \
                largest = left;                                                 \
        if (right <= _this->array->count &&                                     \
            cmpfn.NS##_##N##__gt__(_this->array->pData[left],                   \
                                    _this->array->pData[right]))                \
                largest = right;                                                \
        if (largest !=  i) {                                                    \
            T tmp =     _this->array->pData[i];                                 \
            _this->array->pData[i] = _this->array->pData[largest];              \
            _this->array->pData[largest] = tmp;                                 \
            NS##_##N##_max_heapify(i, _this, cmpfn);                            \
        }                                                                       \
    }                                                                           \
                                                                                \
    static void NS##_##N##_cleanup(NS##_##N##_t** _this)                        \
    {                                                                           \
        printf("cleanup of bheap\r\n");                                         \
        NS##_##N##_arr_cleanup(&((*_this)->array));                             \
        if ((*_this)) { free((*_this)); (*_this)=NULL; }                        \
    }

#endif // BHEAP_T_H
