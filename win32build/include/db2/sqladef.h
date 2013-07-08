/******************************************************************************
 *
 * Source File Name = SQLADEF.H
 *
 * (C) COPYRIGHT International Business Machines Corp. 1993, 1997
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * Function = Include File defining:
 *              Information for Precompiler Generated C Files
 *
 * Operating System = Common C Include File
 *
 *****************************************************************************/

#ifndef SQL_H_SQLADEF
   #define SQL_H_SQLADEF           /* Permit duplicate Includes */

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>                /* Required when using DBCLOBs */
#include "sqlsystm.h"              /* System dependent defines  */

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

/* Macros for initializing LOB declarations. */
#define SQL_BLOB_INIT(s)   { sizeof(s)-1,     s }
#define SQL_CLOB_INIT(s)   { sizeof(s)-1,     s }
#define SQL_DBCLOB_INIT(s) { (sizeof(s)/2)-1, s }

#ifndef SQL_SQLDBCHAR_DEFN
#define SQL_SQLDBCHAR_DEFN
  typedef unsigned short sqldbchar;
#endif

struct sqla_runtime_info
{
  char           id[8];
  unsigned short wc_size;
  unsigned short wc_type;
  char           unused[4];
};

/* Prototypes for Runtime API's */
struct sqlca;

struct sqlda;

struct sqla_setd_list
{
  unsigned short  sqltype;            /* SQL data type   */
  unsigned long   sqllen;             /* declared length */
  void           *sqldata;            /* address of host var */
  short          *sqlind;             /* address of ind. var */
};

SQL_API_RC SQL_API_FN  sqlaaloc(unsigned short,
                                unsigned short,
                                unsigned short,
                                void *);

SQL_API_RC SQL_API_FN  sqlacall(unsigned short,
                                unsigned short,
                                unsigned short,
                                unsigned short,
                                void *);

SQL_API_RC SQL_API_FN  sqlacmpd(unsigned short,
                                unsigned short,
                                unsigned short,
                                unsigned short,
                                void *);

SQL_API_RC SQL_API_FN  sqladloc(unsigned short,
                                void *);

SQL_API_RC SQL_API_FN  sqlasetd(unsigned short,
                                unsigned short,
                                unsigned short,
                                struct sqla_setd_list *,
                                void *);

/*
** NOTE: sqlasets has been obsoleted in favor of sqlastls, and will
** be going away in a future release.
*/
SQL_API_RC SQL_API_FN  sqlasets(unsigned short,
                                const void *,
                                void *);

SQL_API_RC SQL_API_FN  sqlastls(unsigned long,
                                const void *,
                                void *);

/*
** NOTE: sqlasetv has been obsoleted in favor of sqlastlv, and will
** be going away in a future release.
*/
SQL_API_RC SQL_API_FN  sqlasetv(unsigned short,
                                unsigned short,
                                unsigned short,
                                unsigned short,
                                void  *,
                                short *,
                                void  *);

SQL_API_RC SQL_API_FN  sqlastlv(unsigned short,
                                unsigned short,
                                unsigned short,
                                unsigned long,
                                void *,
                                short *,
                                void *);

SQL_API_RC SQL_API_FN  sqlastop(void *);

SQL_API_RC SQL_API_FN  sqlastrt(char[40],
                                struct sqla_runtime_info *,
                                struct sqlca *);

SQL_API_RC SQL_API_FN  sqlausda(unsigned short,
                                struct sqlda *,
                                void *);

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

#endif  /* SQL_H_SQLADEF */
