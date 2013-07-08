//////
// DTXPLP.hpp - Header file for the DTXPrivateLabel class
//  (c)Copyright InnerX Communications, Inc. 1998
//////

#ifndef __DTXPLP__
#define __DTXPLP__

#include <dtxstr.hpp>


class DTX_CLSEXPENTRY DTXPrivateLabel
{
public:
	DTXPrivateLabel();
	virtual ~DTXPrivateLabel();

	enum ERRORCODE { rcNOERROR, rcNOSERVER, rcNODBSERVER, rcDBERROR, rcADDERROR, rcDELERROR, rcONHOLD, rcDUPLICATE };

	virtual DTX_RETCODE  netConnect( DTXString& strPrivateID, DTXString& strPrivatePW );
	virtual DTX_RETCODE  netDisconnect();
	virtual DTX_RETCODE  netUserAdd( DTXString& strUserID, DTXString& strPassWord );
	virtual DTX_RETCODE  netUserDel( DTXString& strUserID );

	DTX_INT      getErrorCode();
	DTX_PSZ      getErrorMsg();

protected:
	DTXString     strError;
	DTXString     strBuffer;
	DTXString     strPID;
	DTXString     strPPW;
	DTX_INT       nError;
};


#endif
