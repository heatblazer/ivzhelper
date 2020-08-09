#include "utils.h"
#include "dynarray_t.h"
#include <string.h>

DARRAY(string_t, str_darray, 1000, )

/**
 * @brief
 * spits by patter, not by a char delimiter
 * @param src
 * @param pattern
 * @return
 */
size_t split_s(const char* src,const char* pattern, char** out)
{
    static size_t spl_size =0;
    const size_t  pat_len = strlen(pattern);
    char* begin = (char*) src;

    const char* next = begin;
    if ((begin = strstr((const char*)begin, pattern)) != 0x00) {
        unsigned int size = begin - next;
        char* n = (char*) malloc(sizeof(char)* size);
        if (n) {
            memcpy(n, next, size);
            (*out) = n;
            out++;
            spl_size += 1;
            return  split_s(begin+pat_len, pattern, out);
        } else {
            return 0;
        }
    } else {
        unsigned int size = &src[strlen(src)-1] - next + 1;
        char* n = (char*) malloc(sizeof(char)* size);
        if (n) {
            memcpy(n, next, size);
            (*out++) = n;
            spl_size += 1;
        }
    }
    size_t t = spl_size;
    spl_size = 0;
    return  t;
}



void split_ss(const char* src,const char* pattern, struct str_darray_t* vec)
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
            str_darray_add(s, vec);
            split_ss(begin+pat_len, pattern, vec);
        }
    } else {
        unsigned int size = &src[strlen(src)-1] - next + 1;
        char* n = (char*) alloca(sizeof(char)* size);
        if (n) {
            string_t s = {{0}};
            memcpy(n, next, size);
            memcpy(s.buff, next, size);
            str_darray_add(s, vec);
        }
    }
}

