//////
// DTXNETC.inl - Inline header file for the DTXNetClient class
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

inline DTX_PSZ DTXNetClient::getUserName()
{
	return szUser;
}

inline DTX_PSZ DTXNetClient::getPassWord()
{
	return szPass;
}



inline DTX_VOID DTXNetClient::setUserName( DTX_CPSZ pszUser )
{
	if ( pszUser != NULL )
		strncpy(szUser,pszUser,sizeof(szUser));
}

inline DTX_VOID DTXNetClient::setPassWord( DTX_CPSZ pszPass )
{
	if ( pszPass != NULL )
		strncpy(szPass,pszPass,sizeof(szPass));
}


