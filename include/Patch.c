/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   Patch.c
//  Version     :   1.0
//  Creator     :   RM
//  Create Date :   2006-01-01
//  Comment     :
//
///////////////////////////////////////////////////////////////////////////////
*/

#include < tchar.h >
#include < stdio.h >
#include < stdarg.h >
#include < malloc.h >

#ifdef _MSC_VER
#include < windows.h >
#else
#include "Compatible.h"
#endif

#include "Stack.h"
#include "Patch.h"

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
ULONG PatchMemory(
    PATCH_FUNCTION PatchFunction,
    PVOID Context,
    UCHAR *Address,
    ULONG Size,
    PATCH_ARRAY *PatchArray,
    ULONG PatchArrayCount,
    ULONG *PatchOffsetArray[],
    ULONG PatchOffsetArrayCount
    )
{
    ULONG RetCode;
    UCHAR *StartAddress;
    UCHAR *EndAddress;
    register ULONG Iter;
    register ULONG Iter1;
    register ULONG PatchOffset;

    do
    {
        RetCode = FALSE;
        if ( PatchOffsetArray == NULL )
            PatchOffsetArrayCount = 0;

        if ( PatchOffsetArray == NULL )
            PatchOffsetArrayCount = 0;

        StartAddress = Address;
        EndAddress = StartAddress + Size;

        /* Find Patch address */
        for ( Iter = 0; Iter < PatchArrayCount; Iter++ )
        {
            for ( Iter1 = 0; Iter1 < PatchOffsetArrayCount; Iter1++ )
            {
                PatchOffset = PatchOffsetArray[Iter1][Iter];
                if ( PatchOffset < Size && 0 == memcmp( Address + PatchOffset, PatchArray[Iter].Data, PatchArray[Iter].DataSize ) )
                {
                    StartAddress = Address + PatchOffset;
                    PatchArray[Iter].PatchAddress = StartAddress;
                    break;
                }
            }
            if ( Iter1 == PatchOffsetArrayCount )
            {
                while ( StartAddress < EndAddress )
                {
                    if ( StartAddress[0] == *( ( UCHAR* )( PatchArray[Iter].Data ) ) && 0 == memcmp( StartAddress, PatchArray[Iter].Data, PatchArray[Iter].DataSize ) )
                    {
                        PatchArray[Iter].PatchAddress = StartAddress;
                        break;
                    }
                    StartAddress++;
                }
            }
        }
        if ( StartAddress >= EndAddress )
            break;

        /* Patch */
        for ( Iter = 0; Iter < PatchArrayCount; Iter++ )
            PatchFunction( Iter, ( UCHAR* )( PatchArray[Iter].PatchAddress ) + PatchArray[Iter].PatchOffset, PatchArray[Iter].PatchData, PatchArray[Iter].PatchDataSize, Context );

        RetCode = TRUE;
    } while ( 0 );

    return RetCode;
}

ULONG PatchFile(
    PATCH_FUNCTION PatchFunction,
    PVOID Context,
    LPCTSTR FileName,
    PATCH_ARRAY *PatchArray,
    ULONG PatchArrayCount,
    ULONG *PatchOffsetArray[],
    ULONG PatchOffsetArrayCount
    )
{
    ULONG RetCode;
    HANDLE hFile;
    HANDLE hMapFile;
    ULONG FileSize;
    ULONG FileSizeHigh;
    UCHAR *FileMap;
    UCHAR *FileMapStart;
    UCHAR *FileMapEnd;
    register ULONG Iter;
    register ULONG Iter1;
    register ULONG PatchOffset;

    do
    {
        RetCode = FALSE;
        hFile = NULL;
        hMapFile = NULL;
        FileMap = NULL;

        hFile = CreateFile( FileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
        if ( hFile == NULL )
            break;

        FileSize = GetFileSize( hFile, &FileSizeHigh );
        hMapFile = CreateFileMapping( hFile, NULL, PAGE_READWRITE, FileSizeHigh, FileSize, NULL );
        if ( hMapFile == NULL )
            break;

        FileMap = ( UCHAR* )MapViewOfFile( hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, FileSize );
        if ( FileMap == NULL )
            break;

        if ( PatchOffsetArray == NULL )
            PatchOffsetArrayCount = 0;

        if ( PatchOffsetArray == NULL )
            PatchOffsetArrayCount = 0;

        FileMapStart = FileMap;
        FileMapEnd = FileMapStart + FileSize;

        /* Find Patch address */
        for ( Iter = 0; Iter < PatchArrayCount; Iter++ )
        {
            for ( Iter1 = 0; Iter1 < PatchOffsetArrayCount; Iter1++ )
            {
                PatchOffset = PatchOffsetArray[Iter1][Iter];
                if ( PatchOffset < FileSize && 0 == memcmp( FileMap + PatchOffset, PatchArray[Iter].Data, PatchArray[Iter].DataSize ) )
                {
                    FileMapStart = FileMap + PatchOffset;
                    PatchArray[Iter].PatchAddress = FileMapStart;
                    break;
                }
            }
            if ( Iter1 == PatchOffsetArrayCount )
            {
                while ( FileMapStart < FileMapEnd )
                {
                    if ( FileMapStart[0] == *( ( UCHAR* )( PatchArray[Iter].Data ) ) && 0 == memcmp( FileMapStart, PatchArray[Iter].Data, PatchArray[Iter].DataSize ) )
                    {
                        PatchArray[Iter].PatchAddress = FileMapStart;
                        break;
                    }
                    FileMapStart++;
                }
            }
        }
        if ( FileMapStart >= FileMapEnd )
            break;

        /* Patch */
        for ( Iter = 0; Iter < PatchArrayCount; Iter++ )
            PatchFunction( Iter, ( UCHAR* )( PatchArray[Iter].PatchAddress ) + PatchArray[Iter].PatchOffset, PatchArray[Iter].PatchData, PatchArray[Iter].PatchDataSize, Context );

        RetCode = TRUE;
    } while ( 0 );

    if ( FileMap )
        UnmapViewOfFile( FileMap );

    if ( hMapFile )
        CloseHandle( hMapFile );

    if ( hFile )
        CloseHandle( hFile );

    return RetCode;
}