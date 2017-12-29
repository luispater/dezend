/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   Encode.c
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
#include "Map.h"
#include "MD5.h"
#include "AddLog.h"
#include "Dump.h"
#include "Encode.h"

/* Skip warning */
#pragma warning( disable: 4054 )
#pragma warning( disable: 4055 )
#pragma warning( disable: 4100 )
#pragma warning( disable: 4127 )
#pragma warning( disable: 4152 )
#pragma warning( disable: 4201 )
#pragma warning( disable: 4204 )
#pragma warning( disable: 4244 )
#pragma warning( disable: 4245 )
#pragma warning( disable: 4305 )
#pragma warning( disable: 4310 )
#pragma warning( disable: 4505 )
#pragma warning( disable: 4706 )

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/
/* Des */
#define DEFAULT_XOR 0xA5A5

/* CRC32 */
#define CRC32( CRC, Ch ) CRC = ( ( CRC >> 8 ) & 0x00FFFFFF ) ^ g_CRC32Table[( CRC ^ ( Ch ) ) & 0xFF]

/* Check if hook */
#define OP_CODE_INT3 0xCC /* INT 3 */
#define OP_CODE_PUSH 0x68 /* PUSH */
#define OP_CODE_RET 0xC3 /* RET */
#define OP_CODE_CALL 0xE8 /* CALL data32 */
#define OP_CODE_JMP 0xE9 /* JMP data32 */
#define OP_CODE_JMP_FAR 0xEA /* JMP data16:data32 */
#define OP_CODE_JMP_NEAR 0xEB /* JMP data8 */

/* Get global */
#define GET_INTERNAL_STUB( ) g_InternalStubPtr

/*
///////////////////////////////////////////////////////////////////////////////
// S T R U C T U R E S
///////////////////////////////////////////////////////////////////////////////
*/
typedef BOOL ( WINAPI *IsDebuggerPresentProc ) ( );
typedef BOOL ( WINAPI *VirtualProtectProc ) ( LPVOID, DWORD, DWORD, PDWORD );

typedef UCHAR ( DES_SUBKEY )[16] [48];
typedef DES_SUBKEY *PDES_SUBKEY;

/*
///////////////////////////////////////////////////////////////////////////////
// G L O B A L S
///////////////////////////////////////////////////////////////////////////////
*/
static UCHAR g_DummyStart[4] = {
    0, 1, 0, 1
};

static UINT g_CRC32Table[256] = {
    0x00000000, 0x77073096, 0xee0e612c, 0x990951ba,
    0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
    0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
    0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
    0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de,
    0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
    0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,
    0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
    0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
    0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
    0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940,
    0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
    0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116,
    0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
    0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
    0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
    0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a,
    0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
    0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818,
    0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
    0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
    0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
    0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c,
    0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
    0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2,
    0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
    0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
    0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
    0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086,
    0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
    0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4,
    0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,
    0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
    0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
    0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8,
    0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
    0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe,
    0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
    0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
    0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
    0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252,
    0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
    0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60,
    0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
    0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
    0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
    0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04,
    0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
    0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a,
    0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
    0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
    0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
    0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e,
    0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
    0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c,
    0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
    0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
    0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
    0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0,
    0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
    0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6,
    0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
    0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
    0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d,
};

/* Initial permutation IP */
static UCHAR IP_Table[64] = {
    58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
};
/* Final permutation IP^-1 */
static UCHAR IPR_Table[64] = {
    40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25
};
/* Expansion operation matrix */
static UCHAR E_Table[48] = {
    32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9,
        8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1
};
/* 32-bit permutation function P used on the output of the S-boxes */
static UCHAR P_Table[32] = {
    16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25
};
/* Permuted choice table (Key) */
static UCHAR PC1_Table[56] = {
    57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4
};
/* Permuted choice key (table) */
static UCHAR PC2_Table[48] = {
    14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};
/* Number left rotations of pc1 */
static UCHAR LOOP_Table[16] = {
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};
/* The (in)famous S-boxes */
static UCHAR S_Box[8] [4] [16] = {
    /* S1 */
    14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
    0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
    4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
    15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13,
    /* S2 */
    15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
    3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
    0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
    13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9,
    /* S3 */
    10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
    13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
    13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
    1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12,
    /* S4 */
    7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
    13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
    10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
    3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14,
    /* S5 */
    2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
    14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
    4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
    11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3,
    /* S6 */
    12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
    10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
    9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
    4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13,
    /* S7 */
    4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
    13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
    1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
    6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12,
    /* S8 */
    13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
    1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
    7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
    2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
};
static UCHAR g_DummyEnd[4] = {
    0, 1, 0, 1
};

void EncodeDummyStart( );
void EncodeDummyEnd( );

ENCODE_RANGE g_InternalRange[] = {
    { g_DummyStart, g_DummyEnd, ES_FLAGS_ENCODE_1 },
    { EncodeDummyStart, EncodeDummyEnd, ES_FLAGS_ENCODE_1 },
};

ENCODE_STUB g_InternalStub = {
    TYPE_ENCODE_INTERNAL,
    sizeof( ENCODE_STUB ),
    0,
    0,
    DEFAULT_ENCODE_KEY,
    DEFAULT_ENCODE_KEY_LENGTH,
    { 0 },
    0,
    { 0 },
    SIZE_OF_ARRAY( g_InternalRange ),
    g_InternalRange
};
PENCODE_STUB g_InternalStubPtr = &g_InternalStub;

/*
///////////////////////////////////////////////////////////////////////////////
// F U N C T I O N S  P R O T O T Y P E
///////////////////////////////////////////////////////////////////////////////
*/
/* Standard DES encode/decode */
static void DES( UCHAR Out[8], const UCHAR In[8], const PDES_SUBKEY SubKey, ULONG Type );
static void SetKey( PDES_SUBKEY SubKey, ULONG *Is3DES, const UCHAR *Key, ULONG Length );
static void SetSubKey( PDES_SUBKEY SubKey, const UCHAR Key[8] );
static void F_Func( UCHAR In[32], const UCHAR Ki[48] );
static void S_Func( UCHAR Out[32], const UCHAR In[48] );
static void Transform( UCHAR *Out, const UCHAR *In, const UCHAR *Table, ULONG Length );
static void Xor( UCHAR *InA, const UCHAR *InB, ULONG Length );
static void RotateL( UCHAR *In, ULONG Length, ULONG Loop );
static void ByteToBit( UCHAR *Out, const UCHAR *In, ULONG Bits );
static void BitToByte( UCHAR *Out, const UCHAR *In, ULONG Bits );

/* Get executable file information */
ULONG GetPeInfo( PVOID, PIMAGE_NT_HEADERS*, PIMAGE_FILE_HEADER*, PIMAGE_OPTIONAL_HEADER*, PIMAGE_SECTION_HEADER* );

/*
///////////////////////////////////////////////////////////////////////////////
// F U N C T I O N S
///////////////////////////////////////////////////////////////////////////////
*/
void EncodeDummyStart( )
{
    /* Just for count */
}

ULONG DesCode( void *Out, const void *In, ULONG Length, const void *Key, ULONG KeyLength, ULONG Type )
{
    register int Iter;
    register int Count;
    ULONG Is3DES;
    ULONG Left;
    const UCHAR *UKey;
    register UCHAR *UOut;
    register const UCHAR *UIn;
    DES_SUBKEY SubKey[2]; /* 16 loop sub key */

    if ( Out == NULL || In == NULL || Key == NULL || Length == 0 )
        return FALSE;

    UKey = ( const UCHAR* )Key;
    SetKey( SubKey, &Is3DES, UKey, KeyLength );

    Left = Length & 7;
    Length &= ~7;
    if ( !Is3DES )
    {
        /* 1DES */
        UOut = ( UCHAR* )Out;
        UIn = ( const UCHAR* )In;
        for ( Iter = 0, Count = Length >> 3; Iter < Count; Iter++, UOut += 8, UIn += 8 )
            DES( UOut, UIn, &SubKey[0], Type );
        while ( Left )
        {
            *UOut = ( UCHAR ) ( *UIn ^ DEFAULT_XOR ^ UKey[Left % KeyLength] );
            UIn++;
            UOut++;
            Left--;
        }
    }
    else
    {
        /* 3DES */
        /* Encode: E(key0)-D(key1)-E(key0) */
        /* Decode: D(key0)-E(key1)-D(key0) */
        UOut = ( UCHAR* )Out;
        UIn = ( const UCHAR* )In;
        for ( Iter = 0, Count = Length >> 3; Iter < Count; Iter++, UOut += 8, UIn += 8 )
        {
            DES( UOut, UIn, &SubKey[0], Type );
            DES( UOut, UOut, &SubKey[1], !Type );
            DES( UOut, UOut, &SubKey[0], Type );
        }
        while ( Left )
        {
            *UOut = ( UCHAR ) ( *UIn ^ DEFAULT_XOR ^ UKey[Left % KeyLength] );
            UIn++;
            UOut++;
            Left--;
        }
    }

    return TRUE;
}

void SetKey( PDES_SUBKEY SubKey, ULONG *Is3DES, const UCHAR *Key, ULONG Length )
{
    UCHAR DesKey[16];
    memset( DesKey, 0, 16 );
    memcpy( DesKey, Key, Length > 16 ? 16 : Length );
    SetSubKey( &SubKey[0], &DesKey[0] );
    if ( Length > 8 )
    {
        SetSubKey( &SubKey[1], &DesKey[8] );
        if ( Is3DES )
            *Is3DES = TRUE;
    }
    else
    {
        if ( Is3DES )
            *Is3DES = FALSE;
    }
}

void DES( UCHAR Out[8], const UCHAR In[8], const PDES_SUBKEY SubKey, ULONG Type )
{
    register LONG Iter;
    UCHAR M[64];
    UCHAR Tmp[32];
    UCHAR *Li = &M[0];
    UCHAR *Ri = &M[32];

    ByteToBit( M, In, 64 );
    Transform( M, M, IP_Table, 64 );
    if ( Type == DES_ENCRYPT )
    {
        for ( Iter = 0; Iter < 16; Iter++ )
        {
            memcpy( Tmp, Ri, 32 );
            F_Func( Ri, ( *SubKey )[Iter] );
            Xor( Ri, Li, 32 );
            memcpy( Li, Tmp, 32 );
        }
    }
    else
    {
        for ( Iter = 15; Iter >= 0; Iter-- )
        {
            memcpy( Tmp, Li, 32 );
            F_Func( Li, ( *SubKey )[Iter] );
            Xor( Li, Ri, 32 );
            memcpy( Ri, Tmp, 32 );
        }
    }
    Transform( M, M, IPR_Table, 64 );
    BitToByte( Out, M, 64 );
}

void SetSubKey( PDES_SUBKEY SubKey, const UCHAR Key[8] )
{
    register ULONG Iter;
    UCHAR K[64];
    UCHAR *KL = &K[0];
    UCHAR *KR = &K[28];
    ByteToBit( K, Key, 64 );
    Transform( K, K, PC1_Table, 56 );
    for ( Iter = 0; Iter < 16; Iter++ )
    {
        RotateL( KL, 28, LOOP_Table[Iter] );
        RotateL( KR, 28, LOOP_Table[Iter] );
        Transform( ( *SubKey )[Iter], K, PC2_Table, 48 );
    }
}

void F_Func( UCHAR In[32], const UCHAR Ki[48] )
{
    UCHAR MR[48];
    Transform( MR, In, E_Table, 48 );
    Xor( MR, Ki, 48 );
    S_Func( In, MR );
    Transform( In, In, P_Table, 32 );
}

void S_Func( UCHAR Out[32], const UCHAR In[48] )
{
    register UCHAR Iter, Jter, Kter;
    for ( Iter = 0; Iter < 8; Iter++, In += 6, Out += 4 )
    {
        Jter = ( UCHAR ) ( ( In[0] << 1 ) + In[5] );
        Kter = ( UCHAR ) ( ( In[1] << 3 ) + ( In[2] << 2 ) + ( In[3] << 1 ) + In[4] );
        ByteToBit( Out, &S_Box[Iter] [Jter] [Kter], 4 );
    }
}

void Transform( UCHAR *Out, const UCHAR *In, const UCHAR *Table, ULONG Length )
{
    register ULONG Iter;
    UCHAR Tmp[256];
    for ( Iter = 0; Iter < Length; Iter++ )
        Tmp[Iter] = In[Table[Iter] - 1];
    memcpy( Out, Tmp, Length );
}

void Xor( UCHAR *InA, const UCHAR *InB, ULONG Length )
{
    register ULONG Iter;
    for ( Iter = 0; Iter < Length; Iter++ )
        InA[Iter] ^= InB[Iter];
}

void RotateL( UCHAR *In, ULONG Length, ULONG Loop )
{
    UCHAR Tmp[256];
    memcpy( Tmp, In, Loop );
    memcpy( In, In + Loop, Length - Loop );
    memcpy( In + Length - Loop, Tmp, Loop );
}

void ByteToBit( UCHAR *Out, const UCHAR *In, ULONG Bits )
{
    register ULONG Iter;
    for ( Iter = 0; Iter < Bits; Iter++ )
        Out[Iter] = ( UCHAR ) ( ( In[Iter >> 3] >> ( Iter & 7 ) ) & 1 );
}

void BitToByte( UCHAR *Out, const UCHAR *In, ULONG Bits )
{
    register ULONG Iter;
    memset( Out, 0, Bits >> 3 );
    for ( Iter = 0; Iter < Bits; Iter++ )
        Out[Iter >> 3] |= In[Iter] << ( Iter & 7 );
}

void GetCRC( PMD5_VALUE MD5, UCHAR *Buffer, ULONG BufferLength )
{
    register ULONG Iter;
    register UCHAR *BufferPtr;
    unsigned __int64 Sum = 0;
    UINT CRC = 0;

    for ( Iter = BufferLength, BufferPtr = Buffer; Iter--; BufferPtr++ )
    {
        Sum += *BufferPtr;
        /* Use default crc32 */
        CRC32( CRC, *BufferPtr );
    }

    *( ( UINT* )&MD5->Value[0] ) += CRC;
    *( ( UINT* )&MD5->Value[4] ) += BufferLength;
    *( ( unsigned __int64* )&MD5->Value[8] ) += Sum;
}

ULONG GetFileCRC( PMD5_VALUE MD5, const TCHAR *FileName, ULONG SkipOffset, ULONG SkipSize )
{
    ULONG Size;
    PVOID FileImage;

    MapFileEx( FileName, &FileImage, &Size, NULL, MAP_FILE_READ | MAP_FILE_GENERIC_READ | MAP_FILE_SHARE_READ );
    if ( FileImage )
    {
        memset( MD5, 0, sizeof( *MD5 ) );
        GetCRC( MD5, ( UCHAR* )FileImage, SkipOffset );
        GetCRC( MD5, ( UCHAR* )FileImage + SkipOffset + SkipSize, Size - SkipOffset - SkipSize );
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

ULONG GetModuleCRC( PMD5_VALUE MD5, LPVOID ModuleBase, ULONG SkipOffset, ULONG SkipSize )
{
    register ULONG Iter;
    register ULONG Count;
    PIMAGE_NT_HEADERS NtHeaders;
    PIMAGE_FILE_HEADER FileHeader;
    PIMAGE_OPTIONAL_HEADER OptionalHeader;
    PIMAGE_SECTION_HEADER SectionHeader;
    ULONG Size;
    UCHAR *StartAddress;
    UCHAR *SkipAddressStart;
    UCHAR *SkipAddressEnd;

    if ( GetPeInfo( ModuleBase, &NtHeaders, &FileHeader, &OptionalHeader, &SectionHeader ) )
    {
        memset( MD5, 0, sizeof( *MD5 ) );
        SkipAddressStart = ( UCHAR* )ModuleBase + SkipOffset;
        SkipAddressEnd = SkipAddressStart + SkipSize;
        for ( Iter = 0, Count = FileHeader->NumberOfSections; Iter < Count; Iter++, SectionHeader++ )
        {
            if ( !( SectionHeader->Characteristics & IMAGE_SCN_MEM_WRITE ) && *( ( ULONG* )SectionHeader->Name ) != 0x6164722e )
            {
                StartAddress = ( UCHAR* )ModuleBase + SectionHeader->VirtualAddress;
                Size = SectionHeader->SizeOfRawData;
                if ( StartAddress <= SkipAddressStart && SkipAddressEnd < StartAddress + Size )
                {
                    GetCRC( MD5, StartAddress, SkipOffset );
                    GetCRC( MD5, SkipAddressEnd, Size - SkipOffset - SkipSize );
                }
                else
                {
                    GetCRC( MD5, StartAddress, Size );
                }
            }
        }
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void GetMD5( PMD5_VALUE MD5, UCHAR *Buffer, ULONG BufferLength )
{
    MD5_CTX MD5Ctx;
    MD5Init( &MD5Ctx );
    MD5Update( &MD5Ctx, Buffer, BufferLength );
    MD5Final( MD5->Value, &MD5Ctx );
}

ULONG GetFileMD5( PMD5_VALUE MD5, const TCHAR *FileName, ULONG SkipOffset, ULONG SkipSize )
{
    ULONG Size;
    PVOID FileImage;
    MD5_CTX MD5Ctx;

    MapFileEx( FileName, &FileImage, &Size, NULL, MAP_FILE_READ | MAP_FILE_GENERIC_READ | MAP_FILE_SHARE_READ );
    if ( FileImage )
    {
        MD5Init( &MD5Ctx );
        if ( SkipSize )
        {
            MD5Update( &MD5Ctx, ( UCHAR* )FileImage, SkipOffset );
            MD5Update( &MD5Ctx, ( UCHAR* )FileImage + SkipOffset + SkipSize, Size - SkipOffset - SkipSize );
        }
        else
        {
            MD5Update( &MD5Ctx, ( UCHAR* )FileImage, Size );
        }
        MD5Final( MD5->Value, &MD5Ctx );
        UnMapFile( FileImage );
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

ULONG GetModuleMD5( PMD5_VALUE MD5, LPVOID ModuleBase, ULONG SkipOffset, ULONG SkipSize )
{
    register ULONG Iter;
    register ULONG Count;
    PIMAGE_NT_HEADERS NtHeaders;
    PIMAGE_FILE_HEADER FileHeader;
    PIMAGE_OPTIONAL_HEADER OptionalHeader;
    PIMAGE_SECTION_HEADER SectionHeader;
    ULONG Size;
    UCHAR *StartAddress;
    UCHAR *SkipAddressStart;
    UCHAR *SkipAddressEnd;
    MD5_CTX MD5Ctx;

    if ( GetPeInfo( ModuleBase, &NtHeaders, &FileHeader, &OptionalHeader, &SectionHeader ) )
    {
        memset( MD5, 0, sizeof( *MD5 ) );
        SkipAddressStart = ( UCHAR* )ModuleBase + SkipOffset;
        SkipAddressEnd = SkipAddressStart + SkipSize;
        for ( Iter = 0, Count = FileHeader->NumberOfSections; Iter < Count; Iter++, SectionHeader++ )
        {
            if ( !( SectionHeader->Characteristics & IMAGE_SCN_MEM_WRITE ) && *( ( ULONG* )SectionHeader->Name ) != 0x6164722e )
            {
                StartAddress = ( UCHAR* )ModuleBase + SectionHeader->VirtualAddress;
                Size = SectionHeader->SizeOfRawData;
                if ( StartAddress <= SkipAddressStart && SkipAddressEnd < StartAddress + Size )
                {
                    MD5Update( &MD5Ctx, StartAddress, SkipOffset );
                    MD5Update( &MD5Ctx, SkipAddressEnd, Size - SkipOffset - SkipSize );
                }
                else
                {
                    MD5Update( &MD5Ctx, StartAddress, Size );
                }
            }
        }
        MD5Final( MD5->Value, &MD5Ctx );
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

ULONG DecodeStubKey( PENCODE_STUB Stub, const TCHAR *ModuleName )
{
    ULONG RetCode;
    ULONG Flags;
    MD5_VALUE MD5;
    ULONG Size;
    UCHAR *Module;
    UCHAR *SkipAddress;

    if ( Stub == NULL )
        Stub = GET_INTERNAL_STUB( );

    Flags = GET_INTERNAL_STUB( )->Flags;
    if ( Flags & ES_FLAGS_CRC_FILE )
    {
        Size = sizeof( MD5 );
        SkipAddress = ( UCHAR* )GET_INTERNAL_STUB( );
        Module = ( UCHAR* )GetModuleHandle( ModuleName );
        RetCode = GetFileCRC( &MD5, ModuleName, SkipAddress - Module, sizeof( ENCODE_STUB ) );
    }
    else if ( Flags & ES_FLAGS_CRC_MODULE )
    {
        Size = sizeof( MD5 );
        SkipAddress = ( UCHAR* )GET_INTERNAL_STUB( );
        Module = ( UCHAR* )GetModuleHandle( ModuleName );
        RetCode = GetModuleCRC( &MD5, Module, SkipAddress - Module, sizeof( ENCODE_STUB ) );
    }
    else if ( Flags & ES_FLAGS_MD5_FILE )
    {
        Size = sizeof( MD5 );
        SkipAddress = ( UCHAR* )GET_INTERNAL_STUB( );
        Module = ( UCHAR* )GetModuleHandle( ModuleName );
        RetCode = GetFileMD5( &MD5, ModuleName, SkipAddress - Module, sizeof( ENCODE_STUB ) );
    }
    else if ( Flags & ES_FLAGS_MD5_MODULE )
    {
        Size = sizeof( MD5 );
        SkipAddress = ( UCHAR* )GET_INTERNAL_STUB( );
        Module = ( UCHAR* )GetModuleHandle( ModuleName );
        RetCode = GetModuleMD5( &MD5, Module, SkipAddress - Module, sizeof( ENCODE_STUB ) );
    }
    else
    {
        RetCode = FALSE;
    }

    if ( RetCode )
        DecodeEx( Stub->Key, Stub->KeyLength, Stub->MD5.Value, sizeof( Stub->MD5.Value ) );

    return RetCode;
}

ULONG CheckIfHook( UCHAR *Buffer, ULONG Length )
{
    register ULONG Iter;
    register ULONG Count;
    register UCHAR *BufferPtr;
    LONG Address;

    BufferPtr = Buffer;
    Count = Length;
    for ( Iter = 0; Iter < Count; Iter++, BufferPtr++ )
    {
        switch ( *BufferPtr )
        {
        case OP_CODE_INT3 :
            return TRUE;
        case OP_CODE_PUSH :
            if ( BufferPtr[1] == OP_CODE_RET )
            {
                Address = *( ( LONG* ) ( BufferPtr + 2 ) );
                if ( Address < 0 )
                    return TRUE;
            }
            break;
        case OP_CODE_CALL :
            Address = *( ( LONG* ) ( BufferPtr + 2 ) );
            if ( Address < 0 )
                return TRUE;
            break;
        case OP_CODE_JMP :
            Address = *( ( LONG* ) ( BufferPtr + 2 ) );
            if ( Address < 0 )
                return TRUE;
            break;
        case OP_CODE_JMP_FAR :
            Address = *( ( LONG* ) ( BufferPtr + 2 ) );
            if ( Address < 0 )
                return TRUE;
            break;
        case OP_CODE_JMP_NEAR :
            Address = *( ( CHAR* ) ( BufferPtr + 2 ) );
            if ( Address < 0 )
                return TRUE;
            break;
        }
    }

    return FALSE;
}

ULONG CheckIfTrace( )
{
    ULONG Count;
    static HMODULE hKernel32 = NULL;
    static VirtualProtectProc VirtualProtect = NULL;
    static IsDebuggerPresentProc IsDebuggerPresent = NULL;
    static TCHAR tszkernel32[] = {
        _T( 'k' ) ^ XOR_STR, _T( 'e' ) ^ XOR_STR, _T( 'r' ) ^ XOR_STR, _T( 'n' ) ^ XOR_STR,
        _T( 'e' ) ^ XOR_STR, _T( 'l' ) ^ XOR_STR, _T( '3' ) ^ XOR_STR, _T( '2' ) ^ XOR_STR,
        _T( '.' ) ^ XOR_STR, _T( 'd' ) ^ XOR_STR, _T( 'l' ) ^ XOR_STR, _T( 'l' ) ^ XOR_STR,
        _T( '\0' ) ^ XOR_STR,
    };
    static CHAR aszVirtualProtect[] = {
        ( 'V' ) ^ XOR_STR, ( 'i' ) ^ XOR_STR, ( 'r' ) ^ XOR_STR, ( 't' ) ^ XOR_STR,
        ( 'u' ) ^ XOR_STR, ( 'a' ) ^ XOR_STR, ( 'l' ) ^ XOR_STR, ( 'P' ) ^ XOR_STR,
        ( 'r' ) ^ XOR_STR, ( 'o' ) ^ XOR_STR, ( 't' ) ^ XOR_STR, ( 'e' ) ^ XOR_STR,
        ( 'c' ) ^ XOR_STR, ( 't' ) ^ XOR_STR, ( '\0' ) ^ XOR_STR,
    };
    static CHAR aszIsDebuggerPresent[] = {
        ( 'I' ) ^ XOR_STR, ( 's' ) ^ XOR_STR, ( 'D' ) ^ XOR_STR, ( 'e' ) ^ XOR_STR,
        ( 'b' ) ^ XOR_STR, ( 'u' ) ^ XOR_STR, ( 'g' ) ^ XOR_STR, ( 'g' ) ^ XOR_STR,
        ( 'e' ) ^ XOR_STR, ( 'r' ) ^ XOR_STR, ( 'P' ) ^ XOR_STR, ( 'r' ) ^ XOR_STR,
        ( 'e' ) ^ XOR_STR, ( 's' ) ^ XOR_STR, ( 'e' ) ^ XOR_STR, ( 'n' ) ^ XOR_STR,
        ( 't' ) ^ XOR_STR, ( '\0' ) ^ XOR_STR,
    };

    if ( hKernel32 == NULL )
    {
        DECODE_STR( Count, tszkernel32 );
        hKernel32 = GetModuleHandle( tszkernel32 );
        ENCODE_STR( Count, tszkernel32 );
    }

    if ( VirtualProtect == NULL )
    {
        if ( hKernel32 )
        {
            DECODE_STR( Count, aszVirtualProtect );
            VirtualProtect = ( VirtualProtectProc )GetProcAddress( hKernel32, aszVirtualProtect );
            ENCODE_STR( Count, aszVirtualProtect );
        }
    }

    if ( IsDebuggerPresent == NULL )
    {
        if ( hKernel32 )
        {
            DECODE_STR( Count, aszIsDebuggerPresent );
            IsDebuggerPresent = ( IsDebuggerPresentProc )GetProcAddress( hKernel32, aszIsDebuggerPresent );
            ENCODE_STR( Count, aszIsDebuggerPresent );
        }
    }

#ifdef _MSC_VER
    __try
#endif
    {
        if ( CheckIfHook( ( UCHAR* )VirtualProtect, 16 ) )
            return TRUE;

        if ( CheckIfHook( ( UCHAR* )IsDebuggerPresent, 10 ) )
            return TRUE;

        if ( IsDebuggerPresent( ) )
            return TRUE;
    }
#ifdef _MSC_VER
    __except ( EXCEPTION_EXECUTE_HANDLER )
    {
        return TRUE;
    }
#endif

    return FALSE;
}

void DestroyCode( PUCHAR AddressStart, PUCHAR AddressEnd )
{
    ULONG OldProtection;

    VirtualProtect( AddressStart, AddressEnd - AddressStart, PAGE_READWRITE, &OldProtection );
    memset( AddressStart, 0, AddressEnd - AddressStart );
    VirtualProtect( AddressStart, AddressEnd - AddressStart, OldProtection, &OldProtection );
}

void AlterCode( PUCHAR AddressStart, PUCHAR AddressEnd )
{
    ULONG OldProtection;

    VirtualProtect( AddressStart, AddressEnd - AddressStart, PAGE_READWRITE, &OldProtection );
    for ( ; AddressStart < AddressEnd; AddressStart++ )
        *AddressStart ^= 0xA5;
    VirtualProtect( AddressStart, AddressEnd - AddressStart, OldProtection, &OldProtection );
}

void EncodeDummyEnd( )
{
    /* Just for count */
    EncodeDummyStart( );
}

ULONG GetPeInfo(
    IN PVOID ModuleBase,
    OUT PIMAGE_NT_HEADERS *ppNH,
    OUT PIMAGE_FILE_HEADER *ppFH,
    OUT PIMAGE_OPTIONAL_HEADER *ppOH,
    OUT PIMAGE_SECTION_HEADER *ppSH
    )
{
    PIMAGE_DOS_HEADER DosHeader;
    PIMAGE_NT_HEADERS NtHeaders;
    PIMAGE_FILE_HEADER FileHeader;
    PIMAGE_OPTIONAL_HEADER OptionalHeader;
    PIMAGE_SECTION_HEADER SectionHeader;

#ifdef _MSC_VER
    __try
#endif
    {
        DosHeader = ( PIMAGE_DOS_HEADER )ModuleBase;
        if ( DosHeader->e_magic != IMAGE_DOS_SIGNATURE )
            return FALSE;

        NtHeaders = ( PIMAGE_NT_HEADERS ) ( ( UCHAR* )ModuleBase + DosHeader->e_lfanew );
        if ( NtHeaders->Signature != IMAGE_NT_SIGNATURE )
            return FALSE;

        FileHeader = ( PIMAGE_FILE_HEADER )&( NtHeaders )->FileHeader;
        OptionalHeader = ( PIMAGE_OPTIONAL_HEADER ) &( NtHeaders )->OptionalHeader;
        if ( ( OptionalHeader )->Magic != IMAGE_NT_OPTIONAL_HDR32_MAGIC )
            return FALSE;

        SectionHeader = ( PIMAGE_SECTION_HEADER ) ( ( UCHAR* )OptionalHeader + sizeof( IMAGE_OPTIONAL_HEADER ) );
        if ( ppNH )
            *ppNH = NtHeaders;
        if ( ppFH )
            *ppFH = FileHeader;
        if ( ppOH )
            *ppOH = OptionalHeader;
        if ( ppSH )
            *ppSH = SectionHeader;
    }
#ifdef _MSC_VER
    __except( EXCEPTION_EXECUTE_HANDLER )
    {
        return FALSE;
    }
#endif

    return TRUE;
}

void RemoveCodeProtection( PVOID ModuleBase )
{
    ULONG Iter;
    ULONG Count;
    PIMAGE_FILE_HEADER FileHeader;
    PIMAGE_SECTION_HEADER SectionHeader;

    if ( GET_INTERNAL_STUB( )->Flags & ES_FLAGS_ENCODE )
    {
        if ( GetPeInfo( ModuleBase, NULL, &FileHeader, NULL, &SectionHeader ) )
        {
            for ( Iter = 0, Count = FileHeader->NumberOfSections; Iter < Count; Iter++, SectionHeader++ )
            {
                if ( SectionHeader->Characteristics & IMAGE_SCN_CNT_CODE )
                    VirtualProtect( ( UCHAR* )ModuleBase + SectionHeader->VirtualAddress, SectionHeader->SizeOfRawData, PAGE_READWRITE, &GET_INTERNAL_STUB( )->Protection );
            }
        }
        GET_INTERNAL_STUB( )->Flags |= ES_FLAGS_REMOVE_PROTECTION;
    }
}

void RecoverCodeProtection( PVOID ModuleBase )
{
    ULONG Iter;
    ULONG Count;
    PIMAGE_FILE_HEADER FileHeader;
    PIMAGE_SECTION_HEADER SectionHeader;

    if ( GET_INTERNAL_STUB( )->Flags & ES_FLAGS_REMOVE_PROTECTION )
    {
        if ( GetPeInfo( ModuleBase, NULL, &FileHeader, NULL, &SectionHeader ) )
        {
            for ( Iter = 0, Count = FileHeader->NumberOfSections; Iter < Count; Iter++, SectionHeader++ )
            {
                if ( SectionHeader->Characteristics & IMAGE_SCN_CNT_CODE )
                    VirtualProtect( ( UCHAR* )ModuleBase + SectionHeader->VirtualAddress, SectionHeader->SizeOfRawData, GET_INTERNAL_STUB( )->Protection, &GET_INTERNAL_STUB( )->Protection );
            }
        }
        GET_INTERNAL_STUB( )->Flags &= ~ES_FLAGS_REMOVE_PROTECTION;
    }
}

void EncodeKey( UCHAR *Key, ULONG KeyLength )
{
    UCHAR Prev;
    UCHAR *KeyPtr;
    UCHAR *KeyPtrEnd;

    Prev = 0;
    KeyPtr = Key;
    KeyPtrEnd = Key + KeyLength;
    while ( KeyPtr < KeyPtrEnd )
    {
        Prev = *KeyPtr = ( ( ( *KeyPtr ^ 0xAA ) + Prev ) ^ 0x55 ) + Prev;
        KeyPtr++;
    }
}

void DecodeKey( UCHAR *Key, ULONG KeyLength )
{
    UCHAR Prev;
    UCHAR *KeyPtr;
    UCHAR *KeyPtrStart;

    KeyPtr = Key + KeyLength;
    KeyPtrStart = Key;
    while ( KeyPtr > KeyPtrStart )
    {
        KeyPtr--;
        if ( KeyPtr == Key )
            Prev = 0;
        else
            Prev = *( KeyPtr - 1 );
        *KeyPtr = ( ( ( *KeyPtr - Prev ) ^ 0x55 ) - Prev ) ^ 0xAA;
    }
}

void ObfuscateKey( UCHAR *Key, ULONG KeyLength )
{
    UCHAR Prev;
    UCHAR Cur;
    UCHAR *KeyPtr;
    UCHAR *KeyPtrEnd;

    Prev = 0;
    KeyPtr = Key;
    KeyPtrEnd = Key + KeyLength;
    while ( KeyPtr < KeyPtrEnd )
    {
        Cur = *KeyPtr;
        *KeyPtr++ = ( ( ( Cur ^ 0xAA ) + Prev ) ^ 0x55 ) + Prev;
        Prev = Cur;
    }
}

void EncodeEx( UCHAR *Buffer, ULONG Length, UCHAR *Key, ULONG KeyLength )
{
    ULONG Iter;
    ULONG Count;
    UCHAR Prev;
    UCHAR *BufferPtr;
    UCHAR *KeyPtr;
    UCHAR *KeyPtrEnd;

    BufferPtr = Buffer;
    KeyPtrEnd = Key + KeyLength;
    for ( Iter = 0, Prev = 0, Count = Length / KeyLength; Iter < Count; Iter++ )
    {
        KeyPtr = Key;
        while ( KeyPtr < KeyPtrEnd )
        {
            Prev = *BufferPtr = ( ( ( *BufferPtr ^ *KeyPtr ) + Prev ) ^ ~*KeyPtr ) + Prev;
            BufferPtr++;
            KeyPtr++;
        }
    }

    KeyPtr = Key;
    KeyPtrEnd = Key + ( Length % KeyLength );
    while ( KeyPtr < KeyPtrEnd )
    {
        Prev = *BufferPtr = ( ( ( *BufferPtr ^ *KeyPtr ) + Prev ) ^ ~*KeyPtr ) + Prev;
        BufferPtr++;
        KeyPtr++;
    }
}

void DecodeEx( UCHAR *Buffer, ULONG Length, UCHAR *Key, ULONG KeyLength )
{
    ULONG Iter;
    ULONG Count;
    UCHAR Prev;
    UCHAR *BufferPtr;
    UCHAR *KeyPtr;
    UCHAR *KeyPtrStart;

    BufferPtr = Buffer + Length;
    KeyPtr = Key + ( Length % KeyLength );
    KeyPtrStart = Key;
    while ( KeyPtr > KeyPtrStart )
    {
        KeyPtr--;
        BufferPtr--;
        if ( BufferPtr == Buffer )
            Prev = 0;
        else
            Prev = *( BufferPtr - 1 );
        *BufferPtr = ( ( ( *BufferPtr - Prev ) ^ ~*KeyPtr ) - Prev ) ^ *KeyPtr;
    }

    for ( Iter = 0, Count = Length / KeyLength; Iter < Count; Iter++ )
    {
        KeyPtr = Key + KeyLength;
        while ( KeyPtr > KeyPtrStart )
        {
            KeyPtr--;
            BufferPtr--;
            if ( BufferPtr == Buffer )
                Prev = 0;
            else
                Prev = *( BufferPtr - 1 );
            *BufferPtr = ( ( ( *BufferPtr - Prev ) ^ ~*KeyPtr ) - Prev ) ^ *KeyPtr;
        }
    }
}

void EncodeInternalStub( PENCODE_STUB Stub, PVOID ImageBase, PVOID FileImage )
{
    ULONG Iter;
    ULONG Count;
    ULONG Length;
    UCHAR *StartAddress;
    UCHAR *Key;
    ULONG KeyLength;
    PENCODE_RANGE Range;

    if ( !( Stub->Flags & ES_FLAGS_ENCODE ) )
    {
        Range = ( PENCODE_RANGE ) ( ( PUCHAR )Stub->Range - ( PUCHAR )ImageBase + ( PUCHAR )FileImage );
        Key = Stub->InternalKey;
        KeyLength = Stub->InternalKeyLength;
        for ( Iter = 0, Count = Stub->Count; Iter < Count; Iter++, Range++ )
        {
            StartAddress = ( PUCHAR )Range->Start;
            Length = ( ( PUCHAR )Range->End - StartAddress ) & ~0xF;
            StartAddress += ( PUCHAR )FileImage - ( PUCHAR )ImageBase;
            EncodeEx( StartAddress, Length, Key, KeyLength );
        }
        EncodeKey( Key, KeyLength );
        Stub->Flags |= ES_FLAGS_ENCODE;
    }
}

void DecodeInternalStub( PENCODE_STUB Stub )
{
    ULONG Iter;
    ULONG Count;
    ULONG Length;
    UCHAR *StartAddress;
    UCHAR *Key;
    ULONG KeyLength;
    PENCODE_RANGE Range;

    if ( Stub == NULL )
        Stub = GET_INTERNAL_STUB( );

    if ( Stub->Flags & ES_FLAGS_ENCODE )
    {
        Key = Stub->InternalKey;
        KeyLength = Stub->InternalKeyLength;
        DecodeKey( Key, KeyLength );
        for ( Iter = 0, Count = Stub->Count; Iter < Count; Iter++ )
        {
            Range = &Stub->Range[Iter];
            StartAddress = ( PUCHAR )Range->Start;
            Length = ( ( PUCHAR )Range->End - StartAddress ) & ~0xF;
            DecodeEx( StartAddress, Length, Key, KeyLength );
        }
        Stub->Flags &= ~ES_FLAGS_ENCODE;
    }
}

void EncodeStub( PENCODE_STUB Stub, PVOID ImageBase, PVOID FileImage )
{
    ULONG Iter;
    ULONG Count;
    ULONG Length;
    UCHAR *StartAddress;
    UCHAR *Key;
    ULONG KeyLength;
    PENCODE_RANGE Range;

    if ( !( Stub->Flags & ES_FLAGS_ENCODE ) )
    {
        Range = ( PENCODE_RANGE ) ( ( PUCHAR )Stub->Range - ( PUCHAR )ImageBase + ( PUCHAR )FileImage );
        Key = Stub->Key;
        KeyLength = Stub->KeyLength;
        for ( Iter = 0, Count = Stub->Count; Iter < Count; Iter++, Range++ )
        {
            StartAddress = ( PUCHAR )Range->Start;
            Length = ( ( PUCHAR )Range->End - StartAddress ) & ~0xF;
            StartAddress += ( PUCHAR )FileImage - ( PUCHAR )ImageBase;
            if ( Range->Flags & ES_FLAGS_ENCODE_1 )
                DesCode( StartAddress, StartAddress, Length, Key, KeyLength, DES_ENCRYPT );
            else
                EncodeEx( StartAddress, Length, Key, KeyLength );
        }
        Stub->Flags |= ES_FLAGS_ENCODE;
    }
}

void DecodeStub( PENCODE_STUB Stub )
{
    ULONG Iter;
    ULONG Count;
    ULONG Length;
    UCHAR *StartAddress;
    UCHAR *Key;
    ULONG KeyLength;
    PENCODE_RANGE Range;

    if ( Stub->Flags & ES_FLAGS_ENCODE )
    {
        Key = Stub->Key;
        KeyLength = Stub->KeyLength;
        for ( Iter = 0, Count = Stub->Count; Iter < Count; Iter++ )
        {
            Range = &Stub->Range[Iter];
            StartAddress = ( PUCHAR )Range->Start;
            Length = ( ( PUCHAR )Range->End - StartAddress ) & ~0xF;
            if ( Range->Flags & ES_FLAGS_ENCODE_1 )
                DesCode( StartAddress, StartAddress, Length, Key, KeyLength, DES_DECRYPT );
            else
                DecodeEx( StartAddress, Length, Key, KeyLength );
        }
        Stub->Flags &= ~ES_FLAGS_ENCODE;
    }
}
