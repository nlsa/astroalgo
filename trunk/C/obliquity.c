#include "astroalgo.h"

/* ---------------------------------------------------------------------------------
	NAME:
		Obliquity
		
	PURPOSE:
		Computes the mean and true obliquity of the ecliptic
		
	REFERENCES;
		Meeus, Jean. "Astronomical Algorithms, 1st ed." Willmann-Bell. Inc. 1991.
			pp. 135-136
			
	INPUT ARGUMENTS:
		T (double)
			Julian Centuries
	
	OUTPUT ARGUMENTS:
	 	*epsilon (double)
	 		true obliquity of the ecliptic in degrees
	 	*epsilonNull (double)
	 		mean obliquity of the ecliptic in arc seconds
	 
	RETURNED VALUE:
	 	none yet
	 
	GLOBALS USED:
	 	none
	 
	FUNCTIONS CALLED:
	 	Nutation
	 
	DATE/PROGRAMMER/NOTE:
		07-06-2000	Todd A. Guillory	created
		07-25-2000	Todd A. Guillory	made into separate file and changed output variables
	 	
	NOTES:
	
----------------------------------------------------------------------------------*/
void obliquity( double T, double *epsilon, double *epsilonNull)
{
	double	deltaPsi,		/* nutation of longitude in arc seconds */
			deltaEpsilon;	/* nutation of obliquity */
	
	/* calculate mean obliquity of the ecliptic */
	*epsilonNull = ((23 * 60) + 26) * 60 + 21.448 - 46.8150 * T - 0.00059 * T * T + 0.001813 * T * T * T;
	*epsilonNull /= 3600;
	
	/* calculate nutation of obliquity */
	nutation(T, &deltaPsi, &deltaEpsilon);
	
	/* calculate true obliquity of the ecliptic */
	*epsilon = *epsilonNull + deltaEpsilon / 3600;
}