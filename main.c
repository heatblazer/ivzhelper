#include "test_cases.h"
#include "linux-commands.h"
#include <stdio.h>
#include <string.h>
int main(int argc, char** argv)
{
#if 0
    printf("\r\nlist testcase\r\n");
    test_case_llist();
    puts("########################");
    printf("\r\ntest bheap\r\n");
    test_case_bheap();
    puts("########################");

    printf("\r\ntest mix\r\n");
//    test_case_mix_adt();
    printf("test case darray\r\n");
    test_case_darray();
    puts("########################");


    printf("\r\ntest bin tree\r\n");
    test_case_bst();
#else
    if (argc != 2) {
        fprintf(stderr, "Err usage: pass a file with `dnf hist` data\r\n");
        return 1;
    }
    dnf_hist(argv[1]);

    //test_case_mixup();

#endif
}

