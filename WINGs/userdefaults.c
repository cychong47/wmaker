
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>


#include "../src/config.h"

#include "WUtil.h"

#include <proplist.h>


typedef struct W_UserDefaults {
    proplist_t defaults;

    proplist_t appDomain;

    proplist_t searchListArray;
    proplist_t *searchList;	       /* cache for searchListArray */

    char dirty;

    char *path;                        /* where is db located */

    struct W_UserDefaults *next;

} UserDefaults;


static UserDefaults *sharedUserDefaults = NULL;

static Bool registeredSaveOnExit = False;



extern char *WMGetApplicationName();

#define DEFAULTS_DIR "/Defaults"


char*
wusergnusteppath()
{
    static char *path = NULL;
    char *gspath;
    int pathlen;

    if (!path) {
	gspath = getenv("GNUSTEP_USER_ROOT");
	if (gspath) {
	    gspath = wexpandpath(gspath);
	    pathlen = strlen(gspath) + 4;
	    path = wmalloc(pathlen);
	    strcpy(path, gspath);
	    free(gspath);
	} else {
	    pathlen = strlen(wgethomedir()) + 10;
	    path = wmalloc(pathlen);
	    strcpy(path, wgethomedir());
	    strcat(path, "/GNUstep");
	}
    }

    return path;
}


char*
wdefaultspathfordomain(char *domain)
{
    char *path;
    char *gspath;

    gspath = wusergnusteppath();
    path = wmalloc(strlen(gspath)+strlen(DEFAULTS_DIR)+strlen(domain)+4);
    strcpy(path, gspath);
    strcat(path, DEFAULTS_DIR);
    strcat(path, "/");
    strcat(path, domain);

    return path;
}


static void
#ifndef HAVE_ATEXIT
saveDefaultsChanges(int foo, void *bar)
#else
saveDefaultsChanges(void)
#endif
{
    /* save the user defaults databases */
    if (sharedUserDefaults) {
        UserDefaults *tmp = sharedUserDefaults;

        while (tmp) {
            if (tmp->appDomain && tmp->dirty)
                PLShallowSynchronize(tmp->appDomain);
            tmp = tmp->next;
        }
    }
}


/* set to save changes in defaults when program is exited */
static void
registerSaveOnExit(void)
{
    if (!registeredSaveOnExit) {
#ifndef HAVE_ATEXIT
        on_exit(saveDefaultsChanges, (void*)NULL);
#else
        atexit(saveDefaultsChanges);
#endif
        registeredSaveOnExit = True;
    }
}


void
WMSynchronizeUserDefaults(WMUserDefaults *database)
{
    /* TODO: check what it should really do */
    PLShallowSynchronize(database->appDomain);
}


WMUserDefaults*
WMGetStandardUserDefaults(void)
{
    WMUserDefaults *defaults;
    proplist_t domain;
    proplist_t key;
    char *path;
    int i;

    if (sharedUserDefaults) {
        defaults = sharedUserDefaults;
        while (defaults) {
            /* Trick, path == NULL only for StandardUserDefaults db */
            if (defaults->path == NULL)
                return defaults;
            defaults = defaults->next;
        }
    }

    /* we didn't found the database we are looking for. Go read it. */
    defaults = wmalloc(sizeof(WMUserDefaults));
    memset(defaults, 0, sizeof(WMUserDefaults));

    defaults->defaults = PLMakeDictionaryFromEntries(NULL, NULL, NULL);

    defaults->searchList = wmalloc(sizeof(proplist_t)*3);

    /* application domain */
    key = PLMakeString(WMGetApplicationName());
    defaults->searchList[0] = key;

    /* temporary kluge */
    if (strcmp(WMGetApplicationName(), "WindowMaker")==0) {
        domain = NULL;
        path = NULL;
    } else {
        path = wdefaultspathfordomain(PLGetString(key));

        domain = PLGetProplistWithPath(path);
    }
    if (!domain) {
        proplist_t p;

        domain = PLMakeDictionaryFromEntries(NULL, NULL, NULL);
        if (path) {
            p = PLMakeString(path);
            PLSetFilename(domain, p);
            PLRelease(p);
        }
    }
    if (path)
        free(path);

    defaults->appDomain = domain;

    if (domain)
        PLInsertDictionaryEntry(defaults->defaults, key, domain);

    PLRelease(key);

    /* global domain */
    key = PLMakeString("WMGLOBAL");
    defaults->searchList[1] = key;

    path = wdefaultspathfordomain(PLGetString(key));

    domain = PLGetProplistWithPath(path);

    free(path);

    if (!domain)
        domain = PLMakeDictionaryFromEntries(NULL, NULL, NULL);

    if (domain)
        PLInsertDictionaryEntry(defaults->defaults, key, domain);

    PLRelease(key);

    /* terminate list */
    defaults->searchList[2] = NULL;

    defaults->searchListArray=PLMakeArrayFromElements(NULL,NULL);


    i = 0;
    while (defaults->searchList[i]) {
        PLAppendArrayElement(defaults->searchListArray,
                             defaults->searchList[i]);
        i++;
    }

    if (sharedUserDefaults)
        defaults->next = sharedUserDefaults;
    sharedUserDefaults = defaults;

    registerSaveOnExit();

    return defaults;
}


WMUserDefaults*
WMGetDefaultsFromPath(char *path)
{
    WMUserDefaults *defaults;
    proplist_t domain;
    proplist_t key;
    char *name;
    int i;

    assert(path != NULL);

    if (sharedUserDefaults) {
        defaults = sharedUserDefaults;
        while (defaults) {
            if (defaults->path && strcmp(defaults->path, path) == 0)
                return defaults;
            defaults = defaults->next;
        }
    }

    /* we didn't found the database we are looking for. Go read it. */
    defaults = wmalloc(sizeof(WMUserDefaults));
    memset(defaults, 0, sizeof(WMUserDefaults));

    defaults->defaults = PLMakeDictionaryFromEntries(NULL, NULL, NULL);

    defaults->searchList = wmalloc(sizeof(proplist_t)*2);

    /* the domain we want, go in the first position */
    name = strrchr(path, '/');
    if (!name)
        name = path;
    else
        name++;

    key = PLMakeString(name);
    defaults->searchList[0] = key;

    domain = PLGetProplistWithPath(path);

    if (!domain) {
        proplist_t p;

        domain = PLMakeDictionaryFromEntries(NULL, NULL, NULL);
        p = PLMakeString(path);
        PLSetFilename(domain, p);
        PLRelease(p);
    }

    defaults->path = wstrdup(path);

    defaults->appDomain = domain;

    if (domain)
        PLInsertDictionaryEntry(defaults->defaults, key, domain);

    PLRelease(key);

    /* terminate list */
    defaults->searchList[1] = NULL;

    defaults->searchListArray=PLMakeArrayFromElements(NULL,NULL);

    i = 0;
    while (defaults->searchList[i]) {
        PLAppendArrayElement(defaults->searchListArray,
                             defaults->searchList[i]);
        i++;
    }

    if (sharedUserDefaults)
        defaults->next = sharedUserDefaults;
    sharedUserDefaults = defaults;

    registerSaveOnExit();

    return defaults;
}


proplist_t
WMGetUDObjectForKey(WMUserDefaults *database, char *defaultName)
{
    proplist_t domainName, domain;
    proplist_t object = NULL;
    proplist_t key = PLMakeString(defaultName);
    int i = 0;
    
    while (database->searchList[i] && !object) {
	domainName = database->searchList[i];
	domain = PLGetDictionaryEntry(database->defaults, domainName);
	if (domain) {
	    object = PLGetDictionaryEntry(domain, key);
	}
	i++;
    }
    PLRelease(key);
    
    return object;
}


void
WMSetUDObjectForKey(WMUserDefaults *database, proplist_t object,
		    char *defaultName)
{
    proplist_t key = PLMakeString(defaultName);

    database->dirty = 1;

    PLInsertDictionaryEntry(database->appDomain, key, object);
    PLRelease(key);
}


void
WMRemoveUDObjectForKey(WMUserDefaults *database, char *defaultName)
{
    proplist_t key = PLMakeString(defaultName);

    database->dirty = 1;

    PLRemoveDictionaryEntry(database->appDomain, key);
    
    PLRelease(key);
}


char*
WMGetUDStringForKey(WMUserDefaults *database, char *defaultName)
{
    proplist_t val;
    
    val = WMGetUDObjectForKey(database, defaultName);

    if (!val)
	return NULL;

    if (!PLIsString(val))
	return NULL;

    return PLGetString(val);
}


int
WMGetUDIntegerForKey(WMUserDefaults *database, char *defaultName)
{
    proplist_t val;
    char *str;
    int value;

    val = WMGetUDObjectForKey(database, defaultName);
    
    if (!val)
	return 0;

    if (!PLIsString(val))
	return 0;
    
    str = PLGetString(val);
    if (!str)
	return 0;
    
    if (sscanf(str, "%i", &value)!=1)
	return 0;

    return value;
}



float
WMGetUDFloatForKey(WMUserDefaults *database, char *defaultName)
{
    proplist_t val;
    char *str;
    float value;

    val = WMGetUDObjectForKey(database, defaultName);
    
    if (!val || !PLIsString(val))
	return 0.0;

    if (!(str = PLGetString(val)))
	return 0.0;

    if (sscanf(str, "%f", &value)!=1)
	return 0.0;

    return value;
}



Bool
WMGetUDBoolForKey(WMUserDefaults *database, char *defaultName)
{
    proplist_t val;
    int value;
    char *str;

    val = WMGetUDObjectForKey(database, defaultName);
    
    if (!val)
	return False;

    if (!PLIsString(val))
	return False;
    
    str = PLGetString(val);
    if (!str)
	return False;
    
    if (sscanf(str, "%i", &value)==1 && value!=0)
	return True;

    if (strcasecmp(str, "YES")==0)
	return True;

    if (strcasecmp(str, "Y")==0)
	return True;

    return False;
}


void
WMSetUDIntegerForKey(WMUserDefaults *database, int value, char *defaultName)
{
    proplist_t object;
    char buffer[128];

    sprintf(buffer, "%i", value);
    object = PLMakeString(buffer);
 
    WMSetUDObjectForKey(database, object, defaultName);
    PLRelease(object);
}




void
WMSetUDStringForKey(WMUserDefaults *database, char *value, char *defaultName)
{
    proplist_t object;

    object = PLMakeString(value);

    WMSetUDObjectForKey(database, object, defaultName);
    PLRelease(object);
}



void
WMSetUDFloatForKey(WMUserDefaults *database, float value, char *defaultName)
{
    proplist_t object;
    char buffer[128];

    sprintf(buffer, "%f", value);
    object = PLMakeString(buffer);

    WMSetUDObjectForKey(database, object, defaultName);
    PLRelease(object);
}



void
WMSetUDBoolForKey(WMUserDefaults *database, Bool value, char *defaultName)
{
    static proplist_t yes = NULL, no = NULL;

    if (!yes) {
	yes = PLMakeString("YES");
	no = PLMakeString("NO");
    }

    WMSetUDObjectForKey(database, value ? yes : no, defaultName);
}


proplist_t
WMGetUDSearchList(WMUserDefaults *database)
{
    return database->searchListArray;
}


void
WMSetUDSearchList(WMUserDefaults *database, proplist_t list)
{
    int i, c;
    
    if (database->searchList) {
	i = 0;
	while (database->searchList[i]) {
	    PLRelease(database->searchList[i]);
	    i++;
	}
	free(database->searchList);
    }
    if (database->searchListArray) {
	PLRelease(database->searchListArray);
    }

    c = PLGetNumberOfElements(list);
    database->searchList = wmalloc(sizeof(proplist_t)*(c+1));

    for (i=0; i<c; i++) {
	database->searchList[i] = PLGetArrayElement(list, i);
    }
    
    database->searchListArray = PLDeepCopy(list);
}


