#ifndef ADT_OPQ_H
#define ADT_OPQ_H
/* opaqua pointers to use in headers, declare structs when needed */

/**
interface for the data structures
*/
#define CMP_FNS(NS, T, N)                                                       \
    typedef struct  NS##_##N##_CMP_##T{                                         \
        int (*__lt__)(const T, const T);                                        \
        int (*__gt__)(const T, const T);                                        \
        int (*__eq__)(const T, const T);                                        \
    }  NS##_##N##_CMP_##T;                                                      \
                                                                                \
    extern struct NS##_##N##_t* NS##_##N##_init(void);                          \
                                                                                \
    extern void NS##_##N##_cleanup(struct NS##_##N##_t** _this);                \
                                                                                \
    extern T* NS##_##N##_find_if(const T item, struct NS##_##N##_t* _this);




#define ADT_OPQ(NS, T, N)                                                       \
    struct  NS##_##N##_t;


#define NODE_OPQ(NS, N)                                                         \
    struct NS##_##N##_node_t;

#define NEW_(NS, N, ALLOC)                                                      \
    (struct NS##_##N##_t*)(ALLOC(sizeof(struct NS##_##N##_t)))

#define NEW_NODE(NS, N, ALLOC)                                                  \
    (struct NS##_##N##_node_t*)(ALLOC(sizeof(struct NS##_##N##_node_t)))

#define CLEANUP(NS, N, SELF, DEL)                                               \
    NS##_##N##_cleanup(&SELF);                                                  \
    DEL(SELF)

#endif // DYNARRAY_OPQ_H
