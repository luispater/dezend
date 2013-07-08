/*
///////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   ParseSetting.h
//  Version     :   1.0
//  Creator     :   RM
//  Create Date :   2006-01-01
//  Comment     :
//
///////////////////////////////////////////////////////////////////////////////
*/

#ifndef __PARSESETTING_H__
#define __PARSESETTING_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*
///////////////////////////////////////////////////////////////////////////////
// D E F I N E S
///////////////////////////////////////////////////////////////////////////////
*/
#ifndef FASTCALL
#define FASTCALL __fastcall
#endif

/* Initiate global setting flags */
#define IGS_FLAGS_SET_FLAGS 0x1
#define IGS_FLAGS_SET_NUMBER 0x2
#define IGS_FLAGS_SET_NUMBER_N 0x4
#define IGS_FLAGS_SET_CHAR 0x8
#define IGS_FLAGS_SET_STRING 0x10
#define IGS_FLAGS_COMPARE_SET 0x20
#define IGS_FLAGS_CALLBACK 0x40

/*
///////////////////////////////////////////////////////////////////////////////
// S T R U C T U R E S
///////////////////////////////////////////////////////////////////////////////
*/
/* Initiate global setting */
typedef struct _INI_GLOBAL_SETTING {
    TCHAR *Environment;
    TCHAR *Command;
    ULONG CommandLength;
    PVOID SetValuePtr;
    PVOID DefaultValuePtr;
    ULONG Data;
    ULONG Flags;
} INI_GLOBAL_SETTING, *PINI_GLOBAL_SETTING;

/* Call back, return FALSE to continue */
typedef ULONG ( FASTCALL *IGS_CALLBACK ) ( LPCTSTR, PINI_GLOBAL_SETTING );

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
void TranslateEscapeCharacter( LPTSTR String, ULONG Length );
void ParseSetting( PINI_GLOBAL_SETTING IniSettingArray, ULONG Count, const TCHAR *ConstTrue );
void ParseCommandLineSetting( PINI_GLOBAL_SETTING IniSettingArray, ULONG Count, PCOMMON_STACK CommandList, PCOMMON_STACK UnkownList, IGS_CALLBACK Callback );

#ifdef __cplusplus
}
#endif
/*
///////////////////////////////////////////////////////////////////////////////
// E N D  O F  F I L E
///////////////////////////////////////////////////////////////////////////////
*/
#endif /* __PARSESETTING_H__ */