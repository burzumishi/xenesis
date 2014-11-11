#                                               -*- Autoconf -*-

# Process this file with autoconf to produce a configure script.

# Copyright © 2014 Antonio Cao (@burzumishi) #

AC_PREREQ([2.69])

PACKAGE=xenesis

XENESIS_MAJOR_VERSION=0
XENESIS_MINOR_VERSION=1

VERSION=$XENESIS_MAJOR_VERSION.$XENESIS_MINOR_VERSION

AC_INIT([xenesis], [0.1],
	[<antoniocao000@gmail.com>],
	[xenesis])

AC_COPYRIGHT(["2014 © Antonio Cao (@burzumishi)"])

AM_INIT_AUTOMAKE

AC_CONFIG_MACRO_DIR([m4])

AC_CANONICAL_HOST
AC_CANONICAL_BUILD

AC_DEFINE_UNQUOTED([PREFIX], ["/opt/xenesis/"], [Define to the root directory.])
AC_DEFINE_UNQUOTED([BINDIR], ["${prefix}/bin/"], [Define Executable Directory.])

AC_SUBST([DESCRIPTION], ["Remote Task Manager"])

AC_PROG_LEX
AC_PROG_AWK
AC_PROG_GREP
AC_PROG_SED
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

AC_CHECK_PROGS([GNUMAKE], [make])
AM_CONDITIONAL([HAVE_GNUMAKE], [test -n "${GNUMAKE}"])

AC_CHECK_PROGS([BASH], [bash])
AM_CONDITIONAL([HAVE_BASH], [test -n "${BASH}"])

AC_CHECK_PROGS([PING], [ping])
AM_CONDITIONAL([HAVE_PING], [test -n "${PING}"])

AC_CHECK_PROGS([NSLOOKUP], [nslookup])
AM_CONDITIONAL([HAVE_NSLOOKUP], [test -n "${NSLOOKUP}"])

AC_CHECK_PROGS([SSH], [ssh])
AM_CONDITIONAL([HAVE_SSH], [test -n "${SSH}"])

AC_CHECK_PROGS([SCP], [scp])
AM_CONDITIONAL([HAVE_SCP], [test -n "${SCP}"])

AC_CHECK_PROGS([TAIL], [tail])
AM_CONDITIONAL([HAVE_TAIL], [test -n "${TAIL}"])

AC_CHECK_PROGS([HEAD], [head])
AM_CONDITIONAL([HAVE_HEAD], [test -n "${HEAD}"])

AC_CHECK_PROGS([LESS], [less])
AM_CONDITIONAL([HAVE_LESS], [test -n "${LESS}"])

AC_CHECK_PROGS([MORE], [more])
AM_CONDITIONAL([HAVE_MORE], [test -n "${MORE}"])

AC_CHECK_PROGS([FIND], [find])
AM_CONDITIONAL([HAVE_FIND], [test -n "${FIND}"])

AC_CHECK_PROGS([SED], [sed])
AM_CONDITIONAL([HAVE_SED], [test -n "${SED}"])

AC_CONFIG_FILES([Makefile
		 src/Makefile
		 conf.d/Makefile])

AC_OUTPUT

