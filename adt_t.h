#ifndef ADT_T_H
#define ADT_T_H
/**
all-in-one header file
*/

/*
#include malloc, strcpy, etc...
*/

/**
interface for the data structures
*/
#define CMP_FNS(NS, T, N)                                                       \
    typedef struct  {                                                           \
        int (*__lt__)(const T, const T);                                        \
        int (*__gt__)(const T, const T);                                        \
        int (*__eq__)(const T, const T);                                        \
    }  NS##_##N##_CMP_##T;                                                      \
                                                                                \
    extern struct NS##_##N##_t* NS##_##N##_init(void);                          \
                                                                                \
    extern void NS##_##N##_cleanup(struct NS##_##N##_t** _this);


#define ADT_OPQ(NS, T, N)                                                       \
    struct  NS##_##N##_t;


#define NODE_OPQ(NS, N)                                                         \
    struct NS##_##N##_node_t;

#define NEW_NODE(NS, N, ALLOC)                                                  \
    (struct NS##_##N##_node_t*)(ALLOC(sizeof(struct NS##_##N##_node_t)))

#define DARRAY(NS, T, N, INITSIZE)                                              \
    CMP_FNS(NS, T, N);                                                          \
static const char __attribute__((unused))                                       \
            NS##_##N##_sassertsizeless[INITSIZE <=0 ? -1 : 1];                  \
    typedef struct NS##_##N##_t                                                 \
    {                                                                           \
        size_t size, count;                                                     \
        T* pData;                                                               \
    } NS##_##N##_t;                                                             \
                                                                                \
    typedef int (*T##cmpfn)(T, T);                                              \
                                                                                \
     NS##_##N##_t* NS##_##N##_init(void)                                        \
    {                                                                           \
        NS##_##N##_t* pN = (NS##_##N##_t*)malloc(sizeof(NS##_##N##_t));         \
        if (!pN) return NULL;                                                   \
        else {                                                                  \
            pN->pData = (T*)calloc(INITSIZE, sizeof(T));                        \
            if (!pN->pData) { free(pN); return NULL; }                          \
            else {                                                              \
                pN->count = 0;                                                  \
                pN->size = INITSIZE;                                            \
                return pN;                                                      \
                }                                                               \
            }                                                                   \
    }                                                                           \
                                                                                \
    static void NS##_##N##_wiffull(NS##_##N##_t* _this)                         \
    {                                                                           \
        if (!(_this->count < _this->size-1)) {                                  \
        T* t = (T*)realloc(_this->pData,                                        \
                            sizeof(T)* _this->size * 2);                        \
        if (t) {                                                                \
            _this->pData = t;                                                   \
            _this->size *= 2;                                                   \
            }                                                                   \
        }                                                                       \
    }                                                                           \
                                                                                \
    static void NS##_##N##_resizeto(NS##_##N##_t* _this, size_t ns)             \
    {                                                                           \
        if (ns > _this->size-1) {                                               \
        T* t = (T*)realloc(_this->pData,                                        \
                            sizeof(T)* ns * 2);                                 \
        if (t) {                                                                \
            _this->pData = t;                                                   \
            _this->size = ns * 2;                                               \
            }                                                                   \
        }                                                                       \
    }                                                                           \
                                                                                \
    static void NS##_##N##_add(T item, NS##_##N##_t* _this)                     \
        {                                                                       \
            NS##_##N##_wiffull(_this);                                          \
            *(_this->pData+_this->count) = item;                                \
            _this->count++;                                                     \
        }                                                                       \
                                                                                \
    static T* NS##_##N##_getat(size_t idx, NS##_##N##_t* _this)                 \
    {                                                                           \
        if (idx < _this->count)                                                 \
            return &_this->pData[idx];                                          \
        else return NULL;                                                       \
    }                                                                           \
                                                                                \
    void NS##_##N##_cleanup(NS##_##N##_t** _this)                               \
    {                                                                           \
        if (*_this) {                                                           \
            if ((*_this)->pData)                                                \
                free((*_this)->pData);                                          \
            (*_this)->pData = NULL;                                             \
            free(*_this);                                                       \
            (*_this) = NULL;                                                    \
        }                                                                       \
    }                                                                           \
                                                                                \
    static void NS##_##N##_add_at(T item, size_t idx, NS##_##N##_t* _this)      \
    {                                                                           \
        NS##_##N##_resizeto(_this, idx);                                        \
        *(_this->pData+idx) = item;                                             \
        _this->count++;                                                         \
    }                                                                           \
                                                                                \
    static T* NS##_##N##_find_if                                                 \
        (T item, NS##_##N##_t* _this, T##cmpfn cmp)                             \
    {                                                                           \
        size_t i;                                                               \
        for(i=0; i < _this->count; i++) {                                       \
            if (cmp(item, _this->pData[i]))                                     \
                return &_this->pData[i];                                        \
        }                                                                       \
        return NULL;                                                            \
    }                                                                           \
                                                                                \
    void NS##_##N##_foo(void) { printf("foooooo \r\n");}

#define BHEAP(NS, T, N, INITSIZE)                                               \
    CMP_FNS(NS, T, N);                                                          \
    DARRAY(NS, T, N##_arr, INITSIZE)                                            \
    typedef struct NS##_##N##_t {                                               \
        NS##_##N##_arr_t* array;                                                \
    } NS##_##N##_t;                                                             \
                                                                                \
                                                                                \
    NS##_##N##_t* NS##_##N##_init(void)                                         \
    {                                                                           \
        NS##_##N##_t* bh = (NS##_##N##_t*)calloc(1, sizeof(NS##_##N##_t));      \
        if (bh) {                                                               \
            bh->array = NS##_##N##_arr_init();                                  \
            if (!bh->array) {                                                   \
                free(bh);                                                       \
                return NULL;                                                    \
            }                                                                   \
         }                                                                      \
            return bh;                                                          \
    }                                                                           \
                                                                                \
                                                                                \
                                                                                \
    void NS##_##N##_cleanup(NS##_##N##_t** _this)                               \
    {                                                                           \
        printf("cleanup of bheap\r\n");                                         \
        NS##_##N##_arr_cleanup(&((*_this)->array));                             \
        if ((*_this)) { free((*_this)); (*_this)=NULL; }                        \
    }                                                                           \
                                                                                \
    static T NS##_##N##_parent(size_t idx, NS##_##N##_t* _this)                 \
    {                                                                           \
        return _this->array->pData[(idx-1)/2];                                  \
    }                                                                           \
                                                                                \
    static T NS##_##N##_left(size_t idx, NS##_##N##_t* _this)                   \
    {                                                                           \
        return _this->array->pData[(idx* 2)+1];                                 \
    }                                                                           \
                                                                                \
    static T NS##_##N##_right(size_t idx, NS##_##N##_t* _this)                  \
    {                                                                           \
        return _this->array->pData[(idx* 2)+2];                                 \
    }                                                                           \


#define LLIST(NS, T, N)                                                         \
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
    } NS##_##N##_t;                                                             \
                                                                                \
    typedef int (*T##cmpfn)(T, T);                                              \
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
    static struct NS##_##N##_node_t*                                            \
        NS##_##N##_find_if(const T element, NS##_##N##_t* _this, T##cmpfn cmp)  \
    {                                                                           \
        struct NS##_##N##_node_t* it  = _this->pHead;                           \
        while (it) {                                                            \
            if (cmp(it->pData, element))                                        \
                    return it;                                                  \
            it = it->next;                                                      \
        }                                                                       \
        return NULL;                                                            \
    }

#define BTREE(NS, T, N)                                                         \
    CMP_FNS(NS, T, N);                                                          \
                                                                                \
    struct NS##_##N##_node_t                                                    \
    {                                                                           \
        struct NS##_##N##_node_t* left,*right;                                  \
        T pData;                                                                \
    };                                                                          \
                                                                                \
    typedef struct NS##_##N##_t                                                 \
    {                                                                           \
        struct NS##_##N##_node_t *pRoot;                                        \
        NS##_##N##_CMP_##T cmpfns;                                              \
    } ;                                                                         \
                                                                                \
    struct NS##_##N##_t* NS##_##N##_init(void)                                  \
    {                                                                           \
        struct NS##_##N##_t* pl = (struct NS##_##N##_t*)                        \
                calloc(1, sizeof(struct NS##_##N##_t));                         \
        if (pl){                                                                \
            pl->pRoot = NULL;                                                   \
            return pl;                                                          \
        }                                                                       \
        return NULL;                                                            \
    }                                                                           \
    static struct NS##_##N##_node_t*                                            \
    _insert_(T item, struct NS##_##N##_node_t* root, NS##_##N##_CMP_##T cmp)    \
    {                                                                           \
        struct NS##_##N##_node_t* n = NEW_NODE(NS, N, malloc);                  \
        if (n) {                                                                \
            n->pData = item;                                                    \
            n->left = n->right = NULL;                                          \
        }                                                                       \
        if (root==NULL)                                                         \
            return n;                                                           \
        if (cmp.__lt__(root->pData, item))                                      \
                root->left = _insert_(item, root->left, cmp);                   \
        else                                                                    \
            root->right = _insert_(item, root->right, cmp);                     \
        return root;                                                            \
    }                                                                           \
                                                                                \
    static void NS##_##N##_insert(T item, struct NS##_##N##_t* _this)           \
    {                                                                           \
            _this->pRoot = _insert_                                             \
                (item, _this->pRoot, _this->cmpfns);                            \
    }                                                                           \
                                                                                \
    extern void NS##_##N##_cleanup(struct NS##_##N##_t** _this)                 \
    {                                                                           \
    }




#endif // ADT_T_H
