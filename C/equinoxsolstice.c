#include "astroalgo.h"
#include "astromath.h"

/* C Headers */
#include <math.h>

/* ---------------------------------------------------------------------------------
	NAME:
		EquinoxSolstice
		
	PURPOSE:
		Compute the Julian Day for the Equinox and Solstice
				
	REFERENCES:

			
	INPUT ARGUMENTS:
		inYear (double)
			year to compute event in
		inES (unsigned short)
			event: 0 march equinox, 1 june solstice, 2 september equinox, 3 december solstice
	
	OUTPUT ARGUMENTS:
	 	none
	 
	RETURNED VALUE:
	 	closest Julian Day event occurs
	 
	GLOBALS USED:
	 	none
	 
	FUNCTIONS CALLED:
		none
	 
	DATE/PROGRAMMER/NOTE:
	 	06-16-1998	Todd A. Guillory	created
	 	01-09-2001	Todd A. Guillory	added to astroalogo lib, lots needs to be fixed
	
----------------------------------------------------------------------------------*/
double equinox_solstice( double inYear, unsigned short inES )
{
	double	y,
			jden,		/* Julian Ephemeris Day */
			T,			/* Julian Centuries */
			W,
			lambda,
			S;			/* sum of periodic terms */
	  
	if ( inYear >= 1000 )
    {
    	y = (floor(inYear) - 2000)/1000;
    
    	if ( inES == 0 ) /* march equinox */
    		jden = 2451623.80984 + 365242.37404 * y + 0.05169 * (y * y) - 0.00411 * (y * y * y) - 0.00057 * (y * y * y * y);
    	else if ( inES == 1 ) /* june solstice */
    		jden = 2451716.56767 + 365241.62603 * y + 0.00325 * (y * y) - 0.00888 * (y * y * y) - 0.00030 * (y * y * y * y);
    	else if ( inES == 2 ) /* september equinox */
    		jden = 2451810.21715 + 365242.01767 * y + 0.11575 * (y * y) - 0.00337 * (y * y * y) - 0.00078 * (y * y * y * y);
    	else if ( inES == 3 ) /* december solstice */
    		jden = 2451900.05952 + 365242.74049 * y + 0.06223 * (y * y) - 0.00823 * (y * y * y) - 0.00032 * (y * y * y * y);
    	else
    		return -1;
    }
    else
    {
    	y = floor(inYear)/1000;
    
    	if ( inES == 0 ) /* march equinox */
    		jden = 1721139.29189 + 365242.13740 * y + 0.06134 * (y * y) - 0.00111 * (y * y * y) - 0.00071 * (y * y * y * y);
    	else if ( inES == 1 ) /* june solstice */
    		jden = 1721233.25401 + 365241.72562 * y + 0.05323 * (y * y) - 0.00907 * (y * y * y) - 0.00025 * (y * y * y * y);
    	else if ( inES == 2 ) /* september equinox */
    		jden = 1721325.70455 + 365242.49558 * y + 0.11677 * (y * y) - 0.00297 * (y * y * y) - 0.00074 * (y * y * y * y);
		else if ( inES == 3 ) /* december solstice */
			jden = 1721414.39987 + 365242.88257 * y + 0.00769 * (y * y) - 0.00933 * (y * y * y) - 0.00006 * (y * y * y * y);
		else
			return -1;
    }
    
    T = ( jden - 2451545.0 ) / 36525;
 
	W = 35999.373 * T - 2.47;
	
	lambda = 1 + 0.0334 * CosD(W) + 0.0007 * CosD(2*W);

	S = 485 * cos(kDegRad*324.96 + kDegRad*(  1934.136 * T))
			+ 203 * cos(kDegRad*337.23 + kDegRad*( 32964.467 * T))
			+ 199 * cos(kDegRad*342.08 + kDegRad*(    20.186 * T))
			+ 182 * cos(kDegRad* 27.85 + kDegRad*(445267.112 * T))
			+ 156 * cos(kDegRad* 73.14 + kDegRad*( 45036.886 * T))
			+ 136 * cos(kDegRad*171.52 + kDegRad*( 22518.443 * T))
			+  77 * cos(kDegRad*222.54 + kDegRad*( 65928.934 * T))
			+  74 * cos(kDegRad*296.72 + kDegRad*(  3034.906 * T))
			+  70 * cos(kDegRad*243.58 + kDegRad*(  9037.513 * T))
			+  58 * cos(kDegRad*119.81 + kDegRad*( 33718.147 * T))
			+  52 * cos(kDegRad*297.17 + kDegRad*(   150.678 * T))
			+  50 * cos(kDegRad* 21.02 + kDegRad*(  2281.226 * T))
			+  45 * cos(kDegRad*247.54 + kDegRad*( 29929.562 * T))
			+  44 * cos(kDegRad*325.15 + kDegRad*( 31555.956 * T))
			+  29 * cos(kDegRad* 60.93 + kDegRad*(  4443.417 * T))
			+  28 * cos(kDegRad*155.12 + kDegRad*( 67555.328 * T))
			+  17 * cos(kDegRad*288.79 + kDegRad*(  4562.452 * T))
			+  16 * cos(kDegRad*198.04 + kDegRad*( 62894.029 * T))
			+  14 * cos(kDegRad*199.76 + kDegRad*( 31436.921 * T))
			+  12 * cos(kDegRad* 95.39 + kDegRad*( 14577.848 * T))
			+  12 * cos(kDegRad*287.11 + kDegRad*( 31931.756 * T))
			+  12 * cos(kDegRad*320.81 + kDegRad*( 34777.259 * T))
			+   9 * cos(kDegRad*227.73 + kDegRad*(  1222.114 * T))
			+   8 * cos(kDegRad* 15.45 + kDegRad*( 16859.074 * T));
			
	return ( jden + (0.00001*S/lambda) );
  
  }
