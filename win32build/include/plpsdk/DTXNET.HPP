//////
// DTXNET.hpp - Header file for the DTXNetObject class
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

#ifndef __DTXNET__
#define __DTXNET__

#include <dtxbase.hpp>
#include <dtxstr.hpp>

//Socket type information.

#if defined(__DTXNT__) || defined(__DTXWIN__)
#include <stdlib.h>
#ifdef __DTXNT__
//#include <winsock2.h>
#include <winsock.h>
#else
#include <winsock.h>
#endif
#endif

#ifdef __DTXOS2__
#include <stdlib.h>
#include <types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#endif

#ifdef __DTXUNIX__
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#ifdef _AIX
#include <ioctl.h>
#else
#include <ioctls.h>
#endif
#include <fcntl.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#endif


typedef struct sockaddr_in   SOCKETADD_IN;
typedef struct sockaddr_in * PSOCKETADD_IN;

typedef struct sockaddr  SOCKETADD;
typedef struct sockaddr *PSOCKETADD;

typedef struct hostent   HOSTENT;
typedef struct hostent * PHOSTENT;

typedef struct servent   SERVENT;
typedef struct servent * PSERVENT;

typedef struct protoent  PROTOENT;
typedef struct protoent *PPROTOENT;

typedef struct in_addr   IN_ADDR;
typedef struct in_addr * PIN_ADDR;


//Socket states
#define DTX_STATECONNECT	0
#define DTX_STATERAW		1


#define DTXNETOBJ_CLIENT    0
#define DTXNETOBJ_SERVER    1
#define DTXNETOBJ_NETORDER  0
#define DTXNETOBJ_HOSTORDER 1
#define DTXNETSOCKETADDLEN  16

#define NETERROR_VENDOR_ID		"[DTX]"
#define NETERROR_XXXX_PRE_ID	"[InnerX]"


//Well known ports
#define DTXNETPORT_NONE			0
#define DTXNETPORT_ECHO			7
#define DTXNETPORT_DISCARD		9
#define DTXNETPORT_SYSTAT		11
#define DTXNETPORT_DAYTIME		13
#define DTXNETPORT_NETSTAT		15
#define DTXNETPORT_FTP			21
#define DTXNETPORT_TELNET		23
#define DTXNETPORT_SMTP			25
#define DTXNETPORT_TIMESERVER	37
#define DTXNETPORT_NAMESERVER	42
#define DTXNETPORT_WHOIS		43
#define DTXNETPORT_MTP			57
#define DTXNETPORT_TFTP			69
#define DTXNETPORT_RJE			77
#define DTXNETPORT_FINGER		79
#define DTXNETPORT_TTYLINK		87
#define DTXNETPORT_SUPDUP		95
#define DTXNETPORT_POP3			110


//Well known protocols
#define DTXNETPROTO_IP			"ip"	//Internet protocol
#define DTXNETPROTO_ICMP		"icmp"	//Internet control message protocol
#define DTXNETPROTO_GGP			"ggp"	//gateway-gateway protocol
#define DTXNETPROTO_TCP			"tcp"	//transmission control protocol
#define DTXNETPROTO_EGP			"egp"	//exterior gateway protocol
#define DTXNETPROTO_UDP			"udp"	//user datagram protocol
#define DTXNETPROTO_HMP			"hmp"	//host monitoring protocol

#define DTXNETCMDKILL			-100 //Send this and the server app. should die.

//All numbers below 1000 are reserved for internal use

//This section defines the warnings and errors
#define DTX_NETMSG_FAIL			0000

#define DTX_NETMSG_SUCCESS      0001

#define DTX_NETMSG_MAXCLIENTS	0999







//Start of user defined messages. 

#define DTX_NETCMD_USER			1000





class DTXNetObject;

class DTX_CLSEXPENTRY DTXNetParameters : public DTXCollectable
{
public:
	DTXNetParameters();
	virtual ~DTXNetParameters();

	DTXString m_strBuffer;
};

class DTX_CLSEXPENTRY DTXNetParam 
{
public:
	DTXNetParam();
	virtual ~DTXNetParam();

	inline  DTX_SMALLINT getNumOfParam();
	inline  DTX_SMALLINT getParameters();
	inline  DTX_LINT	 getPopParam( DTX_PVOID pData, DTX_LINT lLength );
	inline  DTX_LINT     getPopParamLength();

	inline  DTX_VOID     setParameters( DTX_SMALLINT sNumOf = 6 );
	inline  DTX_VOID     setParamList();
	inline  DTX_VOID     setPushParam( DTX_PVOID pData, DTX_LINT lLength );
	inline  DTX_VOID     setResetIter();

	DTXString         m_strCode;	

	//These are public but should not be used!
	DTXNetParameters *m_pParams;
	DTX_LINT          m_lLength;
	DTX_LINT          m_lLength2;
	DTX_LINT          m_lLength3;
	DTX_LINT          m_lOffset;
	DTX_BOOLEAN       m_fCmd;
	DTX_SMALLINT      m_sTotal;
	DTX_SMALLINT      m_sLen;

private:
	DTX_SMALLINT sParams;
	DTX_SMALLINT sCurr;
	DTX_SMALLINT sNParams;
};


class DTX_CLSEXPENTRY DTXNetErrorEvent
{
public:
	DTXNetErrorEvent();
	virtual ~DTXNetErrorEvent();

	DTX_VOID setReset();

	DTXNetObject	*m_pNetObject;
	DTXString		m_strMethod;
	DTXString		m_strErrorText;
	DTX_INT			m_nErrorCode;
};


class DTX_CLSEXPENTRY DTXNetErrorEventHandler
{
public:
	virtual ~DTXNetErrorEventHandler();

	virtual DTX_INT evtError( DTXNetErrorEvent& errEvent );

	virtual DTX_VOID hndStartHandlingFor( DTXNetObject* netObject );
	virtual DTX_VOID hndStopHandlingFor( DTXNetObject* netObject );

	virtual DTX_INT     setGenErrEvent( DTXNetObject *pObject, DTX_INT nErrorCode, DTX_CPSZ pszInternalMethod = NULL );

protected:
	DTXLinkList	NetObjectList;
	virtual DTX_VOID hndStopHandlingFor();
	DTXNetErrorEventHandler();
};




class DTX_CLSEXPENTRY DTXNetCommand

{

public:

	DTXNetCommand();

	virtual ~DTXNetCommand();



	virtual DTX_INT getCommand();

	virtual DTX_PSZ getCommand( DTX_SMALLINT sCommand );

	virtual DTX_INT getCommand( DTXString& strCommand );



	//0 - nCommand will NULL the data members out.  Otherwise they concatenate.

	virtual DTX_VOID setCommand( DTX_INT nCommand, DTXString& strCommand );



//Do not use any methods or data members below here.

//	DTX_VOID     setNumOf( DTX_SMALLINT sNum );

	DTXString    strCmd;

	DTX_INT      nCmd;



private:

	DTXString    strBuffer;

//	DTX_SMALLINT sNumOf;

};


#undef DTXNetObject

class DTX_CLSEXPENTRY DTXNetObject : public DTXNetErrorEventHandler, public DTXCollectable
{
public:
	DTXNetObject( DTX_SMALLINT sObjType = DTXNETOBJ_CLIENT, DTX_BOOLEAN fInit = FALSE );
	virtual ~DTXNetObject();

	virtual u_short	        netCheckSum( DTX_PSMALLINT psData, int nDataLen );
	virtual DTX_RETCODE		netConnect();
	virtual DTX_RETCODE		netConnect( DTX_USMALLINT sValue );
	virtual DTX_RETCODE		netDisconnect( DTX_INT nConnection = 0 );
	virtual DTX_INT         netGetCommand();//Use this only if you do your own message/command structure

	virtual DTX_INT         netGetCommand( DTXNetCommand& netCommand );
	virtual DTX_RETCODE		netGetMsg( DTXString& strBuff );
	virtual DTX_RETCODE		netGetMsg( DTX_PCHAR pBuffer, DTX_PINT pnLen );
	virtual DTX_RETCODE		netGetMsgLen( DTX_PLINT pBuffer );
	virtual DTX_RETCODE		netPeekMsg( DTXString& strBuff );
	virtual DTX_RETCODE		netPeekMsg( DTX_PCHAR pBuffer, DTX_PINT pnLen );
	virtual DTX_RETCODE		netPing( DTX_CPSZ pszHostAdd, DTX_BOOLEAN fBlocking = TRUE );
	virtual DTX_RETCODE     netSendCommand( DTXNetCommand& netCommand );
	virtual DTX_RETCODE		netSendMsg( DTX_CPSZ pszBuffer );
	virtual DTX_RETCODE		netSendMsg( DTX_PCHAR pBuffer, DTX_INT nLen );

	virtual       operator const char*();
	DTXNetObject& operator<<( DTXNetCommand& netCommand );

	DTXNetObject& operator>>( DTXNetCommand& netCommand );

	DTXNetObject& operator<<( DTXNetParam& parValue );
	DTXNetObject& operator>>( DTXNetParam& parValue );
	DTXNetObject& operator<<( DTXString& strValue );
	DTXNetObject& operator>>( DTXString& strValue );
	DTXNetObject& operator<<( DTX_SMALLINT sValue );
	DTXNetObject& operator>>( DTX_PSMALLINT psValue );
	DTXNetObject& operator<<( DTX_INT nValue );
	DTXNetObject& operator>>( DTX_PINT pnValue );

	inline  DTX_ULINT				getAddress();
	virtual DTX_PSZ					getAddressByHost( DTX_CPSZ pszName );
	inline  DTX_PSZ					getAddressString();
	inline  DTX_BOOLEAN				getBlocking();
	virtual DTXNetErrorEventHandler *getErrEventHandler();
	inline  DTX_PSZ					getHost();
	virtual DTX_PSZ                 getHostByAddress( DTX_CPSZ pszAdd );
	virtual DTX_BOOLEAN             getIsConnected();
	virtual DTX_RETCODE             getIsReadyToGet( DTX_INT nReqSocket = -2 );
	virtual DTX_RETCODE             getIsReadyToGet( DTX_INT nReqSocket, DTX_INT nWait );
	virtual DTX_RETCODE             getIsReadyToSend( DTX_INT nReqSocket = -2 );
	virtual DTX_RETCODE             getIsReadyToSend( DTX_INT nReqSocket, DTX_INT nWait );
	virtual DTX_INT                 getNetError();
	inline  DTX_INT					getPacketSize();
	inline  DTX_USMALLINT			getPort();
	virtual DTX_USMALLINT			getPortByService( DTX_CPSZ pszName, DTX_USMALLINT unDefault = DTXNETPORT_NONE );
	inline  DTX_USMALLINT           getProtocol();
	inline  DTX_INT					getRetryCount();
	virtual DTX_PSZ					getService( DTX_USMALLINT uPort = 0 );
	inline  DTX_INT					getSocket();
	inline  DTX_SMALLINT            getState();
	inline  DTX_INT                 getTimeOut();
	inline  DTX_SMALLINT			getType();

	virtual DTX_VOID				setAddress( DTX_CPSZ pszAdd );
	virtual DTX_VOID				setAddress( DTX_ULINT ulAddress );
	virtual DTX_BOOLEAN				setBlocking( DTX_BOOLEAN fMode = TRUE );
	virtual DTX_VOID				setDataSize( DTX_INT nLen );
	virtual DTX_VOID				setErrEventHandler( DTXNetErrorEventHandler *perrEventHandler );
	virtual DTX_VOID				setHost( DTX_CPSZ pszName );
	inline  DTX_VOID				setPacketSize( DTX_INT nLen );
	virtual DTX_VOID				setPort( DTX_CPSZ pszService );
	virtual DTX_VOID				setPort( DTX_USMALLINT sValue, DTX_BOOLEAN fNetOrder = DTXNETOBJ_HOSTORDER );
	inline  DTX_USMALLINT			setProtocol( DTX_CPSZ pszProto = DTXNETPROTO_ICMP );
	inline  DTX_VOID				setRetryCount( DTX_INT nNum = 50000 );
	inline  DTX_SMALLINT			setState( DTX_SMALLINT sSocketState = DTX_STATECONNECT );
	inline  DTX_VOID                setSocket( DTX_INT nClientSocket );
	virtual DTX_RETCODE             setSocketOption( DTX_BOOLEAN fOption, DTX_INT nValue );
	virtual DTX_RETCODE             setSocketOption( DTX_BOOLEAN fOption, DTX_PVOID pOption, DTX_INT nLen = sizeof(int));
	inline  DTX_VOID                setTimeOut( DTX_INT nValue = 0 );
	virtual DTX_VOID                setToAddress( DTX_CPSZ pszHost = NULL );

	//DO NOT access any data members below here!!  Adverse things may happen.
	DTX_PCHAR 				pSocket;
	DTX_INT                 nIntCmd;

protected:
	DTX_PVOID				setAllocParamSize( DTX_LINT lLength );
	DTXString 				strName;
	DTXString 				strAdd;
	DTXString				strService;
	DTXString               strTmp;
	DTX_PCHAR				pData;
	DTX_ULINT				ulAdd;
	DTX_INT                 nRc;
	DTX_INT 				nSocket;
	DTX_INT 				nSize;
	DTX_INT					nData;

private:
	DTXString				strTmpData;
	DTXNetErrorEventHandler			*pErrEventHandler;
	PHOSTENT				pHost; //Working variable
	PSERVENT				pService;
	PPROTOENT				pProtocol;
	SOCKETADD_IN				stToAddress;
#if defined(__DTXNT__) || defined(__DTXWIN__)
	WSADATA					stWSAData;
#endif
	DTX_PCHAR               		pParamValue;
	DTX_LINT				lParamSize;
	DTX_BOOLEAN				fBlock;
	DTX_BOOLEAN				fSocket;
	DTX_INT					nRetry;
	DTX_INT         		        nTimeOut;
	DTX_USMALLINT 				sPort;   //Needs to be held in network order.
	DTX_USMALLINT				usProto; //Host byte order
	DTX_SMALLINT 				sType;
	DTX_SMALLINT				sState;
};

#include <dtxnet.inl>

#endif