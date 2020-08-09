#ifndef LLIST_T_H
#define LLIST_T_H

#define LLIST(T, N, MOD)                                                        \
    struct N##_node_t                                                           \
    {                                                                           \
        T pData;                                                                \
        struct N##_node_t* next;                                                \
    };                                                                          \
                                                                                \
    typedef struct                                                              \
    {                                                                           \
        struct N##_node_t *pHead, *pTail;                                       \
        unsigned int size;                                                      \
    } N##_t;                                                                    \
                                                                                \
    typedef int (*T##cmpfn)(T, T);                                              \
                                                                                \
    static N##_t* N##_init(void)                                                \
    {                                                                           \
        N##_t* pl = (N##_t*)calloc(1, sizeof(N##_t));                           \
        if (pl)                                                                 \
            return pl;                                                          \
        return NULL;                                                            \
    }                                                                           \
                                                                                \
    static void N##_clear(N##_t* _this)                                         \
    {                                                                           \
        while(_this->pHead) {                                                   \
            struct N##_node_t* tmp = _this->pHead;                              \
            _this->pHead = _this->pHead->next;                                  \
            if (tmp) free(tmp);                                                 \
        }                                                                       \
    }                                                                           \
                                                                                \
    static void N##_put(T item, N##_t* _this)                                   \
    {                                                                           \
        struct N##_node_t* nn =                                                 \
                (struct N##_node_t*)malloc(sizeof(struct N##_node_t));          \
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
    static void N##_delete_node(T item, struct N##_node_t** node, T##cmpfn cmp) \
    {                                                                           \
        struct N##_node_t* cur = *node;                                         \
        if (cur && cmp(cur->pData,item)){                                       \
            struct N##_node_t* tmp = cur;                                       \
            cur = cur->next;                                                    \
            free(tmp); tmp = NULL;                                              \
            (*node) = cur;                                                      \
            return;                                                             \
        }                                                                       \
        N##_delete_node(item, &((*node)->next), cmp);                           \
    }                                                                           \
                                                                                \
    static struct N##_node_t* N##_begin(N##_t* _this) { return _this->pHead;}   \
                                                                                \
    static struct N##_node_t* N##_end(N##_t* _this) { return _this->pTail;}     \
                                                                                \
    static int N##_empty(N##_t* _this) { return _this->pHead == NULL; }         \
                                                                                \
    static struct N##_node_t*                                                   \
        N##_find_if(const T element, N##_t* _this, T##cmpfn cmp)                \
    {                                                                           \
        struct N##_node_t* it  = _this->pHead;                                  \
        while (it) {                                                            \
            if (cmp(it->pData, element))                                        \
                    return it;                                                  \
            it = it->next;                                                      \
        }                                                                       \
        return NULL;                                                            \
    }


#endif // LLIST_T_H
