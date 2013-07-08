/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   Search.c
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

#include "Macro.h"
#include "Stack.h"
#include "Search.h"
#include "AddLog.h"

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
ULONG SearchString( PCOMMON_STACK_U Result, LPVOID StartAddress, LPVOID EndAddress, const unsigned char *String, ULONG Length )
{
    ULONG RetCode;
    ULONG PageSize;
    const unsigned char *Start;
    const unsigned char *End;
    const unsigned char *SearchStart;
    const unsigned char *SearchEnd;
    MEMORY_BASIC_INFORMATION BasicMemInfo;

    RetCode = 0;
    PageSize = PAGE_SIZE;
    Start = ( const unsigned char * )StartAddress;
    End = ( const unsigned char * )EndAddress;
    while ( Start < End )
    {
        if ( VirtualQuery( Start, &BasicMemInfo, sizeof( BasicMemInfo ) ) )
        {
            Start = ( const unsigned char * )BasicMemInfo.BaseAddress + BasicMemInfo.RegionSize;
            if ( BasicMemInfo.State & MEM_COMMIT && !( BasicMemInfo.Protect & ( PAGE_GUARD | PAGE_NOACCESS ) ) )
            {
                SearchStart = ( const unsigned char * )BasicMemInfo.BaseAddress;
                SearchEnd = ( const unsigned char * )Start;
                while ( SearchStart < SearchEnd )
                {
                    if ( SearchStart[0] == String[0] && 0 == memcmp( SearchStart, String, Length ) )
                    {
                        RetCode++;
                        StackPushU( Result, ( ULONG )SearchStart );
                        SearchStart += Length;
                    }
                    else
                    {
                        SearchStart++;
                    }
                }
            }
        }
        else
        {
            Start += PageSize;
        }
    }

    return RetCode;
}

ULONG SearchStringEx( PCOMMON_STACK_U Result, HANDLE hProcess, LPVOID StartAddress, LPVOID EndAddress, const unsigned char *String, ULONG Length )
{
    ULONG RetCode;
    ULONG PageSize;
    ULONG Size;
    ULONG Dummy;
    const unsigned char *Start;
    const unsigned char *End;
    const unsigned char *SearchStart;
    const unsigned char *SearchEnd;
    MEMORY_BASIC_INFORMATION BasicMemInfo;
    COMMON_STACK_S Buffer;

    StackInitS( &Buffer, PAGE_SIZE );

    RetCode = 0;
    PageSize = PAGE_SIZE;
    Start = ( const unsigned char * )StartAddress;
    End = ( const unsigned char * )EndAddress;
    while ( Start < End )
    {
        if ( VirtualQueryEx( hProcess, Start, &BasicMemInfo, sizeof( BasicMemInfo ) ) )
        {
            Start = ( const unsigned char * )BasicMemInfo.BaseAddress + BasicMemInfo.RegionSize;
            if ( BasicMemInfo.State & MEM_COMMIT && !( BasicMemInfo.Protect & ( PAGE_GUARD | PAGE_NOACCESS ) ) )
            {
                Size = BasicMemInfo.RegionSize;
                StackSetMaxS( &Buffer, Size );
                if ( ReadProcessMemory( hProcess, ( const unsigned char * )BasicMemInfo.BaseAddress, StackBaseS( &Buffer ), Size, &Dummy ) )
                {
                    SearchStart = ( const unsigned char * )StackBaseS( &Buffer );
                    SearchEnd = ( const unsigned char * )( SearchStart + Size );
                    while ( SearchStart < SearchEnd )
                    {
                        if ( SearchStart[0] == String[0] && 0 == memcmp( SearchStart, String, Length ) )
                        {
                            RetCode++;
                            StackPushU( Result, ( ULONG )BasicMemInfo.BaseAddress + ( ULONG )SearchStart - ( ULONG )StackBaseS( &Buffer ) );
                            SearchStart += Length;
                        }
                        else
                        {
                            SearchStart++;
                        }
                    }
                }
            }
        }
        else
        {
            Start += PageSize;
        }
    }

    StackUninitS( &Buffer );

    return RetCode;
}

ULONG SearchStringAndLog( LPVOID StartAddress, LPVOID EndAddress, const unsigned char *String, ULONG Length )
{
    ULONG RetCode;
    COMMON_STACK_U Result;
    ULONG Address;

    StackInitU( &Result, 0 );

    RetCode = SearchString( &Result, StartAddress, EndAddress, String, Length );

    while ( StackPopBottomU( &Result, &Address ) )
        ADD_DEBUG_LOG_LR( _T( "[ %08X ]" ), Address );

    StackUninitU( &Result );

    return RetCode;
}

ULONG SearchStringAndLogEx( HANDLE Process, LPVOID StartAddress, LPVOID EndAddress, const unsigned char *String, ULONG Length )
{
    ULONG RetCode;
    COMMON_STACK_U Result;
    ULONG Address;

    StackInitU( &Result, 0 );

    RetCode = SearchStringEx( &Result, Process, StartAddress, EndAddress, String, Length );

    while ( StackPopBottomU( &Result, &Address ) )
        ADD_DEBUG_LOG_LR( _T( "[ %08X ]" ), Address );

    StackUninitU( &Result );

    return RetCode;
}