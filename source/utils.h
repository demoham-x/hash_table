
#ifndef UTILS_H
#define UTILS_H
#include "common.h"

UCHAR is_prime(DECL_CONST INT32 x);
INT32 next_prime(INT32 x);
CHAR * rand_word
       (
            INT32 min_len,
            INT32 max_len
       );
#endif /* UTILS_H*/