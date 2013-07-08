//////
// DTXNETS.inl - Inline header for the DTXNetServer class
//  (c)Copyright InnerX Communications, Inc. 1997-1998
/////
/*
inline DTX_INT DTXNetConnection::getNumOfValidConnects()
{
	return nValidConnects;
}

inline DTX_INT DTXNetConnection::getNumOfConnections()
{
	return nConnections;
}
*/


//Server

inline DTX_BOOLEAN DTXNetServer::getAutoPort()
{
	return fAutoPort;
}


inline DTX_VOID DTXNetServer::setAutoPort( DTX_BOOLEAN fPort )
{
	fAutoPort = fPort;
}

inline DTX_UINT DTXNetServer::getActiveConnects()
{
	return unActCon;
}


inline DTX_INT DTXNetServer::getClientMax()
{
	return nMaxClients;
}

inline DTX_SMALLINT DTXNetServer::getConnectThreadPool()
{
	return sCon;
}


inline DTX_BOOLEAN DTXNetServer::getServiceOption()
{
	return fService;
}



inline DTX_VOID DTXNetServer::setClientMax( DTX_INT nNumOf )
{
	nMaxClients = nNumOf;
}

