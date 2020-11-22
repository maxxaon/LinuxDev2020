#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Guess number], [0.0], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE([foreign])
DX_INIT_DOXYGEN(guess)
LT_INIT([disable-static])
AC_CONFIG_SRCDIR([guess.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PATH_PROG([HELP2MAN], [help2man])

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([libintl.h locale.h stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([realpath setlocale])

AC_CONFIG_FILES([Makefile Doxyfile guess.md])
AC_OUTPUT
