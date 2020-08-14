#include "test_cases.h"
#include <stdio.h>

int main(void)
{
    printf("\r\nlist testcase\r\n");
    test_case_llist();
    printf("\r\ntest bheap\r\n");
    test_case_bheap();
    printf("\r\ntest mix\r\n");
    test_case_mix_adt();
    printf("\r\ntest bin tree\r\n");
    test_case_bst();
}

