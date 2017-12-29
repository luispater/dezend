/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   Hash.h
//  Version     :   1.0
//  Creator     :   RM
//  Create Date :   2006-01-01
//  Comment     :
//
///////////////////////////////////////////////////////////////////////////////
*/

#ifndef __HASH_H__
#define __HASH_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/
#define HASH_KEY_IS_STRING 1
#define HASH_KEY_IS_LONG 2
#define HASH_KEY_NON_EXISTANT 3

#define HASH_UPDATE 1
#define HASH_ADD 2
#define HASH_NEXT_INSERT 4

#define HASH_DEL_KEY 0
#define HASH_DEL_INDEX 1

/* Flags */
#define HASH_FLAGS_PERSISTENT 1
#define HASH_FLAGS_PROTECTION 2

#define HASH_FLAGS_MASK 0xFF

/* Apply */
#define HASH_APPLY_KEEP 0
#define HASH_APPLY_REMOVE 1
#define HASH_APPLY_STOP 2

/* Function macro */
#define HashUpdate( Table, Key, KeyLength, Data, DataSize, Dest ) \
    HashAddOrUpdate( Table, Key, KeyLength, Data, DataSize, Dest, HASH_UPDATE )

#define HashAdd( Table, Key, KeyLength, Data, DataSize, Dest ) \
    HashAddOrUpdate( Table, Key, KeyLength, Data, DataSize, Dest, HASH_ADD )

#define HashQuickUpdate( Table, Key, KeyLength, h, Data, DataSize, Dest ) \
    HashQuickAddOrUpdate( Table, Key, KeyLength, h, Data, DataSize, Dest, HASH_UPDATE )

#define HashQuickAdd( Table, Key, KeyLength, h, Data, DataSize, Dest ) \
    HashQuickAddOrUpdate( Table, Key, KeyLength, h, Data, DataSize, Dest, HASH_ADD )

#define HashIndexUpdate( Table, h, Data, DataSize, Dest ) \
    HashIndexUpdateOrNextInsert( Table, h, Data, DataSize, Dest, HASH_UPDATE )

#define HashNextIndexInsert( Table, Data, DataSize, Dest ) \
    HashIndexUpdateOrNextInsert( Table, 0, Data, DataSize, Dest, HASH_NEXT_INSERT )

#define HashDelete( Table, Key, KeyLength ) \
    HashDeleteKeyOrIndex( Table, Key, KeyLength, 0, HASH_DEL_KEY )

#define HashIndexDelete( Table, h ) \
    HashDeleteKeyOrIndex( Table, NULL, 0, h, HASH_DEL_INDEX )

#define HashRemoveForward( Table ) \
    HashRemoveForwardEx( Table, NULL )
#define HashMoveBackward( Table ) \
    HashMoveBackwardEx( Table, NULL )
#define HashGetCurrentKey( Table, Key, Index, Flags ) \
    HashGetCurrentKeyEx( Table, Key, NULL, Index, Flags, NULL )
#define HashGetCurrentKeyType( Table ) \
    HashGetCurrentKeyTypeEx( Table, NULL )
#define HashGetCurrentData( Table, Data ) \
    HashGetCurrentDataEx( Table, Data, NULL )
#define HashInternalPointerReset( Table ) \
    HashInternalPointerResetEx( Table, NULL )
#define HashInternalPointerEnd( Table ) \
    HashInternalPointerEndEx( Table, NULL )

/*
///////////////////////////////////////////////////////////////////////////////
// S T R U C T U R E S
///////////////////////////////////////////////////////////////////////////////
*/
typedef ULONG ( *HASH_FUNCTION )( const TCHAR *Key, ULONG KeyLength );
typedef LONG ( *HASH_COMPARE_FUNCTION )( const void*, const void* );
typedef void ( *HASH_SORT_FUNCTION )( void*, ULONG, register ULONG, HASH_COMPARE_FUNCTION );
typedef void ( *HASH_DESTROY_FUNCTION )( void* );
typedef void ( *HASH_COPY_FUNCTION )( void *Element );

typedef struct _HASH_BUCKET {
    ULONG HashValue;
    ULONG KeyLength;
    void *Data;
    void *DataPtr;
    struct _HASH_BUCKET *ListNext;
    struct _HASH_BUCKET *ListLast;
    struct _HASH_BUCKET *Next;
    struct _HASH_BUCKET *Last;
    TCHAR Key[1]; /* Must be last element */
} HASH_BUCKET, *PHASH_BUCKET;

typedef struct _HASH_TABLE {
    ULONG TableSize;
    ULONG TableMask;
    ULONG NumOfElements;
    ULONG NextFreeElement;
    HASH_BUCKET *InternalPointer;
    HASH_BUCKET *ListHead;
    HASH_BUCKET *ListTail;
    HASH_BUCKET **Buckets;
    HASH_FUNCTION Hash;
    HASH_DESTROY_FUNCTION Destroy;
    UCHAR Flags;
    UCHAR ApplyCount;
    USHORT Reserved;
} HASH_TABLE, *PHASH_TABLE;

typedef struct _HASH_KEY {
    const TCHAR *Key;
    ULONG KeyLength;
    ULONG HashValue;
} HASH_KEY, *PHASH_KEY;

typedef struct _HASH_POINTER {
    HASH_BUCKET *Pos;
    ULONG HashValue;
} HASH_POINTER, *PHASH_POINTER;

typedef ULONG ( *APPLY_FUNCTION )( void *Dest );
typedef ULONG ( *APPLY_ARG_FUNCTION )( void *Dest, void *Context );
typedef ULONG ( *APPLY_ARGS_FUNCTION )( void *Dest, ULONG Count, va_list Args, HASH_KEY *HashKey );

typedef ULONG ( *MERGE_CALLBACK_FUNCTION )( void *Origin, void *New );
typedef ULONG ( *MERGE_CHECKER_FUNCTION ) ( HASH_TABLE*, void *SourceData, PHASH_KEY, void *Context );

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
ULONG DefaultHashFunction( const TCHAR *Key, ULONG KeyLength );
ULONG DefaultHashFunctionInline( const TCHAR *Key, ULONG KeyLength );

ULONG HashInit( HASH_TABLE*, ULONG Size, HASH_FUNCTION, HASH_DESTROY_FUNCTION, ULONG Flags );
ULONG HashInitEx( HASH_TABLE*, ULONG Size, HASH_FUNCTION, HASH_DESTROY_FUNCTION, ULONG Flags );
void HashDestroy( HASH_TABLE* );
void HashGracefulDestroy( HASH_TABLE* );
void HashGracefulReverseDestroy( HASH_TABLE* );
void HashClear( HASH_TABLE* );

ULONG HashAddOrUpdate( HASH_TABLE*, const TCHAR *Key, ULONG KeyLength, void *Data, ULONG DataSize, void **Dest, ULONG Flags );
ULONG HashQuickAddOrUpdate( HASH_TABLE*, const TCHAR *Key, ULONG KeyLength, ULONG HashValue, void *Data, ULONG DataSize, void **Dest, ULONG Flags );
ULONG HashIndexUpdateOrNextInsert( HASH_TABLE*, ULONG HashValue, void *Data, ULONG DataSize, void **Dest, ULONG Flags );
ULONG HashAddEmptyElement( HASH_TABLE*, const TCHAR *Key, ULONG KeyLength );

void HashSetApplyProtection( PHASH_TABLE Table, ULONG Set );
void HashApply( HASH_TABLE*, APPLY_FUNCTION );
void HashApplyWithArgument( HASH_TABLE*, APPLY_ARG_FUNCTION, void* );
void HashApplyWithArgumentEx( HASH_TABLE*, APPLY_ARGS_FUNCTION, ULONG, ... );
void HashGracefulReverseApply( HASH_TABLE*, APPLY_FUNCTION );

ULONG HashDeleteKeyOrIndex( HASH_TABLE*, const TCHAR *Key, ULONG KeyLength, ULONG HashValue, ULONG Flags );

ULONG HashFind( const HASH_TABLE*, const TCHAR *Key, ULONG KeyLength, void **Data );
ULONG HashQuickFind( const HASH_TABLE*, const TCHAR *Key, ULONG KeyLength, ULONG HashValue, void **Data );
ULONG HashIndexFind( const HASH_TABLE*, ULONG HashValue, void **Data );

ULONG HashIsExist( const HASH_TABLE*, const TCHAR *Key, ULONG KeyLength );
ULONG HashQuickIsExist( const HASH_TABLE*, const TCHAR *Key, ULONG KeyLength, ULONG HashValue );
ULONG HashIndexIsExist( const HASH_TABLE*, ULONG HashValue );

ULONG HashGetPointer( HASH_TABLE*, HASH_POINTER* );
ULONG HashSetPointer( HASH_TABLE*, const HASH_POINTER* );

void HashInternalPointerResetEx( HASH_TABLE*, PHASH_BUCKET* );
void HashInternalPointerEndEx( HASH_TABLE*, PHASH_BUCKET* );

ULONG HashRemoveForwardEx( HASH_TABLE*, PHASH_BUCKET* );
ULONG HashMoveBackwardEx( HASH_TABLE*, PHASH_BUCKET* );
ULONG HashGetCurrentKeyEx( HASH_TABLE*, TCHAR **Key, ULONG *KeyLength, ULONG *Index, ULONG Flags, PHASH_BUCKET* );
ULONG HashGetCurrentKeyTypeEx( HASH_TABLE*, PHASH_BUCKET* );
ULONG HashGetCurrentDataEx( HASH_TABLE*, void **Data, PHASH_BUCKET* );
ULONG HashUpdateCurrentKeyEx( HASH_TABLE *Table, ULONG KeyType, TCHAR *Key, ULONG KeyLength, ULONG Index, PHASH_BUCKET *Pos );

void HashCopy( HASH_TABLE *Target, HASH_TABLE *Source, HASH_COPY_FUNCTION, void *Buffer, ULONG Size );
void HashMerge( HASH_TABLE *Target, HASH_TABLE *Source, HASH_COPY_FUNCTION, void *Buffer, ULONG Size, ULONG Overwrite );
void HashMergeEx( HASH_TABLE *Target, HASH_TABLE *Source, HASH_COPY_FUNCTION, ULONG Size, MERGE_CHECKER_FUNCTION, void *Context );

ULONG HashSort( HASH_TABLE*, HASH_SORT_FUNCTION, HASH_COMPARE_FUNCTION, ULONG ReNumber );
ULONG HashCompare( HASH_TABLE*, HASH_TABLE*, HASH_COMPARE_FUNCTION, ULONG Ordered );
ULONG HashMinMax( HASH_TABLE*, HASH_COMPARE_FUNCTION, ULONG Flags, void **Data );

ULONG HashGetValue( const TCHAR *Key, ULONG KeyLength );
ULONG HashGetCount( const HASH_TABLE* );
ULONG HashGetNextFreeElement( const HASH_TABLE* );

ULONG HashRefresh( HASH_TABLE* );

#ifdef __cplusplus
}
#endif
/*
///////////////////////////////////////////////////////////////////////////////
// E N D  O F  F I L E
///////////////////////////////////////////////////////////////////////////////
*/
#endif /* __HASH_H__ */
