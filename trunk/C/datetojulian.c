#include "astroalgo.h"

#include <math.h>

/*******************************************************************************
	NAME:
		date_to_julian
		
	PURPOSE:
		Computes the Julian Day
		
	REFERENCES;
		Meeus, Jean. "Astronomical Algorithms, 1st ed." Willmann-Bell. Inc. 1991.
			pp. 59-61
			
	INPUT ARGUMENTS:
		inMonth (short)
			month
		inDay (double)
	 		day
	 	inYear (int)
	 		year
	
	OUTPUT ARGUMENTS:
	 	*JD (double)
	 		Julian Day
	 
	RETURNED VALUE:
	 	0 if input date is 10/5/1582 - 10/14/1582
	 	1 if input date is valid
	 
	FUNCTIONS CALLED:
	 	none
	 
	DATE/PROGRAMMER/NOTES:
		10-15-1998	Todd A. Guillory	created
	 	
	NOTES:
		you have to test if the input date is a valid date to begin with
	
********************************************************************************/
int date_to_julian(short inMonth, double inDay, int inYear, double *JD)
{
	double		A,B;
	short		theMonth = inMonth;
	int			theYear = inYear;
  
	if ( inMonth <= 2 )
		{ --theYear;  theMonth += 12;  }
   
	A = floor(theYear/100);
  
	if ( inYear < 1582 )
		B = 0;
	else if (inYear > 1582 )
		B = 2 - A + floor(A/4);
	else
    {
		if ( inMonth < 10 )
			B = 0;
		else if ( inMonth > 10 )
			B = 2 - A + floor(A/4);
		else
		{
			if ( inDay < 5 )
				B = 0;
			else if ( inDay >= 15 )
				B = 2 - A + floor(A/4);
			else
				{ return 0; } /* error, days falls on 10/5/1582 - 10/14/1582 */
		} /* end middle else */   
	} /* end outer else */
  
  *JD = ( floor(365.25 * (theYear + 4716)) + floor(30.6001 * (theMonth + 1 )) + inDay + B - 1524.5 );
  
  return 1;
}
