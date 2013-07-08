/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   Stack.h
//  Version     :   1.0
//  Creator     :   RM
//  Create Date :   2006-01-01
//  Comment     :
//
///////////////////////////////////////////////////////////////////////////////
*/

#ifndef __STACK_H__
#define __STACK_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/
/* Macro */
#define DEFAULT_ROUND_BIT 4
#define ROUND_TO_BIT( Size, Bit ) ( ( ( Size ) + ( 1 << ( Bit ) ) - 1 ) & ~( ( 1 << ( Bit ) ) - 1 ) )
#define ROUND_SIZE( Size ) ROUND_TO_BIT( Size, DEFAULT_ROUND_BIT )
#define ROUND_STRING( Size ) ROUND_TO_BIT( ( Size ) + 1, DEFAULT_ROUND_BIT )

#define STACK_APPLY_TOPDOWN 1
#define STACK_APPLY_BOTTOMUP 2

typedef enum _STACK_TYPE {
    STACK_TYPE_P,
    STACK_TYPE_U,
    STACK_TYPE_T,
    STACK_TYPE_S,
} STACK_TYPE;

/*
///////////////////////////////////////////////////////////////////////////////
// S T R U C T U R E S
///////////////////////////////////////////////////////////////////////////////
*/
typedef LONG ( *STACK_ALLOC_FAIL_FUNCTION ) ( PVOID Stack, STACK_TYPE Type, PVOID Context );

typedef ULONG ( *STACK_FUNCTION ) ( PVOID Element );
typedef ULONG ( *STACK_FUNCTION_EX ) ( PVOID Element, PVOID Context );
typedef ULONG ( *STACK_INIT_FUNCTION ) ( PVOID Element, PVOID Context );
typedef ULONG ( *STACK_UNINIT_FUNCTION ) ( PVOID Element, PVOID Context );
typedef LONG ( *STACK_COMPARE_FUNCTION ) ( PVOID Element1, PVOID Element2 );

typedef struct _COMMON_STACK {
    ULONG Top;
    ULONG Bottom;
    ULONG Max;
    PVOID *Elements;
} COMMON_STACK, *PCOMMON_STACK;

typedef struct _COMMON_STACK_U {
    ULONG Top;
    ULONG Bottom;
    ULONG Max;
    ULONG *Elements;
} COMMON_STACK_U, *PCOMMON_STACK_U;

typedef struct _COMMON_STACK_T {
    ULONG Top;
    ULONG Max;
    ULONG Bottom;
    PVOID *Elements;
    ULONG Size;
    STACK_INIT_FUNCTION Init;
    STACK_UNINIT_FUNCTION Uninit;
    STACK_COMPARE_FUNCTION SortCompare;
    STACK_COMPARE_FUNCTION FindCompare;
    PVOID Context;
} COMMON_STACK_T, *PCOMMON_STACK_T;

typedef struct _COMMON_STACK_S {
    ULONG Top;
    ULONG Max;
    ULONG Bottom;
    TCHAR *Elements;
    ULONG PrefixTop;
    ULONG PrefixMax;
    TCHAR *AllocateBase;
} COMMON_STACK_S, *PCOMMON_STACK_S;

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
/* Memory */
PVOID StackAlloc( ULONG Size );
PVOID StackReAlloc( PVOID Buffer, ULONG Size );
void StackFree( PVOID Buffer );

/* Memory allocate fail */
void StackSetAllocFail( STACK_ALLOC_FAIL_FUNCTION, PVOID Context );

/* Object Pointer */
ULONG StackInit( PCOMMON_STACK Stack, ULONG Max );
ULONG StackUninit( PCOMMON_STACK Stack );
ULONG StackReinit( PCOMMON_STACK Stack );
ULONG StackSetMax( PCOMMON_STACK Stack, ULONG Max );
ULONG StackSetTop( PCOMMON_STACK Stack, ULONG Top );
ULONG StackSetBottom( PCOMMON_STACK Stack, ULONG Bottom );
ULONG StackFind( PCOMMON_STACK Stack, PVOID Element );
ULONG StackFindReverse( PCOMMON_STACK Stack, PVOID Element );
ULONG StackPopAll( PCOMMON_STACK Stack, PVOID **Element );
ULONG StackPush( PCOMMON_STACK Stack, PVOID Element, ULONG Size );
ULONG StackPop( PCOMMON_STACK Stack, PVOID Element, ULONG Size );
ULONG StackTop( PCOMMON_STACK Stack, PVOID *Element );
ULONG StackPopBottom( PCOMMON_STACK Stack, PVOID Element, ULONG Size );
ULONG StackBottom( PCOMMON_STACK Stack, PVOID *Element );
ULONG StackRemove( PCOMMON_STACK Stack, PVOID Element );
ULONG StackRemoveIndex( PCOMMON_STACK Stack, ULONG Index );
void StackApply( PCOMMON_STACK Stack, ULONG Type, STACK_FUNCTION );
void StackApplyEx( PCOMMON_STACK Stack, ULONG Type, STACK_FUNCTION_EX, PVOID Context );

/* Ulong */
ULONG StackInitU( PCOMMON_STACK_U Stack, ULONG Max );
ULONG StackUninitU( PCOMMON_STACK_U Stack );
ULONG StackReinitU( PCOMMON_STACK_U Stack );
ULONG StackSetMaxU( PCOMMON_STACK_U Stack, ULONG Max );
ULONG StackSetTopU( PCOMMON_STACK_U Stack, ULONG Top );
ULONG StackSetBottomU( PCOMMON_STACK_U Stack, ULONG Bottom );
ULONG StackFindU( PCOMMON_STACK_U Stack, ULONG Element );
ULONG StackFindReverseU( PCOMMON_STACK_U Stack, ULONG Element );
ULONG StackFindAscU( PCOMMON_STACK_U Stack, ULONG Element );
ULONG StackFindDscU( PCOMMON_STACK_U Stack, ULONG Element );
ULONG StackFindLargeAscU( PCOMMON_STACK_U Stack, ULONG Element );
ULONG StackFindLargeEqualAscU( PCOMMON_STACK_U Stack, ULONG Element );
ULONG StackFindLargeDscU( PCOMMON_STACK_U Stack, ULONG Element );
ULONG StackFindLargeEqualDscU( PCOMMON_STACK_U Stack, ULONG Element );
ULONG StackFindSmallAscU( PCOMMON_STACK_U Stack, ULONG Element );
ULONG StackFindSmallEqualAscU( PCOMMON_STACK_U Stack, ULONG Element );
ULONG StackFindSmallDscU( PCOMMON_STACK_U Stack, ULONG Element );
ULONG StackFindSmallEqualDscU( PCOMMON_STACK_U Stack, ULONG Element );
ULONG StackPopAllU( PCOMMON_STACK_U Stack, ULONG **Element );
ULONG StackPushU( PCOMMON_STACK_U Stack, ULONG Element );
ULONG StackPushIncU( PCOMMON_STACK_U Stack, ULONG Element );
ULONG StackPushDecU( PCOMMON_STACK_U Stack, ULONG Element );
ULONG StackPushAscU( PCOMMON_STACK_U Stack, ULONG Element );
ULONG StackPushDscU( PCOMMON_STACK_U Stack, ULONG Element );
ULONG StackPopU( PCOMMON_STACK_U Stack, ULONG *Element );
ULONG StackTopU( PCOMMON_STACK_U Stack, ULONG *Element );
ULONG StackPopBottomU( PCOMMON_STACK_U Stack, ULONG *Element );
ULONG StackBottomU( PCOMMON_STACK_U Stack, ULONG *Element );
ULONG StackRemoveU( PCOMMON_STACK_U Stack, ULONG Element );
ULONG StackReverseRemoveU( PCOMMON_STACK_U Stack, ULONG Element );
ULONG StackRemoveAllU( PCOMMON_STACK_U Stack, ULONG Element );
ULONG StackRemoveIndexU( PCOMMON_STACK_U Stack, ULONG Index );

/* Object */
ULONG StackInitT( PCOMMON_STACK_T Stack, ULONG Max, ULONG Size, STACK_INIT_FUNCTION, STACK_UNINIT_FUNCTION, STACK_COMPARE_FUNCTION SortCompare, STACK_COMPARE_FUNCTION FindCompare, PVOID Context );
ULONG StackUninitT( PCOMMON_STACK_T Stack );
ULONG StackReinitT( PCOMMON_STACK_T Stack );
ULONG StackSetMaxT( PCOMMON_STACK_T Stack, ULONG Max );
ULONG StackSetTopT( PCOMMON_STACK_T Stack, ULONG Top );
ULONG StackSetBottomT( PCOMMON_STACK_T Stack, ULONG Bottom );
void StackSetSortCompareT( PCOMMON_STACK_T Stack, STACK_COMPARE_FUNCTION );
void StackSetFindCompareT( PCOMMON_STACK_T Stack, STACK_COMPARE_FUNCTION );
ULONG StackFindT( PCOMMON_STACK_T Stack, PVOID Element );
ULONG StackFindReverseT( PCOMMON_STACK_T Stack, PVOID Element );
ULONG StackFindAscT( PCOMMON_STACK_T Stack, PVOID Element );
ULONG StackFindDscT( PCOMMON_STACK_T Stack, PVOID Element );
ULONG StackFindLargeAscT( PCOMMON_STACK_T Stack, PVOID Element );
ULONG StackFindLargeEqualAscT( PCOMMON_STACK_T Stack, PVOID Element );
ULONG StackFindLargeDscT( PCOMMON_STACK_T Stack, PVOID Element );
ULONG StackFindLargeEqualDscT( PCOMMON_STACK_T Stack, PVOID Element );
ULONG StackFindSmallAscT( PCOMMON_STACK_T Stack, PVOID Element );
ULONG StackFindSmallEqualAscT( PCOMMON_STACK_T Stack, PVOID Element );
ULONG StackFindSmallDscT( PCOMMON_STACK_T Stack, PVOID Element );
ULONG StackFindSmallEqualDscT( PCOMMON_STACK_T Stack, PVOID Element );
ULONG StackPopAllT( PCOMMON_STACK_T Stack, PVOID **Element );
ULONG StackPushT( PCOMMON_STACK_T Stack, PVOID Element );
ULONG StackPushAscT( PCOMMON_STACK_T Stack, PVOID Element );
ULONG StackPushDscT( PCOMMON_STACK_T Stack, PVOID Element );
ULONG StackPushSizeT( PCOMMON_STACK_T Stack, PVOID Element, ULONG Size );
ULONG StackPushSizeAscT( PCOMMON_STACK_T Stack, PVOID Element, ULONG Size );
ULONG StackPushSizeDscT( PCOMMON_STACK_T Stack, PVOID Element, ULONG Size );
ULONG StackPopT( PCOMMON_STACK_T Stack, PVOID *Element );
ULONG StackTopT( PCOMMON_STACK_T Stack, PVOID *Element );
ULONG StackPopBottomT( PCOMMON_STACK_T Stack, PVOID *Element );
ULONG StackBottomT( PCOMMON_STACK_T Stack, PVOID *Element );
ULONG StackRemoveT( PCOMMON_STACK_T Stack, PVOID Element );
ULONG StackRemoveIndexT( PCOMMON_STACK_T Stack, ULONG Index );

/* String */
ULONG StackInitS( PCOMMON_STACK_S Stack, ULONG Max );
ULONG StackInitExS( PCOMMON_STACK_S Stack, ULONG Max, ULONG Prefix );
ULONG StackUninitS( PCOMMON_STACK_S Stack );
ULONG StackReinitS( PCOMMON_STACK_S Stack );
ULONG StackSetMaxS( PCOMMON_STACK_S Stack, ULONG Max );
ULONG StackSetTopS( PCOMMON_STACK_S Stack, ULONG Top );
ULONG StackFindS( PCOMMON_STACK_S Stack, TCHAR Element );
ULONG StackFindReveseS( PCOMMON_STACK_S Stack, TCHAR Element );
ULONG StackPopAllS( PCOMMON_STACK_S Stack, const TCHAR **Element );
ULONG StackPushS( PCOMMON_STACK_S Stack, const TCHAR *Element, ULONG Size );
ULONG StackPushNS( PCOMMON_STACK_S Stack, TCHAR Element, ULONG Size );
ULONG StackPopS( PCOMMON_STACK_S Stack, TCHAR *Element );
ULONG StackPopNS( PCOMMON_STACK_S Stack, TCHAR *Element, ULONG Size );
ULONG StackTopS( PCOMMON_STACK_S Stack, TCHAR *Element );
ULONG StackPopAllExS( PCOMMON_STACK_S Stack, const TCHAR **Element );
ULONG StackSetPrefixS( PCOMMON_STACK_S Stack, ULONG Prefix );
ULONG StackPushPrefixS( PCOMMON_STACK_S Stack, const TCHAR *Element, ULONG Size );
ULONG StackPopPrefixS( PCOMMON_STACK_S Stack, TCHAR *Element );
ULONG StackPopPrefixNS( PCOMMON_STACK_S Stack, TCHAR *Element, ULONG Size );
ULONG StackTopPrefixS( PCOMMON_STACK_S Stack, TCHAR *Element );
ULONG StackPopBottomS( PCOMMON_STACK_S Stack, TCHAR *Element );
ULONG StackPopBottomNS( PCOMMON_STACK_S Stack, TCHAR *Element, ULONG Size );
ULONG StackBottomS( PCOMMON_STACK_S Stack, TCHAR *Element );
ULONG StackRemoveS( PCOMMON_STACK_S Stack, TCHAR Element );
ULONG StackReverseRemoveS( PCOMMON_STACK_S Stack, TCHAR Element );
ULONG StackRemoveAllS( PCOMMON_STACK_S Stack, TCHAR Element );
ULONG StackRemoveIndexS( PCOMMON_STACK_S Stack, ULONG Index );

/* Get */
__inline ULONG StackCount( PCOMMON_STACK Stack )
{
    return Stack->Top;
}

__inline ULONG StackMax( PCOMMON_STACK Stack )
{
    return Stack->Max;
}

__inline PVOID *StackBase( PCOMMON_STACK Stack )
{
    return Stack->Elements;
}

__inline PVOID StackAt( PCOMMON_STACK Stack, ULONG Index )
{
    return Stack->Elements[Index];
}

__inline ULONG StackCountU( PCOMMON_STACK_U Stack )
{
    return Stack->Top;
}

__inline ULONG StackMaxU( PCOMMON_STACK_U Stack )
{
    return Stack->Max;
}

__inline ULONG *StackBaseU( PCOMMON_STACK_U Stack )
{
    return Stack->Elements;
}

__inline ULONG StackAtU( PCOMMON_STACK_U Stack, ULONG Index )
{
    return Stack->Elements[Index];
}

__inline ULONG StackCountT( PCOMMON_STACK_T Stack )
{
    return Stack->Top;
}

__inline ULONG StackMaxT( PCOMMON_STACK_T Stack )
{
    return Stack->Max;
}

__inline PVOID *StackBaseT( PCOMMON_STACK_T Stack )
{
    return Stack->Elements;
}

__inline PVOID StackAtT( PCOMMON_STACK_T Stack, ULONG Index )
{
    return Stack->Elements[Index];
}

__inline ULONG StackCountS( PCOMMON_STACK_S Stack )
{
    return Stack->Top;
}

__inline ULONG StackMaxS( PCOMMON_STACK_S Stack )
{
    return Stack->Max;
}

__inline TCHAR *StackBaseS( PCOMMON_STACK_S Stack )
{
    return Stack->Elements;
}

__inline TCHAR StackAtS( PCOMMON_STACK_S Stack, ULONG Index )
{
    return Stack->Elements[Index];
}

__inline ULONG StackPrefixS( PCOMMON_STACK_S Stack )
{
    return Stack->PrefixTop;
}

__inline ULONG StackPrefixMaxS( PCOMMON_STACK_S Stack )
{
    return Stack->PrefixMax;
}

__inline TCHAR *StackAllocateBaseS( PCOMMON_STACK_S Stack )
{
    return Stack->AllocateBase;
}

#ifdef __cplusplus
}
#endif
/*
///////////////////////////////////////////////////////////////////////////////
// E N D  O F  F I L E
///////////////////////////////////////////////////////////////////////////////
*/
#endif /* __STACK_H__ */