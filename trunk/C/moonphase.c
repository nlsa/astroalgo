#include "astroalgo.h"
#include "astromath.h"

/* C Headers */
#include <math.h>

/* ---------------------------------------------------------------------------------
	NAME:
		Moonphase
		
	PURPOSE:
		Calculate Julian Day a given input phase occurs on
				
	REFERENCES:
		Meeus, Jean. "Astronomical Algorithms, 1st ed." Willmann-Bell. Inc. 1991.
			pg. 319 - 324
			
	INPUT ARGUMENTS:
		year (double)
			year to compute phase on, day and time are fractions of the year
		phase (float)
			phase to compute: 0 new, 0.25 first quarter, 0.5 full, 0.75 last quarter
	
	OUTPUT ARGUMENTS:
	 	none
	 
	RETURNED VALUE:
	 	Julian Day (double) that phase occurs on closest to the input day
	 
	GLOBALS USED:
	 	none
	 
	FUNCTIONS CALLED:
		none
	 
	DATE/PROGRAMMER/NOTE:
	 	06-16-1998	Todd A. Guillory	created
	 	01-09-2001	Todd A. Guillory	added to astroalogo lib, lots needs to be fixed
	 	02-17-2001	Todd A. Guillory	corrected error in a[14] resulting from indexing at 1 instead of 0
	
----------------------------------------------------------------------------------*/
double moonphase(double year, Moonphases phase)
{
	double	k = 0;
	double	t = 0;				/* time in Julian centuries */
	double	m = 0;				/* Sun's mean anomaly */
	double	mprime = 0;			/* Moon's mean anomaly */
	double	f = 0;				/* Moon's argument of latitude */
	double	omega = 0;			/* Longitude of the ascending node of the lunar orbit */
	double	w = 0;				/* quarter phase corrections */
	double	a[14] = {0};		/* planatary arguments */
	double	atotal = 0;			/* sum of planatary arguments */
	double	corrections = 0;	/* sum of corrections */
	double	e = 0;				/* eccentricity of Earth's orbit */
	
	k = floor((year - 2000.0) * 12.3685) + ((double)phase * 0.25);
	
	t = (k/1236.85);
	
	e = 1.0 - t * ( 0.002516 - ( 0.0000074 * t)); /* pg 308 */
	
	m = kDegRad * (2.5534 + (29.10535669 * k) - t * t * ( 0.0000218  - (0.00000011 * t )));
	
	mprime = kDegRad * (201.5643 + (385.81693528 * k) + t * t * ( 0.0107438 + (0.00001239 * t) - (0.000000058 * t * t)));
	
	f = kDegRad * (160.7108 + (390.67050274 * k) + t * t * ( 0.0016341  + (0.00000227 * t) - (0.000000011 * t * t)));
	
	omega = kDegRad * (124.7746 - (1.56375580 * k) + t * t * ( 0.0020691 + (0.00000215 * t)));
	
	a[0] =  kDegRad * (299.77 + (0.107408  * k) - (0.009173 * t * t));
	a[1] =  kDegRad * (251.88 + (0.016321  * k));
	a[2] =  kDegRad * (251.83 + (26.651886 * k));
	a[3] =  kDegRad * (349.42 + (36.412478 * k));
	a[4] =  kDegRad * (84.66  + (18.206239 * k));
	a[5] =  kDegRad * (141.74 + (53.303771 * k));
	a[6] =  kDegRad * (207.14 + (2.453732  * k));
	a[7] =  kDegRad * (154.84 + (7.306860  * k));
	a[8] =  kDegRad * (34.52  + (27.261239 * k));
	a[9] = kDegRad * (207.19 + (0.121824  * k));
	a[10] = kDegRad * (291.34 + (1.844379  * k));
	a[11] = kDegRad * (161.72 + (24.198154 * k));
	a[12] = kDegRad * (239.56 + (25.513099 * k));
	a[13] = kDegRad * (331.55 + (3.592518  * k));
	
	atotal = .000001 * ((325 * sin(a[0])) 
				+  (165 * sin(a[1])) 
				+  (164 * sin(a[2])) 
				+  (126 * sin(a[3])) 
				+  (110 * sin(a[4])) 
				+  ( 62 * sin(a[5])) 
				+  ( 60 * sin(a[6])) 
				+  ( 56 * sin(a[7])) 
				+  ( 47 * sin(a[8])) 
				+  ( 42 * sin(a[9])) 
				+  ( 40 * sin(a[10])) 
				+  ( 37 * sin(a[11])) 
				+  ( 35 * sin(a[12])) 
				+  ( 23 * sin(a[13])));
	
	switch (phase)
	{	
		case (newmoon):
		{
			corrections = - (0.40720 *		sin(mprime)) 
						+ (0.17241 * e *	sin(m)) 
						+ (0.01608 *		sin(2*mprime)) 
						+ (0.01039 *		sin(2 * f)) 
						+ (0.00739 * e *      sin(mprime - m)) 
						- (0.00514 * e *      sin(mprime + m)) 
						+ (0.00208 * e * e *  sin(2 * m)) 
						- (0.00111 *          sin(mprime - 2 * f)) 
						- (0.00057 *          sin(mprime + 2 * f)) 
						+ (0.00056 * e *      sin(2 * mprime + m)) 
						- (0.00042 *          sin(3 * mprime)) 
						+ (0.00042 * e *      sin(m + 2 * f)) 
						+ (0.00038 * e *      sin(m - 2 * f)) 
						- (0.00024 * e *      sin(2 * mprime - m)) 
						- (0.00017 *          sin(omega)) 
						- (0.00007 *          sin(mprime + 2 * m)) 
						+ (0.00004 *          sin(2 * mprime - 2 * f)) 
						+ (0.00004 *          sin(3 * m)) 
						+ (0.00003 *          sin(mprime + m - 2 * f)) 
						+ (0.00003 *          sin(2 * mprime + 2 * f)) 
						- (0.00003 *          sin(mprime + m + 2 * f)) 
						+ (0.00003 *          sin(mprime - m + 2 * f)) 
						- (0.00002 *          sin(mprime - m - 2 * f)) 
						- (0.00002 *          sin(3 * mprime + m)) 
						+ (0.00002 *          sin(4 * mprime));
			break;
		}

    case (fullmoon) :
    	{
  		corrections = - (0.40614 *         sin(mprime)) 
                  + (0.17302 * e *     sin(m)) 
                  + (0.01614 *         sin(2*mprime)) 
                  + (0.01043 *         sin(2 * f)) 
                  + (0.00734 * e *     sin(mprime - m)) 
                  - (0.00515 * e *     sin(mprime + m)) 
                  + (0.00209 * e * e * sin(2 * m)) 
                  - (0.00111 *         sin(mprime - 2 * f)) 
                  - (0.00057 *         sin(mprime + 2 * f)) 
                  + (0.00056 * e *     sin(2 * mprime + m)) 
                  - (0.00042 *         sin(3 * mprime)) 
                  + (0.00042 * e *     sin(m + 2 * f)) 
                  + (0.00038 * e *     sin(m - 2 * f)) 
                  - (0.00024 * e *     sin(2 * mprime - m)) 
                  - (0.00017 *         sin(omega)) 
                  - (0.00007 *         sin(mprime + 2 * m)) 
                  + (0.00004 *         sin(2 * mprime - 2 * f)) 
                  + (0.00004 *         sin(3 * m)) 
                  + (0.00003 *         sin(mprime + m - 2 * f)) 
                  + (0.00003 *         sin(2 * mprime + 2 * f)) 
                  - (0.00003 *         sin(mprime + m + 2 * f)) 
                  + (0.00003 *         sin(mprime - m + 2 * f)) 
                  - (0.00002 *         sin(mprime - m - 2 * f)) 
                  - (0.00002 *         sin(3 * mprime + m)) 
                  + (0.00002 *         sin(4 * mprime));
  			break;
  		}
  
  	case (firstquarter):
  	case (lastquarter):
  	{
  		corrections = - (0.62801 *         sin(mprime)) 
                  + (0.17172 * e *     sin(m)) 
                  - (0.01183 * e *     sin(mprime + m)) 
                  + (0.00862 *         sin(2 * mprime)) 
                  + (0.00804 *         sin(2 * f)) 
                  + (0.00454 * e *     sin(mprime - m)) 
                  + (0.00204 * e * e * sin(2 * m)) 
                  - (0.00180 *         sin(mprime - 2 * f)) 
                  - (0.00070 *         sin(mprime + 2 * f)) 
                  - (0.00040 *         sin(3 * mprime)) 
                  - (0.00034 * e *     sin(2 * mprime - m)) 
                  + (0.00032 * e *     sin(m + 2 * f)) 
                  + (0.00032 * e *     sin(m - 2 * f)) 
                  - (0.00028 * e * e * sin(mprime + 2 * m)) 
                  + (0.00027 * e *     sin(2 * mprime + m)) 
                  - (0.00017 *         sin(omega)) 
                  - (0.00005 *         sin(mprime - m - 2 * f)) 
                  + (0.00004 *         sin(2 * mprime + 2 * f)) 
                  - (0.00004 *         sin(mprime + m + 2 * f)) 
                  + (0.00004 *         sin(mprime - 2 * m)) 
                  + (0.00003 *         sin(mprime + m - 2 * f)) 
                  + (0.00003 *         sin(3 * m)) 
                  + (0.00002 *         sin(2 * mprime - 2 * f)) 
                  + (0.00002 *         sin(mprime - m + 2 * f)) 
                  - (0.00002 *         sin(3 * mprime + m));
                 
            w = .00306 - .00038 * e * cos(m) + .00026 * cos(mprime) - .00002 * cos(mprime - m) + .00002 * cos(mprime + m) + .00002 * cos(2*f);

  			if ( phase == lastquarter )
  				w = -w;
  		break;
  	}
	
	default:
		return -1.0;
	}   
   
  
  return(2451550.09765 + (29.530588853 * k) + (0.0001337 * pow(t,2)) - (0.000000150 * pow(t,3)) + (0.00000000073 * pow(t,4))  + corrections + atotal + w);
  
}
