#include "test_cases.h"
#include "linux-commands.h"
#include <stdio.h>

int main(void)
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
//    ls_l();
    test_case_mixup();

#endif
}

