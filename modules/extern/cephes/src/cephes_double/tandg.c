/*							tandg.c
 *
 *	Circular tangent of argument in degrees
 *
 *
 *
 * SYNOPSIS:
 *
 * double x, y, cephes_tandg();
 *
 * y = cephes_tandg( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns the circular tangent of the argument x in degrees.
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
 *    DEC      0,10          8000      3.4e-17      1.2e-17
 *    IEEE     0,10         30000      3.2e-16      8.4e-17
 *
 * ERROR MESSAGES:
 *
 *   message         condition          value returned
 * tandg total loss   x > 8.0e14 (DEC)      0.0
 *                    x > 1.0e14 (IEEE)
 * tandg singularity  x = 180 k  +  90     MAXNUM
 */
/*							cotdg.c
 *
 *	Circular cotangent of argument in degrees
 *
 *
 *
 * SYNOPSIS:
 *
 * double x, y, cephes_cotdg();
 *
 * y = cephes_cotdg( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns the circular cotangent of the argument x in degrees.
 *
 * Range reduction is modulo pi/4.  A rational function
 *       x + x**3 P(x**2)/Q(x**2)
 * is employed in the basic interval [0, pi/4].
 *
 *
 * ERROR MESSAGES:
 *
 *   message         condition          value returned
 * cotdg total loss   x > 8.0e14 (DEC)      0.0
 *                    x > 1.0e14 (IEEE)
 * cotdg singularity  x = 180 k            MAXNUM
 */

/*
Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 2000 by Stephen L. Moshier
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
static double PI180 = 1.74532925199432957692E-2;
static double lossth = 1.0e14;

#ifdef ANSIPROT
extern double cephes_polevl ( double, double *, int );
extern double cephes_p1evl ( double, double *, int );
extern double cephes_floor ( double );
extern double cephes_ldexp ( double, int );
static double tancot( double, int );
#else
double cephes_polevl(), cephes_p1evl(), cephes_floor(), cephes_ldexp();
static double tancot();
#endif
extern double MAXNUM;
extern double PIO4;


double cephes_tandg(x)
double x;
{

return( tancot(x,0) );
}


double cephes_cotdg(x)
double x;
{

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
	cephes_mtherr( "tandg", TLOSS );
	return(0.0);
	}

/* compute x mod PIO4 */
y = cephes_floor( x/45.0 );

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

z = x - y * 45.0;
z *= PI180;

zz = z * z;

if( zz > 1.0e-14 )
	y = z  +  z * (zz * cephes_polevl( zz, P, 2 )/cephes_p1evl(zz, Q, 4));
else
	y = z;
	
if( j & 2 )
	{
	if( cotflg )
		y = -y;
	else
		{
		if( y != 0.0 )
			{
			y = -1.0/y;
			}
		else
			{
			cephes_mtherr( "tandg", SING );
			y = MAXNUM;
			}
		}
	}
else
	{
	if( cotflg )
		{
		if( y != 0.0 )
			y = 1.0/y;
		else
			{
			cephes_mtherr( "cotdg", SING );
			y = MAXNUM;
			}
		}
	}

if( sign < 0 )
	y = -y;

return( y );
}
