CLEANFILES = libxenesis.la libxenesis-debug.la libxenesis-env.la libxenesis-log.la libxenesis-net.la libxenesis-ral.la libxenesis-ssh.la libxenesis-sshnopass.la xenesis$(EXEEXT) *~

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

xenesis_SOURCES = xenesis.c libxenesis.c libxenesis-debug.c libxenesis-env.c libxenesis-log.c libxenesis-net.c libxenesis-ral.c libxenesis-ssh.c libxenesis-sshnopass.c

sbin_PROGRAMS = xenesis$(EXEEXT)

libxenesisdir = $(libdir)
libxenesis_DATA = libxenesis.la libxenesis-debug.la libxenesis-log.la libxenesis-env.la libxenesis-net.la libxenesis-ral.la libxenesis-ssh.la libxenesis-sshnopass.la

libxenesis.la: libxenesis.c Makefile
	$(do_subst) < $(srcdir)/libxenesis.c > libxenesis.la; \
	chmod +x libxenesis.la

libxenesis-debug.la: libxenesis-debug.c Makefile
	$(do_subst) < $(srcdir)/libxenesis-debug.c > libxenesis-debug.la; \
	chmod +x libxenesis-debug.la

libxenesis-env.la: libxenesis-env.c Makefile
	$(do_subst) < $(srcdir)/libxenesis-env.c > libxenesis-env.la; \
	chmod +x libxenesis-env.la

libxenesis-log.la: libxenesis-log.c Makefile
	$(do_subst) < $(srcdir)/libxenesis-log.c > libxenesis-log.la; \
	chmod +x libxenesis-log.la

libxenesis-net.la: libxenesis-net.c Makefile
	$(do_subst) < $(srcdir)/libxenesis-net.c > libxenesis-net.la; \
	chmod +x libxenesis-net.la

libxenesis-ral.la: libxenesis-ral.c Makefile
	$(do_subst) < $(srcdir)/libxenesis-ral.c > libxenesis-ral.la; \
	chmod +x libxenesis-ral.la

libxenesis-ssh.la: libxenesis-ssh.c Makefile
	$(do_subst) < $(srcdir)/libxenesis-ssh.c > libxenesis-ssh.la; \
	chmod +x libxenesis-ssh.la

libxenesis-sshnopass.la: libxenesis-sshnopass.c Makefile
	$(do_subst) < $(srcdir)/libxenesis-sshnopass.c > libxenesis-sshnopass.la; \
	chmod +x libxenesis-sshnopass.la

xenesis$(EXEEXT): xenesis.c Makefile
	$(do_subst) < $(srcdir)/xenesis.c > xenesis$(EXEEXT); \
	chmod +x xenesis$(EXEEXT);

all-local: libxenesis.la libxenesis-debug.la libxenesis-env.la libxenesis-log.la libxenesis-net.la libxenesis-ral.la libxenesis-ssh.la libxenesis-sshnopass.la xenesis$(EXEEXT)
