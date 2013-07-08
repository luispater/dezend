/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   AddLog.h
//  Version     :   1.0
//  Creator     :   RM
//  Create Date :   2006-01-01
//  Comment     :
//
///////////////////////////////////////////////////////////////////////////////
*/

#ifndef __ADDLOG_H__
#define __ADDLOG_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/
#ifndef SIZE_OF_ARRAY
#define SIZE_OF_ARRAY( Array ) ( sizeof( Array ) / sizeof( ( Array )[0] ) )
#endif

#define LOG_POSITION_BEGIN 0
#define LOG_POSITION_CURRENT 1
#define LOG_POSITION_END 2

#if defined( _DISABLE_LOG_FUNC_ )

#define IS_LOG_ENABLED( ) 0
#define IS_LOG_TIME_ENABLED( ) 0

#define INIT_LOG( LogData, LogMethod, Enable )
#define UNINIT_LOG( )

#define SET_LOG_HANDLE( Handle )
#define GET_LOG_HANDLE( )

#define SET_LOG_METHOD( LogMethod )
#define GET_LOG_METHOD( )
#define ADD_DEBUG_LOGA
#define ADD_DEBUG_LOGW
#define ADD_DEBUG_LOG_LRA
#define ADD_DEBUG_LOG_LRW
#define ADD_LOGA
#define ADD_LOGW
#define ADD_LOG_LRA
#define ADD_LOG_LRW
#define BACK_LOG
#define BACK_LOG_EX
#define CLEAR_LOG
#define ENABLE_LOG
#define DISABLE_LOG
#define ENABLE_LOG_TIME
#define DISABLE_LOG_TIME

#else

#if defined( _UNICODE ) || defined( _UNICODE )
#define AddLog_File AddLog_FileW
#define AddLog_Reg AddLog_RegW
#define AddLog_Control AddLog_ControlW
#else
#define AddLog_File AddLog_FileA
#define AddLog_Reg AddLog_RegA
#define AddLog_Control AddLog_ControlA
#endif

#define IS_LOG_ENABLED( ) IsLogEnabled( )
#define IS_LOG_TIME_ENABLED( ) IsLogTimeEnabled( )

#define INIT_LOG( LogData, LogMethod, Enable ) InitLog( LogData, LogMethod, Enable )
#define UNINIT_LOG( ) UnInitLog( )

#define SET_LOG_HANDLE( Handle ) SetLogHandle( Handle )
#define GET_LOG_HANDLE( ) GetLogHandle( Handle )

#define SET_LOG_METHOD( LogMethod ) SetLog_Method( LogMethod )
#define GET_LOG_METHOD( ) GetLog_Method( )
#define ADD_DEBUG_LOGA AddLogA
#define ADD_DEBUG_LOGW AddLogW
#define ADD_DEBUG_LOG_LRA AddLogLRA
#define ADD_DEBUG_LOG_LRW AddLogLRW
#define ADD_LOGA _AddLogA
#define ADD_LOGW _AddLogW
#define ADD_LOG_LRA _AddLogLRA
#define ADD_LOG_LRW _AddLogLRW
#define BACK_LOG BackLog
#define BACK_LOG_EX BackLogEx
#define CLEAR_LOG ClearLog
#define ENABLE_LOG EnableLog
#define DISABLE_LOG DisableLog
#define ENABLE_LOG_TIME EnableLogTime
#define DISABLE_LOG_TIME DisableLogTime

#define LOG_BUFFER_SIZE 1024

/* Log Method */
enum LOG_METHOD {
    LOG_MIN,
    LOG_NONE,
    LOG_FILE, LOG_REGISTRY, LOG_CONTROL,
    LOG_DEBUG_STRING, LOG_MESSAGEBOX,
    LOG_MAX
};

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
ULONG IsLogEnabled( void );
ULONG IsLogTimeEnabled( void );

ULONG SetLogHandle( HANDLE );
HANDLE GetLogHandle( );

ULONG SetLog_Method( ULONG LogMethod );
ULONG GetLog_Method( );

ULONG InitLog( const PVOID LogData, ULONG LogMethod, ULONG Enable );
ULONG UnInitLog( void );

ULONG LogTimeA( CHAR *, ULONG );
ULONG LogTimeW( WCHAR *, ULONG );

ULONG _AddLogA( const CHAR * );
ULONG _AddLogW( const WCHAR * );
ULONG _AddLogLRA( const CHAR * );
ULONG _AddLogLRW( const WCHAR * );

ULONG AddLogA( const CHAR * aszFormat, ... );
ULONG AddLogW( const WCHAR * wszFormat, ... );
ULONG AddLogLRA( const CHAR * aszFormat, ... );
ULONG AddLogLRW( const WCHAR * wszFormat, ... );

/* BackLog */
LONG BackLog( LONG Distance, ULONG Position );
LONGLONG BackLogEx( LONGLONG Distance, ULONG Position );
/* Clear log */
void ClearLog( void );
/* Enable/Disable log */
void EnableLog( void );
void DisableLog( void );
/* Enable/Disable log time */
void EnableLogTime( void );
void DisableLogTime( void );

/* LOG_FILE */
ULONG InitLog_File( void );
ULONG UnInitLog_File( void );
ULONG ClearLog_File( void );

ULONG AddLog_FileA( );
ULONG AddLog_FileW( );

/* LOG_REGISTRY */
ULONG InitLog_Reg( void );
ULONG UnInitLog_Reg( void );
ULONG ClearLog_Reg( void );

ULONG AddLog_RegA( );
ULONG AddLog_RegW( );

/* LOG_CONCTROL */
ULONG InitLog_Control( void );
ULONG UnInitLog_Control( void );
ULONG ClearLog_Control( void );

ULONG AddLog_ControlA( );
ULONG AddLog_ControlW( );

#endif /* _DISABLE_LOG_FUNC_ */

#if defined( _UNICODE ) || defined( UNICODE )
#define ADD_DEBUG_LOG ADD_DEBUG_LOGW
#define ADD_DEBUG_LOG_LR ADD_DEBUG_LOG_LRW
#define ADD_LOG ADD_LOGW
#define ADD_LOG_LR ADD_LOG_LRW
#else
#define ADD_DEBUG_LOG ADD_DEBUG_LOGA
#define ADD_DEBUG_LOG_LR ADD_DEBUG_LOG_LRA
#define ADD_LOG ADD_LOGA
#define ADD_LOG_LR ADD_LOG_LRA
#endif

#ifdef __cplusplus
}
#endif
/*
///////////////////////////////////////////////////////////////////////////////
// E N D  O F  F I L E
///////////////////////////////////////////////////////////////////////////////
*/
#endif /* __ADDLOG_H__ */