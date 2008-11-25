#include "astroalgo.h"
#include "astromath.h"

/* ---------------------------------------------------------------------------------
	NAME:
		MeanSiderealTime
		
	PURPOSE:
		Computes the mean sidereal time, the Greenwich hour angle of the mean
		vernal point (the intersection of the ecliptic of the date with the mean
		equator of the date), for any instant UT NOT just 0 hour UT.
		
	REFERENCES;
		Meeus, Jean. "Astronomical Algorithms, 1st ed." Willmann-Bell. Inc. 1991.
			pp. 83
			
	INPUT ARGUMENTS:
		JD (double)
			Julian Day at any instant UT
	
	OUTPUT ARGUMENTS:
	 	none
	 
	RETURNED VALUE:
	 	mean sidereal time at the meridian of Greenwich (double) in degrees
	 
	GLOBALS USED:
	 	none
	 
	FUNCTIONS CALLED:
		Revolution
	 
	DATE/PROGRAMMER/NOTE:
	 	09-16-1999	Todd A. Guillory	created
	 	07-05-2000	Todd A. Guillory	reduced code some
	 	07-05-2000	Todd A. Guillory	correct results with example 11.a and 11.b
	 	
	NOTES:
	
----------------------------------------------------------------------------------*/
double mean_sidereal_time(double JD)
{
	double T = julian_centuries(JD);
	
	return Revolution(280.46061837 + 360.98564736629 * (JD - 2451545.0) + 0.000387933 * T * T - (T * T * T)/38710000.0);
}

/* ---------------------------------------------------------------------------------
	NAME:
		AppSiderealTime
		
	PURPOSE:
		Computes the apparent sidereal time at Greenwich, or the Greenwich hour angle
		of the true vernal equinox
		
	REFERENCES;
		Meeus, Jean. "Astronomical Algorithms, 1st ed." Willmann-Bell. Inc. 1991.
			pp. 83-84
			
	INPUT ARGUMENTS:
		JD (double)
			Julian Day at any instant UT
	
	OUTPUT ARGUMENTS:
	 	none
	 
	RETURNED VALUE:
	 	apparent sidereal time at the meridian of Greenwich (double) in degrees
	 
	GLOBALS USED:
	 	none
	 
	FUNCTIONS CALLED:
		Nutation
		Obliquity
	 
	DATE/PROGRAMMER:
	 	07-17-2000	Todd A. Guillory	created
	 	07-26-2000	Todd A. Guillory	correct results with example 11.a
	 	
	NOTES:
		
----------------------------------------------------------------------------------*/
double app_sidereal_time(double JD)
{
	double	deltaPsi,		/* nutation in longitude */
			deltaEpsilon,	/* nutation of obliquity */
			epsilon,		/* true obliquity of the ecliptic */
			epsilonNull;	/* mean obliquity of the ecliptic */
	
	nutation(julian_centuries(JD), &deltaPsi, &deltaEpsilon);
	obliquity(julian_centuries(JD), &epsilon, &epsilonNull);
	
	return mean_sidereal_time(JD) + deltaPsi / 15.0 * CosD(epsilon) / 240.0;
}
