/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   Base64X.c
//  Version     :   1.0
//  Creator     :   RM
//  Create Date :   2006-01-01
//  Comment     :
//
///////////////////////////////////////////////////////////////////////////////
*/

#include "Base64X.h"

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/
#define DEFAULT_END_TABLE_CHAR ( ( unsigned char )'\x7F' )
#define DEFAULT_PAD_CHAR ( ( unsigned char )'\xFF' )

#define BIT0( Data ) ( Data & 0xFF )
#define BIT1( Data ) ( ( Data >> 8 ) & 0xFF )
#define BIT2( Data ) ( ( Data >> 16 ) & 0xFF )
#define BIT3( Data ) ( ( Data >> 24 ) & 0xFF )

/*
///////////////////////////////////////////////////////////////////////////////
// S T R U C T U R E S
///////////////////////////////////////////////////////////////////////////////
*/

/*
///////////////////////////////////////////////////////////////////////////////
// F U N C T I O N S
///////////////////////////////////////////////////////////////////////////////
*/
__inline char GetB64Char( unsigned long Index )
{
    const char Base64Table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_\x7F";

    if ( Index >= 0 && Index < sizeof( Base64Table ) - 1 )
        return Base64Table[Index];

    return DEFAULT_PAD_CHAR;
}

__inline unsigned long GetB64Index( char Ch )
{
    unsigned long Index;

    if ( Ch >= 'A' && Ch <= 'Z' )
        Index = Ch - 'A';
    else if ( Ch >= 'a' && Ch <= 'z' )
        Index = Ch - 'a' + 26;
    else if ( Ch >= '0' && Ch <= '9' )
        Index = Ch - '0' + 52;
    else if ( Ch == '_' )
        Index = 62;
    else if ( Ch == DEFAULT_END_TABLE_CHAR )
        Index = 63;
    else if ( Ch == DEFAULT_PAD_CHAR )
        Index = 0;
    else
        Index = - 1;

    return Index;
}

unsigned long Base64EncodeX( char *OutputBuffer, const char *InputBuffer, unsigned long Length )
{
    register long Iter;
    long Count;
    long Left;
    unsigned long Dummy;
    register int Bit0;
    register int Bit1;
    register int Bit2;
    register int Bit3;
    register const char *InPtr;
    register char *OutPtr;

    InPtr = InputBuffer;
    OutPtr = OutputBuffer;
    Left = Length % 3;
    Count = Length - Left;
    for ( Iter = 0; Iter < Count; Iter += 3 )
    {
        Dummy = *( unsigned long * )InPtr;
        Bit0 = GetB64Char( ( BIT0( Dummy ) >> 2 ) & 0x3F );
        Bit1 = GetB64Char( ( BIT0( Dummy ) << 6 >> 2 | BIT1( Dummy ) >> 4 ) & 0x3F );
        Bit2 = GetB64Char( ( BIT1( Dummy ) << 4 >> 2 | BIT2( Dummy ) >> 6 ) & 0x3F );
        Bit3 = GetB64Char( ( BIT2( Dummy ) << 2 >> 2 ) & 0x3F );
        *( ( unsigned long * )OutPtr ) = Bit0 | ( Bit1 << 8 ) | ( Bit2 << 16 ) | ( Bit3 << 24 );
        InPtr += 3;
        OutPtr += 4;
    }

    /* Deal with left data */
    if ( Left )
    {
        Dummy = 0;
        for ( Iter = 0; Iter < Left; Iter++ )
            ( ( char * )&Dummy )[Iter] = *InPtr++;

        Bit0 = GetB64Char( ( BIT0( Dummy ) >> 2 ) & 0x3F );
        Bit1 = GetB64Char( ( BIT0( Dummy ) << 6 >> 2 | BIT1( Dummy ) >> 4 ) & 0x3F );
        Bit2 = Left > 1 ? GetB64Char( ( BIT1( Dummy ) << 4 >> 2 | BIT2( Dummy ) >> 6 ) & 0x3F ) : DEFAULT_PAD_CHAR;
        Bit3 = DEFAULT_PAD_CHAR;
        *( ( unsigned long * )OutPtr ) = Bit0 | ( Bit1 << 8 ) | ( Bit2 << 16 ) | ( Bit3 << 24 );
        OutPtr += 4;
    }
    *OutPtr = '\0';

    return OutPtr - OutputBuffer;
}

unsigned long Base64DecodeX( char *OutputBuffer, const char *InputBuffer, unsigned long Length )
{
    register long Iter;
    long Count;
    long Left;
    unsigned long Dummy;
    register int Bit0;
    register int Bit1;
    register int Bit2;
    register const char *InPtr;
    register char *OutPtr;

    InPtr = InputBuffer;
    OutPtr = OutputBuffer;
    if ( Length > 4 )
    {
        Left = Length % 4;
        if ( Left == 0 )
            Left = 4;

        Count = Length - Left;
        for ( Iter = 0; Iter < Count; Iter += 4 )
        {
            Dummy = *( unsigned long * )InPtr;
            Bit0 = ( GetB64Index( ( char )BIT0( Dummy ) ) << 2 | GetB64Index( ( char )BIT1( Dummy ) ) << 2 >> 6 ) & 0xFF;
            Bit1 = ( GetB64Index( ( char )BIT1( Dummy ) ) << 4 | GetB64Index( ( char )BIT2( Dummy ) ) << 2 >> 4 ) & 0xFF;
            Bit2 = ( GetB64Index( ( char )BIT2( Dummy ) ) << 6 | GetB64Index( ( char )BIT3( Dummy ) ) << 2 >> 2 ) & 0xFF;
            *( ( unsigned long * )OutPtr ) = Bit0 | ( Bit1 << 8 ) | ( Bit2 << 16 );
            InPtr += 4;
            OutPtr += 3;
        }
    }
    else
    {
        Left = Length;
    }

    /* Deal with left data */
    if ( Left )
    {
        Dummy = 0;
        for ( Iter = 0; Iter < Left; Iter++ )
            ( ( char * )&Dummy )[Iter] = *InPtr++;

        *OutPtr++ = ( char ) ( GetB64Index( ( char )BIT0( Dummy ) ) << 2 | GetB64Index( ( char )BIT1( Dummy ) ) << 2 >> 6 ) & 0xFF;
        if ( DEFAULT_PAD_CHAR != BIT1( Dummy ) && DEFAULT_PAD_CHAR != BIT2( Dummy ) )
            *OutPtr++ = ( char ) ( GetB64Index( ( char )BIT1( Dummy ) ) << 4 | GetB64Index( ( char )BIT2( Dummy ) ) << 2 >> 4 ) & 0xFF;
        if ( DEFAULT_PAD_CHAR != BIT2( Dummy ) && DEFAULT_PAD_CHAR != BIT3( Dummy ) )
            *OutPtr++ = ( char ) ( GetB64Index( ( char )BIT2( Dummy ) ) << 6 | GetB64Index( ( char )BIT3( Dummy ) ) << 2 >> 2 ) & 0xFF;
    }
    *OutPtr = '\0';

    return OutPtr - OutputBuffer;
}