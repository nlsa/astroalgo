#include "astroalgo.h"
#include "astromath.h"

/* C Headers */
#include <math.h>

/*******************************************************************************
	NAME:
		AzimuthAltitude
		
	PURPOSE:
		Computes the azimuth and altitude
		
	REFERENCES;
		Meeus, Jean. "Astronomical Algorithms, 1st ed." Willmann-Bell. Inc. 1991.
			pp. 87-90
			
	INPUT ARGUMENTS:
		JD (double)
			Julian Day for day/time to calculate at UT
		alpha (double)
	 		apparent right ascention in degrees
	 	delta (double)
	 		apparent declination in degrees
		L (double)
			longitude in degrees
		phi (double)
			latitude in degrees
	
	OUTPUT ARGUMENTS:
	 	*A (double)
	 		azimuth in degrees west of south
	 	*h (double)
	 		altitude in degrees
	 
	RETURNED VALUE:
	 	none yet
	 
	GLOBALS USED:
	 	none
	 
	FUNCTIONS CALLED:
	 	AppSiderealTime, Revolution, atan2, asin
	 
	DATE/PROGRAMMER/NOTE:
		07-05-2000	Todd A. Guillory	created, minor inaccuracy due to not calculating apparent sidereal time
	
********************************************************************************/
void azimuth_altitude( double JD, double alpha, double delta, double L, double phi, double *A, double *h)
{
	double	theta0,	/* apparent sidereal time at Greenwich*/
			H;		/* local hour angle */
				
	theta0 = app_sidereal_time(JD);
	
	/* calculate local hour angle */
	/* normalize the hour angle to +0 to +360 degrees */
	H = Revolution(theta0 - L - alpha);
	
	/* calculate azimuth */
	*A = atan2( SinD(H), (CosD(H) * SinD(phi) - TanD(delta) * CosD(phi)) ) * kRadDeg;
	
	/* calculate altitude */
	*h = asin( SinD(phi) * SinD(delta) + CosD(phi) * CosD(delta) * CosD(H) ) * kRadDeg;
}
