//////
// DTXREG.hpp - Header file for the DTXRegistry class
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

#ifndef __DTXREG__
#define __DTXREG__
#include <dtxbase.hpp>
#include <dtxstr.hpp>

#if defined(__DTXNT__) || defined(__DTXWIN__)
#define DTX_HKEY         HKEY
//Predefined open keys
#define DTX_HKEY_LOCAL   HKEY_LOCAL_MACHINE
#define DTX_HKEY_USER	 HKEY_CURRENT_USER
#define DTX_HKEY_CLASS   HKEY_CLASSES_ROOT
#define DTX_HKEY_USERS   HKEY_USERS
#endif


class DTX_CLSEXPENTRY DTXRegistry
{
public:
	DTXRegistry();
	DTXRegistry( DTX_HKEY hKey, DTX_CPSZ pszKey );
	virtual ~DTXRegistry();

	enum KEYVALUE { regCreate, regNoCreate };
#if defined(__DTXNT__) || defined(__DTXWIN__)
	enum DATATYPE { typeSTRING = REG_SZ, typeARRAY = REG_MULTI_SZ, typeBINARY = REG_BINARY, typeINT = REG_DWORD, typeINT_LE = REG_DWORD_LITTLE_ENDIAN, typeINT_BE = REG_DWORD_BIG_ENDIAN };
#endif

	virtual DTX_VOID    regCloseKey();
	virtual DTX_VOID    regDeleteKey( DTX_CPSZ pszKey );
    virtual DTX_VOID    regDeleteValue( DTX_CPSZ pszValue );

	inline  DTX_BOOLEAN getIsOpen();
    virtual DTX_BOOLEAN getValue( DTX_CPSZ pszEntry, DTX_PINT pValue, DTX_INT nDefault );
    virtual DTX_BOOLEAN getValue( DTX_CPSZ pszEntry, DTXString& strValue, DTX_PSZ pszDefault = NULL );

    virtual DTX_BOOLEAN setBaseKey( DTX_HKEY hKey, DTX_CPSZ pszKey );
    virtual DTX_BOOLEAN setKey( DTX_HKEY hKey, DTX_CPSZ pszSubKey, DTX_SMALLINT sKeyValue = DTXRegistry::regNoCreate );
    inline  DTX_BOOLEAN setSubKey( DTX_CPSZ pszSubKey, DTX_SMALLINT sKeyValue = DTXRegistry::regNoCreate );
    virtual DTX_BOOLEAN setValue( DTX_CPSZ pszEntry, DTX_CPSZ pszValue );
    virtual DTX_BOOLEAN setValue( DTX_CPSZ pszEntry, DTX_INT nValue );

private:
    DTX_HKEY m_hKey;
    DTX_HKEY m_hBaseKey;
};


#include <dtxreg.inl>

#endif


