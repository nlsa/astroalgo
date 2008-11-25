#ifndef _ASTROCONST_H
	#define _ASTROCONST_H
	
#include "astroalgo.h"
	
#ifdef __cplusplus
extern "C"
{
#endif

#include "astroalgo.h"

/* label names can be modified in the header for localization */

/* names of the month */
const char*		monthlabels[12] = {		"January\0",
										"February\0",
										"March\0",
										"April\0",
										"May\0",
										"June\0",
										"July\0",
										"August\0",
										"September\0",
										"October\0",
										"November\0",
										"December\0"};

/* names of week days */								
const char*	daylabels[7] = {			"Sunday\0",
										"Monday\0",
										"Tuesday\0",
										"Wednesday\0",
										"Thursday\0",
										"Friday\0",
										"Saturday\0"};

/* names of sesonal periods */
const char*		seasonlabels[4] = {	"Vernal Equinox\0",
									"Summer Solstice\0",
									"Autumnal Equinox\0",
									"Winter Solstice\0"};

/* names of moon phases */							
const char*			phaselabels[4] = {	"New Moon\0",
										"First Quarter Moon\0",
										"Full Moon\0",
										"Last Quarter Moon\0"};

/* standard number of days in months */
const short		maxdays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
							
#ifdef __cplusplus
}
#endif

#endif /* _ASTROCONST_H */