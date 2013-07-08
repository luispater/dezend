/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   Utf8.c
//  Version     :   1.0
//  Creator     :   RM
//  Create Date :   2006-01-01
//  Comment     :
//
///////////////////////////////////////////////////////////////////////////////
*/

#include "Utf8.h"

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/
#define PAD_CHAR '?'
#define IS_ONE_BYTE( B ) ( ( ( B ) & 0x80 ) == 0x00 )
#define IS_TWO_BYTE( B ) ( ( ( B ) & 0xE0 ) == 0xC0 )
#define IS_THREE_BYTE( B ) ( ( ( B ) & 0xF0 ) == 0xE0 )
#define IS_MULT_BYTE( B ) ( ( ( B ) & 0xC0 )==0x80 )
#define IS_UTF8_BYTE( B ) IS_ONE_BYTE( B ) || IS_TWO_BYTE( B ) || IS_THREE_BYTE( B )

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
unsigned long IsUtf8( const char *InputBuffer, unsigned long Length )
{
    unsigned long RetCode;
    register unsigned long Iter;
    unsigned char Bit0;
    unsigned char Bit1;
    unsigned char Bit2;

    RetCode = 0;
    for ( Iter = 0; Iter < Length; )
    {
        Bit0 = ( unsigned char )InputBuffer[Iter];
        if ( IS_ONE_BYTE( Bit0 ) )
        {
            Iter++;
            RetCode++;
        }
        else if ( IS_TWO_BYTE( Bit0 ) )
        {
            if ( Iter + 2 > Length )
                break;
            Bit1 = ( unsigned char )InputBuffer[Iter + 1];
            if ( IS_MULT_BYTE( Bit1 ) )
                Iter += 2;
            else
                break;
        }
        else if ( IS_THREE_BYTE( Bit0 ) )
        {
            if ( Iter + 3 > Length )
                break;

            Bit1 = ( unsigned char )InputBuffer[Iter + 1];
            Bit2 = ( unsigned char )InputBuffer[Iter + 2];
            if ( IS_MULT_BYTE( Bit1 ) && IS_MULT_BYTE( Bit2 ) )
                Iter += 3;
            else
                break;
        }
        else
        {
            break;
        }
    }

    return ( RetCode != Length ) && ( Iter == Length );
}

unsigned long Utf8EncodeX( char *OutputBuffer, const char *InputBuffer, unsigned long Length )
{
    return 0;
}

unsigned long Utf8DecodeX( char *OutputBuffer, const char *InputBuffer, unsigned long Length )
{
    register unsigned long Iter;
    register unsigned short *Out;
    unsigned char Bit0;
    unsigned char Bit1;
    unsigned char Bit2;

    Out = ( unsigned short* )OutputBuffer;
    for ( Iter = 0; Iter < Length; )
    {
        Bit0 = ( unsigned char )InputBuffer[Iter];
        if ( IS_ONE_BYTE( Bit0 ) )
        {
            *Out++ = Bit0;
            Iter++;
        }
        else if ( IS_TWO_BYTE( Bit0 ) )
        {
            if ( Iter + 2 > Length )
            {
                *Out++ = PAD_CHAR;
                break;
            }
            Bit1 = ( unsigned char )InputBuffer[Iter + 1];
            if ( IS_MULT_BYTE( Bit1 ) )
            {
                *Out++ = ( ( Bit0 & 0x1F ) << 6 ) + ( Bit1 & 0x3F );
                Iter += 2;
            }
            else if ( IS_UTF8_BYTE( Bit1 ) )
            {
                *Out++ = PAD_CHAR;
                Iter++;
            }
            else
            {
                *Out++ = PAD_CHAR;
                Iter += 2;
            }
        }
        else if ( IS_THREE_BYTE( Bit0 ) )
        {
            if ( Iter + 2 > Length )
            {
                *Out++ = PAD_CHAR;
                break;
            }
            else if ( Iter + 3 > Length )
            {
                Bit1 = ( unsigned char )InputBuffer[Iter + 1];
                if ( IS_ONE_BYTE( Bit1 ) )
                {
                    *Out++ = PAD_CHAR;
                    Iter++;
                    continue;
                }
                else
                {
                    *Out++ = PAD_CHAR;
                    break;
                }
            }

            Bit1 = ( unsigned char )InputBuffer[Iter + 1];
            Bit2 = ( unsigned char )InputBuffer[Iter + 2];
            if ( IS_MULT_BYTE( Bit1 ) && IS_MULT_BYTE( Bit2 ) )
            {
                *Out++ = ( ( Bit0 & 0x0F ) << 12 ) + ( ( Bit1 & 0x3F ) << 6 ) + ( Bit2 & 0x3F );
                Iter += 3;
            }
            else if ( IS_UTF8_BYTE( Bit1 ) )
            {
                *Out++ = PAD_CHAR;
                Iter++;
            }
            else if ( IS_UTF8_BYTE( Bit2 ) )
            {
                *Out++ = PAD_CHAR;
                Iter += 2;
            }
            else
            {
                *Out++ = PAD_CHAR;
                Iter += 3;
            }
        }
        else
        {
            *Out++ = PAD_CHAR;
            Iter++;
        }
    }
    *Out = L'\0';

    return ( char * )Out - OutputBuffer;
}