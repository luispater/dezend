//////
// DTXSMTP.hpp - Header file for the DTXNetSmtp class
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

#ifndef __DTXSMTP__
#define __DTXSMTP__

#include <dtxmail.hpp>



class DTX_CLSEXPENTRY DTXNetSmtp : public DTXNetMail
{
public:
	DTXNetSmtp( DTX_USMALLINT uPort = DTXNETPORT_SMTP );
	virtual ~DTXNetSmtp();

};


#endif

