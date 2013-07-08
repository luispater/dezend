/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   Compatible.h
//  Version     :   1.0
//  Creator     :   RM
//  Create Date :   2006-01-01
//  Comment     :
//
///////////////////////////////////////////////////////////////////////////////
*/

#ifndef __COMPATIBLE_H__
#define __COMPATIBLE_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Plateform */

#ifndef _MSC_VER
/* Non-window os */

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/
#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef NULL
#define NULL 0
#endif

#define WINAPI __stdcall
#define APIENTRY WINAPI
#define CALLBACK WINAPI
#define VOID void
#define FAR
#define NEAR near
#define CONST const

#define GENERIC_READ ( 0x80000000L )
#define GENERIC_WRITE ( 0x40000000L )
#define GENERIC_EXECUTE ( 0x20000000L )
#define GENERIC_ALL ( 0x10000000L )

#define FILE_BEGIN 0
#define FILE_CURRENT 1
#define FILE_END 2

/* Memery */
#define HEAP_ALLOC( Size ) malloc( Size )
#define HEAP_FREE( Buffer ) free( Buffer )
#define HEAP_REALLOC( Buffer, Size ) realloc( Buffer, Size )

/*
///////////////////////////////////////////////////////////////////////////////
// S T R U C T U R E S
///////////////////////////////////////////////////////////////////////////////
*/
typedef void *PVOID;
typedef void FAR *LPVOID;
typedef const void FAR *LPCVOID;

typedef char CHAR, *PCHAR, FAR *LPCHAR;
typedef unsigned short WCHAR, *PWCHAR;
typedef unsigned char UCHAR, *PUCHAR, FAR *LPUCHAR;
typedef short SHORT, *PSHORT, FAR *LPSHORT;
typedef unsigned short USHORT, *PUSHORT, FAR *LPUSHORT;
typedef int INT, *PINT;
typedef unsigned int UINT, *PUINT;
typedef long LONG, *PLONG, FAR *LPLONG;
typedef unsigned long ULONG, *PULONG, FAR *LPULONG;

typedef unsigned char BYTE, *PBYTE, FAR *LPBYTE;
typedef unsigned short WORD, *PWORD, FAR *LPWORD;
typedef unsigned long DWORD, *PDWORD, FAR *LPDWORD;
typedef long BOOL, *PBOOL, FAR *LPBOOL;

typedef char *LPSTR;
typedef unsigned short *LPWSTR;
typedef const char *LPCSTR;
typedef const unsigned short *LPCWSTR;

typedef PVOID HANDLE;
typedef PVOID HMODULE;
typedef PVOID LPCRITICAL_SECTION;
typedef PVOID LPSECURITY_ATTRIBUTES;
typedef PVOID LPOVERLAPPED;

typedef PVOID HKEY, *PHKEY;
typedef PVOID HINSTANCE, *PHINSTANCE;
typedef PVOID HWND, *PHWND;
typedef PVOID HMENU, *PHMENU;
typedef PVOID HCURSOR, *PHCURSOR;

typedef DWORD REGSAM;
typedef UINT WPARAM;
typedef UINT LPARAM;
typedef LONG LRESULT;
typedef WORD ATOM;
typedef PVOID PWNDCLASSW;

typedef struct _RECT {
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
} RECT, *PRECT, FAR *LPRECT;

typedef struct _SYSTEMTIME {
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, FAR *LPSYSTEMTIME;

typedef struct _FILETIME {
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
} FILETIME, *PFILETIME, FAR *LPFILETIME;

typedef ULONG ( WINAPI *PTHREAD_START_ROUTINE ) (
    LPVOID lpThreadParameter
    );
typedef PTHREAD_START_ROUTINE LPTHREAD_START_ROUTINE;

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
VOID WINAPI InitializeCriticalSection(
    LPCRITICAL_SECTION lpCriticalSection
    );

VOID WINAPI EnterCriticalSection(
    LPCRITICAL_SECTION lpCriticalSection
    );

VOID WINAPI LeaveCriticalSection(
    LPCRITICAL_SECTION lpCriticalSection
    );

int WINAPI MultiByteToWideChar(
    UINT CodePage,
    DWORD dwFlags,
    LPCSTR lpMultiByteStr,
    int cchMultiByte,
    LPWSTR lpWideCharStr,
    int cchWideChar
    );

int WINAPI WideCharToMultiByte(
    UINT CodePage,
    DWORD dwFlags,
    LPCWSTR lpWideCharStr,
    int cchWideChar,
    LPSTR lpMultiByteStr,
    int cchMultiByte,
    LPCSTR lpDefaultChar,
    LPBOOL lpUsedDefaultChar
    );

VOID WINAPI DebugBreak(
    VOID
    );

VOID WINAPI RaiseException(
    DWORD dwExceptionCode,
    DWORD dwExceptionFlags,
    DWORD nNumberOfArguments,
    CONST DWORD *lpArguments
    );

DWORD WINAPI GetTickCount(
    VOID
    );

VOID WINAPI GetSystemTime(
    LPSYSTEMTIME lpSystemTime
    );

VOID WINAPI GetLocalTime(
    LPSYSTEMTIME lpSystemTime
    );

VOID WINAPI GetSystemTimeAsFileTime(
    LPFILETIME lpSystemTimeAsFileTime
    );

BOOL WINAPI SystemTimeToFileTime(
    CONST SYSTEMTIME *lpSystemTime,
    LPFILETIME lpFileTime
    );

BOOL WINAPI FileTimeToLocalFileTime(
    CONST FILETIME *lpFileTime,
    LPFILETIME lpLocalFileTime
    );

DWORD WINAPI GetLastError(
    VOID
    );

BOOL WINAPI CloseHandle(
    HANDLE hObject
    );

HANDLE WINAPI CreateEventA(
    LPSECURITY_ATTRIBUTES lpEventAttributes,
    BOOL bManualReset,
    BOOL bInitialState,
    LPCSTR lpName
    );

HANDLE WINAPI CreateEventW(
    LPSECURITY_ATTRIBUTES lpEventAttributes,
    BOOL bManualReset,
    BOOL bInitialState,
    LPCWSTR lpName
    );
#ifdef UNICODE
#define CreateEvent CreateEventW
#else
#define CreateEvent CreateEventA
#endif // !UNICODE

BOOL WINAPI SetEvent(
    HANDLE hEvent
    );

DWORD WINAPI WaitForSingleObject(
    HANDLE hHandle,
    DWORD dwMilliseconds
    );

HANDLE WINAPI GetCurrentProcess(
    VOID
    );

BOOL WINAPI ReadProcessMemory(
    HANDLE hProcess,
    LPCVOID lpBaseAddress,
    LPVOID lpBuffer,
    DWORD nSize,
    LPDWORD lpNumberOfBytesRead
    );

BOOL WINAPI WriteProcessMemory(
    HANDLE hProcess,
    LPVOID lpBaseAddress,
    LPVOID lpBuffer,
    DWORD nSize,
    LPDWORD lpNumberOfBytesWritten
    );

HANDLE WINAPI CreateThread(
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    DWORD dwStackSize,
    LPTHREAD_START_ROUTINE lpStartAddress,
    LPVOID lpParameter,
    DWORD dwCreationFlags,
    LPDWORD lpThreadId
    );

HMODULE WINAPI GetModuleHandleA(
    LPCSTR lpModuleName
    );

HMODULE WINAPI GetModuleHandleW(
    LPCWSTR lpModuleName
    );
#ifdef UNICODE
#define GetModuleHandle GetModuleHandleW
#else
#define GetModuleHandle GetModuleHandleA
#endif // !UNICODE

DWORD WINAPI GetModuleFileNameA(
    HMODULE hModule,
    LPSTR lpFilename,
    DWORD nSize
    );

DWORD WINAPI GetModuleFileNameW(
    HMODULE hModule,
    LPWSTR lpFilename,
    DWORD nSize
    );
#ifdef UNICODE
#define GetModuleFileName GetModuleFileNameW
#else
#define GetModuleFileName GetModuleFileNameA
#endif // !UNICODE

BOOL WINAPI CreateDirectoryA(
    LPCSTR lpPathName,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes
    );

BOOL WINAPI CreateDirectoryW(
    LPCWSTR lpPathName,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes
    );
#ifdef UNICODE
#define CreateDirectory CreateDirectoryW
#else
#define CreateDirectory CreateDirectoryA
#endif // !UNICODE

HANDLE WINAPI CreateFileA(
    LPCSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile
    );

HANDLE WINAPI CreateFileW(
    LPCWSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile
    );
#ifdef UNICODE
#define CreateFile CreateFileW
#else
#define CreateFile CreateFileA
#endif // !UNICODE

BOOL WINAPI SetEndOfFile(
    HANDLE hFile
    );

DWORD WINAPI SetFilePointer(
    HANDLE hFile,
    LONG lDistanceToMove,
    PLONG lpDistanceToMoveHigh,
    DWORD dwMoveMethod
    );

BOOL WINAPI WriteFile(
    HANDLE hFile,
    LPCVOID lpBuffer,
    DWORD nNumberOfBytesToWrite,
    LPDWORD lpNumberOfBytesWritten,
    LPOVERLAPPED lpOverlapped
    );

BOOL WINAPI ReadFile(
    HANDLE hFile,
    LPVOID lpBuffer,
    DWORD nNumberOfBytesToRead,
    LPDWORD lpNumberOfBytesRead,
    LPOVERLAPPED lpOverlapped
    );

LONG APIENTRY RegCloseKey(
    HKEY hKey
    );

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
    );

LONG APIENTRY RegDeleteKey(
    HKEY hKey,
    LPCSTR lpSubKey
    );

LONG APIENTRY RegSetValueExA(
    HKEY hKey,
    LPCSTR lpValueName,
    DWORD Reserved,
    DWORD dwType,
    CONST BYTE *lpData,
    DWORD cbData
    );

LONG APIENTRY RegSetValueExW(
    HKEY hKey,
    LPCWSTR lpValueName,
    DWORD Reserved,
    DWORD dwType,
    CONST BYTE *lpData,
    DWORD cbData
    );

LRESULT WINAPI SendMessageA(
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam
    );

SHORT WINAPI GetKeyState(
    int nVirtKey
    );

LONG WINAPI GetWindowLong(
    HWND hWnd,
    int nIndex
    );

BOOL WINAPI TranslateMessage(
    CONST void *lpMsg
    );

LONG WINAPI DispatchMessage(
    CONST void *lpMsg
    );

LRESULT WINAPI SendMessageW(
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam
    );
#ifdef UNICODE
#define SendMessage SendMessageW
#else
#define SendMessage SendMessageA
#endif // !UNICODE

int WINAPI GetSystemMetrics(
    int nIndex
    );

ATOM WINAPI RegisterClass(
    CONST PWNDCLASSW lpWndClass
    );

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
    );

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
    );
#ifdef UNICODE
#define CreateWindowEx CreateWindowExW
#else
#define CreateWindowEx CreateWindowExA
#endif // !UNICODE

#define CreateWindowA( lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam ) \
    CreateWindowExA( 0L, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam )
#define CreateWindowW( lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam ) \
    CreateWindowExW( 0L, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam )

#ifdef UNICODE
#define CreateWindow CreateWindowW
#else
#define CreateWindow CreateWindowA
#endif // !UNICODE

BOOL WINAPI GetClientRect(
    HWND hWnd,
    LPRECT lpRect
    );

HWND WINAPI GetParent(
    HWND hWnd
    );

BOOL WINAPI IsWindow(
    HWND hWnd
    );

BOOL WINAPI SetWindowPos(
    HWND hWnd,
    HWND hWndInsertAfter,
    int X,
    int Y,
    int cx,
    int cy,
    UINT uFlags
    );

BOOL WINAPI ShowWindow(
    HWND hWnd,
    int nCmdShow
    );

BOOL WINAPI UpdateWindow(
    HWND hWnd
    );

HWND WINAPI SetFocus(
    HWND hWnd
    );

LRESULT CALLBACK DefWindowProc(
    HWND hWnd,
    UINT Msg,
    WPARAM wParam,
    LPARAM lParam
    );

HCURSOR WINAPI LoadCursorA(
    HINSTANCE hInstance,
    LPCSTR lpCursorName
    );

HCURSOR WINAPI LoadCursorW(
    HINSTANCE hInstance,
    LPCWSTR lpCursorName
    );

#else

/* Window os */

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/
#ifndef HEAP_ALLOC
#define HEAP_ALLOC( Size ) HeapAlloc( GetProcessHeap( ), 0, Size )
#endif

#ifndef HEAP_FREE
#define HEAP_FREE( Buffer ) HeapFree( GetProcessHeap( ), 0, Buffer )
#endif

#ifndef HEAP_REALLOC
#define HEAP_REALLOC( Buffer, Size ) HeapReAlloc( GetProcessHeap( ), 0, Buffer, Size )
#endif

#endif

#ifdef __cplusplus
}
#endif
/*
///////////////////////////////////////////////////////////////////////////////
// E N D  O F  F I L E
///////////////////////////////////////////////////////////////////////////////
*/
#endif /* __COMPATIBLE_H__ */