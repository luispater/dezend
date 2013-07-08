/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   ParseString.h
//  Version     :   1.0
//  Creator     :   RM
//  Create Date :   2006-01-01
//  Comment     :
//
///////////////////////////////////////////////////////////////////////////////
*/

#ifndef __PARSESTRING_H__
#define __PARSESTRING_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/
/* Default setting */
#define DEFAULT_SEPARATOR _T( ' ' )
#define DEFAULT_BOUNDARY _T( '\"' )
#define DEFAULT_REPLACE _T( '\0' )

#define DEFAULT_SEPARATOR_A ' '
#define DEFAULT_BOUNDARY_A '\"'
#define DEFAULT_REPLACE_A '\0'

#define DEFAULT_SEPARATOR_W L' '
#define DEFAULT_BOUNDARY_W L'\"'
#define DEFAULT_REPLACE_W L'\0'

#if UNICODE

#define ParseStringEx ParseStringExW
#define ParseStringDataEx ParseStringDataExW
#define ParseCommandLineEx ParseCommandLineExW

#define ParseString ParseStringW
#define ParseStringData ParseStringDataW
#define ParseCommandLine ParseCommandLineW

#else

#define ParseStringEx ParseStringExA
#define ParseStringDataEx ParseStringDataExA
#define ParseCommandLineEx ParseCommandLineExA

#define ParseString ParseStringA
#define ParseStringData ParseStringDataA
#define ParseCommandLine ParseCommandLineA

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
void ParseStringExA( PCOMMON_STACK List, LPCSTR String, char Separator, char Boundary, char Replace );
void ParseStringDataExA( PCOMMON_STACK_U List, LPCSTR String, char Separator, char Boundary, char Replace );
void ParseCommandLineExA( PCOMMON_STACK List, LPCSTR String, char Separator, char Boundary, char Replace );

void ParseStringExW( PCOMMON_STACK List, LPCWSTR String, WCHAR Separator, WCHAR Boundary, WCHAR Replace );
void ParseStringDataExW( PCOMMON_STACK_U List, LPCWSTR String, WCHAR Separator, WCHAR Boundary, WCHAR Replace );
void ParseCommandLineExW( PCOMMON_STACK List, LPCWSTR String, WCHAR Separator, WCHAR Boundary, WCHAR Replace );

void __inline ParseStringA( PCOMMON_STACK List, LPCSTR String, char Separator )
{
    ParseStringExA( List, String, Separator, DEFAULT_BOUNDARY_A, DEFAULT_REPLACE_A );
}

void __inline ParseStringDataA( PCOMMON_STACK_U List, LPCSTR String, char Separator )
{
    ParseStringDataExA( List, String, Separator, DEFAULT_BOUNDARY_A, DEFAULT_REPLACE_A );
}

void __inline ParseCommandLineA( PCOMMON_STACK List, LPCSTR String, char Separator )
{
    ParseCommandLineExA( List, String, Separator, DEFAULT_BOUNDARY_A, DEFAULT_REPLACE_A );
}

void __inline ParseStringW( PCOMMON_STACK List, LPCWSTR String, WCHAR Separator )
{
    ParseStringExW( List, String, Separator, DEFAULT_BOUNDARY_W, DEFAULT_REPLACE_W );
}

void __inline ParseStringDataW( PCOMMON_STACK_U List, LPCWSTR String, WCHAR Separator )
{
    ParseStringDataExW( List, String, Separator, DEFAULT_BOUNDARY_W, DEFAULT_REPLACE_W );
}

void __inline ParseCommandLineW( PCOMMON_STACK List, LPCWSTR String, WCHAR Separator )
{
    ParseCommandLineExW( List, String, Separator, DEFAULT_BOUNDARY_W, DEFAULT_REPLACE_W );
}

#ifdef __cplusplus
}
#endif
/*
///////////////////////////////////////////////////////////////////////////////
// E N D  O F  F I L E
///////////////////////////////////////////////////////////////////////////////
*/
#endif /* __PARSESTRING_H__ */