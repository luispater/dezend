/*
ORACLE, Copyright (c) 1982, 1998 ORACLE Corporation
ORACLE Utilities, Copyright (c) 1981, 1998 ORACLE
Corp
 
Restricted Rights
This program is an unpublished work under the Copyright Act of the
United States and is subject to the terms and conditions stated in
your  license  agreement  with  ORACORP  including  retrictions on
use, duplication, and disclosure.
 
Certain uncopyrighted ideas and concepts are also contained herein.
These are trade secrets of ORACORP and cannot be  used  except  in
accordance with the written permission of ORACLE Corporation.
*/

/*
 * $Header: Z:\oracore3\public\oratypes.h@@\main\coreint_oracore_4.0.0.0 \
 *          .0\nt_8.0.5\2 \
 * Checked in on Wed Apr  1 20:36:08 1998 by ekhor \
 * Copyright (c) 1981, 1998 by Oracle Corporation. All Rights Reserved. \
 * $
 */
 

 
#ifndef ORATYPES
# define ORATYPES
# define SX_ORACLE
# define SX3_ORACLE 


#ifndef ORASTDDEF
# include <stddef.h>
# define ORASTDDEF
#endif

#ifndef ORALIMITS
# include <limits.h>
# define ORALIMITS
#endif


#ifndef TRUE
# define TRUE  1
# define FALSE 0
#endif


typedef unsigned char  ub1;                   
typedef   signed char  sb1;                  
 
#define UB1MAXVAL ((ub1)UCHAR_MAX) 
#define UB1MINVAL ((ub1)        0) 
#define SB1MAXVAL ((sb1)SCHAR_MAX) 
#define SB1MINVAL ((sb1)SCHAR_MIN) 
#define MINUB1MAXVAL ((ub1)  255) 
#define MAXUB1MINVAL ((ub1)    0) 
#define MINSB1MAXVAL ((sb1)  127) 
#define MAXSB1MINVAL ((sb1) -127) 
 
 
typedef unsigned short    ub2;                
typedef   signed short    sb2;               

#define UB2MAXVAL ((ub2)USHRT_MAX) 
#define UB2MINVAL ((ub2)        0) 
#define SB2MAXVAL ((sb2) SHRT_MAX) 
#define SB2MINVAL ((sb2) SHRT_MIN) 
#define MINUB2MAXVAL ((ub2) 65535) 
#define MAXUB2MINVAL ((ub2)     0) 
#define MINSB2MAXVAL ((sb2) 32767) 
#define MAXSB2MINVAL ((sb2)-32767) 
  

typedef unsigned long  ub4;                   
typedef   signed long  sb4;                   
 
#define UB4MAXVAL ((ub4)ULONG_MAX) 
#define UB4MINVAL ((ub4)        0) 
#define SB4MAXVAL ((sb4) LONG_MAX) 
#define SB4MINVAL ((sb4) LONG_MIN) 
#define MINUB4MAXVAL ((ub4) 4294967295) 
#define MAXUB4MINVAL ((ub4)          0) 
#define MINSB4MAXVAL ((sb4) 2147483647) 
#define MAXSB4MINVAL ((sb4)-2147483647) 


#define UB1BITS          CHAR_BIT
#define UB1MASK          ((1 << ((uword)CHAR_BIT)) - 1)


typedef ub1   bitvec;    
#define BITVEC(n) (((n)+(UB1BITS-1))>>3)


typedef  unsigned char OraText;

#ifndef max
#define max(x, y)     (((x) < (y)) ?  (y) : (x))
#endif
#ifndef min
#define min(x, y)     (((x) < (y)) ?  (x) : (y))
#endif

typedef         ub4      duword;                   
typedef         sb4      dsword;                 
typedef         dsword   dword;


#define  DUWORDMAXVAL       UB4MAXVAL 
#define  DUWORDMINVAL       UB4MINVAL 
#define  DSWORDMAXVAL       SB4MAXVAL 
#define  DSWORDMINVAL       SB4MINVAL 
#define  MINDUWORDMAXVAL    MINUB4MAXVAL 
#define  MAXDUWORDMINVAL    MAXUB4MINVAL 
#define  MINDSWORDMAXVAL    MINSB4MAXVAL 
#define  MAXDSWORDMINVAL    MAXSB4MINVAL 
#define  DEWORDMAXVAL       EB4MAXVAL 
#define  DEWORDMINVAL       EB4MINVAL 
#define  MINDEWORDMAXVAL    MINEB4MAXVAL 
#define  MAXDEWORDMINVAL    MAXEB4MINVAL 
#define  DWORDMAXVAL        DSWORDMAXVAL 
#define  DWORDMINVAL        DSWORDMINVAL 
   


typedef ub4 dsize_t;  
 

# define DSIZE_TMAXVAL UB4MAXVAL           
# define MINDSIZE_TMAXVAL (dsize_t)65535 
 

typedef sb4 dboolean;  
 
 
typedef ub4 dptr_t; 


typedef          char     eb1;
typedef          short    eb2;               
typedef          long     eb4;               
typedef          eb4      deword;     


#define EB1MAXVAL      ((eb1)SCHAR_MAX) 
#define EB1MINVAL      ((eb1)        0) 
#define MINEB1MAXVAL   ((eb1)  127) 
#define MAXEB1MINVAL   ((eb1)    0) 
#define EB2MAXVAL      ((eb2) SHRT_MAX) 
#define EB2MINVAL      ((eb2)        0) 
#define MINEB2MAXVAL   ((eb2) 32767) 
#define MAXEB2MINVAL   ((eb2)     0) 
#define EB4MAXVAL      ((eb4) LONG_MAX) 
#define EB4MINVAL      ((eb4)        0) 
#define MINEB4MAXVAL   ((eb4) 2147483647) 
#define MAXEB4MINVAL   ((eb4)          0) 

typedef         sb1  b1;                   

#define  B1MAXVAL  SB1MAXVAL 
#define  B1MINVAL  SB1MINVAL 
 
typedef         sb2      b2;              

#define  B2MAXVAL  SB2MAXVAL 
#define  B2MINVAL  SB2MINVAL 
 
typedef         sb4    b4;                

# define  B4MAXVAL  SB4MAXVAL 
# define  B4MINVAL  SB4MINVAL 
 

#ifndef uiXT
typedef   ub1       BITS8;                              
typedef   ub2       BITS16;                              
typedef   ub4       BITS32;                              
#endif
 
#ifndef LUSEMFC
 typedef OraText text;
#endif

#define  M_IDEN    30

# define SLMXFNMLEN 512		        


typedef          int eword;                  
typedef unsigned int uword;                  
typedef   signed int sword;                  

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

 

typedef unsigned long  ubig_ora;             
typedef   signed long  sbig_ora;             

#define UBIG_ORAMAXVAL ((ubig_ora)ULONG_MAX)
#define UBIG_ORAMINVAL ((ubig_ora)        0)
#define SBIG_ORAMAXVAL ((sbig_ora) LONG_MAX)
#define SBIG_ORAMINVAL ((sbig_ora) LONG_MIN)
#define MINUBIG_ORAMAXVAL ((ubig_ora) 4294967295)
#define MAXUBIG_ORAMINVAL ((ubig_ora)          0)
#define MINSBIG_ORAMAXVAL ((sbig_ora) 2147483647)
#define MAXSBIG_ORAMINVAL ((sbig_ora)-2147483647)

#define UBIGORABITS      (UB1BITS * sizeof(ubig_ora))


#ifdef __BORLANDC__
# ifdef SLU8NATIVE
#  undef SLU8NATIVE
# endif
# ifdef SLS8NATIVE
#  undef SLS8NATIVE
# endif
#else
# define SLU8NATIVE
# define SLS8NATIVE
#endif

#ifdef SLU8NATIVE

typedef unsigned _int64 ub8;

#define UB8ZERO      ((ub8)0)

#define UB8MINVAL ((ub8)0)
#define UB8MAXVAL ((ub8)_UI64_MAX)

#define MAXUB8MINVAL ((ub8)0)
#define MINUB8MAXVAL ((ub8)_UI64_MAX)

#endif 


#ifdef SLS8NATIVE

typedef   signed _int64 sb8;

#define SB8ZERO      ((sb8)0)

#define SB8MINVAL ((sb8) _I64_MIN)
#define SB8MAXVAL ((sb8) _I64_MAX)

#define MAXSB8MINVAL ((sb8) _I64_MIN)
#define MINSB8MAXVAL ((sb8) _I64_MAX)

#endif 


#undef CONST

#define CONST const


# ifdef UTS2
#  define dvoid char
# else
# define dvoid void
# endif 


typedef void (*lgenfp_t)( void );


#ifndef ORASYSTYPES
# include <sys/types.h>
# define ORASYSTYPES
#endif 
#define boolean int


# define SIZE_TMAXVAL UB4MAXVAL              

#define MINSIZE_TMAXVAL (size_t)65535

 
#endif 

