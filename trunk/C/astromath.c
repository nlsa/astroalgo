#include "astromath.h"

/* C Headers */
#include <math.h>

/*******************************************************************************
	NAME:
		SinD
		CosD
		TanD
		
	PURPOSE:
		Trigonometic functions that take input in degrees instead of radians
		
	REFERENCES:
		none
			
	INPUT ARGUMENTS:
		x (double)
			input angle in degrees
	
	OUTPUT ARGUMENTS:
	 	none
	 
	 RETURNED VALUE:
	 	trig value (double) in radians
	 
	 GLOBALS USED:
	 	none
	 
	 FUNCTIONS CALLED:
	 	sin, cos, tan
	 
	 DATE/PROGRAMMER/NOTE:
		7-06-2000	Todd A. Guillory	created

********************************************************************************/
double SinD(double x)
{
	return sin( x * kDegRad );
}

double CosD(double x)
{
	return cos( x * kDegRad );
}

double TanD(double x)
{
	return tan( x * kDegRad );
}

/*******************************************************************************
	NAME:
		Normalize0To1
		
	PURPOSE:
		Normalizes the input value to a value between 0 and 1.  See NOTES for examples.
		
	REFERENCES:
		none
			
	INPUT ARGUMENTS:
		x (double)
			value to normalize
	
	OUTPUT ARGUMENTS:
	 	none
	 
	 RETURNED VALUE:
	 	value between 0 and 1 (double)
	 
	 GLOBALS USED:
	 	none
	 
	 FUNCTIONS CALLED:
	 	fabs
	 
	DATE/PROGRAMMER/NOTE:
		1-15-2000	Todd A. Guillory	created
	 	
	NOTES:
		f(x) =	x + 1,	x < 0
				x,		0 <= x <= 1
				x - 1,	x > 1
				
		Examples:
			-0.65 -> 0.35
			-3.45 -> 0.65
			+1.25 -> 0.25
	
********************************************************************************/
double Normalize0To1(double x)
{
	while ( x < 0 || x > 1 )
		if ( x > 1 )
			--x;
		else
			++x;
	return x;
}

/*
double Normalize0To1(double x)
{
	while ( x < 0 || x > 1 )
		if ( x > 1 )
			--x;
		else
			x = 1 - fabs(x);
	return x;
}
*/

/*******************************************************************************
	NAME:
		Revolution
		
	PURPOSE:
		Normalizes the input angle to an equivalent positive angle between 0 and 360
		
	REFERENCES:
		none
			
	INPUT ARGUMENTS:
		theta (double)
			input angle in degrees
	
	OUTPUT ARGUMENTS:
	 	none
		
	 RETURNED VALUE:
	 	normalized angle (double) in degrees
	 
	 GLOBALS USED:
	 	none
	 
	 FUNCTIONS CALLED:
	 	fmod
	 
	 DATE/PROGRAMMER/NOTE:
	 	8-27-1998	Todd A. Guillory	created
		
********************************************************************************/
double Revolution(double theta)
{
	if ( theta >= 0 )
		return fmod(theta, 360.0);
	else
		return 360.0 + fmod(theta, 360.0);
}


/*******************************************************************************
	NAME:
		revolution_180
		
	PURPOSE:
		Normalizes the input angle to an equivalent angle between +180.0 and -180.0
		
	REFERENCES:
		none
			
	INPUT ARGUMENTS:
		theta (double)
			input angle in degrees
	
	OUTPUT ARGUMENTS:
	 	none
		
	 RETURNED VALUE:
	 	normalized angle (double) in degrees
	 
	 GLOBALS USED:
	 	none
	 
	 FUNCTIONS CALLED:
	 	fmod
	 
	 DATE/PROGRAMMER/NOTE:
	 	4-23-20001	Todd A. Guillory	created
		
********************************************************************************/
double revolution_180(double theta)
{
	while (theta < -180.0 || theta > 180.0)
	{
		theta = fmod(theta, 360.0);
		if ( theta > 180.0 )
			theta = theta - 360.0;
		else if ( theta < -180.0 )
			theta = theta + 360.0;
		else
			;
	}
		
	return theta;
}


/*******************************************************************************
	NAME:
		Fraction2Time
		
	PURPOSE:
		Converts the fractional part of the input to hours, minutes and seconds
		
	REFERENCES:
		none
			
	INPUT ARGUMENTS:
		x (double)
			input day
	
	OUTPUT ARGUMENTS:
	 	hour (short)
			hours
		minute (short)
			minutes
		seconds (double)
			seconds
	 
	 RETURNED VALUE:
	 	none
	 
	 GLOBALS USED:
	 	none
	 
	 FUNCTIONS CALLED:
	 	floor
	 
	 DATE/PROGRAMMER/NOTE:
		1-15-2000	Todd A. Guillory	created
	 	
	NOTES:
		Because rounding by the system using the floor function
		this function is not percise
	
********************************************************************************/
void Fraction2Time(double x, short *hour, short *minute, double *second)
{
	/* obtain the fractional part of the day */
	double	i = x - floor(x);
	
	/* calculate hours, minutes and seconds */
	*hour = (short) (i * 24);
	*minute = (short) ((i * 24 - *hour) * 60);
	*second = (((i * 24 - *hour) * 60 - *minute) * 60);
}


void Angle2Time(double x, short *degree, short *minute, double *second)
{
	/* calculate degrees, minutes and seconds */
	*degree = (short) (x / 15);
	*minute = (short) ((x/15 - floor(x/15)) * 60);
	*second = (((x/15 - floor(x/15)) * 60) - floor((x/15 - floor(x/15)) * 60)) * 60;
}


