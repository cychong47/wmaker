nlsdir      = $(NLSDIR)

CATALOGS = @WINGSMOFILES@

CLEANFILES = $(CATALOGS) WINGs.pot

EXTRA_DIST = sk.po

POTFILES  = \
	$(top_builddir)/WINGs/configuration.c \
	$(top_builddir)/WINGs/connection.c \
	$(top_builddir)/WINGs/dragdestination.c \
	$(top_builddir)/WINGs/dragsource.c \
	$(top_builddir)/WINGs/error.c \
	$(top_builddir)/WINGs/findfile.c \
	$(top_builddir)/WINGs/hashtable.c \
	$(top_builddir)/WINGs/host.c \
	$(top_builddir)/WINGs/international.c \
	$(top_builddir)/WINGs/memory.c \
	$(top_builddir)/WINGs/wcolor.c \
	$(top_builddir)/WINGs/wcolorpanel.c \
	$(top_builddir)/WINGs/wfilepanel.c \
	$(top_builddir)/WINGs/wfont.c \
	$(top_builddir)/WINGs/wfontpanel.c \
	$(top_builddir)/WINGs/widgets.c \
	$(top_builddir)/WINGs/wruler.c \
	$(top_builddir)/WINGs/wtext.c \
	$(top_builddir)/WINGs/wview.c \
	$(top_builddir)/WINGs/wtextfield.c \
	$(top_builddir)/WINGs/wwindow.c


SUFFIXES = .po .mo

.po.mo: 
	msgfmt -o $@ $<


WINGs.pot: $(POTFILES)
	xgettext --default-domain=WINGs \
	--add-comments --keyword=_ $(POTFILES)
	if cmp -s WINGs.po WINGs.pot; then \
	    rm -f WINGs.po; \
	else \
	    mv -f WINGs.po WINGs.pot; \
	fi

install-data-local:  $(CATALOGS)
	$(mkinstalldirs) $(DESTDIR)$(nlsdir)
	chmod 755 $(DESTDIR)$(nlsdir) 
	for n in $(CATALOGS) __DuMmY ; do \
		if test "$$n" -a "$$n" != "__DuMmY" ; then \
			l=`basename $$n .mo`; \
			$(mkinstalldirs) $(DESTDIR)$(nlsdir)/$$l/LC_MESSAGES; \
			chmod 755 $(DESTDIR)$(nlsdir)/$$l; \
			chmod 755 $(DESTDIR)$(nlsdir)/$$l/LC_MESSAGES; \
			$(INSTALL_DATA) -m 644 $$n $(DESTDIR)$(nlsdir)/$$l/LC_MESSAGES/WINGs.mo; \
		fi; \
	done