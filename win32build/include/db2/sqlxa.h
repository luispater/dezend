/******************************************************************************
*
* Source File Name = SQLXA.H
*
* (C) COPYRIGHT International Business Machines Corp. 1993, 1995
* All Rights Reserved
* Licensed Materials - Property of IBM
*
* US Government Users Restricted Rights - Use, duplication or
* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
*
* Function = Include File defining:
*              XA Interface - Constants
*              XA Interface - Data Structures
*              XA Interface - Function Prototypes
*
 * Operating System = Common C Include File
*
******************************************************************************/

#ifndef SQL_H_SQLXA
   #define SQL_H_SQLXA             /* Permit duplicate Includes */

#include "sqlsystm.h"              /* Provides _SQLOLDCHAR      */

#ifdef __cplusplus
extern "C" {
#endif

#if (defined(DB2OS2) || defined(DB2NT))
#pragma pack(4)
#elif (defined(DB2WIN))
#pragma pack(2)
#elif (defined(DB2MAC))
#if (defined(DB2PPC))
#pragma align 4
#elif (defined(DB268K))
#pragma align 2
#endif
#elif (defined(DB2HP) || defined(DB2SNI))

#elif (defined(DB2SUN))
#pragma options align=natural
#elif (defined(DB2AIX))
#pragma options align=power
#endif

/*
* Define an alias for the XID structure defined by X/Open.
* This avoids conflicts with the XID defined by X11 (Xwindows).
*/

#define SQLXA_XIDDATASIZE   128    /* size in bytes           */

#define SQLXA_XID_FORMATID  0x53514C20      /* "SQL " */
#define SQLXA_XID_BQLEN     0
#define SQLXA_XID_APPLIDLEN 25
#define SQLXA_XID_SEQNUM    4
#define SQLXA_XID_GTLEN     SQL_DBNAME_SZ+1+SQLXA_XID_APPLIDLEN+SQLXA_XID_SEQNUM+1

#define SQLXA_XID_TSLEN     4
#define SQLXA_XID_LOGIDLEN  4
#define SQLXA_XID_LOGIDPOS  SQL_DBNAME_SZ+1+SQLXA_XID_TSLEN
#define SQLXA_XID_TIDPOS    SQLXA_XID_LOGIDPOS+SQLXA_XID_LOGIDLEN
#define SQLXA_XID_TIDLEN    6

struct sqlxa_xid_t {
  long formatID;                   /* format identifier       */
  long gtrid_length;               /* value from 1 through 64 */
  long bqual_length;               /* value from 1 through 64 */
  char data[SQLXA_XIDDATASIZE];
  };

typedef struct sqlxa_xid_t SQLXA_XID;

/* the following macro can generate a NULLXID */
#define SQLXA_NULLXID( x ) \
{ (x).formatID     = -1; \
(x).gtrid_length = -1; \
(x).bqual_length = -1; \
(x).data[0] = 0; }

/* provide a test for the NULLXID */
/* note that we only test the formatID! -> a simplification */
#define SQLXA_XID_IS_NULL( x ) ( (x).formatID     == -1 )

/* provide a test for Microsoft DTC */
#define SQLXA_XID_IS_MSDTC( x ) ( (x).formatID    == 0  )

/* provide a test for Encina Server */
#define SQLXA_XID_IS_ENCINA( x ) ( (x).formatID   == 113577 )

/*
* Compare xidA and xidB, for equality.
* Returns "true" if compared to NULLXID by checking the formatID
* Returns "true" (ie. non-zero) if xid's are the same.
* This macro expands to an expression and is therefore suitable for use in
* statements like "while" or "if"
*/

#define XIDEQUAL(xidA, xidB) ( (((xidA).formatID == -1) &&                    \
                                ((xidB).formatID == -1)) ? 1 :                \
                               ((xidA).formatID    ==(xidB).formatID)     &&  \
                               ((xidA).gtrid_length==(xidB).gtrid_length) &&  \
                               ((xidA).bqual_length==(xidB).bqual_length) &&  \
                               ( memcmp((xidA).data, (xidB).data,             \
                                        (int)(xidA).gtrid_length +            \
                                        (int)(xidA).bqual_length) == 0) )

/*
* Copy xidB into xidA
* -> a macro is not really needed here, since the C language supports
* structure assignments (and this should be efficient on any platform).
*/

#define XIDCPY( xidA, xidB )  (xidA) = (xidB);

/* define a TRUE/FALSE pair for boolean fields in XA structures */
#define SQLXA_TRUE    1
#define SQLXA_FALSE   0

/* define all possible states of transactions returned by "recover" */
#define SQLXA_TS_PREP       'P'  /* prepared                        */
#define SQLXA_TS_HCOM       'X'  /* heuristically committed         */
#define SQLXA_TS_HROL       'Y'  /* heuristically rolled back       */
#define SQLXA_TS_END        'E'  /* idle -> xa_end has been issued  */
#define SQLXA_TS_MACK       'M'  /* missing commit acknowledgement  */

/* possible indoubt states in Parallel Edition ONLY other than the above */
#define SQLXA_TS_PHC        'A'  /* prepared and heur. committed */
#define SQLXA_TS_PHR        'B'  /* prepared and heur. rolled back */
#define SQLXA_TS_HCHR       'C'  /* heur. committed and heur. rolled back */
#define SQLXA_TS_PHCHR      'D'  /* prepared, heur. committed and heur. rolled back */

#define SQLXA_EXE_ALL_NODES  1   /* execute the request on all the nodes in MPP environment */
#define SQLXA_EXE_THIS_NODE  0   /* execute the request on the node it is issued from */

/* various transaction originators */
#define SQLXA_ORIG_XA        1   /* transaction originated by XA */
#define SQLXA_ORIG_PE        0   /* transaction originated by DB2 in MPP environment*/

/*
* The following structure is used to describe the current state
* of an indoubt (ie "prepared") or heuristically completed transaction.
*
* We need to beef up the explanations of the structure elements,
* so that they can appear in the user doc -> CLP will be providing
* the info basically verbatim to the user.
*
* The char string areas will always be right padded with blanks.
*/

#define SQLXA_DBNAME_SZ         8
#define SQLXA_APPLID_SZ         32
#define SQLXA_SEQ_SZ            4
#define SQLXA_USERID_SZ         8
#define SQLXA_PASSWD_SZ         8

typedef struct sqlxa_recover_t {
   unsigned long  timestamp;
   SQLXA_XID      xid;
   _SQLOLDCHAR    dbalias[SQLXA_DBNAME_SZ];
   _SQLOLDCHAR    applid[SQLXA_APPLID_SZ];
   _SQLOLDCHAR    sequence_no[SQLXA_SEQ_SZ];
   _SQLOLDCHAR    auth_id[SQLXA_USERID_SZ];
   char           log_full;                    /* SQLXA_TRUE/FALSE */
   char           connected;                   /* SQLXA_TRUE/FALSE */
   char           indoubt_status;              /* SQLXA_TS_xxx     */
   char           originator;                  /* SQLXA_ORIG_PE/XA */
   char           reserved[8];                 /* set to zeroes    */
   } SQLXA_RECOVER;

/**** reason codes for the SQL_RC_W997 general XA warning code */
#define SQLXAER_REASON_DEADLOCK  1  /* returned when XA_END clears a deadlock */
#define SQLXAER_REASON_RDONLYCOM 35 /* trans read-only and has been committed */

/**** reason codes for the SQL_RC_E998 general XA error sqlcode */
#define SQLXAER_REASON_ASYNC    1 /* asynch operation already outstanding     */
#define SQLXAER_REASON_RMERR    2 /* an RM error occurred                     */
#define SQLXAER_REASON_NOTA     3 /* XID not recognized                       */
#define SQLXAER_REASON_INVAL    4 /* invalid parameters                       */
#define SQLXAER_REASON_PROTO    5 /* routine called in improper context       */
#define SQLXAER_REASON_RMFAIL   6 /* RM unavailable                           */
#define SQLXAER_REASON_DUPID    7 /* the XID already exists                   */
#define SQLXAER_REASON_OUTSIDE  8 /* RM doing work outside global transaction */
#define SQLXAER_REASON_AXREG    9 /* axreg failed                             */
#define SQLXAER_REASON_1LUW    10 /* trying to start new trans while suspended*/
#define SQLXAER_REASON_NOJOIN  11 /* can't joing work of existing transaction */
#define SQLXAER_REASON_AXUNREG 12 /* axunreg failed                           */
#define SQLXAER_REASON_BADAX   13 /* ax interface failure (unresolved symbol) */
#define SQLXAER_REASON_NOHEUR  35 /* heuristic operaion invalid for non-XA db */
#define SQLXAER_REASON_BADXID  36 /* XID not knowne by the RM                 */
#define SQLXAER_REASON_HEURCOM 37 /* trans already heuristically commited     */
#define SQLXAER_REASON_HEURROL 38 /* trans already heuristically rolled back  */
#define SQLXAER_REASON_NOTINDT 39 /* not an indoubt transaction               */
#define SQLXAER_REASON_NOTSUPP 40 /* operation not supported                  */

/**** subcodes for the SQL_RC_E998 general XA error sqlcode */
#define SQLXAER_SUBCODE_XAINFO_INVALID                 1
#define SQLXAER_SUBCODE_DBNAME_TOO_LONG                2
#define SQLXAER_SUBCODE_USERID_TOO_LONG                3
#define SQLXAER_SUBCODE_PASSWD_TOO_LONG                4
#define SQLXAER_SUBCODE_USERID_NO_PASSWD               5
#define SQLXAER_SUBCODE_PASSWD_NO_USERID               6
#define SQLXAER_SUBCODE_TOO_MANY_PARMS                 7
#define SQLXAER_SUBCODE_RMID_NOT_MATCH_DBNAME          8
#define SQLXAER_SUBCODE_DBNAME_NOT_SPECIFIED           9                         /* +SAM */
#define SQLXAER_SUBCODE_INVALID_EXE_TYPE               10

/**** reason codes for the SQL_RC_E30090 general XA error code */
#define SQLXAER_REASON_READONLY 1  /* update issued against readonly database */
#define SQLXAER_REASON_BADAPI   2  /* This API not allowed                    */
#define SQLXAER_REASON_CANTHOLD 3  /* HELD CURSOR not allowed                 */


/*** prototypes for the heuristic API's in sqlxapi.c *************/

extern int SQL_API_FN sqlxphqr(    /* query existing indoubt transactions  */
   int                  exe_type,
   SQLXA_RECOVER        **ppIndoubtData,
   long                 *pNumIndoubts,
   struct sqlca         *pSqlca
   );

extern int SQL_API_FN sqlxphcm(    /* heuristically commit a transaction   */
   int                  exe_type,
   SQLXA_XID            *pTransId,
   struct sqlca         *pSqlca
   );

extern int SQL_API_FN sqlxphrl(    /* heuristically rollback a transaction */
   int                  exe_type,
   SQLXA_XID            *pTransId,
   struct sqlca         *pSqlca
   );

extern int SQL_API_FN sqlxhfrg(    /* heuristically forget a transaction   */
   SQLXA_XID            *pTransId,
   struct sqlca         *pSqlca
   );

/*** map old api to new ones ***/
#define sqlxhqry(_ppIndoubtData, _pNumIndoubts, _pSqlca) \
        sqlxphqr(SQLXA_EXE_THIS_NODE, _ppIndoubtData, _pNumIndoubts, _pSqlca)

#define sqlxhcom(_pTransId, _pSqlca) \
        sqlxphcm(SQLXA_EXE_THIS_NODE, _pTransId, _pSqlca)

#define sqlxhrol(_pTransId, _pSqlca) \
        sqlxphrl(SQLXA_EXE_THIS_NODE, _pTransId, _pSqlca)

                                                                    /*@fb33569rjp*/
/*
 * The following structure is used to describe the current state
 * of a DRDA indoubt transaction.
 */

#define SQLCSPQY_DBNAME_SZ       8
#define SQLCSPQY_LUWID_SZ       35
#define SQLCSPQY_LUNAME_SZ      17
#define SQLCSPQY_APPLID_SZ      32

#define SQLCSPQY_AR             'R'
#define SQLCSPQY_AS             'S'

#define SQLCSPQY_STATUS_COM     'C'
#define SQLCSPQY_STATUS_RBK     'R'
#define SQLCSPQY_STATUS_IDB     'I'
#define SQLCSPQY_STATUS_HCM     'X'
#define SQLCSPQY_STATUS_HRB     'Y'

typedef struct sqlcspqy_indoubt_t {
   SQLXA_XID    xid;
   char         luwid[SQLCSPQY_LUWID_SZ+1];
   char         corrtok[SQLCSPQY_APPLID_SZ+1];
   char         partner[SQLCSPQY_LUNAME_SZ+1];
   char         dbname[SQLCSPQY_DBNAME_SZ+1];
   char         dbalias[SQLCSPQY_DBNAME_SZ+1];
   char         role;
   char         uow_status;
   char         partner_status;
} SQLCSPQY_INDOUBT;

/* function prototype for list DRDA indoubt transactions */

extern int SQL_API_FN sqlcspqy(SQLCSPQY_INDOUBT     **indoubt_data,
                               long                  *indoubt_count,
                               struct sqlca          *sqlca);

#if (defined(DB2OS2) || defined(DB2NT) || defined(DB2WIN))
#pragma pack()
#elif (defined(DB2MAC))
#pragma align
#elif (defined(DB2HP) || defined(DB2SNI))

#elif (defined(DB2AIX) || defined(DB2SUN))
#pragma options align=reset
#endif

#ifdef __cplusplus
}
#endif

#endif /* SQL_H_SQLXA */
