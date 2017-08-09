SHELL = /bin/sh


srcdir = .
top_srcdir = ..
top_builddir = ..

PACKAGE = sane-backends
VERSION = 1.0.7
distdir = $(top_srcdir)/$(PACKAGE)-$(VERSION)

prefix = /usr/local
sysconfdir = ${prefix}/etc
configdir = ${sysconfdir}/sane.d

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644

CC = gcc
INCLUDES = -I. -I$(srcdir) -I$(top_builddir)/include -I$(top_srcdir)/include
CPPFLAGS =  -D_GNU_SOURCE -DPATH_SANE_CONFIG_DIR=$(configdir) -DV_MAJOR=1 -DV_MINOR=0
CFLAGS = -g -O2 -W -Wall
DEFS = -DHAVE_CONFIG_H

 COMPILE = $(CC) -c $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)
LIBTOOL = ../libtool
MCOMP	= --mode=compile

TARGETS = sanei_config.o sanei_constrain_value.o sanei_init_debug.o

DISTFILES = Makefile.in sanei_config.c sanei_constrain_value.c	\
	sanei_init_debug.c

.PHONY: all check clean depend dist distclean install uninstall

.SUFFIXES:
.SUFFIXES: .c .o
.c.o:
	@$(LIBTOOL) $(MCOMP) $(COMPILE) $<
	@test -f $@ || $(COMPILE) $<

all:	$(TARGETS)

install:

uninstall:

depend:
	makedepend -I. -I../include *.c

clean:
	rm -f *.out *.o *.lo *~ *.a *.bak
	rm -rf .libs

distclean: clean
	rm -f Makefile

dist: $(DISTFILES)
	for file in $(DISTFILES); do \
	  ln $$file $(distdir)/sanei 2> /dev/null \
	    || cp -p $$file $(distdir)/sanei ; \
	done
