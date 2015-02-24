#                                               -*- Autoconf -*-

# Process this file with autoconf to produce a configure script.

# Copyright © 2014-2015 Antonio Cao (@burzumishi) #

AC_PREREQ([2.69])

PACKAGE=xenesis

XENESIS_MAJOR_VERSION=15
XENESIS_MINOR_VERSION=2
XENESIS_UPDATE_VERSION=24

VERSION=$XENESIS_MAJOR_VERSION.$XENESIS_MINOR_VERSION.$XENESIS_UPDATE_VERSION

AC_INIT([xenesis], [15.2.24],
	[<antoniocao000@gmail.com>],
	[xenesis])

AC_COPYRIGHT(["2014-2015 (c) Antonio Cao (@burzumishi)"])

LT_INIT

AM_INIT_AUTOMAKE

AC_CONFIG_MACRO_DIR([m4])

AC_CANONICAL_HOST
AC_CANONICAL_BUILD

AC_DEFINE_UNQUOTED([PREFIX], ["/usr/"], [Define to the root directory.])
AC_DEFINE_UNQUOTED([SBINDIR], ["${prefix}/sbin/"], [Define Executable Directory.])

AC_SUBST([DESCRIPTION], ["Remote Task Manager"])

AC_PROG_LEX
AC_PROG_AWK
AC_PROG_GREP
AC_PROG_SED
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_MKDIR_P

AC_PATH_PROG([GNUMAKE], [make])
AM_CONDITIONAL([HAVE_GNUMAKE], [test -n "${GNUMAKE}"])

AC_PATH_PROG([FILE], [file])
AM_CONDITIONAL([FILE], [test -n "${FILE}"])

AC_PATH_PROG([BASH], [bash])
AM_CONDITIONAL([HAVE_BASH], [test -n "${BASH}"])

AC_PATH_PROG([ENV], [env])
AM_CONDITIONAL([HAVE_ENV], [test -n "${ENV}"])

AC_PATH_PROG([TAIL], [tail])
AM_CONDITIONAL([HAVE_TAIL], [test -n "${TAIL}"])

AC_PATH_PROG([HEAD], [head])
AM_CONDITIONAL([HAVE_HEAD], [test -n "${HEAD}"])

AC_PATH_PROG([LESS], [less])
AM_CONDITIONAL([HAVE_LESS], [test -n "${LESS}"])

AC_PATH_PROG([MORE], [more])
AM_CONDITIONAL([HAVE_MORE], [test -n "${MORE}"])

AC_PATH_PROG([FIND], [find])
AM_CONDITIONAL([HAVE_FIND], [test -n "${FIND}"])

AC_PATH_PROG([SED], [sed])
AM_CONDITIONAL([HAVE_SED], [test -n "${SED}"])

AC_PATH_PROG([TAR], [tar])
AM_CONDITIONAL([HAVE_TAR], [test -n "${TAR}"])

AC_PATH_PROG([GZIP], [gzip])
AM_CONDITIONAL([HAVE_GZIP], [test -n "${GZIP}"])

AC_PATH_PROG([BZIP2], [bzip2])
AM_CONDITIONAL([HAVE_BZIP2], [test -n "${BZIP2}"])

AC_PATH_PROG([XZ], [xz])
AM_CONDITIONAL([HAVE_XZ], [test -n "${XZ}"])

AC_PATH_PROG([PERL], [perl])
AM_CONDITIONAL([HAVE_PERL], [test -n "${PERL}"])

AC_PATH_PROG([PATCH], [patch])
AM_CONDITIONAL([HAVE_PATCH], [test -n "${PATCH}"])

AC_CONFIG_FILES([Makefile
		 src/Makefile
		 etc/Makefile
		 etc/os/Makefile
		 etc/os/commands/Makefile
		 etc/conf.d/Makefile])

AC_OUTPUT

