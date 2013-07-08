/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   AddLog.c
//  Version     :   1.0
//  Creator     :   RM
//  Create Date :   2006-01-01
//  Comment     :
//
///////////////////////////////////////////////////////////////////////////////
*/

#if !defined( DISABLE_LOG_FUNC )

#pragma warning( disable : 4005 )
#pragma warning( disable : 4115 )
#pragma warning( disable : 4127 )
#pragma warning( disable : 4201 )
#pragma warning( disable : 4273 )

#include < tchar.h >
#include < stdio.h >
#include < stdarg.h >

#ifndef _MSC_VER

/* Non-window os */
#include "Compatible.h"

#else

/* Window os */
#define _STRING_SAFE_

#if defined( _KERNEL_MODE_ ) && !defined( _WIN32_WCE )
/* Kernel mode or Driver */
#include < ntddk.h >
#include < ntstatus.h >
#include < windef.h >
#include < winerror.h >
#include < winioctl.h >
#include "kernel32.h"
#include "ProcessOp.h"
#include "FileOp.h"
#include "RegistryOp.h"
#include "WindowOp.h"
#define VSNWPRINTF __vsnwprintf
#define VSWPRINTF _vswprintf
/**/
#else
/* User mode */
#include < windows.h >
#define VSNWPRINTF _vsnwprintf
#define VSWPRINTF vswprintf
#endif

#endif

#include "AddLog.h"

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/
#define LR_A "\r\n"
#define LR_W L"\r\n"

/* Flags */
#define LOG_FLAGS_EXTERN 0x1

/*
///////////////////////////////////////////////////////////////////////////////
// S T R U C T U R E S
///////////////////////////////////////////////////////////////////////////////
*/
typedef struct _LOG_DATA {
    ULONG LogMethod;
    ULONG Enable;
    ULONG EnableLogTime;
    ULONG Init;
    ULONG Index;
    ULONG Flags;
    union {
        HANDLE hHandle;
        HANDLE hFile;
        HKEY hKey;
        HWND hControl;
        PVOID Reserved;
    } u1;
    ULONG LengthA;
    ULONG LengthW;
    LPSTR lpaszBuffer;
    LPWSTR lpwszBuffer;
#ifdef MAX_PATH
    TCHAR tszLogName[MAX_PATH];
#else
    TCHAR tszLogName[260];
#endif
    CHAR aszBuffer[LOG_BUFFER_SIZE];
    WCHAR wszBuffer[LOG_BUFFER_SIZE];

#if defined( _UNICODE ) || defined( _UNICODE )
#define SZ_LOG_BUFFER lpwszBuffer
#define SZ_LOG_BUFFER_LEN LengthW
#else
#define SZ_LOG_BUFFER lpaszBuffer
#define SZ_LOG_BUFFER_LEN LengthA
#endif
} LOG_DATA, *PLOG_DATA, *LPLOG_DATA;

/*
///////////////////////////////////////////////////////////////////////////////
// G L O B A L S
///////////////////////////////////////////////////////////////////////////////
*/
LOG_DATA g_LogData = {
    LOG_NONE
};

/*
///////////////////////////////////////////////////////////////////////////////
// F U N C T I O N S
///////////////////////////////////////////////////////////////////////////////
*/
ULONG InitLog_File( )
{
#define TOTAL_BUFFER_LEN SIZE_OF_ARRAY( g_LogData.tszLogName )

    ULONG RetCode;
    LPTSTR lptszSep;
    LPTSTR lptszDot;
    LPTSTR lptszDst;
    ULONG AppendLength;
    const TCHAR tszFmt[] = _T( "%s" );
    const TCHAR tszExt[] = _T( ".log" );
    TCHAR tszCurPath[TOTAL_BUFFER_LEN + 0x10];

    lptszSep = _tcsrchr( g_LogData.tszLogName, _T( '\\' ) );
    if ( lptszSep == NULL )
    {
        GetModuleFileName( NULL, tszCurPath, TOTAL_BUFFER_LEN );
        lptszSep = _tcsrchr( tszCurPath, _T( '\\' ) );
        if ( lptszSep )
        {
            lptszDst = lptszSep + 1;
            AppendLength = TOTAL_BUFFER_LEN - ( lptszSep - tszCurPath );
        }
        else
        {
            lptszDst = tszCurPath;
            AppendLength = TOTAL_BUFFER_LEN;
        }
        _sntprintf( lptszDst, AppendLength, tszFmt, g_LogData.tszLogName );
        lptszDot = _tcsrchr( g_LogData.tszLogName, _T( '.' ) );
        if ( lptszDot == NULL )
            _tcscat( tszCurPath, tszExt );

        _tcsncpy( g_LogData.tszLogName, tszCurPath, TOTAL_BUFFER_LEN );
        g_LogData.tszLogName[TOTAL_BUFFER_LEN - 1] = _T( '\0' );
    }

    g_LogData.u1.hFile = INVALID_HANDLE_VALUE;
    RetCode = FALSE;

    do
    {
        g_LogData.u1.hFile = CreateFile( g_LogData.tszLogName,
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            OPEN_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL
            );
        if ( INVALID_HANDLE_VALUE == g_LogData.u1.hFile )
            break;

        SetFilePointer( g_LogData.u1.hFile, 0, NULL, FILE_END );
        RetCode = TRUE;
    } while ( 0 );

    return RetCode;
}

ULONG UnInitLog_File( )
{
    if ( INVALID_HANDLE_VALUE != g_LogData.u1.hFile )
        CloseHandle( g_LogData.u1.hFile );

    g_LogData.u1.hFile = INVALID_HANDLE_VALUE;
    g_LogData.Init = FALSE;

    return TRUE;
}

LONG BackLog_File( LONG Distance, ULONG Position )
{
    LONG RetCode;

    if ( Position == LOG_POSITION_BEGIN )
        Position = FILE_BEGIN;
    else if ( Position == LOG_POSITION_END )
        Position = FILE_END;
    else
        Position = FILE_CURRENT;

    RetCode = SetFilePointer( g_LogData.u1.hFile, Distance, NULL, Position );
    if ( RetCode == - 1 && GetLastError( ) != ERROR_SUCCESS )
        RetCode++;

    return RetCode;
}

LONGLONG BackLog_FileEx( LONGLONG Distance, ULONG Position )
{
    LONGLONG RetCode;
    LARGE_INTEGER LiDistance;

    if ( Position == LOG_POSITION_BEGIN )
        Position = FILE_BEGIN;
    else if ( Position == LOG_POSITION_END )
        Position = FILE_END;
    else
        Position = FILE_CURRENT;

    LiDistance.QuadPart = Distance;
    RetCode = SetFilePointer( g_LogData.u1.hFile, LiDistance.LowPart, &LiDistance.HighPart, Position );
    if ( RetCode == - 1 && GetLastError( ) != ERROR_SUCCESS )
        RetCode++;

    return RetCode;
}

ULONG ClearLog_File( void )
{
    ULONG RetCode;

    if ( INVALID_HANDLE_VALUE == g_LogData.u1.hFile )
        return TRUE;

    SetFilePointer( g_LogData.u1.hFile, 0, NULL, FILE_BEGIN );
    RetCode = SetEndOfFile( g_LogData.u1.hFile );

    return RetCode;
}

ULONG AddLog_FileA( )
{
    ULONG RetCode;
    ULONG Bytes;

    do
    {
        RetCode = FALSE;
        if ( INVALID_HANDLE_VALUE == g_LogData.u1.hFile )
            break;

        if ( g_LogData.EnableLogTime && !( g_LogData.Flags & LOG_FLAGS_EXTERN ) )
            LogTimeA( g_LogData.lpaszBuffer, g_LogData.LengthA );

        Bytes = ( strlen( g_LogData.lpaszBuffer ) ) * sizeof( CHAR );
        RetCode = WriteFile( g_LogData.u1.hFile, g_LogData.lpaszBuffer, Bytes, &Bytes, NULL );
        if ( !RetCode )
            break;

        RetCode = Bytes;
    } while ( 0 );

    return RetCode;
}

ULONG AddLog_FileW( )
{
    ULONG RetCode;
    ULONG Bytes;

    do
    {
        RetCode = FALSE;
        if ( INVALID_HANDLE_VALUE == g_LogData.u1.hFile )
            break;

        if ( g_LogData.EnableLogTime && !( g_LogData.Flags & LOG_FLAGS_EXTERN ) )
            LogTimeW( g_LogData.lpwszBuffer, g_LogData.LengthW );

        Bytes = ( wcslen( g_LogData.lpwszBuffer ) ) * sizeof( WCHAR );
        RetCode = WriteFile( g_LogData.u1.hFile, g_LogData.lpwszBuffer, Bytes, &Bytes, NULL );
        if ( !RetCode )
            break;

        RetCode = Bytes;
    } while ( 0 );

    return RetCode;
}

/*
///////////////////////////////////////////////////////////////////////////////
// LOG_REGISTRY
///////////////////////////////////////////////////////////////////////////////
*/
ULONG InitLog_Reg( )
{
    ULONG RetCode;
    ULONG Disposition;

    g_LogData.Index = 0;
    g_LogData.u1.hKey = NULL;
    RetCode = FALSE;

    do
    {
#ifndef _WIN32_WCE
        _tcscpy( g_LogData.SZ_LOG_BUFFER, g_LogData.tszLogName );

#ifndef _KERNEL_MODE_
        _tcscpy( g_LogData.tszLogName, _T( "SOFTWARE\\__LOG__\\" ) );
#else
        _tcscpy( g_LogData.tszLogName, _T( "SYSTEM\\" ) );
#endif
        _tcscat( g_LogData.tszLogName, g_LogData.SZ_LOG_BUFFER );

        if ( ERROR_SUCCESS != RegCreateKeyEx( HKEY_LOCAL_MACHINE,
            g_LogData.tszLogName,
            0,
            NULL,
            REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS,
            NULL,
            &g_LogData.u1.hKey,
            &Disposition ) )
            break;
#else
        _tcscpy( g_LogData.SZ_LOG_BUFFER, g_LogData.tszLogName );
        _tcscpy( g_LogData.tszLogName, _T( "__LOG__\\" ) );
        _tcscat( g_LogData.tszLogName, g_LogData.SZ_LOG_BUFFER );

        if ( ERROR_SUCCESS != RegCreateKeyEx( HKEY_LOCAL_MACHINE,
            g_LogData.tszLogName,
            0,
            NULL,
            REG_OPTION_NON_VOLATILE,
            0,
            NULL,
            &g_LogData.u1.hKey,
            &Disposition ) )
            break;
#endif
        RetCode = TRUE;
    } while ( 0 );

    return RetCode;
}

ULONG UnInitLog_Reg( )
{
    if ( NULL != g_LogData.u1.hKey )
        RegCloseKey( g_LogData.u1.hKey );

    g_LogData.u1.hKey = NULL;
    g_LogData.Init = FALSE;

    return TRUE;
}

ULONG ClearLog_Reg( void )
{
    ULONG RetCode;
    ULONG Disposition;

    if ( NULL == g_LogData.u1.hKey )
        return TRUE;

    RetCode = FALSE;

    do
    {
        RegCloseKey( g_LogData.u1.hKey );
        RegDeleteKey( HKEY_LOCAL_MACHINE, g_LogData.tszLogName );

        g_LogData.u1.hKey = NULL;
        g_LogData.Index = 0;
        if ( ERROR_SUCCESS != RegCreateKeyEx( HKEY_LOCAL_MACHINE,
            g_LogData.tszLogName,
            0,
            0,
            0,
            0,
            NULL,
            &g_LogData.u1.hKey,
            &Disposition ) )
            break;

        RetCode = TRUE;
    } while ( 0 );

    return RetCode;
}

ULONG AddLog_RegA( )
{
    ULONG RetCode;
    ULONG Bytes;
#ifndef _WIN32_WCE
    CHAR aszIndex[16];
#else
    WCHAR wszIndex[16];
#endif

    do
    {
        RetCode = FALSE;
        if ( NULL == g_LogData.u1.hKey )
            break;

        if ( g_LogData.EnableLogTime && !( g_LogData.Flags & LOG_FLAGS_EXTERN ) )
            LogTimeA( g_LogData.lpaszBuffer, g_LogData.LengthA );

#ifndef _WIN32_WCE
        sprintf( aszIndex, ( "%04d" ), g_LogData.Index );
        g_LogData.Index++;
        Bytes = ( strlen( g_LogData.lpaszBuffer ) + 1 ) * sizeof( CHAR );
        RetCode = RegSetValueExA( g_LogData.u1.hKey,
            aszIndex,
            0,
            REG_SZ,
            ( PBYTE )g_LogData.lpaszBuffer,
            Bytes
            );
#else
        swprintf( wszIndex, L"%04d", g_LogData.Index );
        g_LogData.Index++;
        Bytes = ( MultiByteToWideChar( CP_ACP,
            0,
            g_LogData.lpaszBuffer,
            - 1,
            g_LogData.lpwszBuffer,
            g_LogData.LengthW
            ) + 1 ) * sizeof( WCHAR );
        RetCode = RegSetValueExW( g_LogData.u1.hKey,
            wszIndex,
            0,
            REG_SZ,
            ( PBYTE )g_LogData.lpwszBuffer,
            Bytes
            );
#endif
        if ( ERROR_SUCCESS != RetCode )
            break;

        RetCode = Bytes;
    } while ( 0 );

    return RetCode;
}

ULONG AddLog_RegW( )
{
    ULONG RetCode;
    ULONG Bytes;
    WCHAR wszIndex[16];

    do
    {
        RetCode = FALSE;
        if ( NULL == g_LogData.u1.hKey )
            break;

        if ( g_LogData.EnableLogTime && !( g_LogData.Flags & LOG_FLAGS_EXTERN ) )
            LogTimeW( g_LogData.lpwszBuffer, g_LogData.LengthW );

        swprintf( wszIndex, L"%04d", g_LogData.Index );
        g_LogData.Index++;
        Bytes = ( wcslen( g_LogData.lpwszBuffer ) + 1 ) * sizeof( WCHAR );
        RetCode = RegSetValueExW( g_LogData.u1.hKey,
            wszIndex,
            0,
            REG_SZ,
            ( PBYTE )g_LogData.lpwszBuffer,
            Bytes
            );
        if ( ERROR_SUCCESS != RetCode )
            break;

        RetCode = Bytes;
    } while ( 0 );

    return RetCode;
}

/*
///////////////////////////////////////////////////////////////////////////////
// LOG_CONTROL
///////////////////////////////////////////////////////////////////////////////
*/
HWND CreateLogWindow( HINSTANCE hInstance, LPCTSTR lptszWindowTitle, WNDPROC WndProc )
{
    HWND hWindow;
    HWND hEdit;
    ULONG Style;
    int ScreenX;
    int ScreenY;
    int Cx;
    int Cy;
    WNDCLASS WndCls;
    RECT RtLogWindow;
    const TCHAR tszLogWindowClass[] = _T( "_LogEditWindow_" );

    WndCls.style = CS_HREDRAW | CS_VREDRAW;
    WndCls.lpfnWndProc = WndProc;
    WndCls.cbClsExtra = 0;
    WndCls.cbWndExtra = 0;
    WndCls.hInstance = hInstance;
    WndCls.hIcon = NULL;
    WndCls.hCursor = LoadCursor( NULL, IDC_ARROW );
    WndCls.hbrBackground = ( HBRUSH ) ( COLOR_WINDOW + 1 );
    WndCls.lpszMenuName = NULL;
    WndCls.lpszClassName = tszLogWindowClass;

    RegisterClass( &WndCls );

    ScreenX = GetSystemMetrics( SM_CXSCREEN );
    ScreenY = GetSystemMetrics( SM_CYSCREEN );

#ifndef _WIN32_WCE
    hWindow = CreateWindow( tszLogWindowClass,
        lptszWindowTitle,
        WS_OVERLAPPEDWINDOW,
        0,
        0,
        ScreenX / 2,
        ScreenY / 2,
        NULL,
        NULL,
        hInstance,
        0
        );
    Style = WS_CHILD | WS_BORDER | WS_HSCROLL | WS_VSCROLL | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE;
#else

#define WS_OVERLAPPEDWINDOW ( WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX )

    hWindow = CreateWindow( tszLogWindowClass,
        lptszWindowTitle,
        WS_OVERLAPPEDWINDOW,
        0,
        20,
        ScreenX / 2,
        ScreenY / 3,
        NULL,
        NULL,
        hInstance,
        0
        );
    Style = WS_CHILD | WS_BORDER | WS_HSCROLL | WS_VSCROLL | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE;
#endif

    GetClientRect( hWindow, &RtLogWindow );
    Cx = RtLogWindow.right - RtLogWindow.left;
    Cy = RtLogWindow.bottom - RtLogWindow.top;

    hEdit = CreateWindow( _T( "EDIT" ),
        NULL,
        Style,
        0,
        0,
        Cx,
        Cy,
        hWindow,
        NULL,
        hInstance,
        0
        );

#ifndef _WIN32_WCE
    SetWindowPos( hWindow, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
#else
    SetWindowPos( hWindow, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
#endif

    ShowWindow( hWindow, SW_SHOW );
    ShowWindow( hEdit, SW_SHOW );
    UpdateWindow( hWindow );

    return hEdit;
}

LRESULT CALLBACK LogWndProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
    switch ( Msg )
    {
    case WM_SIZE :
        switch ( wParam )
        {
        case SIZE_RESTORED :
        case SIZE_MAXSHOW :
        case SIZE_MAXIMIZED :
            SetWindowPos( g_LogData.u1.hControl, HWND_TOP, 0, 0, LOWORD( lParam ), HIWORD( lParam ), SWP_SHOWWINDOW );
            break;
        }
        break;

    case WM_SETFOCUS :
        SetFocus( g_LogData.u1.hControl );
        break;

    default :
        return DefWindowProc( hWnd, Msg, wParam, lParam );
    }

    return 0;
}

ULONG WINAPI CreateLogWindowThread( LPVOID Context )
{
    MSG Msg;
    HANDLE hEvent;
    HWND hParent;
    register HWND hEdit;
    register TCHAR TChar;
    static BOOL TopMost = FALSE;

    hEvent = *( ( PHANDLE )Context );
    g_LogData.u1.hControl = CreateLogWindow( NULL, g_LogData.tszLogName, LogWndProc );
    if ( hEvent )
        SetEvent( hEvent );

    if ( g_LogData.u1.hControl == NULL )
        return 0;

    SendMessage( g_LogData.u1.hControl, EM_SETREADONLY, ( WPARAM )TRUE, 0 );
    while ( GetMessage( &Msg, NULL, 0, 0 ) )
    {
        if ( Msg.message == WM_KEYDOWN && Msg.wParam == VK_ESCAPE )
            break;

        hEdit = g_LogData.u1.hControl;
        if ( Msg.hwnd == hEdit )
        {
            if ( Msg.message == WM_KEYDOWN && GetKeyState( VK_CONTROL ) & 0x8000 )
            {
                TChar = ( TCHAR )Msg.wParam;
                if ( TChar >= _T( 'a' ) && TChar <= _T( 'z' ) )
                    TChar -= ( _T( 'a' ) - _T( 'A' ) );

                if ( TChar == _T( 'A' ) )
                    SendMessage( hEdit, EM_SETSEL, 0, - 1 );
                else if ( TChar == _T( 'C' ) )
                    SendMessage( hEdit, WM_COPY, 0, 0 );
                else if ( TChar == _T( 'X' ) )
                    SendMessage( hEdit, WM_CUT, 0, 0 );
                else if ( TChar == _T( 'V' ) )
                    SendMessage( hEdit, WM_PASTE, 0, 0 );
                else if ( TChar == _T( 'Z' ) )
                    SendMessage( hEdit, WM_UNDO, 0, 0 );
                else if ( TChar == _T( 'T' ) )
                {
                    hParent = GetParent( hEdit );
                    if ( TopMost )
                        SetWindowPos( hParent, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
                    else
                        SetWindowPos( hParent, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
                    TopMost = !TopMost;
                }
                else if ( TChar == _T( 'R' ) )
                {
                    if ( GetWindowLong( hEdit, GWL_STYLE ) & ES_READONLY )
                        SendMessage( hEdit, EM_SETREADONLY, ( WPARAM )FALSE, 0 );
                    else
                        SendMessage( hEdit, EM_SETREADONLY, ( WPARAM )TRUE, 0 );
                }
                continue;
            }
            else if ( Msg.message == WM_LBUTTONDBLCLK )
            {
                if ( GetKeyState( VK_CONTROL ) & 0x8000 )
                    SetWindowText( hEdit, _T( "" ) );
                continue;
            }
        }
        TranslateMessage( &Msg );
        DispatchMessage( &Msg );
    }

    return TRUE;
}

/*
///////////////////////////////////////////////////////////////////////////////
// LOG_CONTROL
///////////////////////////////////////////////////////////////////////////////
*/
ULONG InitLog_Control( )
{
    ULONG RetCode;
    HANDLE hEvent;
    HANDLE hThread;
    ULONG ThreadId;

    do
    {
        RetCode = FALSE;
        hThread = NULL;
        hEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
        if ( hEvent == NULL )
            break;

        hThread = CreateThread( NULL, 0, CreateLogWindowThread, &hEvent, 0, &ThreadId );
        if ( hThread == NULL )
            break;

        WaitForSingleObject( hEvent, INFINITE );
        RetCode = IsWindow( g_LogData.u1.hControl );
    } while ( 0 );

    if ( hThread )
        CloseHandle( hThread );

    if ( hEvent )
        CloseHandle( hEvent );

    return RetCode;
}

ULONG UnInitLog_Control( )
{
    if ( IsWindow( g_LogData.u1.hControl ) )
        SendMessage( GetParent( g_LogData.u1.hControl ), WM_CLOSE, 0, 0 );

    g_LogData.u1.hControl = NULL;
    g_LogData.Init = FALSE;

    return TRUE;
}

LONG BackLog_Control( LONG Distance, ULONG Position )
{
    LONG RetCode;
    ULONG Selection;

    RetCode = 0;
    if ( IsWindow( g_LogData.u1.hControl ) )
    {
        if ( Position == LOG_POSITION_BEGIN )
        {
            SendMessage( g_LogData.u1.hControl, EM_SETSEL, ( WPARAM ) Distance, - 1 );
        }
        else if ( Position == LOG_POSITION_END )
        {
            Selection = SendMessage( g_LogData.u1.hControl, EM_GETSEL, 0, 0 );
            SendMessage( g_LogData.u1.hControl, EM_SETSEL, HIWORD( Selection ) + Distance, - 1 );
        }
        else
        {
            Selection = SendMessage( g_LogData.u1.hControl, EM_GETSEL, 0, 0 );
            SendMessage( g_LogData.u1.hControl, EM_SETSEL, HIWORD( Selection ) + Distance, - 1 );
        }
        RetCode = SendMessage( g_LogData.u1.hControl, EM_REPLACESEL, ( WPARAM )FALSE, ( LPARAM )_T( "" ) );
    }

    return RetCode;
}

LONGLONG BackLog_ControlEx( LONGLONG Distance, ULONG Position )
{
    LONG RetCode;
    ULONG Selection;

    RetCode = 0;
    if ( IsWindow( g_LogData.u1.hControl ) )
    {
        if ( Position == LOG_POSITION_BEGIN )
        {
            SendMessage( g_LogData.u1.hControl, EM_SETSEL, ( WPARAM ) Distance, - 1 );
        }
        else if ( Position == LOG_POSITION_END )
        {
            Selection = SendMessage( g_LogData.u1.hControl, EM_GETSEL, 0, 0 );
            SendMessage( g_LogData.u1.hControl, EM_SETSEL, HIWORD( Selection ) + ( ULONG )Distance, - 1 );
        }
        else
        {
            Selection = SendMessage( g_LogData.u1.hControl, EM_GETSEL, 0, 0 );
            SendMessage( g_LogData.u1.hControl, EM_SETSEL, HIWORD( Selection ) + ( ULONG )Distance, - 1 );
        }
        RetCode = SendMessage( g_LogData.u1.hControl, EM_REPLACESEL, ( WPARAM )FALSE, ( LPARAM )_T( "" ) );
    }

    return RetCode;
}

ULONG ClearLog_Control( void )
{
    if ( IsWindow( g_LogData.u1.hControl ) )
    {
        SendMessage( g_LogData.u1.hControl, EM_SETSEL, 0, - 1 );
        SendMessage( g_LogData.u1.hControl, EM_REPLACESEL, ( WPARAM )FALSE, ( LPARAM )_T( "" ) );
        return TRUE;
    }

    return FALSE;
}

ULONG AddLog_ControlA( )
{
#ifndef _WIN32_WCE
    if ( g_LogData.EnableLogTime && !( g_LogData.Flags & LOG_FLAGS_EXTERN ) )
        LogTimeA( g_LogData.lpaszBuffer, g_LogData.LengthA );

    SendMessageA( g_LogData.u1.hControl, EM_SETSEL, ( WPARAM ) - 1, 0 );
    SendMessageA( g_LogData.u1.hControl, EM_REPLACESEL, ( WPARAM )FALSE, ( LPARAM )g_LogData.lpaszBuffer );
#endif

    return TRUE;
}

ULONG AddLog_ControlW( )
{
    if ( g_LogData.EnableLogTime && !( g_LogData.Flags & LOG_FLAGS_EXTERN ) )
        LogTimeW( g_LogData.lpwszBuffer, g_LogData.LengthW );

    SendMessageW( g_LogData.u1.hControl, EM_SETSEL, ( WPARAM ) - 1, 0 );
    SendMessageW( g_LogData.u1.hControl, EM_REPLACESEL, ( WPARAM )FALSE, ( LPARAM )g_LogData.lpwszBuffer );

    return TRUE;
}

/*
///////////////////////////////////////////////////////////////////////////////
// Global
///////////////////////////////////////////////////////////////////////////////
*/
ULONG InitLog( const PVOID LogData, ULONG LogMethod, ULONG Enable )
{
    g_LogData.LengthA = SIZE_OF_ARRAY( g_LogData.aszBuffer );
    g_LogData.LengthW = SIZE_OF_ARRAY( g_LogData.wszBuffer );
    g_LogData.lpaszBuffer = g_LogData.aszBuffer;
    g_LogData.lpwszBuffer = g_LogData.wszBuffer;

    if ( LogData != NULL )
        _tcsncpy( g_LogData.tszLogName, ( LPTSTR )LogData, SIZE_OF_ARRAY( g_LogData.tszLogName ) );
    else
        g_LogData.tszLogName[0] = _T( '\0' );
    g_LogData.tszLogName[SIZE_OF_ARRAY( g_LogData.tszLogName ) - 1] = _T( '\0' );

    UNINIT_LOG( );
    SET_LOG_METHOD( LogMethod );

    g_LogData.Flags = 0;
    g_LogData.Enable = Enable;
    g_LogData.EnableLogTime = FALSE;

    return g_LogData.Init;
}

ULONG UnInitLog( )
{
    switch ( g_LogData.LogMethod )
    {
    case LOG_FILE :
        UnInitLog_File( );
        break;

    case LOG_REGISTRY :
        UnInitLog_Reg( );
        break;

    case LOG_CONTROL :
        UnInitLog_Control( );
        break;
    }

    g_LogData.LogMethod = LOG_NONE;
    g_LogData.Init = FALSE;
    g_LogData.Enable = FALSE;

    return TRUE;
}

ULONG IsLogEnabled( )
{
    if ( g_LogData.Init )
        return g_LogData.Enable;
    else
        return FALSE;
}

ULONG IsLogTimeEnabled( )
{
    if ( g_LogData.Init )
        return g_LogData.EnableLogTime;
    else
        return FALSE;
}

ULONG SetLogHandle( HANDLE hHandle )
{
    /* UnInit previous */
    if ( g_LogData.LogMethod == LOG_FILE )
        UnInitLog_File( );
    else if ( g_LogData.LogMethod == LOG_REGISTRY )
        UnInitLog_Reg( );
    else if ( g_LogData.LogMethod == LOG_CONTROL )
        UnInitLog_Control( );

    g_LogData.u1.hHandle = hHandle;
    g_LogData.Init = TRUE;

    return TRUE;
}

HANDLE GetLogHandle( )
{
    return g_LogData.u1.hHandle;
}

ULONG SetLog_Method( ULONG LogMethod )
{
    if ( g_LogData.LogMethod == LogMethod )
    {
        EnableLog( );
        return TRUE;
    }

    if ( LogMethod <= LOG_MIN || LogMethod >= LOG_MAX )
        LogMethod = LOG_NONE;

    /* UnInit previous */
    if ( g_LogData.LogMethod == LOG_FILE )
        UnInitLog_File( );
    else if ( g_LogData.LogMethod == LOG_REGISTRY )
        UnInitLog_Reg( );
    else if ( g_LogData.LogMethod == LOG_CONTROL )
        UnInitLog_Control( );

    /* Init new */
    if ( LogMethod == LOG_FILE )
        g_LogData.Init = InitLog_File( );
    else if ( LogMethod == LOG_REGISTRY )
        g_LogData.Init = InitLog_Reg( );
    else if ( LogMethod == LOG_CONTROL )
        g_LogData.Init = InitLog_Control( );

    g_LogData.LogMethod = LogMethod;

    return TRUE;
}

ULONG GetLog_Method( )
{
    return g_LogData.LogMethod;
}

ULONG LogTimeA( CHAR * lpaszBuffer, ULONG Size )
{
    ULONG RetCode;
    CHAR aszLocal[LOG_BUFFER_SIZE];

#if !defined( _KERNEL_MODE_ ) || defined( _WIN32_WCE )
    SYSTEMTIME SysTime;

    GetSystemTime( &SysTime );
    strncpy( aszLocal, lpaszBuffer, SIZE_OF_ARRAY( aszLocal ) );

    #ifdef _STRING_SAFE_
    RetCode = _snprintf( lpaszBuffer,
        Size / sizeof( CHAR ),
        "<%04d-%02d-%02d %02d:%02d:%02d>%s",
        SysTime.wYear,
        SysTime.wMonth,
        SysTime.wDay,
        SysTime.wHour,
        SysTime.wMinute,
        SysTime.wSecond,
        aszLocal
        );
    #else
    RetCode = sprintf( lpaszBuffer,
        "<%04d-%02d-%02d %02d:%02d:%02d>%s",
        SysTime.wYear,
        SysTime.wMonth,
        SysTime.wDay,
        SysTime.wHour,
        SysTime.wMinute,
        SysTime.wSecond,
        aszLocal
        );
    #endif
#else
    LARGE_INTEGER SysTime;
    LARGE_INTEGER LocalTime;

    if ( KeGetCurrentIrql( ) != PASSIVE_LEVEL )
        return - 1;

    KeQuerySystemTime( &SysTime );
    ExSystemTimeToLocalTime( &SysTime, &LocalTime );
    strncpy( aszLocal, lpaszBuffer, SIZE_OF_ARRAY( aszLocal ) );

    #ifdef _STRING_SAFE_
    RetCode = _snprintf( lpaszBuffer,
        Size / sizeof( CHAR ),
        "<%08X-%08X>%s",
        LocalTime.HighPart,
        LocalTime.LowPart,
        aszLocal
        );

    #else
    RetCode = sprintf( lpaszBuffer,
        "<%08X-%08X>%s",
        LocalTime.HighPart,
        LocalTime.LowPart,
        aszLocal
        );
    #endif
#endif

    return RetCode * sizeof( CHAR );
}

ULONG LogTimeW( WCHAR * lpwszBuffer, ULONG Size )
{
    ULONG RetCode;
    WCHAR wszLocal[LOG_BUFFER_SIZE];

#if !defined( _KERNEL_MODE_ ) || defined( _WIN32_WCE )
    SYSTEMTIME SysTime;

    GetSystemTime( &SysTime );
    wcsncpy( wszLocal, lpwszBuffer, SIZE_OF_ARRAY( wszLocal ) );

    #ifdef _STRING_SAFE_
    RetCode = _snwprintf( lpwszBuffer,
        Size / sizeof( WCHAR ),
        L"<%04d-%02d-%02d %02d:%02d:%02d>%s",
        SysTime.wYear,
        SysTime.wMonth,
        SysTime.wDay,
        SysTime.wHour,
        SysTime.wMinute,
        SysTime.wSecond,
        wszLocal
        );
    #else
    RetCode = swprintf( lpwszBuffer,
        L"<%04d-%02d-%02d %02d:%02d:%02d>%s",
        SysTime.wYear,
        SysTime.wMonth,
        SysTime.wDay,
        SysTime.wHour,
        SysTime.wMinute,
        SysTime.wSecond,
        wszLocal
        );
    #endif
#else
    LARGE_INTEGER SysTime;
    LARGE_INTEGER LocalTime;

    if ( KeGetCurrentIrql( ) != PASSIVE_LEVEL )
        return - 1;

    KeQuerySystemTime( &SysTime );
    ExSystemTimeToLocalTime( &SysTime, &LocalTime );
    wcsncpy( wszLocal, lpwszBuffer, SIZE_OF_ARRAY( wszLocal ) );

    #ifdef _STRING_SAFE_
    RetCode = _snwprintf( lpwszBuffer,
        Size / sizeof( WCHAR ),
        L"<%08X-%08X>%s",
        LocalTime.HighPart,
        LocalTime.LowPart,
        wszLocal
        );
    #else
    RetCode = swprintf( lpwszBuffer,
        L"<%08X-%08X>%s",
        LocalTime.HighPart,
        LocalTime.LowPart,
        wszLocal
        );
    #endif
#endif

    return RetCode * sizeof( WCHAR );
}

ULONG AddLogDispatch( )
{
    ULONG RetCode;

    switch ( g_LogData.LogMethod )
    {
    case LOG_FILE :
        RetCode = AddLog_File( );
        break;

    case LOG_REGISTRY :
        RetCode = AddLog_Reg( );
        break;

    case LOG_CONTROL :
        RetCode = AddLog_Control( );
        break;

    case LOG_DEBUG_STRING :
        OutputDebugString( g_LogData.SZ_LOG_BUFFER );
        RetCode = TRUE;
        break;

    case LOG_MESSAGEBOX :
        RetCode = MessageBox( NULL, g_LogData.SZ_LOG_BUFFER, g_LogData.tszLogName, MB_OK );
        break;

    default :
        RetCode = FALSE;
        break;
    }

    return RetCode;
}

__inline void ChangeFlags( )
{
    if ( g_LogData.Flags & LOG_FLAGS_EXTERN )
    {
        g_LogData.lpaszBuffer = g_LogData.aszBuffer;
        g_LogData.LengthA = SIZE_OF_ARRAY( g_LogData.aszBuffer );
        g_LogData.lpwszBuffer = g_LogData.wszBuffer;
        g_LogData.LengthW = SIZE_OF_ARRAY( g_LogData.wszBuffer );
        g_LogData.Flags &= ~LOG_FLAGS_EXTERN;
    }
}

ULONG _AddLogA( const CHAR * aszFormat )
{
    if ( !aszFormat || !g_LogData.Enable || g_LogData.LogMethod == LOG_NONE )
        return FALSE;

#if defined( _UNICODE ) || defined( _UNICODE )
    MultiByteToWideChar( CP_ACP,
        0,
        aszFormat,
        - 1,
        g_LogData.lpwszBuffer,
        g_LogData.LengthW
        );
    ChangeFlags( );
#else
    g_LogData.Flags |= LOG_FLAGS_EXTERN;
    g_LogData.lpaszBuffer = ( LPSTR )aszFormat;
#endif

    return AddLogDispatch( );
}

ULONG _AddLogW( const WCHAR * wszFormat )
{
    if ( !wszFormat || !g_LogData.Enable || g_LogData.LogMethod == LOG_NONE )
        return FALSE;

#if defined( _UNICODE ) || defined( _UNICODE )
    g_LogData.Flags |= LOG_FLAGS_EXTERN;
    g_LogData.lpwszBuffer = ( LPWSTR )wszFormat;
#else
    WideCharToMultiByte( CP_ACP,
        0,
        g_LogData.lpwszBuffer,
        - 1,
        g_LogData.lpaszBuffer,
        g_LogData.LengthA,
        0,
        0
        );
    ChangeFlags( );
#endif

    return AddLogDispatch( );
}

ULONG _AddLogLRA( const CHAR * aszFormat )
{
    ULONG RetCode;

    if ( !aszFormat || !g_LogData.Enable || g_LogData.LogMethod == LOG_NONE )
        return FALSE;

#if defined( _UNICODE ) || defined( _UNICODE )
    if ( *aszFormat )
    {
        MultiByteToWideChar( CP_ACP,
            0,
            aszFormat,
            - 1,
            g_LogData.lpwszBuffer,
            g_LogData.LengthW - 2
            );
        wcscat( g_LogData.lpwszBuffer, LR_W );
    }
    else
    {
        wcscpy( g_LogData.lpwszBuffer, LR_W );
    }
    ChangeFlags( );
    RetCode = AddLogDispatch( );
#else
    g_LogData.Flags |= LOG_FLAGS_EXTERN;
    if ( *aszFormat )
    {
        g_LogData.lpaszBuffer = ( LPSTR )aszFormat;
        RetCode = AddLogDispatch( );
    }
    else
    {
        RetCode = 0;
    }
    g_LogData.lpaszBuffer = LR_A;
    RetCode += AddLogDispatch( );
#endif

    return RetCode;
}

ULONG _AddLogLRW( const WCHAR * wszFormat )
{
    ULONG RetCode;

    if ( !wszFormat || !g_LogData.Enable || g_LogData.LogMethod == LOG_NONE )
        return FALSE;

#if defined( _UNICODE ) || defined( _UNICODE )
    g_LogData.Flags |= LOG_FLAGS_EXTERN;
    if ( *wszFormat )
    {
        g_LogData.lpwszBuffer = ( LPWSTR )wszFormat;
        RetCode = AddLogDispatch( );
    }
    else
    {
        RetCode = 0;
    }
    g_LogData.lpwszBuffer = LR_W;
    RetCode += AddLogDispatch( );
#else
    if ( *wszFormat )
    {
        WideCharToMultiByte( CP_ACP,
            0,
            g_LogData.lpwszBuffer,
            - 1,
            g_LogData.lpaszBuffer,
            g_LogData.LengthA - 2,
            0,
            0
            );
        strcat( g_LogData.lpaszBuffer, LR_A );
    }
    else
    {
        strcpy( g_LogData.lpaszBuffer, LR_A );
    }
    ChangeFlags( );
    RetCode = AddLogDispatch( );
#endif

    return RetCode;
}

ULONG AddLogA( const CHAR * aszFormat, ... )
{
    ULONG RetCode;
    va_list vlArgs;

    if ( !g_LogData.Enable || g_LogData.LogMethod == LOG_NONE )
        return FALSE;

    ChangeFlags( );

    va_start( vlArgs, aszFormat );
    RetCode = _vsnprintf( g_LogData.lpaszBuffer,
        g_LogData.LengthA,
        aszFormat,
        vlArgs
        );
    va_end( vlArgs );

#if defined( _UNICODE ) || defined( _UNICODE )
    RetCode = MultiByteToWideChar( CP_ACP,
        0,
        g_LogData.lpaszBuffer,
        - 1,
        g_LogData.lpwszBuffer,
        g_LogData.LengthW
        );
#endif

    return AddLogDispatch( );
}

ULONG AddLogW( const WCHAR * wszFormat, ... )
{
    ULONG RetCode;
    va_list vlArgs;

    if ( !g_LogData.Enable || g_LogData.LogMethod == LOG_NONE )
        return FALSE;

    ChangeFlags( );

    va_start( vlArgs, wszFormat );
    RetCode = _vsnwprintf( g_LogData.lpwszBuffer,
        g_LogData.LengthW,
        wszFormat,
        vlArgs
        );
    va_end( vlArgs );

#if !defined( _UNICODE ) && !defined( _UNICODE )
    RetCode = WideCharToMultiByte( CP_ACP,
        0,
        g_LogData.lpwszBuffer,
        - 1,
        g_LogData.lpaszBuffer,
        g_LogData.LengthA,
        0,
        0
        );
#endif
    
    return AddLogDispatch( );
}

ULONG AddLogLRA( const CHAR * aszFormat, ... )
{
    ULONG RetCode;
    va_list vlArgs;

    if ( !g_LogData.Enable || g_LogData.LogMethod == LOG_NONE )
        return FALSE;

    ChangeFlags( );

    va_start( vlArgs, aszFormat );
    RetCode = _vsnprintf( g_LogData.lpaszBuffer,
        g_LogData.LengthA - 2,
        aszFormat,
        vlArgs
        );
    va_end( vlArgs );

    strcat( g_LogData.lpaszBuffer, LR_A );
    RetCode += 2;

#if defined( _UNICODE ) || defined( _UNICODE )
    RetCode = MultiByteToWideChar( CP_ACP,
        0,
        g_LogData.lpaszBuffer,
        - 1,
        g_LogData.lpwszBuffer,
        g_LogData.LengthW
        );
#endif
   
    return AddLogDispatch( );
}

ULONG AddLogLRW( const WCHAR * wszFormat, ... )
{
    ULONG RetCode;
    va_list vlArgs;

    if ( !g_LogData.Enable || g_LogData.LogMethod == LOG_NONE )
        return FALSE;

    ChangeFlags( );

    va_start( vlArgs, wszFormat );
    RetCode = _vsnwprintf( g_LogData.lpwszBuffer,
        g_LogData.LengthW - 2,
        wszFormat,
        vlArgs
        );
    va_end( vlArgs );

    wcscat( g_LogData.lpwszBuffer, LR_W );
    RetCode += 2;

#if !defined( _UNICODE ) && !defined( _UNICODE )
    RetCode = WideCharToMultiByte( CP_ACP,
        0,
        g_LogData.lpwszBuffer,
        - 1,
        g_LogData.lpaszBuffer,
        g_LogData.LengthA,
        0,
        0
        );
#endif

    return AddLogDispatch( );
}

LONG BackLog( LONG Distance, ULONG Position )
{
    ULONG RetCode;

    RetCode = 0;
    switch ( g_LogData.LogMethod )
    {
    case LOG_FILE :
        RetCode = BackLog_File( Distance, Position );
        break;

    case LOG_CONTROL :
        RetCode = BackLog_Control( Distance, Position );
        break;
    }

    return RetCode;
}

LONGLONG BackLogEx( LONGLONG Distance, ULONG Position )
{
    LONGLONG RetCode;

    RetCode = 0;
    switch ( g_LogData.LogMethod )
    {
    case LOG_FILE :
        RetCode = BackLog_FileEx( Distance, Position );
        break;

    case LOG_CONTROL :
        RetCode = BackLog_ControlEx( Distance, Position );
        break;
    }

    return RetCode;
}

void ClearLog( )
{
    switch ( g_LogData.LogMethod )
    {
    case LOG_FILE :
        ClearLog_File( );
        break;

    case LOG_REGISTRY :
        ClearLog_Reg( );
        break;

    case LOG_CONTROL :
        ClearLog_Control( );
        break;
    }
}

void EnableLog( void )
{
    HWND hParent;

    g_LogData.Enable = TRUE;
    switch ( g_LogData.LogMethod )
    {
    case LOG_CONTROL :
        hParent = GetParent( g_LogData.u1.hControl );
        if ( hParent )
            ShowWindow( hParent, SW_SHOWNORMAL );
        else
            InitLog_Control( );
        break;
    }
}

void DisableLog( void )
{
    HWND hParent;

    g_LogData.Enable = FALSE;
    switch ( g_LogData.LogMethod )
    {
    case LOG_CONTROL :
        hParent = GetParent( g_LogData.u1.hControl );
        if ( hParent )
            ShowWindow( hParent, SW_HIDE );
        break;
    }
}

void EnableLogTime( void )
{
    g_LogData.EnableLogTime = TRUE;
}

void DisableLogTime( void )
{
    g_LogData.EnableLogTime = FALSE;
}

/*
///////////////////////////////////////////////////////////////////////////////
// E N D  O F  F I L E
///////////////////////////////////////////////////////////////////////////////
*/
#endif /* DISABLE_LOG_FUNC */