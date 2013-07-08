//////
// DTXSEC.hpp - Header file for the DTXSecurity class
//  (c)Copyright InnerX Communications, Inc. 1998
//////

#ifndef __DTXSEC__
#define __DTXSEC__

#include <dtxstr.hpp>


class DTX_CLSEXPENTRY DTXSecurity
{
public:
	DTXSecurity();
	virtual ~DTXSecurity();

	virtual DTX_PSZ     secCrypt( DTX_PSZ pszValue, DTX_PSZ pszSetting );
	virtual DTX_BOOLEAN secMod10( DTX_CPSZ pszValue );
};


#endif
