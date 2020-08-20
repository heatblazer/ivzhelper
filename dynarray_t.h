#ifndef DYNARRAY_T_H
#define DYNARRAY_T_H
#include "adt_opq.h"
#include <stdlib.h> /* malloc, calloc, realloc */
#include <stdio.h> // dbf

//in case no initsize is 0 or less we will assert
#define DARRAY(NS, T, N, INITSIZE)                                              \
    IFACE(NS, T, N);                                                          \
static const char __attribute__((unused))                                       \
            NS##_##N##_sassertsizeless[INITSIZE <=0 ? -1 : 1];                  \
    typedef struct NS##_##N##_t                                                 \
    {                                                                           \
        size_t size, count;                                                     \
        T* pData;                                                               \
        NS##_##N##_CMP_##T cmpfns;                                              \
    } NS##_##N##_t;                                                             \
                                                                                \
    typedef int (*T##cmpfn)(T, T);                                              \
                                                                                \
     NS##_##N##_t* NS##_##N##_init(void)                                        \
    {                                                                           \
        NS##_##N##_t* pN = NEW_(NS, N, malloc) ;                                \
        if (!pN) return NULL;                                                   \
        else {                                                                  \
            pN->pData = (T*)calloc(INITSIZE, sizeof(T));                        \
            if (!pN->pData) { free(pN); return NULL; }                          \
            else {                                                              \
                pN->count = 0;                                                  \
                pN->size = INITSIZE;                                            \
                return pN;                                                      \
                }                                                               \
            }                                                                   \
    }                                                                           \
                                                                                \
    static void NS##_##N##_wiffull(NS##_##N##_t* _this)                         \
    {                                                                           \
        if (!(_this->count < _this->size-1)) {                                  \
        T* t = (T*)realloc(_this->pData,                                        \
                            sizeof(T)* _this->size * 2);                        \
        if (t) {                                                                \
            _this->pData = t;                                                   \
            _this->size *= 2;                                                   \
            }                                                                   \
        }                                                                       \
    }                                                                           \
                                                                                \
    static void NS##_##N##_resizeto(NS##_##N##_t* _this, size_t ns)             \
    {                                                                           \
        if (ns > _this->size-1) {                                               \
        T* t = (T*)realloc(_this->pData,                                        \
                            sizeof(T)* ns * 2);                                 \
        if (t) {                                                                \
            _this->pData = t;                                                   \
            _this->size = ns * 2;                                               \
            }                                                                   \
        }                                                                       \
    }                                                                           \
                                                                                \
    static void NS##_##N##_add(T item, NS##_##N##_t* _this)                     \
        {                                                                       \
            NS##_##N##_wiffull(_this);                                          \
            *(_this->pData+_this->count) = item;                                \
            _this->count++;                                                     \
        }                                                                       \
                                                                                \
    static T* NS##_##N##_getat(size_t idx, NS##_##N##_t* _this)                 \
    {                                                                           \
        if (idx < _this->count)                                                 \
            return &_this->pData[idx];                                          \
        else return NULL;                                                       \
    }                                                                           \
                                                                                \
    void NS##_##N##_cleanup(NS##_##N##_t** _this)                               \
    {                                                                           \
        if (*_this) {                                                           \
            if ((*_this)->pData)                                                \
                free((*_this)->pData);                                          \
            (*_this)->pData = NULL;                                             \
            free(*_this);                                                       \
            (*_this) = NULL;                                                    \
        }                                                                       \
    }                                                                           \
                                                                                \
    static void NS##_##N##_add_at(T item, size_t idx, NS##_##N##_t* _this)      \
    {                                                                           \
        NS##_##N##_resizeto(_this, idx);                                        \
        *(_this->pData+idx) = item;                                             \
        _this->count++;                                                         \
    }                                                                           \
                                                                                \
    T* NS##_##N##_find_if                                                       \
    (T item, NS##_##N##_t* _this, NS##_##N##_T##_cmpfn cmp)                     \
    {                                                                           \
        size_t i;                                                               \
        for(i=0; i < _this->count; i++) {                                       \
            if (cmp(item, _this->pData[i]))                                     \
                return &_this->pData[i];                                        \
        }                                                                       \
        return NULL;                                                            \
    }                                                                           \


#endif // DYNARRAY_T_H
