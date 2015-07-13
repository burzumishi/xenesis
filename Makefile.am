#!@ENV@ make -f

#      _____________________________________________________________________
#     /                                                                     \
#     |                         -*- Makefile -*-                            |
#     |_____________________________________________________________________|
#    //                                                                     \\
#   [|  XENESIS 2.0 © 2014-2015 Antonio Cao (@burzumishi)                    |]
#    \\_____________________________________________________________________//

CC = gcc
CPP = cpp
CXX = g++

USER = xenesis
GROUP = xenesis

ARCH = `getconf LONG_BIT`

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = etc src po

EXTRA_DIST = m4/ChangeLog  config.rpath m4/ChangeLog autogen.sh hosts plugins \
	doc etc src man db README.md LICENSE m4 libtool autom4te.cache \
	missing compile config.guess config.sub depcomp aclocal.m4 \
	Doxyfile.in doc/html po ABOUT-NLS *.m4 TODO

do_subst = sed -e 's,[@]sharedstatedir[@],$(sharedstatedir),g' \
		-e 's,[@]localstatedir[@],$(localstatedir),g' \
		-e 's,[@]sysconfdir[@],$(sysconfdir),g' \
		-e 's,[@]includedir[@],$(includedir),g' \
		-e 's,[@]datarootdir[@],$(datarootdir),g' \
		-e 's,[@]localedir[@],$(localedir),g' \
		-e 's,[@]prefix[@],$(prefix),g' \
		-e 's,[@]bindir[@],$(bindir),g' \
		-e 's,[@]sbindir[@],$(sbindir),g' \
		-e 's,[@]libdir[@],$(libdir),g' \
		-e 's,[@]mandir[@],$(mandir),g' \
		-e 's,[@]PERL[@],$(PERL),g' \
		-e 's,[@]ENV[@],$(ENV),g' \
		-e 's,[@]BASH[@],$(BASH),g' \
		-e 's,[@]USER[@],$(USER),g' \
		-e 's,[@]GROUP[@],$(GROUP),g' \
		-e 's,[@]CC[@],$(CC),g' \
		-e 's,[@]CXX[@],$(CXX),g' \
		-e 's,[@]PACKAGE[@],$(PACKAGE),g' \
		-e 's,[@]VERSION[@],$(VERSION),g' \
		-e 's,[@]DESCRIPTION[@],$(DESCRIPTION),g'

docdir = $(datarootdir)/doc/@PACKAGE@
doc_DATA = README AUTHORS INSTALL NEWS LICENSE ChangeLog \
	doc/*.txt ABOUT-NLS

DATAFILES = plugins hosts

localedir = $(datadir)/locale
DEFS = -DLOCALEDIR=\"$(localedir)\" @DEFS@

man_MANS = man/xenesis.1 man/xenesisd.1

CLEANDEVELFILES = compile configure depcomp src/xenesis.h src/*.la ar-lib \
	autom4te.cache config.guess config.sub install-sh missing src/.libs \
	config.status ltmain.sh depcomp README COPYING NEWS po/*.gmo m4 *.m4 \
	src/xenesis Doxyfile po/POTFILES po/stamp-po \
	AUTHORS ChangeLog INSTALL config.lt libtool src/.deps src/*.o src/*.lo \
	`find $(srcdir) -iname "Makefile.in"` \
	`find $(srcdir) -iname "*.autogen-bak"` \
	`find $(srcdir) -iname "*~"`

CLEANBUILDFILES = config.log etc/xenesisd.conf etc/init.d/xenesisd \
	`find $(srcdir) -iname "stamp-h1"` \
	`find $(srcdir) -iname "stamp-po"` \
	`find $(srcdir) -iname "Makefile"`

CLEANFILES = $(CLEANBUILDFILES) \
	`find $(srcdir) -iname "*~"`

if HAVE_DOXYGEN
all-doc:
	@$(DOXYGEN) Doxyfile;

clean-doc:
	@rm -rf $(top_builddir)/doc/latex $(top_builddir)/doc/html;

distclean-doc:
	@rm -rf $(top_builddir)/doc/latex $(top_builddir)/doc/html;

install-doc: all-doc
	@$(mkdir_p) $(DESTDIR)$(docdir); \
	cp -rvf doc/html $(DESTDIR)$(docdir);

uninstall-doc:
	@rm -rvf $(DESTDIR)$(docdir)/html; \
	rmdir $(DESTDIR)$(docdir);
else
all-doc:
	@echo "*** WARNING! Doxygen is not available ***"; \
	echo "*** Documentation will not be built ***";

clean-doc:
	@echo "*** WARNING! Doxygen is not available ***"; \
	echo "*** Documentation will not be cleaned ***";

distclean-doc:
	@echo "*** WARNING! Doxygen is not available ***"; \
	echo "*** Documentation will not be cleaned ***";

install-doc:
	@echo "*** WARNING! Doxygen is not available ***"; \
	echo "*** Documentation will not be installed ***";

uninstall-doc:
	@echo "*** WARNING! Doxygen is not available ***"; \
	echo "*** Documentation will not be uninstalled ***";
endif

all-local:
	@echo "=== all-local done ==="

clean-local:
	@echo "=== clean-local done ==="

distclean-local: clean-local
	@echo "=== distclean-local done ==="

devdistclean: distclean-local distclean-doc
	@rm -rfv $(CLEANDEVELFILES) $(CLEANBUILDFILES); \
	echo "=== distclean-local done ==="

install-data-hook:
	@echo "Creating <@PACKAGE@> directory to store log files ..."; \
	mkdir -pv $(localstatedir)/log/@PACKAGE@; \
	echo "Creating <@PACKAGE@> directories to store lock and run files ..."; \
	mkdir -pv $(localstatedir)/lock/@PACKAGE@; \
	mkdir -pv $(localstatedir)/run/; \
	echo "Installing <@PACKAGE@> Plugin & Hosts data files ..."; \
	mkdir -pv $(sharedstatedir)/@PACKAGE@; \
	cp -rvf $(DATAFILES) $(sharedstatedir)/@PACKAGE@/; \
	echo "Creating user <$(USER)> and group <$(GROUP)> ..."; \
	groupadd $(GROUP) &>/dev/null; \
	useradd $(USER) -g $(GROUP) &>/dev/null; \
	echo "Setting up <$(prefix)> permissions to <$(USER):$(GROUP)> ..."; \
	chown -R $(USER):$(GROUP) $(prefix); \
	echo ""; \
	echo "<@PACKAGE@> has ben installed to <$(prefix)> directory!"; \
	echo "You can execute <$(sysconfdir)/init.d/xenesisd start> now!"; \
	echo "";
