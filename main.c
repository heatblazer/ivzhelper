#include "test_cases.h"

#if 0
int main()
{
    size_t ii;

    str_darray_t* buff = str_darray_t_init();
    FILE* cmdpipe = popen(CCMD, "r");
    if (cmdpipe) {
        for(;;) {
            string_t readbuff = {{0}};
            if (fgets(readbuff.buff, sizeof(readbuff.buff), cmdpipe)) {
                str_darray_t_add(readbuff, buff);
            } else {
                break;
            }
        }
        pclose(cmdpipe);
    }
    // test printing data ...
    size_t i;
    char* full = (char*) malloc(sizeof(char) * buff->size * BUFSIZ);
    if (full) {
        for(i=0; i < buff->size; i++) {
            char* dat = str_darray_t_getat(i, buff)->buff;
            if (dat && strlen(dat) > 1)
                strncat(full, dat, strlen(dat));
        }
    }

    str_darray_t* ll = str_darray_t_init();
    str_darray_t* ln = str_darray_t_init();
//    arr_of_arr_t* ar2d = arr_of_arr_t_init();
    split_ss(full, "\n", ll);

    for(ii=0; ii < ll->size; ++ii) {
        const char* d = str_darray_t_getat(ii, ll)->buff;
        if (d) {
            split_ss(d, " ", ln);
        }
    }

    str_darray_t_cleanup(&ll);
    str_darray_t_cleanup(&ln);
    str_darray_t_cleanup(&buff);
    if (ll || buff || ln) {
        exit(-1);
    }
    free(full);
}
#else

int main(void)
{
    puts("test array");
    test_case_darray();
    puts("\r\ntest list");
    test_case_llist();
}

#endif

