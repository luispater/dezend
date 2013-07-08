/******************************************************************************
 *
 * Source File Name = SQLMON.H
 *
 * (C) COPYRIGHT International Business Machines Corp. 1993, 1997
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * Function = Include File defining:
 *              Database System Monitor - Constants
 *              Database System Monitor - Structures
 *              Database System Monitor - Function Prototypes
 *
 * Operating System: Common C Include File
 *
 * Notes:
 *   structures returned as output to the 'Get Snapshot' function, 'sqlmonss()'
 *   are of the form: 'sqlm_xxxx', for example: sqlm_dbase.
 *
 *   sqlm_xxxx_event structures are logged to a trace by DB2 Event Monitors,
 *   which can be defined and activated using SQL commands (CREATE EVENT
 *   MONITOR, SET EVENT MONITOR).
 *
 *
 *****************************************************************************/

#ifndef  SQL_H_SQLMON
   #define SQL_H_SQLMON            /* Permit duplicate Includes */

#ifdef __cplusplus
extern "C" {
#endif

#include "sqlsystm.h"              /* System dependent defines     */
#include "sqlca.h"                 /* SQL API - Communication Area */
#include "sqlenv.h"                /* DB2 Environment commands     */

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

/******************************************************************************/
/* Database System Monitor Version (version, server_version)                  */
/******************************************************************************/
#define SQLM_DBMON_VERSION1  1
#define SQLM_DBMON_VERSION2  2
#define SQLM_DBMON_VERSION5  3
#define SQLM_CURRENT_VERSION SQLM_DBMON_VERSION5

/******************************************************************************/
/* Snapshot requests (sqlm_obj_struct.obj_type in sqlma)                      */
/******************************************************************************/

/* Database Manager snapshot */
#define SQLMA_DB2                 1      /* Database Manager information      */

/* List of connections */
#define SQLMA_DBASE_APPLINFO      7      /* List of connections to a database */
#define SQLMA_APPLINFO_ALL       11      /* List of connections to DB2        */
#define SQLMA_DCS_APPLINFO_ALL   12      /* List of DDCS connections to DB2   */

/* Database snapshot */
#define SQLMA_DBASE               2      /* Database level information        */
#define SQLMA_DBASE_ALL           9      /* DB info for all active databases  */

/* Application snapshot */
#define SQLMA_APPL_ALL           10      /* Appl level info - all connections */
#define SQLMA_APPL                3      /* Appl level info - for appl_id     */
#define SQLMA_AGENT_ID            4      /* Appl level info - for appl-handle */
#define SQLMA_DBASE_APPLS         6      /* Appl level info - all conns to db */

/* Table snapshot */
#define SQLMA_DBASE_TABLES        5      /* Table related info for a database */

/* Tablespace snapshot */
#define SQLMA_DBASE_TABLESPACES  13      /* Tablespace related info for dbase */

/* Snapshot for locks */
#define SQLMA_APPL_LOCKS          20  /* List of locks held - for appl_id     */
#define SQLMA_APPL_LOCKS_AGENT_ID 21  /* List of locks held - for appl-handle */
#define SQLMA_DBASE_LOCKS         8   /* List of locks - all appls for db     */

/* Bufferpool snapshot */
#define SQLMA_DBASE_BUFFERPOOLS   22     /* Bufferpool info - for a database  */
#define SQLMA_BUFFERPOOLS_ALL     23     /* Bufferpool info - all bufferpools */

/******************************************************************************/
/* Snapshot output structure type identifiers                                 */
/*                                                                            */
/* (info_type element in the sqlm_xxx structures that are returned in the     */
/* sqlmonss() output buffer.)                                                 */
/******************************************************************************/

#define SQLM_DB2_SS                '1'   /* DB2 info (sqlm_db2)               */
#define SQLM_FCM_SS                'E'   /* DB2 FCM info (sqlm_fcm)           */
#define SQLM_NODE_SS               'G'   /* DB2 FCM Node info (sqlm_fcm_node) */
#define SQLM_APPLINFO_SS           '4'   /* Summary appl info (sqlm_applinfo) */
#define SQLM_DCS_APPLINFO_SS       'A'   /* DCS appl info (sqlm_dcs_applinfo) */
#define SQLM_DBASE_SS              '2'   /* DB info (sqlm_dbase)              */
#define SQLM_TABLE_HEADER_SS       '5'   /* DB table info (sqlm_table_header) */
#define SQLM_TABLE_SS              '6'   /* Table info (sqlm_table)           */
#define SQLM_DBASE_LOCK_SS         '7'   /* DB lock info (sqlm_dbase_lock)    */
#define SQLM_APPL_LOCK_SS          '8'   /* Appl lock info (sqlm_appl_lock)   */
#define SQLM_LOCK_SS               '9'   /* Lock info (sqlm_lock)             */
#define SQLM_TABLESPACE_HEADER_SS  'B'  /* DB tspaces (sqlm_tablespace_header)*/
#define SQLM_TABLESPACE_SS         'C'   /* Tablespace info (sqlm_tablespace) */
#define SQLM_APPL_SS               '3'   /* Appl info (sqlm_appl)             */
#define SQLM_DBASE_ROLLFWD_SS      'H'   /* Rollfwd info  (sqlm_rollfwd_info) */
#define SQLM_DBASE_ROLLFWD_TS_SS   'I'   /* Rollfwd tablespace information
                                                (sqlm_rollfwd_ts_info)        */
#define SQLM_BUFFERPOOL_SS         'J'   /* Bufferpool info (sqlm_bufferpool) */
#define SQLM_LOCK_WAIT_SS          'K'   /* Lock wait info (sqlm_lock_wait)   */
#define SQLM_STMT_SS               'L'   /* Statement info (sqlm_stmt)        */
#define SQLM_SUBSECTION_SS         'M'   /* Subsection info (sqlm_subsection) */
#define SQLM_AGENT_SS              'N'   /* Agent info (sqlm_agent)           */

/******************************************************************************/
/* size constants                                                             */
/******************************************************************************/

#define SQLM_APPLID_SZ        32          /* size of the application id       */
#define SQLM_SEQ_SZ            4          /* sequence number size             */
#define SQLM_SH_IDENT_SZ       8          /* Small identifier size            */
#define SQLM_IDENT_SZ         20          /* General identifier size          */
#define SQLM_LG_IDENT_SZ      32          /* Long identifier size             */
#define SQLM_OBJECT_SZ        36          /* object size in sqlma structure   */
#define SQLM_DBPATH_SZ       256          /* Database Path size               */

/******************************************************************************/
/* Information group state switches (sqlmon and sqlmonss functions)           */
/******************************************************************************/

#define SQLM_OFF    0              /* Turn monitoring group OFF               */
#define SQLM_ON     1              /* Turn monitoring group ON                */
#define SQLM_HOLD   2              /* leave monitoring group in current state */

/******************************************************************************/
/* Monitor switches                                                           */
/******************************************************************************/

#define SQLM_UOW_SW          0           /* Unit of Work information          */
#define SQLM_STATEMENT_SW    1           /* Statement information             */
#define SQLM_TABLE_SW        2           /* Table information                 */
#define SQLM_BUFFER_POOL_SW  3           /* Buffer Pool information           */
#define SQLM_LOCK_SW         4           /* Lock information                  */
#define SQLM_SORT_SW         5           /* Sort information                  */

#define SQLM_NUM_GROUPS      6           /* number of monitor switches        */

/******************************************************************************/
/* Statement Types (stmt_type)                                                */
/******************************************************************************/
#define SQLM_STATIC            1         /* Static statement                  */
#define SQLM_DYNAMIC           2         /* Dynamic statement                 */
#define SQLM_NON_STMT          3         /* Operation other than an SQL stmt  */
#define SQLM_STMT_TYPE_UNKNOWN 4         /* Unknown statement type            */

/******************************************************************************/
/* Statement Operation Types (stmt_operation)                                 */
/******************************************************************************/
/* SQL operations */
#define SQLM_SELECT            15        /* SELECT statement                  */
#define SQLM_PREPARE            1        /* SQL Prepare                       */
#define SQLM_EXECUTE            2        /* SQL Execute                       */
#define SQLM_EXECUTE_IMMEDIATE  3        /* SQL Execute Immediate             */
#define SQLM_OPEN               4        /* SQL Open                          */
#define SQLM_FETCH              5        /* SQL Fetch                         */
#define SQLM_CLOSE              6        /* SQL Close                         */
#define SQLM_DESCRIBE           7        /* SQL Describe                      */
#define SQLM_STATIC_COMMIT      8        /* SQL Static Commit                 */
#define SQLM_STATIC_ROLLBACK    9        /* SQL Static Rollback               */
#define SQLM_FREE_LOCATOR      10        /* SQL Free Locator                  */
#define SQLM_PREP_COMMIT       11        /* Prepare to commit (2-phase commit)*/

/* non-SQL operations */
#define SQLM_RUNSTATS          20        /* Runstats                          */
#define SQLM_REORG             21        /* Reorg                             */
#define SQLM_REBIND            22        /* Rebind package                    */
#define SQLM_REDIST            23        /* Redistribute                      */
#define SQLM_GETTA             24        /* Get Table Authorization           */
#define SQLM_GETAA             25        /* Get Administrative Authorization  */

/******************************************************************************/
/* Table Types (table_type)                                                   */
/******************************************************************************/
#define SQLM_USER_TABLE      1           /* User table                        */
#define SQLM_DROPPED_TABLE   2           /* Dropped user table                */
#define SQLM_TEMP_TABLE      3           /* Temporary table                   */
#define SQLM_CATALOG_TABLE   4           /* System Catalog table              */
#define SQLM_REORG_TABLE     5           /* Reorg table                       */

/******************************************************************************/
/* lock modes (lock_mode)                                                     */
/******************************************************************************/

#define SQLM_LNON  0                  /*  No Lock                             */
#define SQLM_LOIS  1                  /*  Intention Share Lock                */
#define SQLM_LOIX  2                  /*  Intention Exclusive Lock            */
#define SQLM_LOOS  3                  /*  Share Lock                          */
#define SQLM_LSIX  4                  /*  Share with Intention Exclusive Lock */
#define SQLM_LOOX  5                  /*  Exclusive Lock                      */
#define SQLM_LOIN  6                  /*  Intent None (For Dirty Read)        */
#define SQLM_LOOZ  7                  /*  Super Exclusive Lock                */
#define SQLM_LOOU  8                  /*  Update Lock                         */
#define SQLM_LONS  9                  /*  Next-key Share Lock                 */
#define SQLM_LONX 10                  /*  Next-key Exclusive Lock             */
#define SQLM_LOOW 11                  /*  Weak Exclusive Lock                 */
#define SQLM_LONW 12                  /*  Next-key Weak Exclusive Lock        */

/******************************************************************************/
/* subsection status (ss_status)                                              */
/******************************************************************************/

#define SQLM_SSEXEC             1  /* Subsection executing                    */
#define SQLM_SSTQ_WAIT_TO_RCV   2  /* Waiting to receive data on a tablequeue */
#define SQLM_SSTQ_WAIT_TO_SEND  3  /* Waiting to send data on a tablequeue    */
#define SQLM_SSCOMPLETED        4  /* Subsection execution is completed       */

/******************************************************************************/
/* application status (appl_status)                                           */
/******************************************************************************/

#define SQLM_CONNECTPEND          1            /* connect pending             */
#define SQLM_CONNECTED            2            /* connect completed           */
#define SQLM_UOWEXEC              3            /* UOW executing               */
#define SQLM_UOWWAIT              4            /* UOW waiting                 */
#define SQLM_LOCKWAIT             5            /* lock wait                   */
#define SQLM_COMMIT_ACT           6            /* commit active               */
#define SQLM_ROLLBACK_ACT         7            /* rollback active             */
#define SQLM_RECOMP               8            /* recompiling a plan          */
#define SQLM_COMP                 9            /* compiling a SQL statement   */
#define SQLM_INTR                10            /* request interrupted         */
#define SQLM_DISCONNECTPEND      11            /* disconnect pending          */
#define SQLM_TPREP               12            /* Prepared transaction        */
#define SQLM_THCOMT              13            /* heuristically committed     */
#define SQLM_THABRT              14            /* heuristically rolled back   */
#define SQLM_TEND                15            /* Transaction ended           */
#define SQLM_CREATE_DB           16            /* Creating Database           */
#define SQLM_RESTART             17            /* Restarting a Database       */
#define SQLM_RESTORE             18            /* Restoring a Database        */
#define SQLM_BACKUP              19            /* Performing a Backup         */
#define SQLM_LOAD                20            /* Performing a fast load      */
#define SQLM_UNLOAD              21            /* Performing a fast unload    */
#define SQLM_IOERROR_WAIT        22            /* Wait to disable tablespace  */
#define SQLM_QUIESCE_TABLESPACE  23            /* Quiescing a tablespace      */

/******************************************************************************/
/* database status (db_status)                                                */
/******************************************************************************/

#define SQLM_DB_ACTIVE          0              /* Database is active          */
#define SQLM_DB_QUIESCE_PEND    1              /* Quiesce is pending for DB   */
#define SQLM_DB_QUIESCED        2              /* Database has been quiesced  */
#define SQLM_DB_ROLLFWD         3              /* DB in Database rollforward  */

/******************************************************************************/
/* rollforward types (rf_type)                                                */
/******************************************************************************/
#define SQLM_ROLLFWD_TYP_DB        0  /* Database rollforward                */
#define SQLM_ROLLFWD_TYP_TSPACE    1  /* DB tablespace (on-line) rollforward */
#define SQLM_NO_ROLLFWD            2  /* No rollforward in progress          */

/******************************************************************************/
/* Rollforward status (rf_status)                                             */
/******************************************************************************/
#define SQLM_ROLLFWD_STATUS_REDO     0  /* REDO phase in progress */
#define SQLM_ROLLFWD_STATUS_UNDO     1  /* UNDO phase in progress */
#define SQLM_ROLLFWD_STATUS_SUCCESS  2  /* Successfuly completed on this node */
#define SQLM_ROLLFWD_STATUS_ERROR    3  /* Error occurred on this node */
#define SQLM_ROLLFWD_STATUS_USR_INTR 4  /* User intervention required */


/******************************************************************************/
/* database manager status  (db2_status)                                      */
/******************************************************************************/

#define SQLM_DB2_ACTIVE          0             /* DB2 is active               */
#define SQLM_DB2_QUIESCE_PEND    1             /* Quiesce is pending for DB2  */
#define SQLM_DB2_QUIESCED        2             /* DB2 has been quiesced       */

/******************************************************************************/
/* UOW completion status (uow_comp_status)                                    */
/******************************************************************************/

#define SQLM_UOWCOMMIT       1       /* UOW issued a commit                   */
#define SQLM_UOWROLLBACK     2       /* UOW issued a rollback                 */
#define SQLM_UOWDEADLOCK     3       /* UOW was rolled back due to a deadlock */
#define SQLM_UOWABEND        4       /* UOW was rolled back due to an abend   */
#define SQLM_APPL_END        5       /* application normal termination        */
#define SQLM_UOWLOCKTIMEOUT  6       /* UOW was rolled back from lock timeout */

/******************************************************************************/
/* lock object type (lock_object_type)                                        */
/******************************************************************************/

#define SQLM_TABLE_LOCK       1          /* table lock type                   */
#define SQLM_ROW_LOCK         2          /* table row lock type               */
#define SQLM_INTERNAL_LOCK    3          /* Internal lock type                */
#define SQLM_TABLESPACE_LOCK  4          /* Tablespace lock type              */
#define SQLM_EOT_LOCK         5          /* end of table lock                 */
#define SQLM_KEYVALUE_LOCK    6          /* key value lock                    */

/******************************************************************************/
/* lock status (lock_status)                                                  */
/******************************************************************************/

#define SQLM_LRBGRNT      1                     /*  Granted State             */
#define SQLM_LRBCONV      2                     /*  Converting state          */

/******************************************************************************/
/* client communications protocols (client_protocol)                          */
/******************************************************************************/
#define SQLM_PROT_APPC         SQL_PROTOCOL_APPC    /* appc                   */
#define SQLM_PROT_NETBIOS      SQL_PROTOCOL_NETB    /* netbios                */
#define SQLM_PROT_APPN         SQL_PROTOCOL_APPN    /* appn                   */
#define SQLM_PROT_TCPIP        SQL_PROTOCOL_TCPIP   /* tcp/ip                 */
#define SQLM_PROT_CPIC         SQL_PROTOCOL_CPIC    /* APPC using CPIC        */
#define SQLM_PROT_IPXSPX       SQL_PROTOCOL_IPXSPX  /* ipx/spx                */
#define SQLM_PROT_LOCAL        SQL_PROTOCOL_LOCAL   /* local client           */
#define SQLM_PROT_NPIPE        SQL_PROTOCOL_NPIPE   /* Named pipe             */


/******************************************************************************/
/* Operating Systems (client_platform and server_platform)                    */
/******************************************************************************/
#define SQLM_PLATFORM_UNKNOWN         0         /* Unknown platform           */
#define SQLM_PLATFORM_OS2             1         /* OS/2                       */
#define SQLM_PLATFORM_DOS             2         /* DOS                        */
#define SQLM_PLATFORM_WINDOWS         3         /* Windows                    */
#define SQLM_PLATFORM_AIX             4         /* AIX                        */
#define SQLM_PLATFORM_NT              5         /* NT                         */
#define SQLM_PLATFORM_HP              6         /* HP                         */
#define SQLM_PLATFORM_SUN             7         /* Sun                        */
#define SQLM_PLATFORM_MVS_DRDA        8         /* MVS (client via DRDA)      */
#define SQLM_PLATFORM_AS400_DRDA      9         /* AS400 (client via DRDA)    */
#define SQLM_PLATFORM_VM_DRDA        10         /* VM (client via DRDA)       */
#define SQLM_PLATFORM_VSE_DRDA       11         /* VSE (client via DRDA)      */
#define SQLM_PLATFORM_UNKNOWN_DRDA   12         /* Unknown DRDA Client        */
#define SQLM_PLATFORM_SNI            13         /* Siemens Nixdorf            */
#define SQLM_PLATFORM_MAC            14         /* Macintosh Client           */
#define SQLM_PLATFORM_WINDOWS95      15         /* Windows 95                 */
#define SQLM_PLATFORM_SCO            16         /* SCO                        */
#define SQLM_PLATFORM_SGI            17         /* Silicon Graphic            */

/******************************************************************************/
/* Operating System Application Priority Type (appl_priority_type)            */
/******************************************************************************/
#define SQLM_FIXED_PRIORITY    1         /* Remains unchanged over time       */
#define SQLM_DYNAMIC_PRIORITY  2         /* Recalculated by OS based on usage */

/******************************************************************************/
/* Event Monitor Record Type Identifiers  (sqlm_event_rec_header.type)        */
/*                                                                            */
/* Used to read the records in a trace produced by an Event Monitor           */
/******************************************************************************/
#define SQLM_EVENT_DB               1  /* Database Event                      */
#define SQLM_EVENT_CONN             2  /* Connection Event                    */
#define SQLM_EVENT_TABLE            3  /* Table Event                         */
#define SQLM_EVENT_STMT             4  /* Statement Event                     */
#define SQLM_EVENT_STMTTEXT         5  /* Dynamic Statement Text (OBSOLETE)   */
#define SQLM_EVENT_XACT             6  /* Transaction Event                   */
#define SQLM_EVENT_DEADLOCK         7  /* Deadlock Event                      */
#define SQLM_EVENT_DLCONN           8  /* Deadlock Connection Event           */
#define SQLM_EVENT_TABLESPACE       9  /* Tablespace Event                    */
#define SQLM_EVENT_DBHEADER        10  /* Database Header Event               */
#define SQLM_EVENT_START           11  /* Event monitor start Event           */
#define SQLM_EVENT_CONNHEADER      12  /* Connection Header Event             */
#define SQLM_EVENT_OVERFLOW        13  /* Overflow Event                      */
#define SQLM_EVENT_BUFFERPOOL      14  /* Bufferpool Event                    */
#define SQLM_EVENT_SUBSECTION      15  /* Subsection Event (MPP systems)      */

/******************************************************************************/
/* Event Monitor Byte Order Identifiers (byte_order)                          */
/******************************************************************************/
#define SQLM_LITTLE_ENDIAN      0         /* Little endian server             */
#define SQLM_BIG_ENDIAN        -1         /* Big endian server                */

/******************************************************************************/
/* Database Monitor Error Constants (sqlcode)                                 */
/******************************************************************************/
#define SQLM_RC_INV_PTR         -1601 /* Parameter is a NULL pointer          */
#define SQLM_RC_INV_OBJ_TYPE    -1602 /* invalid obj_type in sqlma struct     */
#define SQLM_RC_NOT_SPECIFIED   -1603 /* dbname/appl_id not specified in sqlma*/
#define SQLM_RC_NOT_NULL_TERM   -1604 /* dbname/appl_id not NULL terminated   */
#define SQLM_RC_DBNOACT         +1605 /* database is not active               */
#define SQLM_RC_BUFFER_FULL     +1606 /* DBMON buffer area is full            */
#define SQLM_RC_NOMEM           -1607 /* not enough working memory for DBMON  */
#define SQLM_RC_DUPLICATE_DB    +1608 /* duplicate database aliases           */
#define SQLM_RC_REMOTE_DB       -1609 /* cannot monitor remote databases      */
#define SQLM_RC_INV_VALUE       -1610 /* invalid value for input parameter    */
#define SQLM_RC_NO_DATA         +1611 /* No data returned by Database Monitor */
#define SQLM_RC_TOO_MANY_OBJECTS -1623/* Too many objects for this request.   */
#define SQLM_RC_MULTIPLE_NODES  -1624 /* Databases in a sqlmonsz or sqlmonss  */
                                      /* call reside at different nodes.      */

/******************************************************************************/
/* FCM Connection Status (connection_status)                                  */
/******************************************************************************/
#define SQLM_FCM_CONNECT_INACTIVE    0         /* No current connection       */
#define SQLM_FCM_CONNECT_ACTIVE      1         /* Connection is active        */
#define SQLM_FCM_CONNECT_CONGESTED   2         /* Connection is congested     */

/******************************************************************************/
/* Database location relative to snapshot application (db_location)           */
/******************************************************************************/
#define SQLM_LOCAL                   1         /* Same node as snapshot       */
#define SQLM_REMOTE                  2         /* DB is on a different node   */

/******************************************************************************/
/******************************************************************************/
/* Database System Monitor data structures                                    */
/******************************************************************************/
/******************************************************************************/

/******************************************************************************/
/* Timestamp                                                                  */
/******************************************************************************/
typedef struct sqlm_timestamp
{
  unsigned long seconds;          /* GMT time in seconds since Jan.1,1970     */
  unsigned long microsec;         /* microseconds, range 0 to 999999          */
}sqlm_timestamp;

/******************************************************************************/
/* Elpased time (for CPU times)                                               */
/******************************************************************************/
typedef struct sqlm_time
{
  unsigned long seconds;           /* elapsed seconds                         */
  unsigned long microsec;          /* elapsed microseconds, range 0 to 999999 */
}sqlm_time;

/******************************************************************************/
/******************************************************************************/
/* Snapshot Monitoring API (sqlmonss, sqlmon, sqlmrset) data structures       */
/******************************************************************************/
/******************************************************************************/

/******************************************************************************/
/*  Snapshot Object Structure - Specifies a snapshot request (sqlmonss input) */
/*                                                                            */
/*  Specifies what information to collect (e.g., list of locks) for a given   */
/*  object, such as a database or an application.                             */
/*                                                                            */
/*  note: 'agent_id', and 'object' are required, only if applicable for the   */
/*        request type, and are mutually exclusive.                           */
/*        For example: a database name is required when the type is           */
/*        SQLMA_DBASE_LOCKS (get snapshot for locks on database), whereas     */
/*        an agent_id is required when the type is SQLMA_APPL_LOCKS_AGENT_ID. */
/*        Note that AGENT ID is the *APPLICATION HANDLE* of an application,   */
/*        which can be retrieved with an SQLMA_APPLINFO_ALL (list             */
/*        applications) request. It does not correspond to any Operating      */
/*        System process id. (It is named 'agent' for source compatibility    */
/*        with older releases of DB2.                                         */
/*                                                                            */
/*        Both agent_id and object are ignored for requests such              */
/*        as SQLMA_APPLINFO_ALL (list applications).                          */
/******************************************************************************/
typedef struct sqlm_obj_struct      /* specifies a snapshot request           */
{
   unsigned long agent_id;          /* used for requests based on appl-handle */
   unsigned long obj_type;          /* Snapshot Request Type (SQLMA_XXXX)     */
   _SQLOLDCHAR   object[SQLM_OBJECT_SZ];/* used for requests based on object  */
                                 /* name, such as 'get snapshot for database' */
}sqlm_obj_struct;

/******************************************************************************/
/*  SQL Monitor Area  - A list of snapshot requests - (sqlmonss input)        */
/******************************************************************************/
typedef struct sqlma
{
   unsigned long obj_num;     /* number of snapshot requests */
   sqlm_obj_struct obj_var[1];/* A req: which object and what info to collect */
}sqlma;

/******************************************************************************/
/* macro for estimating SQLMA size (use to allocate an sqlma)                 */
/* where 'n' is the number of requests for the snapshot                       */
/******************************************************************************/
#define SQLMASIZE(n) (sizeof(struct sqlma)+(n-1)*(sizeof(struct sqlm_obj_struct)) )

/******************************************************************************/
/* Monitor Switch status                                                      */
/******************************************************************************/
typedef struct sqlm_recording_group
{
  unsigned long  input_state;        /* input state to set group (sqlmon())   */
  unsigned long  output_state;       /* returned current state                */
  sqlm_timestamp start_time;         /* monitor switch set time               */
}sqlm_recording_group;

/******************************************************************************/
/* sqlmonss output                                                            */
/******************************************************************************/
typedef struct sqlm_collected
{
  unsigned long  size;            /* size of sqlm_collected                   */

  unsigned long  db2;             /* OBSOLETE - use num_top_level_structs     */
  unsigned long  databases;       /* OBSOLETE - use num_top_level_structs     */
  unsigned long  table_databases; /* OBSOLETE - use num_top_level_structs     */
  unsigned long  lock_databases;  /* OBSOLETE - use num_top_level_structs     */
  unsigned long  applications;    /* OBSOLETE - use num_top_level_structs     */
  unsigned long  applinfos;       /* OBSOLETE - use num_top_level_structs     */
  unsigned long  dcs_applinfos;   /* OBSOLETE - use num_top_level_structs     */

  unsigned long  server_db2_type; /* Server DB2 Type (defined in sqlutil.h)   */
  sqlm_timestamp time_stamp;      /* Snapshot time                            */
  sqlm_recording_group group_states[SQLM_NUM_GROUPS];/* current sw settings   */
  _SQLOLDCHAR    server_prdid[SQLM_IDENT_SZ]; /* product/version on server    */
  _SQLOLDCHAR    server_nname[SQLM_IDENT_SZ]; /* Config NNAME of server       */
  _SQLOLDCHAR    server_instance_name[SQLM_IDENT_SZ]; /* instance name of DB2 */
  _SQLOLDCHAR    reserved[22];         /* reserved for future use  */
  unsigned short node_number;          /* Node sending data                */
  long           time_zone_disp; /* Diff. in secs between GMT and local time  */
  unsigned long  num_top_level_structs; /* # of high level structs returned */
  unsigned long  tablespace_databases; /* OBSOLETE: use num_top_level_structs */
  unsigned long  server_version;       /* Version of server returning data    */
}sqlm_collected;

/******************************************************************************/
/******************************************************************************/
/* The following are returned in the sqlmonss (user supplied) output buffer:  */
/******************************************************************************/
/******************************************************************************/

/******************************************************************************/
/* Application Identification Information                                     */
/******************************************************************************/
typedef struct sqlm_appl_id_info
{
  unsigned long  agent_id;                   /* Application handle            */
  unsigned long  appl_status;                /* Application Status            */
  unsigned long  codepage_id;                /* codepage/CCSID at node        */
                                             /* where app started             */
  sqlm_timestamp status_change_time;         /* last appl status change time  */
  _SQLOLDCHAR    appl_name[SQLM_IDENT_SZ];   /* Application Program Name      */
  _SQLOLDCHAR    appl_id[SQLM_APPLID_SZ];    /* Application Id                */
  _SQLOLDCHAR    sequence_no[SQLM_SEQ_SZ];   /* application id sequence number*/
  _SQLOLDCHAR    auth_id[SQLM_IDENT_SZ];     /* Authorization Id              */
  _SQLOLDCHAR    client_nname[SQLM_IDENT_SZ]; /* Config NNAME of client       */
  _SQLOLDCHAR    client_prdid[SQLM_IDENT_SZ]; /* product/version on client    */
  _SQLOLDCHAR    input_db_alias[SQLM_IDENT_SZ]; /* Input Database Alias       */
  _SQLOLDCHAR    client_db_alias[SQLM_IDENT_SZ]; /* Client Database Alias     */
  _SQLOLDCHAR    db_name[SQLM_IDENT_SZ];     /* Database name                 */
  _SQLOLDCHAR    db_path[SQLM_DBPATH_SZ];    /* Database Path                 */
}sqlm_appl_id_info;

/******************************************************************************/
/* Application Id Information                                                 */
/******************************************************************************/
typedef struct sqlm_applinfo
{
  unsigned long  size;                       /* size of sqlm_applinfo         */
  _SQLOLDCHAR    info_type;                  /* Always set to SQLM_APPLINFO_SS*/
  _SQLOLDCHAR    pad[3];                     /* padding for 4 byte alignment  */
  sqlm_appl_id_info   id_info;               /* Identification information    */

  _SQLOLDCHAR    reserved[20];               /* reserved for future use       */
  unsigned long  num_assoc_agents;           /* Number of agents associated   */
                                             /* with this application         */
  unsigned long  coord_node_num;             /* Coordinating node number      */
  unsigned long  authority_lvl;              /* User authorizations           */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION2  Client Identification Information                   */
  /****************************************************************************/
  char           execution_id[SQLM_IDENT_SZ]; /* login ID */
  char           corr_token[SQLM_APPLID_SZ];  /* DRDA AS Correlation Token    */
  unsigned long  client_pid;           /* Process/thread ID of client appl.   */
  unsigned short client_platform;      /* Platform of client application      */
  unsigned short client_protocol;      /* Communications protocol of client   */
  unsigned short country_code;         /* Country code of client application  */
  char           pad2[2];
  long           coord_agent_pid;      /* Coordinator agent process/thread id */
}sqlm_applinfo;

/******************************************************************************/
/* DCS Application Identification Information                                 */
/******************************************************************************/
typedef struct sqlm_dcs_applinfo
{
  unsigned long  size;                       /* size of sqlm_dcs_applinfo     */
  _SQLOLDCHAR    info_type;                  /* set to SQLM_DCS_APPLINFO_SS   */
  _SQLOLDCHAR    pad[3];                     /* padding for 4 byte alignment  */
  unsigned long  agent_id;                   /* Application handle            */
  unsigned long  codepage_id;                /* codepage/CCSID at node        */
                                             /* where app started             */
  _SQLOLDCHAR    appl_name[SQLM_IDENT_SZ];   /* Application Program Name      */
  _SQLOLDCHAR    appl_id[SQLM_APPLID_SZ];    /* Application Id                */
  _SQLOLDCHAR    sequence_no[SQLM_SEQ_SZ];   /* application id sequence number*/
  _SQLOLDCHAR    auth_id[SQLM_IDENT_SZ];     /* Authorization Id              */
  _SQLOLDCHAR    client_nname[SQLM_IDENT_SZ]; /* Config NNAME of client       */
  _SQLOLDCHAR    client_prdid[SQLM_IDENT_SZ]; /* product/version on client    */
  _SQLOLDCHAR    client_db_alias[SQLM_IDENT_SZ]; /* Client Database Alias     */
  _SQLOLDCHAR    db_name[SQLM_IDENT_SZ];     /* Host Database name            */
  _SQLOLDCHAR    host_prdid[SQLM_IDENT_SZ];  /* Host Product id               */
  _SQLOLDCHAR    outbound_appl_id[SQLM_APPLID_SZ];   /* Outbound LUWID        */
  _SQLOLDCHAR    outbound_sequence_no[SQLM_SEQ_SZ];  /* Outbound sequence #   */
  _SQLOLDCHAR    reserved[32];               /* reserved for future use       */
}sqlm_dcs_applinfo;

/******************************************************************************/
/* Database manager Snapshot                                                  */
/******************************************************************************/
/* DB2 snapshot layout.  If running in a parallel environment,  'secondary'   */
/* level structures may also be returned.  For example:                       */
/*                                                                            */
/*      high-level struct      secondary-level                                */
/*  |------------+-----------|--------+--------|                              */
/*  +------------------------+-----------------+-------------+-------------+  */
/*  |sqlm_db2                |sqlm_fcm         |sqlm_fcm_node|sqlm_fcm_node|  */
/*  |  num_sec_dbm_structs: 1|  number_nodes: 2|             |             |  */
/*  +------------------------+-----------------+-------------+-------------+  */
/*----------------------------------------------------------------------------*/
typedef struct sqlm_db2
{
  unsigned long  size;                  /* size of sqlm_db2                   */
  _SQLOLDCHAR    info_type;             /* Always set to SQLM_DB2_SS          */
  _SQLOLDCHAR    pad1[3];               /* padding for 4 byte alignment       */

  /****************************************************************************/
  /* Sorting Information                                                      */
  /****************************************************************************/
  unsigned long  sort_heap_allocated;   /* Sort heap currently allocated      */
  unsigned long  post_threshold_sorts;  /* # sorts started after heap         */
                                        /* threshold exceeded                 */
  unsigned long  piped_sorts_requested; /* # of piped sorts requested         */
                                        /* by RDS to SLS                      */
  unsigned long  piped_sorts_accepted;  /* # of piped sorts accepted by SLS   */

  /****************************************************************************/
  /* Timestamps                                                               */
  /****************************************************************************/
  sqlm_timestamp db2start_time;          /* DB2START timestamp                */
  sqlm_timestamp last_reset;             /* Date/Time of Last Reset           */

  /****************************************************************************/
  /* Connection Information                                                   */
  /****************************************************************************/
  unsigned long  rem_cons_in;           /* Remote connects to target DB2      */
  unsigned long  rem_cons_in_exec;      /* Remote connects to target exec DB2 */
  unsigned long  local_cons;            /* Current Local Connections          */
  unsigned long  local_cons_in_exec;    /* Local connects curr exec in DB2    */
  unsigned long  con_local_dbases;      /* Local databases w/current connects */
  unsigned long  agents_registered;     /* Number of agents registered in DB2 */
  unsigned long  agents_waiting_on_token;   /* # of agents waiting on a token */

  /****************************************************************************/
  /* Server Switch settings - indicate if the DBMS is collecting monitor data */
  /****************************************************************************/
  unsigned char  dbmon_sw_settings[SQLM_NUM_GROUPS];     /* SQLM_OFF, SQLM_ON */
  char    pad2[2];                            /* padding for 4 byte alignment */
  unsigned long  dbmon_sw_set_time[SQLM_NUM_GROUPS];/* GMT time (in seconds)  */
                                  /* when switch was set - 0 if switch is OFF */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION2  DB2 Instance Status                                 */
  /****************************************************************************/
  unsigned long  db2_status;            /* status of the DB2 instance         */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION2  High Water Marks                                    */
  /****************************************************************************/
  unsigned long  agents_registered_top; /* agents_registered high water mark  */
  unsigned long  agents_waiting_top;    /* agents_waiting high water mark     */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION2  DB2 Instance Memory Usage Information               */
  /****************************************************************************/
  unsigned long  comm_private_mem;      /* Committed Private Memory           */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION2  Agent Information                                   */
  /****************************************************************************/
  unsigned long  idle_agents;           /* number of unassigned agents in pool*/

  /****************************************************************************/
  /* SQLM_DBMON_VERSION5  Agent Information                                   */
  /****************************************************************************/
  unsigned long  agents_from_pool;      /* # agents assigned from pool        */
  unsigned long  agents_created_empty_pool; /* # agents created because the   */
                                        /* pool was empty                     */
  unsigned long  coord_agents_top;      /* coordinating agents high water mark*/
  unsigned long  max_agent_overflows;   /* # of attempts to exceed the        */
                                        /* MAXAGENTS configuration parameter. */
  unsigned long  agents_stolen;         /* # agents stolen                    */
  unsigned long  num_sec_dbm_structs;   /* Secondary database manager info    */
  char product_name[SQLM_LG_IDENT_SZ];  /* Product Name                       */
  char component_id[SQLM_IDENT_SZ];     /* Product Identificiation            */
  char service_level[SQLM_SH_IDENT_SZ]; /* Service Level                      */
}sqlm_db2;

/******************************************************************************/
/* Fast Communication Manager (FCM) related Snapshot Information              */
/******************************************************************************/
typedef struct sqlm_fcm
{
  unsigned long  size;                  /* size of sqlm_fcm                   */
  _SQLOLDCHAR    info_type;             /* Always set to SQLM_FCM_SS          */
  _SQLOLDCHAR    pad1[3];               /* padding for 4 byte alignment       */

  /****************************************************************************/
  /* FCM Buffer Information                                                   */
  /****************************************************************************/
  unsigned long  buff_free;              /* # of FCM buffers free             */
  unsigned long  buff_free_bottom;       /* low water mark of buffers free    */

  /****************************************************************************/
  /* FCM Message Anchor Information                                           */
  /****************************************************************************/
  unsigned long  MA_free;                /* # of FCM message anchors free     */
  unsigned long  MA_free_bottom;         /* low water mark of anchors free    */

  /****************************************************************************/
  /* FCM Connection Entry Information                                         */
  /****************************************************************************/
  unsigned long  CE_free;                /* # of FCM connection entries free  */
  unsigned long  CE_free_bottom;         /* low water mark of free CEs        */

  /****************************************************************************/
  /* FCM Request Blocks Information                                           */
  /****************************************************************************/
  unsigned long  RB_free;                /* # of FCM request blocks free      */
  unsigned long  RB_free_bottom;         /* low water mark of free RBs        */

  /****************************************************************************/
  /* FCM Node Status Information                                              */
  /****************************************************************************/
  unsigned long  number_nodes;           /* # of FCM node structures which    */
                                         /* follow.                           */
}sqlm_fcm;

/******************************************************************************/
/* FCM Node Snapshot Information                                              */
/******************************************************************************/
typedef struct sqlm_fcm_node
{
  unsigned long  size;                  /* size of sqlm_fcm_node              */
  _SQLOLDCHAR    info_type;             /* Always set to SQLM_NODE_SS         */
  _SQLOLDCHAR    pad1[1];               /* padding for half-word aligment     */
  unsigned short node_number;           /* Remote node number                 */
  unsigned long  connection_status;     /* FCM Connnection status to node     */

  /****************************************************************************/
  /* FCM Buffer Counts                                                        */
  /****************************************************************************/
  unsigned long  total_buffers_sent;     /* Total # of buffers sent           */
  unsigned long  total_buffers_rcvd;     /* Total # of buffers received       */
}sqlm_fcm_node;

/******************************************************************************/
/* Database Snapshot                                                          */
/******************************************************************************/
/* Database snapshot layout. If a rollforward is in progress, a 'secondary'   */
/* level structure is also returned, for example:                             */
/*                                                                            */
/*          high-level struct        secondary-level                          */
/*      |------------+-------------|---------+---------|                      */
/*      +--------------------------+-------------------+--------------------+ */
/*      |sqlm_dbase                |sqlm_rollfwd_info  |sqlm_rollfwd_ts_info| */
/*      |  num_sec_dbase_structs: 1|  rf_num_tspaces: 1|                    | */
/*      +--------------------------+-------------------+--------------------+ */
/*----------------------------------------------------------------------------*/
typedef struct sqlm_dbase
{
  unsigned long  size;                  /* size of sqlm_dbase                 */
  _SQLOLDCHAR    info_type;             /* Always set to SQLM_DBASE_SS        */
  _SQLOLDCHAR    pad1[3];               /* padding for 4 byte alignment       */
  _SQLOLDCHAR    input_db_alias[SQLM_IDENT_SZ]; /* Input Database Alias       */
  _SQLOLDCHAR    db_name[SQLM_IDENT_SZ];        /* Database name              */
  _SQLOLDCHAR    db_path[SQLM_DBPATH_SZ];       /* Database Path              */

  /****************************************************************************/
  /* Locking Information                                                      */
  /****************************************************************************/
  unsigned long  locks_held;             /* Locks currently held              */
  unsigned long  lock_waits;             /* Lock waits since 1st connect      */
  unsigned long  lock_wait_time;         /* Total time dbase waited on locks  */
  unsigned long  lock_list_in_use;       /* total lock list memory in use     */
  unsigned long  deadlocks;              /* Deadlocks since 1st db connect    */
  unsigned long  lock_escals;            /* lock escals since 1st db connect  */
  unsigned long  x_lock_escals;          /* X lock escals since 1st db connect*/
  unsigned long  locks_waiting;          /* Agents currently waiting on locks */

  /****************************************************************************/
  /* Sorting Information                                                      */
  /****************************************************************************/
  unsigned long  sort_heap_allocated;    /* Total sort heap allocated         */
  unsigned long  total_sorts;            /* number of sorts since 1st connect */
  unsigned long  total_sort_time;        /* elapsed time spent in sorts       */
  unsigned long  sort_overflows;         /* number of sort overflows          */
  unsigned long  active_sorts;           /* sorts currently active            */

  /****************************************************************************/
  /* Buffer Pool Information                                                  */
  /****************************************************************************/
  unsigned long  pool_data_l_reads;      /* pool data logical reads since conn*/
  unsigned long  pool_data_p_reads;      /* pool data reads since 1st connect */
  unsigned long  pool_data_writes;       /* pool data writes since 1st connect*/
  unsigned long  pool_index_l_reads;     /* pool indx logical reads since conn*/
  unsigned long  pool_index_p_reads;     /* pool indx reads since 1st connect */
  unsigned long  pool_index_writes;      /* pool indx writes since 1st connect*/
  unsigned long  pool_read_time;         /* Buff pool read time since 1st conn*/
  unsigned long  pool_write_time;        /* Buff pool write time since 1st con*/

  unsigned long  files_closed;           /* files closed since first db conn  */

  /****************************************************************************/
  /* SQL statement counts                                                     */
  /****************************************************************************/
  unsigned long  commit_sql_stmts;       /* # of Commit SQL stmts since conn  */
  unsigned long  rollback_sql_stmts;     /* # of Rollback SQL stmts since conn*/
  unsigned long  dynamic_sql_stmts;      /* # of Dynamic SQL stmts since conn */
  unsigned long  static_sql_stmts;       /* # of Static SQL stmts since conn  */
  unsigned long  failed_sql_stmts;       /* # of Failed SQL stmts since conn  */
  unsigned long  select_sql_stmts;       /* # of SQL select stmts since conn  */
  unsigned long  ddl_sql_stmts;          /* # of data definition lang. stmts  */
  unsigned long  uid_sql_stmts;          /* # of update/insert/delete stmts   */

  /****************************************************************************/
  /* Internal counts                                                          */
  /****************************************************************************/
  unsigned long  int_auto_rebinds;       /* # of Auto Rebinds since 1st conn  */
  unsigned long  int_rows_deleted;       /* # of Casc. Deletes since 1st conn */
  unsigned long  int_rows_updated;       /* # of Set Null Deletes since conn  */
  unsigned long  int_commits;            /* # of int. Commits since 1st conn  */
  unsigned long  int_rollbacks;          /* # of int. Rollbacks since 1st conn*/
  unsigned long  int_deadlock_rollbacks; /* # of Rollbacks due to deadlock    */
                                         /*      since 1st connect            */

  /****************************************************************************/
  /* Row counts                                                               */
  /****************************************************************************/
  unsigned long  rows_deleted;           /* # of Rows Deleted since connect   */
  unsigned long  rows_inserted;          /* # of Rows Inserted since connect  */
  unsigned long  rows_updated;           /* # of Rows Updated since connect   */
  unsigned long  rows_selected;          /* # of Rows Selected since connect  */

  /****************************************************************************/
  /* Binds/Precompiles                                                        */
  /****************************************************************************/
  unsigned long  binds_precompiles;      /* # of Binds/Precomps since 1st conn*/

  /****************************************************************************/
  /* Timestamps                                                               */
  /****************************************************************************/
  sqlm_timestamp  db_conn_time;           /* Time of 1st database connection  */
  sqlm_timestamp  last_reset;             /* Date/Time of Last Reset          */
  sqlm_timestamp  last_backup;            /* Date/Time of Last Backup         */

  /****************************************************************************/
  /* Application connection counters                                          */
  /****************************************************************************/
  unsigned long  total_cons;             /* Connects since 1st db connect     */
  unsigned long  appls_cur_cons;         /* Appls currently connected         */
  unsigned long  appls_in_db2;           /* Appls executing in the DB2        */

  /****************************************************************************/
  /* Logging Information                                                      */
  /****************************************************************************/
  unsigned long  sec_log_used_top;       /* Maximum secondary log space used  */
  unsigned long  tot_log_used_top;       /* Maximum total log space used      */
  unsigned long  sec_logs_allocated;     /* Number of secondary logs allocated*/

  _SQLOLDCHAR    reserved[8];                /* reserved for future use      */

  unsigned long num_sec_dbase_structs;      /* Secondary Database information */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION5  Buffer Pool and I/O Information                     */
  /****************************************************************************/
  unsigned long  pool_async_index_reads;   /* asynchronous pool index reads   */
  unsigned long  pool_data_to_estore;    /* #pages copied from BP to estore   */
  unsigned long  pool_index_to_estore;   /* #pages copied from BP to estore   */
  unsigned long  pool_index_from_estore; /* #pages copied from estore to BP   */
  unsigned long  pool_data_from_estore;  /* #pages copied from estore to BP   */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION2  Database Status                                     */
  /****************************************************************************/
  unsigned long  db_status;             /* status of the Database             */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION2  lock information                                    */
  /****************************************************************************/
  unsigned long  lock_timeouts;        /* # of lock timeouts since 1st conn   */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION2  High Water Marks                                    */
  /****************************************************************************/
  unsigned long  connections_top;  /* high water mark for current connections */
  unsigned long  db_heap_top;      /* high water mark for database heap(bytes)*/

  /****************************************************************************/
  /* SQLM_DBMON_VERSION2  Buffer Pool and I/O Information                     */
  /****************************************************************************/
  unsigned long  pool_async_data_reads;    /* asynchronous pool data reads    */
  unsigned long  pool_async_data_writes;   /* asynchronous pool data writes   */
  unsigned long  pool_async_index_writes;  /* asynchronous pool index writes  */
  unsigned long  pool_async_read_time;     /* total async read time           */
  unsigned long  pool_async_write_time;    /* total async write time          */
  unsigned long  pool_async_data_read_reqs; /* # async read requests          */
  unsigned long  pool_lsn_gap_clns;        /* LSN Gap cleaner triggers        */
  unsigned long  pool_drty_pg_steal_clns;  /* dirty page steal cleaner trig.  */
  unsigned long  pool_drty_pg_thrsh_clns;  /* dirty list threshold cln trig.  */
  unsigned long  direct_reads;             /* direct reads since 1st connect  */
  unsigned long  direct_writes;            /* direct writes since 1st conn    */
  unsigned long  direct_read_reqs;         /* direct read requests            */
  unsigned long  direct_write_reqs;        /* direct write requests           */
  unsigned long  direct_read_time;         /* direct read time since 1st conn */
  unsigned long  direct_write_time;        /* direct write time since 1st conn*/

  /****************************************************************************/
  /* SQLM_DBMON_VERSION2 Internal counts                                      */
  /****************************************************************************/
  unsigned long  int_rows_inserted;      /* # rows insrted for Trigger        */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION2 Logging Information                                  */
  /****************************************************************************/
  unsigned long  log_reads;             /* # of log pages read since 1st conn */
  unsigned long  log_writes;            /* # of log pages read since 1st conn */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION2 Package Cache Information                            */
  /****************************************************************************/
  unsigned long  pkg_cache_lookups;     /* # of section lookups               */
  unsigned long  pkg_cache_inserts;     /* # of sections inserted into cache  */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION2 Catalog Cache Information                            */
  /****************************************************************************/
  unsigned long  cat_cache_lookups;     /* # of table descriptor lookups      */
  unsigned long  cat_cache_inserts;     /* # of table descriptors inserted    */
  unsigned long  cat_cache_overflows;   /* # of catalog cache overflows       */
  unsigned long  cat_cache_heap_full;   /* # of overflows due to db heap full */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION5                                                      */
  /****************************************************************************/
  unsigned long  catalog_node;          /* Catalog node number                */
  unsigned long  total_sec_cons;        /* Secondary connects since 1st       */
                                        /* database connection.               */
  unsigned long  num_assoc_agents;      /* Current number of agents associated*/
                                        /* with appls connected to this db.   */
  unsigned long  agents_top;            /* max # of agents associated at once */
                                        /* with appls connected to this db.   */
  unsigned long  coord_agents_top;      /* max # of coordinating agents       */
                                        /* connected to this db. at one time. */
  unsigned short db_location;           /* local or remote to snapshot appl.  */
  unsigned short server_platform;       /* OS on which dbm runs               */
  char catalog_node_name[SQLM_LG_IDENT_SZ];/* Catalog network node name       */
  unsigned long  prefetch_wait_time;    /* Time waited for prefetch (ms)      */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION5 Application Section Retrieval Information            */
  /****************************************************************************/
  unsigned long  appl_section_lookups;  /* # of section lookups               */
  unsigned long  appl_section_inserts;  /* # of sections inserted             */

}sqlm_dbase;

/******************************************************************************/
/* Application snapshot                                                       */
/******************************************************************************/
/* layout:                                                                    */
/* sqlm_appl may be followed by secondary structures that provide more        */
/* information about the application.                                         */
/*                                                                            */
/* The secondary structures are returned in the following order.              */
/*   1) List of associated agents                                             */
/*      sqlm_agent for each *associated* agent (either active or idle)        */
/*   2) Lock Wait info                                                        */
/*      sqlm_lock_wait for each lock waited on (returned if lock switch       */
/*      is set)                                                               */
/*   3) Statement level information   (returned if statement switch is set)   */
/*      Statement information is returned using the following structures,     */
/*      returned in order:                                                    */
/*                                                                            */
/*       +---------------------------------+----------------------+           */
/*       |Non-Partitioned Databases        |Partitionned Databases|           */
/*       +----------------+----------------+----------------------+           */
/*       |Query degree = 1|Query degree > 1|Query degree = n      |           */
/*       +----------------+----------------+----------------------+           */
/*       |sqlm_stmt       |sqlm_stmt       |sqlm_stmt             |           */
/*       |                |sqlm_agent      |sqlm_subsection       |           */
/*       |                |                |sqlm_agent            |           */
/*       +----------------+----------------+----------------------+           */
/*                                                                            */
/*      An sqlm_stmt is returned for each currently open cursor, and for      */
/*      the most recent statement processed (either the statement still       */
/*      running, if any, or last one terminated). Each sqlm_stmt may be       */
/*      followed by subsection and/or agent information for the statement.    */
/*                                                                            */
/*      On partitioned systems, an sqlm_subsection is returned for each       */
/*      subsection processed.                                                 */
/*                                                                            */
/*      An sqlm_agent is returned for each agent *currently working* on       */
/*      either a statement or subsection.                                     */
/*                                                                            */
/* For example, assuming a partitioned database:                              */
/*                                                                            */
/*     high-level struct            secondary-level structures                */
/*  |-----------+-----------|--------------------+---------------- ...        */
/*  +-----------------------+----------+----------+--------------+            */
/*  |sqlm_appl              |sqlm_agent|sqlm_agent|sqlm_lock_wait|            */
/*  |num_sec_appl_structs:10|          |          |              | ...        */
/*  |num_assoc_agents:    2 |          |          |              |            */
/*  +-----------------------+----------+----------+--------------+            */
/*                                                                            */
/*          secondary-level structures (continued)                            */
/*  ... ---------------------+-------------------------------------- ...      */
/*      +---------------+---------------+----------+---------------+          */
/*      |sqlm_stmt      |sqlm_subsection|sqlm_agent|sqlm_subsection|          */
/*  ... |num_ss: 2      |               |          |               | ...      */
/*      |num_agents: 2  |num_agents: 1  |          |num_agents: 1  |          */
/*      +---------------+---------------+----------+---------------+          */
/*                                                                            */
/*          secondary-level structures (continued)                            */
/*  ... ----------------------------------------------|                       */
/*      +-------------+---------------+---------------+                       */
/*      |sqlm_agent   |sqlm_stmt      |sqlm_subsection|                       */
/*  ... |             |num_ss: 1      |               |                       */
/*      |             |num_agents: 0  |num_agents: 0  |                       */
/*      +-------------+---------------+---------------+                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
typedef struct sqlm_appl
{
  unsigned long  size;                  /* size of sqlm_appl                  */
  _SQLOLDCHAR    info_type;             /* Always set to SQLM_APPL_SS         */
  _SQLOLDCHAR    pad1[3];               /* padding for 4 byte alignment       */

  /****************************************************************************/
  /* Identification Information                                               */
  /****************************************************************************/
  sqlm_appl_id_info   id_info;               /* identification information    */

  /****************************************************************************/
  /* Lock Information                                                         */
  /****************************************************************************/
  unsigned long  locks_held;             /* locks currently held by appl.     */
  unsigned long  lock_waits;             /* Lock waits since appl. connect    */
  unsigned long  lock_wait_time;         /* total time appl waited on locks   */
  unsigned long  lock_escals;            /* Lock Escalations since appl conn. */
  unsigned long  x_lock_escals;          /* X lock escals since appl connect  */
  unsigned long  deadlocks;              /* Deadlocks since appl. connect     */
  unsigned long  uow_lock_wait_time;     /* time UOW waited on locks (ms)     */
  unsigned long  agent_id_holding_lk;    /* OBSOLETE : use sqlm_lock_wait     */
  unsigned long  table_file_id;          /* OBSOLETE : use sqlm_lock_wait     */
  unsigned long  lock_mode;              /* OBSOLETE : use sqlm_lock_wait     */
  unsigned long  lock_object_type;       /* OBSOLETE : use sqlm_lock_wait     */
  unsigned long  lock_object_name;       /* OBSOLETE : use sqlm_lock_wait     */
  sqlm_timestamp lock_wait_start_time;   /* OBSOLETE : use sqlm_lock_wait     */
  _SQLOLDCHAR    appl_id_holding_lk[SQLM_APPLID_SZ]; /* OBSOLETE  */
  _SQLOLDCHAR    sequence_no_holding_lk[SQLM_SEQ_SZ];/* OBSOLETE  */

  /****************************************************************************/
  /* Sorting Information                                                      */
  /****************************************************************************/
  unsigned long  total_sorts;            /* Total Sorts since connect         */
  unsigned long  total_sort_time;        /* elapsed time spent in sorts       */
  unsigned long  sort_overflows;         /* number of sort overflows          */

  /****************************************************************************/
  /* Buffer Pool Information                                                  */
  /****************************************************************************/
  unsigned long  pool_data_l_reads;      /* pool data logical reads since conn*/
  unsigned long  pool_data_p_reads;      /* pool data reads since 1st connect */
  unsigned long  pool_data_writes;       /* pool data writes since 1st connect*/
  unsigned long  pool_index_l_reads;     /* pool indx logical reads since conn*/
  unsigned long  pool_index_p_reads;     /* pool indx reads since 1st connect */
  unsigned long  pool_index_writes;      /* pool indx writes since 1st connect*/
  unsigned long  pool_read_time;         /* Buff pool read time since 1st conn*/
  unsigned long  pool_write_time;        /* Buff pool write time since 1st con*/

  /****************************************************************************/
  /* SQL statement counts                                                     */
  /****************************************************************************/
  unsigned long  commit_sql_stmts;       /* # of Commit SQL stmts since conn  */
  unsigned long  rollback_sql_stmts;     /* # of Rollback SQL stmts since conn*/
  unsigned long  dynamic_sql_stmts;      /* # of Dynamic SQL stmts since conn */
  unsigned long  static_sql_stmts;       /* # of Static SQL stmts since conn  */
  unsigned long  failed_sql_stmts;       /* # of Failed SQL stmts since conn  */
  unsigned long  select_sql_stmts;       /* # of SQL select stmts since conn  */
  unsigned long  ddl_sql_stmts;          /* # of data definition lang. stmts  */
  unsigned long  uid_sql_stmts;          /* # of update/insert/delete stmts   */

  /****************************************************************************/
  /* Internal counts                                                          */
  /****************************************************************************/
  unsigned long  int_auto_rebinds;       /* # of Auto Rebinds since 1st conn  */
  unsigned long  int_rows_deleted;       /* # of Casc. Deletes since 1st conn */
  unsigned long  int_rows_updated;       /* # of Set Null Deletes since conn  */
  unsigned long  int_commits;            /* # of int. Commits since 1st conn  */
  unsigned long  int_rollbacks;          /* # of int. Rollbacks since 1st conn*/
  unsigned long  int_deadlock_rollbacks; /* # of Rollbacks due to deadlock    */
                                         /*      since 1st connect            */

  /****************************************************************************/
  /* Row counts                                                               */
  /****************************************************************************/
  unsigned long  rows_deleted;           /* # of Rows Deleted since connect   */
  unsigned long  rows_inserted;          /* # of Rows Inserted since connect  */
  unsigned long  rows_updated;           /* # of Rows Updated since connect   */
  unsigned long  rows_selected;          /* # of Rows Selected since connect  */

  /****************************************************************************/
  /* Binds/Precompiles                                                        */
  /****************************************************************************/
  unsigned long  binds_precompiles;      /* # of Binds/Precomps since 1st conn*/

  /****************************************************************************/
  /* SQL Statement Information - current operation performed on coordinator   */
  /****************************************************************************/
  unsigned long  stmt_type;
  unsigned long  stmt_operation;
  unsigned long  section_number;
  unsigned long  stmt_length;                 /* OBSOLETE (use sqlm_stmt) */
  unsigned long  stmt_sorts;                  /* OBSOLETE (use sqlm_stmt) */
  sqlm_timestamp stmt_start;
  sqlm_timestamp stmt_stop;   /* Last statement stop time, 0 if still running */
  _SQLOLDCHAR    cursor_name[SQLM_IDENT_SZ];
  _SQLOLDCHAR    creator[SQLM_IDENT_SZ];
  _SQLOLDCHAR    package_name[SQLM_IDENT_SZ];

  /****************************************************************************/
  /* Unit-Of-Work Information                                                 */
  /****************************************************************************/
  unsigned long   uow_log_space_used;   /* Log space used in most recent UOW  */
  unsigned long   uow_comp_status;      /* previous uow completion status     */
  sqlm_timestamp  prev_uow_stop_time;   /* prev commit or rollback time       */
  sqlm_timestamp  uow_start_time;       /* time trans exec started            */
  sqlm_timestamp  uow_stop_time;        /* unit-of-work stop time             */

  /****************************************************************************/
  /* Remote cursor Information                                                */
  /****************************************************************************/
  unsigned long  open_rem_curs;         /* Currently open remote cursors      */
  unsigned long  open_rem_curs_blk;     /* Currently open remote cursors w/blk*/
  unsigned long  rej_curs_blk;          /* Rej block remote cursor requests   */
  unsigned long  acc_curs_blk;          /* Acc block remote cursor requests   */

  /****************************************************************************/
  /* Timestamps                                                               */
  /****************************************************************************/
  sqlm_timestamp  appl_con_time;        /* Connect start date/time            */
  sqlm_timestamp  conn_complete_time;   /* Connect complete date/time         */
  sqlm_timestamp  last_reset;           /* Last reset date and time           */

  unsigned long  curr_comm_heap_size;   /* OBSOLETE */
  unsigned long  max_comm_heap_size;    /* OBSOLETE */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION5  Agent CPU times                                     */
  /****************************************************************************/
  unsigned long  appl_idle_time;        /* Application idle time (seconds)    */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION5  Buffer Pool and I/O Information                     */
  /****************************************************************************/
  unsigned long  pool_data_to_estore;    /* #pages copied from BP to estore   */
  unsigned long  pool_index_to_estore;   /* #pages copied from BP to estore   */
  unsigned long  pool_index_from_estore; /* #pages copied from estore to BP   */
  unsigned long  pool_data_from_estore;  /* #pages copied from estore to BP   */

  unsigned long  authority_lvl;         /* User authorizations                */
  unsigned long  sql_reqs_since_commit; /* # SQL requests since last commit   */
  unsigned long  num_sec_appl_structs;  /* Secondary application information  */

  char  table_name[SQLM_IDENT_SZ];      /* OBSOLETE (moved to sqlm_lock_wait) */
  char  table_schema[SQLM_IDENT_SZ];    /* OBSOLETE (moved to sqlm_lock_wait) */
  char  tablespace_name[SQLM_IDENT_SZ]; /* OBSOLETE (moved to sqlm_lock_wait) */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION2  lock information                                    */
  /****************************************************************************/
  unsigned long  lock_timeouts;        /* number of lock timeouts since conn  */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION2  Agent CPU times                                     */
  /****************************************************************************/
  sqlm_time      agent_usr_cpu_time;   /* total user CPU time of application  */
  sqlm_time      agent_sys_cpu_time;   /* total application system cpu time   */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION2  SQL Statement CPU times                             */
  /****************************************************************************/
  sqlm_time      stmt_usr_cpu_time;    /* OBSOLETE (moved to sqlm_stmt)       */
  sqlm_time      stmt_sys_cpu_time;    /* OBSOLETE (moved to sqlm_stmt)       */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION2  Internal counts                                     */
  /****************************************************************************/
  unsigned long  int_rows_inserted;      /* # rows insrted for Trigger        */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION2  Row Counts                                          */
  /****************************************************************************/
  unsigned long  rows_read;              /* # rows read since connection      */
  unsigned long  rows_written;           /* # rows written since connetion    */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION2  I/O Information                                     */
  /****************************************************************************/
  unsigned long  direct_reads;             /* direct reads since connect      */
  unsigned long  direct_writes;            /* direct writes since connect     */
  unsigned long  direct_read_reqs;         /* direct read requests since conn */
  unsigned long  direct_write_reqs;        /* direct write requests since conn*/
  unsigned long  direct_read_time;         /* direct read time since connect  */
  unsigned long  direct_write_time;        /* direct write time since connect */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION2  Local Cursor Information                            */
  /****************************************************************************/
  unsigned long  open_loc_curs;         /* Currently open local cursors       */
  unsigned long  open_loc_curs_blk;     /* Currently open local cursors w/blk */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION2  Client Identification Information                   */
  /****************************************************************************/
  char           execution_id[SQLM_IDENT_SZ]; /* login ID                     */
  char           corr_token[SQLM_APPLID_SZ];  /* DRDA AS Correlation Token    */
  unsigned long  client_pid;           /* Process thread ID of client appl.   */
  unsigned short client_platform;      /* Platform of client application      */
  unsigned short client_protocol;      /* Communications protocol of client   */
  unsigned short country_code;         /* Country code of client application  */
  char           pad2[2];              /* Padding for 4 byte alignment        */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION2 Package Cache Information                            */
  /****************************************************************************/
  unsigned long  pkg_cache_lookups;     /* # of section lookups               */
  unsigned long  pkg_cache_inserts;     /* # of sections inserted into cache  */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION2 Catalog Cache Information                            */
  /****************************************************************************/
  unsigned long  cat_cache_lookups;     /* # of table descriptor lookups      */
  unsigned long  cat_cache_inserts;     /* # of table descriptors inserted    */
  unsigned long  cat_cache_overflows;   /* # of catalog cache overflows       */
  unsigned long  cat_cache_heap_full;   /* # of overflows due to db heap full */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION5                                                      */
  /****************************************************************************/
  unsigned long  coord_node;            /* Coordinating node number.          */
  unsigned long  num_assoc_agents;      /* # of agents currently associated   */
  unsigned long  num_agents;            /* # of agents currently active       */
  unsigned long  agents_stolen;         /* total # of agents stolen from appl.*/
  unsigned long  associated_agents_top; /* # of agents associated with this   */
                                        /* application  high water mark.      */
  long           appl_priority;         /* priority at which appl agents work */
  unsigned long  appl_priority_type;    /* Dynamic or Static                  */
  unsigned long  prefetch_wait_time;    /* Time waited for prefetch (ms)      */
  long           coord_agent_pid;       /* Coordinator agent process/thread id*/

  unsigned long  appl_section_lookups;  /* # of section lookups               */
  unsigned long  appl_section_inserts;  /* # of sections inserted             */
  unsigned long  locks_waiting;         /* # agents currently waiting on locks*/
}sqlm_appl;

/******************************************************************************/
/* SQL Statement snapshot - returned on application snapshot (SQLMA_APPL)     */
/******************************************************************************/
/* layout:                                                                    */
/* sqlm_stmt may be followed by dynamic statement text, and agent structures. */
/* On Partitioned database systems, it may be followed by subsection          */
/* statistics. For example:                                                   */
/*                                                                            */
/*  Non-Partitioned database (query degree=2):                                */
/*  +-----------------+--------------------------+----------+----------+      */
/*  |sqlm_stmt        |"SELECT * FROM TABLE1    "|sqlm_agent|sqlm_agent|      */
/*  |  stmt_length: 24|                          |          |          |      */
/*  |  num_ss:       1|                          |          |          |      */
/*  |  num_agents:   2|                          |          |          |      */
/*  +-----------------+--------------------------+----------+----------+      */
/*                                                                            */
/*  Partitioned database output (query degree=1):                             */
/*  +-----------------+--------------------------+---------------+----------+ */
/*  |sqlm_stmt        |"SELECT * FROM TABLE1    "|sqlm_subsection|sqlm_agent| */
/*  |  stmt_length: 24|                          |ss_number: 0   |          | */
/*  |  num_ss:       1|                          |               |          | */
/*  |  num_agents:   1|                          |num_agents: 1  |          | */
/*  +-----------------+--------------------------+---------------+----------+ */
/*                                                                            */
/* The statement text length is rounded up to a multiple of 4 bytes and is    */
/* blank padded. It is *NOT* null terminated.  It is retrieved as follows:    */
/*                                                                            */
/*    char*       snapshot_buffer;                                            */
/*    sqlm_stmt*  stmt_snapshot = (sqlm_stmt*) snapshot_buffer;               */
/*    char *stmt_text = snapshot_buffer + stmt_snapshot->stmt_text_offset;    */
/*                                                                            */
/* note: num_sec_appl_structs in sqlm_appl includes the count of              */
/*       sqlm_subsection and sqlm_agent structures.                           */
/*----------------------------------------------------------------------------*/
typedef struct sqlm_stmt {
  unsigned long  size;               /* Use instead of sizeof(sqlm_stmt)      */
                                     /* *INCLUDES* variable length SQL text   */
  char           info_type;          /* Always set to SQLM_STMT_SS            */
  char           pad[1];             /* padding for half-word alignment       */
  unsigned short stmt_node_number;   /* Node where the statement is executing */
  unsigned long  stmt_type;          /* type of stmt: Dynamic or static       */
  unsigned long  stmt_operation;     /* Current Operation                     */
  unsigned long  section_number;     /* Section Number                        */
  unsigned long  query_cost_estimate;/* SQL compiler estim. in TIMERONS       */
  unsigned long  query_card_estimate;/* SQL compiler estim. number of rows    */
  unsigned long  degree_parallelism; /* SMP Intraquery Parallelism requested  */
  unsigned long  stmt_sorts;         /* number of sorts for this statement    */
  unsigned long  total_sort_time;    /* Total sort time for this statement    */
  unsigned long  sort_overflows;     /* # of sort overflows for this stmt     */
  unsigned long  rows_read;          /* # of DMS rows read                    */
  unsigned long  rows_written;       /* # of DMS rows read                    */
  unsigned long  int_rows_deleted;   /* # of internal deletes by the stmt     */
  unsigned long  int_rows_updated;   /* # of internal updates by the stmt     */
  unsigned long  int_rows_inserted;  /* # of internal inserts by the stmt     */
  unsigned long  fetch_count;        /* Count of fetches                      */

  sqlm_timestamp stmt_start;         /* SQL statement operation start time    */
  sqlm_timestamp stmt_stop;          /* SQL statement operation stop time     */
  char           cursor_name[SQLM_IDENT_SZ];  /* sql stmt.cursor name         */
  char           creator[SQLM_IDENT_SZ];      /* auth id for precompile       */
  char           package_name[SQLM_IDENT_SZ]; /* Package Name                 */
  sqlm_time      stmt_usr_cpu_time;  /* total user CPU time of SQL stmt       */
  sqlm_time      stmt_sys_cpu_time;  /* total system CPU time for SQL stmt    */

  unsigned long  num_ss;             /* number of subsections                 */
  unsigned long  num_agents;         /* # of agents currently working on stmt */
  unsigned long  agents_top;         /* # of agents created for statement     */
  unsigned short stmt_length;        /* length of dynamic SQL text, which is  */
                                     /* blank padded to a 4 byte boundary     */
  unsigned short stmt_text_offset;   /* Text offset from start of sqlm_stmt   */
}sqlm_stmt;

/******************************************************************************/
/* SQL Subsection -  returned on application snapshot (SQLMA_APPL)            */
/******************************************************************************/
typedef struct sqlm_subsection
{
  unsigned long  size;              /* Use instead of sizeof(sqlm_subsection) */
  char           info_type;         /* Always set to SQLM_SUBSECTION_SS       */
  char           pad1[1];           /* padding for memory alignment           */

  unsigned short ss_number;         /* Subsection number                      */
  unsigned short ss_status;         /* Subsection status                      */
  unsigned short ss_node_number;    /* Node where the subsection is executing */
  unsigned long  ss_exec_time;      /* Execution elapsed time in seconds      */

  sqlm_time      ss_usr_cpu_time;   /* total user CPU time (sec.microsec)     */
  sqlm_time      ss_sys_cpu_time;   /* total system CPU time (sec.microsec)   */

  /* Tablequeue information */
  unsigned short tq_node_waited_for;/* If blocked when sending or receiving   */
                                    /* on a tablequeue, node for which we wait*/
  unsigned short tq_wait_for_any;   /* TRUE if waiting for any node to send   */
  unsigned short tq_id_waiting_on;  /* tablequeue waiting to send/receive     */
  char           pad2[2];           /* padding for 4 byte memory alignment    */
  unsigned long  tq_tot_send_spills;/* Total # of buffers overflowed to a     */
                                    /*  temp table when sending data on a tq  */
  unsigned long  tq_cur_send_spills;/* Current # of tq send buffers overflowed*/
  unsigned long  tq_max_send_spills;/* Maximum # of tq send buffers overflowed*/
  unsigned long  tq_rows_read;      /* Total # rows received on tablequeues   */
  unsigned long  tq_rows_written;   /* Total # rows sent on tablequeues       */

  unsigned long  rows_read;         /* # of Data Manager (DMS) rows read      */
  unsigned long  rows_written;      /* # of DMS rows written                  */

  unsigned long  num_agents;        /* # of agents currently working on subs  */
}sqlm_subsection;

/******************************************************************************/
/* SQL Agent -  returned on application snapshot (SQLMA_APPL)                 */
/******************************************************************************/
typedef struct sqlm_agent {
  unsigned long  size;               /* Use instead of sizeof(sqlm_agent)     */
  char           info_type;          /* Always set to SQLM_AGENT_SS           */
  char           pad1[3];            /* padding for 4 byte alignment          */

  long           agent_pid;          /* db2agent process/thread id            */
}sqlm_agent;

/******************************************************************************/
/* Lock Wait Snapshot Information                                             */
/******************************************************************************/
typedef struct sqlm_lock_wait
{
  unsigned long  size;                 /* Use over sizeof(sqlm_lock_wait)     */
  char           info_type;            /* Always set to SQLM_LOCK_WAIT_SS     */
  char           pad1[3];              /* padding for 4 byte alignment        */
  unsigned long  subsection_number;    /* Subsection waiting for lock  */

  unsigned long  lock_mode;            /* Mode of Lock waited on              */
  unsigned long  lock_object_type;     /* lock object type: row, table, ...   */
  sqlm_timestamp lock_wait_start_time; /* Time when lock wait entered         */
  char           table_name[SQLM_IDENT_SZ];
  char           table_schema[SQLM_IDENT_SZ];
  char           tablespace_name[SQLM_IDENT_SZ];

  unsigned long  agent_id_holding_lk;  /* Application holding the lock */
  char           appl_id_holding_lk[SQLM_APPLID_SZ];/* Appl. holding the lock */
} sqlm_lock_wait;

/******************************************************************************/
/* Table Related Snapshot Information                                         */
/******************************************************************************/
typedef struct sqlm_table_header
{
  unsigned long  size;                   /* size of sqlm_table_header         */
  _SQLOLDCHAR    info_type;              /* Always set to SQLM_TABLE_HEADER_SS*/
  _SQLOLDCHAR    pad1[3];                /* padding for 4 byte alignment      */
  unsigned long  num_tables;             /* # of sqlm_table struct returned   */
  sqlm_timestamp db_conn_time;           /* Time of 1st database connection   */
  sqlm_timestamp last_reset;             /* last reset date and time          */
  _SQLOLDCHAR    input_db_alias[SQLM_IDENT_SZ]; /* Input Database Alias       */
  _SQLOLDCHAR    db_name[SQLM_IDENT_SZ];        /* Database name              */
  _SQLOLDCHAR    db_path[SQLM_DBPATH_SZ];       /* Database Path              */
}sqlm_table_header;

typedef struct sqlm_table
{
  unsigned long  size;                    /* size of sqlm_table               */
  _SQLOLDCHAR    info_type;               /* Always set to SQLM_TABLE_SS      */
  _SQLOLDCHAR    pad1[3];                 /* padding for 4 byte alignment     */
  unsigned long  table_file_id;           /* the file ID for the table        */
  unsigned long  table_type;              /* table type                       */
  unsigned long  rows_written;            /* number of changes to the table   */
  unsigned long  rows_read;               /* number of reads from the table   */
  unsigned long  overflow_accesses;       /* no. of accesses to overflow rec  */

  _SQLOLDCHAR    reserved[32];            /* reserved for future use          */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION2  Table Identification                                */
  /****************************************************************************/
  char           table_name[SQLM_IDENT_SZ];   /* table name                   */
  char           table_schema[SQLM_IDENT_SZ]; /* table schema                 */
}sqlm_table;

/******************************************************************************/
/* lock related information                                                   */
/******************************************************************************/
/* Database lock snapshot layout, example:                                    */
/*                                                                            */
/*              high-level struct                                             */
/*           |-----------+------------|                                       */
/* buffer--->+------------------------+--------------+     +--------------+   */
/*           |sqlm_dbase_lock         |sqlm_appl_lock| ... |sqlm_appl_lock|   */
/*           |  num_appls: 2          |          (1) |     |              |   */
/*           +------------------------+--------------+     +--------------+   */
/*                                                                            */
/*             (1) see sqlm_appl_lock layout                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/
typedef struct sqlm_dbase_lock
{
  unsigned long  size;                   /* size of sqlm_dbase_lock           */
  _SQLOLDCHAR    info_type;              /* Always set to SQLM_DBASE_LOCK_SS  */
  _SQLOLDCHAR    pad[3];                 /* padding for 4 byte alignment      */
  unsigned long  locks_held;             /* number of locks currently held    */
  unsigned long  appls_cur_cons;         /* Appls currently connected         */
  unsigned long  num_appls;              /* # sqlm_appl_lock structs returned */
  unsigned long  locks_waiting;          /* Agents currently waiting on locks */
  _SQLOLDCHAR    input_db_alias[SQLM_IDENT_SZ]; /* Input Database Alias       */
  _SQLOLDCHAR    db_name[SQLM_IDENT_SZ];        /* Database name              */
  _SQLOLDCHAR    db_path[SQLM_DBPATH_SZ];       /* Database Path              */
}sqlm_dbase_lock;

/******************************************************************************/
/* Application lock snapshot                                                  */
/******************************************************************************/
/* Application lock snapshot layout, example:                                 */
/*                                                                            */
/*              high-level struct                                             */
/*           |-----------+------------|                                       */
/* buffer--->+------------------------+--------------+---------+---------+    */
/*           |sqlm_appl_lock          |sqlm_lock_wait|sqlm_lock|sqlm_lock|    */
/*           |  num_locks: 2          |              |         |         |    */
/*           |  num_lockwaits: 1      |              |         |         |    */
/*           +------------------------+--------------+---------+---------+    */
/*                                                                            */
/* Lock waits, if any, *always precede the locks*. That is, read the buffer   */
/* in the following manner:                                                   */
/*                                                                            */
/*    sqlm_appl_lock *app_lock_info = (sqlm_appl_lock*) buffer;               */
/*    while (app_lock_info->num_lockwaits--)                                  */
/*    {                                                                       */
/*       sqlm_lock_wait *appl_lock = (sqlm_lock_wait*) buffer;                */
/*                . . .                                                       */
/*       buffer += appl_lock->size;                                           */
/*    }                                                                       */
/*    while (app_lock_info->num_locks--)                                      */
/*    {                                                                       */
/*       sqlm_lock *lock = (sqlm_lock*) buffer;                               */
/*                 . . .                                                      */
/*       buffer += lock->size;                                                */
/*    }                                                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
typedef struct sqlm_appl_lock
{
  unsigned long  size;                   /* size of sqlm_appl_lock            */
  _SQLOLDCHAR    info_type;              /* Always set to SQLM_APPL_LOCK_SS   */
  _SQLOLDCHAR    pad[3];                 /* padding for 4 byte alignment      */

  /****************************************************************************/
  /* Application Identification Information                                   */
  /****************************************************************************/
  unsigned long  agent_id;                 /* Application handle              */
  unsigned long  appl_status;              /* Application Status              */
  unsigned long  codepage_id;              /* codepage/CCSID at node          */
                                           /* where app started               */
  unsigned long  locks_held;               /* locks currently held by appl.   */
  unsigned long  num_locks;                /* # sqlm_lock structures returned */
  sqlm_timestamp status_change_time;       /* last appl status change time    */
  _SQLOLDCHAR    appl_id[SQLM_APPLID_SZ];  /* Application Id                  */
  _SQLOLDCHAR    sequence_no[SQLM_SEQ_SZ]; /* appl id sequence number         */
  _SQLOLDCHAR    appl_name[SQLM_IDENT_SZ]; /* Application Name                */
  _SQLOLDCHAR    auth_id[SQLM_IDENT_SZ];   /* Authorization Id                */
  _SQLOLDCHAR    client_db_alias[SQLM_IDENT_SZ]; /* Client Database Alias     */

  unsigned long  agent_id_holding_lk;                 /* OBSOLETE */
  unsigned long  lock_object_name;                    /* OBSOLETE */
  unsigned long  lock_object_type;                    /* OBSOLETE */
  unsigned long  table_file_id;                       /* OBSOLETE */
  _SQLOLDCHAR    appl_id_holding_lk[SQLM_APPLID_SZ];  /* OBSOLETE */
  _SQLOLDCHAR    sequence_no_holding_lk[SQLM_SEQ_SZ]; /* OBSOLETE */
  _SQLOLDCHAR    reserved[24];                        /* OBSOLETE */

  unsigned long  lock_wait_time;           /* total wait time in millisec     */
  unsigned long  num_lockwaits;            /* # sqlm_lock_wait following      */

  char           table_name[SQLM_IDENT_SZ];           /* OBSOLETE */
  char           table_schema[SQLM_IDENT_SZ];         /* OBSOLETE */
  char           tablespace_name[SQLM_IDENT_SZ];      /* OBSOLETE */
}sqlm_appl_lock;

typedef struct sqlm_lock
{
  unsigned long  size;                   /* size of sqlm_lock                 */
  _SQLOLDCHAR    info_type;              /* Always set to SQLM_LOCK_SS        */
  _SQLOLDCHAR    pad[3];                 /* padding for 4 byte alignment      */
  unsigned long  table_file_id;          /* FID of table involved in lock     */
  unsigned long  lock_object_type;       /* lock object type: row, table      */
  unsigned long  lock_mode;              /* Lock mode                         */
  unsigned long  lock_status;            /* Lock status                       */
  unsigned long  lock_object_name;       /* Lock Object Name -                */
                                         /* RID or FID of lock obj            */
  _SQLOLDCHAR    reserved[32];           /* reserved for future use           */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION2  Lock Information                                    */
  /****************************************************************************/
  char           table_name[SQLM_IDENT_SZ];       /* table name               */
  char           table_schema[SQLM_IDENT_SZ];     /* table schema             */
  char           tablespace_name[SQLM_IDENT_SZ];  /* name of the tablespace   */
}sqlm_lock;

/******************************************************************************/
/* Tablespace Related Snapshot Information                                    */
/******************************************************************************/
typedef struct sqlm_tablespace_header
{
  unsigned long  size;                   /* size of sqlm_tablespace_header    */
  char           info_type;              /* Set to SQLM_TABLESPACE_HEADER_SS  */
  char           pad[3];                 /* padding for 4 byte alignment      */
  unsigned long  num_tablespaces;        /* # sqlm_tablespace structs returned*/
  sqlm_timestamp db_conn_time;           /* Time of 1st database connection   */
  sqlm_timestamp last_reset;             /* last reset date and time          */
  char           input_db_alias[SQLM_IDENT_SZ]; /* Input Database Alias       */
  char           db_name[SQLM_IDENT_SZ];        /* Database name              */
  char           db_path[SQLM_DBPATH_SZ];       /* Database Path              */
}sqlm_tablespace_header;


typedef struct sqlm_tablespace
{
  unsigned long  size;                   /* size of sqlm_table                */
  char           info_type;              /* Always set to SQLM_TABLESPACE_SS  */
  char           pad[3];                 /* padding for 4 byte alignment      */

  char           tablespace_name[SQLM_IDENT_SZ];  /* name of the tablespace   */

  unsigned long  pool_data_l_reads;      /* pool data logical reads since conn*/
  unsigned long  pool_data_p_reads;      /* pool data physical reads since con*/
  unsigned long  pool_async_data_reads;  /* asynchronous pool data reads      */
  unsigned long  pool_data_writes;       /* pool data writes since connect    */
  unsigned long  pool_async_data_writes; /* asynchronous pool data writes     */
  unsigned long  pool_index_l_reads;     /* pool index logical reads since con*/
  unsigned long  pool_index_p_reads;     /* pool index physical reads since cn*/
  unsigned long  pool_index_writes;      /* pool index writes since connect   */
  unsigned long  pool_async_index_writes; /* asynchronous pool index writes   */
  unsigned long  pool_read_time;         /* Buff pool read time since 1st conn*/
  unsigned long  pool_write_time;        /* Buff pool write time since 1st con*/
  unsigned long  pool_async_read_time;   /* asynchronous read time            */
  unsigned long  pool_async_write_time;  /* asynchronous write time           */
  unsigned long  pool_async_data_read_reqs; /* # async read requests          */

  unsigned long  direct_reads;           /* direct reads since 1st connect    */
  unsigned long  direct_writes;          /* direct writes since 1st conn      */
  unsigned long  direct_read_reqs;       /* direct read requests              */
  unsigned long  direct_write_reqs;      /* direct write requests             */
  unsigned long  direct_read_time;       /* direct read time since 1st conn   */
  unsigned long  direct_write_time;      /* direct write time since 1st conn  */

  unsigned long  files_closed;           /* files closed for tablespace       */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION5  Buffer Pool and I/O Information                     */
  /****************************************************************************/
  unsigned long  pool_async_index_reads; /* asynchronous pool index reads     */
  unsigned long  pool_data_to_estore;    /* #pages copied from BP to estore   */
  unsigned long  pool_index_to_estore;   /* #pages copied from BP to estore   */
  unsigned long  pool_index_from_estore; /* #pages copied from estore to BP   */
  unsigned long  pool_data_from_estore;  /* #pages copied from estore to BP   */
}sqlm_tablespace;

typedef struct sqlm_rollfwd_info {
 unsigned long  size;             /* Use instead of sizeof(sqlm_rollfwd_info) */
 char           info_type;        /* Always set to SQLM_DBASE_ROLLFWD_SS      */
 char           pad[1];           /* For 2-byte alignment                     */
 unsigned short node_number;      /* Node for which this info is about        */
 unsigned long  rf_type;          /* database or tablespace rollforward       */
 unsigned long  rf_log_num;       /* Current log being processed              */
 unsigned long  rf_status;        /* Log phase in progress                    */
 unsigned long  rf_timestamp;     /* Time of Log record currently processed,  */
                                  /* GMT time in seconds since Jan 1st, 1970  */
 unsigned long  rf_num_tspaces;   /* number of sqlm_rollfwd_ts_info following */
} sqlm_rollfwd_info;

typedef struct sqlm_rollfwd_ts_info
{
 unsigned long size;            /* Must use to skip this record in buffer     */
 char           info_type;      /* Always set to SQLM_DBASE_ROLLFWD_TS_NAME_SS*/
 char           pad[3];         /* For 4-byte alignment                       */
 char    ts_name[SQLM_IDENT_SZ];/* Tablespace being rolled forward            */
} sqlm_rollfwd_ts_info;


/******************************************************************************/
/* Bufferpool Related Snapshot Information                                    */
/******************************************************************************/
typedef struct sqlm_bp_info {
  /* Version 1 counters */
  unsigned long  pool_data_l_reads;      /* pool data logical reads           */
  unsigned long  pool_data_p_reads;      /* pool data physical reads          */
  unsigned long  pool_data_writes;       /* pool data writes                  */
  unsigned long  pool_index_l_reads;     /* pool index logical reads          */
  unsigned long  pool_index_p_reads;     /* pool index physical reads         */
  unsigned long  pool_index_writes;      /* pool index writes                 */
  unsigned long  pool_read_time;         /* Buff pool read time               */
  unsigned long  pool_write_time;        /* Buff pool write time              */
  unsigned long  files_closed;           /* files closed for bufferpool       */

  /* Version 2 counters */
  unsigned long  pool_async_data_reads;  /* asynchronous pool data reads      */
  unsigned long  pool_async_data_writes; /* asynchronous pool data writes     */
  unsigned long  pool_async_index_writes;/* asynchronous pool index writes    */
  unsigned long  pool_async_read_time;   /* asynchronous read time            */
  unsigned long  pool_async_write_time;  /* asynchronous write time           */
  unsigned long  pool_async_data_read_reqs; /* # async read requests          */
  unsigned long  direct_reads;           /* direct reads                      */
  unsigned long  direct_writes;          /* direct writes                     */
  unsigned long  direct_read_reqs;       /* direct read requests              */
  unsigned long  direct_write_reqs;      /* direct write requests             */
  unsigned long  direct_read_time;       /* direct read time                  */
  unsigned long  direct_write_time;      /* direct write time                 */

  /* Version 3 counters */
  unsigned long  pool_async_index_reads; /* asynchronous pool index reads     */
  unsigned long  pool_data_to_estore;    /* #pages copied from BP to estore   */
  unsigned long  pool_index_to_estore;   /* #pages copied from BP to estore   */
  unsigned long  pool_index_from_estore; /* #pages copied from estore to BP   */
  unsigned long  pool_data_from_estore;  /* #pages copied from estore to BP   */
} sqlm_bp_info;

typedef struct sqlm_bufferpool
{
   unsigned long    size;         /* Use instead of sizeof(sqlm_bufferpool)   */
   char             info_type;    /* Always set to SQLM_BUFFERPOOL_SS         */
   char             pad[3];       /* For 4 byte memory alignment              */
   char             bp_name[SQLM_IDENT_SZ];        /* Bufferpool name         */
   char             input_db_alias[SQLM_IDENT_SZ]; /* Database alias          */
   char             db_name[SQLM_IDENT_SZ];        /* Database name           */
   char             db_path[SQLM_DBPATH_SZ];       /* Database Path           */
   sqlm_bp_info     bp_info;      /* total stats from all tspaces for this bp */
} sqlm_bufferpool;


/******************************************************************************/
/******************************************************************************/
/* Event Monitoring event records                                             */
/******************************************************************************/
/******************************************************************************/

/******************************************************************************/
/*  Event Monitor Log Header Record                                           */
/******************************************************************************/
typedef struct sqlm_event_log_header
{
  int            byte_order;                   /* Big Endian or Little Endian */
  unsigned long  size;                         /* Size of this record         */
  unsigned long  version;                      /* Event Monitor Version       */
  char           event_monitor_name[SQLM_IDENT_SZ];  /* Name of the Event Mon */
  unsigned short codepage_id;                  /* Code page of Database       */
  unsigned short country_code;                 /* Country Code of Database    */
  char           server_prdid[SQLM_IDENT_SZ];  /* Server Product Id           */
  char           server_instance_name[SQLM_IDENT_SZ]; /*instance name of DB2  */
  unsigned long  num_nodes_in_db2_instance;    /* 1 if SERIAL                 */
}sqlm_event_log_header;

/******************************************************************************/
/* Event Monitor Record Header                                                */
/******************************************************************************/
typedef struct sqlm_event_rec_header {
  /*
     All event monitor event records have size and type as their first data
     elements.  These fields can be viewed as a 'header' that has to be read
     first to determine how to read the rest of the data.
     The record size for a given event type may vary between releases of DB2.
   */
   unsigned long size;               /* size of Event (size of entire struct) */
   unsigned long type;               /* type of Event                         */
} sqlm_event_rec_header;

/******************************************************************************/
/*  Event Monitor Database Event Record                                       */
/******************************************************************************/
typedef struct sqlm_db_event
{
  unsigned long  size;                   /* event record size                 */
  unsigned long  event_type;             /* event type identifier             */

  /****************************************************************************/
  /* Locking Information                                                      */
  /****************************************************************************/
  unsigned long  lock_waits;             /* Lock waits                        */
  unsigned long  lock_wait_time;         /* Total time dbase waited on locks  */
  unsigned long  deadlocks;              /* Deadlocks                         */
  unsigned long  lock_escals;            /* lock escalations                  */
  unsigned long  x_lock_escals;          /* X lock escalations                */
  unsigned long  lock_timeouts;          /* Lock timeouts                     */

  /****************************************************************************/
  /* Sorting Information                                                      */
  /****************************************************************************/
  unsigned long  total_sorts;            /* number of sorts                   */
  unsigned long  total_sort_time;        /* elapsed time spent in sorts       */
  unsigned long  sort_overflows;         /* number of sort overflows          */

  /****************************************************************************/
  /* Buffer Pool and I/O Information                                          */
  /****************************************************************************/
  unsigned long  pool_data_l_reads;      /* pool data logical reads           */
  unsigned long  pool_data_p_reads;      /* pool data physical reads          */
  unsigned long  pool_async_data_reads;  /* asynchronous pool data reads      */
  unsigned long  pool_data_writes;       /* pool data writes                  */
  unsigned long  pool_async_data_writes; /* asynchronous pool data writes     */
  unsigned long  pool_index_l_reads;     /* pool index logical reads          */
  unsigned long  pool_index_p_reads;     /* pool index physicl reads          */
  unsigned long  pool_index_writes;      /* pool index page writes            */
  unsigned long  pool_async_index_writes; /* asynchronous pool index writes   */
  unsigned long  pool_read_time;         /* Buff pool read time               */
  unsigned long  pool_write_time;        /* Buff pool write time              */
  unsigned long  pool_async_read_time;   /* asynchronous read time            */
  unsigned long  pool_async_write_time;  /* asynchronous write time           */
  unsigned long  pool_async_data_read_reqs; /* # async read requests          */
  unsigned long  pool_lsn_gap_clns;      /* LSN Gap cleaner triggers          */
  unsigned long  pool_drty_pg_steal_clns;    /* dirty page steal cleaner trig.*/
  unsigned long  pool_drty_pg_thrsh_clns;    /* dirty list threshold cln trig.*/
  unsigned long  direct_reads;           /* direct reads                      */
  unsigned long  direct_writes;          /* direct writes                     */
  unsigned long  direct_read_reqs;       /* direct read requests              */
  unsigned long  direct_write_reqs;      /* direct write requests             */
  unsigned long  direct_read_time;       /* direct read time                  */
  unsigned long  direct_write_time;      /* direct write time                 */

  unsigned long  files_closed;           /* files closed                      */

  /****************************************************************************/
  /* SQL statement counts                                                     */
  /****************************************************************************/
  unsigned long  commit_sql_stmts;       /* # of Commit SQL statements        */
  unsigned long  rollback_sql_stmts;     /* # of Rollback SQL statements      */
  unsigned long  dynamic_sql_stmts;      /* # of Dynamic SQL statements       */
  unsigned long  static_sql_stmts;       /* # of Static SQL statements        */
  unsigned long  failed_sql_stmts;       /* # of Failed SQL statements        */
  unsigned long  select_sql_stmts;       /* # of SQL select statements        */
  unsigned long  ddl_sql_stmts;          /* # of data definition lang. stmts  */
  unsigned long  uid_sql_stmts;          /* # of update/insert/delete stmts   */

  /****************************************************************************/
  /* Internal counts                                                          */
  /****************************************************************************/
  unsigned long  int_auto_rebinds;       /* # of interanl auto rebinds        */
  unsigned long  int_rows_deleted;       /* # of internal rows deleted        */
  unsigned long  int_rows_updated;       /* # of internal rows updated        */
  unsigned long  int_rows_inserted;      /* # of internal rows inserted       */
  unsigned long  int_commits;            /* # of internal commits             */
  unsigned long  int_rollbacks;          /* # of internal rollbacks           */

  /****************************************************************************/
  /* Row counts                                                               */
  /****************************************************************************/
  unsigned long  rows_deleted;           /* # of Rows Deleted                 */
  unsigned long  rows_inserted;          /* # of Rows Inserted                */
  unsigned long  rows_updated;           /* # of Rows Updated                 */
  unsigned long  rows_selected;          /* # of Rows Selected                */

  /****************************************************************************/
  /* Binds/Precompiles                                                        */
  /****************************************************************************/
  unsigned long  binds_precompiles;      /* # of Binds/Precomps/Rebinds       */

  /****************************************************************************/
  /* Timestamps                                                               */
  /****************************************************************************/
  sqlm_timestamp disconn_time;            /* Time of last database disconnect */

  /****************************************************************************/
  /* Application connection counters                                          */
  /****************************************************************************/
  unsigned long  total_cons;             /* Total Connects                    */
  unsigned long  connections_top;        /* High water mark for connections   */

  /****************************************************************************/
  /* Database memory pool high water marks                                    */
  /****************************************************************************/
  unsigned long  db_heap_top;            /* High water mark for dbheap        */


  /****************************************************************************/
  /* Logging Information                                                      */
  /****************************************************************************/
  unsigned long  sec_log_used_top;       /* Maximum secondary log space used  */
  unsigned long  tot_log_used_top;       /* Maximum total log space used      */
  unsigned long  log_reads;              /* # of log pages read               */
  unsigned long  log_writes;             /* # of log pages written            */

  /****************************************************************************/
  /* Package Cache Information                                                */
  /****************************************************************************/
  unsigned long  pkg_cache_lookups;     /* # of section lookups               */
  unsigned long  pkg_cache_inserts;     /* # of sections inserted into cache  */

  /****************************************************************************/
  /* Catalog Cache Information                                                */
  /****************************************************************************/
  unsigned long  cat_cache_lookups;     /* # of table descriptor lookups      */
  unsigned long  cat_cache_inserts;     /* # of table descriptors inserted    */
  unsigned long  cat_cache_overflows;   /* # of catalog cache overflows       */
  unsigned long  cat_cache_heap_full;   /* # of overflows due to db heap full */

  /****************************************************************************/
  /* Application Section Retrieval Information                                */
  /****************************************************************************/
  unsigned long  appl_section_lookups;  /* # of section lookups               */
  unsigned long  appl_section_inserts;  /* # of sections inserted             */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION5  Buffer Pool and I/O Information                     */
  /****************************************************************************/
  unsigned long  pool_async_index_reads; /* asynchronous pool index reads     */
  unsigned long  pool_data_to_estore;    /* #pages copied from BP to estore   */
  unsigned long  pool_index_to_estore;   /* #pages copied from BP to estore   */
  unsigned long  pool_index_from_estore; /* #pages copied from estore to BP   */
  unsigned long  pool_data_from_estore;  /* #pages copied from estore to BP   */
  unsigned long  prefetch_wait_time;    /* Time spent waiting for prefetch(ms)*/

  /****************************************************************************/
  /* SQLM_DBMON_VERSION5  Server details                                      */
  /****************************************************************************/
  unsigned long catalog_node;            /* catalog node number               */
  unsigned short server_platform;        /* OS on which the db manager runs   */
  char catalog_node_name[SQLM_LG_IDENT_SZ];/* Catalog network node name       */
}sqlm_db_event;


/******************************************************************************/
/*  Event Monitor Connection Event Record                                     */
/******************************************************************************/
typedef struct sqlm_conn_event
{
  unsigned long  size;                   /* event record size                 */
  unsigned long  event_type;             /* event type identifier             */
  char           appl_id[SQLM_APPLID_SZ];    /* Application Id                */
  char           sequence_no[SQLM_SEQ_SZ];   /* application id sequence number*/

  /****************************************************************************/
  /* Locking Information                                                      */
  /****************************************************************************/
  unsigned long  lock_waits;             /* Lock waits since appl. connect    */
  unsigned long  lock_wait_time;         /* total time waited on locks in ms  */
  unsigned long  lock_escals;            /* Lock Escalations since appl conn. */
  unsigned long  x_lock_escals;          /* X lock escals since appl connect  */
  unsigned long  deadlocks;              /* Deadlocks since appl. connect     */
  unsigned long  lock_timeouts;          /* Lock timeouts since 1st db connect*/

  /****************************************************************************/
  /* Sorting Information                                                      */
  /****************************************************************************/
  unsigned long  total_sorts;            /* Total Sorts since connect         */
  unsigned long  total_sort_time;        /* elapsed time spent in sorts       */
  unsigned long  sort_overflows;         /* number of sort overflows          */

  /****************************************************************************/
  /* Buffer Pool and I/O Information                                          */
  /****************************************************************************/
  unsigned long  pool_data_l_reads;      /* pool data logical reads since conn*/
  unsigned long  pool_data_p_reads;      /* pool data physical reads since con*/
  unsigned long  pool_data_writes;       /* pool data writes since 1st connect*/
  unsigned long  pool_index_l_reads;     /* pool indx logical reads since conn*/
  unsigned long  pool_index_p_reads;     /* pool indx physical reads since con*/
  unsigned long  pool_index_writes;      /* pool indx writes since 1st connect*/
  unsigned long  pool_read_time;         /* Buff pool read time since 1st conn*/
  unsigned long  pool_write_time;        /* Buff pool write time since 1st con*/
  unsigned long  direct_reads;           /* direct reads since connect        */
  unsigned long  direct_writes;          /* direct writes since connect       */
  unsigned long  direct_read_reqs;       /* direct read requests since conn   */
  unsigned long  direct_write_reqs;      /* direct write requests since conn  */
  unsigned long  direct_read_time;       /* direct read time since connect    */
  unsigned long  direct_write_time;      /* direct write time since connect   */

  /****************************************************************************/
  /* SQL statement counts                                                     */
  /****************************************************************************/
  unsigned long  commit_sql_stmts;       /* # of Commit SQL stmts since conn  */
  unsigned long  rollback_sql_stmts;     /* # of Rollback SQL stmts since conn*/
  unsigned long  dynamic_sql_stmts;      /* # of Dynamic SQL stmts since conn */
  unsigned long  static_sql_stmts;       /* # of Static SQL stmts since conn  */
  unsigned long  failed_sql_stmts;       /* # of Failed SQL stmts since conn  */
  unsigned long  select_sql_stmts;       /* # of SQL select stmts since conn  */
  unsigned long  ddl_sql_stmts;          /* # of data definition lang. stmts  */
  unsigned long  uid_sql_stmts;          /* # of update/insert/delete stmts   */

  /****************************************************************************/
  /* Internal counts                                                          */
  /****************************************************************************/
  unsigned long  int_auto_rebinds;       /* # of Auto Rebinds since connect   */
  unsigned long  int_rows_deleted;       /* # of internal deletes since conn  */
  unsigned long  int_rows_updated;       /* # of internal updates since conn  */
  unsigned long  int_rows_inserted;      /* # of internal inserts since conn  */
  unsigned long  int_commits;            /* # of int. Commits since 1st conn  */
  unsigned long  int_rollbacks;          /* # of int. Rollbacks since 1st conn*/
  unsigned long  int_deadlock_rollbacks; /* # of Rollbacks due to deadlock    */
                                         /*      since 1st connect            */

  /****************************************************************************/
  /* Row counts                                                               */
  /****************************************************************************/
  unsigned long  rows_deleted;           /* # of Rows Deleted since connect   */
  unsigned long  rows_inserted;          /* # of Rows Inserted since connect  */
  unsigned long  rows_updated;           /* # of Rows Updated since connect   */
  unsigned long  rows_selected;          /* # of Rows Selected since connect  */
  unsigned long  rows_read;              /* # of Rows read since connect      */
  unsigned long  rows_written;           /* # of Rows written since connect   */

  /****************************************************************************/
  /* Binds/Precompiles                                                        */
  /****************************************************************************/
  unsigned long  binds_precompiles;      /* # of Binds/Precomps/Rebinds       */

  /****************************************************************************/
  /* Blocking Cursor Information                                              */
  /****************************************************************************/
  unsigned long  rej_curs_blk;          /* Rejected block cursor requests     */
  unsigned long  acc_curs_blk;          /* Accepted block cursor requests     */

  /****************************************************************************/
  /* Timestamps                                                               */
  /****************************************************************************/
  sqlm_timestamp  disconn_time;         /* Disconnection  date/time           */

  /****************************************************************************/
  /* Agents activity                                                          */
  /****************************************************************************/
  sqlm_time       user_cpu_time;    /* Total user CPU time of appl agents     */
  sqlm_time       system_cpu_time;  /* Total system CPU time of appl agents   */

  /****************************************************************************/
  /* Package Cache Information                                                */
  /****************************************************************************/
  unsigned long  pkg_cache_lookups;     /* # of section lookups               */
  unsigned long  pkg_cache_inserts;     /* # of sections inserted into cache  */

  /****************************************************************************/
  /* Catalog Cache Information                                                */
  /****************************************************************************/
  unsigned long  cat_cache_overflows;   /* # of catalog cache overflows       */
  unsigned long  cat_cache_heap_full;   /* # of overflows due to db heap full */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION5                                                      */
  /****************************************************************************/
  unsigned long  appl_section_lookups;  /* # of section lookups               */
  unsigned long  appl_section_inserts;  /* # of sections inserted             */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION5  Buffer Pool and I/O Information                     */
  /****************************************************************************/
  unsigned long  prefetch_wait_time;     /* Time waited for prefetch (ms)     */
  unsigned long  pool_data_to_estore;    /* #pages copied from BP to estore   */
  unsigned long  pool_index_to_estore;   /* #pages copied from BP to estore   */
  unsigned long  pool_index_from_estore; /* #pages copied from estore to BP   */
  unsigned long  pool_data_from_estore;  /* #pages copied from estore to BP   */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION5                                                      */
  /****************************************************************************/
  unsigned long  authority_lvl;          /* user authorizations               */
  unsigned long  coord_node;             /* coordinating node number          */
  long           appl_priority;          /* priority at which appl agents work*/
  unsigned long  appl_priority_type;     /* dynamic or static                 */
  unsigned long  agent_id;               /* Application handle                */
}sqlm_conn_event;


/******************************************************************************/
/*  Event Monitor Table Event Record                                          */
/******************************************************************************/
typedef struct sqlm_table_event
{
  unsigned long  size;                   /* event record size                 */
  unsigned long  event_type;             /* event type identifier             */
  char           table_name[SQLM_IDENT_SZ];     /* the name of the table      */
  char           table_schema[SQLM_IDENT_SZ];   /* the name of the table      */
  unsigned long  table_type;             /* table type                        */
  unsigned long  rows_written;           /* number of changes to the table    */
  unsigned long  rows_read;              /* number of reads from the table    */
  unsigned long  overflow_accesses;      /* no. of accesses to overflow rec   */
  sqlm_timestamp table_event_time;       /* Table Event Date and Time         */

}sqlm_table_event;

/******************************************************************************/
/*  Event Monitor Statement record                                            */
/******************************************************************************/
/* NOTE: Text follows the record, its length is rounded up to a 4 bytes       */
/*       boundary, and the text is padded with blanks. It is *NOT* null       */
/*       terminated.  For example:                                            */
/*          +-------------------------+----------------------+                */
/*          |sqlm_stmt_event          |"SELECT * FROM T18   "|                */
/*          |  size:             352  |                      |                */
/*          |  stmt_length:       20  |                      |                */
/*          |  stmt_text_offset: 332  |                      |                */
/*          +-------------------------+----------------------+                */
/*----------------------------------------------------------------------------*/
typedef struct sqlm_stmt_event
{
  unsigned long  size;                   /* event record size *INCLUDING*     */
                                         /* dynamic SQL statement text        */
  unsigned long  event_type;             /* Always set to SQLM_EVENT_STMT     */
  char           appl_id[SQLM_APPLID_SZ];    /* Application Id                */
  char           sequence_no[SQLM_SEQ_SZ];   /* Application Id sequence number*/
  unsigned long  stmt_type;              /* type of stmt: Dynamic or static   */
  unsigned long  operation;              /* Statement Operation               */
  unsigned long  fetch_count;            /* Count of fetches                  */
  unsigned long  section_number;         /* Section Number                    */
  sqlm_timestamp start_time;             /* SQL statement operation start time*/
  sqlm_timestamp stop_time;              /* SQL statement operation stop time */
  char           cursor_name[SQLM_IDENT_SZ];  /* sql stmt.cursor name         */
  char           creator[SQLM_IDENT_SZ];      /* auth id for precompile       */
  char           package_name[SQLM_IDENT_SZ]; /* Package Name                 */
  sqlm_time      user_cpu_time;         /* Total user CPU time of statement   */
  sqlm_time      system_cpu_time;       /* Total system CPU time of statement */
  unsigned long  total_sorts;           /* Total number of sorts for this stmt*/
  unsigned long  total_sort_time;       /* Total sort time for this statement */
  unsigned long  sort_overflows;        /* # of sort overflows for this stmt  */
  unsigned long  rows_read;             /* # of rows read by this statement   */
  unsigned long  rows_written;          /* # of rows upd/ins/del for this stmt*/
  unsigned long  int_rows_deleted;      /* # of internal deletes by the stmt  */
  unsigned long  int_rows_updated;      /* # of internal updates by the stmt  */
  unsigned long  int_rows_inserted;     /* # of internal inserts by the stmt  */
  struct sqlca   sqlca;                 /* sqlca from statement               */
  unsigned long  agent_id;              /* Application handle                 */
  unsigned long  agents_top;            /* # of agents created for statement  */
  unsigned short stmt_length;           /* length of SQL text, 0 if none. It  */
                                        /* is only returned for dynamic SQL   */
  unsigned short stmt_text_offset;      /* offset from sqlm_stmt_event start  */
}sqlm_stmt_event;

/* The following event is only logged by VERSION 2 servers                    */
/* Starting with UDB V5, the text became part of the sqlm_stmt_event          */
typedef struct sqlm_stmttext_event /* OBSOLETE */
{
  unsigned long  size;                   /* event record size                 */
                                         /* INCLUDES statement text           */
  unsigned long  event_type;             /* Set to SQLM_EVENT_STMTTEXT        */
  char           appl_id[SQLM_APPLID_SZ];    /* Application Id                */
  char           sequence_no[SQLM_SEQ_SZ];   /* application id sequence number*/
  char           creator[SQLM_IDENT_SZ];      /* auth id for precompile       */
  char           package_name[SQLM_IDENT_SZ]; /* Package Name                 */
  unsigned long  section_number;         /* Section Number                    */
  unsigned long  stmt_length;           /* length of SQL statement following  */
  char           stmt_text[1];          /* dynamic sql statement text         */
}sqlm_stmttext_event; /* OBSOLETE */

typedef struct sqlm_subsection_event
{
  unsigned long  size;              /* event record size                      */
  unsigned long  event_type;        /* Set to SQLM_EVENT_SUBSECTION           */

  unsigned long  agent_id;          /* Application handle                     */
  unsigned short ss_number;         /* Subsection number                      */
  unsigned short ss_node_number;    /* Node where the subsection was executed */

  /* Execution stats */
  unsigned long  ss_exec_time;      /* total (elapsed) Execution time in ms   */
  sqlm_time      ss_usr_cpu_time;   /* total user CPU time (sec.microsec)     */
  sqlm_time      ss_sys_cpu_time;   /* total system CPU time (sec.microsec)   */

  /* Tablequeue information */
  unsigned long  tq_tot_send_spills;/* total # of buffers overflowed to a     */
                                    /*  temp table when sending data on a tq  */
  unsigned long  tq_max_send_spills;/* maximum # of tq buffers overflowed     */
  unsigned long  tq_rows_read;      /* Total # rows received on tablequeues   */
  unsigned long  tq_rows_written;   /* Total # rows sent on tablequeues       */
  unsigned short num_agents;        /* # agents that were executing this ss.  */
}sqlm_subsection_event;

/******************************************************************************/
/*  Event Monitor Transaction Event Record                                    */
/******************************************************************************/
typedef struct sqlm_xaction_event
{
  unsigned long  size;                   /* event record size                 */
  unsigned long  event_type;                 /* event type identifier         */
  char           appl_id[SQLM_APPLID_SZ];    /* Application Id                */
  char           sequence_no[SQLM_SEQ_SZ];   /* application id sequence number*/
  unsigned long  log_space_used;        /* Log space used in transaction      */
  unsigned long  status;                /* transaction completion status      */
  unsigned long  lock_wait_time;        /* transaction lock wait time (ms)    */
  unsigned long  locks_held_top;        /* max locks held in transaction      */
  unsigned long  lock_escals;           /* # of lock escalation in transaction*/
  unsigned long  x_lock_escals;         /* # of x lock escals in transaction  */
  unsigned long  rows_read;             /* # of rows read by this transaction */
  unsigned long  rows_written;          /* # of rows upd/ins/del for this xact*/
  sqlm_time      user_cpu_time;         /* Total user CPU time of transaction */
  sqlm_time      system_cpu_time;       /* Total system CPU time of xaction   */
  sqlm_timestamp prev_stop_time;        /* prev commit or rollback time       */
  sqlm_timestamp start_time;            /* time trans exec started            */
  sqlm_timestamp stop_time;             /* trans stop time                    */
  unsigned long  agent_id;              /* Application handle                 */
}sqlm_xaction_event;


/******************************************************************************/
/*  Event Monitor Deadlock and Deadlocked Connection Event Records            */
/******************************************************************************/
typedef struct sqlm_deadlock_event
{
  unsigned long  size;                       /* event record size             */
  unsigned long  event_type;                 /* event type identifier         */
  unsigned long  dl_conns;                   /* number of conns deadlocked    */
  sqlm_timestamp start_time;                 /* Time when deadlock detected   */
  char           rolled_back_appl_id[SQLM_APPLID_SZ]; /* victim's appl id     */
  char           rolled_back_sequence_no[SQLM_SEQ_SZ]; /* victim's seq no.    */
  unsigned long  rolled_back_agent_id;       /* Application handle            */
}sqlm_deadlock_event;

typedef struct sqlm_dlconn_event
{
  unsigned long  size;                       /* event record size             */
  unsigned long  event_type;                 /* event type identifier         */
  char           appl_id[SQLM_APPLID_SZ];    /* Application Id                */
  char           sequence_no[SQLM_SEQ_SZ];   /* application id sequence number*/
  char           appl_id_holding_lk[SQLM_APPLID_SZ]; /* id of appl holding lk */
  char           sequence_no_holding_lk[SQLM_SEQ_SZ]; /* seq no. holding lock */
  char           table_name[SQLM_IDENT_SZ];   /* name of tb of lock waited on */
  char           table_schema[SQLM_IDENT_SZ]; /* table schema of lk waited on */
  char           tablespace_name[SQLM_IDENT_SZ];  /* name of the tablespace   */
  unsigned long  lock_mode;              /* Mode of Lock waited on            */
  unsigned long  lock_object_type;       /* Lock Obj type for lock waited on  */
  unsigned long  lock_object_name;       /* Waited On lock obj name           */
  sqlm_timestamp lock_wait_start_time;   /* Time when lock wait started       */
  sqlm_timestamp start_time;             /* Time when deadlock detected       */
  unsigned long  lock_node;              /* Node on which app waited for lock */
  unsigned long  agent_id;               /* Application handle                */
}sqlm_dlconn_event;

/******************************************************************************/
/*  Event Monitor Tablespace Event Record                                     */
/******************************************************************************/
typedef struct sqlm_tablespace_event
{
  unsigned long  size;                   /* event record size                 */
  unsigned long  event_type;             /* event type identifier             */

  char           tablespace_name[SQLM_IDENT_SZ];  /* name of tablespace       */
  unsigned long  pool_data_l_reads;      /* pool data logical reads since conn*/
  unsigned long  pool_data_p_reads;      /* pool data physical reads since con*/
  unsigned long  pool_async_data_reads;  /* asynchronous pool data reads      */
  unsigned long  pool_data_writes;       /* pool data writes since connect    */
  unsigned long  pool_async_data_writes; /* asynchronous pool data writes     */
  unsigned long  pool_index_l_reads;     /* pool index logical reads since con*/
  unsigned long  pool_index_p_reads;     /* pool index physical reads since cn*/
  unsigned long  pool_index_writes;      /* pool index writes since connect   */
  unsigned long  pool_async_index_writes; /* asynchronous pool index writes   */
  unsigned long  pool_read_time;         /* Buff pool read time since 1st conn*/
  unsigned long  pool_write_time;        /* Buff pool write time since 1st con*/
  unsigned long  pool_async_read_time;   /* asynchronous read time            */
  unsigned long  pool_async_write_time;  /* asynchronous write time           */
  unsigned long  pool_async_data_read_reqs; /* # async read requests          */

  unsigned long  direct_reads;           /* direct reads since 1st connect    */
  unsigned long  direct_writes;          /* direct writes since 1st conn      */
  unsigned long  direct_read_reqs;       /* direct read requests              */
  unsigned long  direct_write_reqs;      /* direct write requests             */
  unsigned long  direct_read_time;       /* direct read time since 1st conn   */
  unsigned long  direct_write_time;      /* direct write time since 1st conn  */

  unsigned long  files_closed;           /* files closed since first db conn  */
  sqlm_timestamp ts_event_time;          /* Tablespace event date and time    */

  /****************************************************************************/
  /* SQLM_DBMON_VERSION5  Buffer Pool and I/O Information                     */
  /****************************************************************************/
  unsigned long  pool_async_index_reads; /* asynchronous pool index reads     */
  unsigned long  pool_data_to_estore;    /* #pages copied from BP to estore   */
  unsigned long  pool_index_to_estore;   /* #pages copied from BP to estore   */
  unsigned long  pool_index_from_estore; /* #pages copied from estore to BP   */
  unsigned long  pool_data_from_estore;  /* #pages copied from estore to BP   */
}sqlm_tablespace_event;


/******************************************************************************/
/*  Event Monitor Database Header Event Record                                */
/******************************************************************************/
typedef struct sqlm_dbheader_event
{
  unsigned long  size;                    /* event record size                */
  unsigned long  event_type;              /* event type identifier            */
  char           db_name[SQLM_IDENT_SZ];  /* Database name                    */
  char           db_path[SQLM_DBPATH_SZ]; /* Database Path                    */
  sqlm_timestamp conn_time;               /* Time of 1st database connection  */

}sqlm_dbheader_event;


/******************************************************************************/
/*  Event Monitor Start Event Record                                          */
/******************************************************************************/
typedef struct sqlm_evmon_start_event
{
  unsigned long  size;                    /* event record size                */
  unsigned long  event_type;              /* event type identifier            */
  sqlm_timestamp start_time;              /* Time event monitor started       */
} sqlm_evmon_start_event;

/******************************************************************************/
/*  Event Monitor Connection Header Event Record                              */
/******************************************************************************/
typedef struct sqlm_connheader_event
{
  unsigned long  size;                       /* event record size             */
  unsigned long  event_type;                 /* event type identifier         */
  char           appl_id[SQLM_APPLID_SZ];    /* Application Id                */
  char           sequence_no[SQLM_SEQ_SZ];   /* application id sequence number*/
  char           corr_token[SQLM_APPLID_SZ]; /* DRDA AS Correlation Token     */
  char           appl_name[SQLM_IDENT_SZ];   /* Application Program Name      */
  char           auth_id[SQLM_IDENT_SZ];     /* Authorization Id              */
  char           execution_id[SQLM_IDENT_SZ]; /* Login ID                     */
  char           client_nname[SQLM_IDENT_SZ]; /* Config NNAME of client       */
  char           client_prdid[SQLM_IDENT_SZ]; /* product/version on client    */
  char           client_db_alias[SQLM_IDENT_SZ]; /* Client Database Alias     */
  unsigned long  client_pid;                 /* PID of client                 */
  unsigned long  agent_id;                   /* Application handle            */
  unsigned short codepage_id;                /* codepage at client node       */
  unsigned short country_code;               /* country code of client app    */
  unsigned short client_platform;            /* platform of client app        */
  unsigned short client_protocol;            /* Comms protocol of client      */
  sqlm_timestamp conn_time;                  /* Connect start date/time       */
  unsigned short node_number;                /* Node number conn was establ.  */
  char           pad[2];                     /* for 4 bytes memory alignment  */
} sqlm_connheader_event;

/******************************************************************************/
/*  Event Monitor Overflow Event Record                                       */
/******************************************************************************/
typedef struct sqlm_overflow_event
{
  unsigned long  size;                       /* event record size             */
  unsigned long  event_type;                 /* event type identifier         */
  unsigned long  count;                      /* The number of overflows       */
  sqlm_timestamp first_overflow_time;        /* The time of the first overflow*/
  sqlm_timestamp last_overflow_time;         /* The time of the last overflow */
  unsigned short node_number;                /* Node on which overflow occured*/
  char           pad[2];                     /* padding for word alignment    */
} sqlm_overflow_event;

/******************************************************************************/
/*  Event Monitor Bufferpool Event Record                                     */
/******************************************************************************/
typedef struct sqlm_bufferpool_event
{
  unsigned long  size;        /* Use instead of sizeof(sqlm_bufferpool_event) */
  unsigned long  event_type;  /* always set to SQLM_EVENT_BUFFERPOOL          */
  sqlm_timestamp event_time;  /* GMT time in seconds.microsec since 01/01/70  */
  char           bp_name[SQLM_IDENT_SZ];           /* Bufferpool name         */
  char           db_name[SQLM_IDENT_SZ];           /* Database name           */
  char           db_path[SQLM_DBPATH_SZ];          /* Database Path           */
  sqlm_bp_info   bp_info;     /* total stats from all tspaces for this bp     */
} sqlm_bufferpool_event;

/******************************************************************************/
/* VERSION 1 - Data structure sizes  - *****OBSOLETE***** -                   */
/* ****DON'T USE THESE CONSTANTS**** THEY ARE PROVIDED FOR COMPATIBILITY ONLY */
/******************************************************************************/
#define SQLM_APPLINFO_SZ        492    /* size of V1 sqlm_applinfo struct     */
#define SQLM_DB2_SZ             100    /* size of V1 sqlm_db2 structure       */
#define SQLM_DBASE_SZ           548    /* size of V1 sqlm_dbase structure     */
#define SQLM_TABLE_HEADER_SZ    356    /* size of V1 sqlm_table_header struct */
#define SQLM_TABLE_SZ           60     /* size of V1 sqlm_table structure     */
#define SQLM_APPL_SZ            880    /* size of V1 sqlm_appl structure      */
#define SQLM_DBASE_LOCK_SZ      352    /* size of V1 sqlm_dbase_lock struct   */
#define SQLM_APPL_LOCK_SZ       216    /* size of V1 sqlm_appl_lock struct    */
#define SQLM_LOCK_SZ            60     /* size of V1 sqlm_lock structure      */
#define SQLM_COLLECTED_SZ       232    /* size of V1 sqlm_collected structure */
#define SQLM_DCS_APPLINFO_SZ    260    /* size of V1 sqlm_dcs_applinfo struct */
#define SQLM_TIMESTAMP_SZ       sizeof(sqlm_timestamp)

/******************************************************************************/
/* Database Monitor APIs                                                      */
/******************************************************************************/

/* Set or query Database Monitor switch settings */
int SQL_API_FN sqlmon(unsigned long        version,       /* Version Id       */
                      _SQLOLDCHAR          *reserved,     /* reserved         */
                      sqlm_recording_group group_states[],
                                      /* monitor switches and current states  */
                      struct sqlca         *sqlca         /* sqlca            */
                     );

/* Take a Snapshot of some Database System Monitor data */
int SQL_API_FN sqlmonss(unsigned long     version,        /* Version id       */
                        _SQLOLDCHAR       *reserved,      /* reserved         */
                        sqlma             *sqlma_ptr,     /* monitoring area  */
                        unsigned long     buffer_length,  /* buffer length    */
                        void              *buffer_area,   /* buffer area      */
                        sqlm_collected    *collected,     /* num collected    */
                        struct sqlca      *sqlca          /* sqlca            */
                       );

/* Estimate the buffer size that user need to allocate for sqlmonss */
int SQL_API_FN sqlmonsz(unsigned long         version,    /* Version id       */
                        _SQLOLDCHAR           *reserved,  /* reserved         */
                        sqlma                 *sqlma_ptr, /* sqlma pointer    */
                        unsigned long         *buff_size, /* est. buffer sz   */
                        struct sqlca          *sqlca      /* sqlca structure  */
                       );

/* Re-initialize Database System Monitor data */
int SQL_API_FN sqlmrset(unsigned long          version,   /* Version Id       */
                        _SQLOLDCHAR            *reserved, /* reserved         */
                        unsigned long          reset_all, /* reset db or all  */
                        _SQLOLDCHAR            *db_alias, /* ptr to db_alias  */
                        struct sqlca           *sqlca     /* sqlca            */
                       );


/******************************************************************************/
/* Database Monitor Generic APIs                                              */
/******************************************************************************/

/* Generic Database Monitor Switch API  */
int SQL_API_FN sqlgmon
   (
     unsigned long          reserved_lgth,   /* length of reserved field      */
     struct   sqlca         *sqlca,          /* pointer to sqlca              */
     sqlm_recording_group   group_states[],  /* ptr to returned states        */

     _SQLOLDCHAR            *reserved,       /* reserved for future use       */
     unsigned long          version          /* Version id                    */
   );


/* Generic Database Monitor Snapshot API */
int SQL_API_FN sqlgmnss
   (
     unsigned long           reserved_lgth,  /* length of reserved field      */
     struct   sqlca          *sqlca,         /* pointer to sqlca              */
     sqlm_collected          *collected,     /* pointer to # collected        */
     void                    *buffer_area,   /* pointer to buffer area        */
     unsigned long           buffer_length,  /* length of buffer              */
     sqlma                   *sqlma_ptr,     /* pointer to monitor area       */
     _SQLOLDCHAR             *reserved,      /* reserved for future use       */
     unsigned long           version         /* Version id                    */
   );


/* Generic Database Monitor Estimate Buffer Size API */
int SQL_API_FN sqlgmnsz
   (
     unsigned long           reserved_lgth,  /* length of reserved field      */
     struct   sqlca          *sqlca,         /* pointer to sqlca              */
     unsigned long           *buff_size,     /* length of buffer              */
     sqlma                   *sqlma_ptr,     /* pointer to sqlma              */
     _SQLOLDCHAR             *reserved,      /* reserved for future use       */
     unsigned long           version         /* Version id                    */
   );



/* Generic Database Monitor Reset API */
int SQL_API_FN sqlgmrst
   (
     unsigned short           dbnamel,       /* length of database            */
     unsigned long            reserved_lgth, /* length of reserved field      */
     struct   sqlca           *sqlca,        /* pointer to sqlca              */
     _SQLOLDCHAR              *db_alias,     /* database alias                */
     unsigned long            reset_all,     /* reset db or all info          */
     _SQLOLDCHAR              *reserved,     /* reserved for future use       */
     unsigned long            version        /* Version id                    */
   );

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
#endif  /* SQL_H_SQLMON */
