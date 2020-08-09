#include "utils.h"
#include "dynarray_t.h"
#include "llist_t.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CCMD "dnf hist"

// buffer for splitting
DARRAY(string_t, str_darray, 1000, );

DARRAY(str_darray_t, arr_of_arr, 1000, );



//LLIST(int, test_list, );
LLIST(int, test_list, );

static int int_cmp_eq(int a, int b) {
    return  a == b;
}



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

#if 0
void delete_node(int v, test_list_node **list);
void reverse(test_list_t* l);
void delete_n_nodes(int n, int v, test_list_node* list);
#endif

int main(void)
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
}

#if 0
void delete_n_nodes(int n, int v, test_list_node* list)
{
    while (n-- > 0) {
        delete_node(v, &list);
    }
}

void delete_node(int v, test_list_node** list)
{
    test_list_node* cur = *list;

    if (cur && cur->pData == v){
        test_list_node* tmp = cur;
        cur = cur->next;
        free(tmp);
        (*list) = cur;
        return;
    }
    delete_node(v, &cur->next);
}


void reverse(test_list_t *l)
{
    typedef  test_list_node* tln;
    test_list_node* begin = l->pHead;
    test_list_node* current = l->pHead, *prev, *next;

    while (current)
    {
        // 5, 4, 3, 2, 1
        // 3, 4, 5, 2, 1
        // 3, 2, 5, 4, 1
        // 3, 2, 1, 4, 5
        // 1, 2, 3, 4, 5
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    l->pHead = prev;
}

#endif
#endif
