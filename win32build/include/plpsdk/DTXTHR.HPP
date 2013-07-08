//////
// DTXTHR.hpp - Header file for the DTXThread extension class
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

#ifndef __DTXTHR__
#define __DTXTHR__

#include <dtxbase.hpp>

#ifdef __DTXUNIX__
#include <pthread.h>
#endif

//May need to move to the DTXBASE.hpp header...

#ifdef __DTXNT__
struct DTXCRITICAL
{
	CRITICAL_SECTION stCritical;
	DTX_BOOLEAN      fInit;
};
typedef	DTXCRITICAL      DTX_CRITICAL;
typedef DTX_CRITICAL    *DTX_PCRITICAL;
typedef HANDLE           DTX_HSYNC;
typedef HANDLE           DTX_HTHREAD;
typedef DTX_UINT         DTX_THREADID;
typedef HANDLE           DTX_HPROCESS;

#define DTX_HTHREAD_DEF  NULL
#define DTX_SEM_SHARED   0 
#define DTX_SEM_WAIT     INFINITE
#endif

#ifdef __DTXUNIX__
typedef DTX_CHAR	DTX_CRITICAL;
typedef DTX_PCHAR	*DTX_PCRITICAL;
typedef pthread_mutex_t	DTX_HSYNC;
typedef pthread_t 	DTX_HTHREAD; 
typedef pthread_t       DTX_THREADID;
typedef unsigned long	DTX_HPROCESS;

#define DTX_HTHREAD_DEF 0	
#define DTX_SEM_SHARED	0
#define DTX_SEM_WAIT    0 //-TBD- Force this value	
#endif

#ifdef __DTXOS2__
typedef DTX_CHAR         DTX_CRITICAL;
typedef DTX_PCHAR       *DTX_PCRITICAL;
typedef ULONG           *DTX_HSYNC;
typedef ULONG            DTX_HTHREAD; 
typedef DTX_UINT         DTX_THREADID;
typedef ULONG            DTX_HPROCESS;

#define DTX_HTHREAD_DEF  -1
#define DTX_SEM_SHARED   DC_SEM_SHARED
#define DTX_SEM_WAIT     SEM_INDEFINITE_WAIT
typedef void ( _Optlink *OptlinkFnPtr ) ( void * );
typedef void ( _System  *SystemFnPtr  ) ( unsigned long );
#endif

#define SYNDEFAULTNAMELEN   129
#ifdef __DTXOS2__
#define THRDEFAULTSTACKSIZE 16392
#else
#define THRDEFAULTSTACKSIZE 0 //Assumes the default stack of the process
#endif


enum SYNCHRONIZATION { synNONE, synMUTEX, synEVENT };


class DTX_CLSEXPENTRY DTXSynchronization
{
public:
	DTXSynchronization( DTX_CPSZ pszName = "", DTX_SMALLINT ssynType = synEVENT );
	virtual ~DTXSynchronization();

	virtual DTX_RETCODE  synBlockingReset();
	virtual DTX_RETCODE  synBlockingStart( DTX_UINT nTime = DTX_SEM_WAIT );
	virtual DTX_RETCODE  synBlockingStop();
	virtual DTX_RETCODE  synClose();
	virtual DTX_RETCODE  synCreate( DTX_CPSZ pszName = NULL, DTX_SMALLINT ssynType = synEVENT );
	virtual DTX_RETCODE  synOpen( DTX_CPSZ pszName = NULL, DTX_SMALLINT sSynType = synEVENT );

	inline  DTX_UINT     getSynAttr();
	inline  DTX_HSYNC    getSynHandle();
	inline  DTX_PSZ      getSynName();
	inline  DTX_BOOLEAN  getSynState();
	inline  DTX_SMALLINT getSynType();

	inline  DTX_VOID     setSynAttr( DTX_UINT unAttr );
	inline  DTX_VOID     setSynHandle( DTX_HSYNC hSHync );
	inline  DTX_VOID     setSynName( DTX_CPSZ pszName );
	inline  DTX_VOID     setSynState( DTX_BOOLEAN fState );
	inline  DTX_VOID     setSynType( DTX_SMALLINT sSynType = synEVENT );

private:
	DTX_CHAR     szName[SYNDEFAULTNAMELEN];
	DTX_HSYNC    hSync;
	DTX_SMALLINT sType;
	DTX_UINT     unSynAttr;
	DTX_BOOLEAN  fSyncState;
	DTX_BOOLEAN  fSyncClosed;
};



//DTXProcess class

class DTX_CLSEXPENTRY DTXProcess 
{
public:
	DTXProcess();
	virtual ~DTXProcess();

	virtual DTX_RETCODE  proTerm( DTX_HPROCESS hPHandle );

	inline  DTX_HPROCESS getPHandle();
	inline  DTX_UINT     getPID();

	inline  DTX_VOID     setPHandle( DTX_HPROCESS hPHandle );
	inline  DTX_VOID     setPID( DTX_UINT unID );

private:
	DTX_HPROCESS	hProcess;
	DTX_UINT		unId;
};

//Inherit from this class if you want one of your methods to run in a
// seperate thread.  Just simply override the mthRun() method.

class DTXThread;
class DTXCurrentThread;

class DTX_CLSEXPENTRY DTXThreadFn 
{
public:
	DTXThreadFn();
	virtual ~DTXThreadFn();

	virtual DTX_VOID    mthRun(); // Over ride this method.

	//Use these two only if you pass in a pointer to this class and want the thread to terminate it.
	inline  DTX_BOOLEAN getClassDelete();
	inline  DTX_VOID    setClassDelete( DTX_BOOLEAN fFlag = FALSE );

	DTXThread           *m_pContainerThread; //Calling thread
	DTXCurrentThread    *m_pThread;          //Current thread

	//This is public ONLY to the library.  DO NOT call this method.
	DTX_VOID thrSysInit();
	DTX_VOID thrSysTerm();

private:
	DTX_BOOLEAN fDeleteClass;
	//DTX_BOOLEAN fDelete;
};

struct tagARGLIST
{
	DTXThreadFn *pClass;
};

typedef struct tagARGLIST ARGLIST;
typedef struct tagARGLIST *PARGLIST;


//All Synchronization objects must be destroyed out side of this object.
//By default the DTXCurrentThread class can do MUTEX type blocking without allocating 
// a synchronization object.  This is handle by the thrCriticalStart and stop
// methods.  The limitation is that this feature can only be used in the current
// process.

class DTX_CLSEXPENTRY DTXCurrentThread : public DTXCollectable
{
public:
	DTXCurrentThread();
	virtual ~DTXCurrentThread();

#ifdef __DTXNT__
	enum THREAD_PRIORITY { thrPRIIDLE = THREAD_PRIORITY_IDLE, thrPRILOW = THREAD_PRIORITY_LOWEST, thrPRIBELOWNORMAL = THREAD_PRIORITY_BELOW_NORMAL, thrPRINORMAL = THREAD_PRIORITY_NORMAL, thrPRIABOVENORMAL = THREAD_PRIORITY_ABOVE_NORMAL, thrPRIHIGH = THREAD_PRIORITY_HIGHEST, thrPRITIMECRITICAL = THREAD_PRIORITY_TIME_CRITICAL };
#endif
#if defined (__DTXOS2__) || defined (__DTXUNIX__)
	enum THREAD_PRIORITY { thrPRIIDLE = 0, thrPRILOW = 1, thrPRIBELOWNORMAL = 2, thrPRINORMAL = 3, thrPRIABOVENORMAL = 4, thrPRIHIGH = 5, thrPRITIMECRITICAL = 6 };
#endif

	//These two are ONLY called once in the main thread if they need to be used.
	virtual DTX_VOID        thrCriticalInit( DTX_PCRITICAL pGlobal );//MUST be called from within thread 1 (main) and declared global.
	virtual DTX_VOID        thrCriticalDelete();

	virtual DTX_VOID        thrCriticalStart();
	virtual DTX_VOID        thrCriticalStop();
	virtual DTX_RETCODE  	thrResume( DTX_HTHREAD hTHandle );
	virtual DTX_RETCODE  	thrTerm( DTX_HTHREAD hTHandle = DTX_HTHREAD_DEF );
	virtual DTX_VOID        thrSleep( DTX_UINT unTime ); //M. seconds
	virtual DTX_RETCODE  	thrSuspend( DTX_HTHREAD hTHandle );

	virtual DTX_INT         getPriority();
	inline  DTX_UINT 	    getStackSize();
	//UNIX - The getTID and getTHandle are the same.
	inline  DTX_THREADID    getTID(); //Note: the Thread ID and handle may be the same if your threads execute very fast.  The OS reuses IDs and Handles.  This is normal and the IDs and Handles are unique.
	inline  DTX_HTHREAD     getTHandle();//Use this method to pass to the thr methods

	virtual DTX_BOOLEAN     setPriority( DTX_INT nLevel = DTXCurrentThread::thrPRINORMAL, DTX_SMALLINT sDeltaChange = 0 );
	inline  DTX_VOID 	    setStackSize( DTX_UINT nSize );
	inline  DTX_VOID        setTID( DTX_THREADID nTID );
	inline  DTX_VOID        setTHandle( DTX_HTHREAD hTHandle );
	inline  DTX_VOID 	    setSynchronization( DTXSynchronization *pSynobject = NULL );//These will set all other threads that are created from this class.
	inline  DTX_VOID 	    setSynchronization( DTXSynchronization& Synobject );

	inline  DTXSynchronization  *synObject();

	DTXProcess              m_curProcess; //Current process
	DTXSynchronization     *m_pSync;

	//DO NOT USE THESE DATA MEMBER!
	DTX_PCRITICAL          pIntCrit;
	DTX_HTHREAD            hThread;

private:
	DTX_THREADID           nId;
	DTX_UINT               nStack;
};


//This type of thread is known as a container thread.  It contains information
//	about the 'real' thread it executed, not the thread it resides in (DTXCurrentThread)
//	is used for that.

class DTX_CLSEXPENTRY DTXThread : public DTXCurrentThread
{
public:
	DTXThread();
	DTXThread( DTXThread *pthrCopy );
	virtual ~DTXThread();

	virtual DTX_RETCODE  	thrExec( DTXThreadFn *pMethod );
	virtual DTX_RETCODE     thrExec( DTXThreadFn& thrMethod );
	virtual DTX_RETCODE  	thrTerm( DTX_HTHREAD hTHandle = DTX_HTHREAD_DEF );
	virtual DTX_RETCODE  	thrWait();

	virtual DTX_BOOLEAN     getIsAlive();

	//Do not access these data members
//	DTX_HSYNC               hSync;
//	DTX_HSYNC               hTermSync;
	PARGLIST                pArgList;

protected:
	DTX_RETCODE  	        thrExec( DTX_THREAD_ENTRY_POINT pMethod, DTX_PVOID pArgList = NULL);
};



#include <dtxthr.inl>

#endif

