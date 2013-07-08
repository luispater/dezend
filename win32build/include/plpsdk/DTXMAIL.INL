//////
// DTXMAIL.inl - Inline header file for the DTXNetMail class
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////


inline DTX_PSZ DTXNetMail::getBoundary()
{
	return strBoundary.getBuffer();
}


inline DTX_INT DTXNetMail::getNumOf()
{
	return nNumOf;
}

inline DTX_UINT DTXNetMail::getSizeOf()
{
	return unSizeOf;
}

inline DTX_BOOLEAN DTXNetMail::getSendMail()
{
	return fSendMail;
}


inline DTX_VOID DTXNetMail::setSendMail( DTX_BOOLEAN fSend )
{
	fSendMail = fSend;
}

