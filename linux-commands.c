#include "utils.h"
#include "dynarray_t.h"
#include <string.h>
#include <stdlib.h>


DARRAY(ivz, string_t, dnf_str_array, 100);


void ls_l()
{
    size_t i, j, k;
    static const char* lsl = "ls -l";
    struct ivz_dnf_str_array_t* arr = ivz_dnf_str_array_init();

    FILE* cmdpipe = popen(lsl, "r");
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
        size_t cnt = split(ivz_dnf_str_array_getat(i, arr)->buff, " ", &out);
        for(j=0; j < cnt; j++) {
            printf("[%s]\r\n", out[j].buff);
        }
        printf("###########\r\n");
        free(out);
    }

    CLEANUP(ivz, dnf_str_array, arr, free);

}
