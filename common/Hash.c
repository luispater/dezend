/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   Hash.c
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

#include "AddLog.h"
#include "Hash.h"

#pragma warning( disable : 4706 )

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

#define HANDLE_BLOCK_INTERRUPTIONS( )
#define HANDLE_UNBLOCK_INTERRUPTIONS( )

#define HANDLE_NUMERIC( Key, Length, Func ) { \
    register const TCHAR *Tmp = Key; \
    if ( *Tmp == _T( '-' ) ) { \
        Tmp++; \
    } \
    if ( ( *Tmp >= _T( '0' ) && *Tmp <= _T( '9' ) ) ) do { /* Possibly numeric index */ \
        const TCHAR *End = Key + Length - 1; \
        ULONG Index; \
        if ( *Tmp++ == _T( '0' ) && Length > 2 ) { /* Don't accept numbers with leading zeros */ \
            break; \
        } \
        while ( Tmp < End ) { \
            if ( !( *Tmp >= _T( '0' ) && *Tmp <= _T( '9' ) ) ) { \
                break; \
            } \
            Tmp++; \
        } \
        if ( Tmp == End && *Tmp == _T( '\0' ) ) { /* Numeric index */ \
            if ( *Key == _T( '-' ) ) { \
                Index = _tcstol( Key, NULL, 10 ); \
                if ( Index != LONG_MIN ) { \
                    return Func; \
                } \
            } else { \
                Index = _tcstol( Key, NULL, 10 ); \
                if ( Index != LONG_MAX ) { \
                    return Func; \
                } \
            } \
        } \
    } while ( 0 ); \
}

#define CONNECT_TO_BUCKET_LIST( Element, ListHead ) \
    ( Element )->Next = ( ListHead ); \
    ( Element )->Last = NULL; \
    if ( ( Element )->Next ) { \
        ( Element )->Next->Last = ( Element ); \
    }

#define CONNECT_TO_GLOBAL_LIST( Element, Table ) \
    ( Element )->ListLast = ( Table )->ListTail; \
    ( Table )->ListTail = ( Element ); \
    ( Element )->ListNext = NULL; \
    if ( ( Element )->ListLast != NULL ) { \
        ( Element )->ListLast->ListNext = ( Element ); \
    } \
    if ( !( Table )->ListHead ) { \
        ( Table )->ListHead = ( Element ); \
    } \
    if ( ( Table )->InternalPointer == NULL ) { \
        ( Table )->InternalPointer = ( Element ); \
    }

#define HASH_PROTECT_RECURSION( Table ) \
    if ( ( Table )->Flags & HASH_FLAGS_PROTECTION ) { \
        if ( ( Table )->ApplyCount++ >= 3 ) { \
            ADD_LOGA( "Nesting level too deep - recursive dependency?" ); \
        } \
    }

#define HASH_UNPROTECT_RECURSION( Table ) \
    if ( ( Table )->Flags & HASH_FLAGS_PROTECTION ) { \
        ( Table )->ApplyCount--; \
    }

#define HASH_IF_FULL_DO_RESIZE( Table ) \
    if ( ( Table )->NumOfElements > ( Table )->TableSize ) { \
        HashDoResize( Table ); \
    }

#define UPDATE_DATA( Table, Bucket, Data, DataSize ) \
    if ( DataSize == sizeof( void* ) ) { \
        if ( !( Bucket )->DataPtr ) { \
            HEAP_FREE( ( Bucket )->Data ); \
        } \
        memcpy( &( Bucket )->DataPtr, Data, sizeof( void* ) ); \
        ( Bucket )->Data = &( Bucket )->DataPtr; \
    } else { \
        if ( ( Bucket )->Data == &( Bucket )->DataPtr ) { \
            ( Bucket )->Data = ( void* )HEAP_ALLOC( DataSize ); \
            ( Bucket )->DataPtr = NULL; \
        } else { \
            ( Bucket )->Data = ( void* )HEAP_REALLOC( ( Bucket )->Data, DataSize ); \
        } \
        memcpy( ( Bucket )->Data, Data, DataSize ); \
    }

#define INIT_DATA( Table, Bucket, Data, DataSize ); \
    if ( DataSize == sizeof( void* ) ) { \
        memcpy( &( Bucket )->DataPtr, Data, sizeof( void* ) ); \
        ( Bucket )->Data = &( Bucket )->DataPtr; \
    } else { \
        ( Bucket )->Data = ( void* )HEAP_ALLOC( DataSize ); \
        if ( !( Bucket )->Data ) { \
            HEAP_FREE( Bucket ); \
            return FALSE; \
        } \
        memcpy( ( Bucket )->Data, Data, DataSize ); \
        ( Bucket )->DataPtr = NULL; \
    }

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
/*
 * DJBX33A (Daniel J. Bernstein, Times 33 with Addition)
 *
 * This is Daniel J. Bernstein's popular `times 33' hash function as
 * posted by him years ago on comp.lang.c. It basically uses a function
 * like ``hash(i) = hash(i-1) * 33 + str[i]''. This is one of the best
 * known hash functions for strings. Because it is both computed very
 * fast and distributes very well.
 *
 * The magic of number 33, i.e. why it works better than many other
 * constants, prime or not, has never been adequately explained by
 * anyone. So I try an explanation: if one experimentally tests all
 * multipliers between 1 and 256 (as RSE did now) one detects that even
 * numbers are not usable at all. The remaining 128 odd numbers
 * (except for the number 1) work more or less all equally well. They
 * all distribute in an acceptable way and this way fill a hash table
 * with an average percent of approx. 86%. 
 *
 * If one compares the Chi^2 values of the variants, the number 33 not
 * even has the best value. But the number 33 and a few other equally
 * good numbers like 17, 31, 63, 127 and 129 have nevertheless a great
 * advantage to the remaining numbers in the large set of possible
 * multipliers: their multiply operation can be replaced by a faster
 * operation based on just one shift plus either a single addition
 * or subtraction operation. And because a hash function has to both
 * distribute good _and_ has to be very fast to compute, those few
 * numbers should be preferred and seems to be the reason why Daniel J.
 * Bernstein also preferred it.
 */
__inline ULONG DefaultHashFunctionInline( const TCHAR *Key, ULONG KeyLength )
{
    register ULONG HashValue = 5381;

    for ( ; KeyLength >= 8; KeyLength -= 8 )
    {
        HashValue = ( ( HashValue << 5 ) + HashValue ) + *Key++;
        HashValue = ( ( HashValue << 5 ) + HashValue ) + *Key++;
        HashValue = ( ( HashValue << 5 ) + HashValue ) + *Key++;
        HashValue = ( ( HashValue << 5 ) + HashValue ) + *Key++;
        HashValue = ( ( HashValue << 5 ) + HashValue ) + *Key++;
        HashValue = ( ( HashValue << 5 ) + HashValue ) + *Key++;
        HashValue = ( ( HashValue << 5 ) + HashValue ) + *Key++;
        HashValue = ( ( HashValue << 5 ) + HashValue ) + *Key++;
    }
    switch ( KeyLength )
    {
        case 7: HashValue = ( ( HashValue << 5 ) + HashValue ) + *Key++;
        case 6: HashValue = ( ( HashValue << 5 ) + HashValue ) + *Key++;
        case 5: HashValue = ( ( HashValue << 5 ) + HashValue ) + *Key++;
        case 4: HashValue = ( ( HashValue << 5 ) + HashValue ) + *Key++;
        case 3: HashValue = ( ( HashValue << 5 ) + HashValue ) + *Key++;
        case 2: HashValue = ( ( HashValue << 5 ) + HashValue ) + *Key++;
        case 1: HashValue = ( ( HashValue << 5 ) + HashValue ) + *Key++; break;
        case 0: break;
    }

    return HashValue;
}

ULONG DefaultHashFunction( const TCHAR *Key, ULONG KeyLength )
{
    return DefaultHashFunctionInline( Key, KeyLength );
}

static HASH_BUCKET* HashApplyDeleter( HASH_TABLE *Table, HASH_BUCKET *Bucket )
{
    ULONG Index;
    HASH_BUCKET *RetCode;

    HANDLE_BLOCK_INTERRUPTIONS( );
    if ( Bucket->Last )
    {
        Bucket->Last->Next = Bucket->Next;
    }
    else
    {
        Index = Bucket->HashValue & Table->TableMask;
        Table->Buckets[Index] = Bucket->Next;
    }

    if ( Bucket->Next )
    {
        Bucket->Next->Last = Bucket->Last;
    }
    else
    {
        /* Nothing to do as this list doesn't have a tail */
    }

    if ( Bucket->ListLast != NULL )
        Bucket->ListLast->ListNext = Bucket->ListNext;
    else
        Table->ListHead = Bucket->ListNext;

    if ( Bucket->ListNext != NULL )
        Bucket->ListNext->ListLast = Bucket->ListLast;
    else
        Table->ListTail = Bucket->ListLast;

    if ( Table->InternalPointer == Bucket )
        Table->InternalPointer = Bucket->ListNext;

    Table->NumOfElements--;
    HANDLE_UNBLOCK_INTERRUPTIONS( );

    if ( Table->Destroy )
        Table->Destroy( Bucket->Data );

    if ( Bucket->Data != &Bucket->DataPtr )
        HEAP_FREE( Bucket->Data );

    RetCode = Bucket->ListNext;
    HEAP_FREE( Bucket );

    return RetCode;
}

static ULONG HashDoResize( HASH_TABLE *Table )
{
    HASH_BUCKET **Buckets;

    if ( ( Table->TableSize << 1 ) > 0 )
    {
        Buckets = ( HASH_BUCKET** )HEAP_REALLOC( Table->Buckets, ( Table->TableSize << 1 ) * sizeof( HASH_BUCKET* ) );
        if ( Buckets == NULL )
        {
            Buckets = ( HASH_BUCKET** )HEAP_ALLOC( ( Table->TableSize << 1 ) * sizeof( HASH_BUCKET* ) );
            if ( Buckets == NULL )
                return FALSE;
        }
        HANDLE_BLOCK_INTERRUPTIONS( );
        Table->Buckets = Buckets;
        Table->TableSize = ( Table->TableSize << 1 );
        Table->TableMask = Table->TableSize - 1;
        HashRefresh( Table );
        HANDLE_UNBLOCK_INTERRUPTIONS( );
        return TRUE;
    }

    return TRUE;
}

static ULONG HashReplaceCheckerWrapper( HASH_TABLE *Target, void *Data, HASH_BUCKET *Bucket, void *Context, MERGE_CHECKER_FUNCTION MergeCheckerFunction )
{
    HASH_KEY HashKey;

    HashKey.Key = Bucket->Key;
    HashKey.KeyLength = Bucket->KeyLength;
    HashKey.HashValue = Bucket->HashValue;

    return MergeCheckerFunction( Target, Data, &HashKey, Context );
}

ULONG HashInitEx( PHASH_TABLE Table, ULONG Size, HASH_FUNCTION HashFunction, HASH_DESTROY_FUNCTION DestroyFunction, ULONG Flags )
{
    ULONG Iter;
    HASH_BUCKET **Buckets;

    Iter = 3;
    if ( Size >= 0x80000000 )
    {
        /* Prevent overflow */
        Table->TableSize = 0x80000000;
    }
    else
    {
        while ( ( 1U << Iter ) < Size )
            Iter++;
        Table->TableSize = 1 << Iter;
    }

    if ( HashFunction == NULL )
        HashFunction = DefaultHashFunction;

    Table->TableMask = Table->TableSize - 1;
    Table->Hash = HashFunction;
    Table->Destroy = DestroyFunction;
    Table->Buckets = NULL;
    Table->ListHead = NULL;
    Table->ListTail = NULL;
    Table->NumOfElements = 0;
    Table->NextFreeElement = 0;
    Table->InternalPointer = NULL;
    Table->Flags = ( UCHAR )Flags;
    Table->ApplyCount = 0;
    Table->Reserved = 0;

    Buckets = ( HASH_BUCKET** )HEAP_ALLOC( Table->TableSize * sizeof( HASH_BUCKET* ) );
    if ( Buckets == NULL )
        return FALSE;

    memset( Buckets, 0, Table->TableSize * sizeof( HASH_BUCKET* ) );
    Table->Buckets = Buckets;

    return TRUE;
}

ULONG HashInit( PHASH_TABLE Table, ULONG Size, HASH_FUNCTION HashFunction, HASH_DESTROY_FUNCTION DestroyFunction, ULONG Flags )
{
    return HashInitEx( Table, Size, HashFunction, DestroyFunction, Flags | HASH_FLAGS_PROTECTION );
}

void HashDestroy( PHASH_TABLE Table )
{
    HASH_BUCKET *Cur, *Prev;

    Cur = Table->ListHead;
    while ( Cur != NULL )
    {
        Prev = Cur;
        Cur = Cur->ListNext;
        if ( Table->Destroy )
            Table->Destroy( Prev->Data );
        if ( Prev->Data != &Prev->DataPtr )
            HEAP_FREE( Prev->Data );
        HEAP_FREE( Prev );
    }
    HEAP_FREE( Table->Buckets );
}

void HashGracefulDestroy( HASH_TABLE *Table )
{
    HASH_BUCKET *Bucket;

    Bucket = Table->ListHead;
    while ( Bucket != NULL )
        Bucket = HashApplyDeleter( Table, Bucket );
    HEAP_FREE( Table->Buckets );
}

void HashGracefulReverseDestroy( HASH_TABLE *Table )
{
    HASH_BUCKET *Bucket;

    Bucket = Table->ListTail;
    while ( Bucket != NULL )
    {
        HashApplyDeleter( Table, Bucket );
        Bucket = Table->ListTail;
    }
    HEAP_FREE( Table->Buckets );
}

void HashClear( PHASH_TABLE Table )
{
    HASH_BUCKET *Cur, *Prev;

    Cur = Table->ListHead;
    while ( Cur != NULL )
    {
        Prev = Cur;
        Cur = Cur->ListNext;
        if ( Table->Destroy )
            Table->Destroy( Prev->Data );
        if ( Prev->Data != &Prev->DataPtr )
            HEAP_FREE( Prev->Data );
        HEAP_FREE( Prev );
    }
    memset( Table->Buckets, 0, Table->TableSize * sizeof( HASH_BUCKET* ) );
    Table->ListHead = NULL;
    Table->ListTail = NULL;
    Table->NumOfElements = 0;
    Table->NextFreeElement = 0;
    Table->InternalPointer = NULL;
}

ULONG HashAddOrUpdate( PHASH_TABLE Table, const TCHAR *Key, ULONG KeyLength, void *Data, ULONG DataSize, void **Dest, ULONG Flags )
{
    ULONG HashValue;
    ULONG Index;
    HASH_BUCKET *Bucket;

    if ( KeyLength <= 0 )
        return FALSE;

    HashValue = Table->Hash( Key, KeyLength );
    Index = HashValue & Table->TableMask;
    Bucket = Table->Buckets[Index];
    while ( Bucket != NULL )
    {
        if ( ( Bucket->HashValue == HashValue ) && ( Bucket->KeyLength == KeyLength ) )
        {
            if ( !memcmp( Bucket->Key, Key, KeyLength ) )
            {
                if ( Flags & HASH_ADD )
                    return FALSE;

                HANDLE_BLOCK_INTERRUPTIONS( );
                if ( Table->Destroy )
                    Table->Destroy( Bucket->Data );
                UPDATE_DATA( Table, Bucket, Data, DataSize );
                if ( Dest )
                    *Dest = Bucket->Data;
                HANDLE_UNBLOCK_INTERRUPTIONS( );
                return TRUE;
            }
        }
        Bucket = Bucket->Next;
    }

    Bucket = ( HASH_BUCKET* )HEAP_ALLOC( sizeof( HASH_BUCKET ) + ( KeyLength - 1 ) * sizeof( TCHAR ) );
    if ( Bucket == NULL )
        return FALSE;

    memcpy( Bucket->Key, Key, KeyLength );
    Bucket->KeyLength = KeyLength;
    INIT_DATA( Table, Bucket, Data, DataSize );
    Bucket->HashValue = HashValue;
    CONNECT_TO_BUCKET_LIST( Bucket, Table->Buckets[Index] );
    if ( Dest )
        *Dest = Bucket->Data;

    HANDLE_BLOCK_INTERRUPTIONS( );
    CONNECT_TO_GLOBAL_LIST( Bucket, Table );
    Table->Buckets[Index] = Bucket;
    HANDLE_UNBLOCK_INTERRUPTIONS( );

    Table->NumOfElements++;
    HASH_IF_FULL_DO_RESIZE( Table );

    return TRUE;
}

ULONG HashQuickAddOrUpdate( HASH_TABLE *Table, const TCHAR *Key, ULONG KeyLength, ULONG HashValue, void *Data, ULONG DataSize, void **Dest, ULONG Flags )
{
    ULONG Index;
    HASH_BUCKET *Bucket;

    if ( KeyLength == 0 )
        return HashIndexUpdate( Table, HashValue, Data, DataSize, Dest );

    Index = HashValue & Table->TableMask;
    Bucket = Table->Buckets[Index];
    while ( Bucket != NULL )
    {
        if ( ( Bucket->HashValue == HashValue ) && ( Bucket->KeyLength == KeyLength ) )
        {
            if ( !memcmp( Bucket->Key, Key, KeyLength ) )
            {
                if ( Flags & HASH_ADD )
                    return FALSE;

                HANDLE_BLOCK_INTERRUPTIONS( );
                if ( Table->Destroy )
                    Table->Destroy( Bucket->Data );
                UPDATE_DATA( Table, Bucket, Data, DataSize );
                if ( Dest )
                    *Dest = Bucket->Data;
                HANDLE_UNBLOCK_INTERRUPTIONS( );
                return TRUE;
            }
        }
        Bucket = Bucket->Next;
    }

    Bucket = ( HASH_BUCKET* )HEAP_ALLOC( sizeof( HASH_BUCKET ) + ( KeyLength - 1 ) * sizeof( TCHAR ) );
    if ( Bucket == NULL )
        return FALSE;

    memcpy( Bucket->Key, Key, KeyLength );
    Bucket->KeyLength = KeyLength;
    INIT_DATA( Table, Bucket, Data, DataSize );
    Bucket->HashValue = HashValue;
    CONNECT_TO_BUCKET_LIST( Bucket, Table->Buckets[Index] );
    if ( Dest )
        *Dest = Bucket->Data;

    HANDLE_BLOCK_INTERRUPTIONS( );
    Table->Buckets[Index] = Bucket;
    CONNECT_TO_GLOBAL_LIST( Bucket, Table );
    HANDLE_UNBLOCK_INTERRUPTIONS( );

    Table->NumOfElements++;
    HASH_IF_FULL_DO_RESIZE( Table );

    return TRUE;
}

ULONG HashIndexUpdateOrNextInsert( HASH_TABLE *Table, ULONG HashValue, void *Data, ULONG DataSize, void **Dest, ULONG Flags )
{
    ULONG Index;
    HASH_BUCKET *Bucket;

    if ( Flags & HASH_NEXT_INSERT )
        HashValue = Table->NextFreeElement;

    Index = HashValue & Table->TableMask;
    Bucket = Table->Buckets[Index];
    while ( Bucket != NULL )
    {
        if ( ( Bucket->KeyLength == 0 ) && ( Bucket->HashValue == HashValue ) )
        {
            if ( Flags & HASH_NEXT_INSERT || Flags & HASH_ADD )
                return FALSE;

            HANDLE_BLOCK_INTERRUPTIONS( );
            if ( Table->Destroy )
                Table->Destroy( Bucket->Data );
            UPDATE_DATA( Table, Bucket, Data, DataSize );
            if ( ( LONG )HashValue >= ( LONG )Table->NextFreeElement )
                Table->NextFreeElement = HashValue + 1;
            if ( Dest )
                *Dest = Bucket->Data;
            HANDLE_UNBLOCK_INTERRUPTIONS( );
            return TRUE;
        }
        Bucket = Bucket->Next;
    }

    Bucket = ( HASH_BUCKET* )HEAP_ALLOC( sizeof( HASH_BUCKET ) - 1 * sizeof( TCHAR ) );
    if ( Bucket == NULL )
        return FALSE;

    Bucket->KeyLength = 0; /* Numeric are marked by making the KeyLength == 0 */
    INIT_DATA( Table, Bucket, Data, DataSize );
    Bucket->HashValue = HashValue;
    CONNECT_TO_BUCKET_LIST( Bucket, Table->Buckets[Index] );
    if ( Dest )
        *Dest = Bucket->Data;

    HANDLE_BLOCK_INTERRUPTIONS( );
    Table->Buckets[Index] = Bucket;
    CONNECT_TO_GLOBAL_LIST( Bucket, Table );
    HANDLE_UNBLOCK_INTERRUPTIONS( );

    if ( ( LONG )HashValue >= ( LONG )Table->NextFreeElement )
        Table->NextFreeElement = HashValue + 1;

    Table->NumOfElements++;
    HASH_IF_FULL_DO_RESIZE( Table );

    return TRUE;
}

ULONG HashAddEmptyElement( HASH_TABLE *Table, const TCHAR *Key, ULONG KeyLength )
{
    void *Dummy = ( void* )1;
    return HashAdd( Table, Key, KeyLength, &Dummy, sizeof( void* ), NULL );
}

void HashSetApplyProtection( PHASH_TABLE Table, ULONG Set )
{
    if ( Set )
        Table->Flags |= HASH_FLAGS_PROTECTION;
    else
        Table->Flags &= ~HASH_FLAGS_PROTECTION;
}

void HashApply( HASH_TABLE *Table, APPLY_FUNCTION ApplyFunction )
{
    ULONG RetCode;
    HASH_BUCKET *Bucket;

    HASH_PROTECT_RECURSION( Table );
    Bucket = Table->ListHead;
    while ( Bucket != NULL )
    {
        RetCode = ApplyFunction( Bucket->Data );
        if ( RetCode & HASH_APPLY_REMOVE )
            Bucket = HashApplyDeleter( Table, Bucket );
        else
            Bucket = Bucket->ListNext;

        if ( RetCode & HASH_APPLY_STOP )
            break;
    }
    HASH_UNPROTECT_RECURSION( Table );
}

void HashApplyWithArgument( HASH_TABLE *Table, APPLY_ARG_FUNCTION ApplyFunction, void *Context )
{
    ULONG RetCode;
    HASH_BUCKET *Bucket;

    HASH_PROTECT_RECURSION( Table );
    Bucket = Table->ListHead;
    while ( Bucket != NULL )
    {
        RetCode = ApplyFunction( Bucket->Data, Context );
        if ( RetCode & HASH_APPLY_REMOVE )
            Bucket = HashApplyDeleter( Table, Bucket );
        else
            Bucket = Bucket->ListNext;

        if ( RetCode & HASH_APPLY_STOP )
            break;
    }
    HASH_UNPROTECT_RECURSION( Table );
}

void HashApplyWithArgumentEx( HASH_TABLE *Table, APPLY_ARGS_FUNCTION ApplyFunction, ULONG Count, ... )
{
    ULONG RetCode;
    HASH_BUCKET *Bucket;
    va_list Args;
    HASH_KEY HashKey;

    Bucket = Table->ListHead;
    while ( Bucket != NULL )
    {
        va_start( Args, Count );
        HashKey.Key = Bucket->Key;
        HashKey.KeyLength = Bucket->KeyLength;
        HashKey.HashValue = Bucket->HashValue;
        RetCode = ApplyFunction( Bucket->Data, Count, Args, &HashKey );

        if ( RetCode & HASH_APPLY_REMOVE )
            Bucket = HashApplyDeleter( Table, Bucket );
        else
            Bucket = Bucket->ListNext;

        if ( RetCode & HASH_APPLY_STOP )
            break;
        va_end( Args );
    }
    HASH_UNPROTECT_RECURSION( Table );
}

void HashGracefulReverseApply( HASH_TABLE *Table, APPLY_FUNCTION ApplyFunction )
{
    ULONG RetCode;
    HASH_BUCKET *Bucket;
    HASH_BUCKET *Prev;

    HASH_PROTECT_RECURSION( Table );
    Bucket = Table->ListTail;
    while ( Bucket != NULL )
    {
        RetCode = ApplyFunction( Bucket->Data );
        Prev = Bucket;
        Bucket = Bucket->ListLast;
        if ( RetCode & HASH_APPLY_REMOVE )
            HashApplyDeleter( Table, Prev );

        if ( RetCode & HASH_APPLY_STOP )
            break;
    }
    HASH_UNPROTECT_RECURSION( Table );
}

ULONG HashDeleteKeyOrIndex( HASH_TABLE *Table, const TCHAR *Key, ULONG KeyLength, ULONG HashValue, ULONG Flags )
{
    ULONG Index;
    HASH_BUCKET *Bucket;

    if ( Flags == HASH_DEL_KEY )
        HashValue = Table->Hash( Key, KeyLength );

    Index = HashValue & Table->TableMask;
    Bucket = Table->Buckets[Index];
    while ( Bucket != NULL )
    {
        if ( ( Bucket->HashValue == HashValue ) && ( Bucket->KeyLength == KeyLength ) && ( ( Bucket->KeyLength == 0 ) || !memcmp( Bucket->Key, Key, KeyLength ) ) )
        {
            HANDLE_BLOCK_INTERRUPTIONS( );
            if ( Bucket == Table->Buckets[Index] )
                Table->Buckets[Index] = Bucket->Next;
            else
                Bucket->Last->Next = Bucket->Next;

            if ( Bucket->Next )
                Bucket->Next->Last = Bucket->Last;

            if ( Bucket->ListLast != NULL )
                Bucket->ListLast->ListNext = Bucket->ListNext;
            else
                Table->ListHead = Bucket->ListNext;

            if ( Bucket->ListNext != NULL )
                Bucket->ListNext->ListLast = Bucket->ListLast;
            else
                Table->ListTail = Bucket->ListLast;

            if ( Table->InternalPointer == Bucket )
                Table->InternalPointer = Bucket->ListNext;

            if ( Table->Destroy )
                Table->Destroy( Bucket->Data );

            if ( Bucket->Data != &Bucket->DataPtr )
                HEAP_FREE( Bucket->Data );

            HEAP_FREE( Bucket );
            HANDLE_UNBLOCK_INTERRUPTIONS( );
            Table->NumOfElements--;
            return TRUE;
        }
        Bucket = Bucket->Next;
    }

    return FALSE;
}

ULONG HashFind( const HASH_TABLE *Table, const TCHAR *Key, ULONG KeyLength, void **Data )
{
    ULONG HashValue;
    ULONG Index;
    HASH_BUCKET *Bucket;

    HashValue = Table->Hash( Key, KeyLength );
    Index = HashValue & Table->TableMask;
    Bucket = Table->Buckets[Index];
    while ( Bucket != NULL )
    {
        if ( ( Bucket->HashValue == HashValue ) && ( Bucket->KeyLength == KeyLength ) )
        {
            if ( !memcmp( Bucket->Key, Key, KeyLength ) )
            {
                *Data = Bucket->Data;
                return TRUE;
            }
        }
        Bucket = Bucket->Next;
    }

    return FALSE;
}

ULONG HashQuickFind( const HASH_TABLE *Table, const TCHAR *Key, ULONG KeyLength, ULONG HashValue, void **Data )
{
    ULONG Index;
    HASH_BUCKET *Bucket;

    if ( KeyLength == 0 )
        return HashIndexFind( Table, HashValue, Data );

    Index = HashValue & Table->TableMask;
    Bucket = Table->Buckets[Index];
    while ( Bucket != NULL )
    {
        if ( ( Bucket->HashValue == HashValue ) && ( Bucket->KeyLength == KeyLength ) )
        {
            if ( !memcmp( Bucket->Key, Key, KeyLength ) )
            {
                *Data = Bucket->Data;
                return TRUE;
            }
        }
        Bucket = Bucket->Next;
    }

    return FALSE;
}

ULONG HashIndexFind( const HASH_TABLE *Table, ULONG HashValue, void **Data )
{
    ULONG Index;
    HASH_BUCKET *Bucket;

    Index = HashValue & Table->TableMask;
    Bucket = Table->Buckets[Index];
    while ( Bucket != NULL )
    {
        if ( ( Bucket->HashValue == HashValue ) && ( Bucket->KeyLength == 0 ) )
        {
            *Data = Bucket->Data;
            return TRUE;
        }
        Bucket = Bucket->Next;
    }

    return FALSE;
}

ULONG HashIsExist( const HASH_TABLE *Table, const TCHAR *Key, ULONG KeyLength )
{
    ULONG HashValue;
    ULONG Index;
    HASH_BUCKET *Bucket;

    HashValue = Table->Hash( Key, KeyLength );
    Index = HashValue & Table->TableMask;
    Bucket = Table->Buckets[Index];
    while ( Bucket != NULL )
    {
        if ( ( Bucket->HashValue == HashValue ) && ( Bucket->KeyLength == KeyLength ) )
        {
            if ( !memcmp( Bucket->Key, Key, KeyLength ) )
                return TRUE;
        }
        Bucket = Bucket->Next;
    }

    return FALSE;
}

ULONG HashQuickIsExist( const HASH_TABLE *Table, const TCHAR *Key, ULONG KeyLength, ULONG HashValue )
{
    ULONG Index;
    HASH_BUCKET *Bucket;

    if ( KeyLength == 0 )
        return HashIndexIsExist( Table, HashValue );

    Index = HashValue & Table->TableMask;
    Bucket = Table->Buckets[Index];
    while ( Bucket != NULL )
    {
        if ( ( Bucket->HashValue == HashValue ) && ( Bucket->KeyLength == KeyLength ) )
        {
            if ( !memcmp( Bucket->Key, Key, KeyLength ) )
                return TRUE;
        }
        Bucket = Bucket->Next;
    }

    return FALSE;
}

ULONG HashIndexIsExist( const HASH_TABLE *Table, ULONG HashValue )
{
    ULONG Index;
    HASH_BUCKET *Bucket;

    Index = HashValue & Table->TableMask;
    Bucket = Table->Buckets[Index];
    while ( Bucket != NULL )
    {
        if ( ( Bucket->HashValue == HashValue ) && ( Bucket->KeyLength == 0 ) )
            return TRUE;
        Bucket = Bucket->Next;
    }

    return 0;
}

ULONG HashGetPointer( HASH_TABLE *Table, HASH_POINTER *HashPointer )
{
    HashPointer->Pos = Table->InternalPointer;
    if ( Table->InternalPointer )
    {
        HashPointer->HashValue = Table->InternalPointer->HashValue;
        return TRUE;
    }
    else
    {
        HashPointer->HashValue = 0;
        return FALSE;
    }
}

ULONG HashSetPointer( HASH_TABLE *Table, const HASH_POINTER *HashPointer )
{
    HASH_BUCKET *Bucket;

    if ( Table->InternalPointer != HashPointer->Pos )
    {
        Bucket = Table->Buckets[HashPointer->HashValue & Table->TableMask];
        while ( Bucket != NULL )
        {
            if ( Bucket == HashPointer->Pos )
            {
                Table->InternalPointer = Bucket;
                return TRUE;
            }
            Bucket = Bucket->Next;
        }
        return FALSE;
    }

    return TRUE;
}

void HashInternalPointerResetEx( HASH_TABLE *Table, PHASH_BUCKET *Pos )
{
    if ( Pos )
        *Pos = Table->ListHead;
    else
        Table->InternalPointer = Table->ListHead;
}

void HashInternalPointerEndEx( HASH_TABLE *Table, PHASH_BUCKET *Pos )
{
    if ( Pos )
        *Pos = Table->ListTail;
    else
        Table->InternalPointer = Table->ListTail;
}

ULONG HashRemoveForwardEx( HASH_TABLE *Table, PHASH_BUCKET *Pos )
{
    PHASH_BUCKET *Cur;

    Cur = Pos ? Pos : &Table->InternalPointer;
    if ( *Cur )
    {
        *Cur = ( *Cur )->ListNext;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

ULONG HashMoveBackwardEx( HASH_TABLE *Table, PHASH_BUCKET *Pos )
{
    PHASH_BUCKET *Cur;

    Cur = Pos ? Pos : &Table->InternalPointer;
    if ( *Cur )
    {
        *Cur = ( *Cur )->ListLast;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

ULONG HashGetCurrentKeyEx( HASH_TABLE *Table, TCHAR **Key, ULONG *KeyLength, ULONG *Index, ULONG Duplicate, PHASH_BUCKET *Pos )
{
    HASH_BUCKET *Bucket;

    Bucket = Pos ? ( *Pos ) : Table->InternalPointer;
    if ( Bucket )
    {
        if ( Bucket->KeyLength )
        {
            if ( Duplicate )
            {
                *Key = ( TCHAR* )HEAP_ALLOC( Bucket->KeyLength * sizeof( TCHAR ) );
                if ( *Key )
                {
                    memcpy( *Key, Bucket->Key, ( Bucket->KeyLength - 1 ) * sizeof( TCHAR ) );
                    *( *Key ) = _T( '\0' );
                }
            }
            else
            {
                *Key = Bucket->Key;
            }
            if ( KeyLength )
                *KeyLength = Bucket->KeyLength;
            return HASH_KEY_IS_STRING;
        }
        else
        {
            *Index = Bucket->HashValue;
            return HASH_KEY_IS_LONG;
        }
    }

    return HASH_KEY_NON_EXISTANT;
}

ULONG HashGetCurrentKeyTypeEx( HASH_TABLE *Table, PHASH_BUCKET *Pos )
{
    HASH_BUCKET *Bucket;

    Bucket = Pos ? ( *Pos ) : Table->InternalPointer;
    if ( Bucket )
    {
        if ( Bucket->KeyLength )
            return HASH_KEY_IS_STRING;
        else
            return HASH_KEY_IS_LONG;
    }

    return HASH_KEY_NON_EXISTANT;
}

ULONG HashGetCurrentDataEx( HASH_TABLE *Table, void **Data, PHASH_BUCKET *Pos )
{
    HASH_BUCKET *Bucket;

    Bucket = Pos ? ( *Pos ) : Table->InternalPointer;
    if ( Bucket )
    {
        *Data = Bucket->Data;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

ULONG HashUpdateCurrentKeyEx( HASH_TABLE *Table, ULONG KeyType, TCHAR *Key, ULONG KeyLength, ULONG Index, PHASH_BUCKET *Pos )
{
    HASH_BUCKET *Bucket;
    HASH_BUCKET *AllocBucket;

    Bucket = Pos ? ( *Pos ) : Table->InternalPointer;
    if ( Bucket )
    {
        if ( KeyType == HASH_KEY_IS_LONG )
        {
            KeyLength = 0;
            if ( !Bucket->KeyLength && Bucket->HashValue == Index )
                return TRUE;
            HashIndexDelete( Table, Index );
        }
        else if ( KeyType == HASH_KEY_IS_STRING )
        {
            if ( Bucket->KeyLength == KeyLength && memcmp( Bucket->Key, Key, KeyLength * sizeof( TCHAR ) ) == 0 )
                return TRUE;
            HashDelete( Table, Key, KeyLength );
        }
        else
        {
            return FALSE;
        }

        HANDLE_BLOCK_INTERRUPTIONS( );
        if ( Bucket->Next )
            Bucket->Next->Last = Bucket->Last;

        if ( Bucket->Last )
            Bucket->Last->Next = Bucket->Next;
        else
            Table->Buckets[Bucket->HashValue & Table->TableMask] = Bucket->Next;

        if ( Bucket->KeyLength != KeyLength )
        {
            AllocBucket = ( HASH_BUCKET* )HEAP_ALLOC( sizeof( HASH_BUCKET ) + ( KeyLength - 1 ) * sizeof( TCHAR ) );
            if ( AllocBucket == NULL )
                return FALSE;

            AllocBucket->KeyLength = KeyLength;
            if ( Bucket->Data == &Bucket->DataPtr )
                AllocBucket->Data = &AllocBucket->DataPtr;
            else
                AllocBucket->Data = Bucket->Data;

            AllocBucket->DataPtr = Bucket->DataPtr;
            AllocBucket->ListNext = Bucket->ListNext;
            AllocBucket->ListLast = Bucket->ListLast;
            if ( AllocBucket->ListNext )
                Bucket->ListNext->ListLast = AllocBucket;
            else
                Table->ListTail = AllocBucket;

            if ( AllocBucket->ListLast )
                Bucket->ListLast->ListNext = AllocBucket;
            else
                Table->ListHead = AllocBucket;

            if ( Table->InternalPointer == Bucket )
                Table->InternalPointer = AllocBucket;

            if ( Pos )
                *Pos = AllocBucket;

            HEAP_FREE( Bucket );
            Bucket = AllocBucket;
        }

        if ( KeyType == HASH_KEY_IS_LONG )
        {
            Bucket->HashValue = Index;
        }
        else
        {
            memcpy( Bucket->Key, Key, KeyLength * sizeof( TCHAR ) );
            Bucket->HashValue = Table->Hash( Key, KeyLength );
        }

        CONNECT_TO_BUCKET_LIST( Bucket, Table->Buckets[Bucket->HashValue & Table->TableMask] );
        Table->Buckets[Bucket->HashValue & Table->TableMask] = Bucket;
        HANDLE_UNBLOCK_INTERRUPTIONS( );
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void HashCopy( HASH_TABLE *Target, HASH_TABLE *Source, HASH_COPY_FUNCTION CopyFunction, void *Buffer, ULONG Size )
{
    HASH_BUCKET *Bucket;
    void *Dest;

    UNREFERENCED_PARAMETER( Buffer );
    Bucket = Source->ListHead;
    while ( Bucket )
    {
        if ( Bucket->KeyLength )
            HashQuickUpdate( Target, Bucket->Key, Bucket->KeyLength, Bucket->HashValue, Bucket->Data, Size, &Dest );
        else
            HashIndexUpdate( Target, Bucket->HashValue, Bucket->Data, Size, &Dest );

        if ( CopyFunction )
            CopyFunction( Dest );
        Bucket = Bucket->ListNext;
    }
    Target->InternalPointer = Target->ListHead;
}

void HashMerge( HASH_TABLE *Target, HASH_TABLE *Source, HASH_COPY_FUNCTION CopyFunction, void *Buffer, ULONG Size, ULONG Overwrite )
{
    ULONG Flags;
    HASH_BUCKET *Bucket;
    void *Dest;

    UNREFERENCED_PARAMETER( Buffer );
    Flags = Overwrite ? HASH_UPDATE : HASH_ADD;
    Bucket = Source->ListHead;
    while ( Bucket )
    {
        if ( Bucket->KeyLength > 0 )
        {
            if ( HashQuickAddOrUpdate( Target, Bucket->Key, Bucket->KeyLength, Bucket->HashValue, Bucket->Data, Size, &Dest, Flags ) == TRUE && CopyFunction )
                CopyFunction( Dest );
        }
        else
        {
            if ( ( Flags == HASH_UPDATE || !HashIndexIsExist( Target, Bucket->HashValue ) ) && HashIndexUpdate( Target, Bucket->HashValue, Bucket->Data, Size, &Dest ) == TRUE && CopyFunction )
                CopyFunction( Dest );
        }
        Bucket = Bucket->ListNext;
    }
    Target->InternalPointer = Target->ListHead;
}

void HashMergeEx( HASH_TABLE *Target, HASH_TABLE *Source, HASH_COPY_FUNCTION CopyFunction, ULONG Size, MERGE_CHECKER_FUNCTION MergeCheckerFunction, void *Context )
{
    HASH_BUCKET *Bucket;
    void *Dest;

    Bucket = Source->ListHead;
    while ( Bucket )
    {
        if ( HashReplaceCheckerWrapper( Target, Bucket->Data, Bucket, Context, MergeCheckerFunction ) )
        {
            if ( HashQuickUpdate( Target, Bucket->Key, Bucket->KeyLength, Bucket->HashValue, Bucket->Data, Size, &Dest ) == TRUE && CopyFunction )
                CopyFunction( Dest );
        }
        Bucket = Bucket->ListNext;
    }
    Target->InternalPointer = Target->ListHead;
}

ULONG HashSort( HASH_TABLE *Table, HASH_SORT_FUNCTION SortFunction, HASH_COMPARE_FUNCTION CompareFunction, ULONG ReNumber )
{
    ULONG Iter;
    ULONG Iter1;
    HASH_BUCKET **Buckets;
    HASH_BUCKET *Bucket;

    if ( !( Table->NumOfElements > 1 ) && !( ReNumber && Table->NumOfElements > 0 ) )
        return TRUE;

    Buckets = ( HASH_BUCKET** )HEAP_ALLOC( Table->NumOfElements * sizeof( HASH_BUCKET * ) );
    if ( Buckets == NULL )
        return FALSE;

    Iter = 0;
    Bucket = Table->ListHead;
    while ( Bucket )
    {
        Buckets[Iter] = Bucket;
        Bucket = Bucket->ListNext;
        Iter++;
    }

    SortFunction( ( void* )Buckets, Iter, sizeof( HASH_BUCKET* ), CompareFunction );

    HANDLE_BLOCK_INTERRUPTIONS( );
    Table->ListHead = Buckets[0];
    Table->ListTail = NULL;
    Table->InternalPointer = Table->ListHead;

    Buckets[0]->ListLast = NULL;
    if ( Iter > 1 )
    {
        Buckets[0]->ListNext = Buckets[1];
        for ( Iter1 = 1; Iter1 < Iter - 1; Iter1++ )
        {
            Buckets[Iter1]->ListLast = Buckets[Iter1 - 1];
            Buckets[Iter1]->ListNext = Buckets[Iter1 + 1];
        }
        Buckets[Iter1]->ListLast = Buckets[Iter1 - 1];
        Buckets[Iter1]->ListNext = NULL;
    }
    else
    {
        Buckets[0]->ListNext = NULL;
    }
    Table->ListTail = Buckets[Iter - 1];

    HEAP_FREE( Buckets );
    HANDLE_UNBLOCK_INTERRUPTIONS( );

    if ( ReNumber )
    {
        Bucket = Table->ListHead;
        Iter = 0;
        while ( Bucket != NULL )
        {
            Bucket->KeyLength = 0;
            Bucket->HashValue = Iter++;
            Bucket = Bucket->ListNext;
        }
        Table->NextFreeElement = Iter;
        HashRefresh( Table );
    }

    return TRUE;
}

ULONG HashCompare( HASH_TABLE *Table1, HASH_TABLE *Table2, HASH_COMPARE_FUNCTION CompareFunction, ULONG Ordered )
{
    ULONG RetCode;
    HASH_BUCKET *Bucket1;
    HASH_BUCKET *Bucket2;
    void *Data2;

    HASH_PROTECT_RECURSION( Table1 );
    HASH_PROTECT_RECURSION( Table2 );

    RetCode = Table1->NumOfElements - Table2->NumOfElements;
    if ( RetCode )
    {
        HASH_UNPROTECT_RECURSION( Table1 );
        HASH_UNPROTECT_RECURSION( Table2 );
        return RetCode;
    }

    Bucket1 = Table1->ListHead;
    Bucket2 = NULL;
    if ( Ordered )
        Bucket2 = Table2->ListHead;

    while ( Bucket1 )
    {
        if ( Ordered && !Bucket2 )
        {
            /* That's not supposed to happen */
            HASH_UNPROTECT_RECURSION( Table1 );
            HASH_UNPROTECT_RECURSION( Table2 );
            return 1;
        }
        if ( Ordered )
        {
            if ( Bucket1->KeyLength == 0 && Bucket2->KeyLength == 0 )
            {
                /* Numeric */
                RetCode = Bucket1->HashValue - Bucket2->HashValue;
                if ( RetCode )
                {
                    HASH_UNPROTECT_RECURSION( Table1 );
                    HASH_UNPROTECT_RECURSION( Table2 );
                    return RetCode;
                }
            }
            else
            {
                /* String */
                RetCode = Bucket1->KeyLength - Bucket2->KeyLength;
                if ( RetCode )
                {
                    HASH_UNPROTECT_RECURSION( Table1 );
                    HASH_UNPROTECT_RECURSION( Table2 );
                    return RetCode;
                }

                RetCode = memcmp( Bucket1->Key, Bucket2->Key, Bucket1->KeyLength );
                if ( RetCode )
                {
                    HASH_UNPROTECT_RECURSION( Table1 );
                    HASH_UNPROTECT_RECURSION( Table2 );
                    return RetCode;
                }
            }
            Data2 = Bucket2->Data;
        }
        else
        {
            if ( Bucket1->KeyLength == 0 )
            {
                /* Numeric index */
                if ( HashIndexFind( Table2, Bucket1->HashValue, &Data2 ) == FALSE )
                {
                    HASH_UNPROTECT_RECURSION( Table1 );
                    HASH_UNPROTECT_RECURSION( Table2 );
                    return 1;
                }
            }
            else
            {
                /* String index */
                if ( HashFind( Table2, Bucket1->Key, Bucket1->KeyLength, &Data2 ) == FALSE )
                {
                    HASH_UNPROTECT_RECURSION( Table1 );
                    HASH_UNPROTECT_RECURSION( Table2 );
                    return 1;
                }
            }
        }
        RetCode = CompareFunction( Bucket1->Data, Data2 );
        if ( RetCode )
        {
            HASH_UNPROTECT_RECURSION( Table1 );
            HASH_UNPROTECT_RECURSION( Table2 );
            return RetCode;
        }

        Bucket1 = Bucket1->ListNext;
        if ( Ordered )
            Bucket2 = Bucket2->ListNext;
    }

    HASH_UNPROTECT_RECURSION( Table1 );
    HASH_UNPROTECT_RECURSION( Table2 );

    return 0;
}

ULONG HashMinMax( HASH_TABLE *Table, HASH_COMPARE_FUNCTION CompareFunction, ULONG Flags, void **Data )
{
    HASH_BUCKET *RetCode;
    HASH_BUCKET *Bucket;

    if ( Table->NumOfElements == 0 )
    {
        *Data = NULL;
        return FALSE;
    }

    RetCode = Bucket = Table->ListHead;
    while ( ( Bucket = Bucket->ListNext ) )
    {
        if ( Flags )
        {
            if ( CompareFunction( &RetCode, &Bucket ) < 0 )
            {
                /* Max */
                RetCode = Bucket;
            }
        }
        else
        {
            if ( CompareFunction( &RetCode, &Bucket ) > 0 )
            {
                /* Min */
                RetCode = Bucket;
            }
        }
    }
    *Data = RetCode->Data;

    return TRUE;
}

ULONG HashGetValue( const TCHAR *Key, ULONG KeyLength )
{
    return DefaultHashFunctionInline( Key, KeyLength );
}

ULONG HashGetCount( const HASH_TABLE *Table )
{
    return Table->NumOfElements;
}

ULONG HashGetNextFreeElement( const HASH_TABLE *Table )
{
    return Table->NextFreeElement;
}

ULONG HashRefresh( HASH_TABLE *Table )
{
    ULONG Index;
    HASH_BUCKET *Bucket;

    memset( Table->Buckets, 0, Table->TableSize * sizeof( HASH_BUCKET * ) );
    Bucket = Table->ListHead;
    while ( Bucket != NULL )
    {
        Index = Bucket->HashValue & Table->TableMask;
        CONNECT_TO_BUCKET_LIST( Bucket, Table->Buckets[Index] );
        Table->Buckets[Index] = Bucket;
        Bucket = Bucket->ListNext;
    }

    return TRUE;
}

