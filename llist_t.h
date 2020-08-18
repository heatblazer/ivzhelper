#ifndef LLIST_T_H
#define LLIST_T_H
#include "adt_opq.h"
//NS##_##N##_t
#define LLIST(NS, T, N)                                                         \
    CMP_FNS(NS, T, N);                                                          \
                                                                                \
    struct NS##_##N##_node_t                                                    \
    {                                                                           \
        struct NS##_##N##_node_t* next;                                         \
        T pData;                                                                \
    };                                                                          \
                                                                                \
    typedef struct                                                              \
    {                                                                           \
        struct NS##_##N##_node_t *pHead, *pTail;                                \
        unsigned int size;                                                      \
        NS##_##N##_CMP_##T cmpfns;                                              \
    } NS##_##N##_t;                                                             \
                                                                                \
    NS##_##N##_t* NS##_##N##_init(void)                                         \
    {                                                                           \
        NS##_##N##_t* pl = (NS##_##N##_t*)calloc(1, sizeof(NS##_##N##_t));      \
        if (pl)                                                                 \
            return pl;                                                          \
        return NULL;                                                            \
    }                                                                           \
                                                                                \
    static void NS##_##N##_clear(NS##_##N##_t* _this)                           \
    {                                                                           \
        while(_this->pHead) {                                                   \
            struct NS##_##N##_node_t* tmp = _this->pHead;                       \
            _this->pHead = _this->pHead->next;                                  \
            if (tmp) free(tmp);                                                 \
        }                                                                       \
    }                                                                           \
                                                                                \
    static void NS##_##N##_put(T item, NS##_##N##_t* _this)                     \
    {                                                                           \
        struct NS##_##N##_node_t* nn =                                          \
                (struct NS##_##N##_node_t*)                                     \
                    malloc(sizeof(struct NS##_##N##_node_t));                   \
        if (!nn) return;                                                        \
        nn->pData = item;                                                       \
        if (!_this->pHead) {                                                    \
            nn->next = _this->pHead;                                            \
            _this->pHead = _this->pTail = nn;                                   \
        } else {                                                                \
            _this->pTail->next = nn;                                            \
            _this->pTail = nn;                                                  \
        }                                                                       \
        _this->size++;                                                          \
    }                                                                           \
                                                                                \
    static void NS##_##N##_delete_node                                          \
    (T item, struct NS##_##N##_node_t** node, T##cmpfn cmp)                     \
    {                                                                           \
        struct NS##_##N##_node_t* cur = *node;                                  \
        if (cur && cmp(cur->pData,item)){                                       \
            struct NS##_##N##_node_t* tmp = cur;                                \
            cur = cur->next;                                                    \
            free(tmp); tmp = NULL;                                              \
            (*node) = cur;                                                      \
            return;                                                             \
        }                                                                       \
        NS##_##N##_delete_node(item, &((*node)->next), cmp);                    \
    }                                                                           \
                                                                                \
    static struct NS##_##N##_node_t* NS##_##N##_begin(NS##_##N##_t* _this)      \
    { return _this->pHead;}                                                     \
                                                                                \
    static struct NS##_##N##_node_t* NS##_##N##_end(NS##_##N##_t* _this)        \
    { return _this->pTail;}                                                     \
                                                                                \
    static int NS##_##N##_empty(NS##_##N##_t* _this)                            \
    { return _this->pHead == NULL; }                                            \
                                                                                \
    T* NS##_##N##_find_if(const T element, NS##_##N##_t* _this)                 \
    {                                                                           \
        struct NS##_##N##_node_t* it  = _this->pHead;                           \
        while (it) {                                                            \
            if (_this->cmpfns.__eq__(it->pData, element))                       \
                    return it->pData;                                           \
            it = it->next;                                                      \
        }                                                                       \
        return NULL;                                                            \
    }


#endif // LLIST_T_H
