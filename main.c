#include "test_cases.h"
#include <stdio.h>

int main(void)
{
#if 1
    printf("\r\nlist testcase\r\n");
//    test_case_llist();
    printf("\r\ntest bheap\r\n");
//    test_case_bheap();
    printf("\r\ntest mix\r\n");
//    test_case_mix_adt();
    test_case_darray();

    printf("\r\ntest bin tree\r\n");
    test_case_bst();
#else
    ls_l();


#endif
}

