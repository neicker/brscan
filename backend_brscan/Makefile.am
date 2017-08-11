#
# Brother sane backend Driver
#
# Copyright (C) 2017 Norbert Eicker <norbert.eicker@gmx.de>
#
# This file may be distributed under the terms of the GNU GENERAL PUBLIC LICENSE
# as defined in the file Copying included in the packaging of this file.
#

include $(top_srcdir)/common.am

V_MAJOR = 1
V_MINOR = 0
V_REV = 7

AM_CPPFLAGS += -I$(top_srcdir)/libbrscandec -I$(top_srcdir)/libbrcolm
AM_CPPFLAGS += -D_GNU_SOURCE -DV_MAJOR=1 -DV_MINOR=0 -DBRSANESUFFIX=1

sanelibdir = $(libdir)/sane
sanelib_LTLIBRARIES = libsane-brother.la

libsane_brother_la_SOURCES = brother.c brother_cmatch.c			\
	brother_devaccs.c brother_devinfo.c brother_mfccmd.c		\
	brother_misc.c brother_modelinf.c brother_scanner.c		\
	brother_netdev.c brother_advini.c brother_log.c			\
	brother_bugchk.c sane_strstatus.c ../sanei/sanei_config.c	\
	../sanei/sanei_constrain_value.c ../sanei/sanei_init_debug.c

noinst_HEADERS = brother.h brother_bugchk.h		\
	brother_cmatch.h brother_devaccs.h brother_devinfo.h		\
	brother_dtype.h brother_log.h brother_mfccmd.h	\
	brother_mfcinfo.h brother_misc.h brother_modelinf.h		\
	brother_scanner.h brother_netdev.h brother_advini.h

noinst_LTLIBRARIES = libstubs.la

libstubs_la_SOURCES = stubs.c
libstubs_la_CPPFLAGS = $(AM_CPPFLAGS) -DSTUBS -DBACKEND_NAME=brother

libsane_brother_la_LIBADD = libstubs.la
libsane_brother_la_LDFLAGS = $(AM_LDFLAGS) -lpthread -lnsl -lusb -lm	\
	-ldl -rpath=$(libdir)/sane -version-info $(V_MAJOR):$(V_REV):$(V_MINOR)
