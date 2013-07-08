//////
// DTXDAT.inl - Inline header file for the DTXDate class
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

inline DTX_BOOLEAN DTXDate::operator!=( DTXDate& datValue )
					    
{
	if ( datValue.getJulianDate() != getJulianDate() )
		return TRUE;
	return FALSE;
}

inline DTX_BOOLEAN DTXDate::operator==( DTXDate& datValue )
					    
{
	if ( datValue.getJulianDate() == getJulianDate() )
		return TRUE;
	return FALSE;
}

inline DTX_SMALLINT DTXDate::getYear()
{
	return nYear;
}

inline DTX_INT DTXDate::getMonth()
{
	return nMonth;
}

inline DTX_SMALLINT DTXDate::getDay()
{
	return nDay;
}


inline DTX_UINT DTXDate::getJulianDate()
{
	return nDate;
}



inline DTX_VOID DTXDate::setJulianDate()
{
	setJulianDate(getMonth(),getDay(),getYear());
}


inline DTX_VOID DTXDate::setJulianDate( DTX_INT      sMonth,
					DTX_SMALLINT sDay,
					DTX_SMALLINT sYear )
{
	nDate = getJulianDate(sMonth,sDay,sYear);
}

inline DTX_VOID DTXDate::setMonth( DTX_INT sMonth )
{
	nMonth = sMonth;
}

inline DTX_VOID DTXDate::setDay( DTX_SMALLINT sDay )
{
	nDay = sDay;
}

inline DTX_VOID DTXDate::setYear( DTX_SMALLINT sYear )
{
	nYear = sYear;
}

