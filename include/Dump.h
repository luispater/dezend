/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   Dump.h
//  Version     :   1.0
//  Creator     :   RM
//  Create Date :   2006-01-01
//  Comment     :
//
///////////////////////////////////////////////////////////////////////////////
*/

#ifndef __DUMP_H__
#define __DUMP_H__

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/
#define INVALID_BYTE 0xFF

/*
///////////////////////////////////////////////////////////////////////////////
// S T R U C T U R E S
///////////////////////////////////////////////////////////////////////////////
*/
#pragma pack( push, 1 )

typedef struct _IP_HEAD {
    unsigned char HeaderLength_Version;
    unsigned char TypeOfService; // Type of service
    unsigned short TotalLength; // total length of the packet
    unsigned short Identification; // unique identifier
    unsigned short FragmentationFlags; // flags
    unsigned char TTL; // Time To Live
    unsigned char Protocol; // Protocol ( TCP, UDP etc )
    unsigned short CheckSum; // Ip Header checksum
    unsigned int SourceIp; // Source address
    unsigned int DestinationIp; // Destination Address
} IP_HEAD, *PIP_HEAD;

typedef struct _FAKE_TCP_HEAD {
    unsigned int SourceIp; // Source address
    unsigned int DestinationIp; // Destination Address
    unsigned char Padding; // Time To Live
    unsigned char Protocol; // Protocol ( TCP, UDP etc )
    unsigned short HeadLength; // It is the size of TCP_HEAD
} FAKE_TCP_HEAD, *PFAKE_TCP_HEAD;

typedef struct _TCP_HEAD {
    unsigned short SourcePort;
    unsigned short DestinationPort;
    unsigned int Sequence;
    unsigned int Acknowlegment;
    unsigned char HeadLength;
    unsigned char Flags;
    unsigned short WindowSize;
    unsigned short CheckSum;
    unsigned short UrgencyOffset;
} TCP_HEAD, *PTCP_HEAD;

#pragma pack( pop )

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
#ifdef __cplusplus
extern "C"
{
#endif

/* HexToChar */
TCHAR HexToChar( BYTE );
char HexToCharA( BYTE );
WCHAR HexToCharW( BYTE );

/* CharToHex */
BYTE CharToHex( TCHAR );
BYTE CharToHexA( char );
BYTE CharToHexW( WCHAR );

/* StrToData */
ULONG StrToData( TCHAR *, UINT Mutiply );
ULONG StrToDataA( char *, UINT Mutiply );
ULONG StrToDataW( WCHAR *, UINT Mutiply );

/* StrToHex */
ULONG StrToHex( TCHAR * );
ULONG StrToHexA( char * );
ULONG StrToHexW( WCHAR * );

/* Help */
char * PASCAL _inet_ntoa( struct in_addr );
unsigned short _ntohs( unsigned short );
unsigned short _htons( unsigned short );

/* Dump */
ULONG DumpMem( const void * lpBuffer, ULONG Size );
ULONG DumpProcessMem( HANDLE hProcess, ULONG Address, ULONG Size );
ULONG DumpDebugEvent( DEBUG_EVENT * );
ULONG DumpThreadContext( CONTEXT * );
ULONG DumpIpHead( const void *, ULONG );

#ifdef __cplusplus
}
#endif
/*
///////////////////////////////////////////////////////////////////////////////
// E N D  O F  F I L E
///////////////////////////////////////////////////////////////////////////////
*/
#endif /* __DUMP_H__ */