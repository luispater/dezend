//////
// DTXSTR.inl - Inline methods for the DTXString class
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////


inline DTX_BOOLEAN operator==( DTX_CPSZ   pszString1,
					           DTXString& strString2 )
{
	if ( pszString1 != NULL )
		{
		if ( !strcmp(pszString1,strString2.getBuffer()) )
			return TRUE;
		}
	return FALSE;
}


inline DTX_BOOLEAN operator==( DTX_PSZ    pszString1,
					           DTXString& strString2 )
{
	if ( pszString1 != NULL )
		{
		if ( !strcmp(pszString1,strString2.getBuffer()) )
			return TRUE;
		}
	return FALSE;
}


inline DTX_BOOLEAN DTXString::operator==( DTXString& strString )
					    
{
	if ( !strcmp(pBuffer,(DTX_PCHAR)strString.getBuffer()) )
		return TRUE;
	return FALSE;
}

inline DTX_BOOLEAN DTXString::operator==( DTX_CPSZ pszString )
{
	if ( pszString != NULL )
		{
		if ( !strcmp(getBuffer(),pszString) )
			return TRUE;
		}
	return FALSE;
}


inline DTX_BOOLEAN DTXString::operator==( DTX_PSZ pszString )
{
	if ( pszString != NULL )
		{
		if ( !strcmp(getBuffer(),pszString) )
			return TRUE;
		}
	return FALSE;
}


inline DTX_BOOLEAN operator!=( DTX_CPSZ   pszString1,
					           DTXString& strString2 )
{
	if ( pszString1 != NULL )
		{
		if ( strcmp(pszString1,strString2.getBuffer()) )
			return TRUE;
		}
	return FALSE;
}



inline DTX_BOOLEAN operator!=( DTX_PSZ    pszString1,
					           DTXString& strString2 )
{
	if ( pszString1 != NULL )
		{
		if ( strcmp(pszString1,strString2.getBuffer()) )
			return TRUE;
		}
	return FALSE;
}


inline DTX_BOOLEAN DTXString::operator!=( DTXString& strString )
					    
{
	if ( strcmp(pBuffer,(DTX_PCHAR)strString.getBuffer()) )
		return TRUE;
	return FALSE;
}

inline DTX_BOOLEAN DTXString::operator!=( DTX_CPSZ pszString )
{
	if ( pszString != NULL )
		{
		if ( strcmp(getBuffer(),pszString) )
			return TRUE;
		}
	return FALSE;
}


inline DTX_BOOLEAN DTXString::operator!=( DTX_PSZ pszString )
{
	if ( pszString != NULL )
		{
		if ( strcmp(getBuffer(),pszString) )
			return TRUE;
		}
	return FALSE;
}


inline istream& operator>>( istream& input,
					        DTXString& strValue )
{
	DTX_CHAR szTmp[1025];

	strValue = "";

	do {
		memset(szTmp,0,sizeof(szTmp));
		input.read(szTmp,sizeof(szTmp)-1);
		if ( input.gcount() <= 0 )
			 break;
		strValue += szTmp;
	} while(1);

	return input;
}



inline ostream& operator<<( ostream& output,
					        DTXString& strValue )
{
	output << strValue.getBuffer();
	return output;
}


inline DTXString operator+(DTX_CPSZ   pszString,
		                   DTXString& strString)
{
	if ( pszString != NULL )
		{
		DTXString sTmp1 = pszString;
		DTXString sTmp2 = sTmp1 + strString;
		return sTmp2;
		}
	else
		return strString;
}



inline DTX_PSZ DTXString::getBuffer()
{
	return pBuffer;
}


inline DTX_VOID DTXString::strFilterQuote()
{
	strReplace("'","\''");
}

//DO NOT call strFilterQuote before calling this method
inline DTX_VOID DTXString::strQuote()
{
	strReplace("'","\''");
	strInsert("'");
	strRightTrim();
	*this += "'";
}

inline DTX_PSZ DTXString::strZeroFill( DTX_SMALLINT sWidth )
{
	DTX_CHAR szBuff[128];
	DTX_CHAR szFmt[31];

	memset(szBuff,0,sizeof(szBuff));
	memset(szFmt,0,sizeof(szFmt));
	strcpy(szFmt,"%0");
	sprintf(szFmt+strlen(szFmt),"%d",sWidth);
	strcat(szFmt,"s");
	sprintf(szBuff,szFmt,pBuffer);
	*this = szBuff;
	return pBuffer;
}


inline DTX_PSZ DTXString::strZeroRemove( DTX_SMALLINT sSide )
{
	DTX_CHAR     szBuff[128];
	DTX_BOOLEAN  fOut = TRUE;
	DTX_SMALLINT sCount;
	DTX_SMALLINT sEnd;

	memset(szBuff,0,sizeof(szBuff));

	if ( sSide )
		{
		sEnd = 0;
		sCount = DTXMIN(getStringLen(),sizeof(szBuff)-1);
		}
	else
		{
		sEnd = DTXMIN(getStringLen(),sizeof(szBuff));
		sCount = 0;
		}

	//All spaces should be removed before calling this method.

	for ( ; sCount < sEnd; ((!sSide) ? sCount++ : sCount--) )
		{
		if ( pBuffer[sCount] == '0' &&
			 fOut )
			szBuff[sCount] = ' ';
		else
			{
			szBuff[sCount] = pBuffer[sCount];
			fOut = FALSE;
			}
		};

	*this = szBuff;
	this->strTrim();
	return pBuffer;
}

inline DTX_PCHAR DTXString::getBuffer( DTX_PCHAR pBuff,
				DTX_UINT  nSize)
{
	if ( pBuff != NULL )
		memmove ( pBuff , pBuffer, DTXMIN(nSize,nLen));
	return pBuff;
}

inline DTX_UINT DTXString::getBufferLen()
{
	return nBuffLen;
}

inline DTX_UINT DTXString::getStringLen()
{
	if ( pBuffer[0] == '\0' )
			return 0;
	return nLen;
}


//DTXStringToken

inline DTX_BOOLEAN DTXStringToken::strIsNull()
{
	if ( m_pString == NULL ||
	     nOffset >= m_pString->getStringLen() )
	     return TRUE;
	return FALSE;
}


//DTXFormatDate

inline DTX_VOID DTXFormatDate::setDateObject( DTXDate& datValue )
{
	Date = datValue;
}




//DTXFormatTime

inline DTX_PSZ DTXFormatTime::getAM()
{
	return szAM;
}

inline DTX_PSZ DTXFormatTime::getPM()
{
	return szPM;
}


inline DTX_VOID DTXFormatTime::setTimeObject( DTXTime& timValue )
{
	Time = timValue;
}

inline DTX_VOID DTXFormatTime::setAM( DTX_CPSZ pszAM )
{
	strncpy(szAM,pszAM,sizeof(szAM)-1);
}

inline DTX_VOID DTXFormatTime::setPM( DTX_CPSZ pszPM )
{
	strncpy(szPM,pszPM,sizeof(szPM)-1);
}



