CLEANFILES =

INCLUDES =                                              \
	-I$(top_srcdir)					\
        -I$(srcdir) 					\
	$(DTK_CFLAGS)				\
	$(WARN_CFLAGS)

if PLATFORM_WIN32
no_undefined = -no-undefined
endif

if OS_WIN32
dtk_def = dtk.def
dtk_win32_symbols = -export-symbols $(srcdir)/dtk.def

dtk_win32_res = dtk-win32-res.o
dtk_win32_res_ldflag = -Wl,dtk-win32-res.o

dtk-win32-res.o : dtk-win32.rc
	$(WINDRES) dtk-win32.rc $@

install-def-file: dtk.def
	$(INSTALL) $(srcdir)/dtk.def $(DESTDIR)$(libdir)/dtk-win32-2.0.def

uninstall-def-file:
	-rm $(DESTDIR)$(libdir)/dtk-win32-2.0.def
else
install-def-file:
uninstall-def-file:
endif

if MS_LIB_AVAILABLE
noinst_DATA = dtk-2.0.lib

dtk-2.0.lib: libdtk-2.0.la dtk.def
	lib -machine:@LIB_EXE_MACHINE_FLAG@ -name:libdtk-2.0-$(LT_CURRENT_MINUS_AGE).dll -def:dtk.def -out:$@

install_ms_lib:
	$(INSTALL) dtk-2.0.lib $(DESTDIR)$(libdir)

uninstall_ms_lib:
	-rm $(DESTDIR)$(libdir)/dtk-2.0.lib
else
install-ms-lib:
uninstall-ms-lib:
endif

# This places the generated .def file in srcdir, since it is expected to be there.
# (The one from a tarball is)
dtk.def: dtk.symbols
	$(AM_V_GEN) (echo -e EXPORTS; $(CPP) -P -DINCLUDE_VARIABLES -DINCLUDE_INTERNAL_SYMBOLS -DG_OS_WIN32 -DALL_FILES - <$(srcdir)/dtk.symbols | sed -e '/^$$/d' -e 's/^/	/' -e 's/G_GNUC_[^ ]*//g') > $(srcdir)/dtk.def

deps =

libtool_opts =							\
  -version-info $(LT_VERSION_INFO)				\
  -export-dynamic $(no_undefined) $(LIBTOOL_EXPORT_OPTIONS)	\
  -rpath $(libdir) $(libdtk_target_ldflags)


source_h = dtk.h \
           dtkcalendar.h
source_c = dtkcalendar.c

lib_LTLIBRARIES = libdtk-2.0.la

libdtk_2_0_includedir = $(includedir)/dtk-2.0/dtk
libdtk_2_0_include_HEADERS =	$(source_h)
libdtk_2_0_la_SOURCES = $(source_c)
libdtk_2_0_la_LIBADD = $(DTK_LIBS)
libdtk_2_0_la_LDFLAGS = $(libtool_opts)
libdtk_2_0_la_DEPENDENCIES = $(deps)

if OS_WIN32
libdtk_target_ldflags = $(dtk_win32_res_ldflag) $(dtk_win32_symbols)
libdtk_2_0_la_DEPENDENCIES += $(dtk_def) $(dtk_win32_res)
endif

install-calendar-local: install-ms-lib install-def-file

EXTRA_DIST =  dtk-win32.rc.in dtk.symbols

-include $(top_srcdir)/git.mk
