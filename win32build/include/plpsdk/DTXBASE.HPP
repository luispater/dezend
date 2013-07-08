//////
// DTXBASE.hpp - The header file for the basic information
//  (c)Copyright InnerX Comunications, Inc. 1997-1998
//////

#ifndef __DTXBASE__
#define __DTXBASE__

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <iostream.h>
/*
#ifdef WIN32
#define __DTXNT__
#endif

#ifdef __DTXOS2__
#define INCL_PM
#define INCL_WIN
#define INCL_GPI
#define INCL_DOS
#include <os2.h>
#ifdef HMODULE
#define HINSTANCE HMODULE
#else
#define HINSTANCE unsigned long
#endif
#endif

#ifdef __DTXWIN__
#ifndef _INC_WINDOWS
#include <windows.h>
#endif
#endif

#ifdef __DTXNT__
#ifndef _WINDOWS_
#include <windows.h>
#endif
#endif

*/

#ifdef __DTXUNIX__
#define HINSTANCE unsigned long
#endif

#include <dtxtypes.hpp>

#ifndef memicmp
#define memicmp strncmp
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifdef NONTOC
char *_ltoa (long,char *,int);
char *_gcvt (double foo,int,char *);
char *_fcvt (float foo, int len, int *shrug1, int *shrug2);
#define _itoa _ltoa
#define _ultoa _ltoa
#define BIG_BUFFER_SIZE 6144
#endif

//Used for generic link list node information.

class DTX_CLSEXPENTRY DTXLinkNode
{
public:
	DTXLinkNode();
	virtual ~DTXLinkNode();

	virtual  DTX_PVOID getObject();
	virtual  DTX_UINT  getObjectSize();

	virtual  DTX_VOID  setObject( DTX_PVOID pItem, DTX_UINT unLen = 0 );

	DTXLinkNode *m_pPrev;
	DTXLinkNode *m_pNext;

private:
	DTX_PVOID   pObj;
	DTX_UINT    unSize;
};



//This class contains the base information that most of the
// classes use for link lists and collections.

class DTX_CLSEXPENTRY DTXCollectable
{
public:
	virtual ~DTXCollectable();

	DTXLinkNode m_lnkNode;

protected:
	DTXCollectable();
};



//DTX IDs...
#define DTX_USERID          25000
#define DTXSTATUSBAR_ID     DTX_USERID+1
#define DTXTOOLBAR_ID       DTX_USERID+2
#define DTXSEPARATOR_ID     DTX_USERID+3
#define DTXSPLASH_ID        DTX_USERID+4
#define DTXSBRHORZ_ID       DTX_USERID+5
#define DTXSBRVERT_ID       DTX_USERID+6
#define DTXDEFTOOLBARBMP_ID 1 //Alter resource file if changed.


//DTX defined messages...

#define DXM_FRAMEBAR         WM_USER+1
#define DXM_ACTIVEWIN        WM_USER+2
#define DXM_BEGINDRAG        WM_USER+3
#define DXM_DRAGENTER        WM_USER+4
#define DXM_DRAGLEAVE        WM_USER+5
#define DXM_DRAGNOTIFY       WM_USER+6
#define DXM_DRAGOVER         WM_USER+7
#define DXM_DROP             WM_USER+8
#define DXM_ENDDRAG          WM_USER+9


//Min value for user defined events
#define DTX_USER             WM_USER+100
#define DTX_USER_MAX         WM_USER+600

#endif


