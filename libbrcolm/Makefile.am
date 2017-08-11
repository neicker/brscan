#
# Brother sane backend Driver
#
# Copyright (C) 2017 Norbert Eicker <norbert.eicker@gmx.de>
#
# This file may be distributed under the terms of the GNU GENERAL PUBLIC LICENSE
# as defined in the file Copying included in the packaging of this file.
#

include $(top_srcdir)/common.am

SUBDIRS = GrayCmData

dist_noinst_DATA = libbrcolm.so.1.0.1

noinst_HEADERS = brcolor.h

install-data-local:
	$(INSTALL) -D -t $(DESTDIR)$(libdir) $(dist_noinst_DATA) && \
	cd $(DESTDIR)$(libdir) && \
	$(LN_S) $(dist_noinst_DATA) $(basename $(basename $(dist_noinst_DATA)))
