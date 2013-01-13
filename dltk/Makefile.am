CLEANFILES =

INCLUDES =                                              \
	-I$(top_srcdir)					\
        -I$(srcdir) 					\
	$(DLTK_CFLAGS)				\
	$(WARN_CFLAGS)

if PLATFORM_WIN32
no_undefined = -no-undefined
endif

if OS_WIN32
dltk_def = dltk.def
dltk_win32_symbols = -export-symbols $(srcdir)/dltk.def

dltk_win32_res = dltk-win32-res.o
dltk_win32_res_ldflag = -Wl,dltk-win32-res.o

dltk-win32-res.o : dltk-win32.rc
	$(WINDRES) dltk-win32.rc $@

install-def-file: dltk.def
	$(INSTALL) $(srcdir)/dltk.def $(DESTDIR)$(libdir)/dltk-win32-2.0.def

uninstall-def-file:
	-rm $(DESTDIR)$(libdir)/dltk-win32-2.0.def
else
install-def-file:
uninstall-def-file:
endif

if MS_LIB_AVAILABLE
noinst_DATA = dltk-2.0.lib

dltk-2.0.lib: libdltk-2.0.la dltk.def
	lib -machine:@LIB_EXE_MACHINE_FLAG@ -name:libdltk-2.0-$(LT_CURRENT_MINUS_AGE).dll -def:dltk.def -out:$@

install_ms_lib:
	$(INSTALL) dltk-2.0.lib $(DESTDIR)$(libdir)

uninstall_ms_lib:
	-rm $(DESTDIR)$(libdir)/dltk-2.0.lib
else
install-ms-lib:
uninstall-ms-lib:
endif

# This places the generated .def file in srcdir, since it is expected to be there.
# (The one from a tarball is)
dltk.def: dltk.symbols
	$(AM_V_GEN) (echo -e EXPORTS; $(CPP) -P -DINCLUDE_VARIABLES -DINCLUDE_INTERNAL_SYMBOLS -DG_OS_WIN32 -DALL_FILES - <$(srcdir)/dltk.symbols | sed -e '/^$$/d' -e 's/^/	/' -e 's/G_GNUC_[^ ]*//g') > $(srcdir)/dltk.def

deps =

libtool_opts =							\
  -version-info $(LT_VERSION_INFO)				\
  -export-dynamic $(no_undefined) $(LIBTOOL_EXPORT_OPTIONS)	\
  -rpath $(libdir) $(libdltk_target_ldflags)


source_h = dltk.h \
           dltkdraw.h \
           dltkcalendar.h
source_c = dltkdraw.c \
           dltkcalendar.c

lib_LTLIBRARIES = libdltk-2.0.la

libdltk_2_0_includedir = $(includedir)/dltk-2.0/dltk
libdltk_2_0_include_HEADERS =	$(source_h)
libdltk_2_0_la_SOURCES = $(source_c)
libdltk_2_0_la_LIBADD = $(DLTK_LIBS)
libdltk_2_0_la_LDFLAGS = $(libtool_opts)
libdltk_2_0_la_DEPENDENCIES = $(deps)

if OS_WIN32
libdltk_target_ldflags = $(dltk_win32_res_ldflag) $(dltk_win32_symbols)
libdltk_2_0_la_DEPENDENCIES += $(dltk_def) $(dltk_win32_res)
endif

install-calendar-local: install-ms-lib install-def-file

EXTRA_DIST =  dltk-win32.rc.in dltk.symbols

-include $(top_srcdir)/git.mk
