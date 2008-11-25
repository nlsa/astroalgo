#include "astroalgo.h"
#include "astromath.h"

/* C Headers */
#include <math.h>

/* ---------------------------------------------------------------------------------
	NAME:
		RiseTranSet
		
	PURPOSE:
		Computes the rising, setting and transit time of a body
		
	REFERENCES;
		Meeus, Jean. "Astronomical Algorithms, 1st ed." Willmann-Bell. Inc. 1991.
			pp. 97-99
			
	INPUT ARGUMENTS:
		L (double)
			longitude in degrees
		phi (double)
			latitude in degrees
		h0 (double)
			standard altitude of the body at time of rising and setting
				sun = -0.8333
				stars & planets = -0.5667
				moon (mean value ONLY) = +0.125
		JD (double)
			Julian Day for day/time to calculate at 0 hour UT
		A[] (double)
	 		apparent right ascention in degrees at JD-1, JD and JD+1 respectively at 0 hour Dynamical Time
	 	D[] (double)
	 		apparent declination in degrees at JD-1, JD and JD+1 respectively at 0 hour Dynamical Time
		
	OUTPUT ARGUMENTS:
	 	m[] (double)
	 		transit, rising, setting time respectively of object
	 			 
	RETURNED VALUE:
	 	0	error if the body is up all day or below the horizon all day
	 	1	no error
	 
	GLOBALS USED:
	 	none
	 
	FUNCTIONS CALLED:
	 	MeanSiderealTime
	 	Normalize0To1
	 	fabs
	 
	DATE/NOTE:
		01-19-2000	created
		04-23-2001	added interpolation using JD-1, JD, JD+1
	 	
	NOTES:
		Still need to calculate deltaT
		minor error starting at interpolated theta values
		off from Heavens Above by +/- 1 minute
		
----------------------------------------------------------------------------------*/
int rise_tran_set(double L, double phi, double h0, double JD, double A[], double D[], double m[])
{
	double	theta0;			/* apparent sidereal time */
	double	H0;				/* approximate time */
	double	theta[3];		/* array of sidereal times, transit, rising, setting  */
	double	n[3];			/* interpolating factor, transit, rising, setting */
	double	alpha[3];		/* right ascention correction factor */
	double	gamma[3];		/* declination correction factor */
	double	H[3];			/* local hour angle */
	double	h[3];			/* altitude */
	double	deltaT;			/* TD - UT */

	
	short	i = 0;			/* interpolation iterator */
	
	/* set deltaT to 0 for now */
	deltaT = 0;
	/* deltaT = 56.0; */
	
	/* get apparent sidereal time at greenwich at 0 hour Universal Time on JD */
	theta0 = app_sidereal_time(JD);
	/* theta0 = 177.74208; */
	
	/* Make sure the body is not above or below the horizon all day */
	/* if so, return 0 as an error bit */
	if ( fabs(-SinD(phi) * SinD(D[1]) / CosD(phi) * CosD(D[1])) > 1 )
		return 0;
	
	/* Calculate approximate times, 14.1 */
	H0 = acos((SinD(h0) - SinD(phi) * SinD(D[1])) / (CosD(phi) * CosD(D[1]))) * kRadDeg;
	
	/* calculate transit time */
	m[0] = Normalize0To1( (A[1] + L - theta0) / 360.0 );
		
	/* calculate rise and set time */
	m[1] = Normalize0To1(m[0] - H0 / 360.0);
	m[2] = Normalize0To1(m[0] + H0 / 360.0);
	
	for ( i = 0; i < 3; ++i)
	{
		/* compute the sidereal time */
		theta[i] = theta0 + 360.985647 * m[i];
		theta[i] = Revolution(theta[i]);
		
		/* compute interpolating factor */
		n[i] = m[i] + (deltaT / 86400.0);
		
		/* interpolate alpha and gamma from input, 3.3 */
		alpha[i] = A[1] + (n[i]/2.0) * ( - A[0] + A[2] + n[i]*(A[2] - A[1] - A[1] + A[0]) );
		gamma[i] = D[1] + (n[i]/2.0) * ( - D[0] + D[2] + n[i]*(D[2] - D[1] - D[1] + D[0]) );
		
		/* calculate local hour angle */
		H[i] = revolution_180(theta[i] - L - alpha[i]);
		
		/* calculate altitude, 12.6 */
		h[i] = asin( SinD(phi) * SinD(gamma[i]) + CosD(phi) * CosD(gamma[i]) * CosD(H[i]) ) * kRadDeg;
	}
	
	/* make corrections */
	m[0] = m[0] + ( - H[0] / 360.0 );
	m[1] = m[1] + (h[1] - h0) / (360 * cos(gamma[1]) * cos(phi) * sin(H[1]));
	m[2] = m[2] + (h[2] - h0) / (360 * cos(gamma[2]) * cos(phi) * sin(H[2]));
	
	/* print results
	printf("theta0 = %f\n", theta0);
	printf("H0 = %f\n", H0);
	printf("theta = %f %f %f\n", theta[0], theta[1], theta[2]);
	printf("n = %f %f %f\n", n[0], n[1], n[2]);
	printf("alpha = %f %f %f\n", alpha[0], alpha[1], alpha[2]);
	printf("gamma = %f %f %f\n", gamma[0], gamma[1], gamma[2]);
	printf("H = %f %f %f\n", H[0], H[1], H[2]);
	printf("h = %f %f %f\n", h[0], h[1], h[2]);
	printf("m = %f %f %f\n", m[0], m[1], m[2]);
	*/

	return 1;
}










