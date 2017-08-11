#
# Brother sane backend Driver
#
# Copyright (C) 2017 Norbert Eicker <norbert.eicker@gmx.de>
#
# This file may be distributed under the terms of the GNU GENERAL PUBLIC LICENSE
# as defined in the file Copying included in the packaging of this file.
#

AC_PREREQ([2.68])

AC_INIT([Brother sane backend Driver], [0.2.4],
  [norbert.eicker@gmx.de], [brscan], [https://github.com/neicker/brscan/])
AC_CONFIG_SRCDIR([configure.ac])
AC_CONFIG_AUX_DIR([scripts])
AC_CONFIG_MACRO_DIR([m4])

AC_CANONICAL_TARGET

AM_INIT_AUTOMAKE([foreign -Wall -Wno-portability silent-rules subdir-objects no-define])
AM_MAINTAINER_MODE
AM_SILENT_RULES([yes])

# enable runpath. this has to be set before LT_INIT.
LDFLAGS="$LDFLAGS -Wl,--enable-new-dtags"

AC_PROG_LN_S

AC_PROG_CC
AM_PROG_CC_C_O

LT_INIT([dlopen disable-static])

# This is just a placeholder....
AC_CHECK_LIB([popt], [poptGetContext],
  [AC_SUBST([POPT_LIBS], [-lpopt])],
  [AC_MSG_ERROR([please install the popt devel package])])

AX_CHECK_COMPILE_FLAG([-Wall -Wextra -Wno-unused-parameter],
  [AM_CFLAGS="$AM_CFLAGS -Wall -Wextra -Wno-unused-parameter"])

AX_CHECK_COMPILE_FLAG([-fstack-protector-all],
  [AM_CFLAGS="$AM_CFLAGS -fstack-protector-all"])

AX_CHECK_COMPILE_FLAG([-fno-strict-aliasing],
  [AM_CFLAGS="$AM_CFLAGS -fno-strict-aliasing"])

AC_SUBST([AM_CFLAGS])
AC_SUBST([AM_LDFLAGS])

PKG_PROG_PKG_CONFIG

AC_CONFIG_FILES(Makefile)
AC_CONFIG_FILES(backend_brscan/Makefile)
AC_CONFIG_FILES(include/sane/Makefile)
AC_CONFIG_FILES(libbrcolm/Makefile)
AC_CONFIG_FILES(libbrcolm/GrayCmData/Makefile)
AC_CONFIG_FILES(libbrscandec/Makefile)
AC_CONFIG_FILES(netconfig/Makefile)

AC_OUTPUT
