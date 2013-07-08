/******************************************************************************
 *
 * Source File Name = sqlcli1.h
 *
 * (C) COPYRIGHT International Business Machines Corp. 1993, 1997
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * Function = Include File defining:
 *              DB2 CLI Interface - Constants
 *              DB2 CLI Interface - Function Prototypes
 *
 * Operating System = Common C Include File
 *
 *****************************************************************************/

#ifndef SQL_H_SQLCLI1
   #define SQL_H_SQLCLI1           /* Permit duplicate Includes */


#ifdef __cplusplus
extern "C" {
#endif

#include "sqlsystm.h"              /* System dependent defines  */


#if defined(DB2WIN) || defined(DB2NT)
#include <windows.h>
#endif
#ifdef DB2OS2
#define INCL_WIN
#define INCL_DOS
#include <os2.h>
#endif

#include    "sqlca.h"
#include    "sqlcli.h"

/* SQLGetFunction defines  - supported functions */
#define  SQL_API_SQLALLOCCONNECT        1
#define  SQL_API_SQLALLOCENV            2
#define  SQL_API_SQLALLOCSTMT           3
#define  SQL_API_SQLBINDCOL             4
#define  SQL_API_SQLBINDPARAM           1002
#define  SQL_API_SQLCANCEL              5
#define  SQL_API_SQLCONNECT             7
#define  SQL_API_SQLCOPYDESC            1004
#define  SQL_API_SQLDESCRIBECOL         8
#define  SQL_API_SQLDISCONNECT          9
#define  SQL_API_SQLERROR              10
#define  SQL_API_SQLEXECDIRECT         11
#define  SQL_API_SQLEXECUTE            12
#define  SQL_API_SQLFETCH              13
#define  SQL_API_SQLFREECONNECT        14
#define  SQL_API_SQLFREEENV            15
#define  SQL_API_SQLFREESTMT           16
#define  SQL_API_SQLGETCURSORNAME      17
#define  SQL_API_SQLNUMRESULTCOLS      18
#define  SQL_API_SQLPREPARE            19
#define  SQL_API_SQLROWCOUNT           20
#define  SQL_API_SQLSETCURSORNAME      21
#define  SQL_API_SQLSETDESCFIELD       1017
#define  SQL_API_SQLSETDESCREC         1018
#define  SQL_API_SQLSETENVATTR         1019
#define  SQL_API_SQLSETPARAM           22
#define  SQL_API_SQLTRANSACT           23

#define  SQL_API_SQLCOLUMNS            40
#define  SQL_API_SQLGETCONNECTOPTION   42
#define  SQL_API_SQLGETDATA            43
#define  SQL_API_SQLGETDESCFIELD       1008
#define  SQL_API_SQLGETDESCREC         1009
#define  SQL_API_SQLGETDIAGFIELD       1010
#define  SQL_API_SQLGETDIAGREC         1011
#define  SQL_API_SQLGETENVATTR         1012
#define  SQL_API_SQLGETFUNCTIONS       44
#define  SQL_API_SQLGETINFO            45
#define  SQL_API_SQLGETSTMTOPTION      46
#define  SQL_API_SQLGETTYPEINFO        47
#define  SQL_API_SQLPARAMDATA          48
#define  SQL_API_SQLPUTDATA            49
#define  SQL_API_SQLSETCONNECTOPTION   50
#define  SQL_API_SQLSETSTMTOPTION      51
#define  SQL_API_SQLSPECIALCOLUMNS     52
#define  SQL_API_SQLSTATISTICS         53
#define  SQL_API_SQLTABLES             54
#define  SQL_API_SQLDATASOURCES        57
#define  SQL_API_SQLSETCONNECTATTR     1016
#define  SQL_API_SQLSETSTMTATTR        1020

#define  SQL_API_SQLBINDFILETOCOL      1250
#define  SQL_API_SQLBINDFILETOPARAM    1251
#define  SQL_API_SQLSETCOLATTRIBUTES   1252
#define  SQL_API_SQLGETSQLCA           1253

#define  SQL_API_SQLFETCHSCROLL        1021
#define  SQL_API_SQLGETLENGTH          1022
#define  SQL_API_SQLGETPOSITION        1023
#define  SQL_API_SQLGETSUBSTRING       1024

#define  SQL_API_SQLSETCONNECTION      1254

#define  SQL_API_SQLALLOCHANDLE        1001
#define  SQL_API_SQLFREEHANDLE         1006
#define  SQL_API_SQLCLOSECURSOR        1003
#define  SQL_API_SQLENDTRAN            1005
#define  SQL_API_SQLCOLATTRIBUTE       6
#define  SQL_API_SQLGETSTMTATTR        1014
#define  SQL_API_SQLGETCONNECTATTR     1007

/* SQLGetFunction defines  - unsupported functions */
#define  SQL_EXT_API_LAST              72

/* Information requested by SQLGetInfo() */
#define SQL_MAX_DRIVER_CONNECTIONS           0
#define SQL_MAXIMUM_DRIVER_CONNECTIONS          SQL_MAX_DRIVER_CONNECTIONS
#define SQL_MAX_CONCURRENT_ACTIVITIES        1
#define SQL_MAXIMUM_CONCURRENT_ACTIVITIES       SQL_MAX_CONCURRENT_ACTIVITIES


/* SQLGetInfo defines  - Info Type */
#define  SQL_DATA_SOURCE_NAME                  2
#define  SQL_FETCH_DIRECTION                   8
#define  SQL_SERVER_NAME                      13
#define  SQL_SEARCH_PATTERN_ESCAPE            14
#define  SQL_DBMS_NAME                        17
#define  SQL_DBMS_VER                         18
#define  SQL_ACCESSIBLE_TABLES                19
#define  SQL_ACCESSIBLE_PROCEDURES            20
#define  SQL_CURSOR_COMMIT_BEHAVIOR           23
#define  SQL_DATA_SOURCE_READ_ONLY            25
#define  SQL_DEFAULT_TXN_ISOLATION            26
#define  SQL_IDENTIFIER_CASE                  28
#define  SQL_IDENTIFIER_QUOTE_CHAR            29
#define  SQL_MAX_COLUMN_NAME_LEN              30
#define  SQL_MAXIMUM_COLUMN_NAME_LENGTH       SQL_MAX_COLUMN_NAME_LEN
#define  SQL_MAX_CURSOR_NAME_LEN              31
#define  SQL_MAXIMUM_CURSOR_NAME_LENGTH       SQL_MAX_CURSOR_NAME_LEN
#define  SQL_MAX_TABLE_NAME_LEN               35
#define  SQL_SCROLL_CONCURRENCY               43
#define  SQL_TXN_CAPABLE                      46
#define  SQL_TRANSACTION_CAPABLE              SQL_TXN_CAPABLE
#define  SQL_USER_NAME                        47
#define  SQL_TXN_ISOLATION_OPTION             72
#define  SQL_TRANSACTION_ISOLATION_OPTION     SQL_TXN_ISOLATION_OPTION
#define  SQL_GETDATA_EXTENSIONS               81
#define  SQL_NULL_COLLATION                   85
#define  SQL_ALTER_TABLE                      86
#define  SQL_ORDER_BY_COLUMNS_IN_SELECT       90
#define  SQL_SPECIAL_CHARACTERS               94
#define  SQL_MAX_COLUMNS_IN_GROUP_BY          97
#define  SQL_MAXIMUM_COLUMNS_IN_GROUP_BY      SQL_MAX_COLUMNS_IN_GROUP_BY
#define  SQL_MAX_COLUMNS_IN_INDEX             98
#define  SQL_MAXIMUM_COLUMNS_IN_INDEX         SQL_MAX_COLUMNS_IN_INDEX
#define  SQL_MAX_COLUMNS_IN_ORDER_BY          99
#define  SQL_MAXIMUM_COLUMNS_IN_ORDER_BY      SQL_MAX_COLUMNS_IN_ORDER_BY
#define  SQL_MAX_COLUMNS_IN_SELECT           100
#define  SQL_MAXIMUM_COLUMNS_IN_SELECT       SQL_MAX_COLUMNS_IN_SELECT
#define  SQL_MAX_COLUMNS_IN_TABLE            101
#define  SQL_MAX_INDEX_SIZE                  102
#define  SQL_MAXIMUM_INDEX_SIZE              SQL_MAX_INDEX_SIZE
#define  SQL_MAX_ROW_SIZE                    104
#define  SQL_MAXIMUM_ROW_SIZE                SQL_MAX_ROW_SIZE
#define  SQL_MAX_STATEMENT_LEN               105
#define  SQL_MAXIMUM_STATEMENT_LENGTH        SQL_MAX_STATEMENT_LEN
#define  SQL_MAX_TABLES_IN_SELECT            106
#define  SQL_MAXIMUM_TABLES_IN_SELECT        SQL_MAX_TABLES_IN_SELECT
#define  SQL_MAX_USER_NAME_LEN               107
#define  SQL_MAXIMUM_USER_NAME_LENGTH        SQL_MAX_USER_NAME_LEN
#define  SQL_MAX_SCHEMA_NAME_LEN             SQL_MAX_OWNER_NAME_LEN
#define  SQL_MAXIMUM_SCHEMA_NAME_LENGTH      SQL_MAX_SCHEMA_NAME_LEN
#define  SQL_MAX_CATALOG_NAME_LEN            SQL_MAX_QUALIFIER_NAME_LEN
#define  SQL_MAXIMUM_CATALOG_NAME_LENGTH     SQL_MAX_CATALOG_NAME_LEN
#define  SQL_OJ_CAPABILITIES                115
#define  SQL_OUTER_JOIN_CAPABILITIES                SQL_OJ_CAPABILITIES
#define  SQL_XOPEN_CLI_YEAR               10000
#define  SQL_CURSOR_SENSITIVITY           10001
#define  SQL_DESCRIBE_PARAMETER           10002
#define  SQL_CATALOG_NAME                 10003
#define  SQL_COLLATION_SEQ                10004
#define  SQL_MAX_IDENTIFIER_LEN           10005
#define  SQL_MAXIMUM_IDENTIFIER_LENGTH    SQL_MAX_IDENTIFIER_LEN
#define  SQL_INTEGRITY                       73


#define SQL_INFO_LAST                         114
#define SQL_INFO_DRIVER_START                 1000

/* SQL_ALTER_TABLE bitmasks */
#define SQL_AT_ADD_COLUMN                       0x00000001L
#define SQL_AT_DROP_COLUMN                      0x00000002L
#define SQL_AT_ADD_CONSTRAINT                   0x00000008L

/* SQL_CURSOR_COMMIT_BEHAVIOR and SQL_CURSOR_ROLLBACK_BEHAVIOR values */

#define SQL_CB_DELETE                 0x0000
#define SQL_CB_CLOSE                  0x0001
#define SQL_CB_PRESERVE               0x0002

/* SQL_IDENTIFIER_CASE values */

#define SQL_IC_UPPER                  0x0001
#define SQL_IC_LOWER                  0x0002
#define SQL_IC_SENSITIVE              0x0003
#define SQL_IC_MIXED                  0x0004

/* SQL_TXN_CAPABLE values */

#define SQL_TC_NONE                   0x0000
#define SQL_TC_DML                    0x0001
#define SQL_TC_ALL                    0x0002
#define SQL_TC_DDL_COMMIT             0x0003
#define SQL_TC_DDL_IGNORE             0x0004

/* SQL_SCROLL_CONCURRENCY masks */

#define SQL_SCCO_READ_ONLY            0x00000001L
#define SQL_SCCO_LOCK                 0x00000002L
#define SQL_SCCO_OPT_ROWVER           0x00000004L
#define SQL_SCCO_OPT_VALUES           0x00000008L

/* SQL_FETCH_DIRECTION masks */

#define  SQL_FD_FETCH_NEXT            0x00000001L
#define  SQL_FD_FETCH_FIRST           0x00000002L
#define  SQL_FD_FETCH_LAST            0x00000004L
#define  SQL_FD_FETCH_PRIOR           0x00000008L
#define  SQL_FD_FETCH_ABSOLUTE        0x00000010L
#define  SQL_FD_FETCH_RELATIVE        0x00000020L
#define  SQL_FD_FETCH_RESUME          0x00000040L

/* SQL_TXN_ISOLATION_OPTION masks */
#define SQL_TXN_READ_UNCOMMITTED            0x00000001L
#define SQL_TRANSACTION_READ_UNCOMMITTED        SQL_TXN_READ_UNCOMMITTED
#define SQL_TXN_READ_COMMITTED              0x00000002L
#define SQL_TRANSACTION_READ_COMMITTED          SQL_TXN_READ_COMMITTED
#define SQL_TXN_REPEATABLE_READ             0x00000004L
#define SQL_TRANSACTION_REPEATABLE_READ         SQL_TXN_REPEATABLE_READ
#define SQL_TXN_SERIALIZABLE                0x00000008L
#define SQL_TRANSACTION_SERIALIZABLE            SQL_TXN_SERIALIZABLE
#define SQL_TXN_NOCOMMIT                   0x00000020L
#define SQL_TRANSACTION_NOCOMMIT                SQL_TXN_NOCOMMIT

/* SQL_GETDATA_EXTENSIONS values */

#define SQL_GD_ANY_COLUMN             0x00000001L
#define SQL_GD_ANY_ORDER              0x00000002L

/* SQL_OJ_CAPABILITIES values */

#define SQL_OJ_LEFT                   0x00000001L
#define SQL_OJ_RIGHT                  0x00000002L
#define SQL_OJ_FULL                   0x00000004L
#define SQL_OJ_NESTED                 0x00000008L
#define SQL_OJ_NOT_ORDERED            0x00000010L
#define SQL_OJ_INNER                  0x00000020L
#define SQL_OJ_ALL_COMPARISON_OPS     0x00000040L


/* SQLGetTypeInfo define */
#define  SQL_ALL_TYPES                0

/* Options for SQLGetStmtOption/SQLSetStmtOption */

#define SQL_ATTR_AUTO_IPD               10001
#define SQL_ATTR_APP_ROW_DESC           10010
#define SQL_ATTR_APP_PARAM_DESC         10011
#define SQL_ATTR_IMP_ROW_DESC           10012
#define SQL_ATTR_IMP_PARAM_DESC         10013
#define SQL_ATTR_METADATA_ID            10014
#define SQL_ATTR_CURSOR_SCROLLABLE      (-1)
#define SQL_ATTR_CURSOR_SENSITIVITY     (-2)

/* SQL_ATTR_CURSOR_SCROLLABLE values */
#define SQL_NONSCROLLABLE                       0
#define SQL_SCROLLABLE                          1

/* Options for SQLGetStmtOption/SQLSetStmtOption extensions */
#define  SQL_CURSOR_HOLD              1250
#define  SQL_ATTR_CURSOR_HOLD         1250
#define  SQL_NODESCRIBE_OUTPUT        1251
#define  SQL_ATTR_NODESCRIBE_OUTPUT   1251

#define  SQL_NODESCRIBE_INPUT         1264
#define  SQL_ATTR_NODESCRIBE_INPUT    1264
#define  SQL_NODESCRIBE               SQL_NODESCRIBE_OUTPUT
#define  SQL_ATTR_NODESCRIBE          SQL_NODESCRIBE_OUTPUT
#define  SQL_CLOSE_BEHAVIOR           1257
#define  SQL_ATTR_CLOSE_BEHAVIOR      1257
#define  SQL_ATTR_CLOSE_BEHAVIOR      1257
#define  SQL_ATTR_CLOSEOPEN           1265
#define  SQL_ATTR_CURRENT_PACKAGE_SET 1276
#define  SQL_ATTR_DEFERRED_PREPARE    1277
#define  SQL_ATTR_EARLYCLOSE          1268
#define  SQL_ATTR_PROCESSCTL          1278

/* SQL_CLOSE_BEHAVIOR values.                  */

#define SQL_CC_NO_RELEASE             0
#define SQL_CC_RELEASE                1
#define SQL_CC_DEFAULT                SQL_CC_NO_RELEASE

/* SQL_ATTR_DEFERRED_PREPARE values  */

#define SQL_DEFERRED_PREPARE_ON       1
#define SQL_DEFERRED_PREPARE_OFF      0
#define SQL_DEFERRED_PREPARE_DEFAULT  SQL_DEFERRED_PREPARE_ON

/* SQL_ATTR_EARLYCLOSE values  */

#define SQL_EARLYCLOSE_ON             1
#define SQL_EARLYCLOSE_OFF            0
#define SQL_EARLYCLOSE_DEFAULT        SQL_EARLYCLOSE_ON


/* SQL_ATTR_PROCESSCTL masks  */

#define SQL_PROCESSCTL_NOTHREAD       0x00000001L
#define SQL_PROCESSCTL_NOFORK         0x00000002L

/* CLI attribute/option values */
#define SQL_FALSE               0
#define SQL_TRUE                1

/* Options for SQL_CURSOR_HOLD */
#define SQL_CURSOR_HOLD_ON        1
#define SQL_CURSOR_HOLD_OFF       0
#define SQL_CURSOR_HOLD_DEFAULT   SQL_CURSOR_HOLD_ON


/* Options for SQL_NODESCRIBE_INPUT/SQL_NODESCRIBE_OUTPUT */
#define SQL_NODESCRIBE_ON          1
#define SQL_NODESCRIBE_OFF         0
#define SQL_NODESCRIBE_DEFAULT     SQL_NODESCRIBE_OFF


/* Options for SQLGetConnectOption/SQLSetConnectOption extensions */
#define SQL_WCHARTYPE                1252
#define SQL_LONGDATA_COMPAT          1253
#define SQL_CURRENT_SCHEMA           1254
#define SQL_DB2EXPLAIN               1258
#define SQL_DB2ESTIMATE              1259
#define SQL_PARAMOPT_ATOMIC          1260
#define SQL_STMTTXN_ISOLATION        1261
#define SQL_MAXCONN                  1262

#define SQL_ATTR_WCHARTYPE          SQL_WCHARTYPE
#define SQL_ATTR_LONGDATA_COMPAT    SQL_LONGDATA_COMPAT
#define SQL_ATTR_CURRENT_SCHEMA     SQL_CURRENT_SCHEMA
#define SQL_ATTR_DB2EXPLAIN         SQL_DB2EXPLAIN
#define SQL_ATTR_DB2ESTIMATE        SQL_DB2ESTIMATE
#define SQL_ATTR_PARAMOPT_ATOMIC    SQL_PARAMOPT_ATOMIC
#define SQL_ATTR_STMTTXN_ISOLATION  SQL_STMTTXN_ISOLATION
#define SQL_ATTR_MAXCONN            SQL_MAXCONN

/* Options for SQLSetConnectOption, SQLSetEnvAttr */
#define SQL_CONNECTTYPE              1255
#define SQL_SYNC_POINT               1256
#define SQL_MINMEMORY_USAGE          1263
#define SQL_CONN_CONTEXT             1269
#define SQL_ATTR_INHERIT_NULL_CONNECT    1270
#define SQL_ATTR_FORCE_CONVERSION_ON_CLIENT 1275

#define SQL_ATTR_CONNECTTYPE         SQL_CONNECTTYPE
#define SQL_ATTR_SYNC_POINT          SQL_SYNC_POINT
#define SQL_ATTR_MINMEMORY_USAGE     SQL_MINMEMORY_USAGE
#define SQL_ATTR_CONN_CONTEXT        SQL_CONN_CONTEXT

/* Options for SQL_LONGDATA_COMPAT */
#define SQL_LD_COMPAT_YES            1
#define SQL_LD_COMPAT_NO             0
#define SQL_LD_COMPAT_DEFAULT        SQL_LD_COMPAT_NO

/* SQL_NULL_COLLATION values */
#define SQL_NC_HIGH                         0
#define SQL_NC_LOW                          1

/*
 *  Options for SQL_PARAMOPT_ATOMIC
 */

#define SQL_ATOMIC_YES               1
#define SQL_ATOMIC_NO                0
#define SQL_ATOMIC_DEFAULT           SQL_ATOMIC_YES

/* Options for SQL_CONNECT_TYPE */
#define SQL_CONCURRENT_TRANS         1
#define SQL_COORDINATED_TRANS        2
#define SQL_CONNECTTYPE_DEFAULT      SQL_CONCURRENT_TRANS

/* Options for SQL_SYNCPOINT */
#define SQL_ONEPHASE                 1
#define SQL_TWOPHASE                 2
#define SQL_SYNCPOINT_DEFAULT        SQL_ONEPHASE

/* Options for SQL_DB2ESTIMATE */
#define SQL_DB2ESTIMATE_ON           1
#define SQL_DB2ESTIMATE_OFF          0
#define SQL_DB2ESTIMATE_DEFAULT      SQL_DB2ESTIMATE_OFF

/* Options for SQL_DB2EXPLAIN */
#define SQL_DB2EXPLAIN_OFF              0x00000000L
#define SQL_DB2EXPLAIN_SNAPSHOT_ON      0x00000001L
#define SQL_DB2EXPLAIN_MODE_ON          0x00000002L
#define SQL_DB2EXPLAIN_SNAPSHOT_MODE_ON SQL_DB2EXPLAIN_SNAPSHOT_ON+SQL_DB2EXPLAIN_MODE_ON
#define SQL_DB2EXPLAIN_ON               SQL_DB2EXPLAIN_SNAPSHOT_ON
#define SQL_DB2EXPLAIN_DEFAULT          SQL_DB2EXPLAIN_OFF

/* Options for SQL_WCHARTYPE
 * Note that you can only specify SQL_WCHARTYPE_CONVERT if you have an
 * external compile flag SQL_WCHART_CONVERT defined
 */
#ifdef SQL_WCHART_CONVERT
#define SQL_WCHARTYPE_CONVERT        1
#endif
#define SQL_WCHARTYPE_NOCONVERT      0
#define SQL_WCHARTYPE_DEFAULT        SQL_WCHARTYPE_NOCONVERT

/* Column types and scopes in SQLSpecialColumns */

#define SQL_SCOPE_CURROW             0
#define SQL_SCOPE_TRANSACTION        1
#define SQL_SCOPE_SESSION            2

/* Defines for SQLStatistics */
#define SQL_INDEX_UNIQUE             0
#define SQL_INDEX_ALL                1

/* Defines for SQLStatistics (returned in the result set) */
#define SQL_INDEX_CLUSTERED          1
#define SQL_INDEX_HASHED             2
#define SQL_INDEX_OTHER              3

/* Defines for SQLSpecialColumns (returned in the result set) */
#define SQL_PC_UNKNOWN               0
#define SQL_PC_NON_PSEUDO            1
#define SQL_PC_PSEUDO                2

/* Reserved value for the IdentifierType argument of SQLSpecialColumns() */
#define SQL_ROW_IDENTIFIER  1

/* SQLDataSources "fDirection" values, also used on SQLExtendedFetch() */
/* See sqlext.h for additional SQLExtendedFetch fetch direction defines */
#define  SQL_FETCH_NEXT              1
#define  SQL_FETCH_FIRST             2

/* OTHER CODES USED FOR FETCHORIENTATION IN SQLFETCHSCROLL() */
#define SQL_FETCH_LAST      3
#define SQL_FETCH_PRIOR     4
#define SQL_FETCH_ABSOLUTE  5
#define SQL_FETCH_RELATIVE  6

/*
 * Environment attributes; note SQL_CONNECTTYPE, SQL_SYNC_POINT are also
 * environment attributes that are settable at the connection level
 */

#define SQL_ATTR_OUTPUT_NTS          10001


/*  LOB file reference options */
#ifndef SQL_H_SQL                     /* if sql.h is not included, then...  */
#define SQL_FILE_READ              2  /* Input file to read from            */
#define SQL_FILE_CREATE            8  /* Output file - new file to be       */
                                      /* created                            */
#define SQL_FILE_OVERWRITE        16  /* Output file - overwrite existing   */
                                      /* file or create a new file if it    */
                                      /* doesn't exist                      */
#define SQL_FILE_APPEND           32  /* Output file - append to an         */
                                      /* existing file or create a new file */
                                      /* if it doesn't exist                */
#endif

/*
 *  Source of string for SQLGetLength(), SQLGetPosition(),
 *  and SQLGetSubstring().
 */
#define SQL_FROM_LOCATOR           2
#define SQL_FROM_LITERAL           3



/*
 *  Function definitions of APIs in both X/Open CLI and ODBC
 */

SQLRETURN SQL_API_FN  SQLColumns       (SQLHSTMT          hstmt,
                                        SQLCHAR     FAR   *szCatalogName,
                                        SQLSMALLINT       cbCatalogName,
                                        SQLCHAR     FAR   *szSchemaName,
                                        SQLSMALLINT       cbSchemaName,
                                        SQLCHAR     FAR   *szTableName,
                                        SQLSMALLINT       cbTableName,
                                        SQLCHAR     FAR   *szColumnName,
                                        SQLSMALLINT       cbColumnName);

SQLRETURN SQL_API_FN  SQLDataSources   (SQLHENV           henv,
                                        SQLUSMALLINT      fDirection,
                                        SQLCHAR     FAR   *szDSN,
                                        SQLSMALLINT       cbDSNMax,
                                        SQLSMALLINT FAR   *pcbDSN,
                                        SQLCHAR     FAR   *szDescription,
                                        SQLSMALLINT       cbDescriptionMax,
                                        SQLSMALLINT FAR   *pcbDescription);
SQLRETURN  SQL_API SQLFetchScroll(      SQLHSTMT StatementHandle,
                                        SQLSMALLINT FetchOrientation,
                                        SQLINTEGER FetchOffset);
SQLRETURN  SQL_API SQLGetConnectAttr(   SQLHDBC ConnectionHandle,
                                        SQLINTEGER Attribute,
                                        SQLPOINTER Value,
                                        SQLINTEGER BufferLength,
                                        SQLINTEGER *StringLength);

SQLRETURN SQL_API_FN  SQLGetConnectOption (
                                        SQLHDBC           hdbc,
                                        SQLUSMALLINT      fOption,
                                        SQLPOINTER        pvParam);

SQLRETURN SQL_API_FN  SQLGetFunctions  (SQLHDBC           hdbc,
                                        SQLUSMALLINT      fFunction,
                                        SQLUSMALLINT FAR  *pfExists);

SQLRETURN SQL_API_FN  SQLGetInfo       (SQLHDBC           hdbc,
                                        SQLUSMALLINT      fInfoType,
                                        SQLPOINTER        rgbInfoValue,
                                        SQLSMALLINT       cbInfoValueMax,
                                        SQLSMALLINT FAR   *pcbInfoValue);

SQLRETURN  SQL_API SQLGetStmtAttr(      SQLHSTMT StatementHandle,
                                        SQLINTEGER Attribute,
                                        SQLPOINTER Value,
                                        SQLINTEGER BufferLength,
                                        SQLINTEGER *StringLength);

SQLRETURN SQL_API_FN  SQLGetStmtOption (SQLHSTMT          hstmt,
                                        SQLUSMALLINT      fOption,
                                        SQLPOINTER        pvParam);

SQLRETURN SQL_API_FN  SQLGetTypeInfo   (SQLHSTMT          hstmt,
                                        SQLSMALLINT       fSqlType);

SQLRETURN SQL_API_FN  SQLParamData     (SQLHSTMT          hstmt,
                                        SQLPOINTER  FAR   *prgbValue);

SQLRETURN SQL_API_FN  SQLPutData       (SQLHSTMT          hstmt,
                                        SQLPOINTER        rgbValue,
                                        SQLINTEGER        cbValue);

SQLRETURN SQL_API_FN  SQLSetConnectAttr(
                                        SQLHDBC           hdbc,
                                        SQLINTEGER        fOption,
                                        SQLPOINTER        pvParam,
                                        SQLINTEGER        fStrLen);

SQLRETURN SQL_API_FN  SQLSetConnectOption(
                                        SQLHDBC           hdbc,
                                        SQLUSMALLINT      fOption,
                                        SQLUINTEGER       vParam);

SQLRETURN SQL_API_FN  SQLSetStmtAttr   (SQLHSTMT          hstmt,
                                        SQLINTEGER        fOption,
                                        SQLPOINTER        pvParam,
                                        SQLINTEGER       fStrLen);

SQLRETURN SQL_API_FN  SQLSetStmtOption (SQLHSTMT          hstmt,
                                        SQLUSMALLINT      fOption,
                                        SQLUINTEGER       vParam);

SQLRETURN SQL_API_FN  SQLSpecialColumns(SQLHSTMT          hstmt,
                                        SQLUSMALLINT      fColType,
                                        SQLCHAR     FAR   *szCatalogName,
                                        SQLSMALLINT       cbCatalogName,
                                        SQLCHAR     FAR   *szSchemaName,
                                        SQLSMALLINT       cbSchemaName,
                                        SQLCHAR     FAR   *szTableName,
                                        SQLSMALLINT       cbTableName,
                                        SQLUSMALLINT      fScope,
                                        SQLUSMALLINT      fNullable);

SQLRETURN SQL_API_FN  SQLStatistics    (SQLHSTMT          hstmt,
                                        SQLCHAR     FAR   *szCatalogName,
                                        SQLSMALLINT       cbCatalogName,
                                        SQLCHAR     FAR   *szSchemaName,
                                        SQLSMALLINT       cbSchemaName,
                                        SQLCHAR     FAR   *szTableName,
                                        SQLSMALLINT       cbTableName,
                                        SQLUSMALLINT      fUnique,
                                        SQLUSMALLINT      fAccuracy);

SQLRETURN SQL_API_FN  SQLTables        (SQLHSTMT          hstmt,
                                        SQLCHAR     FAR   *szCatalogName,
                                        SQLSMALLINT       cbCatalogName,
                                        SQLCHAR     FAR   *szSchemaName,
                                        SQLSMALLINT       cbSchemaName,
                                        SQLCHAR     FAR   *szTableName,
                                        SQLSMALLINT       cbTableName,
                                        SQLCHAR     FAR   *szTableType,
                                        SQLSMALLINT       cbTableType);


/*
 * DB2 specific CLI APIs
 */

SQLRETURN SQL_API_FN SQLBindFileToCol  (SQLHSTMT          hstmt,
                                        SQLUSMALLINT      icol,
                                        SQLCHAR     FAR   *FileName,
                                        SQLSMALLINT FAR   *FileNameLength,
                                        SQLUINTEGER FAR   *FileOptions,
                                        SQLSMALLINT       MaxFileNameLength,
                                        SQLINTEGER  FAR   *StringLength,
                                        SQLINTEGER  FAR   *IndicatorValue);

SQLRETURN SQL_API_FN SQLBindFileToParam(SQLHSTMT          hstmt,
                                        SQLUSMALLINT      ipar,
                                        SQLSMALLINT       fSqlType,
                                        SQLCHAR     FAR   *FileName,
                                        SQLSMALLINT FAR   *FileNameLength,
                                        SQLUINTEGER FAR   *FileOptions,
                                        SQLSMALLINT       MaxFileNameLength,
                                        SQLINTEGER  FAR   *IndicatorValue);

SQLRETURN SQL_API_FN SQLGetLength      (SQLHSTMT          hstmt,
                                        SQLSMALLINT       LocatorCType,
                                        SQLINTEGER        Locator,
                                        SQLINTEGER  FAR   *StringLength,
                                        SQLINTEGER  FAR   *IndicatorValue);

SQLRETURN SQL_API_FN SQLGetPosition    (SQLHSTMT          hstmt,
                                        SQLSMALLINT       LocatorCType,
                                        SQLINTEGER        SourceLocator,
                                        SQLINTEGER        SearchLocator,
                                        SQLCHAR     FAR   *SearchLiteral,
                                        SQLINTEGER        SearchLiteralLength,
                                        SQLUINTEGER       FromPosition,
                                        SQLUINTEGER FAR   *LocatedAt,
                                        SQLINTEGER  FAR   *IndicatorValue);


SQLRETURN SQL_API_FN SQLGetSQLCA       (SQLHENV           henv,
                                        SQLHDBC           hdbc,
                                        SQLHSTMT          hstmt,
                                        struct sqlca FAR  *pSqlca );

SQLRETURN SQL_API_FN SQLGetSubString   (SQLHSTMT          hstmt,
                                        SQLSMALLINT       LocatorCType,
                                        SQLINTEGER        SourceLocator,
                                        SQLUINTEGER       FromPosition,
                                        SQLUINTEGER       ForLength,
                                        SQLSMALLINT       TargetCType,
                                        SQLPOINTER        rgbValue,
                                        SQLINTEGER        cbValueMax,
                                        SQLINTEGER  FAR   *StringLength,
                                        SQLINTEGER  FAR   *IndicatorValue);

SQLRETURN SQL_API_FN SQLSetColAttributes (SQLHSTMT        hstmt,
                                        SQLUSMALLINT      icol,
                                        SQLCHAR     FAR   *pszColName,
                                        SQLSMALLINT       cbColName,
                                        SQLSMALLINT       fSQLType,
                                        SQLUINTEGER       cbColDef,
                                        SQLSMALLINT       ibScale,
                                        SQLSMALLINT       fNullable);

/*
 *  Set active connection API, for use in conjunction with embedded
 *  SQL programming only.
 */
SQLRETURN SQL_API_FN SQLSetConnection  (SQLHDBC           hdbc);

/*
 * APIs defined only by X/Open CLI
 */

SQLRETURN SQL_API_FN SQLGetEnvAttr     (SQLHENV           henv,
                                        SQLINTEGER        Attribute,
                                        SQLPOINTER        Value,
                                        SQLINTEGER        BufferLength,
                                        SQLINTEGER  FAR   *StringLength);

SQLRETURN SQL_API_FN SQLSetEnvAttr     (SQLHENV           henv,
                                        SQLINTEGER        Attribute,
                                        SQLPOINTER        Value,
                                        SQLINTEGER        StringLength);

SQLRETURN  SQL_API_FN SQLBindParam(     SQLHSTMT StatementHandle,
                                        SQLUSMALLINT ParameterNumber,
                                        SQLSMALLINT ValueType,
                                        SQLSMALLINT ParameterType,
                                        SQLUINTEGER LengthPrecision,
                                        SQLSMALLINT ParameterScale,
                                        SQLPOINTER ParameterValue,
                                        SQLINTEGER *StrLen_or_Ind);




#ifdef __cplusplus
}
#endif

#endif /* SQL_H_SQLCLI1 */
