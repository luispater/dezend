/* Copyright (c) Oracle Corporation 1986, 1990.  All Rights Reserved. */

#ifndef ORASTDDEF
# include <stddef.h>
# define ORASTDDEF
#endif

#ifndef ORALIMITS
# include <limits.h>
# define ORALIMITS
#endif

#ifndef  SX_ORACLE
#define  SX_ORACLE
#define  SX
#define  ORATYPES

#ifndef TRUE
# define TRUE  1
# define FALSE 0
#endif

#ifdef lint
# ifndef mips
#  define signed
# endif /* mips */
#endif /* lint */

#ifdef ENCORE_88K
# ifndef signed
#  define signed
# endif /* signed */
#endif /* ENCORE_88K */

#if defined(SYSV_386) || defined(SUN_OS)
# ifdef signed
#  undef signed
# endif /* signed */
# define signed
#endif /* SYSV_386 */

#ifndef lint
typedef          int eword;                  /* use where sign not important */
typedef unsigned int uword;                  /* use where unsigned important */
typedef   signed int sword;                  /* use where   signed important */
#else
#define eword int
#define uword unsigned int
#define sword signed int
#endif /*LINT */

#define  EWORDMAXVAL  ((eword) INT_MAX)
#define  EWORDMINVAL  ((eword)       0)
#define  UWORDMAXVAL  ((uword)UINT_MAX)
#define  UWORDMINVAL  ((uword)       0)
#define  SWORDMAXVAL  ((sword) INT_MAX)
#define  SWORDMINVAL  ((sword) INT_MIN)
#define  MINEWORDMAXVAL  ((eword)  32767)
#define  MAXEWORDMINVAL  ((eword)      0)
#define  MINUWORDMAXVAL  ((uword)  65535)
#define  MAXUWORDMINVAL  ((uword)      0)
#define  MINSWORDMAXVAL  ((sword)  32767)
#define  MAXSWORDMINVAL  ((sword) -32767)


#ifndef lint
# ifdef mips
typedef   signed char  eb1;
# else
#if defined(__IBMC__)
     /* make eb1 signed, since it's signed for all other ports */
typedef   signed char  eb1;                  /* use where sign not important */
#else
typedef          char  eb1;                  /* use where sign not important */
#endif
# endif /* mips */
typedef unsigned char  ub1;                  /* use where unsigned important */
typedef   signed char  sb1;                  /* use where   signed important */
#else
#define eb1 char
#define ub1 unsigned char
#define sb1 signed char
#endif /* LINT */

#define EB1MAXVAL ((eb1)SCHAR_MAX)
#define EB1MINVAL ((eb1)        0)
#if defined(mips)                     /* mips compilers barf on x[UB1MAXVAL] */
# ifndef lint
#  define UB1MAXVAL (UCHAR_MAX)
# endif
#endif
#ifndef UB1MAXVAL
# ifdef SCO_UNIX
# define UB1MAXVAL (UCHAR_MAX)
# else
# define UB1MAXVAL ((ub1)UCHAR_MAX)
# endif /* SCO_UNIX */
#endif
#define UB1MINVAL ((ub1)        0)
#define SB1MAXVAL ((sb1)SCHAR_MAX)
#define SB1MINVAL ((sb1)SCHAR_MIN)
#define MINEB1MAXVAL ((eb1)  127)
#define MAXEB1MINVAL ((eb1)    0)
#define MINUB1MAXVAL ((ub1)  255)
#define MAXUB1MINVAL ((ub1)    0)
#define MINSB1MAXVAL ((sb1)  127)
#define MAXSB1MINVAL ((sb1) -127)
/* number of bits in a byte */
#define UB1BITS          CHAR_BIT
#define UB1MASK              0xff

/* human readable (printable) characters */
typedef  unsigned char text;


#ifndef lint
typedef          short    eb2;               /* use where sign not important */
typedef unsigned short    ub2;               /* use where unsigned important */
typedef   signed short    sb2;               /* use where   signed important */
#else
#define eb2  short
#define ub2  unsigned short
#define sb2  signed short
#endif /* LINT */

#define EB2MAXVAL ((eb2) SHRT_MAX)
#define EB2MINVAL ((eb2)        0)
#define UB2MAXVAL ((ub2)USHRT_MAX)
#define UB2MINVAL ((ub2)        0)
#define SB2MAXVAL ((sb2) SHRT_MAX)
#define SB2MINVAL ((sb2) SHRT_MIN)
#define MINEB2MAXVAL ((eb2) 32767)
#define MAXEB2MINVAL ((eb2)     0)
#define MINUB2MAXVAL ((ub2) 65535)
#define MAXUB2MINVAL ((ub2)     0)
#define MINSB2MAXVAL ((sb2) 32767)
#define MAXSB2MINVAL ((sb2)-32767)

#if defined(A_OSF)

#ifndef lint
typedef          int  eb4;                  /* use where sign not important */
typedef unsigned int  ub4;                  /* use where unsigned important */
typedef   signed int  sb4;                  /* use where   signed important */
#else
#define eb4 int
#define ub4 unsigned int
#define sb4 signed int
#endif /* LINT */

#define EB4MAXVAL ((eb4)  INT_MAX)
#define EB4MINVAL ((eb4)        0)
#define UB4MAXVAL ((ub4) UINT_MAX)
#define UB4MINVAL ((ub4)        0)
#define SB4MAXVAL ((sb4)  INT_MAX)
#define SB4MINVAL ((sb4)  INT_MIN)
#define MINEB4MAXVAL ((eb4) 2147483647)
#define MAXEB4MINVAL ((eb4)          0)
#define MINUB4MAXVAL ((ub4) 4294967295)
#define MAXUB4MINVAL ((ub4)          0)
#define MINSB4MAXVAL ((sb4) 2147483647)
#define MAXSB4MINVAL ((sb4)-2147483647)

#else  /* A_OSF */


#ifndef lint
typedef          long  eb4;                  /* use where sign not important */
typedef unsigned long  ub4;                  /* use where unsigned important */
typedef   signed long  sb4;                  /* use where   signed important */
#else
#define eb4 long
#define ub4 unsigned long
#define sb4 signed long
#endif /* LINT */

#define EB4MAXVAL ((eb4) LONG_MAX)
#define EB4MINVAL ((eb4)        0)
#define UB4MAXVAL ((ub4)ULONG_MAX)
#define UB4MINVAL ((ub4)        0)
#define SB4MAXVAL ((sb4) LONG_MAX)
#define SB4MINVAL ((sb4) LONG_MIN)
#define MINEB4MAXVAL ((eb4) 2147483647)
#define MAXEB4MINVAL ((eb4)          0)
#define MINUB4MAXVAL ((ub4) 4294967295)
#define MAXUB4MINVAL ((ub4)          0)
#define MINSB4MAXVAL ((sb4) 2147483647)
#define MAXSB4MINVAL ((sb4)-2147483647)
#endif /* A_OSF */

#ifndef lint
typedef unsigned long  ubig_ora;             /* use where unsigned important */
typedef   signed long  sbig_ora;             /* use where   signed important */
#else
#define ubig_ora unsigned long
#define sbig_ora signed long
#endif /* LINT */

#define UBIG_ORAMAXVAL ((ubig_ora)ULONG_MAX)
#define UBIG_ORAMINVAL ((ubig_ora)        0)
#define SBIG_ORAMAXVAL ((sbig_ora) LONG_MAX)
#define SBIG_ORAMINVAL ((sbig_ora) LONG_MIN)
#define MINUBIG_ORAMAXVAL ((ubig_ora) 4294967295)
#define MAXUBIG_ORAMINVAL ((ubig_ora)          0)
#define MINSBIG_ORAMAXVAL ((sbig_ora) 2147483647)
#define MAXSBIG_ORAMINVAL ((sbig_ora)-2147483647)

#undef CONST

#define CONST const

#ifdef lint
# define dvoid void
#else

# ifdef UTS2
#  define dvoid char
# else
# define dvoid void
# endif /* UTS2 */

#endif /* lint */


typedef void (*lgenfp_t)(/*_ void _*/);

#ifndef ORASYSTYPES
# ifdef MAC_OS
#  include <Types.h>
# else
#  include <sys/types.h>
# endif
# define ORASYSTYPES
#endif /* !ORAUSRINCLUDESYSTYPES */
#ifdef MAC_OS
# define boolean Boolean
#else
# define boolean int
#endif


#ifdef sparc
# define SIZE_TMAXVAL SB4MAXVAL                /* This case applies for sun4 */
#else
# define SIZE_TMAXVAL UB4MAXVAL              /* This case applies for others */
#endif /* sparc */

#define MINSIZE_TMAXVAL (size_t)65535


#endif /* SX_ORACLE */

