/******************************************************************************
 *
 * Source File Name = SQLCA.H
 *
 * (C) COPYRIGHT International Business Machines Corp. 1987, 1997
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * Function = Include File defining:
 *              SQL Communications Area
 *
 * Operating System = Common C Include File
 *
 *****************************************************************************/


#if !(defined(SQLCODE) || defined(SQLCADE)) /* Permit Duplicate Includes  */

#include "sqlsystm.h"                      /* System dependent defines   */

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

/* SQL Communication Area - SQLCA */
/* _SQLOLDCHAR defaults to 'char'.  See sqlsystm.h for details. */

SQL_STRUCTURE  sqlca
{
   _SQLOLDCHAR    sqlcaid[8];           /* Eyecatcher = 'SQLCA   '        */
   long           sqlcabc;              /* SQLCA size in bytes = 136      */
#ifdef DB2_SQL92E
   long           sqlcade;               /* SQL return code                */
#else
   long           sqlcode;              /* SQL return code                */
#endif
   short          sqlerrml;             /* Length for SQLERRMC            */
   _SQLOLDCHAR    sqlerrmc[70];         /* Error message tokens           */

   _SQLOLDCHAR    sqlerrp[8];           /* Diagnostic information         */

   long           sqlerrd[6];           /* Diagnostic information         */
   _SQLOLDCHAR    sqlwarn[11];          /* Warning flags                  */

#ifdef DB2_SQL92E
   _SQLOLDCHAR    sqlstat[5];           /* State corresponding to SQLCODE */
#else
   _SQLOLDCHAR    sqlstate[5];          /* State corresponding to SQLCODE */
#endif

};

#ifdef DB2_SQL92E
#define   SQLCADE        sqlca.sqlcade
#else
#define   SQLCODE        sqlca.sqlcode
#endif
#define   SQLWARN0       sqlca.sqlwarn[0]
#define   SQLWARN1       sqlca.sqlwarn[1]
#define   SQLWARN2       sqlca.sqlwarn[2]
#define   SQLWARN3       sqlca.sqlwarn[3]
#define   SQLWARN4       sqlca.sqlwarn[4]
#define   SQLWARN5       sqlca.sqlwarn[5]
#define   SQLWARN6       sqlca.sqlwarn[6]
#define   SQLWARN7       sqlca.sqlwarn[7]
#define   SQLWARN8       sqlca.sqlwarn[8]
#define   SQLWARN9       sqlca.sqlwarn[9]
#define   SQLWARNA       sqlca.sqlwarn[10]


/* sqlerrd tokens updated when compound SQL statements processed */

#define   SQL_CMP_NA_ERRORS       1
#define   SQL_CMP_ROWS_AFFECTED   2
#define   SQL_CMP_STMTS_COMPLETED 3
#define   SQL_CMP_REF_INT_ROWS    4


/* sqlerrd tokens updated when CONNECT statements processed */

#define   SQL_CONNECT_DB_APP2DB_CONVFACTOR     0
#define   SQL_CONNECT_DB_DB2APP_CONVFACTOR     1
#define   SQL_CONNECT_DB_UPDATEABILITY_IN_UOW  2
#define   SQL_CONNECT_DB_COMMIT_TYPE           3


/* Values returned for sqlerrd[SQL_CONNECT_DB_UPDATEABILITY_IN_UOW]     */

#define   SQL_DB_UPDATEABLE                    1
#define   SQL_DB_READ_ONLY                     2


/* Values returned for sqlerrd[SQL_CONNECT_DB_COMMIT_TYPE]       */

#define   SQL_DB_ONE_PHASE_COMMIT              1
#define   SQL_DB_ONE_PHASE_READ_ONLY           2
#define   SQL_DB_TWO_PHASE_COMMIT              3

#if (defined(DB2OS2) || defined(DB2NT) || defined(DB2WIN))
#pragma pack()
#elif (defined(DB2MAC))
#pragma align
#elif (defined(DB2HP) || defined(DB2SNI))

#elif (defined(DB2AIX) || defined(DB2SUN))                       
#pragma options align=reset
#endif

#endif /* SQLCODE */
