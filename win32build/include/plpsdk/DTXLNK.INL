//////
// DTXLNK.inl - Inline header for DTXLinkList class
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////





inline DTX_INT DTXLinkList::getNumOfItems()
{
	return nNumOfItems;
}





inline DTXLinkNode *DTXLinkList::lnkCurrentItem()
{
	return pCurrent;
}


inline DTXLinkNode *DTXLinkList::lnkFirstItem()
{
	pCurrent = pFirst;
	return pFirst;
}

inline DTXLinkNode *DTXLinkList::lnkFirstObject()
{
	pCurrent = pFirst;
	return pFirst;
}


inline DTXLinkNode *DTXLinkList::lnkNextObject()
{
	if ( pCurrent != NULL )
	     pCurrent = pCurrent->m_pNext;

	return pCurrent;
}


inline DTXLinkNode *DTXLinkList::lnkNextItem()
{
	if ( pCurrent != NULL )
	     pCurrent = pCurrent->m_pNext;

	return pCurrent;
}


inline DTXLinkNode *DTXLinkList::lnkPrevItem()
{
	if ( pCurrent != NULL )
	     pCurrent = pCurrent->m_pPrev;

	return pCurrent;
}


inline DTXLinkNode *DTXLinkList::lnkResetIter()
{
	pCurrent = pFirst;
	return pCurrent;
}

inline DTXLinkNode *DTXLinkList::lnkLastItem()
{
	pCurrent = pLast;
	return pLast;
}



inline DTXLinkNode *DTXLinkList::lnkLocateItem( DTXCollectable& pItem )
{
	return(lnkLocateItem(&pItem.m_lnkNode));
}


inline DTXLinkNode *DTXLinkList::lnkLocateItem( DTXCollectable *pItem )
{
	return (lnkLocateItem(&pItem->m_lnkNode));
}

inline DTXLinkNode *DTXLinkList::lnkDeleteItem( DTXCollectable& pItem )
{
	return(lnkDeleteItem(&pItem.m_lnkNode));
}

inline DTXLinkNode *DTXLinkList::lnkDeleteItem( DTXCollectable *pItem )
{
	return(lnkDeleteItem(&pItem->m_lnkNode));
}


inline DTXLinkNode *DTXLinkList::setFirstItem( DTXCollectable& pItem )
{
	return (setFirstItem(&pItem.m_lnkNode));
}


inline DTXLinkNode *DTXLinkList::setFirstItem( DTXCollectable *pItem )
{
	return (setFirstItem(&pItem->m_lnkNode));
}




inline DTXLinkNode *DTXLinkList::setLastItem( DTXCollectable& pItem )
{
	return (setLastItem(&pItem.m_lnkNode));
}


inline DTXLinkNode *DTXLinkList::setLastItem( DTXCollectable *pItem )
{
	return (setLastItem(&pItem->m_lnkNode));
}
