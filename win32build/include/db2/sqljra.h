/******************************************************************************
 *
 * Source File Name = SQLJRA.H
 *
 * (C) COPYRIGHT International Business Machines Corp. 1991, 1995
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * Function = Include File defining:
 *              Database Connection Services (DCS) Interface Constants
 *              DCS Interface Return Codes
 *              SQLJRA and Other Related DCS Interface Structures
 *
 * Operating System = Common C Include File
 *
 *****************************************************************************/

#ifndef SQL_H_SQLJRA
   #define SQL_H_SQLJRA                    /* Permit duplicate Includes      */

#include "sqlsystm.h"                      /* Provides _SQLOLDCHAR           */

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

/* Service type */

#define  SQLJ_DCSSV                 1      /* Connection Services            */
#define  SQLJ_DBSV                  2      /* Database Services              */

/* Connection Service request types */

#define   SQLJR_NOOP                0      /* Reserved (No-op)               */
#define   SQLJR_STOPGW              1      /* Stop Database function         */
#define   SQLJR_INT                 2      /* Interrupt the request          */
#define   SQLJR_STARTGW             3      /* Start Database Connection      */
#define   SQLJR_RPC                 4      /* Application Remote Interface   */
#define   SQLJR_RESET               5      /* Reset database state           */
#define   SQLJR_CS_MAXOP            6      /* Highest Valid Request + 1      */

/* Database Services request types */

#define   SQLJR_PREPINIT            1      /* Precompiler/Binder
                                              Initialization                 */
#define   SQLJR_PREPFINI            2      /* Precompiler/Binder Termination */
#define   SQLJR_COMPILE             3      /* Compile                        */
#define   SQLJR_FREEDA              4      /* Free SQLDA                     */
#define   SQLJR_OPEN                5      /* Open Cursor                    */
#define   SQLJR_FETCH               6      /* Fetch with Cursor              */
#define   SQLJR_CLOSE               7      /* Close Cursor                   */
#define   SQLJR_EXECUTE             8      /* Execute                        */
#define   SQLJR_PREPARE             9      /* Prepare                        */
#define   SQLJR_EXECIMMD            10     /* Execute Immediate              */
#define   SQLJR_COMMIT              11     /* Commit                         */
#define   SQLJR_ROLLBACK            12     /* Rollback                       */
#define   SQLJR_RUNSTATS            13     /* Runstats                       */
#define   SQLJR_PREREORG            14     /* Reserved for Database Manager
                                              use only                       */
#define   SQLJR_DESCRIBE            15     /* Describe                       */
#define   SQLJR_RQSVPT              17     /* Request Savepoint              */
#define   SQLJR_ENSVPT              18     /* End Savepoint                  */
#define   SQLJR_RBSVPT              19     /* Rollback Savepoint             */
#define   SQLJR_GETAA               20     /* Reserved for Database Manager
                                              use only                       */
#define   SQLJR_NOT_USED            21     /* Not used                       */
#define   SQLJR_REORG               22     /* Reserved for Database Manager
                                              use only                       */
#define   SQLJR_GETTA               23     /* Get Table/View Authorizations  */
#define   SQLJR_CMPNDSQL            24     /* Compund SQL request.           */
                                           /* XA defines in here.            */
#define   SQLJR_XRECOVER            25     /* XA Recover  request.           */
#define   SQLJR_XFORGET             26     /* XA Forget   request.           */
#define   SQLJR_XPREPARE            27     /* XA Prepare  request.           */
#define   SQLJR_XCOMMIT             28     /* XA Commit   request.           */
#define   SQLJR_XROLLBACK           29     /* XA Rollback request.           */
#define   SQLJR_XEND                30     /* XA End      request.           */
#define   SQLJR_XREG                31     /* XA Register request.           */

#define   SQLJR_FREE_HANDLES        32     /* Free BLOB handles (Temporary)  */

#define   SQLJR_CMPNDSQL_NA         33     /* Not Atomic Compound SQL.       */

#define   SQLJR_REBIND              34     /* Rebind package    (Temporary)  */
#define   SQLJR_INTDESC             35     /* Internal Describe (Temporary)  */
#define   SQLJR_TRUNC_TABLE         37     /* Truncate table                 */
#define   SQLJR_DS_MAXOP            38     /* Highest Valid Request + 1      */


/* DCS Interface Positive Return Codes  returned to and by sqledcsr          */

#define   SQLJR_RCF_OK          0x0000     /* Successful Execution           */
#define   SQLJR_RCF_COMMIT      0x0001     /* Commit Performed               */
#define   SQLJR_RCF_ROLLBACK    0x0002     /* Rollback Performed             */
#define   SQLJR_RCF_CLOSED      0x0004     /* Cursors Closed                 */
#define   SQLJR_RCF_HOLD        0x0008     /* Cursor has Hold option         */
#define   SQLJR_RCF_BLOCK       0x0010     /* Cursor can be blocked          */
#define   SQLJR_RCF_NOBLK       0x0020     /* Cursor cannot be blocked       */
#define   SQLJR_RCF_SQLCA       0x0040     /* SQLCA Modified                 */
#define   SQLJR_RCF_FETCHERR    0x0080     /* Cursor closed on fetch         */
#define   SQLJR_RCF_TERMINATE   0x0100     /* Database Connection Terminated */
#define   SQLJR_RCF_SECURITY    0x0200     /* Security error                 */
#define   SQLJR_RCF_FORCE_RLBK  0x0400     /* Forced rollback                */
#define   SQLJR_RCF_END         0x0800     /* XA End                         */
#define   SQLJR_RCF_OPEN        0x1000     /* Cursor already open            */

/* Number of triplets in sqljra */

#define   SQLJCSRA_DATA_ITEMS        5 /* Default Connection Services         */
#define   SQLJDSRA_DATA_ITEMS        9 /* Default Database Services           */
                                       /* STARTGW_DATA_ITEMS from 5.          */
#define   SQLJR_STARTGW_DATA_ITEMS   6 /* Extra triplets for STARTGW          */
#define   SQLJR_MAX_DATA_ITEMS      11 /* Maximum triplets for any request    */

/* Data types */

#define   SQLJ_TYP_CHAR         1      /* Fixed length character string       */
#define   SQLJ_TYP_INTEGER      2      /* 4 byte unsigned short               */
#define   SQLJ_TYP_SMALL        3      /* 2 byte unsigned long                */
#define   SQLJ_TYP_BIN          4      /* Fixed length binary data            */
#define   SQLJ_TYP_INSQLDA      5      /* Input SQLDA                         */
#define   SQLJ_TYP_OUTSQLDA     6      /* Output SQLDA                        */
#define   SQLJ_TYP_INHV         7      /* In SQLDA for host var description.  */
#define   SQLJ_TYP_OUTHV        8      /* Out SQLDA for host var description. */
#define   SQLJ_TYP_SQLCA        9      /* SQLCA                               */
#define   SQLJ_TYP_BNDOPT      10      /* Bind option array                   */
#define   SQLJ_TYP_CSTRING     11      /* Null-terminated char string.        */
#define   SQLJ_TYP_DBMON       12      /* DB monitor triplet.                 */
#define   SQLJ_TYP_XACALL      13      /* X/Open XA triplet type              */
#define   SQLJ_TYP_CMPNDSQL    14      /* Compound SQL control block          */

/* Length and count defaults */

#define   SQLJ_LEN_SQLCA           136     /* SQLCA                          */
#define   SQLJ_LEN_CTK               8     /* Consistency token              */
#define   SQLJ_LEN_USERID            8     /* Userid                         */
#define   SQLJ_LEN_PGMN              8     /* Package name                   */
#define   SQLJ_LEN_SMALL             2     /* 2-Byte signed integer          */
#define   SQLJ_LEN_CDPG              4     /* Application or Database
                                              codepage                       */
#define   SQLJ_LEN_TBLNAM           18     /* Table name                     */

#define   SQLJ_LEN_DBNAME            8     /* Len of database name.          */
#define   SQLJ_LEN_APPLID           32     /* Len of database mon appid.     */
#define   SQLJ_LEN_PRODID            8     /* Length of prodid.              */
#define   SQLJ_LEN_PRNAME           20     /* Length of prog name.           */

#define   SQLJ_LEN_DRDADBNAME       18     /* DRDA-1 database name           */
#define   SQLJ_LEN_PSWD             18     /* User password                  */
#define   SQLJ_LEN_NODE              8     /* Node name                      */
#define   SQLJ_BNDOPT_CNT            6     /* Bind option array count        */
#define   SQLJ_INDICATOR_ARRAY_SIZE  8     /* Indicator array count          */

#define  SQLJ_RELNO         0x0101         /* SQLJRA version number          */
#define  SQLJRA_TTL         "SQLJRA  "     /* SQLJRA title                   */

/*****************************************************************************/
/* Indicator array offset defintions                                         */
/*****************************************************************************/

/* sqlrtype = SQLJR_STARTGW
                             - sqlrflag[SQLJ_CONN_OFF]
                             - sqlrflag[SQLJ_USE_OFF]
                             - sqlrflag[SQLJ_AUTH_OFF]
                             - sqlrflag[SQLJ_UNAME_FROM_OFF]                 */

#define   SQLJ_CONN_OFF              0     /* Offset for Connection type     */
#define   SQLJ_USE_OFF               1     /* Offset for database use        */
#define   SQLJ_AUTH_OFF              2     /* Security authentication type   */
#define   SQLJ_UNAME_FROM_OFF        3     /* Authentication source          */

/* SQLJ_CONN_OFF values                                                      */
#define   SQLJ_CONNECT               1     /* Connection operation           */
#define   SQLJ_MIGRATE               2     /* Migrate operation              */
#define   SQLJ_RESTORE               3     /* Restore database               */
#define   SQLJ_RESTART               4     /* Restart/recover database       */
#define   SQLJ_BACKUP                5     /* Backup database                */
#define   SQLJ_RECOVER               6     /* Recover database               */

/* SQLJ_USE_OFF values                                                       */
#define   SQLJ_USE_SHR             'S'     /* Shared use connection          */
#define   SQLJ_USE_EXC             'X'     /* Exclusive use connection       */


/* sqlrtype = all SQLJ_DBSV sqlrtypes : Standards option
                             - sqlrflag[SQLJ_STND_OFF]                       */

#define   SQLJ_STND_OFF              0     /* Offset for standards option    */

/* SQLJ_STND_OFF values                                                      */
#define   SQLJ_STND_NONE           '0'     /* No compliance required         */
#define   SQLJ_STND_MIA            '1'     /* MIA compliance required        */
#define   SQLJ_STND_SQL89          '2'     /* SQL 89 compliance required     */


/* sqlrtype = SQLJR_COMMIT
                             - sqlrflag[SQLJ_CMMT_OFF]                       */
/*                           - sqlrflag[SQLJ_CMMT_DTP_OFF]                   */

#define   SQLJ_CMMT_OFF              1     /* Offset for hold option         */
#define   SQLJ_CMMT_DTP_OFF          2     /* DTP state offset.              */
#define   SQLJ_CMMT_SNDRCV_OFF       3     /* Sync/Async offset              */

/* SQLJ_CMMT_OFF values                                                      */
#define   SQLJ_CMMT_NOHOLD           0     /* Commit                         */
#define   SQLJ_CMMT_HOLD             1     /* Commit hold                    */

/* SQLJ_CMMT_SNDRCV_OFF values                                                */
/*    SQLE_DB2RA_SNDRCV_BOTH                                                  */
/*    SQLE_DB2RA_SNDRCV_SEND                                                  */
/*    SQLE_DB2RA_SNDRCV_RECV                                                  */

/* ROLLBACK FLAG values                                                      */
#define   SQLJ_ROLL_SNDRCV_OFF       0      /* Indicator for send or receive  */

/* SQLJ_ROLL_SNDRCV_OFF values are the same as SQLJ_CMMT_SNDRCV_OFF           */

/* sqlrtype = SQLJR_COMPILE
                             - sqlrflag[SQLJ_DCSR_OFF]
                             - sqlrflag[SQLJ_CSRH_OFF]
                             - sqlrflag[SQLJ_SG_OFF]                         */
/*                           - sqlrflag[SQLJ_COMP_DTP_OFF]                   */

#define   SQLJ_DCSR_OFF              1     /* Offset for Statement type      */
#define   SQLJ_CSRH_OFF              2     /* Offset for Cursor Hold option  */
#define   SQLJ_SG_OFF                3     /* Offset for Shallow Grammar     */
#define   SQLJ_COMP_DTP_OFF          4     /* DTP state offset.              */

/* SQLJ_DCSR_OFF values                                                      */
#define   SQLJ_STMT_NDCLR            0     /* Statement is not Declare Cursor*/
#define   SQLJ_STMT_DCLR             1     /* Statement is Declare Cursor    */

/* SQLJ_CSRH_OFF values                                                      */
#define   SQLJ_CSR_NOHOLD            0     /* Cursor not declared with Hold  */
#define   SQLJ_CSR_HOLD              1     /* Cursor declared with Hold      */

/* SQLJ_SG_OFF values                                                        */
#define   SQLJ_STMT_VALID            0     /* Statement recognized by
                                              precompiler                    */
#define   SQLJ_STMT_UNKNOWN          1     /* Statement not recognized by
                                              precompiler                    */

/* sqlrtype = SQLJR_CLOSE                                             @d32824acc*/
/*                           - sqlrflag[SQLJ_DTP_OFF] (see below)     @d32824acc*/
/*                           - sqlrflag[SQLJ_REL_OFF]                 @d32824acc*/

#define   SQLJ_REL_OFF               2     /* RELEASE option offset   @d32824acc*/


/* sqlrtype = SQLJR_EXECUTE
                             - sqlrflag[SQLJ_EXEC_OFF]                       */
/*                           - sqlrflag[SQLJ_EXEC_DTP_OFF]                   */

#define   SQLJ_EXEC_OFF              1     /* Offset for output SQLDA option */
#define   SQLJ_EXEC_DTP_OFF          2     /* DTP state offset.              */

/* SQLJ_EXEC_OFF and SQLJ_CSRDA_OFF values                                   */
#define   SQLJ_NO_OUTSQLDA           0     /* Do not return output SQLDA     */
#define   SQLJ_OUTSQLDA              1     /* Return output SQLDA            */


/* sqlrtype =  SQLJR_OPEN
                             - sqlrflag[SQLJ_CSRDA_OFF]
                             - sqlrflag[SQLJ_CSRRW_OFF]
                             - sqlrflag[SQLJ_BLKREQ_OFF]                     */
/*                           - sqlrflag[SQLJ_OPEN_DTP_OFF]                   */

#define   SQLJ_CSRDA_OFF             1     /* Offset for SQLDA option        */
#define   SQLJ_CSRRW_OFF             2     /* Offset for READ/UPDATE option  */
#define   SQLJ_BLKREQ_OFF            3     /* Offset for blocking flag.      */
#define   SQLJ_OPEN_DTP_OFF          4     /* DTP state offset.              */

/* SQLJ_CSRRW_OFF values                                                     */
#define   SQLJ_READ                  0     /* Output SQLDA for read-only     */
#define   SQLJ_UPDATE                1     /* Output SQLDA will be modified  */

/* SQLJ_BLKREQ_OFF values                                                    */
#define   SQLJ_NO_BLOCK              0     /* Ask for no blocking            */
#define   SQLJ_BLOCK                 1     /* Ask for blocking               */


/* sqlrtype = SQLJR_PREPFINI
                            - sqlrflag[SQLJ_PFINI_OFF]                       */
/*                          - sqlrflag[SQLJ_PFINI_DTP_OFF]                   */

#define   SQLJ_PFINI_OFF             0     /* Offset for Commit/Rollback     */
#define   SQLJ_PFINI_DTP_OFF         1     /* DTP state offset.              */

/* SQLJ_PFINI_OFF values                                                     */
#define   SQLJ_COMMIT                1     /* Commit package                 */
#define   SQLJ_ROLLBACK              0     /* Rollback package               */


/* sqlrtype = SQLJR_RUNSTATS
                            - sqlrflag[SQLJ_STATS_OFF]
                            - sqlrflag[SQLJ_SHRLV_OFF]                       */
/*                          - sqlrflag[SQLJ_RUNST_DTP_OFF]                   */

#define   SQLJ_STATS_OFF             1     /* Offset for Statistics option   */
#define   SQLJ_SHRLV_OFF             2     /* Offset for Share level         */
#define   SQLJ_RUNST_DTP_OFF         3     /* DTP state offset.              */

/* SQLJ_STATS_OFF values are defined in sqlutil.h                            */

/* SQLJ_SHRLV_OFF values  are defined in sqlutil.h                           */


/* sqlrtype = all SQLJ_DBSV sqlrtypes EXCEPT the following ...   */
/*            SQLJR_COMMIT                                       */
/*            SQLJR_COMPILE                                      */
/*            SQLJR_EXECUTE                                      */
/*            SQLJR_OPEN                                         */
/*            SQLJR_PREPFINI                                     */
/*            SQLJR_RUNSTATS                                     */
/*                          - sqlrflag[SQLJ_DTP_OFF]             */

#define   SQLJ_DTP_OFF               1     /* DTP state offset.  */

/* SQLJ_DTP_OFF       values are defined in sqlra.h as the       */
/*                    SQLR_XA_CONNECT values.                    */


/*****************************************************************************/
/* Triplet defintions                                                        */
/*****************************************************************************/

/* sqlrtype = SQLJR_STARTGW                                                  */

#define   SQLJ_UPW_OFF               0     /*  user password                 */
#define   SQLJ_ACP_OFF               1     /*  application code page         */
#define   SQLJ_ANN_OFF               2     /*  application node name         */
#define   SQLJ_APN_OFF               3     /*  application name              */
#define   SQLJ_DPW_OFF               4     /*  database password             */
#define   SQLJ_MON_OFF               5     /*  database monitor              */
#define   SQLJ_DCE_OFF               6     /*  DCE Ticket                    */
#define   SQLJ_ACC_OFF               7     /*  User-supplied DDCS accounting */
                                           /*  string component.             */


/* sqlrtype = SQLJR_RPC                                                      */

#define   SQLJ_PRC_OFF               0     /*  procedure return code         */
#define   SQLJ_RPN_OFF               1     /*  remote procedure name         */
#define   SQLJ_DAT_OFF               2     /*  input data area               */
#define   SQLJ_IDA_OFF               2     /*  input sqlda                   */
#define   SQLJ_ODA_OFF               3     /*  output sqlda                  */


/* sqlrtype = SQLJR_COMPILE                                                  */

#define   SQLJ_STN_OFF               0     /*  statement number              */
#define   SQLJ_STT_OFF               1     /*  statement text                */
#define   SQLJ_CRN_OFF               2     /*  cursor name                   */
#define   SQLJ_SEL_OFF               3     /*  select string                 */


/* sqlrtype =  SQLJR_EXECIMMD
               SQLJR_PREPARE
               SQLJR_REORG                                                   */

#define   SQLJ_TXT_OFF               0     /*  statement text                */
#define   SQLJ_ALP_OFF               1     /*  alternate path                */


/* sqlrtype = SQLJR_GETTA
              SQLJR_RUNSTATS                                                 */

#define   SQLJ_TNM_OFF               0     /*  table name                    */
#define   SQLJ_INX_OFF               1     /*  index list                    */

/* sqlrtype = SQLJR_TRUNC_TABLE                                              */

#define   SQLJ_TBN_OFF               0     /*  table name                    */
#define   SQLJ_SCH_OFF               1     /*  index list                    */


/* sqlrtype = SQLJR_PREPINIT                                                 */

#define   SQLJ_BOA_OFF               0     /*  bind option array             */
#define   SQLJ_BIND_OFF              1     /*  New bind option array         */


/* sqlrtype = SQLJR_CMPNDSQL                                                 */

#define   SQLJ_CMPND_OFF             0     /* cmpd SQL control   */


/* sqlrtype = SQLJR_XA_RECOVER
              SQLJR_XA_PREPARE
              SQLJR_XA_FORGET
              SQLJR_XA_COMMIT
              SQLJR_XA_ROLLBACK
              SQLJR_XA_END                                                    */

#define   SQLJ_XACALL_OFF            0     /* XA Call Info struct             */

/*****************************************************************************/
/* Bind Option codepoints                                                    */
/* These are the DDM codepoints which correspond to the all the bind options */
/* which may be specified with the Database Connection Services Programming  */
/* Interface.                                                                */
/*****************************************************************************/

/* sqlrtype = SQLJR_PREPINIT, sqljra.sqlrdata[SQLJ_BOA_OFF],                 */
/*            sqljra_bindopts.option                                         */

#define SQLJ_BO_TITLE           0x0045    /* A brief description             */
#define SQLJ_BO_VRSNAM          0x1144    /* Version name                    */
#define SQLJ_BO_PKGDFTCC        0x119A    /* Package default CCSIDs of col   */
#define SQLJ_BO_CCSIDSBC        0x119C    /* CCSID for single-byte chars     */
#define SQLJ_BO_CCSIDDBC        0x119D    /* CCSID for double-byte chars     */
#define SQLJ_BO_CCSIDMBC        0x119E    /* CCSID for mixed-byte chars      */
#define SQLJ_BO_DECPRC          0x2106    /* Decimal precision               */
#define SQLJ_BO_PKGCNSTKN       0x210D    /* RDB package consistency token   */
#define SQLJ_BO_BNDCHKEXS       0x211B    /* Bind existence checking         */
#define SQLJ_BO_PKGRPLOPT       0x211C    /* Bind package replacement option */
#define SQLJ_BO_BNDCRTCTL       0x211D    /* Bind create package option      */
#define SQLJ_BO_PKGATHOPT       0x211E    /* Bind package authorization      */
#define SQLJ_BO_STTSTRDEL       0x2120    /* Bind statement string delimiter */
#define SQLJ_BO_STTDECDEL       0x2121    /* Bind statement decimal delimiter*/
#define SQLJ_BO_STTDATFMT       0x2122    /* Bind date format option         */
#define SQLJ_BO_STTTIMFMT       0x2123    /* Bind time format option         */
#define SQLJ_BO_PKGISOLVL       0x2124    /* Isolation level                 */
#define SQLJ_BO_PKGDFTCST       0x2125    /* Package default char subtype    */
#define SQLJ_BO_DFTRDBCOL       0x2128    /* Default RDB collection id       */
#define SQLJ_BO_RDBRLSOPT       0x2129    /* RDB release option              */
#define SQLJ_BO_PKGRPLVRS       0x212D    /* Replaced package version name   */
#define SQLJ_BO_DGRIOPRL        0x212F    /* Degree of I/O parallelism       */
#define SQLJ_BO_BNDEXPOPT       0x2130    /* Bind explain option             */
#define SQLJ_BO_PKGOWNID        0x2131    /* Package owner id                */
#define SQLJ_BO_QRYBLKCTL       0x2132    /* Query block protocol            */
#define SQLJ_BO_PKGATHRUL       0x213F    /* Package authorization rules     */

/*   Database Manager internal values                                        */
#define SQLJ_BO_STANDARD        0xF901    /* Standards compliance option     */

/*****************************************************************************/
/* Bind Option values                                                        */
/* These are the DDM codepoints which correspond to the values for the bind  */
/* options which may be specified with the Database Connection Services      */
/* Programming Interface.                                                    */
/*****************************************************************************/

/* sqlrtype = SQLJR_PREPINIT, sqljra.sqlrdata[SQLJ_BOA_OFF],                 */
/*            sqljra_bindopts.value                                          */

#define SQLJ_BO_FRCSNGROW      0x2410     /* Force single row query          */
#define SQLJ_BO_LMTBLCK        0x2417     /* Limited block query             */
#define SQLJ_BO_SNGROW         0x2418     /* Single row query                */
#define SQLJ_BO_BNDEXSRQR      0x241C     /* Bind object existence required  */
#define SQLJ_BO_BNDEXSOPT      0x241D     /* Bind object existence optional  */
#define SQLJ_BO_PKGATHRUL_OWN  0x0001     /* Package auth. rule owner        */
#define SQLJ_BO_PKGATHRUL_REQ  0x0000     /* Package auth. rule requester    */
#define SQLJ_BO_PKGRPLALW      0x241F     /* Package replacement allowed     */
#define SQLJ_BO_PKGRPLNA       0x2420     /* Package replacement not allowed */
#define SQLJ_BO_BNDCHKONL      0x2421     /* Syntax Check only               */
#define SQLJ_BO_BNDNERALW      0x2422     /* Create package if no errors     */
#define SQLJ_BO_BNDERRALW      0x2423     /* Create Package even if errors   */
#define SQLJ_BO_BNDCHK         SQLJ_BO_BNDCHKONL
#define SQLJ_BO_BNDCRT         SQLJ_BO_BNDNERALW
#define SQLJ_BO_BNDERR         SQLJ_BO_BNDERRALW
#define SQLJ_BO_PKGATHRVK      0x2424     /* Package authorizations revoked  */
#define SQLJ_BO_PKGATHKP       0x2425     /* Package authorizations keep     */
#define SQLJ_BO_STRDELAP       0x2426     /* String delimeter apostrophe     */
#define SQLJ_BO_STRDELDQ       0x2427     /* String delimeter double quote   */
#define SQLJ_BO_ISOFMT         0x2429     /* ISO date format                 */
#define SQLJ_BO_USAFMT         0x242A     /* USA date format                 */
#define SQLJ_BO_EURFMT         0x242B     /* European date format            */
#define SQLJ_BO_JAPANFMT       0x242C     /* Japanese date format            */
#define SQLJ_BO_ISOTIMFMT      0x242E     /* ISO time format                 */
#define SQLJ_BO_USATIMFMT      0x242F     /* USA time format                 */
#define SQLJ_BO_EURTIMFMT      0x2430     /* European time format            */
#define SQLJ_BO_JISTIMFMT      0x2431     /* Japanese time format            */
#define SQLJ_BO_CSTSYSDFT      0x2432     /* Character subtype system default*/
#define SQLJ_BO_CSTBITS        0x2433     /* Character subtype bits          */
#define SQLJ_BO_CSTSBCS        0x2434     /* Character subtype SBCS          */
#define SQLJ_BO_CSTMBCS        0x2435     /* Character subtype MBCS          */
#define SQLJ_BO_RDBRLSCMM      0x2438     /* RDB release at commit           */
#define SQLJ_BO_RDBRLSCNV      0x2439     /* RDB release at conversation     */
                                          /* deallocation                    */
#define SQLJ_BO_EXPNON         0x243A     /* Explain no SQL statements       */
#define SQLJ_BO_EXPALL         0x243B     /* Explain all explainable SQL     */
                                          /* statements.                     */
#define SQLJ_BO_DECDELPRD      0x243C     /* Decimal delimeter is period     */
#define SQLJ_BO_DECDELCMA      0x243D     /* Decimal delimeter is comma      */
#define SQLJ_BO_ISOLVLCHG      0x2441     /* Isolation lvl = change          */
#define SQLJ_BO_ISOLVLCS       0x2442     /* Isolation lvl = cursor stability*/
#define SQLJ_BO_ISOLVLALL      0x2443     /* Isolation lvl = all             */
#define SQLJ_BO_ISOLVLRR       0x2444     /* Isolation lvl = repeatable read */
#define SQLJ_BO_ISOLVLNC       0x2445     /* Isolation lvl = no check        */



/*   Database Manager internal values                                        */
#define SQLJ_BO_STDSQL89        0xF902    /* SQL 89 standards compliance     */
#define SQLJ_BO_STDMIA          0xF903    /* MIA standards compliance        */
#define SQLJ_BO_STDNONE         0xF904    /* No standards compliance required*/
#define SQLJ_BO_DEFFMT          0xF905    /* Default country date format     */
#define SQLJ_BO_DEFTIMFMT       0xF907    /* Default country time format     */
#define SQLJ_BO_LOCAL           0xF906    /* Local country date format       */
#define SQLJ_BO_LOCALTIM        0xF906    /* Local country time format       */
#define SQLJ_BO_INSERT          0xF908    /* Buffered insert                 */
#define SQLJ_BO_INSDEF          0xF909    /* No buffering of inserts         */
#define SQLJ_BO_INSBUF          0xF90A    /* Buffering of inserts            */

/*****************************************************************************/
/* Structure Definitions                                                     */
/*****************************************************************************/

/* Database Monitor and NLS - Start Using Triplet structure                   */
typedef struct
{
  unsigned short country;              /* For NLS use.           */
  unsigned short unused;
  _SQLOLDCHAR    appl_id[SQLJ_LEN_APPLID+1];
  _SQLOLDCHAR    dbalias[SQLJ_LEN_DBNAME+1];
  _SQLOLDCHAR    client_prod_id[SQLJ_LEN_PRODID+1];
  _SQLOLDCHAR    prog_name[SQLJ_LEN_PRNAME+1];
  unsigned long  client_platform;
} SQLJ_DBMON_TRIPLET;


/* Bind Option Array Element                                                 */
struct sqljra_bindopts {
         unsigned short length;
         unsigned short option;
         unsigned short value;
};

/* New Bind Options Array Element                                            */
struct sqljra_bind_options {
         unsigned short length;
         unsigned short option;
         unsigned short user_defined;
         union {
               unsigned short value;
               unsigned char  valopt[1];
         } bind_data;
};

/* SQLJRA Triplet element                                                    */
typedef struct
{
   unsigned long   sqlrdtl;
   unsigned long   sqlrdtt;
   _SQLOLDCHAR   * sqlrdtp;

} SQLJDATA;


/* SQLJRA                                                                    */

typedef struct sqljra
{
   _SQLOLDCHAR     sqlraid[8];             /* Eye catcher = 'SQLJRA  '        */
   unsigned long   sqlrabc;                /* Size in bytes                   */
   unsigned short  sqlrelno;               /* Version number                  */
   unsigned short  sqltype;                /* Service type                    */
   unsigned short  sqlrtype;               /* Request type                    */
   unsigned short  sqlrdnum;               /* Number of triplets              */
                                           /* SQLCA                           */
   unsigned long   sqlrcal;                /*   Length of SQLCA               */
   unsigned long   sqlrcat;                /*   Data type of SQLCA            */
   struct sqlca  * sqlrcap;                /*   Pointer to SQLCA              */
                                           /* Input SQLDA                     */
   unsigned long   sqlrdail;               /*   Length of input SQLDA         */
   unsigned long   sqlrdait;               /*   Data type of input SQLDA      */
   struct sqlda  * sqlrdapi;               /*   Pointer to input SQLDA        */
                                           /* Output SQLDA                    */
   unsigned long   sqlrdaol;               /*   Length of output SQLDA        */
   unsigned long   sqlrdaot;               /*   Data type of output SQLDA     */
   struct sqlda  * sqlrdapo;               /*   Pointer to output SQLDA       */
                                           /* Indicator array                 */
   unsigned long   sqlrflgl;               /*   Length of indicator array     */
   unsigned long   sqlrflgt;               /*   Data type of indicator array  */
   _SQLOLDCHAR    *sqlrflag;               /*   Pointer to indicator array    */
                                           /* Userid                          */
   unsigned long   sqlrusrl;               /*   Length of userid              */
   unsigned long   sqlrusrt;               /*   Data type of userid           */
   _SQLOLDCHAR   * sqlruser;               /*   Pointer to userid             */
                                           /* Database name                   */
   unsigned long   sqlrdbnl;               /*   Length of database name       */
   unsigned long   sqlrdbnt;               /*   Data type of database name    */
   _SQLOLDCHAR   * sqlrdbnm;               /*   Pointer to database name      */
                                           /* Package creator                 */
   unsigned long   sqlrcrel;               /*   Length of package creator     */
   unsigned long   sqlrcret;               /*   Data type of package creator  */
   _SQLOLDCHAR   * sqlrcrea;               /*   Pointer to package creator    */
                                           /* Section Number                  */
   unsigned long   sqlrsctl;               /*   Length of section number      */
   unsigned long   sqlrsctt;               /*   Data type of section number   */
   unsigned short *sqlrsect;               /*   Pointer to section number     */
                                           /* Package Name                    */
   unsigned long   sqlrpgml;               /*   Length of package name        */
   unsigned long   sqlrpgmt;               /*   Data type of package name     */
   _SQLOLDCHAR   * sqlrpgmn;               /*   Pointer to package name       */
                                           /* Consistency token               */
   unsigned long   sqlrctkl;               /*   Length of consistency token   */
   unsigned long   sqlrctkt;               /*   Data type of consistency token*/
   _SQLOLDCHAR   * sqlrctkp;               /*   Pointer to consistency token  */
                                           /*   Data triplets                 */
   SQLJDATA        sqlrdata[SQLJR_MAX_DATA_ITEMS];
} SQLJRA;

#define   SQLJCSRA SQLJRA                           /* Connection Services
                                                       SQLJRA                */
#define   SQLJDSRA SQLJRA                           /* Database Services
                                                       SQLJRA                */
#define   SQLJ_LEN_SQLJRA       sizeof(SQLJRA)      /* SQLJRA size           */
#define   SQLJ_LEN_SQLJCSRA     sizeof(SQLJRA)      /* SQLJCSRA size         */
#define   SQLJ_LEN_SQLJDSRA     sizeof(SQLJRA)      /* SQLJDSRA size         */

#if (defined(DB2OS2) || defined(DB2NT) || defined(DB2WIN))
#pragma pack()
#elif (defined(DB2MAC))
#pragma align
#elif (defined(DB2HP) || defined(DB2SNI))

#elif (defined(DB2AIX) || defined(DB2SUN))
#pragma options align=reset
#endif

#endif /* SQL_H_SQLJRA */
