/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   TimerStackList.c
//  Version     :   1.0
//  Creator     :   RM
//  Create Date :   2006-01-01
//  Comment     :
//
///////////////////////////////////////////////////////////////////////////////
*/

#pragma warning( disable : 4115 )
#pragma warning( disable : 4127 )
#pragma warning( disable : 4201 )
#pragma warning( disable : 4214 )
#pragma warning( disable : 4706 )

#ifdef _KERNEL_MODE_

#include <wdm.h>
#include <windef.h>
#include "Stack.h"
#include "TimerStackList.h"

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/
#define KERNEL_API
#define THREAD_RETURN_TYPE void
#define THREAD_RETURN( Code )

/*
///////////////////////////////////////////////////////////////////////////////
// F U N C T I O N S
///////////////////////////////////////////////////////////////////////////////
*/

/*
///////////////////////////////////////////////////////////////////////////////
// PsGetCurrentThreadId
///////////////////////////////////////////////////////////////////////////////
*/
HANDLE PsGetCurrentThreadId(
    VOID
    );

#else

#include <windows.h>
#include "Stack.h"
#include "TimerStackList.h"

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/
#define KERNEL_API __stdcall
#define THREAD_RETURN_TYPE ULONG
#define THREAD_RETURN( Code ) return Code

#define KdPrint( _x_ )

#define NT_SUCCESS( Status ) ( ( NTSTATUS ) ( Status ) >= 0 )
#define STATUS_SUCCESS ( ( NTSTATUS )0x0L )
#define STATUS_UNSUCCESSFUL ( ( NTSTATUS )0xC0000001L )

#define NonPagedPool 0
#define PagedPool 1
#define KernelMode 0
#define UserMode 1

#define PASSIVE_LEVEL 0
#define LOW_LEVEL 0
#define APC_LEVEL 1
#define DISPATCH_LEVEL 2
#define CLOCK_LEVEL 13
#define POWER_LEVEL 15
#define PROFILE_LEVEL 15
#define HIGH_LEVEL 15

#define KSPIN_LOCK CRITICAL_SECTION
#define PKSPIN_LOCK LPCRITICAL_SECTION

#define ExAllocatePool( PoolType, Size ) \
    HeapAlloc( GetProcessHeap( ), HEAP_ZERO_MEMORY, Size )

#define ExFreePool( Data ) \
    HeapFree( GetProcessHeap( ), 0, Data )

#define KeInitializeSpinLock( Lock ) InitializeCriticalSection( Lock )
#define KeAcquireSpinLock( Lock, Irql ) EnterCriticalSection( Lock ); ( Irql )
#define KeReleaseSpinLock( Lock, Irql ) LeaveCriticalSection( Lock ); ( Irql )
#define KeDeleteSpinLock( Lock ) DeleteCriticalSection( Lock )

#define KeInitializeEvent( Event, Type, State ) *Event = CreateEvent( NULL, FALSE, State, NULL )
#define KeSetEvent( Event, Increment, Wait ) SetEvent( *Event )
#define KeClearEvent( Event ) ResetEvent( *Event )

#define KeWaitForSingleObject( Object, a, b, c, d ) \
    WaitForSingleObject( *( ( PHANDLE )( Object ) ), INFINITE )

#define ObReferenceObjectByHandle( Handle, a, b, c, Object, d ) \
    ( *Object = &Handle, STATUS_SUCCESS )

#define ObDereferenceObject( Object ) \
    CloseHandle( *( ( PHANDLE )( Object ) ) )

#define KeGetCurrentIrql( ) PASSIVE_LEVEL

/*
///////////////////////////////////////////////////////////////////////////////
// S T R U C T U R E S
///////////////////////////////////////////////////////////////////////////////
*/
typedef HANDLE KEVENT, *PKEVENT;
typedef UCHAR KIRQL;

typedef PVOID POBJECT_ATTRIBUTES;

typedef struct _CLIENT_ID {
    HANDLE UniqueProcess;
    HANDLE UniqueThread;
} CLIENT_ID, *PCLIENT_ID;

/*
///////////////////////////////////////////////////////////////////////////////
// F U N C T I O N S
///////////////////////////////////////////////////////////////////////////////
*/

/*
///////////////////////////////////////////////////////////////////////////////
// KeQuerySystemTime
///////////////////////////////////////////////////////////////////////////////
*/
VOID _inline KeQuerySystemTime(
    OUT PLARGE_INTEGER CurrentTime
    )
{
    CurrentTime->QuadPart = GetTickCount( );
}

#endif /* _KERNEL_MODE_ */

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/
#ifndef PRINT_IN
#define PRINT_IN( ) KdPrint( ( "==>%s\n", __FUNCTION__ ) )
#define PRINT_IN_1( Data ) KdPrint( ( "==>%s[ %X ]\n", __FUNCTION__, Data ) )
#define PRINT_OUT( ) KdPrint( ( "%s==>\n", __FUNCTION__ ) )
#define PRINT_OUT_1( Data ) KdPrint( ( "%s==>[ %X ]\n", __FUNCTION__, Data ) )
#endif

/* Internal flags */
#define STACK_INTERNAL_FLAGS_PERMANENT 0x0001
#define STACK_INTERNAL_FLAGS_EXECUTING 0x0002
#define STACK_INTERNAL_FLAGS_REMOVED 0x0004
#define STACK_INTERNAL_FLAGS_QUITTED 0x0008
#define STACK_INTERNAL_FLAGS_SELF_CLEAN 0x0010

/* Type of struct */
#define TYPE_TIMER_STACK_CONTEXT 0x10

/*
///////////////////////////////////////////////////////////////////////////////
// S T R U C T U R E S
///////////////////////////////////////////////////////////////////////////////
*/
typedef struct _TIMER_STACK_CONTEXT {
    USHORT Type;
    USHORT Size;
    ULONG Flags;
    ULONG ThreadId;
    HANDLE Thread;
    PKSTART_ROUTINE CancelRoutine;
    PVOID Context;
    LARGE_INTEGER Timeout;
} TIMER_STACK_CONTEXT, *PTIMER_STACK_CONTEXT;

/*
///////////////////////////////////////////////////////////////////////////////
// G L O B A L S
///////////////////////////////////////////////////////////////////////////////
*/
/* Timer stack list */
static COMMON_STACK_T g_TimerStackList;
static KSPIN_LOCK g_TimerStackListLock;

/*
///////////////////////////////////////////////////////////////////////////////
// F U N C T I O N S
///////////////////////////////////////////////////////////////////////////////
*/

/*
///////////////////////////////////////////////////////////////////////////////
// GetTotalTimerStackItem
///////////////////////////////////////////////////////////////////////////////
*/
ULONG GetTotalTimerStackItem(
    VOID
    )
{
    return StackCountT( &g_TimerStackList );
}

/*
///////////////////////////////////////////////////////////////////////////////
// RemoveTimerStackItem
///////////////////////////////////////////////////////////////////////////////
*/
ULONG RemoveTimerStackItem(
    IN ULONG ThreadId
    )
{
    TIMER_STACK_CONTEXT TimerStackCtx;
    ULONG Top;

    TimerStackCtx.ThreadId = ThreadId;
    Top = StackFindAscT( &g_TimerStackList, &TimerStackCtx );
    if ( Top )
        StackRemoveIndexT( &g_TimerStackList, Top - 1 );

    return Top;
}

/*
///////////////////////////////////////////////////////////////////////////////
// RemoveTimerStackItemEx
///////////////////////////////////////////////////////////////////////////////
*/
ULONG RemoveTimerStackItemEx(
    IN ULONG ThreadId,
    IN BOOL Cancel
    )
{
    TIMER_STACK_CONTEXT TimerStackCtx;
    PTIMER_STACK_CONTEXT TimerStackCtxPtr;
    ULONG Top;

    TimerStackCtx.ThreadId = ThreadId;
    Top = StackFindAscT( &g_TimerStackList, &TimerStackCtx );
    if ( Top )
    {
        if ( Cancel )
        {
            TimerStackCtxPtr = StackAtT( &g_TimerStackList, Top - 1 );
            if ( TimerStackCtxPtr->CancelRoutine )
                TimerStackCtxPtr->CancelRoutine( TimerStackCtxPtr->Context );
        }
        StackRemoveIndexT( &g_TimerStackList, Top - 1 );
    }

    return Top;
}

/*
///////////////////////////////////////////////////////////////////////////////
// QueueTimerStackItem
///////////////////////////////////////////////////////////////////////////////
*/
ULONG QueueTimerStackItem(
    IN ULONG ThreadId,
    IN HANDLE Thread,
    IN ULONG Flags
    )
{
    ULONG RetCode;
    TIMER_STACK_CONTEXT TimerStackCtx;
    KIRQL Irql;

    TimerStackCtx.Type = TYPE_TIMER_STACK_CONTEXT;
    TimerStackCtx.Size = sizeof( TIMER_STACK_CONTEXT );

    /* Flags */
    TimerStackCtx.Flags = Flags;
    /* Thread id */
    TimerStackCtx.ThreadId = ThreadId;
    /* Thread handle */
    TimerStackCtx.Thread = Thread;
    /* Cancel routine */
    TimerStackCtx.CancelRoutine = NULL;
    /* Context */
    TimerStackCtx.Context = NULL;
    /* Default Time out */
    TimerStackCtx.Timeout.QuadPart = - 1;

    KeAcquireSpinLock( &g_TimerStackListLock, Irql );
    RetCode = StackPushAscT( &g_TimerStackList, &TimerStackCtx );
    KeReleaseSpinLock( &g_TimerStackListLock, Irql );

    return RetCode;
}

/*
///////////////////////////////////////////////////////////////////////////////
// QueueTimerStackItemEx
///////////////////////////////////////////////////////////////////////////////
*/
ULONG QueueTimerStackItemEx(
    IN ULONG ThreadId,
    IN HANDLE Thread,
    IN ULONG Flags,
    IN PKSTART_ROUTINE CancelRoutine,
    IN PVOID Context,
    IN PLARGE_INTEGER Timeout
    )
{
    ULONG RetCode;
    TIMER_STACK_CONTEXT TimerStackCtx;
    LARGE_INTEGER SystemTime;
    KIRQL Irql;

    TimerStackCtx.Type = TYPE_TIMER_STACK_CONTEXT;
    TimerStackCtx.Size = sizeof( TIMER_STACK_CONTEXT );

    /* Flags */
    TimerStackCtx.Flags = Flags;
    /* Thread id */
    TimerStackCtx.ThreadId = ThreadId;
    /* Thread handle */
    TimerStackCtx.Thread = Thread;
    /* Cancel routine */
    TimerStackCtx.CancelRoutine = CancelRoutine;
    /* Context */
    TimerStackCtx.Context = Context;
    /* Time out */
    if ( Timeout )
    {
        TimerStackCtx.Timeout = *Timeout;
        if ( TimerStackCtx.Timeout.QuadPart < 0 )
        {
            KeQuerySystemTime( &SystemTime );
            TimerStackCtx.Timeout.QuadPart = - TimerStackCtx.Timeout.QuadPart;
            TimerStackCtx.Timeout.QuadPart += SystemTime.QuadPart;
        }
    }
    else
    {
        TimerStackCtx.Timeout.QuadPart = - 1;
    }

    KeAcquireSpinLock( &g_TimerStackListLock, Irql );
    RetCode = StackPushAscT( &g_TimerStackList, &TimerStackCtx );
    KeReleaseSpinLock( &g_TimerStackListLock, Irql );

    return RetCode;
}

/*
///////////////////////////////////////////////////////////////////////////////
// DequeueTimerStackItem
///////////////////////////////////////////////////////////////////////////////
*/
ULONG DequeueTimerStackItem(
    IN ULONG ThreadId
    )
{
    TIMER_STACK_CONTEXT TimerStackCtx;
    ULONG Top;
    KIRQL Irql;

    TimerStackCtx.ThreadId = ThreadId;
    KeAcquireSpinLock( &g_TimerStackListLock, Irql );
    Top = StackFindAscT( &g_TimerStackList, &TimerStackCtx );
    if ( Top )
        StackRemoveIndexT( &g_TimerStackList, Top - 1 );
    KeReleaseSpinLock( &g_TimerStackListLock, Irql );

    return Top;
}

/*
///////////////////////////////////////////////////////////////////////////////
// DequeueTimerStackItemEx
///////////////////////////////////////////////////////////////////////////////
*/
ULONG DequeueTimerStackItemEx(
    IN ULONG ThreadId,
    IN BOOL Cancel
    )
{
    TIMER_STACK_CONTEXT TimerStackCtx;
    PTIMER_STACK_CONTEXT TimerStackCtxPtr;
    ULONG Top;
    KIRQL Irql;

    TimerStackCtx.ThreadId = ThreadId;
    KeAcquireSpinLock( &g_TimerStackListLock, Irql );
    Top = StackFindAscT( &g_TimerStackList, &TimerStackCtx );
    if ( Top )
    {
        if ( Cancel )
        {
            TimerStackCtxPtr = StackAtT( &g_TimerStackList, Top - 1 );
            if ( TimerStackCtxPtr->CancelRoutine )
                TimerStackCtxPtr->CancelRoutine( TimerStackCtxPtr->Context );
        }
        StackRemoveIndexT( &g_TimerStackList, Top - 1 );
    }
    KeReleaseSpinLock( &g_TimerStackListLock, Irql );

    return Top;
}

/*
///////////////////////////////////////////////////////////////////////////////
// TimerStackListRoutine
///////////////////////////////////////////////////////////////////////////////
*/
ULONG TimerStackListRoutine(
    IN PLARGE_INTEGER Time
    )
{
    ULONG RetCode;
    register ULONG Iter;
    register ULONG Count;
    PTIMER_STACK_CONTEXT TimerStackCtxPtr;
    KIRQL Irql;

    RetCode = 0;
    KeAcquireSpinLock( &g_TimerStackListLock, &Irql );
    for ( Iter = 0, Count = StackCountT( &g_TimerStackList ); Iter < Count; Iter++ )
    {
        TimerStackCtxPtr = StackAtT( &g_TimerStackList, Iter );
        if ( TimerStackCtxPtr->Timeout.QuadPart != - 1 &&
            Time->QuadPart > TimerStackCtxPtr->Timeout.QuadPart )
        {
            /* Call cancel routine if it is time out */
            if ( TimerStackCtxPtr->CancelRoutine )
                TimerStackCtxPtr->CancelRoutine( TimerStackCtxPtr->Context );
            StackRemoveIndexT( &g_TimerStackList, Iter );
            Count = StackCountT( &g_TimerStackList );
            RetCode++;
        }
    }
    KeReleaseSpinLock( &g_TimerStackListLock, Irql );

    return RetCode;
}

ULONG _InitContext( PTIMER_STACK_CONTEXT StackContext, PVOID Context )
{
    UNREFERENCED_PARAMETER( StackContext );
    UNREFERENCED_PARAMETER( Context );

    return TRUE;
}

ULONG _UninitContext( PTIMER_STACK_CONTEXT StackContext, PVOID Context )
{
    UNREFERENCED_PARAMETER( StackContext );
    UNREFERENCED_PARAMETER( Context );

    return TRUE;
}

LONG _CompareContext( PTIMER_STACK_CONTEXT Context1, PTIMER_STACK_CONTEXT Context2 )
{
    return Context1->ThreadId - Context2->ThreadId;
}

/*
///////////////////////////////////////////////////////////////////////////////
// InitTimerStackList
///////////////////////////////////////////////////////////////////////////////
*/
VOID InitTimerStackList(
    VOID
    )
{
    /* Initiate timer stack list and lock */
    StackInitT( &g_TimerStackList, 0, sizeof( TIMER_STACK_CONTEXT ), _InitContext, _UninitContext, _CompareContext, _CompareContext, NULL );
    KeInitializeSpinLock( &g_TimerStackListLock );
}

/*
///////////////////////////////////////////////////////////////////////////////
// UninitTimerStackList
///////////////////////////////////////////////////////////////////////////////
*/
VOID UninitTimerStackList(
    VOID
    )
{
    /* Un-Initiate timer stack list and lock */
    StackUninitT( &g_TimerStackList );
    KeDeleteSpinLock( &g_TimerStackListLock );
}