SUBDIRS = xpm tiff po

AUTOMAKE_OPTIONS = no-dependencies

wpexecbindir = @wprefs_bindir@

wpexecbin_PROGRAMS = WPrefs 

wpdatadir = @wprefs_datadir@

wpdata_DATA = WPrefs.tiff WPrefs.xpm

EXTRA_DIST = $(wpdata_DATA)

WPrefs_SOURCES = \
	main.c \
	WPrefs.c \
	WPrefs.h \
	Appearance.c \
	Configurations.c \
	Expert.c \
	Focus.c \
	FontSimple.c \
	Icons.c \
	KeyboardSettings.c \
	KeyboardShortcuts.c \
	Menu.c \
	MenuPreferences.c \
	MouseSettings.c \
	Paths.c \
	Preferences.c \
	TexturePanel.c \
	TexturePanel.h \
	Themes.c \
	WindowHandling.c \
	Workspace.c \
	double.c \
	double.h \
	editmenu.c \
	editmenu.h \
	imagebrowser.c \
	imagebrowser.h \
	xmodifier.c

AM_CPPFLAGS = -DLOCALEDIR=\"$(NLSDIR)\" -DRESOURCE_PATH=\"$(wpdatadir)\"

AM_CFLAGS = @NOSTRICTALIASING@

INCLUDES = -I$(top_srcdir)/wrlib -I$(top_srcdir)/WINGs @HEADER_SEARCH_PATH@ 

WPrefs_DEPENDENCIES = $(top_builddir)/WINGs/libWINGs.la

WPrefs_LDADD = \
	$(top_builddir)/WINGs/libWINGs.la\
	$(top_builddir)/WINGs/libWUtil.la\
	$(top_builddir)/wrlib/libwraster.la \
	@XFTLIBS@ \
	@INTLIBS@

