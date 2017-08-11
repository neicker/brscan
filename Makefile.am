#
# Brother sane backend Driver
#
# Copyright (C) 2017 Norbert Eicker <norbert.eicker@gmx.de>
#
# This file may be distributed under the terms of the GNU GENERAL PUBLIC LICENSE
# as defined in the file Copying included in the packaging of this file.
#

include $(top_srcdir)/common.am

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = include/sane backend_brscan brsaneconfig libbrcolm libbrscandec

# EXTRA_DIST = Copying copying.brother README tests/psid

dist_noinst_DATA = Copying copying.brother brscan.spec

pkgexecdir = $(libexecdir)/brscan
dist_pkgexec_SCRIPTS = data/setupSaneScan

brscandatadir = $(datadir)/sane/brother
dist_brscandata_DATA = data/brsanenetdevice.cfg data/Brsane.ini

.PHONY: rpm
rpm: dist
	rpmbuild -ta --clean --define="_srcrpmdir $$PWD" \
	--define "_rpmdir $$PWD" \
	--define="_rpmfilename %%{NAME}-%%{VERSION}-%%{RELEASE}.%%{ARCH}.rpm" \
	$(DIST_ARCHIVES)
