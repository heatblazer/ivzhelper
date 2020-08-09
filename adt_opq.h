#ifndef ADT_OPQ_H
#define ADT_OPQ_H
/* opaqua pointers to use in headers, declare structs when needed */
#define DARRAY_OPQ(N) struct  N##_t;

#define NODE_OPQ(N)                                                            \
    struct N##_node_t;                                                          \
    struct N##_t;

#endif // DYNARRAY_OPQ_H
