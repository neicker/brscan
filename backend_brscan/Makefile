SHELL = /bin/sh


srcdir = .
top_srcdir = ..
top_builddir = ..

PACKAGE = sane-backends
VERSION = 1.0.7
distdir = $(top_srcdir)/$(PACKAGE)-$(VERSION)

prefix = /usr/local
exec_prefix = ${prefix}
bindir = ${exec_prefix}/bin
sbindir = ${exec_prefix}/sbin
libexecdir = ${exec_prefix}/libexec
datadir = ${prefix}/share
sysconfdir = ${prefix}/etc
sharedstatedir = ${prefix}/com
localstatedir = ${prefix}/var
libdir = ${exec_prefix}/lib
libsanedir = $(libdir)/sane
infodir = ${prefix}/info
mandir = ${prefix}/man
includedir = ${prefix}/include
oldincludedir = /usr/include
configdir = ${sysconfdir}/sane.d

V_MAJOR = 1
V_MINOR = 0
V_REV = 7

MKDIR = $(top_srcdir)/mkinstalldirs
INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644
RANLIB = ranlib
LN_S = ln -s

CC = gcc
INCLUDES = -I. -I$(srcdir) -I$(top_builddir)/include -I$(top_srcdir)/include\
           -I$(top_srcdir)/libbrscandec -I$(top_srcdir)/libbrcolm

CPPFLAGS = -D_GNU_SOURCE -DPATH_SANE_CONFIG_DIR=$(configdir) -DV_MAJOR=1 -DV_MINOR=0
CFLAGS =  -O0 -W -Wall
TARGETSUFFIX = -DBRSANESUFFIX=1
#LDFLAGS = 
LDFLAGS = -lpthread
BACKENDLIBS = -lnsl -lusb -lm  -ldl
DEFS = -DHAVE_CONFIG_H

LIBTOOL = ../libtool
MCOMP	= --mode=compile
MLINK	= --mode=link
MINST	= --mode=install

COMPILE = $(CC) -c $(CFLAGS) $(DEFS) $(INCLUDES) $(CPPFLAGS) $(LDFLAGS) $(TARGETSUFFIX)
#COMPILE = $(CC) -c $(CFLAGS) $(DEFS) $(INCLUDES) $(CPPFLAGS) $(LDFLAGS)
#COMPILE = $(CC) -c $(CFLAGS) $(DEFS) $(INCLUDES) $(CPPFLAGS)

PRELOADABLE_BACKENDS = brother

BRLIBS = $(addprefix libsane-,$(addsuffix .la,$(PRELOADABLE_BACKENDS)))

EXTRA = sane_strstatus.lo ../sanei/sanei_init_debug.lo ../sanei/sanei_config.lo

DISTFILES = Makefile.in \
  dll.aliases dll.c dll.conf dll.desc sane_strstatus.c stubs.c\
  brother_cmatch.c brother_cmatch.h\
  brother_devaccs.c brother_devaccs.h brother_devinfo.c brother_devinfo.h\
  brother_dtype.h brother_log.c brother_log.h brother_mfccmd.c brother_mfccmd.h\
  brother_mfcinfo.h brother_misc.c brother_misc.h brother_modelinf.c\
  brother_modelinf.h brother_scanner.c brother_scanner.h\
  brother.c brother.h brother_netdev.c brother_netdev.h brother_advini.c brother_advini.h

.PHONY: all clean depend dist distclean install uninstall

libsane-%.la: %.lo %-s.lo $(EXTRA)  *.c *.h
	@$(LIBTOOL) $(MLINK) $(CC) -export-dynamic -o $@ $($*_LIBS) \
	$(LDFLAGS) $(BACKENDLIBS) $^ -rpath $(libsanedir) \
	-version-info $(V_MAJOR):$(V_REV):$(V_MINOR)

%-s.lo:	%-s.c
	@$(LIBTOOL) $(MCOMP) $(COMPILE) -DSTUBS -DBACKEND_NAME=$* $<

%.lo:	%.c
	@$(LIBTOOL) $(MCOMP) $(COMPILE) -DBACKEND_NAME=$* \
		-DLIBDIR=$(libsanedir) $<

%-s.c:	$(srcdir)/stubs.c
	rm -f $@
	$(LN_S) $(srcdir)/stubs.c $@

# Don't delete any intermediate files.
.PRECIOUS: %-s.c %-s.lo %.lo

brscan:
	sh mk_backend

all:	$(BRLIBS)

install:
	$(MKDIR) $(libdir) $(libsanedir) $(configdir)
	@list="$(BRLIBS)"; for be in $$list; do \
	  echo installing $${be} in $(libsanedir)...; \
	  $(LIBTOOL) $(MINST) $(INSTALL_PROGRAM) $${be} $(libsanedir)/$${be} \
	    || exit 1; \
	done

uninstall:
	rm -rf $(libsanedir) $(configdir)
	rm -f $(libdir)/libsane.*

# additional dependencies

# We must not build SANE backend libraries that contain unresolved references
# to any of the sanei routines.  These explicit dependencies take care of
# this:

libsane-brother.la: ../sanei/sanei_constrain_value.lo

depend:
	makedepend $(INCLUDES) *.c

clean:
	rm -f *.lo *.o *~ *.la libsane.la *.bak dll-preload.c
	find . -type l -name \*-s.c | xargs rm -f
	rm -rf .libs

distclean: clean
	rm -f Makefile libsane.so

dist: $(DISTFILES)
	for file in $(DISTFILES); do \
	  ln $$file $(distdir)/backend 2> /dev/null \
	    || cp -p $$file $(distdir)/backend ; \
	done
