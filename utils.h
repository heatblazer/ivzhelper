#ifndef UTILS_H
#define UTILS_H
#include "adt_opq.h"
#include "dynarray_t.h"
#include <stdio.h>

typedef struct {
    char buff[1024];
} string_t;

size_t split(const char* src,const char* pattern, string_t** out);

#endif // UTILS_H
