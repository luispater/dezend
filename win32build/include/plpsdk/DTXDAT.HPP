//////
// DTXDAT.hpp - Header file for the DTXDate class.
//  (c)Copyright InnerX Communications, Inc. 1997-1998
//////

#ifndef __DTXDAT__
#define __DTXDAT__

#include <dtxbase.hpp>


class DTX_CLSEXPENTRY DTXDate : public DTXCollectable
{
public:
	DTXDate();
	DTXDate( DTX_INT sMonth, DTX_SMALLINT sDay, DTX_SMALLINT sYear );
	DTXDate( DTX_SMALLINT sDay, DTX_INT sMonth, DTX_SMALLINT sYear );
	DTXDate( const DTXDate& datValue );
	DTXDate( DTX_UINT nJulian );
	virtual ~DTXDate();

	DTXDate& operator=( DTXDate& datValue );
	DTXDate& operator=( DTX_UINT unValue );
	DTXDate  operator+( DTXDate& datValue );
	DTXDate& operator+=( DTXDate& datValue );
	DTXDate& operator+=( DTX_SMALLINT sValue );
	DTXDate& operator+=( DTX_INT nValue );
	DTXDate& operator+=( DTX_UINT unValue );
	DTXDate& operator-=( DTXDate& datValue );
	DTXDate& operator-=( DTX_SMALLINT sValue );
	DTXDate& operator-=( DTX_INT nValue );
	DTXDate& operator-=( DTX_UINT unValue );
	inline DTX_BOOLEAN operator==( DTXDate& datValue );
	inline DTX_BOOLEAN operator!=( DTXDate& datValue );

	virtual DTXDate&     	getCurrentDate();
	inline  DTX_SMALLINT 	getDay();
	virtual DTX_UINT     	getDayOfCentury();
	virtual DTX_SMALLINT 	getDayOfWeek();
	virtual DTX_SMALLINT 	getDayOfYear();
	virtual DTX_BOOLEAN  	getIsDateValid();
	virtual DTX_BOOLEAN  	getIsDateValid( DTX_INT sMonth, DTX_SMALLINT sDay, DTX_SMALLINT sYear );
	inline  DTX_UINT     	getJulianDate();
	virtual DTX_UINT     	getJulianDate( DTX_INT sMonth, DTX_SMALLINT sDay, DTX_SMALLINT sYear );
	inline  DTX_INT      	getMonth();
	inline  DTX_SMALLINT 	getYear();

	inline  DTX_VOID	  	setDay( DTX_SMALLINT sDay );
	inline  DTX_VOID    	setJulianDate();
	virtual DTX_VOID    	setJulianDate( DTX_UINT nJulian );
	inline  DTX_VOID    	setJulianDate( DTX_INT sMonth, DTX_SMALLINT sDay, DTX_SMALLINT sYear );
	inline  DTX_VOID    	setMonth( DTX_INT sMonth );
	inline  DTX_VOID    	setYear( DTX_SMALLINT sYear );

protected:
	DTX_UINT     nDate;
	DTX_INT      nMonth;
	DTX_SMALLINT nDay;
	DTX_SMALLINT nYear;
};


#include <dtxdat.inl>


#endif

