/******************************************************************************
**
** Source File Name: SQLUV
**
** (C) COPYRIGHT International Business Machines Corp. 1995,1997
** All Rights Reserved
** Licensed Materials - Property of IBM
**
** US Government Users Restricted Rights - Use, duplication or
** disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
**
** Function = Include File defining:
**              Vendor - Constants
**              Vendor - Data Structures
**              Vendor - Function Prototypes
**              Vendor - Labels for SQLCODES
**
*******************************************************************************/
#ifndef SQLUV_INCLUDED
#define SQLUV_INCLUDED

#include "sqlutil.h"
#include "sqlenv.h"

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
** external defines for vendor unload and load APIs
*/

/*
** sqluvtun() callerac values
*/
#define SQLU_CALLERAC_UNLOAD_INIT         0
#define SQLU_CALLERAC_UNLOAD_COMPLETE_OK  2
#define SQLU_CALLERAC_UNLOAD_INTERNAL     5
#define SQLU_CALLERAC_UNLOAD_ABORT        9

/*
** sqluvtld() callerac values
*/
#define SQLU_CALLERAC_LOAD_INIT         0
#define SQLU_CALLERAC_LOAD_RESTART      1
#define SQLU_CALLERAC_LOAD_COMPLETE_OK  2
#define SQLU_CALLERAC_LOAD_INTERNAL     5
#define SQLU_CALLERAC_LOAD_ABORT        9
#define SQLU_CALLERAC_LOAD_INTERRUPT    10

/*
** sqluvtld() optype values
*/
#define SQLU_OPTYPE_LOAD_REPLACE 'R'
#define SQLU_OPTYPE_LOAD_INSERT  'I'

/*
** sqluvtld() copy_flag values
*/
#define SQLU_NO_COPY_MADE 0
#define SQLU_COPY_MADE    1

/*
** Backup and load copy image structures
*/

/* Eyecatcher strings
*/
#define SQLU_EYECAT_LEN  13
#define MEDIA_HEAD             "SQLUBRMEDHEAD "
#define OBJECT_HEAD            "SQLUBROBJHEAD "
#define BACKUP_TAIL            "SQLUBRCKTAIL  "
#define MH_TAIL                "SQLUBRMHTAIL  "

/*
** media header constants
*/
#define SQLU_DBNAME_SZ    8
#define SQLU_CMT_SZ       30
#define SQLU_LOGPATH_LEN  255

/* additional backup types - "external" backup types are defined in sqlutil.h
*/
#define SQLUB_LOAD_COPY  4
#define SQLUB_UNLOAD     5

#define SQLU_MEDIA_HEAD_RSRVD_SPACE   4096
typedef struct
{
   unsigned char           eyecat[16];                /* DBM B/R Media Header eyecatcher    */
                                             /* 'SQLUBRMEDHEAD' left justified,    */
                                             /* padded with blanks                 */
   unsigned char           serverDBAlias[SQLU_ALIAS_SZ+1];   /* Server database alias       */
   unsigned char           timestamp[SQLU_TIME_STAMP_LEN+1]; /* timestamp of backup         */
   SQL_PDB_NODE_TYPE       dbnode;                 /* My node number                     */
   unsigned char           db2instance[SQL_INSTNAME_SZ+1];   /* db2instance name            */
   unsigned char           pad2[1];
   unsigned short          sequence;                  /* The sequence number of this backup */
   unsigned char           pad3[2];
   unsigned long           size;                      /* Size of the B/R Media Header       */
   unsigned short          rel_id;                    /* DBM release id                     */
   unsigned char           serverDBName[SQLU_DBNAME_SZ+1];   /* Server database name        */
   unsigned char           pad5[1];
   unsigned long           db_seed;                   /* Database seed                      */
   signed short            com_codepage;              /* Database comment's codepage (volume) */
   unsigned char           comment[SQLU_CMT_SZ+1];    /* Database comment (volume)          */
   unsigned char           pad7[3];
   signed short            d_com_codepage;            /* Database comment's codepage (system) */
   unsigned char           d_comment[SQLU_CMT_SZ+1];  /* Database comment (system)          */
   unsigned char           authentication;            /* Database authentication value      */
   unsigned char           backup_mode;               /* Mode of the backup                 */
                                                      /* '0' = offline                      */
                                                      /* '1' = online                       */
   unsigned char           pad9[1];
   unsigned short          dbStatusFlags;             /* status flags such as:              */
                                                      /* SQLF_DBTN_CONSISTENT (111)         */
                                                      /* SQLF_DBTN_BACKUP_PENDING (112)     */
                                                      /* SQLF_DBTN_ROLLFWD_PENDING (113)    */
                                                      /* SQLF_DBTN_LOG_RETAIN_STATUS (114)  */
                                                      /* SQLF_DBTN_USER_EXIST_STATUS (115)  */

   unsigned char           bkp_granu;                 /* backup granularity:                */
                                                      /*     '0' =  database                */
   unsigned char           backup_type;               /* backup type:                       */
                                                      /*     '0' =  SQLUB_FULL              */
                                                      /*     '3' =  SQLUB_TABLESPAC         */
                                                      /*     '4' =  SQLUB_LOAD_COPY         */
                                                      /*     '5' =  SQLUB_UNLOAD            */
   struct sqledbcountryinfo dbcinfo;                  /* code page info                     */
   unsigned long           LogID;
   unsigned char           LogPath[SQLU_LOGPATH_LEN+5];
   unsigned long           backupBufferSize;          /* buffer size used during backup     */
                                                      /* Useful to determine restore buf    */
                                                      /* size. */
   unsigned long           sessions;                  /* number of sessions used for backup */
   unsigned long           length_mh2;                /* length of secondary media header   */
   unsigned char           *pmh2;                              /* pointer to secondary media header  */

   unsigned long           platform;                  /* Platform                           */
   unsigned short          systemCatsIncluded;        /* indicate if the system catalogs    */
                                                      /* are included in this backup        */
                                                      /* 0 = NO,  1 = YES                   */
   unsigned char           clientDBAlias[SQLU_ALIAS_SZ+1];/* Client database alias          */
   SQL_PDB_NODE_TYPE       cat_node;                  /* Catalog node number                */
} SQLUV_BMH;

/* Backup and copy image object Types
*/
#define SQLUDAT               0x00
#define SQLUINX               0x01
#define SQLULF                0x02
#define SQLULOB               0x03
#define SQLULOBA              0x04
#define SQLUCNF               0x07
#define SQLULOG               0x08
#define SQLULISTOFTABLESPACES 0x09
#define SQLUHISTORYFILE       0x0a
#define SQLUTABLESPACETABLE   0x0b
#define SQLUDMSTABLESPACEDATA 0x0c
#define SQLUBACKUPTAIL        0x0d
#define SQLUDMSLOBDATA        0x0e
#define SQLUDMSLONGDATA       0x0f
#define SQLUSMSLOBDATA        0x10
#define SQLUSMSLONGDATA       0x11
#define SQLUBUFFERPOOLFILE    0x12
#define SQLUSTARTBACKUPREC    0x13
#define SQLUBRGFILE           0xff

/* type def for parameters
*/
typedef unsigned short SQLU_TOKEN;
typedef unsigned char  SQLU_TYPE ;

/* Object Header Structure
*/

#define SQLU_OBJ_HEAD_RSRVD_SPACE   512
typedef struct sqluboh
{
     char           eyecat[16];    /* DBM B/R Object Header eyecatcher */
                                   /* 'SQLUBROBJHEAD '                 */
     unsigned long  size;          /* Size of the B/R Object Header    */
     unsigned long  objsize;       /* Size of the Object in bytes      */
     unsigned long  filesize;      /* bytes in the file                */
                                   /* Only used by special files       */
     unsigned short token;         /* Token of the object              */
     SQLU_TYPE      type;          /* Type of object                   */
     char           pad1[1];
     SQLU_TOKEN     backup_mode;   /* backup mode:                     */
                                   /* SQLUB_OFFLINE or SQLUB_ONLINE    */
     char           objname[SQL_LG_IDENT+SQL_SH_IDENT+2];
                                   /* schema.tablename                 */
     char           pad2[2];
     unsigned long  offset;        /* # of buffers into the file       */
     unsigned long  tableSpaceID;  /* Unique table space identifier    */
} SQLU_OH_T ;

/* Backup Tail Structure
*/
typedef struct sqlubtail
{
     char           eyecat[16];    /* DBM B/R Backup Tail eyecatcher    */
                                   /* 'SQLUBRBCKTAIL'                   */
     unsigned long  size;          /* Size of the Backup Tail structure */
     unsigned long  backupImagesUsed;
                                   /* Number of images created for the  */
                                   /* backup or copy                    */
} SQLUB_TAIL_T;

/*
** APIs to support vendor unload and load utilities
*/

SQL_API_RC  SQL_API_FN
    sqluvtun ( char          *table_name,      /* fully qualified table name */
               long           callerac,        /* caller action              */
               struct sqlu_media_list          /* list of media target       */
                             *copy_target_list,
               void          *reserve0,        /* reserve for internal use   */
               void          *reserve,         /* reserve for future use     */
               struct sqlca  *sqlca);          /* SQLCA                      */


SQL_API_RC  SQL_API_FN
    sqluvtld ( char           *table_name,      /* fully qualified table name */
               long            callerac,        /* caller action              */
               char            optype,          /* operation type             */
               long            copy_flag,       /* indicate copy is done      */
               struct sqlu_media_list
                              *src_location,    /* source location            */
               struct sqlu_media_list           /* list of media target       */
                              *media_list,
               SQLU_LSN       *lsn,             /* log sequence number        */
               SQLUV_BMH      *media_header,    /* media header for copy      */
               void           *reserve0,        /* reserved                   */
               void           *reserve,         /* reserve for future use     */
               struct sqlca   *sqlca);          /* SQLCA                      */

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

#endif  /* SQLUV_INCLUDED */
