/*
   PROPRIETARY SOURCE CODE OF NETSCAPE COMMUNICATIONS CORPORATION.

   Copyright (c) 1994, 1995, 1996, and 1997 Netscape Communications
   Corporation.  All rights reserved.

   Use of this Source Code is subject to the terms of the applicable
   license agreement from Netscape Communications Corporation.
*/

#ifndef PUBLIC_BASE_SYSTEMS_H
#define PUBLIC_BASE_SYSTEMS_H

/*
 * File:        systems.h
 * 
 * Description:
 *
 *      This file defines various platform-dependent symbols, which are
 *      used to configure platform-dependent aspects of the API.
 */

/* --- Begin native platform configuration definitions --- */

#if defined(AIX)

#define FILE_UNIX
#define FILE_UNIX_MMAP
#define MALLOC_POOLS
#define SEM_FLOCK
#define SHMEM_UNIX_MMAP
#define ZERO(ptr,len) memset(ptr,0,len)
#define NEED_STRCASECMP
#define NEED_STRNCASECMP

#elif defined(BSDI)

#define BSD_FLOCK
#define FILE_UNIX
#define FILE_UNIX_MMAP
#define MALLOC_POOLS
#define SEM_FLOCK
#define SHMEM_UNIX_MMAP
#define ZERO(ptr,len) memset(ptr,0,len)

#elif defined(HPUX)

#define FILE_UNIX
#define FILE_UNIX_MMAP
#define MALLOC_POOLS
#define SEM_FLOCK
/* warning: mmap doesn't work under 9.04 */
#define SHMEM_UNIX_MMAP
#define ZERO(ptr,len) memset(ptr,0,len)

#elif defined (IRIX)

#define FILE_UNIX
#define FILE_UNIX_MMAP
#define MALLOC_POOLS
#define SEM_FLOCK
#define SHMEM_UNIX_MMAP
#define ZERO(ptr,len) memset(ptr,0,len)

#elif defined(NCR)
 
#define CASECMPARG_T unsigned
#define FILE_UNIX
#define FILE_UNIX_MMAP
#define MALLOC_POOLS
#define NEED_STRCASECMP
#define NEED_STRNCASECMP
#ifndef S_ISLNK
#define S_ISLNK(m) (((m) & S_IFMT) == S_IFLNK)
#endif
#define SEM_FLOCK
#define SHMEM_UNIX_MMAP
#define ZERO(ptr,len) memset(ptr,0,len)

#elif defined(NEC)

#define FILE_UNIX
#define FILE_UNIX_MMAP
#define MALLOC_POOLS
#define NEED_STRCASECMP
#define NEED_STRNCASECMP
#ifndef S_ISLNK
#define S_ISLNK(m) (((m) & S_IFMT) == S_IFLNK)
#endif
#define SEM_FLOCK
#define SHMEM_UNIX_MMAP
#define ZERO(ptr,len) memset(ptr,0,len)

#elif defined(OSF1)

#undef BSD_FLOCK
#define FILE_UNIX
#define FILE_UNIX_MMAP
#define MALLOC_POOLS
#define SEM_FLOCK
#define SHMEM_UNIX_MMAP
#define ZERO(ptr,len) memset(ptr,0,len)

#elif defined(SCO)

#define FILE_UNIX
#define FILE_UNIX_MMAP
#define MALLOC_POOLS
#define SEM_FLOCK
#define SHMEM_UNIX_MMAP
#define ZERO(ptr,len) memset(ptr,0,len)

#elif defined(SNI)
 
#define FILE_UNIX
#define FILE_UNIX_MMAP
#define MALLOC_POOLS
#define NEED_STRCASECMP
#define NEED_STRNCASECMP
#ifndef S_ISLNK
#define S_ISLNK(m) (((m) & S_IFMT) == S_IFLNK)
#endif
#define SEM_FLOCK
#define SHMEM_UNIX_MMAP
#define socketpair(a,b,c,d) pipe(d)
#define ZERO(ptr,len) memset(ptr,0,len)

#elif defined(SOLARIS)

#undef	FILE_UNIX	/* avoid redefinition message */
#define FILE_UNIX
#define FILE_UNIX_MMAP
#define MALLOC_POOLS
/* The Solaris routines return ENOSPC when too many semaphores are SEM_UNDO. */
#define SEM_FLOCK
#define SHMEM_UNIX_MMAP
#define ZERO(ptr,len) memset(ptr,0,len)

#elif defined (SONY)

#define FILE_UNIX
#define FILE_UNIX_MMAP
#define NEED_STRCASECMP
#define NEED_STRNCASECMP
#define SEM_FLOCK
#define SHMEM_UNIX_MMAP
#define ZERO(ptr,len) memset(ptr,0,len)

#elif defined(SUNOS4)

#define BSD_FLOCK
#define FILE_UNIX
#define FILE_UNIX_MMAP
#define MALLOC_POOLS
#define SEM_FLOCK
#define SHMEM_UNIX_MMAP
#define ZERO(ptr,len) memset(ptr,0,len)

#elif defined(UNIXWARE)
 
#define CASECMPARG_T const
#define FILE_UNIX
#define FILE_UNIX_MMAP
#define MALLOC_POOLS
#define NEED_STRCASECMP
#define NEED_STRNCASECMP
#ifndef S_ISLNK
#define S_ISLNK(m) (((m) & S_IFMT) == S_IFLNK)
#endif
#define SEM_FLOCK
#define SHMEM_UNIX_MMAP
#define ZERO(ptr,len) memset(ptr,0,len)
#define TCPLEN_T size_t

#elif defined (XP_WIN32)      /* Windows NT */

#include <wtypes.h>
#include <winbase.h>

typedef void* PASSWD;

#define caddr_t PCHAR
#define CASECMPARG_T const
#define FILE_WIN32
#define FILE_WIN32_MMAP
#define MALLOC_POOLS
#define NEED_STRCASECMP
#define NEED_STRNCASECMP
#define NET_WINSOCK
#define NSAPI_PUBLIC __declspec(dllexport)
/* The stat call under NT doesn't define these macros */
#ifndef S_ISDIR
#define S_ISDIR(mode)   ((mode&S_IFMT) == S_IFDIR)
#endif
#ifndef S_ISREG
#define S_ISREG(mode)   ((mode&S_IFMT) == S_IFREG)                             
#endif
#ifndef S_ISLNK
#define S_ISLNK(x) (0)
#endif
#define SEM_WIN32
#define SHMEM_WIN32_MMAP
#define ZERO(ptr, len) ZeroMemory(ptr, len)

#endif	/* Windows NT */

#ifndef NSPR_BEGIN_EXTERN_C
#ifdef __cplusplus
#define NSPR_BEGIN_EXTERN_C	extern "C" {
#define NSPR_END_EXTERN_C	}
#else
#define NSPR_BEGIN_EXTERN_C
#define NSPR_END_EXTERN_C
#endif /* __cplusplus */
#endif /* !NSPR_BEGIN_EXTERN_C */

#ifndef TCPLEN_T
#define TCPLEN_T int
#endif

#ifndef NSAPI_PUBLIC
#define NSAPI_PUBLIC
#endif /* !NSAPI_PUBLIC */

#if defined(NEED_STRCASECMP) || defined(NEED_STRNCASECMP)
#ifndef CASECMPARG_T
#define CASECMPARG_T const
#endif /* !CASECMPARG_T */
#endif /* NEED_STRCASECMP || NEED_STRNCASECMP */

#endif /* PUBLIC_BASE_SYSTEMS_H */
