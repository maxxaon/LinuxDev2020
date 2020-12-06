TESTS = init_free_clear grow_trunc pop push
check_PROGRAMS = init_free_clear grow_trunc pop push

CFLAGS = -I$(top_builddir)/src @CHECK_CFLAGS@
LDADD = $(top_builddir)/src/libbuf.la @CHECK_LIBS@

.ts.c:
	checkmk $< > $@
