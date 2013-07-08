//////
// DTXMATH.hpp - Header file for the DTXMath class
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

#ifndef __DTXMATH__
#define __DTXMATH__


#include <dtxint.hpp>
#include <dtxlnk.hpp>


class DTX_CLSEXPENTRY DTXMath : public DTXCollectable
{
public:
	DTXMath();
//	DTXMath( DTX_CPSZ pszString );
//	DTXMath( DTX_PSZ pszString );
//	DTXMath( DTX_PCHAR pString, DTX_UINT nSize );
//	DTXMath( DTX_SMALLINT sString );
//	DTXMath( DTX_INT nString );
//	DTXMath( DTX_UINT unString );
//	DTXMath( DTX_REAL rString );
//	DTXMath( DTX_FLOAT fString );
//	DTXMath( const DTXString& strString );
//	DTXMath( const DTXMath& mMath );
	virtual ~DTXMath();

	DTXMath&           operator=( DTXMath& mValue );
	DTXMath            operator+( DTXMath& mValue );
	DTXMath            operator-( DTXMath& mValue );
	DTXMath            operator*( DTXMath& mValue );
	DTXMath            operator/( DTXMath& mValue );
	DTXMath&           operator+=( DTXMath& mValue );

protected:
	DTXString			strValue;
	DTX_UINT            unDecs;
};

#endif


