/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   Macro.h
//  Version     :   1.0
//  Creator     :   RM
//  Create Date :   2006-01-01
//  Comment     :
//
///////////////////////////////////////////////////////////////////////////////
*/

#ifndef __MACRO_H__
#define __MACRO_H__

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/

/*
///////////////////////////////////////
// PAGE SIZE
///////////////////////////////////////
*/
#ifndef PAGE_SIZE
#if defined( _ALPHA_ )
#define PAGE_SIZE 0x2000 /* 8K */
#else
#define PAGE_SIZE 0x1000 /* 4K */
#endif
#endif

#ifndef SIZE_OF_UNIT
#define SIZE_OF_UNIT( Unit ) ( sizeof( Unit ) )
#endif

#ifndef SIZE_OF_ARRAY
#define SIZE_OF_ARRAY( Array ) ( sizeof( Array ) / sizeof( ( Array )[0] ) )
#endif

/*
///////////////////////////////////////
// S T R I N G
///////////////////////////////////////
*/
#if defined( _UNICODE ) || defined( UNICODE )
/* Convert */
#define WideCharToTChar( In, Out, Len ) \
    ( Out, In )
#define MutiByteToTChar( In, Out, Len ) \
    ( MultiByteToWideChar( CP_ACP, 0, In, - 1, Out, Len ), Out )
#define TCharToWideChar( In, Out, Len ) \
    ( Out, In )
#define TCharToMutiByte( In, Out, Len ) \
    ( WideCharToMultiByte( CP_ACP, 0, In, - 1, Out, Len, 0, 0 ), Out )
/* Copy */
#define CopyWideCharToTChar( In, Out, Len ) \
    wcsncpy( Out, In, Len )
#define CopyMutiByteToTChar( In, Out, Len ) \
    ( MultiByteToWideChar( CP_ACP, 0, In, - 1, Out, Len ), Out )
#define CopyTCharToWideChar( In, Out, Len ) \
    wcsncpy( Out, In, Len )
#define CopyTCharToMutiByte( In, Out, Len ) \
    ( WideCharToMultiByte( CP_ACP, 0, In, - 1, Out, Len, 0, 0 ), Out )
/**/
#else
/**/
/* Convert */
#define WideCharToTChar( In, Out, Len ) \
    ( WideCharToMultiByte( CP_ACP, 0, In, - 1, Out, Len, 0, 0 ), Out )
#define MutiByteToTChar( In, Out, Len ) \
    ( Out, In )
#define TCharToWideChar( In, Out, Len ) \
    ( MultiByteToWideChar( CP_ACP, 0, In, - 1, Out, Len ), Out )
#define TCharToMutiByte( In, Out, Len ) \
    ( Out, In )
/* Copy */
#define CopyWideCharToTChar( In, Out, Len ) \
    ( WideCharToMultiByte( CP_ACP, 0, In, - 1, Out, Len, 0, 0 ), Out )
#define CopyMutiByteToTChar( In, Out, Len ) \
    strncpy( Out, In, Len )
#define CopyTCharToWideChar( In, Out, Len ) \
    ( MultiByteToWideChar( CP_ACP, 0, In, - 1, Out, Len ), Out )
#define CopyTCharToMutiByte( In, Out, Len ) \
    strncpy( Out, In, Len )
#endif

#define WideCharToByte( In, Out, Len ) \
    WideCharToMultiByte( CP_ACP, 0, In, - 1, Out, Len, 0, 0 )

#define ByteToWideChar( In, Out, Len ) \
    MultiByteToWideChar( CP_ACP, 0, In, - 1, Out, Len )

/*
///////////////////////////////////////
// D E C O D E  /  E N C O D E
///////////////////////////////////////
*/
#ifndef ENCODE_STR

#define XOR_STR_A ( ( char )0xA5 )
#define XOR_STR_W ( ( unsigned short )0xB4A5 )

#define ENCODE_CHAR_A( C ) ( C ^ XOR_STR_A )
#define DECODE_CHAR_A( C ) ( C ^ XOR_STR_A )

#define ENCODE_CHAR_W( C ) ( C ^ XOR_STR_W )
#define DECODE_CHAR_W( C ) ( C ^ XOR_STR_W )

#define ENCODE_STR_A( Count, String ) \
    for ( Count = 0; ( ( char * )String )[Count] != ( char ) ( 0 ); Count++ ) \
        ( ( char * )String )[Count] ^= XOR_STR_A; \
    ( ( char * )String )[Count] ^= XOR_STR_A;

#define DECODE_STR_A( Count, String ) \
    for ( Count = 0; ( ( char * )String )[Count] != ( char ) ( 0 ^ XOR_STR_A ); Count++ ) \
        ( ( char * )String )[Count] ^= XOR_STR_A; \
    ( ( char * )String )[Count] ^= XOR_STR_A;

#define ENCODE_STR_W( Count, String ) \
    for ( Count = 0; ( ( unsigned short * )String )[Count] != ( unsigned short ) ( 0 ); Count++ ) \
        ( ( unsigned short * )String )[Count] ^= XOR_STR_W; \
    ( ( unsigned short * )String )[Count] ^= XOR_STR_W;

#define DECODE_STR_W( Count, String ) \
    for ( Count = 0; ( ( unsigned short * )String )[Count] != ( unsigned short ) ( 0 ^ XOR_STR_W ); Count++ ) \
        ( ( unsigned short * )String )[Count] ^= XOR_STR_W; \
    ( ( unsigned short * )String )[Count] ^= XOR_STR_W;

#if !defined( _UNICODE ) && !defined( UNICODE )
#define XOR_STR XOR_STR_A
#define ENCODE_CHAR ENCODE_CHAR_A
#define DECODE_CHAR DECODE_CHAR_A
#define ENCODE_STR ENCODE_STR_A
#define DECODE_STR DECODE_STR_A
#else
#define XOR_STR XOR_STR_W
#define ENCODE_CHAR ENCODE_CHAR_W
#define DECODE_CHAR DECODE_CHAR_W
#define ENCODE_STR ENCODE_STR_W
#define DECODE_STR DECODE_STR_W
#endif

#endif

/*
///////////////////////////////////////////////////////////////////////////////
// E N D  O F  F I L E
///////////////////////////////////////////////////////////////////////////////
*/
#endif /* __MACRO_H__ */