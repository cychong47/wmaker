

#include "WINGsP.h"

#include <X11/Xutil.h>

#include <X11/cursorfont.h>

/********** data ************/


#define CHECK_BUTTON_ON_WIDTH 	16
#define CHECK_BUTTON_ON_HEIGHT 	16

static char *CHECK_BUTTON_ON[] = {
"               %",
" .............%#",
" ........... .%#",
" .......... #.%#",
" ......... #%.%#",
" ........ #%..%#",
" ... #.. #%...%#",
" ... #% #%....%#",
" ... % #%.....%#",
" ...  #%......%#",
" ... #%.......%#",
" ...#%........%#",
" .............%#",
" .............%#",
" %%%%%%%%%%%%%%#",
"%###############"};

#define CHECK_BUTTON_OFF_WIDTH 	16
#define CHECK_BUTTON_OFF_HEIGHT	16

static char *CHECK_BUTTON_OFF[] = {
"               %",
" .............%#",
" .............%#",
" .............%#",
" .............%#",
" .............%#",
" .............%#",
" .............%#",
" .............%#",
" .............%#",
" .............%#",
" .............%#",
" .............%#",
" .............%#",
" %%%%%%%%%%%%%%#",
"%###############"};

#define RADIO_BUTTON_ON_WIDTH 	15
#define RADIO_BUTTON_ON_HEIGHT	15
static char *RADIO_BUTTON_ON[] = {
".....%%%%%.....",
"...%%#####%%...",
"..%##.....%.%..",
".%#%..    .....",
".%#.        ...",
"%#..        .. ",
"%#.          . ",
"%#.          . ",
"%#.          . ",
"%#.          . ",
".%%.        . .",
".%..        . .",
"..%...    .. ..",
".... .....  ...",
".....     .....",
};

#define RADIO_BUTTON_OFF_WIDTH 	15
#define RADIO_BUTTON_OFF_HEIGHT	15
static char *RADIO_BUTTON_OFF[] = {
".....%%%%%.....",
"...%%#####%%...",
"..%##.......%..",
".%#%...........",
".%#............",
"%#............ ",
"%#............ ",
"%#............ ",
"%#............ ",
"%#............ ",
".%%.......... .",
".%........... .",
"..%......... ..",
".... .....  ...",
".....     .....",
};


static char *BUTTON_ARROW[] = {
"..................",
"....##....#### ...",
"...#.%....#... ...",
"..#..%#####... ...",
".#............ ...",
"#............. ...",
".#............ ...",
"..#..          ...",
"...#. ............",
"....# ............"
};

#define BUTTON_ARROW_WIDTH	18
#define BUTTON_ARROW_HEIGHT	10


static char *BUTTON_ARROW2[] = {
"                  ",
"    ##    ####.   ",
"   # %    #   .   ",
"  #  %#####   .   ",
" #            .   ",
"#             .   ",
" #            .   ",
"  #  ..........   ",
"   # .            ",
"    #.            "
};

#define BUTTON_ARROW2_WIDTH	18
#define BUTTON_ARROW2_HEIGHT	10


static char *SCROLLER_DIMPLE[] = {
".%###.",
"%#%%%%",
"#%%...",
"#%..  ",
"#%.   ",
".%.  ."
};

#define SCROLLER_DIMPLE_WIDTH   6
#define SCROLLER_DIMPLE_HEIGHT  6


static char *SCROLLER_ARROW_UP[] = {
"....%....",
"....#....",
"...%#%...",
"...###...",
"..%###%..",
"..#####..",
".%#####%.",
".#######.",
"%#######%"
};

static char *HI_SCROLLER_ARROW_UP[] = {
"    %    ",
"    %    ",
"   %%%   ",
"   %%%   ",
"  %%%%%  ",
"  %%%%%  ",
" %%%%%%% ",
" %%%%%%% ",
"%%%%%%%%%"
};

#define SCROLLER_ARROW_UP_WIDTH   9
#define SCROLLER_ARROW_UP_HEIGHT  9


static char *SCROLLER_ARROW_DOWN[] = {
"%#######%",
".#######.",
".%#####%.",
"..#####..",
"..%###%..",
"...###...",
"...%#%...",
"....#....",
"....%...."
};

static char *HI_SCROLLER_ARROW_DOWN[] = {
"%%%%%%%%%",
" %%%%%%% ",
" %%%%%%% ",
"  %%%%%  ",
"  %%%%%  ",
"   %%%   ",
"   %%%   ",
"    %    ",
"    %    "
};

#define SCROLLER_ARROW_DOWN_WIDTH   9
#define SCROLLER_ARROW_DOWN_HEIGHT  9



static char *SCROLLER_ARROW_LEFT[] = {
"........%",
"......%##",
"....%####",
"..%######",
"%########",
"..%######",
"....%####",
"......%##",
"........%"
};

static char *HI_SCROLLER_ARROW_LEFT[] = {
"        %",
"      %%%",
"    %%%%%",
"  %%%%%%%",
"%%%%%%%%%",
"  %%%%%%%",
"    %%%%%",
"      %%%",
"        %"
};

#define SCROLLER_ARROW_LEFT_WIDTH   9
#define SCROLLER_ARROW_LEFT_HEIGHT  9


static char *SCROLLER_ARROW_RIGHT[] = {
"%........",
"##%......",
"####%....",
"######%..",
"########%",
"######%..",
"####%....",
"##%......",
"%........"
};

static char *HI_SCROLLER_ARROW_RIGHT[] = {
"%        ",
"%%%      ",
"%%%%%    ",
"%%%%%%%  ",
"%%%%%%%%%",
"%%%%%%%  ",
"%%%%%    ",
"%%%      ",
"%        "
};

#define SCROLLER_ARROW_RIGHT_WIDTH   9
#define SCROLLER_ARROW_RIGHT_HEIGHT  9


static char *POPUP_INDICATOR[] = {
"        #==",
" ......%#==",
" ......%#%%",
" ......%#%%",
" %%%%%%%#%%",
"#########%%",
"==%%%%%%%%%",
"==%%%%%%%%%"
};

#define POPUP_INDICATOR_WIDTH	11
#define POPUP_INDICATOR_HEIGHT 	8



static char *PULLDOWN_INDICATOR[] = {
"=#######=",
"=%===== =",
"==%=== ==",
"==%=== ==",
"===%= ===",
"===%= ===",
"====%===="
};
#define PULLDOWN_INDICATOR_WIDTH	9
#define PULLDOWN_INDICATOR_HEIGHT 	7


#define CHECK_MARK_WIDTH 	8
#define CHECK_MARK_HEIGHT 	10

static char *CHECK_MARK[] = {
"======== ",
"======= #",
"====== #%",
"===== #%=",
" #== #%==",
" #% #%===",
" % #%====",
"  #%=====",
" #%======",
"#%======="};


#define STIPPLE_WIDTH 8
#define STIPPLE_HEIGHT 8
static unsigned char STIPPLE_BITS[] = {
    0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa
};




extern void W_ReadConfigurations(void);


static int userWidgetCount=0;


/*****  end data  ******/


static void
renderPixmap(W_Screen *screen, Pixmap d, Pixmap mask, char **data, 
	     int width, int height)
{
    int x, y;
    GC whiteGC = WMColorGC(screen->white);
    GC blackGC = WMColorGC(screen->black);
    GC lightGC = WMColorGC(screen->gray);
    GC darkGC = WMColorGC(screen->darkGray);


    if (mask)
	XSetForeground(screen->display, screen->monoGC, 0);
	
    for (y = 0; y < height; y++) {
	for (x = 0; x < width; x++) {
	    switch (data[y][x]) {		
	     case ' ':
	     case 'w':
		XDrawPoint(screen->display, d, whiteGC, x, y);
		break;

	     case '=':
		if (mask)
		    XDrawPoint(screen->display, mask, screen->monoGC, x, y);
		       
	     case '.':
	     case 'l':
		XDrawPoint(screen->display, d, lightGC, x, y);
		break;
		
	     case '%':
	     case 'd':
		XDrawPoint(screen->display, d, darkGC, x, y);
		break;
		
	     case '#':
	     case 'b':
	     default:
		XDrawPoint(screen->display, d, blackGC, x, y);
		break;
	    }
	}
    }
}



static WMPixmap*
makePixmap(W_Screen *sPtr, char **data, int width, int height, int masked)
{
    Pixmap pixmap, mask = None;
    
    pixmap = XCreatePixmap(sPtr->display, W_DRAWABLE(sPtr), width, height, 
			   sPtr->depth);
    
    if (masked) {
	mask = XCreatePixmap(sPtr->display, W_DRAWABLE(sPtr), width, height, 1);
	XSetForeground(sPtr->display, sPtr->monoGC, 1);
	XFillRectangle(sPtr->display, mask, sPtr->monoGC, 0, 0, width, height);
    }

    renderPixmap(sPtr, pixmap, mask, data, width, height);

    return WMCreatePixmapFromXPixmaps(sPtr, pixmap, mask, width, height,
				      sPtr->depth);
}


#define T_WINGS_IMAGES_FILE  RESOURCE_PATH"/Images.tiff"
#define T_DEFAULT_OBJECT_ICON_FILE RESOURCE_PATH"/defaultIcon.tiff"

#define X_WINGS_IMAGES_FILE  RESOURCE_PATH"/Images.xpm"
#define X_DEFAULT_OBJECT_ICON_FILE RESOURCE_PATH"/defaultIcon.xpm"


static Bool
loadPixmaps(WMScreen *scr)
{
    RImage *image, *tmp;
    RColor gray;
    RColor white;

    gray.red = 0xae;
    gray.green = 0xaa;
    gray.blue = 0xae;

    white.red = 0xff;
    white.green = 0xff;
    white.blue = 0xff;

    image = RLoadImage(scr->rcontext, T_WINGS_IMAGES_FILE, 0);
    if (!image)
	image = RLoadImage(scr->rcontext, X_WINGS_IMAGES_FILE, 0);
    if (!image) {
	wwarning("WINGs: could not load widget images file: %s", 
		 RMessageForError(RErrorCode));
	return False;
    }
    /* home icon */
    /* make it have a gray background */
    tmp = RGetSubImage(image, 0, 0, 24, 24);
    RCombineImageWithColor(tmp, &gray);
    scr->homeIcon = WMCreatePixmapFromRImage(scr, tmp, 128);
    RDestroyImage(tmp);
    /* make it have a white background */
    tmp = RGetSubImage(image, 0, 0, 24, 24);
    RCombineImageWithColor(tmp, &white);
    scr->altHomeIcon = WMCreatePixmapFromRImage(scr, tmp, 128);
    RDestroyImage(tmp);

    /* trash can */
    tmp = RGetSubImage(image, 104, 0, 24, 24);
    RCombineImageWithColor(tmp, &white);
    scr->trashcanIcon = WMCreatePixmapFromRImage(scr, tmp, 128);
    RDestroyImage(tmp);
    tmp = RGetSubImage(image, 104, 0, 24, 24);
    RCombineImageWithColor(tmp, &white);
    scr->altTrashcanIcon = WMCreatePixmapFromRImage(scr, tmp, 128);
    RDestroyImage(tmp);
    /* create dir */
    tmp = RGetSubImage(image, 104, 24, 24, 24);
    RCombineImageWithColor(tmp, &white);
    scr->createDirIcon = WMCreatePixmapFromRImage(scr, tmp, 128);
    RDestroyImage(tmp);
    tmp = RGetSubImage(image, 104, 24, 24, 24);
    RCombineImageWithColor(tmp, &white);
    scr->altCreateDirIcon = WMCreatePixmapFromRImage(scr, tmp, 128);
    RDestroyImage(tmp);
    /* diskettes */
    tmp = RGetSubImage(image, 24, 80, 24, 24);
    RCombineImageWithColor(tmp, &white);
    scr->disketteIcon = WMCreatePixmapFromRImage(scr, tmp, 128);
    RDestroyImage(tmp);
    tmp = RGetSubImage(image, 24, 80, 24, 24);
    RCombineImageWithColor(tmp, &white);
    scr->altDisketteIcon = WMCreatePixmapFromRImage(scr, tmp, 128);
    RDestroyImage(tmp);
    /* unmount */
    tmp = RGetSubImage(image, 0, 80, 24, 24);
    RCombineImageWithColor(tmp, &white);
    scr->unmountIcon = WMCreatePixmapFromRImage(scr, tmp, 128);
    RDestroyImage(tmp);
    tmp = RGetSubImage(image, 0, 80, 24, 24);
    RCombineImageWithColor(tmp, &white);
    scr->altUnmountIcon = WMCreatePixmapFromRImage(scr, tmp, 128);
    RDestroyImage(tmp);

    /* Magnifying Glass Icon for ColorPanel */
    tmp = RGetSubImage(image, 24, 0, 40, 32);
    RCombineImageWithColor(tmp, &gray);
    scr->magnifyIcon = WMCreatePixmapFromRImage(scr, tmp, 128);
    RDestroyImage(tmp);
    /* ColorWheel Icon for ColorPanel */
    tmp = RGetSubImage(image, 0, 25, 24, 24);
    scr->wheelIcon = WMCreatePixmapFromRImage(scr, tmp, 128);
    RDestroyImage(tmp);
    /* GrayScale Icon for ColorPanel */
    tmp = RGetSubImage(image, 65, 0, 40, 24);
    scr->grayIcon = WMCreatePixmapFromRImage(scr, tmp, 128);
    RDestroyImage(tmp);
    /* RGB Icon for ColorPanel */
    tmp = RGetSubImage(image, 25, 33, 40, 24);
    scr->rgbIcon = WMCreatePixmapFromRImage(scr, tmp, 128);
    RDestroyImage(tmp);
    /* CMYK Icon for ColorPanel */
    tmp = RGetSubImage(image, 65, 25, 40, 24);
    scr->cmykIcon = WMCreatePixmapFromRImage(scr, tmp, 128);
    RDestroyImage(tmp);
    /* HSB Icon for ColorPanel */
    tmp = RGetSubImage(image, 0, 57, 40, 24);
    scr->hsbIcon = WMCreatePixmapFromRImage(scr, tmp, 128);
    RDestroyImage(tmp);
    /* CustomColorPalette Icon for ColorPanel */
    tmp = RGetSubImage(image, 81, 57, 40, 24);
    scr->customPaletteIcon = WMCreatePixmapFromRImage(scr, tmp, 128);
    RDestroyImage(tmp);
    /* ColorList Icon for ColorPanel */
    tmp = RGetSubImage(image, 41, 57, 40, 24);
    scr->colorListIcon = WMCreatePixmapFromRImage(scr, tmp, 128);
    RDestroyImage(tmp);
    
    RDestroyImage(image);

#if 0
    scr->defaultObjectIcon =
	WMCreatePixmapFromFile(scr, T_DEFAULT_OBJECT_ICON_FILE);
    if (!scr->defaultObjectIcon) { 
	scr->defaultObjectIcon =
	    WMCreatePixmapFromFile(scr, X_DEFAULT_OBJECT_ICON_FILE);
    }
    if (!scr->defaultObjectIcon) {
	wwarning("WINGs: could not load default icon file");
	return False;
    }
#endif
    return True;
}



WMScreen*
WMCreateSimpleApplicationScreen(Display *display)
{
    WMScreen *scr;
    
    scr = WMCreateScreen(display, DefaultScreen(display));
    
    scr->aflags.hasAppIcon = 0;
    scr->aflags.simpleApplication = 1;
    
    return scr;
}



WMScreen*
WMCreateScreen(Display *display, int screen)
{
    return WMCreateScreenWithRContext(display, screen,
				      RCreateContext(display, screen, NULL));
}


WMScreen*
WMCreateScreenWithRContext(Display *display, int screen, RContext *context)
{
    W_Screen *scrPtr;
    XGCValues gcv;
    Pixmap stipple;
    static int initialized = 0;
    static char *atomNames[] = {
	"_GNUSTEP_WM_ATTR",
	    "WM_DELETE_WINDOW",
	    "WM_PROTOCOLS",
	    "CLIPBOARD",
	    "XdndAware",
	    "XdndSelection",
	    "XdndEnter",
	    "XdndLeave",
	    "XdndPosition",
	    "XdndDrop",
	    "XdndFinished",
	    "XdndTypeList",
	    "XdndActionCopy",
	    "XdndActionMove",
	    "XdndActionLink",
	    "XdndActionAsk",
	    "XdndActionPrivate",
	    "XdndStatus",
	    "_WINGS_DND_MOUSE_OFFSET",
	    "WM_STATE"
    };
    Atom atoms[sizeof(atomNames)/sizeof(char*)];
    int i = 0;

    if (!initialized) {

	initialized = 1;

	W_ReadConfigurations();

	assert(W_ApplicationInitialized());
    }
    
    scrPtr = malloc(sizeof(W_Screen));
    if (!scrPtr)
	return NULL;
    memset(scrPtr, 0, sizeof(W_Screen));
    
    scrPtr->aflags.hasAppIcon = 1;
    
    scrPtr->display = display;
    scrPtr->screen = screen;
    scrPtr->rcontext = context;

    scrPtr->depth = context->depth;

    scrPtr->visual = context->visual;
    scrPtr->lastEventTime = 0;

    scrPtr->colormap = context->cmap;

    scrPtr->rootWin = RootWindow(display, screen);

    scrPtr->fontCache = WMCreateHashTable(WMStringPointerHashCallbacks);

    /* initially allocate some colors */
    WMWhiteColor(scrPtr);
    WMBlackColor(scrPtr);
    WMGrayColor(scrPtr);
    WMDarkGrayColor(scrPtr);
    
    gcv.graphics_exposures = False;
    
    gcv.function = GXxor;
    gcv.foreground = W_PIXEL(scrPtr->white);
    if (gcv.foreground == 0) gcv.foreground = 1;
    scrPtr->xorGC = XCreateGC(display, W_DRAWABLE(scrPtr), GCFunction
			      |GCGraphicsExposures|GCForeground, &gcv);

    gcv.function = GXxor;
    gcv.foreground = W_PIXEL(scrPtr->gray);
    gcv.subwindow_mode = IncludeInferiors;
    scrPtr->ixorGC = XCreateGC(display, W_DRAWABLE(scrPtr), GCFunction
			       |GCGraphicsExposures|GCForeground
			       |GCSubwindowMode, &gcv);

    gcv.function = GXcopy;
    scrPtr->copyGC = XCreateGC(display, W_DRAWABLE(scrPtr), GCFunction
			       |GCGraphicsExposures, &gcv);

    scrPtr->clipGC = XCreateGC(display, W_DRAWABLE(scrPtr), GCFunction
			       |GCGraphicsExposures, &gcv);

    
    stipple = XCreateBitmapFromData(display, W_DRAWABLE(scrPtr), 
				    STIPPLE_BITS, STIPPLE_WIDTH, STIPPLE_HEIGHT);
    gcv.foreground = W_PIXEL(scrPtr->darkGray);
    gcv.background = W_PIXEL(scrPtr->gray);
    gcv.fill_style = FillStippled;
    gcv.stipple = stipple;
    scrPtr->stippleGC = XCreateGC(display, W_DRAWABLE(scrPtr),
				  GCForeground|GCBackground|GCStipple
				  |GCFillStyle|GCGraphicsExposures, &gcv);

    gcv.foreground = W_PIXEL(scrPtr->black);
    gcv.background = W_PIXEL(scrPtr->white);
    scrPtr->textFieldGC = XCreateGC(display, W_DRAWABLE(scrPtr),
				    GCForeground|GCBackground, &gcv);

    /* we need a 1bpp drawable for the monoGC, so borrow this one */
    scrPtr->monoGC = XCreateGC(display, stipple, 0, NULL);

    scrPtr->stipple = stipple;

    scrPtr->useMultiByte = WINGsConfiguration.useMultiByte;

    scrPtr->normalFont = WMSystemFontOfSize(scrPtr, 
		WINGsConfiguration.defaultFontSize);

    scrPtr->boldFont = WMBoldSystemFontOfSize(scrPtr, 
		WINGsConfiguration.defaultFontSize);

    if (!scrPtr->boldFont)
	scrPtr->boldFont = scrPtr->normalFont;

    if (!scrPtr->normalFont) {
	wwarning("could not load any fonts. Make sure your font installation"
		 "and locale settings are correct.");

	return NULL;
    }

    scrPtr->checkButtonImageOn = makePixmap(scrPtr, CHECK_BUTTON_ON,
					    CHECK_BUTTON_ON_WIDTH,
					    CHECK_BUTTON_ON_HEIGHT, False);

    scrPtr->checkButtonImageOff = makePixmap(scrPtr, CHECK_BUTTON_OFF,
					    CHECK_BUTTON_OFF_WIDTH,
					    CHECK_BUTTON_OFF_HEIGHT, False);

    scrPtr->radioButtonImageOn = makePixmap(scrPtr, RADIO_BUTTON_ON,
					    RADIO_BUTTON_ON_WIDTH,
					    RADIO_BUTTON_ON_HEIGHT, False);

    scrPtr->radioButtonImageOff = makePixmap(scrPtr, RADIO_BUTTON_OFF,
					    RADIO_BUTTON_OFF_WIDTH,
					    RADIO_BUTTON_OFF_HEIGHT, False);

    scrPtr->buttonArrow = makePixmap(scrPtr, BUTTON_ARROW, 
				     BUTTON_ARROW_WIDTH, BUTTON_ARROW_HEIGHT, 
				     False);

    scrPtr->pushedButtonArrow = makePixmap(scrPtr, BUTTON_ARROW2,
			           BUTTON_ARROW2_WIDTH, BUTTON_ARROW2_HEIGHT, 
				   False);


    scrPtr->scrollerDimple = makePixmap(scrPtr, SCROLLER_DIMPLE,
					SCROLLER_DIMPLE_WIDTH,
					SCROLLER_DIMPLE_HEIGHT, False);


    scrPtr->upArrow = makePixmap(scrPtr, SCROLLER_ARROW_UP,
				 SCROLLER_ARROW_UP_WIDTH,
				 SCROLLER_ARROW_UP_HEIGHT, True);

    scrPtr->downArrow = makePixmap(scrPtr, SCROLLER_ARROW_DOWN,
				   SCROLLER_ARROW_DOWN_WIDTH,
				   SCROLLER_ARROW_DOWN_HEIGHT, True);

    scrPtr->leftArrow = makePixmap(scrPtr, SCROLLER_ARROW_LEFT,
				   SCROLLER_ARROW_LEFT_WIDTH,
				   SCROLLER_ARROW_LEFT_HEIGHT, True);

    scrPtr->rightArrow = makePixmap(scrPtr, SCROLLER_ARROW_RIGHT,
				    SCROLLER_ARROW_RIGHT_WIDTH,
				    SCROLLER_ARROW_RIGHT_HEIGHT, True);

    scrPtr->hiUpArrow = makePixmap(scrPtr, HI_SCROLLER_ARROW_UP,
				 SCROLLER_ARROW_UP_WIDTH,
				 SCROLLER_ARROW_UP_HEIGHT, True);

    scrPtr->hiDownArrow = makePixmap(scrPtr, HI_SCROLLER_ARROW_DOWN,
				   SCROLLER_ARROW_DOWN_WIDTH,
				   SCROLLER_ARROW_DOWN_HEIGHT, True);

    scrPtr->hiLeftArrow = makePixmap(scrPtr, HI_SCROLLER_ARROW_LEFT,
				   SCROLLER_ARROW_LEFT_WIDTH,
				   SCROLLER_ARROW_LEFT_HEIGHT, True);

    scrPtr->hiRightArrow = makePixmap(scrPtr, HI_SCROLLER_ARROW_RIGHT,
				    SCROLLER_ARROW_RIGHT_WIDTH,
				    SCROLLER_ARROW_RIGHT_HEIGHT, True);

    scrPtr->popUpIndicator = makePixmap(scrPtr, POPUP_INDICATOR,
					POPUP_INDICATOR_WIDTH,
					POPUP_INDICATOR_HEIGHT, True);

    scrPtr->pullDownIndicator = makePixmap(scrPtr, PULLDOWN_INDICATOR,
					   PULLDOWN_INDICATOR_WIDTH,
					   PULLDOWN_INDICATOR_HEIGHT, True);

    scrPtr->checkMark = makePixmap(scrPtr, CHECK_MARK,
				   CHECK_MARK_WIDTH,
				   CHECK_MARK_HEIGHT, True);

    loadPixmaps(scrPtr);

    scrPtr->defaultCursor = XCreateFontCursor(display, XC_left_ptr);

    scrPtr->textCursor = XCreateFontCursor(display, XC_xterm);

    {
	XColor bla;
	Pixmap blank;
	
	blank = XCreatePixmap(display, scrPtr->stipple, 1, 1, 1);
	XSetForeground(display, scrPtr->monoGC, 0);
	XFillRectangle(display, blank, scrPtr->monoGC, 0, 0, 1, 1);

	scrPtr->invisibleCursor = XCreatePixmapCursor(display, blank, blank,
						      &bla, &bla, 0, 0);
	XFreePixmap(display, blank);
    }

#ifdef HAVE_XINTERNATOMS
    XInternAtoms(display, atomNames, sizeof(atomNames)/sizeof(char*), False,
		 atoms);
#else
    {
	int i;
	for (i = 0; i < sizeof(atomNames)/sizeof(char*); i++) {
	    atoms[i] = XInternAtom(display, atomNames[i], False);
	}
    }
#endif

    i = 0;
    scrPtr->attribsAtom = atoms[i++];

    scrPtr->deleteWindowAtom = atoms[i++];

    scrPtr->protocolsAtom = atoms[i++];
    
    scrPtr->clipboardAtom = atoms[i++];

    scrPtr->xdndAwareAtom = atoms[i++];
    scrPtr->xdndSelectionAtom = atoms[i++];
    scrPtr->xdndEnterAtom = atoms[i++];
    scrPtr->xdndLeaveAtom = atoms[i++];
    scrPtr->xdndPositionAtom = atoms[i++];
    scrPtr->xdndDropAtom = atoms[i++];
    scrPtr->xdndFinishedAtom = atoms[i++];
    scrPtr->xdndTypeListAtom = atoms[i++];
    scrPtr->xdndStatusAtom = atoms[i++];

    scrPtr->xdndActionCopy = atoms[i++];
    scrPtr->xdndActionMove = atoms[i++];
    scrPtr->xdndActionLink = atoms[i++];
    scrPtr->xdndActionAsk = atoms[i++];
    scrPtr->xdndActionPrivate = atoms[i++];

    scrPtr->wmIconDragOffsetAtom = atoms[i++];

    scrPtr->wmStateAtom = atoms[i++];
	
    scrPtr->rootView = W_CreateRootView(scrPtr);


    scrPtr->balloon = W_CreateBalloon(scrPtr);


    W_InitApplication(scrPtr);
    
    return scrPtr;
}



void
WMSetWidgetDefaultFont(WMScreen *scr, WMFont *font)
{
    WMReleaseFont(scr->normalFont);
    scr->normalFont = WMRetainFont(font);
}


void
WMSetWidgetDefaultBoldFont(WMScreen *scr, WMFont *font)
{
    WMReleaseFont(scr->boldFont);
    scr->boldFont = WMRetainFont(font);
}



void 
WMHangData(WMWidget *widget, void *data)
{
    W_VIEW(widget)->hangedData = data;
}


void*
WMGetHangedData(WMWidget *widget)
{
    return W_VIEW(widget)->hangedData;
}



void
WMDestroyWidget(WMWidget *widget)
{
    W_UnmapView(W_VIEW(widget));
    W_DestroyView(W_VIEW(widget));
}


void
WMSetFocusToWidget(WMWidget *widget)
{
    W_SetFocusOfTopLevel(W_TopLevelOfView(W_VIEW(widget)), W_VIEW(widget));
}


/*
 * WMRealizeWidget-
 * 	Realizes the widget and all it's children.
 * 
 */
void
WMRealizeWidget(WMWidget *w)
{
    W_RealizeView(W_VIEW(w));
}

void
WMMapWidget(WMWidget *w)
{        
    W_MapView(W_VIEW(w));
}


void
WMReparentWidget(WMWidget *w, WMWidget *newParent, int x, int y)
{
    W_ReparentView(W_VIEW(w), newParent, x, y);
}


static void
makeChildrenAutomap(W_View *view, int flag)
{
    view = view->childrenList;
    
    while (view) {
	view->flags.mapWhenRealized = flag;
	makeChildrenAutomap(view, flag);
	
	view = view->nextSister;
    }
}


void
WMMapSubwidgets(WMWidget *w)
{   
    /* make sure that subwidgets created after the parent was realized
     * are mapped too */
    if (!W_VIEW(w)->flags.realized) {
	makeChildrenAutomap(W_VIEW(w), True);
    } else {
	W_MapSubviews(W_VIEW(w));
    }
}


void
WMUnmapSubwidgets(WMWidget *w)
{   
    if (!W_VIEW(w)->flags.realized) {
	makeChildrenAutomap(W_VIEW(w), False);
    } else {
	W_UnmapSubviews(W_VIEW(w));
    }
}



void
WMUnmapWidget(WMWidget *w)
{   
    W_UnmapView(W_VIEW(w));
}


Bool
WMWidgetIsMapped(WMWidget *w)
{
    return W_VIEW(w)->flags.mapped;
}


void
WMSetWidgetBackgroundColor(WMWidget *w, WMColor *color)
{    
    W_SetViewBackgroundColor(W_VIEW(w), color);
    if (W_VIEW(w)->flags.mapped)
	WMRedisplayWidget(w);
}


void
WMRaiseWidget(WMWidget *w)
{
     W_RaiseView(W_VIEW(w));
}


void
WMLowerWidget(WMWidget *w)
{
     W_LowerView(W_VIEW(w));
}


void
WMMoveWidget(WMWidget *w, int x, int y)
{
    W_MoveView(W_VIEW(w), x, y);
}


void
WMResizeWidget(WMWidget *w, unsigned int width, unsigned int height)
{
    W_ResizeView(W_VIEW(w), width, height);
}



W_Class
W_RegisterUserWidget(void)
{
    userWidgetCount++;

    return userWidgetCount + WC_UserWidget - 1;
}



RContext*
WMScreenRContext(WMScreen *scr)
{
    return scr->rcontext;
}



unsigned int 
WMWidgetWidth(WMWidget *w)
{
    return W_VIEW(w)->size.width;
}


unsigned int
WMWidgetHeight(WMWidget *w)
{
    return W_VIEW(w)->size.height;
}


Window
WMWidgetXID(WMWidget *w)
{
    return W_VIEW(w)->window;
}


WMScreen*
WMWidgetScreen(WMWidget *w)
{
    return W_VIEW(w)->screen;
}



void
WMScreenMainLoop(WMScreen *scr)
{
    XEvent event;
	
    while (1) {
	WMNextEvent(scr->display, &event);
	WMHandleEvent(&event);
    }
}



Display*
WMScreenDisplay(WMScreen *scr)
{
    return scr->display;
}


int 
WMScreenDepth(WMScreen *scr)
{
    return scr->depth;
}


unsigned int 
WMScreenWidth(WMScreen *scr)
{
    return scr->rootView->size.width;
}


unsigned int
WMScreenHeight(WMScreen *scr)
{
    return scr->rootView->size.height;
}


void 
WMRedisplayWidget(WMWidget *w)
{
    W_RedisplayView(W_VIEW(w));
}

