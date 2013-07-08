/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   zend_dump.c
//  Version     :   1.0
//  Creator     :   RM
//  Create Date :   2006-01-01
//  Comment     :
//
///////////////////////////////////////////////////////////////////////////////
*/

#include < tchar.h >
#include < time.h >
#include "zend.h"
#include "zend_extensions.h"
#include "zend_modules.h"
#include "zend_variables.h"
#include "zend_constants.h"
#include "zend_globals_macros.h"
#include "zend_list.h"
#include "zend_ptr_stack.h"
#include "zend_API.h"
#include "zend_ini.h"
#include "zend_compile.h"
#include "zend_execute.h"

#include "Macro.h"
#include "Compatible.h"
#include "Encode.h"
#include "Dump.h"
#include "AddLog.h"
#include "Base64X.h"
#include "Utf8.h"
#include "ListEntry.h"
#include "Stack.h"
#include "ParseString.h"
#include "ParseSetting.h"
#include "Patch.h"
#include "zend_dump.h"

#ifdef _MSC_VER

/* Skip warning */
#pragma warning( disable: 4054 )
#pragma warning( disable: 4055 )
#pragma warning( disable: 4100 )
#pragma warning( disable: 4127 )
#pragma warning( disable: 4152 )
#pragma warning( disable: 4201 )
#pragma warning( disable: 4204 )
#pragma warning( disable: 4245 )
#pragma warning( disable: 4310 )
#pragma warning( disable: 4505 )
#pragma warning( disable: 4706 )

/* Heap reserve size 4194304bytes( =4M ) */
#pragma comment( linker, "/HEAP:4194304" )

#endif

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/
/* Private version, full feature */
#define PRIVATE_VERSION 0

#ifndef FASTCALL
#define FASTCALL __fastcall
#endif

/* Try-catch */
#define try_ex \
{ \
    jmp_buf *__orig_jmp_buf = GET_GS( )->JmpBuffer; \
    jmp_buf __jmp_buf; \
    GET_GS( )->JmpBuffer = &__jmp_buf; \
    if ( ( GET_GS( )->ExceptionCode = setjmp( __jmp_buf ) ) == 0 ) {
#define catch_ex \
    } else { \
    GET_GS( )->JmpBuffer = __orig_jmp_buf;
#define end_try_ex( ) \
    } \
    GET_GS( )->JmpBuffer = __orig_jmp_buf; \
}

#ifdef _MSC_VER
#define throw_ex( _Code ) RaiseException( _Code, 0, 0, NULL );
#define exception_code_ex( ) exception_code( )
#else
#define throw_ex( _Code ) longjmp( *GET_GS( )->JmpBuffer, _Code )
#define exception_code_ex( ) ( GET_GS( )->ExceptionCode )
#endif

/* All known extension engine */
#define EXTENSION_ID_1 1
#define EXTENSION_ID_2 2
#define EXTENSION_ID_3 3

/* Support max engine */
#define SUPPORT_MAX_ENGINE EXTENSION_ID_3

/* Default setting */
#define DEFAULT_SIGNATURE ( 20071130 )

/* Default indent */
#define DEFAULT_INDENT 4

/* Max indent char */
#define MAX_INDENT_CHAR 4

/* Default indent char */
#define DEFAULT_INDENT_CHAR _T( ' ' )
#define DEFAULT_INDENT_STRING _T( " " )
#define DEFAULT_INDENT_STRING_LENGTH ( sizeof( DEFAULT_INDENT_STRING ) - 1 )

/* Default silence char */
#define DEFAULT_SILENCE_CHAR _T( '@' )
#define DEFAULT_SILENCE_STRING _T( "@" )
#define DEFAULT_SILENCE_STRING_LENGTH ( sizeof( DEFAULT_SILENCE_STRING ) - 1 )

#define DEFAULT_STATEMENT_CHAR _T( ';' )
#define DEFAULT_STATEMENT_STRING _T( ";" )
#define DEFAULT_STATEMENT_STRING_LENGTH ( sizeof( DEFAULT_STATEMENT_STRING ) - 1 )

/* Default php file setting */
#define MAX_MODULE_NAME_LENGTH 64
#define MAX_PHP_FILE_HEAD_LENGTH 128
#define MAX_PHP_FILE_TAIL_LENGTH 128
#define MAX_PHP_FILE_COMMENT_LENGTH 512
#define MAX_PHP_FILE_EXTENTION_LENGTH 256

/* Default log file type */
#define DEFAULT_LOG_TYPE LOG_FILE

/* Default log file */
#define DEFAULT_LOG_FILE_PRINT _T( "phpinfo.log" )
#define DEFAULT_LOG_FILE g_LogFile
#define DEFAULT_LOG_FILE_LENGTH ( SIZE_OF_ARRAY( DEFAULT_LOG_FILE ) - 1 )

/* Default configure file */
#define DEFAULT_CONFIG_FILE_PRINT _T( "config.ini" )
#define DEFAULT_CONFIG_FILE g_ConfigFile
#define DEFAULT_CONFIG_FILE_LENGTH ( SIZE_OF_ARRAY( DEFAULT_CONFIG_FILE ) - 1 )

/* Default file head and tail */
#define DEFAULT_FILE_HEAD {\
    _T( '<' ) ^ XOR_STR, _T( '?' ) ^ XOR_STR, _T( 'p' ) ^ XOR_STR, _T( 'h' ) ^ XOR_STR,\
    _T( 'p' ) ^ XOR_STR, _T( '\0' ) ^ XOR_STR,\
}

#define DEFAULT_FILE_TAIL {\
    _T( '?' ) ^ XOR_STR, _T( '>' ) ^ XOR_STR, _T( '\0' ) ^ XOR_STR,\
}

/* Default comment */
#ifdef ZEND_ENGINE_2
#define DEFAULT_EXTENSION_ID EXTENSION_ID_2
#define DEFAULT_FILE_COMMENT {\
    _T( '/' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR,\
    _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR,\
    _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR,\
    _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR,\
    _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR,\
    _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '/' ) ^ XOR_STR, _T( '\r' ) ^ XOR_STR,\
    _T( '\n' ) ^ XOR_STR, _T( '/' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '/' ) ^ XOR_STR,\
    _T( '\r' ) ^ XOR_STR, _T( '\n' ) ^ XOR_STR, _T( '/' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( 'V' ) ^ XOR_STR, _T( 'e' ) ^ XOR_STR,\
    _T( 'r' ) ^ XOR_STR, _T( 's' ) ^ XOR_STR, _T( 'i' ) ^ XOR_STR, _T( 'o' ) ^ XOR_STR,\
    _T( 'n' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ':' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( '5' ) ^ XOR_STR, _T( '.' ) ^ XOR_STR, _T( '1' ) ^ XOR_STR, _T( '.' ) ^ XOR_STR,\
    _T( '0' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR,\
    _T( '/' ) ^ XOR_STR, _T( '\r' ) ^ XOR_STR, _T( '\n' ) ^ XOR_STR, _T( '/' ) ^ XOR_STR,\
    _T( '*' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( 'A' ) ^ XOR_STR,\
    _T( 'u' ) ^ XOR_STR, _T( 't' ) ^ XOR_STR, _T( 'h' ) ^ XOR_STR, _T( 'o' ) ^ XOR_STR,\
    _T( 'r' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ':' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( 'R' ) ^ XOR_STR, _T( 'M' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( '*' ) ^ XOR_STR, _T( '/' ) ^ XOR_STR, _T( '\r' ) ^ XOR_STR, _T( '\n' ) ^ XOR_STR,\
    _T( '/' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( 'C' ) ^ XOR_STR, _T( 'o' ) ^ XOR_STR, _T( 'm' ) ^ XOR_STR, _T( 'm' ) ^ XOR_STR,\
    _T( 'e' ) ^ XOR_STR, _T( 'n' ) ^ XOR_STR, _T( 't' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( ':' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( '0' ) ^ XOR_STR, _T( '7' ) ^ XOR_STR,\
    _T( '1' ) ^ XOR_STR, _T( '2' ) ^ XOR_STR, _T( '2' ) ^ XOR_STR, _T( '3' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '/' ) ^ XOR_STR, _T( '\r' ) ^ XOR_STR,\
    _T( '\n' ) ^ XOR_STR, _T( '/' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '/' ) ^ XOR_STR,\
    _T( '\r' ) ^ XOR_STR, _T( '\n' ) ^ XOR_STR, _T( '/' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR,\
    _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR,\
    _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR,\
    _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR,\
    _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR,\
    _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR,\
    _T( '/' ) ^ XOR_STR, _T( '\r' ) ^ XOR_STR, _T( '\n' ) ^ XOR_STR, _T( '\0' ) ^ XOR_STR,\
}
#define DEFAULT_MODULE_FILE_NAME {\
    _T( 'p' ) ^ XOR_STR, _T( 'h' ) ^ XOR_STR, _T( 'p' ) ^ XOR_STR, _T( '5' ) ^ XOR_STR,\
    _T( 't' ) ^ XOR_STR, _T( 's' ) ^ XOR_STR, _T( '.' ) ^ XOR_STR, _T( 'd' ) ^ XOR_STR,\
    _T( 'l' ) ^ XOR_STR, _T( 'l' ) ^ XOR_STR, _T( '\0' ) ^ XOR_STR,\
}
#else
#define DEFAULT_EXTENSION_ID EXTENSION_ID_1
#define DEFAULT_FILE_COMMENT {\
    _T( '/' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR,\
    _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR,\
    _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR,\
    _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR,\
    _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR,\
    _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '/' ) ^ XOR_STR, _T( '\r' ) ^ XOR_STR,\
    _T( '\n' ) ^ XOR_STR, _T( '/' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '/' ) ^ XOR_STR,\
    _T( '\r' ) ^ XOR_STR, _T( '\n' ) ^ XOR_STR, _T( '/' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( 'V' ) ^ XOR_STR, _T( 'e' ) ^ XOR_STR,\
    _T( 'r' ) ^ XOR_STR, _T( 's' ) ^ XOR_STR, _T( 'i' ) ^ XOR_STR, _T( 'o' ) ^ XOR_STR,\
    _T( 'n' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ':' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( '4' ) ^ XOR_STR, _T( '.' ) ^ XOR_STR, _T( '1' ) ^ XOR_STR, _T( '.' ) ^ XOR_STR,\
    _T( '0' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR,\
    _T( '/' ) ^ XOR_STR, _T( '\r' ) ^ XOR_STR, _T( '\n' ) ^ XOR_STR, _T( '/' ) ^ XOR_STR,\
    _T( '*' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( 'A' ) ^ XOR_STR,\
    _T( 'u' ) ^ XOR_STR, _T( 't' ) ^ XOR_STR, _T( 'h' ) ^ XOR_STR, _T( 'o' ) ^ XOR_STR,\
    _T( 'r' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ':' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( 'R' ) ^ XOR_STR, _T( 'M' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( '*' ) ^ XOR_STR, _T( '/' ) ^ XOR_STR, _T( '\r' ) ^ XOR_STR, _T( '\n' ) ^ XOR_STR,\
    _T( '/' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( 'C' ) ^ XOR_STR, _T( 'o' ) ^ XOR_STR, _T( 'm' ) ^ XOR_STR, _T( 'm' ) ^ XOR_STR,\
    _T( 'e' ) ^ XOR_STR, _T( 'n' ) ^ XOR_STR, _T( 't' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( ':' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( '0' ) ^ XOR_STR, _T( '7' ) ^ XOR_STR,\
    _T( '1' ) ^ XOR_STR, _T( '2' ) ^ XOR_STR, _T( '2' ) ^ XOR_STR, _T( '3' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '/' ) ^ XOR_STR, _T( '\r' ) ^ XOR_STR,\
    _T( '\n' ) ^ XOR_STR, _T( '/' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR,\
    _T( ' ' ) ^ XOR_STR, _T( ' ' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '/' ) ^ XOR_STR,\
    _T( '\r' ) ^ XOR_STR, _T( '\n' ) ^ XOR_STR, _T( '/' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR,\
    _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR,\
    _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR,\
    _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR,\
    _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR,\
    _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR, _T( '*' ) ^ XOR_STR,\
    _T( '/' ) ^ XOR_STR, _T( '\r' ) ^ XOR_STR, _T( '\n' ) ^ XOR_STR, _T( '\0' ) ^ XOR_STR,\
}
#define DEFAULT_MODULE_FILE_NAME {\
    _T( 'p' ) ^ XOR_STR, _T( 'h' ) ^ XOR_STR, _T( 'p' ) ^ XOR_STR, _T( '4' ) ^ XOR_STR,\
    _T( 't' ) ^ XOR_STR, _T( 's' ) ^ XOR_STR, _T( '.' ) ^ XOR_STR, _T( 'd' ) ^ XOR_STR,\
    _T( 'l' ) ^ XOR_STR, _T( 'l' ) ^ XOR_STR, _T( '\0' ) ^ XOR_STR,\
}
#endif
#define DEFAULT_FILE_COMMENT_LENGTH ( SIZE_OF_ARRAY( DEFAULT_FILE_COMMENT ) - 1 )

/* Default obfuscate prefix */
#define DEFAULT_OBFUSCATE_PREFIX_PRINT _T( "_obfuscate_" )
#define DEFAULT_OBFUSCATE_PREFIX {\
    _T( '_' ) ^ XOR_STR, _T( 'o' ) ^ XOR_STR, _T( 'b' ) ^ XOR_STR, _T( 'f' ) ^ XOR_STR,\
    _T( 'u' ) ^ XOR_STR, _T( 's' ) ^ XOR_STR, _T( 'c' ) ^ XOR_STR, _T( 'a' ) ^ XOR_STR,\
    _T( 't' ) ^ XOR_STR, _T( 'e' ) ^ XOR_STR, _T( '_' ) ^ XOR_STR, _T( '\0' ) ^ XOR_STR,\
}
#define DEFAULT_OBFUSCATE_PREFIX_LENGTH ( SIZE_OF_ARRAY( DEFAULT_OBFUSCATE_PREFIX_PRINT ) - 1 )

/* Default file extension */
#define DEFAULT_FILE_EXTENSION_PRINT _T( ".de.php" )
#define DEFAULT_FILE_EXTENSION {\
    _T( '.' ) ^ XOR_STR, _T( 'd' ) ^ XOR_STR, _T( 'e' ) ^ XOR_STR, _T( '.' ) ^ XOR_STR,\
    _T( 'p' ) ^ XOR_STR, _T( 'h' ) ^ XOR_STR, _T( 'p' ) ^ XOR_STR, _T( '\0' ) ^ XOR_STR,\
}
#define DEFAULT_FILE_EXTENSION_LENGTH ( SIZE_OF_ARRAY( DEFAULT_FILE_EXTENSION ) - 1 )

/* Default decode level */
#define DEFAULT_DECODE_LEVEL_HIGH 4
#define DEFAULT_DECODE_LEVEL_LOW 1

/* Default extension module name */
#define DEFAULT_EXTENSION_MODULE_NAME_PRINT _T( "ZendOptimizer" )
#define DEFAULT_EXTENSION_MODULE_NAME {\
    _T( 'Z' ) ^ XOR_STR, _T( 'e' ) ^ XOR_STR, _T( 'n' ) ^ XOR_STR, _T( 'd' ) ^ XOR_STR,\
    _T( 'O' ) ^ XOR_STR, _T( 'p' ) ^ XOR_STR, _T( 't' ) ^ XOR_STR, _T( 'i' ) ^ XOR_STR,\
    _T( 'm' ) ^ XOR_STR, _T( 'i' ) ^ XOR_STR, _T( 'z' ) ^ XOR_STR, _T( 'e' ) ^ XOR_STR,\
    _T( 'r' ) ^ XOR_STR, _T( '\0' ) ^ XOR_STR,\
}

/* Hook time module name */
#define DEFAULT_HOOK_TIME_MODULE_NAME_PRINT _T( "msvcrt.dll" )
#define DEFAULT_HOOK_TIME_MODULE_NAME {\
    _T( 'm' ) ^ XOR_STR, _T( 's' ) ^ XOR_STR, _T( 'v' ) ^ XOR_STR, _T( 'c' ) ^ XOR_STR,\
    _T( 'r' ) ^ XOR_STR, _T( 't' ) ^ XOR_STR, _T( '.' ) ^ XOR_STR, _T( 'd' ) ^ XOR_STR,\
    _T( 'l' ) ^ XOR_STR, _T( 'l' ) ^ XOR_STR, _T( '\0' ) ^ XOR_STR,\
}

/* Path environment name */
#define DEFAULT_INI_NAME _T( "PHPRC" )
#define DEFAULT_INI_PATH _T( "." )

/* Path environment positive value */
#define DEFAULT_TRUE _T( "true" )
#define DEFAULT_TRUE_LENGTH ( SIZE_OF_ARRAY( DEFAULT_TRUE ) - 1 )
#define DEFAULT_TRUE_LENGTH_ROUND ( ( SIZE_OF_ARRAY( DEFAULT_TRUE ) + 3 ) & ~3 )

/* Encoded file signature */
#define DEFAULT_FILE_SIGNATURE "<?php @Zend;\n"
#define DEFAULT_FILE_SIGNATURE_SHORT "Zend"

/* Main */
#define DEFAULT_FILE_MAIN _T( "main" )
#define DEFAULT_FILE_MAIN_LENGTH ( SIZE_OF_ARRAY( DEFAULT_FILE_MAIN ) - 1 )

/* Global variable */
#define DEFAULT_GLOBAL_VARIABLE _T( "$GLOBALS" )
#define DEFAULT_GLOBAL_VARIABLE_LENGTH ( SIZE_OF_ARRAY( DEFAULT_GLOBAL_VARIABLE ) - 1 )

/* Class this */
#define DEFAULT_CLASS_THIS _T( "$this" )
#define DEFAULT_CLASS_THIS_LENGTH ( SIZE_OF_ARRAY( DEFAULT_CLASS_THIS ) - 1 )

#define DEFAULT_CLASS_THIS_P _T( "$this->" )
#define DEFAULT_CLASS_THIS_P_LENGTH ( SIZE_OF_ARRAY( DEFAULT_CLASS_THIS_P ) - 1 )

/* Class self */
#define DEFAULT_CLASS_SELF _T( "self" )
#define DEFAULT_CLASS_SELF_LENGTH ( SIZE_OF_ARRAY( DEFAULT_CLASS_SELF ) - 1 )

/* Class parent */
#define DEFAULT_CLASS_PARENT _T( "parent" )
#define DEFAULT_CLASS_PARENT_LENGTH ( SIZE_OF_ARRAY( DEFAULT_CLASS_PARENT ) - 1 )

/* Special file postfix */
#define DEFAULT_EVAL_FILE_POSTFIX _T( "eval()'d code" )
#define DEFAULT_EVAL_FILE_POSTFIX_LENGTH ( SIZE_OF_ARRAY( DEFAULT_EVAL_FILE_POSTFIX ) - 1 )

/* Special string */
#define DEFAULT_FILE_STRING _T( "__FILE__" )
#define DEFAULT_FILE_STRING_LENGTH sizeof( DEFAULT_FILE_STRING ) - 1

/* Variable array */
#define DEFAULT_LIST_ARRAY_SIZE 6

/* Special flags */
#define FLAGS_SPECIAL_LEFT 0x40000000
#define FLAGS_SPECIAL_RIGHT 0x80000000

#define FLAGS_SPECIAL_MASK 0xFF000000

/* Invalid op code array offset */
#define INVALID_OP_OFFSET ( ( ULONG ) ( - 1 ) )
#define INVALID_OP_VAR ( ( ULONG ) ( - 1 ) )

/* Constant global variable */
#define GET_HELP_INFOMATION( ) ( g_HelpInformation )
#define GET_HELP_INFOMATION_LENGTH( ) ( SIZE_OF_ARRAY( g_HelpInformation ) - 1 )

#define GET_HEX_CHAR_ARRAY( ) ( g_HexCharArray )
#define GET_HEX_CHAR_ARRAY_SIZE( ) SIZE_OF_ARRAY( g_HexCharArray )
#define GET_HEX_CHAR( Offset ) ( g_HexCharArray[( Offset )] )

#define GET_VM_DECODE_ARRAY( ) ( g_VmDecodeArray )
#define GET_VM_DECODE_ARRAY_SIZE( ) SIZE_OF_ARRAY( g_VmDecodeArray )
#define GET_VM_DECODE( Offset ) ( g_VmDecodeArray[( Offset )] )

#define GET_OP_TABLE_ARRAY( ) ( g_OpTableArray )
#define GET_OP_TABLE_ARRAY_SIZE( ) SIZE_OF_ARRAY( g_OpTableArray )
#define GET_OP_TABLE( Offset ) ( g_OpTableArray[( Offset )] )

#define GET_OP_TYPE_ARRAY( ) ( g_OpTypeArray )
#define GET_OP_TYPE_ARRAY_SIZE( ) SIZE_OF_ARRAY( g_OpTypeArray )
#define GET_OP_TYPE( Offset ) ( g_OpTypeArray[Offset] )

#define GET_DATA_TYPE_ARRAY( ) ( g_DataTypeArray )
#define GET_DATA_TYPE_ARRAY_SIZE( ) SIZE_OF_ARRAY( g_DataTypeArray )
#define GET_DATA_TYPE( Offset ) ( g_DataTypeArray[Offset] )

#define GET_VAR_TYPE_ARRAY( ) ( g_VarTypeArray )
#define GET_VAR_TYPE_ARRAY_SIZE( ) SIZE_OF_ARRAY( g_VarTypeArray )
#define GET_VAR_TYPE( Offset ) ( g_VarTypeArray[Offset] )

#define GET_OP_STRING_EX_ARRAY( ) ( g_OpStringEx )
#define GET_OP_STRING_EX_ARRAY_SIZE( ) SIZE_OF_ARRAY( g_OpStringEx )
#define GET_OP_STRING_EX( Offset ) ( g_OpStringEx[Offset] )

#define GET_FORMAT_3_STRING_ARRAY( ) ( g_Fmt3String )
#define GET_FORMAT_3_STRING_ARRAY_SIZE( ) SIZE_OF_ARRAY( g_Fmt3String )
#define GET_FORMAT_3_STRING( Offset ) ( g_Fmt3String[Offset] )

#define GET_FORMAT_2_STRING_ARRAY( ) ( g_Fmt2String )
#define GET_FORMAT_2_STRING_ARRAY_SIZE( ) SIZE_OF_ARRAY( g_Fmt2String )
#define GET_FORMAT_2_STRING( Offset ) ( g_Fmt2String[Offset] )

/* Encode stub */
#define GET_STUB( ) g_StubPtr
#define SET_STUB( _StubPtr ) g_StubPtr = _StubPtr

/* Global setting */
#define GET_GS( ) ( g_SettingPtr )
#define SET_GS( _Setting ) g_SettingPtr = _Setting

#define LOCK_GS( ) EnterCriticalSection( &GET_GS( )->Lock )
#define UNLOCK_GS( ) LeaveCriticalSection( &GET_GS( )->Lock )

#define GET_GS_VERSION( ) GET_GS( )->Version
#define SET_GS_VERSION( _Version ) GET_GS( )->Version = _Version

#define GET_GS_FLAGS( ) GET_GS( )->Flags
#define SET_GS_FLAGS( _Flags ) GET_GS( )->Flags = _Flags

#define GET_GS_STATE( ) GET_GS( )->State
#define SET_GS_STATE( _State ) GET_GS( )->State = _State

#define GET_GS_INDENT( ) GET_GS( )->Indent
#define SET_GS_INDENT( _Indent ) GET_GS( )->Indent = _Indent

#define GET_GS_INDENT_CHAR( ) GET_GS( )->IndentChar[0]
#define SET_GS_INDENT_CHAR( _IndentChar ) GET_GS( )->IndentChar[0] = _IndentChar

#define GET_GS_OPARRAY( ) GET_GS( )->OpArray
#define SET_GS_OPARRAY( _OpArray ) GET_GS( )->OpArray = _OpArray

#define GET_GS_CLASS_TABLE( ) GET_GS( )->GExecutor->class_table
#define SET_GS_CLASS_TABLE( _class_table ) GET_GS( )->GExecutor->class_table = _class_table

#define GET_GS_FUNCTION_TABLE( ) GET_GS( )->GExecutor->function_table
#define SET_GS_FUNCTION_TABLE( _function_table ) GET_GS( )->GExecutor->function_table = _function_table;

#define GET_GS_STACK( ) GET_GS( )->Stack
#define SET_GS_STACK( _Stack ) GET_GS( )->Stack = _Stack

#define PUSH_GS_STACK( ) \
    LOCK_GS( ); \
    StackPushU( &GET_GS( )->StackPtrList, ( ULONG )GET_GS( )->Stack ); \
    UNLOCK_GS( )

#define POP_GS_STACK( ) \
    LOCK_GS( ) \
    StackPopU( &GET_GS( )->StackPtrList, NULL ) \
    UNLOCK_GS( )

#define POP_SET_GS_STACK( ) \
    LOCK_GS( ); \
    if ( StackPopU( &GET_GS( )->StackPtrList, NULL ) > 1 ) \
        StackTopU( &GET_GS( )->StackPtrList, ( ULONG* )&GET_GS( )->Stack ); \
    UNLOCK_GS( )

#define GET_GS_LAST_OP( ) GET_GS_STACK( )->LogicOpType
#define SET_GS_LAST_OP( _LogicOpType ) GET_GS_STACK( )->LogicOpType = _LogicOpType

/* Stack setting */
#define DEFAULT_STRING_LENGTH 4096
#define DEFAULT_STACK_SIZE 16

/* Buffer size */
#define BUFFER_SIZE 4096
#define SMALL_BUFFER_SIZE 1024
#define LARGE_BUFFER_SIZE 8192

/* Type of struct */
#define TYPE_GLOBAL_SETTING 1
#define TYPE_DUMP_STACK 2

/* Global encode setting flags */
#define GS_ENCODE_FLAGS_HEAD 0x1
#define GS_ENCODE_FLAGS_TAIL 0x2
#define GS_ENCODE_FLAGS_COMMENT 0x4
#define GS_ENCODE_FLAGS_LOG_FILE 0x8
#define GS_ENCODE_FLAGS_CONFIG_FILE 0x10
#define GS_ENCODE_FLAGS_OBFUSCATE_PREFIX 0x20

/* Global setting flags */
#define GS_FLAGS_DETAIL 0x1
#define GS_FLAGS_OPCODE 0x2
#define GS_FLAGS_OPARRAY 0x4
#define GS_FLAGS_FUNCTION 0x8
#define GS_FLAGS_CLASS 0x10
#define GS_FLAGS_HASH 0x20
#define GS_FLAGS_INFO 0x40
#define GS_FLAGS_RAW 0x80
#define GS_FLAGS_EXECUTE 0x100
#define GS_FLAGS_BACKUP 0x200
#define GS_FLAGS_APPEND 0x400
#define GS_FLAGS_TICK 0x800
#define GS_FLAGS_NOEXPIRE 0x1000
#define GS_FLAGS_NOINDENT 0x2000
#define GS_FLAGS_COMPACT 0x4000
#define GS_FLAGS_CLASSIC 0x8000
#define GS_FLAGS_BUG 0x10000
#define GS_FLAGS_DEBUG 0x20000
#define GS_FLAGS_FULL 0x40000
#define GS_FLAGS_FORCE 0x80000
#define GS_FLAGS_IMPORT 0x100000
#define GS_FLAGS_EXPORT 0x200000
#define GS_FLAGS_OBFUSCATE 0x400000
#define GS_FLAGS_OBFUSCATE_DIC 0x800000

/* Internal flags */
#define GS_IFLAGS_FUNCTION_ONCE 0x01000000
#define GS_IFLAGS_CLASS_ONCE 0x02000000
#define GS_IFLAGS_HOOK_TIME 0x04000000
#define GS_IFLAGS_QUITTING 0x08000000

/* State */
#define GS_STATE_OBFUSCATION_LEVEL_SHIFT 0
#define GS_STATE_OBFUSCATION_LEVEL_MASK ( 0xF0 << GS_STATE_OBFUSCATION_LEVEL_SHIFT )

#define GS_STATE_OBFUSCATION_CURRENT_LEVEL_SHIFT 4
#define GS_STATE_OBFUSCATION_CURRENT_LEVEL_MASK ( 0xF0 << GS_STATE_OBFUSCATION_CURRENT_LEVEL_SHIFT )

#define GS_STATE_EXTEND 0x100
#define GS_STATE_LOADER_ENABLED 0x200
#define GS_STATE_LOADER_FILE_ENCODED 0x400
#define GS_STATE_RUNTIME_OBFUSCATE 0x800
#define GS_STATE_OBFUSCATE 0x1000
#define GS_STATE_OBFUSCATE_VARIABLE 0x2000
#define GS_STATE_OP_ENCODE 0x4000

#define GS_STATE_ADD_OBFUSCATE 0x10000
#define GS_STATE_IMPORT_OBFUSCATE 0x20000
#define GS_STATE_ENCODE_HASH 0x40000
#define GS_STATE_DECODE_HASH 0x80000

#define GS_STATE_EVAL_FILE 0x100000

#define GS_STATE_CHECK_MODIFY 0x10000000
#define GS_STATE_CHECK_TRACE 0x20000000

/* State mask */
#define GS_STATE_MASK 0xFFFFFFFF

/* Stack flags */
#define DS_FLAGS_NULL 0
#define DS_FLAGS_BRK 1
#define DS_FLAGS_CONT 2
#define DS_FLAGS_IF 3
#define DS_FLAGS_ELSE 4
#define DS_FLAGS_ELSEIF 5
#define DS_FLAGS_IF_END 6
#define DS_FLAGS_DO 7
#define DS_FLAGS_DO_WHILE_END 8
#define DS_FLAGS_DO_WHILE_TRUE 9
#define DS_FLAGS_DO_WHILE_FALSE 10
#define DS_FLAGS_WHILE 11
#define DS_FLAGS_WHILE_END 12
#define DS_FLAGS_FOR 13
#define DS_FLAGS_FORBRACKET_IN 14
#define DS_FLAGS_FORBRACKET_END 15
#define DS_FLAGS_FOR_END 16
#define DS_FLAGS_FOREACH 17
#define DS_FLAGS_FOREACH_END 18
#define DS_FLAGS_SWITCH 19
#define DS_FLAGS_SWITCH_CASE 20
#define DS_FLAGS_SWITCH_DEFAULT 21
#define DS_FLAGS_SWITCH_END 22
#define DS_FLAGS_TRY 23
#define DS_FLAGS_TRY_END 24
#define DS_FLAGS_CATCH 25
#define DS_FLAGS_CATCH_END 26

/* Mask */
#define DS_FLAGS_MASK 0x1F

/* Flags */
#define DS_FLAGS_UPDATED 0x20000000
#define DS_FLAGS_INTERNAL 0x40000000

/* Control list flags */
#define DS_FLAGS_END 0x80000000

/* Control list types */
#define DS_TYPE_EMPTY 0x00100000
#define DS_TYPE_SKIP_BACK 0x00200000

#define DS_TYPE_BRK 0x01000000
#define DS_TYPE_CONT 0x02000000
#define DS_TYPE_REVERSE 0x04000000
#define DS_TYPE_NOINDENT 0x08000000

#define DS_TYPE_TOP 0x10000000
#define DS_TYPE_EXTEND 0x20000000
#define DS_TYPE_SKIP_REVERSE 0x40000000
#define DS_TYPE_SKIP_NOINDENT 0x80000000

#define DS_TYPE_MASK 0xFFFF0000

/* Stack internal flags */
#define DS_IFLAGS_OT_NOP 0x2
#define DS_IFLAGS_OT_COMMA 0x8

#define DS_IFLAGS_OT_LG_OR 0x10
#define DS_IFLAGS_OT_LG_XOR 0x12
#define DS_IFLAGS_OT_LG_AND 0x14

#define DS_IFLAGS_OT_ASSIGN 0x20
#define DS_IFLAGS_OT_ASSIGN_REF 0x20
#define DS_IFLAGS_OT_ASSIGN_ADD 0x20
#define DS_IFLAGS_OT_ASSIGN_SUB 0x20
#define DS_IFLAGS_OT_ASSIGN_MUL 0x20
#define DS_IFLAGS_OT_ASSIGN_DIV 0x20
#define DS_IFLAGS_OT_ASSIGN_MOD 0x20
#define DS_IFLAGS_OT_ASSIGN_SL 0x20
#define DS_IFLAGS_OT_ASSIGN_SR 0x20
#define DS_IFLAGS_OT_ASSIGN_CONCAT 0x20
#define DS_IFLAGS_OT_ASSIGN_BW_OR 0x20
#define DS_IFLAGS_OT_ASSIGN_BW_AND 0x20
#define DS_IFLAGS_OT_ASSIGN_BW_XOR 0x20

#define DS_IFLAGS_OT_QM_ASSIGN 0x28

#define DS_IFLAGS_OT_BOOL_OR 0x30
#define DS_IFLAGS_OT_BOOL_AND 0x32
#define DS_IFLAGS_OT_BW_OR 0x34
#define DS_IFLAGS_OT_BW_XOR 0x36
#define DS_IFLAGS_OT_BW_AND 0x38

#define DS_IFLAGS_OT_IS_EQUAL 0x40
#define DS_IFLAGS_OT_IS_NOT_EQUAL 0x40
#define DS_IFLAGS_OT_IS_IDENTICAL 0x40
#define DS_IFLAGS_OT_IS_NOT_IDENTICAL 0x40

#define DS_IFLAGS_OT_IS_SMALLER 0x44
#define DS_IFLAGS_OT_IS_SMALLER_OR_EQUAL 0x44
#define DS_IFLAGS_OT_IS_LARGE 0x44
#define DS_IFLAGS_OT_IS_LARGE_OR_EQUAL 0x44

#define DS_IFLAGS_OT_SL 0x48
#define DS_IFLAGS_OT_SR 0x48

#define DS_IFLAGS_OT_ADD 0x50
#define DS_IFLAGS_OT_SUB 0x50
#define DS_IFLAGS_OT_CONCAT 0x50

#define DS_IFLAGS_OT_MUL 0x58
#define DS_IFLAGS_OT_DIV 0x58
#define DS_IFLAGS_OT_MOD 0x58

#define DS_IFLAGS_OT_SILENCE 0x60
#define DS_IFLAGS_OT_CAST 0x60
#define DS_IFLAGS_OT_SIGN 0x60
#define DS_IFLAGS_OT_BW_NOT 0x60
#define DS_IFLAGS_OT_BOOL_NOT 0x60

#define DS_IFLAGS_OT_PRE_INC 0x68
#define DS_IFLAGS_OT_PRE_DEC 0x68
#define DS_IFLAGS_OT_POST_INC 0x68
#define DS_IFLAGS_OT_POST_DEC 0x68

#define DS_IFLAGS_OT_LEFT_ARRAY 0x70
#define DS_IFLAGS_OT_NEW 0x78
#define DS_IFLAGS_OT_BRAKET 0x80

#define DS_IFLAGS_OT_MIN 0x02
#define DS_IFLAGS_OT_MAX 0xFE
#define DS_IFLAGS_OT_MASK 0xFF

#define DS_IFLAGS_BOOL_NOT 0x000100
#define DS_IFLAGS_BRK 0x000200
#define DS_IFLAGS_CONT 0x000400
#define DS_IFLAGS_LOOP 0x000800

#define DS_IFLAGS_ONE_OP 0x00010000
#define DS_IFLAGS_TWO_OP 0x00020000
#define DS_IFLAGS_OP_ASSIGN 0x00040000
#define DS_IFLAGS_OP_FETCH 0x00080000

#define DS_IFLAGS_POST 0x00100000
#define DS_IFLAGS_COMPACT 0x00200000
#define DS_IFLAGS_FIX_OT 0x00400000
#define DS_IFLAGS_FIX_NODE 0x00800000

#define DS_IFLAGS_IS_OPLINE1 0x01000000
#define DS_IFLAGS_IS_OPLINE2 0x02000000
#define DS_IFLAGS_IS_RESULT 0x04000000
#define DS_IFLAGS_IS_SPECIAL 0x08000000

#define DS_IFLAGS_IS_CLASS 0x10000000
#define DS_IFLAGS_IS_FUNCTION 0x20000000
#define DS_IFLAGS_IS_VAR 0x40000000
#define DS_IFLAGS_UNKNOWN_OP 0x80000000

#define DS_IFLAGS_OP1_MASK ( DS_IFLAGS_IS_SPECIAL | DS_IFLAGS_IS_OPLINE1 | DS_IFLAGS_IS_VAR )
#define DS_IFLAGS_OP2_MASK ( DS_IFLAGS_IS_SPECIAL | DS_IFLAGS_IS_OPLINE2 | DS_IFLAGS_IS_VAR )
#define DS_IFLAGS_OP_MASK 0x0F000000

/* For dump znode */
#define DS_IFLAGS_OPCODE_SHIFT 8
#define DS_IFLAGS_OPCODE_MASK ( DS_IFLAGS_OT_MASK << DS_IFLAGS_OPCODE_SHIFT )
#define DS_IFLAGS_DUMP_MASK_R ( DS_IFLAGS_IS_CLASS | DS_IFLAGS_IS_FUNCTION | DS_IFLAGS_IS_VAR | DS_IFLAGS_IS_RESULT )
#define DS_IFLAGS_DUMP_MASK_OP1 ( 0xF0000000 | DS_IFLAGS_OP1_MASK | DS_IFLAGS_OPCODE_MASK )
#define DS_IFLAGS_DUMP_MASK_OP2 ( 0xF0000000 | DS_IFLAGS_OP2_MASK | DS_IFLAGS_OPCODE_MASK )
#define DS_IFLAGS_DUMP_MASK ( DS_IFLAGS_DUMP_MASK_OP1 | DS_IFLAGS_DUMP_MASK_OP2 )

/* Stack state */
#define DS_STATE_NEST 0x1
#define DS_STATE_ELSEIF 0x2
#define DS_STATE_ISSET_ISEMPTY 0x4

#define DS_STATE_DONE 0x00010000
#define DS_STATE_SKIP 0x00020000
#define DS_STATE_NONE 0x00040000

#define DS_STATE_RUNTIME_OBFUSCATE 0x00100000
#define DS_STATE_OBFUSCATE 0x00200000
#define DS_STATE_OP_ENCODE 0x00400000
#define DS_STATE_EXTEND 0x00800000

#define DS_STATE_MAIN 0x01000000
#define DS_STATE_CLASS 0x02000000
#define DS_STATE_FUNCTION 0x04000000
#define DS_STATE_INTERNAL 0x08000000

#define DS_STATE_SILENCE 0x20000000
#define DS_STATE_NO_INDENT 0x40000000
#define DS_STATE_SINGLE_INDENT 0x80000000

/* Variable type */
#define VE_TYPE_NULL 0
#define VE_TYPE_VAR 1
#define VE_TYPE_TMP_VAR 2
#define VE_TYPE_GLOBAL_VAR 4

/* Variable type mask */
#define VE_TYPE_VAR_MASK 0xFF

/* Variable flags( MUST large than DS_IFLAGS_OT_MASK ) */
#define VE_FLAGS_FLAGS 0x00001000
#define VE_FLAGS_SKIP_SILENCE 0x00002000

#define VE_FLAGS_NUMBER1 0x00010000
#define VE_FLAGS_NUMBER2 0x00020000
#define VE_FLAGS_FUNCTION 0x00040000
#define VE_FLAGS_MUTIARRAY 0x00080000

#define VE_FLAGS_QMASSIGN 0x00100000
#define VE_FLAGS_SILENCE 0x00200000
#define VE_FLAGS_ISSET_ISEMPTY 0x00400000
#define VE_FLAGS_VAR_MAP 0x0080000

#define VE_FLAGS_JMPZ 0x01000000
#define VE_FLAGS_JMPNZ 0x02000000
#define VE_FLAGS_JMPZ_EX 0x04000000
#define VE_FLAGS_JMPNZ_EX 0x08000000

#define VE_FLAGS_FREE 0x10000000
#define VE_FLAGS_EXTEND 0x20000000
#define VE_FLAGS_UPDATED 0x40000000
#define VE_FLAGS_OBFUSCATE 0x80000000

/* Combine flags */
#define VE_FLAGS_SILENCE_FUNCTION ( VE_FLAGS_SILENCE | VE_FLAGS_FUNCTION )

#define VE_FLAGS_FETCH_SHIFT 8
#define VE_FLAGS_FETCH_MAX_INDEX 0x3
#define MAKE_FETCH_FLAGS( Type ) ( ( Type + 1 ) << VE_FLAGS_FETCH_SHIFT )

#define VE_FLAGS_GLOBAL MAKE_FETCH_FLAGS( ZEND_FETCH_GLOBAL )
#define VE_FLAGS_LOCAL MAKE_FETCH_FLAGS( ZEND_FETCH_LOCAL )
#define VE_FLAGS_STATIC MAKE_FETCH_FLAGS( ZEND_FETCH_STATIC )

#define VE_FLAGS_FETCH_MASK ( VE_FLAGS_FETCH_MAX_INDEX << VE_FLAGS_FETCH_SHIFT )

#define VE_FLAGS_NUMBER_MASK ( VE_FLAGS_NUMBER1 | VE_FLAGS_NUMBER2 )
#define VE_FLAGS_EXPRESS_MASK ( VE_FLAGS_NUMBER_MASK | VE_FLAGS_FUNCTION | VE_FLAGS_MUTIARRAY | VE_FLAGS_ISSET_ISEMPTY | VE_FLAGS_JMPZ_EX | VE_FLAGS_JMPNZ_EX )
#define VE_FLAGS_HIGH_MASK ( VE_FLAGS_NUMBER_MASK | VE_FLAGS_FUNCTION | VE_FLAGS_MUTIARRAY | VE_FLAGS_SILENCE | VE_FLAGS_ISSET_ISEMPTY | VE_FLAGS_JMPZ_EX | VE_FLAGS_JMPNZ_EX )
#define VE_FLAGS_MASK ( DS_IFLAGS_OT_MASK | VE_FLAGS_FETCH_MASK | VE_FLAGS_HIGH_MASK )

/* Dump struct macro */
#define DUMP_STRUCT_SIZE( Str ) \
    ADD_DEBUG_LOG_LRA( "[%08X( %8d )]"#Str, sizeof( Str ), sizeof( Str ) )

#define DUMP_FIELD_OFFSET( Str, Element ) \
    ADD_DEBUG_LOG_LRA( "[%08X( %8d )]"#Str"->"#Element, FIELD_OFFSET( Str, Element ), FIELD_OFFSET( Str, Element ) )

/* Dump indent macro */
#define PUSH_INC_INDENT( Stack ) \
{ \
    ULONG Indent; \
    StackTopU( &Stack->Indent, &Indent ); \
    StackPushU( &Stack->Indent, Indent + GET_GS_INDENT( ) ); \
}

#define PUSH_INDENT( Stack, _Indent ) StackPushU( &Stack->Indent, _Indent )
#define POP_INDENT( Stack ) StackPopU( &Stack->Indent, NULL )
#define GET_INDENT( Stack, _Indent ) StackTopU( &Stack->Indent, _Indent )

/* Engine 2 Op type */
#ifndef IS_CV
#define IS_CV 0x10 /* Compiled variable */
#endif

/* Engine 2 Vm decode */
#define _CONST_CODE 0
#define _TMP_CODE 1
#define _VAR_CODE 2
#define _UNUSED_CODE 3
#define _CV_CODE 4

/* User defined Op type */
#define IS_CLASS 0x1
#define IS_FUNCTION 0xF0

/* User defined Id */
#define IS_SPECIFIC_ID 0x80000000

/* Engine 2 Op code */
#ifndef ZEND_ENGINE_2

#define ZEND_CATCH 107
#define ZEND_THROW 108
#define ZEND_FETCH_CLASS 109
#define ZEND_CLONE 110
#define ZEND_INIT_CTOR_CALL 111
#define ZEND_INIT_METHOD_CALL 112
#define ZEND_INIT_STATIC_METHOD_CALL 113
#define ZEND_ISSET_ISEMPTY_VAR 114
#define ZEND_ISSET_ISEMPTY_DIM_OBJ 115
#define ZEND_PRE_INC_OBJ 132
#define ZEND_PRE_DEC_OBJ 133
#define ZEND_POST_INC_OBJ 134
#define ZEND_POST_DEC_OBJ 135
#define ZEND_ASSIGN_OBJ 136
#define ZEND_OP_DATA 137
#define ZEND_INSTANCEOF 138
#define ZEND_RAISE_ABSTRACT_ERROR 142
#define ZEND_ADD_INTERFACE 144
#define ZEND_VERIFY_ABSTRACT_CLASS 146
#define ZEND_ASSIGN_DIM 147
#define ZEND_ISSET_ISEMPTY_PROP_OBJ 148
#define ZEND_HANDLE_EXCEPTION 149
#define ZEND_USER_OPCODE 150

/* Class fetches */
#define ZEND_FETCH_CLASS_DEFAULT 0
#define ZEND_FETCH_CLASS_SELF 1
#define ZEND_FETCH_CLASS_PARENT 2
#define ZEND_FETCH_CLASS_MAIN 3
#define ZEND_FETCH_CLASS_GLOBAL 4
#define ZEND_FETCH_CLASS_AUTO 5
#define ZEND_FETCH_CLASS_INTERFACE 6
#define ZEND_FETCH_CLASS_NO_AUTOLOAD 0x80

/* Method flags (types) */
#define ZEND_ACC_STATIC 0x01
#define ZEND_ACC_ABSTRACT 0x02
#define ZEND_ACC_FINAL 0x04
#define ZEND_ACC_IMPLEMENTED_ABSTRACT 0x08

/* Class flags (types) */
#define ZEND_ACC_IMPLICIT_ABSTRACT_CLASS 0x10
#define ZEND_ACC_EXPLICIT_ABSTRACT_CLASS 0x20
#define ZEND_ACC_FINAL_CLASS 0x40
#define ZEND_ACC_INTERFACE 0x80

/* Method flags (visibility) */
#define ZEND_ACC_PUBLIC 0x100
#define ZEND_ACC_PROTECTED 0x200
#define ZEND_ACC_PRIVATE 0x400
#define ZEND_ACC_PPP_MASK ( ZEND_ACC_PUBLIC | ZEND_ACC_PROTECTED | ZEND_ACC_PRIVATE )

#define ZEND_ACC_CHANGED 0x800
#define ZEND_ACC_IMPLICIT_PUBLIC 0x1000

/* Method flags (special method detection) */
#define ZEND_ACC_CTOR 0x2000
#define ZEND_ACC_DTOR 0x4000
#define ZEND_ACC_CLONE 0x8000

/* Method flag (bc only), any method that has this flag can be used statically and non statically. */
#define ZEND_ACC_ALLOW_STATIC 0x10000

/* Shadow of parent's private method/property */
#define ZEND_ACC_SHADOW 0x20000

/* Deprecation flag */
#define ZEND_ACC_DEPRECATED 0x40000

/* Op line */
#define OP_JMP( OpLine, Head ) ( ( OpLine )->op1.u.opline_num )
#define OP_JMPX( OpLine, Head ) ( ( OpLine )->op2.u.opline_num )
#define OP_JMPZNZ( OpLine, Head ) ( ( OpLine )->op2.u.opline_num )
#define NODE_JMP( Node, Head ) ( ( Node )->u.opline_num )
#define NODE_JMPX( Node, Head ) ( ( Node )->u.opline_num )
#define NODE_JMPZNZ( Node, Head ) ( ( Node )->u.opline_num )
#define NODE_VAR( Node ) ( ( Node )->u.var )

#define SET_OP_JMP( OpLine, Offset, Head ) ( ( OpLine )->op1.u.opline_num = ( Offset ) )
#define SET_OP_JMPX( OpLine, Offset, Head ) ( ( OpLine )->op2.u.opline_num = ( Offset ) )
#define SET_OP_JMPZNZ( OpLine, Offset, Head ) ( ( OpLine )->op2.u.opline_num = ( Offset ) )
#define SET_NODE_JMP( Node, Offset, Head ) ( ( Node )->u.opline_num = ( Offset ) )
#define SET_NODE_JMPX( Node, Offset, Head ) ( ( Node )->u.opline_num = ( Offset ) )
#define SET_NODE_JMPZNZ( Node, Offset, Head ) ( ( Node )->u.opline_num = ( Offset ) )
#define SET_NODE_VAR( Node, Var ) ( ( Node )->u.var = ( Var ) )

#define NODE_FETCH_TYPE( Node ) ( ( Node )->u.fetch_type )
#define SET_NODE_FETCH_TYPE( Node, Type ) ( ( Node )->u.fetch_type = ( Type ) )

#else

#define BYREF_NONE 0
#define BYREF_FORCE 1
#define BYREF_ALLOW 2
#define BYREF_FORCE_REST 3

#define ZEND_CTOR_CALL ( 1 << 1 )

#define ZEND_JMP_NO_CTOR 69
#define ZEND_UNSET_DIM_OBJ 75
#define ZEND_ISSET_ISEMPTY 76
#define ZEND_DECLARE_FUNCTION_OR_CLASS 100
#define ZEND_INIT_CTOR_CALL 111

/* Op line */
#define OP_JMP( OpLine, Head ) ( zend_uint ) ( ( OpLine )->op1.u.jmp_addr - ( Head ) )
#define OP_JMPX( OpLine, Head ) ( zend_uint ) ( ( OpLine )->op2.u.jmp_addr - ( Head ) )
#define OP_JMPZNZ( OpLine, Head ) ( ( OpLine )->op2.u.opline_num )
#define NODE_JMP( Node, Head ) ( zend_uint ) ( ( Node )->u.jmp_addr - ( Head ) )
#define NODE_JMPX( Node, Head ) ( zend_uint ) ( ( Node )->u.jmp_addr - ( Head ) )
#define NODE_JMPZNZ( Node, Head ) ( ( Node )->u.opline_num )
#define NODE_VAR( Node ) ( ( Node )->op_type == IS_TMP_VAR ? ( Node )->u.var / sizeof( temp_variable ) : ( Node )->u.var )

#define SET_OP_JMP( OpLine, Offset, Head ) ( ( OpLine )->op1.u.jmp_addr = ( Head ) + ( Offset ) )
#define SET_OP_JMPX( OpLine, Offset, Head ) ( ( OpLine )->op2.u.jmp_addr = ( Head ) + ( Offset ) )
#define SET_OP_JMPZNZ( OpLine, Offset, Head ) ( ( OpLine )->op2.u.opline_num = ( Offset ) )
#define SET_NODE_JMP( Node, Offset, Head ) ( ( Node )->u.opline_num = ( Head ) + ( Offset ) )
#define SET_NODE_JMPX( Node, Offset, Head ) ( ( Node )->u.opline_num = ( Head ) + ( Offset ) )
#define SET_NODE_JMPZNZ( Node, Offset, Head ) ( ( Node )->u.opline_num = ( Offset ) )
#define SET_NODE_VAR( Node, Var ) ( ( Node )->u.var = ( Node )->op_type == IS_TMP_VAR ? ( Var ) * sizeof( temp_variable ) : ( Var ) )

#define NODE_FETCH_TYPE( Node ) ( ( Node )->u.EA.type )
#define SET_NODE_FETCH_TYPE( Node, Type ) ( ( Node )->u.EA.type = ( Type ) )

#endif

/* Op code */
#define OP_CODE( OpLine ) ( ( OpLine )->opcode )
#define SET_OP_CODE( OpLine, OpCode ) ( ( OpLine )->opcode = ( OpCode ) )

/* Op extended value */
#define OP_EX_VALUE( OpLine ) ( ( OpLine )->extended_value )
#define SET_OP_EV( OpLine, Value ) ( ( OpLine )->extended_value = ( Value ) )

/* Op type and id */
#define OP1_VAL( OpLine ) ( &( OpLine )->op1.u.constant )
#define OP2_VAL( OpLine ) ( &( OpLine )->op2.u.constant )
#define OPR_VAL( OpLine ) ( &( OpLine )->result.u.constant )
#define OP1_VAL_TYPE( OpLine ) ( ( OpLine )->op1.u.constant.type )
#define OP2_VAL_TYPE( OpLine ) ( ( OpLine )->op2.u.constant.type )
#define OPR_VAL_TYPE( OpLine ) ( ( OpLine )->result.u.constant.type )
#define OP1_TYPE( OpLine ) ( ( OpLine )->op1.op_type )
#define OP2_TYPE( OpLine ) ( ( OpLine )->op2.op_type )
#define OPR_TYPE( OpLine ) ( ( OpLine )->result.op_type )
#define OP1_VAR( OpLine ) NODE_VAR( &( OpLine )->op1 )
#define OP2_VAR( OpLine ) NODE_VAR( &( OpLine )->op2 )
#define OPR_VAR( OpLine ) NODE_VAR( &( OpLine )->result )

#define OP1_VAR_EX( OpLine ) ( ( OpLine )->op1.u.var )
#define OP2_VAR_EX( OpLine ) ( ( OpLine )->op2.u.var )
#define OPR_VAR_EX( OpLine ) ( ( OpLine )->result.u.var )

#define SET_OP1_VAR( OpLine, Var ) SET_NODE_VAR( &OpLine->op1, Var )
#define SET_OP2_VAR( OpLine, Var ) SET_NODE_VAR( &OpLine->op2, Var )
#define SET_OPR_VAR( OpLine, Var ) SET_NODE_VAR( &OpLine->result, Var )

#define SET_OP1_VAR_EX( OpLine, Var ) ( ( OpLine )->op1.u.var = ( Var ) )
#define SET_OP2_VAR_EX( OpLine, Var ) ( ( OpLine )->op2.u.var = ( Var ) )
#define SET_OPR_VAR_EX( OpLine, Var ) ( ( OpLine )->result.u.var = ( Var ) )

/* Op extend type */
#define OP1_EA_TYPE( OpLine ) ( ( OpLine )->op1.u.EA.type )
#define OP2_EA_TYPE( OpLine ) ( ( OpLine )->op2.u.EA.type )
#define OPR_EA_TYPE( OpLine ) ( ( OpLine )->result.u.EA.type )

/* Op break-continue array */
#define OPLINE_BRK_CONT( OpLine ) ( ( OpLine )->op1.u.opline_num )

/* Op type test */
#define TEST_CONST( Node ) ( ( Node )->op_type == IS_CONST )
#define TEST_VAR( Node ) ( ( Node )->op_type == IS_VAR )
#define TEST_TMP_VAR( Node ) ( ( Node )->op_type == IS_TMP_VAR )
#define TEST_CMP_VAR( Node ) ( ( Node )->op_type == IS_CV )
#define TEST_NOT_TMP_VAR( Node ) ( ( Node )->op_type & ( IS_VAR | IS_CV ) )
#define TEST_ALL_VAR( Node ) ( ( Node )->op_type & ( IS_VAR | IS_TMP_VAR | IS_CV ) )

#define TEST_NUMBER( Node ) ( ( Node )->u.constant.type == IS_LONG || ( Node )->u.constant.type == IS_DOUBLE )

#define TEST_OP1_CONST( OpLine ) TEST_CONST( &OpLine->op1 )
#define TEST_OP2_CONST( OpLine ) TEST_CONST( &OpLine->op2 )
#define TEST_OPR_CONST( OpLine ) TEST_CONST( &OpLine->result )

#define TEST_OP1_TMP_VAR( OpLine ) TEST_TMP_VAR( &OpLine->op1 )
#define TEST_OP2_TMP_VAR( OpLine ) TEST_TMP_VAR( &OpLine->op2 )
#define TEST_OPR_TMP_VAR( OpLine ) TEST_TMP_VAR( &OpLine->result )

#define TEST_OP1_CMP_VAR( OpLine ) TEST_CMP_VAR( &OpLine->op1 )
#define TEST_OP2_CMP_VAR( OpLine ) TEST_CMP_VAR( &OpLine->op2 )
#define TEST_OPR_CMP_VAR( OpLine ) TEST_CMP_VAR( &OpLine->result )

#define TEST_OP1_ALL_VAR( OpLine ) TEST_ALL_VAR( &OpLine->op1 )
#define TEST_OP2_ALL_VAR( OpLine ) TEST_ALL_VAR( &OpLine->op2 )
#define TEST_OPR_ALL_VAR( OpLine ) TEST_ALL_VAR( &OpLine->result )

#define TEST_OP1_NUMBER( OpLine ) TEST_NUMBER( &OpLine->op1 )
#define TEST_OP2_NUMBER( OpLine ) TEST_NUMBER( &OpLine->op2 )
#define TEST_OPR_NUMBER( OpLine ) TEST_NUMBER( &OpLine->result )

/* Var string map key */
#define MAKE_KEY( Type, Var ) ( ( ( Type ) << 16 ) | ( Var ) )

/* Macro */
#define TSRMG_GET( Id ) ( *( ( void*** )TSRMLS_C ) )[TSRM_UNSHUFFLE_RSRC_ID( Id )]
#define TSRMG_GET_EX( TsrmLs, Id ) ( *( ( void*** )TsrmLs ) )[TSRM_UNSHUFFLE_RSRC_ID( Id )]

/* Encode/decode hash */
#define ENCODE_HASH_KEY 0x80000000
#define ENCODE_HASH( Data ) ( ( Data ) | ENCODE_HASH_KEY )
#define DECODE_HASH( Data ) ( ( Data ) & ~ENCODE_HASH_KEY )

/* Lock flags */
#define FLAGS_LOCKED 0x80000000

/* Logic prefix flags */
#define LL_FLAGS_TOP 0x10000000

/* Brk_cont list flags */
#define BL_FLAGS_SPECIAL 0x80000000

/* Logic op type */
#define OT_BOOL_AND 0
#define OT_BOOL_OR 1
#define OT_LG_AND 2
#define OT_LG_OR 3

/* Map flags */
#define FLAGS_OFFSET_MAP 0x80000000

/* Scan flags */
#define FLAGS_NEST 0x1
#define FLAGS_RETURN 0x2

#define FLAGS_NEST_RETURN ( FLAGS_NEST | FLAGS_RETURN )

/* Jmpx flags */
#define FLAGS_JMPX_SPECIAL 0x1
#define FLAGS_JMPX_MAP 0x2
#define FLAGS_JMPX_BRK 0x4
#define FLAGS_JMPX_CONT 0x8

#define FLAGS_JMPX_MAP_1 0x10003
#define FLAGS_JMPX_MAP_2 0x20003
#define FLAGS_JMPX_MAP_3 0x40003
#define FLAGS_JMPX_MAP_SWITCH 0x80003

/*
///////////////////////////////////////////////////////////////////////////////
// S T R U C T U R E S
///////////////////////////////////////////////////////////////////////////////
*/
typedef zend_op_array* ( *COMPILE_PROC ) ( zend_file_handle *, int TSRMLS_DC );
typedef void ( *EXECUTE_PROC ) ( zend_op_array* TSRMLS_DC );
typedef void ( *HANDLER_1 ) ( int ht, zval *return_value, zval *this_ptr, int return_value_used TSRMLS_DC );
typedef void ( *HANDLER_2 ) ( int ht, zval *return_value, zval **return_value_ptr, zval *this_ptr, int return_value_used TSRMLS_DC );
typedef int ( *opcode_handler_t_2 ) ( zend_execute_data *execute_data TSRMLS_DC );

typedef struct _znode_x {
    int op_type;
    union {
        zval constant;
        zend_uint var;
        zend_uint opline_num; /* Needs to be signed */
        zend_uint fetch_type;
        zend_op_array *op_array;
        zend_op *jmp_addr;
        struct {
            zend_uint var; /* dummy */
            zend_uint type;
        } EA;
    } u;
} znode_x;

typedef struct _zend_op_1 {
    zend_uchar opcode;
    znode_x result;
    znode_x op1;
    znode_x op2;
    ulong extended_value;
    uint lineno;
} zend_op_1;

typedef struct _zend_op_array_1 {
    zend_uchar type; /* MUST be the first element of this struct! */

    zend_uchar *arg_types; /* MUST be the second element of this struct! */
    TCHAR *function_name; /* MUST be the third element of this struct! */

    zend_uint *refcount;

    zend_op_1 *opcodes;
    zend_uint last, size;

    zend_uint T;

    zend_brk_cont_element *brk_cont_array;
    zend_uint last_brk_cont;
    zend_uint current_brk_cont;
    zend_bool uses_globals;

    /* static variables support */
    HashTable *static_variables;

    zend_op_1 *start_op;
    int backpatch_count;

    zend_bool return_reference;
    zend_bool done_pass_two;

    TCHAR *filename;

    void *reserved[ZEND_MAX_RESERVED_RESOURCES];
} zend_op_array_1;

typedef union _zvalue_value_1 {
    long lval; /* long value */
    double dval; /* double value */
    struct {
        TCHAR *val;
        int len;
    } str;
    HashTable *ht; /* hash table value */
    zend_object obj;
} zvalue_value_1;

typedef struct _zval_1 {
    /* Variable information */
    zvalue_value_1 value; /* value */
    zend_uint refcount;
    zend_uchar type; /* active type */
    zend_uchar is_ref;
} zval_1;

typedef struct _zend_overloaded_function_1 {
    zend_uchar type; /* MUST be the first element of this struct! */
    zend_uchar *arg_types; /* MUST be the second element of this struct */
    TCHAR *function_name; /* MUST be the third element of this struct */
    zend_uint var;
} zend_overloaded_function_1;

typedef union _zend_function_1 {
    zend_uchar type; /* MUST be the first element of this struct! */
    struct {
        zend_uchar type; /* never used */
        zend_uchar *arg_types;
        TCHAR *function_name;
    } common;

    zend_op_array_1 op_array;
    zend_internal_function internal_function;
    zend_overloaded_function_1 overloaded_function;
} zend_function_1;

typedef struct _zend_class_entry_1 {
    TCHAR type;
    TCHAR *name;
    uint name_length;
    struct _zend_class_entry_1 *parent;
    int *refcount;
    zend_bool constants_updated;

    HashTable function_table;
    HashTable default_properties;
    zend_function_entry *builtin_functions;

    /* handlers */
    PVOID handle_function_call;
    PVOID handle_property_get;
    PVOID handle_property_set;
} zend_class_entry_1;

typedef struct _zend_compiler_globals_1 {
    zend_stack bp_stack;
    zend_stack switch_cond_stack;
    zend_stack foreach_copy_stack;
    zend_stack object_stack;
    zend_stack declare_stack;

    zend_class_entry_1 class_entry, *active_class_entry;
    zval_1 active_ce_parent_class_name;

    /* variables for list() compilation */
    zend_llist list_llist;
    zend_llist dimension_llist;
    zend_stack list_stack;

    zend_stack function_call_stack;

    TCHAR *compiled_filename;

    int zend_lineno;
    int comment_start_line;
    TCHAR *heredoc;
    int heredoc_len;

    zend_op_array_1 *active_op_array;

    HashTable *function_table; /* function symbol table */
    HashTable *class_table; /* class table */

    HashTable filenames_table;

    HashTable *auto_globals;

    zend_bool in_compilation;
    zend_bool short_tags;
    zend_bool asp_tags;
    zend_bool allow_call_time_pass_reference;

    zend_declarables declarables;

    /* For extensions support */
    zend_bool extended_info; /* generate extension information for debugger/profiler */
    zend_bool handle_op_arrays; /* run op_arrays through op_array handlers */

    zend_bool unclean_shutdown;

    zend_bool ini_parser_unbuffered_errors;

    zend_llist open_files;

    struct _zend_ini_parser_param *ini_parser_param;

    int interactive;

    zend_bool increment_lineno;

#ifdef ZEND_MULTIBYTE
    zend_encoding **script_encoding_list;
    int script_encoding_list_size;

    zend_encoding *internal_encoding;

    zend_encoding_detector encoding_detector;
    zend_encoding_converter encoding_converter;
    zend_multibyte_oddlen multibyte_oddlen;
#endif /* ZEND_MULTIBYTE */
} zend_compiler_globals_1;

typedef struct _zend_executor_globals_1 {
    zval **return_value_ptr_ptr;

    zval uninitialized_zval;
    zval *uninitialized_zval_ptr;

    zval error_zval;
    zval *error_zval_ptr;

    zend_function_state *function_state_ptr;
    zend_ptr_stack arg_types_stack;

    /* symbol table cache */
    HashTable *symtable_cache[SYMTABLE_CACHE_SIZE];
    HashTable **symtable_cache_limit;
    HashTable **symtable_cache_ptr;

    zend_op **opline_ptr;

    zend_execute_data *current_execute_data;

    HashTable *active_symbol_table;
    HashTable symbol_table; /* main symbol table */

    HashTable included_files; /* files already included */

    jmp_buf bailout;

    int error_reporting;
    int orig_error_reporting;
    int exit_status;

    zend_op_array *active_op_array;

    HashTable *function_table; /* function symbol table */
    HashTable *class_table; /* class table */
    HashTable *zend_constants; /* constants table */

    long precision;

    int ticks_count;

    zend_bool in_execution;
    zend_bool bailout_set;
    zend_bool full_tables_cleanup;

    /* for extended information support */
    zend_bool no_extensions;

#ifdef ZEND_WIN32
    zend_bool timed_out;
#endif

    HashTable regular_list;
    HashTable persistent_list;

    zend_ptr_stack argument_stack;
    int free_op1, free_op2;
    int ( *unary_op ) ( zval *result, zval *op1 );
    int ( *binary_op ) ( zval *result, zval *op1, zval *op2 TSRMLS_DC );

    zval *garbage[2];
    int garbage_ptr;

    zval *user_error_handler;
    zend_ptr_stack user_error_handlers;

    /* timeout support */
    int timeout_seconds;

    int lambda_count;

    HashTable *ini_directives;

    void *reserved[ZEND_MAX_RESERVED_RESOURCES];
} zend_executor_globals_1;

typedef struct _zend_op_2 {
    void *handler;
    znode_x result;
    znode_x op1;
    znode_x op2;
    ulong extended_value;
    uint lineno;
    zend_uchar opcode;
} zend_op_2;

typedef struct _zend_property_info_2 {
    zend_uint flags;
    TCHAR *name;
    int name_length;
    ulong h;
    TCHAR *doc_comment;
    int doc_comment_len;
    struct _zend_class_entry_2 *ce;
} zend_property_info_2;

typedef struct _zend_arg_info_2 {
    TCHAR *name;
    zend_uint name_len;
    TCHAR *class_name;
    zend_uint class_name_len;
    zend_bool array_type_hint;
    zend_bool allow_null;
    zend_bool pass_by_reference;
    zend_bool return_reference;
    int required_num_args;
} zend_arg_info_2;

typedef struct _zend_compiled_variable_2 {
    TCHAR *name;
    int name_len;
    ulong hash_value;
} zend_compiled_variable_2;

typedef struct _zend_try_catch_element_2 {
    zend_uint try_op;
    zend_uint catch_op;
} zend_try_catch_element_2;

typedef struct _zend_op_array_2 {
    /* Common elements */
    zend_uchar type;
    TCHAR *function_name;
    zend_class_entry *scope;
    zend_uint fn_flags;
    union _zend_function_2 *prototype;
    zend_uint num_args;
    zend_uint required_num_args;
    zend_arg_info_2 *arg_info;
    zend_bool pass_rest_by_reference;
    unsigned char return_reference;
    /* END of common elements */

    zend_uint *refcount;

    zend_op_2 *opcodes;
    zend_uint last, size;

    zend_compiled_variable_2 *vars;
    int last_var, size_var;

    zend_uint T;

    zend_brk_cont_element *brk_cont_array;
    zend_uint last_brk_cont;
    zend_uint current_brk_cont;

    zend_try_catch_element_2 *try_catch_array;
    int last_try_catch;

    /* static variables support */
    HashTable *static_variables;

    zend_op_2 *start_op;
    int backpatch_count;

    zend_bool done_pass_two;
    zend_bool uses_this;

    TCHAR *filename;
    zend_uint line_start;
    zend_uint line_end;
    TCHAR *doc_comment;
    zend_uint doc_comment_len;

    void *reserved[ZEND_MAX_RESERVED_RESOURCES];
} zend_op_array_2;

typedef struct _zend_object_value_2 {
    unsigned int handle;
    void *handlers;
} zend_object_value_2;

typedef union _zvalue_value_2 {
    long lval; /* long value */
    double dval; /* double value */
    struct {
        TCHAR *val;
        int len;
    } str;
    HashTable *ht; /* hash table value */
    zend_object_value_2 obj;
} zvalue_value_2;

typedef struct _zval_2 {
    /* Variable information */
    zvalue_value_2 value; /* value */
    zend_uint refcount;
    zend_uchar type; /* active type */
    zend_uchar is_ref;
} zval_2;

typedef struct _zend_class_iterator_funcs_2 {
    PVOID *funcs;
    union _zend_function_2 *zf_new_iterator;
    union _zend_function_2 *zf_valid;
    union _zend_function_2 *zf_current;
    union _zend_function_2 *zf_key;
    union _zend_function_2 *zf_next;
    union _zend_function_2 *zf_rewind;
} zend_class_iterator_funcs_2;

typedef union _zend_function_2 {
    zend_uchar type; /* MUST be the first element of this struct! */

    struct {
        zend_uchar type; /* never used */
        TCHAR *function_name;
        zend_class_entry *scope;
        zend_uint fn_flags;
        union _zend_function *prototype;
        zend_uint num_args;
        zend_uint required_num_args;
        zend_arg_info_2 *arg_info;
        zend_bool pass_rest_by_reference;
        unsigned char return_reference;
    } common;

    zend_op_array_2 op_array;
    zend_internal_function internal_function;
} zend_function_2;

typedef struct _zend_class_entry_2 {
    TCHAR type;
    TCHAR *name;
    zend_uint name_length;
    struct _zend_class_entry_2 *parent;
    int refcount;
    zend_bool constants_updated;
    zend_uint ce_flags;

    HashTable function_table;
    HashTable default_properties;
    HashTable properties_info;
    HashTable default_static_members;
    HashTable *static_members;
    HashTable constants_table;
    struct _zend_function_entry *builtin_functions;

    union _zend_function_2 *constructor;
    union _zend_function_2 *destructor;
    union _zend_function_2 *clone;
    union _zend_function_2 *__get;
    union _zend_function_2 *__set;
    union _zend_function_2 *__unset;
    union _zend_function_2 *__isset;
    union _zend_function_2 *__call;
    union _zend_function_2 *__tostring;
    union _zend_function_2 *serialize_func;
    union _zend_function_2 *unserialize_func;

    zend_class_iterator_funcs_2 iterator_funcs;

    /* handlers */
    PVOID create_object;
    PVOID get_iterator;
    PVOID interface_gets_implemented;

    /* serializer callbacks */
    PVOID serialize;
    PVOID unserialize;

    struct _zend_class_entry_2 **interfaces;
    zend_uint num_interfaces;

    TCHAR *filename;
    zend_uint line_start;
    zend_uint line_end;
    TCHAR *doc_comment;
    zend_uint doc_comment_len;

    struct _zend_module_entry *module;
} zend_class_entry_2;

typedef struct _zend_compiler_globals_2 {
    zend_stack bp_stack;
    zend_stack switch_cond_stack;
    zend_stack foreach_copy_stack;
    zend_stack object_stack;
    zend_stack declare_stack;

    zend_class_entry *active_class_entry;

    /* variables for list() compilation */
    zend_llist list_llist;
    zend_llist dimension_llist;
    zend_stack list_stack;

    zend_stack function_call_stack;

    TCHAR *compiled_filename;

    int zend_lineno;
    int comment_start_line;
    TCHAR *heredoc;
    int heredoc_len;

    zend_op_array *active_op_array;

    HashTable *function_table; /* function symbol table */
    HashTable *class_table; /* class table */

    HashTable filenames_table;

    HashTable *auto_globals;

    zend_bool in_compilation;
    zend_bool short_tags;
    zend_bool asp_tags;
    zend_bool allow_call_time_pass_reference;

    zend_declarables declarables;

    /* For extensions support */
    zend_bool extended_info; /* generate extension information for debugger/profiler */
    zend_bool handle_op_arrays; /* run op_arrays through op_array handlers */

    zend_bool unclean_shutdown;

    zend_bool ini_parser_unbuffered_errors;

    zend_llist open_files;

    long catch_begin;

    struct _zend_ini_parser_param *ini_parser_param;

    int interactive;

    zend_uint start_lineno;
    zend_bool increment_lineno;

    znode implementing_class;

    zend_uint access_type;

    TCHAR *doc_comment;
    zend_uint doc_comment_len;

#ifdef ZEND_MULTIBYTE
    zend_encoding **script_encoding_list;
    int script_encoding_list_size;
    zend_bool detect_unicode;

    zend_encoding *internal_encoding;

    /* multibyte utility functions */
    void *encoding_detector;
    void *encoding_converter;
    void *encoding_oddlen;
#endif /* ZEND_MULTIBYTE */

#ifdef ZTS
    HashTable **static_members;
    int last_static_member;
#endif
} zend_compiler_globals_2;

typedef struct _zend_objects_store_2 {
    struct _zend_object_store_bucket *object_buckets;
    zend_uint top;
    zend_uint size;
    int free_list_head;
} zend_objects_store_2;

typedef struct _zend_executor_globals_2 {
    zval **return_value_ptr_ptr;

    zval uninitialized_zval;
    zval *uninitialized_zval_ptr;

    zval error_zval;
    zval *error_zval_ptr;

    zend_function_state *function_state_ptr;
    zend_ptr_stack arg_types_stack;

    /* symbol table cache */
    HashTable *symtable_cache[SYMTABLE_CACHE_SIZE];
    HashTable **symtable_cache_limit;
    HashTable **symtable_cache_ptr;

    zend_op **opline_ptr;

    HashTable *active_symbol_table;
    HashTable symbol_table; /* main symbol table */

    HashTable included_files; /* files already included */

    jmp_buf *bailout;

    int error_reporting;
    int orig_error_reporting;
    int exit_status;

    zend_op_array *active_op_array;

    HashTable *function_table; /* function symbol table */
    HashTable *class_table; /* class table */
    HashTable *zend_constants; /* constants table */

    zend_class_entry *scope;

    zval *This;

    long precision;

    int ticks_count;

    zend_bool in_execution;
    HashTable *in_autoload;
    zend_function_2 *autoload_func;
    zend_bool full_tables_cleanup;
    zend_bool ze1_compatibility_mode;

    /* for extended information support */
    zend_bool no_extensions;

#ifdef ZEND_WIN32
    zend_bool timed_out;
#endif

    HashTable regular_list;
    HashTable persistent_list;

    zend_ptr_stack argument_stack;

    int user_error_handler_error_reporting;
    zval *user_error_handler;
    zval *user_exception_handler;
    zend_stack user_error_handlers_error_reporting;
    zend_ptr_stack user_error_handlers;
    zend_ptr_stack user_exception_handlers;

    /* timeout support */
    int timeout_seconds;

    int lambda_count;

    HashTable *ini_directives;
    HashTable *modified_ini_directives;

    zend_objects_store_2 objects_store;
    zval *exception;
    zend_op *opline_before_exception;

    struct _zend_execute_data *current_execute_data;

    struct _zend_module_entry *current_module;

    zend_property_info_2 std_property_info;

    zend_bool active;

    void *reserved[ZEND_MAX_RESERVED_RESOURCES];
} zend_executor_globals_2;

/* Dump stack */
typedef struct _DUMP_STACK {
    /* Header */
    USHORT Type;
    USHORT Size;
    ULONG TotalSize;

    /* For Re-init */
    ULONG DummyStart;

    /* Global and current scan state */
    ULONG State;
    /* Global and current scan flags */
    ULONG InternalFlags;
    /* Current scan step */
    ULONG Step;
    /* Current op line offset */
    ULONG Offset;
    /* Last offset */
    ULONG LastOffset;
    /* Begin silence count */
    ULONG SilenceCount;

    /* Virtual last op code */
    zend_op LocalOpLine;
    /* Op array */
    zend_op_array *OpArray;
    /* Op line head */
    zend_op *Head;
    /* Op line Tail */
    zend_op *Tail;
    /* Current op line */
    zend_op *OpLine;
    /* Skip to next op line */
    zend_op *NextOpLine;
    /* Origin op code array */
    zend_uchar *OrgOpCode;
    /* Decode op code table */
    zend_uchar *DecodeOpCodeTable;
    /* Current op code name */
    const TCHAR *OpName;
    /* Current op code string */
    const TCHAR *OpString;
    /* Prefix string */
    TCHAR StartChar[4];
    /* Postfix string */
    TCHAR EndChar[4];
    /* Prefix string length */
    ULONG StartCharLength;
    /* Postfix string */
    ULONG EndCharLength;
    /* Function argument count */
    LONG ArgumentCount;

    /* Depend on Major id */
    PVOID ArgInfo;

    /* Extend information */
    struct _ZEND_EXTEND_INFO *ExtendInfo;

    /* Call argument depend on function */
    ULONG Argument;
    ULONG Argument1;
    ULONG Argument2;

    /* Call return code depend on function */
    ULONG RetCode;

    /* For Re-init */
    ULONG DummyEnd;

    /* Variable */
    ULONG VariableTableCount;
    LIST_ENTRY ListArray[DEFAULT_LIST_ARRAY_SIZE];
    CRITICAL_SECTION ListLockArray[DEFAULT_LIST_ARRAY_SIZE];

    ULONG LogicEndOffset;
    ULONG LogicEndJmp;
    ULONG LogicEndOffsetEx;
    ULONG LogicEndJmpEx;
    ULONG LogicEndType;
    ULONG LogicOpType;
    ULONG IssetEndOffset;
    COMMON_STACK ArgumentList;
    COMMON_STACK Trinary;
    COMMON_STACK_T ScanList;
    COMMON_STACK_T OffsetMap;
    COMMON_STACK_T VarStringMap;
    COMMON_STACK_T ControlList;
    COMMON_STACK_T BreakList;
    COMMON_STACK_T ContinueList;
    COMMON_STACK_T PostOpTypeList;
    COMMON_STACK_T Logic;
    COMMON_STACK_T LogicPrefix;
    COMMON_STACK_U Common;
    COMMON_STACK_U Common1;
    COMMON_STACK_U Common2;
    COMMON_STACK_U Indent;
    COMMON_STACK_U Skip;
    COMMON_STACK_U SkipOnce;
    COMMON_STACK_U PreSkip;
    COMMON_STACK_U Output;
    COMMON_STACK_U Declare;
    COMMON_STACK_U ReturnX;
    COMMON_STACK_U Jmp;
    COMMON_STACK_U JmpX;
    COMMON_STACK_U JmpXX;
    COMMON_STACK_U JmpZnz;
    COMMON_STACK_U If;
    COMMON_STACK_U ForEach;
    COMMON_STACK_U SwitchCase;
    COMMON_STACK_U SwitchFree;
    COMMON_STACK_U QmAssign;
    COMMON_STACK_U New;
    COMMON_STACK_U InitCall;
    COMMON_STACK_U LogicList;
    COMMON_STACK_U LogicPostfix;
    COMMON_STACK_U LogicOpReverse;
    COMMON_STACK_S LogicExpress;
    COMMON_STACK_S Isset;
    COMMON_STACK_S ArgumentString;
    COMMON_STACK_S Buffer;
    COMMON_STACK_S Buffer1;
    COMMON_STACK_S Buffer2;
    COMMON_STACK_S LargeBuffer;
    LIST_ENTRY ListEntry;
} DUMP_STACK, *PDUMP_STACK;

/* Global setting */
typedef struct _GLOBAL_SETTING {
    USHORT Type;
    USHORT Size;
    ULONG Signature;
    ULONG Init;
    /* See GS_FLAGS_XXX */
    ULONG Flags;
    ULONG State;
    ULONG LogType;
    ULONG ExtensionId;
    ULONG RealExtensionId;
    ULONG Version;
    ULONG FormatId;
    ULONG MajorId;
    ULONG Indent;
    ULONG StackSize;
    ULONG StackStringLength;
    USHORT DecodeLevelHigh;
    USHORT DecodeLevelLow;
    /* Global */
    TCHAR IndentChar[MAX_INDENT_CHAR];
    TCHAR ConstTrue[DEFAULT_TRUE_LENGTH_ROUND];
    PENCODE_STUB EncodeStub;
    /* Lock */
    CRITICAL_SECTION Lock;
    /* Stack list */
    LIST_ENTRY StackList;
    CRITICAL_SECTION StackListLock;
    LIST_ENTRY FreeStackList;
    CRITICAL_SECTION FreeStackListLock;
    COMMON_STACK_U StackPtrList;
    COMMON_STACK_U Class;
    COMMON_STACK_U Function;
    COMMON_STACK_U FunctionFlags;
    ULONG ExtensionModuleSize;
    ULONG HookTimeSignature;
    ULONG ExceptionCode;
    jmp_buf *JmpBuffer;
    void *ModuleBase;
    void *ExtensionModuleBase;
    void ***Context;
    COMPILE_PROC Compile;
    EXECUTE_PROC Execute;
    zend_scanner_globals *GScanner;
    zend_compiler_globals *GCompiler;
    zend_executor_globals *GExecutor;
    zend_function *zend_obfuscate_function_name;
    zend_function *zend_obfuscate_class_name;
    zend_op_array *OpArray;
    struct _DUMP_STACK *Stack;
    LIST_ENTRY ObfuscateName;
    CRITICAL_SECTION ObfuscateNameLock;
    LPCTSTR FileNamePtr;
    LPCTSTR ClassNamePtr;
    LPCTSTR FunctionNamePtr;
    ULONG FileNameLength;
    ULONG ClassNameLength;
    ULONG FunctionNameLength;
    COMMON_STACK FileName;
    COMMON_STACK ClassName;
    COMMON_STACK FunctionName;
    COMMON_STACK_S Buffer;
    COMMON_STACK_S Buffer1;
    FILETIME FakeTime;
    LPTSTR LastFile;
    TCHAR ModuleFile[MAX_MODULE_NAME_LENGTH];
    TCHAR ExtensionModuleName[MAX_MODULE_NAME_LENGTH];
    TCHAR HookTimeModuleName[MAX_MODULE_NAME_LENGTH];
    TCHAR ObfuscatePrefix[32];
    ULONG ObfuscatePrefixLength;
    TCHAR FileHead[MAX_PHP_FILE_HEAD_LENGTH];
    TCHAR FileTail[MAX_PHP_FILE_TAIL_LENGTH];
    TCHAR FileComment[MAX_PHP_FILE_COMMENT_LENGTH];
    TCHAR OutputExt[MAX_PHP_FILE_EXTENTION_LENGTH];
    TCHAR RootPath[MAX_PATH];
    TCHAR OutputPath[MAX_PATH];
    TCHAR OutputFile[MAX_PATH];
    TCHAR SourceFile[MAX_PATH];
    TCHAR ConfigFile[MAX_PATH];
    TCHAR LogFile[MAX_PATH];
} GLOBAL_SETTING, *PGLOBAL_SETTING;

/* Variable entry */
typedef struct _VARIABLE_ENTRY {
    ULONG Type;
    ULONG Id;
    /* See VE_FLAGS_XXX */
    ULONG Flags;
    ULONG Offset;
    LPTSTR Name;
    ULONG NameLength;
    ULONG MaxNameLength;
    LPTSTR Expr;
    ULONG ExprLength;
    ULONG MaxExprLength;
    LIST_ENTRY ListEntry;
} VARIABLE_ENTRY, *PVARIABLE_ENTRY;

/* Obfuscate name entry */
typedef struct _OBFUSCATE_NAME_ENTRY {
    LPTSTR Name;
    ULONG NameLength;
    LPTSTR ObfuscateName;
    ULONG ObfuscateNameLength;
    LIST_ENTRY ListEntry;
} OBFUSCATE_NAME_ENTRY, *POBFUSCATE_NAME_ENTRY;

/* Control list entry */
typedef struct _COMMON_CONTROL_ENTRY {
    ULONG Start;
    ULONG End;
    ULONG Offset;
    /* See DS_FLAGS_XXX */
    ULONG Flags;
    /* Type */
    ULONG Type;
} COMMON_CONTROL_ENTRY, *PCOMMON_CONTROL_ENTRY;

/* Control list */
typedef struct _CONTROL_LIST {
    ULONG Offset;
    COMMON_STACK_T List[2];
} CONTROL_LIST, *PCONTROL_LIST;

/* Logic express list */
typedef struct _LOGIC_LIST {
    /* Main key to compare */
    ULONG End;
    ULONG Start;
    /* See LL_FLAGS_XXX */
    ULONG Flags;
} LOGIC_LIST, *PLOGIC_LIST;

/* Logic express prefix list */
typedef struct _LOGIC_PREFIX_LIST {
    /* Main key to compare */
    ULONG Offset;
    /* See LL_FLAGS_XXX */
    ULONG Flags;
} LOGIC_PREFIX_LIST, *PLOGIC_PREFIX_LIST;

/* Break-continue list */
typedef struct _BRK_CONT_LIST {
    ULONG Continue;
    ULONG Break;
    ULONG Start;
    ULONG End;
    ULONG Offset;
    /* See BL_FLAGS_XXX */
    ULONG Flags;
} BRK_CONT_LIST, *PBRK_CONT_LIST;

/* Key value pair */
typedef struct _KEY_VALUE {
    /* Main key to compare */
    ULONG Key;
    /* Second key to compare when sort */
    ULONG Value;
} KEY_VALUE, *PKEY_VALUE;

/* String array */
typedef struct _STRING_ARRAY {
    TCHAR *Name;
    ULONG NameLength;
} STRING_ARRAY, *PSTRING_ARRAY;

typedef struct _STRING_ARRAY_EX {
    TCHAR *Name;
    ULONG NameLength;
    PVOID Data;
} STRING_ARRAY_EX, *PSTRING_ARRAY_EX;

typedef struct _ZEND_TRANS_INFO {
    TCHAR R0[0x1C]; /* 0x00 */
    zend_uchar *OpCodeTable; /* 0x1C */
    ULONG R32; /* 0x20 */
    ULONG R36; /* 0x24 */
    PVOID P40; /* 0x28 */
} ZEND_TRANS_INFO, *PZEND_TRANS_INFO;

typedef struct _ZEND_VAR_ENTRY {
    ULONG Reserved; /* 0x00 */
    TCHAR *Name; /* 0x04 */
    ULONG NameLengh; /* 0x08 */
    ULONG HashValue; /* 0x0C */
} ZEND_VAR_ENTRY, *PZEND_VAR_ENTRY;

typedef struct _ZEND_EXTEND_FUNCTION_INFO {
    PZEND_VAR_ENTRY StringList; /* 0x00 */
    ULONG StringIndex; /* 0x04 */
    ULONG StringSize; /* 0x08 */
    ULONG R12; /* 0x0C */
    PVOID P16; /* 0x10 */
    ULONG R20; /* 0x14 */
    ULONG R24; /* 0x18 */
    ULONG R28; /* 0x1C */
    PVOID P32; /* 0x20 */
    PVOID P36; /* 0x24 */
    ULONG R40; /* 0x28 */
    PVOID P44; /* 0x2C */
} ZEND_EXTEND_FUNCTION_INFO, *PZEND_EXTEND_FUNCTION_INFO;

typedef struct _ZEND_CONTEXT {
    PVOID P0; /* 0x00 */
    PVOID P4; /* 0x04 */
    PVOID P8; /* 0x08 */
    PVOID P12; /* 0x0C */
    PVOID P16; /* 0x10 */
    ULONG P20; /* 0x14 */
    ULONG P24; /* 0x18 */
    ULONG P28; /* 0x1C */
    PVOID P32; /* 0x20 */
    PVOID P36; /* 0x24 */
    ULONG P40; /* 0x28 */
    PVOID P44; /* 0x2C */
} ZEND_COTEXT, *PZEND_CONTEXT;

typedef struct _ZEND_EXTEND_INFO {
    PZEND_VAR_ENTRY StringList; /* 0x0 */
    ULONG StringIndex; /* 0x4 */
    ULONG StringSize; /* 0x8 */
    PZEND_EXTEND_FUNCTION_INFO Function; /* 0xC */
    ULONG Data; /* 0x10 */
    union {
        PZEND_TRANS_INFO Trans; /* 0x14 */
        PZEND_CONTEXT Context; /* 0x14 */
    } u;
    ULONG *RefCount; /* 0x18 */
    PKEY_VALUE Array; /* 0x1C */
    ULONG ArrayCount; /* 0x20 */
} ZEND_EXTEND_INFO, *PZEND_EXTEND_INFO;

/* Dump function prototype */
typedef ULONG ( FASTCALL *DUMP_HANDLER ) ( PDUMP_STACK );
typedef void ( FASTCALL *DUMP_CONTROL_HANDLER ) ( PDUMP_STACK, PCOMMON_CONTROL_ENTRY, TCHAR** );

/*
///////////////////////////////////////////////////////////////////////////////
// G L O B A L S
///////////////////////////////////////////////////////////////////////////////
*/
UCHAR g_DummyMainStart[4] = {
    0, 1, 0, 1
};

TCHAR g_HexCharArray[] = _T( "0123456789ABCDEF" );
UINT g_VmDecodeArray[] = {
    _UNUSED_CODE, /* 0 */
    _CONST_CODE, /* 1 = IS_CONST */
    _TMP_CODE, /* 2 = IS_TMP_VAR */
    _UNUSED_CODE, /* 3 */
    _VAR_CODE, /* 4 = IS_VAR */
    _UNUSED_CODE, /* 5 */
    _UNUSED_CODE, /* 6 */
    _UNUSED_CODE, /* 7 */
    _UNUSED_CODE, /* 8 = IS_UNUSED */
    _UNUSED_CODE, /* 9 */
    _UNUSED_CODE, /* 10 */
    _UNUSED_CODE, /* 11 */
    _UNUSED_CODE, /* 12 */
    _UNUSED_CODE, /* 13 */
    _UNUSED_CODE, /* 14 */
    _UNUSED_CODE, /* 15 */
    _CV_CODE /* 16 = IS_CV */
};

OPCODE_TABLE g_OpTableArray[] = {
    /* 000 */ { _T( "NOP" ), _T( "" ), DS_IFLAGS_OT_NOP },
    /* 001 */ { _T( "ADD" ), _T( "+" ), DS_IFLAGS_TWO_OP | DS_IFLAGS_OT_ADD },
    /* 002 */ { _T( "SUB" ), _T( "-" ), DS_IFLAGS_TWO_OP | DS_IFLAGS_OT_SUB },
    /* 003 */ { _T( "MUL" ), _T( "*" ), DS_IFLAGS_TWO_OP | DS_IFLAGS_OT_MUL },
    /* 004 */ { _T( "DIV" ), _T( "/" ), DS_IFLAGS_TWO_OP | DS_IFLAGS_OT_DIV },
    /* 005 */ { _T( "MOD" ), _T( "%" ), DS_IFLAGS_TWO_OP | DS_IFLAGS_OT_MOD },
    /* 006 */ { _T( "SL" ), _T( "<<" ), DS_IFLAGS_TWO_OP | DS_IFLAGS_OT_SL },
    /* 007 */ { _T( "SR" ), _T( ">>" ), DS_IFLAGS_TWO_OP | DS_IFLAGS_OT_SR },
    /* 008 */ { _T( "CONCAT" ), _T( "." ), DS_IFLAGS_TWO_OP | DS_IFLAGS_OT_CONCAT | DS_IFLAGS_COMPACT | DS_IFLAGS_FIX_OT },
    /* 009 */ { _T( "BW_OR" ), _T( "|" ), DS_IFLAGS_TWO_OP | DS_IFLAGS_OT_BW_OR },
    /* 010 */ { _T( "BW_AND" ), _T( "&" ), DS_IFLAGS_TWO_OP | DS_IFLAGS_OT_BW_AND },
    /* 011 */ { _T( "BW_XOR" ), _T( "^" ), DS_IFLAGS_TWO_OP | DS_IFLAGS_OT_BW_XOR },
    /* 012 */ { _T( "BW_NOT" ), _T( "~" ), DS_IFLAGS_ONE_OP | DS_IFLAGS_COMPACT | DS_IFLAGS_OT_BW_NOT },
    /* 013 */ { _T( "BOOL_NOT" ), _T( "!" ), DS_IFLAGS_OT_BOOL_NOT },
    /* 014 */ { _T( "BOOL_XOR" ), _T( "xor" ), DS_IFLAGS_TWO_OP | DS_IFLAGS_OT_LG_XOR },
    /* 015 */ { _T( "IS_IDENTICAL" ), _T( "===" ), DS_IFLAGS_TWO_OP | DS_IFLAGS_OT_IS_IDENTICAL },
    /* 016 */ { _T( "IS_NOT_IDENTICAL" ), _T( "!==" ), DS_IFLAGS_TWO_OP | DS_IFLAGS_OT_IS_NOT_IDENTICAL },
    /* 017 */ { _T( "IS_EQUAL" ), _T( "==" ), DS_IFLAGS_TWO_OP | DS_IFLAGS_OT_IS_EQUAL },
    /* 018 */ { _T( "IS_NOT_EQUAL" ), _T( "!=" ), DS_IFLAGS_TWO_OP | DS_IFLAGS_OT_IS_NOT_EQUAL },
    /* 019 */ { _T( "IS_SMALLER" ), _T( "<" ), DS_IFLAGS_TWO_OP | DS_IFLAGS_OT_IS_SMALLER },
    /* 020 */ { _T( "IS_SMALLER_OR_EQUAL" ), _T( "<=" ), DS_IFLAGS_TWO_OP | DS_IFLAGS_OT_IS_SMALLER_OR_EQUAL },
    /* 021 */ { _T( "CAST" ), _T( "" ), DS_IFLAGS_OT_CAST },
    /* 022 */ { _T( "QM_ASSIGN" ), _T( "=" ), DS_IFLAGS_OT_QM_ASSIGN },
    /* 023 */ { _T( "ASSIGN_ADD" ), _T( "+=" ), DS_IFLAGS_OP_ASSIGN | DS_IFLAGS_OT_ASSIGN_ADD },
    /* 024 */ { _T( "ASSIGN_SUB" ), _T( "-=" ), DS_IFLAGS_OP_ASSIGN | DS_IFLAGS_OT_ASSIGN_SUB },
    /* 025 */ { _T( "ASSIGN_MUL" ), _T( "*=" ), DS_IFLAGS_OP_ASSIGN | DS_IFLAGS_OT_ASSIGN_MUL },
    /* 026 */ { _T( "ASSIGN_DIV" ), _T( "/=" ), DS_IFLAGS_OP_ASSIGN | DS_IFLAGS_OT_ASSIGN_DIV},
    /* 027 */ { _T( "ASSIGN_MOD" ), _T( "%=" ), DS_IFLAGS_OP_ASSIGN | DS_IFLAGS_OT_ASSIGN_MOD },
    /* 028 */ { _T( "ASSIGN_SL" ), _T( "<<=" ), DS_IFLAGS_OP_ASSIGN | DS_IFLAGS_OT_ASSIGN_SL },
    /* 029 */ { _T( "ASSIGN_SR" ), _T( ">>=" ), DS_IFLAGS_OP_ASSIGN | DS_IFLAGS_OT_ASSIGN_SR },
    /* 030 */ { _T( "ASSIGN_CONCAT" ), _T( ".=" ), DS_IFLAGS_OP_ASSIGN | DS_IFLAGS_OT_ASSIGN_CONCAT },
    /* 031 */ { _T( "ASSIGN_BW_OR" ), _T( "|=" ), DS_IFLAGS_OP_ASSIGN | DS_IFLAGS_OT_ASSIGN_BW_OR },
    /* 032 */ { _T( "ASSIGN_BW_AND" ), _T( "&=" ), DS_IFLAGS_OP_ASSIGN | DS_IFLAGS_OT_ASSIGN_BW_AND },
    /* 033 */ { _T( "ASSIGN_BW_XOR" ), _T( "^=" ), DS_IFLAGS_OP_ASSIGN | DS_IFLAGS_OT_ASSIGN_BW_XOR },
    /* 034 */ { _T( "PRE_INC" ), _T( "++" ), DS_IFLAGS_ONE_OP | DS_IFLAGS_COMPACT | DS_IFLAGS_OT_PRE_INC },
    /* 035 */ { _T( "PRE_DEC" ), _T( "--" ), DS_IFLAGS_ONE_OP | DS_IFLAGS_COMPACT | DS_IFLAGS_OT_PRE_DEC },
    /* 036 */ { _T( "POST_INC" ), _T( "++" ), DS_IFLAGS_ONE_OP | DS_IFLAGS_COMPACT | DS_IFLAGS_POST | DS_IFLAGS_OT_POST_INC },
    /* 037 */ { _T( "POST_DEC" ), _T( "--" ), DS_IFLAGS_ONE_OP | DS_IFLAGS_COMPACT | DS_IFLAGS_POST | DS_IFLAGS_OT_POST_DEC },
    /* 038 */ { _T( "ASSIGN" ), _T( "=" ), DS_IFLAGS_OP_ASSIGN | DS_IFLAGS_OT_ASSIGN },
    /* 039 */ { _T( "ASSIGN_REF" ), _T( "=&" ), DS_IFLAGS_OP_ASSIGN | DS_IFLAGS_OT_ASSIGN_REF },
    /* 040 */ { _T( "ECHO" ), _T( "echo" ), 0 },
    /* 041 */ { _T( "PRINT" ), _T( "print" ), 0 },
    /* 042 */ { _T( "JMP" ), _T( "" ), DS_IFLAGS_FIX_NODE },
    /* 043 */ { _T( "JMPZ" ), _T( " && " ), DS_IFLAGS_FIX_NODE | DS_IFLAGS_OT_BOOL_AND }, /* if ( ){} or while ( ){} or switch ( ){} */
    /* 044 */ { _T( "JMPNZ" ), _T( " || " ), DS_IFLAGS_FIX_NODE | DS_IFLAGS_OT_BOOL_OR }, /* do{} while ( ) */
    /* 045 */ { _T( "JMPZNZ" ), _T( "" ), DS_IFLAGS_FIX_NODE }, /* for ( ){} */
    /* 046 */ { _T( "JMPZ_EX" ), _T( " && " ), DS_IFLAGS_FIX_NODE | DS_IFLAGS_OT_BOOL_AND },
    /* 047 */ { _T( "JMPNZ_EX" ), _T( " || " ), DS_IFLAGS_FIX_NODE | DS_IFLAGS_OT_BOOL_OR },
    /* 048 */ { _T( "CASE" ), _T( "case" ), 0 },
    /* 049 */ { _T( "SWITCH_FREE" ), _T( "}" ), 0 },
    /* 050 */ { _T( "BRK" ), _T( "break" ), 0 },
    /* 051 */ { _T( "CONT" ), _T( "continue" ), 0 },
    /* 052 */ { _T( "BOOL" ), _T( "" ), 0 },
    /* 053 */ { _T( "INIT_STRING" ), _T( "" ), 0 },
    /* 054 */ { _T( "ADD_CHAR" ), _T( "" ), 0 },
    /* 055 */ { _T( "ADD_STRING" ), _T( "" ), 0 },
    /* 056 */ { _T( "ADD_VAR" ), _T( "" ), 0 },
    /* 057 */ { _T( "BEGIN_SILENCE" ), _T( "" ), 0 },
    /* 058 */ { _T( "END_SILENCE" ), _T( "" ), 0 },
    /* 059 */ { _T( "INIT_FCALL_BY_NAME" ), _T( "" ), 0 },
    /* 060 */ { _T( "DO_FCALL" ), _T( "" ), 0 },
    /* 061 */ { _T( "DO_FCALL_BY_NAME" ), _T( "" ), 0 },
    /* 062 */ { _T( "RETURN" ), _T( "return" ), 0 },
    /* 063 */ { _T( "RECV" ), _T( "" ), 0 },
    /* 064 */ { _T( "RECV_INIT" ), _T( "" ), 0 },
    /* 065 */ { _T( "SEND_VAL" ), _T( "" ), 0 },
    /* 066 */ { _T( "SEND_VAR" ), _T( "" ), 0 },
    /* 067 */ { _T( "SEND_REF" ), _T( "" ), 0 },
    /* 068 */ { _T( "NEW" ), _T( "new" ), DS_IFLAGS_FIX_NODE | DS_IFLAGS_OT_NEW },
    /* 069 */ { _T( "JMP_NO_CTOR" ), _T( "" ), DS_IFLAGS_FIX_NODE },
    /* 070 */ { _T( "FREE" ), _T( "free" ), 0 },
    /* 071 */ { _T( "INIT_ARRAY" ), _T( "=>" ), 0 },
    /* 072 */ { _T( "ADD_ARRAY_ELEMENT" ), _T( "=>" ), 0 },
    /* 073 */ { _T( "INCLUDE_OR_EVAL" ), _T( "" ), 0 },
    /* 074 */ { _T( "UNSET_VAR" ), _T( "unset" ), 0 },
    /* 075 */ { _T( "UNSET_DIM_OBJ" ), _T( "unset" ), 0 },
    /* 076 */ { _T( "ISSET_ISEMPTY" ), _T( "" ), 0 },
    /* 077 */ { _T( "FE_RESET" ), _T( "" ), 0 },
    /* 078 */ { _T( "FE_FETCH" ), _T( "foreach" ), 0 },
    /* 079 */ { _T( "EXIT" ), _T( "exit" ), 0 },
    /* 080 */ { _T( "FETCH_R" ), _T( "" ), DS_IFLAGS_OP_FETCH },
    /* 081 */ { _T( "FETCH_DIM_R" ), _T( "" ), 0 },
    /* 082 */ { _T( "FETCH_OBJ_R" ), _T( "" ), 0 },
    /* 083 */ { _T( "FETCH_W" ), _T( "" ), DS_IFLAGS_OP_FETCH },
    /* 084 */ { _T( "FETCH_DIM_W" ), _T( "" ), 0 },
    /* 085 */ { _T( "FETCH_OBJ_W" ), _T( "" ), 0 },
    /* 086 */ { _T( "FETCH_RW" ), _T( "" ), DS_IFLAGS_OP_FETCH },
    /* 087 */ { _T( "FETCH_DIM_RW" ), _T( "" ), 0 },
    /* 088 */ { _T( "FETCH_OBJ_RW" ), _T( "" ), 0 },
    /* 089 */ { _T( "FETCH_IS" ), _T( "" ), 0 },
    /* 090 */ { _T( "FETCH_DIM_IS" ), _T( "" ), 0 },
    /* 091 */ { _T( "FETCH_OBJ_IS" ), _T( "" ), 0 },
    /* 092 */ { _T( "FETCH_FUNC_ARG" ), _T( "" ), DS_IFLAGS_OP_FETCH },
    /* 093 */ { _T( "FETCH_DIM_FUNC_ARG" ), _T( "" ), 0 },
    /* 094 */ { _T( "FETCH_OBJ_FUNC_ARG" ), _T( "" ), 0 },
    /* 095 */ { _T( "FETCH_UNSET" ), _T( "" ), 0 },
    /* 096 */ { _T( "FETCH_DIM_UNSET" ), _T( "" ), 0 },
    /* 097 */ { _T( "FETCH_OBJ_UNSET" ), _T( "" ), 0 },
    /* 098 */ { _T( "FETCH_DIM_TMP_VAR" ), _T( "" ), 0 },
    /* 099 */ { _T( "FETCH_CONSTANT" ), _T( "" ), 0 },
    /* 100 */ { _T( "DECLARE_FUNCTION_OR_CLASS" ), _T( "" ), 0 },
    /* 101 */ { _T( "EXT_STMT" ), _T( "" ), 0 },
    /* 102 */ { _T( "EXT_FCALL_BEGIN" ), _T( "" ), 0 },
    /* 103 */ { _T( "EXT_FCALL_END" ), _T( "" ), 0 },
    /* 104 */ { _T( "EXT_NOP" ), _T( "" ), 0 },
    /* 105 */ { _T( "TICKS" ), _T( "" ), 0 },
    /* 106 */ { _T( "SEND_VAR_NO_REF" ), _T( "" ), 0 },

/* Engine 2 */
    /* 107 */ { _T( "CATCH" ), _T( "catch" ), 0 },
    /* 108 */ { _T( "THROW" ), _T( "throw" ), 0 },

    /* 109 */ { _T( "FETCH_CLASS" ), _T( "" ), DS_IFLAGS_FIX_NODE },

    /* 110 */ { _T( "CLONE" ), _T( "" ), DS_IFLAGS_FIX_NODE },

    /* 111 */ { _T( "INIT_CTOR_CALL" ), _T( "" ), 0 },
    /* 112 */ { _T( "INIT_METHOD_CALL" ), _T( "" ), 0 },
    /* 113 */ { _T( "INIT_STATIC_METHOD_CALL" ), _T( "" ), 0 },

    /* 114 */ { _T( "ISSET_ISEMPTY_VAR" ), _T( "isset" ), 0 },
    /* 115 */ { _T( "ISSET_ISEMPTY_DIM_OBJ" ), _T( "isset" ), 0 },

    /* 116 */ { _T( "IMPORT_FUNCTION" ), _T( "" ), 0 },
    /* 117 */ { _T( "IMPORT_CLASS" ), _T( "" ), 0 },
    /* 118 */ { _T( "IMPORT_CONST" ), _T( "" ), 0 },

    /* 119 */ { _T( "119" ), _T( "" ), 0 },
    /* 120 */ { _T( "120" ), _T( "" ), 0 },

    /* 121 */ { _T( "ASSIGN_ADD_OBJ" ), _T( "" ), DS_IFLAGS_OP_ASSIGN | DS_IFLAGS_OT_ASSIGN_ADD },
    /* 122 */ { _T( "ASSIGN_SUB_OBJ" ), _T( "" ), DS_IFLAGS_OP_ASSIGN | DS_IFLAGS_OT_ASSIGN_SUB },
    /* 123 */ { _T( "ASSIGN_MUL_OBJ" ), _T( "" ), DS_IFLAGS_OP_ASSIGN | DS_IFLAGS_OT_ASSIGN_MUL },
    /* 124 */ { _T( "ASSIGN_DIV_OBJ" ), _T( "" ), DS_IFLAGS_OP_ASSIGN | DS_IFLAGS_OT_ASSIGN_DIV },
    /* 125 */ { _T( "ASSIGN_MOD_OBJ" ), _T( "" ), DS_IFLAGS_OP_ASSIGN | DS_IFLAGS_OT_ASSIGN_MOD },
    /* 126 */ { _T( "ASSIGN_SL_OBJ" ), _T( "" ), DS_IFLAGS_OP_ASSIGN | DS_IFLAGS_OT_ASSIGN_SL },
    /* 127 */ { _T( "ASSIGN_SR_OBJ" ), _T( "" ), DS_IFLAGS_OP_ASSIGN | DS_IFLAGS_OT_ASSIGN_SR },
    /* 128 */ { _T( "ASSIGN_CONCAT_OBJ" ), _T( "" ), DS_IFLAGS_OP_ASSIGN | DS_IFLAGS_OT_CONCAT },
    /* 129 */ { _T( "ASSIGN_BW_OR_OBJ" ), _T( "" ), DS_IFLAGS_OP_ASSIGN | DS_IFLAGS_OT_BW_OR },
    /* 130 */ { _T( "ASSIGN_BW_AND_OBJ" ), _T( "" ), DS_IFLAGS_OP_ASSIGN | DS_IFLAGS_OT_BW_AND },
    /* 131 */ { _T( "ASSIGN_BW_XOR_OBJ" ), _T( "" ), DS_IFLAGS_OP_ASSIGN | DS_IFLAGS_OT_BW_XOR },

    /* 132 */ { _T( "PRE_INC_OBJ" ), _T( "++" ), DS_IFLAGS_ONE_OP | DS_IFLAGS_COMPACT | DS_IFLAGS_OT_PRE_INC },
    /* 133 */ { _T( "PRE_DEC_OBJ" ), _T( "--" ), DS_IFLAGS_ONE_OP | DS_IFLAGS_COMPACT | DS_IFLAGS_OT_PRE_DEC },
    /* 134 */ { _T( "POST_INC_OBJ" ), _T( "++" ), DS_IFLAGS_ONE_OP | DS_IFLAGS_COMPACT | DS_IFLAGS_POST | DS_IFLAGS_OT_POST_INC },
    /* 135 */ { _T( "POST_DEC_OBJ" ), _T( "--" ), DS_IFLAGS_ONE_OP | DS_IFLAGS_COMPACT | DS_IFLAGS_POST | DS_IFLAGS_OT_POST_DEC },

    /* 136 */ { _T( "ASSIGN_OBJ" ), _T( "=" ), DS_IFLAGS_OP_ASSIGN | DS_IFLAGS_OT_ASSIGN },
    /* 137 */ { _T( "OP_DATA" ), _T( "" ), DS_IFLAGS_FIX_NODE },

    /* 138 */ { _T( "INSTANCEOF" ), _T( "instanceof" ), 0 },

    /* 139 */ { _T( "DECLARE_CLASS" ), _T( "" ), 0 },
    /* 140 */ { _T( "DECLARE_INHERITED_CLASS" ), _T( "" ), 0 },
    /* 141 */ { _T( "DECLARE_FUNCTION" ), _T( "" ), 0 },

    /* 142 */ { _T( "RAISE_ABSTRACT_ERROR" ), _T( "" ), 0 },

    /* 143 */ { _T( "START_NAMESPACE" ), _T( "" ), 0 },

    /* 144 */ { _T( "ADD_INTERFACE" ), _T( "" ), 0 },
    /* 145 */ { _T( "VERIFY_INSTANCEOF" ), _T( "" ), 0 },
    /* 146 */ { _T( "VERIFY_ABSTRACT_CLASS" ), _T( "" ), 0 },
    /* 147 */ { _T( "ASSIGN_DIM" ), _T( "" ), 0 },
    /* 148 */ { _T( "ISSET_ISEMPTY_PROP_OBJ" ), _T( "isset" ), 0 },
    /* 149 */ { _T( "HANDLE_EXCEPTION" ), _T( "" ), 0 },
    /* 150 */ { _T( "USER_OPCODE" ), _T( "" ), DS_IFLAGS_FIX_NODE },
};

TCHAR g_OpTypeArray[][16] = {
    _T( "const" ),
    _T( "tmp_var" ),
    _T( "var" ),
    _T( "unused" ),
};

TCHAR g_DataTypeArray[][16] = {
    _T( "NULL" ),
    _T( "integer" ),
    _T( "double" ),
    _T( "string" ),
    _T( "array" ),
    _T( "object" ),
    _T( "boolean" ),
    _T( "resource" ),
    _T( "constant" ),
    _T( "constant_array" ),
};

TCHAR g_VarTypeArray[][8] = {
    _T( "Var" ),
    _T( "Tmp" ),
    _T( "CV" ),
    _T( "UN" ),
    _T( "CLS" ),
    _T( "FN" ),
};

TCHAR g_OpStringEx[][8] = {
    _T( " && " ),
    _T( " || " ),
    _T( " and " ),
    _T( " or " ),
};

TCHAR g_Fmt3String[][16] = {
    _T( "%s %s %s" ),
    _T( "%s%s%s" ),
    _T( "%s %s ( %s )" ),
    _T( "%s%s( %s )" ),
    _T( "( %s ) %s %s" ),
    _T( "( %s )%s%s" ),
    _T( "( %s ) %s ( %s )" ),
    _T( "( %s )%s( %s )" ),
};

TCHAR g_Fmt2String[][16] = {
    _T( "%s %s" ),
    _T( "%s%s" ),
    _T( "%s ( %s )" ),
    _T( "%s( %s )" ),
    _T( "%s %s" ),
    _T( "%s%s" ),
    _T( "( %s ) %s" ),
    _T( "( %s )%s" ),
};

/* Default log file */
TCHAR g_LogFile[] = DEFAULT_LOG_FILE_PRINT;
/* Default configure file */
TCHAR g_ConfigFile[] = DEFAULT_CONFIG_FILE_PRINT;

TCHAR g_HelpInformation[] = {
    _T( "\r\n====Php dump help====\r\n\r\n" )
    _T( "[{/}|{-}command[:attributes]]\r\n\r\n" )
    _T( "/h or /?     help \r\n" )
    _T( "/detail{/d}  show detail\r\n" )
    _T( "/opcode      show opcode\r\n" )
    _T( "/oparray     show oparray\r\n" )
    _T( "/function    show all the function\r\n" )
    _T( "/class       show all the class\r\n" )
    _T( "/hash        show all known hash table\r\n" )
    _T( "/info        log general infomation(default %s)\r\n" )
    _T( "/raw{/r}     dump raw op code\r\n" )
    _T( "/execute     execute the file(default NOT)\r\n" )
    _T( "/backup{/b}  backup the file with extension .bak if out file exist\r\n" )
    _T( "/append{/a}  appaned to previous log file\r\n" )
    _T( "/tick{/t}    show tick span\r\n" )
    _T( "/noexpire    ignore file expire\r\n" )
    _T( "/noindent    ignore indent\r\n" )
    _T( "/compact     dump with compact style[not support yet]\r\n" )
    _T( "/classic     dump with classic style[not support yet]\r\n" )
#if PRIVATE_VERSION
    _T( "/bug         dump bug statement\r\n" )
    _T( "/debug       add break point at pre-compile and post-execute\r\n" )
#endif
    _T( "/full        set to full mode\r\n" )
    _T( "/force{/f}   set to force mode\r\n" )
    _T( "/import{/i}  import class and function name[obfuscate name] from config file\r\n" )
    _T( "/export{/e}  export class and function name[obfuscate name] to config file\r\n" )
    _T( "/obfuscate   dump obfuscate name and its url encoded name\r\n" )
    _T( "/dic         dump obfuscate name dictionary depend on $level\r\n" )
    _T( "/tab         dump with tab prefix(default space)\r\n" )
    _T( "/indent:$i   dump with indent $i(default %d)\r\n" )
    _T( "/stack:$i    dump with stack size $i(default %d)\r\n" )
    _T( "/string:$i   dump with stack string length $i(default %d)\r\n" )
    _T( "/level:$i,$j dump with decode level range $i-$j(default %d-%d)\r\n" )
    _T( "/ext:$ext    dump to file with file extension $ext(default %s)\r\n" )
    _T( "/root:$root  dump to $path + ( $source - $root ) if specified /path:$path\r\n" )
    _T( "/path:$path  dump to $path\r\n" )
    _T( "/file:$file  dump to $file\r\n" )
    _T( "/config[:$c] override config file by %c([:%s])\r\n" )
    _T( "/log[:$name] override log name by $name([:%s])\r\n" )
    _T( "/logtype:$t  override log type by $t<file|registry|debug|messagebox>\r\n" )
#if PRIVATE_VERSION
    _T( "/head:$head  override php head, support escape characters, see help\r\n" )
    _T( "/tail:$tail  override php tail, support escape characters, see help\r\n" )
    _T( "/comment:$c  override php comment, support escape characters, see help\r\n" )
    _T( "/prefix:$p   dump to file with obfuscate prefix $p(default %s)\r\n" )
#endif
    _T( "/ini[:$ini]  override php.ini search path by $ini([:.], if not specified)\r\n" )
    _T( "\r\nEnviroment string PHP_DECODE_XXX override default setting, see help" )
    _T( "\r\nPriority(high->low):" )
    _T( "\r\nCommand line->Enviroment string->default setting\r\n" )
    _T( "\r\nif $ext set to *, then keep origin file extension" )
    _T( "\r\nif $path = 'd:\\', $root = 'e:\\', then 'e:\\php\\xxx'=>'d:\\php\\xxx'" )
    _T( "\r\n\r\n====Php dump help====\r\n\r\n" )
};

UCHAR g_DummyMainEnd[4] = {
    0, 1, 0, 1
};

void dummy_start( );
void dummy_end( );
void dummy_start_1( );
void dummy_end_1( );

/* Decode local string */
void DecodeLocalString( );

/* Encode range */
ENCODE_RANGE g_Range[] = {
    { &g_DummyMainStart, &g_DummyMainEnd, ES_FLAGS_ENCODE_1 },
    { dummy_start, dummy_end, ES_FLAGS_ENCODE_2 },
    { dummy_start_1, dummy_end_1, ES_FLAGS_ENCODE_1 },
    { StackAlloc, StackRemoveIndexS, ES_FLAGS_ENCODE_1 },
};

/* Encode stub */
ENCODE_STUB g_Stub = {
    TYPE_ENCODE_GLOBAL,
    sizeof( ENCODE_STUB ),
    0,
    0,
    DEFAULT_ENCODE_KEY,
    DEFAULT_ENCODE_KEY_LENGTH,
    { 0 },
    0,
    { 0 },
    SIZE_OF_ARRAY( g_Range ),
    g_Range
};
PENCODE_STUB g_StubPtr = &g_Stub;

/* Global setting */
GLOBAL_SETTING g_Setting = { TYPE_GLOBAL_SETTING,
    sizeof( GLOBAL_SETTING ),
    DEFAULT_SIGNATURE, /* Signature */
    0, /* Initiate */
    0, /* Flags */
    0, /* State */
    DEFAULT_LOG_TYPE, /* Log type */
    DEFAULT_EXTENSION_ID, /* Extension id */
    DEFAULT_EXTENSION_ID, /* Real extension id */
    0, /* Version */
    0, /* Format id */
    0, /* Major id */
    DEFAULT_INDENT, /* Indent */
    DEFAULT_STACK_SIZE, /* Stack size */
    DEFAULT_STRING_LENGTH, /* Stack string length */
    DEFAULT_DECODE_LEVEL_HIGH, /* Decode level high */
    DEFAULT_DECODE_LEVEL_LOW, /* Decode level low */
    DEFAULT_INDENT_STRING, /* Indent string */
    DEFAULT_TRUE, /* Path environment positive value */
    &g_Stub, /* Encode stub */
    { 0 }, /* Lock */
    { 0 }, /* Stack list */
    { 0 }, /* Stack list lock */
    { 0 }, /* Free stack list */
    { 0 }, /* Free stack list lock */
    { 0 }, /* Stack pointer list */
    { 0 }, /* Class pointer list */
    { 0 }, /* Function pointer list */
    { 0 }, /* Function flags list */
    0, /* Extension module size */
    0, /* Hook time signature */
    0, /* Exception code */
    NULL, /* Jump buffer */
    NULL, /* Module base address */
    NULL, /* Extension module base address */
    NULL, /* Context */
    NULL, /* Compile routine */
    NULL, /* Execute routine */
    NULL, /* Scanner */
    NULL, /* Compiler */
    NULL, /* Execute */
    NULL, /* zend_obfuscate_function_name */
    NULL, /* zend_obfuscate_class_name */
    NULL, /* OpArray */
    NULL, /* Stack */
    { 0 }, /* Obfuscate name list */
    { 0 }, /* Obfuscate name list lock */
    DEFAULT_FILE_MAIN, /* File name pointer */
    DEFAULT_FILE_MAIN, /* Class name pointer */
    DEFAULT_FILE_MAIN, /* Function name pointer */
    DEFAULT_FILE_MAIN_LENGTH, /* File name length */
    DEFAULT_FILE_MAIN_LENGTH, /* Class name length */
    DEFAULT_FILE_MAIN_LENGTH, /* Function name length */
    { 0 }, /* File name list */
    { 0 }, /* Class name list */
    { 0 }, /* Function name list */
    { 0 }, /* String buffer */
    { 0 }, /* String buffer1 */
    { 0 }, /* Fake time */
    NULL, /* Last log file */
    DEFAULT_MODULE_FILE_NAME, /* Default module name */
    DEFAULT_EXTENSION_MODULE_NAME, /* Default extension module name */
    DEFAULT_HOOK_TIME_MODULE_NAME, /* Default hook time module name */
    DEFAULT_OBFUSCATE_PREFIX, /* Default obfuscate prefix */
    DEFAULT_OBFUSCATE_PREFIX_LENGTH, /* Default obfuscate prefix length */
    DEFAULT_FILE_HEAD, /* File head */
    DEFAULT_FILE_TAIL, /* File tail */
    DEFAULT_FILE_COMMENT, /* Comment */
    DEFAULT_FILE_EXTENSION, /* Extension */
    _T( "" ), /* Base source file path */
    _T( "" ), /* Output path */
    _T( "" ), /* Output file */
    _T( "" ), /* Output source file */
    _T( "" ), /* Configure file */
    _T( "" ), /* Log file */
};
PGLOBAL_SETTING g_SettingPtr = &g_Setting;

/* For encode local string */
UCHAR g_DummyMainStart_1[4] = {
    0, 1, 0, 1
};

/* Extern function Prototype */
extern TCHAR *php_url_encode( TCHAR *, int, int * );

/* Function prototype */
int parse_string_len( const TCHAR *String, ULONG Length );
int parse_string( TCHAR *Buffer, const TCHAR *String, ULONG Length );
int parse_string_len_url( const TCHAR *String, ULONG Length );
int parse_string_url( TCHAR *Buffer, const TCHAR *String, ULONG Length );

ULONG make_printable_zval( zval *Expr, PCOMMON_STACK_S StringBuffer );
ULONG make_printable_zval_ex( zval *Expr, PCOMMON_STACK_S StringBuffer, ULONG Enclose );
ULONG make_printable_zval_url( zval *Expr, PCOMMON_STACK_S StringBuffer );
ULONG make_printable_zval_url_ex( zval *Expr, PCOMMON_STACK_S StringBuffer, ULONG Enclose );

ULONG FASTCALL dump_two_op_function( PDUMP_STACK Stack );
ULONG FASTCALL dump_assign_function( PDUMP_STACK Stack );

ULONG dump_opcode( PDUMP_STACK Stack );
ULONG dump_function( HashTable *Table, LPCTSTR Name, ULONG Length, ULONG Indent );
ULONG dump_class( HashTable *Table, LPCTSTR Name, ULONG Length, LPCTSTR ParentName, ULONG ParentLength, LPCTSTR ImplementName, ULONG ImplementNameLength, ULONG Indent );

ULONG AddObfuscateClass( HashTable *Table );
ULONG AddObfuscateFunction( HashTable *Table );

ULONG decode_obfuscate_function_name( PCOMMON_STACK_S Buffer, LPCTSTR Name, ULONG Length );
ULONG decode_obfuscate_class_name( PCOMMON_STACK_S Buffer, LPCTSTR Name, ULONG Length );

/*
///////////////////////////////////////////////////////////////////////////////
// F U N C T I O N S
///////////////////////////////////////////////////////////////////////////////
*/
#ifdef ZEND_ENGINE_2
ZEND_API zend_uchar *zend_get_user_opcodes( );
ZEND_API opcode_handler_t *zend_get_user_opcode_handlers( );
#else
#define ZEND_OPCODE_HANDLER_ARGS zend_execute_data * TSRMLS_DC
typedef int ( *opcode_handler_t ) ( ZEND_OPCODE_HANDLER_ARGS );
__forceinline zend_uchar *zend_get_user_opcodes( )
{
    return NULL;
}
__forceinline opcode_handler_t *zend_get_user_opcode_handlers( )
{
    return NULL;
}
#endif

/* Get functions */
__forceinline zend_op *get_oparray_op( zend_op_array *OpArray )
{
    register zend_op *Head;
    if ( GET_GS( )->ExtensionId < EXTENSION_ID_2 )
    {
        if ( ( ( zend_op_array_1* )OpArray )->start_op )
            Head = ( zend_op* ) ( ( zend_op_array_1* )OpArray )->start_op;
        else
            Head = ( zend_op* ) ( ( zend_op_array_1* )OpArray )->opcodes;
    }
    else
    {
        if ( ( ( zend_op_array_2* )OpArray )->start_op )
            Head = ( zend_op* ) ( ( zend_op_array_2* )OpArray )->start_op;
        else
            Head = ( zend_op* ) ( ( zend_op_array_2* )OpArray )->opcodes;
    }

    return Head;
}

__forceinline zend_op *get_oparray_op_1( zend_op_array *OpArray )
{
    if ( ( ( zend_op_array_1* )OpArray )->start_op )
        return ( zend_op* ) ( ( zend_op_array_1* )OpArray )->start_op;
    else
        return ( zend_op* ) ( ( zend_op_array_1* )OpArray )->opcodes;
}

__forceinline zend_op *get_oparray_op_2( zend_op_array *OpArray )
{
    if ( ( ( zend_op_array_2* )OpArray )->start_op )
        return ( zend_op* ) ( ( zend_op_array_2* )OpArray )->start_op;
    else
        return ( zend_op* ) ( ( zend_op_array_2* )OpArray )->opcodes;
}

__forceinline LPCTSTR get_file_name_ex( zend_op_array *OpArray )
{
    if ( GET_GS( )->ExtensionId < EXTENSION_ID_2 )
        return ( ( zend_op_array_1* )OpArray )->filename;
    else
        return ( ( zend_op_array_2* )OpArray )->filename;
}

__forceinline LPCTSTR get_function_name_ex( zend_op_array *OpArray )
{
    if ( GET_GS( )->ExtensionId < EXTENSION_ID_2 )
        return ( ( zend_op_array_1* )OpArray )->function_name;
    else
        return ( ( zend_op_array_2* )OpArray )->function_name;
}

__forceinline LPCTSTR get_file_name( )
{
    return GET_GS( )->FileNamePtr;
}

__forceinline ULONG get_file_name_length( )
{
    return GET_GS( )->FileNameLength;
}

void dummy_start( )
{
    /* Just for count */
}

/* Push file name */
void push_file_name( const TCHAR *FileName, ULONG Length )
{
    if ( FileName )
    {
        if ( Length == 0 )
            Length = _tcslen( FileName );

        StackPush( &GET_GS( )->FileName, ( PVOID )FileName, Length + 1 );
        StackTop( &GET_GS( )->FileName, ( PVOID* )&GET_GS( )->FileNamePtr );
        GET_GS( )->FileNameLength = Length;
    }
    else
    {
        StackPush( &GET_GS( )->FileName, DEFAULT_FILE_MAIN, DEFAULT_FILE_MAIN_LENGTH + 1 );
        StackTop( &GET_GS( )->FunctionName, ( PVOID* )&GET_GS( )->FunctionNamePtr );
        GET_GS( )->FileNameLength = DEFAULT_FILE_MAIN_LENGTH;
    }
}

/* Pop file name */
void pop_file_name( )
{
    StackPop( &GET_GS( )->FileName, NULL, 0 );

    if ( !StackCount( &GET_GS( )->FileName ) )
        StackPush( &GET_GS( )->FileName, DEFAULT_FILE_MAIN, DEFAULT_FILE_MAIN_LENGTH + 1 );

    StackTop( &GET_GS( )->FileName, ( PVOID* )&GET_GS( )->FileNamePtr );
    GET_GS( )->FileNameLength = _tcslen( GET_GS( )->FileNamePtr );
}

__forceinline LPCTSTR get_class_name( )
{
    return GET_GS( )->ClassNamePtr;
}

__forceinline ULONG get_class_name_length( )
{
    return GET_GS( )->ClassNameLength;
}

/* Push class name */
void push_class_name( const TCHAR *ClassName, ULONG Length )
{
    if ( ClassName )
    {
        if ( Length == 0 )
            Length = _tcslen( ClassName );

        StackPush( &GET_GS( )->ClassName, ( PVOID )ClassName, Length + 1 );
        StackTop( &GET_GS( )->ClassName, ( PVOID* )&GET_GS( )->ClassNamePtr );
        GET_GS( )->ClassNameLength = Length;
    }
    else
    {
        StackPush( &GET_GS( )->ClassName, DEFAULT_FILE_MAIN, DEFAULT_FILE_MAIN_LENGTH + 1 );
        StackTop( &GET_GS( )->FunctionName, ( PVOID* )&GET_GS( )->FunctionNamePtr );
        GET_GS( )->ClassNameLength = DEFAULT_FILE_MAIN_LENGTH;
    }
}

/* Push class name */
void push_class_name_ex( const TCHAR *ClassName, ULONG Length )
{
    if ( ClassName )
    {
        if ( Length == 0 )
            Length = _tcslen( ClassName );

        decode_obfuscate_class_name( &GET_GS( )->Buffer, ClassName, Length );
        Length = StackPopAllS( &GET_GS( )->Buffer, &ClassName );
        StackPush( &GET_GS( )->ClassName, ( PVOID )ClassName, Length + 1 );
        StackTop( &GET_GS( )->ClassName, ( PVOID* )&GET_GS( )->ClassNamePtr );
        GET_GS( )->ClassNameLength = Length;
    }
    else
    {
        StackPush( &GET_GS( )->ClassName, DEFAULT_FILE_MAIN, DEFAULT_FILE_MAIN_LENGTH + 1 );
        StackTop( &GET_GS( )->FunctionName, ( PVOID* )&GET_GS( )->FunctionNamePtr );
        GET_GS( )->ClassNameLength = DEFAULT_FILE_MAIN_LENGTH;
    }
}

/* Pop class name */
void pop_class_name( )
{
    StackPop( &GET_GS( )->ClassName, NULL, 0 );

    if ( !StackCount( &GET_GS( )->ClassName ) )
        StackPush( &GET_GS( )->ClassName, DEFAULT_FILE_MAIN, DEFAULT_FILE_MAIN_LENGTH + 1 );

    StackTop( &GET_GS( )->ClassName, ( PVOID* )&GET_GS( )->ClassNamePtr );
    GET_GS( )->ClassNameLength = _tcslen( GET_GS( )->ClassNamePtr );
}

__forceinline LPCTSTR get_function_name( )
{
    return GET_GS( )->FunctionNamePtr;
}

__forceinline ULONG get_function_name_length( )
{
    return GET_GS( )->FunctionNameLength;
}

/* Push function name */
void push_function_name( const TCHAR *FunctionName, ULONG Length )
{
    if ( FunctionName )
    {
        if ( Length == 0 )
            Length = _tcslen( FunctionName );

        StackPush( &GET_GS( )->FunctionName, ( PVOID )FunctionName, Length + 1 );
        StackTop( &GET_GS( )->FunctionName, ( PVOID* )&GET_GS( )->FunctionNamePtr );
        GET_GS( )->FunctionNameLength = Length;
    }
    else
    {
        StackPush( &GET_GS( )->FunctionName, DEFAULT_FILE_MAIN, DEFAULT_FILE_MAIN_LENGTH + 1 );
        StackTop( &GET_GS( )->FunctionName, ( PVOID* )&GET_GS( )->FunctionNamePtr );
        GET_GS( )->FunctionNameLength = DEFAULT_FILE_MAIN_LENGTH;
    }
}

/* Push function name */
void push_function_name_ex( const TCHAR *FunctionName, ULONG Length )
{
    if ( FunctionName )
    {
        if ( Length == 0 )
            Length = _tcslen( FunctionName );

        decode_obfuscate_function_name( &GET_GS( )->Buffer, FunctionName, Length );
        Length = StackPopAllS( &GET_GS( )->Buffer, &FunctionName );
        StackPush( &GET_GS( )->FunctionName, ( PVOID )FunctionName, Length + 1 );
        StackTop( &GET_GS( )->FunctionName, ( PVOID* )&GET_GS( )->FunctionNamePtr );
        GET_GS( )->FunctionNameLength = Length;
    }
    else
    {
        StackPush( &GET_GS( )->FunctionName, DEFAULT_FILE_MAIN, DEFAULT_FILE_MAIN_LENGTH + 1 );
        StackTop( &GET_GS( )->FunctionName, ( PVOID* )&GET_GS( )->FunctionNamePtr );
        GET_GS( )->FunctionNameLength = DEFAULT_FILE_MAIN_LENGTH;
    }
}

/* Pop function name */
void pop_function_name( )
{
    StackPop( &GET_GS( )->FunctionName, NULL, 0 );

    if ( !StackCount( &GET_GS( )->FunctionName ) )
        StackPush( &GET_GS( )->FunctionName, DEFAULT_FILE_MAIN, DEFAULT_FILE_MAIN_LENGTH + 1 );

    StackTop( &GET_GS( )->FunctionName, ( PVOID* )&GET_GS( )->FunctionNamePtr );
    GET_GS( )->FunctionNameLength = _tcslen( GET_GS( )->FunctionNamePtr );
}

/* Dump functions */
void dump_indent_string( ULONG Indent )
{
    register ULONG Left;
    TCHAR Buffer[BUFFER_SIZE + 4];

    Left = Indent;
    while ( Left > BUFFER_SIZE )
    {
        memset( Buffer, GET_GS_INDENT_CHAR( ), BUFFER_SIZE * sizeof( TCHAR ) );
        Buffer[BUFFER_SIZE] = _T( '\0' );
        ADD_LOG( Buffer );
        Left -= BUFFER_SIZE;
    }

    if ( Left )
    {
        memset( Buffer, GET_GS_INDENT_CHAR( ), Left * sizeof( TCHAR ) );
        Buffer[Left] = _T( '\0' );
        ADD_LOG( Buffer );
    }
}

__forceinline ULONG dump_string_no_indent( const TCHAR *Format )
{
    return ADD_LOG( Format );
}

ULONG dump_string_no_indent_ex( PDUMP_STACK Stack, const TCHAR *Format, ... )
{
    ULONG RetCode;
    va_list vlArgs;
    TCHAR *String;

    String = StackBaseS( &Stack->LargeBuffer );

    va_start( vlArgs, Format );
    RetCode = _vsntprintf( String,
        StackMaxS( &Stack->LargeBuffer ),
        Format,
        vlArgs
        );
    va_end( vlArgs );

    ADD_LOG( String );

    return RetCode;
}

__forceinline void dump_indent_string_stub( ULONG Indent )
{
    if ( !( GET_GS_FLAGS( ) & GS_FLAGS_NOINDENT ) )
        dump_indent_string( Indent );
}

ULONG dump_string( PDUMP_STACK Stack, const TCHAR *Format )
{
    ULONG Indent;

    if ( Stack->State & DS_STATE_SINGLE_INDENT )
    {
        dump_indent_string_stub( 1 );
    }
    else if ( !( Stack->State & DS_STATE_NO_INDENT ) )
    {
        GET_INDENT( Stack, &Indent );
        dump_indent_string_stub( Indent );
    }

    return ADD_LOG( Format );
}

ULONG dump_string_ex( PDUMP_STACK Stack, const TCHAR *Format, ... )
{
    ULONG RetCode;
    ULONG Indent;
    va_list vlArgs;
    TCHAR *String;

    String = StackBaseS( &Stack->LargeBuffer );

    va_start( vlArgs, Format );
    RetCode = _vsntprintf( String,
        StackMaxS( &Stack->LargeBuffer ),
        Format,
        vlArgs
        );
    va_end( vlArgs );

    if ( Stack->State & DS_STATE_SINGLE_INDENT )
    {
        dump_indent_string_stub( 1 );
    }
    else if ( !( Stack->State & DS_STATE_NO_INDENT ) )
    {
        GET_INDENT( Stack, &Indent );
        dump_indent_string_stub( Indent );
    }

    ADD_LOG( String );

    return RetCode;
}

LONG BreakListCompare( PBRK_CONT_LIST Entry1, PBRK_CONT_LIST Entry2 )
{
    return Entry1->Break - Entry2->Break;
}

LONG ContinueListCompare( PBRK_CONT_LIST Entry1, PBRK_CONT_LIST Entry2 )
{
    return Entry1->Continue - Entry2->Continue;
}

LONG LogicPrefixListCompare( PLOGIC_PREFIX_LIST Entry1, PLOGIC_PREFIX_LIST Entry2 )
{
    if ( Entry1->Offset == Entry2->Offset )
    {
        if ( Entry1->Flags & LL_FLAGS_TOP )
            return 1;
        else
            return - 1;
    }
    else
        return Entry1->Offset - Entry2->Offset;
}

/* Postfix */
LONG ControlListComparePostfix( PCOMMON_CONTROL_ENTRY Entry1, PCOMMON_CONTROL_ENTRY Entry2 )
{
    register LONG Result;

    /* Range large value small behind */
    Result = ( Entry2->End - Entry2->Start ) - ( Entry1->End - Entry1->Start );
    if ( Result == 0 )
    {
        if ( Entry1->Type & DS_TYPE_TOP )
            return 1;
        else
            return - 1;
    }
    else
    {
        return Result;
    }
}

/* Prefix */
LONG ControlListComparePrefix( PCOMMON_CONTROL_ENTRY Entry1, PCOMMON_CONTROL_ENTRY Entry2 )
{
    register LONG Result;

    /* Range large value large front */
    Result = ( Entry1->End - Entry1->Start ) - ( Entry2->End - Entry2->Start );
    if ( Result == 0 )
    {
        if ( Entry1->Type & DS_TYPE_TOP )
            return 1;
        else
            return - 1;
    }
    else
    {
        return Result;
    }
}

ULONG InitControlList( PCONTROL_LIST List, PVOID Context )
{
    register ULONG RetCode;

    RetCode = StackInitT( &List->List[0], ( ULONG )Context, sizeof( COMMON_CONTROL_ENTRY ), NULL, NULL, ControlListComparePostfix, NULL, List );
    RetCode &= StackInitT( &List->List[1], ( ULONG )Context, sizeof( COMMON_CONTROL_ENTRY ), NULL, NULL, ControlListComparePrefix, NULL, List );

    return RetCode;
}

ULONG UninitControlList( PCONTROL_LIST List, PVOID Context )
{
    register ULONG RetCode;

    UNREFERENCED_PARAMETER( Context );

    if ( GET_GS_FLAGS( ) & GS_IFLAGS_QUITTING )
    {
        RetCode = StackUninitT( &List->List[0] );
        RetCode &= StackUninitT( &List->List[1] );
    }
    else
    {
        RetCode = StackReinitT( &List->List[0] ) > 0;
        RetCode &= StackReinitT( &List->List[1] ) > 0;
    }

    return RetCode;
}

ULONG UninitVarStringMap( PKEY_VALUE KeyValue, PVOID Context )
{
    HEAP_FREE( ( PVOID )KeyValue->Value );

    return TRUE;
}

ULONG FASTCALL AllocateStack( ULONG StackDepth, ULONG StringLength, ULONG Size )
{
    PGLOBAL_SETTING Setting;
    register ULONG Iter;
    register ULONG Count;
    register ULONG Iter1;
    register ULONG Count1;
    register ULONG TotalSize;
    register PDUMP_STACK Stack;

    Setting = GET_GS( );
    Count = Size;
    TotalSize = ROUND_TO_BIT( sizeof( DUMP_STACK ), 8 );
    for ( Iter = 0; Iter < Count; Iter++ )
    {
        /* Allocate memory */
        Stack = ( PDUMP_STACK )HEAP_ALLOC( TotalSize );
        if ( Stack == NULL )
            break;

        /* Initiate default */
        memset( Stack, 0, TotalSize );

        /* Initiate type information */
        Stack->Type = TYPE_DUMP_STACK;
        Stack->Size = sizeof( DUMP_STACK );
        Stack->TotalSize = TotalSize;

        Count1 = SIZE_OF_ARRAY( Stack->ListArray );
        Stack->VariableTableCount = Count1;
        for ( Iter1 = 0; Iter1 < Count1; Iter1++ )
        {
            InitializeListHead( &Stack->ListArray[Iter1] );
            InitializeCriticalSection( &Stack->ListLockArray[Iter1] );
        }

        /* Initiate list */
        StackInit( &Stack->ArgumentList, StackDepth );
        StackInit( &Stack->Trinary, StackDepth );
        StackInitT( &Stack->ScanList, StackDepth, sizeof( KEY_VALUE ), NULL, NULL, NULL, NULL, NULL );
        StackInitT( &Stack->OffsetMap, StackDepth, sizeof( KEY_VALUE ), NULL, NULL, NULL, NULL, NULL );
        StackInitT( &Stack->VarStringMap, StackDepth, sizeof( KEY_VALUE ), NULL, UninitVarStringMap, NULL, NULL, NULL );
        StackInitT( &Stack->ControlList, StackDepth, sizeof( CONTROL_LIST ), InitControlList, UninitControlList, NULL, NULL, ( PVOID )4 );
        StackInitT( &Stack->BreakList, StackDepth, sizeof( BRK_CONT_LIST ), NULL, NULL, BreakListCompare, BreakListCompare, NULL );
        StackInitT( &Stack->ContinueList, StackDepth, sizeof( BRK_CONT_LIST ), NULL, NULL, ContinueListCompare, ContinueListCompare, NULL );
        StackInitT( &Stack->PostOpTypeList, StackDepth, sizeof( KEY_VALUE ), NULL, NULL, NULL, NULL, NULL );
        StackInitT( &Stack->Logic, StackDepth, sizeof( LOGIC_LIST ), NULL, NULL, NULL, NULL, NULL );
        StackInitT( &Stack->LogicPrefix, StackDepth, sizeof( LOGIC_PREFIX_LIST ), NULL, NULL, LogicPrefixListCompare, NULL, NULL );
        StackInitU( &Stack->Common, StackDepth );
        StackInitU( &Stack->Common1, StackDepth );
        StackInitU( &Stack->Common2, StackDepth );
        StackInitU( &Stack->Indent, StackDepth );
        StackInitU( &Stack->Skip, StackDepth );
        StackInitU( &Stack->SkipOnce, StackDepth );
        StackInitU( &Stack->PreSkip, StackDepth );
        StackInitU( &Stack->Output, StackDepth );
        StackInitU( &Stack->Declare, StackDepth );
        StackInitU( &Stack->ReturnX, StackDepth );
        StackInitU( &Stack->Jmp, StackDepth );
        StackInitU( &Stack->JmpX, StackDepth );
        StackInitU( &Stack->JmpXX, StackDepth );
        StackInitU( &Stack->JmpZnz, StackDepth );
        StackInitU( &Stack->If, StackDepth );
        StackInitU( &Stack->ForEach, StackDepth );
        StackInitU( &Stack->SwitchCase, StackDepth );
        StackInitU( &Stack->SwitchFree, StackDepth );
        StackInitU( &Stack->QmAssign, StackDepth );
        StackInitU( &Stack->New, StackDepth );
        StackInitU( &Stack->InitCall, StackDepth );
        StackInitU( &Stack->LogicList, StackDepth );
        StackInitU( &Stack->LogicPostfix, StackDepth );
        StackInitU( &Stack->LogicOpReverse, StackDepth );
        StackInitS( &Stack->LogicExpress, StringLength );
        StackInitS( &Stack->Isset, SMALL_BUFFER_SIZE );
        StackInitS( &Stack->ArgumentString, SMALL_BUFFER_SIZE );
        StackInitS( &Stack->Buffer, StringLength );
        StackInitS( &Stack->Buffer1, StringLength );
        StackInitS( &Stack->Buffer2, StringLength );
        StackInitS( &Stack->LargeBuffer, LARGE_BUFFER_SIZE );

        /* Insert into free list */
        ExInterlockedInsertTailList( &Setting->FreeStackList, &Stack->ListEntry, &Setting->FreeStackListLock );
    }

    return Iter;
}

void FASTCALL FreeStack( PDUMP_STACK Stack )
{
    register ULONG Iter;
    register ULONG Count;
    register PLIST_ENTRY ListHead;
    register PLIST_ENTRY ListEntry;
    register PVARIABLE_ENTRY Var;

    if ( Stack )
    {
        Count = Stack->VariableTableCount;
        for ( Iter = 0; Iter < Count; Iter++ )
        {
            ListHead = &Stack->ListArray[Iter];
            EnterCriticalSection( &Stack->ListLockArray[Iter] );
            while ( ( ListEntry = RemoveHeadList( ListHead ) ) )
            {
                Var = CONTAINING_RECORD( ListEntry, VARIABLE_ENTRY, ListEntry );
                if ( Var->Name )
                    HEAP_FREE( Var->Name );

                if ( Var->Expr )
                    HEAP_FREE( Var->Expr );

                HEAP_FREE( Var );
            }
            LeaveCriticalSection( &Stack->ListLockArray[Iter] );
            DeleteCriticalSection( &Stack->ListLockArray[Iter] );
        }

        /* Un-initiate list */
        StackUninit( &Stack->ArgumentList );
        StackUninit( &Stack->Trinary );
        StackUninitT( &Stack->ScanList );
        StackUninitT( &Stack->OffsetMap );
        StackUninitT( &Stack->VarStringMap );
        StackUninitT( &Stack->ControlList );
        StackUninitT( &Stack->BreakList );
        StackUninitT( &Stack->ContinueList );
        StackUninitT( &Stack->PostOpTypeList );
        StackUninitT( &Stack->Logic );
        StackUninitT( &Stack->LogicPrefix );
        StackUninitU( &Stack->Common );
        StackUninitU( &Stack->Common1 );
        StackUninitU( &Stack->Common2 );
        StackUninitU( &Stack->Indent );
        StackUninitU( &Stack->Skip );
        StackUninitU( &Stack->SkipOnce );
        StackUninitU( &Stack->PreSkip );
        StackUninitU( &Stack->Output );
        StackUninitU( &Stack->Declare );
        StackUninitU( &Stack->ReturnX );
        StackUninitU( &Stack->Jmp );
        StackUninitU( &Stack->JmpX );
        StackUninitU( &Stack->JmpXX );
        StackUninitU( &Stack->JmpZnz );
        StackUninitU( &Stack->If );
        StackUninitU( &Stack->ForEach );
        StackUninitU( &Stack->SwitchCase );
        StackUninitU( &Stack->SwitchFree );
        StackUninitU( &Stack->QmAssign );
        StackUninitU( &Stack->New );
        StackUninitU( &Stack->InitCall );
        StackUninitU( &Stack->LogicList );
        StackUninitU( &Stack->LogicPostfix );
        StackUninitU( &Stack->LogicOpReverse );
        StackUninitS( &Stack->LogicExpress );
        StackUninitS( &Stack->Isset );
        StackUninitS( &Stack->ArgumentString );
        StackUninitS( &Stack->Buffer );
        StackUninitS( &Stack->Buffer1 );
        StackUninitS( &Stack->Buffer2 );
        StackUninitS( &Stack->LargeBuffer );

        /* Free memory */
        if ( Stack->OrgOpCode )
        {
            HEAP_FREE( Stack->OrgOpCode );
            Stack->OrgOpCode = NULL;
        }

        HEAP_FREE( Stack );
    }
}

PDUMP_STACK FASTCALL AllocateStackFromPool( ULONG StackDepth, ULONG StringLength )
{
    PGLOBAL_SETTING Setting;
    PLIST_ENTRY ListEntry;
    PDUMP_STACK Stack;

    Setting = GET_GS( );
    Stack = NULL;
    do
    {
        /* See if lookahead list have empty item */
        if ( ListEntry = ExInterlockedRemoveHeadList( &Setting->FreeStackList, &Setting->FreeStackListLock ) )
        {
            Stack = CONTAINING_RECORD( ListEntry, DUMP_STACK, ListEntry );

            /* Initiate default */
            memset( &Stack->DummyStart, 0, ( TCHAR* )&Stack->DummyEnd - ( TCHAR* )&Stack->DummyStart );

            /* Initiate variable */
            Stack->EndChar[0] = DEFAULT_STATEMENT_CHAR;
            Stack->EndChar[1] = _T( '\r' );
            Stack->EndChar[2] = _T( '\n' );
            Stack->EndChar[3] = _T( '\0' );
            Stack->EndCharLength = 3;

            Stack->LogicEndOffset = INVALID_OP_OFFSET;
            Stack->LogicEndJmp = INVALID_OP_OFFSET;
            Stack->LogicEndOffsetEx = INVALID_OP_OFFSET;
            Stack->LogicEndJmpEx = INVALID_OP_OFFSET;
            Stack->LogicEndType = 0;
            Stack->LogicOpType = DS_IFLAGS_OT_MAX;
            Stack->IssetEndOffset = INVALID_OP_OFFSET;

            /* Re-init list */
            StackReinit( &Stack->ArgumentList );
            StackReinit( &Stack->Trinary );
            StackReinitT( &Stack->ScanList );
            StackReinitT( &Stack->OffsetMap );
            StackReinitT( &Stack->VarStringMap );
            StackReinitT( &Stack->ControlList );
            StackReinitT( &Stack->BreakList );
            StackReinitT( &Stack->ContinueList );
            StackReinitT( &Stack->PostOpTypeList );
            StackReinitT( &Stack->Logic );
            StackReinitT( &Stack->LogicPrefix );
            StackReinitU( &Stack->Common );
            StackReinitU( &Stack->Common1 );
            StackReinitU( &Stack->Common2 );
            StackReinitU( &Stack->Indent );
            StackReinitU( &Stack->Skip );
            StackReinitU( &Stack->SkipOnce );
            StackReinitU( &Stack->PreSkip );
            StackReinitU( &Stack->Output );
            StackReinitU( &Stack->Declare );
            StackReinitU( &Stack->ReturnX );
            StackReinitU( &Stack->Jmp );
            StackReinitU( &Stack->JmpX );
            StackReinitU( &Stack->JmpXX );
            StackReinitU( &Stack->JmpZnz );
            StackReinitU( &Stack->If );
            StackReinitU( &Stack->ForEach );
            StackReinitU( &Stack->SwitchCase );
            StackReinitU( &Stack->SwitchFree );
            StackReinitU( &Stack->QmAssign );
            StackReinitU( &Stack->New );
            StackReinitU( &Stack->InitCall );
            StackReinitU( &Stack->LogicList );
            StackReinitU( &Stack->LogicPostfix );
            StackReinitU( &Stack->LogicOpReverse );
            StackReinitS( &Stack->LogicExpress );
            StackReinitS( &Stack->Isset );
            StackReinitS( &Stack->ArgumentString );
            StackReinitS( &Stack->Buffer );
            StackReinitS( &Stack->Buffer1 );
            StackReinitS( &Stack->Buffer2 );
            StackReinitS( &Stack->LargeBuffer );

            /* Insert into in use list */
            ExInterlockedInsertTailList( &Setting->StackList, &Stack->ListEntry, &Setting->StackListLock );
        }
        else
        {
            /* Allocate new item */
            if ( !AllocateStack( StackDepth, StringLength, 1 ) )
                break;
        }
    } while ( Stack == NULL );

    return Stack;
}

void FASTCALL FreeStackToPool( PDUMP_STACK Stack )
{
    ULONG Flags;
    PGLOBAL_SETTING Setting;
    register ULONG Iter;
    register PLIST_ENTRY ListHead;
    register PLIST_ENTRY ListEntry;
    register PVARIABLE_ENTRY Var;
    ULONG Dummy;
    PCOMMON_STACK_S Buffer;
    PCOMMON_STACK_S Buffer1;

    LOCK_GS( );
    Setting = GET_GS( );
    Flags = Setting->Flags & GS_FLAGS_OBFUSCATE;
    Buffer = &Setting->Buffer;
    Buffer1 = &Setting->Buffer1;
    ListHead = &Setting->StackList;
    ListEntry = ListHead->Flink;
    EnterCriticalSection( &Setting->StackListLock );
    for ( ; ListEntry != ListHead; ListEntry = ListEntry->Flink )
    {
        if ( Stack == CONTAINING_RECORD( ListEntry, DUMP_STACK, ListEntry ) )
        {
            RemoveEntryList( &Stack->ListEntry );
            break;
        }
    }
    LeaveCriticalSection( &Setting->StackListLock );

    for ( Iter = 0; Iter < Stack->VariableTableCount; Iter++ )
    {
        ListHead = &Stack->ListArray[Iter];
        EnterCriticalSection( &Stack->ListLockArray[Iter] );
        while ( ( ListEntry = RemoveHeadList( ListHead ) ) )
        {
            Var = CONTAINING_RECORD( ListEntry, VARIABLE_ENTRY, ListEntry );
            /* Dump obfuscate name and its origin name */
            if ( Flags )
            {
                if ( 0 == memcmp( Var->Name, Setting->ObfuscatePrefix, Setting->ObfuscatePrefixLength ) )
                {
                    StackSetMaxS( Buffer, Var->NameLength );
                    Dummy = Base64DecodeX( StackBaseS( Buffer ), Var->Name + Setting->ObfuscatePrefixLength, Var->NameLength - Setting->ObfuscatePrefixLength );
                    StackSetMaxS( Buffer1, parse_string_len_url( StackBaseS( Buffer ), Dummy ) );
                    parse_string_url( StackBaseS( Buffer1 ), StackBaseS( Buffer ), Dummy );
                    ADD_DEBUG_LOG_LR( _T( "//[ %s ]->[ %s ]" ), Var->Name, StackBaseS( Buffer1 ) );
                }
            }

            if ( Var->Name )
                HEAP_FREE( Var->Name );

            if ( Var->Expr )
                HEAP_FREE( Var->Expr );

            HEAP_FREE( Var );
        }
        LeaveCriticalSection( &Stack->ListLockArray[Iter] );
    }

    /* Insert into free list */
    ExInterlockedInsertTailList( &GET_GS( )->FreeStackList, &Stack->ListEntry, &GET_GS( )->FreeStackListLock );
    UNLOCK_GS( );
}

__forceinline ULONG TypeToIndex( ULONG Type )
{
    register ULONG VarType;

    VarType = Type & VE_TYPE_VAR_MASK;
    if ( VarType == IS_VAR )
        return 0;
    else if ( VarType == IS_TMP_VAR )
        return 1;
    else if ( VarType == IS_CV )
        return 2;
    else if ( VarType == IS_CLASS )
        return 3;
    else if ( VarType == IS_FUNCTION )
        return 4;
    else
        return 5;
}

__forceinline ULONG IndexToType( ULONG Index )
{
    static ULONG IndexToTypeArray[] = {
        IS_VAR,
        IS_TMP_VAR,
        IS_CV,
        IS_CLASS,
        IS_FUNCTION,
        IS_UNUSED
    };

    if ( Index < SIZE_OF_ARRAY( IndexToTypeArray ) )
        return IndexToTypeArray[Index];
    else
        return IS_NULL;
}

POBFUSCATE_NAME_ENTRY InsertObfuscateName(
    LPCTSTR Name,
    ULONG NameLength,
    LPCTSTR ObfuscateName,
    ULONG ObfuscateNameLength
    )
{
    PGLOBAL_SETTING Setting;
    register POBFUSCATE_NAME_ENTRY Entry;
    POBFUSCATE_NAME_ENTRY EntryRet;

    do
    {
        Setting = GET_GS( );
        EntryRet = NULL;
        Entry = ( POBFUSCATE_NAME_ENTRY )HEAP_ALLOC( sizeof( OBFUSCATE_NAME_ENTRY ) );
        if ( Entry == NULL )
            break;

        Entry->ObfuscateName = NULL;
        Entry->Name = ( LPTSTR )HEAP_ALLOC( ( NameLength + 1 ) * sizeof( TCHAR ) );
        if ( Entry->Name == NULL )
            break;

        memcpy( Entry->Name, Name, NameLength );
        Entry->NameLength = NameLength;
        Entry->Name[NameLength] = _T( '\0' );

        Entry->ObfuscateName = ( LPTSTR )HEAP_ALLOC( ( ObfuscateNameLength + 1 ) * sizeof( TCHAR ) );
        if ( Entry->ObfuscateName == NULL )
            break;

        memcpy( Entry->ObfuscateName, ObfuscateName, ObfuscateNameLength );
        Entry->ObfuscateNameLength = ObfuscateNameLength;
        Entry->ObfuscateName[ObfuscateNameLength] = _T( '\0' );
        ExInterlockedInsertHeadList( &Setting->ObfuscateName, &Entry->ListEntry, &Setting->ObfuscateNameLock );
        EntryRet = Entry;
    } while ( 0 );

    if ( EntryRet == NULL )
    {
        if ( Entry )
        {
            if ( Entry->Name )
                HEAP_FREE( Entry->Name );

            if ( Entry->ObfuscateName )
                HEAP_FREE( Entry->ObfuscateName );

            HEAP_FREE( Entry );
        }
    }

    return EntryRet;
}

POBFUSCATE_NAME_ENTRY FindObfuscateName( LPCTSTR Name, ULONG Length )
{
    PGLOBAL_SETTING Setting;
    PLIST_ENTRY ListHead;
    register PLIST_ENTRY ListEntry;
    register POBFUSCATE_NAME_ENTRY Entry;
    POBFUSCATE_NAME_ENTRY EntryRet;

    Setting = GET_GS( );
    EntryRet = NULL;
    ListHead = &Setting->ObfuscateName;
    ListEntry = ListHead->Flink;
    EnterCriticalSection( &Setting->ObfuscateNameLock );
    for ( ; ListEntry != ListHead; ListEntry = ListEntry->Flink )
    {
        Entry = CONTAINING_RECORD( ListEntry, OBFUSCATE_NAME_ENTRY, ListEntry );
        if ( Entry->ObfuscateNameLength == Length && Entry->ObfuscateName[0] == Name[0] && 0 == memcmp( Entry->ObfuscateName, Name, Length ) )
        {
            EntryRet = Entry;
            break;
        }
    }
    LeaveCriticalSection( &Setting->ObfuscateNameLock );

    return EntryRet;
}

POBFUSCATE_NAME_ENTRY FindOriginName( LPCTSTR Name, ULONG Length )
{
    PGLOBAL_SETTING Setting;
    PLIST_ENTRY ListHead;
    register PLIST_ENTRY ListEntry;
    register POBFUSCATE_NAME_ENTRY Entry;
    POBFUSCATE_NAME_ENTRY EntryRet;

    Setting = GET_GS( );
    EntryRet = NULL;
    ListHead = &Setting->ObfuscateName;
    ListEntry = ListHead->Flink;
    EnterCriticalSection( &Setting->ObfuscateNameLock );
    for ( ; ListEntry != ListHead; ListEntry = ListEntry->Flink )
    {
        Entry = CONTAINING_RECORD( ListEntry, OBFUSCATE_NAME_ENTRY, ListEntry );
        if ( Entry->NameLength == Length && Entry->Name[0] == Name[0] && 0 == memcmp( Entry->Name, Name, Length ) )
        {
            EntryRet = Entry;
            break;
        }
    }
    LeaveCriticalSection( &Setting->ObfuscateNameLock );

    return EntryRet;
}

POBFUSCATE_NAME_ENTRY RemoveObfuscateName( LPCTSTR Name, ULONG Length )
{
    PGLOBAL_SETTING Setting;
    PLIST_ENTRY ListHead;
    register PLIST_ENTRY ListEntry;
    register POBFUSCATE_NAME_ENTRY Entry;
    POBFUSCATE_NAME_ENTRY EntryRet;

    Setting = GET_GS( );
    EntryRet = NULL;
    ListHead = &Setting->ObfuscateName;
    ListEntry = ListHead->Flink;
    EnterCriticalSection( &Setting->ObfuscateNameLock );
    for ( ; ListEntry != ListHead; ListEntry = ListEntry->Flink )
    {
        Entry = CONTAINING_RECORD( ListEntry, OBFUSCATE_NAME_ENTRY, ListEntry );
        if ( Entry->ObfuscateNameLength == Length && Entry->ObfuscateName[0] == Name[0] && 0 == memcmp( Entry->ObfuscateName, Name, Length ) )
        {
            RemoveEntryList( ListEntry );
            EntryRet = Entry;
            break;
        }
    }
    LeaveCriticalSection( &Setting->ObfuscateNameLock );

    return EntryRet;
}

void DumpObfuscateName( )
{
    PGLOBAL_SETTING Setting;
    register PLIST_ENTRY ListHead;
    register PLIST_ENTRY ListEntry;
    register POBFUSCATE_NAME_ENTRY Entry;
    PCOMMON_STACK_S Buffer;

    LOCK_GS( );
    Setting = GET_GS( );
    Buffer = &Setting->Buffer;
    ListHead = &Setting->ObfuscateName;
    ListEntry = ListHead->Flink;
    EnterCriticalSection( &Setting->ObfuscateNameLock );
    for ( ; ListEntry != ListHead; ListEntry = ListEntry->Flink )
    {
        Entry = CONTAINING_RECORD( ListEntry, OBFUSCATE_NAME_ENTRY, ListEntry );
        if ( 0 == memcmp( Entry->Name, Setting->ObfuscatePrefix, Setting->ObfuscatePrefixLength ) )
        {
            StackSetMaxS( Buffer, Entry->ObfuscateNameLength << 2 );
            parse_string_url( StackBaseS( Buffer ), Entry->ObfuscateName, Entry->ObfuscateNameLength );
            ADD_DEBUG_LOG_LR( _T( "//[ %s ]->[ %s ]" ), Entry->Name, StackBaseS( Buffer ) );
        }
    }
    LeaveCriticalSection( &Setting->ObfuscateNameLock );
    UNLOCK_GS( );
}

void CleanupObfuscateName( )
{
    PGLOBAL_SETTING Setting;
    register PLIST_ENTRY ListHead;
    register PLIST_ENTRY ListEntry;
    register POBFUSCATE_NAME_ENTRY Entry;
    PCOMMON_STACK_S Buffer;

    LOCK_GS( );
    Setting = GET_GS( );
    Buffer = &Setting->Buffer;
    ListHead = &Setting->ObfuscateName;
    while ( ( ListEntry = ExInterlockedRemoveHeadList( ListHead, &Setting->ObfuscateNameLock ) ) )
    {
        Entry = CONTAINING_RECORD( ListEntry, OBFUSCATE_NAME_ENTRY, ListEntry );
        HEAP_FREE( Entry->Name );
        HEAP_FREE( Entry->ObfuscateName );
        HEAP_FREE( Entry );
    }
    UNLOCK_GS( );
}

ULONG Utf8DecodeString( PCOMMON_STACK_S Buffer, const TCHAR *String, ULONG Length )
{
    ULONG RetCode;
    COMMON_STACK_S Utf8Buffer;

#if defined( _UNICODE ) || defined( UNICODE )
    UNREFERENCED_PARAMETER( Utf8Buffer );
    StackSetMaxS( Buffer, Length + 1 );
    RetCode = Utf8DecodeX( StackBaseS( Buffer ), String, Length );
    StackSetTopS( Buffer, RetCode );
#else
    StackSetMaxS( Buffer, Length + 1 );
    StackInitS( &Utf8Buffer, ( Length + 1 ) << 1 );
    Utf8DecodeX( StackBaseS( &Utf8Buffer ), String, Length );
    RetCode = WideCharToMultiByte( CP_ACP, 0, ( LPCWSTR )StackBaseS( &Utf8Buffer ), - 1, StackBaseS( Buffer ), StackMaxS( Buffer ), NULL, NULL ) - 1;
    StackUninitS( &Utf8Buffer );
    StackSetTopS( Buffer, RetCode );
#endif

    return RetCode;
}

/*
void TransExtendVariableEx( TCHAR *Out, const TCHAR *In, ULONG Length )
{
    register WCHAR Cur;
    register const TCHAR *Ptr;
    const TCHAR Prefix[] = _T( "{ \"" ) );
    const TCHAR Postfix[] = _T( "\" }" ) );

    if ( GET_GS_STATE( ) & GS_STATE_OBFUSCATE_VARIABLE )
    {
        memcpy( Out, GET_GS( )->ObfuscatePrefix, GET_GS( )->ObfuscatePrefixLength );
        Base64EncodeX( Out + GET_GS( )->ObfuscatePrefixLength, In, Length );
    }
    else
    {
        memcpy( Out, Prefix, sizeof( Prefix ) - 1 );
        Out += sizeof( Prefix ) - 1;

        for ( Ptr = In; Cur = *Ptr; Ptr++ )
        {
            *Out++ = _T( '\\' );
            *Out++ = _T( 'x' );
            *Out++ = GET_HEX_CHAR( )[( Cur >> 4 ) & 0xF];
            *Out++ = GET_HEX_CHAR( )[Cur & 0xF];
        }

        memcpy( Out, Postfix, sizeof( Postfix ) - 1 );
    }
}
*/

LONG ParseExtendVariableLength( const TCHAR *Name, ULONG NameLength )
{
    register WCHAR Cur;
    register const TCHAR *Ptr;
    register ULONG Length;
    register ULONG Flags;

    Length = GET_GS( )->ObfuscatePrefixLength + ( NameLength + 2 ) / 3 * 4 - NameLength;
    if ( GET_GS_STATE( ) & GS_STATE_OBFUSCATE )
        Flags = 1;
    else
        Flags = 0;

    Ptr = Name;
    Cur = *Ptr++;
    if ( Cur != _T( '_' ) )
    {
        if ( Cur < 0 )
        {
            if ( !( Flags & 2 ) )
            {
                if ( IsUtf8( ( const char * )Name, NameLength ) )
                    return 0;
                Flags |= 2;
            }
            if ( Flags & 1 )
                return Length;
        }
        else if ( Cur < _T( 'A' ) || ( _T( 'Z' ) < Cur && Cur < _T( 'a' ) ) || _T( 'z' ) < Cur )
        {
            /* Begin with number */
            return Length;
        }
    }

    for ( ; Cur = *Ptr; Ptr++ )
    {
        if ( Cur == _T( '_' ) || Cur == 0xFF )
            continue;

        if ( Cur < 0 )
        {
            if ( !( Flags & 2 ) )
            {
                if ( IsUtf8( ( const char * )Name, NameLength ) )
                    return 0;
                Flags |= 2;
            }
            if ( Flags & 1 )
                return Length;
        }
        else if ( Cur < _T( '0' ) || ( _T( '9' ) < Cur && Cur < _T( 'A' ) ) || ( _T( 'Z' ) < Cur && Cur < _T( 'a' ) ) || _T( 'z' ) < Cur )
        {
            return Length;
        }
    }

    return 0;
}

ULONG ParseExtendVariable( TCHAR *Buffer, const TCHAR *Name, ULONG NameLength )
{
    ULONG RetCode;
    POBFUSCATE_NAME_ENTRY Entry;
    ULONG NewLength;

    Entry = FindObfuscateName( Name, NameLength );
    if ( Entry == NULL )
    {
        memcpy( Buffer, GET_GS( )->ObfuscatePrefix, GET_GS( )->ObfuscatePrefixLength );
        NewLength = Base64EncodeX( Buffer + GET_GS( )->ObfuscatePrefixLength, Name, NameLength );
        InsertObfuscateName( Buffer, NewLength + GET_GS( )->ObfuscatePrefixLength, Name, NameLength );
        RetCode = NewLength + GET_GS( )->ObfuscatePrefixLength;
    }
    else
    {
        memcpy( Buffer, Entry->Name, Entry->NameLength );
        Buffer[Entry->NameLength] = _T( '\0' );
        RetCode = Entry->NameLength;
    }

    return RetCode;
}

ULONG ParseExtendVariableEx( PCOMMON_STACK_S Buffer, ULONG AddLength, const TCHAR *Name, ULONG NameLength )
{
    ULONG RetCode;
    ULONG Top;

    Top = StackCountS( Buffer );
    StackSetMaxS( Buffer, Top + AddLength + 1 );
    RetCode = ParseExtendVariable( StackBaseS( Buffer ) + Top, Name, NameLength );
    StackSetTopS( Buffer, Top + RetCode );

    return RetCode;
}

PVARIABLE_ENTRY FindVariableById( ULONG Type, ULONG Id )
{
    PDUMP_STACK Stack;
    ULONG Index;
    PLIST_ENTRY ListHead;
    register PLIST_ENTRY ListEntry;
    register PVARIABLE_ENTRY Entry;
    PVARIABLE_ENTRY EntryRet;

    Stack = GET_GS_STACK( );
    Index = TypeToIndex( Type );
    EntryRet = NULL;
    ListHead = &Stack->ListArray[Index];
    ListEntry = ListHead->Flink;
    EnterCriticalSection( &Stack->ListLockArray[Index] );
    for ( ; ListEntry != ListHead; ListEntry = ListEntry->Flink )
    {
        Entry = CONTAINING_RECORD( ListEntry, VARIABLE_ENTRY, ListEntry );
        if ( Entry->Id == Id )
        {
            EntryRet = Entry;
            break;
        }
    }
    LeaveCriticalSection( &Stack->ListLockArray[Index] );

    return EntryRet;
}

PVARIABLE_ENTRY RemoveVariableById( ULONG Type, ULONG Id )
{
    PDUMP_STACK Stack;
    ULONG Index;
    PLIST_ENTRY ListHead;
    register PLIST_ENTRY ListEntry;
    register PVARIABLE_ENTRY Entry;
    PVARIABLE_ENTRY EntryRet;

    Stack = GET_GS_STACK( );
    Index = TypeToIndex( Type );
    EntryRet = NULL;
    ListHead = &Stack->ListArray[Index];
    ListEntry = ListHead->Flink;
    EnterCriticalSection( &Stack->ListLockArray[Index] );
    for ( ; ListEntry != ListHead; ListEntry = ListEntry->Flink )
    {
        Entry = CONTAINING_RECORD( ListEntry, VARIABLE_ENTRY, ListEntry );
        if ( Entry->Id == Id )
        {
            RemoveEntryList( ListEntry );
            EntryRet = Entry;
            break;
        }
    }
    LeaveCriticalSection( &Stack->ListLockArray[Index] );

    return EntryRet;
}

void ClearVariableTable( ULONG Type )
{
    PDUMP_STACK Stack;
    ULONG Index;
    register PLIST_ENTRY ListHead;
    register PLIST_ENTRY ListEntry;
    register PVARIABLE_ENTRY Entry;

    Stack = GET_GS_STACK( );
    Index = TypeToIndex( Type );
    ListHead = &Stack->ListArray[Index];
    EnterCriticalSection( &Stack->ListLockArray[Index] );
    while ( ( ListEntry = RemoveHeadList( ListHead ) ) )
    {
        Entry = CONTAINING_RECORD( ListEntry, VARIABLE_ENTRY, ListEntry );
        if ( Entry->Name )
            HEAP_FREE( Entry->Name );

        if ( Entry->Expr )
            HEAP_FREE( Entry->Expr );

        HEAP_FREE( Entry );
    }
    LeaveCriticalSection( &Stack->ListLockArray[Index] );
}

void CleanupVariableTable( )
{
    PDUMP_STACK Stack;
    register ULONG Iter;
    register ULONG Count;
    register PLIST_ENTRY ListHead;
    register PLIST_ENTRY ListEntry;
    register PVARIABLE_ENTRY Entry;

    Stack = GET_GS_STACK( );
    Count = Stack->VariableTableCount;
    for ( Iter = 0; Iter < Count; Iter++ )
    {
        ListHead = &Stack->ListArray[Iter];
        EnterCriticalSection( &Stack->ListLockArray[Iter] );
        while ( ( ListEntry = RemoveHeadList( ListHead ) ) )
        {
            Entry = CONTAINING_RECORD( ListEntry, VARIABLE_ENTRY, ListEntry );
            if ( Entry->Name )
                HEAP_FREE( Entry->Name );

            if ( Entry->Expr )
                HEAP_FREE( Entry->Expr );

            HEAP_FREE( Entry );
        }
        LeaveCriticalSection( &Stack->ListLockArray[Iter] );
    }
}

PVARIABLE_ENTRY InsertVariableEx(
    ULONG Type,
    ULONG Id,
    ULONG Offset,
    LPCTSTR Name,
    LPCTSTR Expr,
    ULONG Flags
    )
{
    PDUMP_STACK Stack;
    ULONG Index;
    ULONG OrgLength;
    ULONG Length;
    ULONG MaxLength;
    ULONG ExtendLength;
    register PVARIABLE_ENTRY Entry;
    PVARIABLE_ENTRY EntryRet;
    TCHAR *Alloc;
    TCHAR Buffer[BUFFER_SIZE];

    do
    {
        EntryRet = NULL;
        Entry = ( PVARIABLE_ENTRY )HEAP_ALLOC( sizeof( VARIABLE_ENTRY ) );
        if ( Entry == NULL )
            break;

        Index = TypeToIndex( Type );
        if ( Name == NULL )
        {
            OrgLength = _sntprintf( Buffer, sizeof( Buffer ), _T( "%s_%d" ), GET_VAR_TYPE( Index ), Id );
            Name = Buffer;
            ExtendLength = 0;
            Length = OrgLength;
        }
        else
        {
            OrgLength = _tcslen( Name );
            if ( Flags & VE_FLAGS_OBFUSCATE )
                ExtendLength = 0;
            else
                ExtendLength = ParseExtendVariableLength( Name, OrgLength );
            Length = OrgLength + ExtendLength;
        }

        MaxLength = ROUND_STRING( Length ) * sizeof( TCHAR );
        Alloc = ( LPTSTR )HEAP_ALLOC( MaxLength );
        if ( Alloc == NULL )
            break;

        if ( ExtendLength )
        {
            Length = ParseExtendVariable( Alloc, Name, OrgLength );
            Entry->Flags |= VE_FLAGS_EXTEND;
        }
        else
        {
            memcpy( Alloc, Name, Length );
        }
        Alloc[Length] = _T( '\0' );
        Entry->Name = Alloc;
        Entry->NameLength = Length;
        Entry->MaxNameLength = MaxLength;

        if ( Expr == NULL )
        {
            Length = _sntprintf( Buffer, sizeof( Buffer ), _T( "$%s" ), Entry->Name );
            Expr = Buffer;
        }
        else
        {
            Length = _tcslen( Expr );
            Flags |= VE_FLAGS_UPDATED;
        }

        MaxLength = ROUND_STRING( Length ) * sizeof( TCHAR );
        Entry->Expr = ( LPTSTR )HEAP_ALLOC( MaxLength );
        if ( Entry->Expr == NULL )
            break;

        memcpy( Entry->Expr, Expr, Length );
        Entry->Expr[Length] = _T( '\0' );
        Entry->ExprLength = Length;
        Entry->MaxExprLength = MaxLength;

        Entry->Id = Id;
        Entry->Type = Type;
        Entry->Offset = Offset;
        Entry->Flags = Flags;
        if ( !( Flags & DS_IFLAGS_OT_MASK ) )
            Entry->Flags |= DS_IFLAGS_OT_MAX;

        Stack = GET_GS_STACK( );
        if ( Stack->State & DS_STATE_SILENCE )
            Entry->Flags |= VE_FLAGS_SILENCE;

        ExInterlockedInsertHeadList( &Stack->ListArray[Index],
            &Entry->ListEntry,
            &Stack->ListLockArray[Index]
            );
        EntryRet = Entry;
    } while ( 0 );

    if ( EntryRet == NULL )
    {
        if ( Entry )
        {
            if ( Entry->Name )
                HEAP_FREE( Entry->Name );

            if ( Entry->Expr )
                HEAP_FREE( Entry->Expr );

            HEAP_FREE( Entry );
        }
    }

    return EntryRet;
}

__forceinline PVARIABLE_ENTRY InsertVariable(
    ULONG Type,
    ULONG Id,
    LPCTSTR Name,
    LPCTSTR Expr,
    ULONG Flags
    )
{
    return InsertVariableEx( Type, Id, GET_GS_STACK( )->Offset, Name, Expr, Flags );
}

PVARIABLE_ENTRY FindInsertVariable(
    ULONG Type,
    ULONG Id
    )
{
    PDUMP_STACK Stack;
    ULONG Index;
    PLIST_ENTRY ListHead;
    register PLIST_ENTRY ListEntry;
    register PVARIABLE_ENTRY Entry;
    PVARIABLE_ENTRY EntryRet;

    Stack = GET_GS_STACK( );
    Index = TypeToIndex( Type );
    EntryRet = NULL;
    ListHead = &Stack->ListArray[Index];
    ListEntry = ListHead->Flink;
    EnterCriticalSection( &Stack->ListLockArray[Index] );
    for ( ; ListEntry != ListHead; ListEntry = ListEntry->Flink )
    {
        Entry = CONTAINING_RECORD( ListEntry, VARIABLE_ENTRY, ListEntry );
        if ( Entry->Id == Id )
        {
            EntryRet = Entry;
            break;
        }
    }
    LeaveCriticalSection( &Stack->ListLockArray[Index] );

    if ( EntryRet == NULL )
        EntryRet = InsertVariableEx( Type, Id, GET_GS_STACK( )->Offset, NULL, NULL, 0 );

    return EntryRet;
}

PVARIABLE_ENTRY FindInsertVariableEx(
    ULONG Type,
    ULONG Id,
    ULONG Flags
    )
{
    PDUMP_STACK Stack;
    ULONG Index;
    PLIST_ENTRY ListHead;
    register PLIST_ENTRY ListEntry;
    register PVARIABLE_ENTRY Entry;
    PVARIABLE_ENTRY EntryRet;

    Stack = GET_GS_STACK( );
    Index = TypeToIndex( Type );
    EntryRet = NULL;
    ListHead = &Stack->ListArray[Index];
    ListEntry = ListHead->Flink;
    EnterCriticalSection( &Stack->ListLockArray[Index] );
    for ( ; ListEntry != ListHead; ListEntry = ListEntry->Flink )
    {
        Entry = CONTAINING_RECORD( ListEntry, VARIABLE_ENTRY, ListEntry );
        if ( Entry->Id == Id )
        {
            EntryRet = Entry;
            break;
        }
    }
    LeaveCriticalSection( &Stack->ListLockArray[Index] );

    if ( EntryRet == NULL )
        EntryRet = InsertVariableEx( Type, Id, GET_GS_STACK( )->Offset, NULL, NULL, Flags );

    return EntryRet;
}

PVARIABLE_ENTRY UpdateVariable(
    ULONG Type,
    ULONG Id,
    LPCTSTR Expr
    )
{
    PDUMP_STACK Stack;
    ULONG Index;
    ULONG Length;
    ULONG MaxLength;
    ULONG Dummy;
    PLIST_ENTRY ListHead;
    register PLIST_ENTRY ListEntry;
    register PVARIABLE_ENTRY Entry;
    PVARIABLE_ENTRY EntryRet;
    TCHAR *Alloc;
    TCHAR Buffer[BUFFER_SIZE];

    ( Dummy );
    Stack = GET_GS_STACK( );
    Index = TypeToIndex( Type );
    EntryRet = NULL;
    ListHead = &Stack->ListArray[Index];
    ListEntry = ListHead->Flink;
    EnterCriticalSection( &Stack->ListLockArray[Index] );
    for ( ; ListEntry != ListHead; ListEntry = ListEntry->Flink )
    {
        Entry = CONTAINING_RECORD( ListEntry, VARIABLE_ENTRY, ListEntry );
        if ( Entry->Id == Id )
        {
            do
            {
                if ( Expr == NULL )
                {
                    Length = _sntprintf( Buffer, sizeof( Buffer ), _T( "$%s" ), Entry->Name );
                    Expr = Buffer;
                }
                else
                {
                    Length = _tcslen( Expr );
                }
                if ( Entry->MaxExprLength > Length )
                {
                    Alloc = Entry->Expr;
                }
                else
                {
                    MaxLength = ROUND_STRING( Length ) * sizeof( TCHAR );
                    Alloc = ( LPTSTR )HEAP_ALLOC( MaxLength );
                    if ( Alloc == NULL )
                        break;

                    HEAP_FREE( Entry->Expr );
                    Entry->MaxExprLength = MaxLength;
                }

                memcpy( Alloc, Expr, Length );
                Alloc[Length] = _T( '\0' );
                Entry->Expr = Alloc;
                Entry->ExprLength = Length;
                Entry->Flags |= VE_FLAGS_UPDATED;
            } while ( 0 );
            EntryRet = Entry;
            break;
        }
    }
    LeaveCriticalSection( &Stack->ListLockArray[Index] );

    if ( EntryRet == NULL )
        EntryRet = InsertVariableEx( Type, Id, GET_GS_STACK( )->Offset, NULL, Expr, 0 );

    return EntryRet;
}

PVARIABLE_ENTRY UpdateVariableEx(
    ULONG Type,
    ULONG Id,
    ULONG Offset,
    LPCTSTR Name,
    LPCTSTR Expr,
    ULONG Flags
    )
{
    PDUMP_STACK Stack;
    ULONG Index;
    ULONG Length;
    ULONG MaxLength;
    ULONG OrgLength;
    ULONG ExtendLength;
    PLIST_ENTRY ListHead;
    register PLIST_ENTRY ListEntry;
    register PVARIABLE_ENTRY Entry;
    PVARIABLE_ENTRY EntryRet;
    TCHAR *Alloc;
    TCHAR Buffer[BUFFER_SIZE];

    Stack = GET_GS_STACK( );
    Index = TypeToIndex( Type );
    EntryRet = NULL;
    ListHead = &Stack->ListArray[Index];
    ListEntry = ListHead->Flink;
    EnterCriticalSection( &Stack->ListLockArray[Index] );
    for ( ; ListEntry != ListHead; ListEntry = ListEntry->Flink )
    {
        Entry = CONTAINING_RECORD( ListEntry, VARIABLE_ENTRY, ListEntry );
        if ( Entry->Id == Id )
        {
            do
            {
                if ( !( Flags & VE_FLAGS_FLAGS ) )
                {
                    if ( Name )
                    {
                        OrgLength = _tcslen( Name );
                        if ( Entry->Flags & VE_FLAGS_OBFUSCATE )
                            ExtendLength = 0;
                        else
                            ExtendLength = ParseExtendVariableLength( Name, OrgLength );
                        Length = OrgLength + ExtendLength;
                        if ( Entry->MaxNameLength > Length )
                        {
                            Alloc = Entry->Name;
                        }
                        else
                        {
                            MaxLength = ROUND_STRING( Length ) * sizeof( TCHAR );
                            Alloc = ( LPTSTR )HEAP_ALLOC( MaxLength );
                            if ( Alloc == NULL )
                                break;

                            HEAP_FREE( Entry->Name );
                            Entry->MaxNameLength = MaxLength;
                        }

                        if ( ExtendLength )
                        {
                            Length = ParseExtendVariable( Alloc, Name, OrgLength );
                            Entry->Flags |= VE_FLAGS_EXTEND;
                        }
                        else
                        {
                            memcpy( Alloc, Name, Length );
                        }
                        Alloc[Length] = _T( '\0' );
                        Entry->Name = Alloc;
                        Entry->NameLength = Length;
                    }

                    if ( Expr == NULL )
                    {
                        Length = _sntprintf( Buffer, sizeof( Buffer ), _T( "$%s" ), Entry->Name );
                        Expr = Buffer;
                    }
                    else
                    {
                        Length = _tcslen( Expr );
                    }
                    if ( Entry->MaxExprLength > Length )
                    {
                        Alloc = Entry->Expr;
                    }
                    else
                    {
                        MaxLength = ROUND_STRING( Length ) * sizeof( TCHAR );
                        Alloc = ( LPTSTR )HEAP_ALLOC( MaxLength );
                        if ( Alloc == NULL )
                            break;

                        if ( Entry->Expr )
                            HEAP_FREE( Entry->Expr );
                        Entry->MaxExprLength = MaxLength;
                    }

                    memcpy( Alloc, Expr, Length );
                    Alloc[Length] = _T( '\0' );
                    Entry->Expr = Alloc;
                    Entry->ExprLength = Length;
                }

                Entry->Offset = Offset;
                Entry->Flags |= VE_FLAGS_UPDATED;
                Entry->Flags &= ~VE_FLAGS_MASK;
                Entry->Flags |= ( Flags & VE_FLAGS_MASK );
                if ( !( Flags & DS_IFLAGS_OT_MASK ) )
                    Entry->Flags |= DS_IFLAGS_OT_MAX;

                if ( !( Flags & VE_FLAGS_SKIP_SILENCE ) && ( Stack->State & DS_STATE_SILENCE ) )
                    Entry->Flags |= VE_FLAGS_SILENCE;
            } while ( 0 );
            EntryRet = Entry;
            break;
        }
    }
    LeaveCriticalSection( &Stack->ListLockArray[Index] );

    if ( EntryRet == NULL )
        EntryRet = InsertVariableEx( Type, Id, Offset, Name, Expr, Flags );

    return EntryRet;
}

int parse_string_len( const TCHAR *String, ULONG Length )
{
    register TCHAR Cur;
    register const TCHAR *Start;
    register const TCHAR *End;
    register int Count;

    Start = String;
    End = String + Length;
    Count = 0;
    while ( Start < End )
    {
        Cur = *Start++;
        if ( Cur == *GET_GS( )->FileNamePtr && Start + GET_GS( )->FileNameLength - 1 <= End && 0 == _tcsnicmp( Start, GET_GS( )->FileNamePtr + 1, GET_GS( )->FileNameLength - 1 ) )
        {
            if ( Start == String + 1 )
            {
                if ( Length == GET_GS( )->FileNameLength )
                {
                    /* __FILE__ */
                    Count |= FLAGS_SPECIAL_LEFT;
                    Count |= FLAGS_SPECIAL_RIGHT;
                    Count += DEFAULT_FILE_STRING_LENGTH;
                }
                else
                {
                    /* __FILE__."x" */
                    Count |= FLAGS_SPECIAL_LEFT;
                    Count += DEFAULT_FILE_STRING_LENGTH + 2;
                }
            }
            else
            {
                if ( Start + GET_GS( )->FileNameLength - 1 == End )
                {
                    /* "x".__FILE__ */
                    Count |= FLAGS_SPECIAL_RIGHT;
                    Count += DEFAULT_FILE_STRING_LENGTH;
                }
                else
                {
                    /* "x".__FILE__."x" */
                    Count += DEFAULT_FILE_STRING_LENGTH + 4;
                }
            }
            Start += GET_GS( )->FileNameLength - 1;
        }
        else if ( Cur == _T( '\\' ) )
            Count += 2;
        else if ( Cur == _T( '\t' ) )
            Count += 2;
        else if ( Cur == _T( '\n' ) )
            Count += 2;
        else if ( Cur == _T( '\r' ) )
            Count += 2;
        else if ( Cur == _T( '$' ) )
            Count += 2;
        else if ( Cur == _T( '\"' ) )
            Count += 2;
        else if ( ( USHORT )Cur < 0x20 || Length == 1 && ( Cur < 0 || Cur > 0x80 ) )
            Count += 4;
        else
            Count++;
    }

    return Count;
}

int parse_string( TCHAR *Buffer, const TCHAR *String, ULONG Length )
{
    register TCHAR Cur;
    register const TCHAR *Start;
    register const TCHAR *End;
    register TCHAR *Out;
    ULONG BigCount;
    ULONG OutLength;

    Start = String;
    End = String + Length;
    Out = Buffer;
    BigCount = 0;
    while ( Start < End )
    {
        Cur = *Start++;
        if ( Cur == *GET_GS( )->FileNamePtr && Start + GET_GS( )->FileNameLength - 1 <= End && 0 == _tcsnicmp( Start, GET_GS( )->FileNamePtr + 1, GET_GS( )->FileNameLength - 1 ) )
        {
            if ( Start == String + 1 )
            {
                if ( Length == GET_GS( )->FileNameLength )
                {
                    /* __FILE__ */
                    _tcsncpy( Out, DEFAULT_FILE_STRING, DEFAULT_FILE_STRING_LENGTH );
                    Out += DEFAULT_FILE_STRING_LENGTH;
                }
                else
                {
                    /* __FILE__."x" */
                    _tcsncpy( Out, DEFAULT_FILE_STRING, DEFAULT_FILE_STRING_LENGTH );
                    Out += DEFAULT_FILE_STRING_LENGTH;
                    *Out++ = _T( '.' );
                    *Out++ = _T( '\"' );
                }
            }
            else
            {
                if ( Start + GET_GS( )->FileNameLength - 1 == End )
                {
                    /* "x".__FILE__ */
                    *Out++ = _T( '\"' );
                    *Out++ = _T( '.' );
                    _tcsncpy( Out, DEFAULT_FILE_STRING, DEFAULT_FILE_STRING_LENGTH );
                    Out += DEFAULT_FILE_STRING_LENGTH;
                }
                else
                {
                    /* "x".__FILE__."x" */
                    *Out++ = _T( '\"' );
                    *Out++ = _T( '.' );
                    _tcsncpy( Out, DEFAULT_FILE_STRING, DEFAULT_FILE_STRING_LENGTH );
                    Out += DEFAULT_FILE_STRING_LENGTH;
                    *Out++ = _T( '.' );
                    *Out++ = _T( '\"' );
                }
            }
            Start += GET_GS( )->FileNameLength - 1;
        }
        else if ( Cur == _T( '\\' ) || Cur == _T( '\"' ) )
        {
            *Out++ = _T( '\\' );
            *Out++ = ( TCHAR )Cur;
        }
        else if ( Cur == _T( '\t' ) )
        {
            *Out++ = _T( '\\' );
            *Out++ = _T( 't' );
        }
        else if ( Cur == _T( '\n' ) )
        {
            *Out++ = _T( '\\' );
            *Out++ = _T( 'n' );
        }
        else if ( Cur == _T( '\r' ) )
        {
            *Out++ = _T( '\\' );
            *Out++ = _T( 'r' );
        }
        else if ( Cur == _T( '$' ) )
        {
            *Out++ = _T( '\\' );
            *Out++ = _T( '$' );
        }
        else if ( ( USHORT )Cur < 0x20 || Length == 1 && ( Cur < 0 || Cur > 0x80 ) )
        {
            *Out++ = _T( '\\' );
            *Out++ = _T( 'x' );
            *Out++ = GET_HEX_CHAR( ( Cur >> 4 ) & 0xF );
            *Out++ = GET_HEX_CHAR( Cur & 0xF );
        }
        else
        {
            if ( ( UCHAR )Cur > 0x80 )
                BigCount++;
            *Out++ = ( TCHAR )Cur;
        }
    }

    if ( BigCount )
    {
        if ( IsUtf8( String, Length ) )
        {
#if 0
            OutLength = Utf8DecodeString( &GET_GS( )->Buffer, String, Length );
            _tcsncpy( Buffer, StackBaseS( &GET_GS( )->Buffer ), OutLength );
            Out = Buffer + OutLength;
#else
            UNREFERENCED_PARAMETER( OutLength );
            if ( GET_GS_FLAGS( ) & GS_FLAGS_BUG )
                dump_string_ex( GET_GS_STACK( ), _T( "//[WARNING]Utf8\r\n" ) );
#endif
        }
    }
    *Out = _T( '\0' );

    return Out - Buffer;
}

int parse_string_len_url( const TCHAR *String, ULONG Length )
{
    register WCHAR Cur;
    register const TCHAR *Start;
    register const TCHAR *End;
    register int Count;

    Start = String;
    End = Start + Length;
    Count = 0;
    while ( Start < End )
    {
        Cur = *Start++;
        if ( Cur == *GET_GS( )->FileNamePtr && Start + GET_GS( )->FileNameLength - 1 <= End && 0 == _tcsnicmp( Start, GET_GS( )->FileNamePtr + 1, GET_GS( )->FileNameLength - 1 ) )
        {
            Start += GET_GS( )->FileNameLength - 1;
            Count += DEFAULT_FILE_STRING_LENGTH;
        }
        else if ( Cur == _T( ' ' ) || Cur == _T( '-' ) || Cur == _T( '.' ) || Cur == _T( '_' ) )
            Count++;
        else if ( Cur < _T( '0' ) || _T( '9' ) < Cur && Cur < _T( 'A' ) || _T( 'Z' ) < Cur && Cur < _T( 'a' ) || 0x7F < Cur )
            Count += 3;
        else
            Count++;
    }

    return Count;
}

int parse_string_url( TCHAR *Buffer, const TCHAR *String, ULONG Length )
{
    register WCHAR Cur;
    register const TCHAR *Start;
    register const TCHAR *End;
    register TCHAR *Out;

    Start = String;
    End = Start + Length;
    Out = Buffer;
    while ( Start < End )
    {
        Cur = *Start++;
        if ( Cur == *GET_GS( )->FileNamePtr && Start + GET_GS( )->FileNameLength - 1 <= End && 0 == _tcsnicmp( Start, GET_GS( )->FileNamePtr + 1, GET_GS( )->FileNameLength - 1 ) )
        {
            Start += GET_GS( )->FileNameLength - 1;
            _tcsncpy( Out, DEFAULT_FILE_STRING, DEFAULT_FILE_STRING_LENGTH );
            Out += DEFAULT_FILE_STRING_LENGTH;
        }
        else if ( Cur == _T( ' ' ) )
        {
            *Out++ = _T( '+' );
        }
        else if ( Cur == _T( '-' ) || Cur == _T( '.' ) || Cur == _T( '_' ) )
        {
            *Out++ = ( TCHAR )Cur;
        }
        else if ( Cur < _T( '0' ) || _T( '9' ) < Cur && Cur < _T( 'A' ) || _T( 'Z' ) < Cur && Cur < _T( 'a' ) || 0x7F < Cur )
        {
            *Out++ = _T( '%' );
            *Out++ = GET_HEX_CHAR( ( Cur >> 4 ) & 0xF );
            *Out++ = GET_HEX_CHAR( Cur & 0xF );
        }
        else
        {
            *Out++ = ( TCHAR )Cur;
        }
    }
    *Out = _T( '\0' );

    return Out - Buffer;
}

ULONG make_printable_array( zval *Expr, PCOMMON_STACK_S StringBuffer )
{
    ULONG RetCode;
    ULONG Indent;
    register Bucket *Bt;
    zval *Property;
    PDUMP_STACK Stack;
    TCHAR Buffer[256];

    Bt = Expr->value.ht->pListHead;
    if ( Bt )
    {
        Stack = GET_GS_STACK( );
        PUSH_INC_INDENT( Stack );
        GET_INDENT( Stack, &Indent );
        StackPushS( StringBuffer, _T( "array\r\n" ), 7 );
        StackPushNS( StringBuffer, GET_GS( )->IndentChar[0], Indent - GET_GS_INDENT( ) );
        StackPushS( StringBuffer, _T( "(\r\n" ), 3 );
        while ( Bt )
        {
            Property = ( zval* ) ( Bt->pDataPtr ? Bt->pDataPtr : Bt->pData );
            StackPushNS( StringBuffer, GET_GS( )->IndentChar[0], Indent );
            if ( Property != Expr )
            {
                if ( Bt->nKeyLength )
                {
                    StackPushS( StringBuffer, _T( "\"" ), 1 );
                    StackPushS( StringBuffer, Bt->arKey, Bt->nKeyLength - 1 );
                    StackPushS( StringBuffer, _T( "\" => " ), 5 );
                }
                else
                {
                    RetCode = _stprintf( Buffer, _T( "%d => " ), Bt->h );
                    StackPushS( StringBuffer, Buffer, RetCode );
                }
                make_printable_zval_url( Property, StringBuffer );
                StackPushS( StringBuffer, _T( ",\r\n" ), 3 );
            }
            else
            {
                StackPushS( StringBuffer, _T( "\"" ), 1 );
                StackPushS( StringBuffer, Bt->arKey, Bt->nKeyLength - 1 );
                StackPushS( StringBuffer, _T( "\",\r\n" ), 4 );
            }
            Bt = Bt->pListNext;
        }
        StackPopNS( StringBuffer, NULL, 2 );
        if ( StackTopS( StringBuffer, Buffer ) && Buffer[0] == _T( ',' ) )
        {
            StackPopS( StringBuffer, NULL );
            StackPushS( StringBuffer, _T( "\r\n" ), 2 );
        }

        Indent -= GET_GS_INDENT( );
        POP_INDENT( Stack );
        StackPushNS( StringBuffer, GET_GS( )->IndentChar[0], Indent );
        RetCode = StackPushS( StringBuffer, _T( ")" ), 1 );
    }
    else
    {
        RetCode = StackPushS( StringBuffer, _T( "array( )" ), 8 );
    }

    return RetCode;
}

ULONG make_printable_object( zval *Expr, PCOMMON_STACK_S StringBuffer )
{
    ULONG RetCode;

    RetCode = StackPushS( StringBuffer, _T( "Object" ), 6 );

    return RetCode;
}

ULONG make_printable_resource( zval *Expr, PCOMMON_STACK_S StringBuffer )
{
    ULONG RetCode;
    TCHAR Buffer[256];

    RetCode = StackPushS( StringBuffer, Buffer, _stprintf( Buffer, _T( "Resource id #%ld" ), Expr->value.lval ) );

    return RetCode;
}

ULONG make_printable_other( zval *Expr, PCOMMON_STACK_S StringBuffer )
{
    ULONG RetCode;
    TCHAR Buffer[256];

    RetCode = StackPushS( StringBuffer, Buffer, _stprintf( Buffer, _T( "?id #%ld" ), Expr->value.lval ) );

    return RetCode;
}

ULONG make_printable_zval( zval *Expr, PCOMMON_STACK_S StringBuffer )
{
    ULONG RetCode;
    TCHAR Buffer[BUFFER_SIZE];

    RetCode = 0;
    switch ( Expr->type )
    {
    case IS_NULL :
        RetCode = StackPushS( StringBuffer, _T( "NULL" ), 4 );
        break;
    case IS_LONG :
        RetCode = _stprintf( Buffer, _T( "%ld" ), Expr->value.lval );
        StackPushS( StringBuffer, Buffer, RetCode );
        break;
    case IS_DOUBLE :
        RetCode = _stprintf( Buffer, _T( "%g" ), Expr->value.dval );
        StackPushS( StringBuffer, Buffer, RetCode );
        break;
    case IS_STRING :
        StackPushS( StringBuffer, _T( "\"" ), 1 );
        StackPushS( StringBuffer, Expr->value.str.val, Expr->value.str.len );
        RetCode = StackPushS( StringBuffer, _T( "\"" ), 1 );
        break;
    case IS_CONSTANT :
        StackPushS( StringBuffer, Expr->value.str.val, Expr->value.str.len );
        break;
    case IS_ARRAY :
        RetCode = make_printable_array( Expr, StringBuffer );
        break;
    case IS_OBJECT :
        RetCode = make_printable_object( Expr, StringBuffer );
        break;
    case IS_BOOL :
        if ( Expr->value.lval )
            RetCode = StackPushS( StringBuffer, _T( "TRUE" ), 4 );
        else
            RetCode = StackPushS( StringBuffer, _T( "FALSE" ), 5 );
        break;
    case IS_RESOURCE :
        RetCode = make_printable_resource( Expr, StringBuffer );
        break;
    case IS_CONSTANT_ARRAY :
        RetCode = make_printable_array( Expr, StringBuffer );
        break;
    default :
        RetCode = make_printable_other( Expr, StringBuffer );
        break;
    }

    return RetCode;
}

ULONG make_printable_zval_ex( zval *Expr, PCOMMON_STACK_S StringBuffer, ULONG Enclose )
{
    ULONG RetCode;
    TCHAR Buffer[BUFFER_SIZE];

    RetCode = 0;
    switch ( Expr->type )
    {
    case IS_NULL :
        RetCode = StackPushS( StringBuffer, _T( "NULL" ), 4 );
        break;
    case IS_LONG :
        RetCode = _stprintf( Buffer, _T( "%ld" ), Expr->value.lval );
        StackPushS( StringBuffer, Buffer, RetCode );
        break;
    case IS_DOUBLE :
        RetCode = _stprintf( Buffer, _T( "%g" ), Expr->value.dval );
        StackPushS( StringBuffer, Buffer, RetCode );
        break;
    case IS_STRING :
        if ( Enclose )
        {
            Buffer[0] = ( TCHAR )Enclose;
            StackPushS( StringBuffer, Buffer, 1 );
            StackPushS( StringBuffer, Expr->value.str.val, Expr->value.str.len );
            RetCode = StackPushS( StringBuffer, Buffer, 1 );
        }
        else
        {
            RetCode = StackPushS( StringBuffer, Expr->value.str.val, Expr->value.str.len );
        }
        break;
    case IS_CONSTANT :
        StackPushS( StringBuffer, Expr->value.str.val, Expr->value.str.len );
        break;
    case IS_ARRAY :
        RetCode = make_printable_array( Expr, StringBuffer );
        break;
    case IS_OBJECT :
        RetCode = make_printable_object( Expr, StringBuffer );
        break;
    case IS_BOOL :
        if ( Expr->value.lval )
            RetCode = StackPushS( StringBuffer, _T( "TRUE" ), 4 );
        else
            RetCode = StackPushS( StringBuffer, _T( "FALSE" ), 5 );
        break;
    case IS_RESOURCE :
        RetCode = make_printable_resource( Expr, StringBuffer );
        break;
    case IS_CONSTANT_ARRAY :
        RetCode = make_printable_array( Expr, StringBuffer );
        break;
    default :
        RetCode = make_printable_other( Expr, StringBuffer );
        break;
    }

    return RetCode;
}

ULONG make_printable_zval_url( zval *Expr, PCOMMON_STACK_S StringBuffer )
{
    ULONG RetCode;
    ULONG Flags;
    register ULONG Top;
    register LONG Length;
    TCHAR Buffer[BUFFER_SIZE];

    RetCode = 0;
    switch ( Expr->type )
    {
    case IS_NULL :
        RetCode = StackPushS( StringBuffer, _T( "NULL" ), 4 );
        break;
    case IS_LONG :
        RetCode = _stprintf( Buffer, _T( "%ld" ), Expr->value.lval );
        StackPushS( StringBuffer, Buffer, RetCode );
        break;
    case IS_DOUBLE :
        RetCode = _stprintf( Buffer, _T( "%g" ), Expr->value.dval );
        StackPushS( StringBuffer, Buffer, RetCode );
        break;
    case IS_STRING :
        /* Parse the string for length */
        Length = parse_string_len( Expr->value.str.val, Expr->value.str.len );
        Flags = Length & FLAGS_SPECIAL_MASK;
        Length &= ~FLAGS_SPECIAL_MASK;
        if ( !( Flags & FLAGS_SPECIAL_LEFT ) )
            StackPushS( StringBuffer, _T( "\"" ), 1 );
        Top = StackCountS( StringBuffer );
        StackSetMaxS( StringBuffer, ROUND_STRING( Top + Length ) );
        Length = parse_string( StackBaseS( StringBuffer ) + Top, Expr->value.str.val, Expr->value.str.len );
        RetCode = StackSetTopS( StringBuffer, Top + Length );
        if ( !( Flags & FLAGS_SPECIAL_RIGHT ) )
            RetCode = StackPushS( StringBuffer, _T( "\"" ), 1 );
        break;
    case IS_CONSTANT :
        StackPushS( StringBuffer, Expr->value.str.val, Expr->value.str.len );
        break;
    case IS_ARRAY :
        RetCode = make_printable_array( Expr, StringBuffer );
        break;
    case IS_OBJECT :
        RetCode = make_printable_object( Expr, StringBuffer );
        break;
    case IS_BOOL :
        if ( Expr->value.lval )
            RetCode = StackPushS( StringBuffer, _T( "TRUE" ), 4 );
        else
            RetCode = StackPushS( StringBuffer, _T( "FALSE" ), 5 );
        break;
    case IS_RESOURCE :
        RetCode = make_printable_resource( Expr, StringBuffer );
        break;
    case IS_CONSTANT_ARRAY :
        RetCode = make_printable_array( Expr, StringBuffer );
        break;
    default :
        RetCode = make_printable_other( Expr, StringBuffer );
        break;
    }

    return RetCode;
}

ULONG make_printable_zval_url_ex( zval *Expr, PCOMMON_STACK_S StringBuffer, ULONG Enclose )
{
    ULONG RetCode;
    ULONG Flags;
    register ULONG Top;
    register LONG Length;
    TCHAR Buffer[BUFFER_SIZE];

    RetCode = 0;
    switch ( Expr->type )
    {
    case IS_NULL :
        RetCode = StackPushS( StringBuffer, _T( "NULL" ), 4 );
        break;
    case IS_LONG :
        RetCode = _stprintf( Buffer, _T( "%ld" ), Expr->value.lval );
        StackPushS( StringBuffer, Buffer, RetCode );
        break;
    case IS_DOUBLE :
        RetCode = _stprintf( Buffer, _T( "%g" ), Expr->value.dval );
        StackPushS( StringBuffer, Buffer, RetCode );
        break;
    case IS_STRING :
        /* Parse the string for length */
        Length = parse_string_len( Expr->value.str.val, Expr->value.str.len );
        Flags = Length & FLAGS_SPECIAL_MASK;
        Length &= ~FLAGS_SPECIAL_MASK;
        if ( Enclose )
        {
            if ( !( Flags & FLAGS_SPECIAL_LEFT ) )
                StackPushS( StringBuffer, ( TCHAR* )&Enclose, 1 );
            Top = StackCountS( StringBuffer );
            StackSetMaxS( StringBuffer, ROUND_STRING( Top + Length ) );
            Length = parse_string( StackBaseS( StringBuffer ) + Top, Expr->value.str.val, Expr->value.str.len );
            RetCode = StackSetTopS( StringBuffer, Top + Length );
            if ( !( Flags & FLAGS_SPECIAL_RIGHT ) )
                RetCode = StackPushS( StringBuffer, ( TCHAR* )&Enclose, 1 );
        }
        else
        {
            Top = StackCountS( StringBuffer );
            StackSetMaxS( StringBuffer, ROUND_STRING( Top + Length ) );
            Length = parse_string( StackBaseS( StringBuffer ) + Top, Expr->value.str.val, Expr->value.str.len );
            RetCode = StackSetTopS( StringBuffer, Top + Length );
        }
        break;
    case IS_CONSTANT :
        StackPushS( StringBuffer, Expr->value.str.val, Expr->value.str.len );
        break;
    case IS_ARRAY :
        RetCode = make_printable_array( Expr, StringBuffer );
        break;
    case IS_OBJECT :
        RetCode = make_printable_object( Expr, StringBuffer );
        break;
    case IS_BOOL :
        if ( Expr->value.lval )
            RetCode = StackPushS( StringBuffer, _T( "TRUE" ), 4 );
        else
            RetCode = StackPushS( StringBuffer, _T( "FALSE" ), 5 );
        break;
    case IS_RESOURCE :
        RetCode = make_printable_resource( Expr, StringBuffer );
        break;
    case IS_CONSTANT_ARRAY :
        RetCode = make_printable_array( Expr, StringBuffer );
        break;
    default :
        RetCode = make_printable_other( Expr, StringBuffer );
        break;
    }

    return RetCode;
}

__forceinline void dump_zval_null( zvalue_value *Value )
{
    ADD_DEBUG_LOG( _T( "NULL" ) );
}

__forceinline void dump_zval_long( zvalue_value *Value )
{
    ADD_DEBUG_LOG( _T( "%ld" ), Value->lval );
}

__forceinline void dump_zval_double( zvalue_value *Value )
{
    ADD_DEBUG_LOG( _T( "%g" ), Value->dval );
}

__forceinline void dump_zval_string( zvalue_value *Value )
{
    TCHAR *NewString;
    int StringLength;

    NewString = php_url_encode( Value->str.val, Value->str.len, &StringLength );
    ADD_LOG( _T( "\"" ) );
    ADD_LOG( NewString );
    ADD_LOG( _T( "\"" ) );
    efree( NewString );
}

__forceinline void dump_zval_array( zvalue_value *Value )
{
    PCOMMON_STACK_S StringBuffer;
    const TCHAR *String;

    LOCK_GS( );
    StringBuffer = &GET_GS( )->Buffer;
    make_printable_zval_url( CONTAINING_RECORD( Value, zval, value ), StringBuffer );
    StackPopAllS( StringBuffer, &String );
    ADD_LOGA( String );
    UNLOCK_GS( );
}

__forceinline void dump_zval_object( zvalue_value *Value )
{
    ADD_LOG( _T( "Object" ) );
}

__forceinline void dump_zval_bool( zvalue_value *Value )
{
    ADD_LOGA( Value->lval ? _T( "TRUE" ) : _T( "FALSE" ) );
}

__forceinline void dump_zval_resource( zvalue_value *Value )
{
    ADD_DEBUG_LOG( _T( "Resource id #%ld" ), Value->lval );
}

__forceinline void dump_zval_constant( zvalue_value *Value )
{
    dump_zval_string( Value );
}

__forceinline void dump_zval_constant_array( zvalue_value *Value )
{
    dump_zval_array( Value );
}

void dump_zval( zval *Val )
{
    switch ( Val->type )
    {
    case IS_NULL :
        dump_zval_null( &Val->value );
        break;
    case IS_LONG :
        dump_zval_long( &Val->value );
        break;
    case IS_DOUBLE :
        dump_zval_double( &Val->value );
        break;
    case IS_STRING :
        dump_zval_string( &Val->value );
        break;
    case IS_ARRAY :
        dump_zval_array( &Val->value );
        break;
    case IS_OBJECT :
        dump_zval_object( &Val->value );
        break;
    case IS_BOOL :
        dump_zval_bool( &Val->value );
        break;
    case IS_RESOURCE :
        dump_zval_resource( &Val->value );
        break;
    case IS_CONSTANT :
        dump_zval_constant( &Val->value );
        break;
    case IS_CONSTANT_ARRAY :
        dump_zval_constant_array( &Val->value );
        break;
    }
}

ULONG dump_znode( PDUMP_STACK Stack, ULONG Flags, ULONG *Step, znode *Node )
{
    PVARIABLE_ENTRY Var;

    if ( Node->op_type != IS_UNUSED )
    {
        if ( *Step )
            ADD_DEBUG_LOG( _T( " - " ) );
        *Step = 1;
    }

    switch ( Node->op_type )
    {
    case IS_CONST : /* 1 */
        if ( Flags & DS_IFLAGS_IS_CLASS && Flags & DS_IFLAGS_IS_RESULT )
        {
            Var = FindVariableById( Node->op_type, NODE_VAR( Node ) );
            if ( Var )
                ADD_DEBUG_LOG( _T( "class %s" ), Var->Name );
        }
        else
        {
            dump_zval( &Node->u.constant );
        }
        break;

    case IS_TMP_VAR : /* 2 */
    case IS_VAR : /* 4 */
    case IS_CV : /* 16 */
        Var = FindVariableById( Node->op_type, NODE_VAR( Node ) );
        if ( Var )
            ADD_DEBUG_LOG( _T( "$%s" ), Var->Name );
        else
            ADD_DEBUG_LOG( _T( "$%s_%d" ), GET_VAR_TYPE( TypeToIndex( Node->op_type ) ), NODE_VAR( Node ) );
        break;

    case IS_UNUSED :
        if ( Flags & DS_IFLAGS_IS_FUNCTION )
        {
            if ( Flags & DS_IFLAGS_OP_MASK )
            {
                Var = FindVariableById( IS_FUNCTION, NODE_VAR( Node ) );
                if ( Var )
                    ADD_DEBUG_LOG( _T( "=%s( ... )" ), Var->Name );
            }
        }
        else if ( Flags & DS_IFLAGS_IS_OPLINE1 || Flags & DS_IFLAGS_IS_OPLINE2 )
            ADD_DEBUG_LOG( _T( "->%d" ), NODE_JMP( Node, Stack->Head ) );
        else if ( Flags & DS_IFLAGS_IS_SPECIAL )
            ADD_DEBUG_LOG( _T( "->%d" ), NODE_JMPZNZ( Node, Stack->Head ) );
        else if ( Flags & DS_IFLAGS_IS_VAR )
            ADD_DEBUG_LOG( _T( "[%d]" ), NODE_VAR( Node ) );
        else
            return FALSE;
        break;
    default :
        ADD_DEBUG_LOG( _T( "Type[ %d ] V-T[ %d - %d ]" ), Node->op_type, Node->u.EA.var, Node->u.EA.type );
        return FALSE;
    }

    return TRUE;
}

ULONG GetArrayIndent( LPCTSTR String, ULONG Length )
{
    ULONG RetCode;
    LPCTSTR Start;
    LPCTSTR End;
    LPCTSTR Tail;

    RetCode = 0;
    Start = String;
    Tail = String + Length;
    End = Tail - 1;

    while ( Start < End )
    {
        if ( *End == _T( '\n' ) )
            break;
        End--;
    }

    if ( Start < End )
    {
        End++;
        Start = End;
        while ( *End == GET_GS( )->IndentChar[0] && End < Tail )
            End++;

        RetCode = ( ULONG ) ( End - Start );
    }

    return RetCode;
}

void AddArrayIndent( PCOMMON_STACK_S Buffer, LPCTSTR String, ULONG Length, ULONG Indent )
{
    LPCTSTR Start;
    LPCTSTR End;
    LPCTSTR Tail;

    Start = String;
    Tail = String + Length;

    End = _tcsstr( Start, _T( "\r\n" ) );
    if ( End )
    {
        Indent -= GetArrayIndent( Start, Tail - Start );
        while ( Start < Tail )
        {
            if ( End == NULL )
            {
                StackPushS( Buffer, Start, Tail - Start );
                break;
            }
            else
            {
                End += 2 * sizeof( TCHAR );
                StackPushS( Buffer, Start, End - Start );
                Start = End;
                while ( *End == GET_GS( )->IndentChar[0] )
                    End++;

                StackPushNS( Buffer, GET_GS( )->IndentChar[0], End - Start + Indent );
                Start = End;
            }
            End = _tcsstr( Start, _T( "\r\n" ) );
        }
    }
    else
    {
        StackPushS( Buffer, String, Length );
    }
}

ULONG AddArrayElementIndent( PCOMMON_STACK_S Buffer, LPTSTR Array, LPCTSTR OpString, zval *Val1, zval *Val2, ULONG Indent )
{
    ULONG RetCode;
    TCHAR *String;

    RetCode = 0;
    String = _tcsrchr( Array, _T( '\r' ) );
    if ( String )
    {
        *String = 0;
        StackPushS( Buffer, Array, String - Array );
        if ( *( String - 1 ) == _T( '(' ) )
            StackPushS( Buffer, _T( "\r\n" ), 2 );
        else
            StackPushS( Buffer, _T( ",\r\n" ), 3 );
        StackPushNS( Buffer, GET_GS( )->IndentChar[0], Indent );
        if ( Val1 )
            make_printable_zval_url( Val1, Buffer );
        if ( OpString )
        {
            StackPushS( Buffer, _T( " " ), 1 );
            StackPushS( Buffer, OpString, _tcslen( OpString ) );
            StackPushS( Buffer, _T( " " ), 1 );
        }
        if ( Val2 )
            make_printable_zval_url( Val2, Buffer );
        StackPushS( Buffer, _T( "\r\n" ), 2 );
        StackPushNS( Buffer, GET_GS( )->IndentChar[0], Indent - GET_GS_INDENT( ) );
        StackPushS( Buffer, _T( ")" ), 1 );
        RetCode = TRUE;
    }

    return RetCode;
}

ULONG AddArrayElementIndentEx( PCOMMON_STACK_S Buffer, LPTSTR Array, LPCTSTR OpString, LPCTSTR String1, LPCTSTR String2, ULONG Indent )
{
    ULONG RetCode;
    TCHAR *String;

    RetCode = 0;
    String = _tcsrchr( Array, _T( '\r' ) );
    if ( String )
    {
        *String = 0;
        StackPushS( Buffer, Array, String - Array );
        if ( *( String - 1 ) == _T( '(' ) )
            StackPushS( Buffer, _T( "\r\n" ), 2 );
        else
            StackPushS( Buffer, _T( ",\r\n" ), 3 );
        StackPushNS( Buffer, GET_GS( )->IndentChar[0], Indent );
        if ( String1 )
            StackPushS( Buffer, String1, _tcslen( String1 ) );
        if ( OpString )
        {
            StackPushS( Buffer, _T( " " ), 1 );
            StackPushS( Buffer, OpString, _tcslen( OpString ) );
            StackPushS( Buffer, _T( " " ), 1 );
        }
        if ( String2 )
            StackPushS( Buffer, String2, _tcslen( String2 ) );
        StackPushS( Buffer, _T( "\r\n" ), 2 );
        StackPushNS( Buffer, GET_GS( )->IndentChar[0], Indent - GET_GS_INDENT( ) );
        StackPushS( Buffer, _T( ")" ), 1 );
        RetCode = TRUE;
    }

    return RetCode;
}

ULONG AddArrayElement( PCOMMON_STACK_S Buffer, LPTSTR Array, LPCTSTR OpString, zval *Val1, zval *Val2 )
{
    ULONG RetCode;
    TCHAR *String;

    RetCode = 0;
    String = _tcsrchr( Array, _T( ' ' ) );
    if ( String )
    {
        *String = 0;
        StackPushS( Buffer, Array, String - Array );
        if ( *( String - 1 ) == _T( '(' ) )
            StackPushS( Buffer, _T( " " ), 1 );
        else
            StackPushS( Buffer, _T( ", " ), 2 );
        if ( Val1 )
            make_printable_zval_url( Val1, Buffer );
        if ( OpString )
        {
            StackPushS( Buffer, _T( " " ), 1 );
            StackPushS( Buffer, OpString, _tcslen( OpString ) );
            StackPushS( Buffer, _T( " " ), 1 );
        }
        if ( Val2 )
            make_printable_zval_url( Val2, Buffer );
        StackPushS( Buffer, _T( " )" ), 2 );
        RetCode = TRUE;
    }

    return RetCode;
}

ULONG AddArrayElementEx( PCOMMON_STACK_S Buffer, LPTSTR Array, LPCTSTR OpString, LPCTSTR String1, LPCTSTR String2 )
{
    ULONG RetCode;
    TCHAR *String;

    RetCode = 0;
    String = _tcsrchr( Array, _T( ' ' ) );
    if ( String )
    {
        *String = 0;
        StackPushS( Buffer, Array, String - Array );
        if ( *( String - 1 ) == _T( '(' ) )
            StackPushS( Buffer, _T( " " ), 1 );
        else
            StackPushS( Buffer, _T( ", " ), 2 );
        if ( String1 )
            StackPushS( Buffer, String1, _tcslen( String1 ) );
        if ( OpString )
        {
            StackPushS( Buffer, _T( " " ), 1 );
            StackPushS( Buffer, OpString, _tcslen( OpString ) );
            StackPushS( Buffer, _T( " " ), 1 );
        }
        if ( String2 )
            StackPushS( Buffer, String2, _tcslen( String2 ) );
        StackPushS( Buffer, _T( " )" ), 2 );
        RetCode = TRUE;
    }

    return RetCode;
}

void PopArgumentList( PDUMP_STACK Stack, ULONG Count )
{
    register ULONG Dummy;
    TCHAR *String;

    /* Pop argument list */
    Dummy = Count;
    if ( Dummy )
    {
        StackPushS( &Stack->Buffer, _T( "( " ), 2 );
        StackSetBottom( &Stack->ArgumentList, StackCount( &Stack->ArgumentList ) - Dummy );
        Dummy--;
        while ( Dummy )
        {
            if ( StackBottom( &Stack->ArgumentList, &String ) )
            {
                StackPopBottom( &Stack->ArgumentList, NULL, 0 );
                StackPushS( &Stack->Buffer, String, _tcslen( String ) );
                StackPushS( &Stack->Buffer, _T( ", " ), 2 );
            }
            Dummy--;
        }
        if ( StackBottom( &Stack->ArgumentList, &String ) )
            StackPushS( &Stack->Buffer, String, _tcslen( String ) );
        StackPushS( &Stack->Buffer, _T( " )" ), 2 );
        /* Free */
        Dummy = Count;
        while ( Dummy )
        {
            StackPop( &Stack->ArgumentList, NULL, 0 );
            Dummy--;
        }
    }
    else
    {
        StackPushS( &Stack->Buffer, _T( "( )" ), 3 );
    }
}

PVOID find_hash_key( HashTable *Table, TCHAR *Key, ULONG KeyLength )
{
    register Bucket *Bt;
    PVOID *Data;

    Data = NULL;
    Bt = Table->pListHead;
    while ( Bt )
    {
        if ( Bt->nKeyLength == KeyLength && 0 == memcmp( Bt->arKey, Key, KeyLength ) )
        {
            Data = Bt->pDataPtr ? Bt->pDataPtr : Bt->pData;
            break;
        }
        Bt = Bt->pListNext;
    }

    return Data;
}

PVOID find_hash_key_ex( HashTable *Table, TCHAR *Key, ULONG KeyLength )
{
    ULONG HashValue;
    ULONG Index;
    register Bucket *Bt;
    PVOID *Data;

    Data = NULL;
    HashValue = zend_inline_hash_func( Key, KeyLength );
    Index = HashValue & Table->nTableMask;

    Bt = Table->arBuckets[Index];
    while ( Bt )
    {
        if ( ( Bt->h == HashValue ) && ( Bt->nKeyLength == KeyLength ) )
        {
            if ( 0 == memcmp( Bt->arKey, Key, KeyLength ) )
            {
                Data = Bt->pDataPtr ? Bt->pDataPtr : Bt->pData;
                break;
            }
        }
        Bt = Bt->pNext;
    }

    return Data;
}

PVOID find_hash_key_fast( HashTable *Table, TCHAR *Key, ULONG KeyLength, ULONG HashValue )
{
    ULONG Index;
    register Bucket *Bt;
    PVOID *Data;

    Data = NULL;
    Index = HashValue & Table->nTableMask;

    Bt = Table->arBuckets[Index];
    while ( Bt )
    {
        if ( ( Bt->h == HashValue ) && ( Bt->nKeyLength == KeyLength ) )
        {
            if ( 0 == memcmp( Bt->arKey, Key, KeyLength ) )
            {
                Data = Bt->pDataPtr ? Bt->pDataPtr : Bt->pData;
                break;
            }
        }
        Bt = Bt->pNext;
    }

    return Data;
}

void dump_hash_key( HashTable *Table, ULONG Indent )
{
    Bucket *Bt;

    if ( Table )
    {
        Bt = Table->pListHead;
        while ( Bt )
        {
            dump_indent_string_stub( Indent );
            ADD_DEBUG_LOG_LR( _T( "//%s" ), Bt->arKey );
            Bt = Bt->pListNext;
        }
    }
}

ULONG find_control_list_start( PDUMP_STACK Stack, ULONG Offset, ULONG End )
{
    ULONG RetCode;
    register ULONG Iter;
    register ULONG Iter1;
    ULONG Count;
    ULONG Count1;
    PCOMMON_STACK_T StackControl;
    PCOMMON_STACK_T StackList;
    register PCONTROL_LIST ControlList;
    register PCOMMON_CONTROL_ENTRY Entry;

    RetCode = INVALID_OP_OFFSET;
    StackControl = &Stack->ControlList;
    Count = StackCountT( StackControl );
    for ( Iter = 0; Iter < Count; Iter++ )
    {
        ControlList = StackAtT( StackControl, Iter );

        StackList = &ControlList->List[1];
        Count1 = StackCountT( StackList );
        for ( Iter1 = 0; Iter1 < Count1; Iter1++ )
        {
            Entry = StackAtT( StackList, Iter1 );
            if ( End == Entry->End && Offset == Entry->Offset )
            {
                RetCode = Entry->Start;
                break;
            }
        }
    }

    return RetCode;
}

ULONG find_control_list_end( PDUMP_STACK Stack, ULONG Offset, ULONG Start )
{
    ULONG RetCode;
    register ULONG Iter;
    register ULONG Iter1;
    ULONG Count;
    ULONG Count1;
    PCOMMON_STACK_T StackControl;
    PCOMMON_STACK_T StackList;
    register PCONTROL_LIST ControlList;
    register PCOMMON_CONTROL_ENTRY Entry;

    RetCode = INVALID_OP_OFFSET;
    StackControl = &Stack->ControlList;
    Count = StackCountT( StackControl );
    for ( Iter = 0; Iter < Count; Iter++ )
    {
        ControlList = StackAtT( StackControl, Iter );

        StackList = &ControlList->List[1];
        Count1 = StackCountT( StackList );
        for ( Iter1 = 0; Iter1 < Count1; Iter1++ )
        {
            Entry = StackAtT( StackList, Iter1 );
            if ( Start == Entry->Start && Offset == Entry->Offset )
            {
                RetCode = Entry->End;
                break;
            }
        }
    }

    return RetCode;
}

PCONTROL_LIST find_control_list( PCOMMON_STACK_T Control, ULONG Offset )
{
    register ULONG Iter;
    ULONG Count;
    register PCONTROL_LIST ControlList;

    Count = StackCountT( Control );
    for ( Iter = 0; Iter < Count; Iter++ )
    {
        ControlList = StackAtT( Control, Iter );
        if ( ControlList->Offset == Offset )
            return ControlList;
    }

    return NULL;
}

ULONG find_control_list_if_enclose( PDUMP_STACK Stack, ULONG Offset, ULONG JmpOffset, ULONG *Start )
{
    ULONG NewStart;
    ULONG NewEnd;
    ULONG Seek;
    ULONG Flags;
    register ULONG Iter;
    register ULONG Iter1;
    ULONG Count;
    ULONG Count1;
    PCOMMON_STACK_T StackControl;
    PCOMMON_STACK_T StackList;
    PCONTROL_LIST ControlList;
    PCOMMON_CONTROL_ENTRY Entry;

    NewStart = 0;
    NewEnd = INVALID_OP_OFFSET;
    StackControl = &Stack->ControlList;
    Count = StackCountT( StackControl );
    for ( Iter = 0; Iter < Count; Iter++ )
    {
        ControlList = StackAtT( StackControl, Iter );
        StackList = &ControlList->List[1];
        Count1 = StackCountT( StackList );
        for ( Iter1 = 0; Iter1 < Count1; Iter1++ )
        {
            Entry = StackAtT( StackList, Iter1 );
            Flags = Entry->Flags;
            if ( ( Flags & DS_FLAGS_MASK ) == DS_FLAGS_IF || ( Flags & DS_FLAGS_MASK ) == DS_FLAGS_ELSE || ( Flags & DS_FLAGS_MASK ) == DS_FLAGS_ELSEIF )
            {
                if ( NewStart <= Entry->Start && Entry->End <= NewEnd )
                {
                    if ( Entry->Start <= Offset && Offset < Entry->End )
                    {
                        NewStart = Entry->Start;
                        NewEnd = Entry->End;
                    }
                }
            }
        }
    }

    if ( NewEnd != INVALID_OP_OFFSET )
    {
        Seek = NewEnd;
        while ( ControlList = find_control_list( StackControl, Seek ) )
        {
            StackList = &ControlList->List[1];
            Count = StackCountT( StackList );
            for ( Iter = 0; Iter < Count; Iter++ )
            {
                Entry = StackAtT( StackList, Iter );
                Flags = Entry->Flags;
                if ( ( Flags & DS_FLAGS_MASK ) == DS_FLAGS_IF || ( Flags & DS_FLAGS_MASK ) == DS_FLAGS_ELSE || ( Flags & DS_FLAGS_MASK ) == DS_FLAGS_ELSEIF )
                {
                    Seek = Entry->End;
                    break;
                }
            }
            if ( Iter == Count )
                break;
        }
    }
    else
    {
        Seek = INVALID_OP_OFFSET;
    }

    if ( Start )
        *Start = NewStart;

    if ( Seek == JmpOffset && NewEnd != JmpOffset )
        return NewEnd;
    else
        return INVALID_OP_OFFSET;
}

ULONG is_control_list( PDUMP_STACK Stack, ULONG Start, ULONG End )
{
    register ULONG Iter;
    register ULONG Iter1;
    ULONG Count;
    ULONG Count1;
    PCOMMON_STACK_T StackControl;
    PCOMMON_STACK_T StackList;
    register PCONTROL_LIST ControlList;
    register PCOMMON_CONTROL_ENTRY Entry;

    StackControl = &Stack->ControlList;
    Count = StackCountT( StackControl );
    for ( Iter = 0; Iter < Count; Iter++ )
    {
        ControlList = StackAtT( StackControl, Iter );

        StackList = &ControlList->List[1];
        Count1 = StackCountT( StackList );
        for ( Iter1 = 0; Iter1 < Count1; Iter1++ )
        {
            Entry = StackAtT( StackList, Iter1 );
            if ( Start < Entry->Start && Entry->Start < End && End < Entry->End ||
                Entry->Start < Start && Start < Entry->End && Entry->End < End )
                return FALSE;
        }

        StackList = &ControlList->List[0];
        Count1 = StackCountT( StackList );
        for ( Iter1 = 0; Iter1 < Count1; Iter1++ )
        {
            Entry = StackAtT( StackList, Iter1 );
            if ( Start < Entry->Start && Entry->Start < End && End < Entry->End ||
                Entry->Start < Start && Start < Entry->End && Entry->End < End )
                return FALSE;
        }
    }

    return TRUE;
}

ULONG adjust_control_list_start( PDUMP_STACK Stack, ULONG Start, ULONG End )
{
    ULONG NewStart;
    register ULONG Iter;
    register ULONG Iter1;
    ULONG Count;
    ULONG Count1;
    PCOMMON_STACK_T StackControl;
    PCOMMON_STACK_T StackList;
    register PCONTROL_LIST ControlList;
    register PCOMMON_CONTROL_ENTRY Entry;

    NewStart = Start;
    StackControl = &Stack->ControlList;
    Count = StackCountT( StackControl );
    for ( Iter = 0; Iter < Count; Iter++ )
    {
        ControlList = StackAtT( StackControl, Iter );

        StackList = &ControlList->List[1];
        Count1 = StackCountT( StackList );
        for ( Iter1 = 0; Iter1 < Count1; Iter1++ )
        {
            Entry = StackAtT( StackList, Iter1 );
            if ( Entry->Start < NewStart && NewStart < Entry->End && Entry->End <= End )
                NewStart = Entry->Start;
            else if ( NewStart < Entry->Start && Entry->Start < End && End < Entry->End )
                NewStart = Entry->Start;
        }

        StackList = &ControlList->List[0];
        Count1 = StackCountT( StackList );
        for ( Iter1 = 0; Iter1 < Count1; Iter1++ )
        {
            Entry = StackAtT( StackList, Iter1 );
            if ( Entry->Start < NewStart && NewStart < Entry->End && Entry->End <= End )
                NewStart = Entry->Start;
            else if ( NewStart < Entry->Start && Entry->Start < End && End < Entry->End )
                NewStart = Entry->Start;
        }
    }

    return NewStart;
}

ULONG adjust_control_list_end( PDUMP_STACK Stack, ULONG Start, ULONG End )
{
    ULONG NewEnd;
    register ULONG Iter;
    register ULONG Iter1;
    ULONG Count;
    ULONG Count1;
    PCOMMON_STACK_T StackControl;
    PCOMMON_STACK_T StackList;
    register PCONTROL_LIST ControlList;
    register PCOMMON_CONTROL_ENTRY Entry;

    NewEnd = End;
    StackControl = &Stack->ControlList;
    Count = StackCountT( StackControl );
    for ( Iter = 0; Iter < Count; Iter++ )
    {
        ControlList = StackAtT( StackControl, Iter );

        StackList = &ControlList->List[1];
        Count1 = StackCountT( StackList );
        for ( Iter1 = 0; Iter1 < Count1; Iter1++ )
        {
            Entry = StackAtT( StackList, Iter1 );
            if ( Entry->Start < Start && Start < Entry->End && Entry->End < NewEnd )
                NewEnd = Entry->End;
            else if ( Start < Entry->Start && Entry->Start < NewEnd && NewEnd < Entry->End )
                NewEnd = Entry->End;
        }

        StackList = &ControlList->List[0];
        Count1 = StackCountT( StackList );
        for ( Iter1 = 0; Iter1 < Count1; Iter1++ )
        {
            Entry = StackAtT( StackList, Iter1 );
            if ( Entry->Start < Start && Start < Entry->End && Entry->End < NewEnd )
                NewEnd = Entry->End;
            else if ( Start < Entry->Start && Entry->Start < NewEnd && NewEnd < Entry->End )
                NewEnd = Entry->End;
        }
    }

    return NewEnd;
}

ULONG insert_control_list( PDUMP_STACK Stack, ULONG Offset, PCOMMON_CONTROL_ENTRY Entry )
{
    ULONG RetCode;
    PCONTROL_LIST ControlList;
    register PCOMMON_STACK_T StackControl;
    register ULONG Start;
    register ULONG End;
    register ULONG Mid;

    RetCode = 0;
    ControlList = NULL;
    Entry->Offset = Stack->Offset;
    StackControl = &Stack->ControlList;
    End = StackCountT( StackControl );
    if ( End )
    {
        Start = 0;
        Mid = End >> 1;
        while ( Mid < End )
        {
            ControlList = StackAtT( StackControl, Mid );
            if ( Offset > ControlList->Offset )
            {
                Start = Mid + 1;
                Mid = ( Start + End ) >> 1;
            }
            else if ( Offset < ControlList->Offset )
            {
                End = Mid;
                Mid = ( Start + End ) >> 1;
            }
            else
            {
                RetCode = TRUE;
                break;
            }
        }
    }

    if ( !RetCode )
    {
        Start = StackPushSizeAscT( StackControl, &Offset, FIELD_OFFSET( CONTROL_LIST, List ) );
        ControlList = StackAtT( &Stack->ControlList, Start - 1 );
    }

    if ( Entry->Flags & DS_FLAGS_END )
        RetCode = StackPushSizeDscT( &ControlList->List[0], Entry, sizeof( COMMON_CONTROL_ENTRY ) );
    else
        RetCode = StackPushSizeDscT( &ControlList->List[1], Entry, sizeof( COMMON_CONTROL_ENTRY ) );

    return RetCode;
}

ULONG remove_control_list( PDUMP_STACK Stack, ULONG Offset, PCOMMON_CONTROL_ENTRY Entry )
{
    register ULONG Iter;
    ULONG Count;
    register PCOMMON_STACK_T StackControl;
    register ULONG Start;
    register ULONG End;
    register ULONG Mid;
    PCONTROL_LIST ControlList;
    PCOMMON_CONTROL_ENTRY EntryPtr;

    StackControl = &Stack->ControlList;
    End = StackCountT( StackControl );
    if ( End )
    {
        Start = 0;
        Mid = End >> 1;
        while ( Mid < End )
        {
            ControlList = StackAtT( StackControl, Mid );
            if ( Offset > ControlList->Offset )
            {
                Start = Mid + 1;
                Mid = ( Start + End ) >> 1;
            }
            else if ( Offset < ControlList->Offset )
            {
                End = Mid;
                Mid = ( Start + End ) >> 1;
            }
            else
            {
                for ( Iter = 0, Count = StackCountT( &ControlList->List[0] ); Iter < Count; Iter++ )
                {
                    EntryPtr = StackAtT( &ControlList->List[0], Iter );
                    if ( EntryPtr->Start == Entry->Start && EntryPtr->End == Entry->End )
                    {
                        StackRemoveIndexT( &ControlList->List[0], Iter );
                        return TRUE;
                    }
                }

                for ( Iter = 0, Count = StackCountT( &ControlList->List[1] ); Iter < Count; Iter++ )
                {
                    EntryPtr = StackAtT( &ControlList->List[1], Iter );
                    if ( EntryPtr->Start == Entry->Start && EntryPtr->End == Entry->End )
                    {
                        StackRemoveIndexT( &ControlList->List[1], Iter );
                        return TRUE;
                    }
                }
                break;
            }
        }
    }

    return FALSE;
}

void insert_cont_brk_list( PDUMP_STACK Stack, ULONG Continue, ULONG Break, ULONG Start, ULONG End, ULONG Flags )
{
    BRK_CONT_LIST BrkCont;

    BrkCont.Offset = Stack->Offset;
    BrkCont.Break = Break;
    BrkCont.Continue = Continue;
    BrkCont.Start = Start;
    BrkCont.End = End;
    BrkCont.Flags = Flags;

    StackPushAscT( &Stack->BreakList, &BrkCont );
    StackPushAscT( &Stack->ContinueList, &BrkCont );
}

PBRK_CONT_LIST GetBreak( PDUMP_STACK Stack, ULONG CheckOffset, ULONG Offset )
{
    PBRK_CONT_LIST RetCode;
    register ULONG Start;
    register ULONG End;
    ULONG Count;
    BRK_CONT_LIST BrkCont;
    register PBRK_CONT_LIST BrkContPtr;

    RetCode = NULL;
    BrkCont.Break = CheckOffset;
    Start = StackFindAscT( &Stack->BreakList, &BrkCont );
    if ( Start )
    {
        End = Start;
        Start -= 2;
        Count = StackCountT( &Stack->BreakList );
        while ( Start != - 1 && ( ( PBRK_CONT_LIST )StackAtT( &Stack->BreakList, Start ) )->Break == CheckOffset )
            Start--;

        while ( End < Count && ( ( PBRK_CONT_LIST )StackAtT( &Stack->BreakList, End ) )->Break == CheckOffset )
            End++;

        while ( ++Start < End )
        {
            BrkContPtr = StackAtT( &Stack->BreakList, Start );
            if ( BrkContPtr->Start <= Offset && Offset < BrkContPtr->End )
                RetCode = BrkContPtr;
        }
    }

    return RetCode;
}

PBRK_CONT_LIST GetContinue( PDUMP_STACK Stack, ULONG CheckOffset, ULONG Offset )
{
    PBRK_CONT_LIST RetCode;
    register ULONG Start;
    register ULONG End;
    ULONG Count;
    BRK_CONT_LIST BrkCont;
    register PBRK_CONT_LIST BrkContPtr;

    RetCode = NULL;
    BrkCont.Continue = CheckOffset;
    Start = StackFindAscT( &Stack->ContinueList, &BrkCont );
    if ( Start )
    {
        End = Start;
        Start -= 2;
        Count = StackCountT( &Stack->ContinueList );
        while ( Start != - 1 && ( ( PBRK_CONT_LIST )StackAtT( &Stack->ContinueList, Start ) )->Continue == CheckOffset )
            Start--;

        while ( End < Count && ( ( PBRK_CONT_LIST )StackAtT( &Stack->ContinueList, End ) )->Continue == CheckOffset )
            End++;

        while ( ++Start < End )
        {
            BrkContPtr = StackAtT( &Stack->ContinueList, Start );
            if ( BrkContPtr->Start <= Offset && Offset < BrkContPtr->End )
                RetCode = BrkContPtr;
        }
    }

    return RetCode;
}

PBRK_CONT_LIST GetBreakEx( PDUMP_STACK Stack, ULONG CheckOffset, ULONG Offset, ULONG *IndexPtr )
{
    PBRK_CONT_LIST RetCode;
    register ULONG Start;
    register ULONG End;
    register ULONG Index;
    ULONG Count;
    ULONG MaxIndex;
    BRK_CONT_LIST BrkCont;
    register PBRK_CONT_LIST BrkContPtr;

    RetCode = NULL;
    BrkCont.Break = CheckOffset;
    Start = StackFindAscT( &Stack->BreakList, &BrkCont );
    if ( Start )
    {
        Index = 0;
        if ( IndexPtr )
            MaxIndex = *IndexPtr;
        else
            MaxIndex = 1;

        End = Start;
        Start -= 2;
        Count = StackCountT( &Stack->BreakList );
        while ( Start != - 1 && ( ( PBRK_CONT_LIST )StackAtT( &Stack->BreakList, Start ) )->Break == CheckOffset )
            Start--;

        while ( End < Count && ( ( PBRK_CONT_LIST )StackAtT( &Stack->BreakList, End ) )->Break == CheckOffset )
            End++;

        while ( ++Start < End )
        {
            BrkContPtr = StackAtT( &Stack->BreakList, Start );
            if ( BrkContPtr->Start <= Offset && Offset < BrkContPtr->End ||
                ( BrkContPtr->Continue == BrkContPtr->Break - 1 && Offset <= BrkContPtr->Continue ) )
            {
                Index++;
                RetCode = BrkContPtr;
                if ( Index == MaxIndex )
                    break;
            }
        }

        if ( IndexPtr )
            *IndexPtr = Index;
    }

    return RetCode;
}

PBRK_CONT_LIST GetContinueEx( PDUMP_STACK Stack, ULONG CheckOffset, ULONG Offset, ULONG *IndexPtr )
{
    PBRK_CONT_LIST RetCode;
    register ULONG Start;
    register ULONG End;
    register ULONG Index;
    ULONG Count;
    ULONG MaxIndex;
    BRK_CONT_LIST BrkCont;
    register PBRK_CONT_LIST BrkContPtr;

    RetCode = NULL;
    BrkCont.Continue = CheckOffset;
    Start = StackFindAscT( &Stack->ContinueList, &BrkCont );
    if ( Start )
    {
        Index = 0;
        if ( IndexPtr )
            MaxIndex = *IndexPtr;
        else
            MaxIndex = 1;

        End = Start;
        Start -= 2;
        Count = StackCountT( &Stack->ContinueList );
        while ( Start != - 1 && ( ( PBRK_CONT_LIST )StackAtT( &Stack->ContinueList, Start ) )->Continue == CheckOffset )
            Start--;

        while ( End < Count && ( ( PBRK_CONT_LIST )StackAtT( &Stack->ContinueList, End ) )->Continue == CheckOffset )
            End++;

        while ( ++Start < End )
        {
            BrkContPtr = StackAtT( &Stack->ContinueList, Start );
            if ( BrkContPtr->Start <= Offset && Offset < BrkContPtr->End ||
                ( BrkContPtr->Continue == BrkContPtr->Break - 1 && Offset <= BrkContPtr->Continue ) )
            {
                Index++;
                RetCode = BrkContPtr;
                if ( Index == MaxIndex )
                    break;
            }
        }

        if ( IndexPtr )
            *IndexPtr = Index;
    }

    return RetCode;
}

ULONG scan_prev_output( PDUMP_STACK Stack, ULONG Start, ULONG End )
{
    ULONG RetCode;
    register ULONG Top;
    register ULONG Offset;

    RetCode = Start - 1;
    Top = StackFindSmallEqualAscU( &Stack->Output, End );
    if ( Top )
    {
        Offset = StackAtU( &Stack->Output, Top - 1 );
        if ( Offset >= Start )
            RetCode = Offset;
    }

    return RetCode;
}

ULONG scan_next_output( PDUMP_STACK Stack, ULONG Start, ULONG End )
{
    ULONG RetCode;
    register ULONG Top;
    register ULONG Offset;

    RetCode = End;
    Top = StackFindLargeEqualAscU( &Stack->Output, Start );
    if ( Top )
    {
        Offset = StackAtU( &Stack->Output, Top - 1 );
        if ( Offset < End )
            RetCode = Offset;
    }

    return RetCode;
}

inline ULONG get_jmp_offset( PDUMP_STACK Stack, zend_op *OpLine )
{
    if ( OP_CODE( OpLine ) == ZEND_JMPZ || OP_CODE( OpLine ) == ZEND_JMPNZ )
        return OP_JMPX( OpLine, Stack->Head );
    else if ( OP_CODE( OpLine ) == ZEND_JMP )
        return OP_JMP( OpLine, Stack->Head );
    else if ( OP_CODE( OpLine ) == ZEND_JMPZNZ )
        return OP_JMPZNZ( OpLine, Stack->Head );
    else
        return INVALID_OP_OFFSET;
}

inline ULONG is_special_opcode( zend_uchar OpCode )
{
    if ( OpCode == ZEND_JMPZ_EX ||
        OpCode == ZEND_JMPNZ_EX ||
        OpCode == ZEND_END_SILENCE ||
        OpCode == ZEND_INIT_CTOR_CALL ||
        OpCode == ZEND_INIT_METHOD_CALL ||
        OpCode == ZEND_INIT_STATIC_METHOD_CALL ||
        OpCode == ZEND_INIT_FCALL_BY_NAME ||
        OpCode == ZEND_SEND_VAR ||
        OpCode == ZEND_SEND_VAR_NO_REF ||
        OpCode == ZEND_SEND_VAL ||
        OpCode == ZEND_FETCH_DIM_R ||
        OpCode == ZEND_FETCH_CLASS ||
        OpCode == ZEND_USER_OPCODE ||
        OpCode == ZEND_NOP )
        return TRUE;
    else
        return FALSE;
}

inline ULONG is_default_return( ULONG State, zend_op *OpLine )
{
    /* Is default return value */
    if ( ( State & DS_STATE_MAIN ) && TEST_OP1_CONST( OpLine ) && OP1_VAL( OpLine )->value.lval == 1 ||
        !( State & DS_STATE_MAIN ) && TEST_OP1_CONST( OpLine ) && OP1_VAL_TYPE( OpLine ) == IS_NULL )
        return TRUE;
    else
        return FALSE;
}

inline ULONG is_default_return_ex( PDUMP_STACK Stack, zend_op *OpLine )
{
    /* Is default return value */
    if ( OP_CODE( OpLine ) == OP_CODE( Stack->Tail - 1 ) &&
        OP1_TYPE( OpLine ) == OP1_TYPE( Stack->Tail - 1 ) &&
        OP1_VAL_TYPE( OpLine ) == OP1_VAL_TYPE( Stack->Tail - 1 ) )
        return TRUE;
    else
        return FALSE;
}

inline ULONG scan_if_default_return( PDUMP_STACK Stack, ULONG Offset )
{
    ULONG Top;

    Top = StackFindAscU( &Stack->ReturnX, Offset );
    if ( Top )
        return TRUE;
    else
        return FALSE;
}

inline ULONG is_special_jump( ULONG Offset, zend_op *Head )
{
    zend_op *OpLine;

    OpLine = Head + Offset;

    /* JmpX in cond express */
    if ( OP_CODE( OpLine ) == ZEND_JMP )
    {
        OpLine = Head + OP_JMP( OpLine, Head ) - 1;
        while ( OP_CODE( OpLine ) == ZEND_NOP )
            OpLine--;

        if ( OP_CODE( OpLine ) == ZEND_QM_ASSIGN )
            return TRUE;
    }

    return FALSE;
}

inline ULONG is_special_switch_free( zend_op *OpLine, zend_op *Tail )
{
    while ( OP_CODE( OpLine ) == ZEND_SWITCH_FREE )
        OpLine++;

    if ( OP_CODE( OpLine ) == ZEND_RETURN && OpLine < Tail - 2 )
        return TRUE;
    else
        return FALSE;
}

inline ULONG is_jump_to_loop( zend_op *Head, ULONG Offset )
{
    zend_op *OpLine;

    OpLine = Head + Offset;
    if ( OP_CODE( OpLine ) == ZEND_FE_FETCH ||
        OP_CODE( OpLine ) == ZEND_NOP && OP_CODE( OpLine + 1 ) == ZEND_FE_FETCH ||
        Offset && OP_CODE( --OpLine ) == ZEND_JMPZNZ )
        return TRUE;
    else
        return FALSE;
}

inline ULONG is_jump_to_loop_back( PDUMP_STACK Stack, ULONG Offset, ULONG Start )
{
    ULONG Top;
    ULONG NextOffset;
    ULONG NextOutput;
    zend_op *Head;
    zend_op *OpLine;

    Head = Stack->Head;
    OpLine = Head + Offset;
    if ( Offset && OP_CODE( OpLine - 1 ) == ZEND_JMPZNZ )
    {
        if ( OP_JMPZNZ( OpLine - 1, Head ) == Start )
            return TRUE;
        else
            return FALSE;
    }
    else
    {
        Top = StackFindLargeEqualAscT( &Stack->Logic, &Offset );
        if ( Top )
        {
            NextOffset = ( ( PLOGIC_LIST )StackAtT( &Stack->Logic, Top - 1 ) )->End;
            NextOutput = scan_next_output( Stack, Offset, NextOffset );
            if ( NextOutput == NextOffset && OP_JMPX( Head + NextOffset, Head ) == Start )
                return TRUE;
        }
    }

    return FALSE;
}

ULONG FASTCALL get_real_continue_offset( PDUMP_STACK Stack, ULONG Offset )
{
    ULONG Top;
    ULONG Dummy;
    zend_op *Head;
    zend_op *OpLine;

    Head = Stack->Head;
    OpLine = Stack->Head + Offset;
    if ( Offset && OP_CODE( OpLine - 1 ) == ZEND_JMPZNZ )
    {
        Dummy = OP_JMPZNZ( OpLine - 1, Head );
        if ( Dummy < Offset )
            return get_real_continue_offset( Stack, Dummy );
        else
            return Offset;
    }
    else if ( OP_CODE( OpLine ) == ZEND_FE_FETCH )
    {
        return Offset;
    }
    else
    {
        Top = StackFindLargeEqualAscT( &Stack->Logic, &Offset );
        if ( Top )
        {
            OpLine = Stack->Head + ( ( PLOGIC_LIST )StackAtT( &Stack->Logic, Top - 1 ) )->End;
            if ( OP_CODE( OpLine ) == ZEND_JMPZ || OP_CODE( OpLine ) == ZEND_JMPNZ )
            {
                Dummy = OP_JMPX( OpLine, Head );
                if ( Dummy < Offset )
                    return get_real_continue_offset( Stack, Dummy );
                else
                    return Offset;
            }
        }
        return Offset;
    }
}

ULONG FASTCALL get_real_break_offset( PDUMP_STACK Stack, ULONG Offset )
{
    ULONG Top;
    ULONG Dummy;
    zend_op *Head;
    zend_op *OpLine;

    Head = Stack->Head;
    OpLine = Stack->Head + Offset;
    if ( Offset && OP_CODE( OpLine - 1 ) == ZEND_JMPZNZ )
    {
        Dummy = OP_JMPZNZ( OpLine - 1, Head );
        if ( Dummy < Offset )
            return get_real_break_offset( Stack, Dummy );
        else
            return Dummy;
    }
    else if ( OP_CODE( OpLine ) == ZEND_FE_FETCH )
    {
        return Stack->Argument;
    }
    else
    {
        Top = StackFindLargeEqualAscT( &Stack->Logic, &Offset );
        if ( Top )
        {
            OpLine = Stack->Head + ( ( PLOGIC_LIST )StackAtT( &Stack->Logic, Top - 1 ) )->End;
            if ( OP_CODE( OpLine ) == ZEND_JMPZ || OP_CODE( OpLine ) == ZEND_JMPNZ )
            {
                Dummy = OP_JMPX( OpLine, Head );
                if ( Dummy < Offset )
                    return get_real_break_offset( Stack, Dummy );
                else
                    return Dummy;
            }
        }
        return Stack->Argument;
    }
}

ULONG FASTCALL scan_if_logic_end( PDUMP_STACK Stack, zend_op *OpLine )
{
    zend_op *Head;
    zend_op *Tail;
    zend_op *Start;
    zend_op *End;
    zend_op *PrevStart;
    zend_op *PrevEnd;

    Head = Stack->Head;
    Tail = Stack->Tail;
    End = OpLine;
    do
    {
        Start = End;
        if ( OP_CODE( End ) == ZEND_JMPZNZ )
            End = Head + OP_JMPZNZ( End, Head );
        else
            End = Head + OP_JMPX( End, Head );
        if ( End < Start + 2 )
            break;

        PrevStart = Start;
        PrevEnd = End - 1;
        if ( PrevStart < PrevEnd - 1 )
        {
            /* MUST be compile variable */
            while ( OP1_VAR( PrevStart ) == OP1_VAR( PrevEnd ) &&
                OP1_TYPE( PrevStart ) == IS_CV && OP1_TYPE( PrevEnd ) == IS_CV &&
                ( OP_CODE( PrevStart ) == ZEND_JMPZ && OP_CODE( PrevEnd ) == ZEND_JMPNZ ||
                    OP_CODE( PrevStart ) == ZEND_JMPNZ && OP_CODE( PrevEnd ) == ZEND_JMPZ ) )
            {
                PrevStart--;
                PrevEnd--;
                End--;
            }
        }

        if ( OP_CODE( Start ) == ZEND_JMPZ )
        {
            if ( OP_CODE( End - 1 ) == ZEND_JMPZ || OP_CODE( End - 1 ) == ZEND_JMPNZ )
            {
                End--;
                if ( Head + OP_JMPX( End, Head ) - 1 != End )
                    continue;
                End++;
            }
            else
            {
                break;
            }
        }
        else if ( OP_CODE( Start ) == ZEND_JMPNZ )
        {
            if ( OP_CODE( End - 1 ) == ZEND_JMPZ || OP_CODE( End - 1 ) == ZEND_JMPNZ )
            {
                End--;
                if ( Head + OP_JMPX( End, Head ) - 1 != End )
                    continue;
                End++;
            }
            else
            {
                break;
            }
        }
        else
            break;

        while ( OP_CODE( End ) != ZEND_JMPZ && OP_CODE( End ) != ZEND_JMPNZ )
        {
            if ( OPR_EA_TYPE( End ) & EXT_TYPE_UNUSED )
            {
                Tail = End;
                break;
            }
            End++;
        }
    } while ( End < Tail );

    return End - Head;
}

void FASTCALL patch_if_logic( PDUMP_STACK Stack, zend_op *OpLine )
{
    ULONG JmpOffset;
    zend_uchar OpCode;
    zend_uchar OpCode1;
    zend_op *Head;
    zend_op *OpLine1;

    if ( TEST_NOT_TMP_VAR( &OpLine->op1 ) )
    {
        Head = Stack->Head;
        JmpOffset = OP_JMPX( OpLine, Head );
        OpLine1 = Head + JmpOffset;
        OpCode = OP_CODE( OpLine );
        OpCode1 = OP_CODE( OpLine1 );
        if ( OpCode1 == ZEND_JMPZ || OpCode1 == ZEND_JMPNZ )
        {
            OpLine++;
            if ( OpCode == OpCode1 && OP1_VAR( OpLine ) == OP1_VAR( OpLine1 ) && OP1_TYPE( OpLine ) == OP1_TYPE( OpLine1 ) )
                SET_OP_JMPX( OpLine, JmpOffset, Head );
        }
        else if ( OpCode == ZEND_JMPZ )
        {
            OpLine1--;
            OpCode1 = OP_CODE( OpLine1 );
            if ( OpCode1 == ZEND_JMPNZ )
            {
                if ( OP1_VAR( OpLine ) == OP1_VAR( OpLine1 ) && OP1_TYPE( OpLine ) == OP1_TYPE( OpLine1 ) )
                    SET_OP_JMPX( OpLine, JmpOffset - 1, Head );
            }
        }
    }
}

void FASTCALL patch_jmpx( PDUMP_STACK Stack, zend_op *OpLine )
{
    ULONG Top;
    ULONG Count;
    ULONG JmpOffset;
    ULONG Dummy;
    zend_uchar OpCode;
    zend_op *Head;
    zend_op *OpLine1;

    Head = Stack->Head;
    Top = StackFindLargeAscU( &Stack->JmpXX, OpLine - Head );
    if ( Top )
    {
        Top--;
        OpCode = OP_CODE( OpLine );
        JmpOffset = OP_JMPX( OpLine, Head );
        Count = StackCountU( &Stack->JmpXX );
        while ( Top < Count )
        {
            Dummy = StackAtU( &Stack->JmpXX, Top );
            if ( Dummy >= JmpOffset )
                break;

            OpLine1 = Head + Dummy;
            if ( OpCode == OP_CODE( OpLine1 ) && JmpOffset == OP_JMPX( OpLine1, Head ) )
            {
                OpLine1--;
                SET_OP_JMPX( OpLine, Dummy, Head );
                break;
            }
            Top++;
        }
    }
}

ULONG scan_if_logic( PDUMP_STACK Stack, zend_op *OpLine )
{
    ULONG RetCode;
    ULONG Offset;
    ULONG StartOffset;
    ULONG JmpEndOffset;
    zend_op *Head;
    zend_op *Start;
    zend_op *End;
    LOGIC_LIST Logic;

    RetCode = INVALID_OP_OFFSET;
    Head = Stack->Head;
    End = Stack->Tail;

    while ( OpLine < End )
    {
        if ( OP_CODE( OpLine ) == ZEND_JMPZ || OP_CODE( OpLine ) == ZEND_JMPNZ )
            break;
        OpLine++;
    }

    StartOffset = OpLine - Head;

    /* See if exist */
    if ( StackFindAscT( &Stack->Logic, &StartOffset ) )
        return StartOffset;

    /* Re-init */
    StackReinitU( &Stack->Common );

    /* Re-init */
    StackReinitU( &Stack->PreSkip );

    /* Save skip offset */
    StackPushU( &Stack->PreSkip, StartOffset );

    /* Recover optimized opline */
    patch_if_logic( Stack, OpLine );

    JmpEndOffset = scan_if_logic_end( Stack, OpLine );
    Start = OpLine + 1;
    Offset = StartOffset + 1;
    while ( Start < End )
    {
        if ( OP_CODE( Start ) == ZEND_JMPZ || OP_CODE( Start ) == ZEND_JMPNZ )
        {
            /* JmpX in cond express */
            if ( is_special_jump( OP_JMPX( Start, Head ) - 1, Head ) )
                StackPushU( &Stack->Common, OP_JMPX( Start, Head ) - 1 );

            if ( scan_if_logic_end( Stack, Start ) != JmpEndOffset )
                break;

            /* Save skip offset */
            StackPushU( &Stack->PreSkip, Offset );
        }
        else if ( OP_CODE( Start ) == ZEND_JMPZNZ )
        {
            if ( scan_if_logic_end( Stack, Start ) != JmpEndOffset )
                break;

            /* Save skip offset */
            StackPushU( &Stack->PreSkip, Offset );
        }
        else if ( OP_CODE( Start ) == ZEND_JMP )
        {
            if ( StackFindU( &Stack->Common, Offset ) == 0 )
                break;
        }
        else if ( OPR_EA_TYPE( Start ) & EXT_TYPE_UNUSED && !is_special_opcode( OP_CODE( Start ) ) )
        {
            break;
        }
        else if ( OP_CODE( Start ) == ZEND_BRK || OP_CODE( Start ) == ZEND_CONT )
        {
            break;
        }
        Start++;
        Offset++;
    }

    /* Pop up end offset */
    StackPopU( &Stack->PreSkip, &RetCode );
    StackPushU( &Stack->Output, RetCode );

    /* Skip once */
    while ( StackPopBottomU( &Stack->PreSkip, &Offset ) )
        StackPushAscU( &Stack->SkipOnce, Offset );

    Logic.End = RetCode;
    Logic.Start = StartOffset;
    Logic.Flags = 0;
    StackPushAscT( &Stack->Logic, &Logic );

    OpLine = Head + RetCode;
    if ( OP_CODE( OpLine ) == ZEND_JMPZNZ )
    {
        StackPushU( &Stack->JmpZnz, RetCode );
    }
    else
    {
        StackPushU( &Stack->JmpX, RetCode );
        Offset = OP_JMPX( OpLine, Head ) - 1;
        /* JmpX in cond express */
        if ( is_special_jump( Offset, Head ) )
        {
            /* Condition ? r1 : r2 */
            StackPushAscU( &Stack->SkipOnce, Offset );
            StackPushAscU( &Stack->SkipOnce, RetCode );
        }
    }

    return RetCode;
}

ULONG find_jmp_small_ex( PDUMP_STACK Stack, ULONG FindOffset, ULONG Start, ULONG End, ULONG *JmpOffsetPtr )
{
    ULONG RetCode;
    ULONG Offset;
    zend_op *Head;
    zend_op *OpLine1;
    zend_op *OpLine2;

    RetCode = INVALID_OP_OFFSET;
    Head = Stack->Head;
    OpLine1 = Head + Start;
    OpLine2 = Head + End;
    while ( OpLine1 < OpLine2 )
    {
        if ( OP_CODE( OpLine1 ) == ZEND_JMP )
        {
            Offset = OP_JMP( OpLine1, Head );
            if ( Offset <= FindOffset )
            {
                if ( JmpOffsetPtr )
                    *JmpOffsetPtr = Offset;
                RetCode = OpLine1 - Head;
                break;
            }
        }
        else if ( OP_CODE( OpLine1 ) == ZEND_JMPZ || OP_CODE( OpLine1 ) == ZEND_JMPNZ )
        {
            Offset = OP_JMPX( OpLine1, Head );
            if ( Offset <= FindOffset )
            {
                if ( JmpOffsetPtr )
                    *JmpOffsetPtr = Offset;
                RetCode = OpLine1 - Head;
                break;
            }
        }
        else if ( OP_CODE( OpLine1 ) == ZEND_JMPZNZ )
        {
            Offset = OP_JMPZNZ( OpLine1, Head );
            if ( Offset <= FindOffset )
            {
                if ( JmpOffsetPtr )
                    *JmpOffsetPtr = Offset;
                RetCode = OpLine1 - Head;
                break;
            }
        }
        OpLine1++;
    }

    return RetCode;
}

ULONG find_jmp_large_ex( PDUMP_STACK Stack, ULONG FindOffset, ULONG Start, ULONG End, ULONG *JmpOffsetPtr )
{
    ULONG RetCode;
    ULONG Offset;
    zend_op *Head;
    zend_op *OpLine1;
    zend_op *OpLine2;

    RetCode = INVALID_OP_OFFSET;
    Head = Stack->Head;
    OpLine1 = Head + Start;
    OpLine2 = Head + End;
    while ( OpLine1 < OpLine2 )
    {
        if ( OP_CODE( OpLine1 ) == ZEND_JMP )
        {
            Offset = OP_JMP( OpLine1, Head );
            if ( Offset > FindOffset )
            {
                if ( JmpOffsetPtr )
                    *JmpOffsetPtr = Offset;
                RetCode = OpLine1 - Head;
                break;
            }
        }
        else if ( OP_CODE( OpLine1 ) == ZEND_JMPZ || OP_CODE( OpLine1 ) == ZEND_JMPNZ )
        {
            Offset = OP_JMPX( OpLine1, Head );
            if ( Offset > FindOffset )
            {
                if ( JmpOffsetPtr )
                    *JmpOffsetPtr = Offset;
                RetCode = OpLine1 - Head;
                break;
            }
        }
        else if ( OP_CODE( OpLine1 ) == ZEND_JMPZNZ )
        {
            Offset = OP_JMPZNZ( OpLine1, Head );
            if ( Offset > FindOffset )
            {
                if ( JmpOffsetPtr )
                    *JmpOffsetPtr = Offset;
                RetCode = OpLine1 - Head;
                break;
            }
        }
        OpLine1++;
    }

    return RetCode;
}

ULONG find_jmp_small( PDUMP_STACK Stack, ULONG FindOffset, ULONG Start, ULONG End, ULONG *JmpOffsetPtr )
{
    ULONG RetCode;
    ULONG Top;
    ULONG Offset;
    ULONG JmpOffset;
    zend_op *Head;

    RetCode = INVALID_OP_OFFSET;
    Head = Stack->Head;

    Top = StackFindSmallAscU( &Stack->Jmp, End );
    while ( Top )
    {
        Offset = StackAtU( &Stack->Jmp, ( --Top ) );
        if ( Start <= Offset )
        {
            JmpOffset = OP_JMP( Head + Offset, Head );
            if ( JmpOffset <= FindOffset )
            {
                if ( JmpOffsetPtr )
                    *JmpOffsetPtr = JmpOffset;
                return Offset;
            }
        }
        else
        {
            break;
        }
    }

    Top = StackFindSmallAscU( &Stack->JmpX, End );
    while ( Top )
    {
        Offset = StackAtU( &Stack->JmpX, ( --Top ) );
        if ( Start <= Offset )
        {
            JmpOffset = OP_JMPX( Head + Offset, Head );
            if ( JmpOffset <= FindOffset )
            {
                if ( JmpOffsetPtr )
                    *JmpOffsetPtr = JmpOffset;
                return Offset;
            }
        }
        else
        {
            break;
        }
    }

    Top = StackFindSmallAscU( &Stack->JmpZnz, End );
    while ( Top )
    {
        Offset = StackAtU( &Stack->JmpZnz, ( --Top ) );
        if ( Start <= Offset )
        {
            JmpOffset = OP_JMPZNZ( Head + Offset, Head );
            if ( JmpOffset <= FindOffset )
            {
                if ( JmpOffsetPtr )
                    *JmpOffsetPtr = JmpOffset;
                return Offset;
            }
        }
        else
        {
            break;
        }
    }

    return RetCode;
}

ULONG find_jmp_large( PDUMP_STACK Stack, ULONG FindOffset, ULONG Start, ULONG End, ULONG *JmpOffsetPtr )
{
    ULONG RetCode;
    ULONG Top;
    ULONG Offset;
    ULONG JmpOffset;
    zend_op *Head;

    RetCode = INVALID_OP_OFFSET;
    Head = Stack->Head;

    Top = StackFindSmallAscU( &Stack->Jmp, End );
    while ( Top )
    {
        Offset = StackAtU( &Stack->Jmp, ( --Top ) );
        if ( Start <= Offset )
        {
            JmpOffset = OP_JMP( Head + Offset, Head );
            if ( JmpOffset > FindOffset )
            {
                if ( JmpOffsetPtr )
                    *JmpOffsetPtr = JmpOffset;
                return Offset;
            }
        }
        else
        {
            break;
        }
    }

    Top = StackFindSmallAscU( &Stack->JmpX, End );
    while ( Top )
    {
        Offset = StackAtU( &Stack->JmpX, ( --Top ) );
        if ( Start <= Offset )
        {
            JmpOffset = OP_JMPX( Head + Offset, Head );
            if ( JmpOffset > FindOffset )
            {
                if ( JmpOffsetPtr )
                    *JmpOffsetPtr = JmpOffset;
                return Offset;
            }
        }
        else
        {
            break;
        }
    }

    Top = StackFindSmallAscU( &Stack->JmpZnz, End );
    while ( Top )
    {
        Offset = StackAtU( &Stack->JmpZnz, ( --Top ) );
        if ( Start <= Offset )
        {
            JmpOffset = OP_JMPZNZ( Head + Offset, Head );
            if ( JmpOffset > FindOffset )
            {
                if ( JmpOffsetPtr )
                    *JmpOffsetPtr = JmpOffset;
                return Offset;
            }
        }
        else
        {
            break;
        }
    }

    Top = StackFindSmallAscU( &Stack->ReturnX, End );
    while ( Top )
    {
        Offset = StackAtU( &Stack->ReturnX, ( --Top ) );
        if ( Start <= Offset )
        {
            if ( JmpOffsetPtr )
                *JmpOffsetPtr = Stack->LastOffset - 1;
            return Offset;
        }
        else
        {
            break;
        }
    }

    return RetCode;
}

ULONG find_jmp_large_max( PDUMP_STACK Stack, ULONG FindOffset, ULONG Start, ULONG End, ULONG *JmpOffsetPtr )
{
    ULONG RetCode;
    ULONG Top;
    ULONG Offset;
    ULONG JmpOffset;
    ULONG JmpMaxOffset;
    zend_op *Head;

    RetCode = INVALID_OP_OFFSET;
    JmpMaxOffset = 0;
    Head = Stack->Head;

    Top = StackFindSmallAscU( &Stack->Jmp, End );
    while ( Top )
    {
        Offset = StackAtU( &Stack->Jmp, ( --Top ) );
        if ( Start <= Offset )
        {
            JmpOffset = OP_JMP( Head + Offset, Head );
            if ( JmpOffset > FindOffset )
            {
                if ( JmpOffset > JmpMaxOffset )
                {
                    JmpMaxOffset = JmpOffset;
                    RetCode = Offset;
                }
            }
        }
        else
        {
            break;
        }
    }

    Top = StackFindSmallAscU( &Stack->JmpX, End );
    while ( Top )
    {
        Offset = StackAtU( &Stack->JmpX, ( --Top ) );
        if ( Start <= Offset )
        {
            JmpOffset = OP_JMPX( Head + Offset, Head );
            if ( JmpOffset > FindOffset )
            {
                if ( JmpOffset > JmpMaxOffset )
                {
                    JmpMaxOffset = JmpOffset;
                    RetCode = Offset;
                }
            }
        }
        else
        {
            break;
        }
    }

    Top = StackFindSmallAscU( &Stack->JmpZnz, End );
    while ( Top )
    {
        Offset = StackAtU( &Stack->JmpZnz, ( --Top ) );
        if ( Start <= Offset )
        {
            JmpOffset = OP_JMPZNZ( Head + Offset, Head );
            if ( JmpOffset > FindOffset )
            {
                if ( JmpOffset > JmpMaxOffset )
                {
                    JmpMaxOffset = JmpOffset;
                    RetCode = Offset;
                }
            }
        }
        else
        {
            break;
        }
    }

    if ( RetCode != INVALID_OP_OFFSET && JmpOffsetPtr )
        *JmpOffsetPtr = JmpMaxOffset;

    return RetCode;
}

ULONG find_jmp_middle( PDUMP_STACK Stack, ULONG FindOffset, ULONG Start, ULONG End, ULONG *JmpOffsetPtr )
{
    ULONG RetCode;
    ULONG Top;
    ULONG Offset;
    ULONG JmpOffset;
    zend_op *Head;

    RetCode = INVALID_OP_OFFSET;
    Head = Stack->Head;

    Top = StackFindSmallAscU( &Stack->Jmp, FindOffset );
    while ( Top )
    {
        Offset = StackAtU( &Stack->Jmp, ( --Top ) );
        JmpOffset = OP_JMP( Head + Offset, Head );
        if ( Start < JmpOffset && JmpOffset < End )
        {
            if ( JmpOffsetPtr )
                *JmpOffsetPtr = JmpOffset;
            return Offset;
        }
    }

    Top = StackFindSmallAscU( &Stack->JmpX, FindOffset );
    while ( Top )
    {
        Offset = StackAtU( &Stack->JmpX, ( --Top ) );
        JmpOffset = OP_JMPX( Head + Offset, Head );
        if ( Start < JmpOffset && JmpOffset < End )
        {
            if ( JmpOffsetPtr )
                *JmpOffsetPtr = JmpOffset;
            return Offset;
        }
    }

    return RetCode;
}

ULONG find_jmp_offset( PDUMP_STACK Stack, ULONG FindOffset, ULONG Start, ULONG End )
{
    ULONG RetCode;
    ULONG Top;
    ULONG Offset;
    zend_op *Head;

    RetCode = INVALID_OP_OFFSET;
    Head = Stack->Head;

    Top = StackFindSmallAscU( &Stack->Jmp, End );
    while ( Top )
    {
        Offset = StackAtU( &Stack->Jmp, ( --Top ) );
        if ( Start <= Offset )
        {
            if ( OP_JMP( Head + Offset, Head ) == FindOffset )
                return Offset;
        }
        else
        {
            break;
        }
    }

    Top = StackFindSmallAscU( &Stack->JmpX, End );
    while ( Top )
    {
        Offset = StackAtU( &Stack->JmpX, ( --Top ) );
        if ( Start <= Offset )
        {
            if ( OP_JMPX( Head + Offset, Head ) == FindOffset )
                return Offset;
        }
        else
        {
            break;
        }
    }

    Top = StackFindSmallAscU( &Stack->JmpZnz, End );
    while ( Top )
    {
        Offset = StackAtU( &Stack->JmpZnz, ( --Top ) );
        if ( Start <= Offset )
        {
            if ( OP_JMPZNZ( Head + Offset, Head ) == FindOffset )
                return Offset;
        }
        else
        {
            break;
        }
    }

    return RetCode;
}

ULONG find_jmp_offset_last( PDUMP_STACK Stack, ULONG FindOffset, ULONG Start, ULONG End )
{
    ULONG RetCode;
    ULONG Top;
    ULONG Offset;
    zend_op *Head;

    RetCode = INVALID_OP_OFFSET;
    Head = Stack->Head;

    Top = StackFindLargeAscU( &Stack->Jmp, Start );
    if ( Top )
    {
        Top--;
        while ( Top < StackCountU( &Stack->Jmp ) )
        {
            Offset = StackAtU( &Stack->Jmp, Top );
            if ( OP_JMP( Head + Offset, Head ) == FindOffset )
                RetCode = Offset;
            Top++;
        }
    }

    if ( RetCode != INVALID_OP_OFFSET )
        Start = RetCode;

    Top = StackFindLargeAscU( &Stack->JmpX, Start );
    if ( Top )
    {
        Top--;
        while ( Top < StackCountU( &Stack->JmpX ) )
        {
            Offset = StackAtU( &Stack->JmpX, Top );
            if ( OP_JMPX( Head + Offset, Head ) == FindOffset )
                RetCode = Offset;
            Top++;
        }
    }

    if ( RetCode != INVALID_OP_OFFSET )
        Start = RetCode;

    Top = StackFindLargeAscU( &Stack->JmpZnz, Start );
    if ( Top )
    {
        Top--;
        while ( Top < StackCountU( &Stack->JmpZnz ) )
        {
            Offset = StackAtU( &Stack->JmpZnz, Top );
            if ( OP_JMPZNZ( Head + Offset, Head ) == FindOffset )
                RetCode = Offset;
            Top++;
        }
    }

    return RetCode;
}

ULONG scan_if_list_end( PDUMP_STACK Stack, ULONG StartOffset, ULONG Flags )
{
    ULONG Adjust;
    ULONG Offset;
    ULONG EndOffset;
    ULONG NextOffset;
    ULONG JmpOffset;
    ULONG NextJmpOffset;
    ULONG Top;
    ULONG Dummy;
    zend_uchar OpCode;
    zend_op *Head;
    zend_op *Start;
    zend_op *End;
    zend_op *OpLine;
    zend_op *OpLine1;
    KEY_VALUE OffsetMap;
    PBRK_CONT_LIST BrkContPtr;

    /* Default */
    Adjust = TRUE;
    /* Flags */
    Flags &= FLAGS_NEST;
    Head = Stack->Head;
    Start = Head + StartOffset;
    End = Stack->Tail;

    /* Default end offset */
    if ( OP_CODE( Start ) == ZEND_JMPZNZ )
        EndOffset = OP_JMPZNZ( Start, Head );
    else
        EndOffset = OP_JMPX( Start, Head );

    /* Seek for end offset */
    while ( Start < End )
    {
        /* Current offset */
        Offset = Start - Head;

        /* Next offset start */
        if ( OP_CODE( Start ) == ZEND_JMPZNZ )
            NextOffset = OP_JMPZNZ( Start, Head );
        else
            NextOffset = OP_JMPX( Start, Head );

        OpLine = Head + NextOffset - 1;
        if ( ( OP_CODE( OpLine ) == ZEND_JMPZ && OP_CODE( Start ) == ZEND_JMPNZ ||
            OP_CODE( OpLine ) == ZEND_JMPNZ && OP_CODE( Start ) == ZEND_JMPZ ) &&
                OP1_TYPE( OpLine ) == OP1_TYPE( Start ) && OP1_VAR( OpLine ) == OP1_VAR( Start ) )
        {
            /* May be optimized */
            OpLine--;
            NextOffset--;
        }
        OpCode = OP_CODE( OpLine );

        /* Deal with special case */
        if ( NextOffset < StartOffset )
        {
            /* if ( )Continue */
            BrkContPtr = GetContinue( Stack, NextOffset, Offset );
            if ( BrkContPtr )
            {
                /* Jump to loop start, update end offset */
                OpLine1 = Head + BrkContPtr->Break - 1;
                if ( OP_CODE( OpLine1 ) == ZEND_JMP && OP_JMP( OpLine1, Head ) == BrkContPtr->Continue )
                {
                    EndOffset = adjust_control_list_end( Stack, StartOffset, BrkContPtr->Break - 1 );
                    OffsetMap.Key = Offset;
                    OffsetMap.Value = EndOffset;
                    StackPushAscT( &Stack->OffsetMap, &OffsetMap );
                }
                else
                {
                    EndOffset = Offset + 1;
                }
            }
            else
            {
                /* BUG */
                if ( GET_GS_FLAGS( ) & GS_FLAGS_BUG )
                    dump_string_ex( Stack, _T( "//[BUG][%6d][%6d]jmpz to unknow<-\r\n" ), Offset, NextOffset );
                Adjust = FALSE;
            }
            break;
        }

        /* if ( )break */
        BrkContPtr = GetBreak( Stack, NextOffset, Offset );
        if ( BrkContPtr )
        {
            /* Jump to loop end, update end offset */
            EndOffset = Offset + 1;
            Adjust = FALSE;
            break;
        }
        else
        {
            Dummy = find_control_list_if_enclose( Stack, Offset, NextOffset, NULL );
            if ( Dummy != INVALID_OP_OFFSET )
            {
                NextOffset = Dummy;
                OffsetMap.Key = Offset;
                OffsetMap.Value = NextOffset;
                StackPushAscT( &Stack->OffsetMap, &OffsetMap );
                EndOffset = NextOffset;
                OpLine = Head + NextOffset - 1;
                OpCode = OP_CODE( OpLine );
            }
            else if ( OP_CODE( OpLine ) == ZEND_JMPZ && OP_CODE( OpLine - 1 ) == ZEND_CASE )
            {
                NextOffset -= 3;
                OffsetMap.Key = Offset;
                OffsetMap.Value = NextOffset;
                StackPushAscT( &Stack->OffsetMap, &OffsetMap );
                EndOffset = NextOffset;
                OpLine = Head + NextOffset - 1;
                OpCode = OP_CODE( OpLine );
            }
        }

        /* Deal with special case */
        if ( NextOffset >= Stack->LastOffset - 1 )
        {
            /* Jump to end */
            Dummy = find_control_list_if_enclose( Stack, Offset, NextOffset, NULL );
            if ( Dummy != INVALID_OP_OFFSET )
            {
                OffsetMap.Key = Offset;
                OffsetMap.Value = Dummy;
                StackPushAscT( &Stack->OffsetMap, &OffsetMap );
                EndOffset = Dummy;
                Adjust = FALSE;
            }
            else
            {
                EndOffset = NextOffset;
            }
            break;
        }

        if ( OpCode == ZEND_JMP )
        {
            /* if ( ){} [ else{} ] */
            JmpOffset = OP_JMP( OpLine, Head );
        }
        else if ( OpCode == ZEND_JMPZNZ )
        {
            /* if ( ){} [ else{} ] */
            JmpOffset = OP_JMPZNZ( OpLine, Head );
        }
        else if ( OpCode == ZEND_RETURN || OpCode == ZEND_EXIT )
        {
            /* Set flags */
            Flags |= FLAGS_RETURN;
            /* if ( ){} [ else{} ] */
            if ( NextOffset == Offset + 2 )
                JmpOffset = NextOffset;
            else if ( OpCode == ZEND_RETURN && scan_if_default_return( Stack, NextOffset - 1 ) || Flags & FLAGS_NEST )
                JmpOffset = Stack->LastOffset - 1;
            else if ( find_jmp_large( Stack, NextOffset, Offset, NextOffset, &Dummy ) != INVALID_OP_OFFSET )
                JmpOffset = Dummy;
            else if ( StackFindLargeEqualAscU( &Stack->Declare, NextOffset ) )
                JmpOffset = Stack->LastOffset - 1;
            else
                JmpOffset = NextOffset;
        }
        else
        {
            if ( OpCode == ZEND_JMPZ || OpCode == ZEND_JMPNZ )
                JmpOffset = OP_JMPX( OpLine, Head );
            else
                JmpOffset = EndOffset;

            if ( JmpOffset <= EndOffset )
            {
                /* if ( ){} */
                Dummy = find_control_list_if_enclose( Stack, Offset, NextOffset, NULL );
                if ( Dummy != INVALID_OP_OFFSET )
                {
                    OffsetMap.Key = Offset;
                    OffsetMap.Value = Dummy;
                    StackPushAscT( &Stack->OffsetMap, &OffsetMap );
                    EndOffset = Dummy;
                    Adjust = FALSE;
                }
                else
                {
                    EndOffset = NextOffset;
                }
                break;
            }
        }

        if ( JmpOffset <= StartOffset )
        {
            /* Continue ? if-else ? */
            BrkContPtr = GetContinue( Stack, JmpOffset, Offset );
            if ( BrkContPtr )
            {
                JmpOffset = BrkContPtr->Break;
            }
            else
            {
                /* BUG */
                if ( GET_GS_FLAGS( ) & GS_FLAGS_BUG )
                    dump_string_ex( Stack, _T( "//[BUG][%6d][%6d]if jump to unknow^\r\n" ), StartOffset, JmpOffset );
                Adjust = FALSE;
                break;
            }
        }
        else if ( JmpOffset > EndOffset )
        {
            BrkContPtr = GetBreak( Stack, JmpOffset, Offset );
            if ( BrkContPtr )
            {
                Dummy = adjust_control_list_end( Stack, StartOffset, JmpOffset );
                if ( Dummy != JmpOffset )
                {
                    if ( ( BrkContPtr->Flags & DS_FLAGS_MASK ) == DS_FLAGS_SWITCH )
                    {
                        /* See if break */
                        if ( OP_CODE( Head + Dummy ) != ZEND_JMP || OP_JMP( Head + Dummy, Head ) >= NextOffset )
                        {
                            while ( OP_CODE( Head + Dummy ) == ZEND_JMP && OP_JMP( Head + Dummy, Head ) != JmpOffset )
                                Dummy--;

                            OffsetMap.Key = NextOffset - 1;
                            OffsetMap.Value = Dummy;
                            StackPushAscT( &Stack->OffsetMap, &OffsetMap );
                        }
                    }
                    JmpOffset = Dummy;
                }
            }
            else if ( ( Flags & FLAGS_NEST_RETURN ) != FLAGS_NEST_RETURN )
            {
                Dummy = find_control_list_if_enclose( Stack, Offset, JmpOffset, NULL );
                if ( Dummy != INVALID_OP_OFFSET )
                {
                    OffsetMap.Key = NextOffset - 1;
                    OffsetMap.Value = Dummy;
                    StackPushAscT( &Stack->OffsetMap, &OffsetMap );
                    JmpOffset = Dummy;
                }
                else if ( JmpOffset > 2 && OP_CODE( Head + JmpOffset - 1 ) == ZEND_JMPZ && OP_CODE( Head + JmpOffset - 2 ) == ZEND_CASE )
                {
                    OffsetMap.Key = NextOffset - 1;
                    OffsetMap.Value = NextOffset;
                    StackPushAscT( &Stack->OffsetMap, &OffsetMap );
                    JmpOffset = NextOffset;
                }
                else if ( JmpOffset == Stack->LastOffset - 1 )
                {
                    /* if ( x ) { ... return } else { } */
                    Dummy = adjust_control_list_end( Stack, StartOffset, JmpOffset );
                    if ( Dummy != JmpOffset )
                    {
                        OpLine1 = Head + Dummy;
                        while ( OpLine1 > Head )
                        {
                            if ( OP_CODE( OpLine1 ) == ZEND_JMP && OP_JMP( OpLine1, Head ) > EndOffset )
                            {
                                Dummy--;
                                OpLine1--;
                            }
                            else
                            {
                                Dummy++;
                                break;
                            }
                        }
                        JmpOffset = Dummy;
                    }
                }
            }
        }
        else if ( JmpOffset == NextOffset )
        {
            Dummy = find_control_list_if_enclose( Stack, Offset, JmpOffset, NULL );
            if ( Dummy != INVALID_OP_OFFSET )
            {
                OffsetMap.Key = NextOffset - 1;
                OffsetMap.Value = Dummy;
                StackPushAscT( &Stack->OffsetMap, &OffsetMap );
                EndOffset = Dummy;
                Adjust = FALSE;
            }
            else
            {
                EndOffset = NextOffset;
            }
            break;
        }
        else if ( StartOffset < JmpOffset && JmpOffset < NextOffset )
        {
            /* May be loop */
            BrkContPtr = GetContinue( Stack, JmpOffset, ( JmpOffset + NextOffset + 1 ) >> 1 );
            if ( BrkContPtr )
            {
                if ( BrkContPtr->Break >= NextOffset )
                {
                    Stack->Argument = BrkContPtr->Break;
                    JmpOffset = get_real_break_offset( Stack, JmpOffset );
                    JmpOffset = adjust_control_list_end( Stack, Offset, JmpOffset );
                }
                else
                {
                    OpLine1 = Head + BrkContPtr->Offset;
                    if ( ( BrkContPtr->Flags & DS_FLAGS_MASK ) == DS_FLAGS_WHILE )
                        JmpOffset = OP_JMPX( OpLine1, Head );
                    else
                        JmpOffset = OP_JMPZNZ( OpLine1 - 1, Head );
                }
                OffsetMap.Key = NextOffset - 1;
                OffsetMap.Value = JmpOffset;
                StackPushAscT( &Stack->OffsetMap, &OffsetMap );
            }
            else if ( JmpOffset == NextOffset - 1 )
            {
                /* while ( 1 ) */
                break;
            }
            else
            {
                /* while() { if () { while() {} }else{} } */
                Top = StackFindLargeAscU( &Stack->Output, JmpOffset );
                if ( Top )
                {
                    Dummy = StackAtU( &Stack->Output, Top - 1 );
                    Top = StackFindSmallAscU( &Stack->JmpX, Dummy );
                    if ( Top )
                    {
                        JmpOffset = OP_JMPX( Head + StackAtU( &Stack->JmpX, Top - 1 ), Head );
                        BrkContPtr = GetContinue( Stack, JmpOffset, Offset );
                        if ( BrkContPtr )
                            JmpOffset = BrkContPtr->Break;
                    }
                }
                if ( !Top )
                {
                    /* BUG */
                    if ( GET_GS_FLAGS( ) & GS_FLAGS_BUG )
                        dump_string_ex( Stack, _T( "//[BUG][%6d][%6d]if jump to unknow<>\r\n" ), StartOffset, JmpOffset );
                    Adjust = FALSE;
                    break;
                }
            }
        }
        else
        {
            /* BUG */
            if ( GET_GS_FLAGS( ) & GS_FLAGS_BUG )
                dump_string_ex( Stack, _T( "//[WARNING][%6d][%6d]if jump to unknow<>\r\n" ), StartOffset, JmpOffset );
        }

        Top = StackFindLargeEqualAscU( &Stack->JmpX, NextOffset );
        if ( !Top )
        {
            /* No more */
            if ( NextOffset < JmpOffset )
                EndOffset = JmpOffset;
            else
                EndOffset = NextOffset;
            break;
        }

        NextJmpOffset = StackAtU( &Stack->JmpX, Top - 1 );
        if ( OP_CODE( Head + NextJmpOffset - 1 ) == ZEND_CASE )
        {
            /* No more */
            if ( NextOffset < JmpOffset )
                EndOffset = JmpOffset;
            else
                EndOffset = NextOffset;
            break;
        }

        if ( NextJmpOffset <= JmpOffset )
        {
            if ( JmpOffset > EndOffset )
            {
                /* See if next else if */
                Dummy = scan_prev_output( Stack, NextOffset, NextJmpOffset );
                if ( Dummy == NextOffset - 1 )
                {
                    /* Update end offset */
                    EndOffset = adjust_control_list_end( Stack, StartOffset, JmpOffset );
                    /* Scan next if logic end */
                    Dummy = scan_if_logic( Stack, Head + NextJmpOffset );
                    if ( Dummy != INVALID_OP_OFFSET )
                        NextJmpOffset = Dummy;
                    /* Save next else if offset */
                    StackPushU( &Stack->If, NextJmpOffset );
                    /* Save stack top position */
                    Top = StackCountU( &Stack->If );
                    /* Scan next else if end offset */
                    Dummy = scan_if_list_end( Stack, NextJmpOffset, FLAGS_NEST );
                    if ( Dummy == EndOffset )
                    {
                        /* Ok */
                    }
                    else if ( Dummy == EndOffset - 1 && OP_CODE( Head + Dummy ) == ZEND_JMP )
                    {
                        EndOffset--;
                    }
                    else
                    {
                        StackSetTopU( &Stack->If, Top > 1 ? Top - 2 : 0 );
                    }
                    /* Skip adjust */
                    Adjust = FALSE;
                }
                else
                {
                    /* No else[ if ] */
                    EndOffset = JmpOffset;
                }
                break;
            }
            else
            {
                /* else if ( ){} */
                Dummy = scan_if_logic( Stack, Head + NextJmpOffset );
                if ( Dummy != INVALID_OP_OFFSET )
                    NextJmpOffset = Dummy;
                StackPushU( &Stack->If, NextJmpOffset );
                Start = Head + NextJmpOffset;
            }
        }
        else
        {
            /* if ( ){}[ else{} ] */
            if ( JmpOffset > EndOffset )
                EndOffset = JmpOffset;
            break;
        }
    }

    if ( Adjust )
        return adjust_control_list_end( Stack, StartOffset, EndOffset );
    else
        return EndOffset;
}

ULONG scan_if_list( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG Flags;
    ULONG Type;
    ULONG StartOffset;
    ULONG EndOffset;
    ULONG Offset;
    ULONG NextOffset;
    ULONG JmpOffset;
    ULONG Dummy;
    zend_uchar OpCode;
    zend_op *Head;
    zend_op *Start;
    zend_op *End;
    zend_op *OpLine;
    zend_op *OpLine1;
    COMMON_CONTROL_ENTRY Entry;
    COMMON_CONTROL_ENTRY Entry1;

    /* Re-init */
    StackReinitU( &Stack->If );

    RetCode = 0;
    Flags = 0;
    Head = Stack->Head;
    Offset = Stack->Offset;
    StartOffset = Stack->Offset;
    Start = Stack->OpLine;

    EndOffset = scan_if_list_end( Stack, StartOffset, 0 );
    End = Head + EndOffset;

    while ( Start < End )
    {
        /* Skip JmpX */
        StackPushAscU( &Stack->Skip, Offset );

        /* Layer */
        RetCode++;

        if ( OP_CODE( Start ) == ZEND_JMPZNZ )
            NextOffset = OP_JMPZNZ( Start, Head );
        else
            NextOffset = OP_JMPX( Start, Head );

        if ( Flags == DS_FLAGS_IF )
            Flags = DS_FLAGS_ELSEIF;
        else if ( Flags == 0 )
            Flags = DS_FLAGS_IF;

        if ( NextOffset == Offset )
            break;

        OpLine = Head + NextOffset - 1;
        if ( ( OP_CODE( OpLine ) == ZEND_JMPZ && OP_CODE( Start ) == ZEND_JMPNZ ||
            OP_CODE( OpLine ) == ZEND_JMPNZ && OP_CODE( Start ) == ZEND_JMPZ ) &&
                OP1_TYPE( OpLine ) == OP1_TYPE( Start ) && OP1_VAR( OpLine ) == OP1_VAR( Start ) )
        {
            /* May be Optimized */
            OpLine--;
            NextOffset--;
            OpLine1 = Head + EndOffset;
            if ( OP_CODE( OpLine1 ) == OP_CODE( Start ) )
            {
                Dummy = scan_if_logic( Stack, Head + EndOffset );
                if ( Dummy != INVALID_OP_OFFSET )
                    if ( Dummy == NextOffset - 1 )
                        NextOffset = EndOffset;
            }
        }

        Dummy = StackFindAscT( &Stack->OffsetMap, ( PKEY_VALUE )&Offset );
        if ( Dummy )
        {
            NextOffset = ( ( PKEY_VALUE )StackAtT( &Stack->OffsetMap, Dummy - 1 ) )->Value;
            OpLine = Head + NextOffset - 1;
        }
        OpCode = OP_CODE( OpLine );

        if ( EndOffset == Offset + 1 )
        {
            if ( NextOffset == EndOffset )
            {
                /* if ( ){} */
                Type = 0;
                JmpOffset = EndOffset;
            }
            else if ( NextOffset < StartOffset )
            {
                /* if ( )continue */
                Entry1.Flags = Flags;
                Entry1.Type = DS_TYPE_CONT;
                Entry1.Start = Offset;
                Entry1.End = EndOffset;
                insert_control_list( Stack, Offset, &Entry1 );

                Entry1.Flags = DS_FLAGS_IF_END | DS_FLAGS_END;
                Entry1.Start = StartOffset;
                Entry1.End = EndOffset;
                insert_control_list( Stack, EndOffset, &Entry1 );
                break;
            }
            else
            {
                /* if ( )break */
                Entry1.Flags = Flags;
                Entry1.Type = DS_TYPE_BRK;
                Entry1.Start = Offset;
                Entry1.End = EndOffset;
                insert_control_list( Stack, Offset, &Entry1 );

                Entry1.Flags = DS_FLAGS_IF_END | DS_FLAGS_END;
                Entry1.Start = StartOffset;
                Entry1.End = EndOffset;
                insert_control_list( Stack, EndOffset, &Entry1 );
                break;
            }
        }
        else if ( NextOffset > EndOffset )
        {
            Type = DS_TYPE_BRK;
            /* Scan suitable start place */
            Dummy = adjust_control_list_start( Stack, StartOffset, NextOffset );
            if ( Dummy != StartOffset )
                Dummy++;

            /* do {} while ( 0 ) */
            Entry1.Flags = DS_FLAGS_DO;
            Entry1.Type = DS_TYPE_TOP;
            Entry1.Start = Dummy;
            Entry1.End = NextOffset;
            insert_control_list( Stack, Dummy, &Entry1 );

            Entry1.Flags = DS_FLAGS_DO_WHILE_FALSE | DS_FLAGS_END;
            Entry1.Type = DS_TYPE_TOP;
            insert_control_list( Stack, NextOffset, &Entry1 );

            /* Insert to continue/break list */
            insert_cont_brk_list( Stack, NextOffset, NextOffset, Dummy, NextOffset, DS_FLAGS_DO_WHILE_FALSE );

            NextOffset = Offset + 1;
            OpCode = ZEND_JMP;
            JmpOffset = Offset + 1;
        }
        else
        {
            Type = 0;
            /* See if map */
            Dummy = NextOffset - 1;
            Dummy = StackFindReverseT( &Stack->OffsetMap, ( PKEY_VALUE )&Dummy );
            if ( Dummy )
                JmpOffset = ( ( PKEY_VALUE )StackAtT( &Stack->OffsetMap, Dummy - 1 ) )->Value;
            else
                JmpOffset = EndOffset;

            if ( OpCode == ZEND_JMP )
            {
                if ( !Dummy )
                    JmpOffset = OP_JMP( OpLine, Head );

                /* Skip */
                StackPushAscU( &Stack->Skip, NextOffset - 1 );
            }
            else if ( OpCode == ZEND_JMPZNZ )
            {
                /* if( x )break; */
                Entry1.Flags = DS_FLAGS_IF;
                Entry1.Type = DS_TYPE_SKIP_REVERSE | DS_TYPE_BRK;
                Entry1.Start = NextOffset - 1;
                Entry1.End = NextOffset - 1;
                insert_control_list( Stack, NextOffset - 1, &Entry1 );

                Entry1.Flags = DS_FLAGS_IF_END | DS_FLAGS_END;
                insert_control_list( Stack, NextOffset, &Entry1 );

                if ( !Dummy )
                    JmpOffset = OP_EX_VALUE( OpLine );

                /* Skip */
                StackPushAscU( &Stack->Skip, NextOffset - 1 );
            }
            else if ( OpCode == ZEND_RETURN && scan_if_default_return( Stack, NextOffset - 1 ) && NextOffset != Offset + 2 )
            {
                if ( !Dummy )
                    JmpOffset = EndOffset;

                /* Skip */
                StackPushAscU( &Stack->Skip, NextOffset - 1 );
            }
            else if ( OpCode == ZEND_JMPZ || OpCode == ZEND_JMPNZ )
            {
                JmpOffset = OP_JMPX( OpLine, Head );
            }
        }

        Entry.Flags = Flags;
        Entry.Type = Type;
        if ( JmpOffset > EndOffset )
        {
            if ( GetBreak( Stack, JmpOffset, Offset ) )
            {
                /* break; */
                Entry1.Flags = DS_FLAGS_BRK;
                Entry1.Type = DS_TYPE_NOINDENT;
                Entry1.Start = NextOffset - 1;
                Entry1.End = NextOffset - 1;
                insert_control_list( Stack, NextOffset - 1, &Entry1 );
            }
            else if ( JmpOffset >= EndOffset + 2 && OP_CODE( Head + JmpOffset - 2 ) == ZEND_CASE )
            {
                /* FIX */
            }
            else
            {
                /* Scan suitable start place */
                Dummy = adjust_control_list_start( Stack, StartOffset, JmpOffset );

                /* do {} while ( 0 ) */
                Entry1.Flags = DS_FLAGS_DO;
                Entry1.Type = 0;
                Entry1.Start = Dummy + 1;
                Entry1.End = JmpOffset;
                insert_control_list( Stack, Dummy + 1, &Entry1 );

                Entry1.Flags = DS_FLAGS_DO_WHILE_FALSE | DS_FLAGS_END;
                Entry1.Type = DS_TYPE_TOP;
                insert_control_list( Stack, JmpOffset, &Entry1 );

                /* Insert to continue/break list */
                insert_cont_brk_list( Stack, JmpOffset, JmpOffset, Dummy, JmpOffset, DS_FLAGS_DO_WHILE_FALSE );

                if ( OpCode == ZEND_JMPZNZ )
                {
                    /* if ( )break; */
                    Entry1.Flags = DS_FLAGS_IF;
                    Entry1.Type = DS_TYPE_BRK | DS_TYPE_SKIP_REVERSE;
                }
                else
                {
                    /* break; */
                    Entry1.Flags = DS_FLAGS_BRK;
                    Entry1.Type = DS_TYPE_NOINDENT | DS_TYPE_SKIP_REVERSE;
                }
                Entry1.Start = NextOffset - 1;
                Entry1.End = NextOffset - 1;
                insert_control_list( Stack, NextOffset - 1, &Entry1 );
            }
        }

        /* Update offset */
        Stack->Offset = Offset;
        if ( StackPopBottomU( &Stack->If, &Dummy ) )
        {
            /* if ( ){} else if ( ){} */
            Entry.Start = Offset;
            Entry.End = Dummy;
            insert_control_list( Stack, Offset, &Entry );

            Offset = Dummy;
            Start = Head + Offset;
            if ( Offset == EndOffset )
            {
                Entry.Flags = DS_FLAGS_IF_END | DS_FLAGS_END;
                Entry.Start = StartOffset;
                Entry.End = EndOffset;
                insert_control_list( Stack, EndOffset, &Entry );
            }
        }
        else
        {
            Entry.Start = Offset;
            Entry.End = NextOffset;
            insert_control_list( Stack, Offset, &Entry );

            if ( StartOffset < NextOffset && NextOffset < EndOffset )
            {
                /* if ( ){} else {} */
                Entry.Flags = DS_FLAGS_ELSE;
                Entry.Start = NextOffset;
                Entry.End = EndOffset;
                insert_control_list( Stack, NextOffset, &Entry );
            }

            Entry.Flags = DS_FLAGS_IF_END | DS_FLAGS_END;
            Entry.Start = StartOffset;
            Entry.End = EndOffset;
            insert_control_list( Stack, EndOffset, &Entry );
            break;
        }
    }

    /* Restore offset */
    Stack->Offset = StartOffset;

    return RetCode;
}

ULONG find_logic_op( ULONG StartOffset, ULONG EndOffset )
{
    ULONG Offset;
    ULONG NextOffset;
    zend_op *Head;
    zend_op *Start;
    zend_op *End;
    PDUMP_STACK Stack;

    Stack = GET_GS_STACK( );
    Head = Stack->Head;
    Start = Head + StartOffset;
    End = Head + EndOffset;
    Offset = StartOffset;

    while ( Start < End )
    {
        if ( OP_CODE( Start ) == ZEND_JMPZ || OP_CODE( Start ) == ZEND_JMPNZ )
        {
            Offset = Start - Head;
            NextOffset = OP_JMPX( Start, Head );
            if ( NextOffset > EndOffset || NextOffset <= StartOffset )
                break;

            if ( Head + NextOffset - 1 == Start )
                Start++;
            else
                Start = Head + NextOffset - 1;
        }
        else
            Start++;
    }

    return Offset;
}

ULONG scan_logic_order( ULONG StartOffset, ULONG EndOffset )
{
    ULONG Flags;
    ULONG BoundTop;
    ULONG NextOffset;
    ULONG BoundOffset;
    ULONG LogicEndOffset;
    ULONG LogicEndJmp;
    ULONG LogicEndType;
    ULONG OpType;
    ULONG OpType1;
    ULONG OpType2;
    zend_op *Head;
    zend_op *Bound;
    PDUMP_STACK Stack;
    PVARIABLE_ENTRY Var;
    KEY_VALUE PostOpType;
    LOGIC_PREFIX_LIST LogicPrefix;

    Flags = GET_GS_LAST_OP( );
    Stack = GET_GS_STACK( );
    Head = Stack->Head;
    if ( StartOffset >= EndOffset )
    {
        BoundOffset = EndOffset;
        Bound = Head + BoundOffset;
        NextOffset = OP_JMPX( Bound, Head );
        if ( NextOffset <= Stack->Offset || NextOffset > Stack->LogicEndOffset )
        {
            LogicEndOffset = Stack->LogicEndOffset;
            LogicEndJmp = Stack->LogicEndJmp;
            LogicEndType = Stack->LogicEndType;
        }
        else
        {
            LogicEndOffset = NextOffset - 1;
            LogicEndJmp = OP_JMPX( Head + LogicEndOffset, Head );
            LogicEndType = OP_CODE( Head + LogicEndOffset );
        }
    }
    else
    {
        BoundOffset = find_logic_op( StartOffset, EndOffset );
        Bound = Head + BoundOffset;
        LogicEndOffset = EndOffset;
        LogicEndJmp = OP_JMPX( Head + LogicEndOffset, Head );
        LogicEndType = OP_CODE( Head + LogicEndOffset );
    }

    /* See if break or continue statement */
    if ( LogicEndJmp != Stack->LogicEndJmp )
    {
        if ( LogicEndJmp > StartOffset )
        {
            if ( GetBreak( Stack, LogicEndJmp, StartOffset ) )
                Flags |= DS_IFLAGS_BRK;
        }
        else
        {
            if ( GetContinue( Stack, LogicEndJmp, StartOffset ) )
                Flags |= DS_IFLAGS_CONT;
            else
                Flags |= DS_IFLAGS_LOOP;
        }
    }

    /* See if reverse op type */
    Bound = Head + BoundOffset;
    if ( OP_CODE( Bound ) == ZEND_JMPZ )
    {
        OpType = DS_IFLAGS_OT_BOOL_AND;
        NextOffset = OP_JMPX( Bound, Head );
        if ( Flags & DS_IFLAGS_BRK )
        {
            if ( NextOffset == LogicEndJmp )
            {
                Flags |= DS_IFLAGS_BOOL_NOT;
                StackPushAscU( &Stack->LogicOpReverse, BoundOffset );
                OpType = DS_IFLAGS_OT_BOOL_OR;
            }
        }
        else if ( Flags & DS_IFLAGS_CONT )
        {
            if ( NextOffset == LogicEndJmp )
            {
                Flags |= DS_IFLAGS_BOOL_NOT;
                StackPushAscU( &Stack->LogicOpReverse, BoundOffset );
                OpType = DS_IFLAGS_OT_BOOL_OR;
            }
        }
        else if ( Flags & DS_IFLAGS_LOOP && NextOffset == LogicEndJmp )
        {
            Flags |= DS_IFLAGS_BOOL_NOT;
            StackPushAscU( &Stack->LogicOpReverse, BoundOffset );
            OpType = DS_IFLAGS_OT_BOOL_OR;
        }
        else if ( LogicEndType == ZEND_JMPZ && LogicEndJmp > StartOffset && NextOffset - 1 == LogicEndOffset ||
            LogicEndType == ZEND_JMPZ && LogicEndJmp < StartOffset && NextOffset == LogicEndJmp ||
            LogicEndType == ZEND_JMPNZ && LogicEndJmp > StartOffset && NextOffset - 1 == LogicEndOffset ||
            LogicEndType == ZEND_JMPNZ && LogicEndJmp < StartOffset && NextOffset == LogicEndJmp )
        {
            Flags |= DS_IFLAGS_BOOL_NOT;
            StackPushAscU( &Stack->LogicOpReverse, BoundOffset );
            OpType = DS_IFLAGS_OT_BOOL_OR;
        }
    }
    else if ( OP_CODE( Bound ) == ZEND_JMPNZ )
    {
        OpType = DS_IFLAGS_OT_BOOL_OR;
        NextOffset = OP_JMPX( Bound, Head );
        if ( Flags & DS_IFLAGS_BRK )
        {
            if ( NextOffset != LogicEndJmp )
            {
                Flags |= DS_IFLAGS_BOOL_NOT;
                StackPushAscU( &Stack->LogicOpReverse, BoundOffset );
                OpType = DS_IFLAGS_OT_BOOL_AND;
            }
        }
        else if ( Flags & DS_IFLAGS_CONT )
        {
            if ( NextOffset != LogicEndJmp )
            {
                Flags |= DS_IFLAGS_BOOL_NOT;
                StackPushAscU( &Stack->LogicOpReverse, BoundOffset );
                OpType = DS_IFLAGS_OT_BOOL_AND;
            }
        }
        else if ( Flags & DS_IFLAGS_LOOP && NextOffset == LogicEndOffset + 1 )
        {
            Flags |= DS_IFLAGS_BOOL_NOT;
            StackPushAscU( &Stack->LogicOpReverse, BoundOffset );
            OpType = DS_IFLAGS_OT_BOOL_AND;
        }
        else if ( LogicEndType == ZEND_JMPZ && LogicEndJmp > StartOffset && NextOffset == LogicEndJmp ||
            LogicEndType == ZEND_JMPZ && LogicEndJmp < StartOffset && NextOffset - 1 == LogicEndOffset ||
            LogicEndType == ZEND_JMPNZ && LogicEndJmp > StartOffset && NextOffset == LogicEndJmp ||
            LogicEndType == ZEND_JMPNZ && LogicEndJmp < StartOffset && NextOffset - 1 == LogicEndOffset )
        {
            Flags |= DS_IFLAGS_BOOL_NOT;
            StackPushAscU( &Stack->LogicOpReverse, BoundOffset );
            OpType = DS_IFLAGS_OT_BOOL_AND;
        }
    }
    else
        OpType = DS_IFLAGS_OT_MAX;

    /* Final expression */
    if ( StartOffset >= EndOffset )
    {
        if ( StartOffset <= Stack->Offset )
        {
            Var = FindVariableById( OP1_TYPE( Bound ), OP1_VAR( Bound ) );
            if ( Var )
                return ( Var->Flags & DS_IFLAGS_OT_MASK ) | ( Flags & ~DS_IFLAGS_OT_MASK );
        }
        PostOpType.Key = StartOffset;
        if ( Flags & DS_IFLAGS_BOOL_NOT )
            PostOpType.Value = DS_IFLAGS_BOOL_NOT | DS_IFLAGS_OT_BOOL_NOT;
        else
            PostOpType.Value = Flags & DS_IFLAGS_OT_MASK;
        StackPushAscT( &Stack->PostOpTypeList, &PostOpType );

        return DS_IFLAGS_OT_MAX;
    }

    /* Bound index */
    BoundTop = StackFindAscU( &Stack->LogicList, BoundOffset );

    /* Set last op for final expression */
    SET_GS_LAST_OP( OpType | ( Flags & ( DS_IFLAGS_BRK | DS_IFLAGS_CONT | DS_IFLAGS_LOOP ) ) );

    /* Split into two part */
    if ( BoundOffset == StartOffset )
    {
        /* ( 1 -> n ) => ( 1 -> 1 ) + ( 2 -> n ) */
        NextOffset = BoundOffset;
        BoundOffset = StackAtU( &Stack->LogicList, BoundTop );
    }
    else
    {
        /* ( 1 -> n ) => ( 1 -> k ) + ( k + 1 -> n ) */
        NextOffset = BoundOffset;
        BoundOffset = StackAtU( &Stack->LogicList, BoundTop );
    }

    /* Scan two part respectively */
    OpType1 = scan_logic_order( StartOffset, NextOffset );
    OpType2 = scan_logic_order( BoundOffset, EndOffset );

    if ( OpType1 & DS_IFLAGS_BOOL_NOT )
    {
        /* expression1 => !( expression1 ) or !expression1 */
        if ( ( OpType1 & DS_IFLAGS_OT_MASK ) < DS_IFLAGS_OT_BOOL_NOT )
        {
            /* expression1 => ( expression1 ) */
            LogicPrefix.Offset = StartOffset;
            LogicPrefix.Flags = 0;
            StackPushAscT( &Stack->LogicPrefix, &LogicPrefix );
            StackPushAscU( &Stack->LogicPostfix, NextOffset );
        }

        /* expression1 => !expression1 */
        LogicPrefix.Offset = StartOffset;
        LogicPrefix.Flags = DS_IFLAGS_BOOL_NOT;
        StackPushAscT( &Stack->LogicPrefix, &LogicPrefix );
        OpType1 = DS_IFLAGS_OT_BOOL_NOT;
    }

    if ( OpType2 & DS_IFLAGS_BOOL_NOT )
    {
        /* expression2 => !( expression2 ) or !expression2 */
        if ( ( OpType2 & DS_IFLAGS_OT_MASK ) < DS_IFLAGS_OT_BOOL_NOT )
        {
            /* expression2 => ( expression2 ) */
            LogicPrefix.Offset = BoundOffset;
            LogicPrefix.Flags = 0;
            StackPushAscT( &Stack->LogicPrefix, &LogicPrefix );
            StackPushAscU( &Stack->LogicPostfix, EndOffset );
        }

        /* expression2 => !expression2 */
        LogicPrefix.Offset = BoundOffset;
        LogicPrefix.Flags = DS_IFLAGS_BOOL_NOT;
        StackPushAscT( &Stack->LogicPrefix, &LogicPrefix );
        OpType1 = DS_IFLAGS_OT_BOOL_NOT;
    }

    if ( OpType1 < OpType )
    {
        /* expression1 => ( expression1 ) */
        LogicPrefix.Offset = StartOffset;
        LogicPrefix.Flags = 0;
        StackPushAscT( &Stack->LogicPrefix, &LogicPrefix );
        StackPushAscU( &Stack->LogicPostfix, NextOffset );
    }

    if ( OpType2 < OpType )
    {
        /* expression2 => ( expression2 ) */
        LogicPrefix.Offset = BoundOffset;
        LogicPrefix.Flags = 0;
        StackPushAscT( &Stack->LogicPrefix, &LogicPrefix );
        StackPushAscU( &Stack->LogicPostfix, EndOffset );
    }

    return OpType;
}

ULONG scan_logic_order_stub( PDUMP_STACK Stack, ULONG StartOffset, ULONG EndOffset )
{
    zend_op *Head;
    zend_op *Start;
    zend_op *End;

    Head = Stack->Head;
    Start = Head + StartOffset;
    End = Head + EndOffset + 1;

    while ( Start < End )
    {
        if ( OP_CODE( Start ) == ZEND_JMPZ || OP_CODE( Start ) == ZEND_JMPNZ )
            StackPushAscU( &Stack->LogicList, Start - Head );
        Start++;
    }
    StackPushAscU( &Stack->LogicList, EndOffset );

    return scan_logic_order( StartOffset, EndOffset );
}

/*
///////////////////////////////////////////////////////////////////////////////
// dump_assign_function
///////////////////////////////////////////////////////////////////////////////
*/
ULONG FASTCALL dump_assign_function( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG Index;
    ULONG OpType;
    ULONG Length;
    ULONG Dummy;
    zend_op *OpLine;
    zend_op *OpLine1;
    zend_op LocalOpLine;
    zval *Value;
    zval **ValuePtr;
    PVARIABLE_ENTRY Var;
    PVARIABLE_ENTRY Var1;
    TCHAR *String;
    TCHAR *String1;
    TCHAR *String2;
    ULONG BufferSize;
    ULONG BufferCount;
    TCHAR *Buffer;

    RetCode = 0;
    OpLine = Stack->OpLine;
    OpLine1 = OpLine + 1;
    do
    {
        Index = 0;
        Length = 0;
        if ( OP_CODE( OpLine1 ) == ZEND_OP_DATA )
        {
            if ( TEST_OP1_CONST( OpLine ) )
            {
                break;
            }
            else if ( TEST_OP1_ALL_VAR( OpLine ) )
            {
                Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
                if ( Var == NULL )
                    break;

                StackPushS( &Stack->LargeBuffer, Var->Expr, Var->ExprLength );
                StackPushS( &Stack->LargeBuffer, _T( "[" ), 1 );
                if ( TEST_OP2_CONST( OpLine ) )
                {
                    make_printable_zval_url_ex( OP2_VAL( OpLine ), &Stack->Buffer2, _T( '\'' ) );
                    Dummy = StackPopAllS( &Stack->Buffer2, &String1 );
                }
                else if ( TEST_OP2_ALL_VAR( OpLine ) )
                {
                    Var1 = FindVariableById( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
                    if ( Var1 == NULL )
                        break;

                    String1 = Var1->Expr;
                    Dummy = Var1->ExprLength;
                }
                else
                {
                    break;
                }
                Dummy = StackPushS( &Stack->LargeBuffer, String1, Dummy );
                StackPushS( &Stack->LargeBuffer, _T( "]" ), 1 );
            }
            else
            {
                StackPushS( &Stack->LargeBuffer, DEFAULT_CLASS_THIS_P, DEFAULT_CLASS_THIS_P_LENGTH );
                if ( TEST_OP2_CONST( OpLine ) )
                {
                    make_printable_zval_url_ex( OP2_VAL( OpLine ), &Stack->Buffer2, 0 );
                    Dummy = StackPopAllS( &Stack->Buffer2, &String1 );
                }
                else if ( TEST_OP2_ALL_VAR( OpLine ) )
                {
                    Var1 = FindVariableById( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
                    if ( Var1 == NULL )
                        break;

                    String1 = Var1->Expr;
                    Dummy = Var1->ExprLength;
                }
                else
                {
                    break;
                }
                Dummy = StackPushS( &Stack->LargeBuffer, String1, Dummy );
            }

            /* Replace op2 */
            LocalOpLine.result = OpLine->result;
            LocalOpLine.op1 = OpLine->op1;
            LocalOpLine.op2 = OpLine1->op1;
            OpLine = &LocalOpLine;
            String1 = _T( "" );
            Stack->NextOpLine = OpLine1 + 1;
        }
        else
        {
            Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                break;

            String1 = Var->Expr;
            Dummy = Var->ExprLength;
        }

        OpType = Stack->InternalFlags & DS_IFLAGS_OT_MASK;
        if ( Stack->StartCharLength )
            OpType |= VE_FLAGS_SILENCE;

        Length += 16 + Dummy;
        if ( TEST_OP2_CONST( OpLine ) )
        {
            if ( TEST_OP2_NUMBER( OpLine ) )
                OpType |= VE_FLAGS_NUMBER2;

            make_printable_zval_url( OP2_VAL( OpLine ), &Stack->Buffer2 );
            Length += StackPopAllS( &Stack->Buffer2, &String2 );

            /* Adjust buffer length */
            BufferSize = StackSetMaxS( &Stack->LargeBuffer, Length );
            BufferCount = StackCountS( &Stack->LargeBuffer );
            Buffer = StackBaseS( &Stack->LargeBuffer ) + BufferCount;

            Index |= Stack->InternalFlags & DS_IFLAGS_COMPACT ? 1 : 0;
            RetCode = _sntprintf( Buffer, BufferSize, GET_FORMAT_3_STRING( Index ), String1, Stack->OpString, String2 );
            StackSetTopS( &Stack->LargeBuffer, RetCode + BufferCount );
        }
        else if ( TEST_OP2_ALL_VAR( OpLine ) )
        {
            Var1 = FindVariableById( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
            if ( Var1 == NULL )
                break;

            OpType |= Var1->Flags & VE_FLAGS_NUMBER2;

            /* Global $x */
            if ( OP_CODE( OpLine ) == ZEND_ASSIGN_REF && OPR_TYPE( OpLine ) == IS_UNUSED )
            {
                if ( ( Var1->Flags & VE_FLAGS_FETCH_MASK ) == VE_FLAGS_GLOBAL )
                {
                    StackPushS( &Stack->LargeBuffer, _T( "global " ), 7 );
                    StackPushS( &Stack->LargeBuffer, Var1->Expr, Var1->ExprLength );
                }
                else if ( ( Var1->Flags & VE_FLAGS_FETCH_MASK ) == VE_FLAGS_STATIC )
                {
                    StackPushS( &Stack->LargeBuffer, _T( "static " ), 7 );
                    StackPushS( &Stack->LargeBuffer, Var1->Expr, Var1->ExprLength );
                    if ( Stack->OpArray->static_variables )
                    {
                        /* Not use find_hash_key_ex since hash function maybe varying */
                        ValuePtr = ( zval** )find_hash_key( Stack->OpArray->static_variables, Var1->Name, Var1->NameLength + 1 );
                        if ( ValuePtr == NULL )
                            break;

                        if ( GET_GS( )->ExtensionId < EXTENSION_ID_2 )
                            Value = *ValuePtr;
                        else
                            Value = ( zval* )ValuePtr;

                        if ( Value )
                        {
                            StackPushS( &Stack->LargeBuffer, _T( " = " ), 3 );
                            make_printable_zval_url( Value, &Stack->LargeBuffer );
                        }
                    }
                }
                else if ( ( Var1->Flags & VE_FLAGS_FETCH_MASK ) == VE_FLAGS_LOCAL )
                {
                    /* BUG */
                    if ( GET_GS_FLAGS( ) & GS_FLAGS_BUG )
                        dump_string_ex( Stack, _T( "//[BUG][%6d]assign_ref local\r\n" ), Stack->Offset );
                    break;
                }
                UpdateVariableEx( OP1_TYPE( OpLine ), OP1_VAR( OpLine ), Stack->Offset, Var1->Name, Var1->Expr, 0 );
            }
            else
            {
                /* Prefix */
                if ( ( Var1->Flags & VE_FLAGS_SILENCE_FUNCTION ) == VE_FLAGS_SILENCE_FUNCTION )
                {
                    StackPushS( &Stack->Buffer2, DEFAULT_SILENCE_STRING, DEFAULT_SILENCE_STRING_LENGTH );
                    StackPushS( &Stack->Buffer2, Var1->Expr, Var1->ExprLength );
                    Length += StackPopAllS( &Stack->Buffer2, &String2 );
                }
                else
                {
                    String2 = Var1->Expr;
                    Length += Var1->ExprLength;
                }

                /* Adjust buffer length */
                BufferSize = StackSetMaxS( &Stack->LargeBuffer, Length );
                BufferCount = StackCountS( &Stack->LargeBuffer );
                Buffer = StackBaseS( &Stack->LargeBuffer ) + BufferCount;

                Index |= Stack->InternalFlags & DS_IFLAGS_COMPACT ? 1 : 0;
                Index |= ( Stack->InternalFlags & DS_IFLAGS_OT_MASK ) > ( Var1->Flags & DS_IFLAGS_OT_MASK ) ? 2 : 0;
                RetCode = _sntprintf( Buffer, BufferSize, GET_FORMAT_3_STRING( Index ), String1, Stack->OpString, String2 );
                StackSetTopS( &Stack->LargeBuffer, RetCode + BufferCount );
            }
        }

        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
        {
            StackPushS( &Stack->LargeBuffer, Stack->EndChar, Stack->EndCharLength );
            if ( OpType & VE_FLAGS_SILENCE )
                StackPushPrefixS( &Stack->LargeBuffer, DEFAULT_SILENCE_STRING, DEFAULT_SILENCE_STRING_LENGTH );
            RetCode = StackPopAllExS( &Stack->LargeBuffer, &String );
            dump_string( Stack, String );
        }
        else if ( TEST_OPR_ALL_VAR( OpLine ) )
        {
            RetCode = StackPopAllS( &Stack->LargeBuffer, &String );
            if ( String[0] == DEFAULT_SILENCE_CHAR )
            {
                String++;
                OpType |= VE_FLAGS_SILENCE;
            }
            UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, OpType );
        }
        else
        {
            StackReinitS( &Stack->LargeBuffer );
        }
    } while ( 0 );

    return RetCode;
}

/*
///////////////////////////////////////////////////////////////////////////////
// dump_two_op_function
///////////////////////////////////////////////////////////////////////////////
*/
ULONG FASTCALL dump_two_op_function( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG Index;
    ULONG OpType;
    ULONG Length;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    PVARIABLE_ENTRY Var1;
    const TCHAR *String;
    const TCHAR *String1;
    const TCHAR *String2;
    ULONG BufferSize;
    ULONG BufferCount;
    TCHAR *Buffer;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        Index = 0;
        Length = 0;
        OpType = Stack->InternalFlags & DS_IFLAGS_OT_MASK;
        if ( Stack->StartCharLength )
            OpType |= VE_FLAGS_SILENCE;

        if ( TEST_OP1_CONST( OpLine ) )
        {
            if ( TEST_OP1_NUMBER( OpLine ) )
            {
                OpType |= VE_FLAGS_NUMBER1;
                if ( Stack->InternalFlags & DS_IFLAGS_FIX_OT )
                    Index |= 4;
            }

            make_printable_zval_url( OP1_VAL( OpLine ), &Stack->Buffer1 );
            Length += StackPopAllS( &Stack->Buffer1, &String1 ) + 16;
            if ( TEST_OP2_CONST( OpLine ) )
            {
                if ( TEST_OP2_NUMBER( OpLine ) )
                    OpType |= VE_FLAGS_NUMBER2;

                if ( Stack->InternalFlags & DS_IFLAGS_FIX_OT && OpType & VE_FLAGS_NUMBER2 )
                    Index |= 2;

                make_printable_zval_url( OP2_VAL( OpLine ), &Stack->Buffer2 );
                Length += StackPopAllS( &Stack->Buffer2, &String2 );

                /* Adjust buffer length */
                BufferSize = StackSetMaxS( &Stack->LargeBuffer, Length );
                BufferCount = StackCountS( &Stack->LargeBuffer );
                Buffer = StackBaseS( &Stack->LargeBuffer ) + BufferCount;

                Index |= Stack->InternalFlags & DS_IFLAGS_COMPACT ? 1 : 0;
                RetCode = _sntprintf( Buffer, BufferSize, GET_FORMAT_3_STRING( Index ), String1, Stack->OpString, String2 );
                StackSetTopS( &Stack->LargeBuffer, RetCode + BufferCount );
            }
            else if ( TEST_OP2_ALL_VAR( OpLine ) )
            {
                Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
                if ( Var1 == NULL )
                    break;

                OpType |= Var1->Flags & VE_FLAGS_NUMBER1;
                if ( Stack->InternalFlags & DS_IFLAGS_FIX_OT && OpType & VE_FLAGS_NUMBER1 )
                    Index |= 2;

                /* Prefix */
                if ( ( Var1->Flags & VE_FLAGS_SILENCE_FUNCTION ) == VE_FLAGS_SILENCE_FUNCTION )
                {
                    StackPushS( &Stack->Buffer2, DEFAULT_SILENCE_STRING, DEFAULT_SILENCE_STRING_LENGTH );
                    StackPushS( &Stack->Buffer2, Var1->Expr, Var1->ExprLength );
                    Length += StackPopAllS( &Stack->Buffer2, &String2 );
                }
                else
                {
                    String2 = Var1->Expr;
                    Length += Var1->ExprLength;
                }

                /* Adjust buffer length */
                BufferSize = StackSetMaxS( &Stack->LargeBuffer, Length );
                BufferCount = StackCountS( &Stack->LargeBuffer );
                Buffer = StackBaseS( &Stack->LargeBuffer ) + BufferCount;

                Index |= Stack->InternalFlags & DS_IFLAGS_COMPACT ? 1 : 0;
                Index |= ( Stack->InternalFlags & DS_IFLAGS_OT_MASK ) >= ( Var1->Flags & DS_IFLAGS_OT_MASK ) ? 2 : 0;
                RetCode = _sntprintf( Buffer, BufferSize, GET_FORMAT_3_STRING( Index ), String1, Stack->OpString, String2 );
                StackSetTopS( &Stack->LargeBuffer, RetCode + BufferCount );
            }
        }
        else if ( TEST_OP1_ALL_VAR( OpLine ) )
        {
            Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                break;

            OpType |= Var->Flags & VE_FLAGS_NUMBER2;
            if ( Stack->InternalFlags & DS_IFLAGS_FIX_OT && OpType & VE_FLAGS_NUMBER2 )
                Index |= 4;

            /* Prefix */
            Length += 16;
            if ( ( Var->Flags & VE_FLAGS_SILENCE_FUNCTION ) == VE_FLAGS_SILENCE_FUNCTION )
            {
                StackPushS( &Stack->Buffer1, DEFAULT_SILENCE_STRING, DEFAULT_SILENCE_STRING_LENGTH );
                StackPushS( &Stack->Buffer1, Var->Expr, Var->ExprLength );
                Length += StackPopAllS( &Stack->Buffer1, &String1 );
            }
            else
            {
                String1 = Var->Expr;
                Length += Var->ExprLength;
            }

            if ( TEST_OP2_CONST( OpLine ) )
            {
                if ( TEST_OP2_NUMBER( OpLine ) )
                {
                    OpType |= VE_FLAGS_NUMBER2;
                    if ( Stack->InternalFlags & DS_IFLAGS_FIX_OT )
                        Index |= 2;
                }

                make_printable_zval_url( OP2_VAL( OpLine ), &Stack->Buffer2 );
                Length += StackPopAllS( &Stack->Buffer2, &String2 );

                /* Adjust buffer length */
                BufferSize = StackSetMaxS( &Stack->LargeBuffer, Length );
                BufferCount = StackCountS( &Stack->LargeBuffer );
                Buffer = StackBaseS( &Stack->LargeBuffer ) + BufferCount;

                Index |= Stack->InternalFlags & DS_IFLAGS_COMPACT ? 1 : 0;
                Index |= ( Stack->InternalFlags & DS_IFLAGS_OT_MASK ) > ( Var->Flags & DS_IFLAGS_OT_MASK ) ? 4 : 0;
                RetCode = _sntprintf( Buffer, BufferSize, GET_FORMAT_3_STRING( Index ), String1, Stack->OpString, String2 );
                StackSetTopS( &Stack->LargeBuffer, RetCode + BufferCount );
            }
            else if ( TEST_OP2_ALL_VAR( OpLine ) )
            {
                Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
                if ( Var1 == NULL )
                    break;

                OpType |= Var1->Flags & VE_FLAGS_NUMBER1;
                if ( Stack->InternalFlags & DS_IFLAGS_FIX_OT && OpType & VE_FLAGS_NUMBER1 )
                    Index |= 2;

                /* Prefix */
                if ( ( Var1->Flags & VE_FLAGS_SILENCE_FUNCTION ) == VE_FLAGS_SILENCE_FUNCTION )
                {
                    StackPushS( &Stack->Buffer2, DEFAULT_SILENCE_STRING, DEFAULT_SILENCE_STRING_LENGTH );
                    StackPushS( &Stack->Buffer2, Var1->Expr, Var1->ExprLength );
                    Length += StackPopAllS( &Stack->Buffer2, &String2 );
                }
                else
                {
                    String2 = Var1->Expr;
                    Length += Var1->ExprLength;
                }

                /* Adjust buffer length */
                BufferSize = StackSetMaxS( &Stack->LargeBuffer, Length );
                BufferCount = StackCountS( &Stack->LargeBuffer );
                Buffer = StackBaseS( &Stack->LargeBuffer ) + BufferCount;

                Index |= Stack->InternalFlags & DS_IFLAGS_COMPACT ? 1 : 0;
                Index |= ( Stack->InternalFlags & DS_IFLAGS_OT_MASK ) >= ( Var1->Flags & DS_IFLAGS_OT_MASK ) ? 2 : 0;
                Index |= ( Stack->InternalFlags & DS_IFLAGS_OT_MASK ) > ( Var->Flags & DS_IFLAGS_OT_MASK ) ? 4 : 0;
                RetCode = _sntprintf( Buffer, BufferSize, GET_FORMAT_3_STRING( Index ), String1, Stack->OpString, String2 );
                StackSetTopS( &Stack->LargeBuffer, RetCode + BufferCount );
            }
            else
            {
                /* Adjust buffer length */
                BufferSize = StackSetMaxS( &Stack->LargeBuffer, Var->ExprLength + 16 );
                BufferCount = StackCountS( &Stack->LargeBuffer );
                Buffer = StackBaseS( &Stack->LargeBuffer ) + BufferCount;

                /* Only one Op */
                Index |= Stack->InternalFlags & DS_IFLAGS_COMPACT ? 1 : 0;
                Index |= ( Stack->InternalFlags & DS_IFLAGS_OT_MASK ) >= ( Var->Flags & DS_IFLAGS_OT_MASK ) ? 2 : 0;
                Index |= ( Stack->InternalFlags & DS_IFLAGS_POST ) ? 4 : 0;
                if ( Stack->InternalFlags & DS_IFLAGS_POST )
                {
                    String1 = Var->Expr;
                    String2 = Stack->OpString;
                }
                else
                {
                    String2 = Var->Expr;
                    String1 = ( TCHAR* )Stack->OpString;
                }
                RetCode = _sntprintf( Buffer, BufferSize, GET_FORMAT_2_STRING( Index ), String1, String2 );
                StackSetTopS( &Stack->LargeBuffer, RetCode + BufferCount );
            }
        }
        else if ( TEST_OP2_CONST( OpLine ) )
        {
            StackPushS( &Stack->Buffer1, DEFAULT_CLASS_THIS_P, DEFAULT_CLASS_THIS_P_LENGTH );
            make_printable_zval_url_ex( OP2_VAL( OpLine ), &Stack->Buffer1, 0 );
            Length += StackPopAllS( &Stack->Buffer1, &String );

            /* Adjust buffer length */
            BufferSize = StackSetMaxS( &Stack->LargeBuffer, Length + 16 );
            BufferCount = StackCountS( &Stack->LargeBuffer );
            Buffer = StackBaseS( &Stack->LargeBuffer ) + BufferCount;

            /* Only one Op */
            Index |= Stack->InternalFlags & DS_IFLAGS_COMPACT ? 1 : 0;
            Index |= ( Stack->InternalFlags & DS_IFLAGS_POST ) ? 4 : 0;
            if ( Stack->InternalFlags & DS_IFLAGS_POST )
            {
                String1 = String;
                String2 = Stack->OpString;
            }
            else
            {
                String2 = String;
                String1 = Stack->OpString;
            }
            RetCode = _sntprintf( Buffer, BufferSize, GET_FORMAT_2_STRING( Index ), String1, String2 );
            StackSetTopS( &Stack->LargeBuffer, RetCode + BufferCount );
        }
        else if ( TEST_OP2_ALL_VAR( OpLine ) )
        {
            Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
            if ( Var1 == NULL )
                break;

            StackPushS( &Stack->Buffer1, DEFAULT_CLASS_THIS_P, DEFAULT_CLASS_THIS_P_LENGTH );
            StackPushS( &Stack->Buffer1, Var1->Expr, Var1->ExprLength );
            Length += StackPopAllS( &Stack->Buffer1, &String );

            /* Adjust buffer length */
            BufferSize = StackSetMaxS( &Stack->LargeBuffer, Length + 16 );
            BufferCount = StackCountS( &Stack->LargeBuffer );
            Buffer = StackBaseS( &Stack->LargeBuffer ) + BufferCount;

            /* Only one Op */
            Index |= Stack->InternalFlags & DS_IFLAGS_COMPACT ? 1 : 0;
            Index |= ( Stack->InternalFlags & DS_IFLAGS_OT_MASK ) >= ( Var1->Flags & DS_IFLAGS_OT_MASK ) ? 2 : 0;
            Index |= ( Stack->InternalFlags & DS_IFLAGS_POST ) ? 4 : 0;
            if ( Stack->InternalFlags & DS_IFLAGS_POST )
            {
                String1 = String;
                String2 = Stack->OpString;
            }
            else
            {
                String2 = String;
                String1 = Stack->OpString;
            }
            RetCode = _sntprintf( Buffer, BufferSize, GET_FORMAT_2_STRING( Index ), String1, String2 );
            StackSetTopS( &Stack->LargeBuffer, RetCode + BufferCount );
        }

        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
        {
            StackPushS( &Stack->LargeBuffer, Stack->EndChar, Stack->EndCharLength );
            if ( OpType & VE_FLAGS_SILENCE )
                StackPushPrefixS( &Stack->LargeBuffer, DEFAULT_SILENCE_STRING, DEFAULT_SILENCE_STRING_LENGTH );
            RetCode = StackPopAllExS( &Stack->LargeBuffer, &String );
            dump_string( Stack, String );
        }
        else if ( TEST_OPR_ALL_VAR( OpLine ) )
        {
            RetCode = StackPopAllS( &Stack->LargeBuffer, &String );
            if ( String[0] == DEFAULT_SILENCE_CHAR )
            {
                String++;
                OpType |= VE_FLAGS_SILENCE;
            }
            UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, OpType );
        }
        else
        {
            StackReinitS( &Stack->LargeBuffer );
        }
    } while ( 0 );

    return RetCode;
}

void adjust_return_list( PDUMP_STACK Stack, ULONG Offset )
{
    register ULONG Iter;
    register ULONG Count;
    register PBRK_CONT_LIST BrkContPtr;
    COMMON_CONTROL_ENTRY Entry;

    /* Default return */
    if ( scan_if_default_return( Stack, Offset ) && Offset > 1 &&
        OP_CODE( Stack->Head + Offset - 1 ) != ZEND_JMPZ && OP_CODE( Stack->Head + Offset - 1 ) != ZEND_JMPNZ )
    {
        Iter = 0;
        Count = StackCountT( &Stack->BreakList );
        while ( Iter < Count )
        {
            BrkContPtr = StackAtT( &Stack->BreakList, Iter );
            if ( Stack->LastOffset - 1 <= BrkContPtr->End && BrkContPtr->Start < Offset && Offset < BrkContPtr->End )
            {
                /* if ( ){break;} in while ( ){} */
                Entry.Flags = DS_FLAGS_BRK;
                Entry.Type = DS_TYPE_NOINDENT;
                Entry.Start = Offset;
                Entry.End = Offset;
                insert_control_list( Stack, Offset, &Entry );

                /* Skip */
                StackPushAscU( &Stack->Skip, Offset );
                /* Remove */
                StackRemoveU( &Stack->ReturnX, Offset );
                break;
            }
            Iter++;
        }
    }
}

inline void push_scan_control_list( PCOMMON_STACK_T ScanList, ULONG Offset )
{
    KEY_VALUE Scan;

    Scan.Key = Offset;
    Scan.Value = 0;
    StackPushT( ScanList, &Scan );
}

inline void delete_scan_control_list( PCOMMON_STACK_T ScanList, ULONG Offset )
{
    ULONG Top;

    /* Mark as delete */
    Top = StackFindAscT( ScanList, ( PKEY_VALUE )&Offset );
    if ( Top )
        ( ( PKEY_VALUE )StackAtT( ScanList, Top - 1 ) )->Value = 0xFFFFFFFF;
}

inline void zap_scan_control_list( PCOMMON_STACK_T ScanList, ULONG Offset )
{
    PKEY_VALUE *In;
    PKEY_VALUE *InEnd;
    PKEY_VALUE *Out;

    In = ( PKEY_VALUE* )StackBaseT( ScanList );
    InEnd = In + StackCountT( ScanList );
    Out = In;
    /* Find first item */
    while ( In < InEnd )
    {
        if ( ( *In )->Value == 0xFFFFFFFF )
            break;
        In++;
        Out++;
    }

    /* Start to move date */
    while ( In < InEnd )
    {
        if ( ( *In )->Value != 0xFFFFFFFF )
        {
            ( *Out )->Key = ( *In )->Key;
            ( *Out )->Value = 0;
            Out++;
        }
        In++;
    }

    /* Set new top */
    StackSetTopT( ScanList, Out - ( PKEY_VALUE* )StackBaseT( ScanList ) );
}

void scan_control_list( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG Offset;
    ULONG Size;
    ULONG Top;
    ULONG Start;
    ULONG End;
    ULONG ContinueOffset;
    ULONG BreakOffset;
    ULONG NextOffset;
    ULONG JmpOffset;
    ULONG ExtendOffset;
    ULONG NextOutput;
    ULONG Flags;
    ULONG Type;
    ULONG Dummy;
    zend_uchar OpCode;
    zend_op_array *OpArray;
    zend_op *Head;
    zend_op *Tail;
    register zend_op *OpLine;
    zend_op *OpLine1;
    zend_op *OpLine2;
    zend_try_catch_element_2 *TryCatchArray;
    zend_try_catch_element_2 *TryCatchArrayEnd;
    zend_brk_cont_element *BrkContArray;
    zend_brk_cont_element *BrkContArrayEnd;
    COMMON_CONTROL_ENTRY Entry;
    PKEY_VALUE Scan;
    PBRK_CONT_LIST BrkContPtr;

    RetCode = 0;
    Head = Stack->Head;
    Tail = Stack->Tail;
    OpArray = Stack->OpArray;
    Size = Stack->LastOffset;

    if ( Size )
    {
        /* Skip last handle exception */
        OpLine = Stack->Tail - 1;
        if ( OP_CODE( OpLine ) == ZEND_HANDLE_EXCEPTION )
        {
            OpLine--;
            Tail--;
            Size--;
            Stack->Tail--;
            Stack->LastOffset--;
        }

        /* Skip last default return */
        if ( OP_CODE( OpLine ) == ZEND_RETURN && is_default_return( Stack->State, OpLine ) )
        {
            Size--;
            StackPushAscU( &Stack->Skip, Size );
        }
    }

    /* Next step */
    Stack->Step++;

    /* Try-catch */
    if ( GET_GS( )->ExtensionId > EXTENSION_ID_1 )
    {
        TryCatchArray = ( ( zend_op_array_2* )OpArray )->try_catch_array;
        if ( TryCatchArray )
        {
            TryCatchArrayEnd = TryCatchArray + ( ( zend_op_array_2* )OpArray )->last_try_catch;
            while ( TryCatchArray < TryCatchArrayEnd )
            {
                Start = TryCatchArray->try_op;
                End = TryCatchArray->catch_op;

                Entry.Flags = DS_FLAGS_TRY;
                Entry.Type = 0;
                Entry.Start = Start;
                Entry.End = End;
                insert_control_list( Stack, Start, &Entry );

                Entry.Flags = DS_FLAGS_TRY_END | DS_FLAGS_END;
                insert_control_list( Stack, End, &Entry );
                TryCatchArray++;
            }
        }
    }

    /* Break-continue */
    BrkContArray = OpArray->brk_cont_array;
    if ( BrkContArray )
    {
        BrkContArrayEnd = BrkContArray + OpArray->last_brk_cont;
        while ( BrkContArray < BrkContArrayEnd )
        {
            Offset = Stack->Offset;
            Dummy = DS_FLAGS_INTERNAL;
            if ( is_jump_to_loop( Head, BrkContArray->cont ) )
                Dummy |= DS_FLAGS_UPDATED;

            /* Special offset */
            Stack->Offset = INVALID_OP_OFFSET;

            /* Insert to continue/break list */
            insert_cont_brk_list( Stack, BrkContArray->cont, BrkContArray->brk, BrkContArray->cont, BrkContArray->brk, Dummy );
            Stack->Offset = Offset;
            BrkContArray++;
        }
    }

    /* Re-init */
    StackReinitT( &Stack->ScanList );

    /* First scan */
    for ( Offset = 0, OpLine = Head; Offset < Size; Offset++, OpLine++ )
    {
        /* Skip */
        if ( StackBottomU( &Stack->Skip, &Dummy ) )
        {
            while ( StackBottomU( &Stack->Skip, &Dummy ) && Dummy < Offset )
                StackPopBottomU( &Stack->Skip, NULL );

            /* Skip this */
            if ( Dummy == Offset )
            {
                StackPopBottomU( &Stack->Skip, NULL );
                continue;
            }
        }

        /* Skip Once */
        if ( StackBottomU( &Stack->SkipOnce, &Dummy ) )
        {
            while ( StackBottomU( &Stack->SkipOnce, &Dummy ) && Dummy < Offset )
                StackPopBottomU( &Stack->SkipOnce, NULL );

            /* Skip this */
            if ( Dummy == Offset )
            {
                StackPopBottomU( &Stack->SkipOnce, NULL );
                continue;
            }
        }

        Stack->OpLine = OpLine;
        Stack->Offset = Offset;
        switch ( OP_CODE( OpLine ) )
        {
        case ZEND_JMP :
            push_scan_control_list( &Stack->ScanList, Offset );
            StackPushU( &Stack->Output, Offset );
            StackPushU( &Stack->Jmp, Offset );
            break;

        case ZEND_JMPZ :
        case ZEND_JMPNZ :
            push_scan_control_list( &Stack->ScanList, Offset );
            scan_if_logic( Stack, OpLine );
            break;

        case ZEND_JMPZNZ :
            if ( OP_CODE( OpLine - 1 ) == ZEND_CASE )
            {
                StackPushAscU( &Stack->Skip, Offset );
                break;
            }

            push_scan_control_list( &Stack->ScanList, Offset );
            StackPushU( &Stack->JmpZnz, Offset );
            break;

        case ZEND_FE_FETCH :
            push_scan_control_list( &Stack->ScanList, Offset );
            StackPushU( &Stack->Output, Offset );
            StackPushU( &Stack->ForEach, Offset );
            break;

        case ZEND_CASE :
            push_scan_control_list( &Stack->ScanList, Offset );
            StackPushU( &Stack->Output, Offset );
            StackPushU( &Stack->SwitchCase, Offset );
            break;

        case ZEND_SWITCH_FREE :
            StackPushU( &Stack->Output, Offset );
            StackPushU( &Stack->SwitchFree, Offset );
            break;

        case ZEND_RECV :
        case ZEND_RECV_INIT :
            StackPushU( &Stack->Output, Offset );
            Stack->ArgumentCount++;
            break;

        case ZEND_JMPZ_EX :
        case ZEND_JMPNZ_EX :
            /* Php5 */
            NextOffset = OP_JMPX( OpLine, Head );
            OpLine1 = Head + NextOffset;
            OpLine2 = OpLine1 - 1;
            /* Skip */
            while ( OP_CODE( OpLine1 ) == ZEND_NOP && OpLine1 < Tail )
                OpLine1++;

            if ( OpLine1 == Tail || OP_CODE( OpLine1 ) != ZEND_FREE )
                break;

            StackPushU( &Stack->Output, Offset );
            NextOffset = OpLine1 - Head;
            StackPushAscU( &Stack->Skip, Offset );
            if ( OP_CODE( OpLine2 ) == ZEND_BOOL && !TEST_OP1_CONST( OpLine2 ) &&
                OPR_TYPE( OpLine2 ) == OP1_TYPE( OpLine1 ) && OPR_VAR( OpLine2 ) == OP1_VAR( OpLine1 ) )
            {
                /* Not bool true */
            }
            else
            {
                /* Optimized */
                StackPushAscU( &Stack->Skip, NextOffset );
            }

            if ( OP_CODE( OpLine ) == ZEND_JMPZ_EX )
                Entry.Type = 0;
            else
                Entry.Type = DS_TYPE_REVERSE;

            Start = Offset;
            End = NextOffset + 1;

            Entry.Flags = DS_FLAGS_IF;
            Entry.Start = Start;
            Entry.End = End;
            insert_control_list( Stack, Start, &Entry );

            Entry.Flags = DS_FLAGS_IF_END | DS_FLAGS_END;
            Entry.Start = NextOffset;
            insert_control_list( Stack, End, &Entry );
            break;

        case ZEND_FETCH_DIM_R :
        case ZEND_FETCH_DIM_TMP_VAR :
            if ( TEST_OP2_CONST( OpLine ) && OP2_VAL_TYPE( OpLine ) == IS_LONG )
            {
                StackReinitU( &Stack->Common );

                Dummy = OP2_VAL( OpLine )->value.lval;
                OpLine1 = OpLine;
                while ( OpLine1 < Stack->Tail )
                {
                    if ( OP_CODE( OpLine1 ) == OP_CODE( OpLine ) )
                    {
                        if ( !TEST_OP2_CONST( OpLine1 ) || OP2_VAL_TYPE( OpLine1 ) != IS_LONG )
                            break;

                        StackPushU( &Stack->Common, OpLine1 - Head );
                    }
                    else if ( OP_CODE( OpLine1 ) == ZEND_ASSIGN )
                    {
                        OpLine2 = OpLine1 - 1;
                        /* Skip */
                        while ( Head < OpLine2 && ( OP_CODE( OpLine2 ) == ZEND_NOP || OP_CODE( OpLine2 ) == ZEND_FETCH_W || OP_CODE( OpLine2 ) == ZEND_FETCH_DIM_W ) )
                            OpLine2--;
                        if ( OP_CODE( OpLine2 ) != OP_CODE( OpLine ) )
                            break;

                        if ( OPR_TYPE( OpLine2 ) != OP2_TYPE( OpLine1 ) || OPR_VAR( OpLine2 ) != OP2_VAR( OpLine1 ) )
                            break;

                        StackPushU( &Stack->Common, OpLine1 - Head );
                    }
                    else if ( OP_CODE( OpLine1 ) == ZEND_FETCH_W && TEST_OP1_CONST( OpLine1 ) || OP_CODE( OpLine1 ) == ZEND_FETCH_DIM_W )
                    {
                    }
                    else if ( OP_CODE( OpLine1 ) != ZEND_NOP )
                    {
                        break;
                    }
                    OpLine1++;
                }

                if ( StackCountU( &Stack->Common ) > 1 )
                {
                    /* Skip once */
                    while ( StackPopU( &Stack->Common, &NextOffset ) )
                        StackPushAscU( &Stack->SkipOnce, NextOffset );
                }
            }
            break;

        case ZEND_DECLARE_FUNCTION_OR_CLASS :
        case ZEND_DECLARE_FUNCTION :
        case ZEND_DECLARE_CLASS :
        case ZEND_DECLARE_INHERITED_CLASS :
            StackPushU( &Stack->Output, Offset );
            StackPushU( &Stack->Declare, Offset );
            break;

        case ZEND_BRK :
        case ZEND_CONT :
            push_scan_control_list( &Stack->ScanList, Offset );
            StackPushU( &Stack->Output, Offset );
            break;

        case ZEND_CATCH :
            Start = Offset;
            End = OP_EX_VALUE( OpLine );

            Entry.Flags = DS_FLAGS_CATCH;
            Entry.Type = 0;
            Entry.Start = Start;
            Entry.End = End;
            insert_control_list( Stack, Start, &Entry );

            Entry.Flags = DS_FLAGS_CATCH_END | DS_FLAGS_END;
            insert_control_list( Stack, End, &Entry );
            break;

        case ZEND_ASSIGN_REF :
            /* Global $x */
            if ( OPR_VAR( OpLine ) == IS_UNUSED || OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
                StackPushU( &Stack->Output, Offset );
            break;

        case ZEND_END_SILENCE :
        case ZEND_SEND_VAL :
        case ZEND_SEND_VAR :
        case ZEND_SEND_REF :
        case ZEND_SEND_VAR_NO_REF :
        case ZEND_INIT_CTOR_CALL :
        case ZEND_INIT_METHOD_CALL :
        case ZEND_INIT_STATIC_METHOD_CALL :
        case ZEND_FETCH_CLASS :
        case ZEND_USER_OPCODE :
            break;

        case ZEND_NOP :
            StackPushAscU( &Stack->Skip, Offset );
            break;

        case ZEND_RETURN :
            if ( is_default_return( Stack->State, OpLine ) )
                StackPushU( &Stack->ReturnX, Offset );
            push_scan_control_list( &Stack->ScanList, Offset );
        case ZEND_EXIT :
            StackPushU( &Stack->Output, Offset );
            break;

        default :
            if ( OPR_TYPE( OpLine ) != IS_UNUSED && OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
                StackPushU( &Stack->Output, Offset );
            break;
        }
    }
    StackSetBottomU( &Stack->Skip, 0 );
    StackSetBottomU( &Stack->SkipOnce, 0 );

    /* Next step */
    Stack->Step++;

    /* Zap item marked as deleted */
    zap_scan_control_list( &Stack->ScanList, Offset );

    /* Set to start */
    StackSetBottomT( &Stack->ScanList, 0 );

    /* Second scan */
    while ( StackPopBottomT( &Stack->ScanList, &Scan ) )
    {
        Offset = Scan->Key;
        OpLine = Head + Offset;
        Stack->Offset = Offset;
        Stack->OpLine = OpLine;

        /* Skip */
        if ( StackBottomU( &Stack->Skip, &Dummy ) )
        {
            while ( StackBottomU( &Stack->Skip, &Dummy ) && Dummy < Offset )
                StackPopBottomU( &Stack->Skip, NULL );

            /* Skip this */
            if ( Dummy == Offset )
            {
                StackPopBottomU( &Stack->Skip, NULL );
                continue;
            }
        }

        /* Skip Once */
        if ( StackBottomU( &Stack->SkipOnce, &Dummy ) )
        {
            while ( StackBottomU( &Stack->SkipOnce, &Dummy ) && Dummy < Offset )
                StackPopBottomU( &Stack->SkipOnce, NULL );

            /* Skip this */
            if ( Dummy == Offset )
            {
                StackPopBottomU( &Stack->SkipOnce, NULL );
                continue;
            }
        }

        switch ( OP_CODE( OpLine ) )
        {
        case ZEND_JMP :
            JmpOffset = OP_JMP( OpLine, Head );
            OpLine1 = OpLine + 1;
            /* Skip duplicate jmp */
            if ( JmpOffset == Offset + 1 || OP_CODE( OpLine1 ) == ZEND_JMP && OP_JMP( OpLine1, Head ) == JmpOffset )
            {
                StackPushAscU( &Stack->Skip, Offset );
                /* Delete */
                delete_scan_control_list( &Stack->ScanList, Offset );
            }
            break;

        case ZEND_JMPZ :
        case ZEND_JMPNZ :
            patch_jmpx( Stack, OpLine );
            Flags = 0;
            NextOffset = OP_JMPX( OpLine, Head );
            if ( NextOffset < Offset )
            {
                BrkContPtr = GetContinue( Stack, NextOffset, Offset );
                Flags |= FLAGS_JMPX_CONT;
                if ( BrkContPtr )
                {
                    ContinueOffset = BrkContPtr->Continue;
                    BreakOffset = BrkContPtr->Break;
                    NextOffset = BreakOffset;
                    OpLine1 = Head + NextOffset - 1;
                    /* Skip */
                    while ( OP_CODE( OpLine1 ) == ZEND_NOP )
                    {
                        OpLine1--;
                        NextOffset--;
                    }

                    /* Loop in if-else */
                    while ( OP_CODE( OpLine1 ) == ZEND_JMP && OP_JMP( OpLine1, Head ) > BreakOffset )
                    {
                        OpLine1--;
                        NextOffset--;
                    }

                    /* Loop jump back */
                    while ( OP_CODE( OpLine1 ) == ZEND_JMP && OP_JMP( OpLine1, Head ) == ContinueOffset )
                    {
                        OpLine1--;
                        NextOffset--;
                    }

                    JmpOffset = get_jmp_offset( Stack, OpLine1 );
                    if ( JmpOffset == INVALID_OP_OFFSET )
                        break;

                    if ( JmpOffset <= ContinueOffset )
                        break;

                    if ( JmpOffset <= Offset )
                    {
                        Flags |= FLAGS_JMPX_MAP_1;
                    }
                    else if ( Offset < JmpOffset && JmpOffset < NextOffset )
                    {
                        /* Parent loop */
                        if ( get_real_continue_offset( Stack, JmpOffset ) != get_real_continue_offset( Stack, ContinueOffset ) )
                            break;

                        Flags |= FLAGS_JMPX_MAP_2;
                    }
                    else
                    {
                        if ( find_jmp_middle( Stack, Offset, Offset, NextOffset, &Dummy ) != INVALID_OP_OFFSET )
                        {
                            NextOffset = Dummy;
                            OpLine1 = Head + NextOffset - 1;
                        }
                        Flags |= FLAGS_JMPX_MAP_3;
                    }
                }
            }
            else
            {
                BrkContPtr = GetBreak( Stack, NextOffset, Offset );
                Flags |= FLAGS_JMPX_BRK;
                if ( BrkContPtr )
                {
                    ContinueOffset = BrkContPtr->Continue;
                    BreakOffset = BrkContPtr->Break;
                    if ( ( BrkContPtr->Flags & DS_FLAGS_MASK ) == DS_FLAGS_SWITCH )
                    {
                        /* See if in switch */
                        NextOffset = adjust_control_list_end( Stack, Offset, NextOffset );
                        OpLine2 = Head + NextOffset - 1;
                        while ( OpLine < OpLine2 )
                        {
                            if ( OP_CODE( OpLine2 ) == ZEND_JMP )
                            {
                                if ( OP_JMP( OpLine2, Head ) < NextOffset )
                                {
                                    Flags |= FLAGS_JMPX_MAP_SWITCH;
                                    NextOffset = OpLine2 - Head + 1;
                                    break;
                                }
                            }
                            else if ( OP_CODE( OpLine2 ) != ZEND_NOP )
                            {
                                break;
                            }
                            OpLine2--;
                        }
                    }
                }
            }

            if ( NextOffset < Offset )
            {
                if ( !( Flags & FLAGS_JMPX_SPECIAL ) )
                {
                    if ( !( Flags & FLAGS_JMPX_CONT ) )
                        BrkContPtr = GetContinue( Stack, NextOffset, Offset );
                    if ( BrkContPtr )
                    {
                        if ( BrkContPtr->Flags & DS_FLAGS_INTERNAL )
                        {
                            BrkContPtr->Flags |= DS_FLAGS_UPDATED;
                            BrkContPtr->Offset = Offset;
                        }
                    }
                }

                End = find_jmp_offset_last( Stack, NextOffset, Offset + 1, Stack->LastOffset );
                if ( End == INVALID_OP_OFFSET )
                {
                    End = Offset;
                    Flags = DS_FLAGS_DO_WHILE_END | DS_FLAGS_END;
                }
                else if ( OP_CODE( Head + End ) == ZEND_JMP )
                {
                    /* do{} while ( 1 ) */
                    Flags = DS_FLAGS_DO_WHILE_TRUE | DS_FLAGS_END;
                }
                else
                {
                    /* do{} while ( x ) */
                    Flags = DS_FLAGS_DO_WHILE_END | DS_FLAGS_END;
                }

                Start = adjust_control_list_start( Stack, NextOffset, End );
                BreakOffset = End + 1;
                if ( ( Flags & DS_FLAGS_MASK ) == DS_FLAGS_DO_WHILE_END )
                {
                    ContinueOffset = scan_prev_output( Stack, NextOffset, Offset ) + 1;
                    /* Php5 */
                    OpLine1 = Head + ContinueOffset;
                    while ( OP_CODE( OpLine1 ) == ZEND_NOP )
                        OpLine1++;
                    ContinueOffset = OpLine1 - Head;
                    Dummy = End;
                }
                else
                {
                    ContinueOffset = NextOffset;
                    Dummy = End + 1;
                }

                Entry.Flags = DS_FLAGS_DO;
                Entry.Type = 0;
                Entry.Start = Start;
                Entry.End = End;
                insert_control_list( Stack, Start, &Entry );

                Entry.Flags = Flags;
                insert_control_list( Stack, Dummy, &Entry );

                /* Insert to continue/break list */
                insert_cont_brk_list( Stack, ContinueOffset, BreakOffset, Start, End, Flags );

                StackPushAscU( &Stack->Skip, End );
            }
            else if ( NextOffset > Offset )
            {
                if ( !( Flags & FLAGS_JMPX_SPECIAL ) )
                {
                    if ( !( Flags & FLAGS_JMPX_BRK ) )
                        BrkContPtr = GetBreak( Stack, NextOffset, Offset );
                    if ( BrkContPtr )
                    {
                        if ( BrkContPtr->Flags & DS_FLAGS_INTERNAL )
                        {
                            BrkContPtr->Flags |= DS_FLAGS_UPDATED;
                            BrkContPtr->Offset = Offset;
                        }
                    }
                }

                OpLine1 = Head + NextOffset - 1;
                OpCode = OP_CODE( OpLine1 );
                /* Special */
                if ( OpCode == ZEND_JMPZNZ )
                {
                    JmpOffset = OpLine1->extended_value;
                }
                else if ( OP_CODE( OpLine1 + 1 ) == ZEND_JMPZNZ )
                {
                    /* while ( ){ if( )break; } */
                    OpLine1++;
                    NextOffset++;
                    OpCode = OP_CODE( OpLine1 );
                    JmpOffset = OP_JMPZNZ( OpLine1, Head );
                }
                else
                {
                    if ( !( Flags & FLAGS_JMPX_SPECIAL ) )
                    {
                        /* See if loop in if-else */
                        if ( find_jmp_middle( Stack, Offset, Offset, NextOffset, &Dummy ) != INVALID_OP_OFFSET )
                        {
                            NextOffset = Dummy;
                            OpLine1 = Head + NextOffset - 1;
                        }

                        /* See if loop in loop */
                        Dummy = NextOffset;
                        while ( INVALID_OP_OFFSET != ( Dummy = find_jmp_small( Stack, Offset, Offset + 1, Dummy, &JmpOffset ) ) )
                        {
                            if ( scan_next_output( Stack, JmpOffset, Offset ) == Offset && OP_CODE( Head + Dummy ) == ZEND_JMP )
                            {
                                Flags |= FLAGS_JMPX_SPECIAL;
                                NextOffset = Dummy + 1;
                                OpLine1 = Head + NextOffset - 1;
                                break;
                            }
                        }

                        /* Skip */
                        while ( OP_CODE( OpLine1 ) == ZEND_NOP )
                            OpLine1--;

                        OpCode = OP_CODE( OpLine1 );
                    }

                    if ( OpCode == ZEND_JMP )
                    {
                        JmpOffset = OP_JMP( OpLine1, Head );
                        /* Php5 */
                        while ( JmpOffset == NextOffset )
                        {
                            OpLine1--;
                            NextOffset--;
                            OpCode = OP_CODE( OpLine1 );
                            if ( OpCode == ZEND_JMP )
                                JmpOffset = OP_JMP( OpLine1, Head );
                            else if ( OpCode == ZEND_JMPZ || OpCode == ZEND_JMPNZ )
                                JmpOffset = OP_JMPX( OpLine1, Head );
                            else if ( OpCode != ZEND_NOP )
                                break;
                        }
                    }
                    else if ( OpCode == ZEND_JMPZ || OpCode == ZEND_JMPNZ )
                    {
                        JmpOffset = OP_JMPX( OpLine1, Head );
                    }
                    else if ( OpCode == ZEND_JMPZNZ )
                    {
                        JmpOffset = OpLine1->extended_value;
                    }
                    else
                    {
                        /* Special */
                        Dummy = find_jmp_small( Stack, Offset, Offset + 1, NextOffset, &JmpOffset );
                        if ( Dummy == INVALID_OP_OFFSET )
                            break;

                        BrkContPtr = GetContinue( Stack, JmpOffset, Offset );
                        if ( BrkContPtr )
                        {
                            NextOffset = BrkContPtr->Break;
                            OpLine1 = Head + NextOffset - 1;
                            OpCode = OP_CODE( OpLine1 );
                        }
                        else
                        {
                            /* See if loop */
                            if ( scan_next_output( Stack, JmpOffset, Offset ) != Offset )
                                break;
                        }
                        Flags |= FLAGS_JMPX_SPECIAL;
                    }
                }

                if ( JmpOffset > Offset )
                {
                    /* See if nest loop */
                    Dummy = find_jmp_small( Stack, Offset, Offset + 1, NextOffset, &JmpOffset );
                    if ( Dummy == INVALID_OP_OFFSET )
                        break;

                    if ( scan_next_output( Stack, JmpOffset, Offset ) != Offset )
                        break;
                    Flags |= FLAGS_JMPX_SPECIAL;
                }
                else
                {
                    /* Continue */
                    BrkContPtr = GetContinue( Stack, JmpOffset, Offset );
                    if ( BrkContPtr )
                    {
                        if ( BrkContPtr->Flags & DS_FLAGS_INTERNAL )
                        {
                            BrkContPtr->Flags |= DS_FLAGS_UPDATED;
                            BrkContPtr->Offset = Offset;
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                if ( OpCode == ZEND_JMP )
                {
                    if ( !( Flags & FLAGS_JMPX_SPECIAL ) )
                    {
                        /* Seek for other jmp */
                        Top = StackFindAscU( &Stack->Jmp, NextOffset - 1 );
                        while ( Top < StackCountU( &Stack->Jmp ) )
                        {
                            OpLine2 = Head + StackAtU( &Stack->Jmp, Top );
                            if ( OP_JMP( OpLine2, Head ) == JmpOffset )
                                break;
                            Top++;
                        }
                        if ( Top < StackCountU( &Stack->Jmp ) )
                            break;
                    }

                    OpLine2 = OpLine1;
                    /* Skip jmp */
                    while ( Head < OpLine2 )
                    {
                        if ( OP_CODE( OpLine2 ) == ZEND_JMP && OP_JMP( OpLine2, Head ) == JmpOffset )
                            StackPushAscU( &Stack->Skip, OpLine2 - Head );
                        else if ( OP_CODE( OpLine2 ) != ZEND_NOP )
                            break;
                        OpLine2--;
                    }
                }
                else if ( OpCode == ZEND_RETURN || OpCode == ZEND_EXIT )
                {
                    /* Nothing */
                }
                else if ( OpCode == ZEND_JMPZNZ )
                {
                    if ( JmpOffset == OpLine1->extended_value )
                    {
                        /* if( x )break; */
                        Stack->Offset = OpLine1 - Head;
                        Entry.Flags = DS_FLAGS_IF;
                        Entry.Type = DS_TYPE_SKIP_REVERSE | DS_TYPE_BRK;
                        Entry.Start = NextOffset - 1;
                        Entry.End = NextOffset - 1;
                        insert_control_list( Stack, NextOffset - 1, &Entry );

                        Entry.Flags = DS_FLAGS_IF_END | DS_FLAGS_END;
                        insert_control_list( Stack, NextOffset, &Entry );

                        /* Skip */
                        StackPushAscU( &Stack->Skip, NextOffset - 1 );
                        Stack->Offset = Offset;
                    }
                }
                else
                {
                    /* break; */
                    Entry.Flags = DS_FLAGS_BRK | DS_FLAGS_END;
                    Entry.Type = DS_TYPE_NOINDENT;
                    Entry.Start = Offset + 1;
                    Entry.End = NextOffset;
                    insert_control_list( Stack, NextOffset, &Entry );
                }

                NextOutput = scan_prev_output( Stack, JmpOffset, Offset );
                if ( NextOutput == JmpOffset - 1 )
                {
                    /* While ( ){} */
                    Dummy = 1;
                }
                else
                {
                    if ( find_jmp_large( Stack, Offset, JmpOffset, Offset, &Dummy ) != INVALID_OP_OFFSET )
                        break;
                    Dummy = 0;
                }

                if ( Dummy )
                {
                    Start = Offset;
                    End = NextOffset;
                    ContinueOffset = JmpOffset;
                    BreakOffset = NextOffset;

                    /* While ( ){} */
                    Entry.Flags = DS_FLAGS_WHILE;
                    Entry.Type = 0;
                    Entry.Start = Start;
                    Entry.End = End;
                    insert_control_list( Stack, Start, &Entry );

                    Entry.Flags = DS_FLAGS_WHILE_END | DS_FLAGS_END;
                    insert_control_list( Stack, End, &Entry );

                    Flags = DS_FLAGS_WHILE;

                    StackPushAscU( &Stack->Skip, Offset );
                }
                else
                {
                    Start = JmpOffset;
                    End = NextOffset - 1;
                    BreakOffset = NextOffset;
                    if ( OpCode == ZEND_JMP )
                    {
                        /* do{} while ( 1 ) */
                        ContinueOffset = JmpOffset;
                        Flags = DS_FLAGS_DO_WHILE_TRUE | DS_FLAGS_END;
                    }
                    else
                    {
                        /* do{} while ( ) */
                        ContinueOffset = scan_prev_output( Stack, Offset, NextOffset ) + 1;
                        Flags = DS_FLAGS_DO_WHILE_END | DS_FLAGS_END;
                    }

                    Entry.Flags = DS_FLAGS_DO;
                    Entry.Type = 0;
                    Entry.Start = Start;
                    Entry.End = End;
                    insert_control_list( Stack, Start, &Entry );

                    Entry.Flags = Flags;
                    insert_control_list( Stack, End, &Entry );

                    Flags &= DS_FLAGS_MASK;

                    StackPushAscU( &Stack->Skip, End );
                }

                /* Insert to continue/break list */
                insert_cont_brk_list( Stack, ContinueOffset, BreakOffset, Start, End, Flags );
            }
            else
            {
                Start = Offset;
                End = Offset;

                /* do{} while ( 1 ) */
                Entry.Flags = DS_FLAGS_DO;
                Entry.Type = 0;
                Entry.Start = Start;
                Entry.End = End;
                insert_control_list( Stack, Start, &Entry );

                Entry.Flags = DS_FLAGS_DO_WHILE_TRUE | DS_FLAGS_END;
                Entry.Type = DS_TYPE_TOP;
                insert_control_list( Stack, End + 1, &Entry );

                StackPushAscU( &Stack->Skip, Start );
            }
            /* Delete */
            delete_scan_control_list( &Stack->ScanList, Offset );
            break;

        case ZEND_JMPZNZ :
            Flags = 0;
            Type = 0;
            NextOffset = OP_JMPZNZ( OpLine, Head );
            ExtendOffset = OP_EX_VALUE( OpLine );
            OpLine1 = Head + NextOffset - 1;
            OpLine2 = Head + ExtendOffset - 1;

            if ( ExtendOffset < Offset || OP_CODE( OpLine2 ) != ZEND_JMP )
            {
                /* Special */
                break;
            }
            else if ( NextOffset < Offset )
            {
                /* Nest loop */
                BrkContPtr = GetContinue( Stack, NextOffset, ExtendOffset );
                if ( BrkContPtr )
                {
                    ContinueOffset = BrkContPtr->Continue;
                    BreakOffset = BrkContPtr->Break;
                    NextOffset = BreakOffset;
                    OpLine1 = Head + NextOffset - 1;
                    /* Skip */
                    while ( OP_CODE( OpLine1 ) == ZEND_NOP )
                    {
                        OpLine1--;
                        NextOffset--;
                    }

                    /* Loop in if-else */
                    while ( OP_CODE( OpLine1 ) == ZEND_JMP && OP_JMP( OpLine1, Head ) > BreakOffset )
                    {
                        OpLine1--;
                        NextOffset--;
                    }

                    /* Loop jump back */
                    while ( OP_CODE( OpLine1 ) == ZEND_JMP && OP_JMP( OpLine1, Head ) == ContinueOffset )
                    {
                        OpLine1--;
                        NextOffset--;
                    }
                    Flags |= 1;
                }
                else
                {
                    /* Not ready */
                    break;
                }
            }
            else if ( OP_CODE( OpLine1 ) == ZEND_JMPNZ && OP1_VAR( OpLine1 ) == OP1_VAR( OpLine ) && OP1_TYPE( OpLine1 ) == OP1_TYPE( OpLine ) )
            {
                /* Special */
                StackPushAscU( &Stack->Skip, Offset );
                break;
            }

            /* See if in if-else */
            if ( find_jmp_middle( Stack, Offset, Offset, NextOffset, &Dummy ) != INVALID_OP_OFFSET )
            {
                NextOffset = Dummy - 1;
                OpLine1 = Head + NextOffset - 1;
            }

            /* Skip */
            while ( OP_CODE( OpLine1 ) == ZEND_NOP )
            {
                OpLine1--;
                NextOffset--;
            }

            Start = OP_JMP( OpLine2, Head );
            OpCode = OP_CODE( OpLine1 );
            /* Special */
            if ( OpCode == ZEND_JMPZNZ )
            {
                JmpOffset = OpLine1->extended_value;
            }
            else if ( OP_CODE( OpLine1 + 1 ) == ZEND_JMPZNZ )
            {
                /* while ( ){ if( )break; } */
                OpLine1++;
                NextOffset++;
                OpCode = OP_CODE( OpLine1 );
                JmpOffset = OP_JMPZNZ( OpLine1, Head );
            }
            else
            {
                if ( OpCode == ZEND_JMP )
                {
                    JmpOffset = OP_JMP( OpLine1, Head );
                    /* Php5 */
                    while ( JmpOffset == NextOffset )
                    {
                        OpLine1--;
                        NextOffset--;
                        OpCode = OP_CODE( OpLine1 );
                        if ( OpCode == ZEND_JMP )
                            JmpOffset = OP_JMP( OpLine1, Head );
                        else if ( OpCode == ZEND_JMPZ || OpCode == ZEND_JMPNZ )
                            JmpOffset = OP_JMPX( OpLine1, Head );
                        else if ( OpCode != ZEND_NOP )
                            break;
                    }
                }
                else if ( OpCode == ZEND_JMPZ || OpCode == ZEND_JMPNZ )
                {
                    JmpOffset = OP_JMPX( OpLine1, Head );
                }
                else
                {
                    /* Special */
                    if ( find_jmp_offset( Stack, Offset + 1, Offset + 1, NextOffset ) == INVALID_OP_OFFSET )
                    {
                        if ( find_jmp_offset( Stack, Start, Offset + 1, NextOffset ) == INVALID_OP_OFFSET )
                            break;

                        JmpOffset = Start;
                    }
                    else
                    {
                        JmpOffset = Offset + 1;
                    }

                    /* Seek for end */
                    if ( find_jmp_middle( Stack, Offset, Offset, NextOffset, &Dummy ) != INVALID_OP_OFFSET )
                    {
                        NextOffset = Dummy;
                        /* See if if-else */
                        OpLine1 = Head + NextOffset - 1;
                        if ( OP_CODE( OpLine1 ) == ZEND_JMP && OP_JMP( OpLine1, Head ) >= NextOffset )
                        {
                            OpLine1--;
                            NextOffset--;
                        }
                    }
                }
            }

            if ( JmpOffset > ExtendOffset )
            {
                /* See if nest loop */
                if ( find_jmp_offset( Stack, Offset + 1, Offset + 1, NextOffset ) == INVALID_OP_OFFSET )
                {
                    if ( find_jmp_offset( Stack, Start, Offset + 1, NextOffset ) == INVALID_OP_OFFSET )
                        break;

                    ContinueOffset = Start;
                }
                else
                {
                    ContinueOffset = Offset + 1;
                }
            }
            else
            {
                if ( JmpOffset == Offset + 1 )
                {
                    /* OK */
                    ContinueOffset = JmpOffset;
                }
                else if ( JmpOffset == Start )
                {
                    /* for ( ; condition; ) */
                    ContinueOffset = JmpOffset;
                    Type = DS_TYPE_SKIP_BACK;
                }
                else if ( Flags )
                {
                    ContinueOffset = Offset + 1;
                }
                else
                {
                    /* BUG */
                    if ( GET_GS_FLAGS( ) & GS_FLAGS_BUG )
                        dump_string_ex( Stack, _T( "//[BUG][%6d]for end bracket unknown\r\n" ), Offset );
                    break;
                }
            }

            OpCode = OP_CODE( OpLine1 );
            if ( OpCode == ZEND_JMP )
            {
                OpLine2 = OpLine1;
                /* Skip jmp */
                while ( OpLine < OpLine2 )
                {
                    if ( OP_CODE( OpLine2 ) == ZEND_JMP )
                    {
                        Dummy = OP_JMP( OpLine2, Head );
                        if ( Dummy == ContinueOffset )
                            StackPushAscU( &Stack->Skip, OpLine2 - Head );
                        else if ( Dummy != JmpOffset )
                            break;
                    }
                    else if ( OP_CODE( OpLine2 ) != ZEND_NOP )
                    {
                        break;
                    }
                    OpLine2--;
                }
            }
            else if ( OpCode == ZEND_RETURN || OpCode == ZEND_EXIT )
            {
                /* Nothing */
            }
            else if ( OpCode == ZEND_JMPZNZ )
            {
                if ( JmpOffset == OpLine1->extended_value )
                {
                    /* if( x )break; */
                    Stack->Offset = OpLine1 - Head;
                    Entry.Flags = DS_FLAGS_IF;
                    Entry.Type = DS_TYPE_SKIP_REVERSE | DS_TYPE_BRK;
                    Entry.Start = NextOffset - 1;
                    Entry.End = NextOffset - 1;
                    insert_control_list( Stack, NextOffset - 1, &Entry );

                    Entry.Flags = DS_FLAGS_IF_END | DS_FLAGS_END;
                    insert_control_list( Stack, NextOffset, &Entry );

                    /* Skip */
                    StackPushAscU( &Stack->Skip, NextOffset - 1 );
                    Stack->Offset = Offset;
                }
            }
            else if ( Flags )
            {
                /* Nest loop */
            }
            else
            {
                /* break; */
                Entry.Flags = DS_FLAGS_BRK | DS_FLAGS_END;
                Entry.Type = DS_TYPE_NOINDENT;
                Entry.Start = Offset + 1;
                Entry.End = NextOffset;
                insert_control_list( Stack, NextOffset, &Entry );
            }

            /* End */
            BreakOffset = NextOffset;
            End = NextOffset;

            Entry.Flags = DS_FLAGS_FOR | DS_FLAGS_END;
            Entry.Type = 0;
            Entry.Start = Start;
            Entry.End = End;
            insert_control_list( Stack, Start, &Entry );

            Entry.Flags = DS_FLAGS_FOR_END | DS_FLAGS_END;
            Entry.Start = Start;
            Entry.End = End;
            insert_control_list( Stack, End, &Entry );

            Entry.Flags = DS_FLAGS_FORBRACKET_IN;
            Entry.Start = Offset;
            Entry.End = End;
            insert_control_list( Stack, Offset, &Entry );

            Entry.Flags = DS_FLAGS_FORBRACKET_END | DS_FLAGS_END;
            Entry.Type = Type;
            Entry.Start = ExtendOffset;
            Entry.End = End;
            insert_control_list( Stack, ExtendOffset, &Entry );

            /* Insert to continue/break list */
            insert_cont_brk_list( Stack, ContinueOffset, BreakOffset, Start, End, DS_FLAGS_FOR );

            /* Skip */
            StackPushAscU( &Stack->Skip, Offset );
            StackPushAscU( &Stack->Skip, ExtendOffset - 1 );
            /* Delete */
            delete_scan_control_list( &Stack->ScanList, Offset );
            break;

        case ZEND_FE_FETCH :
            End = Stack->LastOffset - 1;
            Top = StackFindLargeAscU( &Stack->ForEach, Offset );
            if ( Top )
            {
                Top--;
                while ( Top < StackCountU( &Stack->ForEach ) )
                {
                    OpLine1 = Head + StackAtU( &Stack->ForEach, Top );
                    if ( OP1_VAR( OpLine1 ) == OP1_VAR( OpLine ) && OP1_TYPE( OpLine1 ) == OP1_TYPE( OpLine ) )
                        End = OpLine1 - Head;
                    Top++;
                }
            }

            OpLine2 = Tail;
            Top = StackFindLargeAscU( &Stack->SwitchFree, Offset );
            if ( Top )
            {
                Top--;
                while ( Top < StackCountU( &Stack->SwitchFree ) )
                {
                    Dummy = StackAtU( &Stack->SwitchFree, Top );
                    if ( Dummy > End )
                        break;

                    OpLine1 = Head + Dummy;
                    /* See generate_free_foreach_copy( zend_compile.c ) */
                    if ( OpLine1->extended_value == 1 &&
                        OP1_VAR( OpLine1 ) == OP1_VAR( OpLine ) &&
                        OP1_TYPE( OpLine1 ) == OP1_TYPE( OpLine ) )
                    {
                        OpLine2 = OpLine1;
                        if ( !is_special_switch_free( OpLine1, Stack->Tail ) )
                            break;
                    }
                    Top++;
                }
            }

            /* New start */
            OpLine1 = OpLine - 1;
            while ( Head <= OpLine1 && OP_CODE( OpLine1 ) == ZEND_NOP )
                OpLine1--;
            Start = OpLine1 - Head + 1;
            End = OpLine2 - Head;

            Entry.Flags = DS_FLAGS_FOREACH;
            Entry.Type = 0;
            Entry.Start = Start;
            Entry.End = End;
            insert_control_list( Stack, Start, &Entry );

            Entry.Flags = DS_FLAGS_FOREACH_END | DS_FLAGS_END;
            insert_control_list( Stack, End, &Entry );

            /* Insert to continue/break list */
            insert_cont_brk_list( Stack, Start, End, Start, End, DS_FLAGS_FOREACH );

            if ( OpLine2 < Tail )
            {
                /* Skip ZEND_SWITCH_FREE */
                StackPushAscU( &Stack->Skip, End );

                OpLine2--;
                /* Skip */
                while ( OP_CODE( OpLine2 ) == ZEND_NOP )
                    OpLine2--;

                if ( OP_CODE( OpLine2 ) == ZEND_JMP && OP_JMP( OpLine2, Head ) == Start )
                {
                    do
                    {
                        StackPushAscU( &Stack->Skip, OpLine2 - Head );
                        OpLine2--;
                    } while ( OP_CODE( OpLine2 ) == ZEND_JMP && OP_JMP( OpLine2, Head ) == Start || OP_CODE( OpLine2 ) == ZEND_NOP );
                }
                else
                {
                    if ( OP_CODE( OpLine2 ) == ZEND_JMP )
                    {
                        Dummy = OP_JMP( OpLine2, Head );
                        NextOffset = OpLine2 - Head;
                        if ( Offset < Dummy && Dummy < NextOffset && is_jump_to_loop_back( Stack, Dummy, Start ) )
                            StackPushAscU( &Stack->Skip, NextOffset );
                    }
                    else if ( OP_CODE( OpLine2 ) == ZEND_JMPZNZ )
                    {
                        /* if( x )continue; else break; */
                        Entry.Flags = DS_FLAGS_IF;
                        Entry.Type = DS_TYPE_SKIP_REVERSE | DS_TYPE_EXTEND | DS_TYPE_CONT;
                        Entry.Start = End - 1;
                        Entry.End = End - 1;
                        insert_control_list( Stack, End - 1, &Entry );

                        Entry.Flags = DS_FLAGS_IF_END | DS_FLAGS_END;
                        insert_control_list( Stack, End, &Entry );

                        /* Skip */
                        StackPushAscU( &Stack->Skip, End - 1 );
                    }
                    else if ( OP_CODE( OpLine2 ) == ZEND_RETURN || OP_CODE( OpLine2 ) == ZEND_EXIT )
                    {
                        /* Nothing */
                    }
                    else
                    {
                        /* break; */
                        Entry.Flags = DS_FLAGS_BRK | DS_FLAGS_END;
                        Entry.Type = DS_TYPE_NOINDENT;
                        Entry.Start = Start + 1;
                        Entry.End = End;
                        insert_control_list( Stack, End, &Entry );
                    }
                }
            }
            /* Delete */
            delete_scan_control_list( &Stack->ScanList, Offset );
            break;

        case ZEND_CASE :
            Start = Offset;
            End = INVALID_OP_OFFSET;
            ExtendOffset = INVALID_OP_OFFSET;
            Top = StackFindLargeAscU( &Stack->SwitchFree, Offset );
            if ( Top )
            {
                Top--;
                while ( Top < StackCountU( &Stack->SwitchFree ) )
                {
                    Dummy = StackAtU( &Stack->SwitchFree, Top );
                    OpLine1 = Head + Dummy;
                    if ( OP1_TYPE( OpLine1 ) == OP1_TYPE( OpLine ) && OP1_VAR( OpLine1 ) == OP1_VAR( OpLine ) )
                    {
                        if ( !is_special_switch_free( OpLine1, Tail ) )
                        {
                            End = Dummy;
                            break;
                        }
                        else
                        {
                            End = Dummy + 2;
                        }
                    }
                    Top++;
                }
            }

            StackReinitU( &Stack->Common );
            Top = StackFindAscU( &Stack->SwitchCase, Offset );
            if ( Top )
            {
                while ( Top < StackCountU( &Stack->SwitchCase ) )
                {
                    Dummy = StackAtU( &Stack->SwitchCase, Top );
                    if ( Dummy >= End )
                        break;

                    /* Next case */
                    OpLine1 = Head + Dummy;
                    if (  OP1_VAR( OpLine1 ) == OP1_VAR( OpLine ) && OP1_TYPE( OpLine1 ) == OP1_TYPE( OpLine ) &&
                        OPR_VAR( OpLine1 ) == OPR_VAR( OpLine ) && OPR_TYPE( OpLine1 ) == OPR_TYPE( OpLine ) )
                    {
                        if ( !is_control_list( Stack, Start, Dummy ) )
                            break;

                        /* Next case */
                        StackPushU( &Stack->Common, Dummy );
                    }
                    Top++;
                }
                /* End case */
            }
            else
            {
                break;
            }

            while ( StackPopBottomU( &Stack->Common, &NextOffset ) )
            {
                OpLine1 = Head + Offset + 1;
                while ( OP_CODE( OpLine1 ) == ZEND_NOP )
                    OpLine1++;

                if ( OP_CODE( OpLine1 ) == ZEND_JMPZ || OP_CODE( OpLine1 ) == ZEND_JMPZNZ )
                {
                    if ( OP_CODE( OpLine1 ) == ZEND_JMPZ )
                        JmpOffset = OP_JMPX( OpLine1, Head );
                    else
                        JmpOffset = OP_JMPZNZ( OpLine1, Head );
                    /* End case */
                    if ( JmpOffset > NextOffset )
                    {
                        break;
                    }
                    else if ( JmpOffset != NextOffset )
                    {
                        OpLine2 = Head + JmpOffset - 1;
                        if ( OP_CODE( OpLine2 ) != ZEND_JMP && OP_CODE( OpLine2 ) != ZEND_RETURN && OP_CODE( OpLine2 ) != ZEND_EXIT )
                            break;

                        NextOutput = scan_next_output( Stack, JmpOffset, NextOffset );
                        if ( NextOutput != NextOffset )
                            break;
                    }

                    if ( JmpOffset < Offset )
                    {
                        BrkContPtr = GetContinue( Stack, NextOffset, Offset );
                        if ( BrkContPtr )
                        {
                            /* Loop */
                            End = BrkContPtr->Break;
                        }
                        else
                        {
                            /* Default */
                            ExtendOffset = JmpOffset;
                            Start = JmpOffset;
                        }
                    }
                    StackPushAscU( &Stack->Skip, OpLine1 - Head );
                }
                else if ( OP_CODE( OpLine1 ) == ZEND_JMPNZ )
                {
                    /* Case x : {} case x1 : {} ... case xx : break */
                    JmpOffset = OP_JMPX( OpLine1, Head );
                    if ( JmpOffset < Offset )
                    {
                        BrkContPtr = GetContinue( Stack, NextOffset, Offset );
                        if ( BrkContPtr )
                        {
                            /* Loop */
                            Entry.Flags = DS_FLAGS_BRK;
                            Entry.Type = DS_TYPE_NOINDENT;
                            Entry.Start = Offset + 1;
                            Entry.End = Offset + 1;
                            insert_control_list( Stack, Offset + 1, &Entry );
                            End = BrkContPtr->Break;
                        }
                        else
                        {
                            /* Default */
                            ExtendOffset = JmpOffset;
                            Start = JmpOffset;
                        }
                    }
                    StackPushAscU( &Stack->Skip, OpLine1 - Head );
                }
                else if ( OP_CODE( OpLine1 ) == ZEND_RETURN || OP_CODE( OpLine1 ) == ZEND_EXIT )
                {
                    /* End case? */
                    JmpOffset = NextOffset;
                }
                else
                {
                    JmpOffset = NextOffset;
                    break;
                }

                /* Skip this */
                StackPushAscU( &Stack->Skip, Offset );

                /* Seek for case end */
                OpLine2 = Head + NextOffset - 1;
                while ( Head < OpLine2 )
                {
                    if ( OP_CODE( OpLine2 ) == ZEND_JMP || OP_CODE( OpLine2 ) == ZEND_RETURN || OP_CODE( OpLine2 ) == ZEND_EXIT )
                        break;
                    OpLine2--;
                }
                if ( Head == OpLine2 )
                    Dummy = NextOffset;
                else
                    Dummy = OpLine2 - Head;

                Stack->Offset = Offset;
                Entry.Flags = DS_FLAGS_SWITCH_CASE;
                Entry.Type = 0;
                Entry.Start = Offset;
                Entry.End = Dummy;
                insert_control_list( Stack, Offset, &Entry );

                /* Delete */
                delete_scan_control_list( &Stack->ScanList, Offset );
                /* Save case */
                Offset = NextOffset;
            }

            OpLine1 = Head + Offset + 1;
            while ( OP_CODE( OpLine1 ) == ZEND_NOP )
                OpLine1++;

            if ( OP_CODE( OpLine1 ) == ZEND_JMPZ || OP_CODE( OpLine1 ) == ZEND_JMPZNZ )
            {
                StackPushAscU( &Stack->Skip, OpLine1 - Head );
                if ( OP_CODE( OpLine1 ) == ZEND_JMPZ )
                    JmpOffset = OP_JMPX( OpLine1, Head );
                else
                    JmpOffset = OP_JMPZNZ( OpLine1, Head );
                if ( JmpOffset < Offset )
                {
                    BrkContPtr = GetContinue( Stack, NextOffset, Offset );
                    if ( BrkContPtr )
                    {
                        /* Loop */
                        End = BrkContPtr->Break;
                    }
                    else
                    {
                        /* Default */
                        ExtendOffset = JmpOffset;
                        Start = JmpOffset;

                        if ( find_jmp_large_max( Stack, Offset, Start, Offset, &JmpOffset ) != INVALID_OP_OFFSET )
                            if ( End == INVALID_OP_OFFSET || End < JmpOffset )
                                End = JmpOffset;
                    }
                }
                else
                {
                    if ( End == INVALID_OP_OFFSET || End < JmpOffset )
                    {
                        End = JmpOffset;
                        /* See if default */
                        OpLine2 = Head + End;
                        if ( OP_CODE( OpLine2 ) == ZEND_JMPZ && OP_JMPX( OpLine2, Head ) < End )
                            End++;
                    }
                    else if ( JmpOffset < End )
                    {
                        /* Default */
                        ExtendOffset = JmpOffset;
                    }
                }
            }
            else if ( OP_CODE( OpLine1 ) == ZEND_JMPNZ )
            {
                StackPushAscU( &Stack->Skip, OpLine1 - Head );
                /* Case x : {} case x1 : {} ... case xx : break */
                JmpOffset = OP_JMPX( OpLine1, Head );
                if ( JmpOffset < Offset )
                {
                    BrkContPtr = GetContinue( Stack, NextOffset, Offset );
                    if ( BrkContPtr )
                    {
                        /* Loop */
                        Entry.Flags = DS_FLAGS_BRK;
                        Entry.Type = DS_TYPE_NOINDENT;
                        Entry.Start = Offset + 1;
                        Entry.End = Offset + 1;
                        insert_control_list( Stack, Offset + 1, &Entry );
                        End = BrkContPtr->Break;
                    }
                    else
                    {
                        /* Default */
                        ExtendOffset = JmpOffset;
                        Start = JmpOffset;

                        if ( find_jmp_large_max( Stack, Offset, Start, Offset, &JmpOffset ) != INVALID_OP_OFFSET )
                            if ( End == INVALID_OP_OFFSET || End < JmpOffset )
                                End = JmpOffset;
                    }
                }
                else
                {
                    if ( End == INVALID_OP_OFFSET || End < JmpOffset )
                        End = JmpOffset;
                }
            }
            else if ( OP_CODE( OpLine1 ) == ZEND_RETURN || OP_CODE( OpLine1 ) == ZEND_EXIT )
            {
                JmpOffset = OpLine1 - Head;
                if ( End == INVALID_OP_OFFSET || Head + End < OpLine1 )
                    End = JmpOffset;
            }
            else
            {
                JmpOffset = OpLine1 - Head;
                if ( End == INVALID_OP_OFFSET || Head + End < OpLine1 )
                    End = JmpOffset;
            }

            /* Find end offset */
            find_jmp_large_max( Stack, Offset, Start, JmpOffset, &Dummy );
            if ( End == INVALID_OP_OFFSET || End < Dummy )
                End = Dummy;

            /* Skip */
            OpLine2 = Head + End - 1;
            if ( OP_CODE( OpLine2 ) == ZEND_JMPZ )
            {
                /* Update default position */
                ExtendOffset = OP_JMPX( OpLine2, Head );
                OpLine1 = Head + ExtendOffset;

                /* Skip */
                while ( OP_CODE( OpLine1 ) == ZEND_NOP )
                    OpLine1++;

                if ( ( OP_CODE( OpLine1 ) == ZEND_QM_ASSIGN || OP_CODE( OpLine1 ) == ZEND_BOOL ) &&
                    OP1_VAL_TYPE( OpLine1 ) == IS_BOOL && OP1_VAL( OpLine1 )->value.lval == TRUE )
                    StackPushAscU( &Stack->Skip, ExtendOffset );
                StackPushAscU( &Stack->Skip, End - 1 );
            }
            else if ( OP_CODE( OpLine2 + 1 ) == ZEND_JMPZ )
            {
                /* Update default position */
                ExtendOffset = OP_JMPX( OpLine2 + 1, Head );
                OpLine1 = Head + ExtendOffset;

                /* Skip */
                while ( OP_CODE( OpLine1 ) == ZEND_NOP )
                    OpLine1++;

                if ( ( OP_CODE( OpLine1 ) == ZEND_QM_ASSIGN || OP_CODE( OpLine1 ) == ZEND_BOOL ) &&
                    OP1_VAL_TYPE( OpLine1 ) == IS_BOOL && OP1_VAL( OpLine1 )->value.lval == TRUE )
                    StackPushAscU( &Stack->Skip, ExtendOffset );
                StackPushAscU( &Stack->Skip, End );
            }
            else if ( OP_CODE( OpLine2 ) == ZEND_JMP )
            {
                if ( OP_JMP( OpLine2, Head ) == JmpOffset )
                {
                    /* Php5 */
                    Dummy = find_jmp_offset_last( Stack, JmpOffset, End, Stack->LastOffset );
                    if ( Dummy != INVALID_OP_OFFSET )
                    {
                        ExtendOffset = JmpOffset;
                        End = Dummy + 1;
                        StackPushAscU( &Stack->Skip, Dummy );
                    }
                    if ( JmpOffset == ExtendOffset )
                    {
                        OpLine2--;
                        if ( OP_CODE( OpLine2 ) == ZEND_JMP && OP_JMP( OpLine2, Head ) == End )
                            StackPushAscU( &Stack->Skip, End - 1 );
                    }
                }
            }

            OpLine = Head + Offset;
            OpLine1 = Head + JmpOffset;
            if ( OP_CODE( OpLine + 1 ) == ZEND_JMPZ &&
                ( OP_CODE( OpLine1 ) == ZEND_QM_ASSIGN || OP_CODE( OpLine1 ) == ZEND_BOOL ) &&
                OP1_VAL_TYPE( OpLine1 ) == IS_BOOL && OP1_VAL( OpLine1 )->value.lval == TRUE )
            {
                ExtendOffset = OpLine1 - Head;
                Dummy = find_jmp_offset_last( Stack, ExtendOffset, Offset, Stack->LastOffset );
                if ( Dummy != INVALID_OP_OFFSET )
                    End = Dummy + 1;
                /* Skip bool TRUE */
                StackPushAscU( &Stack->Skip, ExtendOffset );
            }
            else if ( OP_CODE( OpLine + 1 ) == ZEND_JMPNZ &&
                ( OP_CODE( OpLine1 - 1 ) == ZEND_QM_ASSIGN || OP_CODE( OpLine1 - 1 ) == ZEND_BOOL ) &&
                OP1_VAL_TYPE( OpLine1 - 1 ) == IS_BOOL && OP1_VAL( OpLine1 - 1 )->value.lval == TRUE )
            {
                ExtendOffset = OpLine1 - Head - 1;
                Dummy = find_jmp_offset_last( Stack, ExtendOffset, Offset, Stack->LastOffset );
                if ( Dummy != INVALID_OP_OFFSET )
                    End = Dummy + 1;
                /* Skip bool TRUE */
                StackPushAscU( &Stack->Skip, ExtendOffset - 1 );
            }

            /* Skip last case */
            StackPushAscU( &Stack->Skip, Offset );

            /* Set offset */
            Stack->Offset = Offset;

            /* Type */
            Entry.Type = 0;

            /* See if have default */
            if ( ExtendOffset != INVALID_OP_OFFSET && ExtendOffset < End )
            {
                Entry.Flags = DS_FLAGS_SWITCH_DEFAULT;
                Entry.Start = ExtendOffset;
                Entry.End = End;
                insert_control_list( Stack, ExtendOffset, &Entry );
                NextOffset = ExtendOffset;
            }
            else
            {
                NextOffset = End;
            }

            /* Switch */
            Entry.Flags = DS_FLAGS_SWITCH;
            Entry.Start = Start;
            Entry.End = End;
            insert_control_list( Stack, Start, &Entry );

            /* Last case */
            Entry.Flags = DS_FLAGS_SWITCH_CASE;
            Entry.Start = Offset;
            Entry.End = NextOffset;
            insert_control_list( Stack, Offset, &Entry );

            /* Switch end */
            Entry.Flags = DS_FLAGS_SWITCH_END | DS_FLAGS_END;
            insert_control_list( Stack, End, &Entry );

            /* Insert to continue/break list */
            insert_cont_brk_list( Stack, End, End, Start, End, DS_FLAGS_SWITCH );

            /* Delete */
            delete_scan_control_list( &Stack->ScanList, Offset );
            break;
        }
    }
    StackSetBottomU( &Stack->Skip, 0 );
    StackSetBottomU( &Stack->SkipOnce, 0 );

    /* Next step */
    Stack->Step++;

    /* Zap item marked as deleted */
    zap_scan_control_list( &Stack->ScanList, Offset );

    /* Set to start */
    StackSetBottomT( &Stack->ScanList, 0 );

    /* Third scan */
    while ( StackPopBottomT( &Stack->ScanList, &Scan ) )
    {
        Offset = Scan->Key;
        OpLine = Head + Offset;
        Stack->Offset = Offset;
        Stack->OpLine = OpLine;

        /* Skip */
        if ( StackBottomU( &Stack->Skip, &Dummy ) )
        {
            while ( StackBottomU( &Stack->Skip, &Dummy ) && Dummy < Offset )
                StackPopBottomU( &Stack->Skip, NULL );

            /* Skip this */
            if ( Dummy == Offset )
            {
                StackPopBottomU( &Stack->Skip, NULL );
                continue;
            }
        }

        /* Skip Once */
        if ( StackBottomU( &Stack->SkipOnce, &Dummy ) )
        {
            while ( StackBottomU( &Stack->SkipOnce, &Dummy ) && Dummy < Offset )
                StackPopBottomU( &Stack->SkipOnce, NULL );

            /* Skip this */
            if ( Dummy == Offset )
            {
                StackPopBottomU( &Stack->SkipOnce, NULL );
                continue;
            }
        }

        switch ( OP_CODE( OpLine ) )
        {
        case ZEND_JMP :
            NextOffset = OP_JMP( OpLine, Head );
            if ( NextOffset < Offset )
            {
                /* Switch( ){ default : ... case : ... } */
                if ( NextOffset > 0 )
                {
                    OpLine1 = Head + NextOffset - 1;
                    if ( OP_CODE( OpLine1 ) == ZEND_JMP )
                    {
                        OpLine2 = Head + OP_JMP( OpLine1, Head );
                        if ( OP_CODE( OpLine2 ) == ZEND_CASE )
                        {
                            StackPushAscU( &Stack->Skip, Offset );
                            break;
                        }
                    }
                }

                /* See if exist */
                BrkContPtr = GetContinue( Stack, NextOffset, Offset );
                if ( BrkContPtr )
                {
                    if ( !( BrkContPtr->Flags & DS_FLAGS_INTERNAL ) )
                        break;
                }

                OpLine1 = Head + NextOffset - 1;
                Dummy = OP_JMP( OpLine1, Head );
                if ( Offset && OP_CODE( OpLine1 ) == ZEND_JMP && NextOffset < Dummy && Dummy < Offset )
                {
                    /* for ( ; ; ... ) */
                    Start = NextOffset - 1;
                    End = Offset + 1;
                    ExtendOffset = Dummy;
                    ContinueOffset = NextOffset;
                    BreakOffset = Offset + 1;

                    Entry.Flags = DS_FLAGS_FOR | DS_FLAGS_END;
                    Entry.Type = 0;
                    Entry.Start = Start;
                    Entry.End = End;
                    insert_control_list( Stack, Start, &Entry );

                    Entry.Flags = DS_FLAGS_FOR_END | DS_FLAGS_END;
                    Entry.Start = Start;
                    Entry.End = End;
                    insert_control_list( Stack, End, &Entry );

                    Entry.Flags = DS_FLAGS_FORBRACKET_IN;
                    Entry.Type = DS_TYPE_EMPTY;
                    Entry.Start = NextOffset;
                    Entry.End = End;
                    insert_control_list( Stack, NextOffset, &Entry );

                    Entry.Flags = DS_FLAGS_FORBRACKET_END | DS_FLAGS_END;
                    Entry.Type = 0;
                    Entry.Start = ExtendOffset;
                    Entry.End = End;
                    insert_control_list( Stack, ExtendOffset, &Entry );

                    /* Insert to continue/break list */
                    insert_cont_brk_list( Stack, ContinueOffset, BreakOffset, Start, End, DS_FLAGS_FOR );
                }
                else
                {
                    End = Offset;
                    JmpOffset = NextOffset;
                    Start = adjust_control_list_start( Stack, NextOffset, End );

                    /* Seek for other jmp */
                    Top = StackFindAscU( &Stack->Jmp, Offset );
                    while ( Top < StackCountU( &Stack->Jmp ) )
                    {
                        OpLine1 = Head + StackAtU( &Stack->Jmp, Top );
                        if ( OP_JMP( OpLine1, Head ) == JmpOffset )
                            End = OpLine1 - Head;
                        Top++;
                    }

                    ContinueOffset = JmpOffset;
                    BreakOffset = End + 1;
                    /* do{} while ( 1 ) */
                    Entry.Flags = DS_FLAGS_DO;
                    Entry.Type = 0;
                    Entry.Start = Start;
                    Entry.End = End;
                    insert_control_list( Stack, Start, &Entry );

                    Entry.Flags = DS_FLAGS_DO_WHILE_TRUE | DS_FLAGS_END;
                    insert_control_list( Stack, End, &Entry );

                    /* Insert to continue/break list */
                    insert_cont_brk_list( Stack, ContinueOffset, BreakOffset, Start, End, DS_FLAGS_DO_WHILE_TRUE );

                    StackPushAscU( &Stack->Skip, End );
                }
            }
            else if ( NextOffset == Offset )
            {
                Start = Offset;
                End = Offset;

                /* do{} while ( 1 ) */
                Entry.Flags = DS_FLAGS_DO;
                Entry.Type = 0;
                Entry.Start = Start;
                Entry.End = End;
                insert_control_list( Stack, Start, &Entry );

                Entry.Flags = DS_FLAGS_DO_WHILE_TRUE | DS_FLAGS_END;
                Entry.Type = DS_TYPE_TOP;
                insert_control_list( Stack, End + 1, &Entry );

                StackPushAscU( &Stack->Skip, Start );
            }
            else
            {
                break;
            }
            /* Delete */
            delete_scan_control_list( &Stack->ScanList, Offset );
            break;
        }
    }
    StackSetBottomU( &Stack->Skip, 0 );
    StackSetBottomU( &Stack->SkipOnce, 0 );

    /* Next step */
    Stack->Step++;

    /* Zap item marked as deleted */
    zap_scan_control_list( &Stack->ScanList, Offset );

    /* Set to start */
    StackSetBottomT( &Stack->ScanList, 0 );

    /* Fourth scan */
    while ( StackPopBottomT( &Stack->ScanList, &Scan ) )
    {
        Offset = Scan->Key;
        OpLine = Head + Offset;
        Stack->Offset = Offset;
        Stack->OpLine = OpLine;

        /* Skip */
        if ( StackBottomU( &Stack->Skip, &Dummy ) )
        {
            while ( StackBottomU( &Stack->Skip, &Dummy ) && Dummy < Offset )
                StackPopBottomU( &Stack->Skip, NULL );

            /* Skip this */
            if ( Dummy == Offset )
            {
                StackPopBottomU( &Stack->Skip, NULL );
                continue;
            }
        }

        /* Skip Once */
        if ( StackBottomU( &Stack->SkipOnce, &Dummy ) )
        {
            while ( StackBottomU( &Stack->SkipOnce, &Dummy ) && Dummy < Offset )
                StackPopBottomU( &Stack->SkipOnce, NULL );

            /* Skip this */
            if ( Dummy == Offset )
            {
                StackPopBottomU( &Stack->SkipOnce, NULL );
                continue;
            }
        }

        switch ( OP_CODE( OpLine ) )
        {
        case ZEND_JMP :
            NextOffset = OP_JMP( OpLine, Head );
            OpLine1 = OpLine - 1;
            if ( OP_CODE( OpLine1 ) == ZEND_BRK || OP_CODE( OpLine1 ) == ZEND_CONT )
            {
                StackPushAscU( &Stack->Skip, Offset );
                break;
            }

            if ( GetBreak( Stack, NextOffset, Offset ) )
            {
                if ( OP_CODE( OpLine1 ) != ZEND_RETURN && OP_CODE( OpLine1 ) != ZEND_EXIT )
                {
                    /* break; */
                    Entry.Flags = DS_FLAGS_BRK;
                    Entry.Type = DS_TYPE_NOINDENT;
                    Entry.Start = Offset;
                    Entry.End = Offset;
                    insert_control_list( Stack, Offset, &Entry );

                    StackPushAscU( &Stack->Skip, Offset );
                }
            }
            else if ( GetContinue( Stack, NextOffset, Offset ) )
            {
                if ( OP_CODE( OpLine1 ) != ZEND_RETURN && OP_CODE( OpLine1 ) != ZEND_EXIT )
                {
                    /* continue; */
                    Entry.Flags = DS_FLAGS_CONT;
                    Entry.Type = DS_TYPE_NOINDENT;
                    Entry.Start = Offset;
                    Entry.End = Offset;
                    insert_control_list( Stack, Offset, &Entry );

                    StackPushAscU( &Stack->Skip, Offset );
                }
            }
            /* Delete */
            delete_scan_control_list( &Stack->ScanList, Offset );
            break;

        case ZEND_JMPZ :
        case ZEND_JMPNZ :
            scan_if_list( Stack );
            /* Delete */
            delete_scan_control_list( &Stack->ScanList, Offset );
            break;

        case ZEND_JMPZNZ :
            scan_if_list( Stack );
            /* Delete */
            delete_scan_control_list( &Stack->ScanList, Offset );
            break;

        case ZEND_BRK :
        case ZEND_CONT :
            /* Delete */
            delete_scan_control_list( &Stack->ScanList, Offset );
            /* Break-continue */
            BrkContArray = OpArray->brk_cont_array;
            if ( BrkContArray == NULL )
                break;

            if ( OPLINE_BRK_CONT( OpLine ) == - 1 )
                break;

            BrkContArray += OPLINE_BRK_CONT( OpLine );
            if ( BrkContArray->brk != BrkContArray->cont + 1 )
                break;

            /* See if exist */
            BrkContPtr = GetBreak( Stack, BrkContArray->brk, Offset );
            if ( BrkContPtr )
                if ( !( BrkContPtr->Flags & DS_FLAGS_INTERNAL ) )
                    break;

            /* End */
            End = BrkContArray->brk;
            /* Scan suitable start place */
            Start = adjust_control_list_start( Stack, Offset, End );
            End = BrkContArray->brk;

            Entry.Flags = DS_FLAGS_DO;
            Entry.Type = 0;
            Entry.Start = Start;
            Entry.End = End;
            insert_control_list( Stack, Start, &Entry );

            Entry.Flags = DS_FLAGS_DO_WHILE_FALSE | DS_FLAGS_END;
            Entry.Type = DS_TYPE_TOP;
            insert_control_list( Stack, End, &Entry );

            /* Insert to continue/break list */
            insert_cont_brk_list( Stack, BrkContArray->cont, End, Start, End, DS_FLAGS_NULL );
            break;

        case ZEND_RETURN :
            adjust_return_list( Stack, Offset );
            /* Delete */
            delete_scan_control_list( &Stack->ScanList, Offset );
            break;
        }
    }
    StackSetBottomU( &Stack->Skip, 0 );
    StackSetBottomU( &Stack->SkipOnce, 0 );

    /* Zap item marked as deleted */
    zap_scan_control_list( &Stack->ScanList, Offset );

    /* Set to start */
    StackSetBottomT( &Stack->ScanList, 0 );
}

void scan_if_logic_reverse( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry )
{
    ULONG Top;
    ULONG Offset;
    ULONG NextOffset;
    ULONG Type;
    zend_uchar OpCode;
    zend_op *Head;
    zend_op *OpLine;
    PLOGIC_LIST LogicPtr;

    Offset = Stack->Offset;
    Top = StackFindAscT( &Stack->Logic, &Offset );
    if ( Top )
    {
        Head = Stack->Head;
        OpLine = Stack->OpLine;
        LogicPtr = StackAtT( &Stack->Logic, Top - 1 );
        /* Single */
        if ( LogicPtr->Start == LogicPtr->End )
        {
            OpCode = OP_CODE( OpLine );
            Type = Entry->Type & ( DS_TYPE_BRK | DS_TYPE_CONT );
            switch ( Entry->Flags & DS_FLAGS_MASK )
            {
            case DS_FLAGS_IF :
            case DS_FLAGS_ELSEIF :
            case DS_FLAGS_WHILE :
                if ( OpCode == ZEND_JMPZ )
                {
                    NextOffset = OP_JMPX( OpLine, Head );
                    if ( Type )
                        Entry->Type |= DS_TYPE_REVERSE;
                }
                else if ( OpCode == ZEND_JMPNZ )
                {
                    NextOffset = OP_JMPX( OpLine, Head );
                    Top = StackFindAscT( &Stack->OffsetMap, ( PKEY_VALUE )&Offset );
                    if ( Top )
                        NextOffset = ( ( PKEY_VALUE )StackAtT( &Stack->OffsetMap, Top - 1 ) )->Value;
                    if ( NextOffset > Offset && !Type )
                        Entry->Type |= DS_TYPE_REVERSE;
                }
                break;

            case DS_FLAGS_DO_WHILE_END :
                if ( OP_CODE( OpLine ) == ZEND_JMPZ )
                {
                    NextOffset = OP_JMPX( OpLine, Head );
                    if ( NextOffset < Offset )
                        Entry->Type |= DS_TYPE_REVERSE;
                }
                break;
            }
        }
    }
}

TCHAR *expand_var_string( PDUMP_STACK Stack, PVARIABLE_ENTRY Var, ULONG Key )
{
    ULONG Top;
    ULONG Length;
    TCHAR *String;
    KEY_VALUE VarStringMap;

    String = Var->Expr;
    Length = Var->ExprLength;
    /* Var string map */
    if ( Var->Flags & VE_FLAGS_VAR_MAP )
    {
        VarStringMap.Key = Key;
        Top = StackFindAscT( &Stack->VarStringMap, &VarStringMap );
        if ( Top )
        {
            String = ( TCHAR* ) ( ( PKEY_VALUE )StackAtT( &Stack->VarStringMap, Top - 1 ) )->Value;
            Length = _tcslen( String );
        }
    }
    /* Prefix */
    if ( ( Var->Flags & VE_FLAGS_SILENCE_FUNCTION ) == VE_FLAGS_SILENCE_FUNCTION )
    {
        StackPushS( &Stack->Buffer, DEFAULT_SILENCE_STRING, DEFAULT_SILENCE_STRING_LENGTH );
        StackPushS( &Stack->Buffer, String, Length );
        Length = StackPopAllS( &Stack->Buffer, &String );
        Var->Flags = ( Var->Flags & DS_IFLAGS_OT_MASK ) | DS_IFLAGS_OT_MAX;
    }

    return String;
}

void FASTCALL dump_control_null( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
}

void FASTCALL dump_control_brk( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
    if ( Entry->Type & DS_TYPE_NOINDENT )
    {
        dump_string( Stack, _T( "break;\r\n" ) );
    }
    else
    {
        PUSH_INC_INDENT( Stack );
        dump_string( Stack, _T( "break;\r\n" ) );
        POP_INDENT( Stack );
    }
}

void FASTCALL dump_control_cont( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
    if ( Entry->Type & DS_TYPE_NOINDENT )
    {
        dump_string( Stack, _T( "continue;\r\n" ) );
    }
    else
    {
        PUSH_INC_INDENT( Stack );
        dump_string( Stack, _T( "continue;\r\n" ) );
        POP_INDENT( Stack );
    }
}

void FASTCALL dump_control_if( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
    ULONG Type;
    ULONG OpType;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    TCHAR *String;

    if ( *StringInOut == NULL )
    {
        OpLine = Stack->Head + Entry->Offset;
        if ( TEST_OP1_CONST( OpLine ) )
        {
            make_printable_zval_url( OP1_VAL( OpLine ), &Stack->Buffer );
            StackPopAllS( &Stack->Buffer, &String );
            OpType = DS_IFLAGS_OT_MAX;
        }
        else if ( TEST_OP1_ALL_VAR( OpLine ) )
        {
            Var = FindVariableById( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                return;

            String = expand_var_string( Stack, Var, MAKE_KEY( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) ) );
            OpType = Var->Flags & DS_IFLAGS_OT_MASK;
        }
        else
        {
            return;
        }
    }
    else
    {
        String = *StringInOut;
        *StringInOut = NULL;
        OpType = Stack->Argument;
    }

    if ( !( Entry->Type & DS_TYPE_SKIP_REVERSE ) )
        scan_if_logic_reverse( Stack, Entry );

    if ( Entry->Type & DS_TYPE_REVERSE )
    {
        if ( OpType > DS_IFLAGS_OT_BOOL_NOT )
            dump_string_ex( Stack, _T( "if ( !%s )\r\n" ), String );
        else if ( OpType == DS_IFLAGS_OT_BOOL_NOT && *String == _T( '!' ) )
            dump_string_ex( Stack, _T( "if ( %s )\r\n" ), String + 1 );
        else
            dump_string_ex( Stack, _T( "if ( !( %s ) )\r\n" ), String );
    }
    else
    {
        dump_string_ex( Stack, _T( "if ( %s )\r\n" ), String );
    }

    Type = Entry->Type & DS_TYPE_MASK;
    if ( Type == 0 )
    {
        dump_string( Stack, _T( "{\r\n" ) );
        PUSH_INC_INDENT( Stack );
    }
    else
    {
        dump_string( Stack, _T( "{\r\n" ) );
        PUSH_INC_INDENT( Stack );
        if ( ( Type & DS_TYPE_EXTEND ) == DS_TYPE_EXTEND )
        {
            if ( ( Type & DS_TYPE_BRK ) == DS_TYPE_BRK )
            {
                dump_string( Stack, _T( "break;\r\n" ) );
                POP_INDENT( Stack );
                dump_string( Stack, _T( "}\r\n" ) );
                dump_string( Stack, _T( "else\r\n" ) );
                dump_string( Stack, _T( "{\r\n" ) );
                PUSH_INC_INDENT( Stack );
                dump_string( Stack, _T( "continue;\r\n" ) );
            }
            else if ( ( Type & DS_TYPE_CONT ) == DS_TYPE_CONT )
            {
                dump_string( Stack, _T( "continue;\r\n" ) );
                POP_INDENT( Stack );
                dump_string( Stack, _T( "}\r\n" ) );
                dump_string( Stack, _T( "else\r\n" ) );
                dump_string( Stack, _T( "{\r\n" ) );
                PUSH_INC_INDENT( Stack );
                dump_string( Stack, _T( "break;\r\n" ) );
            }
        }
        else
        {
            if ( ( Type & DS_TYPE_BRK ) == DS_TYPE_BRK )
            {
                dump_string( Stack, _T( "break;\r\n" ) );
            }
            else if ( ( Type & DS_TYPE_CONT ) == DS_TYPE_CONT )
            {
                dump_string( Stack, _T( "continue;\r\n" ) );
            }
        }
    }
}

void FASTCALL dump_control_else( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
    POP_INDENT( Stack );
    dump_string( Stack, _T( "}\r\n" ) );
    dump_string( Stack, _T( "else\r\n" ) );
    dump_string( Stack, _T( "{\r\n" ) );
    PUSH_INC_INDENT( Stack );
}

void FASTCALL dump_control_elseif( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
    ULONG Type;
    ULONG OpType;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    TCHAR *String;

    if ( *StringInOut == NULL )
    {
        OpLine = Stack->Head + Entry->Offset;
        if ( TEST_OP1_CONST( OpLine ) )
        {
            make_printable_zval_url( OP1_VAL( OpLine ), &Stack->Buffer );
            StackPopAllS( &Stack->Buffer, &String );
            OpType = DS_IFLAGS_OT_MAX;
        }
        else if ( TEST_OP1_ALL_VAR( OpLine ) )
        {
            Var = FindVariableById( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                return;

            String = expand_var_string( Stack, Var, MAKE_KEY( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) ) );
            OpType = Var->Flags & DS_IFLAGS_OT_MASK;
        }
        else
        {
            return;
        }
    }
    else
    {
        String = *StringInOut;
        *StringInOut = NULL;
        OpType = Stack->Argument;
    }

    if ( !( Entry->Type & DS_TYPE_SKIP_REVERSE ) )
        scan_if_logic_reverse( Stack, Entry );

    POP_INDENT( Stack );
    dump_string( Stack, _T( "}\r\n" ) );
    if ( Entry->Type & DS_TYPE_REVERSE )
    {
        if ( OpType > DS_IFLAGS_OT_BOOL_NOT )
            dump_string_ex( Stack, _T( "else if ( !%s )\r\n" ), String );
        else if ( OpType == DS_IFLAGS_OT_BOOL_NOT && *String == _T( '!' ) )
            dump_string_ex( Stack, _T( "else if ( %s )\r\n" ), String + 1 );
        else
            dump_string_ex( Stack, _T( "else if ( !( %s ) )\r\n" ), String );
    }
    else
    {
        dump_string_ex( Stack, _T( "else if ( %s )\r\n" ), String );
    }

    Type = Entry->Type & DS_TYPE_MASK;
    if ( Type == 0 )
    {
        dump_string( Stack, _T( "{\r\n" ) );
        PUSH_INC_INDENT( Stack );
    }
    else
    {
        dump_string( Stack, _T( "{\r\n" ) );
        PUSH_INC_INDENT( Stack );
        if ( ( Type & DS_TYPE_EXTEND ) == DS_TYPE_EXTEND )
        {
            if ( ( Type & DS_TYPE_BRK ) == DS_TYPE_BRK )
            {
                dump_string( Stack, _T( "break;\r\n" ) );
                POP_INDENT( Stack );
                dump_string( Stack, _T( "}\r\n" ) );
                dump_string( Stack, _T( "else\r\n" ) );
                dump_string( Stack, _T( "{\r\n" ) );
                PUSH_INC_INDENT( Stack );
                dump_string( Stack, _T( "continue;\r\n" ) );
            }
            else if ( ( Type & DS_TYPE_CONT ) == DS_TYPE_CONT )
            {
                dump_string( Stack, _T( "continue;\r\n" ) );
                POP_INDENT( Stack );
                dump_string( Stack, _T( "}\r\n" ) );
                dump_string( Stack, _T( "else\r\n" ) );
                dump_string( Stack, _T( "{\r\n" ) );
                PUSH_INC_INDENT( Stack );
                dump_string( Stack, _T( "break;\r\n" ) );
            }
        }
        else
        {
            if ( ( Type & DS_TYPE_BRK ) == DS_TYPE_BRK )
            {
                dump_string( Stack, _T( "break;\r\n" ) );
            }
            else if ( ( Type & DS_TYPE_CONT ) == DS_TYPE_CONT )
            {
                dump_string( Stack, _T( "continue;\r\n" ) );
            }
        }
    }
}

void FASTCALL dump_control_if_end( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
    POP_INDENT( Stack );
    dump_string( Stack, _T( "}\r\n" ) );
}

void FASTCALL dump_control_do( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
    dump_string( Stack, _T( "do\r\n" ) );
    dump_string( Stack, _T( "{\r\n" ) );
    PUSH_INC_INDENT( Stack );
}

void FASTCALL dump_control_do_while_end( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
    ULONG OpType;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    TCHAR *String;

    if ( *StringInOut == NULL )
    {
        OpLine = Stack->Head + Entry->Offset;
        if ( TEST_OP1_CONST( OpLine ) )
        {
            make_printable_zval_url( OP1_VAL( OpLine ), &Stack->Buffer );
            StackPopAllS( &Stack->Buffer, &String );
            OpType = DS_IFLAGS_OT_MAX;
        }
        else if ( TEST_OP1_ALL_VAR( OpLine ) )
        {
            Var = FindVariableById( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                return;

            String = expand_var_string( Stack, Var, MAKE_KEY( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) ) );
            OpType = Var->Flags & DS_IFLAGS_OT_MASK;
        }
        else
        {
            return;
        }
    }
    else
    {
        String = *StringInOut;
        *StringInOut = NULL;
        OpType = Stack->Argument;
    }

    if ( !( Entry->Type & DS_TYPE_SKIP_REVERSE ) )
        scan_if_logic_reverse( Stack, Entry );

    POP_INDENT( Stack );
    if ( Entry->Type & DS_TYPE_REVERSE )
    {
        if ( OpType > DS_IFLAGS_OT_BOOL_NOT )
            dump_string_ex( Stack, _T( "} while ( !%s )%s" ), String, Stack->EndChar );
        else if ( OpType == DS_IFLAGS_OT_BOOL_NOT && *String == _T( '!' ) )
            dump_string_ex( Stack, _T( "} while ( %s )%s" ), String + 1, Stack->EndChar );
        else
            dump_string_ex( Stack, _T( "} while ( !( %s ) )%s" ), String, Stack->EndChar );
    }
    else
    {
        dump_string_ex( Stack, _T( "} while ( %s )%s" ), String, Stack->EndChar );
    }
}

void FASTCALL dump_control_do_while_true( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
    POP_INDENT( Stack );
    dump_string_ex( Stack, _T( "} while ( 1 )%s" ), Stack->EndChar );
}

void FASTCALL dump_control_do_while_false( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
    POP_INDENT( Stack );
    dump_string_ex( Stack, _T( "} while ( 0 )%s" ), Stack->EndChar );
}

void FASTCALL dump_control_while( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
    ULONG OpType;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    TCHAR *String;

    if ( *StringInOut == NULL )
    {
        OpLine = Stack->Head + Entry->Offset;
        if ( TEST_OP1_CONST( OpLine ) )
        {
            make_printable_zval_url( OP1_VAL( OpLine ), &Stack->Buffer );
            StackPopAllS( &Stack->Buffer, &String );
            OpType = DS_IFLAGS_OT_MAX;
        }
        else if ( TEST_OP1_ALL_VAR( OpLine ) )
        {
            Var = FindVariableById( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                return;

            String = expand_var_string( Stack, Var, MAKE_KEY( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) ) );
            OpType = Var->Flags & DS_IFLAGS_OT_MASK;
        }
        else
        {
            return;
        }
    }
    else
    {
        String = *StringInOut;
        *StringInOut = NULL;
        OpType = Stack->Argument;
    }

    if ( !( Entry->Type & DS_TYPE_SKIP_REVERSE ) )
        scan_if_logic_reverse( Stack, Entry );

    if ( Entry->Type & DS_TYPE_REVERSE )
    {
        if ( OpType > DS_IFLAGS_OT_BOOL_NOT )
            dump_string_ex( Stack, _T( "while ( !%s )\r\n" ), String );
        else if ( OpType == DS_IFLAGS_OT_BOOL_NOT && *String == _T( '!' ) )
            dump_string_ex( Stack, _T( "while ( %s )\r\n" ), String + 1 );
        else
            dump_string_ex( Stack, _T( "while ( !( %s ) )\r\n" ), String );
    }
    else
    {
        dump_string_ex( Stack, _T( "while ( %s )\r\n" ), String );
    }
    dump_string( Stack, _T( "{\r\n" ) );
    PUSH_INC_INDENT( Stack );
}

void FASTCALL dump_control_while_end( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
    POP_INDENT( Stack );
    dump_string( Stack, _T( "}\r\n" ) );
}

void FASTCALL dump_control_for( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
    if ( GET_GS_FLAGS( ) & GS_FLAGS_DETAIL )
    {
        dump_string( Stack, _T( "for ( ;\r\n" ) );
        PUSH_INC_INDENT( Stack );
        Stack->EndChar[0] = _T( ',' );
    }
    else
    {
        dump_string( Stack, _T( "for ( ;" ) );
        Stack->State |= DS_STATE_SINGLE_INDENT;
        Stack->EndChar[0] = _T( ',' );
        Stack->EndChar[1] = _T( '\0' );
        Stack->EndCharLength = 1;
    }
}

void FASTCALL dump_control_forbracket_in( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
    ULONG OpType;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    TCHAR *String;

    if ( Entry->Type == DS_TYPE_EMPTY )
    {
        if ( GET_GS_FLAGS( ) & GS_FLAGS_DETAIL )
            dump_string( Stack, _T( ";\r\n" ) );
        else
            dump_string( Stack, DEFAULT_STATEMENT_STRING );
        return;
    }

    if ( *StringInOut == NULL )
    {
        OpLine = Stack->Head + Entry->Offset;
        if ( TEST_OP1_CONST( OpLine ) )
        {
            make_printable_zval_url( OP1_VAL( OpLine ), &Stack->Buffer );
            StackPopAllS( &Stack->Buffer, &String );
        }
        else if ( TEST_OP1_ALL_VAR( OpLine ) )
        {
            Var = FindVariableById( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                return;

            String = expand_var_string( Stack, Var, MAKE_KEY( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) ) );
            OpType = Var->Flags & DS_IFLAGS_OT_MASK;
        }
        else
        {
            return;
        }
    }
    else
    {
        String = *StringInOut;
        *StringInOut = NULL;
    }

    if ( GET_GS_FLAGS( ) & GS_FLAGS_DETAIL )
        dump_string_ex( Stack, _T( "%s;\r\n" ), String );
    else
        dump_string_ex( Stack, _T( "%s;" ), String );
}

void FASTCALL dump_control_forbracket_end( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
    if ( GET_GS_FLAGS( ) & GS_FLAGS_DETAIL )
    {
        dump_string( Stack, _T( ")\r\n" ) );
        POP_INDENT( Stack );
        Stack->EndChar[0] = DEFAULT_STATEMENT_CHAR;
    }
    else
    {
        /* NOTE for ( ; condition; ) */
        if ( !( Entry->Type & DS_TYPE_SKIP_BACK ) )
            BACK_LOG( - 1, LOG_POSITION_CURRENT );
        dump_string( Stack, _T( ")\r\n" ) );
        Stack->State &= ~DS_STATE_SINGLE_INDENT;
        Stack->EndChar[0] = DEFAULT_STATEMENT_CHAR;
        Stack->EndChar[1] = _T( '\r' );
        Stack->EndCharLength = 3;
    }
    dump_string( Stack, _T( "{\r\n" ) );
    PUSH_INC_INDENT( Stack );
}

void FASTCALL dump_control_for_end( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
    POP_INDENT( Stack );
    dump_string( Stack, _T( "}\r\n" ) );
}

void FASTCALL dump_control_foreach( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
}

void FASTCALL dump_control_foreach_end( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
    POP_INDENT( Stack );
    dump_string( Stack, _T( "}\r\n" ) );
}

void FASTCALL dump_control_switch( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
    ULONG OpType;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    TCHAR *String;

    if ( *StringInOut == NULL )
    {
        OpLine = Stack->Head + Entry->Offset;
        if ( TEST_OP1_CONST( OpLine ) )
        {
            make_printable_zval_url( OP1_VAL( OpLine ), &Stack->Buffer );
            StackPopAllS( &Stack->Buffer, &String );
            OpType = DS_IFLAGS_OT_MAX;
        }
        else if ( TEST_OP1_ALL_VAR( OpLine ) )
        {
            Var = FindVariableById( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                return;

            String = expand_var_string( Stack, Var, MAKE_KEY( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) ) );
            OpType = Var->Flags & DS_IFLAGS_OT_MASK;
        }
        else
        {
            return;
        }
    }
    else
    {
        String = *StringInOut;
        *StringInOut = NULL;
        OpType = Stack->Argument;
    }

    if ( Entry->Type & DS_TYPE_REVERSE )
    {
        if ( OpType > DS_IFLAGS_OT_BOOL_NOT )
            dump_string_ex( Stack, _T( "switch ( !%s )\r\n" ), String );
        else if ( OpType == DS_IFLAGS_OT_BOOL_NOT && *String == _T( '!' ) )
            dump_string_ex( Stack, _T( "switch ( %s )\r\n" ), String + 1 );
        else
            dump_string_ex( Stack, _T( "switch ( !( %s ) )\r\n" ), String );
    }
    else
    {
        dump_string_ex( Stack, _T( "switch ( %s )\r\n" ), String );
    }
    dump_string( Stack, _T( "{\r\n" ) );
    PUSH_INC_INDENT( Stack );
}

void FASTCALL dump_control_switch_case( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
    ULONG OpType;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    TCHAR *String;

    if ( *StringInOut == NULL )
    {
        OpLine = Stack->Head + Entry->Offset;
        if ( TEST_OP2_CONST( OpLine ) )
        {
            make_printable_zval_url( OP2_VAL( OpLine ), &Stack->Buffer );
            StackPopAllS( &Stack->Buffer, &String );
            OpType = DS_IFLAGS_OT_MAX;
        }
        else if ( TEST_OP1_ALL_VAR( OpLine ) )
        {
            Var = FindVariableById( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
            if ( Var == NULL )
                return;

            String = expand_var_string( Stack, Var, MAKE_KEY( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) ) );
            OpType = Var->Flags & DS_IFLAGS_OT_MASK;
        }
        else
        {
            return;
        }
    }
    else
    {
        String = *StringInOut;
        *StringInOut = NULL;
        OpType = Stack->Argument;
    }

    POP_INDENT( Stack );
    if ( Entry->Type & DS_TYPE_REVERSE )
    {
        if ( OpType > DS_IFLAGS_OT_BOOL_NOT )
            dump_string_ex( Stack, _T( "case !%s :\r\n" ), String );
        else if ( OpType == DS_IFLAGS_OT_BOOL_NOT && *String == _T( '!' ) )
            dump_string_ex( Stack, _T( "case %s :\r\n" ), String + 1 );
        else
            dump_string_ex( Stack, _T( "case !( %s ) :\r\n" ), String );
    }
    else
    {
        dump_string_ex( Stack, _T( "case %s :\r\n" ), String );
    }
    PUSH_INC_INDENT( Stack );
}

void FASTCALL dump_control_switch_default( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
    POP_INDENT( Stack );
    dump_string( Stack, _T( "default :\r\n" ) );
    PUSH_INC_INDENT( Stack );
}

void FASTCALL dump_control_switch_end( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
    POP_INDENT( Stack );
    dump_string( Stack, _T( "}\r\n" ) );
}

void FASTCALL dump_control_switch_try( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
    dump_string( Stack, _T( "try\r\n" ) );
    dump_string( Stack, _T( "{\r\n" ) );
    PUSH_INC_INDENT( Stack );
}

void FASTCALL dump_control_switch_try_end( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
    POP_INDENT( Stack );
    dump_string( Stack, _T( "}\r\n" ) );
}

void FASTCALL dump_control_switch_catch( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    TCHAR *String;

    if ( *StringInOut == NULL )
    {
        OpLine = Stack->Head + Entry->Offset;
        Var = FindVariableById( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
        if ( Var == NULL )
            return;

        StackPushS( &Stack->Buffer, Stack->OpString, _tcslen( Stack->OpString ) );
        StackPushS( &Stack->Buffer, _T( " ( " ), 3 );
        StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
        StackPushS( &Stack->Buffer, _T( " $" ), 2 );
        StackPushS( &Stack->Buffer, OP2_VAL( OpLine )->value.str.val, OP2_VAL( OpLine )->value.str.len );
        StackPushS( &Stack->Buffer, _T( " )\r\n" ), 4 );
        StackPopAllS( &Stack->Buffer, &String );
    }
    else
    {
        String = *StringInOut;
        *StringInOut = NULL;
    }

    dump_string( Stack, String );
    dump_string( Stack, _T( "{\r\n" ) );
    PUSH_INC_INDENT( Stack );
}

void FASTCALL dump_control_switch_catch_end( PDUMP_STACK Stack, PCOMMON_CONTROL_ENTRY Entry, TCHAR **StringInOut )
{
    POP_INDENT( Stack );
    dump_string( Stack, _T( "}\r\n" ) );
}

void dump_control_list( PDUMP_STACK Stack )
{
    ULONG Offset;
    ULONG Flags;
    ULONG OpType;
    ULONG Length;
    ULONG Iter;
    ULONG Dummy;
    PCONTROL_LIST ControlList;
    PCOMMON_CONTROL_ENTRY Entry;
    PVARIABLE_ENTRY Var;
    PLOGIC_PREFIX_LIST LogicPrefixPtr;
    LOGIC_PREFIX_LIST LogicPrefix;
    zend_op *Head;
    zend_op *OpLine;
    TCHAR *String;
    PKEY_VALUE PostOpTypePtr;
    TCHAR Buffer[256];
    static DUMP_CONTROL_HANDLER DumpControlHandlers[] = {
        dump_control_null,
        dump_control_brk,
        dump_control_cont,
        dump_control_if,
        dump_control_else,
        dump_control_elseif,
        dump_control_if_end,
        dump_control_do,
        dump_control_do_while_end,
        dump_control_do_while_true,
        dump_control_do_while_false,
        dump_control_while,
        dump_control_while_end,
        dump_control_for,
        dump_control_forbracket_in,
        dump_control_forbracket_end,
        dump_control_for_end,
        dump_control_foreach,
        dump_control_foreach_end,
        dump_control_switch,
        dump_control_switch_case,
        dump_control_switch_default,
        dump_control_switch_end,
        dump_control_switch_try,
        dump_control_switch_try_end,
        dump_control_switch_catch,
        dump_control_switch_catch_end,
    };

    OpType = DS_IFLAGS_OT_MAX;
    Head = Stack->Head;
    OpLine = Stack->OpLine;
    Offset = Stack->Offset;
    String = NULL;

    if ( StackBottomT( &Stack->PostOpTypeList, &PostOpTypePtr ) && PostOpTypePtr->Key == Offset )
    {
        StackPopBottomT( &Stack->PostOpTypeList, NULL );
        Var = FindVariableById( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
        if ( Var )
        {
            /* ! */
            if ( PostOpTypePtr->Value & DS_IFLAGS_BOOL_NOT )
            {
                LogicPrefix.Offset = Offset;
                LogicPrefix.Flags = DS_IFLAGS_BOOL_NOT | LL_FLAGS_TOP;
                StackPushAscT( &Stack->LogicPrefix, &LogicPrefix );
            }

            if ( ( Var->Flags & DS_IFLAGS_OT_MASK ) < ( PostOpTypePtr->Value & DS_IFLAGS_OT_MASK ) )
            {
                /* ( ) */
                LogicPrefix.Offset = Offset;
                LogicPrefix.Flags = LL_FLAGS_TOP;
                StackPushAscT( &Stack->LogicPrefix, &LogicPrefix );
                StackPushAscU( &Stack->LogicPostfix, Offset );
            }
        }
    }

    if ( Stack->LogicEndOffset == Offset )
    {
        Var = FindVariableById( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
        if ( Var )
        {
            /* Prefix */
            while ( StackBottomT( &Stack->LogicPrefix, &LogicPrefixPtr ) && LogicPrefixPtr->Offset <= Offset )
            {
                StackPopBottomT( &Stack->LogicPrefix, NULL );
                if ( LogicPrefixPtr->Flags & DS_IFLAGS_BOOL_NOT )
                {
                    if ( StackTopS( &Stack->LogicExpress, Buffer ) && Buffer[0] == _T( '!' ) )
                        StackPopS( &Stack->LogicExpress, NULL );
                    else
                        StackPushS( &Stack->LogicExpress, _T( "!" ), 1 );
                }
                else
                {
                    StackPushS( &Stack->LogicExpress, _T( "( " ), 2 );
                }
            }

            String = expand_var_string( Stack, Var, MAKE_KEY( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) ) );
            if ( String == Var->Expr )
                Length = Var->ExprLength;
            else
                Length = _tcslen( String );

            if ( StackTopS( &Stack->LogicExpress, Buffer ) && Buffer[0] == _T( '!' ) && String[0] == _T( '!' ) )
            {
                StackPopS( &Stack->LogicExpress, NULL );
                StackPushS( &Stack->LogicExpress, String + 1, Length - 1 );
            }
            else
            {
                StackPushS( &Stack->LogicExpress, String, Length );
            }

            /* Postfix */
            while ( StackBottomU( &Stack->LogicPostfix, &Dummy ) && Dummy <= Offset )
            {
                StackPopBottomU( &Stack->LogicPostfix, NULL );
                StackPushS( &Stack->LogicExpress, _T( " )" ), 2 );
            }
            Dummy = StackPopAllS( &Stack->LogicExpress, &String );
            OpType = Stack->LogicOpType & DS_IFLAGS_OT_MASK;

            /* JmpX in cond express */
            if ( ( OP_CODE( OpLine ) == ZEND_JMPZ || OP_CODE( OpLine ) == ZEND_JMPNZ ) &&
                is_special_jump( OP_JMPX( OpLine, Head ) - 1, Head ) )
            {
                /* Condition ? r1 : r2 */
                Flags = Var->Flags;
                if ( OP_CODE( OpLine ) == ZEND_JMPZ )
                    Flags |= VE_FLAGS_JMPZ;
                else
                    Flags |= VE_FLAGS_JMPNZ;
                StackPushU( &Stack->QmAssign, Flags );
                StackPush( &Stack->Trinary, String, Dummy + 1 );

                /* Skip */
                StackPushAscU( &Stack->Skip, Offset );
            }

            /* Reset temporary variable to avoid side-effect */
            if ( TEST_OP1_TMP_VAR( OpLine ) )
                UpdateVariableEx( OP1_TYPE( OpLine ), OP1_VAR( OpLine ), Offset, NULL, NULL, OpType );
        }
        Stack->LogicEndOffset = INVALID_OP_OFFSET;
        Stack->LogicEndJmp = INVALID_OP_OFFSET;

        StackReinitU( &Stack->LogicOpReverse );
        StackReinitT( &Stack->PostOpTypeList );
        StackReinitU( &Stack->LogicList );
        StackReinitT( &Stack->LogicPrefix );
        StackReinitU( &Stack->LogicPostfix );
    }

    if ( StackBottomT( &Stack->ControlList, &ControlList ) && ControlList->Offset == Offset )
    {
        StackPopBottomT( &Stack->ControlList, NULL );
        Stack->Argument = OpType;
        for ( Iter = 0; Iter < SIZE_OF_ARRAY( ControlList->List ); Iter++ )
            while ( StackPopBottomT( &ControlList->List[Iter], &Entry ) )
                DumpControlHandlers[Entry->Flags & DS_FLAGS_MASK]( Stack, Entry, &String );
    }
}

ULONG dump_function( HashTable *Table, LPCTSTR Name, ULONG Length, ULONG Indent )
{
    ULONG RetCode;
    register Bucket *Bt;
    zend_function *Function;

    RetCode = FALSE;
    Bt = Table->pListHead;
    while ( Bt )
    {
        Function = ( zend_function* ) ( Bt->pDataPtr ? Bt->pDataPtr : Bt->pData );
        if ( Function->type == ZEND_USER_FUNCTION && Bt->nKeyLength && 0 == _strnicmp( Function->common.function_name, Name, Length ) )
        {
            if ( GET_GS( )->ExtensionId < EXTENSION_ID_2 )
                StackPushU( &GET_GS( )->FunctionFlags, 0 );
            else
                StackPushU( &GET_GS( )->FunctionFlags, ( ( zend_function_2* )Function )->common.fn_flags );
            dump_op_array_ex( &Function->op_array, Indent, DS_STATE_FUNCTION | DS_STATE_INTERNAL );
            RetCode = TRUE;
            break;
        }
        Bt = Bt->pListNext;
    }

    return RetCode;
}

ULONG dump_function_table( HashTable *Table, ULONG Indent )
{
    ULONG RetCode;
    register Bucket *Bt;
    zend_function *Function;

    RetCode = 0;
    Bt = Table->pListHead;
    while ( Bt )
    {
        Function = ( zend_function* ) ( Bt->pDataPtr ? Bt->pDataPtr : Bt->pData );
        if ( Function->type == ZEND_USER_FUNCTION && Bt->nKeyLength && 0 == _strnicmp( Function->common.function_name, Bt->arKey, Bt->nKeyLength ) )
        {
            if ( !StackFindAscU( &GET_GS( )->Function, ( ULONG )Function ) )
            {
                StackPushAscU( &GET_GS( )->Function, ( ULONG )Function );
                StackPushU( &GET_GS( )->FunctionFlags, 0 );
                dump_op_array_ex( &Function->op_array, Indent, DS_STATE_FUNCTION );
                ADD_LOG_LR( _T( "" ) );
                RetCode++;
            }
        }
        else if ( Function->type == ZEND_INTERNAL_FUNCTION )
        {
            if ( GET_GS_FLAGS( ) & GS_FLAGS_FUNCTION && *GET_GS( )->LogFile )
            {
                INIT_LOG( GET_GS( )->LogFile, GET_GS( )->LogType, TRUE );
                ADD_DEBUG_LOG_LR( _T( "//[IF]%s Handler[ %08X ]" ), Bt->arKey, Function->internal_function.handler );
                INIT_LOG( GET_GS( )->LastFile, GET_GS( )->LogType, TRUE );
            }
        }
        else if ( Function->type == ZEND_OVERLOADED_FUNCTION )
        {
            if ( GET_GS_FLAGS( ) & GS_FLAGS_FUNCTION && *GET_GS( )->LogFile )
            {
                INIT_LOG( GET_GS( )->LogFile, GET_GS( )->LogType, TRUE );
                ADD_DEBUG_LOG_LR( _T( "//[OF]%s [ %X ]" ), Bt->arKey );
                INIT_LOG( GET_GS( )->LastFile, GET_GS( )->LogType, TRUE );
            }
        }
        else if ( Function->type == ZEND_EVAL_CODE )
        {
            if ( GET_GS_FLAGS( ) & GS_FLAGS_FUNCTION && *GET_GS( )->LogFile )
            {
                INIT_LOG( GET_GS( )->LogFile, GET_GS( )->LogType, TRUE );
                ADD_DEBUG_LOG_LR( _T( "//[EF]%s" ), Bt->arKey );
                INIT_LOG( GET_GS( )->LastFile, GET_GS( )->LogType, TRUE );
            }
        }
        Bt = Bt->pListNext;
    }
    SET_GS_FLAGS( GET_GS_FLAGS( ) | GS_IFLAGS_FUNCTION_ONCE );

    return RetCode;
}

ULONG dump_class_properties( zend_class_entry *Entry, zend_class_entry *BaseEntry, ULONG Indent )
{
    ULONG RetCode;
    register Bucket *Bt;
    HashTable *BaseTable;
    zval *Property;
    zval *BaseProperty;
    PCOMMON_STACK_S Buffer;
    TCHAR *String;

    RetCode = 0;
    if ( BaseEntry )
        BaseTable = &BaseEntry->default_properties;
    else
        BaseTable = NULL;

    LOCK_GS( );
    Buffer = &GET_GS( )->Buffer;
    Bt = Entry->default_properties.pListHead;
    while ( Bt )
    {
        do
        {
            Property = ( zval* ) ( Bt->pDataPtr ? Bt->pDataPtr : Bt->pData );
            /* See if inherited property */
            if ( BaseTable )
            {
                BaseProperty = find_hash_key_fast( BaseTable, Bt->arKey, Bt->nKeyLength, Bt->h );
                if ( BaseProperty )
                {
                    if ( GET_GS( )->ExtensionId < EXTENSION_ID_2 )
                    {
                        if ( ( ( zval_1* )Property )->type == ( ( zval_1* )BaseProperty )->type &&
                            ( ( zval_1* )Property )->value.lval == ( ( zval_1* )BaseProperty )->value.lval )
                            break;
                    }
                    else
                    {
                        if ( ( ( zval_2* )Property )->type == ( ( zval_2* )BaseProperty )->type &&
                            ( ( zval_2* )Property )->value.lval == ( ( zval_2* )BaseProperty )->value.lval )
                            break;
                    }
                }
            }

            dump_indent_string_stub( Indent );
            StackPushS( Buffer, _T( "var $" ), 5 );
            StackPushS( Buffer, Bt->arKey, Bt->nKeyLength - 1 );
            if ( Property->type != IS_NULL )
            {
                StackPushS( Buffer, _T( " = " ), 3 );
                PUSH_INDENT( GET_GS_STACK( ), Indent );
                make_printable_zval_url( Property, Buffer );
                POP_INDENT( GET_GS_STACK( ) );
            }
            StackPushS( Buffer, DEFAULT_STATEMENT_STRING, DEFAULT_STATEMENT_STRING_LENGTH );
            StackPopAllS( Buffer, &String );
            ADD_LOG_LRA( String );
            RetCode++;
        } while ( 0 );
        Bt = Bt->pListNext;
    }
    UNLOCK_GS( );

    return RetCode;
}

ULONG dump_class_properties_info( zend_class_entry *Entry, zend_class_entry *BaseEntry, ULONG Indent )
{
    ULONG RetCode;
    register Bucket *Bt;
    HashTable *BaseTable;
    HashTable *TargetTable;
    zend_property_info_2 *Property;
    zend_property_info_2 *BaseProperty;
    zval *Val;
    PCOMMON_STACK_S Buffer;
    TCHAR *String;

    RetCode = 0;
    LOCK_GS( );
    Buffer = &GET_GS( )->Buffer;
    Bt = ( ( zend_class_entry_2* )Entry )->properties_info.pListHead;
    while ( Bt )
    {
        do
        {
            Property = ( zend_property_info_2* ) ( Bt->pDataPtr ? Bt->pDataPtr : Bt->pData );
            /* See if inherited property */
            if ( Property->flags & ZEND_ACC_STATIC )
            {
                TargetTable = &( ( zend_class_entry_2* )Entry )->default_static_members;
                if ( BaseEntry )
                    BaseTable = &( ( zend_class_entry_2* )BaseEntry )->default_static_members;
                else
                    BaseTable = NULL;
            }
            else
            {
                TargetTable = &( ( zend_class_entry_2* )Entry )->default_properties;
                if ( BaseEntry )
                    BaseTable = &( ( zend_class_entry_2* )BaseEntry )->default_properties;
                else
                    BaseTable = NULL;
            }

            if ( BaseTable )
            {
                BaseProperty = find_hash_key_fast( BaseTable, Property->name, Property->name_length + 1, Property->h );
                if ( BaseProperty )
                    break;
            }

            dump_indent_string_stub( Indent );
            switch ( Property->flags & ZEND_ACC_PPP_MASK )
            {
            case ZEND_ACC_PUBLIC :
                StackPushS( Buffer, _T( "public " ), 7 );
                break;

            case ZEND_ACC_PROTECTED :
                StackPushS( Buffer, _T( "protected " ), 10 );
                break;

            case ZEND_ACC_PRIVATE :
                StackPushS( Buffer, _T( "private " ), 8 );
                break;

            default :
                StackPushS( Buffer, _T( "public " ), 7 );
                break;
            }

            if ( Property->flags & ZEND_ACC_STATIC )
                StackPushS( Buffer, _T( "static $" ), 8 );
            else
                StackPushS( Buffer, _T( "$" ), 1 );

            StackPushS( Buffer, Bt->arKey, Bt->nKeyLength - 1 );
            Val = ( zval* )find_hash_key_fast( TargetTable, Property->name, Property->name_length + 1, Property->h );
            if ( Val )
            {
                StackPushS( Buffer, _T( " = " ), 3 );
                PUSH_INDENT( GET_GS_STACK( ), Indent );
                make_printable_zval_url( Val, Buffer );
                POP_INDENT( GET_GS_STACK( ) );
            }

            StackPushS( Buffer, DEFAULT_STATEMENT_STRING, DEFAULT_STATEMENT_STRING_LENGTH );
            StackPopAllS( Buffer, &String );
            ADD_LOG_LRA( String );
            RetCode++;
        } while ( 0 );
        Bt = Bt->pListNext;
    }
    UNLOCK_GS( );

    return RetCode;
}

ULONG dump_class_properties_const( zend_class_entry *Entry, zend_class_entry *BaseEntry, ULONG Indent )
{
    ULONG RetCode;
    register Bucket *Bt;
    zval *Val;
    PCOMMON_STACK_S Buffer;
    TCHAR *String;

    RetCode = 0;
    LOCK_GS( );
    Buffer = &GET_GS( )->Buffer;
    Bt = ( ( zend_class_entry_2* )Entry )->constants_table.pListHead;
    while ( Bt )
    {
        do
        {
            Val = ( zval* ) ( Bt->pDataPtr ? Bt->pDataPtr : Bt->pData );
            dump_indent_string_stub( Indent );
            StackPushS( Buffer, _T( "const " ), 6 );
            StackPushS( Buffer, Bt->arKey, Bt->nKeyLength - 1 );
            StackPushS( Buffer, _T( " = " ), 3 );
            PUSH_INDENT( GET_GS_STACK( ), Indent );
            make_printable_zval_url( Val, Buffer );
            POP_INDENT( GET_GS_STACK( ) );
            StackPushS( Buffer, DEFAULT_STATEMENT_STRING, DEFAULT_STATEMENT_STRING_LENGTH );
            StackPopAllS( Buffer, &String );
            ADD_LOG_LRA( String );
            RetCode++;
        } while ( 0 );
        Bt = Bt->pListNext;
    }
    UNLOCK_GS( );

    return RetCode;
}

ULONG dump_class_function_table( zend_class_entry *Entry, zend_class_entry *BaseEntry, ULONG Indent, ULONG State )
{
    ULONG RetCode;
    register Bucket *Bt;
    HashTable *BaseTable;
    zend_function *Function;
    zend_function *BaseFunction;
    zend_op *OpLine;
    ULONG LastOffset;

    RetCode = 0;
    if ( BaseEntry )
        BaseTable = &BaseEntry->function_table;
    else
        BaseTable = NULL;

    Bt = Entry->function_table.pListHead;
    while ( Bt )
    {
        do
        {
            Function = ( zend_function* ) ( Bt->pDataPtr ? Bt->pDataPtr : Bt->pData );
            if ( !Bt->nKeyLength || _strnicmp( Function->common.function_name, Bt->arKey, Bt->nKeyLength ) )
                break;

            if ( GET_GS( )->ExtensionId < EXTENSION_ID_2 )
            {
                OpLine = get_oparray_op_1( &Function->op_array );
                LastOffset = ( ( zend_op_array_1* )&Function->op_array )->last;
            }
            else
            {
                OpLine = get_oparray_op_2( &Function->op_array );
                LastOffset = ( ( zend_op_array_2* )&Function->op_array )->last;
            }

            /* Default constructor */
            if ( ( GET_GS_VERSION( ) & 0xFFFF ) > 3 && LastOffset == 1 && OP_CODE( OpLine ) == ZEND_RECV_INIT )
            {
                if ( 0 == _strnicmp( OP2_VAL( OpLine )->value.str.val, Entry->name, Entry->name_length ) )
                    break;
            }

            if ( BaseTable )
            {
                BaseFunction = find_hash_key_fast( BaseTable, Bt->arKey, Bt->nKeyLength, Bt->h );
                if ( BaseFunction && get_oparray_op( &BaseFunction->op_array ) == OpLine )
                    break;
            }

            if ( GET_GS( )->ExtensionId < EXTENSION_ID_2 )
                StackPushU( &GET_GS( )->FunctionFlags, 0 );
            else
                StackPushU( &GET_GS( )->FunctionFlags, ( ( zend_function_2* )Function )->common.fn_flags );
            dump_op_array_ex( &Function->op_array, Indent, State );
            ADD_LOG_LR( _T( "" ) );
            RetCode++;
        } while ( 0 );
        Bt = Bt->pListNext;
    }

    return RetCode;
}

zend_class_entry *find_class( HashTable *Table, UCHAR Type, LPCTSTR Name, ULONG Length )
{
    register Bucket *Bt;
    zend_class_entry *ClassEntry;

    Bt = Table->pListHead;
    while ( Bt )
    {
        ClassEntry = ( zend_class_entry* ) ( Bt->pDataPtr ? Bt->pDataPtr : Bt->pData );
        if ( ClassEntry->type == Type && ClassEntry->name_length == Length && 0 == memcmp( ClassEntry->name, Name, Length ) )
            return ClassEntry;
        Bt = Bt->pListNext;
    }

    return NULL;
}

zend_class_entry *find_base_class( HashTable *Table, zend_class_entry *zend_class_entry, UCHAR Type, LPCTSTR Name, ULONG Length )
{
    if ( zend_class_entry->parent )
        return zend_class_entry->parent;
    else if ( Name )
        return find_class( Table, Type, Name, Length );
    else
        return NULL;
}

ULONG dump_class( HashTable *Table, LPCTSTR Name, ULONG Length, LPCTSTR ParentName, ULONG ParentLength, LPCTSTR ImplementName, ULONG ImplementNameLength, ULONG Indent )
{
    ULONG RetCode;
    ULONG Dummy;
    register Bucket *Bt;
    zend_class_entry *ClassEntry;
    zend_class_entry *ClassEntryParent;
    PCOMMON_STACK_S Buffer;
    PCOMMON_STACK_S Buffer1;
    const TCHAR *String;

    RetCode = FALSE;
    Buffer = &GET_GS( )->Buffer;
    Buffer1 = &GET_GS( )->Buffer1;
    Bt = Table->pListHead;
    while ( Bt )
    {
        ClassEntry = ( zend_class_entry* ) ( Bt->pDataPtr ? Bt->pDataPtr : Bt->pData );
        if ( ClassEntry->type == ZEND_USER_CLASS && Bt->nKeyLength && 0 == _strnicmp( ClassEntry->name, Name, Length + 1 ) )
        {
            dump_indent_string_stub( Indent );

            /* Lock */
            LOCK_GS( );
            StackReinitS( Buffer );
            StackReinitS( Buffer1 );

            /* Class attribute */
            if ( ( ( zend_class_entry_2* )ClassEntry )->ce_flags & ZEND_ACC_EXPLICIT_ABSTRACT_CLASS )
                StackPushS( Buffer, _T( "abstract class " ), 15 );
            else if ( ( ( zend_class_entry_2* )ClassEntry )->ce_flags & ZEND_ACC_FINAL_CLASS )
                StackPushS( Buffer, _T( "final class " ), 12 );
            else if ( ( ( zend_class_entry_2* )ClassEntry )->ce_flags & ZEND_ACC_INTERFACE )
                StackPushS( Buffer, _T( "interface " ), 10 );
            else
                StackPushS( Buffer, _T( "class " ), 6 );

            /* Decode class name */
            decode_obfuscate_class_name( Buffer1, ClassEntry->name, ClassEntry->name_length );
            Dummy = StackPopAllS( Buffer1, &String );
            push_class_name( String, Dummy );

            StackPushS( Buffer, String, Dummy );
            ClassEntryParent = find_base_class( Table, ClassEntry, ZEND_USER_CLASS, ParentName, ParentLength );
            if ( ClassEntryParent )
            {
                StackPushS( Buffer, _T( " extends " ), 9 );
                decode_obfuscate_class_name( Buffer, ClassEntryParent->name, ClassEntryParent->name_length );
            }
            else if ( ParentName )
            {
                StackPushS( Buffer, _T( " extends " ), 9 );
                StackPushS( Buffer, ParentName, ParentLength );
            }
            if ( ImplementName )
            {
                StackPushS( Buffer, _T( " implements " ), 12 );
                StackPushS( Buffer, ImplementName, ImplementNameLength );
            }
            StackPopAllS( Buffer, &String );
            ADD_LOG_LRA( String );
            dump_indent_string_stub( Indent );
            ADD_LOG_LR( _T( "{" ) );
            ADD_LOG_LR( _T( "" ) );

            /* Unlock */
            UNLOCK_GS( );

            if ( GET_GS( )->MajorId < EXTENSION_ID_2 )
            {
                if ( dump_class_properties( ClassEntry, ClassEntryParent, Indent + GET_GS_INDENT( ) ) )
                    ADD_LOG_LR( _T( "" ) );
            }
            else
            {
                if ( dump_class_properties_info( ClassEntry, ClassEntryParent, Indent + GET_GS_INDENT( ) ) )
                    ADD_LOG_LR( _T( "" ) );

                if ( dump_class_properties_const( ClassEntry, ClassEntryParent, Indent + GET_GS_INDENT( ) ) )
                    ADD_LOG_LR( _T( "" ) );
            }

            dump_class_function_table( ClassEntry, ClassEntryParent, Indent + GET_GS_INDENT( ), DS_STATE_CLASS | DS_STATE_INTERNAL );
            dump_indent_string_stub( Indent );
            ADD_LOG_LR( _T( "}" ) );
            ADD_LOG_LR( _T( "" ) );
            pop_class_name( );
            RetCode = TRUE;
            break;
        }
        Bt = Bt->pListNext;
    }

    return RetCode;
}

ULONG dump_class_table( HashTable *Table, ULONG Indent )
{
    ULONG RetCode;
    ULONG Dummy;
    register Bucket *Bt;
    zend_class_entry *ClassEntry;
    zend_class_entry *ClassEntryParent;
    PCOMMON_STACK_S Buffer;
    PCOMMON_STACK_S Buffer1;
    const TCHAR *String;

    RetCode = 0;
    Buffer = &GET_GS( )->Buffer;
    Buffer1 = &GET_GS( )->Buffer1;
    Bt = Table->pListHead;
    while ( Bt )
    {
        ClassEntry = ( zend_class_entry* ) ( Bt->pDataPtr ? Bt->pDataPtr : Bt->pData );
        if ( ClassEntry->type == ZEND_USER_CLASS && Bt->nKeyLength && 0 == _strnicmp( ClassEntry->name, Bt->arKey, Bt->nKeyLength ) )
        {
            if ( !StackFindAscU( &GET_GS( )->Class, ( ULONG )ClassEntry ) )
            {
                StackPushAscU( &GET_GS( )->Class, ( ULONG )ClassEntry );
                dump_indent_string_stub( Indent );

                /* Lock */
                LOCK_GS( );
                StackReinitS( Buffer );
                StackReinitS( Buffer1 );

                /* Class attribute */
                if ( ( ( zend_class_entry_2* )ClassEntry )->ce_flags & ZEND_ACC_EXPLICIT_ABSTRACT_CLASS )
                    StackPushS( Buffer, _T( "abstract class " ), 15 );
                else if ( ( ( zend_class_entry_2* )ClassEntry )->ce_flags & ZEND_ACC_FINAL_CLASS )
                    StackPushS( Buffer, _T( "final class " ), 12 );
                else if ( ( ( zend_class_entry_2* )ClassEntry )->ce_flags & ZEND_ACC_INTERFACE )
                    StackPushS( Buffer, _T( "interface " ), 10 );
                else
                    StackPushS( Buffer, _T( "class " ), 6 );

                /* Decode class name */
                decode_obfuscate_class_name( Buffer1, ClassEntry->name, ClassEntry->name_length );
                Dummy = StackPopAllS( Buffer1, &String );
                push_class_name( String, Dummy );

                StackPushS( Buffer, String, Dummy );
                ClassEntryParent = find_base_class( Table, ClassEntry, ZEND_USER_CLASS, NULL, 0 );
                if ( ClassEntryParent )
                {
                    StackPushS( Buffer, _T( " extends " ), 9 );
                    decode_obfuscate_class_name( Buffer, ClassEntryParent->name, ClassEntryParent->name_length );
                }
                StackPopAllS( Buffer, &String );
                ADD_LOG_LRA( String );
                dump_indent_string_stub( Indent );
                ADD_LOG_LR( _T( "{" ) );
                ADD_LOG_LR( _T( "" ) );

                /* Unlock */
                UNLOCK_GS( );

                if ( GET_GS( )->MajorId < EXTENSION_ID_2 )
                {
                    if ( dump_class_properties( ClassEntry, ClassEntryParent, Indent + GET_GS_INDENT( ) ) )
                        ADD_LOG_LR( _T( "" ) );
                }
                else
                {
                    if ( dump_class_properties_info( ClassEntry, ClassEntryParent, Indent + GET_GS_INDENT( ) ) )
                        ADD_LOG_LR( _T( "" ) );

                    if ( dump_class_properties_const( ClassEntry, ClassEntryParent, Indent + GET_GS_INDENT( ) ) )
                        ADD_LOG_LR( _T( "" ) );
                }

                dump_class_function_table( ClassEntry, ClassEntryParent, Indent + GET_GS_INDENT( ), DS_STATE_CLASS );
                dump_indent_string_stub( Indent );
                ADD_LOG_LR( _T( "}" ) );
                ADD_LOG_LR( _T( "" ) );
                pop_class_name( );
                RetCode++;
            }
        }
        else if ( ClassEntry->type == ZEND_INTERNAL_CLASS )
        {
            if ( GET_GS_FLAGS( ) & GS_FLAGS_CLASS && *GET_GS( )->LogFile )
            {
                INIT_LOG( GET_GS( )->LogFile, GET_GS( )->LogType, TRUE );
                ADD_DEBUG_LOG_LR( _T( "//[IC]%s" ), Bt->arKey );
                INIT_LOG( GET_GS( )->LastFile, GET_GS( )->LogType, TRUE );
            }
        }
        Bt = Bt->pListNext;
    }
    SET_GS_FLAGS( GET_GS_FLAGS( ) | GS_IFLAGS_CLASS_ONCE );

    return RetCode;
}

PVOID find_function_handler( HashTable *Table, const TCHAR *FunctionName )
{
    register ULONG Length;
    register Bucket *Bt;

    Length = _tcslen( FunctionName ) + 1;
    Bt = Table->pListHead;
    while ( Bt )
    {
        if ( Bt->nKeyLength == Length && 0 == _strnicmp( FunctionName, Bt->arKey, Bt->nKeyLength ) )
            return Bt->pDataPtr ? Bt->pDataPtr : Bt->pData;
        Bt = Bt->pListNext;
    }

    return NULL;
}

ULONG find_function_handler_ex( HashTable *Table, ULONG Count, PSTRING_ARRAY_EX Array )
{
    ULONG RetCode;
    register ULONG Iter;
    register Bucket *Bt;
    register TCHAR *FunctionName;

    RetCode = 0;
    Bt = Table->pListHead;
    while ( Bt )
    {
        for ( Iter = 0; Iter < Count; Iter++ )
        {
            FunctionName = Array[Iter].Name;
            if ( Bt->nKeyLength == Array[Iter].NameLength && 0 == _strnicmp( FunctionName, Bt->arKey, Bt->nKeyLength ) )
            {
                Array[Iter].Data = Bt->pDataPtr ? Bt->pDataPtr : Bt->pData;
                RetCode++;
            }
        }
        Bt = Bt->pListNext;
    }

    return RetCode;
}

ULONG call_internal_function( zend_function *Function, zval **ReturnValue, ULONG Count, ... )
{
    va_list VarList;
    register ULONG Iter;
    int ReturnValueUsed;
    ULONG ArgType;
    void *ArgValue;
    zval *ArgVal;
    zval *RetValue;
    zval *RetValuePtr;
    void *Dummy;

    TSRMLS_FETCH( );

    if ( ReturnValue )
    {
        *ReturnValue = NULL;
        ReturnValueUsed = 1;
    }
    else
    {
        ReturnValueUsed = 0;
    }

    if ( Function == NULL )
        return FALSE;

    Iter = 0;
    /* Push argument */
    va_start( VarList, Count );
    while ( Iter < Count )
    {
        ALLOC_ZVAL( ArgVal );
        INIT_PZVAL( ArgVal );
        ArgType = va_arg( VarList, long );
        ArgVal->type = ( zend_uchar )ArgType;
        switch ( ArgType )
        {
        case IS_LONG :
        case IS_BOOL :
            ArgVal->value.lval = va_arg( VarList, long );
            break;

        case IS_STRING :
        case IS_CONSTANT :
            ArgValue = va_arg( VarList, TCHAR* );
            ArgVal->value.str.val = ArgValue;
            ArgVal->value.str.len = _tcslen( ArgValue );
            break;

        case IS_DOUBLE :
            ArgVal->value.dval = va_arg( VarList, double );
            break;

        default :
            ArgVal->value.dval = va_arg( VarList, long );
            break;
        }

        zend_ptr_stack_push( &GET_GS( )->GExecutor->argument_stack, ArgVal );
        Iter++;
    }
    va_end( VarList );

    /* Argument end */
    zend_ptr_stack_n_push( &GET_GS( )->GExecutor->argument_stack, 2, Count, NULL );

    if ( Function->type == ZEND_INTERNAL_FUNCTION )
    {
        ALLOC_ZVAL( RetValue );
        INIT_ZVAL( *RetValue );
        zend_ptr_stack_n_push( &GET_GS( )->GExecutor->arg_types_stack, 3, NULL, NULL, NULL );

        if ( GET_GS( )->ExtensionId < EXTENSION_ID_2 )
            ( ( HANDLER_1 )Function->internal_function.handler ) ( Count, RetValue, NULL, ReturnValueUsed TSRMLS_CC );
        else
            ( ( HANDLER_2 )Function->internal_function.handler ) ( Count, RetValue, &RetValuePtr, NULL, ReturnValueUsed TSRMLS_CC );

        zend_ptr_stack_n_pop( &GET_GS( )->GExecutor->arg_types_stack, 3, &Dummy, &Dummy, &Dummy );

        RetValue->is_ref = 0;
        RetValue->refcount = 1;
        if ( !ReturnValueUsed )
            zval_ptr_dtor( &RetValue );
        else
            *ReturnValue = RetValue;
    }

    zend_ptr_stack_n_pop( &GET_GS( )->GExecutor->argument_stack, 2, &Dummy, &Dummy );
    Iter = 0;
    while ( Iter < Count )
    {
        ArgVal = zend_ptr_stack_pop( &GET_GS( )->GExecutor->argument_stack );
        Iter++;
    }

    return TRUE;
}

inline void free_zval( zval *Val )
{
    zval_ptr_dtor( &Val );
}

zval *php_version( )
{
    zval *RetValue;
    static zend_function *Function = NULL;

    if ( Function == ( zend_function* )- 1 )
        return NULL;

    if ( Function == NULL )
    {
        Function = find_function_handler( GET_GS_FUNCTION_TABLE( ), _T( "phpversion" ) );
        if ( Function == NULL )
        {
            Function = ( zend_function* )- 1;
            return NULL;
        }
    }

    call_internal_function( Function, &RetValue, 0 );

    return RetValue;
}

zval *zend_loader_version( )
{
    zval *RetValue;
    static zend_function *Function = NULL;

    if ( Function == ( zend_function* )- 1 )
        return NULL;

    if ( Function == NULL )
    {
        Function = find_function_handler( GET_GS_FUNCTION_TABLE( ), _T( "zend_loader_version" ) );
        if ( Function == NULL )
        {
            Function = ( zend_function* )- 1;
            return NULL;
        }
    }

    call_internal_function( Function, &RetValue, 0 );

    return RetValue;
}

zval *zend_optimizer_version( )
{
    zval *RetValue;
    static zend_function *Function = NULL;

    if ( Function == ( zend_function* )- 1 )
        return NULL;

    if ( Function == NULL )
    {
        Function = find_function_handler( GET_GS_FUNCTION_TABLE( ), _T( "zend_optimizer_version" ) );
        if ( Function == NULL )
        {
            Function = ( zend_function* )- 1;
            return NULL;
        }
    }

    call_internal_function( Function, &RetValue, 0 );

    return RetValue;
}

/* bool zend_loader_enabled( ) */
zval *zend_loader_enabled( )
{
    zval *RetValue;
    static zend_function *Function = NULL;

    if ( Function == ( zend_function* )- 1 )
        return NULL;

    if ( Function == NULL )
    {
        Function = find_function_handler( GET_GS_FUNCTION_TABLE( ), _T( "zend_loader_enabled" ) );
        if ( Function == NULL )
        {
            Function = ( zend_function* )- 1;
            return NULL;
        }
    }

    call_internal_function( Function, &RetValue, 0 );

    return RetValue;
}

/* bool zend_loader_file_encoded( ) */
zval *zend_loader_file_encoded( )
{
    zval *RetValue;
    static zend_function *Function = NULL;

    if ( Function == ( zend_function* )- 1 )
        return NULL;

    if ( Function == NULL )
    {
        Function = find_function_handler( GET_GS_FUNCTION_TABLE( ), _T( "zend_loader_file_encoded" ) );
        if ( Function == NULL )
        {
            Function = ( zend_function* )- 1;
            return NULL;
        }
    }

    call_internal_function( Function, &RetValue, 0 );

    return RetValue;
}

/* array zend_loader_file_licensed( ) */
zval *zend_loader_file_licensed( )
{
    zval *RetValue;
    static zend_function *Function = NULL;

    if ( Function == ( zend_function* )- 1 )
        return NULL;

    if ( Function == NULL )
    {
        Function = find_function_handler( GET_GS_FUNCTION_TABLE( ), _T( "zend_loader_file_licensed" ) );
        if ( Function == NULL )
        {
            Function = ( zend_function* )- 1;
            return NULL;
        }
    }

    call_internal_function( Function, &RetValue, 0 );

    return RetValue;
}

/* bool zend_loader_install_license( string license_file[, bool override] ) */
zval *zend_loader_install_license( const TCHAR *LicenseFile, ULONG Override )
{
    zval *RetValue;
    static zend_function *Function = NULL;

    if ( Function == ( zend_function* )- 1 )
        return NULL;

    if ( Function == NULL )
    {
        Function = find_function_handler( GET_GS_FUNCTION_TABLE( ), _T( "zend_loader_install_license" ) );
        if ( Function == NULL )
        {
            Function = ( zend_function* )- 1;
            return NULL;
        }
    }

    call_internal_function( Function, &RetValue, 2, IS_STRING, LicenseFile, IS_BOOL, Override );

    return RetValue;
}

/* int zend_current_obfuscation_level( ) */
zval *zend_current_obfuscation_level( )
{
    zval *RetValue;
    static zend_function *Function = NULL;

    if ( Function == ( zend_function* )- 1 )
        return NULL;

    if ( Function == NULL )
    {
        Function = find_function_handler( GET_GS_FUNCTION_TABLE( ), _T( "zend_current_obfuscation_level" ) );
        if ( Function == NULL )
        {
            Function = ( zend_function* )- 1;
            return NULL;
        }
    }

    call_internal_function( Function, &RetValue, 0 );

    return RetValue;
}

zval *zend_obfuscate_function_name( const TCHAR *Name )
{
    zval *RetValue;

    call_internal_function( GET_GS( )->zend_obfuscate_function_name, &RetValue, 1, IS_STRING, Name );

    return RetValue;
}

zval *zend_obfuscate_class_name( const TCHAR *Name )
{
    zval *RetValue;

    call_internal_function( GET_GS( )->zend_obfuscate_class_name, &RetValue, 1, IS_STRING, Name );

    return RetValue;
}

/* bool zend_runtime_obfuscate( ) */
zval *zend_runtime_obfuscate( )
{
    zval *RetValue;
    static zend_function *Function = NULL;

    if ( Function == ( zend_function* )- 1 )
        return NULL;

    if ( Function == NULL )
    {
        Function = find_function_handler( GET_GS_FUNCTION_TABLE( ), _T( "zend_runtime_obfuscate" ) );
        if ( Function == NULL )
        {
            Function = ( zend_function* )- 1;
            return NULL;
        }
    }

    call_internal_function( Function, &RetValue, 0 );

    return RetValue;
}

zval *get_defined_vars( )
{
    zval *RetValue;
    static zend_function *Function = NULL;

    if ( Function == ( zend_function* )- 1 )
        return NULL;

    if ( Function == NULL )
    {
        Function = find_function_handler( GET_GS_FUNCTION_TABLE( ), _T( "get_defined_vars" ) );
        if ( Function == NULL )
        {
            Function = ( zend_function* )- 1;
            return NULL;
        }
    }

    call_internal_function( Function, &RetValue, 0 );

    return RetValue;
}

TCHAR *generate_string( TCHAR *Buffer, ULONG Length )
{
    register ULONG Iter;
    TCHAR Cur;
    TCHAR Prev;
    static TCHAR Div = 1;

    srand( GetTickCount( ) / Div + Length );
    for ( Iter = 0; Iter < Length; Iter++ )
    {
        Cur = ( TCHAR )rand( );
        while ( Cur < _T( '0' ) || _T( '9' ) < Cur && Cur < _T( 'A' ) || _T( 'Z' ) < Cur && Cur < _T( 'a' ) || _T( 'z' ) < Cur )
        {
            Prev = Cur;
            if ( Cur == _T( '_' ) )
                break;
            else if ( Cur < _T( '0' ) )
                Cur += ( 0x7F - _T( '0' ) ) >> 1;
            else if ( Cur < _T( 'A' ) )
                Cur += ( 0x7F - _T( 'A' ) ) >> 1;
            else if ( Cur < _T( 'a' ) )
                Cur += ( 0x7F - _T( 'a' ) ) >> 1;
            else if ( Cur < 0x7F )
                Cur += ( 0x7F - _T( 'a' ) ) >> 1;
            else
                Cur = ( TCHAR ) ( ( Cur + 0x7F ) >> 1 );

            if ( Cur == Prev )
                Cur--;
        }
        if ( _T( 'A' ) <= Cur && Cur <= _T( 'Z' ) )
            Cur += _T( 'a' ) - _T( 'A' );
        Buffer[Iter] = Cur;
    }
    Div = Buffer[0];
    Buffer[Length] = 0;

    if ( _T( '0' ) < Div && Div < _T( '9' ) )
        Buffer[0] = ( TCHAR ) ( rand( ) % 26 + _T( 'a' ) );

    return Buffer;
}

TCHAR *inc_string( TCHAR *Buffer, ULONG Length )
{
    register LONG Iter;
    register TCHAR Cur;

    for ( Iter = Length - 1; Iter >= 0; Iter-- )
    {
        Cur = ++Buffer[Iter];
        if ( _T( 'z' ) < Cur )
        {
            Buffer[Iter] = _T( '0' );
        }
        else if ( _T( '_' ) < Cur && Cur < _T( 'a' ) )
        {
            Buffer[Iter] = _T( 'a' );
            break;
        }
        else if ( _T( '9' ) < Cur && Cur < _T( '_' ) )
        {
            Buffer[Iter] = _T( '_' );
            break;
        }
        else
        {
            break;
        }
    }

    return Buffer;
}

__declspec( naked ) ULONG obfuscate( TCHAR **String, ULONG *Length )
{
#define var_68 -0x68
#define var_58 -0x58
#define arg_0 4
#define arg_4 8

    static ULONG DDCDC0 = 0xDDCDC0;
    static ULONG DDCE30 = 0xDDCE30;
    static ULONG DD7650 = 0xDD7650;
    static ULONG DD6C70 = 0xDD6C70;

    __asm
    {
        jmp     loc_Begin

DD6C40 :
        mov     eax, [esp+4]
        mov     dword ptr [eax+4], 0
        mov     dword ptr [eax], 0
        mov     dword ptr [eax+8], 67452301h
        mov     dword ptr [eax+0Ch], 0EFCDAB89h
        mov     dword ptr [eax+10h], 98BADCFEh
        mov     dword ptr [eax+14h], 10325476h
        retn

loc_Begin :
        mov     eax, [esp+arg_4]
        sub     esp, 68h
        push    ebx
        mov     ebx, [esp+6Ch+arg_0]
        push    ebp
        push    esi
        mov     esi, [eax]
        push    edi
        mov     edi, [ebx]
        test    esi, esi
        jz      loc_DDCDB0
        test    edi, edi
        jz      loc_DDCDB0
        mov     al, [edi]
        test    al, al
        jnz     short loc_DDCCC7
        inc     edi
        dec     esi

loc_DDCCC7 :
        cmp     esi, 4
        jg      short loc_DDCD28
        xor     ebx, ebx
        test    esi, esi
        jle     loc_DDCD98

loc_DDCD0A :
        push    esi
        push    edi
        call    DDCE30
        add     esp, 8
        and     al, 7Fh
        jz      short loc_DDCD1C
        cmp     al, 3Ah
        jnz     short loc_DDCD1E

loc_DDCD1C :
        inc     al

loc_DDCD1E :
        mov     [ebx+edi], al
        inc     ebx
        cmp     ebx, esi
        jl      short loc_DDCD0A
        jmp     short loc_DDCD98

loc_DDCD28 :
        lea     edx, [esp+78h+var_58]
        push    edx
        call    DD6C40
        push    esi
        lea     eax, [esp+80h+var_58]
        push    edi
        push    eax
        call    DD6C70
        lea     ecx, [esp+88h+var_68]
        lea     edx, [esp+88h+var_58]
        push    ecx
        push    edx
        call    DD7650
        add     esp, 18h
        test    esi, esi
        jle     short loc_DDCD98
        mov     edx, 1
        mov     ecx, edi
        sub     edx, edi
        mov     ebp, esi

loc_DDCD5F :
        lea     eax, [edx+ecx]
        and     eax, 8000000Fh
        jns     short loc_DDCD6E
        dec     eax
        or      eax, 0FFFFFFF0h
        inc     eax

loc_DDCD6E :
        xor     ebx, ebx
        mov     bl, byte ptr [esp+eax+78h+var_68]
        mov     eax, ebx
        xor     ebx, ebx
        mov     bl, [ecx]
        xor     eax, ebx
        and     eax, 8000007Fh
        jns     short loc_DDCD88
        dec     eax
        or      eax, 0FFFFFF80h
        inc     eax

loc_DDCD88 :
        test    al, al
        jz      short loc_DDCD90
        cmp     al, 3Ah
        jnz     short loc_DDCD92

loc_DDCD90 :
        inc     al

loc_DDCD92 :
        mov     [ecx], al
        inc     ecx
        dec     ebp
        jnz     short loc_DDCD5F

loc_DDCD98 :
        mov     eax, 1
        pop     edi
        pop     esi
        pop     ebp
        pop     ebx
        add     esp, 68h
        retn

loc_DDCDB0 :
        xor     eax, eax
        pop     edi
        pop     esi
        pop     ebp
        pop     ebx
        add     esp, 68h
        retn
    }
}

/*
typedef ULONG ( *_DDCE30 ) ( const TCHAR *, ULONG );
typedef void ( *_DD6C70 ) ( void *, const TCHAR *, ULONG );
typedef void ( *_DD7650 ) ( void *, TCHAR * );
typedef void ( *_DD6D40 ) ( void *, TCHAR * );

const _DDCE30 fn_DDCE30 = ( _DDCE30 )0xDDCE30;
const _DD6C70 fn_DD6C70 = ( _DD6C70 )0xDD6C70;
const _DD7650 fn_DD7650 = ( _DD7650 )0xDD7650;
const _DD6D40 fn_DD6D40 = ( _DD6D40 )0xDD6D40;
*/

const UCHAR Key[24] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
    0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10
};

ULONG my_DDCE30_ex( const TCHAR *String, ULONG Length )
{
    register ULONG RetCode;
    register ULONG Iter;
    register ULONG Count;

    RetCode = 0x1505;
    Count = Length;
    for ( Iter = 0; Iter < Count; Iter++ )
        RetCode = String[Iter] + ( RetCode << 5 ) + RetCode;

    return RetCode;
}

__declspec( naked ) void my_DD6D40( void *Buffer, const TCHAR *String )
{
#define var_40 -0x40
#define var_3C -0x3C
#define var_38 -0x38
#define var_34 -0x34
#define var_30 -0x30
#define var_2C -0x2C
#define var_28 -0x28
#define var_24 -0x24
#define var_20 -0x20
#define var_1C -0x1C
#define var_18 -0x18
#define var_14 -0x14
#define var_10 -0x10
#define var_C -0x0C
#define var_8 -8
#define var_4 -4
#define arg_0 4
#define arg_4 8

    __asm
    {
        mov     ecx, [esp+arg_4]
        mov     eax, [esp+arg_0]
        sub     esp, 40h
        add     ecx, 2
        push    ebx
        push    ebp
        push    esi
        push    edi
        lea     esi, [esp+50h+var_40]
        mov     edi, 10h

loc_DD6D5B :
        xor     edx, edx
        xor     ebx, ebx
        mov     dl, [ecx+1]
        mov     bl, [ecx]
        shl     edx, 8
        add     edx, ebx
        xor     ebx, ebx
        mov     bl, [ecx-1]
        add     esi, 4
        shl     edx, 8
        add     edx, ebx
        xor     ebx, ebx
        mov     bl, [ecx-2]
        add     ecx, 4
        shl     edx, 8
        add     edx, ebx
        dec     edi
        mov     [esi-4], edx
        jnz     short loc_DD6D5B
        mov     esi, [eax+0Ch]
        mov     edi, [eax+10h]
        mov     edx, [eax+14h]
        mov     ebp, [esp+50h+var_40]
        mov     ecx, esi
        mov     eax, [eax+8]
        not     ecx
        mov     ebx, edi
        and     ecx, edx
        and     ebx, esi
        or      ecx, ebx
        mov     ebx, esi
        add     ecx, ebp
        mov     ebp, [esp+50h+var_3C]
        lea     ecx, [ecx+eax-28955B88h]
        mov     eax, ecx
        shr     eax, 19h
        shl     ecx, 7
        or      eax, ecx
        add     eax, esi
        mov     ecx, eax
        and     ebx, eax
        not     ecx
        and     ecx, edi
        or      ecx, ebx
        add     ecx, ebp
        mov     ebp, [esp+50h+var_38]
        lea     edx, [ecx+edx-173848AAh]
        mov     ecx, edx
        shr     ecx, 14h
        shl     edx, 0Ch
        or      ecx, edx
        add     ecx, eax
        mov     edx, ecx
        mov     ebx, ecx
        not     edx
        and     edx, esi
        and     ebx, eax
        or      edx, ebx
        mov     ebx, ecx
        add     edx, ebp
        mov     ebp, [esp+50h+var_34]
        lea     edi, [edx+edi+242070DBh]
        mov     edx, edi
        shr     edx, 0Fh
        shl     edi, 11h
        or      edx, edi
        add     edx, ecx
        mov     edi, edx
        and     ebx, edx
        not     edi
        and     edi, eax
        or      edi, ebx
        mov     ebx, edx
        add     edi, ebp
        mov     ebp, [esp+50h+var_30]
        lea     edi, [edi+esi-3E423112h]
        mov     esi, edi
        shl     esi, 16h
        shr     edi, 0Ah
        or      esi, edi
        add     esi, edx
        mov     edi, esi
        and     ebx, esi
        not     edi
        and     edi, ecx
        or      edi, ebx
        mov     ebx, esi
        add     edi, ebp
        mov     ebp, [esp+50h+var_2C]
        lea     edi, [edi+eax-0A83F051h]
        mov     eax, edi
        shr     eax, 19h
        shl     edi, 7
        or      eax, edi
        add     eax, esi
        mov     edi, eax
        and     ebx, eax
        not     edi
        and     edi, edx
        or      edi, ebx
        add     edi, ebp
        mov     ebp, [esp+50h+var_28]
        lea     edi, [edi+ecx+4787C62Ah]
        mov     ecx, edi
        shl     edi, 0Ch
        shr     ecx, 14h
        or      ecx, edi
        add     ecx, eax
        mov     edi, ecx
        mov     ebx, ecx
        not     edi
        and     edi, esi
        and     ebx, eax
        or      edi, ebx
        mov     ebx, ecx
        add     edi, ebp
        mov     ebp, [esp+50h+var_24]
        lea     edi, [edi+edx-57CFB9EDh]
        mov     edx, edi
        shl     edi, 11h
        shr     edx, 0Fh
        or      edx, edi
        add     edx, ecx
        mov     edi, edx
        and     ebx, edx
        not     edi
        and     edi, eax
        or      edi, ebx
        mov     ebx, edx
        add     edi, ebp
        mov     ebp, [esp+50h+var_20]
        lea     edi, [edi+esi-2B96AFFh]
        mov     esi, edi
        shl     esi, 16h
        shr     edi, 0Ah
        or      esi, edi
        add     esi, edx
        mov     edi, esi
        and     ebx, esi
        not     edi
        and     edi, ecx
        or      edi, ebx
        mov     ebx, esi
        add     edi, ebp
        mov     ebp, [esp+50h+var_1C]
        lea     edi, [edi+eax+698098D8h]
        mov     eax, edi
        shr     eax, 19h
        shl     edi, 7
        or      eax, edi
        add     eax, esi
        mov     edi, eax
        and     ebx, eax
        not     edi
        and     edi, edx
        or      edi, ebx
        add     edi, ebp
        mov     ebp, [esp+50h+var_18]
        lea     edi, [edi+ecx-74BB0851h]
        mov     ecx, edi
        shr     ecx, 14h
        shl     edi, 0Ch
        or      ecx, edi
        add     ecx, eax
        mov     edi, ecx
        mov     ebx, ecx
        not     edi
        and     edi, esi
        and     ebx, eax
        or      edi, ebx
        mov     ebx, ecx
        add     edi, ebp
        lea     edi, [edi+edx-0A44Fh]
        mov     edx, edi
        shr     edx, 0Fh
        shl     edi, 11h
        or      edx, edi
        add     edx, ecx
        mov     edi, edx
        not     edi
        and     edi, eax
        mov     ebp, [esp+50h+var_14]
        and     ebx, edx
        or      edi, ebx
        mov     ebx, edx
        add     edi, ebp
        mov     ebp, [esp+50h+var_10]
        lea     edi, [edi+esi-76A32842h]
        mov     esi, edi
        shl     esi, 16h
        shr     edi, 0Ah
        or      esi, edi
        add     esi, edx
        mov     edi, esi
        and     ebx, esi
        not     edi
        and     edi, ecx
        or      edi, ebx
        mov     ebx, esi
        add     edi, ebp
        mov     ebp, [esp+50h+var_C]
        lea     edi, [edi+eax+6B901122h]
        mov     eax, edi
        shr     eax, 19h
        shl     edi, 7
        or      eax, edi
        add     eax, esi
        mov     edi, eax
        and     ebx, eax
        not     edi
        and     edi, edx
        or      edi, ebx
        add     edi, ebp
        lea     edi, [edi+ecx-2678E6Dh]
        mov     ecx, edi
        shr     ecx, 14h
        shl     edi, 0Ch
        or      ecx, edi
        add     ecx, eax
        mov     edi, ecx
        mov     ebp, ecx
        not     edi
        mov     ebx, edi
        and     ebp, eax
        and     ebx, esi
        or      ebx, ebp
        mov     ebp, [esp+50h+var_8]
        add     ebx, ebp
        mov     ebp, ecx
        lea     ebx, [ebx+edx-5986BC72h]
        mov     edx, ebx
        shr     edx, 0Fh
        shl     ebx, 11h
        or      edx, ebx
        add     edx, ecx
        mov     ebx, edx
        and     ebp, edx
        not     ebx
        mov     [esp+50h+arg_4], ebx
        and     ebx, eax
        or      ebx, ebp
        mov     ebp, [esp+50h+var_4]
        add     ebx, ebp
        and     edi, edx
        lea     ebx, [ebx+esi+49B40821h]
        mov     esi, ebx
        shl     esi, 16h
        shr     ebx, 0Ah
        or      esi, ebx
        mov     ebx, ecx
        add     esi, edx
        and     ebx, esi
        or      edi, ebx
        mov     ebx, [esp+50h+var_3C]
        add     edi, ebx
        lea     edi, [edi+eax-9E1DA9Eh]
        mov     eax, edi
        shr     eax, 1Bh
        shl     edi, 5
        or      eax, edi
        mov     edi, [esp+50h+arg_4]
        add     eax, esi
        mov     ebx, edx
        and     edi, esi
        and     ebx, eax
        or      edi, ebx
        mov     ebx, [esp+50h+var_28]
        add     edi, ebx
        lea     edi, [edi+ecx-3FBF4CC0h]
        mov     ecx, edi
        shl     edi, 9
        shr     ecx, 17h
        or      ecx, edi
        mov     edi, esi
        add     ecx, eax
        not     edi
        mov     ebx, ecx
        and     edi, eax
        and     ebx, esi
        or      edi, ebx
        mov     ebx, [esp+50h+var_14]
        add     edi, ebx
        lea     edi, [edi+edx+265E5A51h]
        mov     edx, edi
        shr     edx, 12h
        shl     edi, 0Eh
        or      edx, edi
        mov     edi, eax
        add     edx, ecx
        not     edi
        mov     ebx, edx
        and     edi, ecx
        and     ebx, eax
        or      edi, ebx
        mov     ebx, [esp+50h+var_40]
        add     edi, ebx
        mov     ebx, ecx
        lea     edi, [edi+esi-16493856h]
        mov     esi, edi
        shl     esi, 14h
        shr     edi, 0Ch
        or      esi, edi
        mov     edi, ecx
        add     esi, edx
        not     edi
        and     edi, edx
        and     ebx, esi
        or      edi, ebx
        mov     ebx, [esp+50h+var_2C]
        add     edi, ebx
        mov     ebx, edx
        lea     edi, [edi+eax-29D0EFA3h]
        mov     eax, edi
        shr     eax, 1Bh
        shl     edi, 5
        or      eax, edi
        mov     edi, edx
        add     eax, esi
        not     edi
        and     edi, esi
        and     ebx, eax
        or      edi, ebx
        mov     ebx, [esp+50h+var_18]
        add     edi, ebx
        lea     edi, [edi+ecx+2441453h]
        mov     ecx, edi
        shr     ecx, 17h
        shl     edi, 9
        or      ecx, edi
        mov     edi, esi
        add     ecx, eax
        not     edi
        mov     ebx, ecx
        and     edi, eax
        and     ebx, esi
        or      edi, ebx
        add     edi, ebp
        lea     edi, [edi+edx-275E197Fh]
        mov     edx, edi
        shr     edx, 12h
        shl     edi, 0Eh
        or      edx, edi
        add     edx, ecx
        mov     edi, eax
        mov     ebx, edx
        not     edi
        and     edi, ecx
        and     ebx, eax
        or      edi, ebx
        mov     ebx, [esp+50h+var_30]
        add     edi, ebx
        mov     ebx, ecx
        lea     edi, [edi+esi-182C0438h]
        mov     esi, edi
        shr     edi, 0Ch
        shl     esi, 14h
        or      esi, edi
        mov     edi, ecx
        not     edi
        add     esi, edx
        and     edi, edx
        and     ebx, esi
        or      edi, ebx
        mov     ebx, [esp+50h+var_1C]
        add     edi, ebx
        mov     ebx, edx
        lea     edi, [edi+eax+21E1CDE6h]
        mov     eax, edi
        shr     eax, 1Bh
        shl     edi, 5
        or      eax, edi
        mov     edi, edx
        add     eax, esi
        not     edi
        and     edi, esi
        and     ebx, eax
        or      edi, ebx
        mov     ebx, [esp+50h+var_8]
        add     edi, ebx
        lea     edi, [edi+ecx-3CC8F82Ah]
        mov     ecx, edi
        shr     ecx, 17h
        shl     edi, 9
        or      ecx, edi
        mov     edi, esi
        add     ecx, eax
        not     edi
        mov     ebx, ecx
        and     edi, eax
        and     ebx, esi
        or      edi, ebx
        mov     ebx, [esp+50h+var_34]
        add     edi, ebx
        lea     edi, [edi+edx-0B2AF279h]
        mov     edx, edi
        shr     edx, 12h
        shl     edi, 0Eh
        or      edx, edi
        mov     edi, eax
        add     edx, ecx
        not     edi
        mov     ebx, edx
        and     edi, ecx
        and     ebx, eax
        or      edi, ebx
        mov     ebx, [esp+50h+var_20]
        add     edi, ebx
        mov     ebx, ecx
        lea     edi, [edi+esi+455A14EDh]
        mov     esi, edi
        shl     esi, 14h
        shr     edi, 0Ch
        or      esi, edi
        mov     edi, ecx
        add     esi, edx
        not     edi
        and     edi, edx
        and     ebx, esi
        or      edi, ebx
        mov     ebx, [esp+50h+var_C]
        add     edi, ebx
        lea     edi, [edi+eax-561C16FBh]
        mov     eax, edi
        shr     eax, 1Bh
        shl     edi, 5
        or      eax, edi
        mov     edi, edx
        not     edi
        add     eax, esi
        mov     ebx, edx
        and     edi, esi
        and     ebx, eax
        or      edi, ebx
        mov     ebx, [esp+50h+var_38]
        add     edi, ebx
        lea     edi, [edi+ecx-3105C08h]
        mov     ecx, edi
        shr     ecx, 17h
        shl     edi, 9
        or      ecx, edi
        mov     edi, esi
        add     ecx, eax
        not     edi
        mov     ebx, ecx
        and     edi, eax
        and     ebx, esi
        or      edi, ebx
        mov     ebx, [esp+50h+var_24]
        add     edi, ebx
        lea     edi, [edi+edx+676F02D9h]
        mov     edx, edi
        shr     edx, 12h
        shl     edi, 0Eh
        or      edx, edi
        mov     edi, eax
        add     edx, ecx
        not     edi
        mov     ebx, edx
        and     edi, ecx
        and     ebx, eax
        or      edi, ebx
        mov     ebx, [esp+50h+var_10]
        add     edi, ebx
        mov     ebx, [esp+50h+var_2C]
        lea     edi, [edi+esi-72D5B376h]
        mov     esi, edi
        shl     esi, 14h
        shr     edi, 0Ch
        or      esi, edi
        mov     edi, ecx
        add     esi, edx
        xor     edi, edx
        xor     edi, esi
        add     edi, ebx
        mov     ebx, [esp+50h+var_20]
        lea     edi, [edi+eax-5C6BEh]
        mov     eax, edi
        shr     eax, 1Ch
        shl     edi, 4
        or      eax, edi
        mov     edi, edx
        add     eax, esi
        xor     edi, esi
        xor     edi, eax
        add     edi, ebx
        mov     ebx, [esp+50h+var_14]
        lea     ecx, [edi+ecx-788E097Fh]
        mov     edi, ecx
        shr     edi, 15h
        shl     ecx, 0Bh
        or      edi, ecx
        add     edi, eax
        mov     ecx, edi
        xor     ecx, esi
        xor     ecx, eax
        add     ecx, ebx
        mov     ebx, edi
        lea     ecx, [ecx+edx+6D9D6122h]
        mov     edx, ecx
        shr     edx, 10h
        shl     ecx, 10h
        or      edx, ecx
        add     edx, edi
        xor     ebx, edx
        mov     ecx, ebx
        xor     ecx, eax
        add     ecx, [esp+50h+var_8]
        lea     esi, [ecx+esi-21AC7F4h]
        mov     ecx, esi
        shl     ecx, 17h
        shr     esi, 9
        or      ecx, esi
        mov     esi, [esp+50h+var_3C]
        add     ecx, edx
        xor     ebx, ecx
        add     ebx, esi
        mov     esi, edx
        xor     esi, ecx
        lea     ebx, [ebx+eax-5B4115BCh]
        mov     eax, ebx
        shr     eax, 1Ch
        shl     ebx, 4
        or      eax, ebx
        mov     ebx, [esp+50h+var_30]
        add     eax, ecx
        xor     esi, eax
        add     esi, ebx
        mov     ebx, [esp+50h+var_24]
        lea     edi, [esi+edi+4BDECFA9h]
        mov     esi, edi
        shr     esi, 15h
        shl     edi, 0Bh
        or      esi, edi
        add     esi, eax
        mov     edi, esi
        xor     edi, ecx
        xor     edi, eax
        add     edi, ebx
        lea     edi, [edi+edx-944B4A0h]
        mov     edx, edi
        shr     edx, 10h
        shl     edi, 10h
        or      edx, edi
        mov     edi, esi
        add     edx, esi
        xor     edi, edx
        mov     ebx, edi
        xor     ebx, eax
        add     ebx, [esp+50h+var_18]
        lea     ebx, [ebx+ecx-41404390h]
        mov     ecx, ebx
        shl     ecx, 17h
        shr     ebx, 9
        or      ecx, ebx
        mov     ebx, [esp+50h+var_C]
        add     ecx, edx
        xor     edi, ecx
        add     edi, ebx
        mov     ebx, [esp+50h+var_40]
        lea     edi, [edi+eax+289B7EC6h]
        mov     eax, edi
        shr     eax, 1Ch
        shl     edi, 4
        or      eax, edi
        mov     edi, edx
        add     eax, ecx
        xor     edi, ecx
        xor     edi, eax
        add     edi, ebx
        mov     ebx, [esp+50h+var_34]
        lea     edi, [edi+esi-155ED806h]
        mov     esi, edi
        shr     esi, 15h
        shl     edi, 0Bh
        or      esi, edi
        add     esi, eax
        mov     edi, esi
        xor     edi, ecx
        xor     edi, eax
        add     edi, ebx
        lea     edx, [edi+edx-2B10CF7Bh]
        mov     edi, edx
        shr     edi, 10h
        shl     edx, 10h
        or      edi, edx
        add     edi, esi
        mov     edx, esi
        xor     edx, edi
        mov     ebx, edx
        xor     ebx, eax
        add     ebx, [esp+50h+var_28]
        lea     ebx, [ebx+ecx+4881D05h]
        mov     ecx, ebx
        shl     ecx, 17h
        shr     ebx, 9
        or      ecx, ebx
        mov     ebx, [esp+50h+var_1C]
        add     ecx, edi
        xor     edx, ecx
        add     edx, ebx
        mov     ebx, [esp+50h+var_10]
        lea     edx, [edx+eax-262B2FC7h]
        mov     eax, edx
        shr     eax, 1Ch
        shl     edx, 4
        or      eax, edx
        mov     edx, edi
        add     eax, ecx
        xor     edx, ecx
        xor     edx, eax
        add     edx, ebx
        mov     ebx, [esp+50h+var_38]
        lea     esi, [edx+esi-1924661Bh]
        mov     edx, esi
        shr     edx, 15h
        shl     esi, 0Bh
        or      edx, esi
        add     edx, eax
        mov     esi, edx
        xor     esi, ecx
        xor     esi, eax
        add     esi, ebp
        lea     edi, [esi+edi+1FA27CF8h]
        mov     esi, edi
        shr     esi, 10h
        shl     edi, 10h
        or      esi, edi
        mov     edi, edx
        add     esi, edx
        xor     edi, esi
        xor     edi, eax
        add     edi, ebx
        mov     ebx, [esp+50h+var_40]
        lea     edi, [edi+ecx-3B53A99Bh]
        mov     ecx, edi
        shl     ecx, 17h
        shr     edi, 9
        or      ecx, edi
        mov     edi, edx
        add     ecx, esi
        not     edi
        or      edi, ecx
        xor     edi, esi
        add     edi, ebx
        mov     ebx, [esp+50h+var_24]
        lea     edi, [edi+eax-0BD6DDBCh]
        mov     eax, edi
        shr     eax, 1Ah
        shl     edi, 6
        or      eax, edi
        mov     edi, esi
        add     eax, ecx
        not     edi
        or      edi, eax
        xor     edi, ecx
        add     edi, ebx
        mov     ebx, [esp+50h+var_8]
        lea     edi, [edi+edx+432AFF97h]
        mov     edx, edi
        shr     edx, 16h
        shl     edi, 0Ah
        or      edx, edi
        mov     edi, ecx
        add     edx, eax
        not     edi
        or      edi, edx
        xor     edi, eax
        add     edi, ebx
        mov     ebx, [esp+50h+var_2C]
        lea     edi, [edi+esi-546BDC59h]
        mov     esi, edi
        shl     edi, 0Fh
        shr     esi, 11h
        or      esi, edi
        mov     edi, eax
        not     edi
        add     esi, edx
        or      edi, esi
        xor     edi, edx
        add     edi, ebx
        mov     ebx, [esp+50h+var_10]
        lea     edi, [edi+ecx-36C5FC7h]
        mov     ecx, edi
        shr     edi, 0Bh
        shl     ecx, 15h
        or      ecx, edi
        mov     edi, edx
        not     edi
        add     ecx, esi
        or      edi, ecx
        xor     edi, esi
        add     edi, ebx
        mov     ebx, [esp+50h+var_34]
        lea     edi, [edi+eax+655B59C3h]
        mov     eax, edi
        shl     edi, 6
        shr     eax, 1Ah
        or      eax, edi
        mov     edi, esi
        add     eax, ecx
        not     edi
        or      edi, eax
        xor     edi, ecx
        add     edi, ebx
        mov     ebx, [esp+50h+var_18]
        lea     edi, [edi+edx-70F3336Eh]
        mov     edx, edi
        shr     edx, 16h
        shl     edi, 0Ah
        or      edx, edi
        mov     edi, ecx
        add     edx, eax
        not     edi
        or      edi, edx
        xor     edi, eax
        add     edi, ebx
        mov     ebx, [esp+50h+var_3C]
        lea     edi, [edi+esi-100B83h]
        mov     esi, edi
        shr     esi, 11h
        shl     edi, 0Fh
        or      esi, edi
        mov     edi, eax
        add     esi, edx
        not     edi
        or      edi, esi
        xor     edi, edx
        add     edi, ebx
        mov     ebx, [esp+50h+var_20]
        lea     edi, [edi+ecx-7A7BA22Fh]
        mov     ecx, edi
        shl     ecx, 15h
        shr     edi, 0Bh
        or      ecx, edi
        mov     edi, edx
        add     ecx, esi
        not     edi
        or      edi, ecx
        xor     edi, esi
        add     edi, ebx
        lea     edi, [edi+eax+6FA87E4Fh]
        mov     eax, edi
        shr     eax, 1Ah
        shl     edi, 6
        or      eax, edi
        mov     edi, esi
        add     eax, ecx
        not     edi
        or      edi, eax
        mov     ebx, [esp+50h+var_1C]
        xor     edi, ecx
        add     edi, ebp
        mov     ebp, [esp+50h+var_28]
        lea     edi, [edi+edx-1D31920h]
        mov     edx, edi
        shl     edi, 0Ah
        shr     edx, 16h
        or      edx, edi
        mov     edi, ecx
        not     edi
        add     edx, eax
        or      edi, edx
        xor     edi, eax
        add     edi, ebp
        mov     ebp, [esp+50h+var_C]
        lea     edi, [edi+esi-5CFEBCECh]
        mov     esi, edi
        shl     edi, 0Fh
        shr     esi, 11h
        or      esi, edi
        mov     edi, eax
        add     esi, edx
        not     edi
        or      edi, esi
        xor     edi, edx
        add     edi, ebp
        mov     ebp, [esp+50h+var_30]
        lea     edi, [edi+ecx+4E0811A1h]
        mov     ecx, edi
        shl     ecx, 15h
        shr     edi, 0Bh
        or      ecx, edi
        mov     edi, edx
        add     ecx, esi
        not     edi
        or      edi, ecx
        xor     edi, esi
        add     edi, ebp
        mov     ebp, [esp+50h+var_14]
        lea     edi, [edi+eax-8AC817Eh]
        mov     eax, edi
        shr     eax, 1Ah
        shl     edi, 6
        or      eax, edi
        mov     edi, esi
        add     eax, ecx
        not     edi
        or      edi, eax
        xor     edi, ecx
        add     edi, ebp
        mov     ebp, [esp+50h+var_38]
        lea     edi, [edi+edx-42C50DCBh]
        mov     edx, edi
        shr     edx, 16h
        shl     edi, 0Ah
        or      edx, edi
        mov     edi, ecx
        add     edx, eax
        not     edi
        or      edi, edx
        xor     edi, eax
        add     edi, ebp
        lea     esi, [edi+esi+2AD7D2BBh]
        mov     edi, esi
        shr     edi, 11h
        shl     esi, 0Fh
        or      edi, esi
        mov     esi, eax
        add     edi, edx
        not     esi
        or      esi, edi
        xor     esi, edx
        add     esi, ebx
        lea     ecx, [esi+ecx-14792C6Fh]
        mov     esi, [esp+50h+arg_0]
        mov     ebx, [esi+8]
        add     ebx, eax
        mov     eax, ecx
        mov     [esi+8], ebx
        mov     ebx, [esi+0Ch]
        shl     eax, 15h
        shr     ecx, 0Bh
        or      eax, ecx
        add     eax, ebx
        add     eax, edi
        mov     [esi+0Ch], eax
        mov     eax, [esi+10h]
        add     eax, edi
        pop     edi
        mov     [esi+10h], eax
        mov     eax, [esi+14h]
        add     eax, edx
        mov     [esi+14h], eax
        pop     esi
        pop     ebp
        pop     ebx
        add     esp, 40h
        retn
    }
}

void my_DD6C70_ex( void *Key, const TCHAR *String, ULONG Length )
{
    ULONG Iter;
    ULONG Count;
    ULONG Eax;
    LONG Edx;
    ULONG *Ebx;
    const TCHAR *Esi;
    ULONG Edi;
    ULONG Ecx;

    Edx = Length;
    Ebx = ( ULONG* )Key;
    Esi = String;
    Eax = ( Ebx[0] >> 3 ) & 0x3F;
    Edi = Edx;
    Ecx = Edx * 8;
    Ebx[0] += Ecx;
    Ebx[1] += ( Edx >> 0x1D );
    if ( Ebx[0] < Ecx )
        Ebx[1]++;

    if ( Eax )
    {
        /*
        Length = ( 55 - x ) % 64 + 1;
        Ecx = Length + x = ( 55 - x ) % 64 + 1 + x = 56 + 64 * n;
        0 <= 64 * n + 55 - x < 64;
        ( x - 55 ) / 64 <= n < ( x + 7 ) / 64;
        */
        Ecx = Eax + Edx;
        if ( Ecx > 0x40 )
        {
            /* n >= 1, x >= 119; */
            Ecx = 0x40 - Eax;
        }
        else
        {
            /* n = 0, 4 < x <= 55 */
            Ecx = Edx;
        }
        Length = Ecx;
        memcpy( Eax + ( TCHAR* )Ebx + 24, Esi, Ecx );
        Eax += Ecx;
        if ( Eax < 0x40 )
            return;

        Edi = Edx - Ecx;
        Esi = Ecx + String;
        my_DD6D40( Ebx, ( TCHAR* )Ebx + 24 );
    }

    if ( Edi >= 0x40 )
    {
        Count = ( Edi >> 6 );
        Edi += ( 0 - Count ) << 6;

        for ( Iter = 0; Iter < Count; Iter++ )
        {
            my_DD6D40( Ebx, Esi );
            Esi += 0x40;
        }
    }

    if ( Edi )
        memcpy( ( TCHAR* )Ebx + 24, Esi, Edi );
}

void my_DD7650_ex( void *Key, TCHAR *Buffer )
{
    register LONG Iter;
    register ULONG *Esi;
    TCHAR Var[8];

    Esi = ( ULONG* )Key;
    for ( Iter = 0; Iter < 8; Iter++ )
        Var[Iter] = ( TCHAR ) ( Esi[( Iter >> 2 )] >> ( ( Iter & 3 ) << 3 ) );

    /* ( 55 - x ) % 64 + 1 */
    my_DD6C70_ex( Esi, ( TCHAR* )0xE84530, ( ( - 9 - ( Esi[0] >> 3 ) ) & 0x3F ) + 1 );
    my_DD6C70_ex( Esi, Var, 8 );

    for ( Iter = 0; Iter < 16; Iter++ )
        Buffer[Iter] = ( UCHAR ) ( Esi[( Iter >> 2 ) + 2] >> ( ( Iter & 3 ) << 3 ) );
}

void obfuscate_name( zend_function *Function, TCHAR *Buffer, const TCHAR *String, ULONG Length )
{
    zval ArgVal;
    zval *RetValue;
    zval *RetValuePtr;
    void *Dummy;

    TSRMLS_FETCH( );

    INIT_PZVAL( &ArgVal );
    ArgVal.type = IS_STRING;
    ArgVal.value.str.val = ( TCHAR* )String;
    ArgVal.value.str.len = Length;
    zend_ptr_stack_push( &GET_GS( )->GExecutor->argument_stack, &ArgVal );
    zend_ptr_stack_n_push( &GET_GS( )->GExecutor->argument_stack, 2, 1, NULL );
    zend_ptr_stack_n_push( &GET_GS( )->GExecutor->arg_types_stack, 3, NULL, NULL, NULL );

    ALLOC_ZVAL( RetValue );
    INIT_ZVAL( *RetValue );

    if ( GET_GS( )->ExtensionId < EXTENSION_ID_2 )
        ( ( HANDLER_1 )Function->internal_function.handler ) ( 1, RetValue, NULL, TRUE TSRMLS_CC );
    else
        ( ( HANDLER_2 )Function->internal_function.handler ) ( 1, RetValue, &RetValuePtr, NULL, TRUE TSRMLS_CC );

    RetValue->is_ref = 0;
    RetValue->refcount = 1;
    _tcscpy( Buffer, RetValue->value.str.val );
    zval_ptr_dtor( &RetValue );

    zend_ptr_stack_n_pop( &GET_GS( )->GExecutor->argument_stack, 3, &Dummy, &Dummy, &Dummy );
    zend_ptr_stack_n_pop( &GET_GS( )->GExecutor->arg_types_stack, 3, &Dummy, &Dummy, &Dummy );
}

void obfuscate_class_name_ex( TCHAR *Obfuscate, const TCHAR *String, ULONG Length )
{
    register ULONG Iter;
    register ULONG Count;
    register TCHAR *In;
    register TCHAR *Out;
    register ULONG Eax;
    UCHAR UseKey[SMALL_BUFFER_SIZE];
    TCHAR Buffer[SMALL_BUFFER_SIZE];
    const TCHAR LegecyCharSet[] = _T( "0123456789_abcdefghijklmnopqrstuvwxyz" );

    do
    {
        if ( *String == _T( '\0' ) )
        {
            String++;
            Length--;
        }

        if ( Length == 0 )
            break;

        Out = Obfuscate;
        if ( Length <= 4 )
        {
            _tcscpy( Buffer, String );
            for ( Iter = 0, Count = Length, In = Buffer; Iter < Count; Iter++ )
            {
                if ( In[Iter] == 0x7A )
                    In[Iter] = 0x5A;
                Eax = my_DDCE30_ex( In, Count );
                *Out++ = In[Iter] = LegecyCharSet[Eax % ( SIZE_OF_ARRAY( LegecyCharSet ) - 1 )];
            }
        }
        else
        {
            Out = Obfuscate;
            memcpy( UseKey, Key, sizeof( Key ) );
            my_DD6C70_ex( UseKey, String, Length );
            my_DD7650_ex( UseKey, Buffer );

            for ( Iter = 0, Count = Length, In = ( TCHAR* )String; Iter < Count; Iter++ )
            {
                Eax = Iter + 2;
                Eax &= 0x8000000F;
                if ( ( LONG )Eax < 0 )
                {
                    Eax--;
                    Eax |= 0xFFFFFFF0;
                    Eax++;
                }
                Eax = Buffer[Eax];
                Eax ^= *( ( UCHAR* )In );
                In++;
                *Out++ = LegecyCharSet[Eax % ( SIZE_OF_ARRAY( LegecyCharSet ) - 1 )];
            }
        }
        *Out = _T( '\0' );
    } while ( 0 );
}

void obfuscate_function_name_ex( TCHAR *Obfuscate, const TCHAR *String, ULONG Length )
{
    register ULONG Iter;
    register ULONG Count;
    register TCHAR *In;
    register TCHAR *Out;
    register ULONG Eax;
    UCHAR UseKey[SMALL_BUFFER_SIZE];
    TCHAR Buffer[SMALL_BUFFER_SIZE];

    do
    {
        if ( *String == _T( '\0' ) )
        {
            String++;
            Length--;
        }

        if ( Length == 0 )
            break;

        Out = Obfuscate;
        if ( Length <= 4 )
        {
            _tcscpy( Buffer, String );
            for ( Iter = 0, Count = Length, In = Buffer; Iter < Count; Iter++ )
            {
                Eax = my_DDCE30_ex( In, Count ) & 0x7F;
                if ( Eax == 0 )
                    Eax++;
                else if ( Eax == 0x3A )
                    Eax++;
                *Out++ = In[Iter] = ( TCHAR )Eax;
            }
        }
        else
        {
            memcpy( UseKey, Key, sizeof( Key ) );
            my_DD6C70_ex( UseKey, String, Length );
            my_DD7650_ex( UseKey, Buffer );

            for ( Iter = 0, Count = Length, In = ( TCHAR* )String; Iter < Count; Iter++ )
            {
                Eax = Iter + 1;
                Eax &= 0x8000000F;
                if ( ( LONG )Eax < 0 )
                {
                    Eax--;
                    Eax |= 0xFFFFFFF0;
                    Eax++;
                }
                Eax = Buffer[Eax];
                Eax ^= *( ( UCHAR* )In );
                Eax &= 0x8000007F;
                if ( ( LONG )Eax < 0 )
                {
                    Eax--;
                    Eax |= 0xFFFFFF80;
                    Eax++;
                }
                if ( Eax == 0 )
                    Eax++;
                else if ( Eax == 0x3A )
                    Eax++;
                In++;
                *Out++ = ( TCHAR )Eax;
            }
        }
        *Out = _T( '\0' );
    } while( 0 );
}

inline void obfuscate_name_ex( zend_function *Function, TCHAR *Obfuscate, const TCHAR *String, ULONG Length )
{
    if ( Function == GET_GS( )->zend_obfuscate_class_name )
        obfuscate_class_name_ex( Obfuscate, String, Length );
    else
        obfuscate_function_name_ex( Obfuscate, String, Length );
}

inline ULONG compare_obfuscate_class_name( const TCHAR *ObfuscateString, const TCHAR *String, ULONG Length )
{
    TCHAR Buffer[SMALL_BUFFER_SIZE];

    obfuscate_name( GET_GS( )->zend_obfuscate_class_name, Buffer, String, Length );

    return ( _tcsicmp( ObfuscateString, Buffer ) == 0 );
}

inline ULONG compare_obfuscate_function_name( const TCHAR *ObfuscateString, const TCHAR *String, ULONG Length )
{
    TCHAR Buffer[SMALL_BUFFER_SIZE];

    obfuscate_name( GET_GS( )->zend_obfuscate_function_name, Buffer, String, Length );

    return ( _tcsicmp( ObfuscateString, Buffer ) == 0 );
}

ULONG compare_obfuscate_class_name_ex( const TCHAR *ObfuscateString, const TCHAR *String, ULONG Length, ULONG CompareLength )
{
    ULONG RetCode;
    register ULONG Iter;
    register ULONG Count;
    register TCHAR *In;
    register ULONG Eax;
    UCHAR UseKey[SMALL_BUFFER_SIZE];
    TCHAR Buffer[SMALL_BUFFER_SIZE];
    const TCHAR LegecyCharSet[] = _T( "0123456789_abcdefghijklmnopqrstuvwxyz" );

    RetCode = FALSE;
    do
    {
        if ( *String == _T( '\0' ) )
        {
            String++;
            Length--;
        }

        if ( Length == 0 )
            break;

        if ( Length <= 4 )
        {
            _tcscpy( Buffer, String );
            for ( Iter = 0, Count = CompareLength, In = Buffer; Iter < Count; Iter++ )
            {
                if ( In[Iter] == 0x7A )
                    In[Iter] = 0x5A;
                Eax = my_DDCE30_ex( In, Count );
                In[Iter] = LegecyCharSet[Eax % ( SIZE_OF_ARRAY( LegecyCharSet ) - 1 )];
                if ( *ObfuscateString++ != In[Iter] )
                    return FALSE;
            }
        }
        else
        {
            memcpy( UseKey, Key, sizeof( Key ) );
            my_DD6C70_ex( UseKey, String, Length );
            my_DD7650_ex( UseKey, Buffer );

            for ( Iter = 0, Count = CompareLength, In = ( TCHAR* )String; Iter < Count; Iter++ )
            {
                Eax = Iter + 2;
                Eax &= 0x8000000F;
                if ( ( LONG )Eax < 0 )
                {
                    Eax--;
                    Eax |= 0xFFFFFFF0;
                    Eax++;
                }
                Eax = Buffer[Eax];
                Eax ^= *( ( UCHAR* )In );
                In++;
                if ( *ObfuscateString++ != LegecyCharSet[Eax % ( SIZE_OF_ARRAY( LegecyCharSet ) - 1 )] )
                    return FALSE;
            }
        }
        RetCode = TRUE;
    } while ( 0 );

    return RetCode;
}

ULONG compare_obfuscate_function_name_ex( const TCHAR *ObfuscateString, const TCHAR *String, ULONG Length, ULONG CompareLength )
{
    ULONG RetCode;
    register ULONG Iter;
    register ULONG Count;
    register TCHAR *In;
    register ULONG Eax;
    UCHAR UseKey[SMALL_BUFFER_SIZE];
    TCHAR Buffer[SMALL_BUFFER_SIZE];

    RetCode = FALSE;
    do
    {
        if ( *String == _T( '\0' ) )
        {
            String++;
            Length--;
        }

        if ( Length == 0 )
            break;

        if ( Length <= 4 )
        {
            _tcscpy( Buffer, String );
            for ( Iter = 0, Count = CompareLength, In = Buffer; Iter < Count; Iter++ )
            {
                Eax = my_DDCE30_ex( In, Count ) & 0x7F;
                if ( Eax == 0 )
                    Eax++;
                else if ( Eax == 0x3A )
                    Eax++;
                In[Iter] = ( TCHAR )Eax;
                if ( _T( 'A' ) <= ( TCHAR )Eax && ( TCHAR )Eax <= _T( 'Z' ) )
                    Eax += _T( 'a' ) - _T( 'A' );
                if ( *ObfuscateString++ != ( TCHAR )Eax )
                    return FALSE;
            }
        }
        else
        {
            memcpy( UseKey, Key, sizeof( Key ) );
            my_DD6C70_ex( UseKey, String, Length );
            my_DD7650_ex( UseKey, Buffer );

            for ( Iter = 0, Count = CompareLength, In = ( TCHAR* )String; Iter < Count; Iter++ )
            {
                Eax = Iter + 1;
                Eax &= 0x8000000F;
                if ( ( LONG )Eax < 0 )
                {
                    Eax--;
                    Eax |= 0xFFFFFFF0;
                    Eax++;
                }
                Eax = Buffer[Eax];
                Eax ^= *( ( UCHAR* )In );
                Eax &= 0x8000007F;
                if ( ( LONG )Eax < 0 )
                {
                    Eax--;
                    Eax |= 0xFFFFFF80;
                    Eax++;
                }
                if ( Eax == 0 )
                    Eax++;
                else if ( Eax == 0x3A )
                    Eax++;
                if ( _T( 'A' ) <= ( TCHAR )Eax && ( TCHAR )Eax <= _T( 'Z' ) )
                    Eax += _T( 'a' ) - _T( 'A' );
                if ( *ObfuscateString++ != ( TCHAR )Eax )
                    return FALSE;
                In++;
            }
        }
        RetCode = TRUE;
    } while( 0 );

    return RetCode;
}

ULONG obfuscate_name_guess( zend_function *Function, const TCHAR *String, TCHAR *Buffer, ULONG Length )
{
    ULONG RetCode;
    zval ArgVal;
    zval *RetValue;
    zval *RetValuePtr;
    void *Dummy;

    TSRMLS_FETCH( );

    RetCode = FALSE;
    memset( Buffer, _T( '1' ), Length );
    Buffer[0] = _T( 'a' );
    Buffer[Length] = 0;

    INIT_PZVAL( &ArgVal );
    ArgVal.type = IS_STRING;
    ArgVal.value.str.val = Buffer;
    ArgVal.value.str.len = Length;
    zend_ptr_stack_push( &GET_GS( )->GExecutor->argument_stack, &ArgVal );
    zend_ptr_stack_n_push( &GET_GS( )->GExecutor->argument_stack, 2, 1, NULL );
    zend_ptr_stack_n_push( &GET_GS( )->GExecutor->arg_types_stack, 3, NULL, NULL, NULL );

    do
    {
        ALLOC_ZVAL( RetValue );
        INIT_ZVAL( *RetValue );

        if ( GET_GS( )->ExtensionId < EXTENSION_ID_2 )
            ( ( HANDLER_1 )Function->internal_function.handler ) ( 1, RetValue, NULL, TRUE TSRMLS_CC );
        else
            ( ( HANDLER_2 )Function->internal_function.handler ) ( 1, RetValue, &RetValuePtr, NULL, TRUE TSRMLS_CC );

        RetValue->is_ref = 0;
        RetValue->refcount = 1;
        if ( String[0] == RetValue->value.str.val[0] && 0 == _tcsicmp( String, RetValue->value.str.val ) )
        {
            zval_ptr_dtor( &RetValue );
            RetCode = TRUE;
            break;
        }
        zval_ptr_dtor( &RetValue );

        inc_string( Buffer, Length );
    } while ( Buffer[0] != _T( '0' ) );

    zend_ptr_stack_n_pop( &GET_GS( )->GExecutor->argument_stack, 3, &Dummy, &Dummy, &Dummy );
    zend_ptr_stack_n_pop( &GET_GS( )->GExecutor->arg_types_stack, 3, &Dummy, &Dummy, &Dummy );

    return RetCode;
}

ULONG obfuscate_class_name_guess_ex( const TCHAR *String, TCHAR *Buffer, ULONG Length )
{
    ULONG RetCode;

    RetCode = FALSE;
    memset( Buffer, _T( '1' ), Length );
    Buffer[0] = _T( 'a' );
    Buffer[Length] = 0;

    do
    {
        if ( compare_obfuscate_class_name_ex( String, Buffer, Length, Length ) )
        {
            RetCode = TRUE;
            break;
        }
        inc_string( Buffer, Length );
    } while ( Buffer[0] != _T( '0' ) );

    return RetCode;
}

ULONG obfuscate_function_name_guess_ex( const TCHAR *String, TCHAR *Buffer, ULONG Length )
{
    ULONG RetCode;

    RetCode = FALSE;
    memset( Buffer, _T( '1' ), Length );
    Buffer[0] = _T( 'a' );
    Buffer[Length] = 0;

    do
    {
        if ( compare_obfuscate_function_name_ex( String, Buffer, Length, Length ) )
        {
            RetCode = TRUE;
            break;
        }
        inc_string( Buffer, Length );
    } while ( Buffer[0] != _T( '0' ) );

    return RetCode;
}

ULONG obfuscate_name_guess_ex( zend_function *Function, const TCHAR *String, TCHAR *Buffer, ULONG Length )
{
    if ( Function == GET_GS( )->zend_obfuscate_class_name )
        return obfuscate_class_name_guess_ex( String, Buffer, Length );
    else
        return obfuscate_function_name_guess_ex( String, Buffer, Length );
}

ULONG decode_obfuscate_name( zend_function *Function, PCOMMON_STACK_S Buffer, LPCTSTR Name, ULONG Length )
{
    POBFUSCATE_NAME_ENTRY Entry;
    ULONG Tick;
    ULONG Top;
    ULONG NewLength;
    TCHAR Result[BUFFER_SIZE];

    Entry = FindObfuscateName( Name, Length );
    if ( Entry )
    {
        StackPushS( Buffer, Entry->Name, Entry->NameLength );
        return TRUE;
    }

    if ( Length <= GET_GS( )->DecodeLevelHigh )
    {
        if ( GET_GS_FLAGS( ) & GS_FLAGS_TICK )
            Tick = GetTickCount( );
        else
            Tick = 0;
        if ( obfuscate_name_guess_ex( Function, Name, Result, Length ) )
        {
            if ( GET_GS_FLAGS( ) & GS_FLAGS_TICK )
                _tprintf( _T( "[%s]<%s>-><%s> Tick[%d]\r\n" ), Function->common.function_name, Name, Result, GetTickCount( ) - Tick );
            InsertObfuscateName( Result, Length, Name, Length );
            StackPushS( Buffer, Result, Length );
            return TRUE;
        }
    }

    Top = StackCountS( Buffer );
    StackPushS( Buffer, GET_GS( )->ObfuscatePrefix, GET_GS( )->ObfuscatePrefixLength );
    NewLength = Base64EncodeX( Result, Name, Length );
    NewLength = StackPushS( Buffer, Result, NewLength );
    InsertObfuscateName( StackBaseS( Buffer ) + Top, NewLength - Top, Name, Length );

    return FALSE;
}

ULONG decode_obfuscate_class_name( PCOMMON_STACK_S Buffer, LPCTSTR Name, ULONG Length )
{
    ULONG ExtendLength;

    if ( GET_GS_STATE( ) & GS_STATE_OBFUSCATE )
        return decode_obfuscate_name( GET_GS( )->zend_obfuscate_class_name, Buffer, Name, Length );

    ExtendLength = ParseExtendVariableLength( Name, Length );
    if ( ExtendLength )
        ParseExtendVariableEx( Buffer, Length + ExtendLength, Name, Length );
    else
        StackPushS( Buffer, Name, Length );

    return TRUE;
}

ULONG decode_obfuscate_function_name( PCOMMON_STACK_S Buffer, LPCTSTR Name, ULONG Length )
{
    ULONG ExtendLength;

    if ( GET_GS_STATE( ) & GS_STATE_OBFUSCATE )
        return decode_obfuscate_name( GET_GS( )->zend_obfuscate_function_name, Buffer, Name, Length );

    ExtendLength = ParseExtendVariableLength( Name, Length );
    if ( ExtendLength )
        ParseExtendVariableEx( Buffer, Length + ExtendLength, Name, Length );
    else
        StackPushS( Buffer, Name, Length );

    return TRUE;
}

void obfuscate_name_test( zend_function *Function, ULONG Start, ULONG End )
{
    zval ArgVal;
    zval *RetValue;
    zval *RetValuePtr;
    void *Dummy;
    ULONG Length;
    ULONG Tick;
    TCHAR Buffer[SMALL_BUFFER_SIZE];
    TCHAR Result[SMALL_BUFFER_SIZE];

    TSRMLS_FETCH( );

    if ( Start == 0 )
        Start = 1;

    INIT_PZVAL( &ArgVal );
    zend_ptr_stack_push( &GET_GS( )->GExecutor->argument_stack, &ArgVal );
    zend_ptr_stack_n_push( &GET_GS( )->GExecutor->argument_stack, 2, 1, NULL );
    zend_ptr_stack_n_push( &GET_GS( )->GExecutor->arg_types_stack, 3, NULL, NULL, NULL );

    for ( Length = Start; Length <= End; Length++ )
    {
        ArgVal.type = IS_STRING;
        ArgVal.value.str.val = generate_string( Buffer, Length );
        ArgVal.value.str.len = Length;

        ALLOC_ZVAL( RetValue );
        INIT_ZVAL( *RetValue );

        Tick = GetTickCount( );
        obfuscate_name_ex( Function, Result, Buffer, Length );
        ADD_DEBUG_LOG_LR( _T( "Result<%s> Tick[%d]" ), Result, GetTickCount( ) - Tick );

        if ( GET_GS( )->ExtensionId < EXTENSION_ID_2 )
            ( ( HANDLER_1 )Function->internal_function.handler ) ( 1, RetValue, NULL, TRUE TSRMLS_CC );
        else
            ( ( HANDLER_2 )Function->internal_function.handler ) ( 1, RetValue, &RetValuePtr, NULL, TRUE TSRMLS_CC );

        ADD_DEBUG_LOG_LR( _T( "<%s>:[%d]-><%s>:[%d]" ), Buffer, Length, RetValue->value.str.val, RetValue->value.str.len );

        RetValue->is_ref = 0;
        RetValue->refcount = 1;
        zval_ptr_dtor( &RetValue );
    }

    zend_ptr_stack_n_pop( &GET_GS( )->GExecutor->argument_stack, 3, &Dummy, &Dummy, &Dummy );
    zend_ptr_stack_n_pop( &GET_GS( )->GExecutor->arg_types_stack, 3, &Dummy, &Dummy, &Dummy );
}

void generate_obfuscate_name_list( zend_function *Function, ULONG Start, ULONG End )
{
    zval ArgVal;
    zval *RetValue;
    zval *RetValuePtr;
    void *Dummy;
    ULONG Length;
    TCHAR Buffer[BUFFER_SIZE];

    TSRMLS_FETCH( );

    if ( Start == 0 )
        Start = 1;

    for ( Length = Start; Length <= End; Length++ )
    {
        memset( Buffer, _T( '1' ), Length );
        Buffer[0] = _T( 'a' );
        Buffer[Length] = 0;

        INIT_PZVAL( &ArgVal );
        ArgVal.type = IS_STRING;
        ArgVal.value.str.val = Buffer;
        ArgVal.value.str.len = Length;
        zend_ptr_stack_push( &GET_GS( )->GExecutor->argument_stack, &ArgVal );
        zend_ptr_stack_n_push( &GET_GS( )->GExecutor->argument_stack, 2, 1, NULL );
        zend_ptr_stack_n_push( &GET_GS( )->GExecutor->arg_types_stack, 3, NULL, NULL, NULL );

        do
        {
            ALLOC_ZVAL( RetValue );
            INIT_ZVAL( *RetValue );

            if ( GET_GS( )->ExtensionId < EXTENSION_ID_2 )
                ( ( HANDLER_1 )Function->internal_function.handler ) ( 1, RetValue, NULL, TRUE TSRMLS_CC );
            else
                ( ( HANDLER_2 )Function->internal_function.handler ) ( 1, RetValue, &RetValuePtr, NULL, TRUE TSRMLS_CC );

            RetValue->is_ref = 0;
            RetValue->refcount = 1;
            ADD_DEBUG_LOG_LR( _T( "<%s>-><%s>" ), Buffer, RetValue->value.str.val );
            zval_ptr_dtor( &RetValue );
            inc_string( Buffer, Length );
        } while ( Buffer[0] != _T( '0' ) );

        zend_ptr_stack_n_pop( &GET_GS( )->GExecutor->argument_stack, 3, &Dummy, &Dummy, &Dummy );
        zend_ptr_stack_n_pop( &GET_GS( )->GExecutor->arg_types_stack, 3, &Dummy, &Dummy, &Dummy );
    }
}

void zend_loader_info( )
{
    zval *RetValue;
    const TCHAR Yes[] = _T( "Yes" );
    const TCHAR No[] = _T( "No" );

    RetValue = zend_loader_version( );
    if ( RetValue )
    {
        ADD_DEBUG_LOG_LR( _T( "loader_version< %s >" ), RetValue->value.str.val );
        free_zval( RetValue );
    }

    RetValue = zend_optimizer_version( );
    if ( RetValue )
    {
        ADD_DEBUG_LOG_LR( _T( "optimizer_version< %s >" ), RetValue->value.str.val );
        free_zval( RetValue );
    }

    ADD_DEBUG_LOG_LR( _T( "loader_enabled< %s >" ), GET_GS_STATE( ) & GS_STATE_LOADER_ENABLED ? Yes : No );
    ADD_DEBUG_LOG_LR( _T( "loader_file_encoded< %s >" ), GET_GS_STATE( ) & GS_STATE_LOADER_FILE_ENCODED ? Yes : No );
    ADD_DEBUG_LOG_LR( _T( "runtime_obfuscate< %s >" ), GET_GS_STATE( ) & GS_STATE_RUNTIME_OBFUSCATE ? Yes : No );
    ADD_DEBUG_LOG_LR( _T( "current_obfuscation_level[ %d ]" ), GET_GS_STATE( ) & GS_STATE_OBFUSCATION_LEVEL_MASK );
    ADD_DEBUG_LOG_LR( _T( "format_id[ %08X( %d ) ]" ), GET_GS( )->FormatId, GET_GS( )->FormatId );
    ADD_DEBUG_LOG_LR( _T( "major_id[ %08X( %d ) ]" ), GET_GS( )->MajorId, GET_GS( )->MajorId );
}

void dump_defined_vars( )
{
    zval *RetValue;

    RetValue = get_defined_vars( );
    if ( RetValue )
    {
        ADD_DEBUG_LOG_LR( _T( "get_defined_vars" ) );
        dump_zval( RetValue );
        ADD_DEBUG_LOG_LR( _T( "" ) );
        free_zval( RetValue );
    }
}

ULONG GetPhpVersion( )
{
    ULONG RetCode;
    zval *RetValue;
    TCHAR *String;
    TCHAR *String1;

    RetCode = 0;
    RetValue = php_version( );
    if ( RetValue )
    {
        String = strchr( RetValue->value.str.val, _T( '.' ) );
        *String = _T( '\0' );

        String1 = String;
        do
        {
            String1--;
        } while ( *String1 >= _T( '0' ) && *String1 <= _T( '9' ) );
        String1++;
        RetCode = atoi( String1 ) & 0xFFFF;

        String1 = String;
        do
        {
            String1++;
        } while ( *String1 >= _T( '0' ) && *String1 <= _T( '9' ) );
        *String1 = _T( '\0' );
        RetCode |= atoi( String + 1 ) << 16;

        String = String1;
        do
        {
            String1++;
        } while ( *String1 >= _T( '0' ) && *String1 <= _T( '9' ) );
        *String1 = _T( '\0' );
        RetCode |= atoi( String + 1 ) << 24;

        free_zval( RetValue );
    }

    return RetCode;
}

#ifdef ZEND_ENGINE_2
inline opcode_handler_t_2 vm_get_opcode_handler( zend_op *OpLine )
{
    return zend_opcode_handlers[OP_CODE( OpLine ) * 25 + GET_VM_DECODE( OP1_TYPE( OpLine ) ) * 5 + GET_VM_DECODE( OP2_TYPE( OpLine ) )];
}

inline ULONG vm_get_opcode( zend_op *OpLine )
{
    ULONG RetCode;
    ULONG Iter;
    ULONG Count;

    if ( OpLine->handler == zend_opcode_handlers[ZEND_OP_DATA * 25 + _CV_CODE * 5 ] )
        return ZEND_OP_DATA;

    RetCode = ZEND_NOP;
    Count = GET_OP_TABLE_ARRAY_SIZE( ) * 25 + 1;
    for ( Iter = GET_VM_DECODE( OP1_TYPE( OpLine ) ) * 5 + GET_VM_DECODE( OP2_TYPE( OpLine ) ); Iter < Count; Iter += 25 )
    {
        if ( zend_opcode_handlers[Iter] == OpLine->handler )
        {
            RetCode = Iter / 25;
            break;
        }
    }

    return RetCode;
}
#endif

ULONG InitFunction( PZEND_VAR_ENTRY StringList, ULONG Size )
{
    register ULONG Iter;
    register ULONG Count;
    register PZEND_VAR_ENTRY Entry;
    PCOMMON_STACK_S Buffer;
    const TCHAR *String;

    Iter = 0;
    Count = Size;
    Entry = StringList;
    LOCK_GS( );
    Buffer = &GET_GS( )->Buffer;
    for ( ; Iter < Count; Iter++, Entry++ )
    {
        decode_obfuscate_function_name( Buffer, Entry->Name, Entry->NameLengh );
        StackPopAllS( Buffer, &String );
        InsertVariable( IS_FUNCTION, Iter, String, NULL, VE_FLAGS_OBFUSCATE );
    }
    UNLOCK_GS( );

    return Iter;
}

/*
///////////////////////////////////////////////////////////////////////////////
// InitExtendInfo
///////////////////////////////////////////////////////////////////////////////
*/
void InitExtendInfo( PDUMP_STACK Stack )
{
    register ULONG Iter;
    register ULONG Count;
    ULONG Size;
    ULONG State;
    zend_op_array *OpArray;
    PZEND_EXTEND_INFO ExtendInfo;
    PZEND_EXTEND_FUNCTION_INFO FunctionInfo;
    PZEND_VAR_ENTRY Var1;
    zend_compiled_variable_2 *Var2;
    zend_op *StartOpLine;
    zend_op *OpLine;
    zend_uchar *DecodeOpCodeTable;
    register zend_uchar OpCode;
    register zend_uchar Delta;
    zend_uchar *OrgOpCode;
    ULONG64 Multi;
    register ULONG Edx;

    do
    {
        Size = Stack->LastOffset;
        if ( !Size )
            break;

        State = GET_GS_STATE( );
        if ( State & GS_STATE_RUNTIME_OBFUSCATE )
            Stack->State |= DS_STATE_RUNTIME_OBFUSCATE;

        if ( State & GS_STATE_OBFUSCATE )
            Stack->State |= DS_STATE_OBFUSCATE;

        if ( State & GS_STATE_OP_ENCODE )
            Stack->State |= DS_STATE_OP_ENCODE;

        if ( State & GS_STATE_EXTEND )
            Stack->State |= DS_STATE_EXTEND;

        OpArray = Stack->OpArray;
        StartOpLine = Stack->Head;

        /* Extension information */
        ExtendInfo = OpArray->reserved[0];
        Stack->ExtendInfo = ExtendInfo;

        /* Variable name and index */
        if ( GET_GS( )->ExtensionId < EXTENSION_ID_2 )
        {
            if ( !( State & GS_STATE_EXTEND ) )
                break;

            Var1 = ExtendInfo->StringList;
            if ( Var1 )
            {
                if ( GET_GS_FLAGS( ) & GS_FLAGS_DEBUG )
                    ADD_DEBUG_LOG_LR( _T( "OpArray[ %08X ] Reserved[ %08X ] Var[ %08X ]" ), OpArray, ExtendInfo, Var1 );
                Count = ExtendInfo->StringIndex;
                for ( Iter = 0; Iter < Count; Iter++, Var1++ )
                    InsertVariable( IS_CV, Iter, Var1->Name, NULL, 0 );
            }
        }
        else
        {
            Var2 = ( ( zend_op_array_2* )OpArray )->vars;
            if ( Var2 )
            {
                if ( GET_GS_FLAGS( ) & GS_FLAGS_DEBUG )
                    ADD_DEBUG_LOG_LR( _T( "OpArray[ %08X ] Reserved[ %08X ] Var[ %08X ]" ), OpArray, ExtendInfo, Var2 );
                Count = ( ( zend_op_array_2* )OpArray )->last_var;
                for ( Iter = 0; Iter < Count; Iter++, Var2++ )
                    InsertVariable( IS_CV, Iter, Var2->name, NULL, 0 );
            }

            if ( !( State & GS_STATE_EXTEND ) )
                break;
        }

        /* Function name and index */
        FunctionInfo = ExtendInfo->Function;
        if ( FunctionInfo && FunctionInfo->StringList )
            InitFunction( FunctionInfo->StringList, FunctionInfo->StringIndex );

        if ( GET_GS( )->ExtensionId < EXTENSION_ID_2 )
        {
            if ( !( Stack->State & DS_STATE_OP_ENCODE ) || ExtendInfo == NULL || ExtendInfo->u.Trans == NULL )
                break;

            DecodeOpCodeTable = ExtendInfo->u.Trans->OpCodeTable;
            if ( DecodeOpCodeTable == NULL )
            {
                Stack->State &= ~DS_STATE_OP_ENCODE;
                break;
            }

            OrgOpCode = ( zend_uchar* )HEAP_ALLOC( Size * sizeof( zend_uchar ) );
            if ( OrgOpCode == NULL )
                break;

            Stack->OrgOpCode = OrgOpCode;
            Stack->DecodeOpCodeTable = DecodeOpCodeTable;
            OpLine = StartOpLine;
            for ( Iter = 0; Iter < Size; Iter++, OpLine++ )
            {
                Multi = 0x2E8BA2E9 * ( ULONG64 ) ( ( ULONG )OpLine - ( ULONG )StartOpLine );
                Edx = ( ( ULONG ) ( Multi >> 32 ) >> 4 );
                Delta = ( zend_uchar ) ( ( Edx + ( Edx >> 31 ) ) & 7 );
                OpCode = OP_CODE( OpLine );
                *OrgOpCode++ = OpCode;
                OP_CODE( OpLine ) = ( zend_uchar ) ( DecodeOpCodeTable[OpCode] - Delta );
            }
        }
        else
        {
#ifdef ZEND_ENGINE_2
            OrgOpCode = HEAP_ALLOC( Size * sizeof( ULONG ) );
            if ( OrgOpCode == NULL )
                break;

            Stack->OrgOpCode = OrgOpCode;
            Stack->DecodeOpCodeTable = NULL;
            OpLine = StartOpLine;
            if ( Stack->State & DS_STATE_OP_ENCODE || GET_GS( )->RealExtensionId == EXTENSION_ID_3 )
            {
                for ( Iter = 0; Iter < Size; Iter++, OpLine++ )
                {
                    *OrgOpCode++ = OP_CODE( OpLine );
                    OP_CODE( OpLine ) = ( zend_uchar )vm_get_opcode( OpLine );
                }
            }
            else
            {
                register zend_uchar *zend_user_opcodes = zend_get_user_opcodes( );
                for ( Iter = 0; Iter < Size; Iter++, OpLine++ )
                {
                    *OrgOpCode++ = OP_CODE( OpLine );
                    OP_CODE( OpLine ) = zend_user_opcodes[OP_CODE( OpLine )];
                }
            }
#endif
        }
    } while ( 0 );
}

/*
///////////////////////////////////////////////////////////////////////////////
// UninitExtendInfo
///////////////////////////////////////////////////////////////////////////////
*/
void UninitExtendInfo( PDUMP_STACK Stack )
{
    register ULONG Iter;
    register ULONG Count;
    register zend_op *OpLine;
    register zend_uchar *OrgOpCode;

    OrgOpCode = Stack->OrgOpCode;
    if ( OrgOpCode )
    {
        Count = Stack->LastOffset;
        for ( Iter = 0, OpLine = Stack->Head; Iter < Count; Iter++, OpLine++ )
            OP_CODE( OpLine ) = OrgOpCode[Iter];
    }
}

/*
///////////////////////////////////////////////////////////////////////////////
// fix_flags
///////////////////////////////////////////////////////////////////////////////
*/
ULONG fix_flags( zend_op *OpLine, ULONG Flags )
{
    ULONG RetCode;

    UNREFERENCED_PARAMETER( Flags );

    switch ( OP_CODE( OpLine ) )
    {
    case ZEND_JMP :
        RetCode = DS_IFLAGS_IS_OPLINE1;
        break;

    case ZEND_JMPZ :
    case ZEND_JMPNZ :
    case ZEND_JMPZ_EX :
    case ZEND_JMPNZ_EX :
        RetCode = DS_IFLAGS_IS_OPLINE2;
        break;

    case ZEND_JMPZNZ :
        RetCode = DS_IFLAGS_IS_SPECIAL;
        break;

    case ZEND_JMP_NO_CTOR :
        RetCode = DS_IFLAGS_IS_OPLINE2;
        break;

    case ZEND_CLONE :
    case ZEND_USER_OPCODE :
        RetCode = DS_IFLAGS_IS_FUNCTION | DS_IFLAGS_IS_OPLINE1;
        break;

    case ZEND_FETCH_CLASS :
        RetCode = DS_IFLAGS_IS_CLASS | DS_IFLAGS_IS_RESULT;
        break;

    case ZEND_OP_DATA :
        RetCode = DS_IFLAGS_IS_RESULT | DS_IFLAGS_IS_VAR;
        break;

    default :
        RetCode = OP_CODE( OpLine ) << DS_IFLAGS_OPCODE_SHIFT;
        break;
    }

    return RetCode;
}

/*
///////////////////////////////////////////////////////////////////////////////
// dump_opcode_detail
///////////////////////////////////////////////////////////////////////////////
*/
void dump_opcode_detail( PDUMP_STACK Stack )
{
    ULONG Step;
    ULONG Flags;
    ULONG Offset;
    ULONG FetchType;
    zend_op *Head;
    zend_op *OpLine;
    const TCHAR *FetchTypeString = _T( "[-]" );
    TCHAR Buffer[256];

    Step = 0;
    Flags = Stack->InternalFlags;
    Offset = Stack->Offset;
    Head = Stack->Head;
    OpLine = Stack->OpLine;

    if ( Flags & DS_IFLAGS_OP_FETCH )
    {
        FetchType = NODE_FETCH_TYPE( &OpLine->op2 );
        switch ( FetchType )
        {
        case ZEND_FETCH_GLOBAL :
            FetchTypeString = _T( "[G]" );
            break;
        case ZEND_FETCH_LOCAL :
            FetchTypeString = _T( "[L]" );
            break;
        case ZEND_FETCH_STATIC :
            FetchTypeString = _T( "[S]" );
            break;
#ifdef ZEND_ENGINE_2
        case ZEND_FETCH_STATIC_MEMBER :
            FetchTypeString = _T( "[M]" );
            break;

        case ZEND_FETCH_GLOBAL_LOCK :
            FetchTypeString = _T( "[K]" );
            break;
#endif
        default :
            _sntprintf( Buffer, sizeof( Buffer ), _T( "[%1d]" ), FetchType );
            FetchTypeString = Buffer;
            break;
        }
    }

    if ( GET_GS_FLAGS( ) & GS_FLAGS_OPCODE || Flags & DS_IFLAGS_UNKNOWN_OP )
        ADD_DEBUG_LOG( _T( "%6d  <%03d>%-23s %-3s " ), Offset, OP_CODE( OpLine ), Stack->OpName, FetchTypeString );
    else
        ADD_DEBUG_LOG( _T( "%6d  %-28s %-3s " ), Offset, Stack->OpName, FetchTypeString );

    ADD_DEBUG_LOG( _T( "%3ld[%d] " ), OP_EX_VALUE( OpLine ), OPR_EA_TYPE( OpLine ) );

    if ( Flags & DS_IFLAGS_FIX_NODE )
        Flags = fix_flags( OpLine, Flags );

    if ( OP_CODE( OpLine ) == ZEND_BRK || OP_CODE( OpLine ) == ZEND_CONT )
    {
        if ( OPLINE_BRK_CONT( OpLine ) == - 1 )
            ADD_DEBUG_LOG( _T( " - v[?] ^[?] N[%d]" ), OP2_VAL( OpLine )->value.lval );
        else if ( Stack->OpArray->brk_cont_array )
            ADD_DEBUG_LOG( _T( " - v[%d] ^[%d] N[%d]" ),
                Stack->OpArray->brk_cont_array[OPLINE_BRK_CONT( OpLine )].brk,
                Stack->OpArray->brk_cont_array[OPLINE_BRK_CONT( OpLine )].cont,
                OP2_VAL( OpLine )->value.lval
                );
        else
            ADD_DEBUG_LOG( _T( " - [?]" ) );
    }
    else
    {
        if ( !dump_znode( Stack, Flags & DS_IFLAGS_DUMP_MASK_R, &Step, &OpLine->result ) )
            ADD_LOG( _T( " - " ) );

        if ( !dump_znode( Stack, Flags & DS_IFLAGS_DUMP_MASK_OP1, &Step, &OpLine->op1 ) )
            ADD_LOG( _T( " - " ) );

        if ( !dump_znode( Stack, Flags & DS_IFLAGS_DUMP_MASK_OP2, &Step, &OpLine->op2 ) )
            ADD_LOG( _T( " - " ) );
    }

    ADD_LOG_LR( _T( "" ) );
}

/*
///////////////////////////////////////////////////////////////////////////////
// dump_opcode_detail_ex
///////////////////////////////////////////////////////////////////////////////
*/
void dump_opcode_detail_ex( PDUMP_STACK Stack )
{
    zend_op *OpLine;
    zend_uchar OpCode;

    if ( Stack->Head )
    {
        OpLine = Stack->Head + Stack->Offset;
        OpCode = OP_CODE( OpLine );
        Stack->OpLine = OpLine;
        if ( OpCode >= GET_OP_TABLE_ARRAY_SIZE( ) )
        {
            Stack->InternalFlags = DS_IFLAGS_UNKNOWN_OP;
            Stack->OpName = _T( "?" );
            Stack->OpString = _T( "" );
        }
        else
        {
            Stack->InternalFlags = GET_OP_TABLE( OpCode ).Flags;
            Stack->OpName = GET_OP_TABLE( OpCode ).OpName;
            Stack->OpString = GET_OP_TABLE( OpCode ).Op;
        }
        dump_opcode_detail( Stack );
    }
}

/*
///////////////////////////////////////////////////////////////////////////////
// dump_xxx
///////////////////////////////////////////////////////////////////////////////
*/
ULONG FASTCALL dump_bool_not( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG OpType;
    ULONG Dummy;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    PVARIABLE_ENTRY Var1;
    const TCHAR *OpString;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        if ( TEST_OP1_CONST( OpLine ) )
        {
            StackPushS( &Stack->Buffer, Stack->OpString, _tcslen( Stack->OpString ) );
            make_printable_zval_url( OP1_VAL( OpLine ), &Stack->Buffer );
            RetCode = StackPopAllS( &Stack->Buffer, &String );
            OpType = DS_IFLAGS_OT_BOOL_NOT;
        }
        else
        {
            Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                break;

            Var1 = FindInsertVariable( OPR_TYPE( OpLine ), OPR_VAR( OpLine ) );
            if ( Var1 == NULL )
                break;

            if ( Var1->Flags & ( VE_FLAGS_JMPZ_EX | VE_FLAGS_JMPNZ_EX ) )
            {
                if ( Var1->Flags & VE_FLAGS_JMPZ_EX )
                {
                    OpType = DS_IFLAGS_OT_BOOL_AND;
                    OpString = GET_OP_STRING_EX( OT_BOOL_AND );
                    Dummy = sizeof( " && " ) - 1;
                }
                else
                {
                    OpType = DS_IFLAGS_OT_BOOL_OR;
                    OpString = GET_OP_STRING_EX( OT_BOOL_OR );
                    Dummy = sizeof( " || " ) - 1;
                }

                if ( ( Var1->Flags & VE_FLAGS_SILENCE_FUNCTION ) == VE_FLAGS_SILENCE_FUNCTION )
                    StackPushS( &Stack->Buffer, DEFAULT_SILENCE_STRING, DEFAULT_SILENCE_STRING_LENGTH );

                if ( ( Var1->Flags & DS_IFLAGS_OT_MASK ) < OpType )
                {
                    StackPushS( &Stack->Buffer, _T( "( " ), 2 );
                    StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
                    StackPushS( &Stack->Buffer, _T( " )" ), 2 );
                }
                else
                {
                    StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
                }

                StackPushS( &Stack->Buffer, OpString, Dummy );

                if ( ( Var->Flags & VE_FLAGS_SILENCE_FUNCTION ) == VE_FLAGS_SILENCE_FUNCTION )
                    StackPushS( &Stack->Buffer, DEFAULT_SILENCE_STRING, DEFAULT_SILENCE_STRING_LENGTH );

                if ( ( Var->Flags & DS_IFLAGS_OT_MASK ) < DS_IFLAGS_OT_BOOL_NOT )
                {
                    StackPushS( &Stack->Buffer, Stack->OpString, _tcslen( Stack->OpString ) );
                    StackPushS( &Stack->Buffer, _T( "( " ), 2 );
                    StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
                    StackPushS( &Stack->Buffer, _T( " )" ), 2 );
                }
                else if ( ( Var->Flags & DS_IFLAGS_OT_MASK ) == DS_IFLAGS_OT_BOOL_NOT )
                {
                    StackPushS( &Stack->Buffer, Var->Expr + 1, Var->ExprLength - 1 );
                }
                else
                {
                    StackPushS( &Stack->Buffer, Stack->OpString, _tcslen( Stack->OpString ) );
                    StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
                }
                RetCode= StackPopAllS( &Stack->Buffer, &String );
                OpType |= ( Var->Flags & VE_FLAGS_EXPRESS_MASK ) | VE_FLAGS_SKIP_SILENCE;
            }
            else
            {
                OpType = DS_IFLAGS_OT_BOOL_NOT;
                if ( ( Var->Flags & DS_IFLAGS_OT_MASK ) < DS_IFLAGS_OT_BOOL_NOT )
                {
                    StackPushS( &Stack->Buffer, Stack->OpString, _tcslen( Stack->OpString ) );
                    StackPushS( &Stack->Buffer, _T( "( " ), 2 );
                    StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
                    StackPushS( &Stack->Buffer, _T( " )" ), 2 );
                }
                else if ( ( Var->Flags & DS_IFLAGS_OT_MASK ) == DS_IFLAGS_OT_BOOL_NOT )
                {
                    StackPushS( &Stack->Buffer, Var->Expr + 1, Var->ExprLength - 1 );
                }
                else
                {
                    StackPushS( &Stack->Buffer, Stack->OpString, _tcslen( Stack->OpString ) );
                    StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
                }
                RetCode = StackPopAllS( &Stack->Buffer, &String );
                OpType |= ( Var->Flags & VE_FLAGS_EXPRESS_MASK );
            }
        }

        if ( TEST_OPR_ALL_VAR( OpLine ) )
            UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, OpType );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_cast( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG OpType;
    ULONG Dummy;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    const TCHAR *OpString;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        if ( TEST_OP1_CONST( OpLine ) )
        {
            make_printable_zval_url( OP1_VAL( OpLine ), &Stack->Buffer1 );
            Dummy = StackPopAllS( &Stack->Buffer1, &String );
            OpType = DS_IFLAGS_OT_MAX;
        }
        else if ( TEST_OP1_ALL_VAR( OpLine ) )
        {
            Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                break;

            String = Var->Expr;
            Dummy = Var->ExprLength;
            OpType = Var->Flags & DS_IFLAGS_OT_MASK;
        }
        else
        {
            break;
        }

        if ( OP_EX_VALUE( OpLine ) < GET_DATA_TYPE_ARRAY_SIZE( ) )
            OpString = GET_DATA_TYPE( OP_EX_VALUE( OpLine ) );
        else
            OpString = _T( "?" );

        StackPushS( &Stack->Buffer, _T( "( " ), 2 );
        StackPushS( &Stack->Buffer, OpString, _tcslen( OpString ) );
        StackPushS( &Stack->Buffer, _T( " )" ), 2 );
        if ( OpType < ( Stack->InternalFlags & DS_IFLAGS_OT_MASK ) )
        {
            StackPushS( &Stack->Buffer, _T( "( " ), 2 );
            StackPushS( &Stack->Buffer, String, Dummy );
            StackPushS( &Stack->Buffer, _T( " )" ), 2 );
        }
        else
        {
            StackPushS( &Stack->Buffer, String, Dummy );
        }

        /* Prefix */
        if ( Stack->State & DS_STATE_SILENCE && OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushPrefixS( &Stack->Buffer, Stack->StartChar, Stack->StartCharLength );

        /* Postfix */
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushS( &Stack->Buffer, Stack->EndChar, Stack->EndCharLength );

        RetCode = StackPopAllExS( &Stack->Buffer, &String );
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            dump_string( Stack, String );
        else if ( TEST_OPR_ALL_VAR( OpLine ) )
            UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, Stack->InternalFlags & DS_IFLAGS_OT_MASK );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_qm_assign( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG OpType;
    ULONG Flags;
    ULONG Dummy;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    PVARIABLE_ENTRY Var1;
    TCHAR *String;
    TCHAR *String1;
    TCHAR Buffer[256];

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        if ( TEST_OP1_CONST( OpLine ) )
        {
            make_printable_zval_url( OP1_VAL( OpLine ), &Stack->Buffer );
            RetCode = StackPopAllS( &Stack->Buffer, &String );
            OpType = DS_IFLAGS_OT_MAX;
        }
        else if ( TEST_OP1_ALL_VAR( OpLine ) )
        {
            Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                break;

            String = Var->Expr;
            RetCode = Var->ExprLength;
            OpType = Var->Flags & DS_IFLAGS_OT_MASK;
        }
        else
        {
            /* BUG */
            if ( GET_GS_FLAGS( ) & GS_FLAGS_BUG )
                dump_string_ex( Stack, _T( "//[BUG][%6d]QM_ASSIGN[Op1]\r\n" ), Stack->Offset );
            break;
        }

        if ( StackTopU( &Stack->QmAssign, &Flags ) )
        {
            StackPopU( &Stack->QmAssign, NULL );
            /* Condition ? r1 : r2 */
            if ( Flags & VE_FLAGS_QMASSIGN )
            {
                Var1 = FindInsertVariable( OPR_TYPE( OpLine ), OPR_VAR( OpLine ) );
                if ( Var1 == NULL )
                    break;

                StackPop( &Stack->Trinary, NULL, 0 );
                StackPushS( &Stack->Buffer1, Var1->Expr, Var1->ExprLength );
                if ( OpType < ( Stack->InternalFlags & DS_IFLAGS_OT_MASK ) )
                {
                    StackPushS( &Stack->Buffer1, _T( "( " ), 2 );
                    StackPushS( &Stack->Buffer1, String, RetCode );
                    StackPushS( &Stack->Buffer1, _T( " )" ), 2 );
                }
                else
                {
                    StackPushS( &Stack->Buffer1, String, RetCode );
                }
                RetCode = StackPopAllS( &Stack->Buffer1, &String );
            }
            else
            {
                StackPushU( &Stack->QmAssign, Flags | VE_FLAGS_QMASSIGN );
                StackTop( &Stack->Trinary, &String1 );
                Dummy = _tcslen( String1 );

                if ( ( Flags & VE_FLAGS_SILENCE_FUNCTION ) == VE_FLAGS_SILENCE_FUNCTION )
                    StackPushS( &Stack->Buffer1, DEFAULT_SILENCE_STRING, DEFAULT_SILENCE_STRING_LENGTH );

                if ( Flags & VE_FLAGS_JMPNZ )
                {
                    if ( StackTopS( &Stack->Buffer1, Buffer ) && Buffer[0] == _T( '!' ) )
                        StackPopS( &Stack->Buffer1, NULL );
                    else
                        StackPushS( &Stack->Buffer1, _T( "!" ), 1 );

                    if ( ( Flags & DS_IFLAGS_OT_MASK ) < DS_IFLAGS_OT_BOOL_NOT )
                        Flags &= ~DS_IFLAGS_OT_MASK;
                }

                if ( ( Flags & DS_IFLAGS_OT_MASK ) < ( Stack->InternalFlags & DS_IFLAGS_OT_MASK ) )
                {
                    StackPushS( &Stack->Buffer1, _T( "( " ), 2 );
                    StackPushS( &Stack->Buffer1, String1, Dummy );
                    StackPushS( &Stack->Buffer1, _T( " )" ), 2 );
                }
                else
                {
                    StackPushS( &Stack->Buffer1, String1, Dummy );
                }
                StackPushS( &Stack->Buffer1, _T( " ? " ), 3 );
                if ( OpType < ( Stack->InternalFlags & DS_IFLAGS_OT_MASK ) )
                {
                    StackPushS( &Stack->Buffer1, _T( "( " ), 2 );
                    StackPushS( &Stack->Buffer1, String, RetCode );
                    StackPushS( &Stack->Buffer1, _T( " )" ), 2 );
                }
                else
                {
                    StackPushS( &Stack->Buffer1, String, RetCode );
                }
                StackPushS( &Stack->Buffer1, _T( " : " ), 3 );
                RetCode = StackPopAllS( &Stack->Buffer1, &String );
            }
        }
        if ( TEST_OPR_ALL_VAR( OpLine ) )
            UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, Stack->InternalFlags & DS_IFLAGS_OT_MASK );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_echo( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG Dummy;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        if ( TEST_OP1_CONST( OpLine ) )
        {
            StackPushS( &Stack->Buffer, Stack->OpString, _tcslen( Stack->OpString ) );
            StackPushS( &Stack->Buffer, _T( " " ), 1 );
            make_printable_zval_url( OP1_VAL( OpLine ), &Stack->Buffer );
        }
        else if ( TEST_OP1_ALL_VAR( OpLine ) )
        {
            Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                break;

            StackPushS( &Stack->Buffer, Stack->OpString, _tcslen( Stack->OpString ) );
            StackPushS( &Stack->Buffer, _T( " " ), 1 );
            StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
        }
        else
        {
            break;
        }

        /* Prefix */
        if ( Stack->State & DS_STATE_SILENCE && OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushPrefixS( &Stack->Buffer, Stack->StartChar, Stack->StartCharLength );

        if ( GET_GS_STATE( ) & GS_STATE_EXTEND )
            Dummy = 1;
        else
            Dummy = ( OPR_TYPE( OpLine ) == IS_UNUSED || OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED );

        /* Postfix */
        if ( Dummy )
            StackPushS( &Stack->Buffer, Stack->EndChar, Stack->EndCharLength );

        RetCode = StackPopAllExS( &Stack->Buffer, &String );
        if ( Dummy )
            dump_string( Stack, String );
        else if ( TEST_OPR_ALL_VAR( OpLine ) )
            UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, Stack->InternalFlags & DS_IFLAGS_OT_MASK );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_print( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG Dummy;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        if ( TEST_OP1_CONST( OpLine ) )
        {
            StackPushS( &Stack->Buffer, Stack->OpString, _tcslen( Stack->OpString ) );
            StackPushS( &Stack->Buffer, _T( " " ), 1 );
            make_printable_zval_url( OP1_VAL( OpLine ), &Stack->Buffer );
        }
        else if ( TEST_OP1_ALL_VAR( OpLine ) )
        {
            Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                break;

            StackPushS( &Stack->Buffer, Stack->OpString, _tcslen( Stack->OpString ) );
            StackPushS( &Stack->Buffer, _T( " " ), 1 );
            StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
        }

        /* Prefix */
        if ( Stack->State & DS_STATE_SILENCE && OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushPrefixS( &Stack->Buffer, Stack->StartChar, Stack->StartCharLength );

        if ( GET_GS_STATE( ) & GS_STATE_EXTEND )
            Dummy = !TEST_OPR_ALL_VAR( OpLine );
        else
            Dummy = ( OPR_TYPE( OpLine ) == IS_UNUSED || OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED );

        /* Postfix */
        if ( Dummy )
            StackPushS( &Stack->Buffer, Stack->EndChar, Stack->EndCharLength );

        RetCode = StackPopAllExS( &Stack->Buffer, &String );
        if ( Dummy )
            dump_string( Stack, String );
        else if ( TEST_OPR_ALL_VAR( OpLine ) )
            UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, Stack->InternalFlags & DS_IFLAGS_OT_MASK );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_jmpx( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG Offset;
    ULONG Flags;
    ULONG Dummy;
    zend_op *Head;
    zend_op *OpLine;
    zend_op *OpLine1;
    PVARIABLE_ENTRY Var;
    PLOGIC_LIST LogicPtr;
    PLOGIC_PREFIX_LIST LogicPrefixPtr;
    const TCHAR *OpString;
    TCHAR Buffer[256];

    RetCode = 0;
    Head = Stack->Head;
    OpLine = Stack->OpLine;
    Offset = Stack->Offset;
    do
    {
        Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
        if ( Var == NULL )
            break;

        if ( Stack->LogicEndOffset == INVALID_OP_OFFSET )
        {
            while ( StackBottomT( &Stack->Logic, &LogicPtr ) && LogicPtr->End < Offset )
                StackPopBottomT( &Stack->Logic, NULL );

            if ( StackBottomT( &Stack->Logic, &LogicPtr ) )
            {
                StackPopBottomT( &Stack->Logic, NULL );
                Stack->LogicEndOffset = LogicPtr->End;
            }
            else
            {
                Stack->LogicEndOffset = INVALID_OP_OFFSET;
                break;
            }

            OpLine1 = Head + Stack->LogicEndOffset;
            Stack->LogicEndJmp = OP_JMPX( OpLine1, Head );
            Stack->LogicEndType = OP_CODE( OpLine1 );
            Stack->LogicOpType = DS_IFLAGS_OT_MAX;

            if ( Stack->LogicEndJmp > Offset )
            {
                if ( GetBreak( Stack, Stack->LogicEndJmp, Offset ) )
                    Stack->LogicOpType |= DS_IFLAGS_BRK;
            }
            else
            {
                if ( GetContinue( Stack, Stack->LogicEndJmp, Offset ) )
                    Stack->LogicOpType |= DS_IFLAGS_CONT;
                else
                    Stack->LogicOpType |= DS_IFLAGS_LOOP;
            }

            LogicPtr->Flags = scan_logic_order_stub( Stack, Offset, Stack->LogicEndOffset );

            if ( Stack->LogicEndOffset == Offset )
            {
                /* JmpX in cond express */
                if ( is_special_jump( OP_JMPX( OpLine, Head ) - 1, Head ) )
                {
                    /* Condition ? r1 : r2 */
                    Flags = Var->Flags;
                    if ( OP_CODE( OpLine ) == ZEND_JMPZ )
                        Flags |= VE_FLAGS_JMPZ;
                    else
                        Flags |= VE_FLAGS_JMPNZ;
                    StackPushU( &Stack->QmAssign, Flags );
                    StackPush( &Stack->Trinary, Var->Expr, Var->ExprLength + 1 );
                }
                Stack->LogicEndOffset = INVALID_OP_OFFSET;
                Stack->LogicEndJmp = INVALID_OP_OFFSET;
                break;
            }
        }

        if ( ( Var->Flags & VE_FLAGS_SILENCE_FUNCTION ) == VE_FLAGS_SILENCE_FUNCTION )
            StackPushS( &Stack->LogicExpress, DEFAULT_SILENCE_STRING, DEFAULT_SILENCE_STRING_LENGTH );

        while ( StackBottomT( &Stack->LogicPrefix, &LogicPrefixPtr ) && LogicPrefixPtr->Offset <= Offset )
        {
            StackPopBottomT( &Stack->LogicPrefix, NULL );
            if ( LogicPrefixPtr->Flags & DS_IFLAGS_BOOL_NOT )
            {
                if ( StackTopS( &Stack->LogicExpress, Buffer ) && Buffer[0] == _T( '!' ) )
                    StackPopS( &Stack->LogicExpress, NULL );
                else
                    StackPushS( &Stack->LogicExpress, _T( "!" ), 1 );
            }
            else
            {
                StackPushS( &Stack->LogicExpress, _T( "( " ), 2 );
            }
        }

        while ( StackBottomU( &Stack->LogicOpReverse, &Dummy ) && Dummy <= Offset )
        {
            StackPopBottomU( &Stack->LogicOpReverse, NULL );
            if ( OP_CODE( OpLine ) == ZEND_JMPZ )
                OpString = GET_OP_STRING_EX( OT_BOOL_OR );
            else
                OpString = GET_OP_STRING_EX( OT_BOOL_AND );
        }

        StackPushS( &Stack->LogicExpress, Var->Expr, Var->ExprLength );

        while ( StackBottomU( &Stack->LogicPostfix, &Dummy ) && Dummy <= Offset )
        {
            StackPopBottomU( &Stack->LogicPostfix, NULL );
            StackPushS( &Stack->LogicExpress, _T( " )" ), 2 );
        }
        StackPushS( &Stack->LogicExpress, Stack->OpString, _tcslen( Stack->OpString ) );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_jmpx_ex( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG OpType;
    ULONG Dummy;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    PVARIABLE_ENTRY Var1;
    const TCHAR *OpString;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
        if ( Var == NULL )
            break;

        Var1 = FindInsertVariable( OPR_TYPE( OpLine ), OPR_VAR( OpLine ) );
        if ( Var1 == NULL )
            break;

        if ( Var1->Flags & ( VE_FLAGS_JMPZ_EX | VE_FLAGS_JMPNZ_EX ) )
        {
            if ( Var1->Flags & VE_FLAGS_JMPZ_EX )
            {
                OpType = DS_IFLAGS_OT_BOOL_AND;
                OpString = GET_OP_STRING_EX( OT_BOOL_AND );
                Dummy = sizeof( " && " ) - 1;
            }
            else
            {
                OpType = DS_IFLAGS_OT_BOOL_OR;
                OpString = GET_OP_STRING_EX( OT_BOOL_OR );
                Dummy = sizeof( " || " ) - 1;
            }

            if ( ( Var1->Flags & DS_IFLAGS_OT_MASK ) < OpType )
            {
                StackPushS( &Stack->Buffer, _T( "( " ), 2 );
                StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
                StackPushS( &Stack->Buffer, _T( " )" ), 2 );
            }
            else
            {
                StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
            }

            StackPushS( &Stack->Buffer, OpString, Dummy );

            if ( ( Var->Flags & DS_IFLAGS_OT_MASK ) <= OpType )
            {
                StackPushS( &Stack->Buffer, _T( "( " ), 2 );
                StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
                StackPushS( &Stack->Buffer, _T( " )" ), 2 );
            }
            else
            {
                StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
            }
            RetCode= StackPopAllS( &Stack->Buffer, &String );
        }
        else
        {
            String = Var->Expr;
            RetCode = Var->ExprLength;
            OpType = Var->Flags & VE_FLAGS_MASK;
        }

        if ( OP_CODE( OpLine ) == ZEND_JMPZ_EX )
            OpType |= VE_FLAGS_JMPZ_EX;
        else
            OpType |= VE_FLAGS_JMPNZ_EX;

        if ( TEST_OPR_ALL_VAR( OpLine ) )
            UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, OpType );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_switch_free( PDUMP_STACK Stack )
{
    UNREFERENCED_PARAMETER( Stack );
    return 0;
}

ULONG FASTCALL dump_brk( PDUMP_STACK Stack )
{
    dump_string_ex( Stack, _T( "%s;\r\n" ), Stack->OpString );
    return 0;
}

ULONG FASTCALL dump_cont( PDUMP_STACK Stack )
{
    dump_string_ex( Stack, _T( "%s;\r\n" ), Stack->OpString );
    return 0;
}

ULONG FASTCALL dump_bool( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG OpType;
    ULONG Dummy;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    PVARIABLE_ENTRY Var1;
    const TCHAR *OpString;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        if ( TEST_OP1_CONST( OpLine ) )
        {
            make_printable_zval_url( OP1_VAL( OpLine ), &Stack->Buffer );
            RetCode = StackPopAllS( &Stack->Buffer, &String );
            OpType = DS_IFLAGS_OT_MAX;
        }
        else
        {
            Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                break;

            Var1 = FindInsertVariable( OPR_TYPE( OpLine ), OPR_VAR( OpLine ) );
            if ( Var1 == NULL )
                break;

            if ( Var1->Flags & ( VE_FLAGS_JMPZ_EX | VE_FLAGS_JMPNZ_EX ) )
            {
                if ( Var1->Flags & VE_FLAGS_JMPZ_EX )
                {
                    OpType = DS_IFLAGS_OT_BOOL_AND;
                    OpString = GET_OP_STRING_EX( OT_BOOL_AND );
                    Dummy = sizeof( " && " ) - 1;
                }
                else
                {
                    OpType = DS_IFLAGS_OT_BOOL_OR;
                    OpString = GET_OP_STRING_EX( OT_BOOL_OR );
                    Dummy = sizeof( " || " ) - 1;
                }

                if ( ( Var1->Flags & VE_FLAGS_SILENCE_FUNCTION ) == VE_FLAGS_SILENCE_FUNCTION )
                    StackPushS( &Stack->Buffer, DEFAULT_SILENCE_STRING, DEFAULT_SILENCE_STRING_LENGTH );

                if ( ( Var1->Flags & DS_IFLAGS_OT_MASK ) < OpType )
                {
                    StackPushS( &Stack->Buffer, _T( "( " ), 2 );
                    StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
                    StackPushS( &Stack->Buffer, _T( " )" ), 2 );
                }
                else
                {
                    StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
                }

                StackPushS( &Stack->Buffer, OpString, Dummy );

                if ( ( Var->Flags & VE_FLAGS_SILENCE_FUNCTION ) == VE_FLAGS_SILENCE_FUNCTION )
                    StackPushS( &Stack->Buffer, DEFAULT_SILENCE_STRING, DEFAULT_SILENCE_STRING_LENGTH );

                if ( ( Var->Flags & DS_IFLAGS_OT_MASK ) <= OpType )
                {
                    StackPushS( &Stack->Buffer, _T( "( " ), 2 );
                    StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
                    StackPushS( &Stack->Buffer, _T( " )" ), 2 );
                }
                else
                {
                    StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
                }
                RetCode= StackPopAllS( &Stack->Buffer, &String );
                OpType |= ( Var->Flags & VE_FLAGS_EXPRESS_MASK ) | VE_FLAGS_SKIP_SILENCE;
            }
            else
            {
                String = Var->Expr;
                RetCode = Var->ExprLength;
                OpType = ( Var->Flags & VE_FLAGS_EXPRESS_MASK );
            }
        }

        if ( TEST_OPR_ALL_VAR( OpLine ) )
            UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, OpType );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_init_string( PDUMP_STACK Stack )
{
    UpdateVariableEx( OPR_TYPE( Stack->OpLine ), OPR_VAR( Stack->OpLine ), Stack->Offset, NULL, _T( "\"\"" ), 0 );
    return 0;
}

ULONG FASTCALL dump_add_char( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG Dummy;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    TCHAR *String;
    TCHAR Buffer[256];

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
        if ( Var == NULL )
            break;

        StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
        StackTopS( &Stack->Buffer, Buffer );
        if ( Buffer[0] != _T( '\"' ) )
            StackPushS( &Stack->Buffer, _T( ".\"" ), 2 );
        else
            StackPopS( &Stack->Buffer, NULL );

        Dummy = StackCountS( &Stack->Buffer );
        StackSetMaxS( &Stack->Buffer, Dummy + 4 );
        Dummy += parse_string( StackBaseS( &Stack->Buffer ) + Dummy, ( const TCHAR* )&OP2_VAL( OpLine )->value.lval, 1 );
        StackSetTopS( &Stack->Buffer, Dummy );
        StackPushS( &Stack->Buffer, _T( "\"" ), 1 );
        RetCode = StackPopAllS( &Stack->Buffer, &String );
        UpdateVariable( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), String );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_add_string( PDUMP_STACK Stack )
{
    ULONG RetCode;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    TCHAR *String;
    TCHAR Buffer[256];

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
        if ( Var == NULL )
            break;

        StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
        StackTopS( &Stack->Buffer, Buffer );
        if ( Buffer[0] != _T( '\"' ) )
            StackPushS( &Stack->Buffer, _T( ".\"" ), 2 );
        else
            StackPopS( &Stack->Buffer, NULL );

        make_printable_zval_url_ex( OP2_VAL( OpLine ), &Stack->Buffer, 0 );
        StackPushS( &Stack->Buffer, _T( "\"" ), 1 );
        RetCode = StackPopAllS( &Stack->Buffer, &String );
        UpdateVariable( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), String );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_add_var( PDUMP_STACK Stack )
{
    ULONG RetCode;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    PVARIABLE_ENTRY Var1;
    TCHAR *String;
    TCHAR Buffer[256];

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
        if ( Var == NULL )
            break;

        Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
        if ( Var1 == NULL )
            break;

        StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );

        /* "{$var['string']}" */
        StackPopS( &Stack->Buffer, Buffer );
        if ( Buffer[0] != _T( '\"' ) )
            StackPushS( &Stack->Buffer, _T( ".\"{" ), 3 );
        else
            StackPushS( &Stack->Buffer, _T( "{" ), 1 );
        StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
        StackPushS( &Stack->Buffer, _T( "}\"" ), 2 );

        RetCode = StackPopAllS( &Stack->Buffer, &String );
        UpdateVariable( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), String );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_begin_silence( PDUMP_STACK Stack )
{
    Stack->SilenceCount++;
    Stack->State |= DS_STATE_SILENCE;
    Stack->StartChar[0] = DEFAULT_SILENCE_CHAR;
    Stack->StartCharLength = 1;

    return 0;
}

ULONG FASTCALL dump_end_silence( PDUMP_STACK Stack )
{
    Stack->SilenceCount--;
    if ( Stack->SilenceCount <= 0 )
    {
        Stack->State &= ~DS_STATE_SILENCE;
        Stack->StartChar[0] = _T( '\0' );
        Stack->StartCharLength = 0;
    }

    return 0;
}

ULONG FASTCALL dump_init_fcall_by_name( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG RVar;
    zend_op *Head;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    PVARIABLE_ENTRY Var1;
    TCHAR *String;

    RetCode = 0;
    Head = Stack->Head;
    OpLine = Stack->OpLine;
    RVar = OPR_VAR( OpLine );
    do
    {
        StackPushU( &Stack->InitCall, Stack->Offset );
        if ( TEST_OP1_CONST( OpLine ) )
        {
            decode_obfuscate_class_name( &Stack->Buffer, OP1_VAL( OpLine )->value.str.val, OP1_VAL( OpLine )->value.str.len );
            StackPushS( &Stack->Buffer, _T( "::" ), 2 );
            if ( TEST_OP2_CONST( OpLine ) )
            {
                /* Used for $var->string */
                decode_obfuscate_function_name( &Stack->Buffer, OP2_VAL( OpLine )->value.str.val, OP2_VAL( OpLine )->value.str.len );
            }
            else if ( TEST_OP2_ALL_VAR( OpLine ) )
            {
                /* Used for $var->$var1 */
                Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
                if ( Var1 == NULL )
                    break;

                StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
            }
            else
            {
                /* BUG */
                break;
            }
        }
        else if ( TEST_OP1_ALL_VAR( OpLine ) )
        {
            Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                break;

            if ( OpLine < Head || OP_CODE( OpLine - 1 ) != ZEND_JMP_NO_CTOR )
            {
                /* Used for $var->function */
                StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
                StackPushS( &Stack->Buffer, _T( "->" ), 2 );
            }

            if ( TEST_OP2_CONST( OpLine ) )
            {
                /* Used for $var->function */
                decode_obfuscate_function_name( &Stack->Buffer, OP2_VAL( OpLine )->value.str.val, OP2_VAL( OpLine )->value.str.len );
            }
            else if ( TEST_OP2_ALL_VAR( OpLine ) )
            {
                /* Used for $var->$var1 */
                Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
                if ( Var1 == NULL )
                    break;

                StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
            }
            else
            {
                /* BUG */
                break;
            }
        }
        else
        {
            /* Used for $var */
            if ( TEST_OP2_CONST( OpLine ) )
            {
                /* Used for $var->function */
                decode_obfuscate_function_name( &Stack->Buffer, OP2_VAL( OpLine )->value.str.val, OP2_VAL( OpLine )->value.str.len );
            }
            else if ( TEST_OP2_ALL_VAR( OpLine ) )
            {
                Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
                if ( Var1 == NULL )
                    break;

                StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
            }
            else
            {
                /* BUG */
                break;
            }
        }

        RetCode = StackPopAllS( &Stack->Buffer, &String );
        if ( OPR_TYPE( OpLine ) == IS_UNUSED )
            UpdateVariableEx( OPR_TYPE( OpLine ), RVar, Stack->Offset, NULL, String, Stack->InternalFlags & DS_IFLAGS_OT_MASK );
        UpdateVariableEx( OPR_TYPE( OpLine ), Stack->Offset | IS_SPECIFIC_ID, Stack->Offset, NULL, String, Stack->InternalFlags & DS_IFLAGS_OT_MASK );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_do_fcall( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG OpType;
    zend_op *OpLine;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        if ( !TEST_OP1_CONST( OpLine ) )
            break;

        /* Op type */
        OpType = ( Stack->InternalFlags & DS_IFLAGS_OT_MASK ) | VE_FLAGS_FUNCTION;

        /* Prefix */
        if ( Stack->State & DS_STATE_SILENCE && OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushS( &Stack->Buffer, Stack->StartChar, Stack->StartCharLength );

        /* Function name */
        decode_obfuscate_function_name( &Stack->Buffer, OP1_VAL( OpLine )->value.str.val, OP1_VAL( OpLine )->value.str.len );

        /* Pop argument list */
        PopArgumentList( Stack, OP_EX_VALUE( OpLine ) );

        /* Postfix */
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushS( &Stack->Buffer, Stack->EndChar, Stack->EndCharLength );

        RetCode = StackPopAllS( &Stack->Buffer, &String );
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            dump_string( Stack, String );
        else if ( TEST_OPR_ALL_VAR( OpLine ) )
            UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, OpType );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_do_fcall_by_name( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG NextOffset;
    ULONG OpType;
    ULONG Dummy;
    zend_op *Head;
    zend_op *OpLine;
    zend_op *OpLine1;
    zend_op *OpLine2;
    zend_op LocalOpLine;
    PVARIABLE_ENTRY Var;
    TCHAR *String;

    RetCode = 0;
    Head = Stack->Head;
    OpLine = Stack->OpLine;
    do
    {
        if ( StackPopU( &Stack->InitCall, &NextOffset ) )
        {
            OpLine1 = Head + NextOffset;
            Dummy = NextOffset | IS_SPECIFIC_ID;
            switch ( OP_CODE( OpLine1 ) )
            {
            case ZEND_INIT_FCALL_BY_NAME :
                Var = FindInsertVariable( OPR_TYPE( OpLine1 ), Dummy );
                if ( Var == NULL )
                    break;

                StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
                break;
            case ZEND_INIT_METHOD_CALL :
                Var = FindInsertVariable( OPR_TYPE( OpLine1 ), Dummy );
                if ( Var == NULL )
                    break;

                StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
                break;
            case ZEND_INIT_STATIC_METHOD_CALL :
                Var = FindInsertVariable( OPR_TYPE( OpLine1 ), Dummy );
                if ( Var == NULL )
                    break;

                StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
                break;
            case ZEND_USER_OPCODE :
                /* Used for function */
                Var = FindVariableById( IS_FUNCTION, OP1_VAR( OpLine1 ) );
                if ( Var == NULL )
                    break;

                StackPushS( &Stack->Buffer, Var->Name, Var->NameLength );
                break;
            case ZEND_NEW :
                Var = FindInsertVariable( OP1_TYPE( OpLine1 ), OP1_VAR( OpLine1 ) );
                if ( Var == NULL )
                    break;

                /* new class_name */
                StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
                StackPushPrefixS( &Stack->Buffer, _T( "new " ), 4 );
                LocalOpLine = *OpLine;
                OPR_EA_TYPE( &LocalOpLine ) = OPR_EA_TYPE( OpLine1 );
                OPR_TYPE( &LocalOpLine ) = OPR_TYPE( OpLine1 );
                SET_OPR_VAR_EX( &LocalOpLine, OPR_VAR_EX( OpLine1 ) );
                OpLine = &LocalOpLine;
                break;
            case ZEND_INIT_CTOR_CALL :
                decode_obfuscate_function_name( &Stack->Buffer, OP1_VAL( OpLine )->value.str.val, OP1_VAL( OpLine )->value.str.len );
                break;
            default :
                /* Used for $var->function */
                if ( TEST_OP1_CONST( OpLine ) )
                {
                    /* Used for $var->string */
                    decode_obfuscate_function_name( &Stack->Buffer, OP1_VAL( OpLine )->value.str.val, OP1_VAL( OpLine )->value.str.len );
                }
                else if ( TEST_OP1_ALL_VAR( OpLine ) )
                {
                    /* Used for $var->$var1 */
                    Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
                    if ( Var == NULL )
                        break;

                    StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
                }
                break;
            }
        }
        else
        {
            /* V4.0.1 */

            /* Used for $var->function */
            if ( TEST_OP1_CONST( OpLine ) )
            {
                /* Used for $var->string */
                decode_obfuscate_function_name( &Stack->Buffer, OP1_VAL( OpLine )->value.str.val, OP1_VAL( OpLine )->value.str.len );
            }
            else if ( TEST_OP1_ALL_VAR( OpLine ) )
            {
                /* Used for $var->$var1 */
                Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
                if ( Var == NULL )
                    break;

                StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
            }
        }

        if ( GET_GS( )->ExtensionId < EXTENSION_ID_2 )
        {
            if ( StackTopU( &Stack->New, &Dummy ) )
            {
                OpLine1 = Head + Dummy;
                OpLine2 = OpLine1 + 1;
                if ( OP_CODE( OpLine2 ) == ZEND_JMP_NO_CTOR && OP_JMPX( OpLine2, Head ) == Stack->Offset + 1 )
                {
                    StackPopU( &Stack->New, NULL );

                    /* new class_name */
                    StackPushPrefixS( &Stack->Buffer, _T( "new " ), 4 );
                    if ( OPR_VAR( OpLine1 ) == OPR_VAR( OpLine ) && OPR_TYPE( OpLine1 ) == OPR_TYPE( OpLine ) )
                    {
                        LocalOpLine = *OpLine;
                        OPR_EA_TYPE( &LocalOpLine ) |= EXT_TYPE_UNUSED;
                        OpLine = &LocalOpLine;
                    }
                    else
                    {
                        LocalOpLine = *OpLine;
                        OPR_EA_TYPE( &LocalOpLine ) = OPR_EA_TYPE( OpLine1 ) & EXT_TYPE_UNUSED;
                        OPR_TYPE( &LocalOpLine ) = OPR_TYPE( OpLine1 );
                        SET_OPR_VAR_EX( &LocalOpLine, OPR_VAR_EX( OpLine1 ) );
                        OpLine = &LocalOpLine;
                    }
                }
            }
        }

        /* Op type */
        OpType = ( Stack->InternalFlags & DS_IFLAGS_OT_MASK ) | VE_FLAGS_FUNCTION;

        /* Prefix */
        if ( Stack->State & DS_STATE_SILENCE && OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushPrefixS( &Stack->Buffer, Stack->StartChar, Stack->StartCharLength );

        /* Pop argument list */
        PopArgumentList( Stack, OP_EX_VALUE( OpLine ) );

        /* Postfix */
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushS( &Stack->Buffer, Stack->EndChar, Stack->EndCharLength );

        RetCode = StackPopAllExS( &Stack->Buffer, &String );
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            dump_string( Stack, String );
        else if ( TEST_OPR_ALL_VAR( OpLine ) )
            UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, OpType );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_return( PDUMP_STACK Stack )
{
    ULONG RetCode;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        if ( TEST_OP1_CONST( OpLine ) )
        {
            StackPushS( &Stack->Buffer, Stack->StartChar, Stack->StartCharLength );
            StackPushS( &Stack->Buffer, Stack->OpString, _tcslen( Stack->OpString ) );
            if ( OP1_VAL_TYPE( OpLine ) != IS_NULL )
            {
                StackPushS( &Stack->Buffer, _T( " " ), 1 );
                make_printable_zval_url( OP1_VAL( OpLine ), &Stack->Buffer );
            }
            StackPushS( &Stack->Buffer, Stack->EndChar, Stack->EndCharLength );
            RetCode = StackPopAllS( &Stack->Buffer, &String );
            dump_string( Stack, String );
        }
        else if ( TEST_OP1_ALL_VAR( OpLine ) )
        {
            Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                break;

            StackPushS( &Stack->Buffer, Stack->StartChar, Stack->StartCharLength );
            StackPushS( &Stack->Buffer, Stack->OpString, _tcslen( Stack->OpString ) );
            StackPushS( &Stack->Buffer, _T( " " ), 1 );
            StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
            StackPushS( &Stack->Buffer, Stack->EndChar, Stack->EndCharLength );
            RetCode = StackPopAllS( &Stack->Buffer, &String );
            dump_string( Stack, String );
        }
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_recv( PDUMP_STACK Stack )
{
    ULONG RetCode;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        Var = FindInsertVariable( OPR_TYPE( OpLine ), OPR_VAR( OpLine ) );
        if ( Var == NULL )
            break;

        if ( GET_GS( )->ExtensionId < EXTENSION_ID_2 )
        {
            if ( Stack->ArgInfo && ( ( UCHAR* )Stack->ArgInfo )[OP1_VAL( OpLine )->value.lval - 1] != BYREF_NONE )
            StackPushS( &Stack->ArgumentString, _T( "&" ), 1 );
        }
        else
        {
            if ( Stack->ArgInfo && ( ( zend_arg_info_2* )Stack->ArgInfo )[OP1_VAL( OpLine )->value.lval - 1].pass_by_reference )
                StackPushS( &Stack->ArgumentString, _T( "&" ), 1 );
        }

        StackPushS( &Stack->ArgumentString, Var->Expr, Var->ExprLength );
        if ( Stack->ArgumentCount == OP1_VAL( OpLine )->value.lval )
        {
            StackPushS( &Stack->ArgumentString, _T( " )\r\n" ), 4 );
            StackPopAllS( &Stack->ArgumentString, &String );
            dump_string_no_indent( String );
            dump_string( Stack, _T( "{\r\n" ) );
            PUSH_INC_INDENT( Stack );
        }
        else
        {
            StackPushS( &Stack->ArgumentString, _T( ", " ), 2 );
        }
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_recv_init( PDUMP_STACK Stack )
{
    ULONG RetCode;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        Var = FindInsertVariable( OPR_TYPE( OpLine ), OPR_VAR( OpLine ) );
        if ( Var == NULL )
            break;

        StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
        StackPushS( &Stack->Buffer, _T( " = " ), 3 );
        make_printable_zval_url( OP2_VAL( OpLine ), &Stack->Buffer );
        RetCode = StackPopAllS( &Stack->Buffer, &String );

        if ( Stack->ArgumentCount == OP1_VAL( OpLine )->value.lval )
        {
            StackPushS( &Stack->ArgumentString, String, RetCode );
            StackPushS( &Stack->ArgumentString, _T( " )\r\n" ), 4 );
            StackPopAllS( &Stack->ArgumentString, &String );
            dump_string_no_indent( String );
            dump_string( Stack, _T( "{\r\n" ) );
            PUSH_INC_INDENT( Stack );
        }
        else
        {
            StackPushS( &Stack->ArgumentString, String, RetCode );
            StackPushS( &Stack->ArgumentString, _T( ", " ), 2 );
        }
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_send_x( PDUMP_STACK Stack )
{
    ULONG RetCode;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        if ( TEST_OP1_CONST( OpLine ) )
        {
            if ( OP_CODE( OpLine ) == ZEND_SEND_REF )
                StackPushS( &Stack->Buffer, _T( "&" ), 1 );
            make_printable_zval_url( OP1_VAL( OpLine ), &Stack->Buffer );
            RetCode = StackPopAllS( &Stack->Buffer, &String );
            StackPush( &Stack->ArgumentList, String, RetCode + 1 );
        }
        else if ( TEST_OP1_ALL_VAR( OpLine ) )
        {
            Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                break;

            if ( ( Var->Flags & VE_FLAGS_SILENCE_FUNCTION ) == VE_FLAGS_SILENCE_FUNCTION )
                StackPushS( &Stack->Buffer, DEFAULT_SILENCE_STRING, DEFAULT_SILENCE_STRING_LENGTH );

            if ( OP_CODE( OpLine ) == ZEND_SEND_REF )
                StackPushS( &Stack->Buffer, _T( "&" ), 1 );

            StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
            RetCode = StackPopAllS( &Stack->Buffer, &String );
            StackPush( &Stack->ArgumentList, String, RetCode + 1 );
        }
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_new( PDUMP_STACK Stack )
{
    if ( GET_GS( )->ExtensionId < EXTENSION_ID_2 )
        StackPushU( &Stack->New, Stack->Offset );
    else
        StackPushU( &Stack->InitCall, Stack->Offset );

    return 0;
}

ULONG FASTCALL dump_free( PDUMP_STACK Stack )
{
    ULONG RetCode;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        Var = FindVariableById( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
        if ( Var == NULL )
            break;

        /* Prefix */
        if ( ( Var->Flags & VE_FLAGS_SILENCE_FUNCTION ) == VE_FLAGS_SILENCE_FUNCTION )
        {
            StackPushS( &Stack->Buffer, DEFAULT_SILENCE_STRING, DEFAULT_SILENCE_STRING_LENGTH );
            if ( ( Var->Flags & DS_IFLAGS_OT_MASK ) < DS_IFLAGS_OT_MAX )
            {
                StackPushS( &Stack->Buffer, _T( "( " ), 2 );
                StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
                StackPushS( &Stack->Buffer, _T( " )" ), 2 );
            }
            else
            {
                StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
            }
        }
        else
        {
            StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
        }

        /* Clean flags */
        Var->Flags &= ~VE_FLAGS_MASK;
        Var->Flags |= VE_FLAGS_FREE;

        /* Postfix */
        StackPushS( &Stack->Buffer, Stack->EndChar, Stack->EndCharLength );

        RetCode = StackPopAllS( &Stack->Buffer, &String );
        dump_string( Stack, String );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_init_array( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG OpType;
    ULONG Dummy;
    zend_op *Tail;
    zend_op *OpLine;
    zend_op *OpLine1;
    PVARIABLE_ENTRY Var;
    PVARIABLE_ENTRY Var1;
    TCHAR *String;
    TCHAR *String1;
    TCHAR *String2;
    TCHAR Buffer[256];

    RetCode = 0;
    Tail = Stack->Tail;
    OpLine = Stack->OpLine;
    do
    {
        OpType = 0;
        OpLine1 = OpLine;
        while ( OpLine1 < Tail )
        {
            if ( OP_CODE( OpLine1 ) == ZEND_ADD_ARRAY_ELEMENT || OP_CODE( OpLine1 ) == ZEND_INIT_ARRAY )
            {
                if ( OPR_VAR( OpLine1 ) == OPR_VAR( OpLine ) && TEST_OP1_ALL_VAR( OpLine1 ) )
                {
                    OpType |= VE_FLAGS_MUTIARRAY;
                    break;
                }
                else if ( TEST_OP1_ALL_VAR( OpLine1 ) && OP1_VAR( OpLine1 ) == OPR_VAR( OpLine ) )
                {
                    break;
                }
            }
            else if ( OPR_EA_TYPE( OpLine1 ) & EXT_TYPE_UNUSED && !is_special_opcode( OP_CODE( OpLine1 ) ) )
            {
                break;
            }
            OpLine1++;
        }

        if ( OpType )
        {
            GET_INDENT( Stack, &Dummy );
            Dummy += GET_GS_INDENT( );

            memcpy( Buffer, _T( "array(\r\n)" ), sizeof( _T( "array(\r\n)" ) ) );
            String = Buffer;

            if ( TEST_OP1_CONST( OpLine ) )
            {
                if ( TEST_OP2_CONST( OpLine ) )
                    AddArrayElementIndent( &Stack->Buffer, String, Stack->OpString, OP2_VAL( OpLine ), OP1_VAL( OpLine ), Dummy );
                else
                    AddArrayElementIndent( &Stack->Buffer, String, NULL, NULL, OP1_VAL( OpLine ), Dummy );
            }
            else if ( TEST_OP1_ALL_VAR( OpLine ) )
            {
                Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
                if ( Var == NULL )
                    break;

                AddArrayIndent( &Stack->Buffer1, Var->Expr, Var->ExprLength, Dummy );
                StackPopAllS( &Stack->Buffer1, &String1 );
                if ( TEST_OP2_CONST( OpLine ) )
                {
                    make_printable_zval_url( OP2_VAL( OpLine ), &Stack->Buffer2 );
                    StackPopAllS( &Stack->Buffer2, &String2 );
                    AddArrayElementIndentEx( &Stack->Buffer, String, Stack->OpString, String2, String1, Dummy );
                }
                else if ( TEST_OP2_ALL_VAR( OpLine ) )
                {
                    Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
                    if ( Var1 == NULL )
                        break;

                    AddArrayIndent( &Stack->Buffer2, Var1->Expr, Var1->ExprLength, Dummy );
                    StackPopAllS( &Stack->Buffer2, &String2 );
                    AddArrayElementIndentEx( &Stack->Buffer, String, Stack->OpString, String2, String1, Dummy );
                }
                else
                {
                    AddArrayElementIndentEx( &Stack->Buffer, String, NULL, NULL, String1, Dummy );
                }
            }
            else
            {
                StackPushS( &Stack->Buffer, _T( "array( )" ), SIZE_OF_ARRAY( _T( "array( )" ) ) - 1 );
            }
        }
        else
        {
            memcpy( Buffer, _T( "array( )" ), sizeof( _T( "array( )" ) ) );
            String = Buffer;

            if ( TEST_OP1_CONST( OpLine ) )
            {
                if ( TEST_OP2_CONST( OpLine ) )
                    AddArrayElement( &Stack->Buffer, String, Stack->OpString, OP2_VAL( OpLine ), OP1_VAL( OpLine ) );
                else
                    AddArrayElement( &Stack->Buffer, String, NULL, NULL, OP1_VAL( OpLine ) );
            }
            else if ( TEST_OP1_ALL_VAR( OpLine ) )
            {
                Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
                if ( Var == NULL )
                    break;

                String1 = Var->Expr;
                if ( TEST_OP2_CONST( OpLine ) )
                {
                    make_printable_zval_url( OP2_VAL( OpLine ), &Stack->Buffer2 );
                    StackPopAllS( &Stack->Buffer2, &String2 );
                    AddArrayElementEx( &Stack->Buffer, String, Stack->OpString, String2, String1 );
                }
                else if ( TEST_OP2_ALL_VAR( OpLine ) )
                {
                    Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
                    if ( Var1 == NULL )
                        break;

                    String2 = Var1->Expr;
                    AddArrayElementEx( &Stack->Buffer, String, Stack->OpString, String2, String1 );
                }
                else
                {
                    AddArrayElementEx( &Stack->Buffer, String, NULL, NULL, String1 );
                }
            }
            else
            {
                StackPushS( &Stack->Buffer, _T( "array( )" ), SIZE_OF_ARRAY( _T( "array( )" ) ) - 1 );
            }
        }
        RetCode = StackPopAllS( &Stack->Buffer, &String );
        UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, OpType );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_add_element( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG OpType;
    ULONG Dummy;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    PVARIABLE_ENTRY Var1;
    PVARIABLE_ENTRY Var2;
    TCHAR *String;
    TCHAR *String1;
    TCHAR *String2;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        Var2 = FindVariableById( OPR_TYPE( OpLine ), OPR_VAR( OpLine ) );
        if ( Var2 == NULL )
            break;

        String = Var2->Expr;
        OpType = Var2->Flags & VE_FLAGS_MUTIARRAY;
        if ( OpType )
        {
            GET_INDENT( Stack, &Dummy );
            Dummy += GET_GS_INDENT( );
            if ( TEST_OP1_CONST( OpLine ) )
            {
                if ( TEST_OP2_CONST( OpLine ) )
                    AddArrayElementIndent( &Stack->Buffer, String, Stack->OpString, OP2_VAL( OpLine ), OP1_VAL( OpLine ), Dummy );
                else
                    AddArrayElementIndent( &Stack->Buffer, String, NULL, NULL, OP1_VAL( OpLine ), Dummy );
            }
            else if ( TEST_OP1_ALL_VAR( OpLine ) )
            {
                Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
                if ( Var == NULL )
                    break;

                AddArrayIndent( &Stack->Buffer1, Var->Expr, Var->ExprLength, Dummy );
                StackPopAllS( &Stack->Buffer1, &String1 );
                if ( TEST_OP2_CONST( OpLine ) )
                {
                    make_printable_zval_url( OP2_VAL( OpLine ), &Stack->Buffer2 );
                    StackPopAllS( &Stack->Buffer2, &String2 );
                    AddArrayElementIndentEx( &Stack->Buffer, String, Stack->OpString, String2, String1, Dummy );
                }
                else if ( TEST_OP2_ALL_VAR( OpLine ) )
                {
                    Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
                    if ( Var1 == NULL )
                        break;

                    AddArrayIndent( &Stack->Buffer2, Var1->Expr, Var1->ExprLength, Dummy );
                    StackPopAllS( &Stack->Buffer2, &String2 );
                    AddArrayElementIndentEx( &Stack->Buffer, String, Stack->OpString, String2, String1, Dummy );
                }
                else
                {
                    AddArrayElementIndentEx( &Stack->Buffer, String, NULL, NULL, String1, Dummy );
                }
            }
            else
            {
                break;
            }
        }
        else
        {
            if ( TEST_OP1_CONST( OpLine ) )
            {
                if ( TEST_OP2_CONST( OpLine ) )
                    AddArrayElement( &Stack->Buffer, String, Stack->OpString, OP2_VAL( OpLine ), OP1_VAL( OpLine ) );
                else
                    AddArrayElement( &Stack->Buffer, String, NULL, NULL, OP1_VAL( OpLine ) );
            }
            else if ( TEST_OP1_ALL_VAR( OpLine ) )
            {
                Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
                if ( Var == NULL )
                    break;

                String1 = Var->Expr;
                if ( TEST_OP2_CONST( OpLine ) )
                {
                    make_printable_zval_url( OP2_VAL( OpLine ), &Stack->Buffer2 );
                    StackPopAllS( &Stack->Buffer2, &String2 );
                    AddArrayElementEx( &Stack->Buffer, String, Stack->OpString, String2, String1 );
                }
                else if ( TEST_OP2_ALL_VAR( OpLine ) )
                {
                    Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
                    if ( Var1 == NULL )
                        break;

                    String2 = Var1->Expr;
                    AddArrayElementEx( &Stack->Buffer, String, Stack->OpString, String2, String1 );
                }
                else
                {
                    AddArrayElementEx( &Stack->Buffer, String, NULL, NULL, String1 );
                }
            }
            else
            {
                break;
            }
        }
        RetCode = StackPopAllS( &Stack->Buffer, &String );
        UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, OpType );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_include_or_eval( PDUMP_STACK Stack )
{
    ULONG RetCode;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        switch ( OP2_VAL( OpLine )->value.lval )
        {
        case ZEND_INCLUDE :
            String = _T( "include" );
            break;

        case ZEND_INCLUDE_ONCE :
            String = _T( "include_once" );
            break;

        case ZEND_REQUIRE :
            String = _T( "require" );
            break;

        case ZEND_REQUIRE_ONCE :
            String = _T( "require_once" );
            break;

        case ZEND_EVAL :
            String = _T( "eval" );
            break;

        default :
            String = _T( "include" );
            break;
        }
        if ( TEST_OP1_CONST( OpLine ) )
        {
            StackPushS( &Stack->Buffer, String, _tcslen( String ) );
            StackPushS( &Stack->Buffer, _T( "( " ), 2 );
            make_printable_zval_url( OP1_VAL( OpLine ), &Stack->Buffer );
            StackPushS( &Stack->Buffer, _T( " )" ), 2 );
        }
        else if ( TEST_OP1_ALL_VAR( OpLine ) )
        {
            Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                break;

            StackPushS( &Stack->Buffer, String, _tcslen( String ) );
            StackPushS( &Stack->Buffer, _T( "( " ), 2 );
            StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
            StackPushS( &Stack->Buffer, _T( " )" ), 2 );
        }
        else
        {
            break;
        }

        /* Prefix */
        if ( Stack->State & DS_STATE_SILENCE && OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushPrefixS( &Stack->Buffer, Stack->StartChar, Stack->StartCharLength );

        /* Postfix */
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushS( &Stack->Buffer, Stack->EndChar, Stack->EndCharLength );

        RetCode = StackPopAllExS( &Stack->Buffer, &String );
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            dump_string( Stack, String );
        else if ( TEST_OPR_ALL_VAR( OpLine ) )
            UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, Stack->InternalFlags & DS_IFLAGS_OT_MASK );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_unset_var( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG Length;
    ULONG Count;
    zend_op *OpLine;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        if ( !TEST_OP1_CONST( OpLine ) )
            break;

        /* Prefix */
        if ( Stack->State & DS_STATE_SILENCE && OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushS( &Stack->Buffer, Stack->StartChar, Stack->StartCharLength );

        StackPushS( &Stack->Buffer, Stack->OpString, _tcslen( Stack->OpString ) );
        StackPushS( &Stack->Buffer, _T( "( " ), 2 );
        StackPushS( &Stack->Buffer, _T( "$" ), 1 );
        if ( OP1_VAL_TYPE( OpLine ) == IS_STRING )
        {
            Length = ParseExtendVariableLength( OP1_VAL( OpLine )->value.str.val, OP1_VAL( OpLine )->value.str.len );
            if ( Length )
            {
                Count = StackCountS( &Stack->Buffer );
                Length += OP1_VAL( OpLine )->value.str.len + Count;
                StackSetMaxS( &Stack->Buffer, Length );
                ParseExtendVariable( StackBaseS( &Stack->Buffer ) + Count, OP1_VAL( OpLine )->value.str.val, OP1_VAL( OpLine )->value.str.len );
                StackSetTopS( &Stack->Buffer, Length );
            }
            else
            {
                StackPushS( &Stack->Buffer, OP1_VAL( OpLine )->value.str.val, OP1_VAL( OpLine )->value.str.len );
            }
        }
        else
        {
            make_printable_zval_ex( OP1_VAL( OpLine ), &Stack->Buffer, 0 );
        }
        StackPushS( &Stack->Buffer, _T( " )" ), 2 );

        /* Postfix */
        StackPushS( &Stack->Buffer, Stack->EndChar, Stack->EndCharLength );

        RetCode = StackPopAllS( &Stack->Buffer, &String );
        dump_string( Stack, String );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_unset_dim_obj( PDUMP_STACK Stack )
{
    ULONG RetCode;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    PVARIABLE_ENTRY Var1;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
        if ( Var == NULL )
            break;

        if ( TEST_OP2_CONST( OpLine ) )
        {
            StackPushS( &Stack->Buffer, Stack->OpString, _tcslen( Stack->OpString ) );
            StackPushS( &Stack->Buffer, _T( "( " ), 2 );
            StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
            StackPushS( &Stack->Buffer, _T( "[" ), 1 );
            make_printable_zval_ex( OP2_VAL( OpLine ), &Stack->Buffer, _T( '\'' ) );
            StackPushS( &Stack->Buffer, _T( "]" ), 1 );
            StackPushS( &Stack->Buffer, _T( " )" ), 2 );
        }
        else if ( TEST_OP2_ALL_VAR( OpLine ) )
        {
            Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
            if ( Var1 == NULL )
                break;

            StackPushS( &Stack->Buffer, Stack->OpString, _tcslen( Stack->OpString ) );
            StackPushS( &Stack->Buffer, _T( "( " ), 2 );
            StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
            StackPushS( &Stack->Buffer, _T( "[" ), 1 );
            StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
            StackPushS( &Stack->Buffer, _T( "]" ), 1 );
            StackPushS( &Stack->Buffer, _T( " )" ), 2 );
        }
        else
        {
            break;
        }

        /* Prefix */
        if ( Stack->State & DS_STATE_SILENCE && OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushPrefixS( &Stack->Buffer, Stack->StartChar, Stack->StartCharLength );

        /* Postfix */
        StackPushS( &Stack->Buffer, Stack->EndChar, Stack->EndCharLength );

        RetCode = StackPopAllExS( &Stack->Buffer, &String );
        dump_string( Stack, String );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_isset_isempty_x( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG OpType;
    ULONG Flags;
    ULONG Length;
    ULONG Count;
    ULONG Dummy;
    zend_op *Head;
    zend_op *OpLine;
    zend_op *OpLine1;
    zend_op *OpLine2;
    PVARIABLE_ENTRY Var;
    PVARIABLE_ENTRY Var1;
    const TCHAR *OpString;
    TCHAR *String;

    RetCode = 0;
    Head = Stack->Head;
    OpLine = Stack->OpLine;
    do
    {
        if ( TEST_OP1_CONST( OpLine ) )
        {
            if ( OP_CODE( OpLine ) == ZEND_ISSET_ISEMPTY_VAR )
            {
                StackPushPrefixS( &Stack->Buffer1, _T( "$" ), 1 );
                if ( OP1_VAL_TYPE( OpLine ) == IS_STRING )
                {
                    Length = ParseExtendVariableLength( OP1_VAL( OpLine )->value.str.val, OP1_VAL( OpLine )->value.str.len );
                    if ( Length )
                    {
                        Count = StackCountS( &Stack->Buffer1 );
                        Length += OP1_VAL( OpLine )->value.str.len + Count;
                        StackSetMaxS( &Stack->Buffer1, Length );
                        ParseExtendVariable( StackBaseS( &Stack->Buffer1 ) + Count, OP1_VAL( OpLine )->value.str.val, OP1_VAL( OpLine )->value.str.len );
                        StackSetTopS( &Stack->Buffer1, Length );
                    }
                    else
                    {
                        StackPushS( &Stack->Buffer1, OP1_VAL( OpLine )->value.str.val, OP1_VAL( OpLine )->value.str.len );
                    }
                }
                else
                {
                    make_printable_zval_url_ex( OP1_VAL( OpLine ), &Stack->Buffer1, 0 );
                }
            }
            else
            {
                make_printable_zval_url( OP1_VAL( OpLine ), &Stack->Buffer1 );
            }
            Dummy = StackPopAllExS( &Stack->Buffer1, &String );
        }
        else if ( TEST_OP1_ALL_VAR( OpLine ) )
        {
            Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                break;

            String = Var->Expr;
            Dummy = Var->ExprLength;
        }
        else
        {
            if ( OP_CODE( OpLine ) == ZEND_ISSET_ISEMPTY_PROP_OBJ )
            {
                StackPushS( &Stack->Buffer1, DEFAULT_CLASS_THIS, DEFAULT_CLASS_THIS_LENGTH );
                Dummy = StackPopAllExS( &Stack->Buffer1, &String );
            }
            else
            {
                break;
            }
        }

        Var1 = FindInsertVariable( OPR_TYPE( OpLine ), OPR_VAR( OpLine ) );
        if ( Var1 == NULL )
            break;

        if ( Stack->State & DS_STATE_SILENCE )
            Var1->Flags |= VE_FLAGS_SILENCE;
        else
            Var1->Flags &= ~VE_FLAGS_SILENCE;

        if ( Stack->IssetEndOffset != INVALID_OP_OFFSET )
        {
            if ( TEST_OP2_CONST( OpLine ) )
            {
                StackPopNS( &Stack->Isset, NULL, 2 );
                StackPushS( &Stack->Isset, _T( ", " ), 2 );
                StackPushS( &Stack->Isset, String, Dummy );
                if ( OP_CODE( OpLine ) == ZEND_ISSET_ISEMPTY_PROP_OBJ )
                {
                    StackPushS( &Stack->Isset, _T( "->" ), 2 );
                    make_printable_zval_ex( OP2_VAL( OpLine ), &Stack->Isset, 0 );
                }
                else
                {
                    StackPushS( &Stack->Isset, _T( "[" ), 1 );
                    make_printable_zval_ex( OP2_VAL( OpLine ), &Stack->Isset, _T( '\'' ) );
                    StackPushS( &Stack->Isset, _T( "]" ), 1 );
                }
                StackPushS( &Stack->Isset, _T( " )" ), 2 );
            }
            else if ( TEST_OP2_ALL_VAR( OpLine ) )
            {
                Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
                if ( Var1 == NULL )
                    break;

                StackPopNS( &Stack->Isset, NULL, 2 );
                StackPushS( &Stack->Isset, _T( ", " ), 2 );
                StackPushS( &Stack->Isset, String, Dummy );
                if ( OP_CODE( OpLine ) == ZEND_ISSET_ISEMPTY_PROP_OBJ )
                {
                    StackPushS( &Stack->Isset, _T( "->" ), 2 );
                    StackPushS( &Stack->Isset, Var1->Expr, Var1->ExprLength );
                }
                else
                {
                    StackPushS( &Stack->Isset, _T( "[" ), 1 );
                    StackPushS( &Stack->Isset, Var1->Expr, Var1->ExprLength );
                    StackPushS( &Stack->Isset, _T( "]" ), 1 );
                }
                StackPushS( &Stack->Isset, _T( " )" ), 2 );
            }
            else
            {
                StackPopNS( &Stack->Isset, NULL, 2 );
                StackPushS( &Stack->Isset, _T( ", " ), 2 );
                StackPushS( &Stack->Isset, String, Dummy );
                StackPushS( &Stack->Isset, _T( " )" ), 2 );
            }

            if ( Stack->IssetEndOffset != Stack->Offset )
                break;

            Stack->IssetEndOffset = INVALID_OP_OFFSET;
            RetCode = StackPopAllS( &Stack->Isset, &String );
            StackPushS( &Stack->Buffer, String, RetCode );
        }
        else
        {
            if ( GET_GS( )->ExtensionId < EXTENSION_ID_2 )
                Flags = OP2_VAL( OpLine )->value.lval;
            else
                Flags = OP_EX_VALUE( OpLine );
            if ( Flags == ZEND_ISSET )
                OpString = _T( "isset" );
            else
                OpString = _T( "empty" );

            if ( Flags == ZEND_ISSET )
            {
                StackReinitU( &Stack->Common );
                StackReinitU( &Stack->PreSkip );

                OpLine1 = OpLine + 1;
                OpLine2 = Stack->Tail;
                while ( OpLine1 < OpLine2 )
                {
                    if ( OP_CODE( OpLine1 ) == OP_CODE( OpLine ) )
                    {
                        if ( OP_CODE( OpLine1 + 1 ) == ZEND_BOOL &&
                            OP1_VAR( OpLine1 + 1 ) == OPR_VAR( OpLine1 ) &&
                            OP1_TYPE( OpLine1 + 1 ) == OPR_TYPE( OpLine1 ) )
                        {
                            if ( OPR_VAR( OpLine1 + 1 ) != OPR_VAR( OpLine ) )
                                break;
                        }
                        else
                        {
                            if ( OPR_VAR( OpLine1 ) != OPR_VAR( OpLine ) )
                                break;
                        }

                        StackPushU( &Stack->Common, OpLine1 - Head );
                    }
                    else if ( OP_CODE( OpLine1 ) == ZEND_JMPZ_EX )
                    {
                        if ( OPR_VAR( OpLine1 ) != OPR_VAR( OpLine ) || OP1_VAR( OpLine1 ) != OPR_VAR( OpLine ) )
                            break;

                        OpLine2 = Head + OP_JMPX( OpLine1, Head );
                        if ( OP_CODE( OpLine2 ) == ZEND_JMPZ_EX || OP_CODE( OpLine2 ) == ZEND_JMPNZ_EX )
                            OpLine2++;
                        StackPushAscU( &Stack->PreSkip, OpLine1 - Head );
                    }
                    else if ( OP_CODE( OpLine1 ) == ZEND_JMPNZ_EX || OP_CODE( OpLine1 ) == ZEND_JMPNZ )
                    {
                        StackPushAscU( &Stack->PreSkip, OpLine1 - Head );
                        break;
                    }
                    else if ( OP_CODE( OpLine1 ) == ZEND_JMPZ )
                    {
                        if ( OP1_VAR( OpLine1 ) != OPR_VAR( OpLine ) )
                            break;

                        OpLine2 = Head + OP_JMPX( OpLine1, Head );
                        StackPushAscU( &Stack->PreSkip, OpLine1 - Head );
                    }
                    else if ( OP_CODE( OpLine1 ) == ZEND_BOOL )
                    {
                        StackPushAscU( &Stack->PreSkip, OpLine1 - Head );
                        break;
                    }
                    else if ( OPR_EA_TYPE( OpLine1 ) & EXT_TYPE_UNUSED || OP_CODE( OpLine1 ) == ZEND_FREE )
                    {
                        break;
                    }
                    OpLine1++;
                }
            }

            /* Prefix */
            if ( Stack->State & DS_STATE_SILENCE && OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
                StackPushS( &Stack->Buffer, Stack->StartChar, Stack->StartCharLength );

            if ( TEST_OP2_CONST( OpLine ) )
            {
                if ( OP2_VAL_TYPE( OpLine ) == IS_STRING )
                {
                    StackPushS( &Stack->Buffer, OpString, _tcslen( OpString ) );
                    StackPushS( &Stack->Buffer, _T( "( " ), 2 );
                    StackPushS( &Stack->Buffer, String, Dummy );
                    if ( OP_CODE( OpLine ) == ZEND_ISSET_ISEMPTY_PROP_OBJ )
                    {
                        StackPushS( &Stack->Buffer, _T( "->" ), 2 );
                        make_printable_zval_ex( OP2_VAL( OpLine ), &Stack->Buffer, 0 );
                    }
                    else
                    {
                        StackPushS( &Stack->Buffer, _T( "[" ), 1 );
                        make_printable_zval_ex( OP2_VAL( OpLine ), &Stack->Buffer, _T( '\'' ) );
                        StackPushS( &Stack->Buffer, _T( "]" ), 1 );
                    }
                    StackPushS( &Stack->Buffer, _T( " )" ), 2 );
                }
                else if ( OP2_VAL_TYPE( OpLine ) == IS_NULL )
                {
                    Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
                    if ( Var1 )
                    {
                        StackPushS( &Stack->Buffer, OpString, _tcslen( OpString ) );
                        StackPushS( &Stack->Buffer, _T( "( " ), 2 );
                        StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
                        StackPushS( &Stack->Buffer, _T( "::" ), 2 );
                        StackPushS( &Stack->Buffer, String, Dummy );
                        StackPushS( &Stack->Buffer, _T( " )" ), 2 );
                    }
                }
                else
                {
                    StackPushS( &Stack->Buffer, OpString, _tcslen( OpString ) );
                    StackPushS( &Stack->Buffer, _T( "( " ), 2 );
                    StackPushS( &Stack->Buffer, String, Dummy );
                    StackPushS( &Stack->Buffer, _T( "[" ), 1 );
                    make_printable_zval_ex( OP2_VAL( OpLine ), &Stack->Buffer, 0 );
                    StackPushS( &Stack->Buffer, _T( "] )" ), 3 );
                }
            }
            else if ( TEST_OP2_ALL_VAR( OpLine ) )
            {
                Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
                if ( Var1 == NULL )
                    break;

                StackPushS( &Stack->Buffer, OpString, _tcslen( OpString ) );
                StackPushS( &Stack->Buffer, _T( "( " ), 2 );
                StackPushS( &Stack->Buffer, String, Dummy );
                if ( OP_CODE( OpLine ) == ZEND_ISSET_ISEMPTY_PROP_OBJ )
                {
                    StackPushS( &Stack->Buffer, _T( "->" ), 2 );
                    StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
                }
                else
                {
                    StackPushS( &Stack->Buffer, _T( "[" ), 1 );
                    StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
                    StackPushS( &Stack->Buffer, _T( "]" ), 1 );
                }
                StackPushS( &Stack->Buffer, _T( " )" ), 2 );
            }
            else
            {
                StackPushS( &Stack->Buffer, OpString, _tcslen( OpString ) );
                StackPushS( &Stack->Buffer, _T( "( " ), 2 );
                StackPushS( &Stack->Buffer, String, Dummy );
                StackPushS( &Stack->Buffer, _T( " )" ), 2 );
            }

            if ( Flags == ZEND_ISSET )
            {
                if ( StackCountU( &Stack->Common ) )
                {
                    StackTopU( &Stack->Common, &Stack->IssetEndOffset );
                    StackPopAllU( &Stack->Common, NULL );

                    StackPopU( &Stack->PreSkip, NULL );
                    while ( StackPopBottomU( &Stack->PreSkip, &Dummy ) )
                        StackPushAscU( &Stack->Skip, Dummy );

                    RetCode = StackPopAllS( &Stack->Buffer, &String );
                    StackPushS( &Stack->Isset, String, RetCode );
                    break;
                }
            }
        }

        /* Op type */
        OpType = ( Stack->InternalFlags & DS_IFLAGS_OT_MASK ) | VE_FLAGS_ISSET_ISEMPTY;

        /* Postfix */
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushS( &Stack->Buffer, Stack->EndChar, Stack->EndCharLength );

        RetCode = StackPopAllS( &Stack->Buffer, &String );
        if ( GET_GS_STATE( ) & GS_STATE_EXTEND )
        {
            UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, OpType );
        }
        else
        {
            if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
                dump_string( Stack, String );
            else if ( TEST_OPR_ALL_VAR( OpLine ) )
                UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, OpType );
        }
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_fe_reset( PDUMP_STACK Stack )
{
    ULONG RetCode;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        if ( !TEST_OP1_ALL_VAR( OpLine ) || !TEST_OPR_ALL_VAR( OpLine ) )
            break;

        Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
        if ( Var == NULL )
            break;

        UpdateVariable( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Var->Expr );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_fe_fetch( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG FetchType;
    ULONG Dummy;
    zend_op *Head;
    zend_op *OpLine;
    zend_op *OpLine1;
    zend_op *OpLine2;
    PVARIABLE_ENTRY Var;
    PVARIABLE_ENTRY Var1;
    PVARIABLE_ENTRY Var2;
    TCHAR *String;

    RetCode = 0;
    Head = Stack->Head;
    OpLine = Stack->OpLine;
    do
    {
        if ( !TEST_OP1_ALL_VAR( OpLine ) || !TEST_OPR_ALL_VAR( OpLine ) )
            break;

        Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
        if ( Var == NULL )
            break;

        /* Php5 */
        OpLine1 = OpLine + 1;
        if ( OP_CODE( OpLine1 ) == ZEND_OP_DATA )
            Dummy = Stack->Offset + 1;
        else
            Dummy = 0;

        /* May be Optimized */
        while ( OP_CODE( OpLine1 ) != ZEND_ASSIGN && OpLine1 < Stack->Tail )
        {
            if ( OP_CODE( OpLine1 ) == ZEND_FETCH_W )
            {
                FetchType = NODE_FETCH_TYPE( &OpLine1->op2 );
                if ( FetchType == ZEND_FETCH_GLOBAL && OP_CODE( OpLine1 + 1 ) != ZEND_ASSIGN_REF )
                {
                    StackPushS( &Stack->Buffer1, DEFAULT_GLOBAL_VARIABLE, DEFAULT_GLOBAL_VARIABLE_LENGTH );
                    StackPushS( &Stack->Buffer1, _T( "['" ), 2 );
                    StackPushS( &Stack->Buffer1, OP1_VAL( OpLine1 )->value.str.val, OP1_VAL( OpLine1 )->value.str.len );
                    StackPushS( &Stack->Buffer1, _T( "']" ), 2 );
                    StackPopAllS( &Stack->Buffer1, &String );
                }
                else
                {
                    String = NULL;
                }
                UpdateVariableEx( OPR_TYPE( OpLine1 ), OPR_VAR( OpLine1 ), OpLine1 - Head, OP1_VAL( OpLine1 )->value.str.val, String, MAKE_FETCH_FLAGS( FetchType ) );
            }
            else if ( OP_CODE( OpLine1 ) == ZEND_FREE || OP_CODE( OpLine1 ) != ZEND_NOP && OPR_EA_TYPE( OpLine1 ) & EXT_TYPE_UNUSED )
            {
                break;
            }
            OpLine1++;
        }

        /* MUST be exist */
        Var1 = FindInsertVariable( OP1_TYPE( OpLine1 ), OP1_VAR( OpLine1 ) );
        if ( Var1 == NULL )
            break;

        StackPushS( &Stack->Buffer, Stack->OpString, _tcslen( Stack->OpString ) );
        StackPushS( &Stack->Buffer, _T( " ( " ), 3 );
        StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
        StackPushS( &Stack->Buffer, _T( " as " ), 4 );

        /* Next op code */
        OpLine2 = OpLine1 + 1;
        if ( Dummy )
        {
            while ( OpLine2 < Stack->Tail )
            {
                if ( OP_CODE( OpLine2 ) == ZEND_ASSIGN )
                {
                    if ( OP2_TYPE( OpLine2 ) != OPR_TYPE( Head + Dummy ) || OP2_VAR( OpLine2 ) != OPR_VAR( Head + Dummy ) )
                        OpLine2 = OpLine;
                    break;
                }
                else if ( OP_CODE( OpLine2 ) == ZEND_FREE || OP_CODE( OpLine2 ) != ZEND_NOP && OPR_EA_TYPE( OpLine2 ) & EXT_TYPE_UNUSED )
                {
                    break;
                }
                OpLine2++;
            }
        }

        if ( OP_CODE( OpLine2 ) == ZEND_ASSIGN )
        {
            Var2 = FindVariableById( OP1_TYPE( OpLine2 ), OP1_VAR( OpLine2 ) );
            if ( Var2 )
            {
                OpLine1 = OpLine2;
                StackPushS( &Stack->Buffer, Var2->Expr, Var2->ExprLength );
                StackPushS( &Stack->Buffer, _T( " => " ), 4 );
                StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
            }
        }
        else if ( OP_CODE( OpLine1 ) == ZEND_FREE )
        {
            StackPushS( &Stack->Buffer, _T( "$_BUG_" ), 6 );
            StackPushS( &Stack->Buffer, Var1->Name, Var1->NameLength );
            if ( GET_GS_FLAGS( ) & GS_FLAGS_BUG )
                dump_string_ex( Stack, _T( "//[BUG][%6d]foreach key unknown\r\n" ), Stack->Offset );
        }
        else
        {
            StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
        }

        if ( GET_GS( )->MajorId < EXTENSION_ID_2 )
        {
            if ( OP_CODE( OpLine1 ) == ZEND_ASSIGN )
                OpLine1++;

            /* Seek end */
            while ( OpLine1 < Stack->Tail )
            {
                if ( OP_CODE( OpLine1 ) == ZEND_FREE || OP_CODE( OpLine1 ) != ZEND_NOP )
                    break;
                OpLine1++;
            }

            if ( OP_CODE( OpLine1 ) != ZEND_FREE )
                OpLine1--;
        }

        /* Skip to next */
        Stack->NextOpLine = OpLine1 + 1;

        StackPushS( &Stack->Buffer, _T( " )\r\n" ), 4 );
        RetCode = StackPopAllS( &Stack->Buffer, &String );
        dump_string( Stack, String );
        dump_string( Stack, _T( "{\r\n" ) );
        PUSH_INC_INDENT( Stack );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_exit( PDUMP_STACK Stack )
{
    ULONG RetCode;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        if ( TEST_OP1_CONST( OpLine ) )
        {
            StackPushS( &Stack->Buffer, _T( "( " ), 2 );
            make_printable_zval_url( OP1_VAL( OpLine ), &Stack->Buffer );
            StackPushS( &Stack->Buffer, _T( " )" ), 2 );
        }
        else if ( TEST_OP1_ALL_VAR( OpLine ) )
        {
            Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                break;

            StackPushS( &Stack->Buffer, _T( "( " ), 2 );
            StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
            StackPushS( &Stack->Buffer, _T( " )" ), 2 );
        }
        else
        {
            StackPushS( &Stack->Buffer, _T( "( )" ), 3 );
        }

        /* Op string */
        StackPushPrefixS( &Stack->Buffer, Stack->OpString, _tcslen( Stack->OpString ) );

        /* Prefix */
        if ( Stack->State & DS_STATE_SILENCE && OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushPrefixS( &Stack->Buffer, Stack->StartChar, Stack->StartCharLength );

        OpLine++;
        if ( Stack->Offset < Stack->LastOffset - 1 && OP_CODE( OpLine ) == ZEND_QM_ASSIGN && OP1_VAL_TYPE( OpLine ) == IS_BOOL && OP1_VAL( OpLine )->value.lval == TRUE )
        {
            OP1_TYPE( OpLine ) = IS_VAR;
            SET_OP1_VAR( OpLine, IS_SPECIFIC_ID | Stack->Offset );
            RetCode = StackPopAllExS( &Stack->Buffer, &String );
            UpdateVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ), String );
        }
        else
        {
            /* Postfix */
            StackPushS( &Stack->Buffer, Stack->EndChar, Stack->EndCharLength );

            RetCode = StackPopAllExS( &Stack->Buffer, &String );
            dump_string( Stack, String );
        }
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_fetch_x( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG FetchType;
    ULONG Dummy;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    PVARIABLE_ENTRY Var1;
    TCHAR *String;
    TCHAR *String1;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        FetchType = NODE_FETCH_TYPE( &OpLine->op2 );
        if ( TEST_OP1_CONST( OpLine ) )
        {
            if ( OP1_VAL_TYPE( OpLine ) == IS_STRING )
            {
                String = OP1_VAL( OpLine )->value.str.val;
                Dummy = OP1_VAL( OpLine )->value.str.len;
                if ( OP_CODE( OpLine ) == ZEND_FETCH_W && FetchType == ZEND_FETCH_GLOBAL && OP_CODE( OpLine + 1 ) != ZEND_ASSIGN_REF )
                {
                    StackPushS( &Stack->Buffer1, DEFAULT_GLOBAL_VARIABLE, DEFAULT_GLOBAL_VARIABLE_LENGTH );
                    StackPushS( &Stack->Buffer1, _T( "['" ), 2 );
                    StackPushS( &Stack->Buffer1, String, Dummy );
                    StackPushS( &Stack->Buffer1, _T( "']" ), 2 );
                    StackPopAllS( &Stack->Buffer1, &String1 );
                }
                else
                {
                    String1 = NULL;
                }

                if ( TEST_OP2_CONST( OpLine ) && OP2_VAL_TYPE( OpLine ) == IS_NULL )
                {
                    Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
                    if ( Var1 == NULL )
                        break;

                    StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
                    StackPushS( &Stack->Buffer, _T( "::$" ), 3 );
                    StackPushS( &Stack->Buffer, String, Dummy );
                    StackPopAllS( &Stack->Buffer, &String1 );
                }
                UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, String, String1, MAKE_FETCH_FLAGS( FetchType ) );
            }
            else
            {
                /* Fix */
                make_printable_zval_url_ex( OP1_VAL( OpLine ), &Stack->Buffer, 0 );
                StackPopAllS( &Stack->Buffer, &String );
                if ( GET_GS( )->ExtensionId < EXTENSION_ID_2 )
                    UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, String, NULL, MAKE_FETCH_FLAGS( FetchType ) );
                else
                    UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, String, NULL, MAKE_FETCH_FLAGS( FetchType ) );
            }
        }
        else if ( TEST_OP1_ALL_VAR( OpLine ) )
        {
            Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                break;

            /* Add bracket if it is expression */
            Dummy = ( Var->Flags & DS_IFLAGS_OT_MASK ) != DS_IFLAGS_OT_MAX;
            if ( Dummy )
                StackPushS( &Stack->Buffer, _T( "${ _T( " ), 3 );
            else
                StackPushS( &Stack->Buffer, _T( "$" ), 1 );

            StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
            if ( Dummy )
                StackPushS( &Stack->Buffer, _T( " }" ), 2 );

            RetCode = StackPopAllS( &Stack->Buffer, &String );
            if ( GET_GS( )->ExtensionId < EXTENSION_ID_2 )
                UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, MAKE_FETCH_FLAGS( FetchType ) );
            else
                UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, MAKE_FETCH_FLAGS( FetchType ) );
        }
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_fetch_dim_x( PDUMP_STACK Stack );
ULONG FASTCALL dump_fetch_dim_r( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG NextOffset;
    ULONG FetchType;
    ULONG Flags;
    ULONG Length;
    ULONG Iter;
    ULONG Count;
    ULONG Dummy;
    ULONG PrevCount;
    ULONG PrevIndex;
    ULONG CurCount;
    ULONG CurIndex;
    ULONG CurTopIndex;
    zend_op *Head;
    zend_op *OpLine;
    zend_op *OpLine1;
    zend_op *OpLine2;
    PVARIABLE_ENTRY Var;
    PVARIABLE_ENTRY Var1;
    KEY_VALUE VarStringMap;
    TCHAR *String;
    TCHAR *String1;
    TCHAR *String2;
    TCHAR Buffer[256];

    RetCode = 0;
    Head = Stack->Head;
    OpLine = Stack->OpLine;
    do
    {
        if ( TEST_OP2_CONST( OpLine ) && OP2_VAL_TYPE( OpLine ) == IS_LONG )
        {
            if ( TEST_OP1_CONST( OpLine ) )
            {
                make_printable_zval_url_ex( OP1_VAL( OpLine ), &Stack->Buffer, 0 );
                Length = StackPopAllS( &Stack->Buffer1, &String );
                Flags = VE_FLAGS_FUNCTION;
            }
            else if ( TEST_OP1_ALL_VAR( OpLine ) )
            {
                Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
                if ( Var == NULL )
                    break;

                StackPushS( &Stack->Buffer1, Var->Expr, Var->ExprLength );
                Length = StackPopAllS( &Stack->Buffer1, &String );
                Flags = Var->Flags & VE_FLAGS_FUNCTION;
            }
            else
            {
                break;
            }

            StackReinitU( &Stack->Common );
            StackReinitU( &Stack->Common1 );
            StackReinitU( &Stack->Common2 );

            Dummy = OP2_VAL( OpLine )->value.lval;
            OpLine1 = OpLine;
            while ( OpLine1 < Stack->Tail )
            {
                if ( OP_CODE( OpLine1 ) == OP_CODE( OpLine ) )
                {
                    if ( OP1_TYPE( OpLine1 ) != OP1_TYPE( OpLine ) || OP1_VAR( OpLine1 ) != OP1_VAR( OpLine ) )
                        break;

                    if ( !TEST_OP2_CONST( OpLine1 ) || OP2_VAL_TYPE( OpLine1 ) != IS_LONG )
                        break;

                    if ( Dummy < ( ULONG )OP2_VAL( OpLine1 )->value.lval )
                        break;
                    else if ( Dummy > ( ULONG )OP2_VAL( OpLine1 )->value.lval )
                        Dummy--;

                    StackPushU( &Stack->Common1, OP2_VAL( OpLine1 )->value.lval );
                    Count = 1;
                    OpLine1++;
                    while ( OP_CODE( OpLine1 ) == OP_CODE( OpLine ) )
                    {
                        if ( OP2_VAL_TYPE( OpLine1 ) != IS_LONG || OP1_TYPE( OpLine1 ) != OPR_TYPE( OpLine1 - 1 ) || OP1_VAR( OpLine1 ) != OPR_VAR( OpLine1 - 1 ) )
                            break;

                        StackPushU( &Stack->Common1, OP2_VAL( OpLine1 )->value.lval );
                        Count++;
                        OpLine1++;
                    }
                    OpLine1--;
                    StackPushU( &Stack->Common1, Count );
                }
                else if ( OP_CODE( OpLine1 ) == ZEND_ASSIGN )
                {
                    OpLine2 = OpLine1 - 1;
                    /* Skip */
                    while ( Head < OpLine2 && ( OP_CODE( OpLine2 ) == ZEND_NOP || OP_CODE( OpLine2 ) == ZEND_FETCH_W || OP_CODE( OpLine2 ) == ZEND_FETCH_DIM_W ) )
                        OpLine2--;
                    if ( OP_CODE( OpLine2 ) != OP_CODE( OpLine ) )
                        break;

                    if ( OPR_TYPE( OpLine2 ) != OP2_TYPE( OpLine1 ) || OPR_VAR( OpLine2 ) != OP2_VAR( OpLine1 ) )
                        break;

                    StackPushU( &Stack->Common, OpLine1 - Head );
                }
                else if ( OP_CODE( OpLine1 ) == ZEND_FETCH_W && TEST_OP1_CONST( OpLine1 ) )
                {
                    String = OP1_VAL( OpLine1 )->value.str.val;
                    Dummy = OP1_VAL( OpLine1 )->value.str.len;
                    FetchType = NODE_FETCH_TYPE( &OpLine1->op2 );
                    if ( FetchType == ZEND_FETCH_GLOBAL && OP_CODE( OpLine1 + 1 ) != ZEND_ASSIGN_REF )
                    {
                        StackPushS( &Stack->Buffer1, DEFAULT_GLOBAL_VARIABLE, DEFAULT_GLOBAL_VARIABLE_LENGTH );
                        StackPushS( &Stack->Buffer1, _T( "['" ), 2 );
                        StackPushS( &Stack->Buffer1, String, Dummy );
                        StackPushS( &Stack->Buffer1, _T( "']" ), 2 );
                        StackPopAllS( &Stack->Buffer1, &String1 );
                    }
                    else
                    {
                        String1 = NULL;
                    }
                    UpdateVariableEx( OPR_TYPE( OpLine1 ), OPR_VAR( OpLine1 ), OpLine1 - Head, String, String1, MAKE_FETCH_FLAGS( FetchType ) );
                }
                else if ( OP_CODE( OpLine1 ) == ZEND_FETCH_DIM_W )
                {
                    Var = FindInsertVariable( OP1_TYPE( OpLine1 ), OP1_VAR( OpLine1 ) );
                    if ( Var == NULL )
                        break;

                    if ( TEST_OP2_CONST( OpLine1 ) )
                    {
                        StackPushS( &Stack->Buffer2, Var->Expr, Var->ExprLength );
                        StackPushS( &Stack->Buffer2, _T( "[" ), 1 );
                        if ( OP2_VAL_TYPE( OpLine1 ) == IS_STRING )
                        {
                            if ( OP2_VAL( OpLine1 )->value.str.val[0] == _T( '\'' ) || OP2_VAL( OpLine1 )->value.str.val[0] == _T( '\"' ) )
                                make_printable_zval_url_ex( OP2_VAL( OpLine1 ), &Stack->Buffer2, 0 );
                            else
                                make_printable_zval_url_ex( OP2_VAL( OpLine1 ), &Stack->Buffer2, _T( '\'' ) );
                        }
                        else if ( OP2_VAL_TYPE( OpLine1 ) == IS_LONG )
                        {
                            Dummy = _sntprintf( Buffer, sizeof( Buffer ), _T( "%d" ), OP2_VAL( OpLine1 )->value.lval );
                            StackPushS( &Stack->Buffer2, Buffer, Dummy );
                        }
                        StackPushS( &Stack->Buffer2, _T( "]" ), 1 );
                    }
                    else if ( TEST_OP2_ALL_VAR( OpLine1 ) )
                    {
                        Var1 = FindInsertVariable( OP2_TYPE( OpLine1 ), OP2_VAR( OpLine1 ) );
                        if ( Var1 == NULL )
                            break;

                        StackPushS( &Stack->Buffer2, Var->Expr, Var->ExprLength );
                        StackPushS( &Stack->Buffer2, _T( "[" ), 1 );
                        StackPushS( &Stack->Buffer2, Var1->Expr, Var1->ExprLength );
                        StackPushS( &Stack->Buffer2, _T( "]" ), 1 );
                    }
                    else
                    {
                        StackPushS( &Stack->Buffer2, Var->Expr, Var->ExprLength );
                        StackPushS( &Stack->Buffer2, _T( "[]" ), 2 );
                    }
                    RetCode = StackPopAllS( &Stack->Buffer2, &String1 );
                    Var = FindInsertVariable( OPR_TYPE( OpLine1 ), OPR_VAR( OpLine1 ) );
                    if ( Var )
                    {
                        /* Save */
                        String2 = HEAP_ALLOC( ROUND_STRING( Var->ExprLength ) * sizeof( TCHAR ) );
                        if ( String2 )
                        {
                            memcpy( String2, Var->Expr, ( Var->ExprLength + 1 ) * sizeof( TCHAR ) );
                            VarStringMap.Key = MAKE_KEY( IS_SPECIFIC_ID, ( ULONG )OpLine1 );
                            VarStringMap.Value = ( ULONG )String2;
                            StackPushAscT( &Stack->VarStringMap, &VarStringMap );
                        }
                        StackPushU( &Stack->Common2, OpLine1 - Head );
                    }
                    UpdateVariableEx( OPR_TYPE( OpLine1 ), OPR_VAR( OpLine1 ), OpLine1 - Head, NULL, String1, 0 );
                }
                else if ( OP_CODE( OpLine1 ) != ZEND_NOP )
                {
                    break;
                }
                OpLine1++;
            }

            if ( ( OP_CODE( OpLine1 ) == ZEND_JMPZ || OP_CODE( OpLine1 ) == ZEND_JMPNZ || OP_CODE( OpLine1 ) == ZEND_JMPZNZ ) &&
                OP1_TYPE( OpLine1 ) == OP1_TYPE( OpLine ) && OP1_VAR( OpLine1 ) == OP1_VAR( OpLine ) )
                Flags |= VE_FLAGS_VAR_MAP;

            if ( StackCountU( &Stack->Common ) > 1 || ( Flags & VE_FLAGS_FUNCTION ) )
            {
                if ( OP_CODE( OpLine1 ) == ZEND_FREE && OP1_TYPE( OpLine1 ) == OP1_TYPE( OpLine ) && OP1_VAR( OpLine1 ) == OP1_VAR( OpLine ) )
                    StackPushAscU( &Stack->Skip, OpLine1 - Head );

                Stack->NextOpLine = OpLine1;
                StackPushS( &Stack->Buffer, _T( "list( " ), 6 );

                PrevCount = 1;
                PrevIndex = 0;
                CurTopIndex = 0;
                StackReinitU( &Stack->Common2 );
                while ( StackPopU( &Stack->Common1, &CurCount ) )
                {
                    StackPopU( &Stack->Common1, &CurIndex );
                    Dummy = CurCount - 1;
                    if ( Dummy == 0 )
                    {
                        CurTopIndex = CurIndex;
                    }
                    else
                    {
                        while ( Dummy > 1 )
                        {
                            StackPopU( &Stack->Common1, NULL );
                            Dummy--;
                        }
                        StackPopU( &Stack->Common1, &CurTopIndex );
                    }

                    if ( CurCount > PrevCount )
                    {
                        StackPushU( &Stack->Common2, CurTopIndex + 1 );
                        PrevIndex = 0;

                        Dummy = CurCount;
                        while ( Dummy > PrevCount )
                        {
                            StackPushS( &Stack->Buffer, _T( "list( " ), 6 );
                            Dummy--;
                        }
                    }
                    else if ( CurCount < PrevCount )
                    {
                        StackPopU( &Stack->Common2, &PrevIndex );

                        StackPopNS( &Stack->Buffer, NULL, 2 );
                        Dummy = CurCount;
                        while ( Dummy < PrevCount )
                        {
                            StackPushS( &Stack->Buffer, _T( " )" ), 2 );
                            Dummy++;
                        }
                        StackPushS( &Stack->Buffer, _T( ", " ), 2 );
                    }
                    PrevCount = CurCount;

                    for ( Iter = PrevIndex; Iter < CurIndex; Iter++ )
                        StackPushS( &Stack->Buffer, _T( ", " ), 2 );
                    PrevIndex = CurIndex + 1;

                    if ( StackPopU( &Stack->Common, &NextOffset ) )
                    {
                        OpLine2 = Head + NextOffset;
                        Var1 = FindInsertVariable( OP1_TYPE( OpLine2 ), OP1_VAR( OpLine2 ) );
                        if ( Var1 )
                        {
                            StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
                            StackPushS( &Stack->Buffer, _T( ", " ), 2 );
                        }
                    }
                }
                StackPopNS( &Stack->Buffer, NULL, 2 );
                StackPushS( &Stack->Buffer, _T( " ) = " ), 5 );
                StackPushS( &Stack->Buffer, String, Length );

                /* Prefix */
                if ( Stack->State & DS_STATE_SILENCE && OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
                    StackPushPrefixS( &Stack->Buffer, Stack->StartChar, Stack->StartCharLength );

                if ( Flags & VE_FLAGS_VAR_MAP )
                {
                    /* list( x, x ) = x */
                    RetCode = StackPopAllExS( &Stack->Buffer, &String );
                    Dummy = ROUND_STRING( RetCode ) * sizeof( TCHAR );
                    String1 = HEAP_ALLOC( Dummy );
                    if ( String1 )
                    {
                        memcpy( String1, String, ( RetCode + 1 ) * sizeof( TCHAR ) );
                        VarStringMap.Key = MAKE_KEY( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
                        VarStringMap.Value = ( ULONG )String1;
                        StackPushAscT( &Stack->VarStringMap, &VarStringMap );
                    }
                    UpdateVariableEx( OP1_TYPE( OpLine ), OP1_VAR( OpLine ), Stack->Offset, NULL, NULL, VE_FLAGS_FLAGS | VE_FLAGS_VAR_MAP );
                }
                else
                {
                    /* Postfix */
                    StackPushS( &Stack->Buffer, Stack->EndChar, Stack->EndCharLength );
                    RetCode = StackPopAllExS( &Stack->Buffer, &String );
                    dump_string( Stack, String );
                }
                break;
            }
            else
            {
                /* Re-init */
                StackReinitS( &Stack->Buffer );
                StackReinitS( &Stack->Buffer1 );
                StackReinitS( &Stack->Buffer2 );

                /* Restore */
                while ( StackPopU( &Stack->Common2, &NextOffset ) )
                {
                    OpLine1 = Head + NextOffset;
                    VarStringMap.Key = MAKE_KEY( IS_SPECIFIC_ID, ( ULONG )OpLine1 );
                    Dummy = StackFindAscT( &Stack->VarStringMap, &VarStringMap );
                    if ( Dummy )
                    {
                        String1 = ( TCHAR* ) ( ( PKEY_VALUE )StackAtT( &Stack->VarStringMap, Dummy - 1 ) )->Value;
                        UpdateVariable( OPR_TYPE( OpLine1 ), OPR_VAR( OpLine1 ), String1 );
                        StackRemoveIndexT( &Stack->VarStringMap, Dummy - 1 );
                    }
                }
            }
        }
        RetCode = dump_fetch_dim_x( Stack );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_fetch_dim_x( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG Dummy;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    PVARIABLE_ENTRY Var1;
    TCHAR *String;
    TCHAR Buffer[256];

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
        if ( Var == NULL )
            break;

        if ( TEST_OP2_CONST( OpLine ) )
        {
            StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
            StackPushS( &Stack->Buffer, _T( "[" ), 1 );
            if ( OP2_VAL_TYPE( OpLine ) == IS_STRING )
            {
                if ( OP2_VAL( OpLine )->value.str.val[0] == _T( '\'' ) || OP2_VAL( OpLine )->value.str.val[0] == _T( '\"' ) )
                    make_printable_zval_url_ex( OP2_VAL( OpLine ), &Stack->Buffer, 0 );
                else
                    make_printable_zval_url_ex( OP2_VAL( OpLine ), &Stack->Buffer, _T( '\'' ) );
            }
            else if ( OP2_VAL_TYPE( OpLine ) == IS_LONG )
            {
                Dummy = _sntprintf( Buffer, sizeof( Buffer ), _T( "%d" ), OP2_VAL( OpLine )->value.lval );
                StackPushS( &Stack->Buffer, Buffer, Dummy );
            }
            StackPushS( &Stack->Buffer, _T( "]" ), 1 );
        }
        else if ( TEST_OP2_ALL_VAR( OpLine ) )
        {
            Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
            if ( Var1 == NULL )
                break;

            StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
            StackPushS( &Stack->Buffer, _T( "[" ), 1 );
            StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
            StackPushS( &Stack->Buffer, _T( "]" ), 1 );
        }
        else
        {
            StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
            StackPushS( &Stack->Buffer, _T( "[]" ), 2 );
        }

        /* Prefix */
        if ( Stack->State & DS_STATE_SILENCE && OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushPrefixS( &Stack->Buffer, Stack->StartChar, Stack->StartCharLength );

        /* Postfix */
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushS( &Stack->Buffer, Stack->EndChar, Stack->EndCharLength );

        RetCode = StackPopAllExS( &Stack->Buffer, &String );
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            dump_string( Stack, String );
        else if ( TEST_OPR_ALL_VAR( OpLine ) )
            UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, Stack->InternalFlags & DS_IFLAGS_OT_MASK );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_fetch_obj_x( PDUMP_STACK Stack )
{
    ULONG RetCode;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    PVARIABLE_ENTRY Var1;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        if ( TEST_OP1_ALL_VAR( OpLine ) )
        {
            Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                break;

            if ( TEST_OP2_CONST( OpLine ) )
            {
                StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
                StackPushS( &Stack->Buffer, _T( "->" ), 2 );
                make_printable_zval_ex( OP2_VAL( OpLine ), &Stack->Buffer, 0 );
            }
            else if ( TEST_OP2_ALL_VAR( OpLine ) )
            {
                Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
                if ( Var1 == NULL )
                    break;

                StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
                StackPushS( &Stack->Buffer, _T( "->" ), 2 );
                StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
            }
            else
            {
                break;
            }
        }
        else
        {
            if ( TEST_OP2_CONST( OpLine ) )
            {
                StackPushS( &Stack->Buffer, DEFAULT_CLASS_THIS_P, DEFAULT_CLASS_THIS_P_LENGTH );
                make_printable_zval_ex( OP2_VAL( OpLine ), &Stack->Buffer, 0 );
            }
            else if ( TEST_OP2_ALL_VAR( OpLine ) )
            {
                Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
                if ( Var1 == NULL )
                    break;

                StackPushS( &Stack->Buffer, DEFAULT_CLASS_THIS_P, DEFAULT_CLASS_THIS_P_LENGTH );
                StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
            }
            else
            {
                break;
            }
        }

        /* Prefix */
        if ( Stack->State & DS_STATE_SILENCE && OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushPrefixS( &Stack->Buffer, Stack->StartChar, Stack->StartCharLength );

        /* Postfix */
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushS( &Stack->Buffer, Stack->EndChar, Stack->EndCharLength );

        RetCode = StackPopAllExS( &Stack->Buffer, &String );
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            dump_string( Stack, String );
        else if ( TEST_OPR_ALL_VAR( OpLine ) )
            UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, Stack->InternalFlags & DS_IFLAGS_OT_MASK );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_fetch_unset_x( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG Length;
    ULONG Count;
    zend_op *OpLine;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        if ( !TEST_OP1_CONST( OpLine ) )
            break;

        /* Prefix */
        if ( Stack->State & DS_STATE_SILENCE && OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushS( &Stack->Buffer, Stack->StartChar, Stack->StartCharLength );

        StackPushS( &Stack->Buffer, _T( "$" ), 1 );
        if ( OP1_VAL_TYPE( OpLine ) == IS_STRING )
        {
            Length = ParseExtendVariableLength( OP1_VAL( OpLine )->value.str.val, OP1_VAL( OpLine )->value.str.len );
            if ( Length )
            {
                Count = StackCountS( &Stack->Buffer );
                Length += OP1_VAL( OpLine )->value.str.len + Count;
                StackSetMaxS( &Stack->Buffer, Length );
                ParseExtendVariable( StackBaseS( &Stack->Buffer ) + Count, OP1_VAL( OpLine )->value.str.val, OP1_VAL( OpLine )->value.str.len );
                StackSetTopS( &Stack->Buffer, Length );
            }
            else
            {
                StackPushS( &Stack->Buffer, OP1_VAL( OpLine )->value.str.val, OP1_VAL( OpLine )->value.str.len );
            }
        }
        else
        {
            make_printable_zval_ex( OP1_VAL( OpLine ), &Stack->Buffer, 0 );
        }

        /* Postfix */
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushS( &Stack->Buffer, Stack->EndChar, Stack->EndCharLength );

        RetCode = StackPopAllS( &Stack->Buffer, &String );
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            dump_string( Stack, String );
        else if ( TEST_OPR_ALL_VAR( OpLine ) )
            UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, Stack->InternalFlags & DS_IFLAGS_OT_MASK );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_fetch_dim_unset( PDUMP_STACK Stack )
{
    UNREFERENCED_PARAMETER( Stack );
    return 0;
}

ULONG FASTCALL dump_fetch_obj_unset( PDUMP_STACK Stack )
{
    UNREFERENCED_PARAMETER( Stack );
    return 0;
}

ULONG FASTCALL dump_fetch_constant( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG OpType;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        if ( TEST_OP1_CONST( OpLine ) )
        {
            if ( GET_GS( )->ExtensionId < EXTENSION_ID_2 )
            {
                make_printable_zval_ex( OP1_VAL( OpLine ), &Stack->Buffer, 0 );
            }
            else
            {
                Var = FindVariableById( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
                if ( Var == NULL )
                {
                    make_printable_zval_ex( OP1_VAL( OpLine ), &Stack->Buffer, 0 );
                }
                else
                {
                    StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
                    StackPushS( &Stack->Buffer, _T( "::" ), 2 );
                    StackPushS( &Stack->Buffer, OP2_VAL( OpLine )->value.str.val, OP2_VAL( OpLine )->value.str.len );
                }
            }
        }
        else if ( TEST_OP2_CONST( OpLine ) )
        {
            make_printable_zval_ex( OP2_VAL( OpLine ), &Stack->Buffer, 0 );
        }

        /* Op type */
        if ( Stack->State & DS_STATE_SILENCE )
            OpType = Stack->InternalFlags & DS_IFLAGS_OT_MASK | VE_FLAGS_SILENCE;
        else
            OpType = Stack->InternalFlags & DS_IFLAGS_OT_MASK;

        /* Prefix */
        if ( Stack->State & DS_STATE_SILENCE && OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushPrefixS( &Stack->Buffer, Stack->StartChar, Stack->StartCharLength );

        /* Postfix */
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushS( &Stack->Buffer, Stack->EndChar, Stack->EndCharLength );

        RetCode = StackPopAllExS( &Stack->Buffer, &String );
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            dump_string( Stack, String );
        else if ( TEST_OPR_ALL_VAR( OpLine ) )
            UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, OpType );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_declare_function_or_class( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG Indent;
    zend_op *OpLine;
    TCHAR *String;
    TCHAR *String1;

    RetCode = 0;
    OpLine = Stack->OpLine;
    if ( TEST_OP2_CONST( OpLine ) && OP2_VAL_TYPE( OpLine ) == IS_STRING )
    {
        StackPushS( &Stack->Buffer, OP2_VAL( OpLine )->value.str.val, OP2_VAL( OpLine )->value.str.len );
        RetCode = StackPopAllS( &Stack->Buffer, &String );
        GET_INDENT( Stack, &Indent );
        switch ( OP_EX_VALUE( OpLine ) )
        {
        case ZEND_DECLARE_FUNCTION :
            dump_function( GET_GS_FUNCTION_TABLE( ), String, RetCode, Indent );
            break;

        case ZEND_DECLARE_CLASS :
            dump_class( GET_GS_CLASS_TABLE( ), String, RetCode, NULL, 0, NULL, 0, Indent );
            break;

        case ZEND_DECLARE_INHERITED_CLASS :
            String1 = _tcsrchr( String, _T( ':' ) );
            if ( String1 )
            {
                *String1++ = _T( '\0' );
                dump_class( GET_GS_CLASS_TABLE( ), String1, String + RetCode - String1, String, String1 - String - 1, NULL, 0, Indent );
            }
            break;
        }
    }

    return RetCode;
}

ULONG FASTCALL dump_throw( PDUMP_STACK Stack )
{
    ULONG RetCode;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
        if ( Var == NULL )
            break;

        StackPushS( &Stack->Buffer, Stack->OpString, _tcslen( Stack->OpString ) );
        StackPushS( &Stack->Buffer, _T( " " ), 1 );
        StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
        StackPushS( &Stack->Buffer, Stack->EndChar, Stack->EndCharLength );
        RetCode = StackPopAllS( &Stack->Buffer, &String );
        dump_string( Stack, String );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_fetch_class( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG Dummy;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    TCHAR *String;
    TCHAR *String1;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        if ( TEST_OP2_CONST( OpLine ) )
        {
            /* Class name */
            decode_obfuscate_class_name( &Stack->Buffer, OP2_VAL( OpLine )->value.str.val, OP2_VAL( OpLine )->value.str.len );
            Dummy = StackPopAllS( &Stack->Buffer, &String );
            String1 = String;
        }
        else if ( TEST_OP2_ALL_VAR( OpLine ) )
        {
            Var = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
            if ( Var == NULL )
                break;

            String = Var->Expr;
            Dummy = Var->ExprLength;
            String1 = NULL;
        }
        else
        {
            if ( OP_EX_VALUE( OpLine ) == ZEND_FETCH_CLASS_SELF )
            {
                /* Self */
                StackPushS( &Stack->Buffer, DEFAULT_CLASS_SELF, DEFAULT_CLASS_SELF_LENGTH );
                Dummy = StackPopAllS( &Stack->Buffer, &String );
                String1 = String;
            }
            else if ( OP_EX_VALUE( OpLine ) == ZEND_FETCH_CLASS_PARENT )
            {
                /* Parent */
                StackPushS( &Stack->Buffer, DEFAULT_CLASS_PARENT, DEFAULT_CLASS_PARENT_LENGTH );
                Dummy = StackPopAllS( &Stack->Buffer, &String );
                String1 = String;
            }
            else
            {
                break;
            }
        }
        UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, String1, String, 0 );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_clone( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG OpType;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        if ( GET_GS( )->ExtensionId < EXTENSION_ID_2 )
        {
            Var = FindVariableById( IS_FUNCTION, OP1_VAR( OpLine ) );
            if ( Var == NULL )
                break;

            /* Function name */
            StackPushS( &Stack->Buffer, Var->Name, Var->NameLength );

            /* Pop argument list */
            PopArgumentList( Stack, OP_EX_VALUE( OpLine ) );
        }
        else
        {
            Var = FindVariableById( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                break;

            /* Key word */
            StackPushS( &Stack->Buffer, _T( "clone " ), 6 );

            /* Variable name */
            StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
        }

        /* Op type */
        OpType = ( Stack->InternalFlags & DS_IFLAGS_OT_MASK ) | VE_FLAGS_FUNCTION;

        /* Prefix */
        if ( Stack->State & DS_STATE_SILENCE && OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushPrefixS( &Stack->Buffer, Stack->StartChar, Stack->StartCharLength );

        /* Postfix */
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushS( &Stack->Buffer, Stack->EndChar, Stack->EndCharLength );

        RetCode = StackPopAllExS( &Stack->Buffer, &String );
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            dump_string( Stack, String );
        else if ( TEST_OPR_ALL_VAR( OpLine ) )
            UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, OpType );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_init_ctor_call( PDUMP_STACK Stack )
{
    StackPushU( &Stack->InitCall, Stack->Offset );
    return 0;
}

ULONG FASTCALL dump_init_method_call( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG RVar;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    PVARIABLE_ENTRY Var1;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    RVar = OPR_VAR( OpLine );
    do
    {
        StackPushU( &Stack->InitCall, Stack->Offset );
        if ( TEST_OP1_CONST( OpLine ) )
        {
            /* BUG */
            break;
        }
        else if ( TEST_OP1_ALL_VAR( OpLine ) )
        {
            Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                break;

            /* class->function */
            if ( TEST_OP2_CONST( OpLine ) )
            {
                StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
                StackPushS( &Stack->Buffer, _T( "->" ), 2 );
                decode_obfuscate_function_name( &Stack->Buffer, OP2_VAL( OpLine )->value.str.val, OP2_VAL( OpLine )->value.str.len );
            }
            else if ( TEST_OP2_ALL_VAR( OpLine ) )
            {
                Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
                if ( Var1 == NULL )
                    break;

                StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
                StackPushS( &Stack->Buffer, _T( "->" ), 2 );
                StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
            }
            else
            {
                /* BUG */
            }
        }
        else
        {
            /* $this->function */
            if ( TEST_OP2_CONST( OpLine ) )
            {
                StackPushS( &Stack->Buffer, DEFAULT_CLASS_THIS_P, DEFAULT_CLASS_THIS_P_LENGTH );
                decode_obfuscate_function_name( &Stack->Buffer, OP2_VAL( OpLine )->value.str.val, OP2_VAL( OpLine )->value.str.len );
            }
            else if ( TEST_OP2_ALL_VAR( OpLine ) )
            {
                Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
                if ( Var1 == NULL )
                    break;

                StackPushS( &Stack->Buffer, DEFAULT_CLASS_THIS_P, DEFAULT_CLASS_THIS_P_LENGTH );
                StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
            }
            else
            {
                /* BUG */
                break;
            }
        }

        RetCode = StackPopAllS( &Stack->Buffer, &String );
        if ( OPR_TYPE( OpLine ) == IS_UNUSED )
            UpdateVariableEx( OPR_TYPE( OpLine ), RVar, Stack->Offset, NULL, String, Stack->InternalFlags & DS_IFLAGS_OT_MASK );
        UpdateVariableEx( OPR_TYPE( OpLine ), Stack->Offset | IS_SPECIFIC_ID, Stack->Offset, NULL, String, Stack->InternalFlags & DS_IFLAGS_OT_MASK );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_static_method_call( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG RVar;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    PVARIABLE_ENTRY Var1;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    RVar = OPR_VAR( OpLine );
    do
    {
        StackPushU( &Stack->InitCall, Stack->Offset );
        if ( TEST_OP1_CONST( OpLine ) )
        {
            /* Used for class_name::function */
            Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                break;

            /* Used for class_name::function */
            StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
            StackPushS( &Stack->Buffer, _T( "::" ), 2 );
            if ( TEST_OP2_CONST( OpLine ) )
            {
                decode_obfuscate_function_name( &Stack->Buffer, OP2_VAL( OpLine )->value.str.val, OP2_VAL( OpLine )->value.str.len );
            }
            else if ( TEST_OP2_ALL_VAR( OpLine ) )
            {
                Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
                if ( Var1 == NULL )
                    break;

                StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
            }
            else
            {
                /* BUG */
                break;
            }
        }
        else if ( TEST_OP1_ALL_VAR( OpLine ) )
        {
            Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                break;

            /* Used for class_name::function */
            StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
            StackPushS( &Stack->Buffer, _T( "::" ), 2 );
            if ( TEST_OP2_CONST( OpLine ) )
            {
                decode_obfuscate_function_name( &Stack->Buffer, OP2_VAL( OpLine )->value.str.val, OP2_VAL( OpLine )->value.str.len );
            }
            else if ( TEST_OP2_ALL_VAR( OpLine ) )
            {
                Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
                if ( Var1 == NULL )
                    break;

                StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
            }
            else
            {
                /* This function */
                StackPushS( &Stack->Buffer, get_function_name( ), get_function_name_length( ) );
            }
        }
        else
        {
            /* BUG */
            break;
        }

        RetCode = StackPopAllS( &Stack->Buffer, &String );
        if ( OPR_TYPE( OpLine ) == IS_UNUSED )
            UpdateVariableEx( OPR_TYPE( OpLine ), RVar, Stack->Offset, NULL, String, Stack->InternalFlags & DS_IFLAGS_OT_MASK );
        UpdateVariableEx( OPR_TYPE( OpLine ), Stack->Offset | IS_SPECIFIC_ID, Stack->Offset, NULL, String, Stack->InternalFlags & DS_IFLAGS_OT_MASK );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_assign_obj( PDUMP_STACK Stack )
{
    ULONG RetCode;
    zend_op *OpLine;
    zend_op *OpLine1;
    PVARIABLE_ENTRY Var;
    PVARIABLE_ENTRY Var1;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        if ( TEST_OP1_ALL_VAR( OpLine ) )
        {
            Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                break;

            if ( TEST_OP2_CONST( OpLine ) )
            {
                StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
                StackPushS( &Stack->Buffer, _T( "->" ), 2 );
                make_printable_zval_url_ex( OP2_VAL( OpLine ), &Stack->Buffer, 0 );
            }
            else if ( TEST_OP2_ALL_VAR( OpLine ) )
            {
                Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
                if ( Var1 == NULL )
                    break;

                StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
                StackPushS( &Stack->Buffer, _T( "->" ), 2 );
                StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
            }
            else
            {
                break;
            }
        }
        else
        {
            if ( TEST_OP2_CONST( OpLine ) )
            {
                StackPushS( &Stack->Buffer, DEFAULT_CLASS_THIS_P, DEFAULT_CLASS_THIS_P_LENGTH );
                make_printable_zval_url_ex( OP2_VAL( OpLine ), &Stack->Buffer, 0 );
            }
            else if ( TEST_OP2_ALL_VAR( OpLine ) )
            {
                Var = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
                if ( Var == NULL )
                    break;

                StackPushS( &Stack->Buffer, DEFAULT_CLASS_THIS_P, DEFAULT_CLASS_THIS_P_LENGTH );
                StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
            }
            else
            {
                break;
            }
        }

        OpLine1 = OpLine + 1;
        /* if ( OP_CODE( OpLine1 ) == ZEND_OP_DATA ) */
        {
            Stack->NextOpLine = OpLine1 + 1;
            StackPushS( &Stack->Buffer, _T( " = " ), 3 );
            if ( TEST_OP1_CONST( OpLine1 ) )
            {
                make_printable_zval_url( OP1_VAL( OpLine1 ), &Stack->Buffer );
            }
            else if ( TEST_OP1_ALL_VAR( OpLine1 ) )
            {
                Var1 = FindInsertVariable( OP1_TYPE( OpLine1 ), OP1_VAR( OpLine1 ) );
                if ( Var1 == NULL )
                    StackSetTopS( &Stack->Buffer, 0 );
                else
                    StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
            }
        }

        /* Prefix */
        if ( Stack->State & DS_STATE_SILENCE && OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushPrefixS( &Stack->Buffer, Stack->StartChar, Stack->StartCharLength );

        /* Postfix */
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushS( &Stack->Buffer, Stack->EndChar, Stack->EndCharLength );

        RetCode = StackPopAllExS( &Stack->Buffer, &String );
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            dump_string( Stack, String );
        else if ( TEST_OPR_ALL_VAR( OpLine ) )
            UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, Stack->InternalFlags & DS_IFLAGS_OT_MASK );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_op_data( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG Dummy;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        if ( TEST_OP1_ALL_VAR( OpLine ) )
        {
            Var = FindVariableById( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                break;

            if ( TEST_OP2_CONST( OpLine ) )
            {
                /* */
                break;
            }
            else if ( TEST_OP2_ALL_VAR( OpLine ) )
            {
                /* */
                break;
            }
            else
            {
                String = Var->Expr;
                Dummy = Var->ExprLength;
            }
        }
        else
        {
            break;
        }
        UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, 0 );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_instanceof( PDUMP_STACK Stack )
{
    ULONG RetCode;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    PVARIABLE_ENTRY Var1;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
        if ( Var == NULL )
            break;

        if ( TEST_OP2_CONST( OpLine ) )
        {
            if ( OP_CODE( OpLine - 1 ) == ZEND_FETCH_CLASS )
            {
                Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
                if ( Var1 == NULL )
                    break;

                StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
                StackPushS( &Stack->Buffer, _T( " " ), 1 );
                StackPushS( &Stack->Buffer, Stack->OpString, _tcslen( Stack->OpString ) );
                StackPushS( &Stack->Buffer, _T( " " ), 1 );
                StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
            }
            else
            {
                StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
                StackPushS( &Stack->Buffer, _T( " " ), 1 );
                StackPushS( &Stack->Buffer, Stack->OpString, _tcslen( Stack->OpString ) );
                StackPushS( &Stack->Buffer, _T( " " ), 1 );
                make_printable_zval_url_ex( OP2_VAL( OpLine ), &Stack->Buffer, 0 );
            }
        }
        else if ( TEST_OP2_ALL_VAR( OpLine ) )
        {
            Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
            if ( Var1 == NULL )
                break;

            StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
            StackPushS( &Stack->Buffer, _T( " " ), 1 );
            StackPushS( &Stack->Buffer, Stack->OpString, _tcslen( Stack->OpString ) );
            StackPushS( &Stack->Buffer, _T( " " ), 1 );
            StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
        }
        else
        {
            break;
        }

        /* Prefix */
        if ( Stack->State & DS_STATE_SILENCE && OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushPrefixS( &Stack->Buffer, Stack->StartChar, Stack->StartCharLength );

        /* Postfix */
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushS( &Stack->Buffer, Stack->EndChar, Stack->EndCharLength );

        RetCode = StackPopAllExS( &Stack->Buffer, &String );
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            dump_string( Stack, String );
        else if ( TEST_OPR_ALL_VAR( OpLine ) )
            UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, Stack->InternalFlags & DS_IFLAGS_OT_MASK );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_declare_class( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG Indent;
    zend_op *OpLine;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    if ( TEST_OP2_CONST( OpLine ) && OP2_VAL_TYPE( OpLine ) == IS_STRING )
    {
        if ( OP_CODE( OpLine + 1 ) == ZEND_FETCH_CLASS && OP_CODE( OpLine + 2 ) == ZEND_ADD_INTERFACE )
        {
            String = OP2_VAL( OpLine )->value.str.val;
            UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, 0 );
        }
        else
        {
            StackPushS( &Stack->Buffer, OP2_VAL( OpLine )->value.str.val, OP2_VAL( OpLine )->value.str.len );
            RetCode = StackPopAllS( &Stack->Buffer, &String );
            GET_INDENT( Stack, &Indent );
            dump_class( GET_GS_CLASS_TABLE( ), String, RetCode, NULL, 0, NULL, 0, Indent );
        }
    }

    return RetCode;
}

ULONG FASTCALL dump_declare_inherited_class( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG Indent;
    zend_op *OpLine;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    if ( TEST_OP2_CONST( OpLine ) && OP2_VAL_TYPE( OpLine ) == IS_STRING )
    {
        if ( OP_CODE( OpLine + 1 ) == ZEND_FETCH_CLASS && OP_CODE( OpLine + 2 ) == ZEND_ADD_INTERFACE )
        {
            String = OP2_VAL( OpLine )->value.str.val;
            UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, 0 );
        }
        else
        {
            StackPushS( &Stack->Buffer, OP2_VAL( OpLine )->value.str.val, OP2_VAL( OpLine )->value.str.len );
            RetCode = StackPopAllS( &Stack->Buffer, &String );
            GET_INDENT( Stack, &Indent );
            dump_class( GET_GS_CLASS_TABLE( ), String, RetCode, NULL, 0, NULL, 0, Indent );
        }
    }

    return RetCode;
}

ULONG FASTCALL dump_declare_function( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG Indent;
    zend_op *OpLine;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    if ( TEST_OP2_CONST( OpLine ) && OP2_VAL_TYPE( OpLine ) == IS_STRING )
    {
        StackPushS( &Stack->Buffer, OP2_VAL( OpLine )->value.str.val, OP2_VAL( OpLine )->value.str.len );
        RetCode = StackPopAllS( &Stack->Buffer, &String );
        GET_INDENT( Stack, &Indent );
        dump_function( GET_GS_FUNCTION_TABLE( ), String, RetCode, Indent );
    }

    return RetCode;
}

ULONG FASTCALL dump_start_namespace( PDUMP_STACK Stack )
{
    UNREFERENCED_PARAMETER( Stack );
    return 0;
}

ULONG FASTCALL dump_add_interface( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG Length;
    ULONG Indent;
    ULONG Dummy;
    zend_op *Head;
    zend_op *OpLine;
    zend_op *OpLine1;
    zend_op *OpLine2;
    PVARIABLE_ENTRY Var;
    PVARIABLE_ENTRY Var1;
    PVARIABLE_ENTRY Var2;
    TCHAR *String;
    TCHAR *String1;

    RetCode = 0;
    Head = Stack->Head;
    OpLine = Stack->OpLine;
    do
    {
        /* Class1 */
        Var = FindVariableById( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
        if ( Var == NULL )
            break;

        /* Class3 */
        Var1 = FindVariableById( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
        if ( Var1 == NULL )
            break;

        StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
        OpLine1 = OpLine + 1;
        while ( OP_CODE( OpLine1 + 1 ) == ZEND_DECLARE_CLASS &&
            OP_CODE( OpLine1 + 2 ) == ZEND_FETCH_CLASS &&
            OP_CODE( OpLine1 + 3 ) == ZEND_ADD_INTERFACE )
        {
            StackPushS( &Stack->Buffer, _T( ", " ), 2 );
            OpLine2 = OpLine1 + 2;
            StackPushS( &Stack->Buffer, OP2_VAL( OpLine2 )->value.str.val, OP2_VAL( OpLine2 )->value.str.len );
            OpLine1 += 4;
        }
        /* Pop up interface */
        Length = StackPopAllS( &Stack->Buffer, &String1 );
        /* Skip */
        Stack->NextOpLine = OpLine1;

        OpLine1 = OpLine - 2;
        if ( OpLine1 > Head && OP_CODE( OpLine1 ) == ZEND_USER_OPCODE )
        {
            /* Class2 */
            Var2 = FindVariableById( OPR_TYPE( OpLine1 ), OpLine1->extended_value );
            if ( Var2 == NULL )
                break;

            String = Var2->Expr;
            Dummy = Var2->ExprLength;
        }
        else
        {
            String = NULL;
            Dummy = 0;
        }

        /* Class1 [extends class2] implements class3 */
        GET_INDENT( Stack, &Indent );
        dump_class( GET_GS_CLASS_TABLE( ), Var->Expr, Var->ExprLength, String, Dummy, String1, Length, Indent );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_assign_dim( PDUMP_STACK Stack )
{
    ULONG RetCode;
    zend_op *OpLine;
    zend_op *OpLine1;
    PVARIABLE_ENTRY Var;
    PVARIABLE_ENTRY Var1;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        if ( TEST_OP1_ALL_VAR( OpLine ) )
        {
            Var = FindInsertVariable( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                break;

            if ( TEST_OP2_CONST( OpLine ) )
            {
                StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
                StackPushS( &Stack->Buffer, _T( "[" ), 1 );
                make_printable_zval_url_ex( OP2_VAL( OpLine ), &Stack->Buffer, _T( '\'' ) );
                StackPushS( &Stack->Buffer, _T( "]" ), 1 );
            }
            else if ( TEST_OP2_ALL_VAR( OpLine ) )
            {
                Var1 = FindInsertVariable( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
                if ( Var1 == NULL )
                    break;

                StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
                StackPushS( &Stack->Buffer, _T( "[" ), 1 );
                StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
                StackPushS( &Stack->Buffer, _T( "]" ), 1 );
            }
            else
            {
                StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
                StackPushS( &Stack->Buffer, _T( "[]" ), 2 );
            }
        }
        else
        {
            break;
        }

        OpLine1 = OpLine + 1;
        /* if ( OP_CODE( OpLine1 ) == ZEND_OP_DATA ) */
        {
            Stack->NextOpLine = OpLine1 + 1;
            StackPushS( &Stack->Buffer, _T( " = " ), 3 );
            if ( TEST_OP1_CONST( OpLine1 ) )
            {
                make_printable_zval_url( OP1_VAL( OpLine1 ), &Stack->Buffer );
            }
            else if ( TEST_OP1_ALL_VAR( OpLine1 ) )
            {
                Var1 = FindInsertVariable( OP1_TYPE( OpLine1 ), OP1_VAR( OpLine1 ) );
                if ( Var1 == NULL )
                    StackSetTopS( &Stack->Buffer, 0 );
                else
                    StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
            }
        }

        /* Prefix */
        if ( Stack->State & DS_STATE_SILENCE && OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushPrefixS( &Stack->Buffer, Stack->StartChar, Stack->StartCharLength );

        /* Postfix */
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushS( &Stack->Buffer, Stack->EndChar, Stack->EndCharLength );

        RetCode = StackPopAllExS( &Stack->Buffer, &String );
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            dump_string( Stack, String );
        else if ( TEST_OPR_ALL_VAR( OpLine ) )
            UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, Stack->InternalFlags & DS_IFLAGS_OT_MASK );
    } while ( 0 );

    return RetCode;
}

ULONG FASTCALL dump_user_opcode( PDUMP_STACK Stack )
{
    ULONG RetCode;
    ULONG OpType;
    ULONG Indent;
    ULONG Dummy;
    zend_op *OpLine;
    PVARIABLE_ENTRY Var;
    PVARIABLE_ENTRY Var1;
    TCHAR *String;

    RetCode = 0;
    OpLine = Stack->OpLine;
    do
    {
        if ( Stack->OrgOpCode )
            Dummy = Stack->OrgOpCode[Stack->Offset];
        else
            Dummy = OP_CODE( OpLine );
        /* 205 E12A60-> */
        /* 200 E12A60->Function */
        /* 140 E12C90->Class */
        /* 206 E12D00->Unset? */
        if ( Dummy == 205 )
        {
            StackPushU( &Stack->InitCall, Stack->Offset );
            break;
        }
        else if ( Dummy == 140 )
        {
            if ( OP_CODE( OpLine + 1 ) == ZEND_FETCH_CLASS && OP_CODE( OpLine + 2 ) == ZEND_ADD_INTERFACE )
            {
                /* Class1 extends class2 implements class3 */
                String = OP2_VAL( OpLine )->value.str.val;
                UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, Stack->InternalFlags & DS_IFLAGS_OT_MASK );
            }
            else
            {
                /* Class1 extends class2 */
                if ( Stack->Offset && OP_CODE( OpLine - 1 ) == ZEND_FETCH_CLASS )
                    Var1 = FindVariableById( OPR_TYPE( OpLine - 1 ), OPR_VAR( OpLine - 1 ) );
                else
                    Var1 = FindVariableById( OPR_TYPE( OpLine ), OP_EX_VALUE( OpLine ) );
                if ( Var1 == NULL )
                {
                    String = NULL;
                    Dummy = 0;
                }
                else
                {
                    String = Var1->Expr;
                    Dummy = Var1->ExprLength;
                }

                GET_INDENT( Stack, &Indent );
                dump_class( GET_GS_CLASS_TABLE( ), OP2_VAL( OpLine )->value.str.val, OP2_VAL( OpLine )->value.str.len, String, Dummy, NULL, 0, Indent );
            }
            break;
        }
        else if ( Dummy == 206 )
        {
            Var = FindVariableById( OP1_TYPE( OpLine ), OP1_VAR( OpLine ) );
            if ( Var == NULL )
                break;

            StackPushS( &Stack->Buffer, _T( "unset( " ), 7 );
            StackPushS( &Stack->Buffer, Var->Expr, Var->ExprLength );
            StackPushS( &Stack->Buffer, _T( "[" ), 1 );
            if ( TEST_OP2_CONST( OpLine ) )
            {
                make_printable_zval_url_ex( OP2_VAL( OpLine ), &Stack->Buffer, _T( '\'' ) );
            }
            else if ( TEST_OP2_ALL_VAR( OpLine ) )
            {
                Var1 = FindVariableById( OP2_TYPE( OpLine ), OP2_VAR( OpLine ) );
                if ( Var1 == NULL )
                    break;

                StackPushS( &Stack->Buffer, Var1->Expr, Var1->ExprLength );
            }
            StackPushS( &Stack->Buffer, _T( "] )" ), 3 );

            /* Prefix */
            if ( Stack->State & DS_STATE_SILENCE )
                StackPushS( &Stack->Buffer, Stack->StartChar, Stack->StartCharLength );

            /* Postfix */
            StackPushS( &Stack->Buffer, Stack->EndChar, Stack->EndCharLength );

            RetCode = StackPopAllS( &Stack->Buffer, &String );
            dump_string( Stack, String );
            break;
        }

        Var = FindVariableById( IS_FUNCTION, OP1_VAR( OpLine ) );
        if ( Var == NULL )
            break;

        /* Op type */
        OpType = ( Stack->InternalFlags & DS_IFLAGS_OT_MASK ) | VE_FLAGS_FUNCTION;

        /* Prefix */
        if ( Stack->State & DS_STATE_SILENCE && OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushS( &Stack->Buffer, Stack->StartChar, Stack->StartCharLength );

        /* Function name */
        StackPushS( &Stack->Buffer, Var->Name, Var->NameLength );

        /* Pop argument list */
        PopArgumentList( Stack, OP_EX_VALUE( OpLine ) );

        /* Postfix */
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            StackPushS( &Stack->Buffer, Stack->EndChar, Stack->EndCharLength );

        RetCode = StackPopAllS( &Stack->Buffer, &String );
        if ( OPR_EA_TYPE( OpLine ) & EXT_TYPE_UNUSED )
            dump_string( Stack, String );
        else if ( TEST_OPR_ALL_VAR( OpLine ) )
            UpdateVariableEx( OPR_TYPE( OpLine ), OPR_VAR( OpLine ), Stack->Offset, NULL, String, OpType );
    } while ( 0 );

    return RetCode;
}

/*
///////////////////////////////////////////////////////////////////////////////
// dump_opcode
///////////////////////////////////////////////////////////////////////////////
*/
ULONG dump_opcode( PDUMP_STACK Stack )
{
    ULONG RetCode;
    register ULONG Offset;
    ULONG NextOffset;
    register zend_op *OpLine;
    static DUMP_HANDLER DumpHandlers[] = {
        NULL, /* 000 NOP */
        dump_two_op_function, /* 001 ADD */
        dump_two_op_function, /* 002 SUB */
        dump_two_op_function, /* 003 MUL */
        dump_two_op_function, /* 004 DIV */
        dump_two_op_function, /* 005 MOD */
        dump_two_op_function, /* 006 SL */
        dump_two_op_function, /* 007 SR */
        dump_two_op_function, /* 008 CONCAT */
        dump_two_op_function, /* 009 BW_OR */
        dump_two_op_function, /* 010 BW_AND */
        dump_two_op_function, /* 011 BW_XOR */
        dump_two_op_function, /* 012 BW_NOT */
        dump_bool_not, /* 013 BOOL_NOT */
        dump_two_op_function, /* 014 BOOL_XOR */
        dump_two_op_function, /* 015 IS_IDENTICAL */
        dump_two_op_function, /* 016 IS_NOT_IDENTICAL */
        dump_two_op_function, /* 017 IS_EQUAL */
        dump_two_op_function, /* 018 IS_NOT_EQUAL */
        dump_two_op_function, /* 019 IS_SMALLER */
        dump_two_op_function, /* 020 IS_SMALLER_OR_EQUAL */
        dump_cast, /* 021 CAST */
        dump_qm_assign, /* 022 QM_ASSIGN */
        dump_assign_function, /* 023 ASSIGN_ADD */
        dump_assign_function, /* 024 ASSIGN_SUB */
        dump_assign_function, /* 025 ASSIGN_MUL */
        dump_assign_function, /* 026 ASSIGN_DIV */
        dump_assign_function, /* 027 ASSIGN_MOD */
        dump_assign_function, /* 028 ASSIGN_SL */
        dump_assign_function, /* 029 ASSIGN_SR */
        dump_assign_function, /* 030 ASSIGN_CONCAT */
        dump_assign_function, /* 031 ASSIGN_BW_OR */
        dump_assign_function, /* 032 ASSIGN_BW_AND */
        dump_assign_function, /* 033 ASSIGN_BW_XOR */
        dump_two_op_function, /* 034 PRE_INC */
        dump_two_op_function, /* 035 PRE_DEC */
        dump_two_op_function, /* 036 POST_INC */
        dump_two_op_function, /* 037 POST_DEC */
        dump_assign_function, /* 038 ASSIGN */
        dump_assign_function, /* 039 ASSIGN_REF */
        dump_echo, /* 040 ECHO */
        dump_print, /* 041 PRINT */
        NULL, /* 042 JMP */
        dump_jmpx, /* 043 JMPZ */
        dump_jmpx, /* 044 JMPNZ */
        NULL, /* 045 JMPZNZ */
        dump_jmpx_ex, /* 046 JMPZ_EX */
        dump_jmpx_ex, /* 047 JMPNZ_EX */
        NULL, /* 048 CASE */
        dump_switch_free, /* 049 SWITCH_FREE */
        dump_brk, /* 050 BRK */
        dump_cont, /* 051 CONT */
        dump_bool, /* 052 BOOL */
        dump_init_string, /* 053 INIT_STRING */
        dump_add_char, /* 054 ADD_CHAR */
        dump_add_string, /* 055 ADD_STRING */
        dump_add_var, /* 056 ADD_VAR */
        dump_begin_silence, /* 057 BEGIN_SILENCE */
        dump_end_silence, /* 058 END_SILENCE */
        dump_init_fcall_by_name, /* 059 INIT_FCALL_BY_NAME */
        dump_do_fcall, /* 060 DO_FCALL */
        dump_do_fcall_by_name, /* 061 DO_FCALL_BY_NAME */
        dump_return, /* 062 RETURN */
        dump_recv, /* 063 RECV */
        dump_recv_init, /* 064 RECV_INIT */
        dump_send_x, /* 065 SEND_VAL */
        dump_send_x, /* 066 SEND_VAR */
        dump_send_x, /* 067 SEND_REF */
        dump_new, /* 068 NEW */
        NULL, /* 069 JMP_NO_CTOR */
        dump_free, /* 070 FREE */
        dump_init_array, /* 071 INIT_ARRAY */
        dump_add_element, /* 072 ADD_ARRAY_ELEMENT */
        dump_include_or_eval, /* 073 INCLUDE_OR_EVAL */
        dump_unset_var, /* 074 UNSET_VAR */
        dump_unset_dim_obj, /* 075 UNSET_DIM_OBJ */
        dump_isset_isempty_x, /* 076 ISSET_ISEMPTY */
        dump_fe_reset, /* 077 FE_RESET */
        dump_fe_fetch, /* 078 FE_FETCH */
        dump_exit, /* 079 EXIT */
        dump_fetch_x, /* 080 FETCH_R */
        dump_fetch_dim_r, /* 081 FETCH_DIM_R */
        dump_fetch_obj_x, /* 082 FETCH_OBJ_R */
        dump_fetch_x, /* 083 FETCH_W */
        dump_fetch_dim_x, /* 084 FETCH_DIM_W */
        dump_fetch_obj_x, /* 085 FETCH_OBJ_W */
        dump_fetch_x, /* 086 FETCH_RW */
        dump_fetch_dim_x, /* 087 FETCH_DIM_RW */
        dump_fetch_obj_x, /* 088 FETCH_OBJ_RW */
        dump_fetch_unset_x, /* 089 FETCH_IS */
        dump_fetch_dim_x, /* 090 FETCH_DIM_IS */
        dump_fetch_obj_x, /* 091 FETCH_OBJ_IS */
        dump_fetch_x, /* 092 FETCH_FUNC_ARG */
        dump_fetch_dim_x, /* 093 FETCH_DIM_FUNC_ARG */
        dump_fetch_obj_x, /* 094 FETCH_OBJ_FUNC_ARG */
        dump_fetch_unset_x, /* 095 FETCH_UNSET */
        dump_fetch_dim_unset, /* 096 FETCH_DIM_UNSET */
        dump_fetch_obj_unset, /* 097 FETCH_OBJ_UNSET */
        dump_fetch_dim_r, /* 098 FETCH_DIM_TMP_VAR */
        dump_fetch_constant, /* 099 FETCH_CONSTANT */
        dump_declare_function_or_class, /* 100 DECLARE_FUNCTION_OR_CLASS */
        NULL, /* 101 EXT_STMT */
        NULL, /* 102 EXT_FCALL_BEGIN */
        NULL, /* 103 EXT_FCALL_END */
        NULL, /* 104 EXT_NOP */
        NULL, /* 105 TICKS */
        dump_send_x, /* 106 SEND_VAR_NO_REF */

        /* Engine 2 */
        NULL, /* 107 CATCH */
        dump_throw, /* 108 THROW */
        dump_fetch_class, /* 109 FETCH_CLASS */
        dump_clone, /* 110 CLONE */
        dump_init_ctor_call, /* 111 INIT_CTOR_CALL */
        dump_init_method_call, /* 112 INIT_METHOD_CALL */
        dump_static_method_call, /* 113 INIT_STATIC_METHOD_CALL */
        dump_isset_isempty_x, /* 114 ISSET_ISEMPTY_VAR */
        dump_isset_isempty_x, /* 115 ISSET_ISEMPTY_DIM_OBJ */
        NULL, /* 116 IMPORT_FUNCTION */
        NULL, /* 117 IMPORT_CLASS */
        NULL, /* 118 IMPORT_CONST */
        NULL, /* 119 119 */
        NULL, /* 120 120 */
        dump_assign_function, /* 121 ASSIGN_ADD_OBJ */
        dump_assign_function, /* 122 ASSIGN_SUB_OBJ */
        dump_assign_function, /* 123 ASSIGN_MUL_OBJ */
        dump_assign_function, /* 124 ASSIGN_DIV_OBJ */
        dump_assign_function, /* 125 ASSIGN_MOD_OBJ */
        dump_assign_function, /* 126 ASSIGN_SL_OBJ */
        dump_assign_function, /* 127 ASSIGN_SR_OBJ */
        dump_assign_function, /* 128 ASSIGN_CONCAT_OBJ */
        dump_assign_function, /* 129 ASSIGN_BW_OR_OBJ */
        dump_assign_function, /* 130 ASSIGN_BW_AND_OBJ */
        dump_assign_function, /* 131 ASSIGN_BW_XOR_OBJ */
        dump_two_op_function, /* 132 PRE_INC_OBJ */
        dump_two_op_function, /* 133 PRE_DEC_OBJ */
        dump_two_op_function, /* 134 POST_INC_OBJ */
        dump_two_op_function, /* 135 POST_DEC_OBJ */
        dump_assign_obj, /* 136 ASSIGN_OBJ */
        dump_op_data, /* 137 OP_DATA */
        dump_instanceof, /* 138 INSTANCEOF */
        dump_declare_class, /* 139 DECLARE_CLASS */
        dump_declare_inherited_class, /* 140 DECLARE_INHERITED_CLASS */
        dump_declare_function, /* 141 DECLARE_FUNCTION */
        NULL, /* 142 RAISE_ABSTRACT_ERROR */
        dump_start_namespace, /* 143 START_NAMESPACE */
        dump_add_interface, /* 144 ADD_INTERFACE */
        NULL, /* 145 VERIFY_INSTANCEOF */
        NULL, /* 146 VERIFY_ABSTRACT_CLASS */
        dump_assign_dim, /* 147 ASSIGN_DIM */
        dump_isset_isempty_x, /* 148 ISSET_ISEMPTY_PROP_OBJ */
        NULL, /* 149 HANDLE_EXCEPTION */
        dump_user_opcode, /* 150 USER_OPCODE */
    };

    RetCode = 0;
    /* See if dump raw op code */
    if ( !( GET_GS_FLAGS( ) & GS_FLAGS_RAW ) )
    {
        Stack->State &= ~( DS_STATE_DONE | DS_STATE_DONE | DS_STATE_NONE );
        Offset = Stack->Offset;
        OpLine = Stack->OpLine;

        /* Dump control statement */
        dump_control_list( Stack );

        /* Skip */
        if ( StackBottomU( &Stack->Skip, &NextOffset ) && NextOffset == Offset )
        {
            do
            {
                StackPopBottomU( &Stack->Skip, NULL );
            } while ( StackBottomU( &Stack->Skip, &NextOffset ) && NextOffset == Offset );
            /* In skip */
            Stack->State |= DS_STATE_SKIP;
        }
        else if ( OpLine >= Stack->NextOpLine )
        {
            if ( OP_CODE( OpLine ) < SIZE_OF_ARRAY( DumpHandlers ) && DumpHandlers[OP_CODE( OpLine )] )
            {
                /* Clean buffer */
                StackReinitS( &Stack->Buffer );
                StackReinitS( &Stack->Buffer1 );
                StackReinitS( &Stack->Buffer2 );

                /* Call to handler */
                RetCode = DumpHandlers[OP_CODE( OpLine )]( Stack );
                /* Done */
                Stack->State |= DS_STATE_DONE;
            }
            else
            {
                /* None */
                Stack->State |= DS_STATE_NONE;
            }
        }
        else
        {
            /* In skip */
            Stack->State |= DS_STATE_SKIP;
        }
    }

    return RetCode;
}

/*
///////////////////////////////////////////////////////////////////////////////
// dump_op_array_ex
///////////////////////////////////////////////////////////////////////////////
*/
void dump_op_array_ex( zend_op_array *OpArray, ULONG Indent, ULONG State )
{
    ULONG Size;
    ULONG ReturnReference;
    ULONG Offset;
    ULONG Flags;
    PDUMP_STACK Stack;
    zend_op *Head;
    zend_op *Tail;
    register zend_op *OpLine;
    register zend_uchar OpCode;
    TCHAR *FunctionName;
    TCHAR *String;

    Stack = AllocateStackFromPool( GET_GS( )->StackSize, GET_GS( )->StackStringLength );
    if ( Stack )
    {
        /* Save to global setting */
        SET_GS_OPARRAY( OpArray );
        SET_GS_STACK( Stack );

        /* Push to */
        PUSH_GS_STACK( );
        PUSH_INDENT( Stack, Indent );

        if ( GET_GS( )->ExtensionId < EXTENSION_ID_2 )
        {
            Head = get_oparray_op_1( OpArray );
            Size = ( ( zend_op_array_1* )OpArray )->last;
            Stack->LastOffset = ( ( zend_op_array_1* )OpArray )->last;
            Stack->ArgInfo = ( ( zend_op_array_1* )OpArray )->arg_types;
            FunctionName = ( ( zend_op_array_1* )OpArray )->function_name;
            ReturnReference = ( ( zend_op_array_1* )OpArray )->return_reference;
        }
        else
        {
            Head = get_oparray_op_2( OpArray );
            Size = ( ( zend_op_array_2* )OpArray )->last;
            Stack->LastOffset = ( ( zend_op_array_2* )OpArray )->last;
            Stack->ArgInfo = ( ( zend_op_array_2* )OpArray )->arg_info;
            FunctionName = ( ( zend_op_array_2* )OpArray )->function_name;
            ReturnReference = ( ( zend_op_array_2* )OpArray )->return_reference;
        }
        Tail = Head + Size;
        Stack->Head = Head;
        Stack->Tail = Tail;
        Stack->State = State;
        Stack->OpArray = OpArray;

        /* Push current function name */
        push_function_name_ex( FunctionName, 0 );

        /* First step */
        Stack->Step++;

        /* Initiate extend information variable and function names */
        InitExtendInfo( Stack );

        /* See if dump only op code */
        if ( !( GET_GS_FLAGS( ) & GS_FLAGS_RAW ) )
            scan_control_list( Stack );

        /* Next step */
        Stack->Step++;

        Flags = 0;
        if ( !( Stack->State & DS_STATE_MAIN ) )
        {
            if ( GET_GS( )->MajorId > EXTENSION_ID_1 )
            {
                if ( StackPopU( &GET_GS( )->FunctionFlags, &Flags ) )
                {
                    switch ( Flags & ZEND_ACC_PPP_MASK )
                    {
                    case ZEND_ACC_PUBLIC :
                        StackPushS( &Stack->LargeBuffer, _T( "public " ), 7 );
                        break;

                    case ZEND_ACC_PROTECTED :
                        StackPushS( &Stack->LargeBuffer, _T( "protected " ), 10 );
                        break;

                    case ZEND_ACC_PRIVATE :
                        StackPushS( &Stack->LargeBuffer, _T( "private " ), 8 );
                        break;
                    }

                    if ( Flags & ZEND_ACC_STATIC )
                        StackPushS( &Stack->LargeBuffer, _T( "static " ), 7 );
                    else if ( Flags & ZEND_ACC_ABSTRACT )
                        StackPushS( &Stack->LargeBuffer, _T( "abstract " ), 9 );
                    else if ( Flags & ZEND_ACC_FINAL )
                        StackPushS( &Stack->LargeBuffer, _T( "final " ), 6 );
                }
            }

            StackPushS( &Stack->LargeBuffer, _T( "function " ), 9 );
            if ( ReturnReference == ZEND_RETURN_REF )
                StackPushS( &Stack->LargeBuffer, _T( "&" ), 1 );
            StackPushS( &Stack->LargeBuffer, get_function_name( ), get_function_name_length( ) );
            if ( Flags & ZEND_ACC_ABSTRACT )
            {
                StackPushS( &Stack->LargeBuffer, _T( "( );\r\n" ), 6 );
                StackPopAllS( &Stack->LargeBuffer, &String );
                dump_string( Stack, String );
            }
            else
            {
                if ( Stack->ArgumentCount == 0 )
                {
                    StackPushS( &Stack->LargeBuffer, _T( "( )\r\n" ), 5 );
                    StackPopAllS( &Stack->LargeBuffer, &String );
                    dump_string( Stack, String );
                    dump_string( Stack, _T( "{\r\n" ) );
                    StackPushU( &Stack->Indent, Indent + GET_GS_INDENT( ) );
                }
                else
                {
                    if ( GET_GS_FLAGS( ) & GS_FLAGS_DETAIL )
                        StackPushS( &Stack->LargeBuffer, _T( "(\r\n" ), 3 );
                    else
                        StackPushS( &Stack->LargeBuffer, _T( "( " ), 2 );
                    StackPopAllS( &Stack->LargeBuffer, &String );
                    dump_string( Stack, String );
                }
            }
        }

        /* Next step */
        Stack->Step++;

        /* Last scan */
        for ( OpLine = Head, Offset = 0; OpLine < Tail; OpLine++, Offset++ )
        {
            OpCode = OP_CODE( OpLine );
            Stack->Offset = Offset;
            Stack->OpLine = OpLine;
            if ( OpCode >= GET_OP_TABLE_ARRAY_SIZE( ) )
            {
                Stack->InternalFlags = DS_IFLAGS_UNKNOWN_OP;
                Stack->OpName = _T( "?" );
                Stack->OpString = _T( "" );
            }
            else
            {
                Stack->InternalFlags = GET_OP_TABLE( OpCode ).Flags;
                Stack->OpName = GET_OP_TABLE( OpCode ).OpName;
                Stack->OpString = GET_OP_TABLE( OpCode ).Op;
            }
            dump_opcode( Stack );
            if ( GET_GS_FLAGS( ) & GS_FLAGS_DETAIL )
                dump_opcode_detail( Stack );
        }
        /* Add a virtual op code since control list may not empty yet */
        SET_OP_CODE( &Stack->LocalOpLine, ZEND_NOP );
        Stack->InternalFlags = GET_OP_TABLE( ZEND_NOP ).Flags;
        Stack->OpName = GET_OP_TABLE( ZEND_NOP ).OpName;
        Stack->OpString = GET_OP_TABLE( ZEND_NOP ).Op;
        Stack->OpLine = &Stack->LocalOpLine;
        Stack->Offset = Stack->LastOffset;
        dump_opcode( Stack );

        /* Last step */
        Stack->Step++;

        /* Pop up indent */
        POP_INDENT( Stack );

        if ( !( Stack->State & DS_STATE_MAIN ) )
        {
            if ( !( Flags & ZEND_ACC_ABSTRACT ) )
                dump_string( Stack, _T( "}\r\n" ) );
        }

        /* Un-initiate extend information */
        UninitExtendInfo( Stack );

        /* Free stack to pool */
        FreeStackToPool( Stack );

        /* Pop function name */
        pop_function_name( );

        /* Pop up stack */
        POP_SET_GS_STACK( );
    }
}

ULONG HookImportTable(
    IN HMODULE hModule,
    IN LPVOID lpProcAddress,
    IN LPVOID lpProcAddressHook
    )
{
    ULONG ModuleBase;
    ULONG Size;
    PIMAGE_DOS_HEADER DosHeader;
    PIMAGE_NT_HEADERS NtHeaders;
    PIMAGE_DATA_DIRECTORY DataDirectory;
    PIMAGE_IMPORT_DESCRIPTOR ImportDesc;
    PIMAGE_IMPORT_DESCRIPTOR ImportDescEnd;
    PIMAGE_THUNK_DATA ThunkData;

    __try
    {
        ModuleBase = ( ULONG )hModule;
        if ( ModuleBase == 0 )
            __leave;

        DosHeader = ( PIMAGE_DOS_HEADER ) ( ModuleBase );
        NtHeaders = ( PIMAGE_NT_HEADERS ) ( ModuleBase + DosHeader->e_lfanew );
        if ( NtHeaders->Signature != IMAGE_NT_SIGNATURE )
            __leave;

        DataDirectory = &NtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
        Size = DataDirectory->Size;
        ImportDesc = ( PIMAGE_IMPORT_DESCRIPTOR ) ( ModuleBase + DataDirectory->VirtualAddress );
        ImportDescEnd = ImportDesc + Size;
        for ( ; ImportDesc < ImportDescEnd; ImportDesc++ )
        {
            ThunkData = ( PIMAGE_THUNK_DATA ) ( ModuleBase + ImportDesc->FirstThunk );
            for ( ; ThunkData->u1.Function; ThunkData++ )
            {
                if ( lpProcAddress == ( LPVOID )ThunkData->u1.Function )
                {
                    /* ThunkData->u1.Function = lpProcAddressHook; */
                    WriteProcessMemory( GetCurrentProcess( ), &ThunkData->u1.Function, &lpProcAddressHook, sizeof( LPVOID ), NULL );
                    return TRUE;
                }
            }
        }
    }
    __except( EXCEPTION_EXECUTE_HANDLER )
    {
    }

    return FALSE;
}

VOID WINAPI GetSystemTimeAsFileTimeHook(
    LPFILETIME lpSystemTimeAsFileTime
    )
{
    static FILETIME StartTime = { ( ULONG )- 1, ( ULONG )- 1 };

    if ( StartTime.dwHighDateTime == - 1 && StartTime.dwLowDateTime == - 1 )
    {
        GetSystemTimeAsFileTime( &StartTime );
        *lpSystemTimeAsFileTime = GET_GS( )->FakeTime;
    }
    else
    {
        GetSystemTimeAsFileTime( lpSystemTimeAsFileTime );
    }

#ifdef _MSC_VER
    do
    {
        PGLOBAL_SETTING Setting;
        ULONG ExtensionModuleBase;
        ULONG Address;
        ULONG Dummy;

        Setting = GET_GS( );
        ExtensionModuleBase = ( ULONG )Setting->ExtensionModuleBase;
        if ( ExtensionModuleBase == 0 )
        {
            DECODE_STR( Dummy, Setting->ExtensionModuleName );
            ExtensionModuleBase = ( ULONG )GetModuleHandle( Setting->ExtensionModuleName );
            ENCODE_STR( Dummy, Setting->ExtensionModuleName );
            if ( ExtensionModuleBase == 0 )
                break;

            Setting->ExtensionModuleBase = ( void* )ExtensionModuleBase;
        }

        /* Get function time( ... ) return address */
        Address = *( ( ULONG* )&lpSystemTimeAsFileTime + sizeof( void* ) );
        /* Return address MUST be in extension module range */
        if ( ExtensionModuleBase < Address && Address < ExtensionModuleBase + Setting->ExtensionModuleSize )
        {
            if ( *( ( ULONG* )Address ) == Setting->HookTimeSignature )
            {
                if ( Setting->ExtensionId < EXTENSION_ID_2 )
                {
                    /* Modify register(esi) in stack to minimum integer */
                    __asm mov dword ptr [esp + 4], 0x80000000
                }
                else
                {
                    /* Modify register(edi) in stack to maximum unsigned integer */
                    __asm mov dword ptr [esp], 0xFFFFFFFF
                }
            }
            else if ( GET_GS_FLAGS( ) & GS_FLAGS_BUG )
            {
                _tprintf( _T( "[F]time" ) );
            }
        }
    } while ( 0 );
#endif
}

void HookTime( )
{
    ULONG Dummy;
    /* 1601-1-1 */
    SYSTEMTIME FakeTime = { 1601, 1, 1, 1, 0, 0, 0, 0 };
    SYSTEMTIME CurrentTime;
    FILETIME FakeFileTime;

    /* Get current time */
    GetLocalTime( &CurrentTime );
    FakeTime.wHour = CurrentTime.wHour;
    FakeTime.wMinute = CurrentTime.wMinute;
    FakeTime.wSecond = CurrentTime.wSecond;
    FakeTime.wMilliseconds = CurrentTime.wMilliseconds;

    /* Find the first date and correspond day Of week */
    do
    {
        FakeTime.wYear--;
    } while ( SystemTimeToFileTime( &FakeTime, &FakeFileTime ) );

    do
    {
        FakeTime.wYear++;
    } while ( !SystemTimeToFileTime( &FakeTime, &FakeFileTime ) );

    /* Translate back to */
    FileTimeToSystemTime( &FakeFileTime, &FakeTime );

    /* Translate to file time */
    SystemTimeToFileTime( &FakeTime, &GET_GS( )->FakeTime );

    DECODE_STR( Dummy, GET_GS( )->HookTimeModuleName );
    if ( HookImportTable( GetModuleHandle( GET_GS( )->HookTimeModuleName ), GetSystemTimeAsFileTime, GetSystemTimeAsFileTimeHook ) )
        GET_GS_FLAGS( ) |= GS_IFLAGS_HOOK_TIME;
    ENCODE_STR( Dummy, GET_GS( )->HookTimeModuleName );
}

void PatchLicenseCallback( ULONG Index, PVOID PatchAddress, PVOID PatchData, ULONG PatchDataSize, PVOID Context )
{
    UNREFERENCED_PARAMETER( Index );
    UNREFERENCED_PARAMETER( Context );

    WriteProcessMemory( GetCurrentProcess( ), PatchAddress, PatchData, PatchDataSize, NULL );
}

void PatchLicense( )
{
    static UCHAR Patch1[] = { 0x3B, 0xF5, 0x75, 0x65, 0x39, 0x6F, 0x0C };
    static ULONG PatchOffset1[] = { 0x438c0, }; /* [3.24]Php5 */
    static ULONG PatchOffset2[] = { 0x15480, }; /* [3.24]Php4 */
    static ULONG PatchOffset3[] = { 0xF220, }; /* [3.30]Php5 */
    static ULONG PatchOffset4[] = { 0x15530, }; /* [3.30]Php4 */
    static PATCH_ARRAY PatchArray[] = {
        { Patch1, sizeof( Patch1 ), NULL, 2, "\xEB", 1 }, /* JC->JMP */
    };
    static ULONG *PatchOffsetArray[] = {
        PatchOffset1,
        PatchOffset2,
        PatchOffset3,
        PatchOffset4,
    };

    if ( GET_GS( )->ExtensionModuleBase != NULL )
        PatchMemory( PatchLicenseCallback, NULL, GET_GS( )->ExtensionModuleBase, 0xED000, PatchArray, SIZE_OF_ARRAY( PatchArray ), PatchOffsetArray, SIZE_OF_ARRAY( PatchOffsetArray ) );
}

ULONG CreateDirectoryRecursive( LPTSTR Path, LPTSTR SubPath )
{
    ULONG RetCode;
    LPTSTR Start;
    LPTSTR Next;
    LPTSTR Out;
    TCHAR Buffer[MAX_PATH];

    RetCode = TRUE;
    _tcscpy( Buffer, Path );
    Out = Buffer + _tcslen( Buffer );
    Start = SubPath;
    while ( Next = _tcschr( Start, _T( '\\' ) ) )
    {
        *Out++ = _T( '\\' );
        _tcsncpy( Out, Start, Next - Start );
        Out += Next - Start;
        *Out = _T( '\0' );
        if ( !CreateDirectory( Buffer, NULL ) && GetLastError( ) != ERROR_ALREADY_EXISTS )
            break;

        Start = Next + 1;
    }

    return RetCode;
}

LPTSTR init_dump_file( LPCTSTR FileName )
{
    LPTSTR Sep;
    LPTSTR RootPath;
    LPTSTR Output;
    ULONG Length;
    ULONG OutputLength;
    ULONG Dummy;
    TCHAR Input[MAX_PATH];
    TCHAR Buffer[MAX_PATH];

    RootPath = GET_GS( )->RootPath;
    Output = GET_GS( )->SourceFile;
    OutputLength = SIZE_OF_ARRAY( GET_GS( )->SourceFile );

#ifdef UNICODE
    mbstowcs( Input, FileName, MB_CUR_MAX );
#else
    strncpy( Input, FileName, SIZE_OF_ARRAY( Input ) );
#endif
    Input[SIZE_OF_ARRAY( Input ) - 1] = _T( '\0' );

    do
    {
        /* See if set output path */
        Length = _tcslen( GET_GS( )->OutputPath );
        if ( Length )
        {
            _tcscpy( Output, GET_GS( )->OutputPath );
            if ( Output[Length - 1] == _T( '\\' ) )
                Output[--Length] = _T( '\0' );

            /* See if set root path */
            Dummy = _tcslen( RootPath );
            if ( Dummy && 0 == _tcsnicmp( Input, RootPath, Dummy ) )
            {
                Sep = Input + Dummy;
                if ( *Sep == _T( '\\' ) )
                    Sep++;

                /* Make directory recursively */
                CreateDirectoryRecursive( Output, Sep );

                /* Set output file */
                _sntprintf( Output + Length, OutputLength - Length, _T( "\\%s" ), Sep );
            }
            else
            {
                /* Set output file */
                Sep = _tcsrchr( Input, _T( '\\' ) );
                if ( Sep )
                    _sntprintf( Output + Length, OutputLength - Length, _T( "%s" ), Sep );
                else
                    _sntprintf( Output + Length, OutputLength - Length, _T( "\\%s" ), Input );
            }
        }
        else
        {
            /* Set output file */
            _tcscpy( Output, Input );
        }

        /* See if set output file name */
        if ( *GET_GS( )->OutputFile )
        {
            Sep = _tcsrchr( Output, _T( '\\' ) );
            if ( Sep )
                _sntprintf( Sep, Output + OutputLength - Sep, _T( "\\%s" ), GET_GS( )->OutputFile );
        }

        /* Set output file extension name */
        Sep = _tcsrchr( Output, _T( '.' ) );
        if ( 0 != _tcsicmp( GET_GS( )->OutputExt, _T( "*" ) ) )
        {
            if ( Sep )
                _tcscpy( Sep, GET_GS( )->OutputExt );
            else
                _tcscat( Output, GET_GS( )->OutputExt );
        }

        /* Backup source file before replace it */
        if ( GET_GS_FLAGS( ) & GS_FLAGS_BACKUP && 0 == _tcsicmp( Output, Input ) )
        {
            _sntprintf( Buffer, SIZE_OF_ARRAY( Buffer ), _T( "%s.bak" ), Output );
            if ( !CopyFile( Output, Buffer, FALSE ) )
                ADD_DEBUG_LOG_LR( _T( "[F]Copy file< %s > to < %s >" ), Input, Buffer );
        }
    } while ( 0 );

    return Output;
}

LPTSTR set_dump_file( LPTSTR FileName, BOOL Clear, BOOL Force )
{
    if ( Force || GET_GS( )->LastFile != FileName )
    {
        UNINIT_LOG( );
        if ( FileName && *FileName )
        {
            INIT_LOG( FileName, GET_GS( )->LogType, TRUE );
            if ( Clear )
                CLEAR_LOG( );
        }
        GET_GS( )->LastFile = FileName;
    }

    return GET_GS( )->LastFile;
}

void set_dump_source( )
{
    set_dump_file( GET_GS( )->SourceFile, GET_GS( )->State & GS_STATE_EVAL_FILE ? FALSE : TRUE, FALSE );
}

void set_dump_log( )
{
    set_dump_file( GET_GS( )->LogFile, FALSE, TRUE );
}

void dump_info( ULONG Indent )
{
    if ( GET_GS_FLAGS( ) & GS_FLAGS_OBFUSCATE_DIC )
    {
        generate_obfuscate_name_list( GET_GS( )->zend_obfuscate_function_name, GET_GS( )->DecodeLevelLow, GET_GS( )->DecodeLevelHigh );
        generate_obfuscate_name_list( GET_GS( )->zend_obfuscate_class_name, GET_GS( )->DecodeLevelLow, GET_GS( )->DecodeLevelHigh );
        //obfuscate_name_test( GET_GS( )->zend_obfuscate_function_name, GET_GS( )->DecodeLevelLow, GET_GS( )->DecodeLevelHigh );
        //obfuscate_name_test( GET_GS( )->zend_obfuscate_class_name, GET_GS( )->DecodeLevelLow, GET_GS( )->DecodeLevelHigh );
    }

    if ( *GET_GS( )->LogFile )
    {
        set_dump_log( );

        /* Loader information */
        zend_loader_info( );

        ADD_DEBUG_LOG_LR( _T( "Def compile[ %08X ] current compile[ %08X ]" ), compile_file, zend_compile_file );
        ADD_DEBUG_LOG_LR( _T( "Def execute[ %08X ] current execute[ %08X ]" ), execute, zend_execute );
        if ( GET_GS_FLAGS( ) & GS_FLAGS_INFO )
        {
            /* Structure information */
            DUMP_STRUCT_SIZE( zend_scanner_globals );
            DUMP_STRUCT_SIZE( zend_compiler_globals );
            DUMP_STRUCT_SIZE( zend_executor_globals );
            DUMP_STRUCT_SIZE( zend_stack );
            DUMP_STRUCT_SIZE( zend_ptr_stack );
            DUMP_STRUCT_SIZE( zend_llist );
            DUMP_STRUCT_SIZE( HashTable );
            DUMP_STRUCT_SIZE( zvalue_value );
            DUMP_STRUCT_SIZE( zval );
            DUMP_STRUCT_SIZE( znode );
            DUMP_STRUCT_SIZE( zend_op );
            DUMP_STRUCT_SIZE( zend_op_array );
            DUMP_STRUCT_SIZE( zend_declarables );
            DUMP_STRUCT_SIZE( zend_function );
            DUMP_STRUCT_SIZE( zend_function_state );

            DUMP_FIELD_OFFSET( zend_compiler_globals, active_op_array );
            DUMP_FIELD_OFFSET( zend_compiler_globals, open_files );

            if ( GET_GS( )->ExtensionId < EXTENSION_ID_2 )
            {
                DUMP_FIELD_OFFSET( zend_compiler_globals_1, active_op_array );
                DUMP_FIELD_OFFSET( zend_compiler_globals_1, open_files );

                DUMP_FIELD_OFFSET( zend_executor_globals_1, uninitialized_zval );
                DUMP_FIELD_OFFSET( zend_executor_globals_1, uninitialized_zval_ptr );
                DUMP_FIELD_OFFSET( zend_executor_globals_1, error_zval );
                DUMP_FIELD_OFFSET( zend_executor_globals_1, error_zval_ptr );
                DUMP_FIELD_OFFSET( zend_executor_globals_1, arg_types_stack );
                DUMP_FIELD_OFFSET( zend_executor_globals_1, symtable_cache );
                DUMP_FIELD_OFFSET( zend_executor_globals_1, symtable_cache_limit );
                DUMP_FIELD_OFFSET( zend_executor_globals_1, symbol_table );
                DUMP_FIELD_OFFSET( zend_executor_globals_1, included_files );
                DUMP_FIELD_OFFSET( zend_executor_globals_1, ticks_count );
                DUMP_FIELD_OFFSET( zend_executor_globals_1, in_execution );
                DUMP_FIELD_OFFSET( zend_executor_globals_1, full_tables_cleanup );
                DUMP_FIELD_OFFSET( zend_executor_globals_1, no_extensions );
                DUMP_FIELD_OFFSET( zend_executor_globals_1, no_extensions );

#ifdef ZEND_WIN32
                DUMP_FIELD_OFFSET( zend_executor_globals_1, timed_out );
#endif
                DUMP_FIELD_OFFSET( zend_executor_globals_1, regular_list );
                DUMP_FIELD_OFFSET( zend_executor_globals_1, persistent_list );
                DUMP_FIELD_OFFSET( zend_executor_globals_1, argument_stack );

                DUMP_FIELD_OFFSET( zend_executor_globals_1, user_error_handler );
                DUMP_FIELD_OFFSET( zend_executor_globals_1, timeout_seconds );
                DUMP_FIELD_OFFSET( zend_executor_globals_1, lambda_count );
                DUMP_FIELD_OFFSET( zend_executor_globals_1, ini_directives );

                DUMP_FIELD_OFFSET( zend_executor_globals_1, current_execute_data );
                DUMP_FIELD_OFFSET( zend_executor_globals_1, reserved );

                DUMP_FIELD_OFFSET( zend_op_array_1, function_name );
                DUMP_FIELD_OFFSET( zend_op_array_1, opcodes );
                DUMP_FIELD_OFFSET( zend_op_array_1, start_op );
                DUMP_FIELD_OFFSET( zend_op_array_1, static_variables );
                DUMP_FIELD_OFFSET( zend_op_array_1, start_op );
                DUMP_FIELD_OFFSET( zend_op_array_1, done_pass_two );
                DUMP_FIELD_OFFSET( zend_op_array_1, filename );
                DUMP_FIELD_OFFSET( zend_op_array_1, reserved );
            }
            else
            {
                DUMP_FIELD_OFFSET( zend_compiler_globals_2, active_op_array );
                DUMP_FIELD_OFFSET( zend_compiler_globals_2, open_files );
                DUMP_FIELD_OFFSET( zend_compiler_globals_2, increment_lineno );
                DUMP_FIELD_OFFSET( zend_compiler_globals_2, implementing_class );
                DUMP_FIELD_OFFSET( zend_compiler_globals_2, static_members );

                DUMP_FIELD_OFFSET( zend_executor_globals_2, uninitialized_zval );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, uninitialized_zval_ptr );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, error_zval );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, error_zval_ptr );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, arg_types_stack );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, symtable_cache );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, symtable_cache_limit );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, symbol_table );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, included_files );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, ticks_count );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, in_execution );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, in_autoload );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, autoload_func );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, full_tables_cleanup );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, ze1_compatibility_mode );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, no_extensions );

#ifdef ZEND_WIN32
                DUMP_FIELD_OFFSET( zend_executor_globals_2, timed_out );
#endif

                DUMP_FIELD_OFFSET( zend_executor_globals_2, regular_list );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, persistent_list );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, argument_stack );

                DUMP_FIELD_OFFSET( zend_executor_globals_2, user_error_handler_error_reporting );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, user_error_handler );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, user_exception_handler );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, user_error_handlers_error_reporting );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, user_exception_handlers );

                DUMP_FIELD_OFFSET( zend_executor_globals_2, timeout_seconds );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, lambda_count );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, ini_directives );

                DUMP_FIELD_OFFSET( zend_executor_globals_2, modified_ini_directives );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, objects_store );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, exception );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, opline_before_exception );

                DUMP_FIELD_OFFSET( zend_executor_globals_2, current_execute_data );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, current_module );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, std_property_info );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, active );
                DUMP_FIELD_OFFSET( zend_executor_globals_2, reserved );

                DUMP_FIELD_OFFSET( zend_op_array_2, function_name );
                DUMP_FIELD_OFFSET( zend_op_array_2, opcodes );
                DUMP_FIELD_OFFSET( zend_op_array_2, start_op );
                DUMP_FIELD_OFFSET( zend_op_array_2, static_variables );
                DUMP_FIELD_OFFSET( zend_op_array_2, start_op );
                DUMP_FIELD_OFFSET( zend_op_array_2, done_pass_two );
                DUMP_FIELD_OFFSET( zend_op_array_2, filename );
                DUMP_FIELD_OFFSET( zend_op_array_2, reserved );
            }
        }

        if ( GET_GS_FLAGS( ) & GS_FLAGS_HASH )
        {
            ADD_LOG_LR( _T( "[Compiler]" ) );
            ADD_LOG_LR( _T( "//<class_table>" ) );
            dump_hash_key( GET_GS( )->GCompiler->class_table, Indent );
            ADD_LOG_LR( _T( "//<function_table>" ) );
            dump_hash_key( GET_GS( )->GCompiler->function_table, Indent );

            ADD_LOG_LR( _T( "[Executor]" ) );
            ADD_LOG_LR( _T( "//<active_symbol_table>" ) );
            dump_hash_key( GET_GS( )->GExecutor->active_symbol_table, Indent );
            ADD_LOG_LR( _T( "//<symbol_table>" ) );
            dump_hash_key( &GET_GS( )->GExecutor->symbol_table, Indent );
            ADD_LOG_LR( _T( "//<included_files>" ) );
            dump_hash_key( &GET_GS( )->GExecutor->included_files, Indent );
            ADD_LOG_LR( _T( "//<zend_constants>" ) );
            dump_hash_key( GET_GS( )->GExecutor->zend_constants, Indent );
            ADD_LOG_LR( _T( "//<regular_list>" ) );
            dump_hash_key( &GET_GS( )->GExecutor->regular_list, Indent );
            ADD_LOG_LR( _T( "//<persistent_list>" ) );
            dump_hash_key( &GET_GS( )->GExecutor->persistent_list, Indent );
            ADD_LOG_LR( _T( "//<ini_directives>" ) );
            dump_hash_key( GET_GS( )->GExecutor->ini_directives, Indent );
        }
        GET_GS( )->LastFile = GET_GS( )->LogFile;
    }
}

void dump_tick( )
{
    static ULONG Tick = 0;
    register ULONG Span;

    if ( GET_GS_FLAGS( ) & GS_FLAGS_TICK )
    {
        if ( Tick == 0 )
        {
            /* Tick Count */
            Tick = GetTickCount( );
        }
        else
        {
            /* Tick Count span */
            Span = GetTickCount( ) - Tick;
            if ( *GET_GS( )->LogFile )
                ADD_DEBUG_LOG( _T( "Tick consume[ %08X( %d ) ]\r\n" ), Span, Span );
            else
                _tprintf( _T( "Tick consume[ %08X( %d ) ]\r\n" ), Span, Span );
        }
    }
}

void dump_op_array_interface( zend_op_array *OpArray )
{
    const TCHAR *FunctionName;
    const TCHAR *String;
    zend_arg_info_2 *ArgInfo;

    TSRMLS_FETCH( );

    if ( GET_GS_FLAGS( ) & GS_FLAGS_OPARRAY && *GET_GS( )->LogFile )
    {
        if ( GET_GS( )->LastFile != GET_GS( )->LogFile )
            INIT_LOG( GET_GS( )->LogFile, GET_GS( )->LogType, TRUE );

        ADD_LOG_LR( _T( "====Op array information start====" ) );
        ADD_DEBUG_LOG_LR( _T( "OpArray[ %08X ]" ), OpArray );
        ADD_DEBUG_LOG_LR( _T( "TSRMLS[ %08X ]" ), TSRMLS_C );

        if ( GET_GS( )->ExtensionId < EXTENSION_ID_2 )
        {
            FunctionName = ( ( zend_op_array_1* )OpArray )->function_name;

            ADD_DEBUG_LOG_LR( _T( "type[ %08X ]" ), ( ( zend_op_array_1* )OpArray )->type );
            if ( ( ( zend_op_array_1* )OpArray )->refcount )
                ADD_DEBUG_LOG_LR( _T( "refcount[ %08X ]" ), *( ( zend_op_array_1* )OpArray )->refcount );

            ADD_DEBUG_LOG_LR( _T( "opcodes[ %08X ]" ), ( ( zend_op_array_1* )OpArray )->opcodes );
            ADD_DEBUG_LOG_LR( _T( "start_op[ %08X ]" ), ( ( zend_op_array_1* )OpArray )->start_op );
            ADD_DEBUG_LOG_LR( _T( "filename< %s >" ), ( ( zend_op_array_1* )OpArray )->filename );
            ADD_DEBUG_LOG_LR( _T( "size[ %d ]" ), ( ( zend_op_array_1* )OpArray )->size );

            ADD_DEBUG_LOG_LR( _T( "arg_types[ %08X ]" ), ( ( zend_op_array_1* )OpArray )->arg_types );
        }
        else
        {
            FunctionName = ( ( zend_op_array_2* )OpArray )->function_name;

            ADD_DEBUG_LOG_LR( _T( "type[ %08X ]" ), ( ( zend_op_array_2* )OpArray )->type );
            if ( ( ( zend_op_array_2* )OpArray )->refcount )
                ADD_DEBUG_LOG_LR( _T( "refcount[ %08X ]" ), *( ( zend_op_array_2* )OpArray )->refcount );

            ADD_DEBUG_LOG_LR( _T( "opcodes[ %08X ]" ), ( ( zend_op_array_2* )OpArray )->opcodes );
            ADD_DEBUG_LOG_LR( _T( "start_op[ %08X ]" ), ( ( zend_op_array_2* )OpArray )->start_op );
            ADD_DEBUG_LOG_LR( _T( "filename< %s >" ), ( ( zend_op_array_2* )OpArray )->filename );
            ADD_DEBUG_LOG_LR( _T( "size[ %d ]" ), ( ( zend_op_array_2* )OpArray )->size );

            ArgInfo = ( zend_arg_info_2* ) ( ( zend_op_array_2* )OpArray )->arg_info;
            if ( ArgInfo )
            {
                ADD_DEBUG_LOG_LR( _T( "name[ %08X ]" ), ArgInfo->name );
                ADD_DEBUG_LOG_LR( _T( "class_name[ %08X ]" ), ArgInfo->class_name );
                ADD_DEBUG_LOG_LR( _T( "array_type_hint[ %08X ]" ), ArgInfo->array_type_hint );
                ADD_DEBUG_LOG_LR( _T( "allow_null[ %08X ]" ), ArgInfo->allow_null );
                ADD_DEBUG_LOG_LR( _T( "required_num_args[ %08X ]" ), ArgInfo->required_num_args );
            }
            ADD_DEBUG_LOG_LR( _T( "pass_rest_by_reference[ %08X ]" ), ( ( zend_op_array_2* )OpArray )->pass_rest_by_reference );
            ADD_DEBUG_LOG_LR( _T( "return_reference[ %08X ]" ), ( ( zend_op_array_2* )OpArray )->return_reference );
        }

        if ( FunctionName )
        {
            LOCK_GS( );
            decode_obfuscate_function_name( &GET_GS( )->Buffer, FunctionName, _tcslen( FunctionName ) );
            StackPopAllS( &GET_GS( )->Buffer, &String );
            ADD_DEBUG_LOG_LR( _T( "function_name< %s >" ), String );
            UNLOCK_GS( );
        }
        else
        {
            ADD_LOG_LR( _T( "function_name< NULL >" ) );
        }
        ADD_LOG_LR( _T( "====Op array information end====" ) );

        if ( GET_GS( )->LastFile != GET_GS( )->LogFile )
            INIT_LOG( GET_GS( )->LastFile, GET_GS( )->LogType, TRUE );
    }
}

void dump_obfuscate_name( )
{
    if ( GET_GS_FLAGS( ) & GS_FLAGS_OBFUSCATE )
        DumpObfuscateName( );
}

void dump_file_head( )
{
    ULONG Dummy;

    DECODE_STR( Dummy, GET_GS( )->FileHead );
    /* Deal with escape character */
    if ( !( GET_GS( )->EncodeStub->Flags & GS_ENCODE_FLAGS_HEAD ) )
    {
        TranslateEscapeCharacter( GET_GS( )->FileHead, SIZE_OF_ARRAY( GET_GS( )->FileHead ) );
        GET_GS( )->EncodeStub->Flags |= GS_ENCODE_FLAGS_HEAD;
    }
    ADD_DEBUG_LOG_LR( GET_GS( )->FileHead );
    ENCODE_STR( Dummy, GET_GS( )->FileHead );
}

void dump_file_tail( )
{
    ULONG Dummy;

    DECODE_STR( Dummy, GET_GS( )->FileTail );
    /* Deal with escape character */
    if ( !( GET_GS( )->EncodeStub->Flags & GS_ENCODE_FLAGS_TAIL ) )
    {
        TranslateEscapeCharacter( GET_GS( )->FileTail, SIZE_OF_ARRAY( GET_GS( )->FileTail ) );
        GET_GS( )->EncodeStub->Flags |= GS_ENCODE_FLAGS_TAIL;
    }
    ADD_DEBUG_LOG_LR( GET_GS( )->FileTail );
    ENCODE_STR( Dummy, GET_GS( )->FileTail );
}

void dump_file_comment( )
{
    ULONG Dummy;

    DECODE_STR( Dummy, GET_GS( )->FileComment );
    /* Deal with escape character */
    if ( !( GET_GS( )->EncodeStub->Flags & GS_ENCODE_FLAGS_COMMENT ) )
    {
        TranslateEscapeCharacter( GET_GS( )->FileComment, SIZE_OF_ARRAY( GET_GS( )->FileComment ) );
        GET_GS( )->EncodeStub->Flags |= GS_ENCODE_FLAGS_COMMENT;
    }
    ADD_DEBUG_LOG_LR( GET_GS( )->FileComment );
    ENCODE_STR( Dummy, GET_GS( )->FileComment );
}

ULONG ImportObfuscate( )
{
    ULONG RetCode;
    FILE *Fp;
    ULONG ReadSize;
    ULONG FilePosition;
    LPTSTR Start;
    LPTSTR Tail;
    LPTSTR String1;
    LPTSTR String2;
    ULONG Length1;
    ULONG Length2;
    TCHAR Signature[] = _T( "[OBFUSCATE]\r\n" );
    TCHAR Buffer[BUFFER_SIZE + 0x10];

    RetCode = 0;
    do
    {
        Fp = NULL;
        if ( GET_GS_STATE( ) & GS_STATE_IMPORT_OBFUSCATE )
            break;

        Fp = _tfopen( GET_GS( )->ConfigFile, _T( "rb" ) );
        if ( Fp == NULL )
            break;

        ReadSize = fread( Buffer, 1, SMALL_BUFFER_SIZE * sizeof( TCHAR ), Fp );
        if ( ReadSize == 0 )
            break;

        Buffer[ReadSize] = _T( '\0' );
        Start = _tcsstr( Buffer, Signature );
        if ( Start == NULL )
            break;

        Buffer[BUFFER_SIZE] = _T( '\0' );
        FilePosition = Start - Buffer + SIZE_OF_ARRAY( Signature ) - 1;
        while ( !feof( Fp ) )
        {
            fseek( Fp, FilePosition, SEEK_SET );
            ReadSize = fread( Buffer, 1, BUFFER_SIZE * sizeof( TCHAR ), Fp );
            if ( ReadSize > 2 )
            {
                Buffer[ReadSize] = _T( '\0' );
                Start = Buffer;
                Tail = Buffer + ReadSize - 1;
                if ( ReadSize == BUFFER_SIZE * sizeof( TCHAR ) )
                {
                    while ( Start < Tail )
                    {
                        if ( *Tail == _T( '\n' ) && *( Tail - 1 ) == _T( '\r' ) )
                            break;
                        Tail--;
                    }
                    if ( Tail == Start )
                        break;
                }

                Tail++;
                while ( Start < Tail )
                {
                    String1 = Start;
                    while ( Start < Tail )
                    {
                        if ( Start[0] == _T( '\r' ) && Start[1] == _T( '\n' ) )
                            break;
                        Start++;
                    }

                    if ( Start == Tail )
                        break;

                    *Start = _T( '\0' );
                    Length1 = Start - String1;

                    Start += 2;
                    String2 = Start;
                    while ( Start < Tail )
                    {
                        if ( Start[0] == _T( '\r' ) && Start[1] == _T( '\n' ) )
                            break;
                        Start++;
                    }

                    if ( Start == Tail )
                        break;

                    *Start = _T( '\0' );
                    Length2 = Start - String2;

                    /* Next */
                    Start += 2;

                    if ( !FindOriginName( String1, Length1 ) )
                        InsertObfuscateName( String1, Length1, String2, Length2 );
                    RetCode++;
                }
                FilePosition += ( Tail - Buffer ) * sizeof( TCHAR );
            }
        }
        GET_GS_STATE( ) |= GS_STATE_IMPORT_OBFUSCATE;
    } while ( 0 );

    if ( Fp )
        fclose( Fp );

    return RetCode;
}

ULONG ImportObfuscateName( )
{
    ULONG RetCode;
    FILE *Fp;
    ULONG ReadSize;
    ULONG FilePosition;
    LPTSTR Start;
    LPTSTR End;
    LPTSTR Tail;
    zval *RetValue;
    TCHAR Signature[] = _T( "[OBFUSCATE_NAME]\r\n" );
    TCHAR Buffer[BUFFER_SIZE + 0x10];

    RetCode = 0;
    do
    {
        Fp = NULL;
        if ( GET_GS_STATE( ) & GS_STATE_IMPORT_OBFUSCATE )
            break;

        Fp = _tfopen( GET_GS( )->ConfigFile, _T( "rb" ) );
        if ( Fp == NULL )
            break;

        ReadSize = fread( Buffer, 1, SMALL_BUFFER_SIZE * sizeof( TCHAR ), Fp );
        if ( ReadSize == 0 )
            break;

        Buffer[ReadSize] = _T( '\0' );
        Start = _tcsstr( Buffer, Signature );
        if ( Start == NULL )
            break;

        Buffer[BUFFER_SIZE] = _T( '\0' );
        FilePosition = Start - Buffer + SIZE_OF_ARRAY( Signature ) - 1;
        while ( !feof( Fp ) )
        {
            fseek( Fp, FilePosition, SEEK_SET );
            ReadSize = fread( Buffer, 1, BUFFER_SIZE * sizeof( TCHAR ), Fp );
            if ( ReadSize )
            {
                Buffer[ReadSize] = _T( '\0' );
                Start = Buffer;
                Tail = Buffer + ReadSize - 1;
                if ( ReadSize == BUFFER_SIZE * sizeof( TCHAR ) )
                {
                    while ( Start < Tail )
                    {
                        if ( *Tail == _T( '\n' ) && *( Tail - 1 ) == _T( '\r' ) )
                            break;
                        Tail--;
                    }
                    if ( Tail == Start )
                        break;
                }

                Tail++;
                while ( Start < Tail )
                {
                    while ( *Start == _T( '\r' ) || *Start == _T( '\n' ) )
                        Start++;

                    if ( Start == Tail )
                        break;

                    End = Start;
                    while ( *End != _T( '\r' ) && *End != _T( '\n' ) && End < Tail )
                        End++;

                    *End = _T( '\0' );
                    if ( !FindOriginName( Start, End - Start ) )
                    {
                        RetValue = zend_obfuscate_class_name( Start );
                        if ( RetValue )
                        {
                            InsertObfuscateName( Start, End - Start, RetValue->value.str.val, RetValue->value.str.len );
                            free_zval( RetValue );
                            RetCode++;
                        }
                        RetValue = zend_obfuscate_function_name( Start );
                        if ( RetValue )
                        {
                            InsertObfuscateName( Start, End - Start, RetValue->value.str.val, RetValue->value.str.len );
                            free_zval( RetValue );
                            RetCode++;
                        }
                    }
                    Start = End + 1;
                }
                FilePosition += ( Tail - Buffer ) * sizeof( TCHAR );
            }
        }
        GET_GS_STATE( ) |= GS_STATE_IMPORT_OBFUSCATE;
    } while ( 0 );

    if ( Fp )
        fclose( Fp );

    return RetCode;
}

ULONG ExportObfuscate( )
{
    FILE *Fp;
    register ULONG RetCode;
    register Bucket *Bt;
    register Bucket *Bt1;
    zend_class_entry *ClassEntry;
    zend_function *Function;
    zval *RetValue;
    TCHAR Signature[] = _T( "[OBFUSCATE]\r\n" );
    TCHAR Separator[] = _T( "\r\n" );

    RetCode = 0;
    do
    {
        Fp = _tfopen( GET_GS( )->ConfigFile, _T( "wb" ) );
        if ( Fp == NULL )
            break;

        _fputts( Signature, Fp );
        Bt = GET_GS_CLASS_TABLE( )->pListHead;
        while ( Bt )
        {
            ClassEntry = ( zend_class_entry* ) ( Bt->pDataPtr ? Bt->pDataPtr : Bt->pData );
            if ( ClassEntry->type == ZEND_INTERNAL_CLASS )
            {
                RetValue = zend_obfuscate_class_name( ClassEntry->name );
                if ( RetValue )
                {
                    _fputts( ClassEntry->name, Fp );
                    _fputts( Separator, Fp );
                    _fputts( RetValue->value.str.val, Fp );
                    _fputts( Separator, Fp );
                    free_zval( RetValue );
                    RetCode++;
                }
                Bt1 = ClassEntry->function_table.pListHead;
                while ( Bt1 )
                {
                    Function = ( zend_function* ) ( Bt1->pDataPtr ? Bt1->pDataPtr : Bt1->pData );
                    if ( Function->type == ZEND_INTERNAL_FUNCTION )
                    {
                        RetValue = zend_obfuscate_function_name( Function->common.function_name );
                        if ( RetValue )
                        {
                            _fputts( Function->common.function_name, Fp );
                            _fputts( Separator, Fp );
                            _fputts( RetValue->value.str.val, Fp );
                            _fputts( Separator, Fp );
                            free_zval( RetValue );
                            RetCode++;
                        }
                    }
                    Bt1 = Bt1->pListNext;
                }
            }
            Bt = Bt->pListNext;
        }

        Bt1 = GET_GS_FUNCTION_TABLE( )->pListHead;
        while ( Bt1 )
        {
            Function = ( zend_function* ) ( Bt1->pDataPtr ? Bt1->pDataPtr : Bt1->pData );
            if ( Function->type == ZEND_INTERNAL_FUNCTION )
            {
                RetValue = zend_obfuscate_function_name( Function->common.function_name );
                if ( RetValue )
                {
                    _fputts( Function->common.function_name, Fp );
                    _fputts( Separator, Fp );
                    _fputts( RetValue->value.str.val, Fp );
                    _fputts( Separator, Fp );
                    free_zval( RetValue );
                    RetCode++;
                }
            }
            Bt1 = Bt1->pListNext;
        }
    } while ( 0 );

    if ( Fp )
        fclose( Fp );

    return RetCode;
}

ULONG ExportObfuscateName( )
{
    FILE *Fp;
    register ULONG RetCode;
    register Bucket *Bt;
    register Bucket *Bt1;
    zend_class_entry *ClassEntry;
    zend_function *Function;
    TCHAR Signature[] = _T( "[OBFUSCATE_NAME]\r\n" );
    TCHAR Separator[] = _T( "\r\n" );

    RetCode = 0;
    do
    {
        Fp = _tfopen( GET_GS( )->ConfigFile, _T( "wb" ) );
        if ( Fp == NULL )
            break;

        _fputts( Signature, Fp );
        Bt = GET_GS_CLASS_TABLE( )->pListHead;
        while ( Bt )
        {
            ClassEntry = ( zend_class_entry* ) ( Bt->pDataPtr ? Bt->pDataPtr : Bt->pData );
            if ( ClassEntry->type == ZEND_INTERNAL_CLASS )
            {
                _fputts( ClassEntry->name, Fp );
                _fputts( Separator, Fp );
                RetCode++;
                Bt1 = ClassEntry->function_table.pListHead;
                while ( Bt1 )
                {
                    Function = ( zend_function* ) ( Bt1->pDataPtr ? Bt1->pDataPtr : Bt1->pData );
                    if ( Function->type == ZEND_INTERNAL_FUNCTION )
                    {
                        _fputts( Function->common.function_name, Fp );
                        _fputts( Separator, Fp );
                        RetCode++;
                    }
                    Bt1 = Bt1->pListNext;
                }
            }
            Bt = Bt->pListNext;
        }

        Bt1 = GET_GS_FUNCTION_TABLE( )->pListHead;
        while ( Bt1 )
        {
            Function = ( zend_function* ) ( Bt1->pDataPtr ? Bt1->pDataPtr : Bt1->pData );
            if ( Function->type == ZEND_INTERNAL_FUNCTION )
            {
                _fputts( Function->common.function_name, Fp );
                _fputts( Separator, Fp );
                RetCode++;
            }
            Bt1 = Bt1->pListNext;
        }
    } while ( 0 );

    if ( Fp )
        fclose( Fp );

    return RetCode;
}

ULONG EncodeHashTable( HashTable *Table )
{
    register ULONG RetCode;
    register Bucket *Bt;

    RetCode = 0;
    Bt = Table->pListHead;
    while ( Bt )
    {
        Bt->nKeyLength = ENCODE_HASH( Bt->nKeyLength );
        Bt = Bt->pListNext;
    }

    return RetCode;
}

ULONG DecodeHashTable( HashTable *Table )
{
    register ULONG RetCode;
    register Bucket *Bt;

    RetCode = 0;
    Bt = Table->pListHead;
    while ( Bt )
    {
        Bt->nKeyLength = DECODE_HASH( Bt->nKeyLength );
        Bt = Bt->pListNext;
    }

    return RetCode;
}

/*
///////////////////////////////////////////////////////////////////////////////
// InitGlobalSettingPreCompile
///////////////////////////////////////////////////////////////////////////////
*/
ULONG InitGlobalSettingPreCompile( )
{
    ULONG RetCode;
    ULONG Dummy;
    PGLOBAL_SETTING Setting;
    static STRING_ARRAY_EX Array[] = {
        { _T( "zend_obfuscate_function_name" ), sizeof( "zend_obfuscate_function_name" ), NULL },
        { _T( "zend_obfuscate_class_name" ), sizeof( "zend_obfuscate_class_name" ), NULL },
    };

    TSRMLS_FETCH( );

    RetCode = FALSE;
    do
    {
        Setting = GET_GS( );

#if !PRIVATE_VERSION
        if ( CheckIfTrace( ) )
        {
            /* Check if being tracing */
            Setting->State |= GS_STATE_CHECK_TRACE;
        }
#endif

        /* State */
        Setting->State &= ~GS_STATE_MASK;
        Setting->Version = 0;
        Setting->MajorId = Setting->ExtensionId;

        /* Context */
        Setting->Context = TSRMLS_C;

        /* Execute environment */
        Setting->GScanner = ( zend_scanner_globals* )TSRMG_GET( language_scanner_globals_id );
        Setting->GCompiler = ( zend_compiler_globals* )TSRMG_GET( compiler_globals_id );
        Setting->GExecutor = ( zend_executor_globals* )TSRMG_GET( executor_globals_id );

        /* Extension module base */
        if ( Setting->ExtensionModuleBase == NULL )
        {
            DECODE_STR( Dummy, GET_GS( )->ExtensionModuleName );
            Setting->ExtensionModuleBase = GetModuleHandle( GET_GS( )->ExtensionModuleName );
            ENCODE_STR( Dummy, GET_GS( )->ExtensionModuleName );
        }

        /* Extension installed */
        if ( zend_compile_file != compile_file )
        {
            Setting->State |= GS_STATE_EXTEND;
            switch ( ( ULONG )zend_compile_file - ( ULONG )Setting->ExtensionModuleBase )
            {
            /* [3.30]Php5 */
            case 0x18C80 :
                Setting->ExtensionId = EXTENSION_ID_3;
                Setting->RealExtensionId = EXTENSION_ID_3;
                break;
            /* [3.30]Php4 */
            case 0x1C230 :
                Setting->RealExtensionId = EXTENSION_ID_3;
                break;
            }
        }

        if ( Setting->ExtensionId < EXTENSION_ID_2 )
        {
            Setting->ExtensionModuleSize = 0x20000;
            Setting->HookTimeSignature = 0x01518005;
        }
        else
        {
            Setting->ExtensionModuleSize = 0xC0000;
            Setting->HookTimeSignature = 0x3B04C483;
        }

        /* We need it to dump class table and function table */
        if ( Setting->GExecutor == NULL )
            break;

        /* Internal function */
        find_function_handler_ex( Setting->GExecutor->function_table, SIZE_OF_ARRAY( Array ), Array );
        Setting->zend_obfuscate_function_name = Array[0].Data;
        Setting->zend_obfuscate_class_name = Array[1].Data;

        /* Encode hash key length to avoid class/function redeclare */
        EncodeHashTable( Setting->GExecutor->class_table );
        EncodeHashTable( Setting->GExecutor->function_table );
        Setting->State |= GS_STATE_ENCODE_HASH;

#if !PRIVATE_VERSION
        if ( ( Setting->State & ( GS_STATE_CHECK_MODIFY | GS_STATE_CHECK_TRACE ) ) )
            Setting->ExtensionModuleBase = NULL;
#endif

        /* Patch memory to skip license check */
        PatchLicense( );

        RetCode = TRUE;
    } while ( 0 );

    return RetCode;
}

/*
///////////////////////////////////////////////////////////////////////////////
// UninitGlobalSettingPreCompile
///////////////////////////////////////////////////////////////////////////////
*/
void UninitGlobalSettingPreCompile( )
{
}

static void execute_stub( zend_op_array *OpArray TSRMLS_DC )
{
    UNREFERENCED_PARAMETER( OpArray );
    UNREFERENCED_PARAMETER( TSRMLS_C );
}

ULONG ReadInteger( FILE *Fp, ULONG *Data )
{
    ULONG RetCode;
    ULONG Size;
    UCHAR Buffer[128];

    do
    {
        RetCode = FALSE;
        if ( fread( Buffer, 1, 1, Fp ) != 1 )
            break;

        if ( Buffer[0] > 0x7F )
            break;

        Size = Buffer[0];
        if ( fread( Buffer, 1, Size, Fp ) != Size )
            break;

        Buffer[Size] = _T( '\0' );
        *Data = _ttoi( ( TCHAR* )Buffer );
        RetCode = TRUE;
    } while ( 0 );

    return RetCode;
}

ULONG AddObfuscateClass( HashTable *Table )
{
    register ULONG RetCode;
    register Bucket *Bt;
    zend_class_entry *ClassEntry;
    zval *RetValue;

    RetCode = 0;
    Bt = Table->pListHead;
    while ( Bt )
    {
        ClassEntry = ( zend_class_entry* ) ( Bt->pDataPtr ? Bt->pDataPtr : Bt->pData );
        if ( ClassEntry->type == ZEND_INTERNAL_CLASS )
        {
            RetValue = zend_obfuscate_class_name( ClassEntry->name );
            if ( RetValue )
            {
                InsertObfuscateName( ClassEntry->name, RetValue->value.str.len, RetValue->value.str.val, RetValue->value.str.len );
                free_zval( RetValue );
                RetCode++;
            }
            AddObfuscateFunction( &ClassEntry->function_table );
        }
        Bt = Bt->pListNext;
    }

    return RetCode;
}

ULONG AddObfuscateFunction( HashTable *Table )
{
    register ULONG RetCode;
    register Bucket *Bt;
    zend_function *Function;
    zval *RetValue;

    RetCode = 0;
    Bt = Table->pListHead;
    while ( Bt )
    {
        Function = ( zend_function* ) ( Bt->pDataPtr ? Bt->pDataPtr : Bt->pData );
        if ( Function->type == ZEND_INTERNAL_FUNCTION )
        {
            RetValue = zend_obfuscate_function_name( Function->common.function_name );
            if ( RetValue )
            {
                InsertObfuscateName( Function->common.function_name, RetValue->value.str.len, RetValue->value.str.val, RetValue->value.str.len );
                free_zval( RetValue );
                RetCode++;
            }
        }
        Bt = Bt->pListNext;
    }

    return RetCode;
}

/*
///////////////////////////////////////////////////////////////////////////////
// InitGlobalSettingRuntime
///////////////////////////////////////////////////////////////////////////////
*/
ULONG InitGlobalSettingRuntime( zend_op_array *OpArray )
{
    ULONG RetCode;
    PGLOBAL_SETTING Setting;
    FILE *Fp;
    ULONG Flags;
    ULONG FormatId;
    ULONG MajorId;
    ULONG Length1;
    ULONG Length2;
    ULONG Data;
    ULONG Dummy;
    ULONG Iter;
    ULONG Count;
    static char Signature[] = DEFAULT_FILE_SIGNATURE;
    static char SignatureShort[] = DEFAULT_FILE_SIGNATURE_SHORT;
    static KEY_VALUE FormatIdToVersion[] = {
        { 0x7736F5E9, 0x00010001 }, /* 1.x */
        { 0x77374981, 0x00010002 }, /* 2.x */
        { 0x77550BDD, 0x00010003 }, /* 3.1 */
        { 0x7765323D, 0x00060003 }, /* 3.6 see 0x40A1C2( push 0x7765323D ) */
        { 0x7765323E, 0x01000004 }, /* 4.0.1 base */
        { 0x77917A91, 0x01000004 }, /* 4.0.1 strong */
        { 0xFFFFFFFF, 0xFFFFFFFF }, /* End */
    };
    zval *RetValue;
    char *Buffer;

    RetCode = FALSE;
    do
    {
        Fp = NULL;
        Flags = 0;
        Setting = GET_GS( );

#if !PRIVATE_VERSION
        if ( CheckIfTrace( ) )
        {
            /* Check if being tracing */
            Setting->State |= GS_STATE_CHECK_TRACE;
        }
#endif

        /* Compile and execute function */
        Setting->Compile = zend_compile_file;
        Setting->Execute = zend_execute;

        /* Don't execute */
        if ( !( Setting->Flags & GS_FLAGS_EXECUTE ) )
        {
#ifdef ZEND_WIN32
            zend_shutdown_timeout_thread( );
#endif
            zend_execute = execute_stub;
        }

        /* Op array */
        Setting->OpArray = OpArray;

        /* We need it to dump class table and function table */
        if ( Setting->GExecutor == NULL )
            break;

#if !PRIVATE_VERSION
        if ( Setting->State & ( GS_STATE_CHECK_MODIFY | GS_STATE_CHECK_TRACE ) )
        {
            Setting->Flags = 0;
            Setting->State = 0;
            Setting->ObfuscatePrefix[0] = _T( '\0' );
            Setting->DecodeLevelHigh = 32;
            Setting->ExtensionModuleBase = NULL;
            Setting->ExtensionModuleName[0] = ENCODE_CHAR( '\0' );
            break;
        }
#endif

        LOCK_GS( );
        Flags |= FLAGS_LOCKED;
        Buffer = StackBaseS( &Setting->Buffer );

        /* Push current file name */
        push_file_name( get_file_name_ex( OpArray ), 0 );

        /* Push current function name */
        push_function_name_ex( get_function_name_ex( OpArray ), 0 );

        if ( !( Setting->EncodeStub->Flags & GS_ENCODE_FLAGS_OBFUSCATE_PREFIX ) )
        {
            DECODE_STR( Dummy, Setting->ObfuscatePrefix );
            /* Update length */
            Setting->ObfuscatePrefixLength = _tcslen( Setting->ObfuscatePrefix );
            Setting->EncodeStub->Flags |= GS_ENCODE_FLAGS_OBFUSCATE_PREFIX;
        }

        if ( 0 == memcmp( Setting->FileNamePtr + Setting->FileNameLength - DEFAULT_EVAL_FILE_POSTFIX_LENGTH, DEFAULT_EVAL_FILE_POSTFIX, DEFAULT_EVAL_FILE_POSTFIX_LENGTH ) )
        {
            Setting->State |= GS_STATE_EVAL_FILE;
            if ( Setting->MajorId < EXTENSION_ID_2 )
                Setting->State &= ~GS_STATE_OBFUSCATE;
            break;
        }

        if ( Setting->State & GS_STATE_ENCODE_HASH )
        {
            /* Decode hash key length */
            DecodeHashTable( Setting->GExecutor->class_table );
            DecodeHashTable( Setting->GExecutor->function_table );
            Setting->State |= GS_STATE_DECODE_HASH;
            Setting->State &= ~GS_STATE_ENCODE_HASH;
        }

        RetValue = zend_loader_enabled( );
        if ( RetValue )
        {
            if ( RetValue->value.lval )
                Setting->State |= GS_STATE_LOADER_ENABLED;
            free_zval( RetValue );
        }

        /* Encoded file */
        RetValue = zend_loader_file_encoded( );
        if ( RetValue )
        {
            if ( RetValue->value.lval )
                Setting->State |= ( GS_STATE_LOADER_FILE_ENCODED | GS_STATE_OP_ENCODE );
            free_zval( RetValue );
        }

        /* Support obfuscation */
        RetValue = zend_runtime_obfuscate( );
        if ( RetValue )
        {
            if ( RetValue->value.lval )
                Setting->State |= GS_STATE_RUNTIME_OBFUSCATE;
            free_zval( RetValue );
        }

        /* Max obfuscation level */
        RetValue = zend_current_obfuscation_level( );
        if ( RetValue )
        {
            Setting->State |= ( RetValue->value.lval << GS_STATE_OBFUSCATION_LEVEL_SHIFT );
            free_zval( RetValue );
        }

        /* Open origin source file */
        Fp = _tfopen( Setting->FileNamePtr, _T( "rb" ) );
        if ( Fp == NULL )
            break;

        /* Read signature */
        if ( fread( Buffer, 1, sizeof( Signature ) - 1, Fp ) != sizeof( Signature ) - 1 )
            break;

        /* Check signature */
        if ( 0 == memcmp( Buffer, Signature, sizeof( Signature ) - 1 ) )
        {
            /* Read data start offset */
            if ( fread( Buffer, 1, 4, Fp ) != 4 )
                break;

            if ( fseek( Fp, strtol( Buffer, 0, 8 ), SEEK_SET ) != 0 )
                break;
        }
        else
        {
            if ( memcmp( Buffer, SignatureShort, sizeof( SignatureShort ) - 1 ) )
                break;

            if ( fseek( Fp, sizeof( SignatureShort ), SEEK_SET ) != 0 )
                break;
        }

        /* Read Format ID */
        if ( !ReadInteger( Fp, &FormatId ) )
            break;

        /* Read encoded file format major ID */
        if ( !ReadInteger( Fp, &MajorId ) )
            break;

        Setting->FormatId = FormatId;
        Setting->MajorId = MajorId;

        /* This file format is no longer supported */
        if ( FormatId == 0x77836D4D )
            break;

        /* Incompatible file format */
        if ( FormatId < 0x7736F5E9 )
            break;

        /* The encoded file has format major ID MajorId, whereas the Optimizer expects x */
#if SUPPORT_MAX_ENGINE
        if ( MajorId > SUPPORT_MAX_ENGINE )
            break;
#else
        if ( MajorId > 1 )
            break;
#endif

        /* The encoded file has format ID FormatId, whereas the Optimizer can read up to 0x77917A91 */
        if ( FormatId > 0x77917A91 )
            break;

        if ( FormatId > 0x77742D01 )
        {
            /* Data */
            if ( ReadInteger( Fp, &Length1 ) && Length1 )
            {
                StackSetMaxS( &Setting->Buffer, Length1 );
                Buffer = StackBaseS( &Setting->Buffer );
                if ( fread( Buffer, 1, Length1, Fp ) == Length1 )
                    Flags |= 1;
            }
        }

        if ( FormatId >= 0x77836D4D )
        {
            /* Read obfuscation current level */
            if ( ReadInteger( Fp, &Dummy ) )
            {
                Setting->State |= ( Dummy << GS_STATE_OBFUSCATION_CURRENT_LEVEL_SHIFT );
                if ( Dummy > 2 )
                    Setting->State |= GS_STATE_OBFUSCATE;
            }
        }

        ReadInteger( Fp, &Length2 );
        ReadInteger( Fp, &Data );

#if 0
        {
            ULONG BufferUlong[16];
            TCHAR InfoBuffer[256];

            if ( Length2 )
            {
                /* Encode file data */
                StackSetMaxS( &Setting->Buffer, Length2 );
                Buffer = StackBaseS( &Setting->Buffer );
                if ( fread( Buffer, 1, Length2, Fp ) == Length2 )
                    Flags |= 2;
            }

            if ( Flags & 1 )
            {
                typedef void ( *sub_C064E0_fun ) ( ULONG*, TCHAR*, ULONG );
                typedef void ( *sub_C06EC0_fun ) ( ULONG*, TCHAR* );

                sub_C064E0_fun sub_C064E0 = ( sub_C064E0_fun )0xC064E0;
                sub_C06EC0_fun sub_C06EC0 = ( sub_C06EC0_fun )0xC06EC0;

                BufferUlong[0] = 0;
                BufferUlong[1] = 0;
                BufferUlong[2] = 0x67452301;
                BufferUlong[3] = 0xEFCDAB89;
                BufferUlong[4] = 0x10325476;

                sub_C064E0( BufferUlong, Buffer, Dummy );
                sub_C06EC0( BufferUlong, ( TCHAR* )TSRMG_GET( 0x1C ) + 0xDC );
            }

            {
                typedef LONG ( *sub_C0A2B0_fun ) ( TCHAR *, ULONG, TCHAR *, ULONG, ULONG );
                Dummy = ( ( sub_C0A2B0_fun )0xC0A2B0 ) ( Buffer, Length2, InfoBuffer, Data, 0xC841D0 );
            }
        }
#endif

        /* Set encode state */
        Setting->State |= GS_STATE_OP_ENCODE;

        /* Get encode version */
        Count = SIZE_OF_ARRAY( FormatIdToVersion );
        for ( Iter = 0; Iter < Count; Iter++ )
        {
            if ( FormatIdToVersion[Iter].Key <= FormatId && FormatId < FormatIdToVersion[Iter + 1].Key )
            {
                Setting->Version = FormatIdToVersion[Iter].Value;
                break;
            }
        }

        /* Add internal obfuscate function and class */
        if ( Setting->State & GS_STATE_OBFUSCATE && !( Setting->State & GS_STATE_ADD_OBFUSCATE ) )
        {
            AddObfuscateClass( GET_GS_CLASS_TABLE( ) );
            AddObfuscateFunction( GET_GS_FUNCTION_TABLE( ) );
            Setting->State |= GS_STATE_ADD_OBFUSCATE;
        }

        RetCode = TRUE;
    } while ( 0 );

    /* Import obfuscate name */
    if ( Setting->Flags & GS_FLAGS_IMPORT && ( Setting->Flags & GS_FLAGS_FORCE || Setting->State & GS_STATE_OBFUSCATE ) )
    {
        if ( Setting->ConfigFile[0] == _T( '\0' ) )
            _tcscpy( Setting->ConfigFile, DEFAULT_CONFIG_FILE );

        if ( Setting->Flags & GS_FLAGS_FULL )
            ImportObfuscate( );
        else
            ImportObfuscateName( );
    }

    /* Export obfuscate name */
    if ( Setting->Flags & GS_FLAGS_EXPORT )
    {
        if ( Setting->ConfigFile[0] == _T( '\0' ) )
            _tcscpy( Setting->ConfigFile, DEFAULT_CONFIG_FILE );

        if ( Setting->Flags & GS_FLAGS_FULL )
            ExportObfuscate( );
        else
            ExportObfuscateName( );
    }

    if ( Flags & FLAGS_LOCKED )
        UNLOCK_GS( );

    if ( Fp )
        fclose( Fp );

    return RetCode;
}

/*
///////////////////////////////////////////////////////////////////////////////
// UninitGlobalSettingRuntime
///////////////////////////////////////////////////////////////////////////////
*/
void UninitGlobalSettingRuntime( )
{
}

LONG StackAllocFail( PVOID Stack, STACK_TYPE Type, PVOID Context )
{
    if ( GET_GS_FLAGS( ) & GS_FLAGS_FORCE )
    {
        _tprintf( _T( "[Alloc Fail]" ) );
    }
    else
    {
        throw_ex( 1 );
    }

    return 0;
}

void InitDestroyStart( )
{
    /* For Destroy */
}

void PrintHelp( )
{
    _tprintf( GET_HELP_INFOMATION( ),
        DEFAULT_LOG_FILE, DEFAULT_INDENT, DEFAULT_STACK_SIZE, DEFAULT_STRING_LENGTH, DEFAULT_DECODE_LEVEL_HIGH, DEFAULT_DECODE_LEVEL_LOW,
        DEFAULT_FILE_EXTENSION_PRINT, DEFAULT_CONFIG_FILE, DEFAULT_LOG_FILE
#if !PRIVATE_VERSION
        , DEFAULT_OBFUSCATE_PREFIX_PRINT
#endif
        );
}

ULONG FASTCALL CallbackGetLogType( LPCTSTR Argument, PINI_GLOBAL_SETTING Setting )
{
    ULONG *LogType;

    if ( Argument )
    {
        LogType = ( ULONG* )Setting->SetValuePtr;
        if ( 0 == _tcsicmp( Argument, _T( "file" ) ) )
            *LogType = LOG_FILE;
        else if ( 0 == _tcsicmp( Argument, _T( "registry" ) ) )
            *LogType = LOG_REGISTRY;
        else if ( 0 == _tcsicmp( Argument, _T( "debug" ) ) )
            *LogType = LOG_DEBUG_STRING;
        else if ( 0 == _tcsicmp( Argument, _T( "messagebox" ) ) )
            *LogType = LOG_MESSAGEBOX;
        else
            *LogType = LOG_NONE;
    }

    return TRUE;
}

ULONG FASTCALL CallbackEncodeString( LPCTSTR Argument, PINI_GLOBAL_SETTING Setting )
{
    ULONG Dummy;

    if ( Argument )
    {
        if ( *Argument == _T( ':' ) )
            Argument++;

        _tcsncpy( Setting->SetValuePtr, Argument, Setting->Data );
        ( ( LPTSTR )Setting->SetValuePtr )[Setting->Data - 1] = _T( '\0' );
        ENCODE_STR( Dummy, ( LPTSTR )Setting->SetValuePtr );
    }

    return TRUE;
}

ULONG FASTCALL CallbackInitCommandLine( LPCTSTR lptszStart, PINI_GLOBAL_SETTING IniSetting )
{
    if ( lptszStart[1] == _T( '\0' ) )
    {
        switch ( lptszStart[0] )
        {
        case _T( 'd' ) :
            GET_GS( )->Flags |= GS_FLAGS_DETAIL;
            break;
        case _T( 'i' ) :
            GET_GS( )->Flags |= GS_FLAGS_IMPORT;
            break;
        case _T( 'e' ) :
            GET_GS( )->Flags |= GS_FLAGS_EXPORT;
            break;
        case _T( 'a' ) :
            GET_GS( )->Flags |= GS_FLAGS_APPEND;
            break;
        case _T( 'b' ) :
            GET_GS( )->Flags |= GS_FLAGS_BACKUP;
            break;
        case _T( 'f' ) :
            GET_GS( )->Flags |= GS_FLAGS_FORCE;
            break;
        case _T( 'r' ) :
            GET_GS( )->Flags |= ( GS_FLAGS_DETAIL | GS_FLAGS_RAW );
            break;
        case _T( 't' ) :
            GET_GS( )->Flags |= GS_FLAGS_TICK;
            break;
        case _T( 'h' ) :
        case _T( '?' ) :
            PrintHelp( );
        default :
            return FALSE;
        }
    }
    else if ( lptszStart[2] == _T( '\0' ) )
    {
        if ( lptszStart[0] == _T( 'o' ) && lptszStart[1] == _T( 'p' ) )
            GET_GS( )->Flags |= ( GS_FLAGS_DETAIL | GS_FLAGS_OPCODE );
        else if ( lptszStart[0] == _T( 'o' ) && lptszStart[1] == _T( 'b' ) )
            GET_GS( )->Flags |= GS_FLAGS_OBFUSCATE;
        else
            return FALSE;
    }
    else if ( lptszStart[3] == _T( '\0' ) )
    {
        if ( lptszStart[0] == _T( 'b' ) && lptszStart[1] == _T( 'u' ) && lptszStart[2] == _T( 'g' ) )
            GET_GS( )->Flags |= GS_FLAGS_BUG;
        else if ( lptszStart[0] == _T( 'e' ) && lptszStart[1] == _T( 'x' ) && lptszStart[2] == _T( 'e' ) )
            GET_GS( )->Flags |= GS_FLAGS_EXECUTE;
        else if ( lptszStart[0] == _T( 'd' ) && lptszStart[1] == _T( 'i' ) && lptszStart[2] == _T( 'c' ) )
            GET_GS( )->Flags |= GS_FLAGS_OBFUSCATE_DIC;
        else if ( lptszStart[0] == _T( 'e' ) && lptszStart[1] == _T( 'x' ) && lptszStart[2] == _T( 't' ) )
            GET_GS( )->OutputExt[0] = _T( '\0' );
        else if ( lptszStart[0] == _T( 't' ) && lptszStart[1] == _T( 'a' ) && lptszStart[2] == _T( 'b' ) )
            GET_GS( )->IndentChar[0] = _T( '\t' ), GET_GS( )->Indent = 1;
        else
            return FALSE;
    }
    else if ( lptszStart[4] == _T( '\0' ) && 0 == _tcsicmp( lptszStart, _T( "help" ) ) )
    {
        PrintHelp( );
    }
    else
    {
        /* Not handle */
        return FALSE;
    }

    return TRUE;
}

/*
///////////////////////////////////////////////////////////////////////////////
// InitGlobalSetting
///////////////////////////////////////////////////////////////////////////////
*/
ULONG InitGlobalSetting( )
{
    ULONG RetCode;
    ULONG Dummy;
    PGLOBAL_SETTING Setting;
    PDUMP_STACK Stack;
    LPCTSTR lptszCommandLine;
    COMMON_STACK CommandList;
    INI_GLOBAL_SETTING IniSetting[] = {
        /* Call back */
        { _T( "PHP_DECODE_LOGTYPE" ), _T( "logtype:" ), 8, &GET_GS( )->LogType, CallbackGetLogType, 0, IGS_FLAGS_CALLBACK },
#if PRIVATE_VERSION
        /* Flags */
        { _T( "PHP_DECODE_BUG" ), _T( "bug" ), 3, &GET_GS( )->Flags, NULL, GS_FLAGS_BUG, IGS_FLAGS_SET_FLAGS },
        { _T( "PHP_DECODE_DEBUG" ), _T( "debug" ), 5, &GET_GS( )->Flags, NULL, GS_FLAGS_DEBUG, IGS_FLAGS_SET_FLAGS },
        /* Call back */
        { _T( "PHP_DECODE_HEAD" ), _T( "head" ), 4, &GET_GS( )->FileHead, CallbackEncodeString, SIZE_OF_ARRAY( Setting->FileHead ) - 1, IGS_FLAGS_CALLBACK },
        { _T( "PHP_DECODE_TAIL" ), _T( "tail" ), 4, &GET_GS( )->FileTail, CallbackEncodeString, SIZE_OF_ARRAY( Setting->FileTail ) - 1, IGS_FLAGS_CALLBACK },
        { _T( "PHP_DECODE_COMMENT" ), _T( "comment" ), 7, &GET_GS( )->FileComment, CallbackEncodeString, SIZE_OF_ARRAY( Setting->FileComment ) - 1, IGS_FLAGS_CALLBACK },
        { _T( "PHP_DECODE_PREFIX" ), _T( "prefix" ), 6, &GET_GS( )->ObfuscatePrefix, CallbackEncodeString, SIZE_OF_ARRAY( Setting->ObfuscatePrefix ) - 1, IGS_FLAGS_CALLBACK },
#endif
        { _T( "PHP_DECODE_EXT" ), _T( "ext" ), 3, &GET_GS( )->OutputExt, CallbackEncodeString, SIZE_OF_ARRAY( Setting->OutputExt ) - 1, IGS_FLAGS_CALLBACK },
        /* Flags */
        { _T( "PHP_DECODE_DETAIL" ), _T( "detail" ), 6, &GET_GS( )->Flags, NULL, GS_FLAGS_DETAIL, IGS_FLAGS_SET_FLAGS },
        { _T( "PHP_DECODE_OPCODE" ), _T( "opcode" ), 6, &GET_GS( )->Flags, NULL, GS_FLAGS_DETAIL | GS_FLAGS_OPCODE, IGS_FLAGS_SET_FLAGS },
        { _T( "PHP_DECODE_OPARRAY" ), _T( "oparray" ), 7, &GET_GS( )->Flags, NULL, GS_FLAGS_OPARRAY, IGS_FLAGS_SET_FLAGS },
        { _T( "PHP_DECODE_FUNCTION" ), _T( "function" ), 8, &GET_GS( )->Flags, NULL, GS_FLAGS_FUNCTION, IGS_FLAGS_SET_FLAGS },
        { _T( "PHP_DECODE_CLASS" ), _T( "class" ), 5, &GET_GS( )->Flags, NULL, GS_FLAGS_CLASS, IGS_FLAGS_SET_FLAGS },
        { _T( "PHP_DECODE_HASH" ), _T( "hash" ), 4, &GET_GS( )->Flags, NULL, GS_FLAGS_HASH, IGS_FLAGS_SET_FLAGS },
        { _T( "PHP_DECODE_INFO" ), _T( "info" ), 4, &GET_GS( )->Flags, NULL, GS_FLAGS_INFO, IGS_FLAGS_SET_FLAGS },
        { _T( "PHP_DECODE_RAW" ), _T( "raw" ), 3, &GET_GS( )->Flags, NULL, GS_FLAGS_DETAIL | GS_FLAGS_RAW, IGS_FLAGS_SET_FLAGS },
        { _T( "PHP_DECODE_EXECUTE" ), _T( "execute" ), 7, &GET_GS( )->Flags, NULL, GS_FLAGS_EXECUTE, IGS_FLAGS_SET_FLAGS },
        { _T( "PHP_DECODE_REPLACE" ), _T( "backup" ), 6, &GET_GS( )->Flags, NULL, GS_FLAGS_BACKUP, IGS_FLAGS_SET_FLAGS },
        { _T( "PHP_DECODE_APPEND" ), _T( "append" ), 6, &GET_GS( )->Flags, NULL, GS_FLAGS_APPEND, IGS_FLAGS_SET_FLAGS },
        { _T( "PHP_DECODE_TICK" ), _T( "tick" ), 4, &GET_GS( )->Flags, NULL, GS_FLAGS_TICK, IGS_FLAGS_SET_FLAGS },
        { _T( "PHP_DECODE_NOEXPIRE" ), _T( "noexpire" ), 8, &GET_GS( )->Flags, NULL, GS_FLAGS_NOEXPIRE, IGS_FLAGS_SET_FLAGS },
        { _T( "PHP_DECODE_NOINDENT" ), _T( "noindent" ), 8, &GET_GS( )->Flags, NULL, GS_FLAGS_NOINDENT, IGS_FLAGS_SET_FLAGS },
        { _T( "PHP_DECODE_COMPACT" ), _T( "compact" ), 7, &GET_GS( )->Flags, NULL, GS_FLAGS_COMPACT, IGS_FLAGS_SET_FLAGS },
        { _T( "PHP_DECODE_CLASSIC" ), _T( "classic" ), 7, &GET_GS( )->Flags, NULL, GS_FLAGS_CLASSIC, IGS_FLAGS_SET_FLAGS },
        { _T( "PHP_DECODE_FULL" ), _T( "full" ), 4, &GET_GS( )->Flags, NULL, GS_FLAGS_FULL, IGS_FLAGS_SET_FLAGS },
        { _T( "PHP_DECODE_FORCE" ), _T( "force" ), 5, &GET_GS( )->Flags, NULL, GS_FLAGS_FORCE, IGS_FLAGS_SET_FLAGS },
        { _T( "PHP_DECODE_IMPORT" ), _T( "import" ), 6, &GET_GS( )->Flags, NULL, GS_FLAGS_IMPORT, IGS_FLAGS_SET_FLAGS },
        { _T( "PHP_DECODE_EXPORT" ), _T( "export" ), 6, &GET_GS( )->Flags, NULL, GS_FLAGS_EXPORT, IGS_FLAGS_SET_FLAGS },
        { _T( "PHP_DECODE_OBFUSCATE" ), _T( "obfuscate" ), 9, &GET_GS( )->Flags, NULL, GS_FLAGS_OBFUSCATE, IGS_FLAGS_SET_FLAGS },
        { _T( "PHP_DECODE_DIC" ), _T( "dic" ), 3, &GET_GS( )->Flags, NULL, GS_FLAGS_OBFUSCATE_DIC, IGS_FLAGS_SET_FLAGS },
        /* Char */
        { _T( "PHP_DECODE_TAB" ), _T( "tab" ), 3, &GET_GS( )->IndentChar[0], NULL, _T( '\t' ), IGS_FLAGS_SET_CHAR },
        /* Number */
        { _T( "PHP_DECODE_INDENT" ), _T( "indent:" ), 7, &GET_GS( )->Indent, NULL, 0, IGS_FLAGS_SET_NUMBER },
        { _T( "PHP_DECODE_STACK" ), _T( "stack:" ), 6, &GET_GS( )->StackSize, NULL, 0, IGS_FLAGS_SET_NUMBER },
        { _T( "PHP_DECODE_STRING" ), _T( "string:" ), 7, &GET_GS( )->StackStringLength, NULL, 0, IGS_FLAGS_SET_NUMBER },
        /* Multi number */
        { _T( "PHP_DECODE_LEVEL" ), _T( "level:" ), 6, &GET_GS( )->DecodeLevelHigh, &GET_GS( )->DecodeLevelLow, 2, IGS_FLAGS_SET_NUMBER_N },
        /* String */
        { _T( "PHP_DECODE_ROOT" ), _T( "root" ), 4, &GET_GS( )->RootPath, NULL, SIZE_OF_ARRAY( Setting->RootPath ) - 1, IGS_FLAGS_SET_STRING },
        { _T( "PHP_DECODE_PATH" ), _T( "path" ), 4, &GET_GS( )->OutputPath, NULL, SIZE_OF_ARRAY( Setting->OutputPath ) - 1, IGS_FLAGS_SET_STRING },
        { _T( "PHP_DECODE_FILE" ), _T( "file" ), 4, &GET_GS( )->OutputFile, NULL, SIZE_OF_ARRAY( Setting->OutputFile ) - 1, IGS_FLAGS_SET_STRING },
        { _T( "PHP_DECODE_CONFIG" ), _T( "config" ), 6, &GET_GS( )->ConfigFile, DEFAULT_CONFIG_FILE, SIZE_OF_ARRAY( Setting->ConfigFile ) - 1, IGS_FLAGS_SET_STRING },
        { _T( "PHP_DECODE_LOG" ), _T( "log" ), 3, &GET_GS( )->LogFile, DEFAULT_LOG_FILE, SIZE_OF_ARRAY( Setting->LogFile ) - 1, IGS_FLAGS_SET_STRING },
        /* Ini */
        { _T( "PHP_DECODE_INI" ), _T( "ini" ), 3, _T( "PHPRC" ), DEFAULT_INI_PATH, 0, IGS_FLAGS_COMPARE_SET },
    };

    do
    {
        RetCode = FALSE;
        Setting = GET_GS( );

        /* Initiate lock */
        InitializeCriticalSection( &Setting->Lock );

        /* Initiate using stack list and lock */
        InitializeListHead( &Setting->StackList );
        InitializeCriticalSection( &Setting->StackListLock );

        /* Initiate free stack list and lock */
        InitializeListHead( &Setting->FreeStackList );
        InitializeCriticalSection( &Setting->FreeStackListLock );

        /* Initiate Obfuscate name list and lock */
        InitializeListHead( &Setting->ObfuscateName );
        InitializeCriticalSection( &Setting->ObfuscateNameLock );

        /* Set stack allocate fail call back */
        StackSetAllocFail( StackAllocFail, NULL );

        /* Initiate stack pointer list */
        StackInitU( &Setting->StackPtrList, 0 );

        /* Initiate class pointer list */
        StackInitU( &Setting->Class, 0 );

        /* Initiate function pointer list */
        StackInitU( &Setting->Function, 0 );

        /* Initiate function flags list */
        StackInitU( &Setting->FunctionFlags, 0 );

        /* Initiate file name */
        StackInit( &Setting->FileName, 0 );

        /* Initiate class name */
        StackInit( &Setting->ClassName, 0 );

        /* Initiate function name */
        StackInit( &Setting->FunctionName, 0 );

        /* Initiate string buffer */
        StackInitS( &Setting->Buffer, 0 );
        StackInitS( &Setting->Buffer1, 0 );

        /* Initiate ok */
        Setting->Init = TRUE;

#if !PRIVATE_VERSION
        if ( CheckIfTrace( ) )
        {
            /* Check if being tracing */
            Setting->State |= GS_STATE_CHECK_TRACE;
        }

        if ( GET_GS( )->State & ( GS_STATE_CHECK_MODIFY | GS_STATE_CHECK_TRACE ) )
            break;
#endif

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
        ParseCommandLineSetting( &IniSetting[0], SIZE_OF_ARRAY( IniSetting ), &CommandList, NULL, CallbackInitCommandLine );

        /* Un-initiate command list */
        StackUninit( &CommandList );

        /* If show info or dump obfuscate dictionary then set log file */
        if ( Setting->Flags & GS_FLAGS_INFO || Setting->Flags & GS_FLAGS_OBFUSCATE_DIC )
        {
            /* Set to default log file */
            if ( Setting->LogFile[0] == _T( '\0' ) )
                _tcscpy( Setting->LogFile, DEFAULT_LOG_FILE );
        }

        /* Decode */
        DECODE_STR( Dummy, Setting->OutputExt );
        RetCode = TRUE;
    } while ( 0 );

    /* Hook time function to prevent file expire */
    if ( Setting->Flags & GS_FLAGS_NOEXPIRE )
        HookTime( );

    /* Allocate stack */
    AllocateStack( Setting->StackSize, Setting->StackStringLength, 1 );

    /* Allocate stack from pool */
    Stack = AllocateStackFromPool( Setting->StackSize, Setting->StackStringLength );
    if ( Stack )
    {
        /* Free to pool for global use */
        FreeStackToPool( Stack );
        SET_GS_STACK( Stack );
        PUSH_INDENT( Stack, 0 );
    }

    return RetCode;
}

void InitDestroyEnd( )
{
    /* For Destroy */
}

/*
///////////////////////////////////////////////////////////////////////////////
// UninitGlobalSetting
///////////////////////////////////////////////////////////////////////////////
*/
void UninitGlobalSetting( )
{
    PGLOBAL_SETTING Setting;
    register PLIST_ENTRY ListEntry;
    register PDUMP_STACK Stack;

    Setting = GET_GS( );
    /* Set quitting flags */
    Setting->Flags |= GS_IFLAGS_QUITTING;

    EnterCriticalSection( &Setting->Lock );

    /* Clear stack allocate fail call back */
    StackSetAllocFail( NULL, NULL );

    /* Un-initiate obfuscate name list and lock */
    CleanupObfuscateName( );
    DeleteCriticalSection( &Setting->ObfuscateNameLock );

    /* Un-initiate using stack list and lock */
    EnterCriticalSection( &Setting->StackListLock );
    while ( ( ListEntry = RemoveHeadList( &Setting->StackList ) ) )
    {
        Stack = CONTAINING_RECORD( ListEntry, DUMP_STACK, ListEntry );
        FreeStack( Stack );
    }
    LeaveCriticalSection( &Setting->StackListLock );
    DeleteCriticalSection( &Setting->StackListLock );

    /* Un-initiate free stack list and lock */
    EnterCriticalSection( &Setting->FreeStackListLock );
    while ( ( ListEntry = RemoveHeadList( &Setting->FreeStackList ) ) )
    {
        Stack = CONTAINING_RECORD( ListEntry, DUMP_STACK, ListEntry );
        FreeStack( Stack );
    }
    LeaveCriticalSection( &Setting->FreeStackListLock );
    DeleteCriticalSection( &Setting->FreeStackListLock );

    /* Un-initiate stack pointer list */
    StackUninitU( &Setting->StackPtrList );

    /* Un-initiate class pointer list */
    StackUninitU( &Setting->Class );

    /* Un-initiate function pointer list */
    StackUninitU( &Setting->Function );

    /* Initiate function flags list */
    StackUninitU( &Setting->FunctionFlags );

    /* Un-initiate file name */
    StackUninit( &Setting->FileName );

    /* Un-initiate class name */
    StackUninit( &Setting->ClassName );

    /* Un-initiate function name */
    StackUninit( &Setting->FunctionName );

    /* Un-initiate string buffer */
    StackUninitS( &Setting->Buffer );
    StackUninitS( &Setting->Buffer1 );

    /* Delete global settings lock */
    LeaveCriticalSection( &Setting->Lock );
    DeleteCriticalSection( &Setting->Lock );

    Setting->Init = FALSE;
}

void dummy_end( )
{
    /* Just for count */
}

/*
///////////////////////////////////////////////////////////////////////////////
// Init
///////////////////////////////////////////////////////////////////////////////
*/
void DUMP_API Init( )
{
    if ( !GET_GS( )->Init )
    {
#if !PRIVATE_VERSION
        register ULONG Dummy;
        register TCHAR *ModuleFile;

        /* Module file name */
        ModuleFile = GET_GS( )->ModuleFile;

        /* Decode file name */
        DECODE_STR( Dummy, ModuleFile );

        /* Get module base address */
        GET_GS( )->ModuleBase = GetModuleHandle( ModuleFile );

        /* Remove code protection */
        RemoveCodeProtection( GET_GS( )->ModuleBase );

        /* Decode code and data for other stub decoding */
        DecodeInternalStub( NULL );

        /* Decode key for other stub decoding */
        DecodeStubKey( NULL, ModuleFile );

        /* Encode file name */
        ENCODE_STR( Dummy, ModuleFile );

        /* Decode main code and data */
        DecodeStub( GET_STUB( ) );

        /* Decode main local string */
        DecodeLocalString( );

        /* Recover code protection */
        RecoverCodeProtection( GET_GS( )->ModuleBase );
#endif

        /* Initiate global setting from command line or environment */
        InitGlobalSetting( );

        /* Dump log */
        set_dump_file( GET_GS( )->LogFile, !( GET_GS_FLAGS( ) & GS_FLAGS_APPEND ), FALSE );

#if !PRIVATE_VERSION
        /* Destroy code that don't use any more */
        DestroyCode( ( UCHAR* )InitDestroyStart, ( UCHAR* )InitDestroyEnd );
#endif
    }
}

/*
///////////////////////////////////////////////////////////////////////////////
// Uninit
///////////////////////////////////////////////////////////////////////////////
*/
void DUMP_API Uninit( )
{
    if ( GET_GS( )->Init )
    {
        /* Un-initiate global setting */
        UninitGlobalSetting( );

        /* Un-initiate log */
        UNINIT_LOG( );

#if !PRIVATE_VERSION
        /* Destroy code that don't use any more */
        DestroyCode( ( UCHAR* )dummy_start, ( UCHAR* )dummy_end );
#endif
    }
}

void dummy_start_1( )
{
    /* Just for count */
}

/*
///////////////////////////////////////////////////////////////////////////////
// pre_compile
///////////////////////////////////////////////////////////////////////////////
*/
void pre_compile( )
{
    /* For debug */
    if ( GET_GS_FLAGS( ) & GS_FLAGS_DEBUG )
        DebugBreak( );

    InitGlobalSettingPreCompile( );
}

/*
///////////////////////////////////////////////////////////////////////////////
// post_execute
///////////////////////////////////////////////////////////////////////////////
*/
void post_execute( )
{
    /* For debug */
    if ( GET_GS_FLAGS( ) & GS_FLAGS_DEBUG )
        DebugBreak( );

    UninitGlobalSettingPreCompile( );
}

/*
///////////////////////////////////////////////////////////////////////////////
// dump_op_array
///////////////////////////////////////////////////////////////////////////////
*/
void dump_op_array( zend_op_array *OpArray, ULONG Indent )
{
    /* Initiate global setting with executing environment */
    InitGlobalSettingRuntime( OpArray );

    /* Dump general information */
    dump_info( Indent );

    /* Dump general information about op code array */
    dump_op_array_interface( OpArray );

    /* Dump tick first time */
    dump_tick( );

    /* Init file name */
    init_dump_file( get_file_name( ) );

    /* Dump source */
    set_dump_source( );

    /* Dump file head */
    dump_file_head( );

    /* Dump file comment */
    dump_file_comment( );

#ifdef _MSC_VER
    __try
#else
    try_ex
#endif
    {
        /* Dump class */
        dump_class_table( GET_GS_CLASS_TABLE( ), Indent );

        /* Dump function */
        dump_function_table( GET_GS_FUNCTION_TABLE( ), Indent );

        /* Dump main */
        dump_op_array_ex( OpArray, Indent, DS_STATE_MAIN );
    }
#ifdef _MSC_VER
    __except ( EXCEPTION_EXECUTE_HANDLER )
#else
    catch_ex
#endif
    {
        /* Handle exception so that we can free resource */
        ADD_LOG_LR( _T( "\r\n[exception occured]\r\n" ) );

        /* Start */
        ADD_LOG_LR( _T( "================================" ) );

        /* Exception code */
        ADD_DEBUG_LOG_LR( _T( "Exception code[ %08X ]" ), exception_code_ex( ) );

        /* Executive object */
        ADD_DEBUG_LOG_LR( _T( "Compiler[ %08X ]" ), GET_GS( )->GCompiler );
        ADD_DEBUG_LOG_LR( _T( "Executor[ %08X ]" ), GET_GS( )->GExecutor );

        /* Op array */
        ADD_DEBUG_LOG_LR( _T( "OpArray[ %08X ]" ), GET_GS_OPARRAY( ) );

        /* Dump current file name if any or else main */
        ADD_DEBUG_LOG_LR( _T( "File< %s >" ), get_file_name( ) );

        /* Dump current class name if any or else main */
        ADD_DEBUG_LOG_LR( _T( "Class< %s >" ), get_class_name( ) );

        /* Dump current function name if any or else main */
        ADD_DEBUG_LOG_LR( _T( "Function< %s >" ), get_function_name( ) );

        /* Stack */
        ADD_DEBUG_LOG_LR( _T( "Stack[ %08X ]" ), GET_GS_STACK( ) );
        if ( GET_GS_STACK( ) )
        {
            /* Dump step */
            ADD_DEBUG_LOG_LR( _T( "Step[ %d ]" ), GET_GS_STACK( )->Step );
            /* Dump op code offset */
            ADD_DEBUG_LOG_LR( _T( "Offset[ %d ]" ), GET_GS_STACK( )->Offset );
            /* Last op code offset */
            ADD_DEBUG_LOG_LR( _T( "LastOffset[ %d ]" ), GET_GS_STACK( )->LastOffset );
            /* Dump current op code if any */
            dump_opcode_detail_ex( GET_GS_STACK( ) );
        }

        /* End */
        ADD_LOG_LR( _T( "================================" ) );
#ifdef _MSC_VER
    }
#else
    } end_try_ex( );
#endif

    /* Dump obfuscate name */
    dump_obfuscate_name( );

    /* Dump file tail */
    dump_file_tail( );

    /* Dump log */
    set_dump_log( );

    /* Dump tick second time */
    dump_tick( );

    /* Pop function name */
    pop_function_name( );

    /* Pop file name */
    pop_function_name( );

    /* Un-initiate global setting */
    UninitGlobalSettingRuntime( );
}

void DecodeLocalString( )
{
#if !PRIVATE_VERSION
    /* Encode range */
    static ENCODE_RANGE Range[] = {
        { &g_DummyMainStart_1, _T( "PHP" ) - sizeof( ENCODE_RANGE ) * 2 - sizeof( ENCODE_STUB ) - 8, ES_FLAGS_ENCODE_1 },
        { ( UCHAR* )&g_Setting + FIELD_OFFSET( GLOBAL_SETTING, ObfuscatePrefix ), &g_SettingPtr, ES_FLAGS_ENCODE_1 },
    };

    /* Encode stub */
    static ENCODE_STUB Stub = {
        TYPE_ENCODE_LOCAL,
        sizeof( ENCODE_STUB ),
        0,
        0,
        DEFAULT_ENCODE_KEY,
        DEFAULT_ENCODE_KEY_LENGTH,
        { 0 },
        0,
        { 0 },
        SIZE_OF_ARRAY( Range ),
        Range
    };
    DecodeStub( &Stub );
#endif
}

void dummy_end_1( )
{
    /* Just for count */
}

/*
BOOL WINAPI DllMain(
    HANDLE hModule,
    ULONG Reason,
    LPVOID lpReserved
    )
{
    switch ( Reason )
    {
    case DLL_PROCESS_ATTACH :
        break;

    case DLL_PROCESS_DETACH :
        break;
    }

    return TRUE;
}
*/