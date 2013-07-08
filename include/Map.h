/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   Map.h
//  Version     :   1.0
//  Creator     :   RM
//  Create Date :   2006-01-01
//  Comment     :
//
///////////////////////////////////////////////////////////////////////////////
*/

#ifndef __MAP_H__
#define __MAP_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/
#define MAP_FILE_QUERY 0x1
#define MAP_FILE_WRITE 0x2
#define MAP_FILE_READ 0x4
#define MAP_FILE_EXECUTE 0x8
#define MAP_FILE_READWRITE ( MAP_FILE_WRITE | MAP_FILE_READ )
#define MAP_FILE_ALL ( MAP_FILE_QUERY | MAP_FILE_WRITE | MAP_FILE_READ )

#define MAP_FILE_GENERIC_WRITE 0x200
#define MAP_FILE_GENERIC_READ 0x400
#define MAP_FILE_GENERIC_EXECUTE 0x800
#define MAP_FILE_GENERIC_READWRITE ( MAP_FILE_GENERIC_WRITE | MAP_FILE_GENERIC_READ )
#define MAP_FILE_GENERIC_ALL ( MAP_FILE_GENERIC_WRITE | MAP_FILE_GENERIC_READ | MAP_FILE_GENERIC_EXECUTE )

#define MAP_FILE_SHARE_WRITE 0x20000
#define MAP_FILE_SHARE_READ 0x40000
#define MAP_FILE_SHARE_DELETE 0x80000
#define MAP_FILE_SHARE_READWRITE ( MAP_FILE_SHARE_WRITE | MAP_FILE_SHARE_READ )
#define MAP_FILE_SHARE_ALL ( MAP_FILE_SHARE_WRITE | MAP_FILE_SHARE_READ | MAP_FILE_SHARE_DELETE )

/*
///////////////////////////////////////////////////////////////////////////////
// S T R U C T U R E S
///////////////////////////////////////////////////////////////////////////////
*/

/*
///////////////////////////////////////////////////////////////////////////////
// G L O B A L S
///////////////////////////////////////////////////////////////////////////////
*/

/*
///////////////////////////////////////////////////////////////////////////////
// F U N C T I O N S
///////////////////////////////////////////////////////////////////////////////
*/
ULONG MapFile( LPCTSTR FileName, PVOID *Map, ULONG *FileSizePtr, ULONG *FileSizeHighPtr );
ULONG MapFileEx( LPCTSTR FileName, PVOID *Map, ULONG *FileSizePtr, ULONG *FileSizeHighPtr, ULONG Flags );
ULONG UnMapFile( PVOID Map );

#ifdef __cplusplus
}
#endif
/*
///////////////////////////////////////////////////////////////////////////////
// E N D  O F  F I L E
///////////////////////////////////////////////////////////////////////////////
*/
#endif /* __MAP_H__ */