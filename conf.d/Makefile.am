CLEANFILES = ssh.conf log.conf editor.conf linux.conf hpux.conf cygwin.conf default_os.conf *~

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

ssh.conf: ssh.conf.in Makefile
	$(do_subst) < $(srcdir)/ssh.conf.in > ssh.conf;

log.conf: log.conf.in Makefile
	$(do_subst) < $(srcdir)/log.conf.in > log.conf;

editor.conf: editor.conf.in Makefile
	$(do_subst) < $(srcdir)/editor.conf.in > editor.conf;

linux.conf: linux.conf.in Makefile
	$(do_subst) < $(srcdir)/linux.conf.in > linux.conf;

hpux.conf: hpux.conf.in Makefile
	$(do_subst) < $(srcdir)/hpux.conf.in > hpux.conf;

cygwin.conf: cygwin.conf.in Makefile
	$(do_subst) < $(srcdir)/cygwin.conf.in > cygwin.conf;

default_os.conf: default_os.conf.in Makefile
	$(do_subst) < $(srcdir)/default_os.conf.in > default_os.conf;

all-local: ssh.conf log.conf editor.conf linux.conf hpux.conf cygwin.conf default_os.conf
