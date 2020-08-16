#include "utils.h"
#include "dynarray_t.h"
#include <string.h>
#include <stdlib.h>


DARRAY(ivz, string_t, dnf_str_array, 100);

static size_t nlidx(const char*  in, size_t cnt)
{
    size_t i;
    if (!in) return 0;
    for(i=0; i < cnt; i++) {
        if (in[i] == '\n')
            return  i;
    }
    return 0;
}

static void trimnline(string_t** in, size_t cnt)
{
    size_t i;
    for(i=0; i < cnt; i++) {
        size_t nl ;
        if ((nl = nlidx(in[i]->buff, 1024)) != 0) {
            memset(in[i]->buff+nl, '\0', 1024-nl);
        }
    }
}

void dnf_history()
{
    size_t i, j, k;
    static const char* dnf = "dnf hist";
    struct ivz_dnf_str_array_t* arr = ivz_dnf_str_array_init();

    FILE* cmdpipe = popen(dnf, "r");
    if (cmdpipe) {
        for(;;) {
            string_t readbuff = {{0}};
            if (fgets(readbuff.buff, sizeof(readbuff.buff), cmdpipe)) {
                ivz_dnf_str_array_add(readbuff, arr);
            } else {
                break;
            }
        }
        pclose(cmdpipe);
    }

    for(i=0; i < arr->count; i++)
    {
        string_t* out = NULL;
        size_t cnt = split(ivz_dnf_str_array_getat(i, arr)->buff, " | ", &out);
#if 1
        trimnline(&out, cnt);
        string_t prn = {{0}};
        snprintf(prn.buff, sizeof(prn.buff), "[%s] on [%s]", out[1].buff, out[2].buff);
        printf("[%s]\r\n", prn.buff);
#endif
        printf("\r\n###########");
        free(out);
    }

    CLEANUP(ivz, dnf_str_array, arr, free);

}
