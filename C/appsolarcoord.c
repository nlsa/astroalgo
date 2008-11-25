#include "astroalgo.h"
#include "astromath.h"

/* C Headers */
#include <math.h>

/*******************************************************************************
*	NAME:
*		AppSolarCoordinates
*		
*	PURPOSE:
*		Computes the apparent coordinates of the sun
*		
*	REFERENCES;
*		Meeus, Jean. "Astronomical Algorithms, 1st ed." Willmann-Bell. Inc. 1991.
*			pp. 151-153
*			
*	INPUT ARGUMENTS:
*		JD (double)
*			Julian Day for day/time to calculate  at TD
*	
*	OUTPUT ARGUMENTS:
*	 	*alpha (double)
*	 		apparent right ascention in degrees
*	 	*delta (double)
*	 		apparent declination in degrees
*	 
*	RETURNED VALUE:
*	 	none yet
*	 
*	GLOBALS USED:
*	 	none
*	 
*	FUNCTIONS CALLED:
*	 	SinD, CosD, Revolution, atan2
*	 
*	DATE/PROGRAMMER/NOTE:
*	 	09-16-1999	Todd A. Guillory	created
*	 	07-04-2000	Todd A. Guillory	condensed equations some more
*	 	07-27-2000	Todd A. Guillory	checked with example 24.a
*
********************************************************************************/
void app_solar_coordinates( double JD, double *alpha, double *delta)
{
	double	T,		/* Julian Centuries */
			L0,		/* geometric mean longitude of the sun */
			M,		/* mean anomoly */
			e,		/* eccentricity of Earth's orbit */
			C,		/* Sun's equation of center */
			Long,	/* true longitude of the sun */
			v,		/* true anomaly of the sun */
			R,		/* Radius in AU */
			omega,	/* nutation */
			lamda,	/* apparent longitude of the sun */
			ep0;	/* mean obliquity of the ecliptic */

	/* Get Julian Centuries */
	T = julian_centuries(JD);
	
	/* calculate the geometric mean longitude of the sun */
	L0 = 280.46645 + 36000.76983 * T + 0.0003032 * T * T;
	
	/* calculate the mean anomaly of the sun */
	M = 357.52910 + 35999.05030 * T - 0.0001559 * T * T - 0.00000048 * T * T * T;
	
	/* calculate the eccentricity of the Earth's Orbit */
	e = 0.016708617 - 0.000042037 * T - 0.0000001236 * T * T;
	
	/* calculate the sun's equation of center */
	C = (1.914600 - 0.004817 * T - 0.000014 * T * T) * SinD(M)
		+ (0.019993 - 0.000101 * T) * SinD(2*M)
		+ 0.000290 * SinD(3*M);
	
	/* calculate the sun's true longitude */	
	Long = L0 + C;
	
	/* calculate the true anomaly */
	v = M + C;
	
	/* calculate the sun's radius vector, distance of the earth in AUs */
	R = (1.000001018 * ( 1 - e * e)) / ( 1 + e * CosD(v) );
	
	omega = 125.04 - 1934.136 * T;
	
	/* calculate the apparent longitude of the sun */
	lamda = Revolution(Long - 0.00569 - 0.00478 * SinD(omega));
	
	/* calculate the mean obliquity of the ecliptic */
	ep0 = ((23*60)+26)*60+21.448 - 46.8150 * T - 0.00059 * T * T + 0.001813 * T * T * T;
	ep0 /= 3600;
	
	/* correct mean obliquity of the ecliptic */
	ep0 = ep0 + 0.00256 * CosD(omega);

	/* calculate right ascension and declination */
	*alpha = Revolution(atan2(CosD(ep0) * SinD(lamda), CosD(lamda)) * kRadDeg);
	*delta = asin(SinD(ep0) * SinD(lamda)) * kRadDeg;
}
