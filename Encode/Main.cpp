/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   ForDebug.cpp
//  Version     :   1.0
//  Creator     :   RM
//  Create Date :   2006-01-01
//  Comment     :
//
///////////////////////////////////////////////////////////////////////////////
*/

#include < tchar.h >
#include < stdio.h >
#include < windows.h >
#include < tlhelp32.h >

#include "Macro.h"
#include "Stack.h"
#include "AddLog.h"
#include "Map.h"
#include "MD5.h"
#include "Search.h"
#include "Dump.h"
#include "Hash.h"
#include "Encode.h"
#include "ParseString.h"
#include "ParseSetting.h"

/* Skip warning */
#pragma warning( disable: 4054 )
#pragma warning( disable: 4055 )
#pragma warning( disable: 4100 )
#pragma warning( disable: 4127 )
#pragma warning( disable: 4152 )
#pragma warning( disable: 4201 )
#pragma warning( disable: 4204 )
#pragma warning( disable: 4310 )
#pragma warning( disable: 4505 )
#pragma warning( disable: 4706 )

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/
#ifndef SIZE_OF_ARRAY
#define SIZE_OF_ARRAY( Array ) ( sizeof( Array ) / sizeof( ( Array )[0] ) )
#endif

#ifndef HEAP_ALLOC
#define HEAP_ALLOC( Size ) HeapAlloc( GetProcessHeap( ), 0, Size )
#endif

#ifndef HEAP_FREE
#define HEAP_FREE( Buffer ) HeapFree( GetProcessHeap( ), 0, Buffer )
#endif

#ifndef HEAP_REALLOC
#define HEAP_REALLOC( Buffer, Size ) HeapReAlloc( GetProcessHeap( ), 0, Buffer, Size )
#endif

#define BUFFER_SIZE 4096

/* Encode key length */
#define MAX_KEY_INTERNAL_LENGTH 16
#define MAX_KEY_LENGTH 256

/* Default log file name */
#define DEFAULT_VERSION 0x10001
#define DEFAULT_LOG_FILE _T( "Encode" )

/* Path environment positive value */
#define DEFAULT_TRUE _T( "true" )
#define DEFAULT_TRUE_LENGTH ( SIZE_OF_ARRAY( DEFAULT_TRUE ) - 1 )
#define DEFAULT_TRUE_LENGTH_ROUND ( ( SIZE_OF_ARRAY( DEFAULT_TRUE ) + 3 ) & ~3 )

/* Type of struct */
#define TYPE_GLOBAL_SETTING 1

/* Global setting */
#define DEFAULT_VERSION 0x10001
#define DEFAULT_SIGNATURE ( 20060101 )

/* Global setting flags */
#define GS_FLAGS_DETAIL 0x1
#define GS_FLAGS_ALL_YES 0x2
#define GS_FLAGS_ALL_NO 0x4
#define GS_FLAGS_SILENCE 0x8
#define GS_FLAGS_FORCE 0x10
#define GS_FLAGS_NOEXECUTE 0x20
#define GS_FLAGS_NOGUI 0x40
#define GS_FLAGS_HOOK 0x80
#define GS_FLAGS_HEX 0x100
#define GS_FLAGS_DIC 0x200
#define GS_FLAGS_SEARCH 0x400
#define GS_FLAGS_PATCHPOPO 0x800
#define GS_FLAGS_PATCHWEBLOG 0x1000

#define GS_FLAGS_TEST 0x80000000

/* Get global setting */
#define GET_GS( ) ( g_SettingPtr )
#define SET_GS( ) ( _Setting ) g_SettingPtr = _Setting

/* Hook */
#define HOOK_FUNCTION( Name, Arg1, Arg2 ) \
if ( g_HookMgr.HookApiFunction( Arg1, Name, GET_HOOK_FUNCTION( Name ), Arg2 ) ) \
    ADD_DEBUG_LOG_LRA( _T( "[S]HookEx " )#Name ); \
else \
    ADD_DEBUG_LOG_LRA( _T( "[F]HookEx " )#Name ); \

#define HOOK_FUNCTION_IMP( Name, Module, HookFunction ) \
if ( HookImportTable( GetModuleHandle( Module ), Name, HookFunction ) ) \
    ADD_DEBUG_LOG_LRA( _T( "[S]Hook " )#Name ); \
else \
    ADD_DEBUG_LOG_LRA( _T( "[F]Hook " )#Name ); \

/*
///////////////////////////////////////////////////////////////////////////////
// S T R U C T U R E S
///////////////////////////////////////////////////////////////////////////////
*/
typedef struct _GLOBAL_SETTING {
    USHORT Type;
    USHORT Size;
    ULONG Signature;
    ULONG Init;
    /* See GS_FLAGS_XXX */
    ULONG Flags;
    ULONG State;
    ULONG LogType;
    ULONG HexLength;
    ULONG StartAddress;
    ULONG EndAddress;
    COMMON_STACK FileList;
    COMMON_STACK NameList;
    COMMON_STACK SearchList;
    COMMON_STACK_U IdList;
    COMMON_STACK_U Allocate;
    TCHAR ConstTrue[DEFAULT_TRUE_LENGTH_ROUND];
    TCHAR Key[MAX_KEY_LENGTH];
    TCHAR InFile[MAX_PATH];
    TCHAR OutFile[MAX_PATH];
    TCHAR LogFile[MAX_PATH];
} GLOBAL_SETTING, *PGLOBAL_SETTING;

typedef struct _DATA_ARRAY {
    PVOID Data;
    ULONG DataSize;
} DATA_ARRAY, PDATA_ARRAY;

/*
///////////////////////////////////////////////////////////////////////////////
// G L O B A L S
///////////////////////////////////////////////////////////////////////////////
*/
GLOBAL_SETTING g_Setting = {
    TYPE_GLOBAL_SETTING,
    sizeof( GLOBAL_SETTING ),
    DEFAULT_SIGNATURE, /* Signature */
    0, /* Initiate */
    0, /* Flags */
    0, /* State */
    LOG_FILE, /* Log type */
    sizeof( ULONG ), /* Hex length */
    0x10000, /* Start address */
    0x7FFFF000, /* End address */
    { 0 }, /* File list */
    { 0 }, /* Name list */
    { 0 }, /* Search list */
    { 0 }, /* Id list */
    { 0 }, /* Allocate */
    DEFAULT_TRUE, /* Path environment positive value */
    _T( "" ), /* Encode key */
    _T( "" ), /* In file */
    _T( "" ), /* Out file */
    DEFAULT_LOG_FILE, /* Log file */
};
PGLOBAL_SETTING g_SettingPtr = &g_Setting;

/* Platform */
ULONG g_uIsWindowsNT = FALSE;
ULONG g_uIsWindows9X = FALSE;

/*
///////////////////////////////////////////////////////////////////////////////
// F U N C T I O N S
///////////////////////////////////////////////////////////////////////////////
*/
ULONG GetSystemVersion( 
    POSVERSIONINFOEX OsVerInfo
    )
{
    ULONG RetCode;
    OSVERSIONINFOEX LocalOSVerInfo;

    if ( OsVerInfo == NULL )
        OsVerInfo = &LocalOSVerInfo;

    RetCode = TRUE;
    memset( OsVerInfo, 0, sizeof( OSVERSIONINFOEX ) );
    OsVerInfo->dwOSVersionInfoSize = sizeof( OSVERSIONINFOEX );
    if ( !GetVersionEx( ( OSVERSIONINFO * )OsVerInfo ) )
    {
        /* If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO */
        OsVerInfo->dwOSVersionInfoSize = sizeof( OSVERSIONINFO );
        if ( !GetVersionEx( ( OSVERSIONINFO * )OsVerInfo ) )
            RetCode = FALSE;
    }

    return RetCode;
}

/*
///////////////////////////////////////////////////////////////////////////////
// GetPeInfo
///////////////////////////////////////////////////////////////////////////////
*/
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

    __try
    {
        DosHeader = ( PIMAGE_DOS_HEADER )ModuleBase;
        if ( DosHeader->e_magic != IMAGE_DOS_SIGNATURE )
            return FALSE;

        NtHeaders = ( PIMAGE_NT_HEADERS ) ( ( PUCHAR )ModuleBase + DosHeader->e_lfanew );
        if ( NtHeaders->Signature != IMAGE_NT_SIGNATURE )
            return FALSE;

        FileHeader = ( PIMAGE_FILE_HEADER )&( NtHeaders )->FileHeader;
        OptionalHeader = ( PIMAGE_OPTIONAL_HEADER ) &( NtHeaders )->OptionalHeader;
        if ( ( OptionalHeader )->Magic != IMAGE_NT_OPTIONAL_HDR32_MAGIC )
            return FALSE;

        SectionHeader = ( PIMAGE_SECTION_HEADER ) ( ( PUCHAR )OptionalHeader + sizeof( IMAGE_OPTIONAL_HEADER ) );
        if ( ppNH )
            *ppNH = NtHeaders;
        if ( ppFH )
            *ppFH = FileHeader;
        if ( ppOH )
            *ppOH = OptionalHeader;
        if ( ppSH )
            *ppSH = SectionHeader;        
    }
    __except( EXCEPTION_EXECUTE_HANDLER )
    {
        return FALSE;
    }

    return TRUE;
}

/*
///////////////////////////////////////////////////////////////////////////////
// GetAlignedSize
///////////////////////////////////////////////////////////////////////////////
*/
ULONG GetAlignedSize(
    IN ULONG Size,
    IN ULONG Alignment
    )
{
    if ( Size % Alignment == 0 )
        return Size;

    return( ( ( Size / Alignment ) + 1 ) * Alignment );
}

/*
///////////////////////////////////////////////////////////////////////////////
// CalcTotalImageSize
///////////////////////////////////////////////////////////////////////////////
*/
ULONG CalcTotalImageSize(
    IN PIMAGE_FILE_HEADER FileHeader,
    IN PIMAGE_OPTIONAL_HEADER OptionalHeader,
    IN PIMAGE_SECTION_HEADER SectionHeader
    )
{
    ULONG Iter;
    ULONG ImageSize;
    ULONG SectionAlignment;
    ULONG VirtualSize;

    __try
    {
        SectionAlignment = OptionalHeader->SectionAlignment;
        ImageSize = GetAlignedSize( OptionalHeader->SizeOfHeaders, SectionAlignment );
        for ( Iter = 0; Iter < FileHeader->NumberOfSections; Iter++ )
        {
            VirtualSize = SectionHeader[Iter].Misc.VirtualSize;
            if ( VirtualSize )
                ImageSize += GetAlignedSize( VirtualSize, SectionAlignment );
        }
    }
    __except( EXCEPTION_EXECUTE_HANDLER )
    {
        return FALSE;
    }

    return ImageSize;
}

void EncodeFile( )
{
    register ULONG Iter;
    register ULONG Count;
    ULONG KeyLength;
    ULONG FileSize;
    ULONG ImageSize;
    ULONG SkipOffset;
    ULONG SkipSize;
    PVOID FileImage;
    PVOID ImageBase;
    LPCTSTR FileName;
    PENCODE_STUB Stub;
    PENCODE_STUB InternalStub;
    PIMAGE_NT_HEADERS NtHeaders;
    PIMAGE_FILE_HEADER FileHeader;
    PIMAGE_OPTIONAL_HEADER OptionalHeader;
    PIMAGE_SECTION_HEADER SectionHeader;    
    const unsigned char *SearchStart;
    const unsigned char *SearchEnd;
    static TCHAR Key[] = DEFAULT_ENCODE_KEY;

    /* Obfuscate key */
    GET_GS( )->Key[MAX_KEY_INTERNAL_LENGTH] = _T( '\0' );
    KeyLength = _tcslen( GET_GS( )->Key );
    ObfuscateKey( ( UCHAR* )GET_GS( )->Key, KeyLength );

    Count = StackCount( &GET_GS( )->FileList );
    for ( Iter = 0; Iter < Count; Iter++ )
    {
        Stub = NULL;
        InternalStub = NULL;
        SkipOffset = 0;
        SkipSize = 0;
        FileName = ( LPCTSTR )StackAt( &GET_GS( )->FileList, Iter );
        MapFile( FileName, &FileImage, &FileSize, NULL );
        if ( FileImage )
        {
            if ( GetPeInfo( FileImage, &NtHeaders, &FileHeader, &OptionalHeader, &SectionHeader ) )
            {
                ImageBase = ( PVOID )OptionalHeader->ImageBase;
                ImageSize = CalcTotalImageSize( FileHeader, OptionalHeader, SectionHeader );
                SearchStart = ( const unsigned char * )FileImage;
                SearchEnd = SearchStart + FileSize - SIZE_OF_ARRAY( Key );
                while ( SearchStart < SearchEnd )
                {
                    if ( 0 == memcmp( SearchStart, Key, SIZE_OF_ARRAY( Key ) ) )
                    {
                        Stub = CONTAINING_RECORD( SearchStart, ENCODE_STUB, Key );
                        if ( Stub->Flags & ES_FLAGS_ENCODE )
                        {
                            ADD_LOG( _T( "All ready encoded.\r\n" ) );
                            break;
                        }
                        memcpy( Stub->Key, GET_GS( )->Key, KeyLength );
                        Stub->KeyLength = KeyLength;
                        if ( Stub->Type == TYPE_ENCODE_INTERNAL )
                        {
                            memcpy( Stub->InternalKey, GET_GS( )->Key, KeyLength );
                            Stub->InternalKeyLength = KeyLength;
                            EncodeInternalStub( Stub, ImageBase, FileImage );
                            /* Get Skip address */
                            SkipOffset = ( UCHAR* )Stub - ( UCHAR* )FileImage;
                            SkipSize = sizeof( ENCODE_STUB );
                            InternalStub = Stub;
                            ADD_LOG( _T( "[S]Step 1.\r\n" ) );
                        }
                        else if ( Stub->Type == TYPE_ENCODE_LOCAL )
                        {
                            EncodeStub( Stub, ImageBase, FileImage );
                        }
                        else
                        {
                            EncodeStub( Stub, ImageBase, FileImage );
                        }
                    }
                    SearchStart++;
                }
            }
            UnMapFile( FileImage );
        }
        if ( InternalStub )
        {
            MapFile( FileName, &FileImage, &FileSize, NULL );
            if ( FileImage )
            {
                /* Get CRC */
                InternalStub = ( PENCODE_STUB ) ( ( UCHAR* )FileImage + SkipOffset );
                memset( &InternalStub->MD5, 0, sizeof( InternalStub->MD5 ) );
                GetCRC( &InternalStub->MD5, ( UCHAR* )FileImage, SkipOffset );
                GetCRC( &InternalStub->MD5, ( UCHAR* )FileImage + SkipOffset + SkipSize, FileSize - SkipOffset - SkipSize );
                EncodeEx( InternalStub->Key, InternalStub->KeyLength, InternalStub->MD5.Value, sizeof( InternalStub->MD5.Value ) );
                InternalStub->Flags |= ES_FLAGS_CRC_FILE;
                ADD_LOG( _T( "[S]Encode successfully.\r\n" ) );
                UnMapFile( FileImage );
            }
        }
    }
}

void WINAPI Execute( )
{
    EncodeFile( );
}

ULONG FASTCALL GetLogType( LPCTSTR Argument, PINI_GLOBAL_SETTING Setting )
{
    ULONG *LogType;

    if ( Argument )
    {
        LogType = ( ULONG* )Setting->SetValuePtr;
        if ( 0 == _tcsicmp( Argument, _T( "file" ) ) )
            *LogType = LOG_FILE;
        else if ( 0 == _tcsicmp( Argument, _T( "registry" ) ) )
            *LogType = LOG_REGISTRY;
        else if ( 0 == _tcsicmp( Argument, _T( "control" ) ) )
            *LogType = LOG_CONTROL;
        else if ( 0 == _tcsicmp( Argument, _T( "debug" ) ) )
            *LogType = LOG_DEBUG_STRING;
        else if ( 0 == _tcsicmp( Argument, _T( "messagebox" ) ) )
            *LogType = LOG_MESSAGEBOX;
        else
            *LogType = LOG_NONE;
    }

    return TRUE;
}

void PrintHelp( )
{
    const TCHAR HelpMsg[] = _T( "\
        [{/}|{-}command[:attributes]] $file\r\n\
        h|?|help : help\r\n\
        log:$log : log file $log\r\n\
        logtype:$type : log type[file|registry|control|debug|messagebox]\r\n\
        key:$key : encode file with key $key\r\n\
        $file : source file\r\n" );

    MessageBox( NULL, HelpMsg, _T( "[Usage]" ), MB_OK );
}

ULONG FASTCALL InitCommandLineCallback( LPCTSTR lptszStart, PINI_GLOBAL_SETTING IniSetting )
{
    if ( lptszStart[1] == _T( '\0' ) )
    {
        switch ( lptszStart[0] )
        {
        case _T( 'f' ) :
        case _T( 'F' ) :
            GET_GS( )->Flags |= GS_FLAGS_FORCE;
            break;
        case _T( 'h' ) :
        case _T( 'H' ) :
        case _T( '?' ) :
        default :
            PrintHelp( );
        }
    }
    else if ( lptszStart[2] == _T( '\0' ) )
    {
        if ( lptszStart[0] == _T( 'n' ) && lptszStart[1] == _T( 'o' ) )
            GET_GS( )->Flags |= GS_FLAGS_ALL_NO;
    }
    else if ( lptszStart[3] == _T( '\0' ) )
    {
        if ( lptszStart[0] == _T( 'y' ) && lptszStart[1] == _T( 'e' ) && lptszStart[2] == _T( 's' ) )
            GET_GS( )->Flags |= GS_FLAGS_ALL_NO;
    }
    else if ( lptszStart[4] == _T( '\0' ) && 0 == _tcsicmp( lptszStart, _T( "help" ) ) )
    {
        PrintHelp( );
    }
    else
    {
        /* Not handler */
        return FALSE;
    }

    return TRUE;
}

void Init( )
{
    ULONG RetCode;
    PGLOBAL_SETTING Setting;
    LPCTSTR lptszCommandLine;
    COMMON_STACK CommandList;
    OSVERSIONINFOEX OsVer;
    static INI_GLOBAL_SETTING IniSetting[] = {
        /* Call back */
        { _T( "ENCODE_FILE_LOGTYPE" ), _T( "logtype:" ), 8, &GET_GS( )->LogType, GetLogType, 0, IGS_FLAGS_CALLBACK },
        /* Flags */
        { _T( "ENCODE_FILE_SILENCE" ), _T( "silence" ), 5, &GET_GS( )->Flags, NULL, GS_FLAGS_SILENCE, IGS_FLAGS_SET_FLAGS },
        { _T( "ENCODE_FILE_FORCE" ), _T( "force" ), 5, &GET_GS( )->Flags, NULL, GS_FLAGS_FORCE, IGS_FLAGS_SET_FLAGS },
        { _T( "ENCODE_FILE_YES" ), _T( "yes" ), 3, &GET_GS( )->Flags, NULL, GS_FLAGS_ALL_YES, IGS_FLAGS_SET_FLAGS },
        { _T( "ENCODE_FILE_NO" ), _T( "no" ), 2, &GET_GS( )->Flags, NULL, GS_FLAGS_ALL_NO, IGS_FLAGS_SET_FLAGS },
        /* Char */
        /* Number */
        /* Multi number */
        /* String */
        { _T( "ENCODE_FILE_KEY" ), _T( "key" ), 3, &GET_GS( )->Key, NULL, SIZE_OF_ARRAY( Setting->Key ) - 1, IGS_FLAGS_SET_STRING },
        { _T( "ENCODE_FILE_IN" ), _T( "in" ), 2, &GET_GS( )->InFile, NULL, SIZE_OF_ARRAY( Setting->InFile ) - 1, IGS_FLAGS_SET_STRING },
        { _T( "ENCODE_FILE_OUT" ), _T( "out" ), 3, &GET_GS( )->OutFile, NULL, SIZE_OF_ARRAY( Setting->OutFile ) - 1, IGS_FLAGS_SET_STRING },
        { _T( "ENCODE_FILE_LOG" ), _T( "log" ), 3, &GET_GS( )->LogFile, DEFAULT_LOG_FILE, SIZE_OF_ARRAY( Setting->LogFile ) - 1, IGS_FLAGS_SET_STRING },
    };

    do
    {
        Setting = GET_GS( );
        RetCode = Setting->Init;
        if ( Setting->Init )
            break;

        /* Initiate list */
        StackInit( &Setting->FileList, 0 );
        StackInit( &Setting->NameList, 0 );
        StackInit( &Setting->SearchList, 0 );
        StackInitU( &Setting->IdList, 0 );
        StackInitU( &Setting->Allocate, 0 );

        if ( !GetSystemVersion( &OsVer ) )
            break;

        switch ( OsVer.dwPlatformId )
        {
        case VER_PLATFORM_WIN32_NT :
            g_uIsWindowsNT = TRUE;
            break;
        case VER_PLATFORM_WIN32_WINDOWS :
            g_uIsWindows9X = TRUE;
            break;
        }

        /* Deal with environment string */
        ParseSetting( &IniSetting[0], SIZE_OF_ARRAY( IniSetting ), GET_GS( )->ConstTrue );

        /* Get command line */
        lptszCommandLine = GetCommandLine( );
        if ( lptszCommandLine == NULL )
            break;

        /* Initiate command list */
        StackInit( &CommandList, 0 );

        /* Parse command line */
        ParseCommandLine( &CommandList, lptszCommandLine, _T( ' ' ) );

        /* Deal with command line */
        ParseCommandLineSetting( &IniSetting[0], SIZE_OF_ARRAY( IniSetting ), &CommandList, &Setting->FileList, InitCommandLineCallback );

        /* Un-initiate command list */
        StackUninit( &CommandList );

        /* Initiate ok */
        Setting->Init = TRUE;
        RetCode = TRUE;
    } while ( 0 );

    if ( !( Setting->Flags & GS_FLAGS_SILENCE ) )
    {
        INIT_LOG( Setting->LogFile, Setting->LogType, TRUE );
        CLEAR_LOG( );
    }
}

void Uninit( )
{
    /* Un-initiate list */
    StackUninit( &GET_GS( )->FileList );
    StackUninit( &GET_GS( )->NameList );
    StackUninit( &GET_GS( )->SearchList );
    StackUninitU( &GET_GS( )->IdList );
    StackUninitU( &GET_GS( )->Allocate );

    UNINIT_LOG( );
}

BOOL WINAPI DllMain( 
    HANDLE hModule,
    ULONG  Reason,
    LPVOID lpReserved
    )
{
    switch ( Reason )
    {
    case DLL_PROCESS_ATTACH :
        Init( );
        Execute( );
        break;

    case DLL_PROCESS_DETACH :
        Uninit( );
        break;
    }

    return TRUE;
}

int WINAPI _tWinMain( 
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR lpCmdLine,
    int nCmdShow
    )
{
    Init( );

    Execute( );

    Uninit( );

    return 0;
}