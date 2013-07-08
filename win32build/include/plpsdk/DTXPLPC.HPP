//////
// DTXPLPC.hpp - Header file for the DTXPrivateLabelClient class
//  (c)Copyright InnerX Communications, Inc. 1998
//////

#ifndef __DTXPLPC__
#define __DTXPLPC__

#include <dtxnetc.hpp>
#include <dtxplp.hpp>


class DTX_CLSEXPENTRY DTXPrivateLabelClient : public DTXPrivateLabel
{
public:
	DTXPrivateLabelClient();
	virtual ~DTXPrivateLabelClient();

	virtual DTX_RETCODE  netConnect( DTXString& strPrivateID, DTXString& strPrivatePW, DTX_CPSZ pszIPAddress = NULL );
	virtual DTX_RETCODE  netDisconnect();
	virtual DTX_RETCODE  netUserAdd( DTXString& strUserID, DTXString& strPassWord, DTX_CPSZ pszType, DTX_CPSZ pszAccess = NULL );
	virtual DTX_RETCODE  netUserChange( DTXString& strUserID, DTXString& strPassWord, DTX_CPSZ pszType, DTX_CPSZ pszAccess = NULL );
	virtual DTX_RETCODE  netUserDel( DTXString& strUserID );
	virtual DTX_RETCODE  netUserHold( DTXString& strUserID );
	virtual DTX_RETCODE  netUserHoldOff( DTXString& strUserID );

protected:
	DTXNetClient netClient;
};


#endif
