//////
// DTXCGI.inl - Inline header file for the DTXNetCgi class
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////


inline DTX_PSZ DTXNetCgi::getAuthenicateType()
{
	return szAutType;
}

inline DTX_INT DTXNetCgi::getContentLength()
{
	return nContLen;
}


inline DTX_PSZ DTXNetCgi::getContentType()
{
	return szConType;
}


inline DTX_PSZ DTXNetCgi::getFieldName( DTX_SMALLINT sField )
{
	return pField[sField-1].strName.getBuffer();
}


inline DTXString DTXNetCgi::getFieldValue( DTX_SMALLINT sField,
										   DTX_BOOLEAN  fCRLF )
{
	DTXString strTmp;

	strTmp = pField[sField-1].strValue;
	if ( fCRLF )
		{
			strTmp.strRemove("\n");
			strTmp.strRemove("\r");
		}

	return strTmp;
}


inline DTX_PSZ DTXNetCgi::getGatewayInterface()
{
	return szGatIntf;
}


inline DTX_PSZ DTXNetCgi::getHttpAccept()
{
	return szHtpAccp;
}

inline DTX_PSZ DTXNetCgi::getHttpReferer()
{
	return szHtpRef;
}

inline DTX_PSZ DTXNetCgi::getHttpUserAgent()
{
	return szHtpUser;
}

inline DTX_INT DTXNetCgi::getNumOfFields()
{
	return nFields;
}


inline DTX_PSZ DTXNetCgi::getPathInfo()
{
	return szPatInfo;
}


inline DTX_PSZ DTXNetCgi::getPathTranslated()
{
	return szPatTran;
}


inline DTX_PSZ DTXNetCgi::getQueryString()
{
	return pQryStr;
}


inline DTX_PSZ DTXNetCgi::getRemoteAddress()
{
	return szRemAddr;
}


inline DTX_PSZ DTXNetCgi::getRemoteHost()
{
	return szRemHost;
}


inline DTX_PSZ DTXNetCgi::getRemoteIdent()
{
	return szRemIden;
}


inline DTX_PSZ DTXNetCgi::getRemoteUser()
{
	return szRemUser;
}


inline DTX_SMALLINT	DTXNetCgi::getRequestMethod()
{
	return sReq;
}


inline DTX_PSZ DTXNetCgi::getScriptName()
{
	return szScrName;
}


inline DTX_PSZ DTXNetCgi::getServerName()
{
	return szSrvName;
}


inline DTX_PSZ DTXNetCgi::getServerProtocol()
{
	return szSrvProt;
}


inline DTX_PSZ DTXNetCgi::getServerSoftware()
{
	return szSrvSoft;
}


inline DTX_PSZ DTXNetCgi::getIFile()
{
	return strIPath.getBuffer();
}


inline DTX_PSZ DTXNetCgi::getOFile()
{
	return strOPath.getBuffer();
}


inline ostream& DTXNetCgi::getOStream()
{
	return *pOStream;
}

inline istream& DTXNetCgi::getIStream()
{
	return *pIStream;
}


inline DTX_VOID DTXNetCgi::setFieldValue( DTX_SMALLINT sField,
										  DTX_CPSZ     pszValue )
{
	pField[sField-1].strValue = pszValue;
}


inline istream& DTXNetCgi::setIStream( istream& input )
{
	pIStream = &input;
	return *pIStream;
}

inline ostream& DTXNetCgi::setOStream( ostream& output )
{
	pOStream = &output;
	return *pOStream;
}
