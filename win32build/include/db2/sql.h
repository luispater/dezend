/******************************************************************************
** 
** Source File Name: SQL
** 
** (C) COPYRIGHT International Business Machines Corp. 1987, 1997
** All Rights Reserved
** Licensed Materials - Property of IBM
** 
** US Government Users Restricted Rights - Use, duplication or
** disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
** 
** Function = Include File defining:
**              System Constants
**              National Language Support Information
**              SQLCA / SQLDA Constants
**              Interface to BINDER and PRECOMPILER
**              Error Message Retrieval Interface
**              Authorization Constants
** 
** Operating System:  Windows NT
** 
*******************************************************************************/
#ifndef SQL_H_SQL
#define SQL_H_SQL

#ifdef __cplusplus
extern "C" {
#endif


/* Note: _SQLOLDCHAR defaults to 'char'.  See sqlsystm.h for details.         */

#include <stddef.h>                    
#include "sqlsystm.h"                  /* System dependent defines  */

#ifndef SQLCODE
#include "sqlca.h"                     /* Required include file    */
#endif

#pragma pack(4)

/* System Constants                                                           */

#ifndef   SQL_RC_OK
#define SQL_RC_OK              0       /* successful execution                */
#endif

#define SQL_KEYPMAX            16      /* Maximum nbr of key parts in Index   */
#define SQL_KEYLMAX            255     /* Maximum key length                  */
#define SQL_SORTFLDLMT         254     /* Maximum size of field for sort      */
#define SQL_MAXRECL            4005    /* Maximum record length               */
#define SQL_MAXTABLES          15      /* Maximum nbr of tables in a SELECT   */
#define SQL_MAXSEL_ITEMS       500     /* Maximum nbr of items in a SELECT    */
#define SQL_MAXVARS_STMT       32767   /* Maximum nbr of Host Vars per stmt   */
#define SQL_MAXCOLS            3000    /* Internal max nbr of columns in a    */
                                       /* table                               */
#define SQL_MAXCOLS_EXT        500     /* External max nbr of columns in a    */
                                       /* table                               */
#define SQL_MAXPARMS           90      /* Maximum nbr of parms in a function  */
#define SQL_MAX_STMT_SIZ       32765   /* Maximum statement size              */

#define SQL_SMALL_LENGTH       2       /* Size of a SMALLINT                  */
#define SQL_MAXSMALLVAL        32767   /* Maximum value of a SMALLINT         */
#define   SQL_MINSMALLVAL (-(SQL_MAXSMALLVAL)-1) /* Minimum value of a SMALLINT */
#define SQL_INT_LENGTH         4       /* Size of an INTEGER                  */
#define SQL_MAXINTVAL          2147483647 /* Maximum value of an INTEGER      */
#define   SQL_MININTVAL (-(SQL_MAXINTVAL)-1) /* Minimum value of an INTEGER  */
#define SQL_FLOAT_LENGTH       8       /* Size of a FLOAT                     */
#define SQL_FLOAT4_LENGTH      4       /* Size of a 4-byte FLOAT              */
#define SQL_MAXSFLTPREC        24      /* Maximum prec for small float        */
#define SQL_MINSFLTPREC        1       /* Minimum prec for small float        */
#define SQL_MAXFLOATPREC       53      /* Minimum prec for any float          */
#define SQL_DEFDEC_PRECISION   5       /* Default precision for DECIMAL       */
#define SQL_DEFDEC_SCALE       0       /* Default scale for DECIMAL           */
#define SQL_MAXDECIMAL         31      /* Maximum scale/prec. for DECIMAL     */
#define SQL_DEFCHAR            1       /* Default length for a CHAR           */
#define SQL_DEFWCHAR           1       /* Default length for a graphic        */
#define SQL_MAXCHAR            254     /* Maximum length of a CHAR            */
#define SQL_MAXLSTR            255     /* Maximum length of an LSTRING        */
#define SQL_MAXVCHAR           (SQL_MAXRECL-5) /* Maximum length of a         */
                                       /* VARCHAR                             */
#define SQL_MAXVGRAPH          2000    /* Maximum length of a VARGRAPHIC      */
#define SQL_MAXBLOB            2147483647 /* Max. length of a BLOB host var   */
#define SQL_MAXCLOB            2147483647 /* Max. length of a CLOB host var   */
#define SQL_MAXDBCLOB          1073741823 /* Max. length of an DBCLOB host    */
                                       /* var                                 */
#define SQL_LOBLOCATOR_LEN     4       /* Length of a LOB locator host var    */
#define SQL_LOBFILE_LEN        267     /* Length of a LOB file host var       */
#define SQL_VCHAROH            4       /* Overhead for VARCHAR in record      */
#define SQL_LONGMAX            32700   /* Maximum length of a LONG VARCHAR    */
#define SQL_LONGGRMAX          16350   /* Max. length of a LONG VARGRAPHIC    */
#define SQL_LVCHAROH           24      /* Overhead for LONG VARCHAR in        */
                                       /* record                              */
#define SQL_LOBCHAROH          312     /* Overhead for LOB in record          */
#define SQL_BLOB_MAXLEN        2147483647 /* BLOB maximum length, in bytes    */
#define SQL_CLOB_MAXLEN        2147483647 /* CLOB maximum length, in chars    */
#define SQL_DBCLOB_MAXLEN      1073741823 /* maxlen for dbcs lobs             */
#define SQL_TIME_LENGTH        3       /* Size of a TIME field                */
#define SQL_TIME_STRLEN        8       /* Size of a TIME field output         */
#define SQL_TIME_MINSTRLEN     5       /* Size of a non-USA TIME field        */
                                       /* output without seconds              */
#define SQL_DATE_LENGTH        4       /* Size of a DATE field                */
#define SQL_DATE_STRLEN        10      /* Size of a DATE field output         */
#define SQL_STAMP_LENGTH       10      /* Size of a TIMESTAMP field           */
#define SQL_STAMP_STRLEN       26      /* Size of a TIMESTAMP field output    */
#define SQL_STAMP_MINSTRLEN    19      /* Size of a TIMESTAMP field output    */
                                       /* without microseconds                */
#define SQL_BOOLEAN_LENGTH     1       /* Size of a BOOLEAN field             */
#define SQL_DATALINK_LENGTH    254     /* Size of a DATALINK field            */
#define SQL_IND_LENGTH         2       /* Size of an indicator value          */

#define SQL_MAX_PNAME_LENGTH   254     /* Max size of Stored Proc Name        */
#define SQL_LG_IDENT           18      /* Maximum length of Long Identifer    */
#define SQL_SH_IDENT           8       /* Maximum length of Short Identifer   */
#define SQL_MN_IDENT           1       /* Minimum length of Identifiers       */
#define SQL_MAX_VAR_NAME       255     /* Max size of Host Variable Name      */
#define SQL_PDB_MAP_SIZE       4096    /* Number of partitions in a pmap      */
#define SQL_MAX_NUM_PART_KEYS  500     /* Max # of Partition Keys             */
#define SQL_BINARYNUMERICS_FORMAT 0x4  /* numeric columns for sqlugrpn are    */
                                       /* in binary format                    */
#define SQL_PACKEDDECIMAL_FORMAT 0x8   /* decimal columns for sqlugrpn are    */
                                       /* in packeddecimal format             */
#define SQL_CHARSTRING_FORMAT  0x0     /* numeric/decimal columns for         */
                                       /* sqlugrpn are in character string    */
                                       /* format                              */
#define SQL_KILO_VALUE         1024    /* # of bytes in a kilobyte            */
#define SQL_MEGA_VALUE         1048576 /* # of bytes in a megabyte            */
#define SQL_GIGA_VALUE         1073741824 /* # of bytes in a gigabyte         */

#define SQLB_MAX_CONTAIN_NAME_SZ 256   /* size of container name for api's    */
                                       /* (includes 1 byte for C NULL         */
                                       /* terminator)                         */

/* System types                                                               */
typedef signed short SQL_PDB_NODE_TYPE;/* Datatype of PDB node               */
typedef int          SQL_PDB_PORT_TYPE;/* Datatype of PDB port               */
#define SQL_PDB_MAX_NUM_NODE   1000    /* limit for max. # of nodes           */
/* information related to logical node name                                   */
#define SQL_PDB_NODE_NUM_DIGIT 4       /* no. of digits for node number in    */
                                       /* node name                           */
#define SQL_PDB_NODE_NAME_LEN  8       /* length of logical node name         */
#define SQL_NODE_NUM_TO_NAME(name_p,node_num) \
        sprintf(name_p,"NODE%.*d", SQL_PDB_NODE_NUM_DIGIT, node_num)
/* Codepages                                                                  */
#define SQL_CP_367             367     /* Codepage 367 - EUC single byte      */
#define SQL_CP_437             437     /* Codepage 437 - US, Europe           */
#define SQL_CP_813             813     /* Codepage 813 - AIX Greece           */
#define SQL_CP_819             819     /* Codepage 819 - ISO 8859-1           */
#define SQL_CP_850             850     /* Codepage 850 - International PC     */
#define SQL_CP_855             855     /* Codepage 855 - OS2 Cyrillic         */
#define SQL_CP_852             852     /* Codepage 852 - OS2 Latin2           */
#define SQL_CP_857             857     /* Codepage 857 - OS2 Turkey           */
#define SQL_CP_860             860     /* Codepage 860 - Portuguese           */
#define SQL_CP_862             862     /* Codepage 862 - OS2 Hebrew           */
#define SQL_CP_863             863     /* Codepage 863 - Canadian-French      */
#define SQL_CP_864             864     /* Codepage 863 - OS2 Arabic           */
#define SQL_CP_865             865     /* Codepage 865 - Norway, Denmark      */
#define SQL_CP_866             866     /* Codepage 866 - Russia               */
#define SQL_CP_869             869     /* Codepage 869 - OS2 Greece           */
#define SQL_CP_874             874     /* Codepage 874 - OS2/AIX Thailand     */
#define SQL_CP_891             891     /* Codepage 891 - Korean               */
#define SQL_CP_897             897     /* Codepage 897 - Japanese             */
#define SQL_CP_903             903     /* Codepage 903 - Chinese              */
#define SQL_CP_904             904     /* Codepage 904 - Taiwan               */
#define SQL_CP_912             912     /* Codepage 912 - AIX Latin2           */
#define SQL_CP_915             915     /* Codepage 915 - AIX Cyrillic         */
#define SQL_CP_916             916     /* Codepage 916 - AIX Hebrew           */
#define SQL_CP_920             920     /* Codepage 920 - AIX Turkey           */
#define SQL_CP_921             921     /* Codepage 921 - Latvia, Lithuania    */
#define SQL_CP_922             922     /* Codepage 922 - Estonia              */
#define SQL_CP_1004            1004    /* Codepage 1004 - MS-WINDOWS          */
#define SQL_CP_1040            1040    /* Codepage 1040 - Extended Korean     */
#define SQL_CP_1041            1041    /* Codepage 1041 - Extended Japanese   */
#define SQL_CP_1042            1042    /* Codepage 1042 - Extended Chinese    */
#define SQL_CP_1043            1043    /* Codepage 1043 - Extended Taiwan     */
#define SQL_CP_1046            1046    /* Codepage 1046 - AIX Arabic          */
#define SQL_CP_1051            1051    /* Codepage 1051 - HP Roman8           */
#define SQL_CP_1088            1088    /* Codepage 1088 - Korea Std           */
#define SQL_CP_1089            1089    /* Codepage 1089 - AIX Arabic          */
#define SQL_CP_1114            1114    /* Codepage 1114 - Big-5 & GBK         */
#define SQL_CP_1115            1115    /* Codepage 1115 - China GB            */
#define SQL_CP_1126            1126    /* Codepage 1126 - Windows Korean Std  */
#define SQL_CP_1250            1250    /* Codepage 1250 - Windows Latin-2     */
#define SQL_CP_1251            1251    /* Codepage 1251 - Windows Cyrillic    */
#define SQL_CP_1252            1252    /* Codepage 1252 - Windows Latin-1     */
#define SQL_CP_1253            1253    /* Codepage 1253 - Windows Greek       */
#define SQL_CP_1254            1254    /* Codepage 1254 - Windows Turkish     */
#define SQL_CP_1255            1255    /* Codepage 1255 - Windows Hebrew      */
#define SQL_CP_1256            1256    /* Codepage 1256 - Windows Arabic      */
#define SQL_CP_1275            1275    /* Codepage 1275 - Mac Latin-1         */
#define SQL_CP_1280            1280    /* Codepage 1280 - Mac Greek           */
#define SQL_CP_1281            1281    /* Codepage 1281 - Mac Turkish         */
#define SQL_CP_1282            1282    /* Codepage 1282 - Mac Latin-2         */
#define SQL_CP_1283            1283    /* Codepage 1283 - Mac Cyrillic        */

/* DBCS Codepages                                                             */
#define SQL_CP_926             926     /* Codepage 926 - Korean               */
#define SQL_CP_951             951     /* Codepage 951 - New Korean           */
#define SQL_CP_301             301     /* Codepage 301 - Japanese             */
#define SQL_CP_928             928     /* Codepage 928 - Chinese              */
#define SQL_CP_927             927     /* Codepage 927 - Taiwan               */
#define SQL_CP_941             941     /* Codepage 941 - Japanese             */
#define SQL_CP_947             947     /* Codepage 947 - Taiwan Big-5         */
#define SQL_CP_971             971     /* Codepage 971 - Korean 5601          */
#define SQL_CP_1351            1351    /* Codepage 1351 - Japanese            */
#define SQL_CP_1362            1362    /* Codepage 1362 - Korean Windows      */
#define SQL_CP_1380            1380    /* Codepage1380 - China GB             */
#define SQL_CP_1382            1382    /* Codepage1382 - Simp Chinese GB      */
#define SQL_CP_1385            1385    /* Codepage1385 - Simp Chinese GBK     */
#define SQL_CP_13488           13488   /* Codepage13488 - UCS-2               */

/* Combined Codepages                                                         */
#define SQL_CP_934             934     /* Codepage 891 + 926 - Korean         */
#define SQL_CP_949             949     /* CP 1088 + 951 - Korean Std          */
#define SQL_CP_932             932     /* Codepage 897 + 301 - Japanese       */
#define SQL_CP_936             936     /* Codepage 903 + 928 - Chinese        */
#define SQL_CP_938             938     /* Codepage 904 + 927 - Taiwan         */
#define SQL_CP_944             944     /* Codepage 1040 + 926 - Ext.Korean    */
#define SQL_CP_942             942     /* Codepage 1041 + 301 - Ext.Japanese  */
#define SQL_CP_943             943     /* Codepage  897 + 941 - Ext.Japanese  */
#define SQL_CP_946             946     /* Codepage 1042 + 928 - Ext.Chinese   */
#define SQL_CP_948             948     /* Codepage 1043 + 927 - Ext.Taiwan    */
#define SQL_CP_950             950     /* Codepage 1114 + 947 - Taiwan Big5   */
#define SQL_CP_954             954     /* Codepage 954 + 13488 - euc Japan    */
#define SQL_CP_964             964     /* Codepage 964 + 13488 - euc Taiwan   */
#define SQL_CP_970             970     /* Codepage  367 + 971 - Korean 5601   */
#define SQL_CP_1363            1363    /* Codepage 1363 - Korean Windows      */
#define SQL_CP_1381            1381    /* Codepage 1115 +1380 - China GB      */
#define SQL_CP_1383            1383    /* Codepage  367 +1382 - Chinese GB    */
#define SQL_CP_1386            1386    /* Codepage  1114 +1385 - Chinese GBK  */
#define SQL_CP_5039            5039    /* Codepage  1041 + 1351 - Japanese    */
/* Datastream Types                                                           */
#define SQL_SBC_PC             0       /* Single byte PC                      */
#define SQL_JPN_PC             1       /* Japanese-PC                         */
#define SQL_CHN_PC             2       /* Chinese-PC                          */
#define SQL_KOR_PC             3       /* Korean-PC                           */
#define SQL_KSC_PC             4       /* New Korean-PC                       */
#define SQL_KR5_PC             5       /* Korean 5601                         */
#define SQL_TWN_PC             6       /* Taiwan Big-5                        */
#define SQL_CGB_PC             7       /* China GB                            */
#define SQL_CGBA_PC            8       /* China GB on AIX                     */
#define SQL_EUCJP_PC           9       /* Japan euc                           */
#define SQL_EUCTW_PC           10      /* Taiwan euc                          */
#define SQL_UCS2_PC            11      /* UCS-2                               */
#define SQL_KSC2_PC            12      /* Korean Windows                      */
#define SQL_CGBK_PC            13      /* China GBK                           */
#define SQL_UNKN_PC            255     /* Unknown                             */

/* AIX codeset & locale lengths                                               */
#define SQL_CODESET_LEN        9
#define SQL_LOCALE_LEN         5

/* SQLCA Constants                                                            */
#ifndef SQL_RC_INVALID_SQLCA
#endif

/* Size of SQLCA                                                              */
#define SQLCA_SIZE             sizeof(struct sqlca)

/* SQL Error message token delimiter                                          */
#define SQL_ERRMC_PRES ((char) 0xFF) /* delimiter for string entry */

/* Offset in SQLERRD - Diagnostic information                                 */
#define SQL_ERRD_RC            0       /* return code                         */
#define SQL_ERRD_REAS          1       /* reason code                         */
#define SQL_ERRD_CNT           2       /* nbr rows inserted/updated/deleted   */
#define SQL_ERRD_OPT_CARD      2       /* optimizer estimate of # rows        */
#define SQL_ERRD_OPTM          3       /* obsolete -- do not use --           */
#define SQL_ERRD_OPT_TOTCOST   3       /* optimzer estimate of total cost     */
#define SQL_ERRD_DCNT          4       /* nbr of cascaded deletes/updates     */
#define SQL_ERRD_LINE          4       /* line number for recompile error     */
#define SQL_ERRD_AUTHTYPE      4       /* authentication type returned for    */
                                       /* CONNECT/ATTACH                      */
#define SQL_ERRD_DIAG          5       /* diagnostics                         */

/* Indexes in SQLWARN - Warning flags                                         */
#define SQL_WARN_ANY           0       /* composite - set if any warnings     */
#define SQL_WARN_TRUNC         1       /* string column truncated             */
#define SQL_WARN_NUL           2       /* null values eliminated              */
#define SQL_WARN_MISM          3       /* nbr of columns/host vars mismatch   */
#define SQL_WARN_ALLR          4       /* no WHERE clause in update/delete    */
#define SQL_WARN_DATE          6       /* date has been truncated             */
#define SQL_WARN_SUB           8       /* character conversion substitution   */
#define SQL_WARN_NUL2          9       /* arithmetic error nulls eliminated   */
#define SQL_WARN_SQLCA         10      /* SQLCA conversion error              */

/* Values for Warning flags in SQLWARN                                        */
#define SQL_WARNING            'W'     /* warning indicator                   */
#define SQL_NULL_TRN           'N'     /* null terminator truncated warning   */
#define SQL_TRN_APP_LEN        'X'     /* truncation warning with             */
                                       /* application context length          */
                                       /* returned in sqlind                  */
#define SQL_NO_WARN            ' '     /* no warning indicator                */

/* SQLDA Constants                                                            */

/* Increment for type with null indicator                                     */
#define SQL_TYP_NULINC         1

/* Variable Types                                                             */
#define SQL_TYP_DATE           384     /* DATE                                */
#define SQL_TYP_NDATE          (SQL_TYP_DATE+SQL_TYP_NULINC)

#define SQL_TYP_TIME           388     /* TIME                                */
#define SQL_TYP_NTIME          (SQL_TYP_TIME+SQL_TYP_NULINC)

#define SQL_TYP_STAMP          392     /* TIMESTAMP                           */
#define SQL_TYP_NSTAMP         (SQL_TYP_STAMP+SQL_TYP_NULINC)

#define SQL_TYP_CGSTR          400     /* C NUL-terminated graphic str        */
#define SQL_TYP_NCGSTR         (SQL_TYP_CGSTR+SQL_TYP_NULINC)

#define SQL_TYP_BLOB           404     /* BLOB - varying length string        */
#define SQL_TYP_NBLOB          (SQL_TYP_BLOB+SQL_TYP_NULINC)

#define SQL_TYP_CLOB           408     /* CLOB - varying length string        */
#define SQL_TYP_NCLOB          (SQL_TYP_CLOB+SQL_TYP_NULINC)

#define SQL_TYP_DBCLOB         412     /* DBCLOB - varying length string      */
#define SQL_TYP_NDBCLOB        (SQL_TYP_DBCLOB+SQL_TYP_NULINC)

#define SQL_TYP_VARCHAR        448     /* VARCHAR(i) - varying length string  */
                                       /* (2 byte length)                     */
#define SQL_TYP_NVARCHAR       (SQL_TYP_VARCHAR+SQL_TYP_NULINC)

#define SQL_TYP_CHAR           452     /* CHAR(i) - fixed length string       */
#define SQL_TYP_NCHAR          (SQL_TYP_CHAR+SQL_TYP_NULINC)

#define SQL_TYP_LONG           456     /* LONG VARCHAR - varying length       */
                                       /* string                              */
#define SQL_TYP_NLONG          (SQL_TYP_LONG+SQL_TYP_NULINC)

#define SQL_TYP_CSTR           460     /* varying length string for C (null   */
                                       /* terminated)                         */
#define SQL_TYP_NCSTR          (SQL_TYP_CSTR+SQL_TYP_NULINC)

#define SQL_TYP_VARGRAPH       464     /* VARGRAPHIC(i) - varying length      */
                                       /* graphic string (2 byte length)      */
#define SQL_TYP_NVARGRAPH      (SQL_TYP_VARGRAPH+SQL_TYP_NULINC)

#define SQL_TYP_GRAPHIC        468     /* GRAPHIC(i) - fixed length graphic   */
                                       /* string                              */
#define SQL_TYP_NGRAPHIC       (SQL_TYP_GRAPHIC+SQL_TYP_NULINC)

#define SQL_TYP_LONGRAPH       472     /* LONG VARGRAPHIC(i) - varying        */
                                       /* length graphic string               */
#define SQL_TYP_NLONGRAPH      (SQL_TYP_LONGRAPH+SQL_TYP_NULINC)

#define SQL_TYP_LSTR           476     /* varying length string for Pascal    */
                                       /* (1-byte length)                     */
#define SQL_TYP_NLSTR          (SQL_TYP_LSTR+SQL_TYP_NULINC)

#define SQL_TYP_FLOAT          480     /* FLOAT - 4 or 8 byte floating point  */
#define SQL_TYP_NFLOAT         (SQL_TYP_FLOAT+SQL_TYP_NULINC)

#define SQL_TYP_DECIMAL        484     /* DECIMAL (m,n)                       */
#define SQL_TYP_NDECIMAL       (SQL_TYP_DECIMAL+SQL_TYP_NULINC)

#define SQL_TYP_ZONED          488     /* Zoned Decimal -> DECIMAL (m,n)      */
#define SQL_TYP_NZONED         (SQL_TYP_ZONED+SQL_TYP_NULINC)

#define SQL_TYP_INTEGER        496     /* INTEGER - 4-byte signed integer     */
#define SQL_TYP_NINTEGER       (SQL_TYP_INTEGER+SQL_TYP_NULINC)

#define SQL_TYP_SMALL          500     /* SMALLINT - 2-byte signed integer    */
#define SQL_TYP_NSMALL         (SQL_TYP_SMALL+SQL_TYP_NULINC)

#define SQL_TYP_NUMERIC        504     /* NUMERIC -> DECIMAL (m,n)            */
#define SQL_TYP_NNUMERIC       (SQL_TYP_NUMERIC+SQL_TYP_NULINC)

#define SQL_TYP_BLOB_FILE      804     /* BLOB File - Binary Large Object     */
                                       /* File                                */
#define SQL_TYP_NBLOB_FILE     (SQL_TYP_BLOB_FILE+SQL_TYP_NULINC)

#define SQL_TYP_CLOB_FILE      808     /* CLOB File - Char Large Object File  */
#define SQL_TYP_NCLOB_FILE     (SQL_TYP_CLOB_FILE+SQL_TYP_NULINC)

#define SQL_TYP_DBCLOB_FILE    812     /* DBCLOB File - Double Byte Char      */
                                       /* Large Object File                   */
#define SQL_TYP_NDBCLOB_FILE   (SQL_TYP_DBCLOB_FILE+SQL_TYP_NULINC)

#define SQL_TYP_BLOB_LOCATOR   960     /* BLOB locator                        */
#define SQL_TYP_NBLOB_LOCATOR  (SQL_TYP_BLOB_LOCATOR+SQL_TYP_NULINC)

#define SQL_TYP_CLOB_LOCATOR   964     /* CLOB locator                        */
#define SQL_TYP_NCLOB_LOCATOR  (SQL_TYP_CLOB_LOCATOR+SQL_TYP_NULINC)

#define SQL_TYP_DBCLOB_LOCATOR 968     /* DBCLOB locator                      */
#define SQL_TYP_NDBCLOB_LOCATOR (SQL_TYP_DBCLOB_LOCATOR+SQL_TYP_NULINC)

#define SQL_LOBTOKEN_LEN       SQL_LOBLOCATOR_LEN
#define SQL_TYP_BLOB_TOKEN     SQL_TYP_BLOB_LOCATOR
#define SQL_TYP_NBLOB_TOKEN    SQL_TYP_NBLOB_LOCATOR
#define SQL_TYP_CLOB_TOKEN     SQL_TYP_CLOB_LOCATOR
#define SQL_TYP_NCLOB_TOKEN    SQL_TYP_NCLOB_LOCATOR
#define SQL_TYP_DBCLOB_TOKEN   SQL_TYP_DBCLOB_LOCATOR
#define SQL_TYP_NDBCLOB_TOKEN  SQL_TYP_NDBCLOB_LOCATOR
#define SQL_NCLOB_MAXLEN       SQL_DBCLOB_MAXLEN
#define SQL_LOBHANDLE_LEN      SQL_LOBTOKEN_LEN
#define SQL_TYP_BLOB_HANDLE    SQL_TYP_BLOB_TOKEN
#define SQL_TYP_NBLOB_HANDLE   SQL_TYP_NBLOB_TOKEN
#define SQL_TYP_CLOB_HANDLE    SQL_TYP_CLOB_TOKEN
#define SQL_TYP_NCLOB_HANDLE   SQL_TYP_NCLOB_TOKEN
#define SQL_TYP_DBCLOB_HANDLE  SQL_TYP_DBCLOB_TOKEN
#define SQL_TYP_NDBCLOB_HANDLE SQL_TYP_NDBCLOB_TOKEN

/* Values for 30th byte of sqlname                                            */
#define SQL_SQLNAME_SYSGEN     ((char) 0xFF) /* sqlname is system generated   */
#define SQL_SQLNAME_NOT_SYSGEN ((char) 0x00) /* sqlname is directly derived   */
                                             /* from a single column or       */
                                             /* specified in the AS clause    */

/* Return Codes for sqlabndx and sqlaprep                                     */
#define SQLA_RC_OPT_IGNORED    20      /* The option(s) specified are not     */
                                       /* supported by the target  database   */
                                       /* and will be ignored                 */
#define SQLA_RC_BINDWARN       25      /* Bind execution succeeded with       */
                                       /* warnings.                           */
#define SQLA_RC_PREPWARN       25      /* Precompilation succeeded with       */
                                       /* warnings.                           */
#define SQLA_RC_BINDERROR      -1      /* Bind execution failed               */
#define SQLA_RC_PREPERROR      -1      /* Precompilation failed               */
#define SQLA_RC_BAD_BINDNAME   -2      /* Invalid bind file                   */
#define SQLA_RC_BAD_DBNAME     -3      /* Invalid database                    */
#define SQLA_RC_BAD_MSGNAME    -5      /* Invalid message file                */
#define SQLA_RC_BAD_FORMAT     -6      /* Invalid format                      */
#define SQLA_RC_OPEN_ERROR     -31     /* Error opening list file             */
#define SQLA_RC_MFILE_OPEN_ERR -35     /* Error opening message file          */
#define SQLA_RC_FILE_NAME_BAD  -36     /* Source file name is invalid         */
#define SQLA_RC_BAD_BNDFILE    -39     /* Bind file corrupted                 */
#define SQLA_RC_LIST_ERROR     -40     /* Bind list errors                    */
#define SQLA_RC_INTERRUPT      -94     /* Interrupt                           */
#define SQLA_RC_OSERROR        -1086   /* System error                        */
#define SQLA_RC_PREP_BIND_BUSY -1392   /* Prep/Bind already in use            */
#define SQLA_RC_OPTION_LEN_BAD -4903   /* Invalid parm. length                */
#define SQLA_RC_OPTION_PTR_BAD -4904   /* Invalid parm. ptr                   */
#define SQLA_RC_OPTION_SIZE_BAD -4905  /* Invalid parm. size                  */
#define SQLA_RC_OPTION_DATA_BAD -4917  /* Invalid parm. data                  */
#define SQLA_RC_OPTION_INVALID -4930   /* Invalid option or option value      */
#define SQLA_RC_SDK_LICENSE    -8005   /* No SDK/6000 license                 */

/* Values used for the date/time format parameter of sqlabind() ** OBSOLETE   */
/* **                                                                         */
#define SQL_FMT_DEF            "DEF"   /* FORMAT = Default for Country Code   */
#define SQL_FMT_USA            "USA"   /* FORMAT = USA                        */
#define SQL_FMT_EUR            "EUR"   /* FORMAT = EUR                        */
#define SQL_FMT_ISO            "ISO"   /* FORMAT = ISO                        */
#define SQL_FMT_JIS            "JIS"   /* FORMAT = JIS                        */
#define SQL_FMT_LOC            "LOC"   /* FORMAT = LOCAL                      */

/* The size of a date/time format buffer                                      */
#define SQL_FMT_LENGTH         3

/* Structures used system wide                                                */

#ifndef SQL_SQLDBCHAR_DEFN
#define SQL_SQLDBCHAR_DEFN
  typedef unsigned short sqldbchar;
#endif

SQL_STRUCTURE sqlchar                  /* General-purpose VARCHAR for         */
                                       /* casting                             */
{
        short                  length;
        _SQLOLDCHAR            data[1];
};

SQL_STRUCTURE sqlgraphic               /* General-purpose VARGRAPHIC for      */
                                       /* casting                             */
{
        short                  length;
#ifdef SQL_WCHART_CONVERT
        wchar_t                data[1];
#else
        sqldbchar              data[1];
#endif
};

SQL_STRUCTURE sqllob                   /* General-purpose LOB for casting     */
{
        unsigned long          length;
        char                   data[1];
};

SQL_STRUCTURE sqldbclob                /* General-purpose DBCLOB for casting  */
{
        unsigned long          length;
#ifdef SQL_WCHART_CONVERT
        wchar_t                data[1];
#else
        sqldbchar              data[1];
#endif
};

SQL_STRUCTURE sqlfile                  /* File reference structure for LOBs   */
{
        unsigned long          name_length;
        unsigned long          data_length;
        unsigned long          file_options;
        char                   name[255];
};

/* Values used for file_options in the sqlfile structure                      */
#define SQL_FILE_READ          2       /* Input file to read from             */
#define SQL_FILE_CREATE        8       /* Output file - new file to be        */
                                       /* created                             */
#define SQL_FILE_OVERWRITE     16      /* Output file - overwrite existing    */
                                       /* file or create a new file if it     */
                                       /* doesn't exist                       */
#define SQL_FILE_APPEND        32      /* Output file - append to an          */
                                       /* existing file or create a new file  */
                                       /* if it doesn't exist                 */

/* Structure used to store binder options when calling sqlabndr()             */
/* or sqlabndx() or to store precompile options when calling                  */
/* sqlaprep().                                                                */

#define sqlbindopt sqloptions

#ifndef SQL_BIND_OPTS

SQL_STRUCTURE sqloptheader     /* Header for sqlopt structure */
{
   unsigned long allocated; /* Number of options allocated */
   unsigned long used; /* Number of options used */
};

SQL_STRUCTURE sqloptions       /* bind/prep option          */
{
   unsigned long type; /* Type  of bind/prep option */
   unsigned long val; /* Value of bind/prep option */
};

SQL_STRUCTURE sqlopt
{
   SQL_STRUCTURE sqloptheader header;     /* Header for sqlopt structure */
   SQL_STRUCTURE sqloptions   option[1];  /* Array of bind/prep options  */
};

#define SQL_BIND_OPTS
#endif

/* Values used for option[n].type in the sqloptions structure                 */
/* of sqlabndx() and sqlaprep().                                              */
#define SQL_DATETIME_OPT       1       /* Option for date/time format - bind  */
                                       /* and precompile option               */
#define SQL_STANDARDS_OPT      2       /* Option for standards level          */
                                       /* compliance - precompile option      */
                                       /* only                                */
#define SQL_ISO_OPT            4       /* Option for isolation level - bind   */
                                       /* and precompile option               */
#define SQL_BLOCK_OPT          5       /* Option for record blocking - bind   */
                                       /* and precompile option               */
#define SQL_GRANT_OPT          6       /* Option for granting privileges -    */
                                       /* bind option only                    */
#define SQL_FLAG_OPT           8       /* Option for the Flagger -            */
                                       /* precompile option only              */
#define SQL_GRANT_USER_OPT     9       /* Option for granting privileges to   */
                                       /* a user - bind option only           */
#define SQL_GRANT_GROUP_OPT    10      /* Option for granting privileges to   */
                                       /* a group - bind option only          */
#define SQL_CNULREQD_OPT       11      /* Option for adding NULLs to strings  */
                                       /* - bind option only                  */
#define SQL_GENERIC_OPT        12      /* Generic option for DRDA servers -   */
                                       /* bind option only                    */
#define SQL_DEFERRED_PREPARE_OPT 15    /* Option for Deferred Prepare -       */
                                       /* precompile option only              */
#define SQL_CONNECT_OPT        16      /* Specifies whether one or multiple   */
                                       /* connections are allowed             */
                                       /* similtaneously within a unit of     */
                                       /* work.                               */
#define SQL_RULES_OPT          17      /* Specifies the set of rules used     */
                                       /* for connection to multiple          */
                                       /* databases within a single unit of   */
                                       /* work                                */
#define SQL_DISCONNECT_OPT     18      /* Specifies which of multiple         */
                                       /* databases connected to will be      */
                                       /* disconnected when a COMMIT or       */
                                       /* ROLLBACK is issued.                 */
#define SQL_SYNCPOINT_OPT      19      /* Specifies what syncpoint option     */
                                       /* (for example one phase or two       */
                                       /* phase) will be used                 */
#define SQL_BIND_OPT           20      /* Option to create a bind file -      */
                                       /* precompile option only              */
#define SQL_SAA_OPT            21      /* Option specifies SAA/non-SAA        */
                                       /* compatibility - FORTRAN precompile  */
                                       /* option only                         */
#define SQL_PKG_OPT            23      /* Option to create a package with a   */
                                       /* specific name - precompile option   */
                                       /* only                                */
#define SQL_OPTIM_OPT          24      /* Option to specify SQLDA             */
                                       /* optimization - precompile option    */
                                       /* only                                */
#define SQL_SYNTAX_OPT         25      /* Option to not create a package or   */
                                       /* bind file - precompile option only  */
#define SQL_SQLERROR_OPT       SQL_SYNTAX_OPT /* Indicates under what         */
                                       /* conditions a package will be be     */
                                       /* created - bind and precompile       */
                                       /* option                              */
#define SQL_LINEMACRO_OPT      26      /* Option to suppress #line macro      */
                                       /* generation in modified source file  */
                                       /* - C precompile option only          */
#define SQL_NO_OPT             27      /* 'No-op' option - ignore this entry  */
                                       /* in the option array - bind and      */
                                       /* precompile option                   */
#define SQL_LEVEL_OPT          30      /* Level of a module - precompile      */
                                       /* option only                         */
#define SQL_COLLECTION_OPT     31      /* Package collection identifier -     */
                                       /* precompile option only              */
#define SQL_VERSION_OPT        32      /* Package version identifier -        */
                                       /* precompile option only              */
#define SQL_OWNER_OPT          33      /* Package owner authorization         */
                                       /* identifier - bind and precompile    */
                                       /* option                              */
#define SQL_SCHEMA_OPT         SQL_OWNER_OPT /* Synonym for owner - bind and  */
                                       /* precompile option                   */
#define SQL_QUALIFIER_OPT      34      /* Authorization identifier that is    */
                                       /* to be used as a qualifier for       */
                                       /* unqualified objects - bind and      */
                                       /* precompile option                   */
#define SQL_CATALOG_OPT        SQL_QUALIFIER_OPT /* Synonym for qualifier -   */
                                       /* bind and precompile option          */
#define SQL_TEXT_OPT           35      /* Package description - bind and      */
                                       /* precompile option                   */
#define SQL_VALIDATE_OPT       40      /* Indicates when object validation    */
                                       /* occurs - bind and precompile        */
                                       /* option                              */
#define SQL_EXPLAIN_OPT        41      /* Determines whether information      */
                                       /* will be produced about how the SQL  */
                                       /* statements in a package will be     */
                                       /* executed - bind and precompile      */
                                       /* option                              */
#define SQL_ACTION_OPT         42      /* Indicates whether a package is to   */
                                       /* be added or replaced - bind and     */
                                       /* precompile option                   */
#define SQL_REPLVER_OPT        44      /* Replaces a specific version of a    */
                                       /* package - bind and precompile       */
                                       /* option                              */
#define SQL_RETAIN_OPT         45      /* Indicates whether EXECUTE           */
                                       /* authorities are to be preserved     */
                                       /* when a package is replaced - bind   */
                                       /* and precompile option               */
#define SQL_RELEASE_OPT        46      /* Indicates whether resources are     */
                                       /* released at each COMMIT or when     */
                                       /* the application  terminates - bind  */
                                       /* and precompile option               */
#define SQL_DEGREE_OPT         47      /* Specifies whether or not the query  */
                                       /* is executed using I/O parallelism   */
                                       /*  bind and precompile option         */
#define SQL_STRDEL_OPT         50      /* Designates whether an apostrophe    */
                                       /* or quote will be used as a string   */
                                       /* delimiter - bind and precompile     */
                                       /* option                              */
#define SQL_DECDEL_OPT         51      /* Designates whether a period or      */
                                       /* comma will be used as a decimal     */
                                       /* point indicator - bind and          */
                                       /* precompile option                   */
#define SQL_CHARSUB_OPT        55      /* Designates default character        */
                                       /* subtype that is to be used for      */
                                       /* column definitions in the CREATE    */
                                       /* and ALTER TABLE SQL statements -    */
                                       /* bind and precompile option          */
#define SQL_CCSIDS_OPT         56      /* Designates what CCSID will be used  */
                                       /* for single byte characters for      */
                                       /* character column definitions        */
                                       /* without a specific CCSID clause in  */
                                       /* the CREATE and ALTER TABLE SQL      */
                                       /* statements - bind and precompile    */
                                       /* option                              */
#define SQL_CCSIDM_OPT         57      /* Designates what CCSID will be used  */
                                       /* for mixed byte characters for       */
                                       /* character column definitions        */
                                       /* without a specific CCSID clause in  */
                                       /* the CREATE and ALTER TABLE SQL      */
                                       /* statements - bind and precompile    */
                                       /* option                              */
#define SQL_CCSIDG_OPT         58      /* Designates what CCSID will be used  */
                                       /* for double byte characters for      */
                                       /* character column definitions        */
                                       /* without a specific CCSID clause in  */
                                       /* the CREATE and ALTER TABLE SQL      */
                                       /* statements - bind and precompile    */
                                       /* option                              */
#define SQL_DEC_OPT            59      /* Specifies maximum precision to be   */
                                       /* used in decimal arithmetic          */
                                       /* operations - bind and precompile    */
                                       /* option                              */
#define SQL_WCHAR_OPT          60      /* Specifies handling of graphic       */
                                       /* vars. - precompile only             */
#define SQL_DYNAMICRULES_OPT   61      /* Specifies which authorization       */
                                       /* identifier to use when dynamic SQL  */
                                       /* in a package is executed. Owner of  */
                                       /* package or authid executing         */
                                       /* package - bind and precompile       */
                                       /* option                              */
#define SQL_INSERT_OPT         62      /* Buffers VALUE inserts - bind and    */
                                       /* precompile option for DB2/PE        */
                                       /* servers only                        */
#define SQL_EXPLSNAP_OPT       63      /* Capture explain snapshot - bind     */
                                       /* and precompile option               */
#define SQL_FUNCTION_PATH      64      /* Path for user-defined function      */
                                       /* resolution - bind and precompile    */
                                       /* option                              */
#define SQL_SQLWARN_OPT        65      /* Disable prepare-time SQL warnings   */
                                       /*  bind and precompile option         */
#define SQL_QUERYOPT_OPT       66      /* Set query optimization class -      */
                                       /* bind and precompile option          */
#define SQL_TARGET_OPT         67      /* Target compiler - precompile        */
                                       /* option                              */
#define SQL_PREP_OUTPUT_OPT    68      /* Name of precompiler output file -   */
                                       /* precompile option                   */

/* Values used for option[n].val when option[n].type is                       */
/* SQL_DATETIME_OPT. These can also be used for the date/time                 */
/* format parameter of sqlabind().                                            */

#define SQL_DATETIME_DEF       48      /* FORMAT = Default for Country Code   */
#define SQL_DATETIME_USA       49      /* FORMAT = USA                        */
#define SQL_DATETIME_EUR       50      /* FORMAT = EUR                        */
#define SQL_DATETIME_ISO       51      /* FORMAT = ISO                        */
#define SQL_DATETIME_JIS       52      /* FORMAT = JIS                        */
#define SQL_DATETIME_LOC       53      /* FORMAT = LOCAL                      */

/* The following constants are here for backwards compatbility with earlier   */
/* releases.                                                                  */

#define SQL_FRMT_OPT           SQL_DATETIME_OPT
#define SQL_FMT_0              SQL_DATETIME_DEF
#define SQL_FMT_1              SQL_DATETIME_USA
#define SQL_FMT_2              SQL_DATETIME_EUR
#define SQL_FMT_3              SQL_DATETIME_ISO
#define SQL_FMT_4              SQL_DATETIME_JIS
#define SQL_FMT_5              SQL_DATETIME_LOC

/* Values used for option[n].val when option[n].type is SQL_STANDARDS_OPT.    */
#define SQL_SAA_COMP           0       /* SAA Level 1 Database CPI            */
#define SQL_MIA_COMP           1       /* MIA                                 */
#define SQL_SQL92E_COMP        2       /* SQL92 Entry                         */

/* Values used for option[n].val when option[n].type is SQL_ISO_OPT           */
#define SQL_REP_READ           0       /* Repeatable read level               */
#define SQL_CURSOR_STAB        1       /* Cursor stability level              */
#define SQL_UNCOM_READ         2       /* Uncommitted read level              */
#define SQL_READ_STAB          3       /* Read stability level                */
#define SQL_NO_COMMIT          4       /* No Commit level      l              */

/* Values used for option[n].val when option[n].type is SQL_BLOCK_OPT         */
#define SQL_BL_UNAMBIG         0       /* Block Unambiguous cursors           */
#define SQL_BL_ALL             1       /* Block All cursors                   */
#define SQL_NO_BL              2       /* Block No cursors                    */

/* Values used for option[n].val when option[n].type is SQL_FLAG_OPT          */
#define SQL_MVSDB2V23_SYNTAX   4       /* Flagger check against MVS           */
#define SQL_MVSDB2V31_SYNTAX   5       /* DB2 V2.3, V3.1 or V4.1 SQL          */
#define SQL_MVSDB2V41_SYNTAX   6       /* syntax                              */
#define SQL_SQL92E_SYNTAX      7       /* FIPS flagger SQL92E syntax          */

/* Values used for option[n].val when option[n].type is SQL_CNULREQD_OPT      */
#define SQL_CNULREQD_NO        0       /* C NULL value not required           */
#define SQL_CNULREQD_YES       1       /* C NULL value required               */

/* Maximum sqlchar length for option[n].val when option[n].type is SQL        */
/* GENERIC_OPT                                                                */
#define SQL_MAX_GENERIC        1023

/* Values used for option[n].val when option[n].type is SQL_SAA_OPT.          */
#define SQL_SAA_NO             0       /* SQLCA definition not SAA            */
                                       /* compatible                          */
#define SQL_SAA_YES            1       /* SQLCA definition is SAA compatible  */

/* Values used for option[n].val when option[n].type is SQL_OPTIM_OPT.        */
#define SQL_DONT_OPTIMIZE      0       /* Do not optimize SQLDA               */
                                       /* initialization                      */
#define SQL_OPTIMIZE           1       /* Optimize SQLDA initialization       */

/* Values used for option[n].val when option[n].type is SQL_SYNTAX_OPT.       */
#define SQL_NO_SYNTAX_CHECK    0       /* Create a package and/or a bind      */
                                       /* file                                */
#define SQL_SYNTAX_CHECK       1       /* Do not create a package or bind     */
                                       /* file                                */

/* Values used for option[n].val when option[n].type is SQL_LINEMACRO_OPT.    */
#define SQL_NO_LINE_MACROS     0       /* Do not generate #line macros in     */
                                       /* modified source file                */
#define SQL_LINE_MACROS        1       /* Generate #line macros in modified   */
                                       /* source file                         */

/* Values used for option[n].val when option[n].type is SQL_WCHAR_OPT.        */
#define SQL_WCHAR_NOCONVERT    0       /* graphic variable not converted      */
#define SQL_WCHAR_CONVERT      1       /* graphic variable converted          */

/* Maximum sqlchar length for option[n].val when option[n].type is SQL_LEVEL  */
/* OPT                                                                        */
#define SQL_MAX_LEVEL          8

/* Values used for option[n].val when option[n].type is SQL_CONNECT_OPT       */
#define SQL_DEFERRED_PREPARE_YES 1     /* Dynamic SQL statements will be      */
                                       /* chained.                            */
#define SQL_DEFERRED_PREPARE_NO 2      /* Dynamic SQL statements will not be  */
                                       /* chained.                            */
#define SQL_DEFERRED_PREPARE_ALL 3     /* Dynamic SQL statements will be      */
                                       /* chained in all cases.  The          */
                                       /* application must not allocate host  */
                                       /* vars a FETCH SQLDA until after the  */
                                       /* OPEN statement for the cursor.      */

/* Maximum sqlchar length for option[n].val when option[n].type is SQL        */
/* COLLECTION_OPT                                                             */
#define SQL_MAX_COLLECTION     8

/* Maximum sqlchar length for option[n].val when option[n].type is SQL        */
/* VERSION_OPT                                                                */
#define SQL_MAX_VERSION        254

/* Maximum sqlchar length for option[n].val when option[n].type is SQL_OWNER  */
/* OPT                                                                        */
#define SQL_MAX_OWNER          8

/* Maximum sqlchar length for option[n].val when option[n].type is SQL        */
/* SCHEMA_OPT                                                                 */
#define SQL_MAX_SCHEMA         SQL_MAX_OWNER

/* Maximum sqlchar length for option[n].val when option[n].type is SQL        */
/* QUALIFIER_OPT                                                              */
#define SQL_MAX_QUALIFIER      18

/* Maximum sqlchar length for option[n].val when option[n].type is SQL        */
/* CATALOG_OPT                                                                */
#define SQL_MAX_CATALOG        SQL_MAX_QUALIFIER

/* Maximum sqlchar length for option[n].val when option[n].type is SQL_TEXT   */
/* OPT                                                                        */
#define SQL_MAX_TEXT           255

/* Values used for option[n].val when option[n].type is SQL_VALIDATE_OPT      */
#define SQL_VALIDATE_BIND      0       /* Validate objects during BIND        */
#define SQL_VALIDATE_RUN       1       /* Validate objects during execution   */

/* Values used for option[n].val when option[n].type is SQL_EXPLAIN_OPT       */
#define SQL_EXPLAIN_NO         0       /* No Explain output saved             */
#define SQL_EXPLAIN_YES        1       /* Explain output saved                */
#define SQL_EXPLAIN_ALL        2       /* Explain output saved for all        */
                                       /* static and dynamic statements       */

/* Values used for option[n].val when option[n].type is SQL_ACTION_OPT        */
#define SQL_ACTION_ADD         0       /* Package is to be added              */
#define SQL_ACTION_REPLACE     1       /* Package is to be replaced           */

/* Maximum sqlchar length for option[n].val when option[n].type is SQL        */
/* REPLVER_OPT                                                                */
#define SQL_MAX_REPLVER        254

/* Values used for option[n].val when option[n].type is SQL_SQLERROR_OPT      */
#define SQL_SQLERROR_NOPACKAGE SQL_NO_SYNTAX_CHECK /* Do not create a         */
                                       /* package if errors are encountered   */
#define SQL_SQLERROR_CHECK     SQL_SYNTAX_CHECK /* Do not create a package    */
#define SQL_SQLERROR_CONTINUE  2       /* Create a package even if errors     */
                                       /* are encountered                     */

/* Values used for option[n].val when option[n].type is SQL_RETAIN_OPT        */
#define SQL_RETAIN_NO          0       /* Do not preserve EXECUTE             */
                                       /* authorities when a package is       */
                                       /* replaced                            */
#define SQL_RETAIN_YES         1       /* Preserve EXECUTE authorities when   */
                                       /* a package is replaced               */

/* Values used for option[n].val when option[n].type is SQL_RELEASE_OPT       */
#define SQL_RELEASE_COMMIT     0       /* Release resources at COMMIT         */
#define SQL_RELEASE_DEALLOCATE 1       /* Release resources when the program  */
                                       /* terminates                          */

/* Values used for option[n].val when option[n].type is SQL_STRDEL_OPT        */
#define SQL_STRDEL_APOSTROPHE  0       /* Apostrophe string delimiter         */
#define SQL_STRDEL_QUOTE       1       /* Quote string delimiter              */

/* Values used for option[n].val when option[n].type is SQL_DECDEL_OPT        */
#define SQL_DECDEL_PERIOD      0       /* Period is used as a decimal point   */
                                       /* indicator in decimal and floating   */
                                       /* point literals                      */
#define SQL_DECDEL_COMMA       1       /* Comma is used as a decimal point    */
                                       /* indicator in decimal and floating   */
                                       /* point literals                      */

/* Values used for option[n].val when option[n].type is SQL_CHARSUB_OPT       */
#define SQL_CHARSUB_DEFAULT    0       /* Use the target system defined       */
                                       /* default for all new character       */
                                       /* columns for which an explicit       */
                                       /* subtype is not specified            */
#define SQL_CHARSUB_BIT        1       /* Use the BIT character subtype for   */
                                       /* all new character columns for       */
                                       /* which an explicit subtype is not    */
                                       /* specified                           */
#define SQL_CHARSUB_SBCS       2       /* Use the SBCS character subtype for  */
                                       /* all new character columns for       */
                                       /* which an explicit subtype is not    */
                                       /* specified                           */
#define SQL_CHARSUB_MIXED      3       /* Use the mixed character subtype     */
                                       /* for all new character columns for   */
                                       /* which an explicit subtype is not    */
                                       /* specified                           */

/* Values used for option[n].val when option[n].type is SQL_DEC_OPT           */
#define SQL_DEC_15             15      /* 15 bit precision is used in         */
                                       /* decimal arithmetic operations       */
#define SQL_DEC_31             31      /* 31 bit precision is used in         */
                                       /* decimal arithmetic operations       */

/* Values used for option[n].val when option[n].type is SQL_DEGREE_OPT        */
#define SQL_DEGREE_1           1       /* Prohibits parallel I/O operations   */
#define SQL_DEGREE_ANY         0       /* Allows the target database system   */
                                       /* to determine the degree of          */
                                       /* parallel I/O operations             */
#define SQL_MAX_DEGREE_VAL     32767   /* Maximum value                       */

/* The next four option values (for CONNECT type, SQLRULES, DISCONNECT and    */
/* SYNCPOINT) are used not only by the precompiler but also by the sqlesetc   */
/* and sqleqryc APIs.                                                         */

/* Values used for option[n].val when option[n].type is SQL_CONNECT_OPT       */
#define SQL_CONNECT_1          1       /* Indicates that only one connection  */
                                       /* to a database can exist at any      */
                                       /* given time.                         */
#define SQL_CONNECT_2          2       /* Indicates that multiple             */
                                       /* connections can exist               */
                                       /* simultaneously, with one being      */
                                       /* active and the others dormant.      */

/* Values used for option[n].val when option[n].type is SQL_RULES_OPT         */
#define SQL_RULES_DB2          1       /* Indicates that CONNECT TO can be    */
                                       /* used to make a dormant connection   */
                                       /* the current connection.             */
#define SQL_RULES_STD          2       /* Indicates that CONNECT TO is not    */
                                       /* valid for making a dormant          */
                                       /* connection current, and SET         */
                                       /* CONNECTION must be used instead.    */

/* Values used for option[n].val when option[n].type is SQL_DISCONNECT_OPT    */
#define SQL_DISCONNECT_EXPL    1       /* Indicates that all connections      */
                                       /* marked by the RELEASE statement     */
                                       /* will be the only connections        */
                                       /* released when a COMMIT is issued.   */
#define SQL_DISCONNECT_COND    2       /* Indicates that all connections      */
                                       /* that do not have open WITH HOLD     */
                                       /* cursors will be the only            */
                                       /* connections released when a COMMIT  */
                                       /* is issued.                          */
#define SQL_DISCONNECT_AUTO    3       /* Indicates that all connections      */
                                       /* will be released when a COMMIT is   */
                                       /* issued.                             */

/* Values used for option[n].val when option[n].type is SQL_SYNCPOINT_OPT     */
#define SQL_SYNC_ONEPHASE      1       /* Do not use a transaction manager    */
                                       /* to perform two phase commit, but    */
                                       /* enforce that there is only one      */
                                       /* database is updated when multiple   */
                                       /* databases are accessed within a     */
                                       /* single transaction.                 */
#define SQL_SYNC_TWOPHASE      2       /* Use a transaction manager to        */
                                       /* coordinate two phase commit.        */
#define SQL_SYNC_NONE          0       /* No update enforcement or two phase  */
                                       /* commit protocol will be used.       */

/* The next option value (for SQL_CONNECT_NODE) is used only by the sqlesetc  */
/* and sqleqryc APIs.                                                         */
#define SQL_CONN_CATALOG_NODE  0xfffe  /* Connect to the catalog node         */

/* Values used for option[n].val when option[n].type is SQL_DYNAMICRULES_OPT  */
#define SQL_DYNAMICRULES_RUN   0       /* Dynamic SQL in package will use     */
                                       /* authid of person running the        */
                                       /* package                             */
#define SQL_DYNAMICRULES_BIND  1       /* Dynamic SQL in package will use     */
                                       /* authid of person who owns the       */
                                       /* package                             */

/* Values used for option[n].val when option[n].type is SQL_INSERT_OPT        */
#define SQL_INSERT_DEF         0       /* Do not buffer VALUE inserts         */
#define SQL_INSERT_BUF         1       /* Buffer VALUE inserts                */

/* Values used for option[n].val when option[n].type is SQL_EXPLSNAP_OPT      */
#define SQL_EXPLSNAP_NO        0       /* No Explain snapshot saved           */
#define SQL_EXPLSNAP_YES       1       /* Explain snapshot saved              */
#define SQL_EXPLSNAP_ALL       2       /* Explain snapshot saved for all      */
                                       /* static and dynamic statements       */

/* Maximum sqlchar length for option[n].val when option[n].type is SQL        */
/* FUNCTION_PATH                                                              */
#define SQL_MAX_FUNCPATH       254

/* Values used for option[n].val when option[n].type is SQL_SQLWARN_OPT       */
#define SQL_SQLWARN_NO         0       /* Suppress prepare-time warning       */
                                       /* SQLCODEs                            */
#define SQL_SQLWARN_YES        1       /* Permit prepare-time warning         */
                                       /* SQLCODEs                            */

/* Values used for option[n].val when option[n].type is SQL_QUERYOPT_OPT      */
#define SQL_QUERYOPT_0         0       /* Class 0 query optimization          */
#define SQL_QUERYOPT_1         1       /* Class 1 query optimization          */
#define SQL_QUERYOPT_3         3       /* Class 3 query optimization          */
#define SQL_QUERYOPT_5         5       /* Class 5 query optimization          */
#define SQL_QUERYOPT_9         9       /* Class 9 query optimization          */

/* Maximum sqlchar length for option[n].val when option[n].type is SQL        */
/* TARGET_OPT                                                                 */
#define SQL_MAX_TARGET_LEN     32

/* Binder Interface Parameters/Return Codes                                   */

SQL_API_RC SQL_API_FN                      /* Bind                            */
  sqlabndx (
        _SQLOLDCHAR * pBindFileName,       /* bind file name                  */
        _SQLOLDCHAR * pMsgFileName,        /* message file                    */
        struct sqlopt * pBindOptions,      /* bind options                    */
        struct sqlca * pSqlca);            /* SQLCA                           */

SQL_API_RC SQL_API_FN                      /* Rebind                          */
  sqlarbnd (
        char * pPackageName,               /* package name                    */
        struct sqlca * pSqlca,             /* SQLCA                           */
        void * pReserved);                 /* reserved                        */

SQL_API_RC SQL_API_FN                      /* Precompile Program              */
  sqlaprep (
        _SQLOLDCHAR * pProgramName,        /* source file name                */
        _SQLOLDCHAR * pMsgFileName,        /* message file name               */
        struct sqlopt * pPrepOptions,      /* precompile options              */
        struct sqlca * pSqlca);            /* SQLCA                           */

/* Generic Interfaces to the Binder and Precompiler                           */

SQL_API_RC SQL_API_FN                      /* Bind                            */
  sqlgbndx (
        unsigned short MsgFileNameLen,     /* message file name length        */
        unsigned short BindFileNameLen,    /* bind file name length           */
        struct sqlca * pSqlca,             /* SQLCA                           */
        struct sqlopt * pBindOptions,      /* binder options                  */
        _SQLOLDCHAR * pMsgFileName,        /* message file                    */
        _SQLOLDCHAR * pBindFileName);      /* bind file name                  */

SQL_API_RC SQL_API_FN                      /* Rebind                          */
  sqlgrbnd (
        unsigned short PackageNameLen,     /* package name length             */
        char * pPackageName,               /* package name                    */
        struct sqlca * pSqlca,             /* SQLCA                           */
        void * pReserved);                 /* reserved                        */

SQL_API_RC SQL_API_FN                      /* Precompile Program              */
  sqlgprep (
        unsigned short MsgFileNameLen,     /* message file name length        */
        unsigned short ProgramNameLen,     /* source file name length         */
        struct sqlca * pSqlca,             /* SQLCA                           */
        struct sqlopt * pPrepOptions,      /* precompile options              */
        _SQLOLDCHAR * pMsgFileName,        /* message file name               */
        _SQLOLDCHAR * pProgramName);       /* source file name                */

/* Application Context apis                                                   */


#define SQL_CTX_ORIGINAL 0                 /* serial access                   */
#define SQL_CTX_MULTI_MANUAL 1             /* concurrent access               */
SQL_API_RC SQL_API_FN                      /* Set Application Context         */
  sqleSetTypeCtx (
        long);                             /* options                         */


#define SQL_CTX_BEGIN_ALL 0                /* create & attach                 */
#define SQL_CTX_CREATE_ONLY 1              /* create only                     */
SQL_API_RC SQL_API_FN                      /* Create Application Context      */
  sqleBeginCtx (
        void **,                           /* pointer to ctx                  */
        long,                              /* lOptions                        */
        void *,                            /* reserved                        */
        struct sqlca *);                   /* SQLCA                           */


#define SQL_CTX_END_ALL 0                  /* detach & free                   */
#define SQL_CTX_FREE_ONLY 1                /* free only                       */
SQL_API_RC SQL_API_FN                      /* Destroy Application Context     */
  sqleEndCtx (
        void **,                           /* pointer to ctx                  */
        long,                              /* lOptions                        */
        void *,                            /* reserved                        */
        struct sqlca *);                   /* SQLCA                           */


SQL_API_RC SQL_API_FN                      /* Attach to Application Context   */
  sqleAttachToCtx (
        void *,                            /* pointer to ctx                  */
        void *,                            /* reserved                        */
        struct sqlca *);                   /* SQLCA                           */


SQL_API_RC SQL_API_FN                      /* Detach Application Context      */
  sqleDetachFromCtx (
        void *,                            /* pointer to ctx                  */
        void *,                            /* reserved                        */
        struct sqlca *);                   /* SQLCA                           */


SQL_API_RC SQL_API_FN                      /* Destroy Application Context     */
  sqleGetCurrentCtx (
        void **,                           /* pointer to ctx                  */
        void *,                            /* reserved                        */
        struct sqlca *);                   /* SQLCA                           */


SQL_API_RC SQL_API_FN                      /* Interrupt Context               */
  sqleInterruptCtx (
        void *,                            /* pointer to ctx                  */
        void *,                            /* reserved                        */
        struct sqlca *);                   /* SQLCA                           */


/* Error/SQLSTATE Message Retrieval Interface Parameters/Return Codes         */

/* Get Error Message Macro                                                    */
#define  sqlaintp(msgbuf,bufsize,linesize,sqlcaptr) \
sqlaintp_api(msgbuf,bufsize,linesize, \
(char *)"db2sql.mo", sqlcaptr)
SQL_API_RC SQL_API_FN                      /* Get Error Message               */
  sqlaintp_api (
        char * pBuffer,                    /* buffer for message text         */
        short BufferSize,                  /* buffer size                     */
        short LineWidth,                   /* line width                      */
        char * pMsgFileName,               /* message file                    */
        struct sqlca * pSqlca);            /* SQLCA                           */

/* Generic Interface to Error Message Retrieval                               */
SQL_API_RC SQL_API_FN                      /* Get Error Message               */
  sqlgintp (
        short BufferSize,                  /* buffer size                     */
        short LineWidth,                   /* line width                      */
        struct sqlca * pSqlca,             /* SQLCA                           */
        _SQLOLDCHAR * pBuffer);            /* buffer                          */

SQL_API_RC SQL_API_FN                      /* Sqlstate Message Retrieval      */
  sqlogstt (
        char * pBuffer,                    /* buffer for message text         */
        short BufferSize,                  /* buffer size                     */
        short LineWidth,                   /* line width                      */
        char * pSqlstate);                 /* sqlstate                        */

/* Generic Interface to SQLSTATE Message Retrieval                            */
SQL_API_RC SQL_API_FN                      /* Sqlstate Message Retrieval      */
  sqlggstt (
        short BufferSize,                  /* buffer size                     */
        short LineWidth,                   /* line width                      */
        char * pSqlstate,                  /* sqlstate                        */
        char * pBuffer);                   /* buffer                          */

/* Return Codes for sqlaintp/sqlogstt                                         */
#define SQLA_ERR_BADCC         -1      /* insufficient memory for msg file    */
#define SQLA_ERR_NOCOD         -2      /* no error code in SQLCA              */
#define SQLA_ERR_NOMSG         -3      /* message file inaccessible or        */
                                       /* incorrect                           */
#define SQLA_ERR_BADLL         -4      /* specified line length negative      */
#define SQLA_ERR_BADCA         -5      /* invalid sqlca/buffer addr/length    */

/* Administrative/Database Authorizations returned from Get Administrative    */
/* Authorizations function                                                    */
/* Authorizations granted explicitly to user                                  */
#define SQL_SYSADM             0x1     /* SYSADM Authority                    */
#define SQL_DBADM              0x2     /* DBADM Authority                     */
#define SQL_CREATETAB          0x4     /* CREATETAB Privilege                 */
#define SQL_BINDADD            0x8     /* BINDADD Privilege                   */
#define SQL_CONNECT            0x10    /* CONNECT Privilege                   */
#define SQL_CREATE_NOT_FENC    0x20    /* CREATE_NOT_FENCED Privilege         */
#define SQL_SYSCTRL            0x40    /* SYSCTRL Authority                   */
#define SQL_SYSMAINT           0x80    /* SYSMAINT Authority                  */
#define SQL_IMPLICIT_SCHEMA    0x10000 /* IMPLICIT_SCHEMA Privilege           */

/* Composite of authorizations granted explicitly to user, to groups of       */
/* which user is a member, and to PUBLIC                                      */
#define SQL_SYSADM_GRP         (SQL_SYSADM << 8)
#define SQL_DBADM_GRP          (SQL_DBADM << 8)
#define SQL_CREATETAB_GRP      (SQL_CREATETAB << 8)
#define SQL_BINDADD_GRP        (SQL_BINDADD << 8)
#define SQL_CONNECT_GRP        (SQL_CONNECT << 8)
#define SQL_CREATE_NOT_FENC_GRP (SQL_CREATE_NOT_FENC << 8)
#define SQL_SYSCTRL_GRP        (SQL_SYSCTRL << 8)
#define SQL_SYSMAINT_GRP       (SQL_SYSMAINT << 8)
#define SQL_IMPLICIT_SCHEMA_GRP (SQL_IMPLICIT_SCHEMA << 8)

/* Table/View Authorizations/Dependencies Bit definitions in                  */
/* SYSTABAUTH.TABAUTH and SYSPLANDEP.TABAUTH                                  */
#define SQL_TAB_CTL            0x1     /* Control Authority                   */
#define SQL_TAB_ALT            0x2     /* Alter Privilege                     */
#define SQL_TAB_DEL            0x4     /* Delete Privilege/Dependency         */
#define SQL_TAB_IDX            0x8     /* Index Privilege                     */
#define SQL_TAB_INS            0x10    /* Insert Privilege/Dependency         */
#define SQL_TAB_SEL            0x20    /* Select Privilege/Dependency         */
#define SQL_TAB_UPD            0x40    /* Update Privilege/Dependency         */
#define SQL_TAB_REF            0x80    /* Reference Privilege                 */
#define SQL_TAB_KEY            0x2000  /* Key Dependency                      */
#define SQL_TAB_CAS            0x4000  /* Cascade Dependency                  */

/* Bit definitions for SYSTABAUTH.TABAUTH indicating the specified table or   */
/* view privilege is grantable.                                               */
#define SQL_TAB_ALT_G          0x200   /* Alter Privilege Grantable           */
#define SQL_TAB_DEL_G          0x400   /* Delete Privilege Grantable          */
#define SQL_TAB_IDX_G          0x800   /* Index Privilege Grantable           */
#define SQL_TAB_INS_G          0x1000  /* Insert Privilege Grantable          */
#define SQL_TAB_SEL_G          0x2000  /* Select Privilege Grantable          */
#define SQL_TAB_UPD_G          0x4000  /* Update Privilege Grantable          */
#define SQL_TAB_REF_G          0x8000  /* References Privilege Grantable      */

/* Definitions for application remote interface                               */
#define SQLZ_DISCONNECT_PROC   1       /* Unload Progam                       */
#define SQLZ_HOLD_PROC         2       /* Keep program loaded                 */
/******************************************************************************
** 
** The following functions and symbols are obsolete and may not be
** supported in future releases. The obsolete functions are provided
** for backward compatibility and exported from DB2API.LIB. All 
** applications should be migrated to use new APIs.
*******************************************************************************/
#define SQLA_RC_BAD_PASSWD     -4      /* Invalid password                    */
#define SQL_MAXSTMTS           32767   /* Maximum statements (see SQL         */
                                       /* reference)                          */
#define SQL_MAXVARS            32767   /* Maximum host variables per          */
                                       /* precompile unit (see SQL            */
                                       /* reference)                          */
#pragma pack()

#ifdef __cplusplus 
}
#endif

#endif /* SQL_H_SQL */
