xpmdatadir = $(wprefs_datadir)/xpm


EXTRA_DIST = \
	advancetonewworkspace.xpm \
	animations.xpm \
	appearance.xpm \
	clip.xpm \
	configs.xpm \
	cycleworkspaces.xpm \
	dock.xpm \
	dontlinkworkspaces.xpm \
	ergonomic.xpm \
	expert.xpm \
	fonts.xpm \
	iconprefs.xpm \
	keyboard.xpm \
	keyboardprefs.xpm \
	keyshortcuts.xpm \
	menualign1.xpm \
	menualign2.xpm \
	menuprefs.xpm \
	menus.xpm \
	moreanim.xpm \
	mousesettings.xpm \
	mousespeed.xpm \
	msty1.xpm \
	msty2.xpm \
	msty3.xpm \
	newstyle.xpm \
	nonopaque.xpm \
	oldstyle.xpm \
	opaque.xpm \
	paths.xpm \
	smooth.xpm \
	sound.xpm \
	speed0.xpm \
	speed0s.xpm \
	speed1.xpm \
	speed1s.xpm \
	speed2.xpm \
	speed2s.xpm \
	speed3.xpm \
	speed3s.xpm \
	speed4.xpm \
	speed4s.xpm \
	tdel.xpm \
	tedit.xpm \
	textr.xpm \
	theme.xpm \
	timer0.xpm \
	timer0s.xpm \
	timer1.xpm \
	timer1s.xpm \
	timer2.xpm \
	timer2s.xpm \
	timer3.xpm \
	timer3s.xpm \
	timer4.xpm \
	timer4s.xpm \
	timer5.xpm \
	timer5s.xpm \
	tnew.xpm \
	whandling.xpm \
	windowfocus.xpm \
	workspace.xpm \
	workspacename.xpm \
	xis.xpm 


XPM_FILES=

xpmdata_DATA=$(XPM_FILES)

install-data-local:
	if [ @ICONEXT@ = "xpm" -a x"$(XPM_FILES)" = "x" ] ; then\
		$(MAKE) install-data XPM_FILES="$(EXTRA_DIST)";\
	fi

