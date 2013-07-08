//////
// DTXBIT.hpp - Header file for DTXByteBit class
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

#include <dtxbase.hpp>

#ifndef __DTXBIT__
#define __DTXBIT__

class DTX_CLSEXPENTRY DTXByteBit
{
public:
	DTXByteBit();
	virtual ~DTXByteBit();

	DTX_CHAR     getCharBit( DTX_CHAR cByte, DTX_SMALLINT sBit );
	DTX_CHAR     getCharBit( DTX_SMALLINT sTwoByte, DTX_SMALLINT sBit );

	DTX_CHAR     getCharByte( DTX_SMALLINT sTwoByte, DTX_SMALLINT sByte );

	DTX_SMALLINT getSmallIntBit( DTX_CHAR cByte, DTX_SMALLINT sBit );

//Do other byte and word conversions

};

#endif
