/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   Encode.h
//  Version     :   1.0
//  Creator     :   RM
//  Create Date :   2006-01-01
//  Comment     :
//
///////////////////////////////////////////////////////////////////////////////
*/

#ifndef __ENCODE_H__
#define __ENCODE_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/
typedef enum _DES_CRYPT_TYPE {
    DES_ENCRYPT,
    DES_DECRYPT
} DES_CRYPT_TYPE;

/* Type of struct */
#define TYPE_ENCODE_INTERNAL 0x1000
#define TYPE_ENCODE_GLOBAL 0x2000
#define TYPE_ENCODE_LOCAL 0x4000

/* Default settings */
#define DEFAULT_ENCODE_KEY_PRINT _T( "amaworld" )
#define DEFAULT_ENCODE_KEY {\
    _T( 'a' ) ^ XOR_STR, _T( 'm' ) ^ XOR_STR, _T( 'a' ) ^ XOR_STR, _T( 'w' ) ^ XOR_STR,\
    _T( 'o' ) ^ XOR_STR, _T( 'r' ) ^ XOR_STR, _T( 'l' ) ^ XOR_STR, _T( 'd' ) ^ XOR_STR,\
    _T( '\0' ) ^ XOR_STR,\
}
#define DEFAULT_ENCODE_KEY_LENGTH ( SIZE_OF_ARRAY( DEFAULT_ENCODE_KEY_PRINT ) - 1 )
#define MAX_ENCODE_KEY_LENGTH 16

/* Flags */
#define ES_FLAGS_ENCODE_STEP1 0x1
#define ES_FLAGS_ENCODE_STEP2 0x2
#define ES_FLAGS_ENCODE_STEP3 0x3
#define ES_FLAGS_ENCODE_STEP4 0x4

#define ES_FLAGS_ENCODE_STEP_MASK 0xFF

#define ES_FLAGS_REMOVE_PROTECTION 0x08000000

#define ES_FLAGS_ENCODE_1 0x10000000
#define ES_FLAGS_ENCODE_2 0x20000000
#define ES_FLAGS_ENCODE_3 0x40000000
#define ES_FLAGS_ENCODE_4 0x80000000

#define ES_FLAGS_ENCODE 0xF0000000

#define ES_FLAGS_CRC_FILE 0x1000
#define ES_FLAGS_CRC_MODULE 0x2000
#define ES_FLAGS_MD5_FILE 0x4000
#define ES_FLAGS_MD5_MODULE 0x8000

/*
///////////////////////////////////////////////////////////////////////////////
// S T R U C T U R E S
///////////////////////////////////////////////////////////////////////////////
*/
typedef struct _MD5_VALUE {
    unsigned char Value[16];
} MD5_VALUE, *PMD5_VALUE;

typedef struct _ENCODE_RANGE {
    PVOID Start;
    PVOID End;
    ULONG Flags;
} ENCODE_RANGE, *PENCODE_RANGE;

typedef struct _ENCODE_STUB {
    USHORT Type;
    USHORT Size;
    ULONG Flags;
    ULONG Protection;
    UCHAR Key[MAX_ENCODE_KEY_LENGTH];
    ULONG KeyLength;
    UCHAR InternalKey[MAX_ENCODE_KEY_LENGTH];
    ULONG InternalKeyLength;
    MD5_VALUE MD5;
    ULONG Count;
    PENCODE_RANGE Range;
} ENCODE_STUB, *PENCODE_STUB;

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
ULONG DesCode( void *Out, const void *In, ULONG Length, const void *Key, ULONG KeyLength, ULONG Type );
void EncodeKey( UCHAR *Key, ULONG KeyLength );
void DecodeKey( UCHAR *Key, ULONG KeyLength );
void ObfuscateKey( UCHAR *Key, ULONG KeyLength );
void EncodeEx( UCHAR *Buffer, ULONG Length, UCHAR *Key, ULONG KeyLength );
void DecodeEx( UCHAR *Buffer, ULONG Length, UCHAR *Key, ULONG KeyLength );

ULONG DecodeStubKey( PENCODE_STUB Stub, const TCHAR *ModuleName );

void RemoveCodeProtection( PVOID ModuleBase );
void RecoverCodeProtection( PVOID ModuleBase );

void EncodeInternalStub( PENCODE_STUB Stub, PVOID ImageBase, PVOID FileImage );
void DecodeInternalStub( PENCODE_STUB Stub );
void EncodeStub( PENCODE_STUB Stub, PVOID ImageBase, PVOID FileImage );
void DecodeStub( PENCODE_STUB Stub );

void GetCRC( PMD5_VALUE MD5, UCHAR *Buffer, ULONG BufferLength );
void GetMD5( PMD5_VALUE MD5, UCHAR *Buffer, ULONG BufferLength );
ULONG GetFileCRC( PMD5_VALUE CRCPtr, const TCHAR *FileName, ULONG SkipOffset, ULONG SkipSize );
ULONG GetModuleCRC( PMD5_VALUE MD5, LPVOID ModuleBase, ULONG SkipOffset, ULONG SkipSize );
ULONG GetFileMD5( PMD5_VALUE MD5, const TCHAR *FileName, ULONG SkipOffset, ULONG SkipSize );
ULONG GetModuleMD5( PMD5_VALUE MD5, LPVOID ModuleBase, ULONG SkipOffset, ULONG SkipSize );

ULONG CheckIfTrace( );

void DestroyCode( PUCHAR AddressStart, PUCHAR AddressEnd );
void AlterCode( PUCHAR AddressStart, PUCHAR AddressEnd );

#ifdef __cplusplus
}
#endif
/*
///////////////////////////////////////////////////////////////////////////////
// E N D  O F  F I L E
///////////////////////////////////////////////////////////////////////////////
*/
#endif /* __ENCODE_H__ */
