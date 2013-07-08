//////
// DTXHTML.inl - Inline header file for the DTXNetHtml class
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////


DTX_VOID DTXNetHtml::htmlContent( DTX_CPSZ pszContent )
{
	strTmp = "Content-type: ";
	strTmp += pszContent;
	strTmp += "\n\n";
	*pOStream << strTmp;
}

DTX_VOID DTXNetHtml::htmlFlush()
{
	pOStream->flush();
}


DTX_VOID DTXNetHtml::htmlLocation( DTX_CPSZ pszURL )
{
	strTmp = "Location: ";
	strTmp += pszURL;
	strTmp += "\n\n";
	*pOStream << strTmp;
}


DTX_VOID DTXNetHtml::htmlStatus( DTX_INT  nStatus,
								 DTX_CPSZ pszStatusMsg )
{
	strTmp = "Status: ";
	strTmp += nStatus;
	strTmp += " ";
	strTmp += pszStatusMsg;
	strTmp += "\n\n";
	*pOStream << strTmp;
}


DTX_VOID DTXNetHtml::htmlStream( DTX_CPSZ    pszBuff,
								 DTX_CPSZ    pszDel )
{
	if ( pszDel != NULL )
		*pOStream << pszBuff << pszDel;
	else
		*pOStream << pszBuff;
}


inline DTX_PSZ DTXNetHtml::getImageSoundUrl()
{
	return strUrl.getBuffer();
}


inline ostream& DTXNetHtml::getOStream()
{
	return *pOStream;
}


inline DTX_VOID DTXNetHtml::setImageSoundUrl( DTX_CPSZ pszUrl )
{
	strUrl = pszUrl;
}

inline ostream& DTXNetHtml::setOStream( ostream& output )
{
	pOStream = &output;
	return output;
}



