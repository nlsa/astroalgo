#include "astroalgo.h"

/*******************************************************************************
	NAME:
		day_of_week_index
		
	PURPOSE:
		Returns the day of the week index for a day in the Gregorian Calendar
		where 0=Sunday and 6=Saturday.
		
	REFERENCES:
		Latham, Lance. "Standard C Date/Time Library: Programming the World Calendars and Clocks."
		R&D Books. 1998. pp. 77.
		Zeller's Congruence
			
	INPUT ARGUMENTS:
		d (int) day
		m (int) month
	 	y (int) year

	OUTPUT ARGUMENTS:
		none
	 
	RETURNED VALUE:
		0-7 (int) index corresponding to day of the week
	 
	FUNCTIONS CALLED:
		none
	 	
	DATE/PROGRAMMER/NOTE:
		2002-03-30	Todd A. Guillory	created
		
	NOTES:
		Only valid within the Gregorian calendar!
		use day_of_week() with the Julian Day as input to find any day of week
		index
********************************************************************************/
int day_of_week_index(int d, int m, int y)
{
	int index;

	if (m > 2)
		m -= 2;
	else
	{
		m += 10;
		y--;
	}
	
	index = ((13 * m - 1) / 5) + d + (y % 100) 
			+ ((y % 100) / 4) + ((y / 100) / 4) 
			- 2 * (y / 100) + 77;
			
	index = index - 7 * (index / 7);
	
	if (index == 7)
		index = 0;
		
	return index;
}
