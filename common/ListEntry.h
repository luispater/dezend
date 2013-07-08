/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   ListEntry.h
//  Version     :   1.0
//  Creator     :   RM
//  Create Date :   2006-01-01
//  Comment     :
//
///////////////////////////////////////////////////////////////////////////////
*/

#ifndef __LISTENTRY_H__
#define __LISTENTRY_H__

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/
#define IsListEmpty( ListHead ) ( ( ListHead )->Flink == ( ListHead ) )

#define PopEntryList( ListHead ) ( ListHead )->Next; \
    { \
        PSINGLE_LIST_ENTRY FirstEntry; \
        FirstEntry = (ListHead)->Next; \
        if ( FirstEntry != NULL ) { \
            ( ListHead )->Next = FirstEntry->Next; \
        } \
    }

#define PushEntryList( ListHead, Entry ) \
    ( Entry )->Next = ( ListHead )->Next; \
    ( ListHead )->Next = ( Entry )

/*
///////////////////////////////////////////////////////////////////////////////
// S T R U C T U R E S
///////////////////////////////////////////////////////////////////////////////
*/
typedef struct _SOCKET_INFO {
    unsigned long IpAddress; // Network byte order
    unsigned short Port; // Network byte order
    unsigned short Reserved;
    LIST_ENTRY ListEntry;
} SOCKET_INFO, *PSOCKET_INFO;

/*
///////////////////////////////////////////////////////////////////////////////
// F U N C T I O N S
///////////////////////////////////////////////////////////////////////////////
*/

#ifdef __cplusplus
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
//
// InitializeListHead
//
///////////////////////////////////////////////////////////////////////////////
VOID __inline InitializeListHead(
    IN PLIST_ENTRY ListHead
    )
{
    ListHead->Flink = ListHead->Blink = ListHead;
}

VOID __inline RemoveEntryList(
    IN PLIST_ENTRY Entry
    )
{
    PLIST_ENTRY Blink;
    PLIST_ENTRY Flink;

    Flink = Entry->Flink;
    Blink = Entry->Blink;
    Blink->Flink = Flink;
    Flink->Blink = Blink;
}

PLIST_ENTRY __inline RemoveHeadList(
    IN PLIST_ENTRY ListHead
    )
{
    PLIST_ENTRY Flink;
    PLIST_ENTRY Entry;

    if ( ListHead == ListHead->Flink )
        return NULL;

    Entry = ListHead->Flink;
    Flink = Entry->Flink;
    ListHead->Flink = Flink;
    Flink->Blink = ListHead;

    return Entry;
}

PLIST_ENTRY __inline RemoveTailList(
    IN PLIST_ENTRY ListHead
    )
{
    PLIST_ENTRY Blink;
    PLIST_ENTRY Entry;

    if ( ListHead == ListHead->Blink )
        return NULL;

    Entry = ListHead->Blink;
    Blink = Entry->Blink;
    ListHead->Blink = Blink;
    Blink->Flink = ListHead;

    return Entry;
}

VOID __inline InsertHeadList(
    IN PLIST_ENTRY ListHead,
    IN PLIST_ENTRY Entry
    )
{
    PLIST_ENTRY Flink;

    Flink = ListHead->Flink;
    Entry->Flink = Flink;
    Entry->Blink = ListHead;
    Flink->Blink = Entry;
    ListHead->Flink = Entry;
}

VOID __inline InsertTailList(
    IN PLIST_ENTRY ListHead,
    IN PLIST_ENTRY Entry
    )
{
    PLIST_ENTRY Blink;

    Blink = ListHead->Blink;
    Entry->Flink = ListHead;
    Entry->Blink = Blink;
    Blink->Flink = Entry;
    ListHead->Blink = Entry;
}

PLIST_ENTRY __inline ExInterlockedRemoveHeadList(
    IN PLIST_ENTRY ListHead,
    IN PCRITICAL_SECTION Lock
    )
{
    PLIST_ENTRY Entry;

    EnterCriticalSection( Lock );
    Entry = RemoveHeadList( ListHead );
    LeaveCriticalSection( Lock );

    return Entry;
}

PLIST_ENTRY __inline ExInterlockedRemoveTailList(
    IN PLIST_ENTRY ListHead,
    IN PCRITICAL_SECTION Lock
    )
{
    PLIST_ENTRY Entry;

    EnterCriticalSection( Lock );
    Entry = RemoveTailList( ListHead );
    LeaveCriticalSection( Lock );

    return Entry;
}

VOID __inline ExInterlockedInsertHeadList(
    IN PLIST_ENTRY ListHead,
    IN PLIST_ENTRY Entry,
    IN PCRITICAL_SECTION Lock
    )
{
    EnterCriticalSection( Lock );
    InsertHeadList( ListHead, Entry );
    LeaveCriticalSection( Lock );
}

VOID __inline ExInterlockedInsertTailList(
    IN PLIST_ENTRY ListHead,
    IN PLIST_ENTRY Entry,
    IN PCRITICAL_SECTION Lock
    )
{
    EnterCriticalSection( Lock );
    InsertTailList( ListHead, Entry );
    LeaveCriticalSection( Lock );
}

#ifdef __cplusplus
}
#endif
/*
///////////////////////////////////////////////////////////////////////////////
// E N D  O F  F I L E
///////////////////////////////////////////////////////////////////////////////
*/
#endif /* __LISTENTRY_H__ */