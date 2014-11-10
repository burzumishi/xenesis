# Makefile - @PACKAGE@-@VERSION@ #

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = src conf.d

EXTRA_DIST = xenesis.conf.in autogen.sh Doxyfile.in README.md plugins conf.d src hosts

CLEANFILES = xenesis.conf *~

etcdir = $(sysconfdir)/@PACKAGE@
etc_DATA = xenesis.conf

do_subst = sed -e 's,[@]sharedstatedir[@],$(sharedstatedir),g' \
		-e 's,[@]localstatedir[@],$(localstatedir),g' \
		-e 's,[@]sysconfdir[@],$(sysconfdir),g' \
		-e 's,[@]prefix[@],$(prefix),g' \
		-e 's,[@]bindir[@],$(bindir),g' \
		-e 's,[@]libdir[@],$(libdir),g' \
		-e 's,[@]mandir[@],$(mandir),g' \
		-e 's,[@]PERL[@],$(PERL),g' \
		-e 's,[@]PACKAGE[@],$(PACKAGE),g' \
		-e 's,[@]VERSION[@],$(VERSION),g' \
		-e 's,[@]DESCRIPTION[@],$(DESCRIPTION),g'

xenesis.conf: xenesis.conf.in Makefile
	$(do_subst) < $(srcdir)/xenesis.conf.in > xenesis.conf

docdir = $(datarootdir)/doc/@PACKAGE@
doc_DATA = README AUTHORS INSTALL NEWS LICENSE ChangeLog 

#  install the man page
man_MANS=man/xenesis.1

all-local:
	@echo "=== all-local done ==="

clean-local: clean-doc
	@echo "=== clean-local done ==="

distclean-local: distclean-doc
	@rm -rfv  rm -rf aclocal.m4 AUTHORS autom4te.cache config.guess \
	configure config.sub COPYING INSTALL install-sh missing NEWS README \
	Makefile.in src/Makefile.in Makefile src/Makefile compile \
	config.log config.status conf.d/Makefile.in conf.d/Makefile; \
	echo "=== distclean-local done ==="

install-data-local: all-doc install-doc
	@echo "=== install-data-local done ==="

uninstall-local: uninstall-doc
	@echo "=== uninstall-local done ==="

if HAVE_DOXYGEN
all-doc:
	$(DOXYGEN) Doxyfile

clean-doc:
	rm -rf $(top_builddir)/doc

distclean-doc:
	rm -rf $(top_builddir)/doc

install-doc:
	$(mkdir_p) $(DESTDIR)$(docdir)
	cp -rf doc/html $(DESTDIR)$(docdir)

uninstall-doc:
	-rm -rf $(DESTDIR)$(docdir)/html
	-rmdir $(DESTDIR)$(docdir)
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

install-data-hook:
	@echo "Installing <<@PACKAGE@>> files ..."; \
	mkdir -pv $(bindir) $(libdir); \
	cp -rfv src/xenesis $(bindir)/xenesis; \
	cp -rfv src/libxenesis.so $(libdir)/libxenesis.so; \
	cp -rfv src/libxenesis-ral.so $(libdir)/libxenesis-ral.so; \
	cp -rfv src/libxenesis-net.so $(libdir)/libxenesis-net.so; \
	cp -rfv src/libxenesis-ssh.so $(libdir)/libxenesis-ssh.so; \
	cp -rfv src/libxenesis-sshnopass.so $(libdir)/libxenesis-sshnopass.so; \
	echo "Installing <<@PACKAGE@>> config files ..."; \
	mkdir -pv $(sysconfdir)/@PACKAGE@/conf.d; \
	cp -rfv conf.d/editor.conf $(sysconfdir)/@PACKAGE@/conf.d/editor.conf; \
	cp -rfv conf.d/ssh.conf $(sysconfdir)/@PACKAGE@/conf.d/ssh.conf; \
	cp -rfv conf.d/log.conf $(sysconfdir)/@PACKAGE@/conf.d/log.conf; \
	echo "Installing <<@PACKAGE@>> data files ..."; \
	mkdir -pv $(localstatedir)/lib/@PACKAGE@; \
	cp -rfv plugins $(localstatedir)/lib/@PACKAGE@/; \
	cp -rfv hosts $(localstatedir)/lib/@PACKAGE@/; \
	mkdir -pv $(prefix)/share/@PACKAGE@; \
	echo ""; \
	echo "<<@PACKAGE@>> has ben installed on <<$(prefix)>> directory!"; \
	echo "You can run <<@PACKAGE@>> now!"; \
	echo "";
