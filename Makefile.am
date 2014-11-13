# Makefile - @PACKAGE@-@VERSION@ #

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = src etc

EXTRA_DIST = xenesis.conf.in autogen.sh README.md plugins conf.d src hosts

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
		-e 's,[@]ENV[@],$(ENV),g' \
		-e 's,[@]BASH[@],$(BASH),g' \
		-e 's,[@]PACKAGE[@],$(PACKAGE),g' \
		-e 's,[@]VERSION[@],$(VERSION),g' \
		-e 's,[@]DESCRIPTION[@],$(DESCRIPTION),g'

xenesis.conf: xenesis.conf.in Makefile
	$(do_subst) < $(srcdir)/xenesis.conf.in > xenesis.conf

docdir = $(datarootdir)/doc/@PACKAGE@
doc_DATA = README AUTHORS INSTALL NEWS LICENSE ChangeLog 

man_MANS=man/xenesis.1

all-local:
	@echo "=== all-local done ==="

clean-local:
	@echo "=== clean-local done ==="

distclean-local:
	@rm -rfv aclocal.m4 AUTHORS autom4te.cache config.guess \
	configure config.sub COPYING INSTALL install-sh missing NEWS README \
	Makefile.in src/Makefile.in Makefile src/Makefile compile \
	config.log config.status \
	etc/os/Makefile.in etc/Makefile.in etc/conf.d/Makefile.in; \
	etc/os/Makefile etc/Makefile etc/conf.d/Makefile; \
	echo "=== distclean-local done ==="

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
	mkdir -pv $(sysconfdir)/@PACKAGE@/os; \
	cp -rfv etc/conf.d/editor.conf $(sysconfdir)/@PACKAGE@/conf.d/editor.conf; \
	cp -rfv etc/conf.d/ssh.conf $(sysconfdir)/@PACKAGE@/conf.d/ssh.conf; \
	cp -rfv etc/conf.d/log.conf $(sysconfdir)/@PACKAGE@/conf.d/log.conf; \
	cp -rfv etc/os/default.conf $(sysconfdir)/@PACKAGE@/os/default.conf; \
	cp -rfv etc/os/linux.conf $(sysconfdir)/@PACKAGE@/os/linux.conf; \
	cp -rfv etc/os/freebsd.conf $(sysconfdir)/@PACKAGE@/os/freebsd.conf; \
	cp -rfv etc/os/hpux.conf $(sysconfdir)/@PACKAGE@/os/hpux.conf; \
	cp -rfv etc/os/cygwin.conf $(sysconfdir)/@PACKAGE@/os/cygwin.conf; \
	echo "Installing <<@PACKAGE@>> data files ..."; \
	mkdir -pv $(localstatedir)/lib/@PACKAGE@; \
	cp -rfv plugins $(localstatedir)/lib/@PACKAGE@/; \
	cp -rfv hosts $(localstatedir)/lib/@PACKAGE@/; \
	mkdir -pv $(prefix)/share/@PACKAGE@; \
	echo ""; \
	echo "<<@PACKAGE@>> has ben installed on <<$(prefix)>> directory!"; \
	echo "You can run <<@PACKAGE@>> now!"; \
	echo "";
