#include "astroalgo.h"

/* C Headers */
#include <math.h>

/* ---------------------------------------------------------------------------------
	NAME:
		Julian2Date
		
	PURPOSE:
		Converts a Julian Day to a Gregorian month, day and year
		
	REFERENCES;
		Meeus, Jean. "Astronomical Algorithms, 1st ed." Willmann-Bell. Inc. 1991.
			pp. 63
			
	INPUT ARGUMENTS:
		JD (double)
			input Julian Day

	OUTPUT ARGUMENTS:
	 	*month (short)
	 		Julian Day
	 	*day (double)
	 		day
	 	*year (int)
	 		year
	 
	RETURNED VALUE:
	 	0 if error occured in calculation
	 	1 if no error
	 
	GLOBALS USED:
	 	none
	 
	FUNCTIONS CALLED:
	 	floor
	 
	DATE/PROGRAMMER/NOTES:
		10-15-1998	Todd A. Guillory	created
	 	
	NOTES:
		does not work for negative Julian Day values but does work for negative years
	
----------------------------------------------------------------------------------*/
int julian_to_date(double JD, short* month, double* day, int* year)
{
	double		A,B,C,D,E,F,J,Z;
	double		alpha;

	J = JD + 0.5;

	Z = floor(J);

	F = J - Z;

	if ( Z >= 2299161 )
	{
		alpha = floor( (Z - 1867216.25)/36524.25 );
		A = Z + 1 + alpha - floor(alpha/4);
	}
	else
		A = Z;

	B = A + 1524;

	C = floor( (B - 122.1)/365.25 );

	D = floor( 365.25 * C );

	E = floor( (B - D)/30.6001 );
	
	*day = B - D - floor(30.6001 * E) + F;

	if ( E < 14 )
		*month = (short)(E - 1.0);
	else if ( E == 14 || E == 15 )
		*month = (short)(E - 13.0);
	else
		return 0; /* error */
  
	if ( *month > 2 )
		*year = (int)(C - 4716.0);
	else if ( *month == 1 || *month == 2 )
		*year = (int)(C - 4715.0);
    else
    	return 0; /* error */
    
    return 1;
}



