#include "astroalgo.h"

/*******************************************************************************
*	NAME:
*		aeaster - Astronomical Easter
*		
*	PURPOSE:
*		Returns the Julian Day Easter occurs on as an astronomical event
*				
*	REFERENCES:
*		none
*		
*	INPUT ARGUMENTS:
*		year (int)
*			year to compute Easter in
*	
*	OUTPUT ARGUMENTS:
*	 	none
*	 
*	RETURNED VALUE:
*	 	Julian day (double) of Easter
*	 
*	GLOBALS USED:
*	 	none
*	 
*	FUNCTIONS CALLED:
*		julian2date, equinox_solstice, moonphase, day_of_week
*	 
*	DATE/PROGRAMMER/NOTE:
*	 	02-18-2001	Todd A. Guillory	started
*		02-20-2001	Todd A. Guillory	1981 and 2019 still wrong
*
*	Notes:
*		Easter is defined as the first Sunday AFTER the first full moon ON or AFTER
*		the Vernal Equinox, thus, it can ONLY occur in March or April, subtract
*		46 days from Easter to find Ash Wednesday.  Lent is 40 days + 6 Sundays
*
*	
*	
********************************************************************************/
double aeaster(int inyear)
{
	short		m;
	double		d;
	int			y;
	double		yd;
	double		moon;
	
	/* calculate the vernal equinox for the given year */
	double equinox = zero_hour_julian(equinox_solstice(inyear, 0));
	
	/* find the first full moon ON or AFTER the equinox */
	julian_to_date(equinox, &m, &d, &y);
	
	yd = y;
	
	moon = zero_hour_julian(moonphase(yd, fullmoon));
	
	while ( moon < equinox)
	{
		yd += 0.04;
		moon = zero_hour_julian(moonphase(yd, fullmoon));
	}
	
	/* find the first Sunday AFTER the full moon */
	moon++;
	while ( day_of_week(moon) != 0 )
	{
		moon++;
	}
		
	return moon;
}
