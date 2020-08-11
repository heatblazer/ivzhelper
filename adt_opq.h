#ifndef ADT_OPQ_H
#define ADT_OPQ_H
/* opaqua pointers to use in headers, declare structs when needed */

#define CMP_FNS(NS, T, N)                                                       \
typedef struct  {                                                               \
        int (*NS##_##N##__lt__)(const T, const T);                              \
        int (*NS##_##N##__gt__)(const T, const T);                              \
        int (*NS##_##N##__eq__)(const T, const T);                              \
    }  NS##_##N##_CMP_##T;



#define DARRAY_OPQ(NS, T, N)                                                    \
    struct  NS##_##N##_t;                                                       \



#define NODE_OPQ(N)                                                             \
    struct N##_node_t;                                                          \
    struct N##_t;


#endif // DYNARRAY_OPQ_H
