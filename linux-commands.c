#include "utils.h"
#include "dynarray_t.h"
#include <string.h>
#include <stdlib.h>

//emulates a namespace, then type, then name of the cotnainer,
//and some init opts like default size
DARRAY(ivz, string_t, dnf_str_array, 100);

typedef struct dnf_etnry_t
{
    string_t id;
    string_t cmd;
    string_t date;
    string_t action;
    string_t altered;
} dnfrec;

DARRAY(ivz, dnfrec, dnf_entry_t_array, 100);

void dnf_hist()
{
    size_t i, j, k;
    static const char* lsl = "dnf hist";
    struct ivz_dnf_str_array_t* arr = ivz_dnf_str_array_init();
    struct ivz_dnf_entry_t_array_t *pDnf = ivz_dnf_entry_t_array_init();

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
        size_t cnt = split(ivz_dnf_str_array_getat(i, arr)->buff, "|", &out);
        if (cnt == 5)
        {
            dnfrec drec;
            drec.id = out[0];
            drec.cmd = out[1];
            drec.date = out[2];
            drec.action = out[3];
            drec.altered = out[4];
            ivz_dnf_entry_t_array_add(drec, pDnf);
        }
        free(out);
    }

    for(k=0; k < pDnf->count; k++)
    {
        dnfrec* pRec = ivz_dnf_entry_t_array_getat(k, pDnf);
        printf("[%s][%s][%s][%s][%s]\r\n", pRec->id.buff, pRec->action.buff,
               pRec->date.buff, pRec->action.buff, pRec->altered.buff);
    }


    CLEANUP(ivz, dnf_str_array, arr, free);
    CLEANUP(ivz, dnf_entry_t_array, pDnf, free);
}
