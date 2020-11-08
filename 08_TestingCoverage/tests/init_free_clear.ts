#include "buf.h"

/* initialization, buf_free() */
#test tbuf_init_free
    float *a = 0;
    ck_assert_uint_eq(buf_capacity(a), 0);
    ck_assert_uint_eq(buf_size(a), 0);
    buf_push(a, 1.3f);
    ck_assert_uint_eq(buf_size(a), 1);
    ck_assert_msg(a[0] == (float)1.3f, "value");
    buf_clear(a);
    ck_assert_uint_eq(buf_size(a), 0);
    ck_assert_ptr_ne(a, 0);
    buf_free(a);
    ck_assert_ptr_eq(a, 0);

/* Clearing an NULL pointer is a no-op */
#test tbuf_clear
    float *a = 0;
    buf_clear(a);
    ck_assert_uint_eq(buf_size(a), 0);
    ck_assert_ptr_eq(a, 0);