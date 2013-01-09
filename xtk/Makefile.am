CLEANFILES =

INCLUDES =                                              \
	-I$(top_srcdir)					\
        -I$(srcdir) 					\
	$(XTK_CFLAGS)				\
	$(WARN_CFLAGS)

if PLATFORM_WIN32
no_undefined = -no-undefined
endif

if OS_WIN32
xtk_def = xtk.def
xtk_win32_symbols = -export-symbols $(srcdir)/xtk.def

xtk_win32_res = xtk-win32-res.o
xtk_win32_res_ldflag = -Wl,xtk-win32-res.o

xtk-win32-res.o : xtk-win32.rc
	$(WINDRES) xtk-win32.rc $@

install-def-file: xtk.def
	$(INSTALL) $(srcdir)/xtk.def $(DESTDIR)$(libdir)/xtk-win32-2.0.def

uninstall-def-file:
	-rm $(DESTDIR)$(libdir)/xtk-win32-2.0.def
else
install-def-file:
uninstall-def-file:
endif

if MS_LIB_AVAILABLE
noinst_DATA = xtk-2.0.lib

xtk-2.0.lib: libxtk-2.0.la xtk.def
	lib -machine:@LIB_EXE_MACHINE_FLAG@ -name:libxtk-2.0-$(LT_CURRENT_MINUS_AGE).dll -def:xtk.def -out:$@

install_ms_lib:
	$(INSTALL) xtk-2.0.lib $(DESTDIR)$(libdir)

uninstall_ms_lib:
	-rm $(DESTDIR)$(libdir)/xtk-2.0.lib
else
install-ms-lib:
uninstall-ms-lib:
endif

# This places the generated .def file in srcdir, since it is expected to be there.
# (The one from a tarball is)
xtk.def: xtk.symbols
	$(AM_V_GEN) (echo -e EXPORTS; $(CPP) -P -DINCLUDE_VARIABLES -DINCLUDE_INTERNAL_SYMBOLS -DG_OS_WIN32 -DALL_FILES - <$(srcdir)/xtk.symbols | sed -e '/^$$/d' -e 's/^/	/' -e 's/G_GNUC_[^ ]*//g') > $(srcdir)/xtk.def

deps =

libtool_opts =							\
  -version-info $(LT_VERSION_INFO)				\
  -export-dynamic $(no_undefined) $(LIBTOOL_EXPORT_OPTIONS)	\
  -rpath $(libdir) $(libxtk_target_ldflags)


source_h = xtk.h \
           xtkcalendar.h
source_c = xtkcalendar.c

lib_LTLIBRARIES = libxtk-2.0.la

libxtk_2_0_includedir = $(includedir)/xtk-2.0/xtk
libxtk_2_0_include_HEADERS =	$(source_h)
libxtk_2_0_la_SOURCES = $(source_c)
libxtk_2_0_la_LIBADD = $(XTK_LIBS)
libxtk_2_0_la_LDFLAGS = $(libtool_opts)
libxtk_2_0_la_DEPENDENCIES = $(deps)

if OS_WIN32
libxtk_target_ldflags = $(xtk_win32_res_ldflag) $(xtk_win32_symbols)
libxtk_2_0_la_DEPENDENCIES += $(xtk_def) $(xtk_win32_res)
endif

install-calendar-local: install-ms-lib install-def-file

EXTRA_DIST =  xtk-win32.rc.in xtk.symbols

-include $(top_srcdir)/git.mk
