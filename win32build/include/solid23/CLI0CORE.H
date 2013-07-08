/****************************************************************\
**  file         * cli0core.h
**		 *
**  description  * ODBC 2.0 Core API and SAG/CLI functions
**		 *
**  copyright 	(C) Solid Information Technology Ltd 1993
\****************************************************************/

/* ODBC 2.0 Core API functions supported

Connecting to a Data Source
	SQLAllocEnv	 Obtains an environment handle. One 
			 environment handle is used for one or
			 more connections.
	SQLAllocConnect	 Obtains a connection handle.
	SQLConnect	 Connects to a specific driver by data 
			 source name, user ID, and password.

Preparing SQL Requests
	SQLAllocStmt	 Allocates a statement handle.
	SQLPrepare	 Prepares an SQL statement for later 
			 execution.
	SQLGetCursorName Returns cursor name associated with a 
			 statement handle.
	SQLSetCursorName Specifies a cursor name.

Submitting Requests
	SQLExecute	 Executes a prepared statement.
	SQLExecDirect	 Executes a statement.

Retrieving Results and Information about Results
	SQLRowCount	 Returns the number of rows affected by 
			 an insert, update or delete request.
	SQLNumResultCols Returns the number of columns in the 
			 result set.
	SQLDescribeCol	 Describes a column in the result set.
	SQLColAttributes Describes attributes of a column in the 
			 result set.
	SQLBindCol	 Assigns storage for a result column and 
			 specifies the data type.
	SQLFetch	 Returns a result row.
	SQLError	 Returns additional error or status 
			 information.

Terminating a Statement
	SQLFreeStmt	 Ends statement processing and closes the 
			 associated cursor, discards pending 
			 results, and, optionally frees all 
			 resources associated with the statement
			 handle.
	SQLCancel	 Cancels an SQL statement.
	SQLTransact	 Commits or rolls back a transaction.

Terminating a Connection
	SQLDisconnect	 Closes the connection.
	SQLFreeConnect	 Releases the connection handle.
	SQLFreeEnv	 Releases the environment handle.
*/ 

/* ODBC 1.0 functions that have been replaced by ODBC 2.0 
   functions SQLSetParam has been replaced by SQLBindParameter 
   (ODBC 2.0 Level 1 function)
*/

/* SAG/CLI functions
Connecting to the HOST DBMS
	SQLAllocEnv	 Allocate an environemnt handle.
	SQLAllocConnect	 Allocate a connection handle.
	SQLConnect	 Open a connection to an SQL-server.
	SQLDisconnect	 Close the connection to an SQL-Server.
	SQLFreeConnect	 Free a connection handle.
	SQLFreeEnv	 Free environement handle.

Sending/Executing SQL Statements
	SQLAllocStmt	 Allocate a statement handle.
	SQLPrepare	 Prepare a statement for later execution.
	SQLBindParam	 Define storage for a parameter in an SQL 
			 statement.
	SQLSetParamValue Set a parameter value.
	SQLSetCursorName Set the name of a cursor.
	SQLGetCursorName Get the name of a cursor.
	SQLExecute	 Execute a prepared SQL statement.
	SQLExecDirect	 Execute an SQL statement directly.

Retrieving results
	SQLNumResultCols Get the number of columns in a result set.
	SQLDescribeCol	 Describe a column of a result set.
	SQLColAttributes Describe attributes of a column in a 
			 result set.
	SQLBindCol	 Define storage for a column in a result 
			 set.
	SQLFetch	 Get the next row of a result set.
	SQLGetCol	 Retrieve data from a row of the result 
			 set one column at a time.
	SQLRowCount	 Get the number of rows affected by an SQL
			 statement.
	SQLFreeStmt	 Free a statement handle.

Transaction Control
	SQLTransact	 Commit or rollback a transaction.

Error Handling nad Miscellaneous
	SQLCancel	 Attempt to cancel execution of an SQL 
			 statement.
	SQLError	 Free a statement handle.
*/

/* SOLID Extensions
	SQLFetchPrev	 Get the previous row of a result set.
	SQLGetAnyCol	 Retrieve data from a specified column of 
			 a row of the result set.
*/

#ifndef CLI0CORE_H
#define CLI0CORE_H

#include "cli0env.h"
#include "cli0defs.h"

RETCODE SS_EXPORT SQLAllocEnv( HENV* phenv );
RETCODE SS_EXPORT SQLAllocConnect( HENV henv, HDBC* phdbc );
RETCODE SS_EXPORT SQLConnect( HDBC hdbc, UCHAR* szDSN,SWORD cbDSN,
            UCHAR* szUID, SWORD cbUID, UCHAR* szAuthStr,
            SWORD cbAuthStr );

RETCODE SS_EXPORT SQLAllocStmt( HDBC hdbc, HSTMT* phstmt );
RETCODE SS_EXPORT SQLPrepare( HSTMT hstmt, UCHAR* szSqlStr, 
	    SDWORD cbSqlStr );
RETCODE SS_EXPORT SQLBindParam( HSTMT hstmt, UWORD ipar, 
	    SWORD fCType, SWORD fSqlType, UDWORD cbColDef, 
	    SWORD ibScale, PTR rgbValue, SDWORD* pcbValue );
RETCODE SS_EXPORT SQLSetParam( HSTMT hstmt, UWORD ipar, 
	    SWORD fCType, SWORD fSqlType, UDWORD cbColDef, 
	    SWORD ibScale, PTR rgbValue, SDWORD* pcbValue );
RETCODE SS_EXPORT SQLSetParamValue( HSTMT hstmt, UWORD ipar, 
	    SWORD fCType, SWORD fSqlType, UDWORD cbColDef, 
	    SWORD ibScale, PTR rgbValue, SDWORD* pcbValue );
RETCODE SS_EXPORT SQLGetCursorName( HSTMT hstmt, UCHAR* szCursor,
            SWORD cbCursorMax, SWORD* pcbCursor );
RETCODE SS_EXPORT SQLSetCursorName( HSTMT hstmt, UCHAR* szCursor,
            SWORD cbCursor );

RETCODE SS_EXPORT SQLExecute( HSTMT hstmt );
RETCODE SS_EXPORT SQLExecDirect( HSTMT hstmt, UCHAR* szSqlStr, 
	    SDWORD cbSqlStr );

RETCODE SS_EXPORT SQLRowCount( HSTMT hstmt, SDWORD* pcrow );
RETCODE SS_EXPORT SQLNumResultCols( HSTMT hstmt, SWORD* pccol );
RETCODE SS_EXPORT SQLDescribeCol( HSTMT hstmt, UWORD icol, 
	    UCHAR* szColName, SWORD cbColNameMax, 
	    SWORD* pcbColName, SWORD* pfSqlType, 
	    UDWORD* pcbColDef, SWORD* pibScale, 
	    SWORD* pfNullable );
RETCODE SS_EXPORT SQLColAttributes( HSTMT hstmt, UWORD icol, 
	    UWORD fDescType, PTR rgbDesc, SWORD cbDescMax, 
	    SWORD* pcbDesc, SDWORD* pfDesc );
RETCODE SS_EXPORT SQLBindCol(HSTMT hstmt, UWORD icol, 
	    SWORD fCType, PTR rgbValue, SDWORD cbValueMax, 
	    SDWORD* pcbValue );
RETCODE SS_EXPORT SQLFetch( HSTMT hstmt );
RETCODE SS_EXPORT SQLGetCol( HSTMT hstmt, UWORD icol, 
	    SWORD fCType, PTR rgbValue, SDWORD cbValueMax, 
	    SDWORD* pcbValue );
RETCODE SS_EXPORT SQLError( HENV henv, HDBC hdbc, HSTMT hstmt,
            UCHAR* szSqlState, SDWORD* pfNativeError,
            UCHAR* szErrorMsg, SWORD cbErrorMsgMax,
            SWORD* pcbErrorMsg );

RETCODE SS_EXPORT SQLFreeStmt( HSTMT hstmt, UWORD fOption );
RETCODE SS_EXPORT SQLCancel( HSTMT hstmt );
RETCODE SS_EXPORT SQLTransact( HENV henv, HDBC hdbc, UWORD fType );

RETCODE SS_EXPORT SQLDisconnect( HDBC hdbc );
RETCODE SS_EXPORT SQLFreeConnect( HDBC hdbc );
RETCODE SS_EXPORT SQLFreeEnv( HENV henv );

/* The following functions are SOLID extensions. */
RETCODE SS_EXPORT SQLFetchPrev( HSTMT hstmt );
RETCODE SS_EXPORT SQLGetAnyCol( HSTMT hstmt, UWORD icol, 
	    SWORD fCType, PTR rgbValue, SDWORD cbValueMax, 
	    SDWORD* pcbValue );
                                
#endif /* CLI0CORE_H */
