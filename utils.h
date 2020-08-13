#ifndef UTILS_H
#define UTILS_H
#include "adt_opq.h"
#include <stdio.h>
typedef struct {
    char buff[1024];
} string_t;

ADT_OPQ(utils, string_t, str_darray);

void split_ss(const char* src,const char* pattern, struct utils_str_darray_t* vec);

#endif // UTILS_H
