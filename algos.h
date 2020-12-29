#ifndef ALGOS_H
#define ALGOS_H


#define ACCUMULATE(RET, FIRST, LAST, INIT, SUM_CB)      \
    do {                                                \
        RET = INIT;                                     \
        while (FIRST != LAST){                          \
            RET = SUM_CB(RET, *FIRST);                  \
            FIRST++;                                    \
        }                                               \
    } while(0);



#endif // ALGOS_H
