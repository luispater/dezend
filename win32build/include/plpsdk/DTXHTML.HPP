//////
// DTXHTML.hpp - Header file for the DTXNetHtml class
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

#ifndef __DTXHTML__
#define __DTXHTML__

#include <dtxnet.hpp>



class DTX_CLSEXPENTRY DTXNetHtml
{
public:
	DTXNetHtml();
	DTXNetHtml( ostream& output );
	virtual ~DTXNetHtml();

	inline  DTX_VOID	htmlContent( DTX_CPSZ pszContent = "text/html" );
	virtual DTX_VOID    htmlError( DTX_CPSZ pszHeader, DTX_CPSZ pszBody, DTX_CPSZ pszEmail, DTX_CPSZ pszColor = "#FFFFFF", DTX_CPSZ pszFooter = NULL );
	inline  DTX_VOID	htmlFlush();
	virtual DTX_VOID	htmlFlushFile( DTX_CPSZ pszFileName, DTX_CPSZ pszPath );
	inline  DTX_VOID    htmlLocation( DTX_CPSZ pszURL );
	inline  DTX_VOID    htmlStatus( DTX_INT nStatus, DTX_CPSZ pszStatusMsg );
	inline  DTX_VOID	htmlStream( DTX_CPSZ pszBuff, DTX_CPSZ pszDel = "\n" );

	inline  DTX_PSZ     getImageSoundUrl();
	inline  ostream&	getOStream();

	inline  DTX_VOID    setImageSoundUrl( DTX_CPSZ pszUrl );
	inline  ostream&	setOStream( ostream& output );

private:
	ostream		*pOStream;
	DTXString   strUrl;
	DTXString   strTmp;
};



#include <dtxhtml.inl>


#endif

