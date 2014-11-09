CLEANFILES = xenesis libxenesis-ral.so libxenesis.so *~

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

libxenesis.so: libxenesis.so.in Makefile
	$(do_subst) < $(srcdir)/libxenesis.so.in > libxenesis.so; \
	chmod +x libxenesis.so

libxenesis-ral.so: libxenesis-ral.so.in Makefile
	$(do_subst) < $(srcdir)/libxenesis-ral.so.in > libxenesis-ral.so; \
	chmod +x libxenesis-ral.so

xenesis: xenesis.in Makefile
	$(do_subst) < $(srcdir)/xenesis.in > xenesis; \
	chmod +x xenesis

all-local: libxenesis.so libxenesis-ral.so xenesis
