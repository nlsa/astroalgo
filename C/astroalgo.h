#ifndef _ASTROALGO_H
   #define _ASTROALGO_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Date and Time data types */
/* provided only as reference or for use in wrappers */
/* currently NOT enforced within this library */
typedef unsigned short		aaMonth;		/* 1-12, not zero based */
typedef double				aaDay;			/* fractional day represents a time, e.g. 4.75 is 18:00 hours */
typedef int					aaYear;			/* positive and negative years */
typedef unsigned short		aaHour;			/* 0-23 */
typedef unsigned short		aaMinute;		/* 0-59 */
typedef double				aaSecond;		/* fractional seconds */

/* Type Definitions */
typedef char				DOWi;		/* day of week index 0=Sunday..6=Saturday */

/* enumerations */
typedef enum moonphases
{
	newmoon = 0,
	firstquarter = 1,
	fullmoon = 2,
	lastquarter = 3
} Moonphases;

			
/* Function Declarations */

const char* day_of_week_name (DOWi i);
const char* month_name(unsigned short m);
short days_in_month(unsigned short m);

int leap_year(int y);

int day_of_week(double j);

int first_week_day(int y);

double julian_centuries(double JDe);

int date_to_julian(short inMonth, double inDay, int inYear, double *JD);

int julian_to_date(double JD, short* month, double* day, int* year);

double zero_hour_julian(double JD);

double mean_sidereal_time(double JD);

double app_sidereal_time(double JD);

void app_solar_coordinates( double JD, double *alpha, double *delta);

int rise_tran_set(double L, double phi, double h0, double JD, double A[], double D[], double m[]);

void azimuth_altitude( double JD, double alpha, double delta, double L, double phi, double *A, double *h);

void nutation( double T, double *deltaPsi, double *deltaEpsilon);

void obliquity( double T, double *epsilon, double *epsilonNull);

double moonphase( double year, Moonphases phase );

double equinox_solstice( double inYear, unsigned short inES );

double aeaster(int year);

double simple_illumination( double inJulian );

int day_of_week_index(int day, int month, int year);

const char* aa_version(void);

#ifdef __cplusplus
}
#endif

#endif /* _ASTROALGO_H */