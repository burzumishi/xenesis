#!/bin/sh

aclocal
autoconf

ln -sf LICENSE COPYING
ln -sf README.md README
ln -sf README.md AUTHORS
ln -sf README.md NEWS

automake -a

if [ -f "configure" ]; then
	./configure --prefix=/opt/xenesis
fi;

# CLEAN
# rm -rf aclocal.m4 AUTHORS autom4te.cache config.guess configure config.sub COPYING INSTALL install-sh missing NEWS README Makefile.in src/Makefile.in Makefile src/Makefile config.log config.status
