//////
// DTXSTR.hpp - Header file for the DTXString and DTXFormatString classes
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

#ifndef __DTXSTR__
#define __DTXSTR__

#include <dtxbase.hpp>
#include <dtxint.hpp>
#include <dtxdat.hpp>
#include <dtxtim.hpp>
#include <dtxlnk.hpp>

class DTXLinkList;
class DTXFormatDate;
class DTXFormatTime;
class DTXFormatNumber;
class DTXFormatString;
class DTXFormatCurrency;


class DTX_CLSEXPENTRY DTXString : public DTXCollectable
{
public:
	DTXString();
	DTXString( DTX_CPSZ pszString );
	DTXString( DTX_PSZ pszString );
	DTXString( DTX_PCHAR pString, DTX_UINT nSize );
	DTXString( DTX_SMALLINT sString );
	DTXString( DTX_INT nString );
	DTXString( DTX_UINT unString );
	DTXString( DTX_REAL rString );
	DTXString( DTX_FLOAT fString );
	DTXString( const DTXString& strString );
	virtual ~DTXString( );

	enum STRSIDE { strLEADING, strTRAILING };

	virtual DTXString&   strAppend( DTX_PCHAR pChar, DTX_UINT nSize );
	DTX_PSZ              strCenter( DTX_UINT unSize, DTX_CHAR cFillChar = ' ' );
	virtual DTX_VOID	 strClear();
	inline  DTX_VOID	 strFilterQuote();
	virtual DTX_PCHAR    strFind( DTX_CPSZ pszSubString , DTX_UINT nOffset = 1 , DTX_CPSZ pszSearchString = NULL ) ;
	virtual DTX_PCHAR    strFind( DTX_CHAR cSubChar, DTX_UINT nOffset = 1 , DTX_CPSZ pszSearchString = NULL ) ;
	virtual DTX_PCHAR    strFind( DTX_PCHAR pSubString, DTX_UINT nSize, DTX_UINT nOffset = 1, DTX_CPSZ pszSearchString = NULL ) ;
						//strFindNextOffset only works with this method
	virtual DTX_UINT     strFindOffset( DTX_CPSZ pszSubString, DTX_UINT nOffset = 1, DTX_CPSZ pszSearchString = NULL );
	virtual DTX_UINT     strFindOffset( DTX_CHAR cSubChar, DTX_UINT nOffset = 1, DTX_CPSZ pszSearchString = NULL );
	virtual DTX_UINT     strFindOffset( DTX_PCHAR pSubString, DTX_UINT nSize, DTX_UINT nOffset = 1, DTX_CPSZ pszSearchString = NULL );
	virtual DTX_UINT     strFindNextOffset(); //Returns 0 if not valid
	virtual DTXString&   strInsert( DTX_CHAR cChar, DTX_UINT nOffset = 1 );
	virtual DTXString&   strInsert( DTX_PCHAR pChar, DTX_UINT nSize, DTX_UINT nOffset = 1 );
	virtual DTXString&   strInsert( DTX_CPSZ pszString, DTX_UINT nOffset = 1 );
	DTX_PSZ              strLeft( DTX_UINT nEnd );
	DTX_PSZ		         strLeftJustify( DTX_UINT unSize, DTX_CHAR cFillChar = ' ', DTX_BOOLEAN fTruncate = FALSE );
	DTX_PSZ              strLeftTrim();
	DTX_PSZ              strMid( DTX_UINT nOffset );
	DTX_PSZ              strMid( DTX_UINT nOffset , DTX_UINT nSize );
	virtual DTX_UINT     strOccurencesOf( DTX_CPSZ pszSubString , DTX_CPSZ pszSearchString = NULL );
	virtual DTX_UINT     strOccurencesOf( DTX_PCHAR pSubString, DTX_UINT nSize , DTX_CPSZ pszSearchString = NULL );
	virtual DTX_UINT     strOccurencesOf( DTX_CHAR cSubChar, DTX_CPSZ pszSearchString = NULL );
	virtual DTXString    strRemove( DTX_UINT nOffset );
	virtual DTXString    strRemove( DTX_UINT nOffset, DTX_UINT nEnd );
	virtual DTX_UINT     strRemove( DTX_CPSZ pszString, DTX_BOOLEAN fALL = TRUE );
	virtual DTX_UINT     strReplace( DTX_CHAR cOldChar, DTX_CHAR cChar = '\0', DTX_BOOLEAN fAll = TRUE );
	virtual DTX_UINT     strReplace( DTX_CHAR cOldChar, DTX_CPSZ pszString, DTX_BOOLEAN fAll );
	virtual DTX_UINT     strReplace( DTX_CPSZ pszOldString, DTX_PCHAR pChar, DTX_UINT nSize, DTX_BOOLEAN fAll );
	virtual DTX_UINT     strReplace( DTX_CPSZ pszOldString , DTX_CPSZ pszString = NULL, DTX_BOOLEAN fAll = TRUE );
	DTX_VOID     		 strResetDefault();
	DTX_PSZ              strRight( DTX_UINT nOffset );
	DTX_PSZ              strRightJustify( DTX_UINT unSize, DTX_CHAR cFillChar = ' ' );
	DTX_PSZ              strRightTrim();
	DTX_PSZ              strRightTrim( DTX_PSZ pszBuffer );
	inline  DTX_VOID     strQuote();
	DTX_FLOAT            strToFloat();
	DTX_INT              strToInt();
	DTX_PSZ              strToLower();
	DTX_REAL             strToReal();
	DTX_SMALLINT         strToSmallInt();
	DTX_PSZ              strToUpper();
	DTX_UINT             strToUInt();
	DTX_PSZ              strTrim();
	inline  DTX_PSZ      strZeroFill( DTX_SMALLINT sWidth );
	inline  DTX_PSZ      strZeroRemove( DTX_SMALLINT sSide = DTXString::strLEADING );

	virtual              operator const char*();
	virtual              operator char*();
	virtual              operator unsigned char*();
	DTX_CHAR             operator[]( DTX_UINT nIndex );
	DTX_CHAR             operator()( DTX_UINT nIndex, DTX_CHAR cChar );
	DTX_UINT             operator[]( DTX_CPSZ pszString );
	DTXString&           operator=( DTXString *pString );
	DTXString&           operator=( DTXString& strString );
	DTXString&           operator=( DTXFormatDate& strDate );
	DTXString&           operator=( DTXFormatTime& strTime );
	DTXString&           operator=( DTXFormatNumber& strNum );
	DTXString&           operator=( DTXFormatCurrency& strCurr );
	DTXString&           operator=( DTXFormatString& strString );
	DTXString&           operator=( DTX_CPSZ pszString );
	DTXString&           operator=( DTX_PSZ pszString );
	DTXString&           operator=( DTX_CHAR cChar );
	DTXString&           operator=( DTX_SMALLINT sValue );
	DTXString&           operator=( DTX_INT nValue );
	DTXString&           operator=( DTX_UINT unValue );
	DTXString&           operator=( DTX_REAL rValue );
	DTXString&           operator=( DTX_FLOAT fValue );
	DTXString            operator+( DTXString *pString );
	DTXString            operator+( DTXString& strString );
	DTXString            operator+( DTX_CPSZ pszString );
	DTXString            operator+( DTX_CHAR cChar );
	inline friend DTXString	operator+( DTX_CPSZ pszString, DTXString& strString );
	DTXString&           operator+=( DTXString *pString );
	DTXString&           operator+=( DTXString& strString );
	DTXString&			 operator+=( DTXFormatDate& strDate );
	DTXString&			 operator+=( DTXFormatTime& strTime );
	DTXString&			 operator+=( DTXFormatNumber& strNum );
	DTXString&			 operator+=( DTXFormatCurrency& strCurr );
	DTXString&			 operator+=( DTXFormatString& strString );
	DTXString&           operator+=( DTX_CPSZ pszString );
	DTXString&           operator+=( DTX_PSZ pszString );
	DTXString&           operator+=( DTX_CHAR cChar );
	inline friend istream&		 operator>>( istream& input, DTXString& strValue );
	inline friend ostream&		 operator<<( ostream& output, DTXString& strValue );
	inline DTX_BOOLEAN			 operator==( DTXString& strString );
	inline DTX_BOOLEAN			 operator==( DTX_CPSZ pszString );
	inline friend DTX_BOOLEAN    operator==( DTX_CPSZ pszString1, const DTXString& strString2 );
	inline DTX_BOOLEAN			 operator==( DTX_PSZ pszString );
	inline friend DTX_BOOLEAN    operator==( DTX_PSZ pszString1, const DTXString& strString2 );
	inline DTX_BOOLEAN			 operator!=( DTXString& strString );
	inline DTX_BOOLEAN			 operator!=( DTX_CPSZ pszString );
	inline friend DTX_BOOLEAN    operator!=( DTX_CPSZ pszString1, const DTXString& strString2 );
	inline DTX_BOOLEAN			 operator!=( DTX_PSZ pszString );
	inline friend DTX_BOOLEAN    operator!=( DTX_PSZ pszString1, const DTXString& strString2 );
	inline  DTX_PSZ      getBuffer();
	inline  DTX_PCHAR    getBuffer( DTX_PCHAR pBuff, DTX_UINT nSize );
	inline  DTX_UINT     getBufferLen();
	DTX_CHAR             getCharAt( DTX_UINT nIndex );
	DTX_BOOLEAN          getFindCase();
	DTX_PSZ              getFirstWord();
	DTX_PSZ              getLastWord();
	DTX_UINT             getNumOfWords();
	inline  DTX_UINT     getStringLen();
	DTX_PSZ 			 getWord( DTX_INT nWord );

	DTX_VOID             setBuffer( DTX_CPCHAR pChar, DTX_UINT nSize );
	DTX_VOID             setBuffer( DTX_UINT nSize );
	DTX_VOID             setFindCase( DTX_BOOLEAN fFlag = FALSE );
	DTX_VOID             setResizeBuffer( DTX_UINT nSize );
	DTX_VOID             setStringLen();

protected:
	DTX_PCHAR            pBuffer;
	DTX_PCHAR            pBuff;
	DTX_PCHAR            pFindNext; //Do not have the class lose scope or this value is dead
	DTX_PCHAR            pFindNextSub;
	DTX_UINT             nFindOffset;
	DTX_UINT             nLen;
	DTX_UINT             nBuffLen;
	DTX_BOOLEAN          fCase;
};



//DTXStringToken...

class DTX_CLSEXPENTRY DTXStringToken : public DTXCollectable
{
public:
	DTXStringToken();
	DTXStringToken( DTXString& strValue );
	virtual ~DTXStringToken();

	enum TOKEN_POS { TOKEN_LAST = -1, TOKEN_FIRST = 0 };

	inline  DTX_BOOLEAN strIsNull();
	virtual DTXString   strToken();

	DTX_BOOLEAN         getWhiteSpaceAsToken();

	DTX_VOID            setTokenPosition( DTX_INT nPos = DTXStringToken::TOKEN_FIRST );
	DTX_VOID            setWhiteSpaceAsToken( DTX_BOOLEAN fFlag = FALSE );

	DTXString		   *m_pString;

private:
	DTX_PCHAR   pPtr;
	DTX_UINT    nOffset;
	DTX_BOOLEAN fWhite;
};






class DTX_CLSEXPENTRY DTXFormatString : public DTXString
{
public:
	DTXFormatString();
	DTXFormatString( const DTXString& strString , DTX_CPSZ pszFormat = NULL );
	DTXFormatString( const DTXFormatString& strString );
	virtual ~DTXFormatString( );

	enum FORMATTYPE { fmtGENERAL, fmtCUSTOM };

	DTX_PSZ           getBuffer();
	DTX_PCHAR         getBuffer( DTX_PCHAR pBuff, DTX_UINT nSize );
	DTX_CHAR          getFmtCharAt( DTX_UINT nIndex );
	DTX_UINT          getFmtBufferLen();
	DTX_PSZ           getFmtBuffer();
	DTXInternational& getInternationalObject();
	DTX_SMALLINT      getNumericDisplayWidth();

	DTX_PSZ   	      setFmtBuffer( DTX_CPSZ pszFmt );
	DTX_PSZ           setFmtBuffer( DTX_PCHAR pFmt, DTX_UINT nSize );
	DTX_VOID          setInternationalObject( const DTXInternational& intObj );
	DTX_VOID          setNumericDisplayWidth( DTX_SMALLINT sWidth );

protected:
	DTXInternational Int;
	DTX_PSZ          getCustomBuffer();
	DTX_PSZ          setCurNumBuffer( DTX_PSZ, DTX_SMALLINT, DTX_SMALLINT, DTX_SMALLINT, DTX_PSZ, DTX_PSZ );
	DTX_PCHAR        pFormat;
	DTX_UINT         nFormatLen;
	DTX_SMALLINT     sFmtType;
	DTX_SMALLINT     sNDisplayWidth;
};


class DTX_CLSEXPENTRY DTXFormatCurrency : public DTXFormatString
{
public:
	DTXFormatCurrency();
	DTXFormatCurrency( const DTXString& strString );
	virtual ~DTXFormatCurrency();

	DTX_PSZ          getBuffer();
	DTX_PCHAR        getBuffer( DTX_PCHAR pBuff, DTX_UINT nSize );
	DTX_PSZ          getWordBuffer();
	DTX_BOOLEAN      getWordOption();

	DTX_VOID         setWordOption( DTX_BOOLEAN fFlag = FALSE );

private:
	DTXString        Tmp;
	DTX_BOOLEAN      fWord;
};


class DTX_CLSEXPENTRY DTXFormatNumber : public DTXFormatString
{
public:
	DTXFormatNumber();
	DTXFormatNumber( const DTXString& strString );
	virtual ~DTXFormatNumber();

	DTX_PSZ          getBuffer();
	DTX_PCHAR        getBuffer( DTX_PCHAR pBuff, DTX_UINT nSize );
};


//The default date formatting is to use the international setting if one is
// present.

class DTX_CLSEXPENTRY DTXFormatDate : public DTXFormatString
{
public:
	DTXFormatDate();
	DTXFormatDate( DTXDate& datValue , DTX_CPSZ pszFormat = NULL );
	virtual ~DTXFormatDate();

	//The following are special characters used for the custom format.
	// All other characters in the format will be treated as literals
	// and left alone.

	//	MONTH	-	Month spelled out in all capitals (JANUARY)
	//	Month	-	Month spelled out with only the first character capitalized (January)
	//	month	- 	Month spelled out with no letters capitalized (january)
	//	MM or mm-	Numeric value of month (01)
	//	MMM	- 	Month abbreviated in all capitals (JAN)
	//	Mmm	- 	Month abbreviated with only the first letter capitalized (Jan)
	//	mmm	-	Month abbreviated with no letters capitalized (jan)

	//	DAY 	-	Day spelled out in all capitals (SUNDAY)
	//	Day	-	Day spelled out with only the first letter capitalized (Sunday)
	//	day	-       Day spelled out with no letters capitialized (sunday)
	//	DD or dd-	Numeric value of day (01)
	//	DDD	-	Day abbreviated in all capitals (SUN)
	//	Ddd	-       Day abbreviated with only the first letter capitalized (Sun)
	//	ddd	-	Day abbreviated with no letters capitalized (sun)

	//	YY or yy-	Numeric value of year (95)
	//	YYYY or yyyy-   Numeric value of century/year (1995)

			DTX_PSZ          getBuffer();
			DTX_PCHAR        getBuffer( DTX_PCHAR pBuff, DTX_UINT nSize );
			DTX_PSZ          getDayName();
			DTX_PSZ          getDayNameAbbreviate();
			DTX_PSZ          getMonthName();
			DTX_PSZ          getMonthNameAbbreviate();

	inline  DTX_VOID      setDateObject( DTXDate& datValue );
		    DTX_VOID      setFormat( DTX_CPSZ pszFormat );

protected:
	DTX_VOID         setPartListFree();
	DTXLinkList      PartList;
	DTXString        Tmp;
	DTXDate          Date;
	DTX_CHAR         szDat[5];
	DTX_SMALLINT     sFormat;
};



class DTX_CLSEXPENTRY DTXFormatTime : public DTXFormatString
{
public:
	DTXFormatTime();
	DTXFormatTime( DTXTime& timValue , DTX_CPSZ pszFormat = NULL );
	virtual ~DTXFormatTime();

	inline  DTX_PSZ          getAM();
			DTX_PSZ          getBuffer();
			DTX_PCHAR        getBuffer( DTX_PCHAR pBuff, DTX_UINT nSize );
	inline  DTX_PSZ          getPM();

	inline	DTX_VOID         setAM( DTX_CPSZ pszAM );
			DTX_VOID         setFormat( DTX_CPSZ pszFormat );
	inline 	DTX_VOID         setPM( DTX_CPSZ pszPM );
	inline	DTX_VOID         setTimeObject( DTXTime& timValue );

protected:
	DTX_VOID		setPartListFree();
	DTXLinkList     PartList;
	DTXString 	    TmpTime;
	DTXString       Hour;
	DTXString       Min;
	DTXString       Sec;
	DTXString       Hun;
	DTXTime         Time;
	DTX_CHAR        szAM[3];
	DTX_CHAR        szPM[3];
	DTX_CHAR 	    szAMPM[3];
	DTX_CHAR 	    szTim[2];
	DTX_SMALLINT    sFmt;
	DTX_SMALLINT    sFormat;
};


#include <dtxstr.inl>

#endif


