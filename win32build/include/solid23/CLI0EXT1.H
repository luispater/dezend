/****************************************************************\
**  filename     * cli0ext1.h
**		 *
**  description  * ODBC level 1 and 2 extension functions 
**		 * prototypes
**		 *
**  copyright 	(C) Solid Information Technology Ltd 1993
\****************************************************************/

/* 
	ODBC 2.0 Level 1 API functions
	==============================

Connecing to a Data Source
	SQLDriverConnect Connects to a specific driver by 
			connection string or requests that the 
			Driver Manager and driver display 
			connection dialog boxes for the user.
	    NOTE! 	This function is implemented only in 
			Windows environments.

Obtaining Information about a Driver and Data Source
	SQLGetInfo	Returns information about a specific 
			driver and data source.
	SQLGetFunctions	Returns supported driver functions.
	SQLGetTypeInfo	Returns information about supported data 
			types.

Setting and Retrieving Driver Options
	SQLSetConnectOption Sets a connection option.
	SQLGetConnectOption Returns the value of a connection 
			    option.
	SQLSetStmtOption Sets a statement option.
	SQLGetStmtOption Returns the value of a statement option.

Preparing SQL Requests
	SQLBindParameter Assigns storage for a parameter in an SQL
			 statement.

Submitting Requests
	SQLParamData	Used in conjunction with SQLPutData to 
			supply parameter at execution time.
	SQLPutData	Send part or all of a data value for a 
			parameter.

Retrieving Results and Information about Results
	SQLGetData	Returns part or all of one column of one 
			row of a result set.

Obtaining information about the data source's system tables 
(catalog functions)
	SQLColumns	Returns a list of column names in 
			specified tables.
	SQLSpecialColumns Returns information about the optimal 
			set of columns that uniquely identifies
			a row in a specified table, or the columns 
			that are automatically updated when any
			value in the row is updated by a 
			transaction.
	SQLStatistics	Returns statistics about a single table
			and the list of indexes associated with
			the table.
	SQLTables	Returns the list of table names stored in 
			a specific data source.
*/

/* NOTE! 

   None of the following ODBC 2.0 Level 2 API functions has 
   been implemented in the SOLID Server Client Library or ODBC 
   Driver.

   The following functions, however, can be used in Windows 
   environments if Microsoft ODBC DLLs are used:
	SQLDataSources	Implemented in Driver Manager
	SQLDrivers	Implemented in Driver Manager
	SQLExtendedFetch Implemented in ODBC Cursor Library
	SQLMoreResults	Implemented in ODBC Cursor Library
	SQLSetPos	Implemented in ODBC Cursor Library
	SQLSetScrollOptions Implemented in ODBC Cursor Library
*/

/* NOTE! 

   None of the ODBC 2.0 Level 2 API functions are implemented 
   in SOLID Server versions prior to version 2.2
*/

/* NOTE! 

   The following ODBC 2.0 Level 2 API functions are implemented 
   in SOLID Server version 2.2

Submitting Requests
	SQLDescribeParam Returns the description for a specific 
			parameter in a statement.
	SQLNumParams	Returns the number of parameters in a 
	  		statement.

Obtaining information about the data source's system tables 
(catalog functions)
	SQLPrimaryKeys	Returns the list of column name(s) that 
			comprise the primary key for a table.
*/

/* 
	ODBC 2.0 Level 2 API functions
	==============================

Connecing to a Data Source
	SQLBrowseConnect Returns successive levels of connection 
			attributes and valid attribute values. 
			When a value has been specified for each 
			connection attribute, connects to the data
			source.

Obtaining Information about a Driver and Data Source
	SQLDataSources	Returns the list of available data sources
	SQLDrivers	Returns the list of installed drivers and 
			their attributes

Preparing SQL Requests
	SQLParamOptions	Specifies the use of multiple values for 
			parameters.
	SQLSetScrollOptions 
			Sets options that control cursor behaviour

Submitting Requests
	SQLNativeSql	Returns the text of an SQL statement as 
			translated by the driver. 
	SQLDescribeParam Returns the description for a specific 
			parameter in a statement.
	SQLNumParams	Returns the number of parameters in a 
			statement.

Retrieving Results and Information about Results
	SQLExtendedFetch Returns multiple result rows.
	SQLSetPos	Positions a cursor within a fecthed block 
			of data.
	SQLMoreResults	Determines whether there are more result 
			sets available and, if so, initializes
		        processing for the next result set.

Obtaining information about the data source's system tables 
(catalog functions)
	SQLColumnPrivileges Returns a list of columns and 
			associated privileges for one or more 
			tables.
	SQLForeignKeys	Returns a list of column names that 
			comprise foreign keys, if they exist for a
			specified table.
	SQLPrimaryKeys	Returns the list of column name(s) that 
			comprise the primary key for a table.
	SQLProcedureColumns Returns the list of input and output 
			parameters, as well as the columns that 
			make up the result set for the specified 
			procedures.
	SQLProcedures	Returns the list of procedure names stored
			in a specified data source.
	SQLTablePrivileges Returns a list of tables and the 
			privileges associated with each table.
*/

#ifndef CLI0EXT1_H
#define CLI0EXT1_H

#include "cli0env.h"
#include "cli0defs.h"
              
/* Level 1 Prototypes */
RETCODE SS_EXPORT SQLColumns(
    HSTMT      hstmt,
    UCHAR      *szTableQualifier,
    SWORD      cbTableQualifier,
    UCHAR      *szTableOwner,
    SWORD      cbTableOwner,
    UCHAR      *szTableName,
    SWORD      cbTableName,
    UCHAR      *szColumnName,
    SWORD      cbColumnName);

#if defined(SS_WIN) || defined(SS_NT)

RETCODE SS_EXPORT SQLDriverConnect(
    HDBC       hdbc,
    HWND       hwnd,
    UCHAR      *szConnStrIn,
    SWORD      cbConnStrIn,
    UCHAR      *szConnStrOut,
    SWORD      cbConnStrOutMax,
    SWORD      *pcbConnStrOut,
    UWORD      fDriverCompletion);
#endif

RETCODE SS_EXPORT SQLGetConnectOption(
    HDBC       hdbc,
    UWORD      fOption,
    PTR        pvParam);

RETCODE SS_EXPORT SQLGetData(
    HSTMT      hstmt,
    UWORD      icol,
    SWORD      fCType,
    PTR        rgbValue,
    SDWORD     cbValueMax,
    SDWORD     *pcbValue);


RETCODE SS_EXPORT SQLGetFunctions(
    HDBC       hdbc,
    UWORD      fFunction,
    UWORD      *pfExists);


RETCODE SS_EXPORT SQLGetInfo(
    HDBC       hdbc,
    UWORD      fInfoType,
    PTR        rgbInfoValue,
    SWORD      cbInfoValueMax,
    SWORD      *pcbInfoValue);

RETCODE SS_EXPORT SQLGetStmtOption(
    HSTMT      hstmt,
    UWORD      fOption,
    PTR        pvParam);

RETCODE SS_EXPORT SQLGetTypeInfo(
    HSTMT      hstmt,
    SWORD      fSqlType);

RETCODE SS_EXPORT SQLParamData(
    HSTMT      hstmt,
    PTR        *prgbValue);

RETCODE SS_EXPORT SQLPutData(
    HSTMT      hstmt,
    PTR        rgbValue,
    SDWORD     cbValue);

RETCODE SS_EXPORT SQLSetConnectOption(
    HDBC       hdbc,
    UWORD      fOption,
    UDWORD     vParam);

RETCODE SS_EXPORT SQLSetStmtOption(
    HSTMT      hstmt,
    UWORD      fOption,
    UDWORD     vParam);

RETCODE SS_EXPORT SQLSpecialColumns(
    HSTMT      hstmt,
    UWORD      fColType,
    UCHAR      *szTableQualifier,
    SWORD      cbTableQualifier,
    UCHAR      *szTableOwner,
    SWORD      cbTableOwner,
    UCHAR      *szTableName,
    SWORD      cbTableName,
    UWORD      fScope,
    UWORD      fNullable);

RETCODE SS_EXPORT SQLStatistics(
    HSTMT      hstmt,
    UCHAR      *szTableQualifier,
    SWORD      cbTableQualifier,
    UCHAR      *szTableOwner,
    SWORD      cbTableOwner,
    UCHAR      *szTableName,
    SWORD      cbTableName,
    UWORD      fUnique,
    UWORD      fAccuracy);

RETCODE SS_EXPORT SQLTables(
    HSTMT      hstmt,
    UCHAR      *szTableQualifier,
    SWORD      cbTableQualifier,
    UCHAR      *szTableOwner,
    SWORD      cbTableOwner,
    UCHAR      *szTableName,
    SWORD      cbTableName,
    UCHAR      *szTableType,
    SWORD      cbTableType);


/* Level 2 Functions                             */

/* Level 2 Prototypes */
RETCODE SS_EXPORT SQLBrowseConnect(
    HDBC       hdbc,
    UCHAR      *szConnStrIn,
    SWORD      cbConnStrIn,
    UCHAR      *szConnStrOut,
    SWORD      cbConnStrOutMax,
    SWORD      *pcbConnStrOut);

RETCODE SS_EXPORT SQLColumnPrivileges(
    HSTMT      hstmt,
    UCHAR      *szTableQualifier,
    SWORD      cbTableQualifier,
    UCHAR      *szTableOwner,
    SWORD      cbTableOwner,
    UCHAR      *szTableName,
    SWORD      cbTableName,
    UCHAR      *szColumnName,
    SWORD      cbColumnName);

RETCODE SS_EXPORT SQLDataSources(
    HENV       henv,
    UWORD      fDirection,
    UCHAR      *szDSN,
    SWORD      cbDSNMax,
    SWORD      *pcbDSN,
    UCHAR      *szDescription,
    SWORD      cbDescriptionMax,
    SWORD      *pcbDescription);

RETCODE SS_EXPORT SQLDescribeParam(
    HSTMT      hstmt,
    UWORD      ipar,
    SWORD      *pfSqlType,
    UDWORD     *pcbColDef,
    SWORD      *pibScale,
    SWORD      *pfNullable);
               
RETCODE SS_EXPORT SQLExtendedFetch(
    HSTMT      hstmt,
    UWORD      fFetchType,
    SDWORD     irow,
    UDWORD     *pcrow,
    UWORD      *rgfRowStatus);

RETCODE SS_EXPORT SQLForeignKeys(
    HSTMT      hstmt,
    UCHAR      *szPkTableQualifier,
    SWORD      cbPkTableQualifier,
    UCHAR      *szPkTableOwner,
    SWORD      cbPkTableOwner,
    UCHAR      *szPkTableName,
    SWORD      cbPkTableName,
    UCHAR      *szFkTableQualifier,
    SWORD      cbFkTableQualifier,
    UCHAR      *szFkTableOwner,
    SWORD      cbFkTableOwner,
    UCHAR      *szFkTableName,
    SWORD      cbFkTableName);

RETCODE SS_EXPORT SQLMoreResults(
    HSTMT      hstmt);

RETCODE SS_EXPORT SQLNativeSql(
    HDBC       hdbc,
    UCHAR      *szSqlStrIn,
    SDWORD     cbSqlStrIn,
    UCHAR      *szSqlStr,
    SDWORD     cbSqlStrMax,
    SDWORD     *pcbSqlStr);

RETCODE SS_EXPORT SQLNumParams(
    HSTMT      hstmt,
    SWORD      *pcpar);

RETCODE SS_EXPORT SQLParamOptions(
    HSTMT      hstmt,
    UDWORD     crow,
    UDWORD     *pirow);

RETCODE SS_EXPORT SQLPrimaryKeys(
    HSTMT      hstmt,
    UCHAR      *szTableQualifier,
    SWORD      cbTableQualifier,
    UCHAR      *szTableOwner,
    SWORD      cbTableOwner,
    UCHAR      *szTableName,
    SWORD      cbTableName);

RETCODE SS_EXPORT SQLForeignKeys(
    HSTMT      hstmt,
    UCHAR      *szPkTableQualifier,
    SWORD      cbPkTableQualifier,
    UCHAR      *szPkTableOwner,
    SWORD      cbPkTableOwner,
    UCHAR      *szPkTableName,
    SWORD      cbPkTableName,
    UCHAR      *szFkTableQualifier,
    SWORD      cbFkTableQualifier,
    UCHAR      *szFkTableOwner,
    SWORD      cbFkTableOwner,
    UCHAR      *szFkTableName,
    SWORD      cbFkTableName);

RETCODE SS_EXPORT SQLProcedureColumns(
    HSTMT      hstmt,
    UCHAR      *szProcQualifier,
    SWORD      cbProcQualifier,
    UCHAR      *szProcOwner,
    SWORD      cbProcOwner,
    UCHAR      *szProcName,
    SWORD      cbProcName,
    UCHAR      *szColumnName,
    SWORD      cbColumnName);

RETCODE SS_EXPORT SQLProcedures(
    HSTMT      hstmt,
    UCHAR      *szProcQualifier,
    SWORD      cbProcQualifier,
    UCHAR      *szProcOwner,
    SWORD      cbProcOwner,
    UCHAR      *szProcName,
    SWORD      cbProcName);

RETCODE SS_EXPORT SQLSetPos(
    HSTMT      hstmt,
    UWORD      irow,
    UWORD      fRefresh,
    UWORD      fLock);

RETCODE SS_EXPORT SQLSetScrollOptions(
    HSTMT      hstmt,
    UWORD      fConcurrency,
    SDWORD     crowKeyset,
    UWORD      crowRowset);

RETCODE SS_EXPORT SQLTablePrivileges(
    HSTMT      hstmt,
    UCHAR      *szTableQualifier,
    SWORD      cbTableQualifier,
    UCHAR      *szTableOwner,
    SWORD      cbTableOwner,
    UCHAR      *szTableName,
    SWORD      cbTableName);

RETCODE SS_EXPORT SQLBindParameter(
        HSTMT   hstmt,
        UWORD   ipar,
        SWORD   fParamType,
        SWORD   fCType,
        SWORD   fSqlType,
        UDWORD  cbColDef,
        SWORD   ibScale,
        PTR     rgbValue,
        SDWORD  cbValueMax,
        SDWORD* pcbValue);

RETCODE SS_EXPORT SQLUserId(
    HDBC       hdbc,
    UWORD      *pUserId);

void* SS_EXPORT SQLSystemConnect(
    HDBC      hdbc);

#endif /* CLI0EXT1_H */
