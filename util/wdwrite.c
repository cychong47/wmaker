/* wdwrite.c - write key/value to defaults database
 *
 *  WindowMaker window manager
 *
 *  Copyright (c) 1997-2003 Alfredo K. Kojima
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

#define PROG_VERSION	"wdwrite (Window Maker) 0.2"


/*
 * WindowMaker defaults DB writer
 */


#include "../src/wconfig.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include <WINGs/WUtil.h>

#include <pwd.h>


char *ProgName;

char*
gethomedir()
{
    char *home = getenv("HOME");
    struct passwd *user;

    if (home)
        return home;

    user = getpwuid(getuid());
    if (!user) {
        perror(ProgName);
        return "/";
    }
    if (!user->pw_dir) {
        return "/";
    } else {
        return user->pw_dir;
    }
}



void wAbort()
{
    exit(0);
}

void help()
{
    printf("Syntax:\n%s [OPTIONS] <domain> <option> <value>\n", ProgName);
    puts("");
    puts("  --help		display this help message");
    puts("  --version		output version information and exit");
    exit(1);
}


int main(int argc, char **argv)
{
    char *path;
    WMPropList *dom, *key, *value, *dict;
    char *gsdir;
    int i;

    ProgName = argv[0];

    for (i = 1; i < argc; i++) {
        if (strcmp("--help", argv[i])==0) {
            help();
            exit(0);
        } else if (strcmp("--version", argv[i])==0) {
            puts(PROG_VERSION);
            exit(0);
        }
    }

    if (argc<4) {
        printf("%s: invalid argument format\n", ProgName);
        printf("Try '%s --help' for more information\n", ProgName);
        exit(1);
    }

    dom = WMCreatePLString(argv[1]);
    key = WMCreatePLString(argv[2]);
    value = WMCreatePropListFromDescription(argv[3]);
    if (!value) {
        printf("%s:syntax error in value \"%s\"", ProgName, argv[3]);
        exit(1);
    }
    gsdir = getenv("GNUSTEP_USER_ROOT");
    if (gsdir) {
        path = wstrdup(gsdir);
    } else {
        path = wstrdup(gethomedir());
        path = wstrappend(path, "/GNUstep");
    }
    path = wstrappend(path, "/");
    path = wstrappend(path, DEFAULTS_DIR);
    path = wstrappend(path, "/");
    path = wstrappend(path, argv[1]);

    dict = WMReadPropListFromFile(path);
    if (!dict) {
        dict = WMCreatePLDictionary(key, value, NULL);
    } else {
        WMPutInPLDictionary(dict, key, value);
    }

    WMWritePropListToFile(dict, path, True);
    wfree(path);

    return 0;
}


