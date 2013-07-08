//////
// DTXTIM.hpp - Header file for the DTXTime class.
//  (c)Copyright InnerX Communications, Inc. 1998
//////

#ifndef __DTXTIM__
#define __DTXTIM__

#include <dtxbase.hpp>

char *abrivday(int);
char *abrivmon(int);
char *emailtime(struct tm *);


class DTX_CLSEXPENTRY DTXTime : public DTXCollectable
{
public:
	DTXTime();
	DTXTime( const DTXTime& timValue );
	virtual ~DTXTime();

	virtual DTXTime&     getCurrentTime();
	virtual DTX_SMALLINT getHour();
	virtual DTX_SMALLINT getHundred();
	virtual DTX_SMALLINT getMinute();
	virtual DTX_SMALLINT getSecond();

	virtual DTX_VOID	setHour( DTX_SMALLINT sHours );
	virtual DTX_VOID	setHundred( DTX_SMALLINT sHund );
	virtual DTX_VOID	setMinute( DTX_SMALLINT sMin );
	virtual DTX_VOID	setSecond( DTX_SMALLINT sSec );
	virtual DTX_VOID	setTime( DTX_SMALLINT sHours, DTX_SMALLINT sMin, DTX_SMALLINT sSec, DTX_SMALLINT sHund = 0 );
	virtual DTX_VOID	setTime( DTX_CPSZ pszHour, DTX_CPSZ pszMin, DTX_CPSZ pszSec, DTX_CPSZ pszHund = NULL );

protected:
	DTX_SMALLINT sHour;
	DTX_SMALLINT sMinute;
	DTX_SMALLINT sSecond;
	DTX_SMALLINT sHundred;
};


#endif

