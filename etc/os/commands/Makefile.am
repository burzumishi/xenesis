CLEANFILES = linux.conf hpux.conf cygwin.conf default.conf freebsd.conf *~

xenesisetcoscmddir = $(sysconfdir)/@PACKAGE@/os/commands
xenesisetcoscmd_DATA = linux.conf hpux.conf cygwin.conf default.conf freebsd.conf

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

linux.conf: linux.conf.in Makefile
	$(do_subst) < $(srcdir)/linux.conf.in > linux.conf;

hpux.conf: hpux.conf.in Makefile
	$(do_subst) < $(srcdir)/hpux.conf.in > hpux.conf;

cygwin.conf: cygwin.conf.in Makefile
	$(do_subst) < $(srcdir)/cygwin.conf.in > cygwin.conf;

freebsd.conf: freebsd.conf.in Makefile
	$(do_subst) < $(srcdir)/freebsd.conf.in > freebsd.conf;

default.conf: default.conf.in Makefile
	$(do_subst) < $(srcdir)/default.conf.in > default.conf;

all-local: linux.conf hpux.conf cygwin.conf default.conf freebsd.conf
