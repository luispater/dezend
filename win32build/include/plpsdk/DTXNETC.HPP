//////
// DTXNETC.hpp - Header file for the DTXNetClient class
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

#ifndef __DTXNETC__
#define __DTXNETC__

#include <dtxnet.hpp>

#define DTXNETCLIENTMAXUSERLEN 61
#define DTXNETCLIENTMAXPASSLEN 21


class DTX_CLSEXPENTRY DTXNetClient : public DTXNetObject
{
public:
	DTXNetClient();
	virtual ~DTXNetClient();

	// These basic methods are defined in all the primary network classes.
	virtual DTX_BOOLEAN netConnect();
	virtual DTX_BOOLEAN netConnect( DTX_USMALLINT sValue );

	inline  DTX_PSZ     getPassWord();
	inline  DTX_PSZ     getUserName();

	inline  DTX_VOID	setPassWord( DTX_CPSZ pszPass );
	inline  DTX_VOID	setUserName( DTX_CPSZ pszUser );

private:
	DTX_CHAR    szUser[DTXNETCLIENTMAXUSERLEN];
	DTX_CHAR    szPass[DTXNETCLIENTMAXPASSLEN];

};

#include <dtxnetc.inl>

#endif

