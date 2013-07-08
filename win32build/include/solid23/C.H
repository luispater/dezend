/****************************************************************\
**  filename	 * c.h
**               * 
**  description  * Basic C language definitions for system 
**		 * services.
**		 * Definitions needed by sample programs.
**               * 
**  copyright 	(C) Solid Information Technology Ltd 1996
\****************************************************************/

#if !defined(SSC_H) && defined(SS_UNIX)
#  include <stdio.h>
#  include <sys/types.h>
#endif /* !SSC_H && SS_UNIX */

#if !defined(SSC_H) && defined(SS_WINDOWS)
#  include <windows.h>
#  include <stdio.h>
#endif /* !SSC_H && SS_WINDOWS */

#ifdef bool
# undef bool
#endif

#ifdef uchar
# undef uchar
#endif

#ifdef ulong
# undef ulong
#endif

#ifdef ushort
# undef ushort
#endif

#ifdef uint
# undef uint
#endif

#define bool    int
#define uchar   unsigned char
#define ulong   unsigned long
#define ushort  unsigned short
#define uint    unsigned int

#ifndef SSC_H
#define SSC_H

#ifdef SS_CLIX
#  define const
#  define volatile
#  define signed
#endif /* SS_CLIX */

#define FALSE   0
#define TRUE    1

#ifdef SS_DOSX
#  define SS_FAR  /* far  */
#else /* SS_DOSX */
#  define SS_FAR 
#endif /* SS_DOSX */

#ifdef SS_VMS

#ifndef signed
# define signed
#endif

#ifdef NULL
#  undef NULL
#endif
#define NULL 0

#endif /* SS_VMS */

/* ------------------------------------------------------------ */
#ifndef MSC

# define __near

#else /* MSC */

# if MSC >= 70

#  pragma warning(disable:4131)
#  pragma warning(disable:4018) 
	/* warning C4018: '<=' : signed/unsigned mismatch */

# else /* MSC 5.1 or 6.0 */

#  define __near    near
#  define __far     far
#  define __cdecl   cdecl
#  define __pascal  pascal
#  define __export  _export

# endif /* MSC >= 70 */

#endif /* MSC */

/* ------------------------------------------------------------ */
#if defined(SS_W32) && defined(WCC)
	/* Watcom Windows 386 version */

#  define SS_EXPORT         far __pascal
#  define SS_EXPORT_CDECL   far __cdecl
#  define SS_CALLBACK       far __pascal
#  define SS_CDECL          __cdecl
#  define SS_PASCAL16       far __pascal
#  define SS_FAR16PTR       *
#  define SS_CLIBCALLBACK
#  if defined(SS_DLL) 
#    define SS_EXPORT_C     SS_EXPORT
#    define SS_EXPORT_H     SS_EXPORT
#    define SS_DLLCALL      far __pascal
#    define SS_DLLCALL16    far __pascal
#  else /* SS_DLL */
#    define SS_EXPORT_H
#    define SS_EXPORT_C
#    define SS_DLLCALL
#    define SS_DLLCALL16
#  endif /* SS_DLL */

/* ------------------------------------------------------------ */
#elif defined(SS_WIN)                  /* 16-bit Windows */

#  define SS_EXPORT         __far __pascal __export
#  define SS_EXPORT_CDECL   __far __cdecl  __export
#  define SS_CALLBACK       __far __pascal __export
#  define SS_CDECL          __cdecl
#  define SS_PASCAL16       __far __pascal
#  define SS_FAR16PTR       *
#  ifdef WCC
#    define SS_CLIBCALLBACK
#  else
#    define SS_CLIBCALLBACK SS_CDECL
#  endif
#  if defined(SS_DLL) 
#    define SS_EXPORT_C     SS_EXPORT
#    define SS_EXPORT_H     SS_EXPORT
#    define SS_DLLCALL      __far __pascal
#    define SS_DLLCALL16    __far __pascal
#  else /* SS_DLL */
#    define SS_EXPORT_H
#    define SS_EXPORT_C
#    define SS_DLLCALL
#    define SS_DLLCALL16
#  endif /* SS_DLL */

/* ------------------------------------------------------------ */
#elif (SS_OS2 == 16)

#  define SS_CDECL          __cdecl
#  define SS_CLIBCALLBACK   SS_CDECL _loadds
#  if defined(SS_DLL)
#    define SS_EXPORT       pascal far _export _loadds
#    define SS_PASCAL16     pascal far
#    define SS_FAR16PTR     *
#    define SS_EXPORT_C     SS_EXPORT
#    define SS_EXPORT_H     SS_EXPORT
#    define SS_DLLCALL      pascal far
#    define SS_DLLCALL16    SS_DLLCALL
#  else
#    define SS_EXPORT       pascal far
#    define SS_PASCAL16 
#    define SS_FAR16PTR     *
#    define SS_EXPORT_C     SS_EXPORT
#    define SS_EXPORT_H     SS_EXPORT
#    define SS_DLLCALL
#    define SS_DLLCALL16    
#  endif
#  define SS_EXPORT_CDECL
#  define SS_CALLBACK       SS_CDECL _loadds

/* ------------------------------------------------------------ */
#elif (SS_OS2 == 32) && defined(BORLANDC)

#  define SS_CLIBCALLBACK   __stdcall
#  define SS_FAR16PTR       _far16 *        /* FAR16PTR */
#  define SS_PASCAL16       _far16 _pascal  /* PASCAL16 */
#  define SS_CDECL          _cdecl
#  if defined(SS_DLL) 
#    define SS_EXPORT       _export __stdcall
#    define SS_DLLCALL      __stdcall
#    define SS_DLLCALL16    _far16 _pascal
#  else /* SS_DLL */
#    define SS_EXPORT
#    define SS_DLLCALL
#  endif /* SS_DLL */
#  define SS_EXPORT_C       SS_EXPORT  
#  define SS_EXPORT_H       SS_EXPORT  
#  define SS_EXPORT_CDECL
#  define SS_CALLBACK

/* ------------------------------------------------------------ */
#elif (SS_OS2 == 32) && defined(CSET2)

#  define SS_CLIBCALLBACK
#  define SS_FAR16PTR       * _Seg16  
#  define SS_PASCAL16       _Far16 _Pascal /* PASCAL16  */
#  define SS_CDECL
#  if defined(SS_DLL)       /* Use system's standard calling convention */
#    define SS_EXPORT_H     _Export _System /* APIENTRY */
#    define SS_EXPORT_C     _System         /* _System */
#    define SS_DLLCALL      _System
#    define SS_DLLCALL16    _Far16 _Pascal /* PASCAL16 == _far16 _pascal */
#  else /* SS_DLL */
#    define SS_EXPORT_H
#    define SS_EXPORT_C
#    define SS_DLLCALL
#    define SS_DLLCALL16
#  endif /* SS_DLL */
#  define SS_EXPORT         SS_EXPORT_H  
#  define SS_EXPORT_CDECL
#  define SS_CALLBACK

/* ------------------------------------------------------------ */
#elif (SS_OS2 == 32) && defined(WCC)

#  define SS_CLIBCALLBACK 
#  define SS_FAR16PTR       _Far16 *
#  define SS_PASCAL16       _Far16 _Pascal
#  define SS_CDECL          __cdecl
#  if defined(SS_DLL) 
#    define SS_EXPORT_H     __syscall _export 
#    define SS_EXPORT_C     __syscall _export
#    define SS_DLLCALL      __syscall
#    define SS_DLLCALL16    _Far16 _Pascal
#  else /* SS_DLL */
#    define SS_EXPORT_H
#    define SS_EXPORT_C
#    define SS_DLLCALL
#    define SS_DLLCALL16
#  endif /* SS_DLL */
#  define SS_EXPORT         SS_EXPORT_H  
#  define SS_EXPORT_CDECL   __export __cdecl
#  define SS_CALLBACK

/* ------------------------------------------------------------ */
#elif defined(SS_NT)

#  define SS_EXPORT         __stdcall   /* WINAPI */
#  define SS_EXPORT_CDECL   _cdecl      /* WINAPIV */
#  define SS_CALLBACK       __stdcall   /* */
#  define SS_CDECL          _cdecl
#  define SS_EXPORT_C       SS_EXPORT  
#  define SS_EXPORT_H       SS_EXPORT  
#  define SS_CLIBCALLBACK   SS_CDECL
#  define SS_DLLCALL        __stdcall   /* WINAPI */
#  define SS_FAR16PTR       *
#  define SS_DLLCALL16
#  define SS_PASCAL16 

/* ------------------------------------------------------------ */
#else 

#  define SS_CLIBCALLBACK
#  define SS_EXPORT  
#  define SS_PASCAL16
#  define SS_FAR16PTR *
#  define SS_EXPORT_C SS_EXPORT
#  define SS_EXPORT_H SS_EXPORT
#  define SS_CDECL
#  define SS_DLLCALL
#  define SS_DLLCALL16
#  define SS_EXPORT_CDECL
#  define SS_CALLBACK

#endif

/* ------------------------------------------------------------ */
#if defined(WCC)
#  define SS_NOTUSED(var) (var = var)
#elif defined(CSET2) || (defined(MSC) && MSC >= 70) || defined(SS_NT)
#  define SS_NOTUSED(var) (var = var)
#else
#  define SS_NOTUSED(var) (void)var
#endif

/* ------------------------------------------------------------ */

#define SS_CLIBCALL SS_CLIBCALLBACK

#define SS_RETYPE(type, expr) (*(type*)&(expr))


#define SS_MIN(a, b)   ((a) < (b) ? (a) : (b))
#define SS_MAX(a, b)   ((a) < (b) ? (b) : (a))

#endif /* SSC_H */

