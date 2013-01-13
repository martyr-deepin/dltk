AC_PREREQ(2.62)

m4_define([dltk_major_version], [2])
m4_define([dltk_minor_version], [0])
m4_define([dltk_micro_version], [1])
m4_define([dltk_interface_age], [0])
m4_define([dltk_binary_age],    [m4_eval(100 * dltk_minor_version + dltk_micro_version)])
m4_define([dltk_version],       [dltk_major_version.dltk_minor_version.dltk_micro_version])
m4_define([dltk_lt_current],    [m4_eval(100 * dltk_minor_version + dltk_micro_version - dltk_interface_age)])
m4_define([dltk_lt_revision],   [dltk_interface_age])
m4_define([dltk_lt_age],        [m4_eval(dltk_binary_age - dltk_interface_age)])

AC_INIT(dltk, dltk_version, zhaixiang@linuxdeepin.com)
AC_COPYRIGHT([Copyright (C) 2013 Zhai Xiang <zhaixiang@linuxdeepin.com>])

AM_INIT_AUTOMAKE([1.8 dist-bzip2 no-define -Wno-portability])

AC_CONFIG_SRCDIR(dltk/dltk.h)
AM_CONFIG_HEADER(config.h)
AC_CONFIG_MACRO_DIR([m4])

LT_VERSION_INFO="dltk_lt_current:dltk_lt_revision:dltk_lt_age"
LT_CURRENT_MINUS_AGE=m4_eval(dltk_lt_current - dltk_lt_age)
AC_SUBST(LT_VERSION_INFO)
AC_SUBST(LT_CURRENT_MINUS_AGE)

DLTK_VERSION=dltk_version
DLTK_BINARY_AGE=dltk_binary_age
AC_SUBST(DLTK_VERSION)
AC_SUBST(DLTK_BINARY_AGE)

AM_MAINTAINER_MODE
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

AC_PROG_CC
AC_ISC_POSIX
AC_HEADER_STDC

AC_PROG_INSTALL
AC_PROG_LIBTOOL

AM_PATH_PYTHON

IT_PROG_INTLTOOL([0.35.0])

GTK_DOC_CHECK([1.0],[--flavour=no-tmpl])

dnl make sure we keep ACLOCAL_FLAGS around for maintainer builds to work
AC_SUBST(ACLOCAL_AMFLAGS, "$ACLOCAL_FLAGS -I m4")

AC_PATH_PROG(GLIB_MKENUMS, glib-mkenums)

dnl ================================================================
dnl check for win32 build
dnl ================================================================
AC_MSG_CHECKING([for some Win32 platform])
case "$host" in
  *-*-mingw*|*-*-cygwin*)
    platform_win32=yes
    os_win32=yes
    ;;
  *)
    platform_win32=no
    os_win32=no
    ;;
esac
AC_MSG_RESULT([$platform_win32])
AM_CONDITIONAL(PLATFORM_WIN32, test "$platform_win32" = "yes")

AM_CONDITIONAL(OS_WIN32, test "$os_win32" = "yes")
AM_CONDITIONAL(OS_UNIX, test "$os_win32" != "yes")

#LIBTOOL_EXPORT_OPTIONS='-export-symbols-regex "^dltk.*"'
if test "$os_win32" != yes; then
    # libtool option to control which symbols are exported
    # right now, symbols starting with _ are not exported
    LIBTOOL_EXPORT_OPTIONS='-export-symbols-regex "^[[^_]].*"'
else
    # We currently use .def files on Windows (for dltk)
    LIBTOOL_EXPORT_OPTIONS=
fi
AC_SUBST(LIBTOOL_EXPORT_OPTIONS)

if test "$os_win32" = "yes"; then
  AC_CHECK_TOOL(WINDRES, windres, no)
  if test "$WINDRES" = no; then
    AC_MSG_ERROR([*** Could not find an implementation of windres in your PATH.])
  fi
  AC_CHECK_PROG(ms_librarian, lib.exe, yes, no)
fi
AM_CONDITIONAL(MS_LIB_AVAILABLE, test x$ms_librarian = xyes)

dnl ================================================================
dnl  Language Support 
dnl ================================================================
GETTEXT_PACKAGE=dltk-2.0
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "$GETTEXT_PACKAGE", [Define the gettext package to be used])
AC_SUBST(GETTEXT_PACKAGE)
AM_GLIB_GNU_GETTEXT

AM_GLIB_DEFINE_LOCALEDIR(DLTK_LOCALEDIR)


dnl ================================================================
dnl check glib, gobject
dnl ================================================================

GTK2_REQUIRED=2.24.10
GDK2_REQUIRED=2.24.10

PKG_CHECK_MODULES(DLTK, gtk+-2.0 >= $GTK2_REQUIRED  gdk-2.0 >= $GDK2_REQUIRED )

AC_SUBST(DLTK_CFLAGS)
AC_SUBST(DLTK_LIBS)

AC_CONFIG_FILES([
dltk+-2.0.pc
dltk/dltk-win32.rc
dltk/Makefile
po/Makefile.in
Makefile
])

AC_OUTPUT
AC_MSG_RESULT([
Build options:
  Version                   ${VERSION}
  Install prefix            ${prefix}
  Build shared libs         ${enable_shared}
  Build static libs         ${enable_static}
  CFLAGS                    ${CFLAGS}
])
