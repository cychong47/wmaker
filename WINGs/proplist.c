

#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>

#include "WUtil.h"
#include "wconfig.h"



typedef enum {
    WPLString     = 0x57504c01,
    WPLData       = 0x57504c02,
    WPLArray      = 0x57504c03,
    WPLDictionary = 0x57504c04
} WPLType;


typedef struct W_PropList {
    WPLType type;

    union {
        char *string;
        WMData *data;
        WMArray *array;
        WMHashTable *dict;
    } d;

    int retainCount;
} W_PropList;



static unsigned hashPropList(WMPropList *plist);



typedef unsigned (*hashFunc)(const void*);
typedef Bool (*isEqualFunc)(const void*, const void*);
typedef void* (*retainFunc)(const void*);
typedef void (*releaseFunc)(const void*);

static const WMHashTableCallbacks WMPropListHashCallbacks = {
    (hashFunc)hashPropList,
    (isEqualFunc)WMIsPropListEqualToPropList,
    (retainFunc)NULL,
    (releaseFunc)NULL
};


static WMCompareDataProc *strCmp = (WMCompareDataProc*) strcmp;


#define MaxHashLength 64


static unsigned
hashPropList(WMPropList *plist)
{
    unsigned ret = 0;
    unsigned ctr = 0;
    const char *key;
    int i, len;

    switch (plist->type) {
    case WPLString:
        key = plist->d.string;
        len = WMIN(strlen(key), MaxHashLength);
        for (i=0; i<len; i++) {
            ret ^= tolower(key[i]) << ctr;
            ctr = (ctr + 1) % sizeof (char *);
        }
        /*while (*key) {
           ret ^= tolower(*key++) << ctr;
           ctr = (ctr + 1) % sizeof (char *);
        }*/
        return ret;
        /*return strlen(plist->d.string);*/

    case WPLData:
        key = WMDataBytes(plist->d.data);
        len = WMIN(WMGetDataLength(plist->d.data), MaxHashLength);
        for (i=0; i<len; i++) {
            ret ^= key[i] << ctr;
            ctr = (ctr + 1) % sizeof (char *);
        }
        return ret;
        /*return WMGetDataLength(plist->d.data);*/

    default:
        wwarning(_("Only string or data is supported for a proplist dictionary key"));
        wassertrv(False, 0);
    }
}

/*WMSetPropListStringComparisonCaseSensitive
WMSetPropListStringComparerIsCaseSensitive
WMSetPLStringComparisonCaseSensitive*/

static WMPropList*
retainPropListByCount(WMPropList *plist, int count)
{
    WMPropList *key, *value;
    WMHashEnumerator e;
    int i;

    plist->retainCount += count;

    switch(plist->type) {
    case WPLString:
    case WPLData:
        break;
    case WPLArray:
        for (i=0; i<WMGetArrayItemCount(plist->d.array); i++) {
            retainPropListByCount(WMGetFromArray(plist->d.array, i), count);
        }
        break;
    case WPLDictionary:
        e = WMEnumerateHashTable(plist->d.dict);
        while (WMNextHashEnumeratorItemAndKey(&e, (void**)&value, (void**)&key)) {
            retainPropListByCount(key, count);
            retainPropListByCount(value, count);
        }
        break;
    default:
        wwarning(_("Used proplist functions on non-WMPropLists objects"));
        wassertrv(False, NULL);
    }

    return plist;
}


static void
releasePropListByCount(WMPropList *plist, int count)
{
    WMPropList *key, *value;
    WMHashEnumerator e;
    int i;

    plist->retainCount -= count;

    switch(plist->type) {
    case WPLString:
        if (plist->retainCount < 1) {
            wfree(plist->d.string);
            wfree(plist);
        }
        break;
    case WPLData:
        if (plist->retainCount < 1) {
            WMReleaseData(plist->d.data);
            wfree(plist);
        }
        break;
    case WPLArray:
        for (i=0; i<WMGetArrayItemCount(plist->d.array); i++) {
            releasePropListByCount(WMGetFromArray(plist->d.array, i), count);
        }
        if (plist->retainCount < 1) {
            WMFreeArray(plist->d.array);
            wfree(plist);
        }
        break;
    case WPLDictionary:
        e = WMEnumerateHashTable(plist->d.dict);
        while (WMNextHashEnumeratorItemAndKey(&e, (void**)&value, (void**)&key)) {
            releasePropListByCount(key, count);
            releasePropListByCount(value, count);
        }
        if (plist->retainCount < 1) {
            WMFreeHashTable(plist->d.dict);
            wfree(plist);
        }
        break;
    default:
        wwarning(_("Used proplist functions on non-WMPropLists objects"));
        wassertr(False);
    }
}


#define num2char(num) ((num) < 0xa ? ((num)+'0') : ((num)+0x57))

static char*
dataDescription(WMPropList *plist)
{
    const unsigned char *data;
    char *retVal;
    int i, j, length;

    data = WMDataBytes(plist->d.data);
    length = WMGetDataLength(plist->d.data);

    retVal = (char*)wmalloc(2*length+length/4+3);

    retVal[0] = '<';
    for (i=0, j=1; i<length; i++) {
        retVal[j++] = num2char((data[i]>>4) & 0x0f);
        retVal[j++] = num2char(data[i] & 0x0f);
        if ((i & 0x03)==3 && i!=length-1) {
            /* if we've just finished a 32-bit int, add a space */
            retVal[j++] = ' ';
        }
    }
    retVal[j++] = '>';
    retVal[j] = '\0';

    return retVal;
}


static char*
stringDescription(WMPropList *plist)
{
    const char *str;
    char *retVal, *sPtr, *dPtr;
    int len, quote;
    unsigned char ch;

    str = plist->d.string;

    if (strlen(str) == 0) {
        return wstrdup("\"\"");
    }

    /* FIXME: make this work with unichars. */

#define inrange(ch, min, max) ((ch)>=(min) && (ch)<=(max))
#define noquote(ch) (inrange(ch, 'a', 'z') || inrange(ch, 'A', 'Z') || inrange(ch, '0', '9') || ((ch)=='_') || ((ch)=='.') || ((ch)=='$'))
#define charesc(ch) (inrange(ch, 0x07, 0x0c) || ((ch)=='"') || ((ch)=='\\'))
#define numesc(ch) (((ch)<=0x06) || inrange(ch, 0x0d, 0x1f) || ((ch)>0x7e))

    quote = 0;
    sPtr = (char*) str;
    len = 0;
    while ((ch = *sPtr)) {
        if (!noquote(ch)) {
            quote = 1;
            if (charesc(ch))
                len++;
            else if (numesc(ch))
                len += 3;
        }
        sPtr++;
        len++;
    }

    if (quote)
        len += 2;

    retVal = (char*)wmalloc(len+1);

    sPtr = (char*) str;
    dPtr = retVal;

    if (quote)
        *dPtr++ = '"';

    while ((ch = *sPtr)) {
        if (charesc(ch)) {
            *(dPtr++) = '\\';
            switch (ch) {
            case '\a': *dPtr = 'a'; break;
            case '\b': *dPtr = 'b'; break;
            case '\t': *dPtr = 't'; break;
            case '\n': *dPtr = 'n'; break;
            case '\v': *dPtr = 'v'; break;
            case '\f': *dPtr = 'f'; break;
            default: *dPtr = ch;  /* " or \ */
            }
        } else if (numesc(ch)) {
            *(dPtr++) = '\\';
            *(dPtr++) = '0' + ((ch>>6)&07);
            *(dPtr++) = '0' + ((ch>>3)&07);
            *dPtr = '0' + (ch&07);
        } else {
            *dPtr = ch;
        }
        sPtr++;
        dPtr++;
    }

    if (quote)
        *dPtr++ = '"';

    *dPtr = '\0';

    return retVal;
}


static char*
description(WMPropList *plist)
{
    WMPropList *key, *val;
    char *retstr, *str, *tmp, *skey, *sval;
    WMHashEnumerator e;
    int i;

    switch (plist->type) {
    case WPLString:
        return stringDescription(plist);
    case WPLData:
        return dataDescription(plist);
    case WPLArray:
        retstr = wstrdup("(");
        for (i=0; i<WMGetArrayItemCount(plist->d.array); i++) {
            str = description(WMGetFromArray(plist->d.array, i));
            if (i==0) {
                retstr = wstrappend(retstr, str);
            } else {
                tmp = (char *)wmalloc(strlen(retstr)+strlen(str)+3);
                sprintf(tmp, "%s, %s", retstr, str);
                wfree(retstr);
                retstr = tmp;
            }
            wfree(str);
        }
        retstr = wstrappend(retstr, ")");
        break;
    case WPLDictionary:
        retstr = wstrdup("{");
        e = WMEnumerateHashTable(plist->d.dict);
        while (WMNextHashEnumeratorItemAndKey(&e, (void**)&val, (void**)&key)) {
            skey = description(key);
            sval = description(val);
            tmp = (char*)wmalloc(strlen(retstr)+strlen(skey)+strlen(sval)+5);
            sprintf(tmp, "%s%s = %s;", retstr, skey, sval);
            wfree(skey);
            wfree(sval);
            wfree(retstr);
            retstr = tmp;
        }
        retstr = wstrappend(retstr, "}");
        break;
    default:
        wwarning(_("Used proplist functions on non-WMPropLists objects"));
        wassertrv(False, NULL);
    }

    return retstr;
}


static char*
indentedDescription(WMPropList *plist, int level)
{
    WMPropList *key, *val;
    char *retstr, *str, *tmp, *skey, *sval;
    WMHashEnumerator e;
    int i;

    switch (plist->type) {
    case WPLString:
        return stringDescription(plist);
    case WPLData:
        return dataDescription(plist);
    case WPLArray:
        retstr = wstrdup("(\n");
        for (i=0; i<WMGetArrayItemCount(plist->d.array); i++) {
            str = indentedDescription(WMGetFromArray(plist->d.array, i),
                                      level+1);
            if (i==0) {
                tmp = (char*)wmalloc(2*(level+1)+strlen(retstr)+strlen(str)+1);
                sprintf(tmp, "%s%*s%s", retstr, 2*(level+1), "", str);
                wfree(retstr);
                retstr = tmp;
            } else {
                tmp = (char*)wmalloc(2*(level+1)+strlen(retstr)+strlen(str)+3);
                sprintf(tmp, "%s,\n%*s%s", retstr, 2*(level+1), "", str);
                wfree(retstr);
                retstr = tmp;
            }
            wfree(str);
        }
        tmp = (char*)wmalloc(strlen(retstr) + 2*level + 3);
        sprintf(tmp, "%s\n%*s)", retstr, 2*level, "");
        wfree(retstr);
        retstr = tmp;
        break;
    case WPLDictionary:
        retstr = wstrdup("{\n");
        e = WMEnumerateHashTable(plist->d.dict);
        while (WMNextHashEnumeratorItemAndKey(&e, (void**)&val, (void**)&key)) {
            skey = indentedDescription(key, level+1);
            sval = indentedDescription(val, level+1);
            tmp = (char*)wmalloc(2*(level+1) + strlen(retstr) + strlen(skey)
                                 + strlen(sval) + 6);
            sprintf(tmp, "%s%*s%s = %s;\n", retstr, 2*(level+1), "",
                    skey, sval);
            wfree(skey);
            wfree(sval);
            wfree(retstr);
            retstr = tmp;
        }
        tmp = (char*)wmalloc(strlen(retstr) + 2*level + 2);
        sprintf(tmp, "%s%*s}", retstr, 2*level, "");
        wfree(retstr);
        retstr = tmp;
        break;
    default:
        wwarning(_("Used proplist functions on non-WMPropLists objects"));
        wassertrv(False, NULL);
    }

    return retstr;
}


void
WMSetPropListStringComparer(WMCompareDataProc *comparer)
{
    if (!comparer)
        strCmp = (WMCompareDataProc*) strcmp;
    else
        strCmp = comparer;
}


WMPropList*
WMCreatePropListString(char *str)
{
    WMPropList *plist;

    wassertrv(str!=NULL, NULL);

    plist = (WMPropList*)wmalloc(sizeof(W_PropList));

    plist->type = WPLString;
    plist->d.string = wstrdup(str);
    plist->retainCount = 1;

    return plist;
}


WMPropList*
WMCreatePropListDataWithBytes(unsigned char *bytes, unsigned int length)
{
    WMPropList *plist;

    wassertrv(bytes!=NULL, NULL);

    plist = (WMPropList*)wmalloc(sizeof(W_PropList));

    plist->type = WPLData;
    plist->d.data = WMCreateDataWithBytes(bytes, length);
    plist->retainCount = 1;

    return plist;
}


WMPropList*
WMCreatePropListDataWithBytesNoCopy(unsigned char *bytes, unsigned int length,
                                    WMFreeDataProc *destructor)
{
    WMPropList *plist;

    wassertrv(bytes!=NULL, NULL);

    plist = (WMPropList*)wmalloc(sizeof(W_PropList));

    plist->type = WPLData;
    plist->d.data = WMCreateDataWithBytesNoCopy(bytes, length, destructor);
    plist->retainCount = 1;

    return plist;
}


WMPropList*
WMCreatePropListDataWithData(WMData *data)
{
    WMPropList *plist;

    wassertrv(data!=NULL, NULL);

    plist = (WMPropList*)wmalloc(sizeof(W_PropList));

    plist->type = WPLData;
    plist->d.data = WMRetainData(data);
    plist->retainCount = 1;

    return plist;
}


WMPropList*
WMCreatePropListArrayFromElements(WMPropList *elem, ...)
{
    WMPropList *plist, *nelem;
    va_list ap;

    plist = (WMPropList*)wmalloc(sizeof(W_PropList));
    plist->type = WPLArray;
    plist->d.array = WMCreateArray(4);
    plist->retainCount = 1;

    if (!elem)
        return plist;

    WMAddToArray(plist->d.array, WMRetainPropList(elem));

    va_start(ap, elem);

    while (1) {
        nelem = va_arg(ap, WMPropList*);
        if(!nelem) {
            va_end(ap);
            return plist;
        }
        WMAddToArray(plist->d.array, WMRetainPropList(nelem));
    }
}


WMPropList*
WMCreatePropListDictionaryFromEntries(WMPropList *key, WMPropList *value, ...)
{
    WMPropList *plist, *nkey, *nvalue, *k, *v;
    va_list ap;

    plist = (WMPropList*)wmalloc(sizeof(W_PropList));
    plist->type = WPLDictionary;
    plist->d.dict = WMCreateHashTable(WMPropListHashCallbacks);
    plist->retainCount = 1;

    if (!key || !value)
        return plist;

    WMHashInsert(plist->d.dict, WMRetainPropList(key), WMRetainPropList(value));

    va_start(ap, value);

    while (1) {
        nkey = va_arg(ap, WMPropList*);
        if (!nkey) {
            va_end(ap);
            return plist;
        }
        nvalue = va_arg(ap, WMPropList*);
        if (!nvalue) {
            va_end(ap);
            return plist;
        }
        if (WMHashGetItemAndKey(plist->d.dict, nkey, (void**)&v, (void**)&k)) {
            WMHashRemove(plist->d.dict, k);
            WMReleasePropList(k);
            WMReleasePropList(v);
        }
        WMHashInsert(plist->d.dict, WMRetainPropList(nkey),
                     WMRetainPropList(nvalue));
    }
}


void
WMInsertPropListArrayElement(WMPropList *plist, WMPropList *item, int index)
{
    wassertr(plist->type==WPLArray);

    retainPropListByCount(item, plist->retainCount);
    WMInsertInArray(plist->d.array, index, item);
}


void
WMAppendPropListArrayElement(WMPropList *plist, WMPropList *item)
{
    wassertr(plist->type==WPLArray);

    retainPropListByCount(item, plist->retainCount);
    WMAddToArray(plist->d.array, item);
}


void
WMRemovePropListArrayElement(WMPropList *plist, int index)
{
    WMPropList *item;

    wassertr(plist->type==WPLArray);

    item = WMGetFromArray(plist->d.array, index);
    if (item != NULL) {
        WMDeleteFromArray(plist->d.array, index);
        releasePropListByCount(item, plist->retainCount);
    }
}


void
WMInsertPropListDictionaryEntry(WMPropList *plist, WMPropList *key,
                                WMPropList *value)
{
    wassertr(plist->type==WPLDictionary);

    WMRemovePropListDictionaryEntry(plist, key);
    retainPropListByCount(key, plist->retainCount);
    retainPropListByCount(value, plist->retainCount);
    WMHashInsert(plist->d.dict, key, value);
}


void
WMRemovePropListDictionaryEntry(WMPropList *plist, WMPropList *key)
{
    WMPropList *k, *v;

    wassertr(plist->type==WPLDictionary);

    if (WMHashGetItemAndKey(plist->d.dict, key, (void**)&v, (void**)&k)) {
        WMHashRemove(plist->d.dict, k);
        releasePropListByCount(k, plist->retainCount);
        releasePropListByCount(v, plist->retainCount);
    }
}


WMPropList*
WMMergePropListDictionaries(WMPropList *dest, WMPropList *source)
{
    WMPropList *key, *value;
    WMHashEnumerator e;

    wassertr(source->type==WPLDictionary && dest->type==WPLDictionary);

    e = WMEnumerateHashTable(source->d.dict);
    while (WMNextHashEnumeratorItemAndKey(&e, (void**)&value, (void**)&key)) {
        WMInsertPropListDictionaryEntry(dest, key, value);
    }

    return dest;
}


WMPropList*
WMRetainPropList(WMPropList *plist)
{
    WMPropList *key, *value;
    WMHashEnumerator e;
    int i;

    plist->retainCount++;

    switch(plist->type) {
    case WPLString:
    case WPLData:
        break;
    case WPLArray:
        for (i=0; i<WMGetArrayItemCount(plist->d.array); i++) {
            WMRetainPropList(WMGetFromArray(plist->d.array, i));
        }
        break;
    case WPLDictionary:
        e = WMEnumerateHashTable(plist->d.dict);
        while (WMNextHashEnumeratorItemAndKey(&e, (void**)&value, (void**)&key)) {
            WMRetainPropList(key);
            WMRetainPropList(value);
        }
        break;
    default:
        wwarning(_("Used proplist functions on non-WMPropLists objects"));
        wassertrv(False, NULL);
    }

    return plist;
}


void
WMReleasePropList(WMPropList *plist)
{
    WMPropList *key, *value;
    WMHashEnumerator e;
    int i;

    plist->retainCount--;

    switch(plist->type) {
    case WPLString:
        if (plist->retainCount < 1) {
            wfree(plist->d.string);
            wfree(plist);
        }
        break;
    case WPLData:
        if (plist->retainCount < 1) {
            WMReleaseData(plist->d.data);
            wfree(plist);
        }
        break;
    case WPLArray:
        for (i=0; i<WMGetArrayItemCount(plist->d.array); i++) {
            WMReleasePropList(WMGetFromArray(plist->d.array, i));
        }
        if (plist->retainCount < 1) {
            WMFreeArray(plist->d.array);
            wfree(plist);
        }
        break;
    case WPLDictionary:
        e = WMEnumerateHashTable(plist->d.dict);
        while (WMNextHashEnumeratorItemAndKey(&e, (void**)&value, (void**)&key)) {
            WMReleasePropList(key);
            WMReleasePropList(value);
        }
        if (plist->retainCount < 1) {
            WMFreeHashTable(plist->d.dict);
            wfree(plist);
        }
        break;
    default:
        wwarning(_("Used proplist functions on non-WMPropLists objects"));
        wassertr(False);
    }
}


Bool
WMPropListIsString(WMPropList *plist)
{
    return (plist->type == WPLString);
}


Bool
WMPropListIsData(WMPropList *plist)
{
    return (plist->type == WPLData);
}


Bool
WMPropListIsArray(WMPropList *plist)
{
    return (plist->type == WPLArray);
}


Bool
WMPropListIsDictionary(WMPropList *plist)
{
    return (plist->type == WPLDictionary);
}


Bool
WMPropListIsSimple(WMPropList *plist)
{
    return (plist->type==WPLString || plist->type==WPLData);
}


Bool
WMPropListIsCompound(WMPropList *plist)
{
    return (plist->type==WPLArray || plist->type==WPLDictionary);
}


Bool
WMIsPropListEqualToPropList(WMPropList *plist, WMPropList *other)
{
    WMPropList *key1, *item1, *item2;
    WMHashEnumerator enumerator;
    int n, i;

    if (plist->type != other->type)
        return False;

    switch(plist->type) {
    case WPLString:
        return (strCmp(plist->d.string, other->d.string) == 0);
    case WPLData:
        return WMIsDataEqualToData(plist->d.data, other->d.data);
    case WPLArray:
        n = WMGetArrayItemCount(plist->d.array);
        if (n != WMGetArrayItemCount(other->d.array))
            return False;
        for (i=0; i<n; i++) {
            item1 = WMGetFromArray(plist->d.array, i);
            item2 = WMGetFromArray(other->d.array, i);
            if (!WMIsPropListEqualToPropList(item1, item2))
                return False;
        }
        return True;
    case WPLDictionary:
        if (WMCountHashTable(plist->d.dict) != WMCountHashTable(other->d.dict))
            return False;
        enumerator = WMEnumerateHashTable(plist->d.dict);
        while (WMNextHashEnumeratorItemAndKey(&enumerator, (void**)&item1,
                                              (void**)&key1)) {
            item2 = WMHashGet(other->d.dict, key1);
            if (!item2 || !item1 || !WMIsPropListEqualToPropList(item1, item2))
                return False;
        }
        return True;
    default:
        wwarning(_("Used proplist functions on non-WMPropLists objects"));
        wassertrv(False, False);
    }

    return False;
}


int
WMGetPropListNumberOfElements(WMPropList *plist)
{
    switch(plist->type) {
    case WPLString:
    case WPLData:
        return 0; /* should this be 1 instead? */
    case WPLArray:
        return WMGetArrayItemCount(plist->d.array);
    case WPLDictionary:
        return (int)WMCountHashTable(plist->d.dict);
    default:
        wwarning(_("Used proplist functions on non-WMPropLists objects"));
        wassertrv(False, 0);
    }
}


char*
WMGetPropListString(WMPropList *plist)
{
    wassertrv(plist->type==WPLString, NULL);

    return plist->d.string;
}


WMData*
WMGetPropListData(WMPropList *plist)
{
    wassertrv(plist->type==WPLData, NULL);

    return plist->d.data;
}


const unsigned char*
WMGetPropListDataBytes(WMPropList *plist)
{
    wassertrv(plist->type==WPLData, NULL);

    return WMDataBytes(plist->d.data);
}


int
WMGetPropListDataLength(WMPropList *plist)
{
    wassertrv(plist->type==WPLData, 0);

    return WMGetDataLength(plist->d.data);
}


WMPropList*
WMGetPropListArrayElement(WMPropList *plist, int index)
{
    wassertrv(plist->type==WPLArray, NULL);

    return WMGetFromArray(plist->d.array, index);
}


WMPropList*
WMGetPropListDictionaryEntry(WMPropList *plist, WMPropList *key)
{
    wassertrv(plist->type==WPLDictionary, NULL);

    return WMHashGet(plist->d.dict, key);
}


WMPropList*
WMGetPropListAllDictionaryKeys(WMPropList *plist)
{
    WMPropList *array, *key;
    WMHashEnumerator enumerator;

    wassertrv(plist->type==WPLDictionary, NULL);

    array = (WMPropList*)wmalloc(sizeof(W_PropList));
    array->type = WPLArray;
    array->d.array = WMCreateArray(WMCountHashTable(plist->d.dict));
    array->retainCount = 1;

    enumerator = WMEnumerateHashTable(plist->d.dict);
    while ((key = WMNextHashEnumeratorKey(&enumerator))) {
        WMAddToArray(array->d.array, WMRetainPropList(key));
    }

    return array;
}


char*
WMGetPropListDescription(WMPropList *plist, Bool indented)
{
    return (indented ? indentedDescription(plist, 0) : description(plist));
}



/* TODO: review this function's code */

Bool
WMSavePropListToFile(WMPropList *plist, char *path, Bool atomically)
{
    char *thePath=NULL;
    char *description;
    FILE *theFile;

    if (atomically) {
#ifdef	HAVE_MKSTEMP
        int fd, mask;
#endif

        /* Use the path name of the destination file as a prefix for the
         * mkstemp() call so that we can be sure that both files are on
         * the same filesystem and the subsequent rename() will work. */
        thePath = wstrconcat(path, ".XXXXXX");

#ifdef  HAVE_MKSTEMP
        if ((fd = mkstemp(thePath)) < 0) {
            wsyserror(_("mkstemp (%s) failed"), thePath);
            goto failure;
        }
        mask = umask(0);
        umask(mask);
        fchmod(fd, 0644 & ~mask);
        if ((theFile = fdopen(fd, "w")) == NULL) {
            close(fd);
        }
#else
        if (mktemp(thePath) == NULL) {
            wsyserror(_("mktemp (%s) failed"), thePath);
            goto failure;
        }
        theFile = fopen(thePath, "wb");
#endif
    } else {
        thePath = wstrdup(path);
        theFile = fopen(thePath, "wb");
    }

    if (theFile == NULL) {
        wsyserror(_("open (%s) failed"), thePath);
        goto failure;
    }

    description = indentedDescription(plist, 0);

    if (fprintf(theFile, "%s\n", description) != strlen(description)+1) {
        wsyserror(_("writing to file: %s failed"), thePath);
        wfree(description);
        goto failure;
    }

    wfree(description);

    if (fclose(theFile) != 0) {
        wsyserror(_("fclose (%s) failed"), thePath);
        goto failure;
    }

    /* If we used a temporary file, we still need to rename() it be the
     * real file.  Also, we need to try to retain the file attributes of
     * the original file we are overwriting (if we are) */
    if (atomically) {
        if (rename(thePath, path) != 0) {
            wsyserror(_("rename ('%s' to '%s') failed"), thePath, path);
            goto failure;
        }
    }

    wfree(thePath);
    return True;

failure:
    if (atomically) {
        unlink(thePath);
        wfree(thePath);
    }

    return False;
}


WMPropList*
WMShallowCopyPropList(WMPropList *plist)
{
    WMPropList *ret, *key, *item;
    WMHashEnumerator e;
    int i;

    switch(plist->type) {
    case WPLString:
    case WPLData:
        return WMDeepCopyPropList(plist);
    case WPLArray:
        ret = (WMPropList*)wmalloc(sizeof(W_PropList));
        ret->type = WPLArray;
        ret->d.array = WMCreateArrayWithArray(plist->d.array);
        ret->retainCount = 1;

        for(i=0; i<WMGetArrayItemCount(ret->d.array); i++)
            WMRetainPropList(WMGetFromArray(ret->d.array, i));

        return ret;
    case WPLDictionary:
        ret = WMCreatePropListDictionaryFromEntries(NULL, NULL);
        e = WMEnumerateHashTable(plist->d.dict);
        while (WMNextHashEnumeratorItemAndKey(&e, (void**)&item, (void**)&key)) {
            WMInsertPropListDictionaryEntry(ret, key, item);
        }
        return ret;
    default:
        wwarning(_("Used proplist functions on non-WMPropLists objects"));
        wassertrv(False, NULL);
    }
}


WMPropList*
WMDeepCopyPropList(WMPropList *plist)
{
    WMPropList *ret, *key, *item;
    WMHashEnumerator e;
    WMData *data;
    int i;

    switch(plist->type) {
    case WPLString:
        return WMCreatePropListString(plist->d.string);
    case WPLData:
        data = WMCreateDataWithData(plist->d.data);
        ret = WMCreatePropListDataWithData(data);
        WMReleaseData(data);
        return ret;
    case WPLArray:
        ret = WMCreatePropListArrayFromElements(NULL);
        for(i=0; i<WMGetArrayItemCount(plist->d.array); i++) {
            item = WMDeepCopyPropList(WMGetFromArray(plist->d.array, i));
            WMAddToArray(ret->d.array, item);
        }
        return ret;
    case WPLDictionary:
        ret = WMCreatePropListDictionaryFromEntries(NULL, NULL);
        e = WMEnumerateHashTable(plist->d.dict);
        /* While we copy an existing dictionary there is no way that we can
         * have duplicate keys, so we don't need to first remove a key/value
         * pair before inserting the new key/value.
         */
        while (WMNextHashEnumeratorItemAndKey(&e, (void**)&item, (void**)&key)) {
            WMHashInsert(ret->d.dict, WMDeepCopyPropList(key),
                         WMDeepCopyPropList(item));
        }
        return ret;
    default:
        wwarning(_("Used proplist functions on non-WMPropLists objects"));
        wassertrv(False, NULL);
    }
}




