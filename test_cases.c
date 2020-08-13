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
    int weight;
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




LLIST(ivz, int, test_list);

void test_case_llist()
{

    ivz_test_list_t* l = ivz_test_list_init();

    ivz_test_list_put(5, l);
    ivz_test_list_put(4, l);
    ivz_test_list_put(3, l);
    ivz_test_list_put(2, l);
    ivz_test_list_put(1, l);
    int i;
    for(i=0; i < 5; i++)
        ivz_test_list_put(10, l);

    ivz_test_list_put(1313, l);

    for(i=0; i < 5; i++)
        ivz_test_list_put(100, l);


    ivz_test_list_delete_node(1, &l->pHead, &int_cmp_eq);
    ivz_test_list_delete_node(2, &l->pHead, &int_cmp_eq);
    ivz_test_list_delete_node(3, &l->pHead, &int_cmp_eq);
    ivz_test_list_delete_node(100, &l->pHead, &int_cmp_eq);
    ivz_test_list_delete_node(10, &l->pHead, &int_cmp_eq);
    ivz_test_list_delete_node(100, &l->pHead, &int_cmp_eq);


    struct ivz_test_list_node_t* it = ivz_test_list_begin(l);
    struct ivz_test_list_node_t* item = ivz_test_list_find_if(1313, l, &int_cmp_eq);

    if (item) {
        printf("[%d]\r\n", item->pData);
    }

    while (it) {
        printf("[%d]\r\n", it->pData);
        it = it->next;
    }

    ivz_test_list_clear(l);
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

static int eq(const str_t a, const str_t b)
{
    return  a.weight == b.weight;
}

static int lt(const str_t a, const str_t b)
{
    return  a.weight < b.weight && !eq(a, b);
}

static int gt(const str_t a, const str_t b)
{
    return  a.weight > b.weight && !eq(a, b);
}



void test_case_bheap()
{
    struct nsivz_myheap_t* it = nsivz_myheap_init();

    nsivz_myheap_CMP_str_t b ;
    b.nsivz_myheap__lt__ = &lt;
    b.nsivz_myheap__gt__ = &gt;
    b.nsivz_myheap__eq__ = &eq;


    int i;
    for(i=0; i < 10; i++) {
        str_t s = {i, {0}};
        snprintf(s.data, sizeof(s.data), "test test[%d]\r\n", i);
        nsivz_myheap_arr_add(s, it->array);
    }

    for (i=0; i < it->array->count; i++) {
        printf("[%s]\r\n", nsivz_myheap_arr_getat(i, it->array)->data);
    }

    nsivz_myheap_arr_foo();

    //nsivz_myheap_max_heapify(10, it, b);
    nsivz_myheap_cleanup(&it);

}

// mix test

DARRAY(ivz, int, test_mix, 100);

LLIST(ivz, ivz_test_mix_t,  test_list_mix);

void test_case_mix_adt()
{
    size_t i, j, h;
    // init list
    ivz_test_list_mix_t* lst = ivz_test_list_mix_init();

    for(i=0; i < 10; i++) {
        ivz_test_mix_t* arr = ivz_test_mix_init();
        for(j=0; j < 120; j++) {
            ivz_test_mix_add(j, arr);
        }
        ivz_test_list_mix_put(*arr, lst);
        ivz_test_mix_cleanup(&arr);
        free(arr);
    }

    struct ivz_test_list_mix_node_t* it = ivz_test_list_mix_begin(lst);
    struct ivz_test_list_mix_node_t* end = ivz_test_list_mix_end(lst);

    while (it != end) {
        ivz_test_mix_t* arr = &it->pData;
        for(h=0; h < arr->count; h++) {
            printf("Iter [%d]\r\n", *ivz_test_mix_getat(h, arr));
        }
        printf("#####################\r\n");
        it = it->next;
    }

    struct ivz_test_list_mix_node_t* begin = ivz_test_list_mix_begin(lst);

    while (lst->pHead != NULL) {
        struct ivz_test_list_mix_node_t* tmp = lst->pHead;
        lst->pHead = lst->pHead->next;
        free(tmp);
    }

    free(lst);
}
