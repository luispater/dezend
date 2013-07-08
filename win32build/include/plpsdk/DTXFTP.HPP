//////
// DTXFTP.hpp - Header file for the DTXNetFtp class
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

#ifndef __DTXFTP__
#define __DTXFTP__

#include <dtxnetc.hpp>
#include <dtxnets.hpp>

//Below are the standard FTP codes as defined by the RFP
//	110	-	Restart marker reply
//	120	-	Service ready in xxx minutes
//	125	-	Data connection already open; transfer starting
//	150	-	File status OK; about to open data connections
//	200	-	Command OK
//	202	-	Command not implemented, superfluous at this site
//	211	-	System status or system help reply
//	212	-	Directory status
//	213	-	File status
//	214	-	Help message
//	215	-	NAME system type
//	220	-	Service ready for new user
//	221	-	Service closing control connection
//	225	-	Data connection open; no transfer in progress
//	226	-	Closing data connection.  Requested file action successful
//	227	-	Entering Passive Mode
//	230	-	User logged in, proceed
//	250	-	Requested file action OK, completed
//	257	-	"PATHNAME" created
//	331	-	User name OK, need password
//	332	-	Need account for login
//	350	-	Requested file action pending further information
//	421	-	Service not available, closing control connection
//	425	-	Can't open data connection
//	426	-	Connection closed; transfer aborted
//	450	-	Requested file action not taken. File unavailable
//	451	-	Requested action aborted: local error in processing
//	452	-	Requested action not taken.  Insufficient storage space in system
//	500	-	Syntax error, command unrecognized
//	501	-	Syntax error in parameters or arguments
//	502	-	Command not implemented
//	503	-	Bad sequence of commands
//	504	-	Command not implemented for that parameter
//	530	-	Not logged in
//	532	-	Need account for storing files
//	550	-	Requested action not taken.  File unavailable
//	551	-	Requested action aborted: page type unknown
//	552	-	Requested file action aborted.  Exceeded storage allocation
//	553	-	Requested action not taken.  File name not allowed



class DTX_CLSEXPENTRY DTXNetFtp : public DTXNetClient
{
public:
	DTXNetFtp( DTX_USMALLINT usPort = DTXNETPORT_FTP );
	virtual ~DTXNetFtp();

	enum MODE { modeTEXT = 0, modeBINARY };

	virtual DTX_RETCODE netAcceptDataConnection();
	virtual DTX_RETCODE netConnect();
	virtual DTX_RETCODE netConnect( DTX_USMALLINT usValue );
	virtual DTX_RETCODE netConnectData();
	virtual DTX_RETCODE netDisconnect();
	virtual DTX_RETCODE netDisconnectData();
	virtual DTX_RETCODE netGetData( DTX_CPSZ pszFileName );
	virtual DTX_RETCODE netSendData( DTX_CPSZ pszFileName );

	virtual DTX_RETCODE netCmdAPPE( DTX_CPSZ pszFileName, DTX_INT nMode = DTXNetFtp::modeTEXT );
	virtual DTX_RETCODE netCmdCDUP();
	virtual DTX_RETCODE netCmdCWD( DTX_CPSZ pszDir );
	virtual DTX_RETCODE netCmdDELE( DTX_CPSZ pszFileName );
	virtual DTX_RETCODE netCmdLIST( DTX_CPSZ pszOutputFileName );
	virtual DTX_RETCODE netCmdMKD( DTX_CPSZ pszDirName );
	virtual DTX_RETCODE netCmdPWD();
	virtual DTX_RETCODE netCmdRETR( DTX_CPSZ pszFileName, DTX_INT nMode = DTXNetFtp::modeTEXT );
	virtual DTX_RETCODE netCmdRMD( DTX_CPSZ pszDirName );
	virtual DTX_RETCODE netCmdREN( DTX_CPSZ pszOldFileName, DTX_CPSZ pszNewFileName );
	virtual DTX_RETCODE netCmdSend( DTX_CPSZ pszCmd, DTX_BOOLEAN fAccept = TRUE );
	virtual DTX_RETCODE netCmdSTOR( DTX_CPSZ pszFileName, DTX_INT nMode = DTXNetFtp::modeTEXT );
	virtual DTX_RETCODE netCmdSTOU( DTX_CPSZ pszFileName, DTX_INT nMode = DTXNetFtp::modeTEXT );
	virtual DTX_RETCODE netCmdQUIT();

	virtual DTX_INT     netSendCommand( DTX_CPSZ pszCommand );

	inline  DTX_RETCODE getServerReplyCode();
	inline  DTX_PSZ     getServerReplyMsg();

	virtual DTX_VOID    setMode( DTX_INT nMode = DTXNetFtp::modeTEXT );

protected: //Do not access any methods beyond here!
	DTX_RETCODE setServerReplyCodeMsg();

private:
	DTXNetServer srvData;
	DTXString    strReply;
	DTXString    strReplyCode;
	DTXString    strBuffer;
	DTXString    strPWD;
	DTX_INT      nReply;
	DTX_INT      nDataSocket;
	DTX_BOOLEAN  fAsc;
};

#include <dtxftp.inl>

#endif

