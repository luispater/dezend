//////
// DTXFTP.inl - Source file for the DTXNetFtp class inline methods
//	(c)Copyright InnerX Communications, Inc. 1997-1998
//////

inline DTX_RETCODE DTXNetFtp::getServerReplyCode()
{
	return nReply;
}


inline DTX_PSZ DTXNetFtp::getServerReplyMsg()
{
	return strReply.getBuffer();
}

