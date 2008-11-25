#include <stdio.h>

#include "astroalgo.h"

void day_of_week_test();
void first_week_day_test();
void date2julian_test();
void date2julian_test();

int main(void)
{
	day_of_week_test();
	first_week_day_test();
	date2julian_test();

	return 0;
}

void day_of_week_test()
{
	int i = day_of_week_index(1,1,2008);
	printf("index is %d, name is %s\n", i, day_of_week_name(i) );
}

void first_week_day_test()
{
	int i = first_week_day(2008);
	printf("index is %d, name is %s\n", i, day_of_week_name(i) );
}

void date2julian_test()
{
	double jd = 0;
	int code = date_to_julian(1,1,2008,&jd);
	printf("Julian Day is %f\n", jd );
}
