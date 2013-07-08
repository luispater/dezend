/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   MD5.c
//  Version     :   1.0
//  Creator     :   RM
//  Create Date :   2006-01-01
//  Comment     :
//
///////////////////////////////////////////////////////////////////////////////
*/

#include "MD5.h"

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/
/* Constants for MD5Transform routine. */
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

/* F, G, H and I are basic MD5 functions. */
#define F( X, Y, Z ) ( ( ( X ) &( Y ) ) | ( ( ~X ) &( Z ) ) )
#define G( X, Y, Z ) ( ( ( X ) &( Z ) ) | ( ( Y ) &( ~Z ) ) )
#define H( X, Y, Z ) ( ( X ) ^ ( Y ) ^ ( Z ) )
#define I( X, Y, Z ) ( ( Y ) ^ ( ( X ) | ( ~Z ) ) )

/* ROTATE_LEFT rotates X left N Bits. */
#define ROTATE_LEFT( X, N ) ( ( ( X ) << ( N ) ) | ( ( X ) >> ( 32 - ( N ) ) ) )

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
    Rotation is separate from addition to prevent recomputation.
*/
#define FF( a, b, c, d, X, s, ac ) { \
    ( a ) += F( ( b ), ( c ), ( d ) ) + ( X ) + ( UINT4 ) ( ac ); \
    ( a ) = ROTATE_LEFT( ( a ), ( s ) ); \
    ( a ) += ( b ); \
}
#define GG( a, b, c, d, X, s, ac ) { \
    ( a ) += G( ( b ), ( c ), ( d ) ) + ( X ) + ( UINT4 ) ( ac ); \
    ( a ) = ROTATE_LEFT( ( a ), ( s ) ); \
    ( a ) += ( b ); \
}
#define HH( a, b, c, d, X, s, ac ) { \
    ( a ) += H( ( b ), ( c ), ( d ) ) + ( X ) + ( UINT4 ) ( ac ); \
    ( a ) = ROTATE_LEFT( ( a ), ( s ) ); \
    ( a ) += ( b ); \
}
#define II( a, b, c, d, X, s, ac ) { \
    ( a ) += I( ( b ), ( c ), ( d ) ) + ( X ) + ( UINT4 ) ( ac ); \
    ( a ) = ROTATE_LEFT( ( a ), ( s ) ); \
    ( a ) += ( b ); \
}

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
static unsigned char PADDING[64] = {
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static void MD5Transform( UINT4[4], unsigned char[64] );
static void Encode( unsigned char *, UINT4 *, unsigned int );
static void Decode( UINT4 *, unsigned char *, unsigned int );
static void MD5_memcpy( POINTER, POINTER, unsigned int );
static void MD5_memset( POINTER, int, unsigned int );

/*
///////////////////////////////////////////////////////////////////////////////
// F U N C T I O N S
///////////////////////////////////////////////////////////////////////////////
*/
/* MD5 initialization. Begins an MD5 operation, writing a new Context. */
void MD5Init( MD5_CTX *Context )
{
    Context->Count[0] = Context->Count[1] = 0;
    /* Load magic initialization constants. */
    Context->State[0] = 0x67452301;
    Context->State[1] = 0xefcdab89;
    Context->State[2] = 0x98badcfe;
    Context->State[3] = 0x10325476;
}

/* MD5 Block update operation. Continues an MD5 message-digest
    operation, processing another message Block, and updating the
    Context.
*/
void MD5Update( MD5_CTX *Context, unsigned char *Input, unsigned int InputLength )
{
    unsigned int Iter;
    unsigned int Index;
    unsigned int PartLength;

    /* Compute number of bytes mod 64 */
    Index = ( unsigned int ) ( ( Context->Count[0] >> 3 ) & 0x3F );

    /* Update number of Bits */
    if ( ( Context->Count[0] += ( ( UINT4 )InputLength << 3 ) ) < ( ( UINT4 )InputLength << 3 ) )
        Context->Count[1]++;

    Context->Count[1] += ( ( UINT4 )InputLength >> 29 );
    PartLength = 64 - Index;
    /* Transform as many times as possible. */
    if ( InputLength >= PartLength )
    {
        MD5_memcpy( ( POINTER ) &Context->Buffer[Index], ( POINTER )Input, PartLength );
        MD5Transform( Context->State, Context->Buffer );

        for ( Iter = PartLength; Iter + 63 < InputLength; Iter += 64 )
            MD5Transform( Context->State, &Input[Iter] );
        Index = 0;
    }
    else
    {
        Iter = 0;
    }

    /* Buffer remaining Input */
    MD5_memcpy( ( POINTER ) &Context->Buffer[Index], ( POINTER ) &Input[Iter], InputLength - Iter );
}

/* MD5 finalization. Ends an MD5 message-digest operation, writing the
    the message digest and zeroizing the Context.
*/
void MD5Final( unsigned char Digest[16], MD5_CTX *Context )
{
    unsigned char Bits[8];
    unsigned int Index;
    unsigned int PadLength;

    /* Save number of Bits */
    Encode( Bits, Context->Count, 8 );

    /* Pad out to 56 mod 64. */
    Index = ( unsigned int ) ( ( Context->Count[0] >> 3 ) & 0x3f );
    PadLength = ( Index < 56 ) ? ( 56 - Index ) : ( 120 - Index );
    MD5Update( Context, PADDING, PadLength );

    /* Append length (before padding) */
    MD5Update( Context, Bits, 8 );

    /* Store state in digest */
    Encode( Digest, Context->State, 16 );

    /* Zeroize sensitive information. */
    MD5_memset( ( POINTER )Context, 0, sizeof( *Context ) );
}

/* MD5 basic transformation. Transforms State based on Block. */
static void MD5Transform( UINT4 State[4], unsigned char Block[64] )
{
    UINT4 A;
    UINT4 B;
    UINT4 C;
    UINT4 D;
    UINT4 X[16];

    A = State[0];
    B = State[1];
    C = State[2];
    D = State[3];

    Decode( X, Block, 64 );

    /* Round 1 */
    FF( A, B, C, D, X[0x00], S11, 0xd76aa478 ); /* 01 */
    FF( D, A, B, C, X[0x01], S12, 0xe8c7b756 ); /* 02 */
    FF( C, D, A, B, X[0x02], S13, 0x242070db ); /* 03 */
    FF( B, C, D, A, X[0x03], S14, 0xc1bdceee ); /* 04 */
    FF( A, B, C, D, X[0x04], S11, 0xf57c0faf ); /* 05 */
    FF( D, A, B, C, X[0x05], S12, 0x4787c62a ); /* 06 */
    FF( C, D, A, B, X[0x06], S13, 0xa8304613 ); /* 07 */
    FF( B, C, D, A, X[0x07], S14, 0xfd469501 ); /* 08 */
    FF( A, B, C, D, X[0x08], S11, 0x698098d8 ); /* 09 */
    FF( D, A, B, C, X[0x09], S12, 0x8b44f7af ); /* 10 */
    FF( C, D, A, B, X[0x0A], S13, 0xffff5bb1 ); /* 11 */
    FF( B, C, D, A, X[0x0B], S14, 0x895cd7be ); /* 12 */
    FF( A, B, C, D, X[0x0C], S11, 0x6b901122 ); /* 13 */
    FF( D, A, B, C, X[0x0D], S12, 0xfd987193 ); /* 14 */
    FF( C, D, A, B, X[0x0E], S13, 0xa679438e ); /* 15 */
    FF( B, C, D, A, X[0x0F], S14, 0x49b40821 ); /* 16 */

    /* Round 2 */
    GG( A, B, C, D, X[0x01], S21, 0xf61e2562 ); /* 17 */
    GG( D, A, B, C, X[0x06], S22, 0xc040b340 ); /* 18 */
    GG( C, D, A, B, X[0x0B], S23, 0x265e5a51 ); /* 19 */
    GG( B, C, D, A, X[0x00], S24, 0xe9b6c7aa ); /* 20 */
    GG( A, B, C, D, X[0x05], S21, 0xd62f105d ); /* 21 */
    GG( D, A, B, C, X[0x0A], S22, 0x02441453 ); /* 22 */
    GG( C, D, A, B, X[0x0F], S23, 0xd8a1e681 ); /* 23 */
    GG( B, C, D, A, X[0x04], S24, 0xe7d3fbc8 ); /* 24 */
    GG( A, B, C, D, X[0x09], S21, 0x21e1cde6 ); /* 25 */
    GG( D, A, B, C, X[0x0E], S22, 0xc33707d6 ); /* 26 */
    GG( C, D, A, B, X[0x03], S23, 0xf4d50d87 ); /* 27 */
    GG( B, C, D, A, X[0x08], S24, 0x455a14ed ); /* 28 */
    GG( A, B, C, D, X[0x0D], S21, 0xa9e3e905 ); /* 29 */
    GG( D, A, B, C, X[0x02], S22, 0xfcefa3f8 ); /* 30 */
    GG( C, D, A, B, X[0x07], S23, 0x676f02d9 ); /* 31 */
    GG( B, C, D, A, X[0x0C], S24, 0x8d2a4c8a ); /* 32 */

    /* Round 3 */
    HH( A, B, C, D, X[0x05], S31, 0xfffa3942 ); /* 33 */
    HH( D, A, B, C, X[0x08], S32, 0x8771f681 ); /* 34 */
    HH( C, D, A, B, X[0x0B], S33, 0x6d9d6122 ); /* 35 */
    HH( B, C, D, A, X[0x0E], S34, 0xfde5380c ); /* 36 */
    HH( A, B, C, D, X[0x01], S31, 0xa4beea44 ); /* 37 */
    HH( D, A, B, C, X[0x04], S32, 0x4bdecfa9 ); /* 38 */
    HH( C, D, A, B, X[0x07], S33, 0xf6bb4b60 ); /* 39 */
    HH( B, C, D, A, X[0x0A], S34, 0xbebfbc70 ); /* 40 */
    HH( A, B, C, D, X[0x0D], S31, 0x289b7ec6 ); /* 41 */
    HH( D, A, B, C, X[0x00], S32, 0xeaa127fa ); /* 42 */
    HH( C, D, A, B, X[0x03], S33, 0xd4ef3085 ); /* 43 */
    HH( B, C, D, A, X[0x06], S34, 0x04881d05 ); /* 44 */
    HH( A, B, C, D, X[0x09], S31, 0xd9d4d039 ); /* 45 */
    HH( D, A, B, C, X[0x0C], S32, 0xe6db99e5 ); /* 46 */
    HH( C, D, A, B, X[0x0F], S33, 0x1fa27cf8 ); /* 47 */
    HH( B, C, D, A, X[0x02], S34, 0xc4ac5665 ); /* 48 */

    /* Round 4 */
    II( A, B, C, D, X[0x00], S41, 0xf4292244 ); /* 49 */
    II( D, A, B, C, X[0x07], S42, 0x432aff97 ); /* 50 */
    II( C, D, A, B, X[0x0E], S43, 0xab9423a7 ); /* 51 */
    II( B, C, D, A, X[0x05], S44, 0xfc93a039 ); /* 52 */
    II( A, B, C, D, X[0x0C], S41, 0x655b59c3 ); /* 53 */
    II( D, A, B, C, X[0x03], S42, 0x8f0ccc92 ); /* 54 */
    II( C, D, A, B, X[0x0A], S43, 0xffeff47d ); /* 55 */
    II( B, C, D, A, X[0x01], S44, 0x85845dd1 ); /* 56 */
    II( A, B, C, D, X[0x08], S41, 0x6fa87e4f ); /* 57 */
    II( D, A, B, C, X[0x0F], S42, 0xfe2ce6e0 ); /* 58 */
    II( C, D, A, B, X[0x06], S43, 0xa3014314 ); /* 59 */
    II( B, C, D, A, X[0x0D], S44, 0x4e0811a1 ); /* 60 */
    II( A, B, C, D, X[0x04], S41, 0xf7537e82 ); /* 61 */
    II( D, A, B, C, X[0x0B], S42, 0xbd3af235 ); /* 62 */
    II( C, D, A, B, X[0x02], S43, 0x2ad7d2bb ); /* 63 */
    II( B, C, D, A, X[0x09], S44, 0xeb86d391 ); /* 64 */

    State[0] += A;
    State[1] += B;
    State[2] += C;
    State[3] += D;

    /* Zeroize sensitive information. */
    MD5_memset( ( POINTER )X, 0, sizeof( X ) );
}

/* Encodes Input (UINT4) into Output (unsigned char). Assumes Length is
    a multiple of 4.
*/
static void Encode( unsigned char *Output, UINT4 *Input, unsigned int Length )
{
    unsigned int Iter;
    unsigned int Jter;

    for ( Iter = 0, Jter = 0; Jter < Length; Iter++, Jter += 4 )
    {
        Output[Jter] = ( unsigned char ) ( Input[Iter] & 0xff );
        Output[Jter + 1] = ( unsigned char ) ( ( Input[Iter] >> 8 ) & 0xff );
        Output[Jter + 2] = ( unsigned char ) ( ( Input[Iter] >> 16 ) & 0xff );
        Output[Jter + 3] = ( unsigned char ) ( ( Input[Iter] >> 24 ) & 0xff );
    }
}

/* Decodes Input (unsigned char) into Output (UINT4). Assumes Length is a multiple of 4. */
static void Decode( UINT4 *Output, unsigned char *Input, unsigned int Length )
{
    unsigned int Iter;
    unsigned int Jter;

    for ( Iter = 0, Jter = 0; Jter < Length; Iter++, Jter += 4 )
        Output[Iter] = ( ( UINT4 )Input[Jter] ) | ( ( ( UINT4 )Input[Jter + 1] ) << 8 ) |
            ( ( ( UINT4 )Input[Jter + 2] ) << 16 ) | ( ( ( UINT4 )Input[Jter + 3] ) << 24 );
}

/* Note: Replace "for loop" with standard memcpy if possible. */
static void MD5_memcpy( POINTER Output, POINTER Input, unsigned int Length )
{
    unsigned int Iter;

    for ( Iter = 0; Iter < Length; Iter++ )
        Output[Iter] = Input[Iter];
}

/* Note: Replace "for loop" with standard memset if possible. */
static void MD5_memset( POINTER Output, int Value, unsigned int Length )
{
    unsigned int Iter;

    for ( Iter = 0; Iter < Length; Iter++ )
        ( ( char* )Output )[Iter] = ( char )Value;
}