//////
// DTXPRF.hpp - Header file for the DTXProfile class
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

#ifndef __DTXPRF__
#define __DTXPRF__
#include <dtxbase.hpp>
#include <dtxstr.hpp>

class DTXString;

//This is the base class for profiles or ini files.  This class can not be
// called or inherited from directly.  You must use one of the three types
// of profile (ini) classes (User,System or Private). Only Private allows
// you to close or open.  The others do it automatically.

//(setBinaryData) - By setting pszKey = NULL, pValue = NULL and unLen = 0 the entry will be deleted.
//(setString)     - By setting pszKey = NULL and pszString = NULL the entry will be deleted.

class DTX_CLSEXPENTRY DTXProfile
{
public:
	DTXProfile();
	virtual ~DTXProfile();

	virtual DTX_PVOID   getBinaryData( DTX_CPSZ pszSection, DTX_CPSZ pszKey, DTX_PVOID pValue, DTX_UINT unLen );
	virtual DTX_UINT    getDefaultStringSize();
	virtual DTX_HINI    getHandle();
	virtual DTX_INT     getInteger( DTX_CPSZ pszSection, DTX_CPSZ pszKey, DTX_INT nDefault = 0 );
	virtual DTX_PSZ     getString( DTX_CPSZ pszSection, DTX_CPSZ pszKey, DTX_CPSZ pszDefult, DTXString& strString );

	virtual DTX_BOOLEAN setBinaryData( DTX_CPSZ pszSection, DTX_CPSZ pszKey, DTX_PVOID pValue, DTX_UINT unLen );
	virtual DTX_VOID    setDefaultStringSize( DTX_UINT unSize = 4096 );
	virtual DTX_VOID    setHandle( DTX_HINI hFile );
	virtual DTX_BOOLEAN setString( DTX_CPSZ pszSection, DTX_CPSZ pszKey, DTX_CPSZ pszString );

private:
	DTX_HINI  hIni;
	DTX_UINT  unDefBuffSize;
};


class DTX_CLSEXPENTRY DTXProfileUser : public DTXProfile
{
public:
	DTXProfileUser();
	virtual ~DTXProfileUser();

};


class DTX_CLSEXPENTRY DTXProfileSystem : public DTXProfile
{
public:
	DTXProfileSystem();
	virtual ~DTXProfileSystem();

};


class DTX_CLSEXPENTRY DTXProfilePrivate : public DTXProfile
{
public:
	DTXProfilePrivate( DTX_ANCBLOCK hBlk = NULL, DTX_CPSZ pszName = NULL );
	virtual ~DTXProfilePrivate();


	virtual DTX_HINI  getOpen( DTX_CPSZ pszName );

	virtual DTX_VOID  setAncBlock( DTX_ANCBLOCK hBlk );
	virtual DTX_VOID  setClose();

private:
	DTX_ANCBLOCK hBlock;
};


#endif


