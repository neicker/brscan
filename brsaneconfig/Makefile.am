#
# Brother sane backend Driver
#
# Copyright (C) 2017 Norbert Eicker <norbert.eicker@gmx.de>
#
# This file may be distributed under the terms of the GNU GENERAL PUBLIC LICENSE
# as defined in the file Copying included in the packaging of this file.
#

include $(top_srcdir)/common.am

bin_PROGRAMS = brsaneconfig

noinst_HEADERS = resource.h

brsaneconfig_SOURCES = brsaneconfig.c ../libsane-brother/brother_advini.c

brsaneconfig_CPPFLAGS = $(AM_CPPFLAGS) -DBRSANESUFFIX=1	\
	-I$(top_srcdir)/libsane-brother

noinst_HEADER = resource.h
