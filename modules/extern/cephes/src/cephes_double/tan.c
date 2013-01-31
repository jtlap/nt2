/*							tan.c
 *
 *	Circular tangent
 *
 *
 *
 * SYNOPSIS:
 *
 * double x, y, cephes_tan();
 *
 * y = cephes_tan( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns the circular tangent of the radian argument x.
 *
 * Range reduction is modulo pi/4.  A rational function
 *       x + x**3 P(x**2)/Q(x**2)
 * is employed in the basic interval [0, pi/4].
 *
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    DEC      +-1.07e9      44000      4.1e-17     1.0e-17
 *    IEEE     +-1.07e9      30000      2.9e-16     8.1e-17
 *
 * ERROR MESSAGES:
 *
 *   message         condition          value returned
 * tan total loss   x > 1.073741824e9     0.0
 *
 */
/*							cot.c
 *
 *	Circular cotangent
 *
 *
 *
 * SYNOPSIS:
 *
 * double x, y, cephes_cot();
 *
 * y = cephes_cot( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns the circular cotangent of the radian argument x.
 *
 * Range reduction is modulo pi/4.  A rational function
 *       x + x**3 P(x**2)/Q(x**2)
 * is employed in the basic interval [0, pi/4].
 *
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE     +-1.07e9      30000      2.9e-16     8.2e-17
 *
 *
 * ERROR MESSAGES:
 *
 *   message         condition          value returned
 * cot total loss   x > 1.073741824e9       0.0
 * cot singularity  x = 0                  INFINITY
 *
 */

/*
Cephes Math Library Release 2.8:  June, 2000
yright 1984, 1995, 2000 by Stephen L. Moshier
*/

#include "mconf.h"

static double P[] = {
-1.30936939181383777646E4,
 1.15351664838587416140E6,
-1.79565251976484877988E7
};
static double Q[] = {
/* 1.00000000000000000000E0,*/
 1.36812963470692954678E4,
-1.32089234440210967447E6,
 2.50083801823357915839E7,
-5.38695755929454629881E7
};
static double DP1 = 7.853981554508209228515625E-1;
static double DP2 = 7.94662735614792836714E-9;
static double DP3 = 3.06161699786838294307E-17;
static double lossth = 1.073741824e9;

#ifdef ANSIPROT
extern double cephes_polevl ( double, double *, int );
extern double cephes_p1evl ( double, double *, int );
extern double cephes_floor ( double );
extern double cephes_ldexp ( double, int );
extern int isnan ( double );
extern int isfinite ( double );
static double tancot(double, int);
#else
double cephes_polevl(), cephes_p1evl(), cephes_floor(), cephes_ldexp();
static double tancot();
int isnan(), isfinite();
#endif
extern double PIO4;
extern double INFINITY;
extern double NAN;

double cephes_tan(x)
double x;
{
#ifdef MINUSZERO
if( x == 0.0 )
	return(x);
#endif
#ifdef NANS
if( isnan(x) )
	return(x);
if( !isfinite(x) )
	{
	cephes_mtherr( "tan", DOMAIN );
	return(NAN);
	}
#endif
return( tancot(x,0) );
}


double cephes_cot(x)
double x;
{

if( x == 0.0 )
	{
	cephes_mtherr( "cot", SING );
	return( INFINITY );
	}
return( tancot(x,1) );
}


static double tancot( xx, cotflg )
double xx;
int cotflg;
{
double x, y, z, zz;
int j, sign;

/* make argument positive but save the sign */
if( xx < 0 )
	{
	x = -xx;
	sign = -1;
	}
else
	{
	x = xx;
	sign = 1;
	}

if( x > lossth )
	{
	if( cotflg )
		cephes_mtherr( "cot", TLOSS );
	else
		cephes_mtherr( "tan", TLOSS );
	return(0.0);
	}

/* compute x mod PIO4 */
y = cephes_floor( x/PIO4 );

/* strip high bits of integer part */
z = cephes_ldexp( y, -3 );
z = cephes_floor(z);		/* integer part of y/8 */
z = y - cephes_ldexp( z, 3 );  /* y - 16 * (y/16) */

/* integer and fractional part modulo one octant */
j = z;

/* map zeros and singularities to origin */
if( j & 1 )
	{
	j += 1;
	y += 1.0;
	}

z = ((x - y * DP1) - y * DP2) - y * DP3;

zz = z * z;

if( zz > 1.0e-14 )
	y = z  +  z * (zz * cephes_polevl( zz, (double*)P, 2 )/cephes_p1evl(zz, (double*)Q, 4));
else
	y = z;
	
if( j & 2 )
	{
	if( cotflg )
		y = -y;
	else
		y = -1.0/y;
	}
else
	{
	if( cotflg )
		y = 1.0/y;
	}

if( sign < 0 )
	y = -y;

return( y );
}
