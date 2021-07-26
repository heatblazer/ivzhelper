#include "utils.h"
#include "dynarray_t.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//emulates a namespace, then type, then name of the cotnainer,
//and some init opts like default size

typedef struct dnf_etnry_t
{
    int idx; //helper index to avoid to call atoi for the integer in the db file
    string_t id;
    string_t cmd;
    string_t date;
    string_t action;
    string_t altered;
} dnfrec;

int cmpfuncIdx (const void * a, const void * b) {

    dnfrec* pA = (dnfrec*)a;
    dnfrec* pB = (dnfrec*)b;
    return  pA->idx - pB->idx;
}


DARRAY(ivz, string_t, dnf_str_array, 100);

DARRAY(ivz, dnfrec, dnf_entry_t_array, 100);

void dnf_hist(const char* fname)
{
    size_t i, j, k;
//    static const char* lsl = "dnf hist";
    struct ivz_dnf_str_array_t* arr = ivz_dnf_str_array_init();

    struct ivz_dnf_entry_t_array_t *pDnf = ivz_dnf_entry_t_array_init();

    dnfrec* pBegin = pDnf->pData;

    FILE* cmdpipe = fopen(fname, "r"); //from file
    FILE* outfile = fopen("dnfinstall.sh", "w");
    if (!outfile) {
        CLEANUP(ivz, dnf_str_array, arr, free);
        CLEANUP(ivz, dnf_entry_t_array, pDnf, free);
        return;
    }

    if (cmdpipe) {
        for(;;) {
            string_t readbuff = {{0}};
            if (fgets(readbuff.buff, sizeof(readbuff.buff), cmdpipe)) {
                ivz_dnf_str_array_add(readbuff, arr);
            } else {
                break;
            }
        }
        fclose(cmdpipe);
    }

    for(i=1; i < arr->count; i++)
    {
        string_t* out = NULL;
        size_t cnt = split(ivz_dnf_str_array_getat(i, arr)->buff, "|", &out);
        if (cnt == 5)
        {
            dnfrec drec;
            drec.idx = arr->count - i;
            drec.id = out[0];
            drec.cmd = out[1];
            drec.date = out[2];
            drec.action = out[3];
            drec.altered = out[4];
            ivz_dnf_entry_t_array_add(drec, pDnf);
        }
        free(out);
    }
    qsort(&pDnf->pData[0], pDnf->count, sizeof(dnfrec),cmpfuncIdx );
    fprintf(outfile, "#!/bin/bash\r\n");
    for(k=0; k < pDnf->count; k++)
    {
        dnfrec* pRec = ivz_dnf_entry_t_array_getat(k, pDnf);

        if (strstr(pRec->action.buff, "Install")) {
            string_t* installout = NULL;
            size_t iter = split(pRec->cmd.buff, " ", &installout);
            if (iter <= 1) continue;
            fprintf(outfile, "dnf install %s \r\n",installout[2].buff);
        }
    }

    fclose(outfile);
    CLEANUP(ivz, dnf_str_array, arr, free);
    CLEANUP(ivz, dnf_entry_t_array, pDnf, free);
}
