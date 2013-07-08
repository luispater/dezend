/*
 * $Header: ocidfn.h,v 1.9 1995/08/25 16:13:37 slari Exp $ 
 */

/* Copyright (c) 1991 by Oracle Corporation */
/*
   NAME
     ocidfn.h - OCI Definations
   NOTES
     Shipped to users.
   MODIFIED   (MM/DD/YY)
    slari      08/24/95 -  b299432, define CDA_SIZE
    slari      05/11/95 -  add OCI_EV_DEF and OCI_EV_TSF
    dchatter   04/06/95 -  add ifdef flags around OCI_flags
    dchatter   03/08/95 -  piece values
    dchatter   03/06/95 -  merge changes from branch 1.2.720.3
    jfbrown    02/17/95 -  merge changes from branch 1.2.720.2
    dchatter   02/08/95 -  olog call modes
    jfbrown    02/03/95 -  remove non-printable characters
    lchidamb   12/06/94 -  merge changes from branch 1.2.720.1
    lchidamb   10/04/94 -  added field chk to cda_head, cda_def
    dchatter   07/05/94 -  SQLT_CUR added
    rkooi2     11/27/92 -  Changing e* datatypes to s* 
    rkooi2     10/26/92 -  More portability mods 
    rkooi2     10/22/92 -  Added #ifndef ORATYPES ... 
    rkooi2     10/18/92 -  Changes to make it portable. 
    sjain      03/16/92 -  Creation 
*/

/*
 *  ocidfn.h
 *
 *  Common header file for OCI C sample programs.
 *  This header declares the cursor and logon data area structure.
 *  The types used are defined in <oratypes.h>.
 *
 */
 
#ifndef OCIDFN
#define OCIDFN

#include <oratypes.h>

/* The cda_head struct is strictly PRIVATE.  It is used
   internally only. Do not use this struct in OCI programs. */

struct cda_head {
    sb2          v2_rc;
    ub2          ft;
    ub4          rpc;
    ub2          peo;
    ub1          fc;
    ub1          rcs1;
    ub2          rc;
    ub1          wrn;
    ub1          rcs2;
    sword        rcs3;
    struct {
        struct {
           ub4    rcs4;
           ub2    rcs5;
           ub1    rcs6;
        } rd;
        ub4    rcs7;
        ub2    rcs8;
    } rid;
    sword        ose;
    ub1		 chk;
    dvoid        *rcsp;
};


# define CDA_SIZE 64

/* the real CDA, padded to CDA_SIZE bytes in size */
struct cda_def {
    sb2          v2_rc;                                    /* V2 return code */
    ub2          ft;                                    /* SQL function type */
    ub4          rpc;                                /* rows processed count */
    ub2          peo;                                  /* parse error offset */
    ub1          fc;                                    /* OCI function code */
    ub1          rcs1;                                        /* filler area */
    ub2          rc;                                       /* V7 return code */
    ub1          wrn;                                       /* warning flags */
    ub1          rcs2;                                           /* reserved */
    sword        rcs3;                                           /* reserved */
    struct {                                              /* rowid structure */
        struct {
           ub4    rcs4;
           ub2    rcs5;
           ub1    rcs6;
        } rd;
        ub4    rcs7;
        ub2    rcs8;
    } rid;
    sword        ose;                                 /* OSD dependent error */
    ub1		 chk;
    dvoid        *rcsp;                          /* pointer to reserved area */
    ub1          rcs9[CDA_SIZE - sizeof (struct cda_head)];        /* filler */
};

typedef struct cda_def Cda_Def;

/* the logon data area (LDA)
   is the same shape as the CDA */
typedef struct cda_def Lda_Def;

/* OCI Environment Modes for opinit call */
#define OCI_EV_DEF 0                  /* default single-threaded environment */
#define OCI_EV_TSF 1                              /* thread-safe environment */

/* OCI Logon Modes for olog call */
#define OCI_LM_DEF 0                                        /* default login */
#define OCI_LM_NBL 1                                   /* non-blocking logon */

/* 
 * since sqllib uses both ocidef and ocidfn the following defines
 * need to be guarded
 */
#ifndef OCI_FLAGS 
#define OCI_FLAGS

/* OCI_*_PIECE defines the piece types that are returned or set
*/
#define OCI_ONE_PIECE   0                 /* there or this is the only piece */
#define OCI_FIRST_PIECE 1                        /* the first of many pieces */
#define OCI_NEXT_PIECE  2                         /* the next of many pieces */
#define OCI_LAST_PIECE  3                   /* the last piece of this column */
#endif


/* input data types */
#define SQLT_CHR  1                        /* (ORANET TYPE) character string */
#define SQLT_NUM  2                          /* (ORANET TYPE) oracle numeric */
#define SQLT_INT  3                                 /* (ORANET TYPE) integer */
#define SQLT_FLT  4                   /* (ORANET TYPE) Floating point number */
#define SQLT_STR  5                                /* zero terminated string */
#define SQLT_VNU  6                        /* NUM with preceding length byte */
#define SQLT_PDN  7                  /* (ORANET TYPE) Packed Decimal Numeric */
#define SQLT_LNG  8                                                  /* long */
#define SQLT_VCS  9                             /* Variable character string */
#define SQLT_NON  10                      /* Null/empty PCC Descriptor entry */
#define SQLT_RID  11                                                /* rowid */
#define SQLT_DAT  12                                /* date in oracle format */
#define SQLT_VBI  15                                 /* binary in VCS format */
#define SQLT_BIN  23                                  /* binary data(DTYBIN) */
#define SQLT_LBI  24                                          /* long binary */
#define SQLT_UIN  68                                     /* unsigned integer */
#define SQLT_SLS  91                        /* Display sign leading separate */
#define SQLT_LVC  94                                  /* Longer longs (char) */
#define SQLT_LVB  95                                  /* Longer long binary */ 
#define SQLT_AFC  96                                      /* Ansi fixed char */
#define SQLT_AVC  97                                        /* Ansi Var char */
#define SQLT_CUR  102                                        /* cursor  type */
#define SQLT_LAB  105                                          /* label type */
#define SQLT_OSL  106                                        /* oslabel type */


#endif  /* OCIDFN */


