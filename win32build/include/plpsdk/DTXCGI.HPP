//////
// DTXCGI.hpp - Header file for the DTXNetCgi class
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

#ifndef __DTXCGI__
#define __DTXCGI__

#include <iostream.h>
#include <fstream.h>
#include <dtxstr.hpp>
#include <dtxnet.hpp>


// CGI is mainly used for input from a Web Server to the calling
//  application.  Output is handled by the STDOUT except when it
//  is redirected or assigned to another stream.

#define DTXNETCGI_MAXENVLEN  129
#define DTXNETCGI_CONTTYPE	 "application/x-www-form-urlencoded"


class DTX_CLSEXPENTRY DTXNetCgiField
{
public:
	DTXString strName;
	DTXString strValue;
};




class DTX_CLSEXPENTRY DTXNetCgi
{
public:
	DTXNetCgi();
	DTXNetCgi( DTX_CPSZ pszWebfile, DTX_INT nMode = ios::out ); //ios::in for Input mode
	DTXNetCgi( istream& input, ostream& output );
	virtual ~DTXNetCgi();

	enum REQMETH { reqNONE, reqPOSTMETHOD, reqGETMETHOD };
	enum SQLSTATEMENT { sqlINSERT, sqlDELETE, sqlPROC, sqlSELECT, sqlUPDATE };

// Use cgiBind(...,DTX_INT,...); for checking DTX_BOOLEAN type fields.
// If checking CHECKBOX type fields the field/value pair will ONLY appear
//  if the field is checked.
// If the field in question is a MULTIPLE SELECT field then the field/value
//  pair will appear for item selected.  To locate the desired item you
//  must pass in the value to look for in the second parameter and set
//  the fMulti flag in the third parameter to TRUE.  Parameter two must be
//  NULL terminated.
	virtual DTX_RETCODE		cgiBind( DTX_CPSZ pszFormField, DTX_PSZ pHost, DTX_UINT unSize, DTX_BOOLEAN fMulti = FALSE, DTX_BOOLEAN fCRLF = FALSE );
	virtual DTX_RETCODE		cgiBind( DTX_CPSZ pszFormField, DTXString& strHost, DTX_BOOLEAN fMulti = FALSE, DTX_BOOLEAN fCRLF = FALSE );
	virtual DTX_RETCODE		cgiBind( DTX_CPSZ pszFormField, DTX_PSMALLINT pHost, DTX_SMALLINT sDef = 0 );
	virtual DTX_RETCODE		cgiBind( DTX_CPSZ pszFormField, DTX_PINT pHost, DTX_INT nDef = 0 );
	virtual DTX_RETCODE		cgiBind( DTX_CPSZ pszFormField, DTX_PREAL pHost, DTX_REAL rDef = 0 );
	virtual DTX_RETCODE		cgiBind( DTX_CPSZ pszFormField, DTX_PFLOAT pHost, DTX_FLOAT fDef = 0 );
	virtual DTX_RETCODE     cgiBind( DTX_SMALLINT sField, DTXString& strHost, DTX_BOOLEAN fCRLF = FALSE );
//	virtual DTX_RETCODE     cgiBuildSQL ( DTXString& strSQL, DTX_SMALLINT sStatementType = DTXNetCgi::sqlSELECT );
	virtual DTX_PSZ 		cgiUnescapeUrl( DTX_CPSZ pszUrl );
	//virtual DTXString&		cgiUnescapeUrl( DTXString& strUrl );
	virtual DTX_PSZ			cgiUnescapeUrl( DTXString& strUrl );

// All environment variables.
	inline  DTX_PSZ			getAuthenicateType();
	inline  DTX_INT			getContentLength();
	inline  DTX_PSZ			getContentType();
	inline  DTX_PSZ         getFieldName( DTX_SMALLINT sField ); 
	inline  DTXString       getFieldValue( DTX_SMALLINT sField, DTX_BOOLEAN fCRLF = FALSE );
	inline  DTX_PSZ			getGatewayInterface();
	inline  DTX_PSZ			getHttpAccept();
	inline  DTX_PSZ			getHttpReferer();
	inline  DTX_PSZ			getHttpUserAgent();
	inline	DTX_PSZ			getIFile();
	inline  istream&		getIStream();
	inline	DTX_INT			getNumOfFields();
	inline	DTX_PSZ			getOFile();
	inline  ostream&	    getOStream();
	inline  DTX_PSZ			getPathInfo();
	inline  DTX_PSZ			getPathTranslated();
	inline  DTX_PSZ			getQueryString();
	inline  DTX_PSZ			getRemoteAddress();
	inline  DTX_PSZ			getRemoteHost();
	inline  DTX_PSZ			getRemoteIdent();
	inline  DTX_PSZ			getRemoteUser();
	inline  DTX_SMALLINT	getRequestMethod();
	inline  DTX_PSZ			getScriptName();
	inline  DTX_PSZ			getServerName();
	inline  DTX_PSZ			getServerProtocol();
	inline  DTX_PSZ			getServerSoftware();

	inline  DTX_VOID        setFieldValue( DTX_SMALLINT sField, DTX_CPSZ pszValue );
	virtual istream&		setIFile( DTX_CPSZ pszPath = NULL );
	inline  istream&		setIStream( istream& input );
	virtual ostream&		setOFile( DTX_CPSZ pszPath = NULL );
	inline  ostream&		setOStream( ostream& output );

	DTXString				m_strData;

protected:
	DTX_VOID		setInit( DTX_SMALLINT sFlag = 0 );
	DTX_VOID		setInitBasic();
	DTX_VOID		setBuildFields();
	DTX_VOID		setWebfileInput( DTX_CPSZ pszWebfile );
	DTX_VOID	    setWebfileOutput( DTX_CPSZ pszWebfile );
	DTXNetCgiField  *pField;

private:
	DTXString		strIPath;
	DTXString		strOPath;
	DTXString       strTmp;
	ofstream		OFile;
	ifstream		IFile;
	ostream			*pOStream;
	istream         *pIStream;
	DTX_INT         nHex[256];
	DTX_CHAR		szSrvSoft[41];
	DTX_CHAR		szSrvName[41];
	DTX_CHAR		szGatIntf[DTXNETCGI_MAXENVLEN];
	DTX_CHAR		szSrvProt[41];
	DTX_CHAR		szReqMeth[41];
	DTX_CHAR		szPatInfo[81];
	DTX_CHAR		szPatTran[81];
	DTX_CHAR		szScrName[41];
	DTX_CHAR		szRemHost[41];
	DTX_CHAR		szRemAddr[81];
	DTX_CHAR		szAutType[41];
	DTX_CHAR		szRemUser[81];
	DTX_CHAR		szRemIden[81];
	DTX_CHAR		szConType[81];
	DTX_CHAR		szConLeng[DTXNETCGI_MAXENVLEN];
	DTX_CHAR		szHtpAccp[41];
	DTX_CHAR		szHtpUser[41];
	DTX_CHAR        szHtpRef[129];
	DTX_PCHAR       pQryStr;
	DTX_INT			nContLen;
	DTX_INT			nFields;
	DTX_SMALLINT	sReq;
};


#include <dtxcgi.inl>

#endif

