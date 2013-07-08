//////
// DTXTYPES.hpp - Contains the generic information for the data types
//  (c) Copyright InnerX Communications, Inc. 1997-1998
//////

#ifndef __DTXTYPES__
#define __DTXTYPES__

//#if defined(_WINDLL) || defined(_WINDOWS)
//#ifndef __DTXMVCWIN__
//#define __DTXMVCWIN__
//#endif
//#endif

#ifdef WIN32
#ifndef STRICT
#define STRICT
#endif
#ifndef __DTXMVCW32__
#define __DTXMVCW32__
#endif
#ifndef __DTXNT__
#define __DTXNT__
#endif
#ifndef __SQLMVCNT__
#define __SQLMVCNT__
#endif
#endif

#ifdef __IBMCPP__
#ifndef __DTXIBMOS2__
#define __DTXIBMOS2__
#endif
#ifndef __DTXOS2__
#define __DTXOS2__
#endif
#define INCL_PM
#define INCL_WIN
#define INCL_DOS
#endif

//// For downward compatibility.
#ifdef __SQLIBMOS2__
#define __DTXIBMOS2__
#endif
#ifdef __SQLBOROS2__
#define __DTXBOROS2__
#endif
#ifdef __SQLWATOS2__
#define __DTXWATOS2__
#endif
#ifdef __SQLUNIX__
#define __DTXUNIX__
#endif
#ifdef __SQLMVCWIN__
#define __DTXMVCWIN__
#endif
#ifdef __SQLBORWIN__
#define __DTXBORWIN__
#endif
#ifdef __SQLWATWIN__
#define __DTXWATWIN__
#endif
//// End downward.

#if defined(__DTXIBMOS2__) || defined(__DTXBOROS2__) || defined(__DTXWATOS2__)
#ifndef __DTXOS2__
#define __DTXOS2__
#endif 
#if (!defined(__OS2_H__))
#define INCL_WIN
#define INCL_DOSMODULEMGR
#include <os2.h>
#endif
#ifdef HMODULE
#define HINSTANCE HMODULE
#else
#define HINSTANCE unsigned long
#endif
#endif

#if defined(__DTXMVCWIN__) || defined(__DTXBORWIN__) || defined(__DTXWATWIN__)
#ifndef __DTXWIN__
#define __DTXWIN__
#endif 
#ifndef _INC_WINDOWS
#include <windows.h>
#endif
#endif

#ifdef __DTXNT__
//#define _WINSOCKAPI_ 
//Don't let windows.h call winsock.h
#ifndef _WINDOWS_
#include <windows.h>
#endif
#endif

#ifdef __DTXUNIX__
#define HINSTANCE unsigned long
#include <unistd.h> //-TBD- Some UNIX flavors may not like this.
#include <ctype.h>
#ifndef __DTXUNIX__
#define __DTXUNIX__
#endif
#endif

#define DTXMIN(a,b) ((a > b) ? b : a)
#define DTXMAX(a,b) ((a > b) ? a : b)
#define DTXABS(a) ((a>=0) ? a : a*-1)

// Defined for TCP/IP classes.
#define DTX_CLOSED       -45
#define DTX_NODATA       -46
#define DTX_TIMEDOUT     -47

#define DTX_HOSTNOTVALID -50
#define DTX_SENDNOTVALID -51
#define DTX_RCPTNOTVALID -52

// Defined for all classes.
#define DTX_SUCCESS  0
#define DTX_FAIL    -1

#ifdef __DTXWIN__
#define IOC_CHAR      char
#define IOC_PSZ       char _far *
#define IOC_PCHAR     char _far *
#define IOC_UPCHAR    unsigned IOC_PCHAR
#define IOC_CPSZ      const IOC_PSZ
#define IOC_CPCHAR    const IOC_PCHAR
//#define IOC_INT       int
#define IOC_INT		  long
#define IOC_UINT      unsigned IOC_INT
#define IOC_PINT      IOC_INT _far *
#define IOC_PUINT     IOC_UINT _far *
#define IOC_LINT      long
#define IOC_ULINT     IOC_UINT
#define IOC_PLINT     IOC_LINT _far *
#define IOC_SMALLINT  short
#define IOC_USMALLINT unsigned short
#define IOC_PSMALLINT IOC_SMALLINT _far *
#define IOC_VOIDTYP   void
#define IOC_PVOID     IOC_VOIDTYP _far *
#define IOC_BOOLEAN   long
#define IOC_HWND      HWND
#define IOC_MONEY     double
#define IOC_HOBJWND   HWND  //Remove later.  This if for SQLObjects v2.2

#define IOC_REAL      float
#define IOC_FLOAT     double
#define IOC_PREAL     IOC_REAL _far *
#define IOC_PFLOAT    IOC_FLOAT _far *

#define IOC_EXPENTRY  FAR PASCAL _export //For internal C functions.


//look at defines
#ifdef __BORLANDC__
#define IOC_CLSEXPENTRY2 _export
#ifdef __DLL__
#define IOC_CLSEXPENTRY  _export
#else
#define IOC_CLSEXPENTRY  _CLASSTYPE
#endif
#else
#ifdef _WINDLL
#define IOC_CLSEXPENTRY  __export
#else                    
#define IOC_CLSEXPENTRY  _far
#endif
#define IOC_CLSEXPENTRY2 IOC_CLSEXPENTRY
#endif

#define IOC_EVTPARAM
#define IOC_EVTMSG
#define IOC_DRWDEVICE    DC
#define IOC_DRWDC        DC
#define IOC_ANCBLOCK     IOC_UINT
#define IOC_MSGQUEHANDLE IOC_UINT
#define IOC_MSGQUE       IOC_UINT
#define IOC_DESKTOP_WND  GetDesktopWindow()
#define IOC_WNDPROC
#define IOC_RESULT
#define IOC_HANDLE       HANDLE
#define IOC_CLIENT_ID    0
#define IOC_HINI         IOC_HANDLE
#define IOC_FHANDLE      IOC_SMALLINT
#define IOC_HINSTANCE	 HINSTANCE

#define IOC_FAR       _far
#define IOC_PFAR      _far *
#define IOC_NEAR      NEAR
#define IOC_PNEAR     NEAR *

#define IOC_NPVOID    void _near *
#endif

#if defined(__DTXOS2__) || defined(__DTXUNIX__) || defined(__DTXNT__)

#define IOC_CHAR      char
#define IOC_PSZ       char *
#define IOC_PCHAR     char *
#define IOC_CPSZ      const char *
#define IOC_CPCHAR    const char *
#define IOC_UPCHAR    unsigned IOC_PCHAR
#define IOC_INT       int
#define IOC_UINT      unsigned IOC_INT
#define IOC_PINT      IOC_INT *
#define IOC_PUINT     IOC_UINT *
#define IOC_LINT      signed long
#define IOC_ULINT     unsigned long
#define IOC_PLINT     IOC_LINT *
#define IOC_SMALLINT  short
#define IOC_USMALLINT unsigned IOC_SMALLINT
#define IOC_PSMALLINT IOC_SMALLINT *

//#ifdef _MSC_VER
#ifdef __DTXNT__
#ifdef IOC_VOIDTYP
#undef IOC_VOIDTYP
#endif
#endif

#define IOC_VOIDTYP      void
#define IOC_PVOID     IOC_VOIDTYP *
#define IOC_BOOLEAN   int

#ifdef __DTXUNIX__
#define IOC_HANDLE       IOC_LINT
#define IOC_HINI         IOC_HANDLE
#define IOC_HWND         IOC_LINT
#define IOC_EVTPARAM     IOC_UINT
#define IOC_EVTMSG       IOC_UINT
#define IOC_DRWDEVICE    IOC_UINT //Change later
#define IOC_ANCBLOCK     IOC_UINT
#define IOC_MSGQUEHANDLE IOC_UINT
#define IOC_MSGQUE       IOC_UINT
#define IOC_DESKTOP_WND  IOC_UINT
#define IOC_DRWDC        IOC_DRWDEVICE
#define IOC_WNDPROC      IOC_UINT
#define IOC_RESULT       IOC_UINT
#define IOC_FHANDLE      IOC_UINT
#define IOC_CLIENT_ID    0
#define IOC_HINSTANCE	 IOC_UINT
#else
#define IOC_HWND      HWND
#define IOC_HINSTANCE HINSTANCE
#endif

#define IOC_MONEY     double
#define IOC_NPVOID    IOC_PVOID

//#ifdef _MSC_VER
#ifdef __DTXNT__
#ifdef _DLL
#define IOC_EXPENTRY     _declspec (dllexport) __stdcall
#else
#define IOC_EXPENTRY     __stdcall
#endif
//#define IOC_CLSEXPENTRY  IOC_EXPENTRY
#ifdef _DLL
#define IOC_CLSEXPENTRY  _declspec (dllexport)
#else
#define IOC_CLSEXPENTRY
#endif
#define IOC_CLSEXPENTRY2

#define IOC_EVTPARAM     LPARAM
#define IOC_EVTMSG       UINT
#define IOC_DRWDEVICE    DC
#define IOC_ANCBLOCK     IOC_UINT
#define IOC_MSGQUEHANDLE IOC_UINT
#define IOC_MSGQUE       IOC_UINT
#define IOC_DESKTOP_WND  GetDesktopWindow()
#define IOC_DRWDC        DC
#define IOC_WNDPROC      IOC_UINT
#define IOC_RESULT       IOC_UINT
#define IOC_HANDLE       HANDLE
#define IOC_HINI         IOC_HANDLE
#define IOC_FHANDLE      IOC_SMALLINT
#define IOC_CLIENT_ID    0

#define IOC_HOBJWND      HWND  //Remove later.  This if for SQLObjects v2.2
#endif

#ifdef __IBMCPP__
#define IOC_EXPENTRY  _System _Export
#define IOC_CLSEXPENTRY
#define IOC_CLSEXPENTRY2
#endif
#ifdef __BCPLUSPLUS__
#define IOC_EXPENTRY  __syscall __export
#define IOC_CLSEXPENTRY _export
#define IOC_CLSEXPENTRY2
#endif
#ifdef __DTXUNIX__
#define IOC_CLSEXPENTRY 
#define IOC_CLSEXPENTRY2
#endif

#ifdef __DTXOS2__
#define IOC_EVTPARAM     MPARAM
#define IOC_EVTMSG       UINT
#define IOC_DRWDEVICE    HPS
#define IOC_ANCBLOCK     HAB
#define IOC_MSGQUEHANDLE HMQ
#define IOC_MSGQUE       QMSG
#define IOC_DESKTOP_WND  HWND_DESKTOP
#define IOC_DRWDC        HDC
#define IOC_WNDPROC      PFNWP
#define IOC_RESULT       IOC_PVOID
#define IOC_HANDLE       LHANDLE
#define IOC_HINI         HINI
#define IOC_FHANDLE      HFILE
#define IOC_CLIENT_ID    FID_CLIENT

#define IOC_HOBJWND      HWND  //Remove later.  This if for SQLObjects v2.2
#endif

#define IOC_FAR
#define IOC_PFAR      *
#define IOC_NEAR
#define IOC_PNEAR     *

#define IOC_REAL      float
#define IOC_FLOAT     double
#define IOC_PREAL     IOC_REAL *
#define IOC_PFLOAT    IOC_FLOAT *

#endif

#define IOC_NUMBER    double
#define IOC_PNUMBER   IOC_NUMBER *

#define IOC_BYTE      IOC_CHAR
#define IOC_RETCODE   IOC_INT


//New defines.  These will be used in the future.  The above defines
// are for compatibility of older versions.

#define DTX_CHAR			IOC_CHAR
#define DTX_PSZ				IOC_PSZ       
#define DTX_PCHAR			IOC_PCHAR     
#define DTX_UPCHAR			IOC_UPCHAR    
#define DTX_CPSZ			IOC_CPSZ      
#define DTX_CPCHAR			IOC_CPCHAR    
#define DTX_INT				IOC_INT       
#define DTX_UINT			IOC_UINT      
#define DTX_PINT			IOC_PINT      
#define DTX_PUINT			IOC_PUINT     
#define DTX_LINT			IOC_LINT      
#define DTX_ULINT			IOC_ULINT     
#define DTX_PLINT			IOC_PLINT     
#define DTX_SMALLINT		IOC_SMALLINT  
#define DTX_USMALLINT		IOC_USMALLINT 
#define DTX_PSMALLINT		IOC_PSMALLINT 
#define DTX_VOID			IOC_VOIDTYP   
#define DTX_PVOID			IOC_PVOID     
#define DTX_BOOLEAN			IOC_BOOLEAN   
#define DTX_HWND			IOC_HWND      
#define DTX_MONEY			IOC_MONEY     
#define DTX_REAL			IOC_REAL      
#define DTX_FLOAT			IOC_FLOAT     
#define DTX_PREAL			IOC_PREAL     
#define DTX_PFLOAT			IOC_PFLOAT    
#define DTX_EXPENTRY		IOC_EXPENTRY  
#define DTX_CLSEXPENTRY2	IOC_CLSEXPENTRY2 
#define DTX_CLSEXPENTRY		IOC_CLSEXPENTRY  
#define DTX_EVTPARAM		IOC_EVTPARAM
#define DTX_EVTMSG			IOC_EVTMSG
#define DTX_DRWDEVICE		IOC_DRWDEVICE    
#define DTX_DRWDC			IOC_DRWDC        
#define DTX_ANCBLOCK		IOC_ANCBLOCK     
#define DTX_MSGQUEHANDLE	IOC_MSGQUEHANDLE 
#define DTX_MSGQUE			IOC_MSGQUE       
#define DTX_DESKTOP_WND		IOC_DESKTOP_WND  
#define DTX_WNDPROC			IOC_WNDPROC
#define DTX_RESULT			IOC_RESULT
#define DTX_HANDLE			IOC_HANDLE       
#define DTX_CLIENT_ID		IOC_CLIENT_ID    
#define DTX_HINI			IOC_HINI         
#define DTX_FHANDLE			IOC_FHANDLE      
#define DTX_HINSTANCE		IOC_HINSTANCE	 
#define DTX_FAR				IOC_FAR       
#define DTX_PFAR			IOC_PFAR      
#define DTX_NEAR			IOC_NEAR      
#define DTX_PNEAR			IOC_PNEAR     
#define DTX_NPVOID			IOC_NPVOID    
#define DTX_NUMBER			IOC_NUMBER    
#define DTX_PNUMBER			IOC_PNUMBER   
#define DTX_BYTE			IOC_BYTE      
#define DTX_RETCODE			IOC_RETCODE   
#define DTX_HOBJWND			IOC_HOBJWND


//DataX Database Interface Specific
//The extra byte in these defines are used for NULL terminators

#define SQLALLOCPAGESIZE      4096
#define SQLMAXUSERNAMELEN     31
#define SQLMAXCOLNAMELEN      256
#define SQLMAXTABLENAMELEN    31
#define SQLMAXPASSWORDNAMELEN 31
#define SQLMAXSERVERNAMELEN   31
#define SQLMAXAPPNAMELEN      31
#define SQLMAXVERSIONLEN      13
#define SQLMAXDBNAMELEN       81
#define SQLMAXSQLCODEMSGLEN   128
#define SQLMAXSQLSENDCMD      9
#define SQLMAXCACHEDIRECT     128
#define SQLMAXPARAMNAMELEN    31
#define SQLMAXVARCHARLEN      256
#define SQLMAXDATEFMTLEN      25
#define SQLMAXTIMEFMTLEN      13
#define SQLMAXDATETIMEFMTLEN  31
#define SQLMAXRAWCOLSIZE      255
#define SQLMAXNUMBEROFCURSORS 25
#define SQLMAXBUFFSIZE        3072
#define SQLMAXCOLS            255
#define SQLMAXTABLES          12

#define SQLMINDATESIZE        10
#define SQLMINTIMESIZE        8
#define SQLMINDATETIMESIZE    26

#define SQLMAXFORMATLEN       31
#define SQLMAXNULLVALUELEN    11
#define SQLMAXCOLSEP          6
#define SQLMAXCOLROWTERM      6
#define SQLMAXCOLNAMEPREFIX   6
#define SQLMAXCOLNAMESUFFIX   6
#define SQLMAXCOLVALUEPREFIX  6
#define SQLMAXCOLVALUESUFFIX  6

#define SQLMAXBLOBLEN         64000


//This set of defines are different for each OS and compiler.

#if defined (__DTXMVCWIN__) || defined(__DTXBORWIN__) || defined(__DTXWATWIN__)
#define IOC_SQL16BIT    _far
#define IOC_PSQL16BIT   _far *
#define IOC_NSQL16BIT   NEAR
#define IOC_PNSQL16BIT  NEAR *
#define IOC_SQL16INT    int
#define IOC_PSQL1632BIT _far *
#endif 

#if defined(__DTXIBMOS2__) || defined(__DTXBOROS2__) || defined(__DTXUNIX__) || defined(__DTXWATOS2__) || defined(__DTXMVCW32__)
#ifdef __DTXUNIX__
#define DTX_NULL 0
#ifdef DTX_HOBJWND
#undef DTX_HOBJWND
#endif
#define DTX_HOBJWND   DTX_INT
#endif

#define IOC_SQL16INT   short

#ifdef __DTXIBMOS2__
#define IOC_SQL16BIT   _Seg16
#define IOC_PSQL16BIT  * _Seg16
#define IOC_NSQL16BIT  IOC_SQL16BIT
#define IOC_PNSQL16BIT IOC_PSQL16BIT

typedef void ( _Optlink *DTX_THREAD_ENTRY_POINT ) ( void * );
#define DTX_THREAD_CALL         _Optlink

#endif

#ifdef __DTXBOROS2__
#define IOC_SQL16BIT   __far16
#define IOC_PSQL16BIT  __far16 *
#define IOC_NSQL16BIT  IOC_SQL16BIT
#define IOC_PNSQL16BIT IOC_PSQL16BIT

#define DTX_THREAD_ENTRY_POINT  DTX_PVOID
#define DTX_THREAD_CALL        
#endif


#if defined(__DTXOS2__) || defined(__DTXUNIX__)
#define DTXSPRINTF		sprintf
#define DTXSTRCAT		strcat
#define DTXSTRCPY		strcpy
#define DTXSTRLEN		strlen
#define DTXSTRNCPY		strncpy
#ifdef __DTXUNIX__
#define DTXSTRICMP		strcasecmp
#else
#define DTXSTRICMP		stricmp
#endif
#define DTXMEMMOVE		memmove
#define DTXMEMSET		memset
#endif

#if defined(__DTXNT__)
#define DTXSPRINTF		wsprintf
#define DTXSTRCAT		lstrcat
#define DTXSTRCPY		lstrcpy
#define DTXSTRICMP      lstrcmpi
#define DTXSTRLEN		lstrlen
#define DTXSTRNCPY		lstrcpyn

#define DTXMEMMOVE      memmove
#define DTXMEMSET       memset	

#endif

#ifdef __DTXMVCW32__
#define IOC_SQL16BIT   
#define IOC_PSQL16BIT  * 
#define IOC_NSQL16BIT  IOC_SQL16BIT
#define IOC_PNSQL16BIT IOC_PSQL16BIT

//typedef void ( _cdecl *DTX_THREAD_ENTRY_POINT ) ( void * );
//#define DTX_THREAD_CALL         _cdecl

typedef unsigned int ( __stdcall *DTX_THREAD_ENTRY_POINT ) ( void * );
#define DTX_THREAD_CALL         __stdcall
#endif

#ifdef __DTXUNIX__
#define IOC_SQL16BIT
#define IOC_PSQL16BIT  *
#define IOC_NSQL16BIT  IOC_SQL16BIT
#define IOC_PNSQL16BIT IOC_PSQL16BIT

#define DTX_THREAD_ENTRY_POINT  DTX_PVOID
#define DTX_THREAD_CALL         

#ifndef __NOSTRICT__
#define stricmp strcasecmp
void strupr(char *);
void strlwr(char *);
#endif
#endif

#define IOC_PSQL1632BIT *

#endif /* __DTXIBMOS2__ || __DTXBOROS2__ || __DTXUNIX__ */

//-TBD-
//// For downward comp.
#define DTX_SQL16BIT    IOC_SQL16BIT
#define DTX_PSQL16BIT   IOC_PSQL16BIT
#define DTX_NSQL16BIT   IOC_NSQL16BIT
#define DTX_PNSQL16BIT  IOC_PNSQL16BIT
#define DTX_SQL16INT    IOC_SQL16INT
#define DTX_PSQL1632BIT IOC_PSQL1632BIT

//defines are DTX_SUCCESS and DTX_FAIL
#define SQLSUCCESS            0     
#define SQLFAIL               -1    
//// End downward


// Bind function defines
// The default bind type is bindZSTRING for character types

#define bindNONE          0
#define bindSTRING        1
#define bindZSTRING       2
#define bindBLOB          4
#define bindTINYINT       8
#define bindSMALLINT      16
#define bindINT           32
#define bindREAL          64
#define bindFLOAT         128
#define bindDATE          256
#define bindTIME          512
#define bindDATETIMESTAMP 1024
#define bindSTRINGCLASS   2048


/* Bind options */

#define bindoptDEFAULT      0
#define bindoptCOLSEP       1
#define bindoptALPHADEL     2
#define bindoptNULLALPHADEL 4
#define bindoptNUMDEL       8
#define bindoptNULLNUMDEL   16
#define bindoptLINETERM     32
#define bindoptDELAYPAINT   64

/* Handle options */

#define handleoptDEFAULT    0
#define handleoptDELAYPAINT 1
#define handleoptSHOWPAINT  2


/* SQL Command Types */

#define SQLCMDTYPE_NONE    0
#define SQLCMDTYPE_SELECT  1
#define SQLCMDTYPE_UPDATE  2
#define SQLCMDTYPE_DELETE  4
#define SQLCMDTYPE_INSERT  8
#define SQLCMDTYPE_OTHER   16

/* SQL Errors - Any value < 0, except 100 */

#define SQLNOMOREROWS				100     /* Command has no rows or has completed processing all rows */
#define SQLNOTSUPPORTED				-99999  /* A feature is not supported in the DBMS */
#define SQLCLASSDOESNOTEXIST		-10000  /* Class has not been created */
#define SQLCOLOUTOFRANGE			-10001  /* Column number was out of range */
#define SQLPOINTERNOTVALID			-10002  /* Pointer is not valid */
#define SQLCREATEFAILED				-10003  /* Unable to allocate new */
#define SQLCOLSNOTDESCRIBED			-10004  /* The sqlDescribe function has not been processed */
#define SQLVARINVALID				-10005  /* The bind or parameter variable was not valid */
#define SQLDISCONNECTFAILED			-10006  /* The sqlDisconnect call failed. This is usually caused when a child object issues this command */
#define SQLCOLERROR					-10007  /* An error in a call to one of the column calls */
#define SQLBINDVARMISSING			-10008  /* A bind variable was missing for a certain column */
#define SQLCONVERTFAILED			-10009  /* The data convert function failed */
#define SQLTABLENOTVALID			-10010  /* Table name was not a valid table name */
#define SQLCOLNOTVALID				-10011  /* Column name was not valid */
#define SQLINCORRECTBINDTYPE		-10012  /* Incorrect bind variable type */
#define SQLDATETIMESTRINGONLY		-10013  /* Date & time bindings can only be with string values. No numerics */
#define SQLRETSTATNONE				-10014  /* No return status from sqlReturnStatus */
#define SQLFMTLENGTHNOTVALID		-10015  /* The format length is not valid */
#define SQLCONNECTFAILED			-10016  /* The database connection failed */
#define SQLLOGINCANCELED			-10017  /* The user canceled the login */
#define SQLEXECFAILED				-10018  /* The sqlExec function or related functions failed */
#define SQLDESCRIBEFAILED			-10019  /* The sqlDescribe function failed */
#define SQLRECORDCHECKFAILED		-10020  /* The record results returned an error in the sqlExec function */
#define SQLDBCONNECTIONNOTVALID		-10021  /* The application is not connected to the database */
#define SQLNOCOLSTODESCRIBE			-10022  /* There were no columns to describe */
#define SQLDBMSVENDORDATANOTVALID	-10023  /* The vendor specific data requested was not valid */
#define SQLDBTIMEOUTNOTSET			-10024  /* Database timeout failed */
#define SQLLOGINTIMEOUTNOTSET		-10025  /* Login timeout failed */
#define SQLPARAMISNULL				-10026  /* The parameter passed is NULL or is zero length */
#define SQLFETCHFAILED				-10027  /* The sqlFetch call failed */
#define SQLBINDSIZENOTVALID			-10028  /* The bind size was not large enough to hold the DBMS data type */
#define SQLSQLDANOTALLOCATED		-10029  /* The sqlda structure is not allocated */
#define SQLBEGINWORKFAILED			-10030  /* The begin work transaction failed */
#define SQLCOMMITWORKFAILED			-10031  /* The commit work transaction failed */
#define SQLROLLBACKWORKFAILED		-10032  /* The rollback work transaction failed */
#define SQLSAVEPOINTFAILED			-10033  /* The savepoint transaction failed */
#define SQLCURSORNOTVALID			-10034  /* The cursor was not valid */
#define SQLPOSITIONEDDELETEFAILED	-10035  /* The positioned cursor delete failed */
#define SQLPOSITIONEDUPDATEFAILED	-10036  /* The positioned cursor update failed */
#define SQLTABLEOUTOFRANGE			-10037  /* The table number was out of range */
#define SQLDBCHANGEFAILED			-10038  /* The database change request failed */
#define SQLLOGINFAILED				-10039  /* Login failed */
#define SQLNOLOADDRIVER				-10200
#define SQLNOLOADDRIVERFUNCTION		-10201
#define SQLNOLOADLANGUAGE			-10202  /* The langauage driver could not be loaded. */
#define SQLHANDLEINVALID			-10050  /* The bind handle was invalid */
#define SQLHANDLENOTSUPPORTED		-10051  /* The bind handle is not supported */
#define SQLDEMOLIMITEXCEEDED		-10400  /* The demo limit exceeded */
#define SQLSYNTAXERROR				-10500  /* General SQL syntax error */


/* Informational messages - Any value > 0, except 100 */

#define SQLMOREFETCHRESULTS    10000  /* A new result set was encountered.  Call sqlDescribe before issuing the sqlFetch call again */
#define SQLFETCH               10001  /* This is set when the SQL command generated FETCH results */
#define SQLNOFETCH             10002  /* This is set when the SQL command does not generate any FETCH results */
#define SQLNOTABLESFOUND       10003  /* No tables were found in the statement */
#define SQLASYNCHWAIT          10004  /* The asynchronous process has been executed */

/* Column Attributes */

#define SQLCOLATTR_NULLABLE    1   /* Default is 0 - NOTNULLABLE */

enum SQLDATATYPES { sqlDATATYPENONE , sqlBIT , sqlSTRING, sqlCHAR , sqlVARCHAR , sqlLONGVARCHAR, sqlBLOB , sqlTINYINT , sqlSMALLINT , sqlINT , sqlREAL , sqlFLOAT , sqlMONEY , sqlDATE , sqlTIME , sqlDATETIMESTAMP , sqlRAW , sqlHOBJWND, sqlNUMERIC, sqlDECIMAL } ;
enum DBMS { sqlDBMSNONE , sqlBTR , sqlSYBASE , sqlSQLSERVER, sqlDB2 , sqlORACLE , sqlBASE, sqlWATCOM, sqlODBC, sqlINFORMIX } ;

#endif

