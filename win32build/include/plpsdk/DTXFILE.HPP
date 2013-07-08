//////
// DTXFile.hpp - Header file for the DTXFile, DTXDirectory classes
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

#ifndef __DTXFILE__
#define __DTXFILE__

#include <fcntl.h>
#if defined(__DTXWIN__) || defined(__DTXNT__)
#include <direct.h>
#include <errno.h>
#include <time.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <sys\utime.h>
#include <stdio.h>
#include <io.h>
#endif
#include <dtxdat.hpp>
#include <dtxstr.hpp>

#if defined(__DTXOS2__) || defined(__DTXUNIX__)
#define _O_RDWR		2 //O_RDWR
#define _O_BINARY	0x00008000//O_BINARY
#define _O_CREAT	0x00000100//O_CREATE
#define _O_RDONLY	0x00000004//O_RDONLY
#define _O_APPEND	0x00000008//O_APPEND
#define _O_TEXT		0x00004000//O_TEXT
#define _O_TRUNC	0x00000200//O_TRUNC
#endif

#ifdef __DTXUNIX__
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <utime.h>
#include <limits.h>
#endif

//DTXDirectory is below...


class DTX_CLSEXPENTRY DTXFile : public DTXCollectable
{
public:
	DTXFile();
	virtual ~DTXFile();

	enum PTR_POS { POS_BEGIN, POS_CURRENT, POS_END };
	enum MODE { modeRW = _O_RDWR, modeBINARY = _O_BINARY, modeCREATE = _O_CREAT, modeRO = _O_RDONLY, modeAPPEND = _O_APPEND, modeTEXT = _O_TEXT, modeTRUNC = _O_TRUNC };

#ifdef __DTXOS2__
	virtual DTX_BOOLEAN Close( DTX_FHANDLE hFileToClose = NULL );
#else
    virtual DTX_BOOLEAN Close( DTX_FHANDLE hFileToClose = -1 );
#endif	
	virtual DTX_BOOLEAN Copy( DTX_CPSZ pszSource, DTX_CPSZ pszDest );
	virtual DTX_BOOLEAN Create( DTX_CPSZ pszFileName );
	virtual DTX_BOOLEAN Delete( DTX_CPSZ pszFileName );
	virtual DTX_BOOLEAN Open( DTX_CPSZ pszFileName, DTX_INT nMode = DTXFile::modeRW );
	virtual DTX_UINT    Read( DTX_PVOID pData, DTX_UINT unLen );
	virtual DTX_UINT    Write( DTX_PVOID pData, DTX_UINT unLen );

	virtual DTXDate&    getDateCreated( DTX_CPSZ pszFileName );

	virtual DTX_BOOLEAN setDateCreated( DTX_CPSZ pszFileName, DTXDate& datValue );
	virtual DTX_INT     setFilePtr( DTX_INT nOffset, DTX_INT nFromWhere = DTXFile::POS_CURRENT );

protected: //Do not alter any data members below here.
	DTXString   strData;
	DTXDate     FileDate;
	DTX_FHANDLE hFile;
};


class DTX_CLSEXPENTRY DTXDirectory : public DTXFile
{
public:
	DTXDirectory();
	virtual ~DTXDirectory();

	//enum FILETYPE { typeNORMAL, typeDIR, typeHIDDEN, typeSYSTEM };

	virtual DTX_BOOLEAN  dirCreate( DTX_CPSZ pszDirName );
	virtual DTX_BOOLEAN  dirDelete( DTX_CPSZ pszDirName );
	virtual DTX_BOOLEAN  dirExist( DTX_CPSZ pszDirName );
	virtual DTX_BOOLEAN  dirFileExist( DTX_CPSZ pszFileName );

	virtual DTXString&   getCurrentDir();
	virtual DTXDate&     getDateCreated( DTX_CPSZ pszDirName );

	virtual DTX_BOOLEAN  setCurrentDir( DTX_CPSZ pszDirName );
};

#endif
