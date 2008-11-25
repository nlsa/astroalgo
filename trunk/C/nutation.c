#include "astroalgo.h"
#include "astromath.h"


/* ---------------------------------------------------------------------------------
	NAME:
		Nutation
		
	PURPOSE:
		Computes the nutation of longitude and nutation of obliquity of the ecliptic
		
	REFERENCES;
		Meeus, Jean. "Astronomical Algorithms, 1st ed." Willmann-Bell. Inc. 1991.
			pp. 131-134
			
	INPUT ARGUMENTS:
		T (double)
			Julian Centuries
	
	OUTPUT ARGUMENTS:
	 	*deltaPsi (double)
	 		nutation of longitude in arc seconds
	 	*deltaEpsilon (double)
	 		nutation of obliquity in arc seconds
	 
	RETURNED VALUE:
	 	none yet
	 
	GLOBALS USED:
	 	none
	 
	FUNCTIONS CALLED:
	 	none
	 
	DATE/PROGRAMMER/NOTE:
		07-06-2000	Todd A. Guillory	created
		07-25-2000	Todd A. Guillory	added the 63 correction factors on pg 133-134
		07-25-2000	Todd A. Guillory	tested with example 21.a
	 	
	NOTES:
	
----------------------------------------------------------------------------------*/
void nutation( double T, double *deltaPsi, double *deltaEpsilon)
{
	double	D, 		/* longitude of the ascending node of the moon's mean orbit */
			m,		/* mean anomaly of the Sun (Earth) */
			mprime,	/* mean anomaly of the moon */
			F,		/* moon's argument of latitude */
			omega;	/* longitude of the ascending node of the moon's mean orbit */
	
	/* calculate the five local variables */
	D = 297.85036 + 445267.111480 * T - 0.0019142 * T * T + (T * T * T)/189474;

	m = 357.52772 + 35999.050340 * T - 0.0001603 * T * T - (T * T * T)/300000;
	
	mprime = 134.96298 + 477198.867398 * T + 0.0086972 * T * T + (T * T * T)/56250;
	
	F = 93.27191 + 483202.017538 * T - 0.0036825 * T * T + (T * T * T)/327270;

	omega = 125.04452 - 1934.136261 * T + 0.0020708 * T * T + (T * T * T)/450000;
	
	/* calculate nutation of longitude in arc seconds */
	*deltaPsi =		(-171996	- 174.2*T)	* SinD(omega)
				+	(-13187		- 1.6*T)	* SinD(-2*D + 2*F + 2*omega)
				+	(-2274		- 0.2*T)	* SinD(2*F + 2*omega)
				+	(2062		+ 0.2*T)	* SinD(2*omega)
				+	(1426		- 3.4*T)	* SinD(m)
				+	(712		+ 0.1*T)	* SinD(mprime)
				+	(-517		+ 1.2*T)	* SinD(-2*D + m + 2*F + 2*omega)
				+	(-386		- 0.4*T)	* SinD(2*F + omega)
				-	301						* SinD(mprime + 2*F + 2*omega)
				+	(217		- 0.5*T)	* SinD(-2*D - m + 2*F + 2*omega)
				-	158						* SinD(-2*D + mprime)
				+	(129		+ 0.1*T)	* SinD(-2*D + 2*F + omega)
				+	123						* SinD(-mprime + 2*F + 2*omega)
				+	63						* SinD(2*D)
				+	(63			+ 0.1*T)	* SinD(mprime + omega)
				-	59						* SinD(2*D - mprime + 2*F + 2*omega)
				+	(-58		- 0.1*T)	* SinD(-mprime + omega)
				-	51						* SinD(mprime + 2*F + omega)
				+	48						* SinD(-2*D + 2*mprime)
				+	46						* SinD(-2*mprime + 2*F + omega)
				-	38						* SinD(2*D + 2*F + 2*omega)
				-	31						* SinD(2*mprime + 2*F + 2*omega)
				+	29						* SinD(2*mprime)
				+	29						* SinD(-2*D + mprime + 2*F + 2*omega)
				+	26						* SinD(2*F)
				-	22						* SinD(-2*D + 2*F)
				+	21						* SinD(-mprime + 2*F + omega)
				+	(17			- 0.1*T)	* SinD(2*m)
				+	16						* SinD(2*D - mprime + omega)
				+	(-16		+ 0.1*T)	* SinD(-2*D + 2*m + 2*F + 2*omega)
				-	15						* SinD(m + omega)
				-	13						* SinD(-2*D + mprime + omega)
				-	12						* SinD(-m + omega)
				+	11						* SinD(2*mprime - 2*F)
				-	10						* SinD(2*D - mprime + 2*F + omega)
				-	8						* SinD(2*D + mprime + 2*F + 2*omega)
				+	7						* SinD(m + 2*F + 2*omega)
				-	7						* SinD(-2*D + m + mprime)
				-	7						* SinD(-m + 2*F + 2*omega)
				-	7						* SinD(2*D + 2*F + omega)
				+	6						* SinD(2*D + mprime)
				+	6						* SinD(-2*D + 2*mprime + 2*F + 2*omega)
				+	6						* SinD(-2*D + mprime + 2*F + omega)
				-	6						* SinD(2*D - 2*mprime + omega)
				-	6						* SinD(2*D + omega)
				+	5						* SinD(-m + mprime)
				-	5						* SinD(-2*D - m + 2*F + omega)
				-	5						* SinD(-2*D + omega)
				-	5						* SinD(2*mprime + 2*F + omega)
				+	4						* SinD(-2*D + 2*mprime + omega)
				+	4						* SinD(-2*D + m + 2*F + omega)
				+	4						* SinD(mprime - 2*F)
				-	4						* SinD(-D + mprime)
				-	4						* SinD(-2*D + m)
				-	4						* SinD(D)
				+	3						* SinD(mprime + 2*F)
				-	3						* SinD(-2*mprime + 2*F + 2*omega)
				-	3						* SinD(-D - m + mprime)
				-	3						* SinD(m + mprime)
				-	3						* SinD(-m + mprime + 2*F + 2*omega)
				-	3						* SinD(2*D - m -mprime + 2*F + 2*omega)
				-	3						* SinD(3*mprime + 2*F + 2*omega)
				-	3						* SinD(2*D - m + 2*F + 2*omega);
	
	/* calculate nutation of obliquity in arc seconds */
	*deltaEpsilon =	(92025		+ 8.9*T)	* CosD(omega)
				+	(5736		- 3.1*T)	* CosD(-2*D + 2*F + 2*omega)
				+	(977		- 0.5*T)	* CosD(2*F + 2*omega)
				+	(-895		+ 0.5*T)	* CosD(2*omega)
				+	(54			- 0.1*T)	* CosD(m)
				-	7						* CosD(mprime)
				+	(224		- 0.6*T)	* CosD(-2*D + m + 2*F + 2*omega)
				+	200						* CosD(2*F + omega)
				+	(129		- 0.1*T)	* CosD(mprime + 2*F + 2*omega)
				+	(-95		+ 0.3*T)	* CosD(-2*D - m + 2*F + 2*omega)
				-	70						* CosD(-2*D + 2*F + omega)
				-	53						* CosD(-mprime + 2*F + 2*omega)
				-	33						* CosD(mprime + omega)
				+	26						* CosD(2*D - mprime + 2*F + 2*omega)
				+	32						* CosD(-mprime + omega)
				+	27						* CosD(mprime + 2*F + omega)
				-	24						* CosD(-2*mprime + 2*F + omega)
				+	16						* CosD(2*D + 2*F + 2*omega)
				+	13						* CosD(2*mprime + 2*F + 2*omega)
				-	12						* CosD(-2*D + mprime + 2*F + 2*omega)
				-	10						* CosD(-mprime + 2*F + omega)
				-	8						* CosD(2*D - mprime + omega)
				+	7						* CosD(-2*D + 2*m + 2*F + 2*omega)
				+	9						* CosD(m + omega)
				+	7						* CosD(-2*D + mprime + omega)
				+	6						* CosD(-m + omega)
				+	5						* CosD(2*D - mprime + 2*F + omega)
				+	3						* CosD(2*D + mprime + 2*F + 2*omega)
				-	3						* CosD(m + 2*F + 2*omega)
				+	3						* CosD(-m + 2*F + 2*omega)
				+	3						* CosD(2*D + 2*F + omega)
				-	3						* CosD(-2*D + 2*mprime + 2*F + 2*omega)
				-	3						* CosD(-2*D + mprime + 2*F + omega)
				+	3						* CosD(2*D - 2*mprime + omega)
				+	3						* CosD(2*D + omega)
				+	3						* CosD(-2*D - m + 2*F + omega)
				+	3						* CosD(-2*D + omega)
				+	3						* CosD(2*mprime + 2*F + omega);	
	
	/* coefficients are in units of 0".0001 so convert */
	*deltaPsi *= 0.0001;			
	*deltaEpsilon *= 0.0001;
}