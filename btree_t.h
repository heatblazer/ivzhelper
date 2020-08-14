#ifndef BTREE_T_H
#define BTREE_T_H
#include "adt_opq.h"

// NS##_##N##_CMP_##T
//NS##_##N##_t

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


#endif // BTREE_T_H

/*
 *

*/
/*
    static struct NS##_##N##_node_t*                                            \
        _insert_                                                                \
        (T item, struct NS##_##N##_node_t* root, T##cmpfn cmp)                  \
    {                                                                           \
        struct NS##_##N##_node_t* n =                                           \
            (struct NS##_##N##_node_t*)malloc(sizeof(struct NS##_##N##_node_t));\
        if (n) {                                                                \
            n->pData = T;                                                       \
            n->left = n->right = NULL;                                          \
        }                                                                       \
        if (!root)                                                              \
            return n;                                                           \
        if (cmp(root->pData, T))                                                \
                root->left = _insert_(item, root, cmpfn);                       \
        else                                                                    \
            root->right = _insert_(item, root, cmpfn);                          \
    }                                                                           \
                                                                                \
                                                                                \
    static void NS##_##N##_insert(T item, NS##_##N##_t* _this)                  \
    {                                                                           \
            _this->pRoot = _insert_                                             \
                (item, _this->pRoot, _this->cmpfns.__lt__);                     \
    }
*/
