/* 
 *  Window Maker window manager
 * 
 *  Copyright (c) 1997, 1998 Alfredo K. Kojima
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, 
 *  USA.
 */
#include "wconfig.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <pwd.h>
#include <math.h>
#include <time.h>

#include <WUtil.h>
#include <wraster.h>


#include "WindowMaker.h"
#include "GNUstep.h"
#include "screen.h"
#include "wcore.h"
#include "window.h"
#include "framewin.h"
#include "funcs.h"
#include "defaults.h"
#include "dialog.h"
#include "xutil.h"
#include "xmodifier.h"


/**** global variables *****/

extern char *DisplayName;

extern WPreferences wPreferences;

extern Time LastTimestamp;

#ifdef OFFIX_DND
extern Atom _XA_DND_SELECTION;
#endif


#ifdef USECPP
static void
putdef(char *line, char *name, char *value)
{
    if (!value) {
	wwarning(_("could not define value for %s for cpp"), name);
	return;
    }
    strcat(line, name);
    strcat(line, value);
}



static void
putidef(char *line, char *name, int value)
{
    char tmp[64];
    sprintf(tmp, "%i", value);
    strcat(line, name);
    strcat(line, tmp);
}


static char*
username()
{
    char *tmp;
    
    tmp = getlogin();
    if (!tmp) {
	struct passwd *user;

	user = getpwuid(getuid());
	if (!user) {
	    wsyserror(_("could not get password entry for UID %i"), getuid());
	    return NULL;
	}
	if (!user->pw_name) {
	    return NULL;
	} else {
	    return user->pw_name;
	}
    }
    return tmp;
}
       
char *
MakeCPPArgs(char *path)
{
    int i;
    char buffer[MAXLINE], *buf, *line;
    Visual *visual;
    char *tmp;
    
    line = wmalloc(MAXLINE);
    *line = 0;
    i=1;
    if ((buf=getenv("HOSTNAME"))!=NULL) {
	if (buf[0]=='(') {
	    wwarning(_("your machine is misconfigured. HOSTNAME is set to %s"),
		     buf);
	} else 
	  putdef(line, " -DHOST=", buf);
    } else if ((buf=getenv("HOST"))!=NULL) {
	if (buf[0]=='(') {
	    wwarning(_("your machine is misconfigured. HOST is set to %s"),
		     buf);
	} else 
	  putdef(line, " -DHOST=", buf);
    }
    buf = username();
    if (buf)
      putdef(line, " -DUSER=", buf);
    putidef(line, " -DUID=", getuid());
    buf = XDisplayName(DisplayString(dpy));
    putdef(line, " -DDISPLAY=", buf);
    putdef(line, " -DWM_VERSION=", VERSION);
    
    visual = DefaultVisual(dpy, DefaultScreen(dpy));
    putidef(line, " -DVISUAL=", visual->class);
    
    putidef(line, " -DDEPTH=", DefaultDepth(dpy, DefaultScreen(dpy)));

    putidef(line, " -DSCR_WIDTH=", WidthOfScreen(DefaultScreenOfDisplay(dpy)));
    putidef(line, " -DSCR_HEIGHT=", 
	    HeightOfScreen(DefaultScreenOfDisplay(dpy)));

    /* put the dir where the menu is being read from to the
     * search path */
    if (path) {
	tmp = wstrdup(path);
	buf = strchr(tmp+1, ' ');
	if (buf) {
        *buf = 0;
    }
	buf = strrchr(tmp, '/');
	if (buf) {
        *buf = 0; /* trunc filename */
        putdef(line, " -I", tmp);
    }
	free(tmp);
    }


    /* this should be done just once, but it works this way */
    strcpy(buffer, DEF_CONFIG_PATHS);
    buf = strtok(buffer, ":");

    do {
      char fullpath[MAXLINE];

      if (buf[0]!='~') {
	strcpy(fullpath, buf);
      } else {
	char * wgethomedir();
	/* home is statically allocated. Don't free it! */
	char *home = wgethomedir();
	
	strcpy(fullpath, home);
	strcat(fullpath, &(buf[1]));
      }

      putdef(line, " -I", fullpath);

    } while ((buf = strtok(NULL, ":"))!=NULL);
    
#undef arg
#ifdef DEBUG
    puts("CPP ARGS");
    puts(line);
#endif
    return line;
}
#endif /* USECPP */


WWindow*
NextFocusWindow(WScreen *scr)
{
    WWindow *tmp, *wwin, *closest, *min;
    Window d;

    if (!(wwin = scr->focused_window))
        return NULL;
    tmp = wwin->prev;
    closest = NULL;
    min = wwin;
    d = 0xffffffff;
    while (tmp) {
        if (wWindowCanReceiveFocus(tmp) 
	    && (!WFLAGP(tmp, skip_window_list)|| tmp->flags.internal_window)) {
	    if (min->client_win > tmp->client_win)
	      min = tmp;
	    if (tmp->client_win > wwin->client_win
		&& (!closest
		    || (tmp->client_win - wwin->client_win) < d)) {
		closest = tmp;
		d = tmp->client_win - wwin->client_win;
	    }
	}
	tmp = tmp->prev;
    }
    if (!closest||closest==wwin)
      return min;
    return closest;
}


WWindow*
PrevFocusWindow(WScreen *scr)
{
    WWindow *tmp, *wwin, *closest, *max;
    Window d;
    
    if (!(wwin = scr->focused_window))
        return NULL;
    tmp = wwin->prev;
    closest = NULL;
    max = wwin;
    d = 0xffffffff;
    while (tmp) {
	if (wWindowCanReceiveFocus(tmp) &&
            (!WFLAGP(tmp, skip_window_list) || tmp->flags.internal_window)) {
	    if (max->client_win < tmp->client_win)
	      max = tmp;
	    if (tmp->client_win < wwin->client_win
		&& (!closest
		    || (wwin->client_win - tmp->client_win) < d)) {
		closest = tmp;
		d = wwin->client_win - tmp->client_win;
	    }
	}
	tmp = tmp->prev;
    }
    if (!closest||closest==wwin)
      return max;
    return closest;
}



#if 0
/*
 * Is win2 below win1?
 */
static Bool
isBelow(WWindow *win1, WWindow *win2)
{
    int i;
    WCoreWindow *tmp;
    
    tmp = win1->frame->core->stacking->under;
    while (tmp) {
	if (tmp == win2->frame->core)
	    return True;
	tmp = tmp->stacking->under;
    }
    
    for (i=win1->frame->core->stacking->window_level-1; i>=0; i--) {
	tmp = win1->screen_ptr->stacking_list[i];
	while (tmp) {
	    if (tmp == win2->frame->core)
		return True;
	    tmp = tmp->stacking->under;
	}
    }
    return True;
}
#endif



/*
 *  XFetchName Wrapper
 *
 */
Bool wFetchName(dpy, win, winname)
Display *dpy;
Window win;
char **winname;
{
    XTextProperty text_prop;
    char **list;
    int num;

    if (XGetWMName(dpy, win, &text_prop)) {
	if (text_prop.value && text_prop.nitems > 0) {
	    if (text_prop.encoding == XA_STRING) {
		*winname = wstrdup((char *)text_prop.value);
		XFree(text_prop.value);
	    } else {
		text_prop.nitems = strlen((char *)text_prop.value);
		if (XmbTextPropertyToTextList(dpy, &text_prop, &list, &num) >=
		    Success && num > 0 && *list) {
		    XFree(text_prop.value);
		    *winname = wstrdup(*list);
		    XFreeStringList(list);
		} else {
		    *winname = wstrdup((char *)text_prop.value);
		    XFree(text_prop.value);
		}
	    }
	} else {
	    /* the title is set, but it was set to none */
	    *winname = wstrdup("");
	}
	return True;
    } else {
	/* the hint is probably not set */
	*winname = NULL;
	
	return False;
    }
}

/*
 *  XGetIconName Wrapper
 *
 */

Bool wGetIconName(dpy, win, iconname)
Display *dpy;
Window win;
char **iconname;
{
    XTextProperty text_prop;
    char **list;
    int num;
    
    if (XGetWMIconName(dpy, win, &text_prop) != 0 && text_prop.value
	&& text_prop.nitems > 0) {
	if (text_prop.encoding == XA_STRING)
	    *iconname = (char *)text_prop.value;
	else {
	    text_prop.nitems = strlen((char *)text_prop.value);
	    if (XmbTextPropertyToTextList(dpy, &text_prop, &list, &num) >=
		Success && num > 0 && *list) {
		XFree(text_prop.value);
		*iconname = wstrdup(*list);
		XFreeStringList(list);
	    } else
		*iconname = (char *)text_prop.value;
	}
	return True;
    }
    *iconname = NULL;
    return False;
}


static void 
eatExpose()
{
    XEvent event, foo;
    
    /* compress all expose events into a single one */
    
    if (XCheckMaskEvent(dpy, ExposureMask, &event)) {
	/* ignore other exposure events for this window */
	while (XCheckWindowEvent(dpy, event.xexpose.window, ExposureMask,
			       &foo));
	/* eat exposes for other windows */
	eatExpose();
	
	event.xexpose.count = 0;
	XPutBackEvent(dpy, &event);
    }
}


void
SlideWindow(Window win, int from_x, int from_y, int to_x, int to_y)
{
    time_t time0 = time(NULL);
    float dx, dy, x=from_x, y=from_y, sx, sy, px, py;
    int dx_is_bigger=0;

    /* animation parameters */
    static struct {
	int delay;
	int steps;
	int slowdown;
    } apars[5] = {
	{ICON_SLIDE_DELAY_UF, ICON_SLIDE_STEPS_UF, ICON_SLIDE_SLOWDOWN_UF},
	{ICON_SLIDE_DELAY_F, ICON_SLIDE_STEPS_F, ICON_SLIDE_SLOWDOWN_F},
	{ICON_SLIDE_DELAY_M, ICON_SLIDE_STEPS_M, ICON_SLIDE_SLOWDOWN_M},
	{ICON_SLIDE_DELAY_S, ICON_SLIDE_STEPS_S, ICON_SLIDE_SLOWDOWN_S},
	{ICON_SLIDE_DELAY_U, ICON_SLIDE_STEPS_U, ICON_SLIDE_SLOWDOWN_U}};
    
    

    dx = (float)(to_x-from_x);
    dy = (float)(to_y-from_y);
    sx = (dx == 0 ? 0 : fabs(dx)/dx);
    sy = (dy == 0 ? 0 : fabs(dy)/dy);

    if (fabs(dx) > fabs(dy)) {
        dx_is_bigger = 1;
    }

    if (dx_is_bigger) {
        px = dx / apars[(int)wPreferences.icon_slide_speed].slowdown;
        if (px < apars[(int)wPreferences.icon_slide_speed].steps && px > 0)
            px = apars[(int)wPreferences.icon_slide_speed].steps;
        else if (px > -apars[(int)wPreferences.icon_slide_speed].steps && px < 0)
            px = -apars[(int)wPreferences.icon_slide_speed].steps;
        py = (sx == 0 ? 0 : px*dy/dx);
    } else {
        py = dy / apars[(int)wPreferences.icon_slide_speed].slowdown;
        if (py < apars[(int)wPreferences.icon_slide_speed].steps && py > 0)
            py = apars[(int)wPreferences.icon_slide_speed].steps;
        else if (py > -apars[(int)wPreferences.icon_slide_speed].steps && py < 0)
            py = -apars[(int)wPreferences.icon_slide_speed].steps;
        px = (sy == 0 ? 0 : py*dx/dy);
    }

    while (x != to_x || y != to_y) {
	x += px;
        y += py;
        if ((px<0 && (int)x < to_x) || (px>0 && (int)x > to_x))
            x = (float)to_x;
        if ((py<0 && (int)y < to_y) || (py>0 && (int)y > to_y))
            y = (float)to_y;

        if (dx_is_bigger) {
            px = px * (1.0 - 1/(float)apars[(int)wPreferences.icon_slide_speed].slowdown);
            if (px < apars[(int)wPreferences.icon_slide_speed].steps && px > 0)
                px = apars[(int)wPreferences.icon_slide_speed].steps;
            else if (px > -apars[(int)wPreferences.icon_slide_speed].steps && px < 0)
                px = -apars[(int)wPreferences.icon_slide_speed].steps;
            py = (sx == 0 ? 0 : px*dy/dx);
        } else {
            py = py * (1.0 - 1/(float)apars[(int)wPreferences.icon_slide_speed].slowdown);
            if (py < apars[(int)wPreferences.icon_slide_speed].steps && py > 0)
                py = apars[(int)wPreferences.icon_slide_speed].steps;
            else if (py > -apars[(int)wPreferences.icon_slide_speed].steps && py < 0)
                py = -apars[(int)wPreferences.icon_slide_speed].steps;
            px = (sy == 0 ? 0 : py*dx/dy);
        }

        XMoveWindow(dpy, win, (int)x, (int)y);
        XFlush(dpy);
        if (apars[(int)wPreferences.icon_slide_speed].delay > 0) {
            wusleep(apars[(int)wPreferences.icon_slide_speed].delay*1000L);
        }
	if (time(NULL) - time0 > MAX_ANIMATION_TIME)
	    break;
    }
    XMoveWindow(dpy, win, to_x, to_y);

    XSync(dpy, 0);
    /* compress expose events */
    eatExpose();
}


char*
ShrinkString(WMFont *font, char *string, int width)
{
    int w, w1=0;
    int p;
    char *pos;
    char *text;
    int p1, p2, t;

    if (wPreferences.multi_byte_text)
	return wstrdup(string);

    p = strlen(string);
    w = WMWidthOfString(font, string, p);
    text = wmalloc(strlen(string)+8);
    strcpy(text, string);
    if (w<=width)
      return text;

    pos = strchr(text, ' ');
    if (!pos)
      pos = strchr(text, ':');

    if (pos) {
	*pos = 0;
	p = strlen(text);
	w1 = WMWidthOfString(font, text, p);
	if (w1 > width) {
	    w1 = 0;
	    p = 0;
	    *pos = ' ';
	    *text = 0;
	} else {
	    *pos = 0;
	    width -= w1;
	    p++;
	}
	string += p;
	p=strlen(string);
    } else {
	*text=0;
    }
    strcat(text, "...");
    width -= WMWidthOfString(font, "...", 3);
    
    pos = string;
    p1=0;
    p2=p;
    t = (p2-p1)/2;
    while (p2>p1 && p1!=t) {
	w = WMWidthOfString(font, &string[p-t], t);
	if (w>width) {
	    p2 = t;
	    t = p1+(p2-p1)/2;
	} else if (w<width) {
	    p1 = t;
	    t = p1+(p2-p1)/2;
	} else 
	  p2=p1=t;
    }
    strcat(text, &string[p-p1]);

    return text;
}


char*
FindImage(char *paths, char *file)
{
    char *tmp, *path;

    tmp = strrchr(file, ':');
    if (tmp) {
	*tmp = 0;
	path = wfindfile(paths, file);
	*tmp = ':';
    }
    if (!tmp || !path) {
	path = wfindfile(paths, file);
    }

    return path;
}


char*
FlattenStringList(char **list, int count)
{
    int i, j;
    char *flat_string, *wspace;

    j = 0;
    for (i=0; i<count; i++) {
        if (list[i]!=NULL && list[i][0]!=0) {
            j += strlen(list[i]);
            if (strpbrk(list[i], " \t"))
                j += 2;
        }
    }
    
    flat_string = malloc(j+count+1);
    if (!flat_string) {
	return NULL;
    }

    *flat_string = 0;
    for (i=0; i<count; i++) {
	if (list[i]!=NULL && list[i][0]!=0) {
	    if (i>0)
		strcat(flat_string, " ");
            wspace = strpbrk(list[i], " \t");
            if (wspace)
                strcat(flat_string, "\"");
	    strcat(flat_string, list[i]);
            if (wspace)
                strcat(flat_string, "\"");
	}
    }

    return flat_string;
}



/*
 *----------------------------------------------------------------------
 * ParseCommand --
 * 	Divides a command line into a argv/argc pair.
 *---------------------------------------------------------------------- 
 */
#define PRC_ALPHA	0
#define PRC_BLANK	1
#define PRC_ESCAPE	2
#define PRC_DQUOTE	3
#define PRC_EOS		4
#define PRC_SQUOTE	5

typedef struct {
    short nstate;
    short output;
} DFA;


static DFA mtable[9][6] = {
    {{3,1},{0,0},{4,0},{1,0},{8,0},{6,0}},
    {{1,1},{1,1},{2,0},{3,0},{5,0},{1,1}},
    {{1,1},{1,1},{1,1},{1,1},{5,0},{1,1}},
    {{3,1},{5,0},{4,0},{1,0},{5,0},{6,0}},
    {{3,1},{3,1},{3,1},{3,1},{5,0},{3,1}},
    {{-1,-1},{0,0},{0,0},{0,0},{0,0},{0,0}}, /* final state */
    {{6,1},{6,1},{7,0},{6,1},{5,0},{3,0}},
    {{6,1},{6,1},{6,1},{6,1},{5,0},{6,1}},
    {{-1,-1},{0,0},{0,0},{0,0},{0,0},{0,0}}, /* final state */
};

char*
next_token(char *word, char **next)
{
    char *ptr;
    char *ret, *t;
    int state, ctype;

    t = ret = wmalloc(strlen(word)+1);
    ptr = word;
    
    state = 0;
    *t = 0;
    while (1) {
	if (*ptr==0) 
	    ctype = PRC_EOS;
	else if (*ptr=='\\')
	    ctype = PRC_ESCAPE;
	else if (*ptr=='"')
	    ctype = PRC_DQUOTE;
	else if (*ptr=='\'')
	    ctype = PRC_SQUOTE;
	else if (*ptr==' ' || *ptr=='\t')
	    ctype = PRC_BLANK;
	else
	    ctype = PRC_ALPHA;

	if (mtable[state][ctype].output) {
	    *t = *ptr; t++;
	    *t = 0;
	}
	state = mtable[state][ctype].nstate;
	ptr++;
	if (mtable[state][0].output<0) {
	    break;
	}
    }

    if (*ret==0)
	t = NULL;
    else
	t = wstrdup(ret);

    free(ret);
    
    if (ctype==PRC_EOS)
	*next = NULL;
    else
	*next = ptr;
    
    return t;
}


void
ParseCommand(char *command, char ***argv, int *argc)
{
    WMBag *bag = WMCreateBag(4);
    char *token, *line;
    int count, j;

    line = command;
    do {
	token = next_token(line, &line);
	if (token) {
	    WMPutInBag(bag, token);
	}
    } while (token!=NULL && line!=NULL);

    count = WMGetBagItemCount(bag);
    *argv = wmalloc(sizeof(char*)*count);
    for (j = 0; j < count; j++) {
	(*argv)[j] = WMGetFromBag(bag, j);
    }
    *argc = count;

    WMFreeBag(bag);
}

#if 0
static void
timeup(void *foo)
{
    *(int*)foo=1;
}
#endif
static char*
getselection(WScreen *scr)
{
    char *tmp;
    extern char *W_GetTextSelection(); /* in WINGs */
    
    tmp = W_GetTextSelection(scr->wmscreen, XA_PRIMARY);
    if (!tmp)
	tmp = W_GetTextSelection(scr->wmscreen, XA_CUT_BUFFER0);
    return tmp;

#if 0
    XEvent event;
    int timeover=0;
    WMHandlerID *id;
    
#ifdef DEBUG
    puts("getting selection");
#endif
    RequestSelection(dpy, scr->no_focus_win, LastTimestamp);
    /* timeout on 1 sec. */
    id = WMAddTimerHandler(1000, timeup, &timeover);
    while (!timeover) {
	WMNextEvent(dpy, &event);
	if (event.type == SelectionNotify 
	    && event.xany.window==scr->no_focus_win) {
	    WMDeleteTimerHandler(id);
#ifdef DEBUG
	    puts("selection ok");
#endif
	    return GetSelection(dpy, scr->no_focus_win);
	} else {
	    WMHandleEvent(&event);
	}
    }
    wwarning(_("selection timed-out"));
    return NULL;
#endif
}


static char*
getuserinput(WScreen *scr, char *line, int *ptr)
{
    char *ret;
    char *title;
    char *prompt;
    int j, state;
    int begin = 0;
    char tbuffer[256], pbuffer[256];

    title = _("Program Arguments");
    prompt = _("Enter command arguments:");
    ret = NULL;

#define _STARTING 0
#define _TITLE 1
#define _PROMPT 2
#define _DONE 3

    state = _STARTING;
    j = 0;
    for (; line[*ptr]!=0 && state!=_DONE; (*ptr)++) {
	switch (state) {
	 case _STARTING:
	    if (line[*ptr]=='(') {
		state = _TITLE;
		begin = *ptr+1;
	    } else {
		state = _DONE;
	    }
	    break;

	 case _TITLE:
	    if (j <= 0 && line[*ptr]==',') {

		j = 0;
		if (*ptr > begin) {
		    strncpy(tbuffer, &line[begin], WMIN(*ptr-begin, 255));
		    tbuffer[WMIN(*ptr-begin, 255)] = 0;
		    title = (char*)tbuffer;
		}
		begin = *ptr+1;
		state = _PROMPT;

	    } else if (j <= 0 && line[*ptr]==')') {

		if (*ptr > begin) {
		    strncpy(tbuffer, &line[begin], WMIN(*ptr-begin, 255));
		    tbuffer[WMIN(*ptr-begin, 255)] = 0;
		    title = (char*)tbuffer;
		}
		state = _DONE;

	    } else if (line[*ptr]=='(') {
		j++;
	    } else if (line[*ptr]==')') {
		j--;
	    }

	    break;

	 case _PROMPT:
	    if (line[*ptr]==')' && j==0) {

		if (*ptr-begin > 1) {
		    strncpy(pbuffer, &line[begin], WMIN(*ptr-begin, 255));
		    pbuffer[WMIN(*ptr-begin, 255)] = 0;
		    prompt = (char*)pbuffer;
		}
		state = _DONE;
	    } else if (line[*ptr]=='(')
		    j++;
	    else if (line[*ptr]==')')
		j--;
	    break;
	}
    }
    (*ptr)--;
#undef _STARTING
#undef _TITLE
#undef _PROMPT
#undef _DONE

    if (!wInputDialog(scr, title, prompt, &ret))
	return NULL;
    else
	return ret;
}


#ifdef OFFIX_DND
static char*
get_dnd_selection(WScreen *scr)
{
    XTextProperty text_ret;
    int result;
    char **list;
    char *flat_string;
    int count;
    
    result=XGetTextProperty(dpy, scr->root_win, &text_ret, _XA_DND_SELECTION);
    
    if (result==0 || text_ret.value==NULL || text_ret.encoding==None
	|| text_ret.format==0 || text_ret.nitems == 0) {
	wwarning(_("unable to get dropped data from DND drop"));
	return NULL;
    }
    
    XTextPropertyToStringList(&text_ret, &list, &count);
    
    if (!list || count<1) {
	XFree(text_ret.value);
	wwarning(_("error getting dropped data from DND drop"));
	return NULL;
    }

    flat_string = FlattenStringList(list, count);
    if (!flat_string) {
	wwarning(_("out of memory while getting data from DND drop"));
    }
    
    XFreeStringList(list);
    XFree(text_ret.value);
    return flat_string;
}
#endif /* OFFIX_DND */


#define S_NORMAL 0
#define S_ESCAPE 1
#define S_OPTION 2

/* 
 * state    	input   new-state	output
 * NORMAL	%	OPTION		<nil>
 * NORMAL	\	ESCAPE		<nil>
 * NORMAL	etc.	NORMAL		<input>
 * ESCAPE	any	NORMAL		<input>
 * OPTION	s	NORMAL		<selection buffer>
 * OPTION	w	NORMAL		<selected window id>
 * OPTION	a	NORMAL		<input text>
 * OPTION	d	NORMAL		<OffiX DND selection object>
 * OPTION	W	NORMAL		<current workspace>
 * OPTION	etc.	NORMAL		%<input>
 */
#define TMPBUFSIZE 64
char*
ExpandOptions(WScreen *scr, char *cmdline)
{
    int ptr, optr, state, len, olen;
    char *out, *nout;
    char *selection=NULL;
    char *user_input=NULL;
#if defined(OFFIX_DND) || defined(XDND)
    char *dropped_thing=NULL;
#endif
    char tmpbuf[TMPBUFSIZE];
    int slen;

    len = strlen(cmdline);
    olen = len+1;
    out = malloc(olen);
    if (!out) {
	wwarning(_("out of memory during expansion of \"%s\""));
	return NULL;
    }
    *out = 0;
    ptr = 0; 			       /* input line pointer */
    optr = 0;			       /* output line pointer */
    state = S_NORMAL;
    while (ptr < len) {
	switch (state) {
	 case S_NORMAL:
	    switch (cmdline[ptr]) {
	     case '\\':
		state = S_ESCAPE;
		break;
	     case '%':
		state = S_OPTION;
		break;
	     default:
		state = S_NORMAL;
		out[optr++]=cmdline[ptr];
		break;
	    }
	    break;
	 case S_ESCAPE:
	    switch (cmdline[ptr]) {
	     case 'n':
		out[optr++]=10;
		break;
		
	     case 'r':
		out[optr++]=13;
		break;
		
	     case 't':
		out[optr++]=9;
		break;
		
	     default:
		out[optr++]=cmdline[ptr];
	    }
	    state = S_NORMAL;
	    break;
	 case S_OPTION:
	    state = S_NORMAL;
	    switch (cmdline[ptr]) {
	     case 'w':
		if (scr->focused_window
		    && scr->focused_window->flags.focused) {
		    sprintf(tmpbuf, "0x%x", 
			    (unsigned int)scr->focused_window->client_win);
		    slen = strlen(tmpbuf);
		    olen += slen;
		    nout = realloc(out,olen);
		    if (!nout) {
			wwarning(_("out of memory during expansion of \"%w\""));
			goto error;
		    }
		    out = nout;
		    strcat(out,tmpbuf);
		    optr+=slen;
		} else {
		    out[optr++]=' ';
		}
		break;
		
	     case 'W':
		sprintf(tmpbuf, "0x%x", 
			(unsigned int)scr->current_workspace + 1);
		slen = strlen(tmpbuf);
		olen += slen;
		nout = realloc(out,olen);
		if (!nout) {
		    wwarning(_("out of memory during expansion of \"%W\""));
		    goto error;
		}
		out = nout;
		strcat(out,tmpbuf);
		optr+=slen;
		break;
		
	     case 'a':
		ptr++;
		user_input = getuserinput(scr, cmdline, &ptr); 
		if (user_input) {
		    slen = strlen(user_input);
		    olen += slen;
		    nout = realloc(out,olen);
		    if (!nout) {
			wwarning(_("out of memory during expansion of \"%a\""));
			goto error;
		    }
		    out = nout;
		    strcat(out,user_input);
		    optr+=slen;
		} else {
		    /* Not an error, but user has Canceled the dialog box.
		     * This will make the command to not be performed. */
		    goto error;
		}
		break;

#if defined(OFFIX_DND) || defined(XDND)
	     case 'd':
#ifdef XDND
        if(scr->xdestring) {
            dropped_thing = wstrdup(scr->xdestring);
        }
#endif
		if (!dropped_thing) {
		    dropped_thing = get_dnd_selection(scr);
		}
		if (!dropped_thing) {
		    scr->flags.dnd_data_convertion_status = 1;
		    goto error;
		}
		slen = strlen(dropped_thing);
		olen += slen;
		nout = realloc(out,olen);
		if (!nout) {
		    wwarning(_("out of memory during expansion of \"%d\""));
		    goto error;
		}
		out = nout;
		strcat(out,dropped_thing);
		optr+=slen;
		break;
#endif /* OFFIX_DND */
		
	     case 's':
		if (!selection) {
		    selection = getselection(scr);
		}
		if (!selection) {
		    wwarning(_("selection not available"));
		    goto error;
		}
		slen = strlen(selection);
		olen += slen;
		nout = realloc(out,olen);
		if (!nout) {
		    wwarning(_("out of memory during expansion of \"%s\""));
		    goto error;
		}
		out = nout;
		strcat(out,selection);
		optr+=slen;
		break;
	     default:
		out[optr++]='%';
		out[optr++]=cmdline[ptr];
	    }
	    break;
	}
	out[optr]=0;
	ptr++;
    }
    if (selection)
      XFree(selection);
    return out;
    
    error:
    free(out);
    if (selection)
      XFree(selection);
    return NULL;
}


/* We don't care for upper/lower case in comparing the keys; so we
   have to define our own comparison function here */
BOOL
StringCompareHook(proplist_t pl1, proplist_t pl2)
{
    char *str1, *str2;

    str1 = PLGetString(pl1);
    str2 = PLGetString(pl2);

    if (strcasecmp(str1, str2)==0)
      return YES;
    else
      return NO;
}


/* feof doesn't seem to work on pipes */
int
IsEof(FILE * stream)
{
    static struct stat stinfo;

    fstat(fileno(stream), &stinfo);
    return ((S_ISFIFO(stinfo.st_dev) && stinfo.st_size == 0) || 
            feof(stream));
}


void
ParseWindowName(proplist_t value, char **winstance, char **wclass, char *where)
{
    char *name;

    *winstance = *wclass = NULL;

    if (!PLIsString(value)) {
	wwarning(_("bad window name value in %s state info"), where);
	return;
    }

    name = PLGetString(value);
    if (!name || strlen(name)==0) {
	wwarning(_("bad window name value in %s state info"), where);
	return;
    }

    UnescapeWM_CLASS(name, winstance, wclass);
}


#if 0
static char*
keysymToString(KeySym keysym, unsigned int state)
{
    XKeyEvent kev;
    char *buf = wmalloc(20);
    int count;

    kev.display = dpy;
    kev.type = KeyPress;
    kev.send_event = False;
    kev.window = DefaultRootWindow(dpy);
    kev.root = DefaultRootWindow(dpy);
    kev.same_screen = True;
    kev.subwindow = kev.root;
    kev.serial = 0x12344321;
    kev.time = CurrentTime;
    kev.state = state;
    kev.keycode = XKeysymToKeycode(dpy, keysym);
    count = XLookupString(&kev, buf, 19, NULL, NULL);
    buf[count] = 0;

    return buf;
}
#endif

char*
GetShortcutString(char *text)
{
    char *buffer = NULL;
    char *k;
    int modmask = 0;
/*    KeySym ksym;*/
    int control = 0;
    char *tmp;
    
    tmp = text = wstrdup(text);

    /* get modifiers */
    while ((k = strchr(text, '+'))!=NULL) {
	int mod;
	
	*k = 0;
	mod = wXModifierFromKey(text);
	if (mod<0) {
	    return wstrdup("bug");
	}
		
	modmask |= mod;
	
	if (strcasecmp(text, "Meta")==0) {
	    buffer = wstrappend(buffer, "M+");
	} else if (strcasecmp(text, "Alt")==0) {
	    buffer = wstrappend(buffer, "A+");
	} else if (strcasecmp(text, "Shift")==0) {
	    buffer = wstrappend(buffer, "Sh+");
	} else if (strcasecmp(text, "Mod1")==0) {
	    buffer = wstrappend(buffer, "M1+"); 
	} else if (strcasecmp(text, "Mod2")==0) {
	    buffer = wstrappend(buffer, "M2+"); 
	} else if (strcasecmp(text, "Mod3")==0) {
	    buffer = wstrappend(buffer, "M3+");
	} else if (strcasecmp(text, "Mod4")==0) {
	    buffer = wstrappend(buffer, "M4+"); 
	} else if (strcasecmp(text, "Mod5")==0) {
	    buffer = wstrappend(buffer, "M5+"); 
	} else if (strcasecmp(text, "Control")==0) {
	    control = 1;
	} else {
	    buffer = wstrappend(buffer, text);
	}
	text = k+1;
    }

    if (control) {
	buffer = wstrappend(buffer, "^");
    }
    buffer = wstrappend(buffer, text);
    
    /* get key */
/*    ksym = XStringToKeysym(text);
    tmp = keysymToString(ksym, modmask);
    puts(tmp);
    buffer = wstrappend(buffer, tmp);
*/
    free(tmp);

    return buffer;
}


char*
EscapeWM_CLASS(char *name, char *class)
{
    char *ret;
    char *ename = NULL, *eclass = NULL;
    int i, j, l;

    if (!name && !class)
	return NULL;

    if (name) {
	l = strlen(name);
	ename = wmalloc(l*2);
	j = 0;
	for (i=0; i<l; i++) {
	    if (name[i]=='\\') {
		ename[j++] = '\\';
	    } else if (name[i]=='.') {
		ename[j++] = '\\';
	    }
	    ename[j++] = name[i];
	}
	ename[j] = 0;
    }
    if (class) {
	l = strlen(class);
	eclass = wmalloc(l*2);
	j = 0;
	for (i=0; i<l; i++) {
	    if (class[i]=='\\') {
		eclass[j++] = '\\';
	    } else if (class[i]=='.') {
		eclass[j++] = '\\';
	    }
	    eclass[j++] = class[i];
	}
	eclass[j] = 0;
    }

    if (ename && eclass) {
	ret = wmalloc(strlen(ename)+strlen(eclass)+4);
	sprintf(ret, "%s.%s", ename, eclass);
	free(ename);
	free(eclass);
    } else if (ename) {
	ret = wstrdup(ename);
	free(ename);
    } else {
	ret = wstrdup(eclass);
	free(eclass);
    }

    return ret;
}


void
UnescapeWM_CLASS(char *str, char **name, char **class)
{
    int i, j, k, dot;
    Bool esc;

    j = strlen(str);
    *name = wmalloc(j);
    **name = 0;
    *class = wmalloc(j);
    **class = 0;

    /* separate string in 2 parts */
    esc = False;
    dot = 0;
    for (i = 0; i < j; i++) {
	if (!esc) {
	    if (str[i]=='\\') {
		esc = True;
	    } else if (str[i]=='.') {
		dot = i;
		break;
	    }
	} else {
	    esc = False;
	}
    }

    /* unescape strings */
    esc = False;
    k = 0;
    for (i = 0; i < dot; i++) {
	if (!esc) {
	    if (str[i]=='\\') {
		esc = True;
	    } else {
		(*name)[k++] = str[i];
	    }
	} else {
	    (*name)[k++] = str[i];
	    esc = False;
	}
    }
    (*name)[k] = 0;

    esc = False;
    k = 0;
    for (i = dot+1; i<j; i++) {
	if (!esc) {
	    if (str[i]=='\\') {
		esc = True;
	    } else {
		(*class)[k++] = str[i];
	    }
	} else {
	    esc = False;
	}
    }
    (*class)[k] = 0;
    
    if (!*name) {
	free(*name);
	*name = NULL;
    }
    if (!*class) {
	free(*class);
	*class = NULL;
    }
}



void
SendHelperMessage(WScreen *scr, char type, int workspace, char *msg)
{
    unsigned char *buffer;
    int len;
    int i;
    char buf[16];

    if (!scr->flags.backimage_helper_launched) {
	return;
    }
    
    len = (msg ? strlen(msg) : 0) + (workspace >=0 ? 4 : 0) + 1 ;
    buffer = wmalloc(len+5);
    sprintf(buf, "%4i", len);
    memcpy(buffer, buf, 4);
    buffer[4] = type;
    i = 5;
    if (workspace >= 0) {
	sprintf(buf, "%4i", workspace);
	memcpy(&buffer[i], buf, 4);
	i += 4;
	buffer[i] = 0;
    }
    if (msg)
	strcpy(&buffer[i], msg);

    if (write(scr->helper_fd, buffer, len+4) < 0) {
	wsyserror(_("could not send message to background image helper"));
    }
    free(buffer);
}



typedef struct {
    WScreen *scr;
    char *command;
} _tuple;


static void
shellCommandHandler(pid_t pid, unsigned char status, _tuple *data)
{
    if (status == 127) {
	char *buffer;

	buffer = wstrappend(_("Could not execute command: "), data->command);

	wMessageDialog(data->scr, _("Error"), buffer, _("OK"), NULL, NULL);
	free(buffer);
    } else if (status != 127) {
	/*
	printf("%s: %i\n", data->command, status);
	 */
    }

    free(data->command);
    free(data);
}


void
ExecuteShellCommand(WScreen *scr, char *command)
{
    static char *shell = NULL;
    pid_t pid;

    /*
     * This have a problem: if the shell is tcsh (not sure about others)
     * and ~/.tcshrc have /bin/stty erase ^H somewhere on it, the shell
     * will block and the command will not be executed.
    if (!shell) {
	shell = getenv("SHELL");
	if (!shell)
	    shell = "/bin/sh";
    }
     */
    shell = "/bin/sh";

    pid = fork();
    
    if (pid==0) {

	SetupEnvironment(scr);

#ifdef HAVE_SETPGID
	setpgid(0, 0);
#endif
	execl(shell, shell, "-c", command, NULL);
	wsyserror("could not execute %s -c %s", shell, command);
	Exit(-1);
    } else if (pid < 0) {
	wsyserror("cannot fork a new process");
    } else {
	_tuple *data = wmalloc(sizeof(_tuple));
	
	data->scr = scr;
	data->command = wstrdup(command);

	wAddDeathHandler(pid, (WDeathHandler*)shellCommandHandler, data);
    }
}





void dbprintf(char *format, ...)
{
    va_list	args;

    va_start(args, format);
    vprintf(format, args);
    fflush(stdout);
    va_end(args);
}



void dbputs(char *text)
{
    puts(text);
    fflush(stdout);
}

