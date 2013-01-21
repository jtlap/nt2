/*							sin.c
 *
 *	Circular sine
 *
 *
 *
 * SYNOPSIS:
 *
 * double x, y, cephes_sin();
 *
 * y = cephes_sin( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Range reduction is into intervals of pi/4.  The reduction
 * error is nearly eliminated by contriving an extended precision
 * modular arithmetic.
 *
 * Two polynomial approximating functions are employed.
 * Between 0 and pi/4 the sine is approximated by
 *      x  +  x**3 P(x**2).
 * Between pi/4 and pi/2 the cosine is represented as
 *      1  -  x**2 Q(x**2).
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain      # trials      peak         rms
 *    DEC       0, 10       150000       3.0e-17     7.8e-18
 *    IEEE -1.07e9,+1.07e9  130000       2.1e-16     5.4e-17
 * 
 * ERROR MESSAGES:
 *
 *   message           condition        value returned
 * sin total loss   x > 1.073741824e9      0.0
 *
 * Partial loss of accuracy begins to occur at x = 2**30
 * = 1.074e9.  The loss is not gradual, but jumps suddenly to
 * about 1 part in 10e7.  Results may be meaningless for
 * x > 2**49 = 5.6e14.  The routine as implemented flags a
 * TLOSS error for x > 2**30 and returns 0.0.
 */
/*							cos.c
 *
 *	Circular cosine
 *
 *
 *
 * SYNOPSIS:
 *
 * double x, y, cephes_cos();
 *
 * y = cephes_cos( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Range reduction is into intervals of pi/4.  The reduction
 * error is nearly eliminated by contriving an extended precision
 * modular arithmetic.
 *
 * Two polynomial approximating functions are employed.
 * Between 0 and pi/4 the cosine is approximated by
 *      1  -  x**2 Q(x**2).
 * Between pi/4 and pi/2 the sine is represented as
 *      x  +  x**3 P(x**2).
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain      # trials      peak         rms
 *    IEEE -1.07e9,+1.07e9  130000       2.1e-16     5.4e-17
 *    DEC        0,+1.07e9   17000       3.0e-17     7.2e-18
 */

/*							sin.c	*/

/*
Cephes Math Library Release 2.8:  June, 2000
Copyright 1985, 1995, 2000 by Stephen L. Moshier
*/

#include "mconf.h"

static double sincof[] = {
 1.58962301576546568060E-10,
-2.50507477628578072866E-8,
 2.75573136213857245213E-6,
-1.98412698295895385996E-4,
 8.33333333332211858878E-3,
-1.66666666666666307295E-1,
};
static double coscof[6] = {
-1.13585365213876817300E-11,
 2.08757008419747316778E-9,
-2.75573141792967388112E-7,
 2.48015872888517045348E-5,
-1.38888888888730564116E-3,
 4.16666666666665929218E-2,
};
static double DP1 =   7.85398125648498535156E-1;
static double DP2 =   3.77489470793079817668E-8;
static double DP3 =   2.69515142907905952645E-15;
/* static double lossth = 1.073741824e9; */

#ifdef ANSIPROT
extern double cephes_polevl ( double, double *, int );
extern double cephes_p1evl ( double, double *, int );
extern double cephes_floor ( double );
extern double cephes_ldexp ( double, int );
extern int isnan ( double );
extern int isfinite ( double );
#else
double cephes_polevl(), cephes_floor(), cephes_ldexp();
int isnan(), isfinite();
#endif
extern double PIO4;
static double lossth = 1.073741824e9;
#ifdef NANS
extern double NAN;
#endif
#ifdef INFINITIES
extern double INFINITY;
#endif


double cephes_sin(x)
double x;
{
double y, z, zz;
int j, sign;

#ifdef MINUSZERO
if( x == 0.0 )
	return(x);
#endif
#ifdef NANS
if( isnan(x) )
	return(x);
if( !isfinite(x) )
	{
	cephes_mtherr( "sin", DOMAIN );
	return(NAN);
	}
#endif
/* make argument positive but save the sign */
sign = 1;
if( x < 0 )
	{
	x = -x;
	sign = -1;
	}

if( x > lossth )
	{
	cephes_mtherr( "sin", TLOSS );
	return(0.0);
	}

y = cephes_floor( x/PIO4 ); /* integer part of x/PIO4 */

/* strip high bits of integer part to prevent integer overflow */
z = cephes_ldexp( y, -4 );
z = cephes_floor(z);           /* integer part of y/8 */
z = y - cephes_ldexp( z, 4 );  /* y - 16 * (y/16) */

j = z; /* convert to integer for tests on the phase angle */
/* map zeros to origin */
if( j & 1 )
	{
	j += 1;
	y += 1.0;
	}
j = j & 07; /* octant modulo 360 degrees */
/* reflect in x axis */
if( j > 3)
	{
	sign = -sign;
	j -= 4;
	}

/* Extended precision modular arithmetic */
z = ((x - y * DP1) - y * DP2) - y * DP3;

zz = z * z;

if( (j==1) || (j==2) )
	{
	y = 1.0 - cephes_ldexp(zz,-1) + zz * zz * cephes_polevl( zz, coscof, 5 );
	}
else
	{
/*	y = z  +  z * (zz * cephes_polevl( zz, sincof, 5 ));*/
	y = z  +  z * z * z * cephes_polevl( zz, sincof, 5 );
	}

if(sign < 0)
	y = -y;

return(y);
}





double cephes_cos(x)
double x;
{
double y, z, zz;
long i;
int j, sign;

#ifdef NANS
if( isnan(x) )
	return(x);
if( !isfinite(x) )
	{
	cephes_mtherr( "cos", DOMAIN );
	return(NAN);
	}
#endif

/* make argument positive */
sign = 1;
if( x < 0 )
	x = -x;

if( x > lossth )
	{
	cephes_mtherr( "cos", TLOSS );
	return(0.0);
	}

y = cephes_floor( x/PIO4 );
z = cephes_ldexp( y, -4 );
z = cephes_floor(z);		/* integer part of y/8 */
z = y - cephes_ldexp( z, 4 );  /* y - 16 * (y/16) */

/* integer and fractional part modulo one octant */
i = z;
if( i & 1 )	/* map zeros to origin */
	{
	i += 1;
	y += 1.0;
	}
j = i & 07;
if( j > 3)
	{
	j -=4;
	sign = -sign;
	}

if( j > 1 )
	sign = -sign;

/* Extended precision modular arithmetic */
z = ((x - y * DP1) - y * DP2) - y * DP3;

zz = z * z;

if( (j==1) || (j==2) )
	{
/*	y = z  +  z * (zz * cephes_polevl( zz, sincof, 5 ));*/
	y = z  +  z * z * z * cephes_polevl( zz, sincof, 5 );
	}
else
	{
	y = 1.0 - cephes_ldexp(zz,-1) + zz * zz * cephes_polevl( zz, coscof, 5 );
	}

if(sign < 0)
	y = -y;

return(y);
}





/* Degrees, minutes, seconds to radians: */

/* 1 arc second, in radians = 4.8481368110953599358991410e-5 */
#ifdef DEC
static unsigned short P648[] = {034513,054170,0176773,0116043,};
#define P64800 *(double *)P648
#else
static double P64800 = 4.8481368110953599358991410e-5;
#endif

double radian(d,m,s)
double d,m,s;
{

return( ((d*60.0 + m)*60.0 + s)*P64800 );
}
