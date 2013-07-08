# Microsoft Developer Studio Project File - Name="php5dllts" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=php5dllts - Win32 Debug_TS
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "php5dllts.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "php5dllts.mak" CFG="php5dllts - Win32 Debug_TS"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "php5dllts - Win32 Debug_TS" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "php5dllts - Win32 Release_TS" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "php5dllts - Win32 Release_TS_inline" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "php5dllts - Win32 Release_TSDbg" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "php5dllts - Win32 Release_TS_Final" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/DeZend/5.2.1/win32", TTNAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "php5dllts - Win32 Debug_TS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug_TS"
# PROP BASE Intermediate_Dir "Debug_TS"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Debug_TS"
# PROP Intermediate_Dir "Debug_TS"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PHP5DLLTS_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../include" /I "..\..\win32build\include" /I "..\..\libiconv\include" /I "..\..\libxml\include" /I ".." /I "..\main" /I "..\Zend" /I "..\TSRM" /I "..\regex" /I "..\ext\sqlite\libsqlite\src" /I "..\ext\date\lib" /I "..\ext\pdo_sqlite\sqlite\src" /D "_DEBUG" /D ZEND_DEBUG=1 /D "LIBXML_THREAD_ENABLED" /D "_WINDOWS" /D "_USRDLL" /D "PHP5DLLTS_EXPORTS" /D "PHP_EXPORTS" /D "LIBZEND_EXPORTS" /D "TSRM_EXPORTS" /D "SAPI_EXPORTS" /D "MSVC5" /D "ZTS" /D "ZEND_WIN32" /D "PHP_WIN32" /D "LIBXML_STATIC" /D "WIN32" /D "_MBCS" /YX /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40d /d "_DEBUG"
# ADD RSC /l 0x40d /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib ws2_32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ZendTS.lib TSRM.lib Urlmon.lib zlib.lib /nologo /version:4.0 /dll /debug /machine:I386 /nodefaultlib:"libcmt" /nodefaultlib:"msvcrt" /out:"..\Debug_TS\php5ts_debug.dll" /pdbtype:sept /libpath:"..\TSRM\Debug_TS" /libpath:"..\Zend\Debug_TS" /libpath:"..\..\bindlib_w32\Debug" /libpath:"Debug_TS" /libpath:"..\..\zlib\Debug" /libpath:"..\..\libxml\lib\Debug" /libpath:"..\ext\sqlite\Debug_TS" /libpath:"..\..\win32build\lib" /libpath:"..\..\libiconv\lib" /libpath:"..\..\libxml\lib"

!ELSEIF  "$(CFG)" == "php5dllts - Win32 Release_TS"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release_TS"
# PROP BASE Intermediate_Dir "Release_TS"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Release_TS"
# PROP Intermediate_Dir "Release_TS"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PHP5DLLTS_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /I "../../include" /I "..\..\win32build\include" /I "..\..\libiconv\include" /I "..\..\libxml\include" /I ".." /I "..\main" /I "..\Zend" /I "..\TSRM" /I "..\regex" /I "..\ext\sqlite\libsqlite\src" /I "..\ext\date\lib" /I "..\ext\pdo_sqlite\sqlite\src" /D "NDEBUG" /D ZEND_DEBUG=0 /D "_WINDOWS" /D "_USRDLL" /D "PHP5DLLTS_EXPORTS" /D "PHP_EXPORTS" /D "LIBZEND_EXPORTS" /D "TSRM_EXPORTS" /D "SAPI_EXPORTS" /D "MSVC5" /D "ZTS" /D "ZEND_WIN32" /D "PHP_WIN32" /D "LIBXML_STATIC" /D "WIN32" /D "_MBCS" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40d /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib ws2_32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ZendTS.lib TSRM.lib Urlmon.lib zlib.lib /nologo /version:4.0 /dll /debug /machine:I386 /nodefaultlib:"libcmt.lib" /out:"../../output/php5ts.dll" /libpath:"..\TSRM\Release_TS" /libpath:"..\Zend\Release_TS" /libpath:"Release_TS" /libpath:"..\ext\sqlite\Release_TS" /libpath:"..\..\bindlib_w32\Release" /libpath:"..\..\zlib\Release" /libpath:"..\..\libxml\lib\Release" /libpath:"..\..\win32build\lib" /libpath:"..\..\libiconv\lib" /libpath:"..\..\libxml\lib"

!ELSEIF  "$(CFG)" == "php5dllts - Win32 Release_TS_inline"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "php5dllts___Win32_Release_TS_inline"
# PROP BASE Intermediate_Dir "php5dllts___Win32_Release_TS_inline"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Release_TS_inline"
# PROP Intermediate_Dir "Release_TS_inline"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "." /I "regex" /I "..\bindlib_w32" /I "Zend" /I "tsrm" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "PHP5DLLTS_EXPORTS" /D "MSVC5" /D "PHP_EXPORTS" /D "LIBZEND_EXPORTS" /D "TSRM_EXPORTS" /D "SAPI_EXPORTS" /D "ZTS" /D "WIN32" /D "_MBCS" /D ZEND_DEBUG=0 /FR /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../include" /I "..\..\win32build\include" /I "..\..\libiconv\include" /I "..\..\libxml\include" /I ".." /I "..\main" /I "..\Zend" /I "..\TSRM" /I "..\regex" /I "..\ext\sqlite\libsqlite\src" /I "..\ext\date\lib" /I "..\ext\pdo_sqlite\sqlite\src" /D "NDEBUG" /D ZEND_DEBUG=0 /D "ZEND_WIN32_FORCE_INLINE" /D "LIBXML_THREAD_ENABLED" /D "_WINDOWS" /D "_USRDLL" /D "PHP5DLLTS_EXPORTS" /D "PHP_EXPORTS" /D "LIBZEND_EXPORTS" /D "TSRM_EXPORTS" /D "SAPI_EXPORTS" /D "MSVC5" /D "ZTS" /D "ZEND_WIN32" /D "PHP_WIN32" /D "LIBXML_STATIC" /D "WIN32" /D "_MBCS" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40d /d "NDEBUG"
# ADD RSC /l 0x40d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib wsock32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ZendTS.lib TSRM.lib resolv.lib /nologo /dll /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcmt.lib" /out:"Release_TS/php5ts.dll" /libpath:"TSRM\Release_TS" /libpath:"Zend\Release_TS" /libpath:"..\bindlib_w32\Release"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib ws2_32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ZendTS.lib TSRM.lib Urlmon.lib zlib.lib /nologo /version:4.0 /dll /machine:I386 /nodefaultlib:"libcmt" /out:"..\Release_TS_inline\php5ts.dll" /libpath:"..\TSRM\Release_TS_inline" /libpath:"..\Zend\Release_TS_inline" /libpath:"Release_TS_Inline" /libpath:"..\..\bindlib_w32\Release" /libpath:"..\..\zlib\Release" /libpath:"..\..\libxml\lib\Release" /libpath:"..\ext\sqlite\Release_TS" /libpath:"..\..\win32build\lib" /libpath:"..\..\libiconv\lib" /libpath:"..\..\libxml\lib"

!ELSEIF  "$(CFG)" == "php5dllts - Win32 Release_TSDbg"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "php5dllts___Win32_Release_TSDbg"
# PROP BASE Intermediate_Dir "php5dllts___Win32_Release_TSDbg"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Release_TSDbg"
# PROP Intermediate_Dir "Release_TSDbg"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I ".." /I "..\main" /I "..\regex" /I "..\..\bindlib_w32" /I "..\Zend" /I "..\TSRM" /D "NDEBUG" /D ZEND_DEBUG=0 /D "_WINDOWS" /D "_USRDLL" /D "PHP5DLLTS_EXPORTS" /D "PHP_EXPORTS" /D "LIBZEND_EXPORTS" /D "TSRM_EXPORTS" /D "SAPI_EXPORTS" /D "MSVC5" /D "ZTS" /D "ZEND_WIN32" /D "PHP_WIN32" /D "WIN32" /D "_MBCS" /FR /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /I "../../include" /I "..\..\win32build\include" /I "..\..\libiconv\include" /I "..\..\libxml\include" /I ".." /I "..\main" /I "..\Zend" /I "..\TSRM" /I "..\regex" /I "..\ext\sqlite\libsqlite\src" /I "..\ext\date\lib" /I "..\ext\pdo_sqlite\sqlite\src" /D "NDEBUG" /D ZEND_DEBUG=0 /D "LIBXML_THREAD_ENABLED" /D "_WINDOWS" /D "_USRDLL" /D "PHP5DLLTS_EXPORTS" /D "PHP_EXPORTS" /D "LIBZEND_EXPORTS" /D "TSRM_EXPORTS" /D "SAPI_EXPORTS" /D "MSVC5" /D "ZTS" /D "ZEND_WIN32" /D "PHP_WIN32" /D "LIBXML_STATIC" /D "WIN32" /D "_MBCS" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40d /d "NDEBUG"
# ADD RSC /l 0x40d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib wsock32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ZendTS.lib TSRM.lib resolv.lib /nologo /version:4.0 /dll /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcmt.lib" /out:"..\Release_TS\php5ts.dll" /libpath:"..\TSRM\Release_TS" /libpath:"..\Zend\Release_TS" /libpath:"..\..\bindlib_w32\Release" /libpath:"Release_TS"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib ws2_32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ZendTS.lib TSRM.lib Urlmon.lib zlib.lib /nologo /version:4.0 /dll /debug /machine:I386 /nodefaultlib:"libcmt" /out:"..\Release_TSDbg\php5ts.dll" /libpath:"..\TSRM\Release_TSDbg" /libpath:"..\Zend\Release_TSDbg" /libpath:"Release_TSDbg" /libpath:"..\ext\sqlite\Release_TSDbg" /libpath:"..\..\bindlib_w32\Release" /libpath:"..\..\zlib\Release" /libpath:"..\..\libxml\lib\Release" /libpath:"..\..\win32build\lib" /libpath:"..\..\libiconv\lib" /libpath:"..\..\libxml\lib"

!ELSEIF  "$(CFG)" == "php5dllts - Win32 Release_TS_Final"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "php5dllts___Win32_Release_TS_Final"
# PROP BASE Intermediate_Dir "php5dllts___Win32_Release_TS_Final"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "php5dllts___Win32_Release_TS_Final"
# PROP Intermediate_Dir "php5dllts___Win32_Release_TS_Final"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /Od /I ".." /I "..\main" /I "..\regex" /I "..\..\bindlib_w32" /I "..\..\zlib" /I "..\Zend" /I "..\TSRM" /I "..\..\libxml\include" /I "..\ext\sqlite\libsqlite\src" /I "..\ext\date\lib" /I "..\ext\pdo_sqlite\sqlite\src" /D "NDEBUG" /D ZEND_DEBUG=0 /D "_WINDOWS" /D "_USRDLL" /D "PHP5DLLTS_EXPORTS" /D "PHP_EXPORTS" /D "LIBZEND_EXPORTS" /D "TSRM_EXPORTS" /D "SAPI_EXPORTS" /D "MSVC5" /D "ZTS" /D "ZEND_WIN32" /D "PHP_WIN32" /D "LIBXML_STATIC" /D "WIN32" /D "_MBCS" /FR /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /I "../../include" /I "..\..\win32build\include" /I "..\..\libiconv\include" /I "..\..\libxml\include" /I ".." /I "..\main" /I "..\Zend" /I "..\TSRM" /I "..\regex" /I "..\ext\sqlite\libsqlite\src" /I "..\ext\date\lib" /I "..\ext\pdo_sqlite\sqlite\src" /D "NDEBUG" /D ZEND_DEBUG=0 /D "_WINDOWS" /D "_USRDLL" /D "PHP5DLLTS_EXPORTS" /D "PHP_EXPORTS" /D "LIBZEND_EXPORTS" /D "TSRM_EXPORTS" /D "SAPI_EXPORTS" /D "MSVC5" /D "ZTS" /D "ZEND_WIN32" /D "PHP_WIN32" /D "LIBXML_STATIC" /D "WIN32" /D "_MBCS" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40d /d "NDEBUG"
# ADD RSC /l 0x40d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib ws2_32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ZendTS.lib TSRM.lib resolv.lib zlib.lib libxml2_a.lib Urlmon.lib iconv_a.lib /nologo /version:4.0 /dll /machine:I386 /nodefaultlib:"libcmt" /out:"..\Release_TS\php5ts.dll" /libpath:"..\TSRM\Release_TS" /libpath:"..\Zend\Release_TS" /libpath:"Release_TS" /libpath:"..\ext\sqlite\Release_TS" /libpath:"..\..\bindlib_w32\Release" /libpath:"..\..\zlib\Release" /libpath:"..\..\libxml\lib\Release" /libpath:"..\..\libiconv\lib"
# ADD LINK32 kernel32.lib user32.lib gdi32.lib ws2_32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ZendTS.lib TSRM.lib Urlmon.lib zlib.lib /nologo /version:4.0 /dll /machine:I386 /nodefaultlib:"libcmt" /out:"../../output/php5ts.dll" /libpath:"..\TSRM\Release_TS" /libpath:"..\Zend\Release_TS" /libpath:"Release_TS" /libpath:"..\ext\sqlite\Release_TS" /libpath:"..\..\bindlib_w32\Release" /libpath:"..\..\zlib\Release" /libpath:"..\..\libxml\lib\Release" /libpath:"..\..\win32build\lib" /libpath:"..\..\libiconv\lib" /libpath:"..\..\libxml\lib"

!ENDIF 

# Begin Target

# Name "php5dllts - Win32 Debug_TS"
# Name "php5dllts - Win32 Release_TS"
# Name "php5dllts - Win32 Release_TS_inline"
# Name "php5dllts - Win32 Release_TSDbg"
# Name "php5dllts - Win32 Release_TS_Final"
# Begin Group "Core"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\main\config.w32.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\css.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\css.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\cyr_convert.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\cyr_convert.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\filters.c
# End Source File
# Begin Source File

SOURCE="..\main\fopen_wrappers.c"
# End Source File
# Begin Source File

SOURCE="..\main\fopen_wrappers.h"
# End Source File
# Begin Source File

SOURCE=.\globals.c
# End Source File
# Begin Source File

SOURCE=..\main\internal_functions_win32.c
# End Source File
# Begin Source File

SOURCE=..\main\logos.h
# End Source File
# Begin Source File

SOURCE=..\main\main.c
# End Source File
# Begin Source File

SOURCE=..\main\mergesort.c
# End Source File
# Begin Source File

SOURCE=..\main\network.c
# End Source File
# Begin Source File

SOURCE=..\main\output.c
# End Source File
# Begin Source File

SOURCE=..\main\php.h
# End Source File
# Begin Source File

SOURCE=..\main\php3_compat.h
# End Source File
# Begin Source File

SOURCE=..\main\php_compat.h
# End Source File
# Begin Source File

SOURCE=..\main\php_content_types.c
# End Source File
# Begin Source File

SOURCE=..\main\php_content_types.h
# End Source File
# Begin Source File

SOURCE=..\main\php_globals.h
# End Source File
# Begin Source File

SOURCE=..\main\php_ini.c
# End Source File
# Begin Source File

SOURCE=..\main\php_ini.h
# End Source File
# Begin Source File

SOURCE=..\main\php_logos.c
# End Source File
# Begin Source File

SOURCE=..\main\php_logos.h
# End Source File
# Begin Source File

SOURCE=..\main\php_main.h
# End Source File
# Begin Source File

SOURCE=..\main\php_open_temporary_file.c
# End Source File
# Begin Source File

SOURCE=..\main\php_open_temporary_file.h
# End Source File
# Begin Source File

SOURCE=..\main\php_output.h
# End Source File
# Begin Source File

SOURCE=..\main\php_regex.h
# End Source File
# Begin Source File

SOURCE=..\main\php_scandir.c
# End Source File
# Begin Source File

SOURCE=..\main\php_scandir.h
# End Source File
# Begin Source File

SOURCE=..\main\php_sprintf.c
# End Source File
# Begin Source File

SOURCE=..\main\php_streams.h
# End Source File
# Begin Source File

SOURCE=..\main\php_ticks.c
# End Source File
# Begin Source File

SOURCE=..\main\php_variables.c
# End Source File
# Begin Source File

SOURCE=..\main\php_variables.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\proc_open.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\quot_print.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\quot_print.h
# End Source File
# Begin Source File

SOURCE=..\main\reentrancy.c
# End Source File
# Begin Source File

SOURCE=..\main\rfc1867.c
# End Source File
# Begin Source File

SOURCE=..\main\rfc1867.h
# End Source File
# Begin Source File

SOURCE=..\main\safe_mode.c
# End Source File
# Begin Source File

SOURCE=..\main\safe_mode.h
# End Source File
# Begin Source File

SOURCE=..\main\SAPI.c
# End Source File
# Begin Source File

SOURCE=..\main\SAPI.h
# End Source File
# Begin Source File

SOURCE=..\main\snprintf.c
# End Source File
# Begin Source File

SOURCE=..\main\snprintf.h
# End Source File
# Begin Source File

SOURCE=..\main\spprintf.c
# End Source File
# Begin Source File

SOURCE=..\main\spprintf.h
# End Source File
# Begin Source File

SOURCE=..\main\strlcat.c
# End Source File
# Begin Source File

SOURCE=..\main\strlcpy.c
# End Source File
# Begin Source File

SOURCE=..\main\win95nt.h
# End Source File
# End Group
# Begin Group "Function Modules"

# PROP Default_Filter ""
# Begin Group "Regular Expressions"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\regex\regcomp.c
# End Source File
# Begin Source File

SOURCE=..\regex\regerror.c
# End Source File
# Begin Source File

SOURCE=..\regex\regexec.c
# End Source File
# Begin Source File

SOURCE=..\regex\regfree.c
# End Source File
# End Group
# Begin Group "Standard"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ext\standard\array.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\assert.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\base64.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\base64.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\basic_functions.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\basic_functions.h
# End Source File
# Begin Source File

SOURCE=..\ext\bcmath\bcmath.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\browscap.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\crc32.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\credits.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\crypt.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\datetime.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\datetime.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\dir.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\dl.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\dl.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\dns.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\dns.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\exec.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\exec.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\file.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\file.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\filestat.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\flock_compat.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\flock_compat.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\formatted_print.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\fsock.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\fsock.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\ftp_fopen_wrapper.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\head.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\head.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\html.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\html.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\http.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\http_fopen_wrapper.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\image.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\incomplete_class.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\info.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\info.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\iptc.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\lcg.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\levenshtein.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\link.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\mail.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\math.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\md5.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\md5.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\metaphone.c
# End Source File
# Begin Source File

SOURCE=..\ext\session\mod_files.c
# End Source File
# Begin Source File

SOURCE=..\ext\session\mod_user.c
# End Source File
# Begin Source File

SOURCE=..\ext\session\mod_user.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\pack.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\pageinfo.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\pageinfo.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\php_array.h
# End Source File
# Begin Source File

SOURCE=..\ext\bcmath\php_bcmath.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\php_crypt.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\php_dir.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\php_filestat.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\php_fopen_wrapper.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\php_fopen_wrappers.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\php_http.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\php_lcg.h
# End Source File
# Begin Source File

SOURCE=..\ext\ldap\php_ldap.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\php_mail.h
# End Source File
# Begin Source File

SOURCE=..\ext\odbc\php_odbc.c
# End Source File
# Begin Source File

SOURCE=..\ext\odbc\php_odbc.h
# End Source File
# Begin Source File

SOURCE=..\ext\odbc\php_odbc_includes.h
# End Source File
# Begin Source File

SOURCE=..\ext\pcre\php_pcre.c
# ADD CPP /D "STATIC"
# End Source File
# Begin Source File

SOURCE=..\ext\pcre\php_pcre.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\php_rand.h
# End Source File
# Begin Source File

SOURCE=..\ext\session\php_session.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\php_string.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\rand.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\reg.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\reg.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\scanf.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\scanf.h
# End Source File
# Begin Source File

SOURCE=..\ext\session\session.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\sha1.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\sha1.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\soundex.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\streamsfuncs.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\string.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\strnatcmp.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\syslog.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\type.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\uniqid.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\uniqid.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\url.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\url.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\url_scanner.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\url_scanner.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\url_scanner_ex.c
# ADD CPP /W2
# End Source File
# Begin Source File

SOURCE=..\ext\standard\url_scanner_ex.h
# End Source File
# Begin Source File

SOURCE=..\ext\standard\user_filters.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\uuencode.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\var.c
# End Source File
# Begin Source File

SOURCE=..\ext\standard\var_unserializer.c
# ADD CPP /W2
# End Source File
# Begin Source File

SOURCE=..\ext\standard\versioning.c
# End Source File
# End Group
# Begin Group "Date"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ext\date\lib\astro.c
# End Source File
# Begin Source File

SOURCE=..\ext\date\lib\astro.h
# End Source File
# Begin Source File

SOURCE=..\ext\date\lib\dow.c
# End Source File
# Begin Source File

SOURCE=..\ext\date\lib\fallbackmap.h
# End Source File
# Begin Source File

SOURCE=..\ext\date\lib\parse_date.c
# End Source File
# Begin Source File

SOURCE=..\ext\date\lib\parse_tz.c
# End Source File
# Begin Source File

SOURCE=..\ext\date\php_date.c
# End Source File
# Begin Source File

SOURCE=..\ext\date\php_date.h
# End Source File
# Begin Source File

SOURCE=..\ext\date\lib\timelib.c
# End Source File
# Begin Source File

SOURCE=..\ext\date\lib\timelib.h
# End Source File
# Begin Source File

SOURCE=..\ext\date\lib\timelib_config.h
# End Source File
# Begin Source File

SOURCE=..\ext\date\lib\timelib_structs.h
# End Source File
# Begin Source File

SOURCE=..\ext\date\lib\timezonedb.h
# End Source File
# Begin Source File

SOURCE=..\ext\date\lib\timezonemap.h
# End Source File
# Begin Source File

SOURCE=..\ext\date\lib\tm2unixtime.c
# End Source File
# Begin Source File

SOURCE=..\ext\date\lib\unixtime2tm.c
# End Source File
# End Group
# End Group
# Begin Group "Win32"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\crypt_win32.c
# End Source File
# Begin Source File

SOURCE=.\crypt_win32.h
# End Source File
# Begin Source File

SOURCE=.\glob.c
# End Source File
# Begin Source File

SOURCE=.\glob.h
# End Source File
# Begin Source File

SOURCE=..\win32\grp.h
# End Source File
# Begin Source File

SOURCE=.\md5crypt.c
# End Source File
# Begin Source File

SOURCE=..\win32\param.h
# End Source File
# Begin Source File

SOURCE=..\win32\php_registry.h
# End Source File
# Begin Source File

SOURCE=..\win32\readdir.c
# End Source File
# Begin Source File

SOURCE=..\win32\readdir.h
# End Source File
# Begin Source File

SOURCE=..\win32\registry.c
# End Source File
# Begin Source File

SOURCE=.\select.c
# End Source File
# Begin Source File

SOURCE=.\select.h
# End Source File
# Begin Source File

SOURCE=..\win32\syslog.h
# End Source File
# Begin Source File

SOURCE=..\win32\time.c
# End Source File
# Begin Source File

SOURCE=..\win32\time.h
# End Source File
# Begin Source File

SOURCE=..\win32\unistd.h
# End Source File
# Begin Source File

SOURCE=..\win32\wfile.c
# End Source File
# Begin Source File

SOURCE=..\win32\wfile.h
# End Source File
# Begin Source File

SOURCE=..\ext\snmp\winsnmp.c
# End Source File
# Begin Source File

SOURCE=..\win32\winutil.c
# End Source File
# Begin Source File

SOURCE=.\winutil.h
# End Source File
# Begin Source File

SOURCE=..\win32\wsyslog.c
# End Source File
# Begin Source File

SOURCE=.\build\wsyslog.mc

!IF  "$(CFG)" == "php5dllts - Win32 Debug_TS"

!ELSEIF  "$(CFG)" == "php5dllts - Win32 Release_TS"

!ELSEIF  "$(CFG)" == "php5dllts - Win32 Release_TS_inline"

!ELSEIF  "$(CFG)" == "php5dllts - Win32 Release_TSDbg"

# Begin Custom Build
InputDir=.\build
IntDir=.\Release_TSDbg
InputPath=.\build\wsyslog.mc

"wsyslog.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	mc -h $(InputDir)/.. -r $(InputDir) -x $(IntDir) $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "php5dllts - Win32 Release_TS_Final"

!ENDIF 

# End Source File
# End Group
# Begin Group "Streams"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\main\streams\cast.c
# End Source File
# Begin Source File

SOURCE=..\main\streams\filter.c
# End Source File
# Begin Source File

SOURCE=..\main\streams\memory.c
# End Source File
# Begin Source File

SOURCE=..\main\streams\mmap.c
# End Source File
# Begin Source File

SOURCE=..\main\streams\php_stream_context.h
# End Source File
# Begin Source File

SOURCE=..\main\streams\php_stream_filter_api.h
# End Source File
# Begin Source File

SOURCE=..\main\streams\php_stream_mmap.h
# End Source File
# Begin Source File

SOURCE=..\main\streams\php_stream_plain_wrapper.h
# End Source File
# Begin Source File

SOURCE=..\main\streams\php_stream_transport.h
# End Source File
# Begin Source File

SOURCE=..\main\streams\php_stream_userspace.h
# End Source File
# Begin Source File

SOURCE=..\main\streams\php_streams_int.h
# End Source File
# Begin Source File

SOURCE=..\main\streams\plain_wrapper.c
# End Source File
# Begin Source File

SOURCE=..\main\streams\streams.c
# End Source File
# Begin Source File

SOURCE=..\main\streams\transports.c
# End Source File
# Begin Source File

SOURCE=..\main\streams\userspace.c
# End Source File
# Begin Source File

SOURCE=..\main\streams\xp_socket.c
# End Source File
# End Group
# Begin Source File

SOURCE=.\php5dllts.rc
# End Source File
# Begin Source File

SOURCE=.\php5dllts.rc2
# End Source File
# Begin Source File

SOURCE=.\phpts.def

!IF  "$(CFG)" == "php5dllts - Win32 Debug_TS"

USERDEP__PHPTS="..\ext\sqlite\php_sqlite.def"	"..\ext\libxml\php_libxml2.def"	
# Begin Custom Build - Generating $(InputPath)
InputPath=.\phpts.def

"phpts.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	builddef.bat > phpts.def

# End Custom Build

!ELSEIF  "$(CFG)" == "php5dllts - Win32 Release_TS"

USERDEP__PHPTS="..\ext\sqlite\php_sqlite.def"	"..\ext\libxml\php_libxml2.def"	
# Begin Custom Build - Generating $(InputPath)
InputPath=.\phpts.def

"phpts.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	builddef.bat > phpts.def

# End Custom Build

!ELSEIF  "$(CFG)" == "php5dllts - Win32 Release_TS_inline"

USERDEP__PHPTS="..\ext\sqlite\php_sqlite.def"	"..\ext\libxml\php_libxml2.def"	
# Begin Custom Build - Generating $(InputPath)
InputPath=.\phpts.def

"phpts.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	builddef.bat > phpts.def

# End Custom Build

!ELSEIF  "$(CFG)" == "php5dllts - Win32 Release_TSDbg"

USERDEP__PHPTS="..\ext\sqlite\php_sqlite.def"	"..\ext\libxml\php_libxml2.def"	
# Begin Custom Build - Generating $(InputPath)
InputPath=.\phpts.def

"phpts.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	builddef.bat > phpts.def

# End Custom Build

!ELSEIF  "$(CFG)" == "php5dllts - Win32 Release_TS_Final"

USERDEP__PHPTS="..\ext\sqlite\php_sqlite.def"	"..\ext\libxml\php_libxml2.def"	
# Begin Custom Build - Generating $(InputPath)
InputPath=.\phpts.def

"phpts.def" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	builddef.bat > phpts.def

# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
