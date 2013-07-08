//////
// DTXLNK.hpp - Header file for the DTXLink class
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

#ifndef __DTXLNK__
#define __DTXLNK__

#include <dtxbase.hpp>




class DTX_CLSEXPENTRY DTXLinkList
{
public:
	DTXLinkList();
	DTXLinkList( DTXLinkNode& pItem );
	virtual ~DTXLinkList();

	DTXLinkNode * operator++(int);
	DTXLinkNode * operator--(int);

	inline  DTXLinkNode *lnkCurrentItem();
	virtual DTX_UINT     lnkDeleteItem();
	virtual DTXLinkNode *lnkDeleteItem( DTX_UINT nNumber );
	virtual DTXLinkNode *lnkDeleteItem( DTXLinkNode *pItem );
	virtual DTXLinkNode *lnkDeleteItem( DTXCollectable& pItem );
	virtual DTXLinkNode *lnkDeleteItem( DTXCollectable *pItem );
	inline  DTXLinkNode *lnkFirstItem();
	virtual DTXLinkNode *lnkInsertItem( DTXLinkNode *pItem ); //This inserts at the current location.
	inline  DTXLinkNode *lnkLastItem();
	virtual DTXLinkNode *lnkLocateItem( DTX_UINT nNumber );
	virtual DTXLinkNode *lnkLocateItem( DTXLinkNode *pItem );
	virtual DTXLinkNode *lnkLocateItem( DTXCollectable& pItem );
	virtual DTXLinkNode *lnkLocateItem( DTXCollectable *pItem );
	inline  DTXLinkNode *lnkNextItem();
	inline  DTXLinkNode *lnkPrevItem();
	inline  DTXLinkNode *lnkResetIter();

	inline  DTXLinkNode  *lnkFirstObject();
	inline  DTXLinkNode  *lnkNextObject();

	inline  DTX_INT      getNumOfItems();

	inline  DTXLinkNode *setFirstItem( DTXLinkNode *pItem );
	inline  DTXLinkNode *setFirstItem( DTXCollectable& pItem );
	inline  DTXLinkNode *setFirstItem( DTXCollectable *pItem );
	virtual DTXLinkNode *setLastItem( DTXLinkNode *pItem );
	inline  DTXLinkNode *setLastItem( DTXCollectable& pItem );
	inline  DTXLinkNode *setLastItem( DTXCollectable *pItem );

private:
	DTXLinkNode *pFirst;
	DTXLinkNode *pLast;
	DTXLinkNode *pCurrent;
	DTX_UINT     nNumOfItems;
};

#include <dtxlnk.inl>

#endif

