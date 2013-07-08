/******************************************************************************
** 
** Source File Name: SQLENV
** 
** (C) COPYRIGHT International Business Machines Corp. 1987, 1997
** All Rights Reserved
** Licensed Materials - Property of IBM
** 
** US Government Users Restricted Rights - Use, duplication or
** disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
** 
** Function = Include File defining:
**              Environment Commands - Constants
**              Environment Commands - Structures
**              Environment Commands - Function Prototypes
**              Environment Commands - Labels for SQLCODES
** 
** Operating System: Windows NT
** 
*******************************************************************************/
#ifndef SQL_H_SQLENV
#define SQL_H_SQLENV

#ifdef __cplusplus
extern "C" {
#endif

/* Note: _SQLOLDCHAR defaults to 'char'.  See sqlsystm.h for details.         */

#include "sqlsystm.h"                  /* System dependent defines  */

/* Required Include Files */

#include "sql.h"                       /* Includes sqlsystm & sqlca */
#include "sqlda.h"
#include <stddef.h>                    /* needed for offsetof */

#pragma pack(4)

/* Interface Parameters/Structures/Return Codes                               */

/* Parameters for START USING DATABASE                                        */
#define SQL_USE_SHR            'S'     /* USE = Share                         */
#define SQL_USE_EXC            'X'     /* USE = Exclusive                     */
#define SQL_USE_EXC_SN         'N'     /* USE = Exclusive on Single Node      */

/* Sizes for entries in sqledinfo, sqleninfo, sqledbstat, sqleusrstat, sql    */
/* dir_entry, sqle_reg_nwbindery                                              */
#define SQL_ALIAS_SZ           8       /* Alias name                          */
#define SQL_USERID_SZ          8       /* User Id                             */
#define SQL_MAX_USERID_SZ      1024    /* Max User Id Size                    */
#define SQL_AUTHID_SZ          8       /* Auth Id                             */
#define SQL_DBNAME_SZ          8       /* Database name                       */

#define SQL_DRIVE_SZ_DB2OS2    2       /* Drive (Qualified) - OS/2            */
#define SQL_DRIVE_SZ_DB2DOS    2       /* Drive (Qualified) - Windows         */
#define SQL_DRIVE_SZ_DB2WINT   12      /* Drive (Qualified) - NT              */
#define SQL_DRIVE_SZ_DB2AIX    215     /* Path (Qualified) - AIX/UNIX         */
#define SQL_DRIVE_SZ           SQL_DRIVE_SZ_DB2WINT

#define SQL_INAME_SZ           8       /* Internal db name                    */
#define SQL_NNAME_SZ           8       /* Node name                           */
#define SQL_INSTNAME_SZ        8       /* Instance Name                       */
#define SQL_DBTYP_SZ           20      /* Type of database                    */
#define SQL_CMT_SZ             30      /* Comment                             */
#define SQL_LOCLU_SZ           8       /* Local_lu                            */
#define SQL_RMTLU_SZ           8       /* Partner_lu                          */
#define SQL_MODE_SZ            8       /* Mode                                */
#define SQL_NRESERVE_SZ        0       /* Reserved                            */
#define SQL_DBSTAT_ALIAS_SZ    16      /* Alias name                          */
#define SQL_DBSTAT_DBNAME_SZ   16      /* Database name                       */
#define SQL_LONG_NAME_SZ       18      /* Host database name                  */
#define SQL_CS_SZ              256     /* collating sequence                  */
#define SQL_PARAMETER_SZ       512     /* Parameter string                    */
#define SQL_NETID_SZ           8       /* Network ID                          */
#define SQL_PATH_SZ            1024    /* Maximum Path size                   */
#define SQL_HOSTNAME_SZ        255     /* Host Name                           */
#define SQL_COMPUTERNAME_SZ    15      /* Computer Name                       */
#define SQL_PROFILE_SZ         235     /* Profile Name                        */
#define SQL_OPTION_SZ          10      /* Option Name                         */
#define SQL_DCEPRIN_SZ         1024    /* DCE principal name size             */
#define SQL_SERVICE_NAME_SZ    14      /* Service Name                        */
#define SQL_TPMON_NAME_SZ      19      /* TP Monitor Name                     */
#define SQL_SYM_DEST_NAME_SZ   8       /* Symbolic Destination Name           */
#define SQL_TMDATABASE_NAME_SZ 8       /* TM Database Name                    */
#define SQL_AR_SZ              8       /* AR Library Name                     */
#define SQL_SYSTEM_NAME_SZ     21      /* System Name                         */
#define SQL_REMOTE_INSTNAME_SZ 8       /* Remote Instance Name                */

#define SQL_DFTDRDAACT_SZ      25      /* Default DRDA accounting string.     */
#define SQL_DIR_NAME_SZ        255     /* Dir/Route Path/Obj Name             */
#define SQL_CLIENT_COMM_SZ     31      /* Client Comm. Protocol               */
#define SQL_SYSADM_SZ          16      /* Sysadm Group name                   */
#define SQL_FILESERVER_SZ      48      /* Netware fileserver name             */
#define SQL_OBJECTNAME_SZ      48      /* Netware bindery name                */
#define SQL_IPXSOCKET_SZ       4       /* Netware IPX socket                  */
#define SQL_NW_UID_SZ          48      /* Netware userid                      */
#define SQL_NW_PSWD_SZ         128     /* Netware password                    */
#define SQL_COLLATE_INFO_SZ    260     /* Collate info size (256 + 4)         */
#define SQL_ACCOUNT_STR_SZ     199     /* Max accounting string               */
#define SQL_DSCVRCOMM_SZ       35      /* Discover protocols string size      */

/* After an SQL CONNECT, the 5th token in the SQLCA identifies the DBMS an    */
/* application has connected to.  The following are values returned from IBM  */
/* DBMS.                                                                      */
#define SQL_DBMS_ES10_OS2      "QOS/2 DBM"
#define SQL_DBMS_DB2_OS2       "QDB2/2"
#define SQL_DBMS_DB2_NT        "QDB2/NT"
#define SQL_DBMS_DB2_95        "QDB2/Windows 95"
#define SQL_DBMS_DB2_AIX       "QDB2/6000"
#define SQL_DBMS_DB2_AIX_PE    "QDB2/6000 PE"
#define SQL_DBMS_DB2_HPUX      "QDB2/HPUX"
#define SQL_DBMS_DB2_SUN       "QDB2/SUN"
#define SQL_DBMS_DB2_SNI       "QDB2/SNI"
#define SQL_DBMS_DB2_SCO       "QDB2/SCO"
#define SQL_DBMS_DB2_SGI       "QDB2/SGI"
#define SQL_DBMS_DB2_MVS       "QDB2"
#define SQL_DBMS_OS400         "QAS"
#define SQL_DBMS_SQLDS_VM      "QSQLDS/VM"
#define SQL_DBMS_SQLDS_VSE     "QSQLDS/VSE"
#define SQL_DBMS_LU62_SPM      "QLU62SPM"

/* Parameters for Entry Type in sqledinfo                                     */
#define SQL_DCE                '3'     /* Database is DCE                     */
#define SQL_HOME               '2'     /* Database is Home                    */
#define SQL_REMOTE             '1'     /* Database is Remote                  */
#define SQL_INDIRECT           '0'     /* Database is Indirect                */

/* Parameters for adapter number in sqlectnd                                  */
#define SQL_ADAPTER_0          0       /* Adapter number 0                    */
#define SQL_ADAPTER_1          1       /* Adapter number 1                    */
#define SQL_ADAPTER_MIN        0       /* Minimum adapter number              */
#define SQL_ADAPTER_MAX        15      /* Maximum adapter number              */

/* Definitions of constants used for Structure IDs                            */
#define SQL_DCS_STR_ID         0x100   /* DCS directory entry id              */
#define SQL_NODE_STR_ID        0x100   /* Catalog node struct id              */

/* Parameters for protocol types in sqlectnd                                  */
#define SQL_PROTOCOL_APPC      0x0     /* APPC                                */
#define SQL_PROTOCOL_NETB      0x1     /* NETBIOS                             */
#define SQL_PROTOCOL_APPN      0x2     /* APPN                                */
#define SQL_PROTOCOL_TCPIP     0x3     /* TCPIP                               */
#define SQL_PROTOCOL_CPIC      0x4     /* APPC using CPIC                     */
#define SQL_PROTOCOL_IPXSPX    0x5     /* IPX/SPX                             */
#define SQL_PROTOCOL_LOCAL     0x6     /* Local IPC                           */
#define SQL_PROTOCOL_NPIPE     0x7     /* Named Pipe                          */
#define SQL_PROTOCOL_SOCKS     0x8     /* TCPIP using SOCKS                   */

/* Security Type for APPC using CPIC                                          */
#define SQL_CPIC_SECURITY_NONE         0    /* None                           */
#define SQL_CPIC_SECURITY_SAME         1    /* Same                           */
#define SQL_CPIC_SECURITY_PROGRAM      2    /* Program                        */

/* Security Type for TCPIP                                                    */
#define SQL_TCPIP_SECURITY_NONE        0    /* None                           */
#define SQL_TCPIP_SECURITY_SOCKS       1    /* TCPIP SOCKS Support            */

/* Authentication Types                                                       */
#define SQL_AUTHENTICATION_SERVER      0    /* Authenticate on Server         */
#define SQL_AUTHENTICATION_CLIENT      1    /* Authenticate on Client         */
#define SQL_AUTHENTICATION_DCS         2    /* Authenticate via DDCS          */
#define SQL_AUTHENTICATION_DCE         3    /* Authenticate via DCE           */
#define SQL_AUTHENTICATION_NOT_SPEC    255  /* Authentication Not Specified   */

/* Parameters for Create Database API Collating Sequences                     */
#define SQL_CS_SYSTEM          0       /* Coll. Seq. from System              */
#define SQL_CS_USER            -1      /* Coll. Seq. from User                */
#define SQL_CS_NONE            -2      /* Coll. Seq. (None)                   */
#define SQL_CS_COMPATIBILITY   -4      /* Coll. Seq. from pre-v5              */

/* Defines for Start Database Manager OPTION parameter and Stop Database      */
/* Manager OPTION and CALLERAC parameters                                     */
#define SQLE_NONE              0
#define SQLE_FORCE             1
#define SQLE_DROP              2
#define SQLE_CONTINUE          3
#define SQLE_TERMINATE         4
#define SQLE_ADDNODE           5
#define SQLE_RESTART           6
#define SQLE_STANDALONE        7

/* Defines for Start Database Manager & Add Node Tablespace type              */
#define SQLE_TABLESPACES_NONE  0       /* No Temp Tablespaces                 */
#define SQLE_TABLESPACES_LIKE_NODE 1   /* Temp Tablespaces like Specified     */
                                       /* Node                                */
#define SQLE_TABLESPACES_LIKE_CATALOG 2 /* Temp Tablespaces like Catalog      */
                                       /* Node                                */

/* Parameters for Drop Node Action                                            */
#define SQL_DROPNODE_VERIFY    1       /* Verify                              */

/* Parameters for indicating the stored procedure invocation was via the      */
/* CALL statement                                                             */
#define SQL_CALLPROC           "$SQL$CAL"

/* Default values for Segmented Tables parameters                             */
#define SQL_DEF_NUMSEGS        1       /* Default number of segments-nonOS2   */
#define SQL_DEF_SEGPAGES       76800   /* OBSOLETE: Default max pages per     */
                                       /* seg                                 */
#define SQL_DEF_EXTSIZE        32      /* default extent size                 */

/* DUOW Connection Setting types used by sqleqryc() and                       */
/* sqlesetc().Associated values are in sql.h, used in common with the         */
/* precompiler.                                                               */
#define SQL_CONNECT_TYPE       1       /* Connect type                        */
#define SQL_RULES              2       /* Rules for changing connections      */
#define SQL_DISCONNECT         3       /* Disconnect type at syncpoint        */
#define SQL_SYNCPOINT          4       /* Syncpoint type                      */
#define SQL_MAX_NETBIOS_CONNECTIONS 5  /* Maximum concurrent connections      */
#define SQL_DEFERRED_PREPARE   6       /* Maximum concurrent connections      */
#define SQL_CONNECT_NODE       7       /* Node to connect to                  */
#define SQL_ATTACH_NODE        8       /* Node to attach to                   */

/* A structure to identify an SQL statement.  The eyecatcher $SQL$CALL        */
/* identifies this as an EXEC SQL CALL statement.                             */
SQL_STRUCTURE SQLSTMTID
{
        char                   sqlcstid[8]; /* eye catcher                    */
        char                   sqluser[8]; /* creator id                      */
        char                   pkgname[8]; /* package name                    */
        char                   contoken[8]; /* consistency token              */
        short                  sectnum; /* reserved                           */
        char                   wchar_info; /* reserved                        */
        char                   fCacheRows; /* reserved                        */
        char                   buffer[38]; /* reserved                        */
};


/******************************************************************************
** Database Description Block structure
*******************************************************************************/
/* TableSpace types                                                           */
#define SQL_TBS_TYP_SMS        'S'
#define SQL_TBS_TYP_DMS        'D'

/* TableSpace container types                                                 */
#define SQL_TBSC_TYP_PATH      'P'     /* path (directory)  SMS only          */
#define SQL_TBSC_TYP_DEV       'D'     /* device (raw disk) DMS only          */
#define SQL_TBSC_TYP_FILE      'F'     /* file (cooked file) DMS only         */

#define SQLE_DBDESC_2          "SQLDBD02" /* version 2 database descriptor    */
#define SQLE_DBTSDESC_1        "SQLTS001" /* version 2 tableSpace descriptor  */

/* Initial TableSpace names                                                   */
#define SQLCATTS_NAME          "SYSCATSPACE" /* system catalogs               */
#define SQLUSRTS_NAME          "USERSPACE1" /* user tables                    */
#define SQLTMPTS_NAME          "TEMPSPACE1" /* temp tables                    */

/* tableSpace container descriptor                                            */
SQL_STRUCTURE SQLETSCDESC
{
        char           sqlctype;                     /* container type        */
        char           pad1[3];                      /* reserved              */
        long           sqlcsize;                     /* container size (4K    */
                                                     /* pages)                */
        short          sqlclen;                      /* length of container   */
                                                     /* name                  */
        char           sqlcontr[SQLB_MAX_CONTAIN_NAME_SZ]; /* container name  */
                                                     /* (includes 1 byte for  */
                                                     /* C NULL terminator)    */
        char           pad2[2];                      /* 2 bytes padding       */
                                                     /* before next           */
                                                     /* container             */
};


/* tableSpace descriptor                                                      */
SQL_STRUCTURE SQLETSDESC
{
        char           sqltsdid[8];                  /* eyecatcher            */
                                                     /* descriptor version    */
        long           sqlextnt;                     /* extent size (in 4K    */
                                                     /* pages)                */
        long           sqlprftc;                     /* prefetch size (4K     */
                                                     /* pages)                */
        double         sqlpovhd;                     /* i/o overhead          */
        double         sqltrfrt;                     /* i/o transfer rate     */
        char           sqltstyp;                     /* tableSpace type       */
        char           pad1;                         /* reserved              */
        short          sqlccnt;                      /* container count       */
        struct SQLETSCDESC containr[1];              /* array of container    */
                                                     /* specs                 */
};

#define SQLETSDESC_SIZE(containerCount) \
(sizeof(struct SQLETSDESC)+ \
((containerCount)-1)*sizeof(struct SQLETSCDESC) )

SQL_STRUCTURE sqledbdesc
{
        _SQLOLDCHAR    sqldbdid[8];                  /* eye catcher           */
        long           sqldbccp;                     /* comment code page     */
        long           sqldbcss;                     /* Source of collating   */
                                                     /* seq                   */
        unsigned char  sqldbudc[SQL_CS_SZ];          /* user-defined          */
                                                     /* collating seq         */
        _SQLOLDCHAR    sqldbcmt[SQL_CMT_SZ+1];       /* comment               */
        _SQLOLDCHAR    pad[1];                       /* reserved              */
        unsigned long  sqldbsgp;                     /* obsolete: use         */
                                                     /* sqltsext              */
        short          sqldbnsg;                     /* number of segments    */
        char           pad2[2];                      /* reserved              */
        long           sqltsext;                     /* default extent size   */
        struct SQLETSDESC *sqlcatts;
        struct SQLETSDESC *sqlusrts;
        struct SQLETSDESC *sqltmpts;
};


/* Database Directory Scan data structure                                     */
SQL_STRUCTURE sqledinfo
{
        _SQLOLDCHAR    alias[SQL_ALIAS_SZ];          /* Alias name            */
        _SQLOLDCHAR    dbname[SQL_DBNAME_SZ];        /* Database name         */
        _SQLOLDCHAR    drive[SQL_DRIVE_SZ];          /* Drive/Path            */
        _SQLOLDCHAR    intname[SQL_INAME_SZ];        /* Database              */
                                                     /* subdirectory          */
        _SQLOLDCHAR    nodename[SQL_NNAME_SZ];       /* Node name             */
        _SQLOLDCHAR    dbtype[SQL_DBTYP_SZ];         /* Release information   */
        _SQLOLDCHAR    comment[SQL_CMT_SZ];          /* Comment               */
        short          com_codepage;                 /* Code page of comment  */
        _SQLOLDCHAR    type;                         /* Entry type - defines  */
                                                     /* above                 */
        unsigned short authentication;               /* Authentication type   */
        char           glbdbname[SQL_DIR_NAME_SZ];   /* Global database name  */
        _SQLOLDCHAR    dceprincipal[SQL_DCEPRIN_SZ]; /* dce principal bin     */
                                                     /* string                */
        short          cat_nodenum;                  /* Catalog node number   */
        short          nodenum;                      /* Node number           */
};

/* Node Directory Scan data structure                                         */
SQL_STRUCTURE sqleninfo
{
        _SQLOLDCHAR    nodename[SQL_NNAME_SZ];       /* Node name             */
        _SQLOLDCHAR    local_lu[SQL_LOCLU_SZ];       /* Local_lu_name         */
        _SQLOLDCHAR    partner_lu[SQL_RMTLU_SZ];     /* Partner_lu_name       */
        _SQLOLDCHAR    mode[SQL_MODE_SZ];            /* Mode                  */
        _SQLOLDCHAR    comment[SQL_CMT_SZ];          /* Comment               */
        unsigned short com_codepage;                 /* Comment code page     */
        unsigned short adapter;                      /* NetBIOS Adapter #     */
        _SQLOLDCHAR    networkid[SQL_NETID_SZ];      /* APPN Network ID       */
        _SQLOLDCHAR    protocol;                     /* Protocol type         */
        _SQLOLDCHAR    sym_dest_name[SQL_SYM_DEST_NAME_SZ]; /* CPIC Sym.      */
                                                     /* Dest. Name            */
        unsigned short security_type;                /* CPIC Security Type    */
        _SQLOLDCHAR    hostname[SQL_HOSTNAME_SZ];    /* TCP/IP Host name      */
        _SQLOLDCHAR    service_name[SQL_SERVICE_NAME_SZ]; /* TCP/IP Service   */
                                                     /* name                  */
        char           fileserver[SQL_FILESERVER_SZ]; /* IPX/SPX fileserver   */
                                                     /* name                  */
        char           objectname[SQL_OBJECTNAME_SZ]; /* IPX/SPX objectname   */
        char           instance_name[SQL_INSTNAME_SZ]; /* LOCAL Instance      */
                                                     /* name                  */
        char           computername[SQL_COMPUTERNAME_SZ]; /* Computer name    */
        char           system_name[SQL_SYSTEM_NAME_SZ]; /* System name        */
        char           remote_instname[SQL_REMOTE_INSTNAME_SZ]; /* Remote     */
                                                     /* instance name         */
        _SQLOLDCHAR    catalog_node_type;            /* Catalog node type     */
        unsigned short os_type;                      /* OS type               */
};

/* General Catalog Node structures and defines                                */

SQL_STRUCTURE sqle_node_struct
{
        unsigned short struct_id;                    /* Structure Identifier  */
        unsigned short codepage;                     /* Codepage for comment  */
        _SQLOLDCHAR    comment[SQL_CMT_SZ + 1];      /* Comment               */
        _SQLOLDCHAR    nodename[SQL_NNAME_SZ + 1];   /* Node name             */
        unsigned char  protocol;                     /* Protocol Type         */
};

SQL_STRUCTURE sqle_node_appc                         /* For APPC protocol     */
{
        _SQLOLDCHAR    local_lu[SQL_LOCLU_SZ + 1];   /* Local_lu name         */
        _SQLOLDCHAR    partner_lu[SQL_RMTLU_SZ + 1]; /* Alias Partner_lu      */
                                                     /* name                  */
        _SQLOLDCHAR    mode[SQL_MODE_SZ + 1];        /* Mode                  */
};

SQL_STRUCTURE sqle_node_netb                         /* For NetBIOS Protocol  */
{
        unsigned short adapter;                      /* Adapter Number        */
        _SQLOLDCHAR    remote_nname[SQL_RMTLU_SZ + 1]; /* Remote Workstation  */
                                                     /* name                  */
};

SQL_STRUCTURE sqle_node_appn                         /* For APPN protocol     */
{
        _SQLOLDCHAR    networkid[SQL_NETID_SZ + 1];  /* Network ID            */
        _SQLOLDCHAR    remote_lu[SQL_RMTLU_SZ + 1];  /* Remoter lu name       */
        _SQLOLDCHAR    local_lu[SQL_LOCLU_SZ + 1];   /* Local_lu name         */
        _SQLOLDCHAR    mode[SQL_MODE_SZ + 1];        /* Mode                  */
};

SQL_STRUCTURE sqle_node_tcpip                        /* For TCPIP protocol    */
{
        _SQLOLDCHAR    hostname[SQL_HOSTNAME_SZ+1];  /* Host name             */
        _SQLOLDCHAR    service_name[SQL_SERVICE_NAME_SZ+1]; /* Service Name   */
};

SQL_STRUCTURE sqle_node_npipe                        /* For NPIPE protocol    */
{
        char           computername[SQL_COMPUTERNAME_SZ+1]; /* Computer name  */
        char           instance_name[SQL_INSTNAME_SZ+1]; /* Instance Name     */
};

SQL_STRUCTURE sqle_node_local                        /* For LOCAL protocol    */
{
        char           instance_name[SQL_INSTNAME_SZ+1]; /* Instance Name     */
};

SQL_STRUCTURE sqle_node_cpic                         /* For APPC using CPIC   */
                                                     /* protocol              */
{
        _SQLOLDCHAR    sym_dest_name[SQL_SYM_DEST_NAME_SZ+1]; /* Sym Dest     */
                                                     /* Name                  */
        unsigned short security_type;                /* Security Type         */
};

SQL_STRUCTURE sqle_node_ipxspx                       /* For IPX/SPX protocol  */
{
        char           fileserver[SQL_FILESERVER_SZ+1]; /* Fileserver name    */
        char           objectname[SQL_OBJECTNAME_SZ+1]; /* Object name        */
};

/* Values for sqlefrce                                                        */
#define SQL_ASYNCH             0       /* Force Mode (Asynchronous)           */
#define SQL_ALL_USERS          -1      /* Force Count (All Users)             */

/* Values for priority type in sqlesapr                                       */
#define SQL_ABSOLUTE_PRIORITY  1       /* Absolute (i.e. fixed) Priority      */
#define SQL_DELTA_PRIORITY     0       /* Delta (i.e. nice) Priority          */

#define SQL_PRODNAME_SZ        30      /* Product name                        */
SQL_STRUCTURE sql_dir_entry            /* DDCS Directory Entry Data           */
                                       /* Structure                           */
{
        unsigned short         struct_id; /* Structure Identifier             */
        unsigned short         release; /* Release level of entry             */
        unsigned short         codepage; /* Codepage of comment               */
        _SQLOLDCHAR            comment[SQL_CMT_SZ + 1]; /* Directory entry    */
                                       /* comment                             */
        _SQLOLDCHAR            ldb[SQL_DBNAME_SZ + 1]; /* Local DB name       */
        _SQLOLDCHAR            tdb[SQL_LONG_NAME_SZ + 1]; /* Target (host)    */
                                       /* DB name                             */
        _SQLOLDCHAR            ar[SQL_AR_SZ + 1]; /* AR library name          */
        _SQLOLDCHAR            parm[SQL_PARAMETER_SZ + 1]; /* Parameter       */
                                       /* string                              */
};

/******************************************************************************
** Database Codepage and Country code info structures
*******************************************************************************/

SQL_STRUCTURE sqledbcinfo
{
        _SQLOLDCHAR            sqldbcp[SQL_CODESET_LEN + 1]; /* database      */
                                       /* codeset                             */
        _SQLOLDCHAR            sqldbcc[SQL_LOCALE_LEN + 1]; /* database       */
                                       /* territory                           */
};

/******************************************************************************
** V2 Database Codepage and Country code info structure
*******************************************************************************/

SQL_STRUCTURE sqledbcountryinfo
{
        char                   sqldbcodeset[SQL_CODESET_LEN + 1]; 
        char                   sqldblocale[SQL_LOCALE_LEN + 1]; /* database   */
                                       /* territory                           */
};

SQL_STRUCTURE sqle_conn_setting        /* Connection setting structure for    */
                                       /* use with distributed unit of work   */
{
        unsigned short         type;   /* Connection setting type             */
        unsigned short         value;  /* Connection setting value            */
};

/******************************************************************************
** Register/Deregister constants and data structures
*******************************************************************************/

/* Defines for LOCATION TO REGISTER parameter                                 */
#define SQL_NWBINDERY          0

/* Register/deregister info. for NW bindery data structure                    */
SQL_STRUCTURE sqle_reg_nwbindery
{
        char                   uid[SQL_NW_UID_SZ+1];
        unsigned short         reserved_len_1;
        char                   pswd[SQL_NW_PSWD_SZ+1];
        unsigned short         reserved_len_2;
};

/******************************************************************************
** Start/Stop Database Manager constants and data structures
*******************************************************************************/

/* V5 Start Options structure Eye Catcher value                               */
#define SQLE_STARTOPTID_V51    "SQLOPT01"

/* V5 Start Database Manager structure                                        */
SQL_STRUCTURE sqle_start_options
{
        char                   sqloptid[8]; /* Structure Eye Catcher          */
        unsigned long          isprofile; /* Profile specified?               */
        char                   profile[SQL_PROFILE_SZ+1]; /* Profile          */
        unsigned long          isnodenum; /* Node number specified?           */
        SQL_PDB_NODE_TYPE      nodenum; /* Node number                        */
        unsigned long          option; /* Start option                        */
        unsigned long          ishostname; /* Hostname specified?             */
        char                   hostname[SQL_HOSTNAME_SZ+1]; /* Hostname       */
        unsigned long          isport; /* Port specified?                     */
        SQL_PDB_PORT_TYPE      port;   /* Port                                */
        unsigned long          isnetname; /* Netname specified?               */
        char                   netname[SQL_HOSTNAME_SZ+1]; /* Netname         */
        unsigned long          tblspace_type; /* Addnode tablespace type      */
        SQL_PDB_NODE_TYPE      tblspace_node; /* Addnode tablespace node      */
        unsigned long          iscomputer; /* Computername specified?         */
        char                   computer[SQL_COMPUTERNAME_SZ+1]; 
        char                   *pUserName; /* Logon Account user name         */
        char                   *pPassword; /* Logon Account password          */
};

/* V5 Stop Database Manager structure                                         */
SQL_STRUCTURE sqledbstopopt
{
        unsigned long          isprofile; /* Profile specified?               */
        char                   profile[SQL_PROFILE_SZ+1]; /* Profile          */
        unsigned long          isnodenum; /* Node number specified?           */
        SQL_PDB_NODE_TYPE      nodenum; /* Node number                        */
        unsigned long          option; /* Option                              */
        unsigned long          callerac; /* Caller action                     */
};

/******************************************************************************
** Add Node data structures
*******************************************************************************/

/* V5 Add Node Option structure Eye Catcher value                             */
#define SQLE_ADDOPTID_V51      "SQLADD01"

/* Add Node structure                                                         */
SQL_STRUCTURE sqle_addn_options
{
        char                   sqladdid[8]; /* Structure Eye Catcher          */
        unsigned long          tblspace_type; /* Temporary Tablespace Type    */
        SQL_PDB_NODE_TYPE      tblspace_node; /* Temporary Tablespace Node    */
};

#if defined(SQLZ_STACK)
#define SQLENOP 0
#else

/******************************************************************************
** Database Environment Commands -- Function Prototypes
*******************************************************************************/


#if defined(SQL_REL_10)
#define sqledrpd(dbn,pw,ca) sqledrpd_api(dbn,pw,ca)
#else
#define sqledrpd(dbn,ca) sqledrpd_api(dbn, (_SQLOLDCHAR *) "",ca)
#endif
#define sqlectdd(dbn,als,ty,nm,dr,com,au,ca) sqlectdd_api(dbn,\
  als,ty,nm,dr,com,au,ca)
#define sqlecadb(dbn,als,ty,nm,dr,com,au,dp,ca) sqlecadb_api(dbn,\
  als,ty,nm,dr,com,au,dp,ca)
#define sqlectnd(node,prot,ca) sqlectnd_api(node,prot,ca)
#define sqledbcr(dbn,drv,dbdesc,au,dbcinfo,ca) \
  sqledbcr_api(dbn,drv,dbdesc,au,dbcinfo,ca)
#define sqledcgd(dbn,drv,com,ca) sqledcgd_api(dbn,drv,com,ca)
#define sqledcls(ha,ca) sqledcls_api(ha,ca)
#define sqledgne(ha,bu,ca) sqledgne_api(ha,bu,ca)
#define sqledosd(dr,ha,co,ca) sqledosd_api(dr,ha,co,ca)
#define sqlefrce(cn,ap,mo,ca) sqlefrce_api(cn,ap,mo,ca)
#define sqlegdad(entry,ca) sqlegdad_api(entry,ca)
#define sqlegdcl(ca) sqlegdcl_api(ca)
#define sqlegdel(entry,ca) sqlegdel_api(entry,ca)
#define sqlegdge(entry,ca) sqlegdge_api(entry,ca)
#define sqlegdgt(ct,entry,ca) sqlegdgt_api(ct,entry,ca)
#define sqlegdsc(ct,ca) sqlegdsc_api(ct,ca)
#define sqlegins(iname,ca) sqlegins_api(iname,ca)
#define sqlesdeg(na,pa,dg,ca) sqlesdeg_api(na,pa,dg,ca)

#define sqleregs(loc,reg,ca) sqleregs_api(loc,reg,ca)
#define sqledreg(loc,reg,ca) sqledreg_api(loc,reg,ca)
#define sqleintr() sqleintr_api()
#define sqleisig(ca) sqleisig_api(ca)
#define sqlefmem(ca,mptr) sqlefmem_api(ca,mptr)
#define sqlemgdb(db,id,pw,ca) sqlemgdb_api(db,id,pw,ca)
#define sqle_activate_db(db,id,pw,rr,ca) sqle_activate_db_api(db,id,pw,rr,ca)
#define sqle_deactivate_db(db,id,pw,rr,ca) sqle_deactivate_db_api(db,id,pw,rr,ca)
#define sqlencls(ha,ca) sqlencls_api(ha,ca)
#define sqlengne(ha,bu,ca) sqlengne_api(ha,bu,ca)
#define sqlenops(ha,bu,ca) sqlenops_api(ha,bu,ca)
#define sqleproc(na,ln,ida,oda,ca) sqleproc_api(na,ln,ida,oda,ca)
#define sqlepstr(so,ca) sqlepstr_api(so,ca)
#define sqlepstp(so,ca) sqlepstp_api(so,ca)
#define sqlepstart(so,ca) sqlepstart_api(so,ca)
#define sqlerstd(dbn,id,pw,ca) sqlerstd_api(dbn,id,pw,ca)
#define sqlesapr(ag,pl,pt,ca) sqlesapr_api(ag,pl,pt,ca)
#define sqlestar() sqlestar_api()
#define sqlestop(ca) sqlestop_api(ca)
#define sqleuncd(dbn,ca) sqleuncd_api(dbn,ca)
#define sqleuncn(nn,ca) sqleuncn_api(nn,ca)
#define sqlesetc(set,num,ca) sqlesetc_api(set,num,ca)
#define sqleqryc(set,num,ca) sqleqryc_api(set,num,ca)
#define sqleatin(iname,id,pw,ca) sqleatin_api(iname,id,pw,ca)
#define sqledtin(ca) sqledtin_api(ca)
#define sqlecrea(dbn,alias,drv,dbdesc,dbcinfo,rsvd2,rsvd1,ca) \
        sqlecrea_api(dbn,alias,drv,dbdesc,dbcinfo,rsvd2,rsvd1,ca)
#define sqlesact(str,ca) sqlesact_api(str,ca)
#define sqleaddn(rsvd,ca)  sqleaddn_api(rsvd,ca)
#define sqlecran(dbn,rsvd,ca)  sqlecran_api(dbn,rsvd,ca)
#define sqledpan(dbn,rsvd,ca)  sqledpan_api(dbn,rsvd,ca)
#define sqledrpn(ac,rsvd,ca)  sqledrpn_api(ac,rsvd,ca)
#endif

SQL_API_RC SQL_API_FN                        /* Catalog Database              */
  sqlectdd_api (
        _SQLOLDCHAR * pDbName,               /* database                      */
        _SQLOLDCHAR * pDbAlias,              /* alias                         */
        unsigned char Type,                  /* type                          */
        _SQLOLDCHAR * pNodeName,             /* node name                     */
        _SQLOLDCHAR * pPath,                 /* drive/path                    */
        _SQLOLDCHAR * pComment,              /* comment                       */
        unsigned short Authentication,       /* authentication                */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Catalog Database              */
  sqlecadb_api (
        _SQLOLDCHAR * pDbName,               /* database                      */
        _SQLOLDCHAR * pDbAlias,              /* alias                         */
        unsigned char Type,                  /* type                          */
        _SQLOLDCHAR * pNodeName,             /* node name                     */
        _SQLOLDCHAR * pPath,                 /* drive/path                    */
        _SQLOLDCHAR * pComment,              /* comment                       */
        unsigned short Authentication,       /* authentication                */
        _SQLOLDCHAR * pDcePrincipal,         /* DCE principal name if         */
                                             /* auth=DCE                      */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Catalog Node                  */
  sqlectnd_api (
        struct sqle_node_struct * pNodeInfo, /* node structure ptr            */
        void * pProtocolInfo,                /* protocol structure ptr        */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Change Database Comment       */
  sqledcgd_api (
        _SQLOLDCHAR * pDbAlias,              /* database alias                */
        _SQLOLDCHAR * pPath,                 /* drive/path                    */
        _SQLOLDCHAR * pComment,              /* comment                       */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Close Directory Scan          */
  sqledcls_api (
        unsigned short Handle,               /* handle                        */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Get Next Directory Entry      */
  sqledgne_api (
        unsigned short Handle,               /* handle                        */
        struct sqledinfo ** ppDbDirEntry,    /* buffer                        */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Open Directory Scan           */
  sqledosd_api (
        _SQLOLDCHAR * pPath,                 /* drive/path                    */
        unsigned short * pHandle,            /* handle                        */
        unsigned short * pNumEntries,        /* count                         */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Drop Database                 */
  sqledrpd_api (
        _SQLOLDCHAR * pDbAlias,              /* database alias                */
        _SQLOLDCHAR * pReserved2,            /* reserved                      */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Set intra query parallelism   */
                                             /* degree                        */
  sqlesdeg_api (
        long NumAgentIds,                    /* number of agents to update    */
        unsigned long * pAgentIds,           /* array of agent ids            */
        long Degree,                         /* degree of parallelism         */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Force Users                   */
  sqlefrce_api (
        long NumAgentIds,                    /* number of users to force      */
        unsigned long * pAgentIds,           /* array of agent ids            */
        unsigned short ForceMode,            /* mode of operation             */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Catalog DCS Database          */
  sqlegdad_api (
        struct sql_dir_entry * pDCSDirEntry, /* pointer to entry structure    */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Close DCS Directory Scan      */
  sqlegdcl_api (
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Uncatalog DCS Database        */
  sqlegdel_api (
        struct sql_dir_entry * pDCSDirEntry, /* pointer to entry structure    */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Get DCS Directory Entry For   */
                                             /* Database                      */
  sqlegdge_api (
        struct sql_dir_entry * pDCSDirEntry, /* pointer to entry structure    */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Get DCS Directory Entries     */
  sqlegdgt_api (
        short * pNumEntries,                 /* pointer to count variable     */
        struct sql_dir_entry * pDCSDirEntries, /* pointer to entry structure  */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Open DCS Directory Scan       */
  sqlegdsc_api (
        short * pNumEntries,                 /* pointer to count variable     */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Get Instance                  */
  sqlegins_api (
        _SQLOLDCHAR * pInstance,             /* pointer to instance name      */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_INTR                      /* Interrupt                     */
        sqleintr_api ( void );

SQL_API_RC SQL_API_FN                        /* Install Signal Handler        */
  sqleisig_api (
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Free Memory                   */
  sqlefmem_api (
        struct sqlca * pSqlca,               /* SQLCA                         */
        void * pBuffer);                     /* buffer pointer                */

SQL_API_RC SQL_API_FN                        /* Migrate Database              */
  sqlemgdb_api (
        _SQLOLDCHAR * pDbAlias,              /* database alias                */
        _SQLOLDCHAR * pUserName,             /* user name                     */
        _SQLOLDCHAR * pPassword,             /* password                      */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Activate Database             */
  sqle_activate_db_api (
        char * pDbAlias,                     /* database alias                */
        char * pUserName,                    /* user name                     */
        char * pPassword,                    /* password                      */
        void * pReserved,                    /* Reserved for future use       */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Deactivate Database           */
  sqle_deactivate_db_api (
        char * pDbAlias,                     /* database alias                */
        char * pUserName,                    /* user name                     */
        char * pPassword,                    /* password                      */
        void * pReserved,                    /* Reserved for future use       */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Close Node Directory Scan     */
  sqlencls_api (
        unsigned short Handle,               /* handle                        */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Get Next Node Directory       */
                                             /* Entry                         */
  sqlengne_api (
        unsigned short Handle,               /* handle                        */
        struct sqleninfo ** ppNodeDirEntry,  /* buffer                        */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Open Node Directory Scan      */
  sqlenops_api (
        unsigned short * pHandle,            /* handle                        */
        unsigned short * pNumEntries,        /* count                         */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Database Application Remote   */
                                             /* Interface                     */
  sqleproc_api (
        char * pProgramName,                 /* Path of program to run        */
        struct sqlchar * pInput,             /* variable length area ptr      */
        struct sqlda * pInputSqlda,          /* input SQLDA                   */
        struct sqlda * pOutputSqlda,         /* output SQLDA                  */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Restart Database              */
  sqlerstd_api (
        _SQLOLDCHAR * pDbAlias,              /* database alias                */
        _SQLOLDCHAR * pUserName,             /* user name                     */
        _SQLOLDCHAR * pPassword,             /* password                      */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* V5 Start Database Manager     */
  sqlepstart_api (
        struct sqle_start_options * pStartOptions, /* start options           */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* V5 Stop Database Manager      */
  sqlepstp_api (
        struct sqledbstopopt * pStopOptions, /* STOP OPTIONS                  */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Uncatalog Database            */
  sqleuncd_api (
        _SQLOLDCHAR * pDbAlias,              /* database alias                */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Uncatalog Node                */
  sqleuncn_api (
        _SQLOLDCHAR * pNodeName,             /* node name                     */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Set Client                    */
  sqlesetc_api (
        struct sqle_conn_setting * pConnectionSettings, /* conn setting       */
                                             /* array                         */
        unsigned short NumSettings,          /* number of settings            */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Query Client                  */
  sqleqryc_api (
        struct sqle_conn_setting * pConnectionSettings, /* conn setting       */
                                             /* array                         */
        unsigned short NumSettings,          /* number of settings            */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Create Database               */
  sqlecrea_api (
        char * pDbName,                      /* database                      */
        char * pLocalDbAlias,                /* local alias                   */
        char * pPath,                        /* drive/path                    */
        struct sqledbdesc * pDbDescriptor,   /* database descriptor block     */
        struct sqledbcountryinfo * pCountryInfo, /* db locale and codeset     */
        char Reserved2,                      /* reserved                      */
        void * pReserved1,                   /* reserved                      */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Attach                        */
  sqleatin_api (
        char * pNodeName,                    /* node name                     */
        char * pUserName,                    /* user name                     */
        char * pPassword,                    /* password                      */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Detach                        */
  sqledtin_api (
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Set Accounting String         */
  sqlesact_api (
        char * pAccountingString,            /* accounting string             */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Register DB2 Server           */
  sqleregs_api (
        unsigned short Registry,             /* location at which to reg      */
        void * pRegisterInfo,                /* register info.                */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Deregister DB2 Server         */
  sqledreg_api (
        unsigned short Registry,             /* location at which to dereg    */
        void * pRegisterInfo,                /* deregister info.              */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Add Node                      */
  sqleaddn_api (
        void * pAddNodeOptions,              /* add node options              */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Create Database at Node       */
  sqlecran_api (
        char * pDbName,                      /* database name                 */
        void * pReserved,                    /* reserved                      */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Drop Database at Node         */
  sqledpan_api (
        char * pDbAlias,                     /* database alias                */
        void * pReserved,                    /* reserved                      */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Drop Node Verify              */
  sqledrpn_api (
        unsigned short Action,               /* Action                        */
        void * pReserved,                    /* reserved                      */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Set Application Priority      */
  sqlesapr_api (
        unsigned long agentId,               /* agentid of application coord  */
        long priorityLevel,                  /* priority level                */
        unsigned short priorityType,         /* priority type                 */
        struct sqlca * pSqlca);              /* SQLCA                         */

/* GENERIC INTERFACES                                                         */

SQL_API_RC SQL_API_FN                        /* Change Database Comment       */
  sqlgdcgd (
        unsigned short CommentLen,           /* comment length                */
        unsigned short PathLen,              /* drive/path length             */
        unsigned short DbAliasLen,           /* database length               */
        struct sqlca * pSqlca,               /* SQLCA                         */
        _SQLOLDCHAR * pComment,              /* comment                       */
        _SQLOLDCHAR * pPath,                 /* drive/path                    */
        _SQLOLDCHAR * pDbAlias);             /* database                      */

SQL_API_RC SQL_API_FN                        /* Close Directory Scan          */
  sqlgdcls (
        unsigned short Handle,               /* handle                        */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Get Next Database Directory   */
                                             /* Entry                         */
  sqlgdgne (
        unsigned short Handle,               /* handle                        */
        struct sqledinfo ** ppDbDirEntry,    /* buffer                        */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Drop Database                 */
  sqlgdrpd (
        unsigned short Reserved1,            /* reserved                      */
        unsigned short DbAliasLen,           /* database alias length         */
        struct sqlca * pSqlca,               /* SQLCA                         */
        _SQLOLDCHAR * pReserved2,            /* reserved                      */
        _SQLOLDCHAR * pDbAlias);             /* database alias                */

SQL_API_RC SQL_API_FN                        /* Open Directory Scan           */
  sqlgdosd (
        unsigned short PathLen,              /* drive/path length             */
        struct sqlca * pSqlca,               /* SQLCA                         */
        unsigned short * pNumEntries,        /* count                         */
        unsigned short * pHandle,            /* handle                        */
        _SQLOLDCHAR * pPath);                /* drive/path                    */

SQL_API_RC SQL_API_FN                        /* Set parallelism degree        */
  sqlgsdeg (
        struct sqlca * pSqlca,               /* SQLCA                         */
        long Degree,                         /* mode of operation             */
        unsigned long * pAgentIds,           /* array of agent ids            */
        long NumAgentIds);                   /* num of users to force         */

SQL_API_RC SQL_API_FN                        /* Force Users                   */
  sqlgfrce (
        struct sqlca * pSqlca,               /* SQLCA                         */
        unsigned short ForceMode,            /* mode of operation             */
        unsigned long * pAgentIds,           /* array of agent ids            */
        long NumAgentIds);                   /* num of users to force         */

SQL_API_RC SQL_API_FN                        /* Catalog DCS Database          */
  sqlggdad (
        struct sqlca * pSqlca,               /* SQLCA                         */
        struct sql_dir_entry * pDCSDirEntry); /* directory entry              */

SQL_API_RC SQL_API_FN                        /* Close DCS Directory Scan      */
  sqlggdcl (
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Uncatalog DCS Database        */
  sqlggdel (
        struct sqlca * pSqlca,               /* SQLCA                         */
        struct sql_dir_entry * pDCSDirEntry); /* directory entry              */

SQL_API_RC SQL_API_FN                        /* Get DCS Directory Entry For   */
                                             /* Database                      */
  sqlggdge (
        struct sqlca * pSqlca,               /* SQLCA                         */
        struct sql_dir_entry * pDCSDirEntry); /* directory entry              */

SQL_API_RC SQL_API_FN                        /* Get DCS Directory Entries     */
  sqlggdgt (
        struct sqlca * pSqlca,               /* SQLCA                         */
        short * pNumEntries,                 /* count variable                */
        struct sql_dir_entry * pDCSDirEntries); /* entry structure            */

SQL_API_RC SQL_API_FN                        /* Open DCS Directory Scan       */
  sqlggdsc (
        struct sqlca * pSqlca,               /* SQLCA                         */
        short * pNumEntries);                /* count variable                */

SQL_API_RC SQL_API_FN                        /* Get Instance                  */
  sqlggins (
        struct sqlca * pSqlca,               /* SQLCA                         */
        _SQLOLDCHAR * pInstance);            /* pointer to instance name      */

SQL_API_RC SQL_API_FN                        /* Catalog Database              */
  sqlgctdd (
        unsigned short CommentLen,           /* comment length                */
        unsigned short PathLen,              /* drive/path length             */
        unsigned short NodeNameLen,          /* node name length              */
        unsigned short DbAliasLen,           /* alias length                  */
        unsigned short DbNameLen,            /* database length               */
        struct sqlca * pSqlca,               /* SQLCA                         */
        unsigned short Authentication,       /* authentication                */
        _SQLOLDCHAR * pComment,              /* comment                       */
        _SQLOLDCHAR * pPath,                 /* drive/path                    */
        _SQLOLDCHAR * pNodeName,             /* node name                     */
        unsigned char Type,                  /* type                          */
        _SQLOLDCHAR * pDbAlias,              /* alias                         */
        _SQLOLDCHAR * pDbName);              /* database                      */

SQL_API_RC SQL_API_FN                        /* Catalog Database              */
  sqlgcadb (
        unsigned short DCEPrinLen,           /* DCE principal length          */
        unsigned short CommentLen,           /* comment length                */
        unsigned short PathLen,              /* drive/path length             */
        unsigned short NodeNameLen,          /* node name length              */
        unsigned short DbAliasLen,           /* alias length                  */
        unsigned short DbNameLen,            /* database length               */
        struct sqlca * pSqlca,               /* SQLCA                         */
        _SQLOLDCHAR * pDcePrin,              /* DCE Principal Name            */
        unsigned short Authentication,       /* authentication                */
        _SQLOLDCHAR * pComment,              /* comment                       */
        _SQLOLDCHAR * pPath,                 /* drive/path                    */
        _SQLOLDCHAR * pNodeName,             /* node name                     */
        unsigned char Type,                  /* type                          */
        _SQLOLDCHAR * pDbAlias,              /* alias                         */
        _SQLOLDCHAR * pDbName);              /* database                      */

SQL_API_RC SQL_API_FN                        /* Catalog Node                  */
  sqlgctnd (
        struct sqlca * pSqlca,               /* SQLCA                         */
        struct sqle_node_struct * pNodeInfo, /* node structure                */
        void * pProtocolInfo);               /* Protocol Structure            */

SQL_API_RC SQL_API_FN                        /* Interrupt                     */
  sqlgintr (
        void);

SQL_API_RC SQL_API_FN                        /* Install Signal Handler        */
  sqlgisig (
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Migrate Database              */
  sqlgmgdb (
        unsigned short PasswordLen,          /* password length               */
        unsigned short UserNameLen,          /* user name length              */
        unsigned short DbAliasLen,           /* database alias length         */
        struct sqlca * pSqlca,               /* SQLCA                         */
        _SQLOLDCHAR * pPassword,             /* password                      */
        _SQLOLDCHAR * pUserName,             /* user name                     */
        _SQLOLDCHAR * pDbAlias);             /* database alias                */

SQL_API_RC SQL_API_FN                        /* Activate Database             */
  sqlg_activate_db (
        unsigned short DbAliasLen,           /* database alias length         */
        unsigned short UserNameLen,          /* user name length              */
        unsigned short PasswordLen,          /* password length               */
        char * pDbAlias,                     /* database alias                */
        char * pUserName,                    /* user name                     */
        char * pPassword,                    /* password                      */
        void * pReserved,                    /* reserved                      */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Deactivate Database           */
  sqlg_deactivate_db (
        unsigned short DbAliasLen,           /* database alias length         */
        unsigned short UserNameLen,          /* user name length              */
        unsigned short PasswordLen,          /* password length               */
        char * pDbAlias,                     /* database alias                */
        char * pUserName,                    /* user name                     */
        char * pPassword,                    /* password                      */
        void * pReserved,                    /* reserved                      */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Close Node Directory Scan     */
  sqlgncls (
        unsigned short Handle,               /* handle                        */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Get Next Node Directory       */
                                             /* Entry                         */
  sqlgngne (
        unsigned short Handle,               /* handle                        */
        struct sqleninfo ** ppNodeDirEntry,  /* buffer                        */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Open Node Directory Scan      */
  sqlgnops (
        unsigned short * pHandle,            /* handle                        */
        unsigned short * pNumEntries,        /* count                         */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Database Application Remote   */
                                             /* Interface                     */
  sqlgproc (
        unsigned short ProgramNameLen,       /* program name length           */
        struct sqlca * pSqlca,               /* SQLCA                         */
        char * pProgramName,                 /* Path of program to run        */
        struct sqlda * pInputSqlda,          /* input SQLDA                   */
        struct sqlda * pOutputSqlda,         /* output SQLDA                  */
        struct sqlchar * pInput);            /* variable length area ptr      */

SQL_API_RC SQL_API_FN                        /* Restart Database              */
  sqlgrstd (
        unsigned short PasswordLen,          /* password length               */
        unsigned short UserNameLen,          /* user name length              */
        unsigned short DbAliasLen,           /* database alias length         */
        struct sqlca * pSqlca,               /* SQLCA                         */
        _SQLOLDCHAR * pPassword,             /* password                      */
        _SQLOLDCHAR * pUserName,             /* user name                     */
        _SQLOLDCHAR * pDbAlias);             /* database alias                */

SQL_API_RC SQL_API_FN                        /* Set Client                    */
  sqlgsetc (
        struct sqle_conn_setting * pConnectionSettings, /* conn setting       */
                                             /* array                         */
        unsigned short NumSettings,          /* number of settings            */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Query Client                  */
  sqlgqryc (
        struct sqle_conn_setting * pConnectionSettings, /* conn setting       */
                                             /* array                         */
        unsigned short NumSettings,          /* number of settings            */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Create Database               */
  sqlgcrea (
        unsigned short PathLen,              /* drive/path length             */
        unsigned short LocalDbAliasLen,      /* local alias length            */
        unsigned short DbNameLen,            /* database length               */
        struct sqlca * pSqlca,               /* SQLCA                         */
        void * pReserved1,                   /* reserved                      */
        unsigned short Reserved2,            /* reserved                      */
        struct sqledbcountryinfo * pCountryInfo, /* db locale and codeset     */
        struct sqledbdesc * pDbDescriptor,   /* db description block          */
        char * pPath,                        /* drive/path                    */
        char * pLocalDbAlias,                /* local alias                   */
        char * pDbName);                     /* database                      */

SQL_API_RC SQL_API_FN                        /* Attach                        */
  sqlgatin (
        unsigned short PasswordLen,          /* password length               */
        unsigned short UserNameLen,          /* user name length              */
        unsigned short NodeNameLen,          /* node name length              */
        struct sqlca * pSqlca,               /* SQLCA                         */
        char * pPassword,                    /* password                      */
        char * pUserName,                    /* user name                     */
        char * pNodeName);                   /* node name                     */

SQL_API_RC SQL_API_FN                        /* Detach                        */
  sqlgdtin (
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* V5 Start Database Manager     */
  sqlgpstart (
        struct sqle_start_options * pStartOptions, /* start options           */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* V5 Stop Database Manager      */
  sqlgpstp (
        struct sqledbstopopt * pStopOptions, /* STOP OPTIONS                  */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Uncatalog Database            */
  sqlguncd (
        unsigned short DbAliasLen,           /* database alias length         */
        struct sqlca * pSqlca,               /* SQLCA                         */
        _SQLOLDCHAR * pDbAlias);             /* database alias                */

SQL_API_RC SQL_API_FN                        /* Uncatalog Node                */
  sqlguncn (
        unsigned short NodeNameLen,          /* node name length              */
        struct sqlca * pSqlca,               /* SQLCA                         */
        _SQLOLDCHAR * pNodeName);            /* node name                     */

SQL_API_RC SQL_API_FN                        /* Set Accounting String         */
  sqlgsact (
        unsigned short AccountingStringLen,  /* accounting string length      */
        char * pAccountingString,            /* accounting string             */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Register DB2 Server           */
  sqlgregs (
        unsigned short Registry,             /* location at which to reg      */
        void * pRegisterInfo,                /* register info.                */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Deregister DB2 Server         */
  sqlgdreg (
        unsigned short Registry,             /* location at which to dereg    */
        void * pRegisterInfo,                /* deregister info.              */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Free Memory                   */
  sqlgfmem (
        struct sqlca * pSqlca,               /* SQLCA                         */
        void * pBuffer);                     /* buffer pointer                */

SQL_API_RC SQL_API_FN                        /* Add Node                      */
  sqlgaddn (
        unsigned short addnOptionsLen,       /* options length                */
        struct sqlca * pSqlca,               /* SQLCA                         */
        void * pAddNodeOptions);             /* add node options              */

SQL_API_RC SQL_API_FN                        /* Create Database at Node       */
  sqlgcran (
        unsigned short reservedLen,          /* reserved length               */
        unsigned short dbNameLen,            /* database name length          */
        struct sqlca * pSqlca,               /* SQLCA                         */
        void * pReserved,                    /* reserved                      */
        char * pDbName);                     /* database name                 */

SQL_API_RC SQL_API_FN                        /* Drop Database at Node         */
  sqlgdpan (
        unsigned short Reserved1,            /* reserved                      */
        unsigned short DbAliasLen,           /* database alias length         */
        struct sqlca * pSqlca,               /* SQLCA                         */
        void * pReserved2,                   /* reserved                      */
        char * pDbAlias);                    /* database alias                */

SQL_API_RC SQL_API_FN                        /* Drop Node Verify              */
  sqlgdrpn (
        unsigned short Reserved1,            /* reserved                      */
        struct sqlca * pSqlca,               /* SQLCA                         */
        void * pReserved2,                   /* reserved                      */
        unsigned short Action);              /* Action                        */

/* SQL Return Codes in SQLCODE for Environment Commands                       */

#ifndef SQL_RC_OK
#define SQL_RC_OK 0 /* everything is ok */
#endif /* SQL_RC_OK */

#ifndef SQL_RC_INVALID_SQLCA
#define SQL_RC_INVALID_SQLCA -1 /* invalid sqlca */
#endif /* SQL_RC_INVALID_SQLCA */

#define SQLE_RC_STILL_EXECUTING 16           /* Request is still executing    */
#define SQLE_RC_INLUW  -752                  /* Connect to other DB not       */
                                             /* allowed                       */
#define SQLE_RC_W863   863                   /* Only SBCS data allowed        */

#define SQLE_RC_E953   -953                  /* Agent heap too small          */
#define SQLE_RC_E957   -957                  /* Requestor comm heap too       */
                                             /* small                         */
#define SQLE_RC_E959   -959                  /* Server comm heap too small    */
#define SQLE_RC_E961   -961                  /* Rqstr remote svcs heap too    */
                                             /* small                         */
#define SQLE_RC_E962   -962                  /* Svr remote svcs heap too      */
                                             /* small                         */
#define SQLE_RC_NO_APP_CTRL_SEG -987         /* Application control shared    */
                                             /* memory set cannot be          */
                                             /* allocated                     */

#define SQLE_RC_INVNEWLOGP 993               /* New log path is invalid       */
#define SQLE_RC_INVLOGP 995                  /* Current log path is invalid   */

#define SQLE_RC_INVALIAS -1000               /* Invalid alias                 */
#define SQLE_RC_INVDBNAME -1001              /* Invalid database name         */
#define SQLE_RC_INVDRIVE -1002               /* Invalid drive                 */

#define SQLE_RC_INVPSW_DB2OS2 -1003          /* Invalid password - OS/2       */
#define SQLE_RC_INVPSW_DB2NT -1003           /* Invalid password - NT         */
#define SQLE_RC_INVPSW_DB2DOS -1003          /* Invalid password - DOS        */
#define SQLE_RC_INVPSW_DB2WIN -1003          /* Invalid password - Windows    */
#define SQLE_RC_INVPSW_DB2MAC -1003          /* Invalid password - Mac        */
#define SQLE_RC_INVPSW_DB2AIX -10002         /* Invalid password - AIX        */

#define SQLE_RC_INVPSW SQLE_RC_INVPSW_DB2NT

#define SQLE_RC_INSSTOR -1004                /* Insuf storage on file system  */
#define SQLE_RC_DUPALIAS -1005               /* Duplicate alias               */
#define SQLE_RC_WRONGCODEPG -1006            /* Appl code page does not       */
                                             /* match db                      */
#define SQLE_RC_INV_NEWPSW -1008             /* Invalid new password          */
#define SQLE_RC_INVREMOTE -1009              /* Invalid remote command        */

#define SQLE_RC_INVTYPE -1010                /* Invalid type                  */
#define SQLE_RC_NODRIVE -1011                /* No drive for indirect entry   */
#define SQLE_RC_NONODE -1012                 /* No nodename for remote entry  */
#define SQLE_RC_NODB   -1013                 /* Alias or database name not    */
                                             /* found                         */
#define SQLE_RC_NOMORE 1014                  /* No more entries               */
#define SQLE_RC_DB_RESTART -1015             /* Database needs restart        */
#define SQLE_RC_INVLLU -1016                 /* Invalid local_lu alias        */
#define SQLE_RC_INVMODE -1017                /* Invalid mode                  */
#define SQLE_RC_DUPNODE -1018                /* Duplicate node name           */
#define SQLE_RC_INVNODE -1019                /* Invalid node name             */

#define SQLE_RC_MAXNODE -1020                /* Node could not be cataloged   */
#define SQLE_RC_NOTNODE -1021                /* Nodename not found            */

#define SQLE_RC_INSSYS_DB2OS2 -1022          /* Insuf system resources - OS   */
                                             /* 2                             */
#define SQLE_RC_INSSYS_DB2NT -1022           /* Insuf system resources - NT   */
#define SQLE_RC_INSSYS_DB2DOS -1022          /* Insuf system resources - DOS  */
#define SQLE_RC_INSSYS_DB2WIN -1022          /* Insuf system resources -      */
                                             /* Windows                       */
#define SQLE_RC_INSSYS_DB2MAC -1022          /* Insuf system resources -      */
                                             /* Macintosh                     */
#define SQLE_RC_INSSYS_DB2AIX -10003         /* Insuf system resources - AIX  */

#define SQLE_RC_INSSYS SQLE_RC_INSSYS_DB2NT

#define SQLE_RC_NOCONV -1023                 /* Communication conversation    */
                                             /* failed                        */
#define SQLE_RC_NOSUDB -1024                 /* No database connection        */
                                             /* exists                        */
#define SQLE_RC_DBACT  -1025                 /* Databases are active          */
#define SQLE_RC_INVSTRT -1026                /* Database manager already      */
                                             /* started                       */
#define SQLE_RC_NONODEDIR -1027              /* Node directory not found      */
#define SQLE_RC_INVRLU -1029                 /* Partner lu not specified      */

#define SQLE_RC_MAXDB  -1030                 /* Database directory is full    */
#define SQLE_RC_NODBDIR -1031                /* Database directory not found  */
#define SQLE_RC_NOSTARTG -1032               /* Database manager not started  */
#define SQLE_RC_DIRBUSY -1033                /* Database directory being      */
                                             /* updated                       */
#define SQLE_RC_DBBAD  -1034                 /* Database is damaged           */
#define SQLE_RC_DB_INUSE -1035               /* Database already in use       */
#define SQLE_RC_FILEDB -1036                 /* Database file error           */
#define SQLE_RC_NODE_DIR_EMPTY 1037          /* No entry in Node directory    */
#define SQLE_RC_FILENODE -1038               /* Node directory file error     */

#define SQLE_RC_FILEDIR_DB2OS2 -1039         /* Directory file error - OS/2   */
#define SQLE_RC_FILEDIR_DB2NT -1039          /* Directory file error - NT     */
#define SQLE_RC_FILEDIR_DB2DOS -1039         /* Directory file error - DOS    */
#define SQLE_RC_FILEDIR_DB2WIN -1039         /* Directory file error -        */
                                             /* Windows                       */
#define SQLE_RC_FILEDIR_DB2MAC -1039         /* Directory file error - Mac    */
#define SQLE_RC_FILEDIR_DB2AIX -10004        /* Directory file error - AIX    */

#define SQLE_RC_FILEDIR SQLE_RC_FILEDIR_DB2NT

#define SQLE_RC_MAXAPPLS -1040               /* Max number of applications    */
                                             /* reached                       */
#define SQLE_RC_MAXDBS -1041                 /* Max number of databases       */
                                             /* started                       */
#define SQLE_RC_SYSERR -1042                 /* System error                  */
#define SQLE_RC_CATBOOT -1043                /* Catalog bootstrap failure     */
#define SQLE_RC_INTRRPT -1044                /* Request interrupted by        */
                                             /* ctrl+break                    */
#define SQLE_RC_INVINDIR -1045               /* Invalid level of indirection  */
#define SQLE_RC_INVAUTHID -1046              /* Invalid userid                */
#define SQLE_RC_APCONN -1047                 /* Appl already connect to       */
                                             /* another db                    */

#define SQLE_RC_USEINVALID_DB2OS2 -1048      /* Invalid use specified - OS/2  */
#define SQLE_RC_USEINVALID_DB2NT -1048       /* Invalid use specified - NT    */
#define SQLE_RC_USEINVALID_DB2DOS -1048      /* Invalid use specified - DOS   */
#define SQLE_RC_USEINVALID_DB2WIN -1048      /* Invalid use specified -       */
                                             /* Windows                       */
#define SQLE_RC_USEINVALID_DB2MAC -1048      /* Invalid use specified -       */
                                             /* MacOS                         */
#define SQLE_RC_USEINVALID_DB2AIX -10005     /* Invalid use specified - AIX   */

#define SQLE_RC_USEINVALID SQLE_RC_USEINVALID_DB2NT

#define SQLE_RC_APPSERR -900                 /* Appl state in error           */

#define SQLE_RC_UNCHOME -1050                /* Cannot uncatalog 'Home'       */
                                             /* database                      */
#define SQLE_RC_NODIRDRV -1051               /* Db direct. drive does not     */
                                             /* exist                         */
#define SQLE_RC_NODBDRV -1052                /* Database drive does not       */
                                             /* exist                         */
#define SQLE_RC_INTBUSY -1053                /* Interrupt already in          */
                                             /* progress                      */
#define SQLE_RC_COMMINP -1054                /* Commit in progress - no       */
                                             /* int's                         */
#define SQLE_RC_ROLLINP -1055                /* Rollback in progress - no     */
                                             /* int's                         */
#define SQLE_RC_NOINTER -1360                /* Cannot be interrupted - no    */
                                             /* int's                         */
#define SQLE_RC_TIMEOUT 1361                 /* Windows Client Execution      */
                                             /* Timeout                       */
#define SQLE_RC_MAXSCAN -1056                /* Maximum allowable scans       */
                                             /* exceeded                      */
#define SQLE_RC_NODENTRY 1057                /* No entries in directory       */
#define SQLE_RC_INVHAND -1058                /* Invalid input handle          */
#define SQLE_RC_NOSCAN -1059                 /* Open scan not issued          */

#define SQLE_RC_NOCONNECT -1060              /* User lacks connect privilege  */
#define SQLE_RC_RESTART_WITH_INDOUBTS 1061   /* RESTART was successful, but   */
                                             /* indoubt transactions exist    */
#define SQLE_RC_BADPATH -1062                /* Database path not found       */
#define SQLE_RC_START_OK -1063               /* Database manager started OK   */
#define SQLE_RC_STOP_OK -1064                /* Database manager stopped OK   */
#define SQLE_RC_DB_BADBINDS 1065             /* N utilities not bound         */

#define SQLE_RC_NOMSG_DB2OS2 -1068           /* Message file not found - OS   */
                                             /* 2                             */
#define SQLE_RC_NOMSG_DB2NT -1068            /* Message file not found - NT   */
#define SQLE_RC_NOMSG_DB2DOS -1068           /* Message file not found - DOS  */
#define SQLE_RC_NOMSG_DB2WIN -1068           /* Message file not found -      */
                                             /* Windows                       */
#define SQLE_RC_NOMSG_DB2MAC -1068           /* Message file not found -      */
                                             /* MacOS                         */
#define SQLE_RC_NOMSG_DB2AIX -10007          /* Message file not found - AIX  */

#define SQLE_RC_NOMSG  SQLE_RC_NOMSG_DB2NT

#define SQLE_RC_INVDROP -1069                /* DB invalid type for Drop      */

#define SQLE_RC_INVDBNAME_PTR -1070          /* Invalid Database Name         */
                                             /* pointer                       */
#define SQLE_RC_INVALIAS_PTR -1071           /* Invalid Alias pointer         */
#define SQLE_RC_RESOURCE_ERROR -1072         /* Resources in inconsistent     */
                                             /* state                         */
#define SQLE_RC_BAD_ND_REL -1073             /* Invalid Node Directory        */
                                             /* release                       */
#define SQLE_RC_INVPSW_PTR -1074             /* Invalid Password pointer      */
#define SQLE_RC_INVCOMM_PTR -1075            /* Invalid Comment pointer       */
#define SQLE_RC_INVCNT_PTR -1076             /* Invalid Count pointer         */
#define SQLE_RC_INVHAND_PTR -1077            /* Invalid Handle pointer        */
#define SQLE_RC_INVBUFF_PTR -1078            /* Invalid Buffer pointer        */
#define SQLE_RC_INVNODE_PTR -1079            /* Invalid Node pointer          */
#define SQLE_RC_INVUSERID_PTR -1150          /* Invalid Userid pointer        */

#define SQLE_RC_INVLLU_PTR -1080             /* Invalid Local Lu pointer      */
#define SQLE_RC_INVRLU_PTR -1081             /* Invalid Remote Lu pointer     */
#define SQLE_RC_INVMODE_PTR -1082            /* Invalid Mode pointer          */
#define SQLE_RC_BAD_DBDB -1083               /* Bad Database Description      */
                                             /* Block                         */
#define SQLE_RC_KSEGSFAIL -1084              /* Cannot Allocate Kernel        */
                                             /* Segments                      */
#define SQLE_RC_APPHEAPFAIL -1085            /* Cannot Allocate Application   */
                                             /* heap                          */
#define SQLE_RC_OS2ERROR -1086               /* Unexpected OS/2 error         */
#define SQLE_RC_BIND_LIST 1087               /* Bind list could not be        */
                                             /* opened                        */
#define SQLE_RC_BIND_ERROR 1088              /* Error occurred during bind    */
#define SQLE_RC_BIND_INTRRPT 1089            /* Binding was interrupted       */

#define SQLE_RC_BAD_APP_REL -1090            /* Release number of appl is     */
                                             /* invalid                       */
#define SQLE_RC_BAD_DB_REL -1091             /* Release number of database    */
                                             /* bad                           */

#define SQLE_RC_INSAUTH -1092                /* Authorization error           */
#define SQLE_RC_NOLOGON -1093                /* User not logged on            */
#define SQLE_RC_NDBUSY -1094                 /* Node directory being updated  */
#define SQLE_RC_MAX_NDSCAN -1095             /* Max node scans open           */
#define SQLE_RC_REQTYPE -1096                /* Invalid type for requester    */
                                             /* node                          */
#define SQLE_RC_NODERR -1097                 /* Node not found for remote db  */
#define SQLE_RC_APCONN_SAME -1098            /* Appl is already connected to  */
                                             /* db                            */

#define SQLE_RC_WRPROT_ERR_DB2OS2 -1099      /* Write protect error on        */
                                             /* diskette                      */
#define SQLE_RC_WRPROT_ERR_DB2NT -1099       /* Write protect error on        */
                                             /* diskette                      */
#define SQLE_RC_WRPROT_ERR_DB2DOS -1099      /* Write protect error on        */
                                             /* diskette                      */
#define SQLE_RC_WRPROT_ERR_DB2WIN -1099      /* Write protect error on        */
                                             /* diskette                      */
#define SQLE_RC_WRPROT_ERR_DB2MAC -1099      /* Write protect error on        */
                                             /* diskette                      */
#define SQLE_RC_WRPROT_ERR_DB2AIX -10021     /* Write protect error on        */
                                             /* filesystem                    */

#define SQLE_RC_WRPROT_ERR SQLE_RC_WRPROT_ERR_DB2NT

#define SQLE_RC_NODE_WARN 1100               /* Node not cataloged for        */
                                             /* database                      */
#define SQLE_RC_REMCONN_ERR -1101            /* Remote communications error   */
#define SQLE_RC_MIG_NODB -1102               /* No database name provided in  */
                                             /* call                          */
#define SQLE_RC_MIG_OK 1103                  /* Migration was successful      */
#define SQLE_RC_INVPROG_PTR -1104            /* Invalid program name pointer  */

#define SQLE_RC_INV_SPDB_DB2OS2 -1105        /* Invalid disconnect from       */
                                             /* database                      */
#define SQLE_RC_INV_SPDB_DB2NT -1105         /* Invalid disconnect from       */
                                             /* database                      */
#define SQLE_RC_INV_SPDB_DB2DOS -1105        /* Invalid disconnect from       */
                                             /* database                      */
#define SQLE_RC_INV_SPDB_DB2WIN -1105        /* Invalid disconnect from       */
                                             /* database                      */
#define SQLE_RC_INV_SPDB_DB2MAC -1105        /* Invalid disconnect from       */
                                             /* database                      */
#define SQLE_RC_INV_SPDB_DB2AIX -10017       /* Invalid disconnect from       */
                                             /* database                      */

#define SQLE_RC_INV_SPDB SQLE_RC_INV_SPDB_DB2NT

#define SQLE_RC_INVALID_PROC_DB2OS2 -1106    /* Function could not be         */
                                             /* executed                      */
#define SQLE_RC_INVALID_PROC_DB2NT -1106     /* Function could not be         */
                                             /* executed                      */
#define SQLE_RC_INVALID_PROC_DB2DOS -1106    /* Function could not be         */
                                             /* executed                      */
#define SQLE_RC_INVALID_PROC_DB2WIN -1106    /* Function could not be         */
                                             /* executed                      */
#define SQLE_RC_INVALID_PROC_DB2MAC -1106    /* Function could not be         */
                                             /* executed                      */
#define SQLE_RC_INVALID_PROC_DB2AIX -10010   /* Function could not be         */
                                             /* executed                      */

#define SQLE_RC_INVALID_PROC SQLE_RC_INVALID_PROC_DB2NT

#define SQLE_RC_INTRP_PROC_DB2OS2 -1107      /* Program interrupted - OS/2    */
#define SQLE_RC_INTRP_PROC_DB2NT -1107       /* Program interrupted - NT      */
#define SQLE_RC_INTRP_PROC_DB2DOS -1107      /* Program interrupted - DOS     */
#define SQLE_RC_INTRP_PROC_DB2WIN -1107      /* Program interrupted -         */
                                             /* Windows                       */
#define SQLE_RC_INTRP_PROC_DB2MAC -1107      /* Program interrupted - MacOS   */
#define SQLE_RC_INTRP_PROC_DB2AIX -10011     /* Program interrupted - AIX     */

#define SQLE_RC_INTRP_PROC SQLE_RC_INVALID_PROC_DB2NT

#define SQLE_RC_SYSERR_PROC_DB2OS2 -1108     /* System error on library load  */
#define SQLE_RC_SYSERR_PROC_DB2NT -1108      /* System error on library load  */
#define SQLE_RC_SYSERR_PROC_DB2DOS -1108     /* System error on library load  */
#define SQLE_RC_SYSERR_PROC_DB2WIN -1108     /* System error on library load  */
#define SQLE_RC_SYSERR_PROC_DB2MAC -1108     /* System error on library load  */
#define SQLE_RC_SYSERR_PROC_DB2AIX -10012    /* System error on library load  */

#define SQLE_RC_SYSERR_PROC SQLE_RC_SYSERR_PROC_DB2NT

#define SQLE_RC_NOFILE_PROC_DB2OS2 -1109     /* Library could not be loaded   */
#define SQLE_RC_NOFILE_PROC_DB2NT -1109      /* Library could not be loaded   */
#define SQLE_RC_NOFILE_PROC_DB2DOS -1109     /* Library could not be loaded   */
#define SQLE_RC_NOFILE_PROC_DB2WIN -1109     /* Library could not be loaded   */
#define SQLE_RC_NOFILE_PROC_DB2MAC -1109     /* Library could not be loaded   */
#define SQLE_RC_NOFILE_PROC_DB2AIX -10013    /* Library could not be loaded   */

#define SQLE_RC_NOFILE_PROC SQLE_RC_NOFILE_PROC_DB2NT

#define SQLE_RC_ERROR_PROC -1110             /* Program error                 */

#define SQLE_RC_BADPGN_PROC_DB2OS2 -1111     /* Invalid DARI prog name        */
                                             /* format                        */
#define SQLE_RC_BADPGN_PROC_DB2NT -1111      /* Invalid DARI prog name        */
                                             /* format                        */
#define SQLE_RC_BADPGN_PROC_DB2DOS -1111     /* Invalid DARI prog name        */
                                             /* format                        */
#define SQLE_RC_BADPGN_PROC_DB2WIN -1111     /* Invalid DARI prog name        */
                                             /* format                        */
#define SQLE_RC_BADPGN_PROC_DB2MAC -1111     /* Invalid DARI prog name        */
                                             /* format                        */
#define SQLE_RC_BADPGN_PROC_DB2AIX -10014    /* Invalid DARI prog name        */
                                             /* format                        */

#define SQLE_RC_BADPGN_PROC SQLE_RC_BADPGN_PROC_DB2NT

#define SQLE_RC_INSMEM_PROC_DB2OS2 -1112     /* Insuf memory to load lib      */
#define SQLE_RC_INSMEM_PROC_DB2NT -1112      /* Insuf memory to load lib      */
#define SQLE_RC_INSMEM_PROC_DB2DOS -1112     /* Insuf memory to load lib      */
#define SQLE_RC_INSMEM_PROC_DB2WIN -1112     /* Insuf memory to load lib      */
#define SQLE_RC_INSMEM_PROC_DB2MAC -1112     /* Insuf memory to load lib      */
#define SQLE_RC_INSMEM_PROC_DB2AIX -10015    /* Insuf memory to load lib      */

#define SQLE_RC_INSMEM_PROC SQLE_RC_INSMEM_PROC_DB2NT

#define SQLE_RC_SQLDA_DATATYPE -1113         /* Data type in output SQLDA     */
                                             /* changed                       */
#define SQLE_RC_SQLDA_LENGTH -1114           /* Data length in output SQLDA   */
                                             /* changed                       */
#define SQLE_RC_SQLDA_VARS -1115             /* Num of sqlvars changed in     */
                                             /* SQLDA                         */
#define SQLE_RC_BKP_PEND -1116               /* Backup pending                */
#define SQLE_RC_ROLLFWD_PEND -1117           /* Roll forward pending          */
#define SQLE_RC_BKP_INPROG -1118             /* Need to rerun the Backup      */
                                             /* process                       */
#define SQLE_RC_RST_INPROG -1119             /* Need to rerun the Restore     */
                                             /* process                       */
#define SQLE_RC_BR_INPROG -1120              /* Need to rerun either Backup   */
                                             /* or Restore process            */

#define SQLE_RC_INVNODESTR_PTR -1121         /* Invalid Node structure        */
                                             /* pointer                       */
#define SQLE_RC_INVPROTOCOL_PTR -1122        /* Invalid Protocol structure    */
                                             /* pointer                       */
#define SQLE_RC_INVPROTOCOL -1123            /* Invalid protocol type         */
#define SQLE_RC_INVRNNAME -1124              /* Invalid remote workstation    */
                                             /* name                          */
#define SQLE_RC_INVADAPTER -1125             /* Invalid adapter number        */
#define SQLE_RC_INVNETID -1126               /* Invalid network id            */
#define SQLE_RC_INVPLU -1127                 /* Invalid real partner LU name  */

#define SQLE_RC_DARI_INSSYS -1129            /* Insuf system resources for    */
                                             /* DARI                          */
#define SQLE_RC_DARI_MAXDARI -1130           /* Max DARI process limit        */
                                             /* reached                       */
#define SQLE_RC_DARI_ABEND -1131             /* DARI process abnormally       */
                                             /* terminated                    */
#define SQLE_RC_DARI_INV_RQST -1132          /* Invalid DB2 request in DARI   */
#define SQLE_RC_DARI_VAR_POINTER_CHG -1133   /* SQLVAR's sqldata or sqlind    */
                                             /* ptrs were altered             */
#define SQLE_RC_DARI_RQST_AUTH_ERR -1134     /* DB2 request is not allowed    */
                                             /* when DB auth is client        */
#define SQLE_RC_BAD_NUMSEGS -1135            /* Invalid numsegs on create db  */
#define SQLE_RC_BAD_EXTSIZE -1136            /* Invalid extSize on create db  */
#define SQLE_RC_MOUNTED_SEGS -1137           /* Mounted Segment Directories   */
                                             /* on a drop database request    */

#define SQLE_RC_INVOS_OBJ -1200              /* Invalid object specified      */
#define SQLE_RC_INVOS_STAT -1201             /* Invalid status specified      */
#define SQLE_RC_INVOS_NOSTAT -1202           /* Status has not been           */
                                             /* collected                     */
#define SQLE_RC_INVOS_NOUSER -1203           /* No users connected to         */
                                             /* database                      */
#define SQLE_RC_UNSUPP_CODEPG -1204          /* Active codepage is not        */
                                             /* supported                     */

#define SQLE_RC_INV_CNTRYINFO_DB2OS2 -1205   /* Invalid country information   */
#define SQLE_RC_INV_CNTRYINFO_DB2NT -1205    /* Invalid country information   */
#define SQLE_RC_INV_CNTRYINFO_DB2DOS -1205   /* Invalid country information   */
#define SQLE_RC_INV_CNTRYINFO_DB2WIN -1205   /* Invalid country information   */
#define SQLE_RC_INV_CNTRYINFO_DB2MAC -1205   /* Invalid country information   */
#define SQLE_RC_INV_CNTRYINFO_DB2AIX -10009  /* Invalid country information   */

#define SQLE_RC_INV_CNTRYINFO SQLE_RC_INV_CNTRYINFO_DB2NT
#define SQLE_RC_INV_COMPUTERNAME -1211       /* Invalid Computer Name         */
#define SQLE_RC_INV_INSTANCENAME -1212       /* Invalid Instance Name         */

#define SQLE_RC_NO_SHRD_SEG -1220            /* DB2 Shared Memory Set alloc   */
                                             /* failed                        */
#define SQLE_RC_NO_ASL_HEAP -1221            /* ASL heap cannot be allocated  */
#define SQLE_RC_ASL_TOO_SMALL -1222          /* ASL heap is too small         */
#define SQLE_RC_NO_AGENT_AVAIL -1223         /* No more agents available      */
#define SQLE_RC_AGENT_GONE -1224             /* DB2 agent not active          */
#define SQLE_RC_PROC_LIMIT -1225             /* Op. Sys. couldn't spawn a     */
                                             /* process                       */
#define SQLE_RC_MAXCOORDS -1226              /* Max number of coords reached  */
#define SQLE_RC_DROPDB_WARN 1228             /* Drop database warning         */

#define SQLE_RC_AGENT_NOT_FORCED 1230        /* At least one agent not        */
                                             /* forced                        */
#define SQLE_RC_INVCOUNT -1231               /* Invalid Force Users count     */
#define SQLE_RC_INVFRCE_MODE -1232           /* Invalid Force Users mode      */

#define SQLE_RC_INV_TBS_DESC -1241           /* Invalid TableSpace            */
                                             /* descriptor                    */

#define SQLE_RC_NO_SETCONNOPT -1246          /* Cannot set connection         */
                                             /* options - existing            */
                                             /* connections                   */

#define SQLE_RC_NOUEXIT -1267                /* db2uexit file not found       */

#define SQLC_RC_NPIPE_BROKEN               -1281
#define SQLC_RC_NPIPE_BUSY                 -1282
#define SQLC_RC_NPIPE_PIPE_INUSE           -1283
#define SQLC_RC_NPIPE_PIPE_NOT_FOUND       -1284
#define SQLC_RC_NPIPE_INVALID_NAME         -1285
#define SQLC_RC_NPIPE_NO_RESOURCE          -1286
#define SQLC_RC_NPIPE_INST_NOT_FOUND       -1287

#define SQLE_RC_DS_FAILED -1291              /* Directory Services failed     */
#define SQLE_RC_DS_BAD_GLB_NAME -1292        /* Bad global name               */
#define SQLE_RC_DS_BAD_GLB_DIR_ENTRY -1293   /* Bad global directory entry    */
#define SQLE_RC_DS_BAD_DIR_PATH_NAME -1294   /* Bad DIR_PATH_NAME             */
#define SQLE_RC_DS_BAD_ROUTE_NAME -1295      /* Bad ROUTE_OBJ_NAME            */
#define SQLE_RC_DS_UNSUPPORTED_CMD -1297     /* Command not supported         */

#define SQLE_RC_DCE_INVPN -1300              /* Invalid DCE principal name    */
#define SQLE_RC_DCE_ERR_KEYTAB -1301         /* Error DCE keytab file         */
#define SQLE_RC_DCE_ERR_MAPPING -1302        /* DCE principal and DB2 authid  */
                                             /* mapping error                 */
#define SQLE_RC_SECD_ERR_RESTART -1303       /* Security daemon could not be  */
                                             /* restarted                     */
#define SQLE_RC_INVSTCP -1304                /* Invalid security type for     */
                                             /* TCPIP protocol                */
#define SQLE_RC_DCE_ERR -1305                /* DCE internal error            */
#define SQLE_RC_DCE_INV_PRINC -1309          /* DCE invalid server principal  */
                                             /* name                          */

#define SQLE_RC_FILEDCS -1310                /* DCS Directory file access     */
                                             /* error                         */
#define SQLE_RC_DCSDIR_NF -1311              /* DCS Directory not found       */
#define SQLE_RC_NO_ENTRY 1312                /* DCS Directory is empty        */
#define SQLE_RC_MAX_ENTRY -1313              /* DCS Directory is full         */
#define SQLE_RC_INVENTRY_PTR -1314           /* Entry parameter pointer       */
                                             /* invalid                       */
#define SQLE_RC_INVLDB -1315                 /* Local DB name has invalid     */
                                             /* chars                         */
#define SQLE_RC_LDB_NF -1316                 /* DCS Directory entry not       */
                                             /* found                         */
#define SQLE_RC_DUPLDB -1317                 /* DCS Directory duplicate       */
                                             /* entry                         */
#define SQLE_RC_INVLENGTH -1318              /* Invalid element length        */
#define SQLE_RC_ENTRYNOT_COL -1319           /* Entries have not been         */
                                             /* collected                     */

#define SQLE_RC_GDBUSY -1320                 /* Cannot access DCS Dir at      */
                                             /* this time                     */
#define SQLE_RC_INVSTRUCT_ID -1321           /* Invalid structure ID          */
#define SQLE_RC_DRDANSP -1325                /* Remote function not           */
                                             /* supported                     */
#define SQLE_RC_ACCD   -1326                 /* File or directory access      */
                                             /* denied                        */
#define SQLE_RC_IMPLCONN_INVDB -1327         /* Implicit connect - invalid    */
                                             /* dbname                        */
#define SQLE_RC_IMPLCONN_NODB -1328          /* Implicit connect - alias not  */
                                             /* found                         */
#define SQLE_RC_PATH_TOO_LONG -1329          /* Input path too long           */

#define SQLE_RC_INVSDNAME -1330              /* Invalid symbolic destination  */
                                             /* name                          */
#define SQLE_RC_INVSTYPE -1331               /* Invalid CPIC security type    */
#define SQLE_RC_INV_HOSTNAME -1332           /* Invalid Host Name             */
#define SQLE_RC_INV_SERNAME -1333            /* Invalid Service Name          */

#define SQLE_RC_DOUBLE_REMOTE -1334          /* Double-hops not allowed       */
#define SQLE_RC_INVAR  -1335                 /* AR name has invalid chars     */

#define SQLE_RC_UNKNOWN_FILESERVER -1340     /* File server is unknown        */
#define SQLE_RC_INV_FSERVER -1342            /* Invalid File Server           */
#define SQLE_RC_INV_OBJNAME -1343            /* Invalid Object Name           */

#define SQLE_RC_BR_ACTIVE -1350              /* Backup or Restore is active   */

#define SQLE_RC_INV_INSTANCE -1390           /* Invalid Instance Name         */
#define SQLE_RC_INSTANCE_USING -1391         /* Another Instance is using     */
                                             /* the DB                        */
#define SQLE_RC_INV_DB2PATH -1393            /* Invalid DB2 Path Name         */

#define SQLE_RC_BAD_AUTH -1400               /* Unsupported authentication    */
                                             /* type                          */
#define SQLE_RC_DIFF_AUTH -1401              /* Authentication types do not   */
                                             /* match                         */
#define SQLE_RC_AUTH_ERR -1402               /* Authentication failed due to  */
                                             /* unexpected error              */
#define SQLE_RC_AUTH_FAILURE -1403           /* Invalid user name and/or      */
                                             /* password                      */
#define SQLE_RC_PASSWORD_EXPIRED -1404       /* Password has expired          */
#define SQLE_RC_PASSWORD_WITHOUT_USERID    -1425   /* Password without        */
                                                   /* userid                  */
#define SQLE_RC_DB2INSTDFT_ERROR -1426       /* Error getting DB2INSTDFT      */
#define SQLE_RC_NOT_INSTANCE_ATTACHED -1427  /* No current attachment         */
#define SQLE_RC_WRONG_ATTACH -1428           /* Attached to wrong instance    */
#define SQLE_RC_RELPATH_NOT_ALLOWED -1431    /* Relative path not allowed     */
#define SQLE_RC_WRONG_CONNECT -1433          /* Connected to wrong database   */

#define SQLE_RC_CTX_INV_PARM -1441           /* Ctx parm invalid              */
#define SQLE_RC_CTX_NOTINUSE -1442           /* App Ctx not in use            */
#define SQLE_RC_CTX_USING -1443              /* Already using Ctx             */
#define SQLE_RC_CTX_INUSE -1444              /* App Ctx in use                */
#define SQLE_RC_CTX_NO_CTX -1445             /* Thread does not have context  */

#define SQLE_RC_INVREGINFO_PTR -1450         /* Invalid registration info.    */
                                             /* ptr.                          */
#define SQLE_RC_REG_INVNODE -1451            /* Reg. issued from invalid      */
                                             /* node                          */
#define SQLE_RC_INVREGLOC -1452              /* Invalid registration          */
                                             /* location                      */
#define SQLE_RC_INVCFG_FSNAME -1453          /* Invalid file server in DBM    */
                                             /* cfg.                          */
#define SQLE_RC_INVCFG_OBJNAME -1454         /* Invalid object name in DBM    */
                                             /* cfg.                          */
#define SQLE_RC_INVCFG_IPXSOCKET -1455       /* Invalid IPX socket in DBM     */
                                             /* cfg.                          */
#define SQLE_RC_DUPLICATE_OBJNAME -1456      /* Object name already exists    */
#define SQLE_RC_NWDS_CONNEXISTS -1457        /* NWDS connection exists,       */
                                             /* cannot log into NW            */
                                             /* fileserver                    */
#define SQLE_RC_REG_NOT_NEEDED -1458         /* DB2 server reg./dereg. not    */
                                             /* needed                        */
#define SQLE_RC_INVSTYPE_TCP -1461           /* Invalid TCPIP Security        */

#define SQLE_RC_ONE_BUFFERPOOL 1478          /* Database is started but only  */
                                             /* one bufferpool is started     */

#define SQLE_RC_SECD_FAILURE -1525           /* An error occured when         */
                                             /* starting the DB2 security     */
                                             /* daemon                        */

#define SQLE_RC_UNSUPP_FUNCTION -1650        /* Function is no longer         */
                                             /* supported                     */

#define SQLE_RC_INV_SERVERLVL -1651          /* Invalid server level for      */
                                             /* request                       */
#define SQLE_RC_FILEIO_ERR -1652             /* File I/O error                */
#define SQLE_RC_INV_PROFILE_PATH -1653       /* Invalid profile path          */
#define SQLE_RC_INSTPATH_ERR -1654           /* Instance path error           */

#define SQLE_RC_GENERATOR_FAILED -1660       /* Generator failed              */

#define SQLE_RC_DSCVR_DISABLED -1670         /* Discover is disabled in DBM   */
                                             /* CFG                           */
#define SQLE_RC_SEARCH_DSCVR_FAILED -1671    /* Search discovery failed       */
#define SQLE_RC_INV_DSCVR_ADDRLST -1673      /* Invalid discover address      */
                                             /* list                          */
#define SQLE_RC_INV_DSCVR_ADDR -1674         /* Invalid discover address      */
#define SQLE_RC_INV_ADMINSERVER -1675        /* Invalid admin. server         */

#define SQLE_RC_INV_SCHEMA -1700             /* Invalid Schema name found     */
#define SQLE_RC_DB_NOT_MIGR -1701            /* DB cannot be migrated         */
#define SQLE_RC_CRT_EVENT_FAIL -1703         /* Fail to create db2event dir   */
#define SQLE_RC_DB_MIG_FAIL -1704            /* DB migration failed           */
#define SQLE_RC_UPDATE_DIR_FAIL 1705         /* Fail to update directory      */
                                             /* entry                         */

#define SQLE_RC_INV_REQINFO_PTR -1800        /* Invalid Request Info pointer  */
#define SQLE_RC_INV_REQUEST_TYPE -1801       /* Invalid Request Type          */
#define SQLE_RC_NO_NODE_ENTRY -1802          /* No entry belongs to Request   */
                                             /* Type                          */
#define SQLE_RC_NODE_EXIST -1803             /* Node already exists in node   */
                                             /* directory                     */

#define SQLE_RC_DB_ACTIVATED 1490            /* DB is already activated       */
#define SQLE_RC_DB_NOT_STOPPED -1491         /* DB is still active            */
#define SQLE_RC_DB_NOT_UP -1492              /* DB is not active              */
#define SQLE_RC_APP_IS_CONNECTED -1493       /* Application is connected to   */
                                             /* a database                    */
#define SQLE_RC_ACT_DB_CONNECTED 1494        /* There is already DB           */
                                             /* connection                    */
#define SQLE_RC_DEACT_DB_CONNECTED 1495      /* There is still DB connection  */
#define SQLE_RC_DEACT_DB_NOT_ACTIVATED 1496  /* DB is not activated           */
#define SQLE_RC_ACTDEACT_ERROR 1497          /* Error occurs on some nodes    */
#define SQLE_RC_INVALID_PARM -2032           /* Invalid parameter             */

#define SQLE_RC_E4411  -4411                 /* Error not Admin Server        */
#define SQLE_RC_NOADMSTART -4414             /* Admin Server not started      */

#define SQLE_RC_COMM_FAILED 5043             /* Communications support        */
                                             /* failed                        */

#define SQLE_RC_SDIRERR -6022                /* System database directory is  */
                                             /* not shared by all PDB nodes   */
#define SQLE_RC_PATH_NOT_QUAL -6027          /* The path specified for the    */
                                             /* database directory is not     */
                                             /* valid                         */
#define SQLE_RC_LOCALDB_NOT_FOUND -6028      /* Database is not found in      */
                                             /* local database directory      */
#define SQLE_RC_INV_PARM -6030               /* Invalid parameter for start   */
                                             /* stop                          */
#define SQLE_RC_ERR_DB2NODES_CFG -6031       /* Error in db2nodes.cfg file    */
#define SQLE_RC_STARTED_PARTIALLY 6032       /* Some nodes have not been      */
                                             /* started properly              */
#define SQLE_RC_STOPPED_PARTIALLY 6033       /* Some nodes have not been      */
                                             /* stopped properly              */
#define SQLE_RC_NODE_NOT_INUSE 6034          /* The node is not in used by    */
                                             /* any database                  */
#define SQLE_RC_NODE_INUSE 6035              /* The node is used by a         */
                                             /* database                      */
#define SQLE_RC_START_STOP_IN_PROG -6036     /* Start/stop command in         */
                                             /* progress                      */
#define SQLE_RC_NODE_TIMEOUT -6037           /* Timeout reached for start     */
                                             /* stop                          */
#define SQLE_RC_INVDROP_ACTION -6046         /* Invalid action for DROP NODE  */
#define SQLE_RC_COMM_ERR -6048               /* Communication error in start  */
                                             /* stop                          */
#define SQLE_RC_NODE_NEED_STOP -6072         /* Need to stop the node before  */
                                             /* starting the node with the    */
                                             /* restart option                */
#define SQLE_RC_ADD_NODE_FAIL -6073          /* Add Node failed               */
#define SQLE_RC_ADD_NODE_CRDP -6074          /* Add Node failed because       */
                                             /* Create/Drop Db in progress    */
#define SQLE_RC_ADD_NODE_OK 6075             /* Add Node operation            */
                                             /* successful                    */
#define SQLE_RC_DROP_PROMPT 6076             /* Prompt for db2stop DROP       */
                                             /* NODENUM                       */
#define SQLE_RC_DROP_OK 6077                 /* Drop node OK. Files still     */
                                             /* exist                         */
#define SQLE_RC_DROP_FAILED -6078            /* Drop node failed              */
#define SQLE_RC_DROP_CANCEL 6079             /* Drop node cancelled           */
                                             /* successfully                  */
#define SQLE_RC_ADD_NODE_NODB 6080           /* Add Node succeeded but no     */
                                             /* databases created on the      */
                                             /* node                          */
#define SQLE_RC_FORCE_TIMEOUT_ERR -6081      /* Timeout reached in stop       */
                                             /* FORCE                         */

#define SQLE_RC_DB2_SERVER_LICENSE -8000     /* No DB2 license                */
#define SQLE_RC_DB2_LICENSE -8001            /* Out of DB2 client licenses    */
#define SQLE_RC_DDCS_LICENSE -8002           /* Out of DDCS clients           */

/******************************************************************************
** 
** The following functions and symbols are obsolete and may not be supported
** in future releases. The obsolete functions are provided for backward compatibility
** and exported from DB2API.LIB. All applications should be migrated to use new APIs.
** Note: Some of the function parameters may be NO-OP.
**       Some structures are larger (eg. SQLEDINFO) in V2.
** 
*******************************************************************************/
#define SQLE_RC_BAD_SEGPAGES -1136           /* Invalid numsegs on create db  */

#define SQLE_RC_CS_LICENSE -8003             /* No CS/6000 license            */
#define SQLE_RC_SNA_LICENSE -8004            /* No SNA/6000 license           */

#define SQL_AUTHENTICATION_UNDEF 255         /* Authentication Undefined      */

SQL_API_RC SQL_API_FN                        /* CREATE DATABASE               */
  sqledbcr_api (
        _SQLOLDCHAR *,                       /* database                      */
        _SQLOLDCHAR *,                       /* drive/path                    */
        struct sqledbdesc *,                 /* db description block          */
        unsigned short,                      /* authentication                */
        struct sqledbcinfo *,                /* database country info         */
        struct sqlca *);                     /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* CREATE DATABASE               */
  sqlgdbcr (
        unsigned short,                      /* length drive/path             */
        unsigned short,                      /* length database               */
        struct sqlca *,                      /* SQLCA                         */
        struct sqledbcinfo *,                /* database country info         */
        unsigned short,                      /* authentication                */
        struct sqledbdesc *,                 /* db descriptor block           */
        _SQLOLDCHAR *,                       /* drive/path                    */
        _SQLOLDCHAR *);                      /* database                      */

SQL_API_RC SQL_API_FN                        /* Start Database Manager        */
  sqlestar_api (
        void);

/* PE V1.2 Start Database Manager structure                                   */
SQL_STRUCTURE sqledbstrtopt
{
        unsigned long  isprofile;            /* Profile specified?            */
        char           profile[SQL_PROFILE_SZ+1]; /* Profile                  */
        unsigned long  isnodenum;            /* Node number specified?        */
        SQL_PDB_NODE_TYPE nodenum;           /* Node number                   */
        unsigned long  iscommand;            /* Command specified?            */
        char           scommand[SQL_OPTION_SZ+1]; /* Command                  */
        unsigned long  ishostname;           /* Hostname specified?           */
        char           hostname[SQL_HOSTNAME_SZ+1]; /* Hostname               */
        unsigned long  isport;               /* Port specified?               */
        SQL_PDB_PORT_TYPE port;              /* Port                          */
        unsigned long  isnetname;            /* Netname specified?            */
        char           netname[SQL_HOSTNAME_SZ+1]; /* Netname                 */
};

SQL_API_RC SQL_API_FN                        /* PE V1.2 Start Database        */
                                             /* Manager                       */
  sqlepstr_api (
        struct sqledbstrtopt * pStartOptions, /* START OPTIONS                */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Start Database Manager        */
  sqlgstar (
        void);

SQL_API_RC SQL_API_FN                        /* PE V1.2 Start Database        */
                                             /* Manager                       */
  sqlgpstr (
        struct sqledbstrtopt * pStartOptions, /* START OPTIONS                */
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Stop Database Manager         */
  sqlestop_api (
        struct sqlca * pSqlca);              /* SQLCA                         */

SQL_API_RC SQL_API_FN                        /* Stop Database Manager         */
  sqlgstdm (
        struct sqlca * pSqlca);              /* SQLCA                         */

/******************************************************************************
** 
** End of obsolete functions and symbols
** 
*******************************************************************************/
#pragma pack()

#ifdef __cplusplus 
}
#endif

#endif /* SQL_H_SQLENV */
