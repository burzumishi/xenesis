#!/bin/sh

aclocal
libtoolize
autoconf
automake -a

#if [ -f "configure" ]; then
	# --prefix /opt/xenesis: ./configure --prefix=/opt/xenesis --sysconfdir=/opt/xenesis/etc --localstatedir=/opt/xenesis/var
	# ./configure --prefix=/opt/xenesis --sysconfdir=/opt/xenesis/etc --localstatedir=/opt/xenesis/var

	# --prefix /usr (default)
	# ./configure --prefix=/usr --sysconfdir=/etc --localstatedir=/var
#fi;

# DEVEL DIST CLEAN ALL
# rm -rf aclocal.m4 autom4te.cache config.guess configure config.sub install-sh missing Makefile.in src/Makefile.in Makefile src/Makefile config.log config.status
