/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   Stack.c
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

#include "Stack.h"

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/
#define DEFAULT_STACK_SIZE 16
#define DEFAULT_STACK_U_SIZE 16
#define DEFAULT_STACK_T_SIZE 16
#define DEFAULT_STACK_T_ELEMENT_SIZE sizeof( PVOID )
#define DEFAULT_STACK_S_SIZE 64
#define DEFAULT_STACK_S_PREFIX_SIZE 16

/* StackS */
#define END_CHAR _T( '\0' )

#ifndef HEAP_ALLOC
#define HEAP_ALLOC( Size ) HeapAlloc( GetProcessHeap( ), 0, Size )
#endif

#ifndef HEAP_FREE
#define HEAP_FREE( Buffer ) HeapFree( GetProcessHeap( ), 0, Buffer )
#endif

#ifndef HEAP_REALLOC
#define HEAP_REALLOC( Buffer, Size ) HeapReAlloc( GetProcessHeap( ), 0, Buffer, Size )
#endif

#define GET_GS_STACK_ALLOC_FAIL( ) g_StackAllocFail
#define SET_GS_STACK_ALLOC_FAIL( _StackAllocFail ) g_StackAllocFail = ( _StackAllocFail )
#define GET_GS_STACK_ALLOC_FAIL_CONTEXT( ) g_StackAllocFailContext
#define SET_GS_STACK_ALLOC_FAIL_CONTEXT( _StackAllocFailContext ) g_StackAllocFailContext = ( _StackAllocFailContext )

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
LONG StackDefaultAllocFail( PVOID, STACK_TYPE, PVOID );
LONG StackDefaultCompare( LONG *Element1, LONG *Element2 );

static STACK_ALLOC_FAIL_FUNCTION g_StackAllocFail = StackDefaultAllocFail;
static PVOID g_StackAllocFailContext = NULL;

/*
///////////////////////////////////////////////////////////////////////////////
// F U N C T I O N S
///////////////////////////////////////////////////////////////////////////////
*/
/* Memory */
PVOID StackAlloc( ULONG Size )
{
    return HEAP_ALLOC( Size );
}

PVOID StackReAlloc( PVOID Buffer, ULONG Size )
{
    return HEAP_REALLOC( Buffer, Size );
}

void StackFree( PVOID Buffer )
{
    HEAP_FREE( Buffer );
}

static LONG StackDefaultAllocFail( PVOID Stack, STACK_TYPE Type, PVOID Context )
{
    return 0;
}

static LONG StackDefaultCompare( LONG *Element1, LONG *Element2 )
{
    return ( *Element1 - *Element2 );
}

void StackSetAllocFail( STACK_ALLOC_FAIL_FUNCTION StackAllocFail, PVOID Context )
{
    if ( StackAllocFail )
    {
        SET_GS_STACK_ALLOC_FAIL( StackAllocFail );
        SET_GS_STACK_ALLOC_FAIL_CONTEXT( Context );
    }
    else
    {
        SET_GS_STACK_ALLOC_FAIL( StackDefaultAllocFail );
        SET_GS_STACK_ALLOC_FAIL_CONTEXT( NULL );
    }
}

/*
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
*/
ULONG StackInit( PCOMMON_STACK Stack, ULONG Max )
{
    if ( Max == 0 )
        Max = DEFAULT_STACK_SIZE;
    else
        Max = ROUND_SIZE( Max );

    Stack->Top = 0;
    Stack->Bottom = 0;
    Stack->Elements = ( PVOID* )HEAP_ALLOC( sizeof( PVOID ) * Max );
    if ( !Stack->Elements )
    {
        Stack->Max = 0;
        return FALSE;
    }
    else
    {
        Stack->Max = Max;
        return TRUE;
    }
}

ULONG StackUninit( PCOMMON_STACK Stack )
{
    register ULONG Iter;
    register ULONG Count;

    for ( Iter = 0, Count = Stack->Top; Iter < Count; Iter++ )
        HEAP_FREE( Stack->Elements[Iter] );

    if ( Stack->Elements )
        HEAP_FREE( Stack->Elements );

    return TRUE;
}

ULONG StackReinit( PCOMMON_STACK Stack )
{
    register ULONG Iter;
    register ULONG Count;

    for ( Iter = 0, Count = Stack->Top; Iter < Count; Iter++ )
        HEAP_FREE( Stack->Elements[Iter] );

    Stack->Top = 0;
    Stack->Bottom = 0;

    return Stack->Max;
}

ULONG StackSetMax( PCOMMON_STACK Stack, ULONG Max )
{
    register PVOID *NewBuffer;

    if ( Max > Stack->Max )
    {
        Max = ROUND_SIZE( Max );
        NewBuffer = ( PVOID* )HEAP_REALLOC( Stack->Elements, Max * sizeof( Stack->Elements[0] ) );
        if ( !NewBuffer )
        {
            NewBuffer = ( PVOID* )HEAP_ALLOC( Max * sizeof( Stack->Elements[0] ) );
            if ( NewBuffer == NULL )
            {
                GET_GS_STACK_ALLOC_FAIL( )( Stack, STACK_TYPE_P, GET_GS_STACK_ALLOC_FAIL_CONTEXT( ) );
                return FALSE;
            }

            memcpy( NewBuffer, Stack->Elements, Stack->Top * sizeof( Stack->Elements[0] ) );
            HEAP_FREE( Stack->Elements );
        }
        Stack->Elements = NewBuffer;
        Stack->Max = Max;
    }

    return Stack->Max;
}

ULONG StackSetTop( PCOMMON_STACK Stack, ULONG Top )
{
    if ( Top > Stack->Max )
        Stack->Top = Stack->Max - 1;
    else
        Stack->Top = Top;

    return Stack->Top;
}

ULONG StackSetBottom( PCOMMON_STACK Stack, ULONG Bottom )
{
    if ( Bottom > Stack->Top )
        Stack->Bottom = Stack->Top;
    else
        Stack->Bottom = Bottom;

    return Stack->Bottom;
}

ULONG StackFind( PCOMMON_STACK Stack, PVOID Element )
{
    register ULONG Iter;
    register ULONG Count;

    Count = Stack->Top;
    for ( Iter = 0; Iter < Count; Iter++ )
    {
        if ( Stack->Elements[Iter] == Element )
            return Iter + 1;
    }

    return 0;
}

ULONG StackFindReverse( PCOMMON_STACK Stack, PVOID Element )
{
    register ULONG Iter;

    Iter = Stack->Top;
    while ( Iter )
    {
        Iter--;
        if ( Stack->Elements[Iter] == Element )
            return Iter + 1;
    }

    return 0;
}

ULONG StackPopAll( PCOMMON_STACK Stack, PVOID **Element )
{
    register ULONG Top;

    if ( Element )
        *Element = Stack->Elements;

    Top = Stack->Top;
    Stack->Top = 0;

    return Top;
}

ULONG StackPush( PCOMMON_STACK Stack, PVOID Element, ULONG Size )
{
    if ( Stack->Top >= Stack->Max )
    {
        if ( !StackSetMax( Stack, Stack->Max + DEFAULT_STACK_SIZE ) )
            return FALSE;
    }
    Stack->Elements[Stack->Top] = ( PVOID  )HEAP_ALLOC( Size );
    memcpy( Stack->Elements[Stack->Top], Element, Size );

    return ++Stack->Top;
}

ULONG StackPop( PCOMMON_STACK Stack, PVOID Element, ULONG Size )
{
    register ULONG Top;

    Top = Stack->Top;
    if ( Stack->Top )
    {
        Stack->Top--;
        if ( Element )
            memcpy( Element, Stack->Elements[Stack->Top], Size );
        HEAP_FREE( Stack->Elements[Stack->Top] );
    }

    return Top;
}

ULONG StackTop( PCOMMON_STACK Stack, PVOID *Element )
{
    if ( Stack->Top )
        *Element = Stack->Elements[Stack->Top - 1];
    else
        *Element = NULL;

    return Stack->Top;
}

ULONG StackPopBottom( PCOMMON_STACK Stack, PVOID Element, ULONG Size )
{
    if ( Stack->Bottom < Stack->Top )
    {
        if ( Element )
            memcpy( Element, Stack->Elements[Stack->Bottom], Size );
        Stack->Bottom++;
        return 1;
    }
    else
    {
        if ( Element )
            memset( Element, 0, Size );
        return 0;
    }
}

ULONG StackBottom( PCOMMON_STACK Stack, PVOID *Element )
{
    if ( Stack->Bottom < Stack->Top )
    {
        *Element = Stack->Elements[Stack->Bottom];
        return Stack->Top - Stack->Bottom;
    }
    else
    {
        *Element = NULL;
        return 0;
    }
}

ULONG StackRemove( PCOMMON_STACK Stack, PVOID Element )
{
    ULONG RetCode;
    register ULONG Iter;
    register ULONG Count;

    RetCode = 0;
    Iter = 0;
    Count = Stack->Top;
    while ( Iter < Count )
    {
        if ( Stack->Elements[Iter] == Element )
        {
            HEAP_FREE( Stack->Elements[Iter] );
            memcpy( Stack->Elements + Iter, Stack->Elements + Iter + 1, ( Count - Iter - 1 ) * sizeof( Stack->Elements[0] ) );
            --Stack->Top;
            RetCode = Iter + 1;
            break;
        }
        Iter++;
    }

    return RetCode;
}

ULONG StackRemoveIndex( PCOMMON_STACK Stack, ULONG Index )
{
    if ( Index < Stack->Top )
    {
        HEAP_FREE( Stack->Elements[Index] );
        memcpy( Stack->Elements + Index, Stack->Elements + Index + 1, ( Stack->Top - Index - 1 ) * sizeof( Stack->Elements[0] ) );
        --Stack->Top;
        return Index + 1;
    }
    else
    {
        return 0;
    }
}

void StackApply( PCOMMON_STACK Stack, ULONG Type, STACK_FUNCTION ApplyFunction )
{
    register ULONG Iter;

    if ( Type == STACK_APPLY_TOPDOWN )
    {
        for ( Iter = Stack->Top - 1; Iter>=0; Iter-- )
        {
            if ( ApplyFunction( Stack->Elements[Iter] ) )
                break;
        }
    }
    else if ( Type == STACK_APPLY_BOTTOMUP )
    {
        for ( Iter = 0; Iter < Stack->Top; Iter++ )
        {
            if ( ApplyFunction( Stack->Elements[Iter] ) )
                break;
        }
    }
}

void StackApplyEx( PCOMMON_STACK Stack, ULONG Type, STACK_FUNCTION_EX ApplyFunction, PVOID Context )
{
    register ULONG Iter;

    if ( Type == STACK_APPLY_TOPDOWN )
    {
        for ( Iter = Stack->Top - 1; Iter>=0; Iter-- )
        {
            if ( ApplyFunction( Stack->Elements[Iter], Context ) )
                break;
        }
    }
    else if ( Type == STACK_APPLY_BOTTOMUP )
    {
        for ( Iter = 0; Iter < Stack->Top; Iter++ )
        {
            if ( ApplyFunction( Stack->Elements[Iter], Context ) )
                break;
        }
    }
}

/*
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
*/
ULONG StackInitU( PCOMMON_STACK_U Stack, ULONG Max )
{
    if ( Max == 0 )
        Max = DEFAULT_STACK_U_SIZE;
    else
        Max = ROUND_SIZE( Max );

    Stack->Top = 0;
    Stack->Bottom = 0;
    Stack->Elements = ( ULONG* )HEAP_ALLOC( Max * sizeof( Stack->Elements[0] ) );
    if ( !Stack->Elements )
    {
        Stack->Max = 0;
        return FALSE;
    }
    else
    {
        Stack->Max = Max;
        return TRUE;
    }
}

ULONG StackUninitU( PCOMMON_STACK_U Stack )
{
    if ( Stack->Elements )
        HEAP_FREE( Stack->Elements );

    return TRUE;
}

ULONG StackReinitU( PCOMMON_STACK_U Stack )
{
    Stack->Top = 0;
    Stack->Bottom = 0;

    return Stack->Max;
}

ULONG StackSetMaxU( PCOMMON_STACK_U Stack, ULONG Max )
{
    register ULONG *NewBuffer;

    if ( Max > Stack->Max )
    {
        Max = ROUND_SIZE( Max );
        NewBuffer = ( ULONG* )HEAP_REALLOC( Stack->Elements, Max * sizeof( Stack->Elements[0] ) );
        if ( !NewBuffer )
        {
            NewBuffer = ( ULONG* )HEAP_ALLOC( Max * sizeof( Stack->Elements[0] ) );
            if ( NewBuffer == NULL )
            {
                GET_GS_STACK_ALLOC_FAIL( )( Stack, STACK_TYPE_U, GET_GS_STACK_ALLOC_FAIL_CONTEXT( ) );
                return FALSE;
            }

            memcpy( NewBuffer, Stack->Elements, Stack->Top * sizeof( Stack->Elements[0] ) );
            HEAP_FREE( Stack->Elements );
        }
        Stack->Elements = NewBuffer;
        Stack->Max = Max;
    }

    return Stack->Max;
}

ULONG StackSetTopU( PCOMMON_STACK_U Stack, ULONG Top )
{
    if ( Top > Stack->Max )
        Stack->Top = Stack->Max - 1;
    else
        Stack->Top = Top;

    return Stack->Top;
}

ULONG StackSetBottomU( PCOMMON_STACK_U Stack, ULONG Bottom )
{
    if ( Bottom > Stack->Top )
        Stack->Bottom = Stack->Top;
    else
        Stack->Bottom = Bottom;

    return Stack->Bottom;
}

ULONG StackFindU( PCOMMON_STACK_U Stack, ULONG Element )
{
    register ULONG Iter;
    register ULONG Count;

    Count = Stack->Top;
    for ( Iter = 0; Iter < Count; Iter++ )
    {
        if ( Stack->Elements[Iter] == Element )
            return Iter + 1;
    }

    return 0;
}

ULONG StackFindReverseU( PCOMMON_STACK_U Stack, ULONG Element )
{
    register ULONG Iter;

    Iter = Stack->Top;
    while ( Iter )
    {
        Iter--;
        if ( Stack->Elements[Iter] == Element )
            return Iter + 1;
    }

    return 0;
}

ULONG StackFindAscU( PCOMMON_STACK_U Stack, ULONG Element )
{
    ULONG RetCode;
    register ULONG Start;
    register ULONG End;
    register ULONG Mid;
    register ULONG StackElement;

    RetCode = 0;
    End = Stack->Top;
    if ( End )
    {
        Start = 0;
        Mid = End >> 1;
        while ( Mid < End )
        {
            StackElement = Stack->Elements[Mid];
            if ( Element > StackElement )
            {
                Start = Mid + 1;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else if ( Element < StackElement )
            {
                End = Mid;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else
            {
                RetCode = Mid + 1;
                break;
            }
        }
    }

    return RetCode;
}

ULONG StackFindDscU( PCOMMON_STACK_U Stack, ULONG Element )
{
    ULONG RetCode;
    register ULONG Start;
    register ULONG End;
    register ULONG Mid;
    register ULONG StackElement;

    RetCode = 0;
    End = Stack->Top;
    if ( End )
    {
        Start = 0;
        Mid = End >> 1;
        while ( Mid < End )
        {
            StackElement = Stack->Elements[Mid];
            if ( Element < StackElement )
            {
                Start = Mid + 1;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else if ( Element > StackElement )
            {
                End = Mid;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else
            {
                RetCode = Mid + 1;
                break;
            }
        }
    }

    return RetCode;
}

ULONG StackFindLargeAscU( PCOMMON_STACK_U Stack, ULONG Element )
{
    ULONG RetCode;
    register ULONG Start;
    register ULONG End;
    register ULONG Mid;
    register ULONG StackElement;

    RetCode = 0;
    End = Stack->Top;
    if ( End )
    {
        Start = 0;
        Mid = End >> 1;
        while ( Mid < End )
        {
            StackElement = Stack->Elements[Mid];
            if ( Element > StackElement )
            {
                Start = Mid + 1;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else if ( Element < StackElement )
            {
                End = Mid;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else
            {
                End = Mid + 1;
                break;
            }
        }
        if ( End < Stack->Top )
            RetCode = End + 1;
    }

    return RetCode;
}

ULONG StackFindLargeEqualAscU( PCOMMON_STACK_U Stack, ULONG Element )
{
    ULONG RetCode;
    register ULONG Start;
    register ULONG End;
    register ULONG Mid;
    register ULONG StackElement;

    RetCode = 0;
    End = Stack->Top;
    if ( End )
    {
        Start = 0;
        Mid = End >> 1;
        while ( Mid < End )
        {
            StackElement = Stack->Elements[Mid];
            if ( Element > StackElement )
            {
                Start = Mid + 1;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else if ( Element < StackElement )
            {
                End = Mid;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else
            {
                End = Mid;
                break;
            }
        }
        if ( End < Stack->Top )
            RetCode = End + 1;
    }

    return RetCode;
}

ULONG StackFindLargeDscU( PCOMMON_STACK_U Stack, ULONG Element )
{
    ULONG RetCode;
    register ULONG Start;
    register ULONG End;
    register ULONG Mid;
    register ULONG StackElement;

    RetCode = 0;
    End = Stack->Top;
    if ( End )
    {
        Start = 0;
        Mid = End >> 1;
        while ( Mid < End )
        {
            StackElement = Stack->Elements[Mid];
            if ( Element < StackElement )
            {
                Start = Mid + 1;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else if ( Element > StackElement )
            {
                End = Mid;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else
            {
                Start = Mid > 0 ? Mid - 1 : Mid;
                break;
            }
        }
        if ( Start < Mid )
            RetCode = Start + 1;
        else
            RetCode = Start;
    }

    return RetCode;
}

ULONG StackFindLargeEqualDscU( PCOMMON_STACK_U Stack, ULONG Element )
{
    ULONG RetCode;
    register ULONG Start;
    register ULONG End;
    register ULONG Mid;
    register ULONG StackElement;

    RetCode = 0;
    End = Stack->Top;
    if ( End )
    {
        Start = 0;
        Mid = End >> 1;
        while ( Mid < End )
        {
            StackElement = Stack->Elements[Mid];
            if ( Element < StackElement )
            {
                Start = Mid + 1;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else if ( Element > StackElement )
            {
                End = Mid;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else
            {
                Start = Mid;
                break;
            }
        }
        if ( Start < Mid )
            RetCode = Start + 1;
        else
            RetCode = Start;
    }

    return RetCode;
}

ULONG StackFindSmallAscU( PCOMMON_STACK_U Stack, ULONG Element )
{
    ULONG RetCode;
    register ULONG Start;
    register ULONG End;
    register ULONG Mid;
    register ULONG StackElement;

    RetCode = 0;
    End = Stack->Top;
    if ( End )
    {
        Start = 0;
        Mid = End >> 1;
        while ( Mid < End )
        {
            StackElement = Stack->Elements[Mid];
            if ( Element > StackElement )
            {
                Start = Mid + 1;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else if ( Element < StackElement )
            {
                End = Mid;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else
            {
                Start = Mid > 0 ? Mid - 1 : Mid;
                break;
            }
        }
        if ( Start < Mid )
            RetCode = Start + 1;
        else
            RetCode = Start;
    }

    return RetCode;
}

ULONG StackFindSmallEqualAscU( PCOMMON_STACK_U Stack, ULONG Element )
{
    ULONG RetCode;
    register ULONG Start;
    register ULONG End;
    register ULONG Mid;
    register ULONG StackElement;

    RetCode = 0;
    End = Stack->Top;
    if ( End )
    {
        Start = 0;
        Mid = End >> 1;
        while ( Mid < End )
        {
            StackElement = Stack->Elements[Mid];
            if ( Element > StackElement )
            {
                Start = Mid + 1;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else if ( Element < StackElement )
            {
                End = Mid;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else
            {
                Start = Mid;
                break;
            }
        }
        if ( Start < Mid )
            RetCode = Start + 1;
        else
            RetCode = Start;
    }

    return RetCode;
}

ULONG StackFindSmallDscU( PCOMMON_STACK_U Stack, ULONG Element )
{
    ULONG RetCode;
    register ULONG Start;
    register ULONG End;
    register ULONG Mid;
    register ULONG StackElement;

    RetCode = 0;
    End = Stack->Top;
    if ( End )
    {
        Start = 0;
        Mid = End >> 1;
        while ( Mid < End )
        {
            StackElement = Stack->Elements[Mid];
            if ( Element < StackElement )
            {
                Start = Mid + 1;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else if ( Element > StackElement )
            {
                End = Mid;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else
            {
                End = Mid + 1;
                break;
            }
        }
        if ( End < Stack->Top )
            RetCode = End + 1;
    }

    return RetCode;
}

ULONG StackFindSmallEqualDscU( PCOMMON_STACK_U Stack, ULONG Element )
{
    ULONG RetCode;
    register ULONG Start;
    register ULONG End;
    register ULONG Mid;
    register ULONG StackElement;

    RetCode = 0;
    End = Stack->Top;
    if ( End )
    {
        Start = 0;
        Mid = End >> 1;
        while ( Mid < End )
        {
            StackElement = Stack->Elements[Mid];
            if ( Element < StackElement )
            {
                Start = Mid + 1;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else if ( Element > StackElement )
            {
                End = Mid;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else
            {
                End = Mid;
                break;
            }
        }
        if ( End < Stack->Top )
            RetCode = End + 1;
    }

    return RetCode;
}

ULONG StackPopAllU( PCOMMON_STACK_U Stack, ULONG **Element )
{
    register ULONG Top;

    if ( Element )
        *Element = Stack->Elements;

    Top = Stack->Top;
    Stack->Top = 0;

    return Top;
}

ULONG StackPushU( PCOMMON_STACK_U Stack, ULONG Element )
{
    if ( Stack->Top >= Stack->Max )
    {
        if ( !StackSetMaxU( Stack, Stack->Max + DEFAULT_STACK_U_SIZE ) )
            return FALSE;
    }
    Stack->Elements[Stack->Top] = Element;

    return ++Stack->Top;
}

ULONG StackPushIncU( PCOMMON_STACK_U Stack, ULONG Element )
{
    if ( Stack->Top >= Stack->Max )
    {
        if ( !StackSetMaxU( Stack, Stack->Max + DEFAULT_STACK_U_SIZE ) )
            return FALSE;
    }

    if ( Stack->Top )
    {
        if ( Stack->Elements[Stack->Top - 1] > Element )
            Stack->Elements[Stack->Top] = Stack->Elements[Stack->Top - 1] + 1;
        else
            Stack->Elements[Stack->Top] = Element;
    }
    else
        Stack->Elements[Stack->Top] = Element;

    return ++Stack->Top;
}

ULONG StackPushDecU( PCOMMON_STACK_U Stack, ULONG Element )
{
    if ( Stack->Top >= Stack->Max )
    {
        if ( !StackSetMaxU( Stack, Stack->Max + DEFAULT_STACK_U_SIZE ) )
            return FALSE;
    }

    if ( Stack->Top )
    {
        if ( Stack->Elements[Stack->Top - 1] < Element )
            Stack->Elements[Stack->Top] = Stack->Elements[Stack->Top - 1] - 1;
        else
            Stack->Elements[Stack->Top] = Element;
    }
    else
        Stack->Elements[Stack->Top] = Element;

    return ++Stack->Top;
}

ULONG StackPushAscU( PCOMMON_STACK_U Stack, ULONG Element )
{
    ULONG Pos;
    register ULONG *Start;
    register ULONG *Cur;
    register ULONG *Prev;
    register ULONG Exchange;

    if ( Stack->Top >= Stack->Max )
    {
        if ( !StackSetMaxU( Stack, Stack->Max + DEFAULT_STACK_U_SIZE ) )
            return FALSE;
    }

    Stack->Elements[Stack->Top] = Element;
    Pos = ++Stack->Top;
    Start = Stack->Elements;
    Cur = Stack->Elements + Stack->Top - 1;
    Prev = Cur - 1;
    while ( Cur != Start )
    {
        if ( *Cur < *Prev )
        {
            Pos--;
            Exchange = *Prev;
            *Prev = *Cur;
            *Cur = Exchange;
        }
        else
            break;
        Cur--;
        Prev--;
    }

    return Pos;
}

ULONG StackPushDscU( PCOMMON_STACK_U Stack, ULONG Element )
{
    ULONG Pos;
    register ULONG *Start;
    register ULONG *Cur;
    register ULONG *Prev;
    register ULONG Exchange;

    if ( Stack->Top >= Stack->Max )
    {
        if ( !StackSetMaxU( Stack, Stack->Max + DEFAULT_STACK_U_SIZE ) )
            return FALSE;
    }

    Stack->Elements[Stack->Top] = Element;
    Pos = ++Stack->Top;
    Start = Stack->Elements;
    Cur = Stack->Elements + Stack->Top - 1;
    Prev = Cur - 1;
    while ( Cur != Start )
    {
        if ( *Cur > *Prev )
        {
            Pos--;
            Exchange = *Prev;
            *Prev = *Cur;
            *Cur = Exchange;
        }
        else
            break;
        Cur--;
        Prev--;
    }

    return Pos;
}

ULONG StackPopU( PCOMMON_STACK_U Stack, ULONG *Element )
{
    register ULONG Top;

    Top = Stack->Top;
    if ( Stack->Top )
    {
        Stack->Top--;
        if ( Element )
            *Element = Stack->Elements[Stack->Top];
    }
    else
    {
        if ( Element )
            *Element = 0;
    }

    return Top;
}

ULONG StackTopU( PCOMMON_STACK_U Stack, ULONG *Element )
{
    if ( Stack->Top )
        *Element = Stack->Elements[Stack->Top - 1];
    else
        *Element = 0;

    return Stack->Top;
}

ULONG StackPopBottomU( PCOMMON_STACK_U Stack, ULONG *Element )
{
    if ( Stack->Bottom < Stack->Top )
    {
        if ( Element )
            *Element = Stack->Elements[Stack->Bottom];
        Stack->Bottom++;
        return 1;
    }
    else
    {
        if ( Element )
            *Element = 0;
        return 0;
    }
}

ULONG StackBottomU( PCOMMON_STACK_U Stack, ULONG *Element )
{
    if ( Stack->Bottom < Stack->Top )
    {
        *Element = Stack->Elements[Stack->Bottom];
        return Stack->Top - Stack->Bottom;
    }
    else
    {
        *Element = 0;
        return 0;
    }
}

ULONG StackRemoveU( PCOMMON_STACK_U Stack, ULONG Element )
{
    ULONG RetCode;
    register ULONG Iter;
    register ULONG Count;

    RetCode = 0;
    Iter = 0;
    Count = Stack->Top;
    while ( Iter < Count )
    {
        if ( Stack->Elements[Iter] == Element )
        {
            memcpy( Stack->Elements + Iter, Stack->Elements + Iter + 1, ( Count - Iter - 1 ) * sizeof( Stack->Elements[0] ) );
            --Stack->Top;
            RetCode = Iter + 1;
            break;
        }
        Iter++;
    }

    return RetCode;
}

ULONG StackReverseRemoveU( PCOMMON_STACK_U Stack, ULONG Element )
{
    ULONG RetCode;
    register ULONG Iter;
    register ULONG Count;

    RetCode = 0;
    Count = Stack->Top;
    Iter = Count;
    while ( Iter )
    {
        Iter--;
        if ( Stack->Elements[Iter] == Element )
        {
            memcpy( Stack->Elements + Iter, Stack->Elements + Iter + 1, ( Count - Iter - 1 ) * sizeof( Stack->Elements[0] ) );
            --Stack->Top;
            RetCode = Iter + 1;
            break;
        }
    }

    return RetCode;
}

ULONG StackRemoveAllU( PCOMMON_STACK_U Stack, ULONG Element )
{
    ULONG RetCode;
    register ULONG Iter;
    register ULONG Count;
    ULONG *Out;

    RetCode = 0;
    Iter = 0;
    Count = Stack->Top;
    while ( Iter < Count && Stack->Elements[Iter] != Element )
        Iter++;

    if ( Iter < Count )
    {
        Out = Stack->Elements + Iter;
        while ( ++Iter < Count )
        {
            if ( Stack->Elements[Iter] != Element )
                *Out++ = Stack->Elements[Iter];
        }
        RetCode = Stack->Top = Out - Stack->Elements;
    }

    return RetCode;
}

ULONG StackRemoveIndexU( PCOMMON_STACK_U Stack, ULONG Index )
{
    if ( Index < Stack->Top )
    {
        memcpy( Stack->Elements + Index, Stack->Elements + Index + 1, ( Stack->Top - Index - 1 ) * sizeof( Stack->Elements[0] ) );
        --Stack->Top;
        return Index + 1;
    }
    else
    {
        return 0;
    }
}

/*
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
*/
ULONG StackInitT(
    PCOMMON_STACK_T Stack,
    ULONG Max,
    ULONG Size,
    STACK_INIT_FUNCTION Init,
    STACK_UNINIT_FUNCTION Uninit,
    STACK_COMPARE_FUNCTION SortCompare,
    STACK_COMPARE_FUNCTION FindCompare,
    PVOID Context
    )
{
    register ULONG Iter;

    if ( Max == 0 )
        Max = DEFAULT_STACK_T_SIZE;
    else
        Max = ROUND_SIZE( Max );

    if ( Size == 0 )
        Size = DEFAULT_STACK_T_ELEMENT_SIZE;

    if ( SortCompare == NULL )
        SortCompare = StackDefaultCompare;

    if ( FindCompare == NULL )
        FindCompare = StackDefaultCompare;

    Stack->Top = 0;
    Stack->Bottom = 0;
    Stack->Elements = ( PVOID* )HEAP_ALLOC( Max * sizeof( Stack->Elements[0] ) );
    Stack->Size = Size;
    Stack->Init = Init;
    Stack->Uninit = Uninit;
    Stack->SortCompare = SortCompare;
    Stack->FindCompare = FindCompare;
    Stack->Context = Context;

    if ( !Stack->Elements )
    {
        Stack->Max = 0;
        return FALSE;
    }

    Stack->Max = Max;
    for ( Iter = 0; Iter < Stack->Max; Iter++ )
        Stack->Elements[Iter] = HEAP_ALLOC( Stack->Size );

    return TRUE;
}

ULONG StackUninitT( PCOMMON_STACK_T Stack )
{
    register ULONG Iter;
    register ULONG Count;

    if ( Stack->Elements )
    {
        if ( Stack->Uninit )
        {
            for ( Iter = 0, Count = Stack->Top; Iter < Count; Iter++ )
                if ( Stack->Elements[Iter] )
                    Stack->Uninit( Stack->Elements[Iter], Stack->Context );
        }
        for ( Iter = 0, Count = Stack->Max; Iter < Count; Iter++ )
            if ( Stack->Elements[Iter] )
                HEAP_FREE( Stack->Elements[Iter] );
        HEAP_FREE( Stack->Elements );
    }

    return Stack->Max;
}

ULONG StackReinitT( PCOMMON_STACK_T Stack )
{
    register ULONG Iter;
    register ULONG Count;

    if ( Stack->Elements )
    {
        if ( Stack->Uninit )
        {
            for ( Iter = 0, Count = Stack->Top; Iter < Count; Iter++ )
                if ( Stack->Elements[Iter] )
                    Stack->Uninit( Stack->Elements[Iter], Stack->Context );
        }
    }

    Stack->Top = 0;
    Stack->Bottom = 0;

    return Stack->Max;
}

ULONG StackSetMaxT( PCOMMON_STACK_T Stack, ULONG Max )
{
    register PVOID *NewBuffer;
    register ULONG Iter;
    register ULONG Count;

    if ( Max > Stack->Max )
    {
        Max = ROUND_SIZE( Max );
        NewBuffer = ( PVOID* )HEAP_REALLOC( Stack->Elements, Max * sizeof( Stack->Elements[0] ) );
        if ( !NewBuffer )
        {
            NewBuffer = ( PVOID* )HEAP_ALLOC( Max * sizeof( Stack->Elements[0] ) );
            if ( NewBuffer == NULL )
            {
                GET_GS_STACK_ALLOC_FAIL( )( Stack, STACK_TYPE_T, GET_GS_STACK_ALLOC_FAIL_CONTEXT( ) );
                return FALSE;
            }

            memcpy( NewBuffer, Stack->Elements, Stack->Top * sizeof( Stack->Elements[0] ) );
            HEAP_FREE( Stack->Elements );
        }
        for ( Iter = Stack->Max, Count = Max; Iter < Count; Iter++ )
            NewBuffer[Iter] = HEAP_ALLOC( Stack->Size );

        Stack->Elements = NewBuffer;
        Stack->Max = Max;
    }

    return Stack->Max;
}

ULONG StackAddElementT( PCOMMON_STACK_T Stack, PVOID Element, ULONG Size )
{
    if ( Stack->Top >= Stack->Max )
    {
        if ( !StackSetMaxT( Stack, Stack->Max + DEFAULT_STACK_T_SIZE ) )
            return FALSE;
    }
    if ( Stack->Elements[Stack->Top] == NULL )
    {
        Stack->Elements[Stack->Top] = HEAP_ALLOC( Stack->Size );
        if ( Stack->Elements[Stack->Top] == NULL )
            return FALSE;
    }

    memcpy( Stack->Elements[Stack->Top], Element, Size );

    if ( Stack->Init )
        Stack->Init( Stack->Elements[Stack->Top], Stack->Context );

    return TRUE;
}

ULONG StackSetTopT( PCOMMON_STACK_T Stack, ULONG Top )
{
    if ( Top > Stack->Max )
        Stack->Top = Stack->Max - 1;
    else
        Stack->Top = Top;

    return Stack->Top;
}

ULONG StackSetBottomT( PCOMMON_STACK_T Stack, ULONG Bottom )
{
    if ( Bottom > Stack->Top )
        Stack->Bottom = Stack->Top;
    else
        Stack->Bottom = Bottom;

    return Stack->Bottom;
}

void StackSetSortCompareT( PCOMMON_STACK_T Stack, STACK_COMPARE_FUNCTION Compare )
{
    if ( Compare == NULL )
        Stack->SortCompare = StackDefaultCompare;
    else
        Stack->SortCompare = Compare;
}

void StackSetFindCompareT( PCOMMON_STACK_T Stack, STACK_COMPARE_FUNCTION Compare )
{
    if ( Compare == NULL )
        Stack->FindCompare = StackDefaultCompare;
    else
        Stack->FindCompare = Compare;
}

ULONG StackFindT( PCOMMON_STACK_T Stack, PVOID Element )
{
    register ULONG Iter;
    register ULONG Count;

    Count = Stack->Top;
    for ( Iter = 0; Iter < Count; Iter++ )
    {
        if ( 0 == Stack->FindCompare( Stack->Elements[Iter], Element ) )
            return Iter + 1;
    }

    return 0;
}

ULONG StackFindReverseT( PCOMMON_STACK_T Stack, PVOID Element )
{
    register ULONG Iter;

    Iter = Stack->Top;
    while ( Iter )
    {
        Iter--;
        if ( 0 == Stack->FindCompare( Stack->Elements[Iter], Element ) )
            return Iter + 1;
    }

    return 0;
}

ULONG StackFindAscT( PCOMMON_STACK_T Stack, PVOID Element )
{
    ULONG RetCode;
    register ULONG Start;
    register ULONG End;
    register ULONG Mid;
    register LONG Sign;
    register PVOID StackElement;

    RetCode = 0;
    End = Stack->Top;
    if ( End )
    {
        Start = 0;
        Mid = End >> 1;
        while ( Mid < End )
        {
            StackElement = Stack->Elements[Mid];
            Sign = Stack->FindCompare( Element, StackElement );
            if ( Sign > 0 )
            {
                Start = Mid + 1;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else if ( Sign < 0 )
            {
                End = Mid;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else
            {
                RetCode = Mid + 1;
                break;
            }
        }
    }

    return RetCode;
}

ULONG StackFindDscT( PCOMMON_STACK_T Stack, PVOID Element )
{
    ULONG RetCode;
    register ULONG Start;
    register ULONG End;
    register ULONG Mid;
    register LONG Sign;
    register PVOID StackElement;

    RetCode = 0;
    End = Stack->Top;
    if ( End )
    {
        Start = 0;
        Mid = End >> 1;
        while ( Mid < End )
        {
            StackElement = Stack->Elements[Mid];
            Sign = Stack->FindCompare( Element, StackElement );
            if ( Sign < 0 )
            {
                Start = Mid + 1;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else if ( Sign > 0 )
            {
                End = Mid;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else
            {
                RetCode = Mid + 1;
                break;
            }
        }
    }

    return RetCode;
}

ULONG StackFindLargeAscT( PCOMMON_STACK_T Stack, PVOID Element )
{
    ULONG RetCode;
    register ULONG Start;
    register ULONG End;
    register ULONG Mid;
    register LONG Sign;
    register PVOID StackElement;

    RetCode = 0;
    End = Stack->Top;
    if ( End )
    {
        Start = 0;
        Mid = End >> 1;
        while ( Mid < End )
        {
            StackElement = Stack->Elements[Mid];
            Sign = Stack->FindCompare( Element, StackElement );
            if ( Sign > 0 )
            {
                Start = Mid + 1;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else if ( Sign < 0 )
            {
                End = Mid;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else
            {
                End = Mid + 1;
                break;
            }
        }
        if ( End < Stack->Top )
            RetCode = End + 1;
    }

    return RetCode;
}

ULONG StackFindLargeEqualAscT( PCOMMON_STACK_T Stack, PVOID Element )
{
    ULONG RetCode;
    register ULONG Start;
    register ULONG End;
    register ULONG Mid;
    register LONG Sign;
    register PVOID StackElement;

    RetCode = 0;
    End = Stack->Top;
    if ( End )
    {
        Start = 0;
        Mid = End >> 1;
        while ( Mid < End )
        {
            StackElement = Stack->Elements[Mid];
            Sign = Stack->FindCompare( Element, StackElement );
            if ( Sign > 0 )
            {
                Start = Mid + 1;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else if ( Sign < 0 )
            {
                End = Mid;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else
            {
                End = Mid;
                break;
            }
        }
        if ( End < Stack->Top )
            RetCode = End + 1;
    }

    return RetCode;
}

ULONG StackFindLargeDscT( PCOMMON_STACK_T Stack, PVOID Element )
{
    ULONG RetCode;
    register ULONG Start;
    register ULONG End;
    register ULONG Mid;
    register LONG Sign;
    register PVOID StackElement;

    RetCode = 0;
    End = Stack->Top;
    if ( End )
    {
        Start = 0;
        Mid = End >> 1;
        while ( Mid < End )
        {
            StackElement = Stack->Elements[Mid];
            Sign = Stack->FindCompare( Element, StackElement );
            if ( Sign < 0 )
            {
                Start = Mid + 1;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else if ( Sign > 0 )
            {
                End = Mid;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else
            {
                Start = Mid > 0 ? Mid - 1 : Mid;
                break;
            }
        }
        if ( Start < Mid )
            RetCode = Start + 1;
        else
            RetCode = Start;
    }

    return RetCode;
}

ULONG StackFindLargeEqualDscT( PCOMMON_STACK_T Stack, PVOID Element )
{
    ULONG RetCode;
    register ULONG Start;
    register ULONG End;
    register ULONG Mid;
    register LONG Sign;
    register PVOID StackElement;

    RetCode = 0;
    End = Stack->Top;
    if ( End )
    {
        Start = 0;
        Mid = End >> 1;
        while ( Mid < End )
        {
            StackElement = Stack->Elements[Mid];
            Sign = Stack->FindCompare( Element, StackElement );
            if ( Sign < 0 )
            {
                Start = Mid + 1;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else if ( Sign > 0 )
            {
                End = Mid;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else
            {
                End = Mid;
                break;
            }
        }
        if ( Start < Mid )
            RetCode = Start + 1;
        else
            RetCode = Start;
    }

    return RetCode;
}

ULONG StackFindSmallAscT( PCOMMON_STACK_T Stack, PVOID Element )
{
    ULONG RetCode;
    register ULONG Start;
    register ULONG End;
    register ULONG Mid;
    register LONG Sign;
    register PVOID StackElement;

    RetCode = 0;
    End = Stack->Top;
    if ( End )
    {
        Start = 0;
        Mid = End >> 1;
        while ( Mid < End )
        {
            StackElement = Stack->Elements[Mid];
            Sign = Stack->FindCompare( Element, StackElement );
            if ( Sign > 0 )
            {
                Start = Mid + 1;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else if ( Sign < 0 )
            {
                End = Mid;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else
            {
                Start = Mid > 0 ? Mid - 1 : Mid;
                break;
            }
        }
        if ( Start < Mid )
            RetCode = Start + 1;
        else
            RetCode = Start;
    }

    return RetCode;
}

ULONG StackFindSmallEqualAscT( PCOMMON_STACK_T Stack, PVOID Element )
{
    ULONG RetCode;
    register ULONG Start;
    register ULONG End;
    register ULONG Mid;
    register LONG Sign;
    register PVOID StackElement;

    RetCode = 0;
    End = Stack->Top;
    if ( End )
    {
        Start = 0;
        Mid = End >> 1;
        while ( Mid < End )
        {
            StackElement = Stack->Elements[Mid];
            Sign = Stack->FindCompare( Element, StackElement );
            if ( Sign > 0 )
            {
                Start = Mid + 1;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else if ( Sign < 0 )
            {
                End = Mid;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else
            {
                Start = Mid;
                break;
            }
        }
        if ( Start < Mid )
            RetCode = Start + 1;
        else
            RetCode = Start;
    }

    return RetCode;
}

ULONG StackFindSmallDscT( PCOMMON_STACK_T Stack, PVOID Element )
{
    ULONG RetCode;
    register ULONG Start;
    register ULONG End;
    register ULONG Mid;
    register LONG Sign;
    register PVOID StackElement;

    RetCode = 0;
    End = Stack->Top;
    if ( End )
    {
        Start = 0;
        Mid = End >> 1;
        while ( Mid < End )
        {
            StackElement = Stack->Elements[Mid];
            Sign = Stack->FindCompare( Element, StackElement );
            if ( Sign < 0 )
            {
                Start = Mid + 1;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else if ( Sign > 0 )
            {
                End = Mid;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else
            {
                End = Mid + 1;
                break;
            }
        }
        if ( End < Stack->Top )
            RetCode = End + 1;
    }

    return RetCode;
}

ULONG StackFindSmallEqualDscT( PCOMMON_STACK_T Stack, PVOID Element )
{
    ULONG RetCode;
    register ULONG Start;
    register ULONG End;
    register ULONG Mid;
    register LONG Sign;
    register PVOID StackElement;

    RetCode = 0;
    End = Stack->Top;
    if ( End )
    {
        Start = 0;
        Mid = End >> 1;
        while ( Mid < End )
        {
            StackElement = Stack->Elements[Mid];
            Sign = Stack->FindCompare( Element, StackElement );
            if ( Sign < 0 )
            {
                Start = Mid + 1;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else if ( Sign > 0 )
            {
                End = Mid;
                Mid = ( Start >> 1 ) + ( End >> 1 ) + ( Start & End & 1 );
            }
            else
            {
                End = Mid + 1;
                break;
            }
        }
        if ( End < Stack->Top )
            RetCode = End + 1;
    }

    return RetCode;
}

ULONG StackPopAllT( PCOMMON_STACK_T Stack, PVOID **Element )
{
    register ULONG Top;

    if ( Element )
        *Element = Stack->Elements;

    Top = Stack->Top;
    Stack->Top = 0;

    return Top;
}

ULONG StackPushT( PCOMMON_STACK_T Stack, PVOID Element )
{
    if ( !StackAddElementT( Stack, Element, Stack->Size ) )
        return 0;

    return ++Stack->Top;
}

ULONG StackPushAscT( PCOMMON_STACK_T Stack, PVOID Element )
{
    ULONG Pos;
    register PVOID *Start;
    register PVOID *Cur;
    register PVOID *Prev;
    register PVOID Exchange;

    if ( !StackAddElementT( Stack, Element, Stack->Size ) )
        return 0;

    Pos = ++Stack->Top;
    Start = Stack->Elements;
    Cur = Stack->Elements + Stack->Top - 1;
    Prev = Cur - 1;
    while ( Cur != Start )
    {
        if ( Stack->SortCompare( *Cur, *Prev ) < 0 )
        {
            Pos--;
            Exchange = *Prev;
            *Prev = *Cur;
            *Cur = Exchange;
        }
        else
            break;
        Cur--;
        Prev--;
    }

    return Pos;
}

ULONG StackPushDscT( PCOMMON_STACK_T Stack, PVOID Element )
{
    ULONG Pos;
    register PVOID *Start;
    register PVOID *Cur;
    register PVOID *Prev;
    register PVOID Exchange;

    if ( !StackAddElementT( Stack, Element, Stack->Size ) )
        return 0;

    Pos = ++Stack->Top;
    Start = Stack->Elements;
    Cur = Stack->Elements + Stack->Top - 1;
    Prev = Cur - 1;
    while ( Cur != Start )
    {
        if ( Stack->SortCompare( *Cur, *Prev ) > 0 )
        {
            Pos--;
            Exchange = *Prev;
            *Prev = *Cur;
            *Cur = Exchange;
        }
        else
            break;
        Cur--;
        Prev--;
    }

    return Pos;
}

ULONG StackPushSizeT( PCOMMON_STACK_T Stack, PVOID Element, ULONG Size )
{
    if ( !StackAddElementT( Stack, Element, Size ) )
        return 0;

    return ++Stack->Top;
}

ULONG StackPushSizeAscT( PCOMMON_STACK_T Stack, PVOID Element, ULONG Size )
{
    ULONG Pos;
    register PVOID *Start;
    register PVOID *Cur;
    register PVOID *Prev;
    register PVOID Exchange;

    if ( !StackAddElementT( Stack, Element, Size ) )
        return 0;

    Pos = ++Stack->Top;
    Start = Stack->Elements;
    Cur = Stack->Elements + Stack->Top - 1;
    Prev = Cur - 1;
    while ( Cur != Start )
    {
        if ( Stack->SortCompare( *Cur, *Prev ) < 0 )
        {
            Pos--;
            Exchange = *Prev;
            *Prev = *Cur;
            *Cur = Exchange;
        }
        else
            break;
        Cur--;
        Prev--;
    }

    return Pos;
}

ULONG StackPushSizeDscT( PCOMMON_STACK_T Stack, PVOID Element, ULONG Size )
{
    ULONG Pos;
    register PVOID *Start;
    register PVOID *Cur;
    register PVOID *Prev;
    register PVOID Exchange;

    if ( !StackAddElementT( Stack, Element, Size ) )
        return 0;

    Pos = ++Stack->Top;
    Start = Stack->Elements;
    Cur = Stack->Elements + Stack->Top - 1;
    Prev = Cur - 1;
    while ( Cur != Start )
    {
        if ( Stack->SortCompare( *Cur, *Prev ) > 0 )
        {
            Pos--;
            Exchange = *Prev;
            *Prev = *Cur;
            *Cur = Exchange;
        }
        else
            break;
        Cur--;
        Prev--;
    }

    return Pos;
}

ULONG StackPopT( PCOMMON_STACK_T Stack, PVOID *Element )
{
    register ULONG Top;

    Top = Stack->Top;
    if ( Stack->Top )
    {
        Stack->Top--;
        if ( Element )
            *Element = Stack->Elements[Stack->Top];
    }
    else
    {
        if ( Element )
            *Element = 0;
    }

    return Top;
}

ULONG StackTopT( PCOMMON_STACK_T Stack, PVOID *Element )
{
    if ( Stack->Top )
        *Element = Stack->Elements[Stack->Top - 1];
    else
        *Element = 0;

    return Stack->Top;
}

ULONG StackPopBottomT( PCOMMON_STACK_T Stack, PVOID *Element )
{
    if ( Stack->Bottom < Stack->Top )
    {
        if ( Element )
            *Element = Stack->Elements[Stack->Bottom];
        Stack->Bottom++;
        return 1;
    }
    else
    {
        if ( Element )
            *Element = 0;
        return 0;
    }
}

ULONG StackBottomT( PCOMMON_STACK_T Stack, PVOID *Element )
{
    if ( Stack->Bottom < Stack->Top )
    {
        *Element = Stack->Elements[Stack->Bottom];
        return Stack->Top - Stack->Bottom;
    }
    else
    {
        *Element = 0;
        return 0;
    }
}

ULONG StackRemoveT( PCOMMON_STACK_T Stack, PVOID Element )
{
    ULONG RetCode;
    register ULONG Iter;
    register ULONG Count;

    RetCode = 0;
    Iter = 0;
    Count = Stack->Top;
    while ( Iter < Count )
    {
        if ( Stack->Elements[Iter] == Element )
        {
            memcpy( Stack->Elements + Iter, Stack->Elements + Iter + 1, ( Count - Iter - 1 ) * sizeof( Stack->Elements[0] ) );
            --Stack->Top;
            RetCode = Iter + 1;
            break;
        }
        Iter++;
    }

    return RetCode;
}

ULONG StackRemoveIndexT( PCOMMON_STACK_T Stack, ULONG Index )
{
    if ( Index < Stack->Top )
    {
        if ( Stack->Uninit )
            Stack->Uninit( Stack->Elements[Index], Stack->Context );

        memcpy( Stack->Elements + Index, Stack->Elements + Index + 1, ( Stack->Top - Index - 1 ) * sizeof( Stack->Elements[0] ) );
        --Stack->Top;
        return Index + 1;
    }
    else
    {
        return 0;
    }
}

/*
///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////
*/
ULONG StackInitS( PCOMMON_STACK_S Stack, ULONG Max )
{
    if ( Max == 0 )
        Max = DEFAULT_STACK_S_SIZE;

    Stack->Top = 0;
    Stack->Bottom = 0;
    Stack->PrefixTop = DEFAULT_STACK_S_PREFIX_SIZE;
    Stack->PrefixMax = DEFAULT_STACK_S_PREFIX_SIZE;
    Stack->AllocateBase = ( TCHAR* )HEAP_ALLOC( ( Max + Stack->PrefixMax ) * sizeof( Stack->Elements[0] ) );
    if ( !Stack->AllocateBase )
    {
        Stack->Max = 0;
        Stack->Elements = NULL;
        return FALSE;
    }
    else
    {
        Stack->Max = Max;
        Stack->Elements = Stack->AllocateBase + Stack->PrefixMax;
        Stack->Elements[0] = END_CHAR;
        return TRUE;
    }
}

ULONG StackInitExS( PCOMMON_STACK_S Stack, ULONG Max, ULONG Prefix )
{
    if ( Max == 0 )
        Max = DEFAULT_STACK_S_SIZE;

    if ( Prefix == 0 )
        Prefix = DEFAULT_STACK_S_PREFIX_SIZE;

    Stack->Top = 0;
    Stack->Bottom = 0;
    Stack->AllocateBase = ( TCHAR* )HEAP_ALLOC( ( Max + Stack->PrefixMax ) * sizeof( Stack->Elements[0] ) );
    Stack->PrefixTop = DEFAULT_STACK_S_PREFIX_SIZE;
    Stack->PrefixMax = DEFAULT_STACK_S_PREFIX_SIZE;
    if ( !Stack->AllocateBase )
    {
        Stack->Max = 0;
        Stack->Elements = NULL;
        return FALSE;
    }
    else
    {
        Stack->Max = Max;
        Stack->Elements = Stack->AllocateBase + Stack->PrefixMax;
        Stack->Elements[0] = END_CHAR;
        return TRUE;
    }
}

ULONG StackUninitS( PCOMMON_STACK_S Stack )
{
    if ( Stack->AllocateBase )
        HEAP_FREE( Stack->AllocateBase );

    return TRUE;
}

ULONG StackReinitS( PCOMMON_STACK_S Stack )
{
    Stack->Top = 0;
    Stack->Bottom = 0;
    Stack->PrefixTop = Stack->PrefixMax;

    if ( Stack->Elements )
        *Stack->Elements = END_CHAR;

    return Stack->Max;
}

ULONG StackSetMaxS( PCOMMON_STACK_S Stack, ULONG Max )
{
    register TCHAR *NewBuffer;

    if ( Max >= Stack->Max )
    {
        Max = ROUND_SIZE( Stack->PrefixMax + Max );
        NewBuffer = ( TCHAR* )HEAP_REALLOC( Stack->AllocateBase, Max * sizeof( Stack->Elements[0] ) );
        if ( !NewBuffer )
        {
            NewBuffer = ( TCHAR* )HEAP_ALLOC( Max * sizeof( Stack->Elements[0] ) );
            if ( NewBuffer == NULL )
            {
                GET_GS_STACK_ALLOC_FAIL( )( Stack, STACK_TYPE_S, GET_GS_STACK_ALLOC_FAIL_CONTEXT( ) );
                return FALSE;
            }

            memcpy( NewBuffer, Stack->AllocateBase, ( Stack->PrefixMax + Stack->Top ) * sizeof( Stack->Elements[0] ) );
            HEAP_FREE( Stack->AllocateBase );
        }
        Stack->AllocateBase = NewBuffer;
        Stack->Max = Max - Stack->PrefixMax;
        Stack->Elements = Stack->AllocateBase + Stack->PrefixMax;
        Stack->Elements[Stack->Top] = END_CHAR;
    }

    return Stack->Max;
}

ULONG StackSetTopS( PCOMMON_STACK_S Stack, ULONG Top )
{
    if ( Top > Stack->Max )
        Stack->Top = Stack->Max - 1;
    else
        Stack->Top = Top;

    return Stack->Top;
}

ULONG StackFindS( PCOMMON_STACK_S Stack, TCHAR Element )
{
    register ULONG Iter;
    register ULONG Count;

    Count = Stack->Top;
    for ( Iter = 0; Iter < Count; Iter++ )
    {
        if ( Stack->Elements[Iter] == Element )
            return Iter + 1;
    }

    return 0;
}

ULONG StackFindReverseS( PCOMMON_STACK_S Stack, TCHAR Element )
{
    register ULONG Iter;

    Iter = Stack->Top;
    while ( Iter )
    {
        Iter--;
        if ( Stack->Elements[Iter] == Element )
            return Iter + 1;
    }

    return 0;
}

ULONG StackPopAllS( PCOMMON_STACK_S Stack, const TCHAR **Element )
{
    register ULONG Top;

    if ( Element )
        *Element = Stack->Elements;

    Top = Stack->Top;
    Stack->Top = 0;

    return Top;
}

ULONG StackPushS( PCOMMON_STACK_S Stack, const TCHAR *Element, ULONG Size )
{
    if ( Stack->Top + Size >= Stack->Max )
    {
        if ( !StackSetMaxS( Stack, Stack->Top + Size + DEFAULT_STACK_S_SIZE ) )
            return FALSE;
    }
    memcpy( Stack->Elements + Stack->Top, Element, Size * sizeof( Stack->Elements[0] ) );
    Stack->Top += Size;
    Stack->Elements[Stack->Top] = END_CHAR;

    return Stack->Top;
}

ULONG StackPushNS( PCOMMON_STACK_S Stack, TCHAR Element, ULONG Size )
{
    if ( Stack->Top + Size >= Stack->Max )
    {
        if ( !StackSetMaxS( Stack, Stack->Top + Size + DEFAULT_STACK_S_SIZE ) )
            return FALSE;
    }
    memset( Stack->Elements + Stack->Top, Element, Size * sizeof( Stack->Elements[0] ) );
    Stack->Top += Size;
    Stack->Elements[Stack->Top] = END_CHAR;

    return Stack->Top;
}

ULONG StackPopS( PCOMMON_STACK_S Stack, TCHAR *Element )
{
    register ULONG Top;

    Top = Stack->Top;
    if ( Stack->Top )
    {
        Stack->Top--;
        if ( Element )
            *Element = Stack->Elements[Stack->Top];
        Stack->Elements[Stack->Top] = END_CHAR;
    }
    else
    {
        if ( Element )
            *Element = END_CHAR;
    }

    return Top;
}

ULONG StackPopNS( PCOMMON_STACK_S Stack, TCHAR *Element, ULONG Size )
{
    register ULONG PopSize;

    if ( Stack->Top )
    {
        if ( Size > Stack->Top )
            PopSize = Stack->Top;
        else
            PopSize = Size;
        Stack->Top -= PopSize;
        if ( Element )
        {
            memcpy( Element, Stack->Elements + Stack->Top, PopSize * sizeof( Stack->Elements[0] ) );
            Element[PopSize] = END_CHAR;
        }
        Stack->Elements[Stack->Top] = END_CHAR;
    }
    else
    {
        PopSize = 0;
        if ( Element )
            *Element = END_CHAR;
    }

    return PopSize;
}

ULONG StackTopS( PCOMMON_STACK_S Stack, TCHAR *Element )
{
    if ( Stack->Top )
        *Element = Stack->Elements[Stack->Top - 1];
    else
        *Element = END_CHAR;

    return Stack->Top;
}

ULONG StackPopAllExS( PCOMMON_STACK_S Stack, const TCHAR **Element )
{
    register ULONG Top;

    Top = Stack->Top + Stack->PrefixMax - Stack->PrefixTop;
    if ( Element )
        *Element = Stack->AllocateBase + Stack->PrefixTop;

    Stack->Top = 0;
    Stack->PrefixTop = Stack->PrefixMax;

    return Top;
}

ULONG StackSetPrefixS( PCOMMON_STACK_S Stack, ULONG Prefix )
{
    if ( Prefix > Stack->PrefixMax )
        Stack->PrefixTop = Stack->PrefixMax;
    else
        Stack->PrefixTop = Prefix;

    return Stack->PrefixTop;
}

ULONG StackPushPrefixS( PCOMMON_STACK_S Stack, const TCHAR *Element, ULONG Size )
{
    if ( Stack->PrefixTop > Size )
    {
        Stack->PrefixTop -= Size;
        memcpy( Stack->AllocateBase + Stack->PrefixTop, Element, Size * sizeof( Stack->Elements[0] ) );
        return Size;
    }
    else
        return 0;
}

ULONG StackPopPrefixS( PCOMMON_STACK_S Stack, TCHAR *Element )
{
    if ( Stack->PrefixTop < Stack->PrefixMax )
    {
        if ( Element )
            *Element = Stack->AllocateBase[Stack->PrefixTop];
        Stack->PrefixTop++;
        return 1;
    }
    else
    {
        if ( Element )
            *Element = END_CHAR;
        return 0;
    }
}

ULONG StackPopPrefixNS( PCOMMON_STACK_S Stack, TCHAR *Element, ULONG Size )
{
    register ULONG PopSize;

    if ( Stack->PrefixTop < Stack->PrefixMax )
    {
        if ( Size > Stack->PrefixMax - Stack->PrefixTop )
            PopSize = Stack->PrefixMax - Stack->PrefixTop;
        else
            PopSize = Size;
        if ( Element )
        {
            memcpy( Element, Stack->AllocateBase + Stack->PrefixTop, PopSize * sizeof( Stack->Elements[0] ) );
            Element[PopSize] = END_CHAR;
        }
        Stack->PrefixTop += PopSize;
    }
    else
    {
        PopSize = 0;
        if ( Element )
            *Element = END_CHAR;
    }

    return PopSize;
}

ULONG StackTopPrefixS( PCOMMON_STACK_S Stack, TCHAR *Element )
{
    if ( Stack->PrefixTop < Stack->PrefixMax )
    {
        *Element = Stack->AllocateBase[Stack->PrefixTop];
        return Stack->PrefixMax - Stack->Top;
    }
    else
    {
        *Element = END_CHAR;
        return 0;
    }
}

ULONG StackPopBottomS( PCOMMON_STACK_S Stack, TCHAR *Element )
{
    if ( Stack->Bottom < Stack->Top )
    {
        if ( Element )
            *Element = Stack->Elements[Stack->Bottom];
        Stack->Bottom++;
        return 1;
    }
    else
    {
        if ( Element )
            *Element = END_CHAR;
        return 0;
    }
}

ULONG StackPopBottomNS( PCOMMON_STACK_S Stack, TCHAR *Element, ULONG Size )
{
    register ULONG PopSize;

    if ( Stack->Bottom < Stack->Top )
    {
        if ( Size > Stack->Top - Stack->Bottom )
            PopSize = Stack->Top - Stack->Bottom;
        else
            PopSize = Size;
        if ( Element )
        {
            memcpy( Element, Stack->Elements + Stack->Bottom, PopSize * sizeof( Stack->Elements[0] ) );
            Element[PopSize] = END_CHAR;
        }
        Stack->Bottom += PopSize;
    }
    else
    {
        PopSize = 0;
        if ( Element )
            *Element = END_CHAR;
    }

    return PopSize;
}

ULONG StackBottomS( PCOMMON_STACK_S Stack, TCHAR *Element )
{
    if ( Stack->Bottom < Stack->Top )
    {
        *Element = Stack->Elements[Stack->Bottom];
        return Stack->Top - Stack->Bottom;
    }
    else
    {
        *Element = END_CHAR;
        return 0;
    }
}

ULONG StackRemoveS( PCOMMON_STACK_S Stack, TCHAR Element )
{
    ULONG RetCode;
    register ULONG Iter;
    register ULONG Count;

    RetCode = 0;
    Iter = 0;
    Count = Stack->Top;
    while ( Iter < Count )
    {
        if ( Stack->Elements[Iter] == Element )
        {
            memcpy( Stack->Elements + Iter, Stack->Elements + Iter + 1, ( Count - Iter - 1 ) * sizeof( Stack->Elements[0] ) );
            Stack->Elements[( --Stack->Top )] = END_CHAR;
            RetCode = Iter + 1;
            break;
        }
        Iter++;
    }

    return RetCode;
}

ULONG StackReverseRemoveS( PCOMMON_STACK_S Stack, TCHAR Element )
{
    ULONG RetCode;
    register ULONG Iter;
    register ULONG Count;

    RetCode = 0;
    Count = Stack->Top;
    Iter = Count;
    while ( Iter )
    {
        Iter--;
        if ( Stack->Elements[Iter] == Element )
        {
            memcpy( Stack->Elements + Iter, Stack->Elements + Iter + 1, ( Count - Iter - 1 ) * sizeof( Stack->Elements[0] ) );
            Stack->Elements[( --Stack->Top )] = END_CHAR;
            RetCode = Iter + 1;
            break;
        }
    }

    return RetCode;
}

ULONG StackRemoveAllS( PCOMMON_STACK_S Stack, TCHAR Element )
{
    ULONG RetCode;
    register ULONG Iter;
    register ULONG Count;
    TCHAR *Out;

    RetCode = 0;
    Iter = 0;
    Count = Stack->Top;
    while ( Iter < Count && Stack->Elements[Iter] != Element )
        Iter++;

    if ( Iter < Count )
    {
        Out = Stack->Elements + Iter;
        while ( ++Iter < Count )
        {
            if ( Stack->Elements[Iter] != Element )
                *Out++ = Stack->Elements[Iter];
        }
        RetCode = Stack->Top = Out - Stack->Elements;
        Stack->Elements[Stack->Top] = END_CHAR;
    }

    return RetCode;
}

ULONG StackRemoveIndexS( PCOMMON_STACK_S Stack, ULONG Index )
{
    if ( Index < Stack->Top )
    {
        memcpy( Stack->Elements + Index, Stack->Elements + Index + 1, ( Stack->Top - Index - 1 ) * sizeof( Stack->Elements[0] ) );
        --Stack->Top;
        return Index + 1;
    }
    else
    {
        return 0;
    }
}