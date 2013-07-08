//////
// DTXNETS.hpp - Header file for the DTXNetConnection, DTXNetServer classes
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

#ifndef __DTXNETS__
#define __DTXNETS__

#include <dtxnet.hpp>
#include <dtxthr.hpp>
#include <dtxlnk.hpp>

//Handles all the client connections for a server.

/*
class DTX_CLSEXPENTRY DTXNetConnectInfo 
{
public:
	DTX_CHAR	pClientSocket[DTXNETSOCKETADDLEN];
	DTX_INT		nClientSocket;
	DTX_BOOLEAN fConnectValid;
};

class DTX_CLSEXPENTRY DTXNetConnection
{
public:
	DTXNetConnection( DTX_INT nServer, DTX_INT nNumOfConnections = 1 );
	virtual ~DTXNetConnection();

	virtual DTX_INT     netConnect();
	virtual DTX_RETCODE netConnect( DTX_INT nClientNo );
	virtual DTX_RETCODE netDisconnect( DTX_INT nClientNo );
	virtual DTX_RETCODE netDisconnect( DTXNetObject& objClient );
	virtual DTX_RETCODE netDisconnectAll();

	virtual DTX_INT     getClientSocket( DTX_INT nClientHandle );
	inline  DTX_INT     getNumOfValidConnects();
	inline  DTX_INT     getNumOfConnections();

	virtual DTX_VOID	setNumOfConnections( DTX_INT nNumOf );

private:
	DTXNetConnectInfo *pConnectInfo;
	DTX_INT   nServerSocket;
	DTX_INT   nConnections;
	DTX_INT   nValidConnects;
};

*/


class DTXNetServerConnect;
class DTXNetServer;

class DTX_CLSEXPENTRY DTXNetClientObject : public DTXThreadFn, public DTXCollectable
{
public:
	DTXNetClientObject( DTXNetServer *pObject = NULL );
	virtual ~DTXNetClientObject();

		    DTX_VOID mthExit(); //MUST be called at end of mthRun method!
	virtual DTX_VOID mthRun();

	DTXNetServer        *m_pServer;
	DTXNetObject        *m_pClient;
	DTXNetServerConnect *m_pCon;
	DTXSynchronization  *m_pSynRemove;
};




class DTX_CLSEXPENTRY DTXNetServerConnect : public DTXThreadFn 
{
public:
	DTXNetServerConnect();
	virtual ~DTXNetServerConnect();

	virtual DTX_RETCODE mthExec( DTXNetClientObject *pObject );
	virtual DTX_VOID    mthRun();

	virtual DTX_UINT    getActiveThreads();
	        DTXThread  *getObject( DTXThread *pThrObject, DTX_UINT unIndex );

		    DTX_VOID    setRemoveObject( DTXNetClientObject *pObject );

	DTXNetServer       *m_pServer;

	//DO NOT USE BELOW HERE!
	DTXSynchronization *m_pSynCon;
	DTXSynchronization *m_pSynInc;

protected:
	DTX_VOID            setClean();
	DTXSynchronization  SynRemove;

private:
	DTXLinkList         List;
	DTXLinkList         DelList;
};





class DTX_CLSEXPENTRY DTXNetServer : public DTXNetObject, public DTXCurrentThread
{
public:
	DTXNetServer();
	virtual ~DTXNetServer();

	virtual DTX_RETCODE netConnect();
	virtual DTX_RETCODE netConnect( DTX_USMALLINT sValue );
			DTX_VOID    netKill();
	virtual DTX_VOID    netRun( DTX_PSZ pszService = NULL );

	inline  DTX_UINT	         getActiveConnects();
	inline  DTX_BOOLEAN          getAutoPort();
	inline  DTX_INT              getClientMax();
	inline  DTX_SMALLINT         getConnectThreadPool();
	virtual DTXNetClientObject * getInstalledObject(); //MUST override this in inherited class!
	virtual DTX_BOOLEAN          getIsClientWantingConnection( DTX_BOOLEAN fPoll = TRUE );
	inline  DTX_BOOLEAN          getServiceOption();
	virtual DTXSynchronization * getSynObject( DTX_SMALLINT sIndex );

	inline  DTX_VOID	         setAutoPort( DTX_BOOLEAN fPort );
	inline  DTX_VOID	         setClientMax( DTX_INT nNumOf = 0 );//0 - Unlimited
	virtual DTX_VOID             setConnectThreadPool( DTX_SMALLINT sThreads = 1 ); //Set only once at the beginning of the code.
	virtual DTX_VOID             setControlCHandler( DTX_BOOLEAN fFlag = FALSE);
	virtual DTX_VOID             setServiceOption( DTX_BOOLEAN fFlag = FALSE, DTX_SMALLINT sArgcs = 0, DTX_PSZ *pszArgv = NULL );
	inline  DTX_VOID             setSynObjects( DTX_SMALLINT sNumOf = 0 );
	virtual DTX_VOID             setSynType( DTX_SMALLINT sIndex, DTX_SMALLINT sType = synEVENT );

	//DO NOT USE THESE METHODS!
			DTX_VOID     netDie();
			//DTX_VOID     netRunService();
			DTX_VOID     setDecCon();
			DTX_VOID     setIncCon();
	DTXSynchronization  *m_pSynPool;
	DTXNetServerConnect *pSrvCon;
	DTXThread           *pSrvConThr;
	DTXSynchronization  Alive;
	DTXSynchronization  Connections;

private:
	DTXSynchronization  Inc;
	DTX_BOOLEAN			fAutoPort;
	DTX_BOOLEAN         fService;
	DTX_INT             nMaxClients;
	DTX_UINT            unActCon;
	DTX_SMALLINT		sCon;
	DTX_SMALLINT        sSynObjects;
	DTX_SMALLINT        sArgc;
	DTX_PSZ             *pArgv;
};

#include <dtxnets.inl>

#endif

