//////
// DTXINT.hpp - Header file for the DTXInternational class.
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

#ifndef __DTXINT__
#define __DTXINT__

#include <dtxbase.hpp>



class DTX_CLSEXPENTRY DTXInternational
{
public:
	DTXInternational();
	virtual ~DTXInternational( );

	enum CURRENCY { curSYMINDEC, curSYMPRECEDES, curSYMFOLLOWES };
	enum CURRENCY_NEGPOS { curPARENTHESIS, curPRECEDE, curFOLLOWS, curPRECEDESYMBOL, curFOLLOWSSYMBOL };
	enum NUMERIC_NEGPOS { numPARENTHESIS, numPRECEDE, numFOLLOWS };

	DTX_UINT		getCodePage();
	DTX_UINT		getCountryCode();
	DTX_SMALLINT	getCurDecimalPlaces();
	DTX_PSZ			getCurDecimalSymbol();
	DTX_SMALLINT	getCurNegativePosition();
	DTX_SMALLINT	getCurSpaces();
	DTX_PSZ			getCurSymbol();
	DTX_SMALLINT	getCurSymbolLoc();
	DTX_PSZ			getCurThousandSymbol();
	DTX_SMALLINT	getDateFormat();
	DTX_PSZ			getDateSymbol();
	DTX_SMALLINT	getDecimalPlaces();
	DTX_PSZ			getDecimalSymbol();
	DTX_SMALLINT	getNegativePosition();
	DTX_PSZ			getThousandSymbol();
	DTX_SMALLINT	getTimeFormat();
	DTX_PSZ			getTimeSymbol();

	DTX_BOOLEAN		setCountryCodeAndPage( DTX_UINT nCode = 0 , DTX_UINT nPage = 0 );
	DTX_VOID		setCurDecimalPlaces( DTX_SMALLINT sDecimalPlaces );
	DTX_VOID		setCurDecimalSymbol( DTX_CPSZ pszDecimalSymbol );
	DTX_VOID		setCurNegativePosition( DTX_SMALLINT sPos = DTXInternational::curPARENTHESIS );
	DTX_VOID		setCurSpaces( DTX_SMALLINT sCurSpaces );
	DTX_VOID		setCurSymbol( DTX_CPSZ pszCurrencySymbol );
	DTX_VOID		setCurSymbolLoc( DTX_SMALLINT sCurLoc );
	DTX_VOID		setCurThousandSymbol( DTX_CPSZ pszThousandsSeparator );
	DTX_VOID		setDateFormat( DTX_SMALLINT sDateFmt );
	DTX_VOID		setDateSymbol( DTX_CPSZ pszDateSeparator );
	DTX_VOID		setDecimalPlaces( DTX_SMALLINT sDecimalPlaces );
	DTX_VOID		setDecimalSymbol( DTX_CPSZ pszDecimalSymbol );
	DTX_VOID		setNegativePosition( DTX_SMALLINT sPos = DTXInternational::numPRECEDE );
	DTX_VOID		setThousandSymbol( DTX_CPSZ pszThousandsSeparator );
	DTX_VOID		setTimeFormat( DTX_SMALLINT sFmt );
	DTX_VOID		setTimeSymbol( DTX_CPSZ pszTimeSeparator );

private:
	DTX_CHAR		szCurSym[5];
	DTX_UINT		nCCode;
	DTX_UINT		nCPage;
	DTX_CHAR		szThoSym[2];
	DTX_CHAR		szCThoSym[2];
	DTX_CHAR		szDecSym[2];
	DTX_CHAR		szCDecSym[2];
	DTX_CHAR		szDatSym[2];
	DTX_CHAR		szTimSym[2];
	DTX_SMALLINT	sDFormat;
	DTX_SMALLINT	sCLocation;
	DTX_SMALLINT	sCSpaces;
	DTX_SMALLINT	sDPlaces;
	DTX_SMALLINT	sCDPlaces;
	DTX_SMALLINT	sTFormat;
	DTX_SMALLINT	sCNegPos;
	DTX_SMALLINT	sNegPos;
};




#endif


