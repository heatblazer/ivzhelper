#include "utils.h"
#include "dynarray_t.h"
#include <string.h>

//DARRAY(utils, string_t, str_darray, 10)
DARRAY(utils, string_t, str_darray, 10);

static void split_ss(const char* src,const char* pattern, struct utils_str_darray_t* vec)
{
    const size_t  pat_len = strlen(pattern);
    char* begin = (char*) src;
    const char* next = begin;
    if ((begin = strstr((const char*)begin, pattern)) != 0x00) {
        unsigned int size = begin - next;
        char* n = (char*) alloca(sizeof(char)* size);
        if (n) {
            string_t s = {{0}};
            memcpy(n , next, size);
            memcpy(s.buff, n, size);
            utils_str_darray_add(s, vec);
            split_ss(begin+pat_len, pattern, vec);
        }
    } else {
        unsigned int size = &src[strlen(src)-1] - next + 1;
        char* n = (char*) alloca(sizeof(char)* size);
        if (n) {
            string_t s = {{0}};
            memcpy(n, next, size);
            memcpy(s.buff, next, size);
            utils_str_darray_add(s, vec);
        }
    }
}

size_t split(const char *src, const char *pattern, string_t **out)
{
    struct utils_str_darray_t* vec = utils_str_darray_init();
    size_t cnt=0;
    split_ss(src, pattern, vec);
    string_t* it = (string_t*)malloc(vec->count * sizeof(string_t));
    string_t* beg = it;
    cnt = vec->count;
    if (it) {
        size_t i;
        for(i=0; i < vec->count; i++) {
            strcpy(it->buff, utils_str_darray_getat(i, vec)->buff);
            it++;
        }
        (*out) = beg;
    }
    utils_str_darray_cleanup(&vec);
    return  cnt;
}
