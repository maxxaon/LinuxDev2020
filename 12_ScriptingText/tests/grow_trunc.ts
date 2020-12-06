#include "buf.h"

/* buf_grow(), buf_trunc() */
#test tbuf_grow_trunc
    long *ai = 0;
    buf_grow(ai, 1000);
    ck_assert_uint_eq(buf_capacity(ai), 1000);
    ck_assert_uint_eq(buf_size(ai), 0);
    buf_trunc(ai, 100);
    ck_assert_uint_eq(buf_capacity(ai), 100);