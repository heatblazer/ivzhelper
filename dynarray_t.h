#ifndef DYNARRAY_T_H
#define DYNARRAY_T_H
#include <stdlib.h> /* malloc, calloc, realloc */

//in case no initsize is 0 or less we will assert
#define DARRAY(T, N, INITSIZE)                                      \
static const char __attribute__((unused))                           \
            N##_sassertsizeless[INITSIZE <=0 ? -1 : 1];             \
    typedef struct N##_t                                            \
    {                                                               \
        size_t size, count;                                         \
        T* pData;                                                   \
    } N##_t;                                                        \
                                                                    \
    typedef int (*T##cmpfn)(T, T);                                  \
                                                                    \
    static N##_t* N##_t##_init(void)                                \
    {                                                               \
        N##_t* pN = (N##_t*)malloc(sizeof(N##_t));                  \
        if (!pN) return NULL;                                       \
        else {                                                      \
            pN->pData = (T*)calloc(INITSIZE, sizeof(T));            \
            if (!pN->pData) { free(pN); return NULL; }              \
            else {                                                  \
                pN->count = 0;                                      \
                pN->size = INITSIZE;                                \
                return pN;                                          \
                }                                                   \
            }                                                       \
    }                                                               \
                                                                    \
    static void N##_wiffull(N##_t* _this)                           \
    {                                                               \
        if (!(_this->count < _this->size-1)) {                      \
        T* t = (T*)realloc(_this->pData,                            \
                            sizeof(T)* _this->size * 2);            \
        if (t) {                                                    \
            _this->pData = t;                                       \
            _this->size *= 2;                                       \
            }                                                       \
        }                                                           \
    }                                                               \
                                                                    \
    static void N##_resizeto(N##_t* _this, size_t ns)               \
    {                                                               \
        if (ns > _this->size-1) {                                   \
        T* t = (T*)realloc(_this->pData,                            \
                            sizeof(T)* ns * 2);                     \
        if (t) {                                                    \
            _this->pData = t;                                       \
            _this->size = ns * 2;                                   \
            }                                                       \
        }                                                           \
    }                                                               \
                                                                    \
    static void N##_add(T item, N##_t* _this)                       \
        {                                                           \
            N##_wiffull(_this);                                     \
            *(_this->pData+_this->count) = item;                    \
            _this->count++;                                         \
        }                                                           \
                                                                    \
    static T* N##_getat(size_t idx, N##_t* _this)                   \
    {                                                               \
        if (idx < _this->count)                                     \
            return &_this->pData[idx];                              \
        else return NULL;                                           \
    }                                                               \
                                                                    \
    static void N##_cleanup(N##_t** _this)                          \
    {                                                               \
        if (*_this) {                                               \
            if ((*_this)->pData)                                    \
                free((*_this)->pData);                              \
            (*_this)->pData = NULL;                                 \
            free(*_this);                                           \
            (*_this) = NULL;                                        \
        }                                                           \
    }                                                               \
                                                                    \
    static void N##_add_at(T item, size_t idx, N##_t* _this)        \
    {                                                               \
        N##_resizeto(_this, idx);                                   \
        *(_this->pData+idx) = item;                                 \
        _this->count++;                                             \
    }                                                               \
                                                                    \
    static T* N##_find_if                                           \
        (T item, N##_t* _this, T##cmpfn cmp)                        \
    {                                                               \
        size_t i;                                                   \
        for(i=0; i < _this->count; i++) {                           \
            if (cmp(item, _this->pData[i]))                         \
                return &_this->pData[i];                            \
        }                                                           \
        return NULL;                                                \
    }

#endif // DYNARRAY_T_H
