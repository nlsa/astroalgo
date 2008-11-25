#ifndef _ASTROMATH_H
   #define _ASTROMATH_H
   
#ifdef __cplusplus
extern "C"
{
#endif

/* convient math functions used by this library */

/* value of PI computed by this system */
/* atan2(1,1) * 4 */
/* const double kPi= 3.141592653589793116; */
#define kPi			3.141592653589793116

/* Degrees to Radians conversion factor */
/* kPi / 180.0 */
#define kDegRad		0.01745329251994329547437168

/* Radians to Degrees conversion factor */
/* 180.0 / kPi */
#define kRadDeg		57.29577951308232286464772

/* Function Declarations */

double SinD(double x);

double CosD(double x);

double TanD(double x);

double Normalize0To1(double x);

double Revolution(double theta);

double revolution_180(double theta);

void Fraction2Time(double x, short *hour, short *minute, double *second);

void Angle2Time(double x, short *degree, short *minute, double *second);

#ifdef __cplusplus
}
#endif

#endif /* _ASTROMATH_H */