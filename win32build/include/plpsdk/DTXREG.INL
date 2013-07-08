//////
// DTXREG.inl - Inline header for DTXRegistry class
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

inline DTX_BOOLEAN DTXRegistry::getIsOpen()
{
	if ( m_hKey == NULL )
		return FALSE;
	else
		return TRUE;
}

inline DTX_BOOLEAN DTXRegistry::setSubKey( DTX_CPSZ pszSubKey, DTX_SMALLINT sKeyValue )
{
	return setKey( m_hBaseKey, pszSubKey, sKeyValue ); 
}

