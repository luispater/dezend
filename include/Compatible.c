/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   Compatible.c
//  Version     :   1.0
//  Creator     :   RM
//  Create Date :   2006-01-01
//  Comment     :
//
///////////////////////////////////////////////////////////////////////////////
*/

#include < stdio.h >
#include < stdlib.h >
#include < string.h >
#include < time.h >
#include < direct.h >
#include < limits.h >
#include "Compatible.h"

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
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

/* Non-window os */
#ifndef _MSC_VER

VOID WINAPI InitializeCriticalSection(
    LPCRITICAL_SECTION lpCriticalSection
    )
{
}

VOID WINAPI EnterCriticalSection(
    LPCRITICAL_SECTION lpCriticalSection
    )
{
}

VOID WINAPI LeaveCriticalSection(
    LPCRITICAL_SECTION lpCriticalSection
    )
{
}

int WINAPI MultiByteToWideChar(
    UINT CodePage,
    DWORD dwFlags,
    LPCSTR lpMultiByteStr,
    int cchMultiByte,
    LPWSTR lpWideCharStr,
    int cchWideChar
    )
{
    return mbstowcs( lpWideCharStr, lpMultiByteStr, cchMultiByte );
}

int WINAPI WideCharToMultiByte(
    UINT CodePage,
    DWORD dwFlags,
    LPCWSTR lpWideCharStr,
    int cchWideChar,
    LPSTR lpMultiByteStr,
    int cchMultiByte,
    LPCSTR lpDefaultChar,
    LPBOOL lpUsedDefaultChar
    )
{
    return wcstombs( lpMultiByteStr, lpWideCharStr, cchWideChar );
}

VOID WINAPI DebugBreak(
    VOID
    )
{
}

VOID WINAPI RaiseException(
    DWORD dwExceptionCode,
    DWORD dwExceptionFlags,
    DWORD nNumberOfArguments,
    CONST DWORD *lpArguments
    )
{
}

DWORD WINAPI GetTickCount(
    VOID
    )
{
    return clock( );
}

VOID WINAPI GetSystemTime(
    LPSYSTEMTIME lpSystemTime
    )
{
}

VOID WINAPI GetLocalTime(
    LPSYSTEMTIME lpSystemTime
    )
{
}

VOID WINAPI GetSystemTimeAsFileTime(
    LPFILETIME lpSystemTimeAsFileTime
    )
{
}

BOOL WINAPI SystemTimeToFileTime(
    CONST SYSTEMTIME *lpSystemTime,
    LPFILETIME lpFileTime
    )
{
    return FALSE;
}

BOOL WINAPI FileTimeToLocalFileTime(
    CONST FILETIME *lpFileTime,
    LPFILETIME lpLocalFileTime
    )
{
    return FALSE;
}

DWORD WINAPI GetLastError(
    VOID
    )
{
    return 0;
}

BOOL WINAPI CloseHandle(
    HANDLE hObject
    )
{
    return fclose( ( FILE * )hObject );
}

HANDLE WINAPI CreateEventA(
    LPSECURITY_ATTRIBUTES lpEventAttributes,
    BOOL bManualReset,
    BOOL bInitialState,
    LPCSTR lpName
    )
{
    return NULL;
}

HANDLE WINAPI CreateEventW(
    LPSECURITY_ATTRIBUTES lpEventAttributes,
    BOOL bManualReset,
    BOOL bInitialState,
    LPCWSTR lpName
    )
{
    return NULL;
}

BOOL WINAPI SetEvent(
    HANDLE hEvent
    )
{
    return FALSE;
}

DWORD WINAPI WaitForSingleObject(
    HANDLE hHandle,
    DWORD dwMilliseconds
    )
{
    return FALSE;
}

HANDLE WINAPI GetCurrentProcess(
    VOID
    )
{
    return NULL;
}

BOOL WINAPI ReadProcessMemory(
    HANDLE hProcess,
    LPCVOID lpBaseAddress,
    LPVOID lpBuffer,
    DWORD nSize,
    LPDWORD lpNumberOfBytesRead
    )
{
    return FALSE;
}

BOOL WINAPI WriteProcessMemory(
    HANDLE hProcess,
    LPVOID lpBaseAddress,
    LPVOID lpBuffer,
    DWORD nSize,
    LPDWORD lpNumberOfBytesWritten
    )
{
    return FALSE;
}

HANDLE WINAPI CreateThread(
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    DWORD dwStackSize,
    LPTHREAD_START_ROUTINE lpStartAddress,
    LPVOID lpParameter,
    DWORD dwCreationFlags,
    LPDWORD lpThreadId
    )
{
    return NULL;
}

HMODULE WINAPI GetModuleHandleA(
    LPCSTR lpModuleName
    )
{
    return NULL;
}

HMODULE WINAPI GetModuleHandleW(
    LPCWSTR lpModuleName
    )
{
    return NULL;
}

DWORD WINAPI GetModuleFileNameA(
    HMODULE hModule,
    LPSTR lpFilename,
    DWORD nSize
    )
{
    return 0;
}

DWORD WINAPI GetModuleFileNameW(
    HMODULE hModule,
    LPWSTR lpFilename,
    DWORD nSize
    )
{
    return 0;
}

BOOL WINAPI CreateDirectoryA(
    LPCSTR lpPathName,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes
    )
{
    return mkdir( lpPathName );
}

BOOL WINAPI CreateDirectoryW(
    LPCWSTR lpPathName,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes
    )
{
    char Buffer[512];

    wcstombs( Buffer, lpPathName, wcslen( lpPathName ) );

    return CreateDirectoryA( Buffer, lpSecurityAttributes );
}

HANDLE WINAPI CreateFileA(
    LPCSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile
    )
{
    char Buffer[256];

    if ( dwDesiredAccess & GENERIC_WRITE )
    {
        Buffer[0] = 'w';
        Buffer[1] = 'b';
        Buffer[2] = '\0';
    }
    else
    {
        Buffer[0] = 'r';
        Buffer[1] = 'b';
        Buffer[2] = '\0';
    }

    return fopen( lpFileName, Buffer );
}

HANDLE WINAPI CreateFileW(
    LPCWSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile
    )
{
    char Buffer[512];

    wcstombs( Buffer, lpFileName, wcslen( lpFileName ) );

    return CreateFileA( Buffer,
        dwDesiredAccess,
        dwShareMode,
        lpSecurityAttributes,
        dwCreationDisposition,
        dwFlagsAndAttributes,
        hTemplateFile
        );
}

BOOL WINAPI SetEndOfFile(
    HANDLE hFile
    )
{
    return fseek( ( FILE * )hFile, 0L, SEEK_END );
}

DWORD WINAPI SetFilePointer(
    HANDLE hFile,
    LONG lDistanceToMove,
    PLONG lpDistanceToMoveHigh,
    DWORD dwMoveMethod
    )
{
    fpos_t FilePos;

    if ( dwMoveMethod == FILE_BEGIN )
    {
        FilePos.lopart = lDistanceToMove;
        if ( lpDistanceToMoveHigh )
            FilePos.hipart = *lpDistanceToMoveHigh;
        else
            FilePos.hipart = 0;
    }
    else
    {
        if ( dwMoveMethod == FILE_END )
            fseek( ( FILE * )hFile, 0L, SEEK_END );
        fgetpos( ( FILE * )hFile, &FilePos );
        if ( lDistanceToMove > 0 )
        {
            if ( FilePos.lopart + ( ULONG )lDistanceToMove >= ( ULONG )lDistanceToMove )
            {
                FilePos.lopart += lDistanceToMove;
                if ( lpDistanceToMoveHigh )
                    FilePos.hipart = *lpDistanceToMoveHigh;
                else
                    FilePos.hipart = 0;
            }
            else
            {
                FilePos.lopart += lDistanceToMove;
                if ( lpDistanceToMoveHigh )
                    FilePos.hipart = *lpDistanceToMoveHigh + 1;
                else
                    FilePos.hipart = 1;
            }
        }
        else
        {
            if ( FilePos.lopart + lDistanceToMove > 0 )
            {
                FilePos.lopart += lDistanceToMove;
                if ( lpDistanceToMoveHigh )
                    FilePos.hipart = *lpDistanceToMoveHigh;
                else
                    FilePos.hipart = 0;
            }
            else
            {
                FilePos.lopart += lDistanceToMove;
                if ( lpDistanceToMoveHigh )
                    FilePos.hipart = *lpDistanceToMoveHigh - 1;
                else
                    FilePos.hipart = 0;
            }
        }
    }

    return fsetpos( ( FILE * )hFile, &FilePos );
}

BOOL WINAPI WriteFile(
    HANDLE hFile,
    LPCVOID lpBuffer,
    DWORD nNumberOfBytesToWrite,
    LPDWORD lpNumberOfBytesWritten,
    LPOVERLAPPED lpOverlapped
    )
{
    BOOL RetCode;
    ULONG Length;

    Length = fwrite( lpBuffer, nNumberOfBytesToWrite, 1, ( FILE * )hFile );
    if ( Length > 0 )
    {
        if ( lpNumberOfBytesWritten )
            *lpNumberOfBytesWritten = Length;
        RetCode = TRUE;
    }
    else
    {
        RetCode = FALSE;
    }

    return RetCode;
}

BOOL WINAPI ReadFile(
    HANDLE hFile,
    LPVOID lpBuffer,
    DWORD nNumberOfBytesToRead,
    LPDWORD lpNumberOfBytesRead,
    LPOVERLAPPED lpOverlapped
    )
{
    BOOL RetCode;
    ULONG Length;

    Length = fread( lpBuffer, nNumberOfBytesToRead, 1, ( FILE * )hFile );
    if ( Length > 0 )
    {
        if ( lpNumberOfBytesRead )
            *lpNumberOfBytesRead = Length;
        RetCode = TRUE;
    }
    else
    {
        RetCode = FALSE;
    }

    return RetCode;
}

LONG APIENTRY RegCloseKey(
    HKEY hKey
    )
{
    return - 1;
}

LONG APIENTRY RegCreateKeyEx(
    HKEY hKey,
    LPCSTR lpSubKey,
    DWORD Reserved,
    LPSTR lpClass,
    DWORD dwOptions,
    REGSAM samDesired,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    PHKEY phkResult,
    LPDWORD lpdwDisposition
    )
{
    return - 1;
}

LONG APIENTRY RegDeleteKey(
    HKEY hKey,
    LPCSTR lpSubKey
    )
{
    return - 1;
}

LONG APIENTRY RegSetValueExA(
    HKEY hKey,
    LPCSTR lpValueName,
    DWORD Reserved,
    DWORD dwType,
    CONST BYTE *lpData,
    DWORD cbData
    )
{
    return - 1;
}

LONG APIENTRY RegSetValueExW(
    HKEY hKey,
    LPCWSTR lpValueName,
    DWORD Reserved,
    DWORD dwType,
    CONST BYTE *lpData,
    DWORD cbData
    )
{
    return - 1;
}

LRESULT WINAPI SendMessageA(
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam
    )
{
    return - 1;
}

SHORT WINAPI GetKeyState(
    int nVirtKey
    )
{
    return 0;
}

LONG WINAPI GetWindowLong(
    HWND hWnd,
    int nIndex
    )
{
    return - 1;
}

BOOL WINAPI TranslateMessage(
    CONST void *lpMsg
    )
{
    return FALSE;
}

LONG WINAPI DispatchMessage(
    CONST void *lpMsg
    )
{
    return - 1;
}

LRESULT WINAPI SendMessageW(
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam
    )
{
    return - 1;
}

int WINAPI GetSystemMetrics(
    int nIndex
    )
{
    return 0;
}

ATOM WINAPI RegisterClass(
    CONST PWNDCLASSW lpWndClass
    )
{
    return 0;
}

HWND WINAPI CreateWindowExA(
    DWORD dwExStyle,
    LPCSTR lpClassName,
    LPCSTR lpWindowName,
    DWORD dwStyle,
    int X,
    int Y,
    int nWidth,
    int nHeight,
    HWND hWndParent ,
    HMENU hMenu,
    HINSTANCE hInstance,
    LPVOID lpParam
    )
{
    return NULL;
}

HWND WINAPI CreateWindowExW(
    DWORD dwExStyle,
    LPCWSTR lpClassName,
    LPCWSTR lpWindowName,
    DWORD dwStyle,
    int X,
    int Y,
    int nWidth,
    int nHeight,
    HWND hWndParent ,
    HMENU hMenu,
    HINSTANCE hInstance,
    LPVOID lpParam
    )
{
    return NULL;
}

BOOL WINAPI GetClientRect(
    HWND hWnd,
    LPRECT lpRect
    )
{
    return FALSE;
}

HWND WINAPI GetParent(
    HWND hWnd
    )
{
    return NULL;
}

BOOL WINAPI IsWindow(
    HWND hWnd
    )
{
    return FALSE;
}

BOOL WINAPI SetWindowPos(
    HWND hWnd,
    HWND hWndInsertAfter,
    int X,
    int Y,
    int cx,
    int cy,
    UINT uFlags
    )
{
    return FALSE;
}

BOOL WINAPI ShowWindow(
    HWND hWnd,
    int nCmdShow
    )
{
    return FALSE;
}

BOOL WINAPI UpdateWindow(
    HWND hWnd
    )
{
    return FALSE;
}

HWND WINAPI SetFocus(
    HWND hWnd
    )
{
    return NULL;
}

LRESULT CALLBACK DefWindowProc(
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam
    )
{
    return - 1;
}

HCURSOR WINAPI LoadCursorA(
    HINSTANCE hInstance,
    LPCSTR lpCursorName
    )
{
    return NULL;
}

HCURSOR WINAPI LoadCursorW(
    HINSTANCE hInstance,
    LPCWSTR lpCursorName
    )
{
    return NULL;
}

/*
///////////////////////////////////////////////////////////////////////////////
// E N D  O F  F I L E
///////////////////////////////////////////////////////////////////////////////
*/
#endif