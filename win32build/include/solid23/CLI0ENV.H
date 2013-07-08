/****************************************************************\
**  filename     * cli0env.h
**		 *
**  description  * Environment (compiler/library/dll) definitions
**               * for SOLID CLI interface
**		 *
**  copyright 	(C) Solid Information Technology Ltd 1994
\****************************************************************/

#ifndef CLI0ENV_H
#define CLI0ENV_H

#if !defined(CLI_DLL_BUILD)
/****************************************************************\
 *      Definitions to use SOLID CLI functions
\****************************************************************/

#undef SS_EXPORT

#if defined(__WATCOMC__) && (defined(__OS2__) || defined(__OS2V2__)) && defined(__386__)

    /* Watcom C for OS/2 32-bit */
#   define SS_EXPORT __syscall

#elif defined(__WATCOMC__) && defined(__OS2__) && defined(M_I86)

    /* Watcom C for OS/2 16-bit */
#   define SS_EXPORT _far _pascal

#elif defined(__WATCOMC__) && defined(__NETWARE__)

    /* Watcom C for Novell Netware */
#   define SS_EXPORT

#elif defined(SCO) || defined(SS_SCO)

    /* SCO Unix */
#   define SS_EXPORT

#elif defined(_MSC_VER) && (defined(_M_IX86) || defined(_ALPHA_))

    /* Windows NT or WIN32S */
#   define SS_EXPORT __stdcall

#elif defined(_MSC_VER) || defined(M_I86SM) || defined(M_I86CM) || defined(M_I86MM) || defined(M_I86LM) || defined(_WINDOWS)

    /* All Windows and OS/2 16-bit compilers should accept this */
#   define SS_EXPORT _far _pascal

#elif defined(__IBMC__)

    /* IBM CSet/2 for OS/2 32-bit */
#   define SS_EXPORT _System

#elif defined(__BORLANDC__)

    /* Borland C for OS/2 32-bit */
#   define SS_EXPORT __stdcall

#else 

    /* Other systems (e.g. Unix, Open VMS and VAX/VMS) */
#   define SS_EXPORT  

#endif

#endif /* CLI_DLL_BUILD */

#endif /* CLI0ENV_H */
