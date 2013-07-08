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
// I N L I N E  D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/

/*
__inline LPTSTR WideCharToTChar( LPCWSTR In, LPSTR Out, ULONG Len )
{
#if defined( _UNICODE ) || defined( UNICODE )
    return ( LPTSTR )In;
#else
    WideCharToMultiByte( CP_ACP,
        0,
        In,
        -1,
        Out,
        Len,
        0,
        0
        );
    return ( LPTSTR )Out;
#endif
}

__inline LPTSTR MutiByteToTChar( LPCSTR In, LPWSTR Out, ULONG Len )
{
#if defined( _UNICODE ) || defined( UNICODE )
    MultiByteToWideChar( CP_ACP,
        0,
        In,
        -1,
        Out,
        Len
        );
    return ( LPTSTR )Out;
#else
    return ( LPTSTR )In;
#endif
}

__inline LPWSTR TCharToWideChar( LPCTSTR In, LPWSTR Out, ULONG Len )
{
#if defined( _UNICODE ) || defined( UNICODE )
    return ( LPWSTR )In;
#else
    MultiByteToWideChar( CP_ACP,
        0,
        In,
        -1,
        Out,
        Len
        );
    return ( LPWSTR )Out;
#endif
}

__inline LPSTR TCharToMutiByte( LPCTSTR In, LPSTR Out, ULONG Len )
{
#if defined( _UNICODE ) || defined( UNICODE )
    WideCharToMultiByte( CP_ACP,
        0,
        In,
        -1,
        Out,
        Len,
        0,
        0
        );
    return ( LPSTR )Out;
#else
    return ( LPSTR )In;
#endif
}
*/

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
#define PAGE_SIZE 0x2000 // 8K
#else
#define PAGE_SIZE 0x1000 // 4K
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
/* convert */
#define WideCharToTChar( In, Out, Len ) \
    ( Out, In )
#define MutiByteToTChar( In, Out, Len ) \
    ( MultiByteToWideChar( CP_ACP, 0, In, - 1, Out, Len ), Out )
#define TCharToWideChar( In, Out, Len ) \
    ( Out, In )
#define TCharToMutiByte( In, Out, Len ) \
    ( WideCharToMultiByte( CP_ACP, 0, In, - 1, Out, Len, 0, 0 ), Out )
/* copy */
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
/* convert */
#define WideCharToTChar( In, Out, Len ) \
    ( WideCharToMultiByte( CP_ACP, 0, In, - 1, Out, Len, 0, 0 ), Out )
#define MutiByteToTChar( In, Out, Len ) \
    ( Out, In )
#define TCharToWideChar( In, Out, Len ) \
    ( MultiByteToWideChar( CP_ACP, 0, In, - 1, Out, Len ), Out )
#define TCharToMutiByte( In, Out, Len ) \
    ( Out, In )
/* copy */
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
///////////////////////////////////////////////////////////////////////////////
// E N D  O F  F I L E
///////////////////////////////////////////////////////////////////////////////
*/
#endif /* __MACRO_H__ */