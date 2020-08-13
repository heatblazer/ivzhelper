#include "utils.h"
#include "dynarray_t.h"
#include <string.h>

DARRAY(utils, string_t, str_darray, 1000)


void split_ss(const char* src,const char* pattern, struct utils_str_darray_t* vec)
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
