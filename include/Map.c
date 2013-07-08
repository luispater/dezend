/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   Map.c
//  Version     :   1.0
//  Creator     :   RM
//  Create Date :   2006-01-01
//  Comment     :
//
///////////////////////////////////////////////////////////////////////////////
*/

#include < stdio.h >

#ifdef _MSC_VER
#include < windows.h >
#else
#include "Compatible.h"
#endif

#include "Macro.h"
#include "Map.h"

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/

/*
///////////////////////////////////////////////////////////////////////////////
// S T R U C T U R E S
///////////////////////////////////////////////////////////////////////////////
*/
typedef struct _KEY_VALUE {
    ULONG Key;
    ULONG Value;
} KEY_VALUE, *PKEY_VALUE;

/*
///////////////////////////////////////////////////////////////////////////////
// F U N C T I O N S
///////////////////////////////////////////////////////////////////////////////
*/
__forceinline ULONG MapFileGenericFlags( ULONG Flags )
{
    ULONG RetCode;
    ULONG Iter;
    ULONG Count;
    static KEY_VALUE MapArray[] = {
        { MAP_FILE_GENERIC_READ, GENERIC_READ },
        { MAP_FILE_GENERIC_WRITE, GENERIC_WRITE },
        { MAP_FILE_GENERIC_EXECUTE, GENERIC_EXECUTE },
    };

    if ( Flags == MAP_FILE_GENERIC_ALL )
    {
        RetCode = GENERIC_ALL;
    }
    else
    {
        RetCode = 0;
        for ( Iter = 0, Count = SIZE_OF_ARRAY( MapArray ); Iter < Count; Iter++ )
            if ( Flags & MapArray[Iter].Key )
                RetCode |= MapArray[Iter].Value;
    }

    return RetCode;
}

__forceinline ULONG MapFileShareFlags( ULONG Flags )
{
    ULONG RetCode;
    ULONG Iter;
    ULONG Count;
    static KEY_VALUE MapArray[] = {
        { MAP_FILE_SHARE_READ, FILE_SHARE_READ },
        { MAP_FILE_SHARE_WRITE, FILE_SHARE_WRITE },
        { MAP_FILE_SHARE_DELETE, FILE_SHARE_DELETE },
    };

    if ( Flags == MAP_FILE_SHARE_ALL )
    {
        RetCode = FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE;
    }
    else
    {
        RetCode = 0;
        for ( Iter = 0, Count = SIZE_OF_ARRAY( MapArray ); Iter < Count; Iter++ )
            if ( Flags & MapArray[Iter].Key )
                RetCode |= MapArray[Iter].Value;
    }

    return RetCode;
}

__forceinline ULONG MapFileMappingFlags( ULONG Flags )
{
    if ( Flags & MAP_FILE_WRITE )
        return PAGE_READWRITE;
    else
        return PAGE_READONLY;
}

__forceinline ULONG MapFileMapFlags( ULONG Flags )
{
    ULONG RetCode;
    ULONG Iter;
    ULONG Count;
    static KEY_VALUE MapArray[] = {
        { MAP_FILE_QUERY, FILE_MAP_COPY },
        { MAP_FILE_READ, FILE_MAP_READ },
        { MAP_FILE_WRITE, FILE_MAP_WRITE },
        { MAP_FILE_EXECUTE, FILE_EXECUTE },
    };

    if ( Flags == MAP_FILE_ALL )
    {
        RetCode = FILE_MAP_ALL_ACCESS;
    }
    else
    {
        RetCode = 0;
        for ( Iter = 0, Count = SIZE_OF_ARRAY( MapArray ); Iter < Count; Iter++ )
            if ( Flags & MapArray[Iter].Key )
                RetCode |= MapArray[Iter].Value;
    }

    return RetCode;
}

ULONG MapFileEx( LPCTSTR FileName, PVOID *Map, ULONG *FileSizePtr, ULONG *FileSizeHighPtr, ULONG Flags )
{
    ULONG RetCode;
    HANDLE hFile;
    HANDLE hMapFile;
    ULONG FileSize;
    ULONG FileSizeHigh;
    UCHAR *FileMap;

    do
    {
        RetCode = FALSE;
        hFile = INVALID_HANDLE_VALUE;
        hMapFile = NULL;
        FileMap = NULL;
        FileSize = 0;
        FileSizeHigh = 0;

        hFile = CreateFile( FileName, MapFileGenericFlags( Flags ), MapFileShareFlags( Flags ), NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
        if ( hFile == INVALID_HANDLE_VALUE )
            break;

        FileSize = GetFileSize( hFile, &FileSizeHigh );
        hMapFile = CreateFileMapping( hFile, NULL, MapFileMappingFlags( Flags ), FileSizeHigh, FileSize, NULL );
        if ( hMapFile == NULL )
            break;

        FileMap = ( UCHAR* )MapViewOfFile( hMapFile, MapFileMapFlags( Flags ), 0, 0, FileSize );
        if ( FileMap == NULL )
            break;

        RetCode = TRUE;
    } while ( 0 );

    if ( Map )
        *Map = FileMap;

    if ( FileSizePtr )
        *FileSizePtr = FileSize;

    if ( FileSizeHighPtr )
        *FileSizeHighPtr = FileSizeHigh;

    if ( hMapFile )
        CloseHandle( hMapFile );

    if ( hFile != INVALID_HANDLE_VALUE )
        CloseHandle( hFile );

    return RetCode;
}

ULONG MapFile( LPCTSTR FileName, PVOID *Map, ULONG *FileSizePtr, ULONG *FileSizeHighPtr )
{
    return MapFileEx( FileName, Map, FileSizePtr, FileSizeHighPtr, MAP_FILE_ALL | MAP_FILE_SHARE_READWRITE | MAP_FILE_GENERIC_READWRITE );
}

ULONG UnMapFile( PVOID Map )
{
    if ( Map )
        return UnmapViewOfFile( Map );
    else
        return TRUE;
}