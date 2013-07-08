/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   ParseSetting.c
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
#include "ParseSetting.h"

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/
/* Buffer size */
#define PS_BUFFER_SIZE 4096
#define GET_GS_CONST_TRUE( ) ( g_ConstTrue )

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
const TCHAR g_GlobalConstTrue[] = _T( "true" );
const TCHAR *g_ConstTrue = g_GlobalConstTrue;

/*
///////////////////////////////////////////////////////////////////////////////
// F U N C T I O N S
///////////////////////////////////////////////////////////////////////////////
*/
__forceinline void set_environment_string( LPCTSTR Key, LPCTSTR Value )
{
    TCHAR Buffer[PS_BUFFER_SIZE];

    if ( Value )
    {
        _sntprintf( Buffer, SIZE_OF_ARRAY( Buffer ) - 1, _T( "%s=%s" ), Key, Value );
        Buffer[SIZE_OF_ARRAY( Buffer ) - 1] = _T( '\0' );
        _tputenv( Buffer );
    }
}

__forceinline void compare_set_environment_string( LPCTSTR Key, LPCTSTR Value )
{
    TCHAR Buffer[PS_BUFFER_SIZE];

    if ( _tgetenv( Key ) == NULL )
    {
        if ( Value )
        {
            _sntprintf( Buffer, SIZE_OF_ARRAY( Buffer ) - 1, _T( "%s=%s" ), Key, Value );
            Buffer[SIZE_OF_ARRAY( Buffer ) - 1] = _T( '\0' );
            _tputenv( Buffer );
        }
    }
}

__forceinline void compare_set_environment_string_ex( LPCTSTR Value, LPCTSTR Key, LPCTSTR DefaultValue )
{
    if ( Value )
        set_environment_string( Key, Value );
    else
        compare_set_environment_string( Key, DefaultValue );
}

__forceinline void get_environment_string( LPCTSTR Value, LPTSTR Data, ULONG Length )
{
    if ( Value )
        _sntprintf( Data, Length, _T( "%s" ), Value );
}

__forceinline void compare_set_flags( LPCTSTR Value, ULONG *SetData, ULONG Data )
{
    if ( Value && 0 == _tcsicmp( Value, GET_GS_CONST_TRUE( ) ) )
        *SetData |= Data;
}

__forceinline void compare_set_char( LPCTSTR Value, TCHAR *SetData, TCHAR Data )
{
    if ( Value && 0 == _tcsicmp( Value, GET_GS_CONST_TRUE( ) ) )
        *SetData = Data;
}

__forceinline void compare_set_string( LPCTSTR Value, TCHAR *SetData, LPCTSTR Data )
{
    if ( Value && 0 == _tcsicmp( Value, GET_GS_CONST_TRUE( ) ) )
        _tcscpy( SetData, Data );
}

__forceinline void compare_set_number( LPCTSTR Value, ULONG *SetData )
{
    register ULONG Dummy;

    if ( Value )
    {
        Dummy = _ttol( Value );
        if ( Dummy )
            *SetData = Dummy;
    }
}

__forceinline void compare_set_number_n( LPCTSTR Value, USHORT *Data1, USHORT *Data2 )
{
    ULONG Dummy;
    LPCTSTR lptszString;
    LPCTSTR lptszString1;

    if ( Value )
    {
        lptszString = Value;
        lptszString1 = _tcschr( lptszString, _T( ',' ) );
        if ( lptszString1 )
        {
            lptszString1++;
            Dummy = _ttol( lptszString1 );
            if ( Dummy )
                *Data2 = ( USHORT )Dummy;
        }
        Dummy = _ttol( lptszString );
        if ( Dummy )
            *Data1 = ( USHORT )Dummy;
    }
}

void TranslateEscapeCharacter( LPTSTR String, ULONG Length )
{
    UCHAR NewChar;
    UCHAR NewChar1;
    LPTSTR lptszStart;
    LPTSTR lptszEnd;
    LPTSTR lptszOut;

    lptszStart = String;
    lptszEnd = lptszStart + Length;
    while ( *lptszStart && lptszStart < lptszEnd )
    {
        if ( *lptszStart == _T( '\\' ) )
            break;
        lptszStart++;
    }

    lptszOut = lptszStart;
    while ( *lptszStart && lptszStart < lptszEnd )
    {
        if ( *lptszStart == _T( '\\' ) )
        {
            if ( *( lptszStart + 1 ) == _T( '\\' ) )
            {
                *lptszOut++ = *lptszStart++;
                lptszStart += 2;
            }
            else if ( *( lptszStart + 1 ) == _T( 't' ) )
            {
                *lptszOut++ = _T( '\t' );
                lptszStart += 2;
            }
            else if ( *( lptszStart + 1 ) == _T( 'r' ) )
            {
                *lptszOut++ = _T( '\r' );
                lptszStart += 2;
            }
            else if ( *( lptszStart + 1 ) == _T( 'n' ) )
            {
                *lptszOut++ = _T( '\n' );
                lptszStart += 2;
            }
            else if ( *( lptszStart + 1 ) == _T( 'x' ) )
            {
                lptszStart += 2;
                NewChar = CharToHex( *lptszStart );
                if ( NewChar != INVALID_BYTE )
                {
                    lptszStart++;
                    NewChar1 = CharToHex( *lptszStart );
                    if ( NewChar1 != INVALID_BYTE )
                    {
                        lptszStart++;
                        NewChar = ( UCHAR ) ( ( NewChar << 4 ) + NewChar1 );
                    }
                    *lptszOut++ = NewChar;
                }
            }
            else
            {
                lptszStart++;
            }
        }
        else
        {
            *lptszOut++ = *lptszStart++;
        }
    }
    *lptszOut = _T( '\0' );
}

void ParseSetting( PINI_GLOBAL_SETTING IniSettingArray, ULONG Count, const TCHAR *ConstTrue )
{
    PINI_GLOBAL_SETTING IsStart;
    PINI_GLOBAL_SETTING IsEnd;

    /* For set flags */
    if ( ConstTrue )
        g_ConstTrue = ConstTrue;
    else
        g_ConstTrue = g_GlobalConstTrue;

    /* Deal with environment string */
    for ( IsStart = IniSettingArray, IsEnd = IsStart + Count; IsStart < IsEnd; IsStart++ )
    {
        if ( IsStart->Flags & IGS_FLAGS_SET_FLAGS )
            compare_set_flags( _tgetenv( IsStart->Environment ), IsStart->SetValuePtr, IsStart->Data );
        else if ( IsStart->Flags & IGS_FLAGS_SET_NUMBER )
            compare_set_number( _tgetenv( IsStart->Environment ), IsStart->SetValuePtr );
        else if ( IsStart->Flags & IGS_FLAGS_SET_NUMBER_N )
            compare_set_number_n( _tgetenv( IsStart->Environment ), IsStart->SetValuePtr, IsStart->DefaultValuePtr );
        else if ( IsStart->Flags & IGS_FLAGS_SET_CHAR )
            compare_set_char( _tgetenv( IsStart->Environment ), IsStart->SetValuePtr, ( TCHAR )IsStart->Data );
        else if ( IsStart->Flags & IGS_FLAGS_SET_STRING )
            get_environment_string( _tgetenv( IsStart->Environment ), IsStart->SetValuePtr, IsStart->Data );
        else if ( IsStart->Flags & IGS_FLAGS_COMPARE_SET )
            compare_set_environment_string_ex( _tgetenv( IsStart->Environment ), IsStart->SetValuePtr, IsStart->DefaultValuePtr );
        else if ( IsStart->Flags & IGS_FLAGS_CALLBACK )
            ( ( IGS_CALLBACK )IsStart->DefaultValuePtr ) ( _tgetenv( IsStart->Environment ), IsStart );
    }
}

void ParseCommandLineSetting( PINI_GLOBAL_SETTING IniSettingArray, ULONG Count, PCOMMON_STACK CommandList, PCOMMON_STACK UnkownList, IGS_CALLBACK Callback )
{
    LPTSTR lptszStart;
    PINI_GLOBAL_SETTING IsStart;
    PINI_GLOBAL_SETTING IsEnd;

    /* Deal with command line */
    for ( ; StackBottom( CommandList, ( PVOID* )&lptszStart ); StackPopBottom( CommandList, NULL, 0 ) )
    {
        if ( *lptszStart != _T( '-' ) && *lptszStart != _T( '/' ) )
        {
            if ( UnkownList )
                StackPush( UnkownList, lptszStart, _tcslen( lptszStart ) + 1 );
            continue;
        }

        lptszStart++;
        if ( Callback )
            if ( Callback( lptszStart, NULL ) )
                continue;

        for ( IsStart = IniSettingArray, IsEnd = IsStart + Count; IsStart < IsEnd; IsStart++ )
        {
            if ( 0 == _tcsnicmp( lptszStart, IsStart->Command, IsStart->CommandLength ) )
            {
                lptszStart += IsStart->CommandLength;
                if ( IsStart->Flags & IGS_FLAGS_SET_FLAGS )
                    compare_set_flags( GET_GS_CONST_TRUE( ), IsStart->SetValuePtr, IsStart->Data );
                else if ( IsStart->Flags & IGS_FLAGS_SET_NUMBER )
                    compare_set_number( lptszStart, IsStart->SetValuePtr );
                else if ( IsStart->Flags & IGS_FLAGS_SET_NUMBER_N )
                    compare_set_number_n( lptszStart, IsStart->SetValuePtr, IsStart->DefaultValuePtr );
                else if ( IsStart->Flags & IGS_FLAGS_SET_CHAR )
                    compare_set_char( GET_GS_CONST_TRUE( ), IsStart->SetValuePtr, ( TCHAR )IsStart->Data );
                else if ( IsStart->Flags & IGS_FLAGS_SET_STRING )
                    get_environment_string( *lptszStart == _T( ':' ) ? lptszStart + 1 : IsStart->DefaultValuePtr, IsStart->SetValuePtr, IsStart->Data );
                else if ( IsStart->Flags & IGS_FLAGS_COMPARE_SET )
                    compare_set_environment_string_ex( *lptszStart == _T( ':' ) ? lptszStart + 1 : IsStart->DefaultValuePtr, IsStart->SetValuePtr, IsStart->DefaultValuePtr );
                else if ( IsStart->Flags & IGS_FLAGS_CALLBACK )
                    ( ( IGS_CALLBACK )IsStart->DefaultValuePtr ) ( lptszStart, IsStart );
                break;
            }
        }
    }
}