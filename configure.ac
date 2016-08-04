#******************************************************************************
# Copyright (c), Recep Aslantas.                                              *
#                                                                             *
# MIT License (MIT), http://opensource.org/licenses/MIT                       *
# Full license can be found in the LICENSE filespaces                         *
#                                                                             *
#******************************************************************************

AC_PREREQ([2.69])
AC_INIT([mathkit], [0.1.0], [info@recp.me])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([src/])
AC_CONFIG_HEADERS([config.h])

AC_PROG_CC
AM_PROG_CC_C_O

AC_PROG_INSTALL
AM_PROG_AR

AC_ENABLE_SHARED
AC_ENABLE_STATIC

LT_INIT


# Checks for header files.
AC_CHECK_HEADERS([stdint.h stdlib.h string.h sys/time.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_SIZE_T

AC_CONFIG_FILES([makefile])

AC_OUTPUT
