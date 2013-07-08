//////
// DTXTHR.inl - Inline header file for the DTXThread, DTXSynchronization and DTXProcess classes
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

inline DTX_VOID DTXCurrentThread::setStackSize( DTX_UINT nSize )
{
	nStack = nSize ;
}


inline DTX_VOID DTXCurrentThread::setTID( DTX_THREADID nTID )
{
	nId = nTID;
}


inline DTX_VOID DTXCurrentThread::setTHandle( DTX_HTHREAD hTHandle )
{
	hThread = hTHandle;
}


inline DTX_THREADID DTXCurrentThread::getTID()
{
	return nId ;
}


inline DTX_HTHREAD DTXCurrentThread::getTHandle()
{
	return hThread ;
}

inline DTX_UINT DTXCurrentThread::getStackSize()
{
	return nStack;
}


inline DTXSynchronization *DTXCurrentThread::synObject()
{
	return m_pSync;
}

inline DTX_VOID DTXCurrentThread::setSynchronization( DTXSynchronization *pSyn )
{
	m_pSync = pSyn;
}


inline DTX_VOID DTXCurrentThread::setSynchronization( DTXSynchronization& Syn )
{
	m_pSync = &Syn;
}



inline DTX_VOID DTXSynchronization::setSynAttr( DTX_UINT unAttr )
{
        unSynAttr = unAttr;
}

inline DTX_VOID DTXSynchronization::setSynName( DTX_CPSZ pszName )
{
        strncpy(szName,pszName,sizeof(szName)-1);
}

inline DTX_VOID DTXSynchronization::setSynState( DTX_BOOLEAN fState )
{
        fSyncState = fState;
}



inline DTX_VOID DTXSynchronization::setSynType( DTX_SMALLINT sSynType )
{
        sType = sSynType;
}

inline DTX_VOID DTXSynchronization::setSynHandle( DTX_HSYNC hSyn )
{
        hSync = hSyn;
}


inline DTX_UINT DTXSynchronization::getSynAttr()
{
        return unSynAttr;
}

inline DTX_HSYNC DTXSynchronization::getSynHandle()
{
        return hSync;
}

inline DTX_PSZ DTXSynchronization::getSynName()
{
        return szName;
}


inline DTX_BOOLEAN DTXSynchronization::getSynState()
{
        return fSyncState;
}

inline DTX_SMALLINT DTXSynchronization::getSynType()
{
        return sType ;
}




inline DTX_UINT DTXProcess::getPID()
{
	return unId;
}


inline DTX_HPROCESS DTXProcess::getPHandle()
{
	return hProcess;
}


inline DTX_VOID DTXProcess::setPID( DTX_UINT unID )
{
	unId = unID;
}



inline DTX_VOID DTXProcess::setPHandle( DTX_HPROCESS hPHandle )
{
	hProcess = hPHandle;
}



inline DTX_BOOLEAN DTXThreadFn::getClassDelete()
{
        return fDeleteClass;
}


inline DTX_VOID DTXThreadFn::setClassDelete( DTX_BOOLEAN fFlag )
{
        fDeleteClass = fFlag;
}


