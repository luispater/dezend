//////
// DTXBTR_DB.hpp - SQLBtrieve header file for the Btrieve DB class.            
//  (c) Copyright InnerX Communications, Inc. 1997-1998
//////

#ifndef __DTXBTRDB__
#define __DTXBTRDB__

#include <dtxbasdb.hpp>   // Base Database header.


#define SQLMAXCATLOGPATH	128
#define SQLMAXDATAPATH		256
#define SQLMAXNSQLFUN		10
         


class DTX_CLSEXPENTRY SQLBtrieve : public SQLObject
{
public:
	SQLBtrieve();
	SQLBtrieve( SQLObject *pObj );
	virtual ~SQLBtrieve();

	enum DBVENDORDATA { sqlBTRNONE , sqlCURSOR } ;

	virtual DTX_RETCODE sqlCommitWork();
	virtual DTX_RETCODE sqlCommitWork ( DTX_CPSZ pszName );
	virtual DTX_RETCODE sqlConnect();
	virtual DTX_RETCODE sqlConnect( DTX_SMALLINT sMode );
	virtual DTX_RETCODE sqlConnect( DTX_CPSZ pszUser , DTX_CPSZ pszPass , DTX_CPSZ pszDatabase , DTX_CPSZ pszServer , DTX_CPSZ pszApp , DTX_CPSZ pszHost );
	virtual DTX_RETCODE sqlDeleteCurrent( DTX_CPSZ pszTableName );
	virtual DTX_RETCODE sqlDescribe();
	virtual DTX_RETCODE sqlDisconnect();
	virtual DTX_RETCODE sqlExec();
	virtual DTX_RETCODE sqlExec( DTX_CPSZ pszSqlCmd );
	virtual DTX_RETCODE sqlExec( DTX_CPCHAR pSqlCmd , DTX_INT nSize );
	virtual DTX_RETCODE sqlFetch();
	virtual DTX_RETCODE sqlRollBackWork();
	virtual DTX_RETCODE sqlRollBackWork( DTX_CPSZ pszName );
	virtual DTX_RETCODE sqlUpdateCurrent( DTX_CPSZ pszTableName , DTX_CPSZ pszSetCmd );

	inline  DTX_PSZ     getServer();
	inline  DTX_PSZ     getDatabase();

	inline  DTX_VOID	setServer( DTX_CPSZ pszServ );
	inline  DTX_VOID	setDatabase( DTX_CPSZ pszDb );

	inline  DTX_VOID	setDbError( DTX_INT nCode );
	inline  DTX_VOID	setBlankChar( DTX_CPSZ pszChar );
	virtual DTX_RETCODE setOwnerNames( DTX_CPCHAR pNames );

	virtual DTX_PCHAR   getDbVendorData( DTX_SMALLINT sData );
	virtual DTX_BOOLEAN getIsConnected();
	virtual DTX_INT     getDBSQLCODE();
	virtual DTX_INT     getDbError();
	inline  DTX_PSZ     getBlankChar();

	virtual DTX_PSZ      getSQLDAColData         ( DTX_INT nColNum ) ;
	virtual DTX_SMALLINT getSQLDAColDataSmallInt ( DTX_INT nColNum ) ;
	virtual DTX_INT      getSQLDAColDataInt      ( DTX_INT nColNum ) ;
	virtual double       getSQLDAColDataDouble   ( DTX_INT nColNum ) ;
	virtual float        getSQLDAColDataFloat    ( DTX_INT nColNum ) ;

protected:
	DTX_SMALLINT getBtrNullInd ( DTX_INT nCount , DTX_PCHAR pSource ) ;

private:
	DTX_CHAR     szCatLogPath [ SQLMAXCATLOGPATH ] ;
	DTX_CHAR     szDataPath   [ SQLMAXDATAPATH   ] ;
	DTX_PCHAR    pBuff ;
	DTX_BOOLEAN  fPos ;
	DTX_INT      nErrorCode ;
	DTX_SMALLINT sMaxSize ;
	DTX_SMALLINT sCursor ;
	DTX_CHAR     szBlank[ 2 ] ;
};

#include <dtxbtrdb.inl>

#endif

