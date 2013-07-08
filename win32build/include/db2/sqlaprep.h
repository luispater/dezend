/******************************************************************************
** 
** Source File Name: SQLAPREP
** 
** (C) COPYRIGHT International Business Machines Corp. 1988, 1997
** All Rights Reserved
** Licensed Materials - Property of IBM
** 
** US Government Users Restricted Rights - Use, duplication or
** disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
** 
** Function = Include File defining:
**              Global equates, structures, and prototypes for
**              Precompiler and Runtime Command Interfaces
** 
** Operating System =  Windows NT
** 
*******************************************************************************/
#ifndef SQL_H_SQLAPREP
#define SQL_H_SQLAPREP

#ifdef __cplusplus
extern "C" {
#endif


/* Required Include Files                                                     */
#include "sqlsystm.h"              /* System dependent defines  */
#include "sqlca.h"
#include "sqlenv.h"
#include "sqladef.h"

#pragma pack(4)

/* Macro used to calculate size of a precompiler option array, an input       */
/* parameter of SQLAINIT.                                                     */
#define SQLA_NUM_OPTIONS(n) (sizeof(struct sqla_options_header) + \
(n)*sizeof(struct sqla_option)        )

/* Values used for option[n].type, an input parameter of SQLAINIT.            */
#define SQLA_FORMAT            SQL_FRMT_OPT      /* Option: date/time format  */
#define SQLA_ACCESS_PLAN       2                 /* Option: access plan       */
                                                 /* creation                  */
#define SQLA_BIND_FILE         3                 /* Option: bind file         */
                                                 /* creation                  */
#define SQLA_ISOLATION         SQL_ISO_OPT       /* Option: isolation level   */
#define SQLA_BLOCK             SQL_BLOCK_OPT     /* Option: record blocking   */
#define SQLA_FLAG_OPT          SQL_FLAG_OPT      /* Flagger option            */
#define SQLA_STDS_LEVEL        7                 /* Option: standards         */
                                                 /* compliance                */
#define SQLA_CNULREQD_OPT      SQL_CNULREQD_OPT  /* C NULL required option    */
#define SQLA_GENERIC_OPT       SQL_GENERIC_OPT   /* Generic option            */
#define SQLA_DEFERRED_PREPARE_OPT SQL_DEFERRED_PREPARE_OPT /* Option for      */
                                                 /* Deferred Prepare          */
#define SQLA_LEVEL_OPT         SQL_LEVEL_OPT     /* Level of a module         */
#define SQLA_COLLECTION_OPT    SQL_COLLECTION_OPT /* Package collection id    */
#define SQLA_VERSION_OPT       SQL_VERSION_OPT   /* Package version id        */
#define SQLA_OWNER_OPT         SQL_OWNER_OPT     /* Package owner auth id     */
#define SQLA_SCHEMA_OPT        SQL_SCHEMA_OPT    /* Synonym for owner         */
#define SQLA_QUALIFIER_OPT     SQL_QUALIFIER_OPT /* Authorization identifier  */
                                                 /* that is to be used as     */
                                                 /* qualifier for             */
                                                 /* unqualified objects       */
#define SQLA_CATALOG_OPT       SQL_CATALOG_OPT   /* Synonym for qualifier.    */
#define SQLA_TEXT_OPT          SQL_TEXT_OPT      /* Package description       */
#define SQLA_VALIDATE_OPT      SQL_VALIDATE_OPT  /* Indicates when object     */
                                                 /* validation occurs         */
#define SQLA_EXPLAIN_OPT       SQL_EXPLAIN_OPT   /* Determines whether        */
                                                 /* information will be       */
                                                 /* produced about how the    */
                                                 /* SQL statements in a       */
                                                 /* package will be executed  */
#define SQLA_ACTION_OPT        SQL_ACTION_OPT    /* Indicates whether a       */
                                                 /* package is to be added    */
                                                 /* or replaced               */
#define SQLA_SQLERROR_OPT      SQL_SYNTAX_OPT    /* Indicates under what      */
                                                 /* conditions a package      */
                                                 /* will be created           */
#define SQLA_REPLVER_OPT       SQL_REPLVER_OPT   /* Replaces a specific       */
                                                 /* version of a package      */
#define SQLA_RETAIN_OPT        SQL_RETAIN_OPT    /* Indicates whether         */
                                                 /* EXECUTE authorities are   */
                                                 /* to be preserved when a    */
                                                 /* package is replaced       */
#define SQLA_RELEASE_OPT       SQL_RELEASE_OPT   /* Indicates whether         */
                                                 /* resources are released    */
                                                 /* at each COMMIT or when    */
                                                 /* the application           */
                                                 /* terminates                */
#define SQLA_DEGREE_OPT        SQL_DEGREE_OPT    /* Specifies whether or not  */
                                                 /* the query is executed     */
                                                 /* using I/O parallelism     */
#define SQLA_STRDEL_OPT        SQL_STRDEL_OPT    /* Designates whether an     */
                                                 /* apostrophe or quote will  */
                                                 /* be used as a string       */
                                                 /* delimiter                 */
#define SQLA_DECDEL_OPT        SQL_DECDEL_OPT    /* Designates whether a      */
                                                 /* period or comma will be   */
                                                 /* used as a decimal point   */
                                                 /* indicator                 */
#define SQLA_CHARSUB_OPT       SQL_CHARSUB_OPT   /* Designates default        */
                                                 /* character subtype that    */
                                                 /* is to be used for column  */
                                                 /* definitions in the        */
                                                 /* CREATE and ALTER TABLE    */
                                                 /* SQL statements            */
#define SQLA_CCSIDS_OPT        SQL_CCSIDS_OPT    /* Designates what CCSID     */
                                                 /* will be used for single   */
                                                 /* byte characters for       */
                                                 /* character column          */
                                                 /* definitions without a     */
                                                 /* specific CCSID clause in  */
                                                 /* the CREATE and ALTER      */
                                                 /* TABLE SQL statements      */
#define SQLA_CCSIDM_OPT        SQL_CCSIDM_OPT    /* Designates what CCSID     */
                                                 /* will be used for mixed    */
                                                 /* byte characters for       */
                                                 /* character column          */
                                                 /* definitions without a     */
                                                 /* specific CCSID clause in  */
                                                 /* the CREATE and ALTER      */
                                                 /* TABLE SQL statements      */
#define SQLA_CCSIDG_OPT        SQL_CCSIDG_OPT    /* Designates what CCSID     */
                                                 /* will be used for double   */
                                                 /* byte characters for       */
                                                 /* character column          */
                                                 /* definitions without a     */
                                                 /* specific CCSID clause in  */
                                                 /* the CREATE and ALTER      */
                                                 /* TABLE SQL statements      */
#define SQLA_DEC_OPT           SQL_DEC_OPT       /* Specifies the maximum     */
                                                 /* precision to be used in   */
                                                 /* decimal arithmetic        */
                                                 /* operations                */
#define SQLA_CONNECT_OPT       SQL_CONNECT_OPT   /* Specifies whether one or  */
                                                 /* multiple connections can  */
                                                 /* exist at the same time.   */
#define SQLA_SQLRULES_OPT      SQL_RULES_OPT     /* Specifies the set of      */
                                                 /* rules used for            */
                                                 /* connection to multiple    */
                                                 /* databases within a        */
                                                 /* single unit of work       */
#define SQLA_DISCONNECT_OPT    SQL_DISCONNECT_OPT /* Specifies which          */
                                                 /* databases disconnected    */
                                                 /* when a COMMIT or          */
                                                 /* ROLLBACK is issued.       */
#define SQLA_SYNCPOINT_OPT     SQL_SYNCPOINT_OPT /* Specifies what syncpoint  */
                                                 /* option (for example one   */
                                                 /* or two phase) will be     */
                                                 /* used.                     */
#define SQLA_DYNAMICRULES_OPT  SQL_DYNAMICRULES_OPT /* Specifies which        */
                                                 /* authorization identifier  */
                                                 /* to use when dynamic SQL   */
                                                 /* in a package is           */
                                                 /* executed. Owner of        */
                                                 /* package or authid         */
                                                 /* executing package.        */
#define SQLA_INSERT            SQL_INSERT_OPT    /* Buffers VALUE inserts -   */
                                                 /* bind and precompile       */
                                                 /* option for DB2/PE         */
                                                 /* servers only              */
#define SQLA_EXPLSNAP_OPT      SQL_EXPLSNAP_OPT  /* Capture explain snapshot  */
                                                 /* - bind and precompile     */
                                                 /* option                    */
#define SQLA_FUNCTION_PATH     SQL_FUNCTION_PATH /* Path for user-defined     */
                                                 /* function resolution -     */
                                                 /* bind and precompile       */
                                                 /* option                    */
#define SQLA_SQLWARN_OPT       SQL_SQLWARN_OPT   /* Disable prepare-time SQL  */
                                                 /* warnings - bind and       */
                                                 /* precompile option         */
#define SQLA_QUERYOPT_OPT      SQL_QUERYOPT_OPT  /* Set query optimization    */
                                                 /* class -bind and           */
                                                 /* precompile option         */
#define SQLA_TARGET_OPT        SQL_TARGET_OPT    /* Target compiler           */
                                                 /* precompile option         */
#define SQLA_PREP_OUTPUT_OPT   SQL_PREP_OUTPUT_OPT /* Name of precompiler     */
                                                 /* output file - precompile  */
                                                 /* option                    */
#define SQLA_TOKEN_USE_INITIALIZED_OPT 1000      /* Internal use only         */
#define SQLA_USE_LONG_LABELS   1001              /* Internal use only         */

/* Values used for option[n].val when option[n].type is SQLA_FORMAT in        */
/* the Precompiler Option Array.                                              */
#define SQLA_POA_DEF           0       /* Default date/time format            */
#define SQLA_POA_USA           1       /* USA date/time format                */
#define SQLA_POA_EUR           2       /* European date/time format           */
#define SQLA_POA_ISO           3       /* International date/time format      */
#define SQLA_POA_JIS           4       /* Japanese date/time format           */
#define SQLA_POA_LOC           5       /* Local date/time format              */

/* Values used for option[n].val when option[n].type is SQLA_ACCESS_PLAN in   */
/* the Precompiler Option Array.                                              */
#define SQLA_CREATE_PLAN       1       /* Create an access plan               */
#define SQLA_NO_PLAN           0       /* Do not create an access plan        */
#define SQLA_NO_PLAN_SYNTAX    3       /* Set ocb->syntax to TRUE             */

/* Values used for option[n].val when option[n].type is SQLA_BIND_FILE in     */
/* the Precompiler Option Array.                                              */
#define SQLA_CREATE_BIND_FILE  1       /* Create a bind file                  */
#define SQLA_NO_BIND_FILE      0       /* Do not create a bind file           */

/* Values used for option[n].val when option[n].type is SQLA_ISOLATION in     */
/* the Precompiler Option Array.                                              */
#define SQLA_REPEATABLE_READ   SQL_REP_READ      /* RR isolation level        */
#define SQLA_CURSOR_STABILITY  SQL_CURSOR_STAB   /* CS Isolation level        */
#define SQLA_UNCOMMITTED_READ  SQL_UNCOM_READ    /* UR Isolation level        */
#define SQLA_READ_STABILITY    SQL_READ_STAB     /* RS Isolation level        */
#define SQLA_NO_COMMIT         SQL_NO_COMMIT     /* NC Isolation level        */

/* Values used for option[n].val when option[n].type is SQLA_BLOCK in         */
/* the Precompiler Option Array.                                              */
#define SQLA_BLOCK_UNAMBIG     SQL_BL_UNAMBIG
#define SQLA_BLOCK_ALL         SQL_BL_ALL
#define SQLA_NO_BLOCK          SQL_NO_BL

/* Maximum sqlchar length for option[n].val when option[n].type is SQLA       */
/* LEVEL_OPT                                                                  */
#define SQLA_MAX_LEVEL         SQL_MAX_LEVEL

/* Maximum sqlchar length for option[n].val when option[n].type is SQLA       */
/* COLLECTION_OPT                                                             */
#define SQLA_MAX_COLLECTION    SQL_MAX_COLLECTION

/* Maximum sqlchar length for option[n].val when option[n].type is SQLA       */
/* VERSION_OPT                                                                */
#define SQLA_MAX_VERSION       SQL_MAX_VERSION

/* Maximum sqlchar length for option[n].val when option[n].type is SQLA       */
/* OWNER_OPT                                                                  */
#define SQLA_MAX_OWNER         SQL_MAX_OWNER

/* Maximum sqlchar length for option[n].val when option[n].type is SQLA       */
/* SCHEMA_OPT                                                                 */
#define SQLA_MAX_SCHEMA        SQLA_MAX_OWNER

/* Maximum sqlchar length for option[n].val when option[n].type is SQLA       */
/* QUALIFIER_OPT                                                              */
#define SQLA_MAX_QUALIFIER     SQL_MAX_QUALIFIER

/* Maximum sqlchar length for option[n].val when option[n].type is SQLA       */
/* CATALOG_OPT                                                                */
#define SQLA_MAX_CATALOG       SQLA_MAX_QUALIFIER

/* Maximum sqlchar length for option[n].val when option[n].type is SQLA_TEXT  */
/* OPT                                                                        */
#define SQLA_MAX_TEXT          SQL_MAX_TEXT

/* Values used for option[n].val when option[n].type is SQLA_VALIDATE_OPT.    */
#define SQLA_VALIDATE_BIND     SQL_VALIDATE_BIND /* Validate objects during   */
                                                 /* BIND                      */
#define SQLA_VALIDATE_RUN      SQL_VALIDATE_RUN  /* Validate objects during   */
                                                 /* execution                 */

/* Values used for option[n].val when option[n].type is SQLA_EXPLAIN_OPT.     */
#define SQLA_EXPLAIN_NO        SQL_EXPLAIN_NO    /* No EXPLAIN output         */
                                                 /* produced                  */
#define SQLA_EXPLAIN_YES       SQL_EXPLAIN_YES   /* EXPLAIN output produced   */
#define SQLA_EXPLAIN_ALL       SQL_EXPLAIN_ALL   /* EXPLAIN output produced   */
                                                 /* for all static and        */
                                                 /* dynamic statements.       */

/* Values used for option[n].val when option[n].type is SQLA_ACTION_OPT.      */
#define SQLA_ACTION_ADD        SQL_ACTION_ADD    /* Package is added          */
#define SQLA_ACTION_REPLACE    SQL_ACTION_REPLACE /* Package is replaced      */

/* Maximum sqlchar length for option[n].val when option[n].type is SQLA       */
/* REPLVER_OPT                                                                */
#define SQLA_MAX_REPLVER       SQL_MAX_REPLVER

/* Values used for option[n].val when option[n].type is SQLA_SQLERROR_OPT.    */
#define SQLA_SQLERROR_NOPACKAGE SQL_NO_SYNTAX_CHECK /* Do not create a        */
                                                 /* package if errors are     */
                                                 /* encountered               */
#define SQLA_SQLERROR_CHECK    SQL_SYNTAX_CHECK  /* Do not create a package   */
#define SQLA_SQLERROR_CONTINUE SQL_SQLERROR_CONTINUE /* Create a package      */
                                                 /* even if errors are        */
                                                 /* encountered               */

/* Values used for option[n].val when option[n].type is SQLA_RETAIN_OPT.      */
#define SQLA_RETAIN_NO         SQL_RETAIN_NO     /* Do not preserve EXECUTE   */
                                                 /* authorities when a        */
                                                 /* package is replaced       */
#define SQLA_RETAIN_YES        SQL_RETAIN_YES    /* Preserve EXECUTE          */
                                                 /* authorities when a        */
                                                 /* package is replaced       */

/* Values used for option[n].val when option[n].type is SQLA_RELEASE_OPT.     */
#define SQLA_RELEASE_COMMIT    SQL_RELEASE_COMMIT /* Release resources at     */
                                                 /* COMMIT                    */
#define SQLA_RELEASE_DEALLOCATE SQL_RELEASE_DEALLOCATE /* Release resources   */
                                                 /* when a program            */
                                                 /* terminates                */

/* Values used for option[n].val when option[n].type is SQLA_STRDEL_OPT.      */
#define SQLA_STRDEL_APOSTROPHE SQL_STRDEL_APOSTROPHE /* Apostrophe string     */
                                                 /* delimiter                 */
#define SQLA_STRDEL_QUOTE      SQL_STRDEL_QUOTE  /* Quote string delimiter    */

/* Values used for option[n].val when option[n].type is SQLA_DECDEL_OPT.      */
#define SQLA_DECDEL_PERIOD     SQL_DECDEL_PERIOD /* Period is used as a       */
                                                 /* decimal point indicator   */
                                                 /* in decimal and floating   */
                                                 /* point literals            */
#define SQLA_DECDEL_COMMA      SQL_DECDEL_COMMA  /* Comma is used as a        */
                                                 /* decimal point indicator   */
                                                 /* in decimal and floating   */
                                                 /* point literals            */

/* Values used for option[n].val when option[n].type is SQLA_CHARSUB_OPT.     */
#define SQLA_CHARSUB_DEFAULT   SQL_CHARSUB_DEFAULT /* Use the target system   */
                                                 /* defined default for all   */
                                                 /* new character columns     */
                                                 /* for which an explicit     */
                                                 /* subtype is not specified  */
#define SQLA_CHARSUB_BIT       SQL_CHARSUB_BIT   /* Use the bit character     */
                                                 /* subtype for all new       */
                                                 /* character columns for     */
                                                 /* which an explicit         */
                                                 /* subtype is not specified  */
#define SQLA_CHARSUB_SBCS      SQL_CHARSUB_SBCS  /* Use the SBCS character    */
                                                 /* subtype for all new       */
                                                 /* character columns for     */
                                                 /* which an explicit         */
                                                 /* subtype is not specified  */
#define SQLA_CHARSUB_MIXED     SQL_CHARSUB_MIXED /* Use the mixed character   */
                                                 /* subtype for all new       */
                                                 /* character columns for     */
                                                 /* which an explicit         */
                                                 /* subtype is not specified  */

/* Values used for option[n].val when option[n].type is SQLA_DEC_OPT.         */
#define SQLA_DEC_15            SQL_DEC_15        /* 15 bit precision is used  */
                                                 /* in decimal arithmetic     */
                                                 /* operations                */
#define SQLA_DEC_31            SQL_DEC_31        /* 31 bit precision is used  */
                                                 /* in decimal arithmetic     */
                                                 /* operations                */

/* Values used for option[n].val when option[n].type is SQLA_DEGREE_OPT.      */
#define SQLA_DEGREE_1          SQL_DEGREE_1      /* Prohibits parallel I/O    */
                                                 /* operations                */
#define SQLA_DEGREE_ANY        SQL_DEGREE_ANY    /* Allows the target         */
                                                 /* database system to        */
                                                 /* determine the degree of   */
                                                 /* parallel I/O operations   */
#define SQLA_MAX_DEGREE_VAL    SQL_MAX_DEGREE_VAL /* Maximum value            */

/* Values used for option[n].val when option[n].type is SQLA_CNULREQD_OPT in  */
/* the Precompiler Option array                                               */
#define SQLA_CNULREQD_NO       SQL_CNULREQD_NO   /* C NULL is not required    */
#define SQLA_CNULREQD_YES      SQL_CNULREQD_YES  /* C NULL is not required    */

/* Maximum sqlchar length for option[n].val when option[n].type is SQLA       */
/* GENERIC_OPT                                                                */
#define SQLA_MAX_GENERIC       SQL_MAX_GENERIC

/* Values used for option[n].val when option[n].type is SQLA_DEFERRED         */
/* PREPARE_OPT.                                                               */
#define SQLA_DEFERRED_PREPARE_YES SQL_DEFERRED_PREPARE_YES /* Enable          */
                                                 /* Deferred Prepare except   */
                                                 /* for a PREPARE...INTO      */
                                                 /* statement which contains  */
                                                 /* parameter markers.        */
#define SQLA_DEFERRED_PREPARE_NO SQL_DEFERRED_PREPARE_NO /* Disable Deferred  */
                                                 /* Prepare                   */
#define SQLA_DEFERRED_PREPARE_ALL SQL_DEFERRED_PREPARE_ALL /* Same as YES     */
                                                 /* except that a             */
                                                 /* PREPARE...INTO which      */
                                                 /* contains parameter        */
                                                 /* markers will also be      */
                                                 /* deferred                  */

/* Values used for option[n].val when option[n].type is SQLA_CONNECT_OPT.     */
#define SQLA_CONNECT_1         SQL_CONNECT_1     /* Indicates that only one   */
                                                 /* connection to a database  */
                                                 /* can exist at any given    */
                                                 /* time.                     */
#define SQLA_CONNECT_2         SQL_CONNECT_2     /* Indicates that multiple   */
                                                 /* connections can exist     */
                                                 /* simultaneously, with one  */
                                                 /* being active and the      */
                                                 /* others dormant.           */

/* Values used for option[n].val when option[n].type is SQLA_RULES_OPT.       */
#define SQLA_RULES_DB2         SQL_RULES_DB2     /* Indicates that CONNECT    */
                                                 /* TO can be used to make a  */
                                                 /* dormant connection the    */
                                                 /* current connection.       */
#define SQLA_RULES_STD         SQL_RULES_STD     /* Indicates that CONNECT    */
                                                 /* TO is not valid for       */
                                                 /* making a dormant          */
                                                 /* connection current,and    */
                                                 /* SET CONNECTION must be    */
                                                 /* used instead.             */
/* Values used for option[n].val when option[n].type is SQLA_DISCONNECT_OPT.  */
#define SQLA_DISCONNECT_EXPL   SQL_DISCONNECT_EXPL /* Indicates that all      */
                                                 /* connections marked by     */
                                                 /* the RELEASE statement     */
                                                 /* will be the only          */
                                                 /* connections released      */
                                                 /* when a COMMIT or          */
                                                 /* ROLLBACK is issued.       */
#define SQLA_DISCONNECT_COND   SQL_DISCONNECT_COND /* Indicates that all      */
                                                 /* connections which don't   */
                                                 /* have open WITH HOLD       */
                                                 /* cursors will be the only  */
                                                 /* connections released      */
                                                 /* when a COMMIT or          */
                                                 /* ROLLBACK is issued.       */
#define SQLA_DISCONNECT_AUTO   SQL_DISCONNECT_AUTO /* Indicates that all      */
                                                 /* connections will be       */
                                                 /* released when a COMMIT    */
                                                 /* or ROLLBACK is issued.    */

/* Values used for option[n].val when option[n].type is SQLA_SYNCPOINT_OPT.   */
#define SQLA_SYNC_ONEPHASE     SQL_SYNC_ONEPHASE /* Do not use a transaction  */
                                                 /* manager to perform two    */
                                                 /* phase commit,but enforce  */
                                                 /* that there is only one    */
                                                 /* database is updated when  */
                                                 /* multiple databases are    */
                                                 /* accessed within a single  */
                                                 /* transaction.              */
#define SQLA_SYNC_TWOPHASE     SQL_SYNC_TWOPHASE /* Use a transaction         */
                                                 /* manager to coordinate     */
                                                 /* two phase commit.         */
#define SQLA_SYNC_NONE         SQL_SYNC_NONE     /* No two-phase commit and   */
                                                 /* no single updater         */
                                                 /* enforcement.              */

/* Values used for option[n].val when option[n].type is SQLA_DYNAMICRULES     */
/* OPT.                                                                       */
#define SQLA_DYNAMICRULES_RUN  SQL_DYNAMICRULES_RUN /* Dynamic SQL in         */
                                                 /* package will use authid   */
                                                 /* of person running the     */
                                                 /* package                   */
#define SQLA_DYNAMICRULES_BIND SQL_DYNAMICRULES_BIND /* Dynamic SQL in        */
                                                 /* package will use authid   */
                                                 /* of person who owns the    */
                                                 /* package                   */

/* Values used for option[n].val when option[n].type is SQLA_FLAG_OPT inthe   */
/* Precompiler Option Array.                                                  */
#define SQLA_DB2V23_SYNTAX     SQL_MVSDB2V23_SYNTAX
#define SQLA_DB2V31_SYNTAX     SQL_MVSDB2V31_SYNTAX
#define SQLA_DB2V41_SYNTAX     SQL_MVSDB2V41_SYNTAX
#define SQLA_FIPS_SYNTAX       SQL_SQL92E_SYNTAX

/* Values used for option[n].val when option[n].type is SQLA_EXPLSNAP_OPT in  */
/* the Precompiler Option array                                               */
#define SQLA_EXPLSNAP_NO       SQL_EXPLSNAP_NO   /* Do not save explain       */
                                                 /* snapshot                  */
#define SQLA_EXPLSNAP_YES      SQL_EXPLSNAP_YES  /* Save explain snapshot     */
#define SQLA_EXPLSNAP_ALL      SQL_EXPLSNAP_ALL  /* Save explain snapshot     */
                                                 /* for all static and        */
                                                 /* dynamic statements        */

/* Maximum sqlchar length for option[n].val when option[n].type is SQLA       */
/* FUNCTION_PATH                                                              */
#define SQLA_MAX_FUNCPATH      SQL_MAX_FUNCPATH

/* Values used for option[n].val when option[n].type is SQLA_SQLWARN_OPT in   */
/* the Precompiler Option array                                               */
#define SQLA_SQLWARN_NO        SQL_SQLWARN_NO    /* Suppress prepare-time     */
                                                 /* warning SQLCODEs          */
#define SQLA_SQLWARN_YES       SQL_SQLWARN_YES   /* Permit prepare-time       */
                                                 /* warning SQLCODEs          */

/* Values used for option[n].val when option[n].type is SQLA_QUERYOPT_OPT in  */
/* the Precompiler Option array                                               */
#define SQLA_QUERYOPT_0        SQL_QUERYOPT_0    /* Class 0 query             */
                                                 /* optimization              */
#define SQLA_QUERYOPT_1        SQL_QUERYOPT_1    /* Class 1 query             */
                                                 /* optimization              */
#define SQLA_QUERYOPT_3        SQL_QUERYOPT_3    /* Class 3 query             */
                                                 /* optimization              */
#define SQLA_QUERYOPT_5        SQL_QUERYOPT_5    /* Class 5 query             */
                                                 /* optimization              */
#define SQLA_QUERYOPT_9        SQL_QUERYOPT_9    /* Class 9 query             */
                                                 /* optimization              */

/* Values used for option[n].val when option[n].type is SQLA_INSERT_OPT       */
#define SQLA_INSERT_DEF        SQL_INSERT_DEF    /* Do not buffer VALUE       */
                                                 /* inserts                   */
#define SQLA_INSERT_BUF        SQL_INSERT_BUF    /* Buffer VALUE inserts      */

/* Maximum target string length in option[n].val when option[n].type is SQLA  */
/* TARGET_OPT                                                                 */
#define SQLA_MAX_TARGET_LEN    SQL_MAX_TARGET_LEN

/* Values used for option[n].val when option[n].type is SQLA_STDS_LEVEL       */
/* inthe Precompiler Option Array.                                            */
#define SQLA_STND_NONE         0                 /* No compliance required    */
#define SQLA_STND_MIA          1                 /* Comply with MIA standard  */
#define SQLA_STND_SQL92E       2                 /* Comply with SQL92E        */
                                                 /* standard                  */

/* Values used for location, an input parameter of SQLAAHVR.                  */
#define SQLA_DECLARE_SECT      0       /* Add host var found in a declare     */
                                       /* section                             */
#define SQLA_SQL_STMT          1       /* Add host var found in an SQL        */
                                       /* statement                           */

/* Values assigned to task[n].func, an output parameter of SQLACMPL.          */
#define SQLA_START             0       /* Generate a call to sqlastrt         */
#define SQLA_DECLARE           1       /* Begin or end parsing hvar           */
                                       /* declarations                        */
#define SQLA_INCLUDE           2       /* Generate code for an SQLCA or       */
                                       /* SQLDA                               */
#define SQLA_ALLOC_INPUT       3       /* Allocate an input SQLDA using       */
                                       /* SQLAALOC                            */
#define SQLA_ALLOC_OUTPUT      4       /* Allocate an output SQLDA using      */
                                       /* SQLAALOC                            */
#define SQLA_SETS              5       /* Register a host variable using      */
                                       /* SQLASETS                            */
#define SQLA_USDA_INPUT        6       /* Register an input user-defined      */
                                       /* SQLDA                               */
#define SQLA_USDA_OUTPUT       7       /* Register an output user-defined     */
                                       /* SQLDA                               */
#define SQLA_CALL              8       /* Generate a call to SQLACALL         */
#define SQLA_DEALLOC           9       /* Generate a call to SQLADLOC         */
#define SQLA_STOP              10      /* Generate a call to SQLASTOP         */
#define SQLA_SQLERROR          11      /* Generate code for WHENEVER          */
                                       /* SQLERROR                            */
#define SQLA_SQLWARNING        12      /* Generate code for WHENEVER          */
                                       /* SQLWARNING                          */
#define SQLA_NOT_FOUND         13      /* Generate code for WHENEVER NOT      */
                                       /* FOUND                               */
#define SQLA_INC_TEXTFILE      14      /* Process an INCLUDE text-file stmt   */
#define SQLA_BEGIN_COMPOUND    15      /* Begin Compound SQL block            */
#define SQLA_CMPD              16      /* Generate a call to SQLACMPD         */
#define SQLA_CMPD_TEST         17      /* Generate a conditional branch       */
                                       /* around subsequent Compound SQL      */
                                       /* substatements.                      */
#define SQLA_CMPD_MARK         18      /* Generate a target label for gotos   */
                                       /* from cmpd_test (optional)           */
#define SQLA_NEXT_SUBSTATEMENT 19      /* Request the outer precompiler to    */
                                       /* get the next triggered SQL          */
                                       /* statement                           */
#define SQLA_SQLCODE_COPY      20      /* Generate code to copy SQLCODE       */
                                       /* SQLSTATE                            */

/* Values returned in task[n].val when task[n].func is SQLA_DECLARE.          */
/* This is an output parameter of SQLACMPL.                                   */
#define SQLA_BEGIN             0
#define SQLA_END               1

/* Values returned in task[n].val when task[n].func is SQLA_INCLUDE.          */
/* This is an output parameter of SQLACMPL.                                   */
#define SQLA_SQLCA             10
#define SQLA_SQLDA             11

/* Values returned in task[n].val when task[n].func is SQLA_CALL.             */
/* This is an output parameter of SQLACMPL.                                   */
#define SQLA_CLOSE             20
#define SQLA_COMMIT            21
#define SQLA_DESCRIBE          22
#define SQLA_EXECIMMD          23
#define SQLA_EXECUTE           24
#define SQLA_FETCH             25
#define SQLA_OPEN              26
#define SQLA_PREPARE           27
#define SQLA_ROLLBACK          28
#define SQLA_CONNECT           29
#define SQLA_CMPDEXEC          30      /* Atomic Compound SQL call            */
#define SQLA_FREE_LOB_LOCATORS 37      /* SQL free locators call              */
#define SQLA_CMPDEXEC_NA       38      /* Not Atomic Compound SQL call        */
#define SQLA_DUOW              40
#define SQLA_CLOSE_REL         41      /* Close Cursor with Release           */
#define SQLA_CALLPROC          42      /* Stored Procedure SQL call           */
#define SQLA_SET_CURRENT_PKGSET 43     /* Set Current Packageset              */
#define SQLA_EXECIMMD_ASYNC    44
#define SQLA_EXECUTE_ASYNC     45
#define SQLA_FETCH_ASYNC       46
#define SQLA_OPEN_ASYNC        47
#define SQLA_CALLPROC_ASYNC    48
#define SQLA_CMPDEXEC_ASYNC    49
#define SQLA_DESCRIBE_ASYNC    50
#define SQLA_PREPARE_ASYNC     51
#define SQLA_EXECIMMD_ASYNC_COMMIT 52
#define SQLA_EXECUTE_ASYNC_COMMIT 53
#define SQLA_CMPDEXEC_ASYNC_COMMIT 54
#define SQLA_EXECIMMD_COMMIT   55
#define SQLA_EXECUTE_COMMIT    56
#define SQLA_CMPDEXEC_COMMIT   57
#define SQLA_CMPDEXEC_NA_ASYNC 58
#define SQLA_CMPDEXEC_NA_COMMIT 59
#define SQLA_CMPDEXEC_NA_DIAG  60
#define SQLA_CMPDEXEC_NA_ASYNC_COMMIT 61
#define SQLA_CMPDEXEC_NA_ASYNC_DIAG 62
#define SQLA_CMPDEXEC_NA_COMMIT_DIAG 63
#define SQLA_CMPDEXEC_NA_A_C_D 64
#define SQLA_CLOSE_OPEN        65
#define SQLA_CLOSE_OPEN_ASYNC  66
#define SQLA_CLOSEREL_OPEN_ASYNC 67
#define SQLA_CLOSEREL_OPEN     68
#define SQLA_SETOPTION         69
#define SQLA_DESCRIBE_CURSOR   70
#define SQLA_DESCRIBE_CURSOR_ASYNC 71
#define SQLA_ARRAYINPUT        72
#define SQLA_ARRAYINPUT_ASYNC  73

/* Values returned in task[n].val when task[n].func is SQLA_SQLCODE_COPY.     */
/* This is an output parameter of SQLACMPL.                                   */
#define SQLA_SQLCODE           1       /* Copy SQLCODE and/or SQLSTATE        */
#define SQLA_SQLCODE_PREP_ERROR 2      /* Copy PREP errors                    */

/* Values assigned to token[n].use, an output parameter of SQLACMPL.          */
#define SQLA_INPUT_HVAR        0       /* Input host var, no indicator var    */
#define SQLA_INPUT_WITH_IND    1       /* Input host var followed by          */
                                       /* indicator var                       */
#define SQLA_OUTPUT_HVAR       2       /* Output host var, no indicator var   */
#define SQLA_OUTPUT_WITH_IND   3       /* Output host var followed by         */
                                       /* indicator var                       */
#define SQLA_INDICATOR         4       /* Indicator variable                  */
#define SQLA_USER_SQLDA        5       /* SQLDA structure                     */
#define SQLA_INVALID_USE       6       /* Host variable type does not match   */
                                       /* use                                 */
#define SQLA_INVALID_ID        7       /* Host variable token ID is not       */
                                       /* valid                               */
#define SQLA_LITERAL           8       /* Literal string                      */
#define SQLA_MULTIPLE_STRUCT_FIELD 9   /* Host var was one of several fields  */
                                       /* expanded from a structure           */
                                       /* reference                           */
#define SQLA_ATOMIC_FIELD      10      /* Host var was either atomic or a     */
                                       /* single field from a structure       */
                                       /* reference                           */

/* Values assigned to stmt_type, an output parameter of SQLACMPL.             */
#define SQLA_TYPE_NULL_CONNECT                   0
#define SQLA_TYPE_CONN_EXCL_NO_PWD               1
#define SQLA_TYPE_CONN_EXCL_PWD                  2
#define SQLA_TYPE_CONN_EXCL_NO_PWD_SN            91
#define SQLA_TYPE_CONN_EXCL_PWD_SN               92
#define SQLA_TYPE_CONNECT_RESET                  3
#define SQLA_TYPE_CONN_SHARE_NO_PWD              4
#define SQLA_TYPE_CONN_SHARE_PWD                 5
#define SQLA_TYPE_CONNECT_USERID                 6
#define SQLA_TYPE_BEGIN                          10
#define SQLA_TYPE_BEGIN_COMPOUND                 12
#define SQLA_TYPE_CALLPROC                       13
#define SQLA_TYPE_CLOSE                          15
#define SQLA_TYPE_COMMIT                         20
#define SQLA_TYPE_CONNECT_1                      21
#define SQLA_TYPE_CONNECT_2                      22
#define SQLA_TYPE_DISCONNECT_DBNAME              23
#define SQLA_TYPE_DISCONNECT_CURRENT             24
#define SQLA_TYPE_DISCONNECT_ALL                 25
#define SQLA_TYPE_RELEASE_DBNAME                 26
#define SQLA_TYPE_RELEASE_CURRENT                27
#define SQLA_TYPE_RELEASE_ALL                    28
#define SQLA_TYPE_SET_CONNECTION                 29
#define SQLA_TYPE_DECLARE_SELECT                 30
#define SQLA_TYPE_DECLARE_SNAME                  40
#define SQLA_TYPE_ALLOCATE_CURSOR                45
#define SQLA_TYPE_DESCRIBE                       50
#define SQLA_TYPE_DESCRIBE_CURSOR                55
#define SQLA_TYPE_END                            60
#define SQLA_TYPE_END_COMPOUND                   65
#define SQLA_TYPE_EXECUTE                        70
#define SQLA_TYPE_EXECUTE_IMM                    80
#define SQLA_TYPE_FETCH                          90
#define SQLA_TYPE_FREE_LOB_LOCATOR               95
#define SQLA_TYPE_INCLUDE_SQLCA                  100
#define SQLA_TYPE_INCLUDE_SQLDA                  110
#define SQLA_TYPE_INCLUDE_TEXTFILE               115
#define SQLA_TYPE_OPEN                           120
#define SQLA_TYPE_PREPARE                        130
#define SQLA_TYPE_ROLLBACK                       140
#define SQLA_TYPE_SELECT                         150
#define SQLA_TYPE_SELECT_INTO                    160
#define SQLA_TYPE_SET_CURRENT_PKGSET             163
#define SQLA_TYPE_WHEN_NOT_FOUND                 170
#define SQLA_TYPE_WHEN_SQLERROR                  180
#define SQLA_TYPE_WHEN_SQLWARNING                190
#define SQLA_TYPE_OTHER                          200

/* Values used for term_option, an input parameter of SQLAFINI.               */
#define SQLA_SAVE              1       /* Save the access plan and/or bind    */
                                       /* file                                */
#define SQLA_DISCARD           0       /* Discard the access plan and/or      */
                                       /* bind file                           */

/* Miscellaneous Constants                                                    */

#define SQL_MAX_FILE_NAME_LENGTH 128   /* size of SQLAINIT file name buffer   */

#define SQL_CMPL_BUFSIZ        256     /* size of SQLACMPL output buffers     */
#define SQL_PID_LENGTH         40      /* length of precompiler pid           */
#define SQLA_FLAG_MAXMSGS      10      /* Message array length same as SQLH   */
                                       /* MAXMSGS                             */
#define SQLA_FLAG_VERSION      1       /* Current SQL Flagger version         */

/* Return codes from Precompiler Services and Runtime Services functions.     */
#define SQLA_SQLCA_BAD         -1      /* sqlca pointer/length invalid        */
#define SQLA_CHECK_SQLCA       0       /* check sqlca completion status       */

/* Values returned in sqlca.sqlcode by Precompiler or Runtime Services        */
#define SQLA_RC_OK                     SQL_RC_OK
#define SQLA_RC_OPTION_IGNORED         20
#define SQLA_RC_CHAR_BAD               SQL_RC_E007
#define SQLA_RC_STRING_NOT_TERMINATED  SQL_RC_E010
#define SQLA_RC_EMPTY_DEL_IDENT        SQL_RC_E013
#define SQLA_RC_BFILE_OPEN_ERROR       -31
#define SQLA_RC_BFILE_DISK_ERROR       -32
#define SQLA_RC_SECTION_LIMIT          -51
#define SQLA_RC_MEMORY_BAD             -83
#define SQLA_RC_SNAME_DUP              -85
#define SQLA_RC_NO_STRUCT              -87
#define SQLA_RC_AMBIG_HOSTVAR          -88
#define SQLA_RC_STMT_LIMIT             SQL_RC_E101
#define SQLA_RC_NUMBER_BAD             SQL_RC_E103
#define SQLA_RC_STMT_SYNTAX_BAD        SQL_RC_E104
#define SQLA_RC_GSTRING_BAD            SQL_RC_E105 /* DBCS only               */
#define SQLA_RC_IDENTIFIER_LIMIT       SQL_RC_E107
#define SQLA_RC_QUALIFIER_BAD          SQL_RC_E108
#define SQLA_RC_DDSBAD                 SQL_RC_E142
#define SQLA_RC_DDSIGN                 SQL_RC_W143
#define SQLA_RC_DDSWRN                 SQL_RC_W143
#define SQLA_RC_STMT_IGNORED           SQL_RC_W143
#define SQLA_RC_KEYWORD_BAD            SQL_RC_E199
#define SQLA_RC_HVAR_NOT_DEC           -306
#define SQLA_RC_HVAR_DUP_NAME          -307
#define SQLA_RC_HVAR_LIMIT             -308
#define SQLA_RC_STMT_HVAR_LIMIT        -310
#define SQLA_RC_HVAR_USE_BAD           -324
#define SQLA_RC_CURSOR_DUP             -505
#define SQLA_RC_STMT_MODIFY_ALL        513
#define SQLA_RC_INVALID_TRIGGER_STMT   SQL_RC_E751
#define SQLA_RC_SQLDA_SQLD_ERR         SQL_RC_E804
#define SQLA_RC_SQLVAR_TYPE_ERR        SQL_RC_E804
#define SQLA_RC_DISK_FULL              SQL_RC_E968
#define SQLA_RC_CMPD_NESTED            -4010
#define SQLA_RC_CMPD_INVALID_STMT      -4011
#define SQLA_RC_CMPD_INVALID_COMMIT    -4012
#define SQLA_RC_CMPD_INVALID_END       -4013
#define SQLA_RC_INVALID_CMPD_SYNTAX    -4014
#define SQLA_RC_FATAL_ERROR            -4901
#define SQLA_RC_PARM_CHARS_BAD         -4902
#define SQLA_RC_PARM_LENGTH_BAD        SQLA_RC_OPTION_LEN_BAD
#define SQLA_RC_PARM_POINTER_BAD       SQLA_RC_OPTION_PTR_BAD
#define SQLA_RC_PARM_RANGE_BAD         SQLA_RC_OPTION_SIZE_BAD
#define SQLA_RC_HVAR_SQLTYPE_BAD       -4911
#define SQLA_RC_HVAR_SQLLEN_BAD        -4912
#define SQLA_RC_HVAR_TOKEN_ID_DUP      -4913
#define SQLA_RC_HVAR_TOKEN_ID_BAD      -4914
#define SQLA_RC_INIT_DUP               -4915
#define SQLA_RC_INIT_REQUIRED          -4916
#define SQLA_RC_OPTION_BAD             SQLA_RC_OPTION_DATA_BAD
#define SQLA_RC_TERM_OPTION_BAD        -4918
#define SQLA_RC_TASK_ARRAY_LIMIT       -4919
#define SQLA_RC_TOKEN_ARRAY_LIMIT      -4920
#define SQLA_RC_OPTION_GEN_INVALID     SQLA_RC_OPTION_INVALID
#define SQLA_RC_STMT_CLAUSE_BAD        -4940       /* Prep version of -109    */
#define SQLA_RC_STMT_BLANK             -4941       /* Prep version of -198    */
#define SQLA_RC_SELECT_HVAR_TYPE_BAD   -4942       /* Prep version of -303    */
#define SQLA_RC_SELECT_LIST_BAD        4943        /* Prep version of -313    */
#define SQLA_RC_COLUMN_NOT_NULLABLE    -4944       /* Prep version of -407    */
#define SQLA_RC_STMT_MARKER_BAD        -4945       /* Prep version of -418    */
#define SQLA_RC_CURSOR_NOT_DECLARED    -4946       /* Prep version of -504    */
#define SQLA_RC_NO_USERDA_IN_CMPD      -4950
#define SQLA_RC_SQLDA_ID_BAD           -4951
#define SQLA_RC_SQLVAR_INDEX_BAD       -4952
#define SQLA_RC_CALL_TYPE_BAD          -4953
#define SQLA_RC_SECTION_BAD            -4954

/* Temporary value used in sqlca.sqlcode after an SQLAALOC function. Runtime  */
/* code can check sqlca.sqlcode to determine whether or not the SQLASETV      */
/* function needs to be called to initialize the sqlda sqlvar elements.       */
#define SQLA_RC_SQLVARS_SET    4959    /* sqlvars already initialized         */

/* Errors that cause Precompiler Services to enter the fatal error state.     */
/* After encountering one of these types of errors, Precompiler Services      */
/* requires an SQLAFINI and SQLAINIT call before it will continue.            */

#define SQLA_RC_INV_INSERT               SQL_RC_E803
#define SQLA_RC_INV_SQLDA_ADR            SQL_RC_E822
#define SQLA_RC_SYS_ERROR                SQL_RC_E902
#define SQLA_RC_DEADLOCK_ERR             SQL_RC_E911
#define SQLA_RC_FAT_SYS_ERR              SQL_RC_E912
#define SQLA_RC_TOO_MANY_LKS             SQL_RC_E930
#define SQLA_RC_STORAGE_ERR              SQL_RC_E954
#define SQLA_RC_DB_HEAP_ERR              SQL_RC_E956
#define SQLA_RC_TOOMANY_OFLS             SQL_RC_E958
#define SQLA_RC_TOOMANY_FILES            SQL_RC_E960
#define SQLA_RC_LOG_FULL                 SQL_RC_E964
#define SQLA_RC_FILE_SYS_FULL            SQL_RC_E968
#define SQLA_RC_READ_ONLY_FIL            SQL_RC_E970

#define SQLA_RC_INCORRECT_DSK            -972
#define SQLA_RC_DB_DRV_LOCKED            -974
#define SQLA_RC_DRV_DOOR_OPEN            -976
#define SQLA_RC_DISK_WRT_PRO             -978
#define SQLA_RC_FILESYSTEM_ACCESS        -10019

#define SQLA_RC_DISK_ERROR               SQL_RC_E980
#define SQLA_RC_DISK_ERR                 SQL_RC_E982
#define SQLA_RC_COMM_RB_ERR              SQL_RC_E984
#define SQLA_RC_CAT_FILE_ERR             SQL_RC_E985
#define SQLA_RC_TAB_FILE_ERR             SQL_RC_E986
#define SQLA_RC_INDEX_ERR                SQL_RC_E990
#define SQLA_RC_REL_NUM_BAD              SQL_RC_E992
#define SQLA_RC_AGENT_GONE               SQLE_RC_AGENT_GONE
#define SQLA_RC_CTRL_BREAK               -4994   /* Prep version of -952      */
#define SQLA_RC_CODEPAGE_BAD             -4995   /* Country info not found    */
#define SQLA_RC_SQLUSER_BAD              -4997   /* Prep version of -1046     */
#define SQLA_RC_DB_DISCONNECTED          -4998   /* Prep version of -1049     */
#define SQLA_RC_INTERNAL_ERR             -4999   /* Precompiler Services err  */

/******************************************************************************
** NOTE: sqlaopts has been obsoleted in favor of sqlaoptions.  sqlaopts will
**  be unavailable in future releases
** .*******************************************************************************/

/******************************************************************************
** Target API constants for sqlaopts()
*******************************************************************************/
#define SQLAO_PREP_SVCS_API              0       /* Precompiler Services API  */
                                                 /* (sqlainit)                */

SQL_API_RC SQL_API_FN                            /* Parse an option string    */
                                                 /* and produce an option     */
                                                 /* array                     */
  sqlaopts (
        void *,                                  /* option string             */
        struct sqlopt *,                         /* option array              */
        void *,                                  /* database name (sqlainit   */
                                                 /* only)                     */
        void *,                                  /* userid (sqlainit only)    */
        void *,                                  /* password (sqlainit only)  */
        void *,                                  /* message file name         */
        void *,                                  /* package name (sqlainit    */
                                                 /* only)                     */
        void *,                                  /* bind file name (sqlainit  */
                                                 /* only)                     */
        long,                                    /* target API                */
        void **,                                 /* memory handle             */
        struct sqlca *);                         /* SQLCA                     */

/******************************************************************************
** NOTE: sqlaopts_free has been obsoleted in favor of sqlaoptions_free.
** sqlaopts_free will be unavailable in future releases.
*******************************************************************************/

SQL_API_RC SQL_API_FN                            /* Frees any memory          */
                                                 /* allocated by sqlaopts     */
  sqlaopts_free (
        void *,                                  /* memory handle returned    */
                                                 /* by sqlaopts               */
        struct sqlca *);                         /* SQLCA                     */

SQL_API_RC SQL_API_FN                            /* Parse an option string    */
                                                 /* and produce an option     */
                                                 /* array                     */
  sqlaoptions (
        void *,                                  /* option string             */
        struct sqlopt *,                         /* option array              */
        short *,                                 /* database name length      */
                                                 /* (sqlainit only)           */
        char **,                                 /* database name (sqlainit   */
                                                 /* only)                     */
        short *,                                 /* userid length (sqlainit   */
                                                 /* only)                     */
        char **,                                 /* userid (sqlainit only)    */
        short *,                                 /* password length           */
                                                 /* (sqlainit only)           */
        char **,                                 /* password (sqlainit only)  */
        short *,                                 /* message file name length  */
        char **,                                 /* message file name         */
        short *,                                 /* package name length       */
        char **,                                 /* package name              */
        short *,                                 /* bind file name length     */
        char **,                                 /* bind file name            */
        long,                                    /* target API                */
        void **,                                 /* memory handle             */
        struct sqlca *);                         /* SQLCA                     */

SQL_API_RC SQL_API_FN                            /* Frees any memory          */
                                                 /* allocated by sqlaoptions  */
  sqlaoptions_free (
        void *,                                  /* memory handle returned    */
                                                 /* by sqlaoptions            */
        struct sqlca *);                         /* SQLCA                     */

/******************************************************************************
** Precompiler Services Structures
*******************************************************************************/

/* Precompiler Option Array.  Used with SQLAINIT.                             */

SQL_STRUCTURE sqla_options_header
{
        unsigned long               allocated;
        unsigned long               used;
};

SQL_STRUCTURE sqla_option
{
        unsigned long               type;
        unsigned long               val;
};

SQL_STRUCTURE sqla_options
{
        struct sqla_options_header  header;
        struct sqla_option          option[1];
};

/* Program ID.  Used by Precompiler Services and Runtime Services             */
SQL_STRUCTURE sqla_program_id
{
        unsigned short    length;
        unsigned short    rp_rel_num;
        unsigned short    db_rel_num;
        unsigned short    bf_rel_num;
        char              sqluser[8];
        char              planname[8];
        char              contoken[8];
        char              buffer[8];
};

/* Indexes into the buffer field, showing the information it provides         */
#define SQLA_PGMID_STD         0
#define SQLA_PGMID_CONNECT     1
#define SQLA_PGMID_SQLRULES    2
#define SQLA_PGMID_DISCONNECT  3
#define SQLA_PGMID_SYNCPOINT   4
#define SQLA_PGMID_DEFERRED_PREPARE 5
#define SQLA_INT_TO_ASCII_DIFF 48

/* Number of DUOW connection options                                          */
#define SQLA_PGMID_CONNOPTS    4

/* Precompiler Task Array.  Used with SQLACMPL.                               */

SQL_STRUCTURE sqla_tasks_header
{
        unsigned long               allocated;
        unsigned long               used;
};

SQL_STRUCTURE sqla_task
{
        unsigned long               func;
        unsigned long               val;
};

SQL_STRUCTURE sqla_tasks
{
        struct sqla_tasks_header    header;
        struct sqla_task            task[1];
};

/* Token return structure.  Used to return length and offset of               */
/* a token within an SQL statement.  May be overlaid on top of                */
/* the val member of the task array or on top of the id member                */
/* of the token id array.                                                     */
SQL_STRUCTURE sqla_return_token
{
        unsigned short    offset;
        unsigned short    length;
};

/* Precompiler Token ID Array.  Used with SQLACMPL.                           */

SQL_STRUCTURE sqla_tokens_header
{
        unsigned long               allocated;
        unsigned long               used;
};

SQL_STRUCTURE sqla_token
{
        unsigned long               id;
        unsigned long               use;
};

SQL_STRUCTURE sqla_tokens
{
        struct sqla_tokens_header   header;
        struct sqla_token           token[1];
};

/* Flagger information area. Used with SQLACMPL and SQLGCMPL.                 */
SQL_STRUCTURE sqla_flagmsgs
{
        short             count;
        short             padding;
        SQL_STRUCTURE sqlca sqlca[SQLA_FLAG_MAXMSGS];
};

SQL_STRUCTURE sqla_flaginfo
{
        short             version;
        short             padding;
        struct            sqla_flagmsgs msgs;
};
/* Precompiler Services Prototypes                                            */

/* NOTE: sqlaahvr has been obsoleted in favor of sqlaalhv.  sqlaahvr will be  */
/* unavailable in future releases.                                            */
SQL_API_RC SQL_API_FN                      /* Add a host variable             */
                                           /* declaration (obsolete)          */
  sqlaahvr (
        unsigned short *,                  /* host variable name length       */
        char *,                            /* host variable name              */
        unsigned short *,                  /* host variable SQL data type     */
        unsigned short *,                  /* host variable length            */
        unsigned long *,                   /* host variable token id          */
        unsigned short *,                  /* host variable location          */
        void *,                            /* reserved                        */
        struct sqlca *);                   /* SQLCA                           */

SQL_API_RC SQL_API_FN                      /* Add a host variable             */
                                           /* declaration                     */
  sqlaalhv (
        unsigned short *,                  /* host variable name length       */
        char *,                            /* host variable name              */
        unsigned short *,                  /* host variable SQL data type     */
        unsigned long *,                   /* host variable length            */
        unsigned long *,                   /* host variable token id          */
        unsigned short *,                  /* host variable location          */
        void *,                            /* reserved                        */
        struct sqlca *);                   /* SQLCA                           */

SQL_API_RC SQL_API_FN                      /* Compile an sql statement        */
  sqlacmpl (
        unsigned short *,                  /* SQL statement text length       */
        char *,                            /* SQL statement text              */
        unsigned short *,                  /* source line number              */
        struct sqla_tasks *,               /* task array                      */
        struct sqla_tokens *,              /* token id array                  */
        unsigned short *,                  /* section number                  */
        unsigned short *,                  /* type of SQL statement           */
        char *,                            /* 128 byte string buffer 1        */
        char *,                            /* 128 byte string buffer 2        */
        char *,                            /* 128 byte string buffer 3        */
        struct sqla_flaginfo *,            /* SQL Flagger information         */
        struct sqlca *);                   /* SQLCA                           */

SQL_API_RC SQL_API_FN                      /* Terminate an access plan        */
  sqlafini (
        unsigned short *,                  /* save/discard plan/bind file     */
        void *,                            /* reserved                        */
        struct sqlca *);                   /* SQLCA                           */

SQL_API_RC SQL_API_FN                      /* Initialize an access plan       */
  sqlainit (
        unsigned short *,                  /* program name length             */
        char *,                            /* program name                    */
        unsigned short *,                  /* database name length            */
        char *,                            /* database name                   */
        unsigned short *,                  /* password length                 */
        char *,                            /* database password               */
        unsigned short *,                  /* bind file name length           */
        char *,                            /* bind file name                  */
        struct sqla_options *,             /* precompiler option array        */
        struct sqla_program_id *,          /* precompiler program ID          */
        void *,                            /* reserved                        */
        struct sqlca *);                   /* SQLCA                           */

/* Generic Precompiler Services Prototypes                                    */

/* NOTE: sqlgahvr has been obsoleted in favor of sqlgalhv.  sqlgahvr will be  */
/* unavailable in future releases.                                            */
SQL_API_RC SQL_API_FN                      /* Add a host variable             */
                                           /* declaration (obsolete)          */
  sqlgahvr (
        unsigned short *,                  /* host variable name length       */
        char *,                            /* host variable name              */
        unsigned short *,                  /* host variable SQL data type     */
        unsigned short *,                  /* host variable length            */
        unsigned long *,                   /* host variable token id          */
        unsigned short *,                  /* host variable location          */
        void *,                            /* reserved                        */
        struct sqlca *);                   /* SQLCA                           */

SQL_API_RC SQL_API_FN                      /* Add a host variable             */
                                           /* declaration                     */
  sqlgalhv (
        unsigned short *,                  /* host variable name length       */
        char *,                            /* host variable name              */
        unsigned short *,                  /* host variable SQL data type     */
        unsigned long *,                   /* host variable length            */
        unsigned long *,                   /* host variable token id          */
        unsigned short *,                  /* host variable location          */
        void *,                            /* reserved                        */
        struct sqlca *);                   /* SQLCA                           */

SQL_API_RC SQL_API_FN                      /* Compile an sql statement        */
  sqlgcmpl (
        unsigned short *,                  /* SQL statement text length       */
        char *,                            /* SQL statement text              */
        unsigned short *,                  /* source line number              */
        struct sqla_tasks *,               /* task array                      */
        struct sqla_tokens *,              /* token id array                  */
        unsigned short *,                  /* section number                  */
        unsigned short *,                  /* type of SQL statement           */
        char *,                            /* 128 byte string buffer 1        */
        char *,                            /* 128 byte string buffer 2        */
        char *,                            /* 128 byte string buffer 3        */
        struct sqla_flaginfo *,            /* SQL Flagger information         */
        struct sqlca *);                   /* SQLCA                           */

SQL_API_RC SQL_API_FN                      /* Terminate an access plan        */
  sqlgfini (
        unsigned short *,                  /* save/discard plan/bind file     */
        void *,                            /* reserved                        */
        struct sqlca *);                   /* SQLCA                           */

SQL_API_RC SQL_API_FN                      /* Initialize an access plan       */
  sqlginit (
        unsigned short *,                  /* program name length             */
        char *,                            /* program name                    */
        unsigned short *,                  /* database name length            */
        char *,                            /* database name                   */
        unsigned short *,                  /* password length                 */
        char *,                            /* database password               */
        unsigned short *,                  /* bind file name length           */
        char *,                            /* bind file name                  */
        struct sqla_options *,             /* precompiler option array        */
        struct sqla_program_id *,          /* precompiler program ID          */
        void *,                            /* reserved                        */
        struct sqlca *);                   /* SQLCA                           */

/* Generic Runtime Services Prototypes                                        */

SQL_API_RC SQL_API_FN
  sqlgaloc (
        unsigned short,                    /* sqlda identification number     */
        unsigned short,                    /* number of sqlvar elements       */
                                           /* needed                          */
        unsigned short,                    /* statement identification        */
                                           /* number                          */
        void *);                           /* reserved                        */

SQL_API_RC SQL_API_FN
  sqlgcall (
        unsigned short,                    /* function call type              */
        unsigned short,                    /* access plan section or          */
                                           /* statement type                  */
        unsigned short,                    /* input SQLDA ID                  */
        unsigned short,                    /* output SQLDA ID                 */
        void *);                           /* reserved                        */

SQL_API_RC SQL_API_FN
  sqlgcmpd (
        unsigned short,                    /* function call type              */
        unsigned short,                    /* access plan section             */
        unsigned short,                    /* input SQLDA ID                  */
        unsigned short,                    /* output SQLDA ID                 */
        void *);                           /* reserved                        */

SQL_API_RC SQL_API_FN
  sqlgdloc (
        unsigned short,                    /* SQLDA ID                        */
        void *);                           /* reserved                        */

/* NOTE: sqlgsets has been obsoleted in favor of sqlgstls.  sqlgsets will be  */
/* unavailable in future releases.                                            */
SQL_API_RC SQL_API_FN
  sqlgsets (
        unsigned short,                    /* SQL statement text length       */
        const void *,                      /* SQL statement text              */
        void *);                           /* reserved                        */

SQL_API_RC SQL_API_FN
  sqlgstls (
        unsigned long,                     /* SQL statement text length       */
        const void *,                      /* SQL statement text              */
        void *);                           /* reserved                        */

/* NOTE: sqlgsetv has been obsoleted in favor of sqlgstlv.  sqlgsetv will be  */
/* unavailable in future releases.                                            */
SQL_API_RC SQL_API_FN
  sqlgsetv (
        unsigned short,                    /* SQLDA ID                        */
        unsigned short,                    /* sqlvar element                  */
        unsigned short,                    /* SQL data type                   */
        unsigned short,                    /* declared length                 */
        void *,                            /* address of host var             */
        short *,                           /* address of indicator var        */
        void *);                           /* reserved                        */

SQL_API_RC SQL_API_FN
  sqlgstlv (
        unsigned short,                    /* SQLDA ID                        */
        unsigned short,                    /* sqlvar element                  */
        unsigned short,                    /* SQL data type                   */
        unsigned long,                     /* declared length                 */
        void *,                            /* address of host var             */
        short *,                           /* address of indicator var        */
        void *);                           /* reserved                        */

SQL_API_RC SQL_API_FN
  sqlgstop (
        void *);                           /* reserved                        */

SQL_API_RC SQL_API_FN
  sqlgstrt (
        char[40],                          /* runtime program ID              */
        struct sqla_runtime_info *,        /* runtime information             */
        struct sqlca *);                   /* SQLCA                           */

SQL_API_RC SQL_API_FN
  sqlgusda (
        unsigned short,                    /* SQLDA ID                        */
        struct sqlda *,                    /* SQLDA                           */
        void *);                           /* reserved                        */

/******************************************************************************
** NOTE: sqlgopts has been obsoleted in favor of sqlgoptions.  sqlgopts will
**  be unavailable in future releases.
*******************************************************************************/

SQL_API_RC SQL_API_FN                      /* Parse an option string and      */
                                           /* produce an option array         */
  sqlgopts (
        void *,                            /* option string                   */
        struct sqlopt *,                   /* option array                    */
        void *,                            /* database name (sqlginit only)   */
        void *,                            /* userid (sqlginit only)          */
        void *,                            /* password (sqlginit only)        */
        void *,                            /* message file name               */
        void *,                            /* package name (sqlginit only)    */
        void *,                            /* bind file name (sqlginit only)  */
        long,                              /* target API                      */
        void **,                           /* memory handle                   */
        struct sqlca *);                   /* SQLCA                           */

/******************************************************************************
** NOTE: sqlgopts_free has been obsoleted in favor of sqlgoptions_free.
**  sqlgopts will be unavailable in future releases.
*******************************************************************************/

SQL_API_RC SQL_API_FN                      /* Frees any memory allocated by   */
                                           /* sqlgopts                        */
  sqlgopts_free (
        void *,                            /* memory handle returned by       */
                                           /* sqlgopts                        */
        struct sqlca *);                   /* SQLCA                           */

SQL_API_RC SQL_API_FN                      /* Parse an option string and      */
                                           /* produce an option array         */
  sqlgoptions (
        void *,                            /* option string                   */
        struct sqlopt *,                   /* option array                    */
        short *,                           /* database name length (sqlginit  */
                                           /* only)                           */
        char **,                           /* database name (sqlginit only)   */
        short *,                           /* userid length (sqlginit only)   */
        char **,                           /* userid (sqlginit only)          */
        short *,                           /* password length (sqlginit       */
                                           /* only)                           */
        char **,                           /* password (sqlginit only)        */
        short *,                           /* message file name length        */
        char **,                           /* message file name               */
        short *,                           /* package name length             */
        char **,                           /* package name                    */
        short *,                           /* bind file name length           */
        char **,                           /* bind file name                  */
        long,                              /* target API                      */
        void **,                           /* memory handle                   */
        struct sqlca *);                   /* SQLCA                           */

SQL_API_RC SQL_API_FN                      /* Frees any memory allocated by   */
                                           /* sqlgoptions                     */
  sqlgoptions_free (
        void *,                            /* memory handle returned by       */
                                           /* sqlgoptions                     */
        struct sqlca *);                   /* SQLCA                           */

#pragma pack()

#ifdef __cplusplus 
}
#endif

#endif /* SQL_H_SQLAPREP */
