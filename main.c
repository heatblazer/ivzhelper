#include "test_cases.h"
#include <stdio.h>

int main(void)
{
#if 1
    printf("\r\nlist testcase\r\n");
    test_case_llist();
    puts("########################");
    printf("\r\ntest bheap\r\n");
//    test_case_bheap();
    printf("\r\ntest mix\r\n");
//    test_case_mix_adt();
    printf("test case darray\r\n");
    test_case_darray();
    puts("########################");


    printf("\r\ntest bin tree\r\n");
    test_case_bst();
#else
    ls_l();


#endif
}

