AC_PREREQ(2.62)

m4_define([xtk_major_version], [2])
m4_define([xtk_minor_version], [0])
m4_define([xtk_micro_version], [1])
m4_define([xtk_interface_age], [0])
m4_define([xtk_binary_age],    [m4_eval(100 * xtk_minor_version + xtk_micro_version)])
m4_define([xtk_version],       [xtk_major_version.xtk_minor_version.xtk_micro_version])
m4_define([xtk_lt_current],    [m4_eval(100 * xtk_minor_version + xtk_micro_version - xtk_interface_age)])
m4_define([xtk_lt_revision],   [xtk_interface_age])
m4_define([xtk_lt_age],        [m4_eval(xtk_binary_age - xtk_interface_age)])

AC_INIT(xtk, xtk_version, zhaixiang@linuxdeepin.com)
AC_COPYRIGHT([Copyright (C) 2013 Zhai Xiang <zhaixiang@linuxdeepin.com>])

AM_INIT_AUTOMAKE([1.8 dist-bzip2 no-define -Wno-portability])

AC_CONFIG_SRCDIR(xtk/xtk.h)
AM_CONFIG_HEADER(config.h)
AC_CONFIG_MACRO_DIR([m4])

LT_VERSION_INFO="xtk_lt_current:xtk_lt_revision:xtk_lt_age"
LT_CURRENT_MINUS_AGE=m4_eval(xtk_lt_current - xtk_lt_age)
AC_SUBST(LT_VERSION_INFO)
AC_SUBST(LT_CURRENT_MINUS_AGE)

XTK_VERSION=xtk_version
XTK_BINARY_AGE=xtk_binary_age
AC_SUBST(XTK_VERSION)
AC_SUBST(XTK_BINARY_AGE)

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

GOBJECT_INTROSPECTION_CHECK([0.6.7])

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

#LIBTOOL_EXPORT_OPTIONS='-export-symbols-regex "^xtk.*"'
if test "$os_win32" != yes; then
    # libtool option to control which symbols are exported
    # right now, symbols starting with _ are not exported
    LIBTOOL_EXPORT_OPTIONS='-export-symbols-regex "^[[^_]].*"'
else
    # We currently use .def files on Windows (for xtk)
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
GETTEXT_PACKAGE=xtk-2.0
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE, "$GETTEXT_PACKAGE", [Define the gettext package to be used])
AC_SUBST(GETTEXT_PACKAGE)
AM_GLIB_GNU_GETTEXT

AM_GLIB_DEFINE_LOCALEDIR(XTK_LOCALEDIR)


dnl ================================================================
dnl check glib, gobject
dnl ================================================================

GTK2_REQUIRED=2.24.10
GDK2_REQUIRED=2.24.10

PKG_CHECK_MODULES(XTK, gtk+-2.0 >= $GTK2_REQUIRED  gdk-2.0 >= $GDK2_REQUIRED )

AC_SUBST(XTK_CFLAGS)
AC_SUBST(XTK_LIBS)

AC_CONFIG_FILES([
xtk+-2.0.pc
xtk/xtk-win32.rc
xtk/Makefile
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
