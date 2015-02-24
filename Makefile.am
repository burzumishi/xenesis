# Makefile - @PACKAGE@-@VERSION@ #

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = src etc

EXTRA_DIST = autogen.sh README.md doc etc src man LICENSE m4 libtool \
	missing compile config.guess config.sub depcomp aclocal.m4 \
	autom4te.cache hosts plugins

CLEANFILES = *~

do_subst = sed -e 's,[@]sharedstatedir[@],$(sharedstatedir),g' \
		-e 's,[@]localstatedir[@],$(localstatedir),g' \
		-e 's,[@]sysconfdir[@],$(sysconfdir),g' \
		-e 's,[@]prefix[@],$(prefix),g' \
		-e 's,[@]bindir[@],$(bindir),g' \
		-e 's,[@]sbindir[@],$(sbindir),g' \
		-e 's,[@]libdir[@],$(libdir),g' \
		-e 's,[@]mandir[@],$(mandir),g' \
		-e 's,[@]PERL[@],$(PERL),g' \
		-e 's,[@]ENV[@],$(ENV),g' \
		-e 's,[@]BASH[@],$(BASH),g' \
		-e 's,[@]PACKAGE[@],$(PACKAGE),g' \
		-e 's,[@]VERSION[@],$(VERSION),g' \
		-e 's,[@]DESCRIPTION[@],$(DESCRIPTION),g'

docdir = $(datarootdir)/doc/@PACKAGE@
doc_DATA = README AUTHORS INSTALL NEWS LICENSE ChangeLog 

man_MANS=man/xenesis.1

all-local:
	@echo "=== all-local done ==="

clean-local:
	@rm -rfv Makefile src/Makefile config.log \
	etc/Makefile etc/conf.d/Makefile; \
	echo "=== clean-local done ==="

distclean-local:
	@rm -rfv configure src/Makefile.in Makefile.in \
	Makefile src/Makefile config.log autom4te.cache \
	etc/Makefile.in etc/conf.d/Makefile.in \
	etc/Makefile etc/conf.d/Makefile \
	etc/os/commands/Makefile etc/os/Makefile \
	etc/os/commands/Makefile.in etc/os/Makefile.in; \
	echo "=== distclean-local done ==="

devdistclean-local:
	@ rm -rfv aclocal.m4 autom4te.cache config.guess \
 	configure config.sub install-sh missing \
	Makefile.in src/Makefile.in Makefile src/Makefile compile \
	config.log config.status ltmain.sh depcomp \
	etc/Makefile.in etc/conf.d/Makefile.in \
	etc/Makefile etc/conf.d/Makefile m4; \
	echo "=== distclean-local done ==="

install-data-hook:
	@echo "Installing <<@PACKAGE@>> data files ..."; \
	mkdir -pv $(localstatedir)/lib/@PACKAGE@; \
	cp -rfv plugins $(localstatedir)/lib/@PACKAGE@/; \
	cp -rfv hosts $(localstatedir)/lib/@PACKAGE@/; \
	echo "<@PACKAGE@> has ben installed on <$(prefix)> directory!"; \
	echo "=== install-data-hook ===";
