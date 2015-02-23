CLEANFILES = log.conf editor.conf ssh.conf plugins.conf network.conf *~

confddir = $(sysconfdir)/@PACKAGE@/conf.d
confd_DATA = editor.conf log.conf ssh.conf plugins.conf network.conf

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

log.conf: log.conf.in Makefile
	$(do_subst) < $(srcdir)/log.conf.in > log.conf;

editor.conf: editor.conf.in Makefile
	$(do_subst) < $(srcdir)/editor.conf.in > editor.conf;

ssh.conf: ssh.conf.in Makefile
	$(do_subst) < $(srcdir)/ssh.conf.in > ssh.conf;

plugins.conf: plugins.conf.in Makefile
	$(do_subst) < $(srcdir)/plugins.conf.in > plugins.conf;

network.conf: network.conf.in Makefile
	$(do_subst) < $(srcdir)/network.conf.in > network.conf;

all-local: log.conf editor.conf ssh.conf plugins.conf network.conf
