AUTOMAKE_OPTIONS = no-dependencies

BUILT_SOURCES = wconfig.h

bin_PROGRAMS = wmaker

#noinst_PROGRAMS = wsmap

EXTRA_DIST = 

#wsmap_SOURCES= wsmap.c

wmaker_SOURCES = 	\
	GNUstep.h \
	WindowMaker.h \
	actions.c \
	actions.h \
	appicon.c \
	appicon.h \
	application.c \
	application.h \
	appmenu.c \
	appmenu.h \
	balloon.c \
	balloon.h \
	client.c \
	client.h \
	colormap.c \
	cycling.c \
	def_pixmaps.h \
	defaults.c \
	defaults.h \
	dialog.c \
	dialog.h \
	dock.c \
	dockedapp.c \
	dock.h \
	event.c \
	extend_pixmaps.h \
	framewin.c \
	framewin.h \
	geomview.c \
	geomview.h \
	funcs.h \
	icon.c \
	icon.h \
	keybind.h \
	main.c \
	menu.c \
	menu.h \
	misc.c \
	monitor.c \
	motif.c \
	motif.h \
	moveres.c \
	pixmap.c \
	pixmap.h \
	placement.c \
	properties.c \
	properties.h \
	resources.c \
	resources.h \
	rootmenu.c \
	screen.c \
	screen.h \
	session.h \
	session.c \
	shutdown.c \
	switchpanel.c \
	switchpanel.h \
	stacking.c \
	stacking.h \
	startup.c \
	superfluous.c \
	superfluous.h \
	switchmenu.c \
	texture.c \
	texture.h \
	usermenu.c \
	usermenu.h \
	xdnd.h \
	xdnd.c \
	xinerama.h \
	xinerama.c \
	xmodifier.h \
	xmodifier.c \
	xutil.c \
	xutil.h \
	wconfig.h \
	wcore.c \
	wcore.h \
	wdefaults.c \
	wdefaults.h \
	window.c \
	window.h \
	winmenu.c \
	winspector.h \
	winspector.c \
	wmspec.h \
	wmspec.c \
	workspace.c \
	workspace.h \
	wsound.c \
	wsound.h \
	text.c \
	text.h 


AM_CPPFLAGS = $(DFLAGS) -DLOCALEDIR=\"$(NLSDIR)\"

AM_CFLAGS = @NOSTRICTALIASING@


INCLUDES = \
	-I$(top_srcdir)/wrlib \
	-I$(top_srcdir)/WINGs @HEADER_SEARCH_PATH@ 


wmaker_LDADD = \
	$(top_builddir)/WINGs/libWINGs.la\
	$(top_builddir)/WINGs/libWUtil.la\
	$(top_builddir)/wrlib/libwraster.la\
	@XLFLAGS@ \
	@XFTLIBS@ \
	@XLIBS@ \
	@INTLIBS@ \
	@DLLIBS@

#wsmap_LDADD = \
#	$(top_builddir)/WINGs/libWINGs.a\
#	$(top_builddir)/wrlib/libwraster.la\
#	@XLFLAGS@ \
#	@XFTLIBS@ \
#	@XLIBS@ \
#	@INTLIBS@ \
#	@DLLIBS@

