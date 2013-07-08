/******************************************************************************
** 
** Source File Name: SQLUTIL
** 
** (C) COPYRIGHT International Business Machines Corp. 1987, 1997
** All Rights Reserved
** Licensed Materials - Property of IBM
** 
** US Government Users Restricted Rights - Use, duplication or
** disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
** 
** Function = Include File defining:
**              Utility / Configuration Commands - Constants
**              Utility / Configuration Commands - Data Structures
**              Utility / Configuration Commands - Function Prototypes
**              Utility / Configuration Commands - Labels for SQLCODES
** 
** Operating System: Windows NT
** 
*******************************************************************************/
#ifndef SQL_H_SQLUTIL
#define SQL_H_SQLUTIL

#ifdef __cplusplus
extern "C" {
#endif

/* Note: _SQLOLDCHAR defaults to 'char'.  See sqlsystm.h for details.         */

#include "sql.h"                       /* Includes sqlca.h & sqlsystm.h */

#pragma pack(4)

/* Interface Parameters/Structures/Return Codes                               */

/* Parameters for Rollforward caller action                                   */
#define SQLUM_ROLLFWD          1       /* Roll forward to requested point     */
#define SQLUM_STOP             2       /* End roll-forward recovery           */
#define SQLUM_COMPLETE         2       /* End roll-forward recovery           */
#define SQLUM_ROLLFWD_STOP     3       /* Roll forward to requested point     */
                                       /* and end roll-forward recovery       */
#define SQLUM_ROLLFWD_COMPLETE 3       /* Roll forward to requested point     */
                                       /* and end roll-forward recovery       */
#define SQLUM_QUERY            4       /* Query nextArcFile, firstDeleteArc,  */
                                       /* lastDeleteArc, lastCommitTime       */
#define SQLUM_CANCEL           8       /* Cancel current rollforward          */
#define SQLUM_PARM_CHECK       10      /* Parameter check                     */
#define SQLUM_LOADREC_CONTINUE 11      /* Continue load recovery.             */
#define SQLUM_LOADREC_TERMINATE 12     /* Terminate load recovery.            */
#define SQLUM_LOADREC_DEVICE_TERMINATE 13 /* Terminate device.Caller action   */
                                       /* codes 31 - 50 reserved for          */
                                       /* internal use.                       */

/* Constants used for Rollforward                                             */
#define SQLUM_INFINITY_TIMESTAMP "9999-12-31-23.59.59.999999" /* Roll         */
                                       /* forward until STOP specified        */
#define SQLUM_ARCHIVE_FILE_LEN 12      /* Length of Archive File name         */
#define SQLUM_TIMESTAMP_LEN    26      /* Length of ISO format Timestamp      */

/* Roll forward input version values                                          */
#define SQLUM_RFWD_VERSION     3       /* current rollforward input version   */

/* Roll forward allNodeFlag values                                            */
#define SQLURF_NODE_LIST       0       /* submit to all nodes in the node     */
                                       /* list                                */
#define SQLURF_ALL_NODES       1       /* submit to all nodes in the          */
                                       /* nodeconfiguration file              */
#define SQLURF_ALL_EXCEPT      2       /* submit to all nodes except the      */
                                       /* onesspecified by the nodelist       */
                                       /* parameter                           */
#define SQLURF_CAT_NODE_ONLY   3       /* submit to catalog node only         */

/* Roll forward query status codes                                            */
#define SQLURFQ_NOT_AVAILABLE  0       /* cannot query node                   */
#define SQLURFQ_NOT_RFW_PENDING 1      /* rollforward is not pending          */
#define SQLURFQ_DB_RFW_PENDING 2       /* database rollforward pending        */
#define SQLURFQ_TBL_RFW_PENDING 3      /* tablespace rollforward pending      */
#define SQLURFQ_DB_RFW_IN_PROGRESS 4   /* database rollforward in progress    */
#define SQLURFQ_TBL_RFW_IN_PROGRESS 5  /* tablespace rollforward in progress  */
#define SQLURFQ_DB_RFW_STOPPING 6      /* database rollforward processing     */
                                       /* STOP                                */
#define SQLURFQ_TBL_RFW_STOPPING 7     /* tablespace rollforward processing   */
                                       /* STOP                                */

/* Rollforward connect mode                                                   */
#define SQLUM_OFFLINE          0x0     /* Offline rollforward mode            */
#define SQLUM_ONLINE           0x1     /* Online rollforward mode             */

/* Backup mode                                                                */
#define SQLUB_OFFLINE          0x0     /* Offline backup mode                 */
#define SQLUB_ONLINE           0x1     /* Online backup mode                  */

/* Backup type                                                                */
#define SQLUB_FULL             0
#define SQLUB_TABLESPACE       3

/* Backup calling action values                                               */
#define SQLUB_BACKUP           0       /* initial call                        */
#define SQLUB_CONTINUE         1       /* Subsequent call                     */
#define SQLUB_TERMINATE        2       /* Terminating call                    */
#define SQLUB_NOINTERRUPT      3       /* Initial call to run without         */
                                       /* prompting                           */
#define SQLUB_DEVICE_TERMINATE 9       /* End media device.                   */
#define SQLUB_PARM_CHECK       10      /* for parameter check and             */
                                       /* initialization.                     */
#define SQLUB_PARM_CHECK_INIT_AND_WAIT 10 /* for parameter check and          */
                                       /* initialization.                     */
#define SQLUB_PARM_CHECK_ONLY  11      /* for parameter checking only.        */

/* Restore rollforward mode                                                   */
#define SQLUD_ROLLFWD          0x0
#define SQLUD_NOROLLFWD        0x1

/* Restore mode                                                               */
#define SQLUD_OFFLINE          0x0     /* Offline restore mode                */
#define SQLUD_ONLINE           0x1     /* Online restore mode                 */

/* Restore calling action values                                              */
#define SQLUD_RESTORE          0       /* initial call                        */
#define SQLUD_CONTINUE         1       /* Subsequent call                     */
#define SQLUD_TERMINATE        2       /* Terminating call                    */
#define SQLUD_NOINTERRUPT      3       /* Initial call to run without         */
                                       /* prompting                           */
#define SQLUD_DEVICE_TERMINATE 9       /* End media device.                   */
#define SQLUD_PARM_CHECK       10      /* for parameter check and             */
                                       /* initialization.                     */
#define SQLUD_PARM_CHECK_INIT_AND_WAIT 10 /* for parameter check and          */
                                       /* initialization.                     */
#define SQLUD_PARM_CHECK_ONLY  11      /* for parameter checking only.        */
#define SQLUD_RESTORE_TABLESPACE_LIST 12 /* list of tablespaces/containers.   */
#define SQLUD_RESTORE_STORDEF  100     /* initial call, tablespace container  */
                                       /* redefinition requested              */
#define SQLUD_STORDEF_NOINTERRUPT 101  /* initial call, tablespace container  */
                                       /* redefinition requested without      */
                                       /* prompting                           */

/* Restore type                                                               */
#define SQLUD_FULL             0
#define SQLUD_ONLINE_TABLESPACE 3
#define SQLUD_TABLESPACE       4
#define SQLUD_HISTORY          5
/* The following are not supported in V2.1.0                                  */
#define SQLUD_TABLESPACE_TBL   6
#define SQLUD_HIST_TBLSPACE_TBL 7

/* Backup/Restore Definitions                                                 */
#define SQLU_ALIAS_SZ          8       /* length of database alias name       */
#define SQLU_USERID_LEN        1024    /* Maximum length of userid            */
#define SQLU_PWD_LEN           8       /* length of password                  */
#define SQLU_TIME_STAMP_LEN    14      /* length of the backup timestamp in   */
                                       /* yyyymmddhhmmss format               */

#define SQLU_INSTNAME_SZ       8       /* max length of an instance name      */
/* length of filename of backup image:                                        */
/* dbalias.type.db2instance.node.timestamp.seq                                */
#define SQLU_BACKUP_NAME_SZ    (SQLU_ALIAS_SZ+5+SQLU_INSTNAME_SZ+5+SQLU_TIME_STAMP_LEN+4)

/* length of directory where backup file will reside:dir - '/' - filename     */
#define SQLU_BACKUP_DIR_SZ     (1023-1-SQLU_BACKUP_NAME_SZ)

/* Data map separator for LOAD utility;  Partition Key Identifier             */
#define SQL_HEADER_DATA_SEPARATOR "===PDB==="
#define SQLU_PARTITIONKEY      "Key:"

/* Parameters for Backup/Restore old api's                                    */
#define SQLU_NSD_ID            '0'     /* User exit used, not SD interface    */

/* Media type for old api's                                                   */
#define SQLUB_MEDIA_TARGET     0x0
#define SQLUB_ADSM             0x1
#define SQLUB_OTHER            0x2

/* Old OS/2 Backup/restore media type values                                  */
#define SQLUD_MEDIA_SRC        0x0
#define SQLUD_ADSM             0x1
#define SQLUD_OTHER            0x2

/* Parameters for SQLUHPRN force option                                       */
#define SQLUH_NO_FORCE         0
#define SQLUH_FORCE            1

/* Parameters for SQLUHOPS caller action                                      */
#define SQLUH_LIST_BACKUP      0
#define SQLUH_LIST_HISTORY     1

/* History File structure sizes                                               */
#define SQLUH_OP_SZ            1
#define SQLUH_OBJ_SZ           1
#define SQLUH_OBJPART_SZ       17
#define SQLUH_OPTYPE_SZ        1
#define SQLUH_DEVTYPE_SZ       1
#define SQLUH_FIRSTLOG_SZ      12
#define SQLUH_LASTLOG_SZ       12
#define SQLUH_BACKID_SZ        14
#define SQLUH_TCREATE_SZ       8
#define SQLUH_TNAME_SZ         18
#define SQLUH_NUMTABLESPACE_SZ 5
#define SQLUH_LOC_SZ           255
#define SQLUH_COMMENT_SZ       30
#define SQLUH_TABLESPACENAME_SZ 18

/* Parameters for RUNSTATS                                                    */
#define SQL_STATS_TABLE           'T'  /* TABLEOPT = Table w/o Indexes        */
#define SQL_STATS_BOTH            'B'  /* TABLEOPT = Table and Indexes        */
#define SQL_STATS_INDEX           'I'  /* TABLEOPT = Indexes w/o Table        */
#define SQL_STATS_EXTTABLE_ONLY   'D'  /* TABLEOPT = Table and dist stats     */
#define SQL_STATS_EXTTABLE_INDEX  'E'  /* TABLEOPT = Table and dist stats     */
                                       /* and basic indexes                   */
#define SQL_STATS_EXTINDEX_ONLY   'X'  /* TABLEOPT = Ext stats for indexes    */
                                       /* only                                */
#define SQL_STATS_EXTINDEX_TABLE  'Y'  /* TABLEOPT = Ext stats for indexes    */
                                       /* and basic table stats               */
#define SQL_STATS_ALL             'A'  /* TABLEOPT = Ext stats for indexes    */
                                       /* and table with dist stats           */
#define SQL_STATS_REF             'R'  /* SHAREOPT = Reference                */
#define SQL_STATS_CHG             'C'  /* SHAREOPT = Change                   */

#define SQLU_STATS_NONE           ' '  /* TABLEOPT - no statistics are to be  */
                                       /* gathered - Load only                */

/* Parameters for selection method in sqldcol                                 */
#define SQL_METH_N             78      /* Names                               */
#define SQL_METH_P             80      /* Positional                          */
#define SQL_METH_D             68      /* Default                             */
#define SQL_METH_L             76      /* Locations                           */

/* File Types for Import/Export                                               */
#define SQL_IXF                "IXF"
#define SQL_WSF                "WSF"
#define SQL_DEL                "DEL"
#define SQL_ASC                "ASC"
#define SQL_DB2CS              "DB2CS" /* load/unload                         */

/* Communication Protocols                                                    */
#define SQLF_PROTOCOL_TCPIP    "TCPIP"
#define SQLF_PROTOCOL_APPC     "APPC"
#define SQLF_PROTOCOL_NETB     "NETBIOS"
#define SQLF_PROTOCOL_IPXSPX   "IPXSPX"

/* Import/Export/Load/Unload calling action values                            */
#define SQLU_INITIAL           0x0     /* Initial call                        */
#define SQLU_CONTINUE          0x1     /* Subsequent call                     */
#define SQLU_TERMINATE         0x2     /* Terminating call                    */
#define SQLU_NOINTERRUPT       0x3     /* Initial call - Load/Unload only     */
#define SQLU_ABORT             0x4     /* Abort call - Load only              */
#define SQLU_RESTART           0x5     /* Restart call - Load only            */
#define SQLU_DEVICE_TERMINATE  0x9     /* Subsequent call - Load/Unload only  */

/* Actions for quiesce tablespaces for table                                  */
#define SQLU_QUIESCEMODE_SHARE              0
#define SQLU_QUIESCEMODE_INTENT_UPDATE      1
#define SQLU_QUIESCEMODE_EXCLUSIVE          2
#define SQLU_QUIESCEMODE_RESET              9
#define SQLU_QUIESCEMODE_RESET_OWNED        10

/* Equates for Configuration Utilities                                        */

/* Token equates for SQLFupd structure for Database Manager config file       */
#define SQLF_KTN_RQRIOBLK      1
#define SQLF_KTN_NUMDB         6
#define SQLF_KTN_NNAME         7
#define SQLF_KTN_MAXAGENTS     12
#define SQLF_KTN_MAXCAGENTS    13
#define SQLF_KTN_ASLHEAPSZ     15
#define SQLF_KTN_BACKBUFSZ     18
#define SQLF_KTN_RESTBUFSZ     19
#define SQLF_KTN_INDEXREC      20
#define SQLF_KTN_SHEAPTHRES    21
#define SQLF_KTN_MAXDARI       80
#define SQLF_KTN_KEEPDARI      81
#define SQLF_KTN_SVCENAME      24
#define SQLF_KTN_TPNAME        25
#define SQLF_KTN_AGENTPRI      26
#define SQLF_KTN_DFTDBPATH     27

/* You may manipulate the bits of SQLF_KTN_DFT_MONSWITCHES or you can enable  */
/* disable, or query the current setting through the individual tokens        */
#define SQLF_KTN_DFT_MONSWITCHES  29
#define SQLF_KTN_DFT_MON_UOW      30   /* Bit 1 of SQLF_KTN_DFT_MONSWITCHES   */
#define SQLF_KTN_DFT_MON_STMT     31   /* Bit 2 of SQLF_KTN_DFT_MONSWITCHES   */
#define SQLF_KTN_DFT_MON_TABLE    32   /* Bit 3 of SQLF_KTN_DFT_MONSWITCHES   */
#define SQLF_KTN_DFT_MON_BUFPOOL  33   /* Bit 4 of SQLF_KTN_DFT_MONSWITCHES   */
#define SQLF_KTN_DFT_MON_LOCK     34   /* Bit 5 of SQLF_KTN_DFT_MONSWITCHES   */
#define SQLF_KTN_DFT_MON_SORT     35   /* Bit 6 of SQLF_KTN_DFT_MONSWITCHES   */

#define SQLF_KTN_DFT_ACCOUNT_STR  28
#define SQLF_KTN_SYSADM_GROUP     39
#define SQLF_KTN_DIR_CACHE        40
#define SQLF_KTN_DRDA_HEAP_SZ     41
#define SQLF_KTN_CPUSPEED         42
#define SQLF_KTN_MIN_PRIV_MEM     43
#define SQLF_KTN_PRIV_MEM_THRESH  44
#define SQLF_KTN_MAXTOTFILOP      45
#define SQLF_KTN_FILESERVER       47
#define SQLF_KTN_OBJECTNAME       48
#define SQLF_KTN_QUERY_HEAP_SZ    49
#define SQLF_KTN_AGENT_STACK_SZ   61
#define SQLF_KTN_SYSMAINT_GROUP   62
#define SQLF_KTN_SYSCTRL_GROUP    63
#define SQLF_KTN_DIAGLEVEL        64
#define SQLF_KTN_DIAGPATH         65
#define SQLF_KTN_TP_MON_NAME      66
#define SQLF_KTN_TM_DATABASE      67
#define SQLF_KTN_RESYNC_INTERVAL  68
#define SQLF_KTN_UDF_MEM_SZ       69
#define SQLF_KTN_IPX_SOCKET       71
#define SQLF_KTN_DOS_RQRIOBLK     72
#define SQLF_KTN_DIR_TYPE         73
#define SQLF_KTN_DIR_PATH_NAME    74
#define SQLF_KTN_DIR_OBJ_NAME     75
#define SQLF_KTN_ROUTE_OBJ_NAME   76
#define SQLF_KTN_DFT_CLIENT_COMM  77
#define SQLF_KTN_DFT_CLIENT_ADPT  82
#define SQLF_KTN_AUTHENTICATION   78
#define SQLF_KTN_MON_HEAP_SZ      79
#define SQLF_KTN_SPM_LOG_FILE_SZ  90
#define SQLF_KTN_SPM_MAX_RESYNC   91
#define SQLF_KTN_SPM_NAME         92
#define SQLF_KTN_NUM_INITAGENTS   500
#define SQLF_KTN_MAX_COORDAGENTS  501
#define SQLF_KTN_NUM_POOLAGENTS   502
#define SQLF_KTN_FCM_NUM_BUFFERS  503
#define SQLF_KTN_FCM_NUM_RQB      504
#define SQLF_KTN_FCM_NUM_CONNECT  505
#define SQLF_KTN_FCM_NUM_ANCHORS  506
#define SQLF_KTN_CONN_ELAPSE      508
#define SQLF_KTN_MAX_CONNRETRIES  509
#define SQLF_KTN_MAX_TIME_DIFF    510
#define SQLF_KTN_START_STOP_TIME  511
#define SQLF_KTN_TRUST_ALLCLNTS   301
#define SQLF_KTN_TRUST_CLNTAUTH   302
#define SQLF_KTN_MAX_QUERYDEGREE  303
#define SQLF_KTN_DISCOVER         304
#define SQLF_KTN_DISCOVER_COMM    305
#define SQLF_KTN_INTRA_PARALLEL   306
#define SQLF_KTN_COMM_BANDWIDTH   307
#define SQLF_KTN_DISCOVER_INST    308
#define SQLF_KTN_SS_LOGON         309
#define SQLF_KTN_JAVA_HEAP_SZ     310
#define SQLF_KTN_JDK11_PATH       311

/* tokens for informational parameters                                        */
#define SQLF_KTN_NODETYPE         100
#define SQLF_KTN_RELEASE          101
#define SQLF_KTN_NOTOKEN          200

/* equates for directory type (for dir_type configuration parameter)          */
#define SQLF_DIRTYPE_NONE         0
#define SQLF_DIRTYPE_DCE          1

/* Nodetype equates                                                           */
#define SQLF_NT_STANDALONE        0
#define SQLF_NT_SERVER            1
#define SQLF_NT_REQUESTOR         2
#define SQLF_NT_STAND_REQ         3
#define SQLF_NT_MPP               4

/******************************************************************************
** Defines for Database Monitor Switches - SQLF_KTN_DFT_MONSWITCHES
** 
** The following meanings apply when the bits are set on.
** 
** SQLF_ENABLE_MON_UOW     -
** SQLF_ENABLE_MON_STMT    -
** SQLF_ENABLE_MON_TABLE   -
** SQLF_ENABLE_MON_BUFPOOL -
** SQLF_ENABLE_MON_LOCK    -
** SQLF_ENABLE_MON_SORT    -
*******************************************************************************/
#define SQLF_ENABLE_MON_UOW       0x1  /* xxxx xxxx xxxx xxx1                 */
#define SQLF_ENABLE_MON_STMT      0x2  /* xxxx xxxx xxxx xx1x                 */
#define SQLF_ENABLE_MON_TABLE     0x4  /* xxxx xxxx xxxx x1xx                 */
#define SQLF_ENABLE_MON_BUFPOOL   0x8  /* xxxx xxxx xxxx 1xxx                 */
#define SQLF_ENABLE_MON_LOCK      0x10 /* xxxx xxxx xxx1 xxxx                 */
#define SQLF_ENABLE_MON_SORT      0x20 /* xxxx xxxx xx1x xxxx                 */

/* Admin. server discover definitions (discover parameter)                    */
#define SQLF_DSCVR_KNOWN          1
#define SQLF_DSCVR_SEARCH         2

/* Token equates for SQLFupd structure for Database configuration file        */
#define SQLF_DBTN_LOCKLIST        1
#define SQLF_DBTN_BUFF_PAGE       90
#define SQLF_DBTN_MAXFILOP        3
#define SQLF_DBTN_SOFTMAX         5
#define SQLF_DBTN_MAXAPPLS        6
#define SQLF_DBTN_APPLHEAPSZ      51
#define SQLF_DBTN_DBHEAP          50
#define SQLF_DBTN_DLCHKTIME       9
#define SQLF_DBTN_SORT_HEAP       52
#define SQLF_DBTN_MAXLOCKS        15
#define SQLF_DBTN_LOGPRIMARY      16
#define SQLF_DBTN_LOGSECOND       17
#define SQLF_DBTN_LOGFIL_SIZ      92
#define SQLF_DBTN_STMTHEAP        53
#define SQLF_DBTN_NEWLOGPATH      20
#define SQLF_DBTN_DETS            21
#define SQLF_DBTN_COPY_PROTECT    22
#define SQLF_DBTN_LOG_RETAIN      23
#define SQLF_DBTN_USER_EXIT       24
#define SQLF_DBTN_AUTO_RESTART    25
#define SQLF_DBTN_INDEXREC        30
#define SQLF_DBTN_PCKCACHESZ      31
#define SQLF_DBTN_MINCOMMIT       32
#define SQLF_DBTN_LOGBUFSZ        33
#define SQLF_DBTN_LOCKTIMEOUT     34
#define SQLF_DBTN_INDEXSORT       35
#define SQLF_DBTN_NUM_FREQVALUES  36
#define SQLF_DBTN_NUM_IOCLEANERS  37
#define SQLF_DBTN_CHNGPGS_THRESH  38
#define SQLF_DBTN_NUM_IOSERVERS   39
#define SQLF_DBTN_DFT_PREFETCH_SZ 40
#define SQLF_DBTN_SEQDETECT       41
#define SQLF_DBTN_DFT_LOADREC_SES 42
#define SQLF_DBTN_REC_HIS_RETENTN 43
#define SQLF_DBTN_STAT_HEAP_SZ    45
#define SQLF_DBTN_DIR_OBJ_NAME    46   /* token for directory services        */
#define SQLF_DBTN_AVG_APPLS       47
#define SQLF_DBTN_NUM_QUANTILES   48
#define SQLF_DBTN_DFT_EXTENT_SZ   54
#define SQLF_DBTN_UTIL_HEAP_SZ    55
#define SQLF_DBTN_CATALOGCACHE_SZ 56
#define SQLF_DBTN_DFT_QUERYOPT    57
#define SQLF_DBTN_APP_CTL_HEAP_SZ 500
#define SQLF_DBTN_ADSM_PASSWORD   501
#define SQLF_DBTN_PCKCACHE_SZ     505
#define SQLF_DBTN_MULTIPAGE_ALLOC 506
#define SQLF_DBTN_DFT_DEGREE      301
#define SQLF_DBTN_ESTORE_SEG_SZ   303
#define SQLF_DBTN_NUM_ESTORE_SEGS 304
#define SQLF_DBTN_ADSM_OWNER      305
#define SQLF_DBTN_ADSM_NODENAME   306
#define SQLF_DBTN_ADSM_MGMTCLASS  307
#define SQLF_DBTN_DISCOVER        308
#define SQLF_DBTN_DFT_SQLMATHWARN 309

/* tokens for informational (non-modifiable) parameters                       */
#define SQLF_DBTN_COLLATE_INFO    44
#define SQLF_DBTN_COUNTRY         100
#define SQLF_DBTN_CODEPAGE        101
#define SQLF_DBTN_RELEASE         102
#define SQLF_DBTN_LOGPATH         103
#define SQLF_DBTN_INTFLAGS        104
#define SQLF_DBTN_LOGHEAD         105
#define SQLF_DBTN_NEXTACTIVE      107
#define SQLF_DBTN_CONSISTENT      111
#define SQLF_DBTN_BACKUP_PENDING  112
#define SQLF_DBTN_ROLLFWD_PENDING 113
#define SQLF_DBTN_LOG_RETAIN_STATUS 114
#define SQLF_DBTN_USER_EXIT_STATUS 115
#define SQLF_DBTN_CODESET         120
#define SQLF_DBTN_TERRITORY       121
#define SQLF_DBTN_NUMSEGS         122
#define SQLF_DBTN_DATABASE_LEVEL  124
#define SQLF_DBTN_NOTOKEN         200
#define SQLF_DBTN_RESTORE_PENDING 503

/* Index recreate type (INDEXREC values)                                      */
#define SQLF_INX_REC_SYSTEM       0
#define SQLF_INX_REC_REFERENCE    1
#define SQLF_INX_REC_RESTART      2

/******************************************************************************
** You may manipulate the bits of SQLF_DBTN_DETS and SQLF_DBTN_INTFLAGS
** or you can enable, disable, or query the current setting through
** the individual tokens.
** 
** Defines for: SQLF_DBTN_COPY_PROTECT    , SQLF_DBTN_LOG_RETAIN
**              SQLF_DBTN_USER_EXIT       , SQLF_DBTN_AUTO_RESTART
**              SQLF_DBTN_CONSISTENT      , SQLF_DBTN_BACKUP_PENDING
**              SQLF_DBTN_ROLLFWD_PENDING , SQLF_DBTN_LOG_RETAIN_STATUS
**              SQLF_DBTN_USER_EXIT_STATUS
*******************************************************************************/
#define SQLF_DISABLE              0
#define SQLF_ENABLE               1
#define SQLF_ROLLFWD_TABLESPACE   2    /* The third state of rollfwd_pending  */

/******************************************************************************
** Defines for Database Details - SQLF_DBTN_DETS
** 
** The following meanings apply when the bits are set on.
** 
** SQLF_COPY_PROTECT       - Database is copy protected.
** SQLF_ENABLE_LOG_RETAIN  - Next time database is started in normal
**                           conditions, the log files will be retained
**                           for the purpose of roll-forward recovery.
** SQLF_ENABLE_USER_EXIT   - Next time database is started in normal
**                           conditions, the user log exit will be enabled
**                           for the purpose of roll-forward recovery.
** SQLF_ENABLE_AUTO_RESTART- The RESTART DATABASE function will be
**                           invoked when needed.
*******************************************************************************/
#define SQLF_COPY_NOPROT          0x0  /* xxxx xxxx xxxx xxx0                 */
#define SQLF_COPY_PROTECT         0x1  /* xxxx xxxx xxxx xxx1                 */
#define SQLF_ENABLE_LOG_RETAIN    0x2  /* xxxx xxxx xxxx xx1x                 */
#define SQLF_ENABLE_USER_EXIT     0x4  /* xxxx xxxx xxxx x1xx                 */
#define SQLF_ENABLE_AUTO_RESTART  0x8  /* xxxx xxxx xxxx 1xxx                 */

/******************************************************************************
** Defines for Logging Flags.  
** A number of parameters can be retreived into one 16 bit integer parameter
** by using the SQLF_DBTN_INTFLAGS token
** 
** The following meanings apply when the bits are set on.
** 
** SQLF_CONSISTENT      - Database is in a consistent state.
** SQLF_BACKUP_PENDING  - User is required to take a backup of the
**                        database before the system will allow the
**                        database to be opened for normal processing.
** SQLF_ROLLFWD_PENDING - User is required to roll forward the database
**                        before the system will allow the database to
**                        be opened for normal processing.
** SQLF_LOG_RETAIN      - Log files are retained so that a database can be
**                        rolled forward after it has been restored from
**                        a backup copy.
** SQLF_USER_EXIT       - User exit is taken when log files are filled and
**                        when log files are needed and not found.
** SQLF_TBS_ROLLFWD     - If the SQLF_ROLLFWD_PENDING bit is off, and this
**                        bit is on, then the tablespace needs to be
**                        rolled forward.
** SQLF_RESTORE_PENDING - User is required to restore the database
**                        before the system will allow the database to
**                        be opened for normal processing.
** 
*******************************************************************************/
#define SQLF_CONSISTENT           0x1  /* xxxx xxxx xxxx xxx1                 */
#define SQLF_BACKUP_PENDING       0x4  /* xxxx xxxx xxxx x1xx                 */
#define SQLF_ROLLFWD_PENDING      0x8  /* xxxx xxxx xxxx 1xxx                 */
#define SQLF_LOG_RETAIN           0x10 /* xxxx xxxx xxx1 xxxx                 */
#define SQLF_USER_EXIT            0x20 /* xxxx xxxx xx1x xxxx                 */
#define SQLF_TBS_ROLLFWD          0x40 /* xxxx xxxx x1xx xxxx                 */
#define SQLF_RESTORE_PENDING      0x80 /* xxxx xxxx 1xxx xxxx                 */

/* Constants for configuration parameter maximum lengths                      */
#define SQL_TPNAME_SZ             64   /* length of tpname config parm        */
#define SQL_SPM_NAME_SZ           8    /* length of syncpoint manager name    */
#define SQL_LOGPATH_SZ            242  /* max length of log parms             */
#define SQL_LOGFILE_NAME_SZ       12   /* max length of log file name         */
#define SQL_DBPATH_SZ             215  /* max length of db path parm          */
#define SQL_FFDCPATH_SZ           215  /* max length of diagpath parm         */

/* Constants for types of Data Redistribution operation                       */
#define SQLUT_UNIFORM          'U'     /* Uniform redistribution              */
#define SQLUT_TARGETMAP        'T'     /* Using target partitioning map       */
#define SQLUT_CONTINUE         'C'     /* Resuming a stopped data redist.     */
#define SQLUT_ROLLBACK         'R'     /* Rolling back a stopped data         */
                                       /* redist.                             */
/* LOAD and UNLOAD defines                                                    */
#define SQLU_LOAD_PHASE        'L'     /* restart at load phase               */
#define SQLU_BUILD_PHASE       'B'     /* restart at build phase              */
#define SQLU_DELETE_PHASE      'D'     /* restart at delete phase             */

SQL_STRUCTURE sqldcoln
{
   short           dcolnlen;
   char            *dcolnptr;
};

SQL_STRUCTURE sqldcol
{
   short           dcolmeth;
   short           dcolnum;
   struct sqldcoln dcolname[1];   /* actual size must be dcolnum              */
};

/* Structure for Pairs of Locations for ASC files                             */
SQL_STRUCTURE sqllocpair
{
   short           begin_loc;
   short           end_loc;
};

SQL_STRUCTURE sqlloctab
{
   struct sqllocpair locpair[1];  /* actual size must be dcolnum              */
};

/* Structures for Input and Output Data for Import and Export                 */

SQL_STRUCTURE sqluimpt_in
{
   unsigned long   sizeOfStruct;
   unsigned long   commitcnt;
   unsigned long   restartcnt;
};

SQL_STRUCTURE sqluimpt_out
{
   unsigned long   sizeOfStruct;
   unsigned long   rowsRead;
   unsigned long   rowsSkipped;
   unsigned long   rowsInserted;
   unsigned long   rowsUpdated;
   unsigned long   rowsRejected;
   unsigned long   rowsCommitted;
};

SQL_STRUCTURE sqluexpt_out
{
   unsigned long   sizeOfStruct;
   unsigned long   rowsExported;
};

#define SQLUIMPT_IN_SIZE       sizeof(struct sqluimpt_in)
#define SQLUIMPT_OUT_SIZE      sizeof(struct sqluimpt_out)
#define SQLUEXPT_OUT_SIZE      sizeof(struct sqluexpt_out)

/* Structures for Input and Output Data for Load and Unload                   */

SQL_STRUCTURE sqluload_in
{
   unsigned long   sizeOfStruct;
   unsigned long   savecnt;
   unsigned long   restartcnt;
   unsigned long   rowcnt;
   unsigned long   warningcnt;
   unsigned long   data_buffer_size;
   unsigned long   sort_buffer_size;
   unsigned short  hold_quiesce;
   char            restartphase;
   char            statsopt;
   unsigned short  cpu_parallelism;
   unsigned short  disk_parallelism;
   unsigned short  non_recoverable;
};

SQL_STRUCTURE sqluload_out
{
   unsigned long   sizeOfStruct;
   unsigned long   rowsRead;
   unsigned long   rowsSkipped;
   unsigned long   rowsLoaded;
   unsigned long   rowsRejected;
   unsigned long   rowsDeleted;
   unsigned long   rowsCommitted;
};

SQL_STRUCTURE sqluunld_in
{
   unsigned long   sizeOfStruct;
   unsigned long   data_buffer_size;
   unsigned long   sort_buffer_size;
   unsigned short  hold_quiesce;
   unsigned short  intent_update;
   unsigned short  serial_write;
   unsigned short  num_buffers;
   unsigned short  reorg_lobs;
   unsigned short  filler;
};

SQL_STRUCTURE sqluunld_out
{
   unsigned long   sizeOfStruct;
   unsigned long   rowsUnloaded;
};

#define SQLULOAD_IN_SIZE       sizeof(struct sqluload_in)
#define SQLULOAD_OUT_SIZE      sizeof(struct sqluload_out)
#define SQLUUNLD_IN_SIZE       sizeof(struct sqluunld_in)
#define SQLUUNLD_OUT_SIZE      sizeof(struct sqluunld_out)

/* Constants and Structures for the Asynchronous Read Log API                 */

#define SQLU_RLOG_READ         1       /* read the database log               */
#define SQLU_RLOG_READ_SINGLE  2       /* read a single log record            */
#define SQLU_RLOG_QUERY        3       /* query the database log              */

typedef union SQLU_LSN
{
   unsigned char   lsnChar[6];         /* 6 byte character representation     */
   unsigned short  lsnWord[3];         /* 6 byte short representation         */
} SQLU_LSN;

typedef SQL_STRUCTURE SQLU_RLOG_INFO
{
   SQLU_LSN        initialLSN;         /* initial lsn at first connect        */
   SQLU_LSN        firstReadLSN;       /* first lsn read on call              */
   SQLU_LSN        lastReadLSN;        /* last lsn read on call               */
   SQLU_LSN        curActiveLSN;       /* current active lsn                  */
   unsigned long   logRecsWritten;     /* number of log records returned      */
   unsigned long   logBytesWritten;    /* number of log bytes returned        */
} SQLU_RLOG_INFO;

/* Structures for Configuration Utility APIs.                                 */

SQL_STRUCTURE sqlfupd
{
   unsigned short  token;
   char            *ptrvalue;
};

/* Constants and structure used by sqlgadau and sqluadau.                     */
#define SQL_USER_AUTHORIZED                 1
#define SQL_USER_UNAUTHORIZED               0
#define SQL_AUTHORIZATION_SIZE_OLD          22
#define SQL_AUTHORIZATION_SIZE_V2           34
#define SQL_AUTHORIZATION_SIZE              38

SQL_STRUCTURE sql_authorizations
{
   short           sql_authorizations_len;
   short           sql_sysadm_auth;
   short           sql_dbadm_auth;
   short           sql_createtab_auth;
   short           sql_bindadd_auth;
   short           sql_connect_auth;
   short           sql_sysadm_grp_auth;
   short           sql_dbadm_grp_auth;
   short           sql_createtab_grp_auth;
   short           sql_bindadd_grp_auth;
   short           sql_connect_grp_auth;
   short           sql_sysctrl_auth;
   short           sql_sysctrl_grp_auth;
   short           sql_sysmaint_auth;
   short           sql_sysmaint_grp_auth;
   short           sql_create_not_fenc_auth;
   short           sql_create_not_fenc_grp_auth;
   short           sql_implicit_schema_auth;
   short           sql_implicit_schema_grp_auth;
};

/* Constants and structure used for backup and restore                        */
#define SQLU_MAX_TBS_NAME_LEN     18
#define SQLU_DB_DIR_LEN           215
#define SQLU_SHR_LIB_LEN          255
#define SQLU_MEDIA_LOCATION_LEN   255
#define SQLU_APPLID_LEN           32
#define SQLU_MAX_SESSIONS         999

typedef SQL_STRUCTURE sqlu_tablespace_entry
{
   unsigned long   reserve_len;
   char            tablespace_entry[SQLU_MAX_TBS_NAME_LEN+1];
   char            filler[1];
} sqlu_tablespace_entry;

typedef SQL_STRUCTURE sqlu_tablespace_bkrst_list
{
   long            num_entry;
   struct sqlu_tablespace_entry *tablespace;
} sqlu_tablespace_bkrst_list;

typedef SQL_STRUCTURE sqlu_media_entry
{
   unsigned long   reserve_len;
   char            media_entry[SQLU_DB_DIR_LEN+1];
} sqlu_media_entry;

typedef SQL_STRUCTURE sqlu_vendor
{
   unsigned long   reserve_len1;
   char            shr_lib[SQLU_SHR_LIB_LEN+1];
   unsigned long   reserve_len2;
   char            filename[SQLU_SHR_LIB_LEN+1];
} sqlu_vendor;

typedef SQL_STRUCTURE sqlu_location_entry
{
   unsigned long   reserve_len;
   char            location_entry[SQLU_MEDIA_LOCATION_LEN+1];
} sqlu_location_entry;

SQL_STRUCTURE sqlurf_newlogpath
{
        SQL_PDB_NODE_TYPE      nodenum; /* node number                        */
        unsigned short         pathlen; /* length of new logpath              */
        char                   logpath[SQL_LOGPATH_SZ+SQL_LOGFILE_NAME_SZ+1]; /*  */
                                       /* SZ+1                                */
};

SQL_STRUCTURE sqlurf_info
{
        SQL_PDB_NODE_TYPE      nodenum; /* node number                        */
        long                   state;  /* state information                   */
        unsigned char          nextarclog[SQLUM_ARCHIVE_FILE_LEN+1]; /* next  */
                                       /* archive file needed                 */
        unsigned char          firstarcdel[SQLUM_ARCHIVE_FILE_LEN+1]; 
        unsigned char          lastarcdel[SQLUM_ARCHIVE_FILE_LEN+1]; /* last  */
                                       /* archive file to be deleted          */
        unsigned char          lastcommit[SQLUM_TIMESTAMP_LEN+1]; 
};

SQL_STRUCTURE sqlurf_stat
{
        long                   numNodes;
        struct sqlurf_info     nodeInfo[SQL_PDB_MAX_NUM_NODE];
};

SQL_STRUCTURE rfwd_input
{
        unsigned long          version; /* rollforward version                */
        char                   *pDbAlias; /* database alias                   */
        unsigned short         CallerAction; /* action                        */
        char                   *pStopTime; /* stop time                       */
        char                   *pUserName; /* user name                       */
        char                   *pPassword; /* password                        */
        char                   *pOverflowLogPath; /* overflow log path        */
        unsigned short         NumChngLgOvrflw; /* no. of changed overflow    */
                                       /* log paths                           */
        struct sqlurf_newlogpath *pChngLogOvrflw; /* changed overflow log     */
                                       /* paths                               */
        unsigned short         ConnectMode; /* connect mode                   */
        struct sqlu_tablespace_bkrst_list *pTablespaceList; /* tablespace     */
                                       /* list                                */
        short                  AllNodeFlag; /* all node flag                  */
        short                  NumNodes; /* size of nodelist                  */
        SQL_PDB_NODE_TYPE      *pNodeList; /* list of node numbers            */
        short                  NumNodeInfo; /* size of pNodeInfo in rfwd      */
                                       /* output                              */
};

SQL_STRUCTURE grfwd_input
{
        unsigned short         DbAliasLen; /* length in bytes of DbAlias      */
        unsigned short         StopTimeLen; /* length in bytes of StopTime    */
        unsigned short         UserNameLen; /* length in bytes of UserName    */
        unsigned short         PasswordLen; /* length in bytes of Password    */
        unsigned short         OvrflwLogPathLen; /* length in bytes of        */
                                       /* OverflowLogPath                     */
        unsigned long          Version; /* rollforward version                */
        char                   *pDbAlias; /* database alias                   */
        unsigned short         CallerAction; /* action                        */
        char                   *pStopTime; /* stop time                       */
        char                   *pUserName; /* user name                       */
        char                   *pPassword; /* password                        */
        char                   *pOverflowLogPath; /* overflow log path        */
        unsigned short         NumChngLgOvrflw; /* no. of changed overflow    */
                                       /* log paths                           */
        struct sqlurf_newlogpath *pChngLogOvrflw; /* changed overflow log     */
                                       /* paths                               */
        unsigned short         ConnectMode; /* connect mode                   */
        struct sqlu_tablespace_bkrst_list *pTablespaceList; /* tablespace     */
                                       /* list                                */
        short                  AllNodeFlag; /* all node flag                  */
        short                  NumNodes; /* size of nodelist                  */
        SQL_PDB_NODE_TYPE      *pNodeList; /* list of node numbers            */
        short                  NumNodeInfo; /* size of pNodeInfo in rfwd      */
                                       /* output                              */
};

SQL_STRUCTURE rfwd_output
{
        char                   *pApplicationId; /* application id             */
        long                   *pNumReplies; /* number of replies received    */
        struct sqlurf_info     *pNodeInfo; /* node reply info                 */
};

#define SQLU_LOCAL_MEDIA       'L'     /* path/device                         */
#define SQLU_SERVER_LOCATION   'S'     /* remote file/device/named pipe       */
#define SQLU_CLIENT_LOCATION   'C'     /* local file/device/named pipe        */
#define SQLU_ADSM_MEDIA        'A'     /* ADSM                                */
#define SQLU_OTHER_MEDIA       'O'     /* vendor library                      */
#define SQLU_USER_EXIT         'U'     /* user exit                           */
#define SQLU_DISK_MEDIA        'D'     /* Generated only by vendors           */
#define SQLU_DISKETTE_MEDIA    'K'     /* Generated only by vendors           */
#define SQLU_TAPE_MEDIA        'T'     /* Generated only by vendors           */
#define SQLU_PIPE_MEDIA        'P'     /* Generated only by vendors           */

union sqlu_media_list_targets
{
   struct sqlu_media_entry        *media;      /* For media_type L - for      */
                                               /* BACKUP, RESTORE and LOAD    */
                                               /* copytarget, workdirectory,  */
                                               /* lobpaths, IMPORT and        */
                                               /* EXPORT lobpaths             */
   struct sqlu_vendor             *vendor;     /* For media_type O            */
   struct sqlu_location_entry     *location;   /* For media_type S - for      */
                                               /* LOAD and LOAD recovery      */
                                               /* For media type C - for      */
                                               /* EXPORT lobfile              */
};

typedef SQL_STRUCTURE sqlu_media_list
{
   char            media_type;
   char            filler[3];
   long            sessions;
   union sqlu_media_list_targets target;
} sqlu_media_list;

/* Struct used by sqlugtpi, sqlugrpi and sqlugrpn to store partitioning       */
/* information                                                                */
SQL_STRUCTURE sqlpartkey
{
   unsigned short  sqltype;    /* Date Type of Key                            */
   unsigned short  sqllen;     /* Data Length of Key                          */
};

SQL_STRUCTURE sqlupi
{
   unsigned short  pmaplen;    /* Length of partitioning map                  */
   SQL_PDB_NODE_TYPE pmap[SQL_PDB_MAP_SIZE]; /* Partitioning map              */
   unsigned short  sqld;       /* # of used SQLPARTKEY elements               */
   struct sqlpartkey sqlpartkey[SQL_MAX_NUM_PART_KEYS]; /* Partitioning Keys  */
};

SQL_STRUCTURE sqluhtsp
{
   char            tablespace_name[SQLUH_TABLESPACENAME_SZ+1]; /* tablespace  */
                               /* name                                        */
   char            filler;
};

SQL_STRUCTURE sqluhinfo
{
   char      sqluhinfoid[8];                   /* Eye catcher = 'SQLUHINF'    */
   long      sqluhinfobc;                      /* SQLUHINFO  in bytes=(   )   */
   short     sqln;                             /* Number of tablespace        */
                                               /* elements                    */
   short     sqld;                             /* # of used tablespace        */
                                               /* elements                    */
   char      operation[SQLUH_OP_SZ+1];         /* operation                   */
   char      object[SQLUH_OBJ_SZ+1];           /* object                      */
   char      object_part[SQLUH_OBJPART_SZ+1];  /* object part                 */
   char      optype[SQLUH_OPTYPE_SZ+1];        /* optype                      */
   char      device_type[SQLUH_DEVTYPE_SZ+1];  /* device type                 */
   char      first_log[SQLUH_FIRSTLOG_SZ+1];   /* first log                   */
   char      last_log[SQLUH_LASTLOG_SZ+1];     /* last log                    */
   char      backup_id[SQLUH_BACKID_SZ+1];     /* backup id                   */
   char      table_creator[SQLUH_TCREATE_SZ+1]; /* table creator              */
   char      table_name[SQLUH_TNAME_SZ+1];     /* table name                  */
   char      num_of_tablespaces[SQLUH_NUMTABLESPACE_SZ+1]; /* # of            */
                                               /* tablespaces                 */
   char      location[SQLUH_LOC_SZ+1];         /* location                    */
   char      comment[SQLUH_COMMENT_SZ+1];      /* comment                     */
   struct sqluhtsp tablespace[1];
};

/* Macro for size of sqluhinfo                                                */
#define   SQLUHINFOSIZE(n) \
(sizeof(struct sqluhinfo) + (n-1)*sizeof(struct sqluhtsp))

/* Definitions needed for the sqlb api calls                                  */
/*                                                                            */
/* nb: 'tbs' is an abbreviaton for 'TABLESPACE'                               */

#define SQLB_SVERSION_SIZE     8       /* length of structure version         */
#define SQLB_MAX_TBS_NAME_SZ   128     /* maximum length of a table space     */
                                       /* name                                */
/* NB: this constant is set to the maximum size that is likely to be needed   */
/* in future.  Don't confuse this with SQLU_MAX_TBS_NAME_LEN which is set to  */
/* the current maximum size (18).                                             */

/* Externally visibile flags of a table space                                 */
/* storage manager class                                                      */
#define SQLB_TBS_SMS           0x1     /* System   Managed Space              */
#define SQLB_TBS_DMS           0x2     /* Database Managed Space              */
/* table space contents                                                       */
#define SQLB_TBS_ANY           0x0     /* regular contents                    */
#define SQLB_TBS_LONG          0x20    /* long field data                     */
#define SQLB_TBS_TMP           0x10    /* temp data                           */
/* other flags values                                                         */
#define SQLB_TBS_TMP_RECOVERY  0x20000 /* temp table space is reserved for    */
                                       /* completion of reorg recovery        */

/* The externally visible state of a table space is composed of the           */
/* hexadecimal sum of various of the following state values.  For example if  */
/* the state is 'quiesced exclusive' and 'load pending', the value would be   */
/* 0x0004 + 0x0008 which is 0x000c.                                           */
/*                                                                            */
/* You may use the tool db2tbst to do the reverse calculation (from 0x000c    */
/* to 'load pending' and 'quiesced exclusive', for example) which is more     */
/* complex. In our example, execute:                                          */
/*                                                                            */
/*  db2tbst 0x000c                                                            */
/*                                                                            */
/* which yields:                                                              */
/*                                                                            */
/* State = Quiesced Exclusive                                                 */
/*       + Load Pending                                                       */
#define SQLB_NORMAL                  0x0    /* Normal                         */
#define SQLB_QUIESCED_SHARE          0x1    /* Quiesced: SHARE                */
#define SQLB_QUIESCED_UPDATE         0x2    /* Quiesced: UPDATE               */
#define SQLB_QUIESCED_EXCLUSIVE      0x4    /* Quiesced: EXCLUSIVE            */
#define SQLB_LOAD_PENDING            0x8    /* Load pending                   */
#define SQLB_DELETE_PENDING          0x10   /* Delete pending                 */
#define SQLB_BACKUP_PENDING          0x20   /* Backup pending                 */
#define SQLB_ROLLFORWARD_IN_PROGRESS 0x40   /* Roll forward in progress       */
#define SQLB_ROLLFORWARD_PENDING     0x80   /* Roll forward pending           */
#define SQLB_RESTORE_PENDING         0x100  /* Restore pending                */
#define SQLB_RECOVERY_PENDING        0x100  /* Recovery pending (use SQLB     */
                                            /* RESTORE_PENDING)               */
#define SQLB_DISABLE_PENDING         0x200  /* Disable pending                */
#define SQLB_REORG_IN_PROGRESS       0x400  /* Reorg in progress              */
#define SQLB_BACKUP_IN_PROGRESS      0x800  /* Backup in progress             */
#define SQLB_STORDEF_PENDING         0x1000 /* storage must be defined        */
#define SQLB_RESTORE_IN_PROGRESS     0x2000 /* Restore in progress            */
#define SQLB_STORDEF_ALLOWED         0x2000000 /* storage may be defined      */
#define SQLB_STORDEF_FINAL_VERSION   0x4000000 /* storDef is in 'final'       */
                                            /* state                          */
#define SQLB_STORDEF_CHANGED         0x8000000 /* storDef was changed prior   */
                                            /* to rollforward                 */
#define SQLB_REBAL_IN_PROGRESS       0x10000000 /* dms rebalancer is active   */
#define SQLB_PSTAT_DELETION          0x20000000 /* TBS deletion in progress   */
#define SQLB_PSTAT_CREATION          0x40000000 /* TBS creation in progress   */

#define SQLB_STATE_SET               0x8    /* For service use only.          */

/* provide information about the quiescers of a tablespace                    */
SQL_STRUCTURE SQLB_QUIESCER_DATA
{
   unsigned long   quiesceId;          /* tablespace id of quiesceObject      */
   unsigned long   quiesceObject;      /* object in quiesceId                 */
};

#define SQLB_MAX_QUIESCERS     5       /* Maximum number of quiescers         */
#define SQLB_TBSPQRY_DATA_ID   "TBSQ0030" /* SQLB_TBSPQRY_DATA version id     */

/* Provide info about a tableSpace in a database                              */
SQL_STRUCTURE SQLB_TBSPQRY_DATA
{
   char            tbspqver[SQLB_SVERSION_SIZE]; /* version                   */
   unsigned long   id;                 /* internal id for the pool            */
   unsigned long   nameLen;            /* length of the name (for cobol &     */
                                       /* other nonC lang.)                   */
   char            name[SQLB_MAX_TBS_NAME_SZ]; /* NUL terminated name         */
   unsigned long   totalPages;         /* DMS : Pages specified by CREATE     */
                                       /* TABLESPACE.                         */
                                       /* SMS : N/A                           */
   unsigned long   useablePages;       /* DMS : totalPages - overhead         */
                                       /* SMS : N/A                           */
   unsigned long   flags;              /* bit attributes for the pool --      */
                                       /* includes 'class' & other stuff to   */
                                       /* be defined                          */
   unsigned long   pageSize;           /* pagesize of tablespace (in          */
                                       /* bytes)..currently fixed at 4K       */
   unsigned long   extSize;            /* extent size (in pages)              */
   unsigned long   prefetchSize;       /* prefetch size                       */
   unsigned long   nContainers;        /* number of containers                */
   unsigned long   tbsState;           /* SQLB_NORMAL, SQLB_LOAD_PENDING,     */
                                       /* etc.                                */
   char            lifeLSN[6];         /* 'timestamp' identifying the origin  */
                                       /* of the tbs                          */
   char            pad[2];             /* for alignment                       */
   unsigned long   flags2;             /* bit attributes for the pool         */
   char            minimumRecTime[SQL_STAMP_STRLEN+1]; /* Minimum Recovery    */
                                       /* Time                                */
   char            pad1[1];            /* for alignment                       */
   unsigned long   StateChngObj;       /* For Load or Delete Pending          */
   unsigned long   StateChngID;        /* For Load or Delete Pending          */
   unsigned long   nQuiescers;         /* Number of queiscers                 */
   struct SQLB_QUIESCER_DATA quiescer[SQLB_MAX_QUIESCERS]; /* quiescer info   */
   char            reserved[32];       /* for future use                      */
};

/* container type                                                             */
#define SQLB_CONT_PATH         0       /* SMS: directory path specs           */
#define SQLB_CONT_DISK         1       /* DMS: a 'raw' or 'device' spec       */
#define SQLB_CONT_FILE         2       /* DMS: a 'cooked file' -> file spec   */

/* provide information about the containers on which tablespaces are based    */
SQL_STRUCTURE SQLB_TBSCONTQRY_DATA
{
   unsigned long   id;                 /* container id                        */
   unsigned long   nTbs;               /* num table spaces sharing this       */
                                       /* container (is always 1 for DMS      */
                                       /* tablespaces)                        */
   unsigned long   tbsID;              /* tableSpace id, when 'nTbs' is 1     */
   unsigned long   nameLen;            /* length of name (for non-C lang.)    */
   char            name[SQLB_MAX_CONTAIN_NAME_SZ]; /* null term. name         */
   unsigned long   underDBDir;         /* 1 if container is under the DB      */
                                       /* directory, 0 if not                 */
   unsigned long   contType;           /* SQLB_CONT_PATH/DISK/FILE            */
   unsigned long   totalPages;         /* DMS : Pages specified by CREATE     */
                                       /* TABLESPACE. SMS : N/A               */
   unsigned long   useablePages;       /* DMS : totalPages - overhead SMS :   */
                                       /* N/A                                 */
   unsigned long   ok;                 /* 1 if container is accessible, 0 if  */
                                       /* there is a problem                  */
};

/* provide statistics on a tablespace                                         */
/* BETA NOTE: currently, we only provide stats on DMS tablespaces             */
/* SRSFIX: determine what SMS support to ship with V2                         */
SQL_STRUCTURE SQLB_TBS_STATS
{
   unsigned long   totalPages;         /* DMS : Pages specified by CREATE     */
                                       /* TABLESPACE.                         */
                                       /* SMS : Pages of all files in the     */
                                       /* directories.                        */
   unsigned long   useablePages;       /* DMS : totalPages - overhead         */
                                       /* SMS : same as totalPages            */
   unsigned long   usedPages;          /* DMS : used and allocated pages in   */
                                       /* the pool                            */
                                       /* SMS : same as totalPages            */
   unsigned long   freePages;          /* DMS : useablePages - usedPages      */
                                       /* SMS : N/A                           */
   unsigned long   highWaterMark;      /* DMS : high water mark of used page  */
                                       /* number                              */
                                       /* SMS : N/A                           */
};

/******************************************************************************
** Function proto-types: 'sqlb' prefix for internal use.
** All functions require a database connection, and return
** info about that database.
*******************************************************************************/

/* stpq - Single TableSpace Query                                             */
SQL_API_RC SQL_API_FN                            /* Single Tablespace Query   */
  sqlbstpq (
   struct sqlca * pSqlca,                        /* SQLCA                     */
   unsigned long TablespaceId,                   /* in: tableSpace id         */
   struct SQLB_TBSPQRY_DATA * pTablespaceData,   /* out: tableSpace data      */
   unsigned long reserved);                      /* in: SQLB_RESERVED1        */

/* otsq - Open TableSpace Query -> use for retrieving a full list             */
#define SQLB_OPEN_TBS_ALL 0x0                    /* all tablespaces in        */
                                                 /* database                  */
#define SQLB_OPEN_TBS_RESTORE 0x1                /* all tablespaces my agent  */
                                                 /* is restoring              */
#define SQLB_OPEN_TBS_STORDEF 0x2                /* all tablespaces where     */
                                                 /* storage definition is     */
                                                 /* allowed                   */
#define SQLB_OPEN_TBS_TEMP 0x4                   /* all temp tablespaces      */
SQL_API_RC SQL_API_FN                            /* Open Tablespace Query     */
  sqlbotsq (
   struct sqlca * pSqlca,                        /* SQLCA                     */
   unsigned long TablespaceQueryOptions,         /* in: processing options:   */
                                                 /* SQLB_TBS_OPEN_xxx         */
   unsigned long * pNumTablespaces);             /* out: # tablespaces        */
                                                 /* defined in db             */

/* ftpq - Fetch TableSpace Query -> fetch the next block of tbs data          */
SQL_API_RC SQL_API_FN                            /* Fetch Tablespace Query    */
  sqlbftpq (
   struct sqlca * pSqlca,                        /* SQLCA                     */
   unsigned long MaxTablespaces,                 /* max num of tbs the        */
                                                 /* output area can hold      */
   struct SQLB_TBSPQRY_DATA * pTablespaceData,   /* out: array of length      */
                                                 /* maxTbs                    */
   unsigned long * pNumTablespaces);             /* out: #data entries        */
                                                 /* returned                  */

/* ctsq - Close TableSpace Query -> terminate the query opened by sqlbotsq    */
SQL_API_RC SQL_API_FN                            /* Close Tablespace Query    */
  sqlbctsq (
   struct sqlca * pSqlca);                       /* SQLCA                     */

/* mtsq - TableSpace Query -> uses the above primitives to return the FULL    */
/* list of tablespaces in an array allocated and returned to the              */
/* application.  The application should free this memory with the sqlefmem()  */
/* api when it is finished with it. Even if this api fails with an            */
/* 'insufficient memory' error, 'nTbs' is set to the number of tablespaces    */
/* in the database. 'nTbs' is set to zero if we fail to sucessfully open a    */
/* query. 'tbsData' is returned as NULL (0;no mem alloc) if we fail for any   */
/* reason.                                                                    */
SQL_API_RC SQL_API_FN                            /* Tablespace Query          */
  sqlbmtsq (
   struct sqlca * pSqlca,                        /* SQLCA                     */
   unsigned long * pNumTablespaces,              /* out: total number of      */
                                                 /* table spaces              */
   struct SQLB_TBSPQRY_DATA *** pppTablespaceData, /* out: mem returned to    */
                                                 /* application               */
   unsigned long reserved1,                      /* in: SQLB_RESERVED1        */
   unsigned long reserved2);                     /* in: SQLB_RESERVED2        */

/* container level queries.They all accept either a tableSpace id (a single   */
/* tbs) ora special id (SQLB_ALL_TABLESPACES) which triggers the fetchof a    */
/* list of containers for the entire database.                                */

/* constant used in place of tablespace id to indicate all table spaces in    */
/* db                                                                         */
#define SQLB_ALL_TABLESPACES 0xfffe

/* constants used for reserved parameters                                     */
#define SQLB_RESERVED1 0xfffd
#define SQLB_RESERVED2 0xfffe

/* otcq - Open Tablespace Container Query -- prepares for fetching a list of  */
/* container data                                                             */
SQL_API_RC SQL_API_FN                            /* Open Tablespace           */
                                                 /* Container Query           */
  sqlbotcq (
   struct sqlca * pSqlca,                        /* SQLCA                     */
   unsigned long TablespaceId,                   /* in: id tbs or SQLB_ALL    */
                                                 /* TABLESPACES               */
   unsigned long * pNumContainers);              /* out:  output...the        */
                                                 /* number of containers for  */
                                                 /* the table space           */

/* ftcq - Fetch Tablespace Container Query. Fetch the next block of           */
/* container info.                                                            */
SQL_API_RC SQL_API_FN                            /* Fetch Tablespace          */
                                                 /* Container Query           */
  sqlbftcq (
   struct sqlca * pSqlca,                        /* SQLCA                     */
   unsigned long MaxContainers,                  /* in:  max # entries to     */
                                                 /* return in 'data'          */
   struct SQLB_TBSCONTQRY_DATA * pContainerData, /* out: array of 'maxCont'   */
                                                 /* entries                   */
   unsigned long * pNumContainers);              /* out: # data entries       */
                                                 /* returned on this query    */

/* ctcq - Close Tablespace Container Query. Terminate processing for this     */
/* query                                                                      */
SQL_API_RC SQL_API_FN                            /* Close Tablespace          */
                                                 /* Container Query           */
  sqlbctcq (
   struct sqlca * pSqlca);

/* tcq - Tablespace Container Query                                           */
/* Like 'sqlbmtsq', this api generates a complete list, allocating            */
/* sufficient memory.  The application is responsible for freeing the memory  */
/* when it is finished with it: call sqlefmem(ca,ptr).                        */
SQL_API_RC SQL_API_FN
  sqlbtcq (
   struct sqlca * pSqlca,                        /* SQLCA                     */
   unsigned long TablespaceId,                   /* in: id a tbs or SQLB_ALL  */
                                                 /* TABLESPACES               */
   unsigned long * pNumContainers,               /* out: # entries returned   */
   struct SQLB_TBSCONTQRY_DATA ** ppContainerData);

/* stsc - Set TableSpace Containers                                           */
/* This api is to be used when the tablespace is in a 'storage definition     */
/* pending' or 'storage definition allowed' state.  These states are          */
/* possible during a restore operation, immediately prior to the restoration  */
/* of database pages.  This API is intended to assist in the provision of a   */
/* 'redirected' restore, where the user is restoring a database and a         */
/* different set of OS storage containers is desired/required.                */
/*                                                                            */
/* As input the application provides a list of storage definitions in the     */
/* SQLB_TBSCONTQRY_DATA structure (also used for query purposes). For this    */
/* api only the following fields are examined:                                */
/*                                                                            */
/* unsigned long   nameLen;    length of name (for non-C lang.)               */
/* char            name[SQLB_MAX_CONTAIN_NAME_SZ];  null term. name           */
/* unsigned long   contType;    SQLB_CONT_PATH/DISK/FILE                      */
/* unsigned long   totalPages;  DMS only                                      */
/*                                                                            */
/* processing options...pass 0 for 'nothing-special', OR in the special       */
/* bits.                                                                      */
/*                                                                            */
/* when setting containers prior to a restore/rollforward, the user may want  */
/* to IGNORE any 'add containers' in the logs.  He may simply be providing a  */
/* different 'final' state for the tablespace configuration.  The default     */
/* behavior is to redo 'alter' logrecords after a new container list has      */
/* been set.                                                                  */

#define SQLB_SET_CONT_INIT_STATE 0
#define SQLB_SET_CONT_FINAL_STATE 1

SQL_API_RC SQL_API_FN                            /* Set Tablespace            */
                                                 /* Containers                */
  sqlbstsc (
   struct sqlca * pSqlca,                        /* SQLCA                     */
   unsigned long SetContainerOptions,            /* in: processing options:   */
                                                 /* SQLB_SET_CONT_xxx         */
   unsigned long TablespaceId,                   /* in: table space which is  */
                                                 /* to be changed             */
   unsigned long NumContainers,                  /* in:#containers in the     */
                                                 /* list                      */
   struct SQLB_TBSCONTQRY_DATA * pContainerData); /* container                */
                                                 /* specifications            */

/* gtss - Get TableSpace Statistics                                           */
/* Provide some basic info about the utilization of a tablespace. BETA NOTE:  */
/* only DMS tablespace are supported at this time - SRSFIX                    */
SQL_API_RC SQL_API_FN                            /* Get Tablespace            */
                                                 /* Statistics                */
  sqlbgtss (
   struct sqlca * pSqlca,                        /* SQLCA                     */
   unsigned long TablespaceId,
   struct SQLB_TBS_STATS * pTablespaceStats);

/* END OF TABLESPACE RELATED API'S                                            */

/* Database Utility Commands -- Function Prototypes                           */

#ifndef SQLZ_STACK

#ifdef SQL_REL_10
#define sqluauth(ca) sqluauth_api(ca)
#define sqlustat(tn,idx,ilst,op,sl,ca) sqlustat_api(tn,idx,ilst,op,sl,ca)
#else
#define sqluauth(ca) sqluauth_api(ca)
#define sqludrdt(ngn,tpm,dstf,alst,acnt,dlst,dcnt,ope,ca)\
        sqludrdt_api(ngn,tpm,dstf,alst,acnt,dlst,dcnt,ope,ca)
#define sqluexpt(df,dcol,tcol,ft,ftm,mf,ac,out,ca)\
        sqluexpr_api(df,NULL,NULL,dcol,tcol,ft,ftm,mf,ac,out,NULL,ca)
#define sqluflsh(tn,lsn,ca)\
        sqluflsh_api(tn,lsn,ca)
#define sqluimpt(df,dcol,tcol,ft,ftm,mf,ac,in,out,ca)\
        sqluimpr_api(df,NULL,dcol,tcol,ft,ftm,mf,ac,in,out,NULL,NULL,ca)
#define sqluexpr(df,lp,lf,dcol,tcol,ft,ftm,mf,ac,out,r,ca)\
        sqluexpr_api(df,lp,lf,dcol,tcol,ft,ftm,mf,ac,out,r,ca)
#define sqluimpr(df,lp,dcol,tcol,ft,ftm,mf,ac,in,out,ni,r,ca)\
        sqluimpr_api(df,lp,dcol,tcol,ft,ftm,mf,ac,in,out,ni,r,ca)
#define sqlureot(tn,in,df,ca) sqlureot_api(tn,in,df,ca)
#define sqlurfwd(dbn,ac,pit,ne,fe,le,rt,us,pa,ca)\
        sqlurfwd_api(dbn,ac,pit,ne,fe,le,rt,us,pa,ca)
#define sqlurllf(dbn,ac,app,pit,ne,fe,le,rt,us,pa,ov,mo,re,ca)\
        sqlurllf_api(dbn,ac,app,pit,ne,fe,le,rt,us,pa,ov,mo,re,ca)
#define sqluprfw(dbn,us,pa,ac,pit,al,nu,no,st,ca)\
        sqluprfw_api(dbn,us,pa,ac,pit,al,nu,no,st,ca)
#define sqluroll(rfin,rfout,ca)\
        sqluroll_api(rfin,rfout,ca)
#define sqluload(df,lp,dc,tc,ft,fm,msg,rf,ac,in,out,wd,ct,ni,r,ca)\
        sqluload_api(df,lp,dc,tc,ft,fm,msg,rf,ac,in,out,wd,ct,ni,r,ca)
#define sqluqry(lf,rf,ca)  sqluqry_api(lf,rf,ca)
#define sqlustat(tn,idx,ilst,op,sl,ca) sqlustat_api(tn,idx,ilst,op,sl,ca)
#define sqlurlog(ac,sl,el,lb,lbs,rli,ca)\
        sqlurlog_api(ac,sl,el,lb,lbs,rli,ca)
#define sqlugrpi(nptrs,aptrs,alens,cc,cp,pinfo,pno,nno,chk,ca)\
        sqlugrpi_api(nptrs,aptrs,alens,cc,cp,pinfo,pno,nno,chk,ca)
#define sqlugrpn(nptrs,aptrs,alens,cc,cp,pinfo,pno,nno,chk,ca,df,re1,re2)\
        sqlugrpn_api(nptrs,aptrs,alens,cc,cp,pinfo,pno,nno,chk,ca,df,re1,re2)
#define sqlugtpi(tn,pinfo,ca) sqlugtpi_api(tn,pinfo,ca)

#endif

#endif

/* General Utility Commands                                                   */

SQL_API_RC SQL_API_FN                       /* Open Recovery History File     */
                                            /* Scan                           */
  sqluhops (
   char * pDbAlias,                         /* database alias to open the     */
                                            /* scan for                       */
   char * pTimestamp,                       /* complete/partial timestamp     */
   char * pObjectName,                      /* table name or tablespace name  */
   unsigned short * pNumRows,               /* rows that match parameters     */
   unsigned short * pHandle,                /* handle used for gne/cls        */
   unsigned short CallerAction,             /* list: 0-backup; 1-history      */
   void * pReserved,                        /* reserved for future use        */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Get Next Recovery History      */
                                            /* File Entry                     */
  sqluhgne (
   unsigned short Handle,                   /* handle returned from open      */
   void * pReserved,                        /* reserved for future use        */
   struct sqluhinfo * pHistoryInfo,         /* pointer to entry               */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Close Recovery History File    */
                                            /* Scan                           */
  sqluhcls (
   unsigned short Handle,                   /* handle returned from open      */
   void * pReserved,                        /* reserved for future use        */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Prune Recovery History File    */
  sqluhprn (
   char * pTimestamp,                       /* timestamp (or partial one)     */
   unsigned short ForceOption,              /* 0 for DON'T FORCE              */
                                            /*  1 for FORCE                   */
   void * pReserved,                        /* reserved for future use        */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Update Recovery History File   */
  sqluhupd (
   char * pObjectPart,                      /* timestamp||(001 -> 999)        */
   char * pNewLocation,                     /* the new location               */
   char * pNewDeviceType,                   /* the new device type            */
   char * pNewComment,                      /* new comment                    */
   void * pReserved,                        /* reserved for future use        */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Quiesce Tablespaces for Table  */
  sqluvqdp (
   char * pTableName,                       /* fully qualified table name     */
   long QuiesceMode,                        /* 0 for share                    */
                                            /* 1 for intent to update         */
                                            /* 2 for exclusive                */
                                            /* 9 to reset                     */
   void * pReserved,                        /* reserved for future use        */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Get Authorizations             */
  sqluadau (
   struct sql_authorizations * pAuthorizations,
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Get Authorizations             */
  sqluauth_api (
   struct sqlca *);                         /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Backup Database                */
  sqlubkp (
   char * pDbAlias,                         /* database alias                 */
   unsigned long BufferSize,                /* backup buffer size             */
   unsigned long BackupMode,                /* online or offline              */
   unsigned long BackupType,                /* backup type.                   */
   unsigned long CallerAction,              /* caller action                  */
   char * pApplicationId,                   /* application ID.                */
   char * pTimestamp,                       /* timestamp returned             */
   unsigned long NumBuffers,                /* num of buffers                 */
   struct sqlu_tablespace_bkrst_list * pTablespaceList, /* list of            */
                                            /* tablespace                     */
   struct sqlu_media_list * pMediaTargetList, /* list of media targ           */
   char * pUserName,                        /* user name                      */
   char * pPassword,                        /* password                       */
   void * pReserved2,                       /* reserved for future            */
   unsigned long VendorOptionsSize,         /* size of options                */
   void * pVendorOptions,                   /* reserved for vendor            */
   unsigned long Parallelism,               /* Degree of parallelism          */
   unsigned long * pBackupSize,             /* Size of backup                 */
   void * pReserved4,                       /* reserved for future            */
   void * pReserved3,                       /* reserved for future            */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* V2 Backup Database             */
  sqlubkup (
   char * pDbAlias,                         /* database alias                 */
   unsigned long BufferSize,                /* backup buffer size             */
   unsigned long BackupMode,                /* online or offline              */
   unsigned long BackupType,                /* backup type.                   */
   unsigned long CallerAction,              /* caller action                  */
   char * pApplicationId,                   /* application ID.                */
   char * pTimestamp,                       /* timestamp returned             */
   unsigned long NumBuffers,                /* num of buffers                 */
   struct sqlu_tablespace_bkrst_list * pTablespaceList, /* list of            */
                                            /* tablespace                     */
   struct sqlu_media_list * pMediaTargetList, /* list of media targ           */
   char * pUserName,                        /* user name                      */
   char * pPassword,                        /* password                       */
   void * pReserved2,                       /* reserved for future            */
   unsigned long VendorOptionsSize,         /* size of options                */
   void * pVendorOptions,                   /* reserved for vendor            */
   void * pReserved3,                       /* reserved for future            */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Describe Database              */
  sqludsdb (
   unsigned char * targetPath,              /* Target path                    */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Data Redistribution            */
  sqludrdt_api (
   char * pNodeGroupName,                   /* Nodegroup name                 */
   char * pTargetPMapFileName,              /* Target partition map file      */
                                            /* name                           */
   char * pDataDistFileName,                /* Data distribution file name    */
   SQL_PDB_NODE_TYPE * pAddList,            /* List of nodes to be added      */
   unsigned short AddCount,                 /* No. of nodes to be added       */
   SQL_PDB_NODE_TYPE * pDropList,           /* List of nodes to be dropped    */
   unsigned short DropCount,                /* No. of nodes to be dropped     */
   unsigned char DataRedistOption,          /* Data redistribution option     */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Restore Database               */
  sqlurst (
   char * pSourceDbAlias,                   /* source alias name              */
   char * pTargetDbAlias,                   /* target dbalias                 */
   unsigned long BufferSize,                /* restore buffer size            */
   unsigned long RollforwardMode,           /* 0 - roll forward               */
                                            /* 1 - do not roll fwd            */
   unsigned long RestoreType,               /* 0 - normal restore             */
                                            /* 3 - online restore for         */
                                            /* tablespace only                */
                                            /* 5 - history file only          */
   unsigned long RestoreMode,               /* Online/Offline                 */
   unsigned long CallerAction,              /* caller action                  */
   char * pApplicationId,                   /* application ID.                */
   char * pTimestamp,                       /* timestamp for backup image     */
   char * pTargetPath,                      /* target path for new database   */
   unsigned long NumBuffers,                /* num of buffers                 */
   struct sqlu_tablespace_bkrst_list * pTablespaceList, /* reserved for       */
                                            /* future use.                    */
   struct sqlu_media_list * pMediaSourceList, /* list of media controllers    */
                                            /* to use.                        */
   char * pUserName,                        /* userid                         */
   char * pPassword,                        /* password                       */
   void * pReserved2,                       /* reserved for future use        */
   unsigned long VendorOptionsSize,         /* size of options field          */
   void * pVendorOptions,                   /* reserved for vendor use        */
   unsigned long Parallelism,               /* Degree of parallelism          */
   void * pRestoreInfo,                     /* reserved                       */
   void * pContainerPageList,               /* Container/Page restore list    */
   void * pReserved3,                       /* reserved for future use        */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* V2 Restore Database            */
  sqlursto (
   char * pSourceDbAlias,                   /* source alias name              */
   char * pTargetDbAlias,                   /* target dbalias                 */
   unsigned long BufferSize,                /* restore buffer size            */
   unsigned long RollforwardMode,           /* 0 - roll forward               */
                                            /* 1 - do not roll fwd            */
   unsigned long RestoreType,               /* 0 - normal restore             */
                                            /* 3 - online restore for         */
                                            /* tablespace only                */
                                            /* 5 - history file only          */
   unsigned long CallerAction,              /* caller action                  */
   char * pApplicationId,                   /* application ID.                */
   char * pTimestamp,                       /* timestamp for backup image     */
   char * pTargetPath,                      /* target path for new database   */
   unsigned long NumBuffers,                /* num of buffers                 */
   struct sqlu_tablespace_bkrst_list * pTablespaceList, /* reserved for       */
                                            /* future use.                    */
   struct sqlu_media_list * pMediaSourceList, /* list of media controllers    */
                                            /* to use.                        */
   char * pUserName,                        /* userid                         */
   char * pPassword,                        /* password                       */
   void * pReserved2,                       /* reserved for future use        */
   unsigned long VendorOptionsSize,         /* size of options field          */
   void * pVendorOptions,                   /* reserved for vendor use        */
   void * pReserved3,                       /* reserved for future use        */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Rollforward Database           */
  sqluroll_api (
   struct rfwd_input * pRfwdInput,          /* input structure                */
   struct rfwd_output * pRfwdOuput,         /* output structure               */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Old backup                     */
  sqlubckp (
   _SQLOLDCHAR *,                           /* alias name                     */
   unsigned long,                           /* backup buffer size             */
   unsigned short,                          /* online or offline              */
   unsigned short,                          /* reserved                       */
   unsigned short,                          /* ADSM or otherwise              */
   _SQLOLDCHAR *,                           /* dir or device name             */
   unsigned short,                          /* caller action                  */
   _SQLOLDCHAR *,                           /* timestamp returned             */
   _SQLOLDCHAR *,                           /* userid                         */
   _SQLOLDCHAR *,                           /* password                       */
   struct sqlca *);                         /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Old Restore                    */
  sqludrst (
   _SQLOLDCHAR *,                           /* source database alias          */
   _SQLOLDCHAR *,                           /* target database alias          */
   unsigned long,                           /* restore buffer size            */
   unsigned short,                          /* media type: ADSM or otherwise  */
   _SQLOLDCHAR *,                           /* dir or device name             */
   _SQLOLDCHAR *,                           /* timestamp of backup            */
   unsigned short,                          /* roll forward flag              */
   unsigned short,                          /* caller action                  */
   _SQLOLDCHAR *,                           /* target: new dbase              */
   _SQLOLDCHAR *,                           /* userid                         */
   _SQLOLDCHAR *,                           /* password                       */
   struct sqlca *);                         /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Old Rollforward Database       */
  sqlurllf_api (
   char * pDbAlias,                         /* database alias                 */
   unsigned short CallerAction,             /* action                         */
   char * pApplicationId,                   /* application id                 */
   char * pStopTime,                        /* stop time                      */
   char * pNextArcFileName,                 /* next archive file needed       */
   char * pFirstDelArcFileName,             /* first archive file to be       */
                                            /* deleted                        */
   char * pLastDelArcFileName,              /* last archive file to be        */
                                            /* deleted                        */
   char * pLastCommitTime,                  /* last commit time               */
   char * pUserName,                        /* user name                      */
   char * pPassword,                        /* password                       */
   char * pOverflowLogPath,                 /* overflow log path              */
   unsigned short ConnectMode,              /* connect mode                   */
   void * pReserved,                        /* reserved                       */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Old PE Rollforward Database    */
  sqluprfw_api (
   _SQLOLDCHAR *,                           /* database name                  */
   _SQLOLDCHAR *,                           /* userid                         */
   _SQLOLDCHAR *,                           /* password                       */
   unsigned short,                          /* action                         */
   _SQLOLDCHAR *,                           /* Stop Timestamp                 */
   long,                                    /* all node flag                  */
   long,                                    /* number of nodes in nodelist    */
   SQL_PDB_NODE_TYPE *,                     /* list of node numbers           */
   struct sqlurf_stat *,                    /* status                         */
   struct sqlca *);                         /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Old Rollforward Database       */
  sqlurfwd_api (
   _SQLOLDCHAR *,                           /* database name                  */
   unsigned short,                          /* action                         */
   _SQLOLDCHAR *,                           /* Stop Timestamp                 */
   _SQLOLDCHAR *,                           /* Next Archive File needed       */
   _SQLOLDCHAR *,                           /* First Archive File to be       */
                                            /* deleted                        */
   _SQLOLDCHAR *,                           /* Last Archive File to be        */
                                            /* deleted                        */
   _SQLOLDCHAR *,                           /* Returned Timestamp             */
   _SQLOLDCHAR *,                           /* userid                         */
   _SQLOLDCHAR *,                           /* password                       */
   struct sqlca *);                         /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Export                         */
  sqluexpr_api (
   char * pDataFileName,                    /* data file                      */
   sqlu_media_list * pLobPathList,          /* lob paths                      */
   sqlu_media_list * pLobFileList,          /* lob files                      */
   struct sqldcol * pDataDescriptor,        /* dcoldata                       */
   struct sqlchar * pActionString,          /* tcolstrg                       */
   char * pFileType,                        /* file type                      */
   struct sqlchar * pFileTypeMod,           /* file type mod                  */
   char * pMsgFileName,                     /* msg file                       */
   short CallerAction,                      /* caller action                  */
   struct sqluexpt_out*  pOutputInfo,       /* rows exported                  */
   void * pReserved,                        /* reserved                       */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Flush Table                    */
  sqluflsh_api (
   char *,                                  /* Fully qualified table name     */
   SQLU_LSN *,                              /* Log Sequence Nbr               */
   struct sqlca *);                         /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Export                         */
  sqluexpt_api (
   _SQLOLDCHAR *,                           /* datafile                       */
   struct sqldcol *,                        /* dcoldata                       */
   struct sqlchar *,                        /* tcolstrg                       */
   _SQLOLDCHAR *,                           /* filetype                       */
   struct sqlchar *,                        /* filetmod                       */
   _SQLOLDCHAR *,                           /* msgfile                        */
   short,                                   /* caller action                  */
   struct sqluexpt_out* ,                   /* rows exported                  */
   struct sqlca *);                         /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Get Row Partitioning           */
                                            /* Information                    */
  sqlugrpi_api (
   unsigned short num_ptrs,                 /* Number of pointers             */
   unsigned char ** ptr_array,              /* An array of pointers           */
   unsigned short * ptr_lens,               /* An array of string lengths     */
   unsigned short ctrycode,                 /* Countrycode                    */
   unsigned short codepage,                 /* Codepage                       */
   struct sqlupi * part_info,               /* Partitioning Information       */
   short * part_num,                        /* Partition number               */
   SQL_PDB_NODE_TYPE * node_num,            /* Node number                    */
   unsigned short chklvl,                   /* Check level                    */
   struct sqlca * sqlca);                   /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Get Row Partitioning Number    */
  sqlugrpn_api (
   unsigned short num_ptrs,                 /* Number of pointers             */
   unsigned char ** ptr_array,              /* An array of pointers           */
   unsigned short * ptr_lens,               /* An array of string lengths     */
   unsigned short ctrycode,                 /* Countrycode                    */
   unsigned short codepage,                 /* Codepage                       */
   struct sqlupi * part_info,               /* Partitioning Information       */
   short * part_num,                        /* Partition number               */
   SQL_PDB_NODE_TYPE * node_num,            /* Node number                    */
   unsigned short chklvl,                   /* Check level                    */
   struct sqlca * sqlca,                    /* SQLCA                          */
   short dataformat,                        /* data format                    */
   void * pReserved1,                       /* reserved for future use        */
   void * pReserved2);                      /* reserved for future use        */

SQL_API_RC SQL_API_FN                       /* Get Table Partitioning         */
                                            /* Information                    */
  sqlugtpi_api (
   unsigned char * tablename,               /* Table name                     */
   struct sqlupi * part_info,               /* Partitioning Information       */
   struct sqlca * sqlca);                   /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Import                         */
  sqluimpt_api (
   _SQLOLDCHAR *,                           /* datafile                       */
   struct sqldcol *,                        /* dcoldata                       */
   struct sqlchar *,                        /* tcolstrg                       */
   _SQLOLDCHAR *,                           /* filetype                       */
   struct sqlchar *,                        /* filetmod                       */
   _SQLOLDCHAR *,                           /* msgfile                        */
   short,                                   /* caller action                  */
   struct sqluimpt_in* ,                    /* input parms                    */
   struct sqluimpt_out* ,                   /* output parms                   */
   struct sqlca *);                         /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Import                         */
  sqluimpr_api (
   char * pDataFileName,                    /* datafile                       */
   sqlu_media_list * pLobPathList,          /* lobpath                        */
   struct sqldcol * pDataDescriptor,        /* dcoldata                       */
   struct sqlchar * pActionString,          /* tcolstrg                       */
   char * pFileType,                        /* filetype                       */
   struct sqlchar * pFileTypeMod,           /* filetmod                       */
   char * pMsgFileName,                     /* msgfile                        */
   short CallerAction,                      /* caller action                  */
   struct sqluimpt_in*  pImportInfoIn,      /* input parms                    */
   struct sqluimpt_out*  pImportInfoOut,    /* output parms                   */
   long * pNullIndicators,                  /* nullind                        */
   void * pReserved,                        /* reserved                       */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Load                           */
  sqluload_api (
   sqlu_media_list * pDataFileList,         /* input data files               */
   sqlu_media_list * pLobPathList,          /* input lob paths                */
   struct sqldcol * pDataDescriptor,        /* dcoldata - describes input     */
                                            /* data                           */
   struct sqlchar * pActionString,          /* tcolstrg - describes the       */
                                            /* columns of the table to load   */
   char * pFileType,                        /* file type                      */
   struct sqlchar * pFileTypeMod,           /* filetmod                       */
   char * pLocalMsgFileName,                /* message file name              */
   char * pRemoteMsgFileName,               /* remote file name               */
   short CallerAction,                      /* caller action                  */
   struct sqluload_in * pLoadInfoIn,        /* input                          */
   struct sqluload_out * pLoadInfoOut,      /* output                         */
   sqlu_media_list * pWorkDirectoryList,    /* work dirs                      */
   sqlu_media_list * pCopyTargetList,       /* copy targets                   */
   long * pNullIndicators,                  /* null ind                       */
   void * pReserved,                        /* reserved                       */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Query                          */
  sqluqry_api (
   char * pLocalMsgFileName,                /* local msg file                 */
   char * pRemoteMsgFileName,               /* remote msg file                */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Asynchronous Read Log          */
  sqlurlog_api (
   unsigned long CallerAction,              /* caller action                  */
   SQLU_LSN * pStartLsn,                    /* read start log sequence        */
                                            /* number                         */
   SQLU_LSN * pEndLsn,                      /* read end log sequence number   */
   char * pLogBuffer,                       /* user buffer                    */
   unsigned long LogBufferSize,             /* size of user buffer            */
   SQLU_RLOG_INFO * pReadLogInfo,           /* read log information           */
                                            /* structure                      */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Reorganize Table               */
  sqlureot_api (
   _SQLOLDCHAR * pTableName,                /* table name                     */
   _SQLOLDCHAR * pIndexName,                /* fully-qualified index name     */
   _SQLOLDCHAR * pTablespace,               /* tablespace                     */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Run Statistics                 */
  sqlustat_api (
   _SQLOLDCHAR * pTableName,                /* table name                     */
   unsigned short NumIndexes,               /* number of indexes              */
   _SQLOLDCHAR ** ppIndexList,              /* indexlist                      */
   unsigned char StatsOption,               /* statsopt                       */
   unsigned char ShareLevel,                /* sharelvl                       */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Get Table Authorizations       */
  sqlutbau (
   _SQLOLDCHAR *,                           /* fully-qualified table name     */
   struct sqlca *);                         /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Get Int Col Part Key Value     */
                                            /* For Given Part Map Index       */
  sqluihsh (
   long InIndex,                            /* input partition map index      */
   long * OutInt,                           /* output integer column part     */
                                            /* key value                      */
   struct sqlca * pSqlca);                  /* SQLCA                          */

/* Generic APIs                                                               */

SQL_API_RC SQL_API_FN                       /* Get Authorizations             */
  sqlgadau (
   struct sql_authorizations * pAuthorizations,
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Get Default Database           */
                                            /* Configuration                  */
  sqlgddb (
   unsigned short DbAliasLen,               /* database alias length          */
   unsigned short NumItems,                 /* count of requested no of       */
                                            /* items                          */
   struct sqlfupd * pItemList,              /* list of items returned         */
   struct sqlca * pSqlca,                   /* SQLCA                          */
   char * pDbAlias);                        /* database  alias                */

SQL_API_RC SQL_API_FN                       /* Reset Database Configuration   */
  sqlgrdb (
   unsigned short DbAliasLen,               /* database alias length          */
   struct sqlca * pSqlca,                   /* SQLCA                          */
   char * pDbAlias);                        /* database alias                 */

SQL_API_RC SQL_API_FN                       /* Update Database Configuration  */
  sqlgudb (
   unsigned short DbAliasLen,               /* database alias length          */
   unsigned short NumItems,                 /* count                          */
   unsigned short * pItemListLens,          /* List of item lengths           */
   struct sqlfupd * pItemList,              /* list of items                  */
   struct sqlca * pSqlca,                   /* SQLCA                          */
   char * pDbAlias);                        /* database                       */

SQL_API_RC SQL_API_FN                       /* Get Database Configuration     */
  sqlgxdb (
   unsigned short DbAliasLen,               /* database alias length          */
   unsigned short NumItems,                 /* count of items being returned  */
   struct sqlfupd * pItemList,              /* list of items                  */
   struct sqlca * pSqlca,                   /* SQLCA                          */
   char * pDbAlias);                        /* database alias                 */

SQL_API_RC SQL_API_FN                       /* Get Database Manager           */
                                            /* Configuration Defaults         */
  sqlgdsys (
   unsigned short NumItems,                 /* count of items being returned  */
   struct sqlfupd * pItemList,              /* list of items                  */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Backup Database                */
  sqlgbkp (
   unsigned short DbAliasLen,               /* database alias length          */
   unsigned short UserNameLen,              /* user name length               */
   unsigned short PasswordLen,              /* password length                */
   unsigned short * pReserved1,             /* reserved for future use        */
   char * pDbAlias,                         /* database alias                 */
   unsigned long BufferSize,                /* buffer size in 4K units        */
   unsigned long BackupMode,                /* online or offline              */
   unsigned long BackupType,                /* 0 - full dB; 3 - tablespace    */
   unsigned long CallerAction,              /* caller action                  */
   char * pApplicationId,                   /* application ID.                */
   char * pTimestamp,                       /* timestamp returned             */
   unsigned long NumBuffers,                /* number of buffers to use       */
   struct sqlu_tablespace_bkrst_list * pTablespaceList, /* list of            */
                                            /* tablespace names               */
   struct sqlu_media_list * pMediaTargetList, /* list of media targets        */
   char * pUserName,                        /* user name                      */
   char * pPassword,                        /* password                       */
   void * pReserved2,                       /* reserved for future use        */
   unsigned long VendorOptionsSize,         /* size of options field          */
   void * pVendorOptions,                   /* reserved for vendor use        */
   unsigned long Parallelism,               /* Degree of parallelism          */
   unsigned long * pBackupSize,             /* Size of backup                 */
   void * pReserved4,                       /* reserved for future            */
   void * pReserved3,                       /* reserved for future use        */
   struct sqlca * pSqlca);                  /* sqlca structure                */

SQL_API_RC SQL_API_FN                       /* Backup Database                */
  sqlgbkup (
   unsigned short DbAliasLen,               /* database alias length          */
   unsigned short UserNameLen,              /* user name length               */
   unsigned short PasswordLen,              /* password length                */
   unsigned short * pReserved1,             /* reserved for future use        */
   char * pDbAlias,                         /* database alias                 */
   unsigned long BufferSize,                /* buffer size in 4K units        */
   unsigned long BackupMode,                /* online or offline              */
   unsigned long BackupType,                /* 0 - full dB; 3 - tablespace    */
   unsigned long CallerAction,              /* caller action                  */
   char * pApplicationId,                   /* application ID.                */
   char * pTimestamp,                       /* timestamp returned             */
   unsigned long NumBuffers,                /* number of buffers to use       */
   struct sqlu_tablespace_bkrst_list * pTablespaceList, /* list of            */
                                            /* tablespace names               */
   struct sqlu_media_list * pMediaTargetList, /* list of media targets        */
   char * pUserName,                        /* user name                      */
   char * pPassword,                        /* password                       */
   void * pReserved2,                       /* reserved for future use        */
   unsigned long VendorOptionsSize,         /* size of options field          */
   void * pVendorOptions,                   /* reserved for vendor use        */
   void * pReserved3,                       /* reserved for future use        */
   struct sqlca * pSqlca);                  /* sqlca structure                */

SQL_API_RC SQL_API_FN                       /* Describe Database              */
  sqlgdsdb (
   unsigned short targetPathLen,            /* Target path length             */
   unsigned char * targetPath,              /* Target path                    */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Close Recovery History File    */
                                            /* Scan                           */
  sqlghcls (
   unsigned short Handle,                   /* handle returned from open      */
   void * pReserved,                        /* reserved for future use        */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Get Next Recovery History      */
                                            /* File Entry                     */
  sqlghgne (
   unsigned short Handle,                   /* handle returned from open      */
   void * pReserved,                        /* reserved for future use        */
   struct sqluhinfo * pHistoryInfo,         /* pointer to the address of the  */
                                            /* history file entry info        */
                                            /* buffer                         */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Open Recovery History File     */
                                            /* Scan                           */
  sqlghops (
   unsigned short DbAliasLen,               /* database alias length          */
   unsigned short TimestampLen,             /* timestamp length               */
   unsigned short ObjectNameLen,            /* object name length             */
   char * pDbAlias,                         /* database alias                 */
   char * pTimestamp,                       /* timestamp used to select       */
                                            /* records                        */
   char * pObjectName,                      /* object name used to select     */
                                            /* records                        */
   unsigned short * pNumRows,               /* return no. of matching         */
                                            /* history file entries           */
   unsigned short * pHandle,                /* return handle used for future  */
                                            /* access                         */
   unsigned short CallerAction,             /* '0' for backup                 */
                                            /* '1' for history                */
   void * pReserved,                        /* reserved for future use        */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Prune Recovery History File    */
  sqlghprn (
   unsigned short TimestampLen,             /* timestamp id length            */
   char * pTimestamp,                       /* timestamp (whole or part)      */
   unsigned short ForceOption,              /* force option                   */
   void * pReserved,                        /* reserved for future use        */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Update Recovery History File   */
  sqlghupd (
   unsigned short ObjectPartLen,            /* object_part length             */
   unsigned short NewLocationLen,           /* new_location length            */
   unsigned short NewDeviceTypeLen,         /* new_device_type length         */
   unsigned short NewCommentLen,            /* new_comment length             */
   char * pObjectPart,                      /* timestamp||(001 -> 999)        */
   char * pNewLocation,                     /* the new location               */
   char * pNewDeviceType,                   /* the new device type            */
   char * pNewComment,                      /* new comment                    */
   void * pReserved,                        /* reserved for future use        */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Rollforward Database           */
  sqlgrllf (
   unsigned short DbAliasLen,               /* database alias length          */
   unsigned short StopTimeLen,              /* stop time length               */
   unsigned short UserNameLen,              /* user name length               */
   unsigned short PasswordLen,              /* password length                */
   unsigned short OverflowLogPathLen,       /* overflow log path length       */
   char * pDbAlias,                         /* database alias                 */
   unsigned short CallerAction,             /* caller action                  */
   char * pApplicationId,                   /* application id returned        */
   char * pStopTime,                        /* stop time                      */
   char * pNextArcFileName,                 /* next archive file              */
   char * pFirstDelArcFileName,             /* first del archive file         */
   char * pLastDelArcFileName,              /* last del archive file          */
   char * pLastCommitTime,                  /* last commit time               */
   char * pUserName,                        /* user name                      */
   char * pPassword,                        /* password                       */
   char * pOverflowLogPath,                 /* overflow log path name         */
   unsigned short ConnectMode,              /* connect mode                   */
   void * pReserved,                        /* reserved for future use        */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Rollforward Database           */
  sqlgroll (
   struct grfwd_input grfwdin,              /* input structure                */
   struct rfwd_output rfwdout,              /* output structure               */
   struct sqlca * Sqlca);                   /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Restore Database               */
  sqlgrst (
   unsigned short SourceDbAliasLen,         /* source database alias length   */
   unsigned short TargetDbAliasLen,         /* target database alias length   */
   unsigned short TimestampLen,             /* timestamp length               */
   unsigned short TargetPathLen,            /* target path length             */
   unsigned short UserNameLen,              /* user name length               */
   unsigned short PasswordLen,              /* password  length               */
   unsigned short * pReserved1,             /* nodename length                */
   char * pSourceDbAlias,                   /* source database alias          */
   char * pTargetDbAlias,                   /* target database alias          */
   unsigned long BufferSize,                /* buffer size in 4K units        */
   unsigned long RollforwardMode,           /* 0 - roll forward               */
                                            /* 1 - do not roll forward        */
   unsigned long RestoreType,               /* 0 - normal restore             */
                                            /* 3 - online restore             */
                                            /*     for tablespace only        */
                                            /* 5 - history file only          */
   unsigned long RestoreMode,               /* Online/Offline                 */
   unsigned long CallerAction,              /* caller action                  */
   char * pApplicationId,                   /* application id returned        */
   char * pTimestamp,                       /* timestamp of backup            */
   char * pTargetPath,                      /* target: new path               */
   unsigned long NumBuffers,                /* number of buffers to use       */
   struct sqlu_tablespace_bkrst_list * pTablespaceList, /* reserved for       */
                                            /* future use                     */
   struct sqlu_media_list * pMediaSourceList, /* list of media sources        */
   char * pUserName,                        /* user name                      */
   char * pPassword,                        /* password                       */
   void * pReserved2,                       /* reserved for future use        */
   unsigned long Parallelism,               /* Degree of parallelism          */
   unsigned short RestoreInfoSize,          /* reserved                       */
   void * pRestoreInfo,                     /* reserved                       */
   unsigned short ContainerPageListSize,    /* Size of Container/Page         */
                                            /* restore list                   */
   void * pContainerPageList,               /* Container/Page restore list    */
   unsigned long VendorOptionsSize,         /* size of options field          */
   void * pVendorOptions,                   /* reserved for vendor use        */
   void * pReserved3,                       /* reserved for future use        */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Restore Database               */
  sqlgrsto (
   unsigned short SourceDbAliasLen,         /* source database alias length   */
   unsigned short TargetDbAliasLen,         /* target database alias length   */
   unsigned short TimestampLen,             /* timestamp length               */
   unsigned short TargetPathLen,            /* target path length             */
   unsigned short UserNameLen,              /* user name length               */
   unsigned short PasswordLen,              /* password  length               */
   unsigned short * pReserved1,             /* nodename length                */
   char * pSourceDbAlias,                   /* source database alias          */
   char * pTargetDbAlias,                   /* target database alias          */
   unsigned long BufferSize,                /* buffer size in 4K units        */
   unsigned long RollforwardMode,           /* 0 - roll forward               */
                                            /* 1 - do not roll forward        */
   unsigned long RestoreType,               /* 0 - normal restore             */
                                            /* 3 - online restore             */
                                            /*     for tablespace only        */
                                            /* 5 - history file only          */
   unsigned long CallerAction,              /* caller action                  */
   char * pApplicationId,                   /* application id returned        */
   char * pTimestamp,                       /* timestamp of backup            */
   char * pTargetPath,                      /* target: new path               */
   unsigned long NumBuffers,                /* number of buffers to use       */
   struct sqlu_tablespace_bkrst_list * pTablespaceList, /* reserved for       */
                                            /* future use                     */
   struct sqlu_media_list * pMediaSourceList, /* list of media sources        */
   char * pUserName,                        /* user name                      */
   char * pPassword,                        /* password                       */
   void * pReserved2,                       /* reserved for future use        */
   unsigned long VendorOptionsSize,         /* size of options field          */
   void * pVendorOptions,                   /* reserved for vendor use        */
   void * pReserved3,                       /* reserved for future use        */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Quiesce Tablespaces for Table  */
  sqlgvqdp (
   unsigned short TableNameLen,             /* length of table_name           */
   char * pTableName,                       /* table name                     */
   long QuiesceMode,                        /* 0 for share                    */
                                            /* 1 for intent to update         */
                                            /* 2 for exclusive                */
                                            /* 9 to reset                     */
   void * pReserved,                        /* reserved for future use        */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Old Backup                     */
  sqlgbckp (
   unsigned short,                          /* password length                */
   unsigned short,                          /* userid length                  */
   unsigned short,                          /* media target length            */
   unsigned short,                          /* database name length           */
   struct sqlca *,                          /* ptr to sqlca                   */
   _SQLOLDCHAR *,                           /* ptr to password                */
   _SQLOLDCHAR *,                           /* ptr to userid                  */
   _SQLOLDCHAR *,                           /* ptr to timestamp               */
   unsigned short,                          /* caller action                  */
   _SQLOLDCHAR *,                           /* ptr to media target            */
   unsigned short,                          /* media type                     */
   unsigned short,                          /* reserved                       */
   unsigned short,                          /* backup mode                    */
   unsigned long,                           /* buffer size                    */
   _SQLOLDCHAR *);                          /* ptr to database name           */

SQL_API_RC SQL_API_FN                       /* Data Redistribution            */
  sqlgdrdt (
   unsigned short NodeGroupNameLen,         /* Length of nodegroup name       */
   unsigned short TargetPMapFileNameLen,    /* Length of target partition     */
                                            /* map file name                  */
   unsigned short DataDistFileNameLen,      /* Length of data distribution    */
                                            /* file name                      */
   char * pNodeGroupName,                   /* Nodegroup name                 */
   char * pTargetPMapFileName,              /* Target partition map file      */
                                            /* name                           */
   char * pDataDistFileName,                /* Data distribution file name    */
   SQL_PDB_NODE_TYPE * pAddList,            /* List of nodes to be added      */
   unsigned short AddCount,                 /* No. of nodes to be added       */
   SQL_PDB_NODE_TYPE * pDropList,           /* List of nodes to be dropped    */
   unsigned short DropCount,                /* No. of nodes to be dropped     */
   unsigned char DataRedistOption,          /* Data redistribution option     */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Restore                        */
  sqlgdrst (
   unsigned short,                          /* password length                */
   unsigned short,                          /* userid length                  */
   unsigned short,                          /* target length                  */
   unsigned short,                          /* timestamp length               */
   unsigned short,                          /* media source length            */
   unsigned short,                          /* target database length         */
   unsigned short,                          /* source database length         */
   struct sqlca *,                          /* ptr to sqlca                   */
   _SQLOLDCHAR *,                           /* ptr to password                */
   _SQLOLDCHAR *,                           /* ptr to userid                  */
   _SQLOLDCHAR *,                           /* ptr to target                  */
   unsigned short,                          /* caller action                  */
   unsigned short,                          /* restore mode                   */
   _SQLOLDCHAR *,                           /* ptr to timestamp               */
   _SQLOLDCHAR *,                           /* ptr to media source            */
   unsigned short,                          /* media type                     */
   unsigned long,                           /* buffer size                    */
   _SQLOLDCHAR *,                           /* ptr to target database         */
   _SQLOLDCHAR *);                          /* ptr to source database         */

SQL_API_RC SQL_API_FN                       /* EXPORT FROM                    */
  sqlgexpr (
   unsigned short DataFileNameLen,          /* data file name length          */
   unsigned short FileTypeLen,              /* file type length               */
   unsigned short MsgFileNameLen,           /* msg file name length           */
   char * pDataFileName,                    /* data file                      */
   sqlu_media_list * pLobPathList,          /* lob paths                      */
   sqlu_media_list * pLobFileList,          /* lob file names                 */
   struct sqldcol * pDataDescriptor,        /* dcoldata                       */
   struct sqlchar * pActionString,          /* tcolstrg                       */
   char * pFileType,                        /* file type                      */
   struct sqlchar * pFileTypeMod,           /* file type mod                  */
   char * pMsgFileName,                     /* msg file name                  */
   short CallerAction,                      /* caller action                  */
   struct sqluexpt_out*  pOutputInfo,       /* rows exported                  */
   void * pReserved,                        /* reserved                       */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Export                         */
  sqlgexpt (
   unsigned short,                          /* message file name length       */
   unsigned short,                          /* file type length               */
   unsigned short,                          /* data file name length          */
   struct sqlca *,                          /* SQLCA                          */
   struct sqluexpt_out* ,                   /* ptr to rows exported           */
   short,                                   /* caller action                  */
   _SQLOLDCHAR *,                           /* message file name              */
   struct sqlchar *,                        /* ptr to file type mod           */
   _SQLOLDCHAR *,                           /* ptr to filetype                */
   struct sqlchar *,                        /* ptr to tcolstrg                */
   struct sqldcol *,                        /* ptr to dcoldata                */
   _SQLOLDCHAR *);                          /* data file name                 */

SQL_API_RC SQL_API_FN                       /* Import                         */
  sqlgimpr (
   unsigned short DataFileNameLen,          /* datafile length                */
   unsigned short FileTypeLen,              /* file type length               */
   unsigned short MsgFileNameLen,           /* msgfile length                 */
   char * pDataFileName,                    /* data file name                 */
   sqlu_media_list * pLobPathList,          /* lobpaths                       */
   struct sqldcol * pDataDescriptor,        /* dcoldata                       */
   struct sqlchar * pActionString,          /* tcolstrg                       */
   char * pFileType,                        /* filetype                       */
   struct sqlchar * pFileTypeMod,           /* filetmod                       */
   char * pMsgFileName,                     /* message file name              */
   short CallerAction,                      /* caller action                  */
   struct sqluimpt_in*  pImportInfoIn,      /* input parms                    */
   struct sqluimpt_out*  pImportInfoOut,    /* output parms                   */
   long * NullIndicators,                   /* nullind                        */
   void * pReserved,                        /* reserved                       */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Get Row Partitioning           */
                                            /* Information                    */
  sqlggrpi (
   unsigned short num_ptrs,                 /* Number of pointers             */
   unsigned char ** ptr_array,              /* An array of pointers           */
   unsigned short * ptr_lens,               /* An array of string lengths     */
   unsigned short ctrycode,                 /* Countrycode                    */
   unsigned short codepage,                 /* Codepage                       */
   struct sqlupi * part_info,               /* Partitioning Information       */
   short * part_num,                        /* Partition number               */
   SQL_PDB_NODE_TYPE * node_num,            /* Node number                    */
   unsigned short chklvl,                   /* Check level                    */
   struct sqlca * sqlca);                   /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Get Row Partitioning Number    */
  sqlggrpn (
   unsigned short num_ptrs,                 /* Number of pointers             */
   unsigned char ** ptr_array,              /* An array of pointers           */
   unsigned short * ptr_lens,               /* An array of string lengths     */
   unsigned short ctrycode,                 /* Countrycode                    */
   unsigned short codepage,                 /* Codepage                       */
   struct sqlupi * part_info,               /* Partitioning Information       */
   short * part_num,                        /* Partition number               */
   SQL_PDB_NODE_TYPE * node_num,            /* Node number                    */
   unsigned short chklvl,                   /* Check level                    */
   struct sqlca * sqlca,                    /* SQLCA                          */
   short dataformat,                        /* dataformat                     */
   void * pReserved1,                       /* reserved for future use        */
   void * pReserved2);                      /* reserved for future use        */

SQL_API_RC SQL_API_FN                       /* Get Table Partitioning         */
                                            /* Information                    */
  sqlggtpi (
   unsigned short tn_length,                /* Length of table name           */
   unsigned char * tablename,               /* Table name                     */
   struct sqlupi * part_info,               /* Partitioning Information       */
   struct sqlca * sqlca);                   /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Import                         */
  sqlgimpt (
   unsigned short,                          /* message file name length       */
   unsigned short,                          /* file type length               */
   unsigned short,                          /* data file name length          */
   struct sqlca *,                          /* SQLCA                          */
   struct sqluimpt_out *,                   /* ptr to output parms            */
   struct sqluimpt_in *,                    /* ptr to input parms             */
   short,                                   /* caller action                  */
   _SQLOLDCHAR *,                           /* message file name              */
   struct sqlchar *,                        /* file mode description          */
   _SQLOLDCHAR *,                           /* file type                      */
   struct sqlchar *,                        /* ptr to table/column            */
   struct sqldcol *,                        /* ptr to column data             */
   _SQLOLDCHAR *);                          /* data file name                 */

SQL_API_RC SQL_API_FN                       /* Load                           */
  sqlgload (
   unsigned short FileTypeLen,              /* file type length               */
   unsigned short LocalMsgFileNameLen,      /* message file length            */
   unsigned short RemoteMsgFileNameLen,     /* remote file length             */
   sqlu_media_list * pDataFileList,         /* data file name                 */
   sqlu_media_list * pLobPathList,          /* lobpaths                       */
   struct sqldcol * pDataDescriptor,        /* dcoldata                       */
   struct sqlchar * pActionString,          /* tcolstrg                       */
   char * pFileType,                        /* file type                      */
   struct sqlchar * pFileTypeMod,           /* filetmod                       */
   char * pLocalMsgFileName,                /* message file name              */
   char * pRemoteMsgFileName,               /* remote file name               */
   short CallerAction,                      /* caller action                  */
   struct sqluload_in * pLoadInfoIn,        /* input                          */
   struct sqluload_out * pLoadInfoOut,      /* output                         */
   sqlu_media_list * pWorkDirectoryList,    /* work directory                 */
   sqlu_media_list * pCopyTargetList,       /* copy target                    */
   long * pNullIndicators,                  /* null ind                       */
   void * pReserved,                        /* reserved                       */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Query                          */
  sqlgqry (
   unsigned short LocalMsgFileNameLen,      /* lf_length                      */
   unsigned short RemoteMsgFileNameLen,     /* rf_length                      */
   char * pLocalMsgFileName,                /* local file                     */
   char * pRemoteMsgFileName,               /* remote file                    */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Reorganize Table               */
  sqlgreot (
   unsigned short TablespaceLen,            /* tablespace length              */
   unsigned short IndexNameLen,             /* index name length              */
   unsigned short TableNameLen,             /* table name length              */
   struct sqlca * pSqlca,                   /* SQLCA                          */
   _SQLOLDCHAR * pTablespace,               /* tablespace                     */
   _SQLOLDCHAR * pIndexName,                /* index name                     */
   _SQLOLDCHAR * pTableName);               /* table name                     */

SQL_API_RC SQL_API_FN                       /* Rollforward                    */
  sqlgrfwd (
   unsigned short,                          /* password length                */
   unsigned short,                          /* userid length                  */
   unsigned short,                          /* point in time length           */
   unsigned short,                          /* database name length           */
   struct sqlca *,                          /* SQLCA                          */
   _SQLOLDCHAR *,                           /* password                       */
   _SQLOLDCHAR *,                           /* userid                         */
   _SQLOLDCHAR *,                           /* last commit time               */
   _SQLOLDCHAR *,                           /* last archive del               */
   _SQLOLDCHAR *,                           /* first archive del              */
   _SQLOLDCHAR *,                           /* next archive need              */
   _SQLOLDCHAR *,                           /* point in time                  */
   unsigned short,                          /* action                         */
   _SQLOLDCHAR *);                          /* database name                  */

SQL_API_RC SQL_API_FN                       /* Run Statistics                 */
  sqlgstat (
   unsigned short TableNameLen,             /* table name length              */
   unsigned short NumIndexes,               /* number of indices              */
   unsigned char StatsOption,               /* stats option                   */
   unsigned char ShareLevel,                /* share level                    */
   unsigned short * pIndexLens,             /* index lengths                  */
   struct sqlca * pSqlca,                   /* SQLCA                          */
   _SQLOLDCHAR ** ppIndexList,              /* index list                     */
   _SQLOLDCHAR * pTableName);               /* table name                     */

SQL_API_RC SQL_API_FN                       /* Dereference Address            */
  sqlgdref (
   unsigned int NumBytes,                   /* number of bytes to transfer    */
   char * pTargetBuffer,                    /* target area for transfer       */
   char ** ppSourceBuffer);                 /* source area for transfer       */

SQL_API_RC SQL_API_FN                       /* Copy Memory                    */
  sqlgmcpy (
   void * pTargetBuffer,                    /* area into which to move the    */
                                            /* data                           */
   const void * pSource,                    /* area from which to move the    */
                                            /* data                           */
   unsigned long NumBytes);                 /* number of bytes to move        */

SQL_API_RC SQL_API_FN                       /* Return address                 */
  sqlgaddr (
   char * pVariable,                        /* variable                       */
   char ** ppOutputAddress);                /* ptr to an area containing the  */
                                            /* address                        */

/* Configuration Utility Commands                                             */

SQL_API_RC SQL_API_FN                       /* Reset Database Manager         */
                                            /* Configuration                  */
  sqlfrsys (
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Reset Database Configuration   */
  sqlfrdb (
   _SQLOLDCHAR * pDbAlias,                  /* database alias                 */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Update Database Manager        */
                                            /* Configuration                  */
  sqlfusys (
   unsigned short NumItems,                 /* count of entries being         */
                                            /* modified                       */
   struct sqlfupd * pItemList,              /* list of items                  */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Update Database Configuration  */
  sqlfudb (
   _SQLOLDCHAR * pDbAlias,                  /* database alias                 */
   unsigned short NumItems,                 /* count of entries being         */
                                            /* modified                       */
   struct sqlfupd * pItemList,              /* list of items                  */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Get Database Manager           */
                                            /* Configuration                  */
  sqlfxsys (
   unsigned short NumItems,                 /* count of entries being         */
                                            /* returned                       */
   struct sqlfupd * pItemList,              /* list of items                  */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Get Database Configuration     */
  sqlfxdb (
   _SQLOLDCHAR * pDbAlias,                  /* database alias                 */
   unsigned short NumItems,                 /* count of entries being         */
                                            /* returned                       */
   struct sqlfupd * pItemList,              /* list of items                  */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Get Database Manager           */
                                            /* Configuration Defaults         */
  sqlfdsys (
   unsigned short NumItems,                 /* count of items being returned  */
   struct sqlfupd * pItemList,              /* list of items                  */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Get Database Configuration     */
                                            /* Defaults                       */
  sqlfddb (
   char * pDbAlias,                         /* database alias                 */
   unsigned short NumItems,                 /* count of entries to return     */
   struct sqlfupd * pItemList,              /* list of items                  */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Reset Database Manager         */
                                            /* Configuration                  */
  sqlgrsys (
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Update Database Manager        */
                                            /* Configuration                  */
  sqlgusys (
   unsigned short NumItems,                 /* count of entries being         */
                                            /* modified                       */
   unsigned short * pItemListLens,          /* list of item lengths           */
   struct sqlfupd * pItemList,              /* list of items                  */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Get Database Manager           */
                                            /* Configuration                  */
  sqlgxsys (
   unsigned short NumItems,                 /* count of entries being         */
                                            /* returned                       */
   struct sqlfupd * pItemList,              /* list of items                  */
   struct sqlca * pSqlca);                  /* SQLCA                          */

SQL_API_RC SQL_API_FN                            /* Single TableSpace Query   */
  sqlgstpq (
   struct sqlca * pSqlca,
   unsigned long TablespaceId,                   /* in: tableSpace id         */
   struct SQLB_TBSPQRY_DATA * pTablespaceData,   /* out: tableSpace data      */
   unsigned long reserved);                      /* in: SQLB_RESERVED1        */

SQL_API_RC SQL_API_FN                            /* Open TableSpace Query     */
  sqlgotsq (
   struct sqlca * pSqlca,
   unsigned long TablespaceQueryOptions,         /* in: processing options:   */
                                                 /* SQLB_TBS_OPEN_xxx         */
   unsigned long * pNumTablespaces);             /* out: # tablespaces        */
                                                 /* defined in db             */

SQL_API_RC SQL_API_FN                            /* Fetch TableSpace Query    */
  sqlgftpq (
   struct sqlca * pSqlca,
   unsigned long MaxTablespaces,                 /* size of output area       */
   struct SQLB_TBSPQRY_DATA * pTablespaceData,   /* out: array of length      */
                                                 /* maxTbs                    */
   unsigned long * pNumTablespaces);             /* out: #data entries        */
                                                 /* returned                  */

SQL_API_RC SQL_API_FN                            /* Close TableSpace Query    */
  sqlgctsq (
   struct sqlca * pSqlca);

SQL_API_RC SQL_API_FN                            /* TableSpace Query          */
  sqlgmtsq (
   struct sqlca * pSqlca,
   unsigned long * pNumTablespaces,              /* out: total number of      */
                                                 /* table spaces              */
   struct SQLB_TBSPQRY_DATA *** pppTablespaceData, /* out: mem returned to    */
                                                 /* application               */
   unsigned long reserved1,                      /* in: SQLB_RESERVED1        */
   unsigned long reserved2);                     /* in: SQLB_RESERVED2        */

SQL_API_RC SQL_API_FN                            /* Open Tablespace           */
                                                 /* Container Query           */
  sqlgotcq (
   struct sqlca * pSqlca,
   unsigned long TablespaceId,                   /* in: id tbs or SQLB_ALL    */
                                                 /* TABLESPACES               */
   unsigned long * pNumContainers);              /* out:  output...the        */
                                                 /* number of containers for  */
                                                 /* the table space           */

SQL_API_RC SQL_API_FN                            /* Fetch Tablespace          */
                                                 /* Container Query           */
  sqlgftcq (
   struct sqlca * pSqlca,
   unsigned long MaxContainers,                  /* in:  max # entries to     */
                                                 /* return in 'data'          */
   struct SQLB_TBSCONTQRY_DATA * pContainerData, /* out: array of 'maxCont'   */
                                                 /* entries                   */
   unsigned long * pNumContainers);              /* out: # data entries       */
                                                 /* returned on this query    */

SQL_API_RC SQL_API_FN                            /* Close Tablespace          */
                                                 /* Container Query           */
  sqlgctcq (
   struct sqlca * pSqlca);

SQL_API_RC SQL_API_FN                            /* Tablespace Container      */
                                                 /* Query                     */
  sqlgtcq (
   struct sqlca * pSqlca,
   unsigned long TablespaceId,                   /* in: id a tbs or SQLB_ALL  */
                                                 /* TABLESPACES               */
   unsigned long * pNumContainers,               /* out: # entries returned   */
   struct SQLB_TBSCONTQRY_DATA ** ppContainerData);

SQL_API_RC SQL_API_FN                            /* Set TableSpace            */
                                                 /* Containers                */
  sqlgstsc (
   struct sqlca * pSqlca,
   unsigned long SetContainerOptions,            /* in: processing options:   */
                                                 /* SQLB_SET_CONT_xxx         */
   unsigned long TablespaceId,                   /* in: table space which is  */
                                                 /* to be changed             */
   unsigned long NumContainers,                  /* in:#containers in the     */
                                                 /* list                      */
   struct SQLB_TBSCONTQRY_DATA * pContainerData); /* container                */
                                                 /* specifications            */

SQL_API_RC SQL_API_FN                            /* Get TableSpace            */
                                                 /* Statistics                */
  sqlggtss (
   struct sqlca * pSqlca,
   unsigned long TablespaceId,
   struct SQLB_TBS_STATS * pTablespaceStats);

SQL_API_RC SQL_API_FN                            /* Get Authorizations        */
  sqlgauth (
   struct sqlca * pSqlca);                       /* SQLCA                     */

SQL_API_RC SQL_API_FN                            /* Get table authorizations  */
  sqlgtbau (
   unsigned short,                               /* table name length         */
   _SQLOLDCHAR *,                                /* fully-qualified table     */
                                                 /* name                      */
   struct sqlca *);                              /* SQLCA                     */

/* SQL Return Codes in SQLCODE for UTILITY/CONFIGURATION Commands             */

#ifndef SQL_RC_OK
#define SQL_RC_OK               0   /* everything is ok                */
#endif
#ifndef SQL_RC_INVALID_SQLCA
#define SQL_RC_INVALID_SQLCA   -1   /* invalid sqlca                   */
#endif

/* ROLL FORWARD Return Codes - more in the 4900's                             */

#define SQLU_RC_NOLFH                  -1258   /* Log Control file not        */
                                               /* found.                      */
#define SQLU_RC_IOELFH                 -1259   /* I/O Error accessing LFH.    */
#define SQLU_RC_RFNOTEN                -1260   /* DB not enabled for Roll     */
                                               /* Fwd                         */
#define SQLU_RC_RFNOTP                 -1261   /* Roll Forward is not         */
                                               /* Pending                     */
#define SQLU_RC_BADPIT                 -1262   /* Bad Point in Time           */
                                               /* specified                   */
#define SQLU_RC_INVEXT                 -1263   /* Invalid Log Extent file     */
#define SQLU_RC_NOTEXT                 -1264   /* Log Extent file does not    */
                                               /* belong to DB                */
#define SQLU_RC_IVREXT                 -1265   /* Log extent file is          */
                                               /* incorrect version           */
#define SQLU_RC_PRTIME                 -1266   /* Time specified is before    */
                                               /* previous roll-forward time  */
#define SQLU_RC_UEXIT_ERR              -1268   /* User exit encountered an    */
                                               /* error (other than retry)    */
                                               /* while attempting to         */
                                               /* retrieve a log extent file  */
                                               /* for roll forward            */
#define SQLU_RC_RFINPRG                -1269   /* Rollforward by tablespace   */
                                               /* in progress.                */
#define SQLU_RC_RCVIOERR               1271    /* Roll forward complete but   */
                                               /* I/O errors encountered      */
#define SQLU_RC_RFSTOP                 -1272   /* Rollforward by tablespace   */
                                               /* has stopped.                */
#define SQLU_RC_MISSING_EXT            -1273   /* Missing log extent file.    */
#define SQLU_RC_INVTSP_STOPTIME        -1274   /* Invalid stop time for       */
                                               /* tablespace rollforward.     */
#define SQLU_INVRFR_STOPTIME           -1275   /* invalid stop time           */
                                               /* specified                   */
#define SQLU_INVRFR_STOP               -1276   /* invalid time to issue a     */
                                               /* stop                        */
#define SQLUD_INACCESSABLE_CONTAINER   1277    /* Restore found one or more   */
                                               /* containers are              */
                                               /* inaccessable                */
#define SQLU_RC_TBSROLLBK              1278    /* Roll forward complete but   */
                                               /* rollback required           */
#define SQL_RC_RECREATE_INDEXES        1279    /* Restart complete but not    */
                                               /* all invalid  indexes were   */
                                               /* recreated                   */
#define SQLU_INVRFR_TBSPITTIME         -1280   /* invalid stop time           */
                                               /* specified for tablespace    */
                                               /* rollforward                 */

#define SQLF_RC_INV_CLIENT_COMM        -1290   /* invalid client comm.        */
                                               /* protocols                   */
#define SQLF_RC_INV_DIR_FIELD          -1296   /* invalid directory services  */
                                               /* field                       */

#define SQLCC_RC_UNKNOWN_HOST          -1336   /* hostname in node dir        */
                                               /* unknown                     */
#define SQLCC_RC_UNKNOWN_SERVICE       -1337   /* service name in node        */
                                               /* directory is unknown        */
#define SQLCC_RC_UNKNOWN_SYM_DEST_NAME -1338   /* CPI-C symdestname is        */
                                               /* unknown                     */
#define SQLCC_RC_NNAME_NOTFOUND        -1341   /* wrkstn name (nname)         */
#define SQLCC_RC_NO_SOCKS_ENV_VAR      -1460   /* SOCKS env vars not found    */
#define SQLCC_RC_SOCKADDR_IN_USE       -5040   /* socket address in use       */
#define SQLCC_RC_COMM_SUPPORT_FAILED   -5042   /* general failure in          */
                                               /* servercommunications        */
                                               /* support                     */

#define SQLF_RC_INV_DISCOVER_TYPE      -1480   /* invalid discover type       */
#define SQLF_RC_INV_DISCOVER_COMM      -1481   /* invalid discover comm       */

#define SQLF_WARNING_BUFFPAGE          1482    /* buffpage may be ignored     */

/* GENERAL UTILITY Return Codes                                               */

#define SQLU_BAD_DRIVE                 -2000   /* Invalid output drive        */
#define SQLU_USER_TERM                 -2001   /* Backup terminated by user   */
#define SQLU_NOT_LOCAL                 -2002   /* database not local          */
#define SQLU_DOS_ERROR                 -2003   /* base op system error        */
#define SQLU_SQL_ERROR                 -2004   /* SQL error occurred          */
#define SQLU_READ_ERROR                -2005   /* read wrong # of bytes       */
#define SQLU_INVALID_ACTION            -2008   /* call out of sequence        */
#define SQLU_INSUFF_MEMORY             -2009   /* insufficient memory         */
#define SQLU_STRD_ERROR                -2010   /* error in Start Using        */
#define SQLU_STPD_ERROR                -2011   /* error in Stop Using         */
#define SQLU_DIR_ERROR                 -2013   /* directory Scan error        */
#define SQLU_INVALID_DBNAME            -2015   /* invalid database name       */
#define SQLU_INVALID_PATH              -2016   /* invalid path in             */
                                               /* environment                 */
#define SQLU_START_SESSION             -2017   /* Start Session failed        */
#define SQLU_INVALID_AUTHS             -2018   /* invalid authorizations      */
#define SQLU_AUTOBIND                  -2019   /* auto-binding failed         */
#define SQLU_TIMESTAMP                 -2020   /* conflict after auto-bind    */
                                               /* control file                */
#define SQLU_IO_ERROR_LFH              -2023   /* I/O error in accessing the  */
                                               /* log                         */
#define SQLU_IO_ERROR_BRG              -2024   /* I/O error in accessing the  */
                                               /* Backup/Restore flag file    */
#define SQLU_IO_ERROR                  -2025   /* System I/O error occurred   */
#define SQLU_PAUSE_ERROR               -2026   /* error in PAUSE the started  */
                                               /* DB                          */
#define SQLU_CONT_ERROR                -2027   /* error in CONTINUE the       */
                                               /* stoped DB                   */
#define SQLU_INT_INST_ERR              -2028   /* interruption installing     */
                                               /* error                       */
#define SQLU_UEXIT_RC                  -2029   /* user exit returned non      */
                                               /* zero rc                     */

#define SQLU_FIRST_TAPE_WARNING        2031    /* warning to mount tape       */
#define SQLU_INVALID_PARM              -2032   /* parameter to utility        */
                                               /* incorrect                   */
#define SQLU_ADSM_ERROR                -2033   /* ADSM reported error         */
#define SQLU_INVALID_PARM_ADDRESS      -2034   /* address of parameter        */
                                               /* incorrect                   */
#define SQLU_NOINT_ERROR               -2035   /* error during nointerrupt    */
                                               /* action                      */
#define SQLU_PATH_ERROR                -2036   /* directory does not exist    */
#define SQLU_LOAD_ADSM_ERROR           -2037   /* unable to load ADSM         */
#define SQLU_DBSYSTEM_ERROR            -2038   /* database system error       */
#define SQLU_NO_APP_ERROR              -2039   /* application terminated      */
#define SQLU_ALIAS_ERROR               -2040   /* alias parameter error       */
#define SQLU_BUFFSIZE_ERROR            -2041   /* buff_size parameter error   */
#define SQLU_IO_WARNING                2042    /* I/O error during change     */
                                               /* tape                        */
#define SQLU_SPAWN_EDU_ERROR           -2043   /* Spawn child process error   */
#define SQLU_QUEUE_ERROR               -2044   /* Message queue error         */
#define SQLU_OBJECT_ACCESS_ERROR       -2048   /* Object access error         */
#define SQLU_CORRUPT_IMAGE_ERROR       -2054   /* Bad backup image            */
#define SQLU_MEMORY_ACCESS_ERROR       -2055   /* Unable to access memory     */
                                               /* set                         */
#define SQLU_UNKNOWN_MEDIA_TYPE        -2056   /* device path point to        */
                                               /* unknown device type         */
#define SQLU_MEDIA_CANNOT_BE_SHARED    -2057   /* device or file already      */
                                               /* opened by other process     */
#define SQLU_END_OF_MEDIA_WARNING      2058    /* End of tape or file         */
                                               /* encountered during read     */
#define SQLU_DEVICE_FULL_WARNING       2059    /* Device is full during       */
                                               /* write                       */
#define SQLU_MEDIA_EMPTY_WARNING       2060    /* Empty device or file not    */
                                               /* found during read           */
#define SQLU_MEDIA_ACCESS_DENIED       -2061   /* Access denied due to        */
                                               /* authority level             */
#define SQLU_MEDIA_ACCESS_ERROR        -2062   /* Access error                */
#define SQLU_TERM_LAST_MEDIA_WARNING   2065    /* Terminate last Media IO.    */
#define SQLU_BAD_TABLESPACE_NAME       -2066   /* Invalid tablespace name     */
#define SQLU_NO_MEDIA_HEADER           -2068   /* Could not locate media      */
                                               /* header in backup or copy    */
                                               /* image                       */
#define SQLU_INCORRECT_DBALIAS         -2069   /* Mismatch alias name from    */
                                               /* media                       */
#define SQLU_INCORRECT_TIMESTAMP       -2070   /* Mismatch timestamp read     */
                                               /* from media                  */

#define SQLU_SHR_LIB_ACCESS_ERROR      -2071   /* Shared library access       */
                                               /* error                       */
#define SQLU_BIND_SHR_LIB_ERROR        -2072   /* Bind shared library error   */

#define SQLUD_TSP_RESTORE_OUT_OF_SEQ   -2154   /* Out of sequence tablespace  */
                                               /* restore                     */

/* HISTORY TABLE Return Codes                                                 */
#define SQLUH_SCAN_UPDATED_WARNING     2155    /* Changes were made to        */
                                               /* historyfile during update.  */
#define SQLUH_MAX_SCANS_EXCEEDED       -2157   /* MAX # open scans exceeded   */
#define SQLUH_FILE_REPLACED_WARNING    2160    /* History file fixed          */
#define SQLUH_DAMAGED_FILE             -2161   /* History file is unfixable   */
#define SQLUH_SQLUHINFO_VARS_WARNING   2165    /* number of tablespaces       */
                                               /* changed                     */
#define SQLUH_DUPLICATE_ENTRY          -2170   /* Duplicate timestamp found   */
#define SQLUH_ENTRY_NOT_FOUND          -2171   /* Entry not found on update   */
#define SQLU_ACCESS_HIST_WARNING       2172    /* Access history file         */
                                               /* warning                     */

/* REORGANIZE TABLE Return Codes                                              */
#define SQLUR_INVALID_AUTHID           -2200   /* invalid authid on index     */
                                               /* name                        */
#define SQLUR_INVALID_TABLENAME        -2203   /* invalid tablename syntax    */
#define SQLUR_INVALID_INDEXNAME        -2204   /* invalid tablename syntax    */
#define SQLUR_INDEX_NOT_FOUND          -2205   /* index doesn't exist         */
#define SQLUR_INVALID_FILEPATH         -2207   /* invalid filepath pointer    */
#define SQLUR_INVALID_TABLESPACE       -2208   /* invalid tablespace pointer  */
#define SQLUR_TABLE_NOT_FOUND          -2211   /* table does not exist        */
#define SQLUR_VIEW_ERROR               -2212   /* cannot reorg a view         */
#define SQLUR_INCORRECT_TABLESPACE     -2213   /* Incorrect tablespace type   */
#define SQLUR_INSAUTH                  -2214   /* insuffic authority          */
#define SQLUR_SQLERR_COMPREV           -2215   /* SQL error commiting prev    */
                                               /* work                        */
#define SQLUR_SQLERR_REORG             -2216   /* SQL error during            */
                                               /* reorganization              */

/* RUN STATISTICS Return Codes                                                */
#define SQLUS_INVALID_AUTHID           -2300   /* invalid authid              */
#define SQLUS_INVALID_TABLE_NAME       -2301   /* invalid table name          */
#define SQLUS_INVALID_INDEX_LIST       -2302   /* invalid index pointer       */
#define SQLUS_INVALID_STATS_OPT        -2303   /* statsopt parameter invalid  */
#define SQLUS_INVALID_SHARE_LEV        -2304   /* sharelev parameter invalid  */
#define SQLUS_VIEWS_NOT_ALLOWED        -2305   /* table specified is a view   */
#define SQLUS_OBJ_DOES_NOT_EXIST       -2306   /* object doesn't exist        */
#define SQLUS_SYS_TABLE_NOT_ALLOWED    -2307   /* system table not allowed    */
#define SQLUS_INVALID_INDEX_AUTHID     -2308   /* index authid invalid        */
#define SQLUS_INVALID_INDEX_NAME       -2309   /* index name invalid          */
#define SQLUS_ERROR_STAT               -2310   /* error running statistics    */
#define SQLUS_INSAUTH                  -2311   /* insuffic authority for      */
                                               /* runstats                    */
#define SQLUS_STATS_HEAP_TOO_SMALL     -2312   /* statistics heap is too      */
                                               /* small                       */
#define SQLUS_PARTIAL_SUCCESS          2313    /* incomplete statistics       */
                                               /* collected                   */

#define SQLUD_RST_NOROLLFWD            3       /* Rst DB turn off roll fwd    */
                                               /* pend, old OS/2 API only     */
/* Old OS/2 Backup calling action values                                      */
#define SQLU_BACK_ALL                  0x0     /* backup entire database      */
#define SQLU_BACK_CHANGES              0x1     /* backup changes only         */
#define SQLU_BACK_QUIESCE              0x800   /* quiesce during backup       */
#define SQLU_NEW_UOW_RETURN_ERROR      0x400   /* New UOW return error immed  */

#define SQLU_DBM_ERROR                 -2014   /* pause or Continue or        */
                                               /* migration error             */
#define SQLU_WRONG_DISKETTE            -2021   /* Wrong diskette inserted     */
#define SQLU_DISK_FULL                 -2030   /* a specific fixed disk is    */
                                               /* full                        */

#define SQLUB_BAD_TYPE                 -2400   /* invalid type                */
#define SQLUB_TYPE_MUSTBE_DB           -2401   /* type must be database       */
#define SQLUB_USER_NOT_AUTH            -2403   /* insufficient auth for       */
                                               /* backup                      */
#define SQLUB_MEDIA_FULL               -2404   /* The target disk/diskette    */
                                               /* is full                     */
#define SQLUB_BR_INPROG                -2407   /* The Backup can't run        */
                                               /* because B/R flag file       */
                                               /* existed and read I/O error  */
                                               /* occurred                    */
#define SQLUB_DEL_BRG_ERR              2408    /* Backup process is           */
                                               /* successful, but unable to   */
                                               /* delete BRG file             */
#define SQLUB_WRONG_BASE_IMAGE         -2409   /* 'change-only' is only       */
                                               /* applied to the most recent  */
                                               /* base image                  */
#define SQLUB_NO_CHG_NSD               -2410   /* change only, backup not     */
                                               /* allowed to user exit        */
#define SQLUB_IO_ERROR                 -2411   /* I/O error during backup     */
#define SQLUD_BIND_WARNING             2507    /* Restore utility not bound   */
#define SQLUD_DROP_ERROR               -2511   /* error dropping database     */

/* BACKUP Return Codes                                                        */
#define SQLUB_RST_IN_PROG              -2405   /* The backup can't run        */
                                               /* because the Restore is in   */
                                               /* progress                    */
#define SQLUB_ROLLFWD_PENDING          -2406   /* The Backup can't run        */
                                               /* because roll forward is     */
                                               /* pending                     */
#define SQLUB_CORRUPT_PAGE             -2412   /* data page encountered       */
                                               /* during backup is corrupted  */
#define SQLUB_LOGRETAIN_ONLINE_ERROR   -2413   /* retain req'd for online     */
                                               /* backup                      */
#define SQLUB_INSUF_SPACE_WARNING      2414    /* no space for control info   */
#define SQLUB_NEXT_TAPE_WARNING        2416    /* tape full, mount another    */
#define SQLUB_DBASE_DOES_NOT_EXIST     -2418   /* database does not exist     */
#define SQLUB_DISK_FULL_ERROR          -2419   /* disk full during backup     */

#define SQLUB_FIRST_TAPE_ERROR         -2420   /* first tape cannot hold      */
                                               /* header                      */
#define SQLUB_LOGRETAIN_TBS_ERROR      -2421   /* retain req'd for tbs        */
                                               /* backup                      */
#define SQLUB_DB_UNSUPPORTED_BY_API    -2422   /* the backup API used does    */
                                               /* not support this format of  */
                                               /* database                    */
#define SQLUB_MISSING_INDEX            -2423   /* A required index is         */
                                               /* missing during an offline   */
                                               /* backup                      */

/* RESTORE Return Codes                                                       */
#define SQLUD_CANNOT_RESTORE           -2501   /* can't read restored         */
                                               /* database                    */
#define SQLUD_DISKETTE_ERROR           -2502   /* error reading backup        */
                                               /* diskette                    */
#define SQLUD_WRONG_DATABASE           -2503   /* wrong backup diskette       */
#define SQLUD_DISKETTE_PROMPT          2504    /* prompt for backup diskette  */
#define SQLUD_DROP_WARNING             2505    /* warn that drop will be      */
                                               /* done                        */
#define SQLUD_DATABASE_WARNING         2506    /* Restore worked, but not     */
                                               /* cleanup                     */
#define SQLUD_INVALID_TIMESTAMP        -2508   /* timestamp incorrectly       */
                                               /* specified                   */
#define SQLUD_INVALID_DBDRV            -2509   /* invalid database drive      */
#define SQLUD_SEM_ERROR                -2510   /* semaphore error             */
#define SQLUD_CREATE_ERROR             -2512   /* error creating database     */
#define SQLUD_REN_ERROR                -2513   /* error renaming database     */
#define SQLUD_BAD_VERSION              -2514   /* restored database wrong     */
                                               /* version                     */
#define SQLUD_INSAUTH                  -2515   /* insuffic authority to       */
                                               /* restore                     */
#define SQLUD_DBACT                    -2516   /* a database active           */
#define SQLUD_MIGRATED                 2517    /* database migrated           */
#define SQLUD_RST_DBCONG_ERR           -2518   /* error in restoring DB       */
                                               /* config.                     */
#define SQLUD_MIGRATE_ERROR            -2519   /* error in migrating the      */
                                               /* database                    */
#define SQLUD_DBCON_WARN               2520    /* DBCON file is restored      */
                                               /* using the backup version    */
#define SQLUD_DEL_BRG_ERR              2521    /* Restore process is          */
                                               /* successful, but unable to   */
                                               /* delete BRG file             */
#define SQLUD_TOO_MANY_BACKUP_FILES    -2522   /* more than one file match    */
#define SQLUD_MEDIA_CORRUPT            -2530   /* corrupted backup image      */
#define SQLUD_WRGIMAGE_ERROR           -2532   /* image of wrong database     */
#define SQLUD_WRGIMAGE_WARNING         2533    /* image of wrong database     */
#define SQLUD_WRONGSEQ_WARNING         2536    /* seq number of backup        */
                                               /* incorrect                   */
#define SQLUD_MUST_ROLLFWD             -2537   /* roll forward required       */
#define SQLUD_UNEXPECT_EOF_ERROR       -2538   /* end of file reached         */
                                               /* unexpectedly                */
#define SQLUD_NOINT_WARNING            2540    /* noint type restore had      */
                                               /* warning                     */
#define SQLUD_CLOSE_MEDIA_WARNING      2541    /* unable to close backup      */
                                               /* file                        */
#define SQLUD_NO_BACKUP_FILE_MATCH     -2542   /* no backup file match found  */
#define SQLUD_DB_DIR_ERROR             -2543   /* invalid directory for new   */
                                               /* dbase                       */
#define SQLUD_DISK_FULL_ERROR          -2544   /* disk full during restore    */
#define SQLUD_NOT_FIRST_IMAGE          -2546   /* restore requires first      */
                                               /* image first                 */
#define SQLUD_OLD_ONLINE_IMAGE_ERROR   -2547   /* cannot restore online       */
                                               /* backup from a previous      */
                                               /* release                     */
#define SQLUD_IMAGE_DB_CP_MISMATCH     -2548   /* backup has diff codepage    */
                                               /* from disk DB                */
#define SQLUD_ALL_TBLSPACES_SKIPPED    -2549   /* all tablespaces skipped     */
                                               /* during restore              */
#define SQLUD_WRONG_NODE               -2550   /* backup from a different     */
                                               /* node                        */
#define SQLUD_WRONG_CAT_NODE           -2551   /* backup of a database with   */
                                               /* a different catalog node    */

/******************************************************************************
**  the meaning of the following 8 warnings :
**        A -> database alias
**        N -> database name
**        S -> database seed
**        0 -> target db value DOES NOT matches backup image value
**        1 -> target db value matches backup image value
** 
*******************************************************************************/
#define SQLUD_A0N0S0_WARNING           2529
#define SQLUD_A0N0S1_WARNING           2528
#define SQLUD_A0N1S0_WARNING           2525
#define SQLUD_A0N1S1_WARNING           2524
#define SQLUD_A1N0S0_WARNING           2527
#define SQLUD_A1N0S1_WARNING           2526
#define SQLUD_A1N1S0_WARNING           2523
#define SQLUD_A1N1S1_WARNING           2539
#define SQLUD_TBLSP_TO_OTHER_DB        -2560   /* restore tablespace to a     */
                                               /* non original database.      */
#define SQLUD_TBLSP_TO_NEW_DB          2561    /* restore tablespace to a     */
                                               /* new data base.              */
#define SQLUD_TBLSP_FR_FULL_BKUP       -2562   /* restore tablespace from     */
                                               /* full backup image.          */
#define SQLUD_NOTALL_TBS_RESTORED      2563    /* Not all tablespases were    */
                                               /* restored                    */
#define SQLUD_DB_MISMATCH              2565    /* Mismatch between restore    */
                                               /* image and database          */
                                               /* restored to                 */
#define SQLU_HEADER_WRITE_ERR          2045    /* Problem on first media      */
                                               /* write                       */

/* sqlgadau and sqluadau Return codes                                         */
#define SQLUA_BAD_INPUT_PARAMETER      -2600   /* sql_authorizations parm is  */
                                               /* bad                         */

/* Asynchronous Read Log SQLCODES                                             */
#define SQLU_RLOG_INVALID_PARM         -2650   /* invalid parameter(s)        */
                                               /* detected                    */
#define SQLU_RLOG_DB_NOT_READABLE      -2651   /* database has circular logs  */
#define SQLU_RLOG_INSUFF_MEMORY        -2652   /* insufficient memory for     */
                                               /* internal buffer             */
#define SQLU_RLOG_LSNS_REUSED           2653   /* log sequence numbers        */
                                               /* reused                      */
#define SQLU_RLOG_READ_TO_CURRENT       2654   /* read to end of database     */
                                               /* log                         */
#define SQLU_RLOG_EXTDB_INCORRECT      -2655   /* log extent not for this     */
                                               /* database                    */
#define SQLU_RLOG_INVALID_EXTENT       -2656   /* invalid extent encountered  */
#define SQLU_RLOG_EXTENT_REQUIRED      -2657   /* log reader requires an      */
                                               /* extent not in the log path  */

/* DB2SPLIT Return codes                                                      */
#define SQLUSP_CMD_LINE_OPT_ERR        -2701   /* invalid command line        */
                                               /* options                     */
#define SQLUSP_OPEN_CFG_FILE_ERR       -2702   /* fail to open config file    */
#define SQLUSP_OPEN_LOG_FILE_ERR       -2703   /* fail to open log file       */
#define SQLUSP_OPEN_IN_DATA_FILE_ERR   -2704   /* fail to open input data     */
                                               /* file                        */
#define SQLUSP_OPEN_INPUT_MAP_FILE_ERR -2705   /* fail to open input          */
                                               /* partition map file          */
#define SQLUSP_OPEN_OUTMAP_FILE_ERR    -2706   /* fail to open output         */
                                               /* partition map file          */
#define SQLUSP_OPEN_DIST_FILE_ERR      -2707   /* fail to open distribution   */
                                               /* file                        */
#define SQLUSP_OPEN_OUTDATA_FILE_ERR   -2708   /* fail to open output data    */
                                               /* file                        */
#define SQLUSP_CFG_SYNTAX_ERR          -2709   /* syntax error in config      */
                                               /* file                        */
#define SQLUSP_INVALID_CFG_KEYWORD     -2710   /* invalid keyword in config   */
                                               /* file                        */
#define SQLUSP_INVALID_COL_DELIMITER   -2711   /* column delimiter can't be   */
                                               /* a blank                     */
#define SQLUSP_INVALID_STR_DELIMITER   -2712   /* string delimiter can't be   */
                                               /* a period                    */
#define SQLUSP_INVALID_RUNTYPE         -2713   /* invalid run type in config  */
                                               /* file                        */
#define SQLUSP_INVALID_MSG_LEVEL       -2714   /* invalid Message Level in    */
                                               /* config file                 */
#define SQLUSP_INVALID_CHK_LEVEL       -2715   /* invalid Check Level in      */
                                               /* config file                 */
#define SQLUSP_INVALID_REC_LEN         -2716   /* record length out of range  */
#define SQLUSP_INVALID_NODE            -2717   /* invalid node specification  */
#define SQLUSP_INVALID_OUTPUTNODE      -2718   /* invalid output node         */
                                               /* specification               */
#define SQLUSP_INVALID_OUTPUTTYPE      -2719   /* invalid output type         */
#define SQLUSP_TOO_MANY_PTITN_KEYS     -2720   /* too many partitioning keys  */
#define SQLUSP_INVALID_PTITN_KEYS      -2721   /* invalid partition key       */
                                               /* specification               */
#define SQLUSP_INVALID_LOG_FILE        -2722   /* invalid log file            */
                                               /* specification               */
#define SQLUSP_INVALID_TRACE           -2723   /* invalid trace               */
                                               /* specification               */
#define SQLUSP_NODE_ERR                -2724   /* specify one and only one:   */
                                               /* MAPFILI or NODE             */
#define SQLUSP_NO_OUTMAP               -2725   /* Output partition map is     */
                                               /* needed                      */
#define SQLUSP_NO_PTITN_KEY            -2726   /* no partitioning key         */
                                               /* defined                     */
#define SQLUSP_KEY_OUT_RANGE           -2727   /* key exceeds record length   */
#define SQLUSP_NODE_NOT_EXISTED        -2728   /* output node list is not a   */
                                               /* subset of node list         */
#define SQLUSP_INPUT_MAP_ERR           -2729   /* invalid data entry in       */
                                               /* input map                   */
#define SQLUSP_WRITE_HEAD_ERR          -2730   /* error writing header of     */
                                               /* out data file               */
#define SQLUSP_DATA_READ_ERR           -2731   /* error processing input      */
                                               /* data file                   */
#define SQLUSP_DATA_BIN_ERR            -2732   /* binary data if VMMVS        */
#define SQLUSP_NO_RUNTYPE              -2733   /* run type not specified      */
#define SQLUSP_32KLIMIT_DEF_ERR        -2734   /* 32kLimit definition error   */
#define SQLUSP_DISCARD_REC_WARN        2735    /* discard empty record        */
#define SQLUSP_GRPI_ERR                -2736   /* error from sqlugrpi or      */
                                               /* sqlugrpn                    */
#define SQLUSP_DATA_WRITE_ERR          -2737   /* error writing data file     */
#define SQLUSP_DATA_WRITE_WARN         2738    /* data is truncated in        */
                                               /* writing                     */
#define SQLUSP_BIN_NO_RECLEN           -2739   /* reclen must be defined for  */
                                               /* BIN                         */
#define SQLUSP_FLOAT_NOT_ALLOWED       -2740   /* FLOAT is not supported for  */
                                               /* DEL/ASC                     */
#define SQLUSP_FILETYPE_DEF_ERR        -2741   /* invalid file type           */
#define SQLUSP_DECIMAL_LEN_NOT_MATCH   -2742   /* decimal len not match its   */
                                               /* precision                   */
#define SQLUSP_DATA_LEN_NOT_MATCH      -2743   /* len not match for binary    */
                                               /* type data                   */
#define SQLUSP_ILLEGAL_FILENAME        -2744   /* illegal filename in cfg     */
                                               /* file                        */
#define SQLUSP_NEWLINE_DEF_ERR         -2745   /* Invalid NEWLINE flag in     */
                                               /* cfg file                    */
#define SQLUSP_INCOMPLETE_RECORD       -2746   /* Incomplete record in input  */
                                               /* data file                   */
#define SQLUSP_RECORD_TOO_LONG         -2747   /* ASC record must be no       */
                                               /* longer than 32K             */
#define SQLUSP_RECORD_TOO_SHORT        -2748   /* ASC record not long enough  */
#define SQLUSP_KEY_NOT_IN_32K          -2749   /* partition key not in the    */
                                               /* first 32k bytes of the      */
                                               /* record.                     */
#define SQLUSP_CFG_LINE_TOO_LONG       -2750   /* line too long in cfg file   */
#define SQLUSP_REC_LEN_ERR             -2751   /* expected reclen not         */
                                               /* matching actual reclen      */
#define SQLUSP_INVALID_CODEPAGE        -2752   /* invalid codepage            */
                                               /* specification               */
#define SQLUSP_APP_CODEPAGE_ERR        -2753   /* failed to get application   */
                                               /* CP                          */
#define SQLUSP_CODEPAGE_NOTABLE        -2754   /* codepages not convertable   */
#define SQLUSP_DELIMITER_ERROR         -2755   /* codepage-related delimiter  */
                                               /* error                       */
#define SQLUSP_CP_DATA_TO_DB           -2756   /* error converting data to    */
                                               /* DB CP                       */
#define SQLUSP_EBCDIC_NO_BIN           -2757   /* binary numerics not         */
                                               /* allowed in EBCDIC data      */

/* DB2GPMAP Return Codes                                                      */
#define SQLUGPMAP_TBL_AND_NDGRP        -2761   /* Specify only tbl or         */
                                               /* nodegrp                     */
#define SQLUGPMAP_NO_INST_PATH         -2762   /* fail to find DB install     */
                                               /* path                        */
#define SQLUGPMAP_TBL_NOT_FOUND        -2763   /* tbl not found               */
#define SQLUGPMAP_NODEGRP_NOT_FOUND    -2764   /* nodegrp not found           */
#define SQLUGPMAP_OPEN_OUTMAPFILE_WARN 2765    /* fail to open file           */
#define SQLUGPMAP_PTITN_MAP_ERR        -2766   /* incorrect ptitn map size    */
#define SQLUGPMAP_INVALID_CMD_OPT      -2767   /* invalid cmd line option     */

/* IMPORT/EXPORT Return codes                                                 */
#define SQLUE_DFO                      -3001   /* error opening output file   */
#define SQLUE_IOE                      -3002   /* i/o error writing output    */
                                               /* file                        */
#define SQLUE_CLS                      -3003   /* i/o error closing output    */
                                               /* file                        */
#define SQLUE_IFT                      -3004   /* invalid filetype parameter  */
#define SQLUE_CBI                      -3005   /* function interrupted        */
#define SQLUE_MFO                      -3006   /* i/o error opening message   */
                                               /* file                        */
#define SQLUE_MFW                      -3007   /* i/o error writing message   */
                                               /* file                        */
#define SQLUE_STA                      -3008   /* start using database        */
                                               /* failed                      */
#define SQLUE_STR                      -3009   /* invalid tcolstrg            */
#define SQLUE_COL                      -3010   /* invalid dcoldata            */

#define SQLUE_MEM                      -3011   /* memory allocation error     */
#define SQLUE_SYSERR                   -3012   /* system error                */
#define SQLUE_FTMOD                    -3013   /* invalid filetmod            */
#define SQLUE_MFC                      -3014   /* failure on closing message  */
                                               /* file                        */
#define SQLUE_SQLERR                   -3015   /* SQL error occurred          */
#define SQLUE_FMODNK                   -3016   /* no keywords found           */
#define SQLUE_FMODID                   -3017   /* invalid delimiter or        */
                                               /* duplicate                   */
#define SQLUE_FMODDEC                  -3018   /* decimal used for char       */
                                               /* delimiter                   */
#define SQLUE_NTS                      -3019   /* no tcolstrg                 */
#define SQLUE_RC_INSAUTH               -3020   /* insufficient authority for  */
                                               /* exp.                        */

#define SQLUI_RC_INSAUTH               -3021   /* insufficient authority for  */
                                               /* imp.                        */
#define SQLUE_SQL_PREP_ERR             -3022   /* SQL error on input string   */
#define SQLUE_DATABASE                 -3023   /* invalid database name       */
#define SQLUE_DATAFILE                 -3025   /* invalid datafile            */
#define SQLUE_MSGFILE                  -3026   /* invalid msgfile             */
#define SQLUE_DCOLMETH                 -3028   /* Export method indicator     */
                                               /* not n/d                     */
#define SQLUE_NUL_FTYPE                -3029   /* filetype is null            */

#define SQLUI_DFO                      -3030   /* error opening input data    */
                                               /* file                        */
#define SQLUI_IOE                      -3031   /* i/o error reading input     */
                                               /* file                        */
#define SQLUI_DCOLMETH                 -3032   /* Import method not n/d/p     */
#define SQLUI_TINSERT                  -3033   /* invalid insert in tcolstrg  */
#define SQLUI_TINTO                    -3034   /* invalid into in tcolstrg    */
#define SQLUI_TABLENAME                -3035   /* invalid tablename in        */
                                               /* tcolstrg                    */
#define SQLUI_CPAREN                   -3036   /* close paren not in          */
                                               /* tcolstrg                    */
#define SQLUE_SQL_PREP_INSERT          -3037   /* SQL error on insert string  */
#define SQLUI_TCOLJUNK                 -3038   /* tcolstrg invalid            */
#define SQLU_REDUCE_CPUPAR             3039    /* load parallelism reduced    */
#define SQLUE_LOBFILE_ERROR            -3040   /* lob file error              */

#define SQLUIC_BAD_DCOL_POS            -3045   /* invalid dcol position for   */
                                               /* CSV                         */
#define SQLUI_NONDEF_DCOL_NOCOLS       -3046   /* non-default dcol and no     */
                                               /* cols                        */
#define SQLUI_BAD_DCOL_METH            -3047   /* dcolinfo has invalid        */
                                               /* method                      */
#define SQLUI_NODCOL_FOR_NONNULL_DBCOL -3048   /* non nullable column         */
#define SQLUIC_UNSUPTYP_NONULLS        -3049   /* unsupported column type     */

#define SQLUII_CONVERSION              3050    /* conversion for cdpg         */
#define SQLUE_ROWCT_TOOBIG             -3053   /* too many rows for WSF       */
                                               /* export                      */
#define SQLUII_HEOF                    -3054   /* eof reading first rec in    */
                                               /* IXF                         */
#define SQLUII_HLEN_CONV               -3055   /* length of 'H' rec not       */
                                               /* numeric                     */
#define SQLUII_HLEN_SHORT              -3056   /* first record too short      */
#define SQLUII_HTYP                    -3057   /* first IXF rec is not 'H'    */
#define SQLUII_HID                     -3058   /* no IXF identifier in 'H'    */
#define SQLUII_HVERS                   -3059   /* invalid version field in    */
                                               /* 'H'                         */

#define SQLUII_HCNT                    -3060   /* HCNT in 'H' not numeric     */
#define SQLUII_HSBCP_BAD               -3061   /* SBCP in 'H' not numeric     */
#define SQLUII_HDBCP_BAD               -3062   /* DBCP in 'H' not numeric     */
#define SQLUII_HSBCP_CMP               -3063   /* 'H' SBCP not compat w/data  */
                                               /* SBCP                        */
#define SQLUII_HDBCP_CMP               -3064   /* 'H' DBCP not compat w/data  */
                                               /* DBCP                        */
#define SQLUII_DB_CODEPG               -3065   /* can't get codepages         */
#define SQLUII_TEOF                    -3066   /* eof reading/looking for     */
                                               /* 'T' rec                     */
#define SQLUII_TLEN_CONV               -3067   /* length of 'T' rec not       */
                                               /* numeric                     */
#define SQLUII_TLEN_SHORT              -3068   /* 'T' record is too short     */
#define SQLUII_TTYP                    -3069   /* first non-'A' rec not 'T'   */
                                               /* rec                         */

#define SQLUII_ALEN_BAD                -3070   /* invalid rec length of 'A'   */
                                               /* rec                         */
#define SQLUII_TCONV                   -3071   /* invalid data convention in  */
                                               /* 'T'                         */
#define SQLUII_TFORM                   -3072   /* invalid data format in 'T'  */
#define SQLUII_TMFRM                   -3073   /* invalid machine form in     */
                                               /* 'T'                         */
#define SQLUII_TLOC                    -3074   /* invalid data location in    */
                                               /* 'T'                         */
#define SQLUII_TCCNT                   -3075   /* 'C' rec cnt in 'T' not      */
                                               /* numeric                     */
#define SQLUII_TNAML                   -3076   /* name len fld in 'T' not     */
                                               /* numeric                     */
#define SQLUII_CCNT_HIGH               -3077   /* too many 'C' records        */
#define SQLUII_ALEN_CONV               -3078   /* length of 'A' rec not       */
                                               /* numeric                     */
#define SQLUII_CLEN_CONV               -3079   /* length of 'C' rec not       */
                                               /* numeric                     */

#define SQLUII_CLEN_SHORT              -3080   /* 'C' record is too short     */
#define SQLUII_CTYP                    -3081   /* wrong rec type / 'C'        */
                                               /* expected                    */
#define SQLUII_CEOF                    -3082   /* EOF while processing 'C'    */
                                               /* recs                        */
#define SQLUII_CDRID                   -3083   /* 'D' rec id field not        */
                                               /* numeric                     */
#define SQLUII_CPOSN                   -3084   /* 'D' rec posn field not      */
                                               /* numeric                     */
#define SQLUII_CIDPOS                  -3085   /* 'D' id/position not         */
                                               /* consistent                  */
#define SQLUII_NOCREC_FOR_NONNULL_DBCOL -3086  /* IXF column does not exist   */
#define SQLUII_INVCREC_NONNULL_DBCOL   -3087   /* IXF column not valid        */
#define SQLUII_CRECCOMP_NONNULL_DBCOL  -3088   /* IXF column not compatible   */
#define SQLUII_DTYP                    -3089   /* wrong rec type / 'D'        */
                                               /* expected                    */

#define SQLUII_DLEN_CONV               -3090   /* length of 'D' rec not       */
                                               /* numeric                     */
#define SQLUII_DLEN_RANGE              -3091   /* length of 'D' rec not       */
                                               /* valid                       */
#define SQLUII_DID                     -3092   /* invalid id field in 'D'     */
                                               /* rec                         */
#define SQLUIW_IFILE_INV               -3093   /* import file not valid WSF   */
#define SQLUIW_NNCOL_LOST              -3094   /* DOS non-nullable name not   */
                                               /* found                       */
#define SQLUIW_PCOL_INV                -3095   /* col position out of range   */
#define SQLUIW_UCOLTYP_NONUL           -3096   /* unsup col type - not        */
                                               /* nullable                    */
#define SQLUIW_RECLEN_INV              -3097   /* record length invalid       */
#define SQLUIW_INROW_INV               -3098   /* row number out of range     */
#define SQLUIW_INCOL_INV               -3099   /* col number out of range     */

#define SQLUE_COL_TOOBIG               3100    /* column longer than 254      */
                                               /* chars                       */
#define SQLUE_DATA_CHARDEL             3101    /* column has char delimiter   */
#define SQLUE_DCNUM_HIGH               3102    /* dcol column nbr > tcol      */
                                               /* number                      */
#define SQLUE_DCNUM_LOW                3103    /* dcol column nbr < tcol      */
                                               /* number                      */
#define SQLUE_WARNING                  3107    /* warning message issued      */

#define SQLUI_FEWER_DCOLS_DBCOLS_NULLED 3112   /* extra database cols         */
#define SQLUIC_UNSUPTYP_NULLABLE       3113    /* column will be nulled       */
#define SQLUIC_IGNORED_CHAR            3114    /* character ignored           */
#define SQLUIC_FIELD_TOO_LONG          3115    /* input CSV field too long    */
#define SQLUIC_CF_REQFIELD_MISSING     3116    /* field value missing         */
#define SQLUIC_CFINT2_NULLED           3117    /* smallint field nulled       */
#define SQLUIC_CFINT2_ROWREJ           3118    /* smallint field error        */
#define SQLUIC_CFINT4_NULLED           3119    /* int field nulled            */

#define SQLUIC_CFINT4_ROWREJ           3120    /* int field error             */
#define SQLUIC_CFFLOAT_NULLED          3121    /* float field nulled          */
#define SQLUIC_CFFLOAT_ROWREJ          3122    /* float field error           */
#define SQLUIC_CFDEC_NULLED            3123    /* decimal field nulled        */
#define SQLUIC_CFDEC_ROWREJ            3124    /* decimal field error         */
#define SQLUIC_CFTRUNC                 3125    /* char field truncated        */

#define SQLUIC_CFCHAR_NULLED           3126    /* char field nulled           */
#define SQLUIC_CFCHAR_ROWREJ           3127    /* char field error            */
#define SQLUIC_CFDATETRUNC             3128    /* date field truncated        */
#define SQLUIC_CFDTPAD                 3129    /* date/time/stamp field       */
                                               /* padded                      */

#define SQLUIC_CFTIMETRUNC             3130    /* time field truncated        */
#define SQLUIC_CFSTAMPTRUNC            3131    /* stamp field truncated       */
#define SQLUE_TRUNCATE                 3132    /* char field truncated        */
#define SQLUIC_ROWTOOSHORT             3137    /* not enough columns          */
#define SQLUIC_EOF_IN_CHARDELS         3138    /* end of input data file      */
#define SQLUE_SQLSTPDB_ERR             3139    /* stop using database failed  */

#define SQLUE_WSFLAB_LEN               3142    /* WSF label too big           */
#define SQLUE_CHAR_MTRUNC              3143    /* WSF char type length too    */
                                               /* long                        */
#define SQLUE_CHAR_WTRUNC              3144    /* WSF char type length too    */
                                               /* long                        */
#define SQLUE_CHAR_ITRUNC              3145    /* WSF char truncated at 240   */
#define SQLUE_ROWCT_LARGE              3147    /* row count exceeds 2048      */
#define SQLUE_3148                     3148    /* row not inserted            */

#define SQLUII_TCNTCMP                 3154    /* 'H' hcnt not equal 'T' rec  */
                                               /* ccnt                        */
#define SQLUII_CNAML                   3155    /* invalid name length in 'C'  */
                                               /* rec                         */
#define SQLUII_CNULL                   3156    /* invalid null field in 'C'   */
                                               /* rec                         */
#define SQLUII_CTYPE                   3157    /* invalid type field in 'C'   */
                                               /* rec                         */
#define SQLUII_CSBCP                   3158    /* invalid SBCP field in 'C'   */
                                               /* rec                         */
#define SQLUII_CDBCP                   3159    /* invalid DBCP field in 'C'   */
                                               /* rec                         */

#define SQLUII_CLENG                   3160    /* invalid col len fld in 'C'  */
                                               /* rec                         */
#define SQLUII_CPREC                   3161    /* invalid precision in 'C'    */
                                               /* rec                         */
#define SQLUII_CSCAL                   3162    /* invalid scale field in 'C'  */
                                               /* rec                         */
#define SQLUII_CFLOAT_BLANKLENG        3163    /* use 00008 for float col     */
                                               /* length                      */
#define SQLUII_CFLOAT_BADLENG          3164    /* invalid float col len in    */
                                               /* 'C'.                        */
#define SQLUII_CUTYPE                  3165    /* 'C' record has invalid      */
                                               /* type                        */
#define SQLUII_NOCREC_FOR_NULL_DBCOL   3166    /* IXF col does not exist      */
#define SQLUII_INVCREC_FOR_NULL_DBCOL  3167    /* IXF col is invalid          */
#define SQLUII_CRECCOMP_NULL_DBCOL     3168    /* IXF col not compatible      */

#define SQLUII_DEOF_INROW              3170    /* EOF found in row of data    */
#define SQLUIW_NONLAB_HDR              3171    /* non-label cell in hdr row   */
#define SQLUIW_NCOL_LOST               3172    /* nullable colnam not found   */
#define SQLUIW_UCOLTYP_NULL            3174    /* unsup col type - nullable   */
#define SQLUIW_INTYPE_INV              3175    /* wrong rec type for db col   */
#define SQLUIW_DATE_INV                3176    /* date value out of range     */
#define SQLUIW_TIME_INV                3177    /* time value out of range     */
#define SQLUIW_INTIME_INV              3178    /* int rec for time invalid    */
#define SQLUIW_NODATA_NNULL            3179    /* no data / non nullable col  */

#define SQLUE_INSERT_DISK              3180    /* insert diskette request     */
#define SQLUII_AE_NOTFOUND             3181    /* file ended before AE rec    */
#define SQLUII_INSERT_DISK_RETRY       3182    /* retry to insert diskette    */
#define SQLUEC_NOBLANK_B4KW            3183    /* mult del o'rides/no blanks  */
#define SQLUI_PREVMESG_ROWNO           3185    /* row of previous warning     */
#define SQLUI_LOGFULL_INSWARN          3186    /* log full inserting row      */
#define SQLUI_INDEX_WARN               3187    /* error creating index        */
#define SQLUI_TRUNCATE_TABLE           -3188   /* error truncating table      */

#define SQLUI_INDEXIXF                 -3190   /* invalid INDEXIXF option     */
#define SQLUI_VIEW_ERROR               -3193   /* cannot import to this view  */
#define SQLUI_SYSTBL_ERROR             -3194   /* cannot import system table  */
#define SQLUE_RETRY_DISK               3195    /* not enough space            */
#define SQLUI_IN_NOTFD                 -3196   /* input file not found        */
#define SQLUI_IMPBUSY                  -3197   /* import/export in use        */

#define SQLUI_REPL_PAR                 -3201   /* cant replace parent table   */
#define SQLUI_IUOPT_NOPK               -3203   /* cant update without PK's    */
#define SQLUI_IUOPT_NOVIEW             -3204   /* cant update views           */
#define SQLUI_VIEW_REF                 -3205   /* cant replace ref cons view  */
#define SQLUI_VIEW_SQUERY              -3206   /* cant replace subquery view  */

#define SQLUE_PROVIDE_FILE_PART        3220    /* AIX req next file           */
#define SQLUI_START_COMMIT             3221    /* start commit                */
#define SQLUI_FINISH_COMMIT            3222    /* finish commit               */
#define SQLUI_BAD_STRUCT_PARM          -3223   /* bad input parms             */
#define SQLUI_SKIPPED_ALL_ROWS         -3225   /* restartcnt too big          */
#define SQLU_WHICH_USER_RECORD         3227    /* map special token to user   */
                                               /* record                      */
#define SQLUI_COMPOUND_ERR             -3250   /* compound=x error            */

#define SQLUIW_RCSEQ_INV               -3300   /* row/col sequence invalid    */
#define SQLUIW_BOF_INV                 -3301   /* BOF in middle of WSF file   */
#define SQLUIW_EARLY_EOF               -3302   /* unexpected EOF              */
#define SQLUI_IXFONLY                  -3303   /* filetype not ixf            */
#define SQLUI_DELTABLE                 -3304   /* table does not exist        */
#define SQLUI_CREATE_ERR               -3305   /* table already exists        */
#define SQLUI_EXECUTE_ERR              -3306   /* SQL error during insert     */
#define SQLUI_INC_COL                  -3307   /* incomplete col info         */
#define SQLUI_CP_MISMATCH              -3308   /* codepage mismatch           */
#define SQLUI_DBLDATA                  -3309   /* double byte data found      */

#define SQLUI_UNREC_CTYPE              -3310   /* unrec col type              */
#define SQLUI_INVCREC_FOR_CREATE       -3310   /* invalid IXF column          */

#define SQLUE_DISK_FULL_DB2OS2         -3313   /* disk full - OS/2            */
#define SQLUE_DISK_FULL_DB2NT          -3313   /* disk full - Windows NT      */
#define SQLUE_DISK_FULL_DB2DOS         -3313   /* disk full - DOS             */
#define SQLUE_DISK_FULL_DB2WIN         -3313   /* disk full - Windows         */
#define SQLUE_DISK_FULL_DB2AIX         -10018  /* disk full - AIX             */
#define SQLUE_DISK_FULL_DB2MAC         -3313   /* disk full - MacOS           */

#define SQLUE_DISK_FULL                SQLUE_DISK_FULL_DB2NT

#define SQLUII_ASTAMP_NOMATCH          -3314   /* 'A' data/ time not as 'H'.  */
#define SQLUII_ACREC_BADVOL            -3315   /* invalid volume info         */
#define SQLUII_CLOSE_NOTLAST           -3316   /* error closing IXF file      */
#define SQLUW_FTMOD_INV                -3317   /* conflict in filetmod        */
#define SQLUEC_DUP_KEYWORD             -3318   /* keyword repeated/filetmod   */
#define SQLUI_ERR_CREATETAB            -3319   /* error creating table        */

#define SQLUEC_NOROOM_AFTERKW          -3320   /* keyword at end of filetmod  */
#define SQLUI_LOGFULL_INSERR           -3321   /* circular log full           */
#define SQLUE_SEM_ERROR                -3322   /* semaphore error             */
#define SQLUE_INVCOLTYPE               -3324   /* column type invalid         */
#define SQLUEW_IGNORED_ROW             3325    /* ignored WSF row             */
#define SQLUI_COL_LIST                 -3326   /* column list invalid         */
#define SQLUEI_SYSERROR                -3327   /* system error                */

#define SQLUII_ODD2GRAPH               3330    /* odd leng char -> graphic    */
#define SQLUE_OEACCESS                 -3331   /* permission denied           */
#define SQLUE_OEMFILE                  -3332   /* too many files open         */
#define SQLUE_OENOENT                  -3333   /* no such file or directory   */
#define SQLUE_OENOMEM                  -3334   /* not enough memory           */
#define SQLUE_OENOSPC                  -3335   /* no space left               */

#define SQLUIA_BAD_DCOL_METH           -3400   /* invalid method for ASC      */
#define SQLUI_DCOLM_ALL                -3401   /* invalid import method       */
#define SQLUIA_NULLLOC                 -3402   /* zeroes as begin/end         */
#define SQLUIA_LOCPAIR                 -3403   /* invalid pair                */
#define SQLUIA_LOCNUM                  -3404   /* invalid pair for number     */
#define SQLUIA_LOCDATE                 -3405   /* invalid pair for date       */
#define SQLUIA_LOCTIME                 -3406   /* invalid pair for time       */
#define SQLUIA_LOCSTAMP                -3407   /* invalid pair for timestamp  */
#define SQLUIA_LOCLONG                 3408    /* pair defines long field     */
#define SQLUIA_LOCSHORT                3409    /* pair defines short field    */
#define SQLUIA_LOCODD                  -3410   /* invalid pair for graphic    */
#define SQLUIA_CFGRAPH_NULLED          3411    /* value not graphic--null     */
#define SQLUIA_CFGRAPH_ROWREJ          3412    /* value not graphic--not      */
                                               /* null                        */
#define SQLUIA_SHORTFLDNULLED          3413    /* field too short--nulled     */
#define SQLU_NO_LIFEBOAT               -3414
#define SQLUIA_CFCPCV_NULLED           3415    /* CPCV failed--null           */
#define SQLUIA_CFCPCV_ROWREJ           3416    /* CPCV failed--not null       */

#define SQLU_TOO_MANY_WARNINGS         3502    /* number of warnings hit      */
                                               /* threshold                   */
#define SQLU_ROWCNT                    3503    /* number of rows hit          */
                                               /* threshold                   */
#define SQLULA_INVALID_RECLEN          -3505   /* reclen > 32767              */
#define SQLULA_NULLIND_IGNORED         3506    /* null ind value not Y or N   */
#define SQLUI_NULLIND                  -3507   /* nullind column is invalid   */
#define SQLUL_FILE_ERROR               -3508   /* file access error during    */
                                               /* load                        */
#define SQLUL_NUM_ROW_DELETED          3509    /* num of row deleted after    */
                                               /* load                        */
#define SQLU_SORT_WORK_DIR_ERROR       -3510   /* work directory is invalid   */
#define SQLU_NB_LOBFILE_MISSING        3511    /* lobfile missing but         */
                                               /* nullable col                */
#define SQLU_NNB_LOBFILE_MISSING       3512    /* lobfile missing,            */
                                               /* nonnullable col             */
#define SQLUL_UNMATCHED_CODEPAGE       -3513   /* codepage doesn't match db   */
#define SQLUL_SYSERR_WITH_REASON       -3514   /* system error with reason    */
                                               /* code                        */
#define SQLUL_UNEXPECTED_RECORD        -3517   /* unexpected rec in db2cs     */
#define SQLUL_INCOMPATIBLE_TABLE       -3518   /* coltype incompatible for    */
                                               /* db2cs                       */
#define SQLUL_FILE_NOT_FOUND           -3521   /* missing file                */
#define SQLUL_COPY_LOGRETAIN_OFF       -3522   /* copy spec, no logretain     */
                                               /* userexit                    */
#define SQLUL_NO_MESSAGES              3523    /* no messages to be           */
                                               /* retrieved                   */
#define SQLUL_FREESPACE_OPT            -3524   /* freespace option invalid    */
#define SQLU_INCOMPAT_OPT              -3525   /* incompatible options        */
#define SQLULA_INVALID_CODEPAGE        -3527   /* invalid codepage            */
#define SQLUL_DELIMITER_CONV_W         3528    /* delimiter may be converted  */
                                               /* from app to DB              */
#define SQLU_NEXT_TAPE_WARNING         3700    /* mount new tape              */
#define SQLU_LOBPATHS_IGNORED          3701    /* no lobs/longs but lobpath   */
                                               /* nonull                      */
#define SQLU_DEVICE_IGNORED            3702    /* device error but ignored    */
#define SQLU_NUM_BUFFERS               -3704   /* invalid number of buffers   */
#define SQLU_BUFFER_SIZE_ERROR         -3705   /* invalid load/unload buffer  */
                                               /* size                        */
#define SQLUL_DISK_FULL                -3706   /* copy target full            */
#define SQLU_SORT_BUFFSIZE_ERROR       -3707   /* invalid sort buffer size    */

/* Load / unload / load recovery SQLCODES                                     */
#define SQLU_OPEN_COPY_LOC_FILE_ERROR  -3783
#define SQLU_INV_COPY_LOC_FILE_INPUT   -3784
#define SQLU_LOAD_RECOVERY_FAILED      -3785
#define SQLU_INVALID_PARM_WARNING      3798
#define SQLU_LOAD_RECOVERY_PENDING     3799

/* load recovery - copy location input error type                             */
#define SQLU_KEYWORD_CODE              1
#define SQLU_OVERRIDE_CODE             2
#define SQLU_UNEXPECTED_EOF_CODE       3
#define SQLU_IOERROR_CODE              4

/* load recovery - Different Load recovery options                            */
#define SQLU_RECOVERABLE_LOAD          0
#define SQLU_NON_RECOVERABLE_LOAD      1

/* Loadapi SQLCODES                                                           */
#define SQLU_INVALID_QUIESCEMODE       -3802
#define SQLU_INVALID_INDEX             -3804
#define SQLU_INVALID_LOADAPI_ACTION    -3805
#define SQLU_CONSTRAINTS_NOT_OFF       -3806

/* Export SQLCODES                                                            */
#define SQLUE_MSG                      -3999   /* Export message              */

/* Roll-Forward Recovery SQLCODES                                             */
#define SQLU_INVALID_PARAM             -4904   /* invalid parameter           */
#define SQLU_INVALID_RANGE             -4905   /* invalid parameter range     */
#define SQLUM_INVALID_TPS_SET          -4906   /* invalid tablespace set      */
#define SQLUM_CHECK_PENDING_SET        4907    /* tables set to check         */
                                               /* pending state               */
#define SQLUM_TSP_NOT_READY            -4908   /* tablespace not ready to     */
                                               /* roll forward                */
#define SQLU_RC_MISSING_LOGFILES       -4970   /* missing log files           */
#define SQLU_RC_LOG_TRUNCATED          -4971   /* log truncation failed       */
#define SQLU_RC_LOGPATH_FULL           -4972   /* log path full               */
#define SQLU_RC_LOG_MISMATCH           -4973   /* log mismatch with catalog   */
                                               /* node                        */
#define SQLU_RC_QRY_ERR_WARN           4974    /* query status warning        */
#define SQLU_RC_CANCELED_WARN          4975    /* rollforward canceled        */
#define SQLU_RC_NOT_ON_CATALOG_NODE    -4976   /* not on catalog node         */

/* Configuration SQLCODES                                                     */
#define SQLF_RC_SYSAUTH                -5001   /* only SYSADM_GROUP can       */
                                               /* change db2 configuration    */
                                               /* file                        */
#define SQLF_RC_SYSERR                 -5005   /* system error                */
#define SQLF_RC_PATHNAME               -5010   /* path name error             */
#define SQLF_RC_INVNODENAME            -5020   /* invalid node name           */
#define SQLF_RC_INVSYSIDX              -5021   /* invalid system flag         */
#define SQLF_RC_INVDBIDX               -5022   /* invalid database flag       */
#define SQLF_RC_INVSYSADM              -5028   /* invalid sysadm_group        */
#define SQLF_RC_REL                    -5030   /* invalid release number      */
#define SQLF_RC_NEEDMIG                -5035   /* database needs migration;   */
                                               /* release number is back      */
                                               /* level                       */

#define SQLF_RC_INSMEM                 -5047   /* insufficient memory to      */
                                               /* support stack switching     */
#define SQLF_RC_SYSCSUM                -5050   /* invalid db2 configuration   */
                                               /* file                        */
#define SQLF_RC_DBCSUM                 -5055   /* invalid db configuration    */
                                               /* file                        */
#define SQLF_RC_INVTKN                 -5060   /* invalid token parameter     */
#define SQLF_RC_INVTKN_STRUCT          -5061   /* invalid ptr to sqlfupd      */
#define SQLF_RC_INVTKN_PTR             -5062   /* invalid token ptr value     */
#define SQLF_RC_INVNT                  -5065   /* invalid node type           */
#define SQLF_RC_CNTINV                 -5070   /* invalid count parameter     */
#define SQLF_RC_CNTBRK                 -5075   /* interrupt received          */
#define SQLF_RC_INVNEWLOGP             -5099   /* invalid new log path        */

#define SQLF_RC_INV_BIT_VALUE          -5112   /* invalid bit value - must    */
                                               /* be 0 or 1                   */

#define SQLF_RC_INVDETS                -5121   /* invalid DB configuration    */
                                               /* details                     */
#define SQLF_RC_PROTECT                -5122   /* database is copy protected  */
#define SQLF_RC_LOGIO                  -5123   /* I/O Error with log header   */
#define SQLF_RC_INV_DBMENT             -5126   /* invalid db2 config file     */
                                               /* entry                       */
#define SQLF_RC_INV_RANGE              -5130   /* integer out of range        */
#define SQLF_RC_INV_RANGE_2            -5131   /* integer out of range (-1)   */
#define SQLF_RC_INV_STRING             -5132   /* string null or too long     */
#define SQLF_RC_INV_SET                -5133   /* char/int not in set         */
#define SQLF_RC_INVTPNAME              -5134   /* tpname not valid            */
#define SQLF_RC_INV_DBPATH             -5136   /* dftdbpath not valid         */
#define SQLF_RC_INV_DIAGPATH           -5137   /* diagpath not valid          */
#define SQLF_RC_INV_AUTHENTICATION     -5140   /* invalid authentication      */
#define SQLF_RC_INV_AGENTPRI           -5131   /* invalid agent priority      */
#define SQLF_RC_INV_RANGE_TOO_SMALL    -5150   /* out of range - value too    */
                                               /* small                       */
#define SQLF_RC_INV_RANGE_TOO_SMALL_2  -5151   /* out of range - value too    */
                                               /* small (-1 is allowed)       */
#define SQLF_RC_INV_RANGE_TOO_BIG      -5152   /* out of range - value too    */
                                               /* large                       */
#define SQLF_RC_INV_RANGE_CONDITION    -5153   /* out of range - condition    */
                                               /* violated                    */
#define SQLF_RC_INV_AUTH_TRUST         -5154   /* authentication must be      */
                                               /* CLIENT for trust_allcnts =  */
                                               /* NO or trust_clntauth =      */
                                               /* SERVER                      */
#define SQLF_RC_SORTHEAP_PERF          5155    /* sortheap performance        */
                                               /* warning                     */

/* Data Redistribution Return Codes                                           */
#define SQLUT_NGNAME_UNDEF             -204    /* nodegroup name is           */
                                               /* undefined                   */
#define SQLUT_NODE_DUP                 -265    /* node is a duplicate node    */
#define SQLUT_NODE_UNDEF               -266    /* node is undefined           */
#define SQLUT_OVER_MAX_PARTNO          -269    /* max no. of part. map        */
                                               /* reached                     */
#define SQLUT_REDIST_UNDEF             -607    /* redist undefined for sys    */
                                               /* obj.                        */
#define SQLUT_INSAUTH                  -1092   /* insufficient authority      */
#define SQLUT_ACCESS_DENIED            -1326   /* file or dir access denied   */
#define SQLUT_NO_CONTAINERS            -1755   /* for tablespaces on a node   */
#define SQLUT_INVALID_AUTHS            SQLU_INVALID_AUTHS /* invalid          */
                                               /* authorizations -2018        */
#define SQLUT_INVALID_PARM             SQLU_INVALID_PARM /* parm to utility   */
                                               /* incorrect -2032             */
#define SQLUT_INVALID_PARM_ADDRESS     SQLU_INVALID_PARM_ADDRESS /* addr of   */
                                               /* parm incorrect -2034        */
#define SQLUT_CBI                      SQLUE_CBI /* function interruption     */
                                               /* 3005                        */
#define SQLUT_REDIST_NO_PARTKEY        -6047   /* redist failed - no part     */
                                               /* key                         */
#define SQLUT_ERR_IN_FILE              -6053   /* error found in the input    */
                                               /* file                        */
#define SQLUT_RC_REDIST_ERR            -6056   /* redistribution not          */
                                               /* performed                   */
#define SQLU_DIFF_LOG_SIZE             -6063   /* Log Extent file size        */
                                               /* changed                     */
#define SQLUT_ERROR_REDIST             -6064   /* error during data           */
                                               /* redistbution                */
#define SQLUT_WRT_OUT_FILE             -6065   /* error writing output file   */
/* Load Header Return Codes                                                   */
#define SQLU_PARTITIONMAP              -6100   /* Invalid partition map       */
#define SQLU_NODE_NUMBER               -6101   /* Invalid node number         */
#define SQLU_FUTURE_PARM               -6102   /* Parameter reserved for      */
                                               /* future                      */
#define SQLU_LOAD_SYSERR               -6103   /* Unexpected load system      */
                                               /* error                       */
#define SQLU_NO_INDICES                -6104   /* Load does not support       */
                                               /* indices                     */
#define SQLU_LOAD_COMPLETE             -6105   /* Load complete - backup NOW  */
                                               /* !                           */
#define SQLU_NOHEADER                  -6106   /* Invalid use of NOHEADER     */
#define SQLU_PARTITION_KEY             -6107   /* Invalid partitioning key    */
#define SQLU_PARTITION_KEY_NUM         -6108   /* Wrong number of partition   */
                                               /* keys                        */
#define SQLU_PARTITION_KEY_NAME        -6109   /* Unexpected partitioning     */
                                               /* key                         */
#define SQLU_PARTITION_KEY_TYPE        -6110   /* Unexpected partition key    */
                                               /* type                        */
/* Repository for obsolete Return Codes                                       */

#define SQLU_WRITE_ERROR               -2006   /* wrote wrong # of bytes      */
#define SQLU_CONNECT_ERROR             -2010   /* error in Start Using        */
#define SQLU_INT_ERROR                 -2012   /* error in ints               */
#define SQLUD_NO_MHEADER_ERROR         -2531   /* media header not present    */
#define SQLUD_NO_MHEADER_WARNING       2534    /* media header missing        */
#define SQLUD_NEXT_TAPE_WARNING        2535    /* another tape mount          */
                                               /* required                    */
#define SQLUD_ADSM_MOUNT_WAIT          2545    /* waiting for ADSM server to  */
                                               /* access data on removable    */
                                               /* media                       */

/******************************************************************************
** Configuration parameter obsolete return codes defines -  
** Some configuration parameters had specific out of range return
** codes; these have been replaced by generic out of range messages
** In these cases the old token names for the specific return codes
** are given, but the values are replaced by the new values returned 
** when out of range.
*******************************************************************************/

#define SQLF_RC_DBAUTH                 -5002   /* only SYSADM can             */
                                               /* changedatabase              */
                                               /* configuration file          */
#define SQLF_RC_INVNDB                 -5130   /* invalid # of concurrent db  */
#define SQLF_RC_INVRIO                 -5130   /* invalid req I/O blk size    */
#define SQLF_RC_INVSIO                 -5015   /* invalid serv I/O blk size   */
#define SQLF_RC_INVCHEAP               -5016   /* invalid communications      */
                                               /* heap                        */
#define SQLF_RC_INVRSHEAP              -5017   /* invalid remote services     */
                                               /* heap                        */
#define SQLF_RC_INVSHPTHR              -5130   /* invalid sort heap           */
                                               /* threshold                   */
#define SQLCC_RC_BAD_DB2COMM           -5036   /* invalid DB2COMM value       */
#define SQLCC_RC_NO_SERV_IN_DBMCFG     -5037   /* service name not definein   */
                                               /* db2 config file             */
#define SQLCC_RC_SERV_NOT_FOUND        -5038   /* service name not found in   */
                                               /* etc/services file           */
#define SQLCC_RC_INT_PORT_NOT_FOUND    -5039   /* interrupt port not found    */
                                               /* in/etc/services file        */
#define SQLCC_RC_NO_TPN_IN_DBMCFG      -5041   /* trans program name not      */
                                               /* definedin db2               */
                                               /* configuration file          */
#define SQLF_RC_INVNLL                 -5130   /* invalid # of locklist       */
#define SQLF_RC_INVNBP                 -5130   /* invalid # bufr pool pages   */
#define SQLF_RC_INVNDBF                -5130   /* invalid # of DB files open  */
#define SQLF_RC_INVSCP_DB2OS2          -5130   /* invalid soft check point    */
                                               /* value                       */
#define SQLF_RC_INVSCP_DB2AIX          -5130   /* invalid soft check point    */
                                               /* value                       */
#define SQLF_RC_INVSCP                 -5130   /* invalid soft check point    */
                                               /* value                       */
#define SQLF_RC_INVNAP                 -5130   /* invalid # of active appls   */
#define SQLF_RC_INVAHP                 -5130   /* invalid application heapsz  */
#define SQLF_RC_INVDHP                 -5130   /* invalid database heap size  */
#define SQLF_RC_INVDLT                 -5130   /* invalid deadlock detection  */
#define SQLF_RC_INVTAF                 -5130   /* invalid # of total files    */
                                               /* openper application         */
#define SQLF_RC_INVSHP                 -5130   /* invalid sortlist heap       */
#define SQLF_RC_INVMAL                 -5130   /* invalid maxlocks per        */
                                               /* application                 */
#define SQLF_RC_INVSTMHP               -5130   /* invalid statement heap      */
#define SQLF_RC_INVLOGPRIM             -5130   /* invalid number primary log  */
                                               /* files                       */
#define SQLF_RC_INVLOG2ND              -5130   /* invalid number of           */
                                               /* secondary log files         */
#define SQLF_RC_INVLOGFSZ              -5130   /* invalid log file size       */
#define SQLF_RC_INVDB2                 -5102   /* incompatible file open      */
                                               /* parmeter                    */
#define SQLF_RC_INVK2                  -5104   /* no DB's / requestor only    */
#define SQLF_RC_INVK3                  -5126   /* standalone nodetype does    */
                                               /* notsupport nodename         */
#define SQLF_RC_RWS_EXIST              -5106   /* remote workstation has      */
                                               /* alreadybeen configured      */
#define SQLF_RC_RWS_SYSADM             -5107   /* <authid> does not           */
                                               /* haveauthority to add or     */
                                               /* drop a remote workstation   */
#define SQLF_RC_RWS_NOT_EXIST          -5108   /* remote workstation has      */
                                               /* notbeen previously setup    */
                                               /* using sqlarws               */
#define SQLF_RC_RWS_MACHINENAME        -5109   /* machine name is missing     */
                                               /* ors too long.               */
#define SQLF_RC_RWS_INV_OPT            -5110   /* configuration option is     */
                                               /* invalid                     */
#define SQLF_RC_ENV_VAR_NOTDEF         -5111   /* environment                 */
                                               /* variableDB2WKSTPROF is not  */
                                               /* defined                     */
#define SQLF_RC_INVDB3                 -5146   /* incompatible buffer pool    */
                                               /* and maximum # of            */
                                               /* applications                */
#define SQLF_RC_INV_QUERY_HEAP_SZ      -5143   /* invalid QUERY_HEAP_SZ       */
#define SQLF_RC_INV_RANGE_3            -5144   /* out of range - limited by   */
                                               /* a parm                      */
#define SQLF_RC_INV_RANGE_MAX_EXPR     -5144   /* out of range - maximum      */
                                               /* limited by an expression    */
#define SQLF_RC_INV_RANGE_MAX_EXPR_2   -5145   /* out of range - maximum      */
                                               /* limited by an expression    */
                                               /* (range includes -1)         */
#define SQLF_RC_INV_RANGE_MIN_EXPR     -5146   /* out of range - minimum      */
                                               /* limited by an expression    */
#define SQLF_RC_INV_RANGE_MIN_EXPR_2   -5147   /* out of range - minimum      */
                                               /* limited by an expression    */
                                               /* (range includes -1)         */
#define SQLF_RC_KCON                   -5025   /* not current db2             */
                                               /* configuration               */
#define SQLF_RC_INVILF                 -5083   /* invalid initial log size    */
#define SQLF_RC_INVLFE                 -5091   /* invalid logfile extention   */
#define SQLF_RC_INVNLE                 -5092   /* invalid # of log extention  */
#define SQLF_RC_INVDB1                 -5101   /* incompatible logfile        */
                                               /* parameter                   */
#define SQLF_RC_LF_1_3                 -5120   /* both R1 & R3 Log            */
                                               /* parameters may not be       */
                                               /* modified                    */
#define SQLF_RC_LOW_APPLS_AND_LOCKS    -5135   /* maxappls*maxlocks too low   */
#define SQLF_RC_MAX_ITEMS_EXCEEDED     -5139   /* To many items on update or  */
                                               /* get                         */
#define SQLF_RC_INV_AVG_APPLS          -5141   /* invalid AVG_APPLS           */

/* Flush Table API Return Codes                                               */
#define SQLUF_TABLE_NOT_AT_NODE        -6024   /* Table not at this node      */

/* sqlugrpi, sqlugrpn, and sqlugtpi return codes                              */
#define SQLUG_INVALID_AUTHID           SQLUS_INVALID_AUTHID /* Invalid        */
                                               /* authid                      */
#define SQLUG_INVALID_TABLE_NAME       SQLUS_INVALID_TABLE_NAME /* invalid    */
                                               /* table                       */
#define SQLUG_CBI                      SQLUE_CBI /* Interrupt                 */
#define SQLUG_TABLE_NOT_FOUND          SQLUR_TABLE_NOT_FOUND /* Table not     */
                                               /* exist                       */
#define SQLUG_RC_INSAUTH               -6023   /* Insufficient authorization  */
#define SQLUG_NULL_PARTKEY             -6038   /* No partitioning key         */
#define SQLUG_NULL_NOTALLOWED          -6039   /* Nulls not allowed           */
#define SQLUG_INVALID_SYNTAX           -6044   /* Invalid syntax              */
#define SQLUG_INVALID_DATATYPE         -6045   /* Invalid datatype            */

/* obsolete database manager configuration parameter tokens                   */
#define SQLF_KTN_SVRIOBLK              3
#define SQLF_KTN_SQLENSEG              5
#define SQLF_KTN_COMHEAPSZ             8
#define SQLF_KTN_RSHEAPSZ              9
#define SQLF_KTN_NUMRC                 10
#define SQLF_KTN_CUINTERVAL            14
#define SQLF_KTN_SQLSTMTSZ             17
#define SQLF_KTN_COMHEAPSZ_P           50
#define SQLF_KTN_RSHEAPSZ_P            51
#define SQLF_KTN_IPX_FILESERVER        SQLF_KTN_FILESERVER
#define SQLF_KTN_IPX_OBJECTNAME        SQLF_KTN_OBJECTNAME
#define SQLF_KTN_ADSM_PASSWORD         93
#define SQLF_KTN_ADSM_NODENAME         94
#define SQLF_KTN_ADSM_OWNER            95
#define SQLF_KTN_MAX_IDLEAGENTS        60

/* obsolete config parm default defines                                       */
#define SQLFDMCA                       -1      /* Default maxcagents          */
#define SQLFDMXD                       -1      /* Default maxdari             */
#define SQLFDAPR                       -1      /* Default agentpri            */
#define SQLFMKPD                       0       /* keepdari - no               */
#define SQLFXKPD                       1       /* keepdari - yes              */

/* obsolete database configuration parameter tokens                           */
#define SQLF_DBTN_LOGFILE              4
#define SQLF_DBTN_MAXTOTFILOP          10
#define SQLF_DBTN_LOGEXT               12
#define SQLF_DBTN_LOGMAXEXT            13
#define SQLF_DBTN_AGENTHEAP            14
#define SQLF_DBTN_SEGPAGES             123
#define SQLF_DBTN_BUFFPAGE             2
#define SQLF_DBTN_SORTHEAP             91
#define SQLF_DBTN_SORTHEAPSZ_P         SQLF_DBTN_SORT_HEAP
#define SQLF_DBTN_DBHEAP_P             SQLF_DBTN_DBHEAP
#define SQLF_DBTN_APPLHEAPSZ_P         SQLF_DBTN_APPLHEAPSZ
#define SQLF_DBTN_STMTHEAPSZ_P         SQLF_DBTN_STMTHEAP
#define SQLF_DBTN_LOGFILSIZ            18
#define SQLF_DBTN_MULTIPGAL            504
#define SQLF_DBTN_ADSM_PASSWD          501


/* Repository for obsolete prototypes                                         */

SQL_API_RC SQL_API_FN
  sqlfeudb (
   _SQLOLDCHAR *,                           /* database                       */
   _SQLOLDCHAR *,                           /* password                       */
   unsigned short,                          /* count                          */
   struct sqlfupd *,                        /* list of items                  */
   struct sqlca *);                         /* SQLCA                          */

SQL_API_RC SQL_API_FN                       /* Update Database Configuration  */
  sqlgeudb (
   unsigned short,                          /* reserved                       */
   unsigned short,                          /* database alias length          */
   unsigned short,                          /* number of entries being        */
                                            /* modified                       */
   unsigned short *,                        /* list of item lengths           */
   struct sqlfupd *,                        /* list of items                  */
   struct sqlca *,                          /* SQLCA                          */
   _SQLOLDCHAR *,                           /* reserved                       */
   _SQLOLDCHAR *);                          /* database alias                 */

SQL_API_RC SQL_API_FN                       /* Reset Database Configuration   */
  sqlgrdbc (
   unsigned short,                          /* Spare1                         */
   unsigned short,                          /* Database name length           */
   struct sqlca *,                          /* SQLCA                          */
   _SQLOLDCHAR *,                           /* Spare2                         */
   _SQLOLDCHAR *);                          /* database                       */

SQL_API_RC SQL_API_FN                       /* Return Database Configuration  */
  sqlgxdbc (
   unsigned short,                          /* Spare1                         */
   unsigned short,                          /* Database name length           */
   unsigned short,                          /* count                          */
   struct sqlfupd *,                        /* list of items                  */
   struct sqlca *,                          /* SQLCA                          */
   _SQLOLDCHAR *,                           /* Spare2                         */
   _SQLOLDCHAR *);                          /* Database                       */

/******************************************************************************
** 
** The following functions and symbols are obsolete and may not be supported
** in future releases. The obsolete functions are provided for backward compatibility
** and exported from DB2API.LIB. All applications should be migrated to use new APIs.
** Note: Some of the function parameters may be NO-OP.
** 
*******************************************************************************/
SQL_API_RC SQL_API_FN
  sqlfrdbc (
        _SQLOLDCHAR *,                         /* database                    */
        _SQLOLDCHAR *,                         /* password                    */
        struct sqlca *);                       /* SQLCA                       */

SQL_API_RC SQL_API_FN
  sqlfxdbc (
        _SQLOLDCHAR *,                         /* database alias              */
        _SQLOLDCHAR *,                         /* password                    */
        unsigned short,                        /* count of entries being      */
                                               /* returned                    */
        struct sqlfupd *,                      /* list of items               */
        struct sqlca *);                       /* SQLCA                       */

/* Provide info about a tableSpace in a database                              */
SQL_STRUCTURE SQLB_TBSQRY_DATA
{
   unsigned long   id;                 /* internal id for the pool            */
   unsigned long   nameLen;            /* length of the name (for cobol &     */
                                       /* other nonC lang.)                   */
   char            name[SQLB_MAX_TBS_NAME_SZ]; /* NUL terminated name         */
   unsigned long   totalPages;         /* DMS : Pages specified by CREATE     */
                                       /* TABLESPACE.                         */
                                       /* SMS : N/A                           */
   unsigned long   useablePages;       /* DMS : totalPages - overhead         */
                                       /* SMS : N/A                           */
   unsigned long   flags;              /* bit attributes for the pool --      */
                                       /* includes 'class' & other stuff to   */
                                       /* be defined                          */
   unsigned long   pageSize;           /* pagesize of tablespace (in          */
                                       /* bytes)..currently fixed at 4K       */
   unsigned long   extSize;            /* extent size (in pages)              */
   unsigned long   prefetchSize;       /* prefetch size                       */
   unsigned long   nContainers;        /* number of containers                */
   unsigned long   tbsState;           /* SQLB_NORMAL, SQLB_LOAD_PENDING,     */
                                       /* etc.                                */
   char            lifeLSN[6];         /* 'timestamp' identifying the origin  */
                                       /* of the tbs                          */
   char            pad[2];             /* for alignment                       */
};

SQL_API_RC SQL_API_FN                            /* Single TableSpace Query   */
  sqlgstsq (
   struct sqlca * pSqlca,
   unsigned long TablespaceId,                   /* in: tableSpace id         */
   struct SQLB_TBSQRY_DATA * pTablespaceData);   /* out: tableSpace data      */

SQL_API_RC SQL_API_FN                            /* Fetch TableSpace Query    */
  sqlgftsq (
   struct sqlca * pSqlca,
   unsigned long MaxTablespaces,                 /* size of output area       */
   struct SQLB_TBSQRY_DATA * pTablespaceData,    /* out: array of length      */
                                                 /* maxTbs                    */
   unsigned long * pNumTablespaces);             /* out: #data entries        */
                                                 /* returned                  */

SQL_API_RC SQL_API_FN                            /* TableSpace Query          */
  sqlgtsq (
   struct sqlca * pSqlca,
   unsigned long * pNumTablespaces,              /* out: total number of      */
                                                 /* table spaces              */
   struct SQLB_TBSQRY_DATA ** ppTablespaceData); /* out: mem returned to      */
                                                 /* application               */

/* stsq - Single TableSpace Query                                             */
SQL_API_RC SQL_API_FN                            /* Single Tablespace Query   */
  sqlbstsq (
   struct sqlca * pSqlca,                        /* SQLCA                     */
   unsigned long TablespaceId,                   /* in: tableSpace id         */
   struct SQLB_TBSQRY_DATA * pTablespaceData);   /* out: tableSpace data      */

/* ftsq - Fetch TableSpace Query -> fetch the next block of tbs data          */
SQL_API_RC SQL_API_FN                            /* Fetch Tablespace Query    */
  sqlbftsq (
   struct sqlca * pSqlca,                        /* SQLCA                     */
   unsigned long MaxTablespaces,                 /* max num of tbs the        */
                                                 /* output area can hold      */
   struct SQLB_TBSQRY_DATA * pTablespaceData,    /* out: array of length      */
                                                 /* maxTbs                    */
   unsigned long * pNumTablespaces);             /* out: #data entries        */
                                                 /* returned                  */

/* tsq - TableSpace Query -> uses the above primitives to return the FULL     */
/* list of tablespaces in an array allocated and returned to the              */
/* application.  The application should free this memory with the sqlefmem()  */
/* api when it is finished with it. Even if this api fails with an            */
/* 'insufficient memory' error, 'nTbs' is set to the number of tablespaces    */
/* in the database. 'nTbs' is set to zero if we fail to sucessfully open a    */
/* query. 'tbsData' is returned as NULL (0;no mem alloc) if we fail for any   */
/* reason.                                                                    */
SQL_API_RC SQL_API_FN                            /* Tablespace Query          */
  sqlbtsq (
   struct sqlca * pSqlca,                        /* SQLCA                     */
   unsigned long * pNumTablespaces,              /* out: total number of      */
                                                 /* table spaces              */
   struct SQLB_TBSQRY_DATA ** ppTablespaceData); /* out: mem returned to      */
                                                 /* application               */

#define SLQUI_TINTO SQLUI_TINTO                  /* invalid into in tcolstrg  */
/******************************************************************************
** 
** End of obsolete functions and symbols
** 
*******************************************************************************/
#pragma pack()

#ifdef __cplusplus 
}
#endif

#endif /* SQL_H_SQLUTIL */
