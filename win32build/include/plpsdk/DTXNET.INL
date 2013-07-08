//////
// DTXNET.inl - Inline header for the DTXNetObject class
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

inline DTX_SMALLINT DTXNetParam::getNumOfParam()
{
	return sNParams;
}


inline DTX_SMALLINT DTXNetParam::getParameters()
{
	return sParams;
}

//Better make sure the buffer is large enough to hold the data!

inline DTX_LINT DTXNetParam::getPopParam( DTX_PVOID pData ,
								          DTX_LINT  lLength )
{
	if ( sNParams <= 0 ||
		 sCurr > sNParams )
		return 0;
	
	memmove(pData,m_pParams[sCurr-1].m_strBuffer.getBuffer(),lLength);
	sCurr++;
	return lLength;
}


inline DTX_LINT DTXNetParam::getPopParamLength()
{
	if ( sNParams <= 0 )
		return 0;
	
	return m_pParams[sCurr-1].m_strBuffer.getStringLen();
}


inline DTX_VOID DTXNetParam::setParameters( DTX_SMALLINT sNumOf )
{
	sCurr = 0;
	sNParams = 0;
	m_lLength = 0;

	if ( sNumOf > sParams )
		{
		if ( m_pParams != NULL )
			delete m_pParams;

		m_pParams = new DTXNetParameters[sNumOf];

		sParams = sNumOf;
		}	
}


inline DTX_VOID DTXNetParam::setParamList()
{
	sNParams = 0;
	sCurr = 0;
	m_lLength = 0;
	return;
}


inline DTX_VOID DTXNetParam::setPushParam( DTX_PVOID pData,
								           DTX_LINT  lLength )
{
	if ( sCurr >= sParams )
		return;
	sCurr++;
	m_pParams[sCurr-1].m_strBuffer.setBuffer((DTX_PCHAR)pData,lLength);
	sNParams++;
	m_lLength += lLength;
}


inline DTX_VOID DTXNetParam::setResetIter()
{
	if ( sNParams <= 0 )
		{
		sNParams = 0;
		sCurr = 0;
		}
	else
		sCurr = 1;
}





inline DTX_INT DTXNetObject::getPacketSize()
{
	return nSize;
}

inline DTX_SMALLINT DTXNetObject::getType()
{
	return sType;
}

inline DTX_SMALLINT DTXNetObject::getState()
{
	return sState;
}


//Should always be returned in Network order.
inline DTX_USMALLINT DTXNetObject::getPort()
{
	return sPort;
}

inline DTX_PSZ DTXNetObject::getHost()
{
	return (strName.getBuffer());
}




inline DTX_ULINT DTXNetObject::getAddress()
{
	return (ulAdd);
}

inline DTX_PSZ DTXNetObject::getAddressString()
{
	return strAdd.getBuffer();
}

inline DTX_USMALLINT DTXNetObject::getProtocol()
{
	return usProto;
}

inline DTX_INT DTXNetObject::getSocket()
{
	return nSocket;
}


inline DTX_INT DTXNetObject::getRetryCount()
{
	return nRetry;
}


inline DTX_BOOLEAN DTXNetObject::getBlocking()
{
	return fBlock;
}


inline DTX_INT DTXNetObject::getTimeOut()
{
	return nTimeOut;
}

/*
inline DTX_SMALLINT DTXNetObject::getGetMsgOption()
{
	return sAction;
}


inline DTX_VOIDTYP DTXNetObject::setGetMsgOption( DTX_SMALLINT sAct )
{
	sAction = sAct;
}
*/

inline DTX_VOID DTXNetObject::setTimeOut( DTX_INT nValue )
{
	nTimeOut = nValue;
}

inline DTX_VOID DTXNetObject::setPacketSize( DTX_INT nLen )
{
	nSize = nLen;
}


inline DTX_VOID DTXNetObject::setRetryCount( DTX_INT nNum )
{
	nRetry = nNum;
}


inline DTX_SMALLINT DTXNetObject::setState( DTX_SMALLINT sSocketState )
{
	DTX_SMALLINT sOld = sState;
	sState = sSocketState;
	return sOld;
}

inline DTX_VOID DTXNetObject::setSocket( DTX_INT nClientSocket )
{
	nSocket = nClientSocket;
	fSocket = FALSE;
}

