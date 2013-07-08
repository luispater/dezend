//////
// DTXRAND.hpp - Header file for the DTXRandom class.
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

#ifndef __DTXRAND__
#define __DTXRAND__

#include <dtxlnk.hpp>
#include <stdlib.h>
#include <time.h>


class DTX_CLSEXPENTRY DTXRandom : public DTXCollectable
{
public:
	DTXRandom();
	virtual ~DTXRandom();

	inline DTX_PSZ rndCreate( DTX_PSZ pszData, DTX_SMALLINT sSize );

protected:
	DTX_CHAR szItoa64[65];
};


#include <dtxrand.inl>

#endif

