//////
// DTXPOP3.hpp - Header file for the DTXNetPop3 class
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

#ifndef __DTXPOP3__
#define __DTXPOP3__

#include <dtxmail.hpp>



class DTX_CLSEXPENTRY DTXNetPop3 : public DTXNetMail
{
public:
	DTXNetPop3( DTX_USMALLINT uPort = DTXNETPORT_POP3 );
	virtual ~DTXNetPop3();
};


#endif

