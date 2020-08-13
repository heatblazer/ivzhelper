#ifndef ADT_OPQ_H
#define ADT_OPQ_H
/* opaqua pointers to use in headers, declare structs when needed */

/**
interface for the data structures
*/
#define CMP_FNS(NS, T, N)                                                       \
typedef struct  {                                                               \
        int (*NS##_##N##__lt__)(const T, const T);                              \
        int (*NS##_##N##__gt__)(const T, const T);                              \
        int (*NS##_##N##__eq__)(const T, const T);                              \
    }  NS##_##N##_CMP_##T;                                                      \
                                                                                \
    extern struct NS##_##N##_t* NS##_##N##_init(void);                          \
                                                                                \
    extern void NS##_##N##_foo(void);




#define ADT_OPQ(NS, T, N)                                                       \
    struct  NS##_##N##_t;


#define NODE_OPQ(NS, N)                                                         \
    struct NS##_##N##_node_t;


#endif // DYNARRAY_OPQ_H
