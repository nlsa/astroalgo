#include "astroalgo.h"
#include "astromath.h"
#include "astroconst.h"

/* C Headers */
#include <math.h>
#include <stdlib.h>

/*******************************************************************************
*	AstroAlgo
*
*	Universal Time (UT) -> Julian Day (JD)
*	UT is also Greenwich Civil Time based on the rotation of the Earth
*	Dynamical TIme (TD)	-> Julian Day Ephemeris (JDe)
*	TD is uniform based on atomic clocks
*	DeltaT = TD - UT
*
********************************************************************************/

/*	Last Update		2001-Jul-31                                                */
#define ASTROALGO_LIB_VERSION		0x0101
static const char* astroalgo_lib_version = "AstroAlgo Library, 1.0.1, copyright 2002 Todd A. Guillory";

const char* aa_version(void)
{
	return astroalgo_lib_version;
}

/*******************************************************************************
	NAME:
		day_of_week_name
		
	PURPOSE:
		Returns the week day name label encoded in the header file
		
	REFERENCES:
		Latham, Lance. "Standard C Date/Time Library: Programming the World Calendars and Clocks."
		R&D Books. 1998. pp. 77.
			
	INPUT ARGUMENTS:
		d (DOWi) index value

	OUTPUT ARGUMENTS:
		none
	 
	RETURNED VALUE:
		day of week name (const char*)
	 
	FUNCTIONS CALLED:
		none
	 	
	DATE/PROGRAMMER/NOTE:
		2002-04-20	Todd A. Guillory	added
********************************************************************************/
const char* day_of_week_name(DOWi i)
{
	if ( i < 0 || i > 6 )
		return NULL;

   return daylabels[i];
}

const char* month_name(unsigned short m)
{
	if ( m > 11 )
		return NULL;

   return monthlabels[m];
}

short days_in_month(unsigned short m)
{
	if ( m > 11 )
		return 0;

   return maxdays[m];
}

/*******************************************************************************
*	NAME:
*		JulianCenturies
*		
*	PURPOSE:
*		Return Julian Centuries
*		
*	REFERENCES:
*		Meeus, Jean. "Astronomical Algorithms, 1st ed." Willmann-Bell. Inc. 1991.
*			pp. 131
*			
*	INPUT ARGUMENTS:
*		JDe (double)
*			Julian Day Ephemeris
*	
*	OUTPUT ARGUMENTS:
*	 	none
*	 
*	RETURNED VALUE:
*	 	Julian Centuries (double) from the Epoch J2000.0 (JDe 2451545.0)
*	 
*	GLOBALS USED:
*	 	none
*	 
*	FUNCTIONS CALLED:
*		none
*	 
*	DATE/PROGRAMMER/NOTE:
*		09-16-1999	Todd A. Guillory	created
*	 	
********************************************************************************/
double julian_centuries(double JDe)
{
	return ( JDe - 2451545.0 ) / 36525.0;
}


/*******************************************************************************
*	NAME:
*		ZeroHourJulian
*		
*	PURPOSE:
*		Returns the JD value at 0 hour (midnight) of the given input Julian Day
*		
*	REFERENCES:
*		none
*			
*	INPUT ARGUMENTS:
*		JD (double)
*			Julian Day for day to calculate
*	
*	OUTPUT ARGUMENTS:
*	 	none
*	 
*	RETURNED VALUE:
*	 	Julian Day value (double) at midnight of the input day
*	 
*	GLOBALS USED:
*	 	none
*	 
*	FUNCTIONS CALLED:
*	 	floor
*	 
*	DATE/PROGRAMMER/NOTE:
*		09-16-1999	Todd A. Guillory	created
*	 	
*	NOTES:
*		This function is usful for some AstroAlgo functions such as RiseSetTrans
*	
********************************************************************************/
double zero_hour_julian(double JD)
{
	return floor(JD - 0.5) + 0.5;
}


/*******************************************************************************
*	NAME:
*		leap_year
*		
*	PURPOSE:
*		Return the number of days in February for the given input year
*		
*	REFERENCES:
*		none
*			
*	INPUT ARGUMENTS:
*		y (int)
*			input year
*	
*	OUTPUT ARGUMENTS:
*	 	none
*	 
*	RETURNED VALUE:
*	 	number of days in February in the input year
*	 
*	GLOBALS USED:
*	 	none
*	 
*	FUNCTIONS CALLED:
*	 	none
*	 
*	DATE/PROGRAMMER/NOTE:
*		02-16-1998	Todd A. Guillory	created
*			
********************************************************************************/
int leap_year(int y)
{
	if ( y >= 0 )
		return ( y % 400 == 0 || y % 4 == 0 && y % 100 != 0 ) ? 29 : 28;
    else
    	return (y % 4 == 0) ? 29 : 28;
}


/*******************************************************************************
*	NAME:
*		day_of_week
*		
*	PURPOSE:
*		Returns what day of the week the input Julian Day is
*		
*	REFERENCES:
*		none
*			
*	INPUT ARGUMENTS:
*		j (double)
*			input Julian Day
*	
*	OUTPUT ARGUMENTS:
*	 	none
*	 
*	RETURNED VALUE:
*	 	day of the week
*	 	0 = Sunday...6 = Saturday
*	 
*	GLOBALS USED:
*	 	none
*	 
*	FUNCTIONS CALLED:
*	 	ZeroHourJulian
*	 
*	DATE/PROGRAMMER/NOTE:
*		02-18-2001	Todd A. Guillory	written in ANSI C
*		02-19-2001	Todd A. Guillory	tested, 2451959.50 -> 1 for Monday
*			
********************************************************************************/
int day_of_week(double j)
{	
	return (int)(zero_hour_julian(j) + 1.5) % 7;
}


/*******************************************************************************
*	NAME:
*		first_week_day
*		
*	PURPOSE:
*		Returns what day of the week January 1 is for the input year
*		
*	REFERENCES:
*		Epp, Susanna S. "Discrete Mathematics With Applications, 2nd ed." PWS Publishing 1995.
*			pp. 153
*			
*	INPUT ARGUMENTS:
*		y (int)
*			input year
*	
*	OUTPUT ARGUMENTS:
*	 	none
*	 
*	RETURNED VALUE:
*	 	day of the week
*	 	0 = Sunday...6 = Saturday
*	 
*	GLOBALS USED:
*	 	none
*	 
*	FUNCTIONS CALLED:
*	 	floor
*	 
*	DATE/PROGRAMMER/NOTE:
*		02-18-2001	Todd A. Guillory	created
*		02-19-2001	Todd A. Guillory	tested, 2001 -> 1 for Monday
*												2025 -> 3 for Wednesday
*		
********************************************************************************/
int first_week_day(int y)
{
	return (int)( y + floor((y-1)/4) - floor((y-1)/100) + floor((y-1)/400) ) % 7;
}
