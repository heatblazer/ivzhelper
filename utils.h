#ifndef UTILS_H
#define UTILS_H
#include "adt_opq.h"
#include <stdio.h>
typedef struct {
    char buff[1024];
} string_t;

DARRAY_OPQ(str_darray);

size_t split_s(const char* src,const char* pattern,char** out);

void split_ss(const char* src,const char* pattern, struct str_darray_t* vec);


#endif // UTILS_H
