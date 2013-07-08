/******************************************************************************
 *
 * Source File Name: SQLJACB.H
 *
 * (C) COPYRIGHT International Business Machines Corp. 1991, 1997
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * Function: Include File defining:
 *             Database Connection Services (DCS) Interface - Constants
 *             DCS Interface - SQLJ_ACBH, SQLJACB handle structure
 *             DCS Interface - SQLJACB, DCS Interface Control Block
 *
 * Operating System: Common C Include File
 *
 *****************************************************************************/

#ifndef  SQL_H_SQLJACB                  /* Permit duplicate includes */
   #define SQL_H_SQLJACB

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

/* Forward Declarations */
struct SQLERCB;

#define SQLJACB_TTL       "SQLJACB "    /* SQLJACB Title   */
#define SQLJACB_VER       0x0100        /* SQLJACB Version */

/* Connection type - SQLJ_ACBH.conn_type */

#define SQLJ_CONN_DRD1     1
#define SQLJ_CONN_ASP0     2
#define SQLJ_CONN_LOC      3
#define SQLJ_CONN_VNDR     5

/* ACB type - SQLJACB.sqlapcont */
#define SQLJALOC        0x00            /* Database is local to Application  */
#define SQLJAREM        0x01            /* Database is remote to Application */

/* ACB Connection States - SQLJACB.sqlapconst */
#define SQLJAINA        0x00000000      /* Application not connected        */
#define SQLJAIDL        0x00000001      /* Application is connected to DB   */
#define SQLJAREQ        0x00000003      /* SQL in progress, interrupt valid */
#define SQLJAERR        0x00000004      /* Connection in error state        */
#define SQLJRCVY        0x00000005      /* Connection in Recovery state     */
#define SQLJ_CONN_PAUS  0x00000009      /* Connection in Paused state       */
#define SQLJ_IN_LUW     0x00000010      /* In Logical Unit of Work.         */

/* ACB Connection Pending States - SQLJACB.sqlapconst */
#define SQLJAACT        0x00000000      /* Nothing Pending         */
#define SQLJASTA        0x00000100      /* Start Database Pending  */
#define SQLJASTO        0x00000200      /* Stop Database Pending   */
#define SQLJAINT        0x00000400      /* Request interrupted     */
#define SQLJ_PAUS_PEND  0x00000800      /* Pause Database Pending  */
#define SQLJ_DB_TERM    0x00001000      /* Database has Terminated */

/* ACB Information States - SQLJACB.sqlapconst */
#define SQLJLOCR        0x00000000      /* Local Request               */
#define SQLJREMR        0x00010000      /* Remote Request              */
#define SQLJBUSY        0x00020000      /* Cleanup already in progress */
#define SQLJBRWT        0x00040000      /* Backup/Restore waiting      */
                                        /* for user input              */

/* ACB Information States - SQLJACB.sqlapconst */
#define SQLJNOIN        0x00000000      /* No Info                     */
#define SQLJREST        0x01000000      /* Restart Request in Progress */
#define SQLJCDIP        0x02000000      /* Create Database in Progress */
#define SQLJBURS        0x04000000      /* Backup/Restore in Progress  */
#define SQLJMIGR        0x08000000      /* Migrate in Progress         */
#define SQLJBACK        0x10000000      /* Backup Only in Progress     */

/* ACB Information States - SQLJACB.sqlapcons2 */
#define SQLJTYP1        0x00000001      /* Connection is Type-1        */
#define SQLJTYP2        0x00000002      /* Connection is Type-2        */
#define SQLJDRD1        0x00000004      /* Connection is DRDA-1        */
#define SQLJDRD2        0x00000008      /* Connection is DRDA-2        */
#define SQLJREL         0x00000010      /* Connection is released      */
#define SQLJDORM        0x00000020      /* Connection is dormant       */

typedef struct sqlj_acb
{
   char                  sqlacbid[8];   /* Control block eye catcher */
   unsigned long         sqlacbsz;      /* Size in bytes             */
   unsigned short        sqlacbver;     /* Version number            */

   unsigned short        sqlnacb;       /* Reserved for Database Connection
                                           Router use only                  */
   /*************************************************************************/
   /* the following two pointer fields are in support of the                */
   /* Application connection set. Each SQLJACB is linked onto one           */
   /* of the synonym chains within the sqlecvt array in the                 */
   /* sqlerglob structure.                                                  */
   /*************************************************************************/
   struct sqlj_acb      *sqljfwd;       /* forward chain field              */
   struct sqlj_acb      *sqljback;      /* backward chain field             */
   short                 sqlhash;       /* index into sqlecvt               */
   /*************************************************************************/
   /* the database use, product signature and country code are              */
   /* moved from the sqlerglob to the sqljacb as they are attributes        */
   /* of the connection.                                                    */
   /*************************************************************************/
   char                  use;           /* database use                 */
   char                  prod_sig[8];   /* served product signature     */
   char                  dbcpcc[32];    /* Database  country and        */
                                        /* code page                    */
   unsigned short        sqlapcont;     /* Application connection type  */
   unsigned long         sqlapconst;    /* Application connection state */
   unsigned long         sqlapcons2;    /* Application connection       */
                                        /* state word 2                 */

/* Process and thread id */

   unsigned short        sqlappid;      /* Process ID of server process */
   unsigned short        sqlaptid;      /* Thread ID of server process  */

/* Codepages */

   unsigned short        sqlapcpg;      /* Codepage of originating
                                           application             */
   unsigned short        sqldbcpg;      /* Codepage of database    */

/* Datastream type */

   unsigned short        sqldtast;      /* Datastream type */

/* Originating Application node */

   unsigned long         sqlapnnl;      /* Length of application node name    */
   unsigned short        sqlapnnt;      /* Data type of application node name */
   void *                sqlapnn;       /* Pointer to application node name   */

/* Originating Application ID */

   unsigned long         sqlapidl;      /* Length of application id    */
   unsigned short        sqlapidt;      /* Data type of application id */
   void *                sqlapid;       /* Pointer to application id   */

/* Database Connection Router internal control block */

   unsigned long         sqlcrtcbl;     /* Length of Database Connection
                                           Router internal control block    */
   unsigned short        sqlcrtcbt;     /* Data type of Database Connection
                                           Router internal control block    */
   struct SQLERCB *      sqlcrtcb;      /* Pointer to Database Connection
                                           Router internal control block
                                           (Database Connection Router use
                                           only)                            */

/* Target internal control block */

   unsigned long         sqlcsvcbl;     /* Length of target internal control
                                           block                              */
   unsigned short        sqlcsvcbt;     /* Data type of target internal
                                           control block                      */
   void *                sqlcsvcb;      /* Pointer to target internal control
                                           block                              */

/* Userid */

   unsigned long         sqlusl;        /* Length of userid    */
   unsigned short        sqlust;        /* Data type of userid */
   char *                sqluser;       /* Pointer to userid   */

/* Alias name in system database directory */

   unsigned long         sqldball;      /* Length of alias name              */
   unsigned short        sqldbalt;      /* Data type of alias name           */
   char *                sqldbal;       /* Pointer to alias name of database
                                           in system database directory      */

/* Database name in system database directory */

   unsigned long         sqlldbnl;      /* Length of database name      */
   unsigned short        sqlldbnt;      /* Data type of database name   */
   char *                sqlldbn;       /* Pointer to name of database
                                           in system database directory */

/* Node name in system database directory */

   unsigned long         sqlnnl;        /* Length of node name            */
   unsigned short        sqlnnt;        /* Data type of node name         */
   char *                sqlnn;         /* Pointer to node name in system
                                           database directory             */

/* Database name in Database Connection Services directory */

   unsigned long         sqlsdbnl;      /* Length of database name            */
   unsigned short        sqlsdbnt;      /* Data type of database name         */
   char *                sqlsdbn;       /* Pointer to database name in Database
                                           Connection Services directory      */

/* Target library name */

   unsigned long         sqlpgmnl;      /* Length of library name        */
   unsigned short        sqlpgmnt;      /* Data type of library name     */
   char *                sqlpgmn;       /* Pointer to library name of
                                           target element                */

/* Parameter string */

   unsigned long         sqlparml;      /* Length of parameter string       */
   unsigned short        sqlparmt;      /* Data type of parameter string    */
   char *                sqlparm;       /* Pointer to parameter string from
                                           Database Connection Services
                                           directory                        */
/* Target element data heap */

   unsigned long         sqlrshpl;      /* Length of target data heap    */
   unsigned short        sqlrshpt;      /* Data type of target data heap */
   unsigned int  *       sqlrshp;       /* Pointer to target data heap   */

} SQLJACB;

#define SQLJ_LEN_SQLJACB sizeof(SQLJACB)

/* SQLJ_ACBH */

typedef struct sqlj_acbh
{
   long                handle;
   short               conn_type;       /* int to short  */
} SQLJ_ACBH;

#if (defined(DB2OS2) || defined(DB2NT) || defined(DB2WIN))
#pragma pack()
#elif (defined(DB2MAC))
#pragma align
#elif (defined(DB2HP) || defined(DB2SNI))

#elif (defined(DB2AIX) || defined(DB2SUN))                       
#pragma options align=reset
#endif

#endif /* SQL_H_SQLJACB */
