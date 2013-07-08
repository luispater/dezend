//////
// DTXWHOIS.hpp - Header file for the DTXNetWhois class
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

#ifndef __DTXWHOIS__
#define __DTXWHOIS__

#include <dtxnetc.hpp>


class DTX_CLSEXPENTRY DTXNetWhois : public DTXNetClient
{
public:
	DTXNetWhois( DTX_CPSZ pszHost, DTX_USMALLINT uPort = DTXNETPORT_WHOIS );
	virtual ~DTXNetWhois();

	virtual DTX_RETCODE netConnect();
	virtual DTX_RETCODE netConnect( DTX_USMALLINT uPort );

	virtual DTX_RETCODE whoFetch( DTX_CPSZ pszDomain );

	virtual operator const char *();

	DTXString   m_strWho;
};


#endif
