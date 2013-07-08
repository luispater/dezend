//////
// DTXMAIL.hpp - Header file for the DTXNetMail class
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

#ifndef __DTXMAIL__
#define __DTXMAIL__

// This is class is full POP3 enabled by default.

//-TBD- This class needs to be altered to support RFC 822.  This
// RFC supports all of the folding and unfolding of lines and 
// the date/time formats.

#include <dtxnetc.hpp>

class DTX_CLSEXPENTRY DTXNetMail : public DTXNetClient
{
public:
	DTXNetMail();
	DTXNetMail( DTX_CPSZ pszHost, DTX_USMALLINT uPort = DTXNETPORT_POP3 );
	virtual ~DTXNetMail();

	virtual DTX_RETCODE netConnect();
	virtual DTX_RETCODE netConnect( DTX_USMALLINT uPort );
	virtual DTX_RETCODE netDisconnect( DTX_INT nConnection = 0 );

	virtual DTX_RETCODE mailAttachment( DTX_CPSZ pszFileName, DTX_CPSZ pszPath );
	virtual DTX_RETCODE mailSend();
	virtual DTX_RETCODE mailDelete( DTX_INT nMsg );
	virtual DTX_RETCODE mailFetch( DTX_INT nMsg );
	virtual DTX_RETCODE mailStat();
	virtual DTX_RETCODE mailStat( DTX_PINT pnCount, DTX_PUINT puSize );
	virtual DTX_PSZ     mailWhois( DTX_CPSZ pszAlias );

	inline  DTX_PSZ     getBoundary();
	inline  DTX_INT     getNumOf();
	inline  DTX_BOOLEAN getSendMail();
	inline  DTX_UINT    getSizeOf();

	virtual DTX_VOID    setBase64();
	virtual DTX_PSZ     setBoundary( DTX_CPSZ pszValue = NULL );
	inline  DTX_VOID    setSendMail( DTX_BOOLEAN fSend = FALSE );

	//Only use these public data members for SMTP operations
	DTXString m_strHeader;
	DTXString m_strBody;
	DTXString m_strFrom;
	DTXString m_strTo;
	DTXString m_strSubject;

private:
	DTXString   strData;
	DTXString   strBoundary;
	DTXString   strAttachment;
	DTXString   strPath;
	DTX_PCHAR   pData;
	DTX_UINT    unDataLen;
	DTX_UINT    unSizeOf;
	DTX_INT     nNumOf;
	DTX_BOOLEAN fSendMail;
	DTX_BOOLEAN fAttachment;
};

#include <dtxmail.inl>

#endif
