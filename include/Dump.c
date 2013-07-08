/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   Dump.c
//  Version     :   1.0
//  Creator     :   RM
//  Create Date :   2006-01-01
//  Comment     :
//
///////////////////////////////////////////////////////////////////////////////
*/

#pragma warning( disable : 4005 )
#pragma warning( disable : 4115 )
#pragma warning( disable : 4127 )
#pragma warning( disable : 4201 )
#pragma warning( disable : 4214 )
#pragma warning( disable : 4706 )

#include < windows.h >
#include < stdio.h >
#include < tchar.h >
#include "Dump.h"
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
UCHAR g_InetNtoa[256];

/* Hex char set */
const TCHAR g_aszUpperCharSet[] = _T( "0123456789ABCDEF" );
const char g_aszUpperCharSetA[] = "0123456789ABCDEF";
const WCHAR g_aszUpperCharSetW[] = L"0123456789ABCDEF";

const TCHAR g_aszLowCharSet[] = _T( "0123456789abcdef" );
const char g_aszLowCharSetA[] = "0123456789abcdef";
const WCHAR g_aszLowCharSetW[] = L"0123456789abcdef";

/*
// This preinitialized array defines the strings to be used for
// _inet_ntoa. The index of each row corresponds to the value for a byte
// IpAddress an IP address. The first three bytes of each row are the
// char / string value for the byte, and the fourth byte in each row is
// the length of the string required for the byte.  This approach
// allows a fast implementation with no jumps.
*/
BYTE NToACharStrings[][4] = {
    '0', 'x', 'x', 1,
    '1', 'x', 'x', 1,
    '2', 'x', 'x', 1,
    '3', 'x', 'x', 1,
    '4', 'x', 'x', 1,
    '5', 'x', 'x', 1,
    '6', 'x', 'x', 1,
    '7', 'x', 'x', 1,
    '8', 'x', 'x', 1,
    '9', 'x', 'x', 1,
    '1', '0', 'x', 2,
    '1', '1', 'x', 2,
    '1', '2', 'x', 2,
    '1', '3', 'x', 2,
    '1', '4', 'x', 2,
    '1', '5', 'x', 2,
    '1', '6', 'x', 2,
    '1', '7', 'x', 2,
    '1', '8', 'x', 2,
    '1', '9', 'x', 2,
    '2', '0', 'x', 2,
    '2', '1', 'x', 2,
    '2', '2', 'x', 2,
    '2', '3', 'x', 2,
    '2', '4', 'x', 2,
    '2', '5', 'x', 2,
    '2', '6', 'x', 2,
    '2', '7', 'x', 2,
    '2', '8', 'x', 2,
    '2', '9', 'x', 2,
    '3', '0', 'x', 2,
    '3', '1', 'x', 2,
    '3', '2', 'x', 2,
    '3', '3', 'x', 2,
    '3', '4', 'x', 2,
    '3', '5', 'x', 2,
    '3', '6', 'x', 2,
    '3', '7', 'x', 2,
    '3', '8', 'x', 2,
    '3', '9', 'x', 2,
    '4', '0', 'x', 2,
    '4', '1', 'x', 2,
    '4', '2', 'x', 2,
    '4', '3', 'x', 2,
    '4', '4', 'x', 2,
    '4', '5', 'x', 2,
    '4', '6', 'x', 2,
    '4', '7', 'x', 2,
    '4', '8', 'x', 2,
    '4', '9', 'x', 2,
    '5', '0', 'x', 2,
    '5', '1', 'x', 2,
    '5', '2', 'x', 2,
    '5', '3', 'x', 2,
    '5', '4', 'x', 2,
    '5', '5', 'x', 2,
    '5', '6', 'x', 2,
    '5', '7', 'x', 2,
    '5', '8', 'x', 2,
    '5', '9', 'x', 2,
    '6', '0', 'x', 2,
    '6', '1', 'x', 2,
    '6', '2', 'x', 2,
    '6', '3', 'x', 2,
    '6', '4', 'x', 2,
    '6', '5', 'x', 2,
    '6', '6', 'x', 2,
    '6', '7', 'x', 2,
    '6', '8', 'x', 2,
    '6', '9', 'x', 2,
    '7', '0', 'x', 2,
    '7', '1', 'x', 2,
    '7', '2', 'x', 2,
    '7', '3', 'x', 2,
    '7', '4', 'x', 2,
    '7', '5', 'x', 2,
    '7', '6', 'x', 2,
    '7', '7', 'x', 2,
    '7', '8', 'x', 2,
    '7', '9', 'x', 2,
    '8', '0', 'x', 2,
    '8', '1', 'x', 2,
    '8', '2', 'x', 2,
    '8', '3', 'x', 2,
    '8', '4', 'x', 2,
    '8', '5', 'x', 2,
    '8', '6', 'x', 2,
    '8', '7', 'x', 2,
    '8', '8', 'x', 2,
    '8', '9', 'x', 2,
    '9', '0', 'x', 2,
    '9', '1', 'x', 2,
    '9', '2', 'x', 2,
    '9', '3', 'x', 2,
    '9', '4', 'x', 2,
    '9', '5', 'x', 2,
    '9', '6', 'x', 2,
    '9', '7', 'x', 2,
    '9', '8', 'x', 2,
    '9', '9', 'x', 2,
    '1', '0', '0', 3,
    '1', '0', '1', 3,
    '1', '0', '2', 3,
    '1', '0', '3', 3,
    '1', '0', '4', 3,
    '1', '0', '5', 3,
    '1', '0', '6', 3,
    '1', '0', '7', 3,
    '1', '0', '8', 3,
    '1', '0', '9', 3,
    '1', '1', '0', 3,
    '1', '1', '1', 3,
    '1', '1', '2', 3,
    '1', '1', '3', 3,
    '1', '1', '4', 3,
    '1', '1', '5', 3,
    '1', '1', '6', 3,
    '1', '1', '7', 3,
    '1', '1', '8', 3,
    '1', '1', '9', 3,
    '1', '2', '0', 3,
    '1', '2', '1', 3,
    '1', '2', '2', 3,
    '1', '2', '3', 3,
    '1', '2', '4', 3,
    '1', '2', '5', 3,
    '1', '2', '6', 3,
    '1', '2', '7', 3,
    '1', '2', '8', 3,
    '1', '2', '9', 3,
    '1', '3', '0', 3,
    '1', '3', '1', 3,
    '1', '3', '2', 3,
    '1', '3', '3', 3,
    '1', '3', '4', 3,
    '1', '3', '5', 3,
    '1', '3', '6', 3,
    '1', '3', '7', 3,
    '1', '3', '8', 3,
    '1', '3', '9', 3,
    '1', '4', '0', 3,
    '1', '4', '1', 3,
    '1', '4', '2', 3,
    '1', '4', '3', 3,
    '1', '4', '4', 3,
    '1', '4', '5', 3,
    '1', '4', '6', 3,
    '1', '4', '7', 3,
    '1', '4', '8', 3,
    '1', '4', '9', 3,
    '1', '5', '0', 3,
    '1', '5', '1', 3,
    '1', '5', '2', 3,
    '1', '5', '3', 3,
    '1', '5', '4', 3,
    '1', '5', '5', 3,
    '1', '5', '6', 3,
    '1', '5', '7', 3,
    '1', '5', '8', 3,
    '1', '5', '9', 3,
    '1', '6', '0', 3,
    '1', '6', '1', 3,
    '1', '6', '2', 3,
    '1', '6', '3', 3,
    '1', '6', '4', 3,
    '1', '6', '5', 3,
    '1', '6', '6', 3,
    '1', '6', '7', 3,
    '1', '6', '8', 3,
    '1', '6', '9', 3,
    '1', '7', '0', 3,
    '1', '7', '1', 3,
    '1', '7', '2', 3,
    '1', '7', '3', 3,
    '1', '7', '4', 3,
    '1', '7', '5', 3,
    '1', '7', '6', 3,
    '1', '7', '7', 3,
    '1', '7', '8', 3,
    '1', '7', '9', 3,
    '1', '8', '0', 3,
    '1', '8', '1', 3,
    '1', '8', '2', 3,
    '1', '8', '3', 3,
    '1', '8', '4', 3,
    '1', '8', '5', 3,
    '1', '8', '6', 3,
    '1', '8', '7', 3,
    '1', '8', '8', 3,
    '1', '8', '9', 3,
    '1', '9', '0', 3,
    '1', '9', '1', 3,
    '1', '9', '2', 3,
    '1', '9', '3', 3,
    '1', '9', '4', 3,
    '1', '9', '5', 3,
    '1', '9', '6', 3,
    '1', '9', '7', 3,
    '1', '9', '8', 3,
    '1', '9', '9', 3,
    '2', '0', '0', 3,
    '2', '0', '1', 3,
    '2', '0', '2', 3,
    '2', '0', '3', 3,
    '2', '0', '4', 3,
    '2', '0', '5', 3,
    '2', '0', '6', 3,
    '2', '0', '7', 3,
    '2', '0', '8', 3,
    '2', '0', '9', 3,
    '2', '1', '0', 3,
    '2', '1', '1', 3,
    '2', '1', '2', 3,
    '2', '1', '3', 3,
    '2', '1', '4', 3,
    '2', '1', '5', 3,
    '2', '1', '6', 3,
    '2', '1', '7', 3,
    '2', '1', '8', 3,
    '2', '1', '9', 3,
    '2', '2', '0', 3,
    '2', '2', '1', 3,
    '2', '2', '2', 3,
    '2', '2', '3', 3,
    '2', '2', '4', 3,
    '2', '2', '5', 3,
    '2', '2', '6', 3,
    '2', '2', '7', 3,
    '2', '2', '8', 3,
    '2', '2', '9', 3,
    '2', '3', '0', 3,
    '2', '3', '1', 3,
    '2', '3', '2', 3,
    '2', '3', '3', 3,
    '2', '3', '4', 3,
    '2', '3', '5', 3,
    '2', '3', '6', 3,
    '2', '3', '7', 3,
    '2', '3', '8', 3,
    '2', '3', '9', 3,
    '2', '4', '0', 3,
    '2', '4', '1', 3,
    '2', '4', '2', 3,
    '2', '4', '3', 3,
    '2', '4', '4', 3,
    '2', '4', '5', 3,
    '2', '4', '6', 3,
    '2', '4', '7', 3,
    '2', '4', '8', 3,
    '2', '4', '9', 3,
    '2', '5', '0', 3,
    '2', '5', '1', 3,
    '2', '5', '2', 3,
    '2', '5', '3', 3,
    '2', '5', '4', 3,
    '2', '5', '5', 3
};

/*
///////////////////////////////////////////////////////////////////////////////
// F U N C T I O N S
///////////////////////////////////////////////////////////////////////////////
*/

/*
///////////////////////////////////////////////////////////////////////////////
// _inet_ntoa
///////////////////////////////////////////////////////////////////////////////
*/
char *PASCAL _inet_ntoa(
    IN struct in_addr IpAddress
    )
{
    PUCHAR Ptr;
    PUCHAR Buffer;
    PUCHAR Out;
    /*
    // A number of applications apparently depend on calling _inet_ntoa( )
    // without first calling WSAStartup( ). Because of this, we must perform
    // our own explicit thread initialization check here.
    */
    Buffer = g_InetNtoa;
    Out = Buffer;
    /*
    // In an unrolled loop, calculate the string value for each of the four
    // bytes IpAddress an IP address.  Note that for values less than 100 we will
    // do one or two extra assignments, but we save a test / jump with this
    // algorithm.
    */
    Ptr = ( PUCHAR ) &IpAddress;

    *Out = NToACharStrings[*Ptr] [0];
    *( Out + 1 ) = NToACharStrings[ *Ptr] [1];
    *( Out + 2 ) = NToACharStrings[ *Ptr] [2];
    Out += NToACharStrings[*Ptr] [3];
    *Out++ = '.';

    Ptr++;
    *Out = NToACharStrings[*Ptr] [0];
    *( Out + 1 ) = NToACharStrings[ *Ptr] [1];
    *( Out + 2 ) = NToACharStrings[ *Ptr] [2];
    Out += NToACharStrings[*Ptr] [3];
    *Out++ = '.';

    Ptr++;
    *Out = NToACharStrings[*Ptr] [0];
    *( Out + 1 ) = NToACharStrings[ *Ptr] [1];
    *( Out + 2 ) = NToACharStrings[ *Ptr] [2];
    Out += NToACharStrings[*Ptr] [3];
    *Out++ = '.';

    Ptr++;
    *Out = NToACharStrings[*Ptr] [0];
    *( Out + 1 ) = NToACharStrings[*Ptr] [1];
    *( Out + 2 ) = NToACharStrings[*Ptr] [2];
    Out += NToACharStrings[*Ptr] [3];
    *Out = '\0';

    return( char* ) ( Buffer );
}

/*
///////////////////////////////////////////////////////////////////////////////
// _ntohl
///////////////////////////////////////////////////////////////////////////////
*/
unsigned long _ntohl( unsigned long In )
{
    return( ( In & 0x000000FF ) << 24 ) |
        ( ( In & 0x0000FF00 ) << 8 ) |
        ( ( In & 0x00FF0000 ) >> 8 ) |
        ( ( In & 0xFF000000 ) >> 24 );
}

/*
///////////////////////////////////////////////////////////////////////////////
// _htonl
///////////////////////////////////////////////////////////////////////////////
*/
unsigned long _htonl( unsigned long In )
{
    return( ( In & 0x000000FF ) << 24 ) |
        ( ( In & 0x0000FF00 ) << 8 ) |
        ( ( In & 0x00FF0000 ) >> 8 ) |
        ( ( In & 0xFF000000 ) >> 24 );
}

/*
///////////////////////////////////////////////////////////////////////////////
// _ntohs
///////////////////////////////////////////////////////////////////////////////
*/
unsigned short _ntohs( unsigned short In )
{
    register unsigned short InHigh;
    register unsigned short InLow;

    InHigh = InLow = In;
    InHigh &= 0xFF;
    InHigh <<= 8;
    InLow &= 0xFF00;
    InLow >>= 8;
    InHigh |= InLow;

    return InHigh;
}

/*
///////////////////////////////////////////////////////////////////////////////
// _htons
///////////////////////////////////////////////////////////////////////////////
*/
unsigned short _htons( unsigned short In )
{
    register unsigned short InHigh;
    register unsigned short InLow;

    InHigh = InLow = In;
    InHigh &= 0xFF;
    InHigh <<= 8;
    InLow &= 0xFF00;
    InLow >>= 8;
    InHigh |= InLow;

    return InHigh;
}

/*
///////////////////////////////////////////////////////////////////////////////
// HexToChar
///////////////////////////////////////////////////////////////////////////////
*/
TCHAR HexToChar( BYTE In )
{
    if ( In < 0x10 )
        return( TCHAR )g_aszUpperCharSet[In];
    else
        return( TCHAR )0;
}

char HexToCharA( BYTE In )
{
    if ( In < 0x10 )
        return( char )g_aszUpperCharSetA[In];
    else
        return( char )0;
}

WCHAR HexToCharW( BYTE In )
{
    if ( In < 0x10 )
        return( WCHAR )g_aszUpperCharSetW[In];
    else
        return( WCHAR )0;
}

/*
///////////////////////////////////////////////////////////////////////////////
// CharToHex
///////////////////////////////////////////////////////////////////////////////
*/
BYTE CharToHex( TCHAR In )
{
    if ( In >= _T( '0' ) && In <= _T( '9' ) )
        return( BYTE ) ( In - _T( '0' ) );
    else if ( In >= _T( 'A' ) && In <= _T( 'F' ) )
        return( BYTE ) ( In - _T( 'A' ) + 10 );
    else if ( In >= _T( 'a' ) && In <= _T( 'f' ) )
        return( BYTE ) ( In - _T( 'a' ) + 10 );
    else
        return( BYTE )INVALID_BYTE;
}

BYTE CharToHexA( char In )
{
    if ( In >= '0' && In <= '9' )
        return( BYTE ) ( In - '0' );
    else if ( In >= 'A' && In <= 'F' )
        return( BYTE ) ( In - 'A'+ 10 );
    else if ( In >= 'a' && In <= 'f' )
        return( BYTE ) ( In - 'a'+ 10 );
    else
        return( BYTE )INVALID_BYTE;
}

BYTE CharToHexW( WCHAR In )
{
    if ( In >= L'0' && In <= L'9' )
        return( BYTE ) ( In - L'0' );
    else if ( In >= L'A' && In <= L'F' )
        return( BYTE ) ( In - L'A'+ 10 );
    else if ( In >= L'a' && In <= L'f' )
        return( BYTE ) ( In - L'a'+ 10 );
    else
        return( BYTE )INVALID_BYTE;
}

/*
///////////////////////////////////////////////////////////////////////////////
// StrToData
///////////////////////////////////////////////////////////////////////////////
*/
ULONG StrToData( TCHAR *DataString, UINT Mutiply )
{
    register ULONG RetCode;
    register TCHAR *Ptr;
    register TCHAR Data;
    register BYTE Digit;

    RetCode = 0;
    for ( Ptr = DataString; Data = *Ptr; Ptr++ )
    {
        Digit = CharToHex( Data );
        if ( Digit == INVALID_BYTE )
            break;

        RetCode *= Mutiply;
        RetCode += Digit;
    }

    return RetCode;
}

ULONG StrToDataA( char *DataString, UINT Mutiply )
{
    register ULONG RetCode;
    register char *Ptr;
    register char Data;
    register BYTE Digit;

    RetCode = 0;
    for ( Ptr = DataString; Data = *Ptr; Ptr++ )
    {
        Digit = CharToHexA( Data );
        if ( Digit == INVALID_BYTE )
            break;

        RetCode *= Mutiply;
        RetCode += Digit;
    }

    return RetCode;
}

ULONG StrToDataW( WCHAR *DataString, UINT Mutiply )
{
    register ULONG RetCode;
    register WCHAR *Ptr;
    register WCHAR Data;
    register BYTE Digit;

    RetCode = 0;
    for ( Ptr = DataString; Data = *Ptr; Ptr++ )
    {
        Digit = CharToHexW( Data );
        if ( Digit == INVALID_BYTE )
            break;

        RetCode *= Mutiply;
        RetCode += Digit;
    }

    return RetCode;
}

/*
///////////////////////////////////////////////////////////////////////////////
// StrToHex
///////////////////////////////////////////////////////////////////////////////
*/
ULONG StrToHex( TCHAR *DataString )
{
    register ULONG RetCode;
    register TCHAR *Ptr;
    register TCHAR Data;
    register BYTE Digit;

    RetCode = 0;
    for ( Ptr = DataString; Data = *Ptr; Ptr++ )
    {
        Digit = CharToHex( Data );
        if ( Digit == INVALID_BYTE )
            break;

        RetCode <<= 4;
        RetCode += Digit;
    }

    return RetCode;
}

ULONG StrToHexA( char *DataString )
{
    register ULONG RetCode;
    register char *Ptr;
    register char Data;
    register BYTE Digit;

    RetCode = 0;
    for ( Ptr = DataString; Data = *Ptr; Ptr++ )
    {
        Digit = CharToHexA( Data );
        if ( Digit == INVALID_BYTE )
            break;

        RetCode <<= 4;
        RetCode += Digit;
    }

    return RetCode;
}

ULONG StrToHexW( WCHAR *DataString )
{
    register ULONG RetCode;
    register WCHAR *Ptr;
    register WCHAR Data;
    register BYTE Digit;

    RetCode = 0;
    for ( Ptr = DataString; Data = *Ptr; Ptr++ )
    {
        Digit = CharToHexW( Data );
        if ( Digit == INVALID_BYTE )
            break;

        RetCode <<= 4;
        RetCode += Digit;
    }

    return RetCode;
}

/*
///////////////////////////////////////////////////////////////////////////////
// DumpMem
///////////////////////////////////////////////////////////////////////////////
*/
ULONG DumpMem( const void *lpBuffer, ULONG Size )
{
    ULONG Iter;
    ULONG AddressS;
    ULONG AddressE;
    ULONG Read;
    ULONG Left;
    ULONG MemAddress;
    const ULONG BytesPerLine = 16;
    PBYTE BufferIn;
    LPSTR lpaszOut;
    CHAR aszOut[256];

    if ( lpBuffer == NULL )
        return FALSE;

    if ( Size == 0 )
        return TRUE;

    MemAddress = ( ULONG )lpBuffer;
    while ( Size )
    {
        lpaszOut = aszOut;
        if ( Size > BytesPerLine )
            Read = BytesPerLine;
        else
            Read = Size;

        AddressS = MemAddress - MemAddress % BytesPerLine;
        AddressE = AddressS + BytesPerLine;
        Left = Read;
        BufferIn = ( PBYTE )AddressS;
        lpaszOut += sprintf( lpaszOut, ( "%08X " ), AddressS );
        for ( Iter = 0; Iter < BytesPerLine; Iter++, AddressS++ )
        {
            if ( ( Iter & 3 ) == 0 && Iter != 0 )
                *lpaszOut++ = ( '-' );
            else
                *lpaszOut++ = ( ' ' );

            if ( AddressS < MemAddress )
            {
                *lpaszOut++ = ( ' ' );
                *lpaszOut++ = ( ' ' );
            }
            else if ( !Left )
            {
                *lpaszOut++ = ( '?' );
                *lpaszOut++ = ( '?' );
            }
            else
            {
                *lpaszOut++ = g_aszUpperCharSetA[( BufferIn[Iter] & 0xF0 ) >> 4];
                *lpaszOut++ = g_aszUpperCharSetA[BufferIn[Iter] & 0x0F];
                Left--;
            }
        }
        *lpaszOut++ = ( ' ' );

        Left = Read;
        AddressS = MemAddress - MemAddress % BytesPerLine;
        AddressE = AddressS + BytesPerLine;
        for ( Iter = 0; Iter < BytesPerLine; Iter++, AddressS++ )
        {
            if ( AddressS < MemAddress )
            {
                *lpaszOut++ = ( ' ' );
            }
            else if ( !Left )
            {
                *lpaszOut++ = ( '?' );
            }
            else
            {
                if ( BufferIn[Iter] >= 0x20 && BufferIn[Iter] < 0x80 )
                    *lpaszOut++ = BufferIn[Iter];
                else
                    *lpaszOut++ = ( '.' );
                Left--;
            }
        }
        *lpaszOut++ = ( '\0' );
        ADD_LOG_LRA( aszOut );

        Size -= min( Size, AddressS - MemAddress );
        MemAddress = AddressS;
    }

    return TRUE;
}

/*
///////////////////////////////////////////////////////////////////////////////
// DumpProcessMem
///////////////////////////////////////////////////////////////////////////////
*/
ULONG DumpProcessMem( HANDLE hProcess, ULONG Address, ULONG Size )
{
    ULONG Iter;
    ULONG AddressS;
    ULONG AddressE;
    ULONG Read;
    ULONG Left;
    ULONG BufferSize;
    ULONG BufferLeft;
    ULONG MemAddress;
    const ULONG BytesPerLine = 16;
    PBYTE BufferIn;
    LPSTR lpaszOut;
    CHAR aszBuffer[256 * 16];
    CHAR aszOut[256];

    if ( Size == 0 )
        return TRUE;

    BufferSize = min( sizeof( aszBuffer ), Size + Address % BytesPerLine );
    BufferLeft = 0;
    BufferIn = ( LPBYTE )aszBuffer;
    MemAddress = Address;
    while ( Size )
    {
        lpaszOut = aszOut;
        if ( Size > BytesPerLine )
            Read = BytesPerLine;
        else
            Read = Size;

        AddressS = MemAddress - MemAddress % BytesPerLine;
        AddressE = AddressS + BytesPerLine;
        Left = Read;
        if ( BufferLeft == 0 )
        {
            if ( !ReadProcessMemory( hProcess, ( LPVOID )AddressS, aszBuffer, BufferSize, &BufferLeft ) )
                return FALSE;
            BufferIn = ( LPBYTE )aszBuffer;
            BufferLeft -= MemAddress % BytesPerLine;
        }

        lpaszOut += sprintf( lpaszOut, ( "%08X " ), AddressS );
        for ( Iter = 0; Iter < BytesPerLine; Iter++, AddressS++ )
        {
            if ( ( Iter & 3 ) == 0 && Iter != 0 )
                *lpaszOut++ = ( '-' );
            else
                *lpaszOut++ = ( ' ' );

            if ( AddressS < MemAddress )
            {
                *lpaszOut++ = ( ' ' );
                *lpaszOut++ = ( ' ' );
            }
            else if ( !Left )
            {
                *lpaszOut++ = ( '?' );
                *lpaszOut++ = ( '?' );
            }
            else
            {
                *lpaszOut++ = g_aszUpperCharSetA[( BufferIn[Iter] & 0xF0 ) >> 4];
                *lpaszOut++ = g_aszUpperCharSetA[BufferIn[Iter] & 0x0F];
                Left--;
            }
        }
        *lpaszOut++ = ( ' ' );

        Left = Read;
        AddressS = MemAddress - MemAddress % BytesPerLine;
        AddressE = AddressS + BytesPerLine;
        for ( Iter = 0; Iter < BytesPerLine; Iter++, AddressS++ )
        {
            if ( AddressS < MemAddress )
            {
                *lpaszOut++ = ( ' ' );
            }
            else if ( !Left )
            {
                *lpaszOut++ = ( '?' );
            }
            else
            {
                if ( BufferIn[Iter] >= 0x20 && BufferIn[Iter] < 0x80 )
                    *lpaszOut++ = BufferIn[Iter];
                else
                    *lpaszOut++ = ( '.' );
                Left--;
            }
        }
        *lpaszOut++ = ( '\0' );
        ADD_LOG_LRA( aszOut );

        Size -= min( Size, AddressS - MemAddress );
        MemAddress = AddressS;
        BufferIn += Read;
        BufferLeft -= Read;
    }

    return TRUE;
}

/*
///////////////////////////////////////////////////////////////////////////////
// DumpDebugEvent
///////////////////////////////////////////////////////////////////////////////
*/
ULONG DumpDebugEvent( DEBUG_EVENT *DbgEvent )
{
    if ( DbgEvent == NULL )
        return FALSE;

    switch ( DbgEvent->dwDebugEventCode )
    {
    case EXCEPTION_DEBUG_EVENT :
        ADD_DEBUG_LOG_LR( _T( "EXCEPTION_DEBUG_EVENT" ) );
        break;

    case CREATE_THREAD_DEBUG_EVENT :
        ADD_DEBUG_LOG_LR( _T( "CREATE_THREAD_DEBUG_EVENT" ) );
        break;

    case CREATE_PROCESS_DEBUG_EVENT :
        ADD_DEBUG_LOG_LR( _T( "CREATE_PROCESS_DEBUG_EVENT" ) );
        break;

    case EXIT_THREAD_DEBUG_EVENT :
        ADD_DEBUG_LOG_LR( _T( "EXIT_THREAD_DEBUG_EVENT" ) );
        break;

    case EXIT_PROCESS_DEBUG_EVENT :
        ADD_DEBUG_LOG_LR( _T( "EXIT_PROCESS_DEBUG_EVENT" ) );
        break;

    case LOAD_DLL_DEBUG_EVENT :
        ADD_DEBUG_LOG_LR( _T( "LOAD_DLL_DEBUG_EVENT" ) );
        break;

    case UNLOAD_DLL_DEBUG_EVENT :
        ADD_DEBUG_LOG_LR( _T( "UNLOAD_DLL_DEBUG_EVENT" ) );
        break;

    case OUTPUT_DEBUG_STRING_EVENT :
        ADD_DEBUG_LOG_LR( _T( "OUTPUT_DEBUG_STRING_EVENT" ) );
        break;

    case RIP_EVENT :
        ADD_DEBUG_LOG_LR( _T( "RIP_EVENT" ) );
        break;

    default :
        ADD_DEBUG_LOG_LR( _T( "Unknown" ) );
        break;
    }

    ADD_DEBUG_LOG_LR( _T( "PID:TID=%08X:%08X" ), DbgEvent->dwProcessId, DbgEvent->dwThreadId );
    ADD_DEBUG_LOG_LR( _T( "ExceptionAddress[ %08X ]" ), DbgEvent->u.Exception.ExceptionRecord.ExceptionAddress );

    return TRUE;
}

/*
///////////////////////////////////////////////////////////////////////////////
// DumpThreadContext
///////////////////////////////////////////////////////////////////////////////
*/
ULONG DumpThreadContext( CONTEXT *ThreadCtx )
{
    if ( ThreadCtx == NULL )
        return FALSE;

#ifndef _WIN32_WCE
    ADD_DEBUG_LOG_LR( _T( "[ Flags ]" ) );
    ADD_DEBUG_LOG_LR( _T( "EFlags=%08X" ), ThreadCtx->EFlags );
    ADD_DEBUG_LOG_LR( _T( "ContextFlags=%08X" ), ThreadCtx->ContextFlags );

    ADD_DEBUG_LOG_LR( _T( "[ Regs ]" ) );
    ADD_DEBUG_LOG_LR( _T( "CS:EIP=%08X:%08X" ), ThreadCtx->SegCs, ThreadCtx->Eip );
    ADD_DEBUG_LOG_LR( _T( "SS:ESP=%08X:%08X" ), ThreadCtx->SegSs, ThreadCtx->Esp );
    ADD_DEBUG_LOG_LR( _T( "SS:EBP=%08X:%08X" ), ThreadCtx->SegSs, ThreadCtx->Ebp );
    ADD_DEBUG_LOG_LR( _T( "DS:ESI=%08X:%08X" ), ThreadCtx->SegDs, ThreadCtx->Esi );
    ADD_DEBUG_LOG_LR( _T( "ES:EDI=%08X:%08X" ), ThreadCtx->SegEs, ThreadCtx->Edi );
    ADD_DEBUG_LOG_LR( _T( "FS=%08X" ), ThreadCtx->SegFs );
    ADD_DEBUG_LOG_LR( _T( "GS=%08X" ), ThreadCtx->SegGs );
    ADD_DEBUG_LOG_LR( _T( "[ Common Regs ]" ) );
    ADD_DEBUG_LOG_LR( _T( "EAX=%08X" ), ThreadCtx->Eax );
    ADD_DEBUG_LOG_LR( _T( "EBX=%08X" ), ThreadCtx->Ebx );
    ADD_DEBUG_LOG_LR( _T( "ECX=%08X" ), ThreadCtx->Ecx );
    ADD_DEBUG_LOG_LR( _T( "EDX=%08X" ), ThreadCtx->Edx );
    ADD_DEBUG_LOG_LR( _T( "[ DrX Regs ]" ) );
    ADD_DEBUG_LOG_LR( _T( "Dr0=%08X" ), ThreadCtx->Dr0 );
    ADD_DEBUG_LOG_LR( _T( "Dr1=%08X" ), ThreadCtx->Dr1 );
    ADD_DEBUG_LOG_LR( _T( "Dr2=%08X" ), ThreadCtx->Dr2 );
    ADD_DEBUG_LOG_LR( _T( "Dr3=%08X" ), ThreadCtx->Dr3 );
    ADD_DEBUG_LOG_LR( _T( "Dr6=%08X" ), ThreadCtx->Dr6 );
    ADD_DEBUG_LOG_LR( _T( "Dr7=%08X" ), ThreadCtx->Dr7 );
#else
    ADD_DEBUG_LOG_LR( _T( "[ Flags ]" ) );
    ADD_DEBUG_LOG_LR( _T( "[ ContextFlags=%08X ]" ), ThreadCtx->ContextFlags );
    ADD_DEBUG_LOG_LR( _T( "[ R0=%08X ]" ), ThreadCtx->R0 );
    ADD_DEBUG_LOG_LR( _T( "[ R1=%08X ]" ), ThreadCtx->R1 );
    ADD_DEBUG_LOG_LR( _T( "[ R2=%08X ]" ), ThreadCtx->R2 );
    ADD_DEBUG_LOG_LR( _T( "[ R3=%08X ]" ), ThreadCtx->R3 );
    ADD_DEBUG_LOG_LR( _T( "[ R4=%08X ]" ), ThreadCtx->R4 );
    ADD_DEBUG_LOG_LR( _T( "[ R5=%08X ]" ), ThreadCtx->R5 );
    ADD_DEBUG_LOG_LR( _T( "[ R6=%08X ]" ), ThreadCtx->R6 );
    ADD_DEBUG_LOG_LR( _T( "[ R7=%08X ]" ), ThreadCtx->R7 );
    ADD_DEBUG_LOG_LR( _T( "[ R8=%08X ]" ), ThreadCtx->R8 );
    ADD_DEBUG_LOG_LR( _T( "[ R9=%08X ]" ), ThreadCtx->R9 );
    ADD_DEBUG_LOG_LR( _T( "[ R10=%08X ]" ), ThreadCtx->R10 );
    ADD_DEBUG_LOG_LR( _T( "[ R11=%08X ]" ), ThreadCtx->R11 );
    ADD_DEBUG_LOG_LR( _T( "[ R12=%08X ]" ), ThreadCtx->R12 );

    ADD_DEBUG_LOG_LR( _T( "[ Sp=%08X ]" ), ThreadCtx->Sp );
    ADD_DEBUG_LOG_LR( _T( "[ Lr=%08X ]" ), ThreadCtx->Lr );
    ADD_DEBUG_LOG_LR( _T( "[ Pc=%08X ]" ), ThreadCtx->Pc );
    ADD_DEBUG_LOG_LR( _T( "[ Psr=%08X ]" ), ThreadCtx->Psr );
    ADD_DEBUG_LOG_LR( _T( "[ Fpscr=%08X ]" ), ThreadCtx->Fpscr );
    ADD_DEBUG_LOG_LR( _T( "[ FpExc=%08X ]" ), ThreadCtx->FpExc );
#endif

    return TRUE;
}

/*
///////////////////////////////////////////////////////////////////////////////
// DumpIpHead
///////////////////////////////////////////////////////////////////////////////
*/
ULONG DumpIpHead( const void *Buffer, ULONG Size )
{
    PIP_HEAD IpHead;
    struct in_addr IpAddress;
    ULONG Length;

    ADD_DEBUG_LOG_LR( _T( "==>DumpIpHead" ) );

    if ( Buffer == NULL )
    {
        ADD_DEBUG_LOG_LR( _T( "( NULL )" ) );
        ADD_DEBUG_LOG_LR( _T( "DumpIpHead==>" ) );
        return FALSE;
    }

    IpHead = ( PIP_HEAD )Buffer;
    ADD_DEBUG_LOG_LR( _T( "HeaderLength_Version[ %X( %d ) ]" ),
        IpHead->HeaderLength_Version & 0xFF,
        IpHead->HeaderLength_Version & 0xFF
        );

    Length = _ntohs( IpHead->TotalLength );
    ADD_DEBUG_LOG_LR( _T( "TypeOfService[ %X ]" ), IpHead->TypeOfService );
    ADD_DEBUG_LOG_LR( _T( "TotalLength[ %X( %d ) ]" ), Length, Length );
    ADD_DEBUG_LOG_LR( _T( "ID[ %X ]" ), IpHead->Identification );
    ADD_DEBUG_LOG_LR( _T( "FragmentationFlags[ %X ]" ), IpHead->FragmentationFlags );
    ADD_DEBUG_LOG_LR( _T( "TTL[ %X( %d ) ]" ), IpHead->TTL, IpHead->TTL );
    ADD_DEBUG_LOG_LR( _T( "Protocol[ %X ]" ), IpHead->Protocol );
    ADD_DEBUG_LOG_LR( _T( "CheckSum[ %X ]" ), IpHead->CheckSum );

    IpAddress.S_un.S_addr = IpHead->SourceIp;
    ADD_DEBUG_LOG_LRA( ( "Source IP< %s >" ),
        _inet_ntoa( IpAddress )
        );

    IpAddress.S_un.S_addr = IpHead->DestinationIp;
    ADD_DEBUG_LOG_LRA( ( "Dest IP< %s >" ),
        _inet_ntoa( IpAddress )
        );

    if ( Size > sizeof( IP_HEAD ) )
        DumpMem( IpHead + 1, Size - sizeof( IP_HEAD ) );

    ADD_DEBUG_LOG_LR( _T( "DumpIpHead==>" ) );

    return TRUE;
}