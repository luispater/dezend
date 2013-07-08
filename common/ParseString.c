/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   ParseString.c
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
#include "Dump.h"
#include "ParseString.h"

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/
#define BUFFER_SIZE 4096

#ifndef HEAP_ALLOC
#define HEAP_ALLOC( Size ) HeapAlloc( GetProcessHeap( ), 0, Size )
#endif

#ifndef HEAP_FREE
#define HEAP_FREE( Buffer ) HeapFree( GetProcessHeap( ), 0, Buffer )
#endif

#ifndef HEAP_REALLOC
#define HEAP_REALLOC( Buffer, Size ) HeapReAlloc( GetProcessHeap( ), 0, Buffer, Size )
#endif

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
void ParseStringExA( PCOMMON_STACK List, LPCSTR String, char Separator, char Boundary, char Replace )
{
    LPSTR lptszHead;
    LPSTR lptszTail;
    LPSTR lptszStart;
    LPSTR lptszEnd;
    LPSTR lptszPtr;
    char Buffer[BUFFER_SIZE];

    strncpy( Buffer, String, SIZE_OF_ARRAY( Buffer ) );
    Buffer[SIZE_OF_ARRAY( Buffer ) - 1] = '\0';

    lptszHead = Buffer;
    lptszTail = lptszHead + strlen( lptszHead );

    /* Encode separator char in boundary */
    lptszStart = lptszHead;
    while ( lptszStart < lptszTail )
    {
        if ( *lptszStart == Boundary )
        {
            lptszStart++;
            while ( lptszStart < lptszTail )
            {
                if ( *lptszStart == Boundary )
                    break;

                if ( *lptszStart == Separator )
                    *lptszStart = Replace;
                lptszStart++;
            }
        }
        lptszStart++;
    }

    for ( lptszStart = lptszHead; lptszStart < lptszTail; lptszStart = lptszEnd + 1 )
    {
        while ( *lptszStart == Separator && lptszStart < lptszTail )
            lptszStart++;

        if ( lptszStart == lptszTail )
            break;

        lptszEnd = lptszStart;
        while ( lptszEnd < lptszTail )
        {
            if ( *lptszEnd == Separator )
                break;
            lptszEnd++;
        }
        if ( lptszEnd < lptszTail )
            *lptszEnd = '\0';

        lptszPtr = lptszStart;
        /* Decode separator char in boundary */
        while ( lptszPtr < lptszEnd )
        {
            if ( *lptszPtr == Replace )
            {
                *lptszPtr = Separator;
            }
            else if ( *lptszPtr == Boundary )
            {
                memcpy( lptszPtr, lptszPtr + 1, ( lptszTail - lptszPtr ) * sizeof( char ) );
                lptszEnd--;
                lptszTail--;
            }
            lptszPtr++;
        }

        StackPush( List, lptszStart, ROUND_SIZE( ( lptszEnd - lptszStart + 1 ) * sizeof( char ) ) );
    }
}

void ParseStringDataExA( PCOMMON_STACK_U List, LPCSTR String, char Separator, char Boundary, char Replace )
{
    LPSTR lptszHead;
    LPSTR lptszTail;
    LPSTR lptszStart;
    LPSTR lptszEnd;
    LPSTR lptszPtr;
    char Buffer[BUFFER_SIZE];

    strncpy( Buffer, String, SIZE_OF_ARRAY( Buffer ) );
    Buffer[SIZE_OF_ARRAY( Buffer ) - 1] = _T( '\0' );

    lptszHead = Buffer;
    lptszTail = lptszHead + strlen( lptszHead );

    /* Encode separator char in boundary */
    lptszStart = lptszHead;
    while ( lptszStart < lptszTail )
    {
        if ( *lptszStart == Boundary )
        {
            lptszStart++;
            while ( lptszStart < lptszTail )
            {
                if ( *lptszStart == Boundary )
                    break;

                if ( *lptszStart == Separator )
                    *lptszStart = Replace;
                lptszStart++;
            }
        }
        lptszStart++;
    }

    for ( lptszStart = lptszHead; lptszStart < lptszTail; lptszStart = lptszEnd + 1 )
    {
        while ( *lptszStart == Separator && lptszStart < lptszTail )
            lptszStart++;

        if ( lptszStart == lptszTail )
            break;

        lptszEnd = lptszStart;
        while ( lptszEnd < lptszTail )
        {
            if ( *lptszEnd == Separator )
                break;
            lptszEnd++;
        }
        if ( lptszEnd < lptszTail )
            *lptszEnd = '\0';

        lptszPtr = lptszStart;
        /* Decode separator char in boundary */
        while ( lptszPtr < lptszEnd )
        {
            if ( *lptszPtr == Replace )
            {
                *lptszPtr = Separator;
            }
            else if ( *lptszPtr == Boundary )
            {
                memcpy( lptszPtr, lptszPtr + 1, ( lptszTail - lptszPtr ) * sizeof( char ) );
                lptszEnd--;
                lptszTail--;
            }
            lptszPtr++;
        }

        StackPushU( List, StrToHexA( lptszStart ) );
    }
}

void ParseCommandLineExA( PCOMMON_STACK List, LPCSTR String, char Separator, char Boundary, char Replace )
{
    LPCSTR lptszStart;

    lptszStart = String;
    if ( *lptszStart == Boundary )
    {
        lptszStart = strchr( lptszStart + 1, Boundary );
        if ( lptszStart )
            lptszStart++;
    }
    else
    {
        while ( *lptszStart && *lptszStart != Separator )
            lptszStart++;
    }

    ParseStringExA( List, lptszStart, Separator, Boundary, Replace );
}

void ParseStringExW( PCOMMON_STACK List, LPCWSTR String, WCHAR Separator, WCHAR Boundary, WCHAR Replace )
{
    LPWSTR lptszHead;
    LPWSTR lptszTail;
    LPWSTR lptszStart;
    LPWSTR lptszEnd;
    LPWSTR lptszPtr;
    WCHAR Buffer[BUFFER_SIZE];

    wcsncpy( Buffer, String, SIZE_OF_ARRAY( Buffer ) );
    Buffer[SIZE_OF_ARRAY( Buffer ) - 1] = _T( '\0' );

    lptszHead = Buffer;
    lptszTail = lptszHead + wcslen( lptszHead );

    /* Encode separator char in boundary */
    lptszStart = lptszHead;
    while ( lptszStart < lptszTail )
    {
        if ( *lptszStart == Boundary )
        {
            lptszStart++;
            while ( lptszStart < lptszTail )
            {
                if ( *lptszStart == Boundary )
                    break;

                if ( *lptszStart == Separator )
                    *lptszStart = Replace;
                lptszStart++;
            }
        }
        lptszStart++;
    }

    for ( lptszStart = lptszHead; lptszStart < lptszTail; lptszStart = lptszEnd + 1 )
    {
        while ( *lptszStart == Separator && lptszStart < lptszTail )
            lptszStart++;

        if ( lptszStart == lptszTail )
            break;

        lptszEnd = lptszStart;
        while ( lptszEnd < lptszTail )
        {
            if ( *lptszEnd == Separator )
                break;
            lptszEnd++;
        }
        if ( lptszEnd < lptszTail )
            *lptszEnd = L'\0';

        lptszPtr = lptszStart;
        /* Decode separator char in boundary */
        while ( lptszPtr < lptszEnd )
        {
            if ( *lptszPtr == Replace )
            {
                *lptszPtr = Separator;
            }
            else if ( *lptszPtr == Boundary )
            {
                memcpy( lptszPtr, lptszPtr + 1, ( lptszTail - lptszPtr ) * sizeof( WCHAR ) );
                lptszEnd--;
                lptszTail--;
            }
            lptszPtr++;
        }

        StackPush( List, lptszStart, ROUND_SIZE( ( lptszEnd - lptszStart + 1 ) * sizeof( WCHAR ) ) );
    }
}

void ParseStringDataExW( PCOMMON_STACK_U List, LPCWSTR String, WCHAR Separator, WCHAR Boundary, WCHAR Replace )
{
    LPWSTR lptszHead;
    LPWSTR lptszTail;
    LPWSTR lptszStart;
    LPWSTR lptszEnd;
    LPWSTR lptszPtr;
    WCHAR Buffer[BUFFER_SIZE];

    wcsncpy( Buffer, String, SIZE_OF_ARRAY( Buffer ) );
    Buffer[SIZE_OF_ARRAY( Buffer ) - 1] = _T( '\0' );

    lptszHead = Buffer;
    lptszTail = lptszHead + wcslen( lptszHead );

    /* Encode separator char in boundary */
    lptszStart = lptszHead;
    while ( lptszStart < lptszTail )
    {
        if ( *lptszStart == Boundary )
        {
            lptszStart++;
            while ( lptszStart < lptszTail )
            {
                if ( *lptszStart == Boundary )
                    break;

                if ( *lptszStart == Separator )
                    *lptszStart = Replace;
                lptszStart++;
            }
        }
        lptszStart++;
    }

    for ( lptszStart = lptszHead; lptszStart < lptszTail; lptszStart = lptszEnd + 1 )
    {
        while ( *lptszStart == Separator && lptszStart < lptszTail )
            lptszStart++;

        if ( lptszStart == lptszTail )
            break;

        lptszEnd = lptszStart;
        while ( lptszEnd < lptszTail )
        {
            if ( *lptszEnd == Separator )
                break;
            lptszEnd++;
        }
        if ( lptszEnd < lptszTail )
            *lptszEnd = L'\0';

        lptszPtr = lptszStart;
        /* Decode separator char in boundary */
        while ( lptszPtr < lptszEnd )
        {
            if ( *lptszPtr == Replace )
            {
                *lptszPtr = Separator;
            }
            else if ( *lptszPtr == Boundary )
            {
                memcpy( lptszPtr, lptszPtr + 1, ( lptszTail - lptszPtr ) * sizeof( WCHAR ) );
                lptszEnd--;
                lptszTail--;
            }
            lptszPtr++;
        }

        StackPushU( List, StrToHexW( lptszStart ) );
    }
}

void ParseCommandLineExW( PCOMMON_STACK List, LPCWSTR String, WCHAR Separator, WCHAR Boundary, WCHAR Replace )
{
    LPCWSTR lptszStart;

    lptszStart = String;
    if ( *lptszStart == Boundary )
    {
        lptszStart = wcschr( lptszStart + 1, Boundary );
        if ( lptszStart )
            lptszStart++;
    }
    else
    {
        while ( *lptszStart && *lptszStart != Separator )
            lptszStart++;
    }

    ParseStringExW( List, lptszStart, Separator, Boundary, Replace );
}