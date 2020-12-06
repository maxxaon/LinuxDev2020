#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Growable Memory Buffers for C99], [0.0], [mr.marinmaksim@gmail.com])
AM_INIT_AUTOMAKE([foreign])
LT_INIT([disable-static])
AC_CONFIG_SRCDIR([src/buf.h])
AC_CONFIG_HEADERS([config.h])

#
PKG_CHECK_MODULES([CHECK],[check])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([
    Makefile
	tests/Makefile
    src/Makefile])

AC_ARG_ENABLE([gcov],
    [AS_HELP_STRING([--enable-gcov],
    [use Gcov to test the test suite])],
    [],
    [enable_gcov=no])

AM_CONDITIONAL([COND_GCOV],[test '!' "$enable_gcov" = no])

AC_OUTPUT


define(COMMENT_LINE, [\/\* COMMENT:: AC_PACKAGE_NAME, AC_PACKAGE_VERSION: `date` \*\/])

sed -is /COMMENT::/d src/*.{c,h}
sed -is "1s/^/COMMENT_LINE\n/" src/*.{c,h}

echo COMMENT_LINE
