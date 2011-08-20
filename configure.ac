#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT([mnetlib], [0.1.0], [mnetlib@googlecode.com])

AC_CONFIG_AUX_DIR([config])

AM_INIT_AUTOMAKE([foreign 1.6.3])

AC_CONFIG_SRCDIR([config.h.in])
AM_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LIBTOOL

# Checks for libraries.
#AC_CHECK_LIB(blas,dcopy_,[LIBS="-lblas ${LIBS}"],[AC_MSG_WARN([blas library must be installed, compilation might fail"]); exit 1;])
#AC_CHECK_LIB(pthread,dcopy_,[LIBS="-lpthread ${LIBS}"],[AC_MSG_WARN([pthread library must be installed, compilation might fail"]); exit 1;])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h sys/time.h sys/timeb.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_CHECK_FUNCS([ftime sqrt])

AC_CONFIG_FILES([Makefile
				 lib/Makefile
                 lib/src/Makefile])
AC_OUTPUT
