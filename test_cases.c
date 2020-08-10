#include "test_cases.h"
#include "llist_t.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static int int_cmp_eq(int a, int b) {
    return  a == b;
}


LLIST(int, test_list, );

void test_case_llist()
{


    test_list_t* l = test_list_init();

    test_list_put(5, l);
    test_list_put(4, l);
    test_list_put(3, l);
    test_list_put(2, l);
    test_list_put(1, l);
    int i;
    for(i=0; i < 5; i++)
        test_list_put(10, l);

    test_list_put(1313, l);

    for(i=0; i < 5; i++)
        test_list_put(100, l);


    test_list_delete_node(1, &l->pHead, &int_cmp_eq);
    test_list_delete_node(2, &l->pHead, &int_cmp_eq);
    test_list_delete_node(3, &l->pHead, &int_cmp_eq);
    test_list_delete_node(100, &l->pHead, &int_cmp_eq);
    test_list_delete_node(10, &l->pHead, &int_cmp_eq);
    test_list_delete_node(100, &l->pHead, &int_cmp_eq);


    struct test_list_node_t* it = test_list_begin(l);
    struct test_list_node_t* item = test_list_find_if(1313, l, &int_cmp_eq);

    if (item) {
        printf("[%d]\r\n", item->pData);
    }
    getc(stdin);

    while (it) {
        printf("[%d]\r\n", it->pData);
        it = it->next;
    }

    test_list_clear(l);
    free(l);
    l = NULL;
}
