#include "test_cases.h"
#include "llist_t.h"
#include "adt_opq.h"
#include "dynarray_t.h"
#include "bheap_t.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct str_t
{
    char data[80];
} str_t;

static int int_cmp_eq(int a, int b) {
    return  a == b;
}

static int str_cmp_eq(str_t a, str_t b) {
    return  !strcmp(a.data, b.data);
}

static int str_cmp_contains(str_t a, str_t b) {
    return  strstr(b.data, a.data)!=NULL;
}

static int str_cmp_grt(str_t a, str_t b) {
    return strcmp(a.data, b.data) == 0 ? 1 : 0;
}




LLIST(int, test_list);

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

    while (it) {
        printf("[%d]\r\n", it->pData);
        it = it->next;
    }

    test_list_clear(l);
    free(l);
    l = NULL;
}


DARRAY(ivz, str_t, test_array, 100);


void test_case_darray()
{
    ivz_test_array_t* arr = ivz_test_array_init();

    int i;
    for(i=0; i < 200; i++) {
        str_t t = {{0}};
        snprintf(t.data, sizeof(t.data), "TEST: [%d]\r\n", i);
        ivz_test_array_add(t, arr);
    }
    str_t f, n ;
    snprintf(f.data, sizeof(f.data), "TEST: [155]\r\n");
    strcpy(n.data, "56");

    str_t* found = ivz_test_array_find_if(f, arr, &str_cmp_eq);

    str_t* found2 = ivz_test_array_find_if(n, arr, &str_cmp_contains);

    if (found) {
        printf("FOUND : [%s]\r\n", found->data);
    }

    if (found2) {
        printf("FOUND: [%s]\r\n", found2->data);
    }

    ivz_test_array_cleanup(&arr);
    free(arr);
    arr = NULL;
}


BHEAP(nsivz, str_t, myheap, 100);


void test_case_bheap()
{
    struct nsivz_myheap_t* it = nsivz_myheap_init();

    int i;
    for(i=0; i < 10; i++) {
        str_t s = {{0}};
        snprintf(s.data, sizeof(s.data), "test test[%d]\r\n", i);
        nsivz_myheap_arr_add(s, it->array);
    }

    for (i=0; i < it->array->count; i++) {
        printf("[%s]\r\n", nsivz_myheap_arr_getat(i, it->array)->data);
    }

    nsivz_myheap_max_heapify(1, it, b);

    nsivz_myheap_cleanup(&it);

}
