/*							exp.c
 *
 *	Exponential function
 *
 *
 *
 * SYNOPSIS:
 *
 * double x, y, cephes_exp();
 *
 * y = cephes_exp( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns e (2.71828...) raised to the x power.
 *
 * Range reduction is accomplished by separating the argument
 * into an integer k and fraction f such that
 *
 *     x    k  f
 *    e  = 2  e.
 *
 * A Pade' form  1 + 2x P(x**2)/( Q(x**2) - P(x**2) )
 * of degree 2/3 is used to approximate cephes_exp(f) in the basic
 * interval [-0.5, 0.5].
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    DEC       +- 88       50000       2.8e-17     7.0e-18
 *    IEEE      +- 708      40000       2.0e-16     5.6e-17
 *
 *
 * Error amplification in the exponential function can be
 * a serious matter.  The error propagation involves
 * cephes_exp( X(1+delta) ) = cephes_exp(X) ( 1 + X*delta + ... ),
 * which shows that a 1 lsb error in representing X produces
 * a relative error of X times 1 lsb in the function.
 * While the routine gives an accurate result for arguments
 * that are exactly represented by a double precision
 * computer number, the result contains amplified roundoff
 * error for large arguments not exactly represented.
 *
 *
 * ERROR MESSAGES:
 *
 *   message         condition      value returned
 * exp underflow    x < MINLOG         0.0
 * exp overflow     x > MAXLOG         INFINITY
 *
 */

/*
Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1995, 2000 by Stephen L. Moshier
*/


/*	Exponential function	*/

#include "mconf.h"

static double P[] = {
 1.26177193074810590878E-4,
 3.02994407707441961300E-2,
 9.99999999999999999910E-1,
};
static double Q[] = {
 3.00198505138664455042E-6,
 2.52448340349684104192E-3,
 2.27265548208155028766E-1,
 2.00000000000000000009E0,
};
static double C1 = 6.93145751953125E-1;
static double C2 = 1.42860682030941723212E-6;

#ifdef ANSIPROT
extern double cephes_polevl ( double, double *, int );
extern double cephes_p1evl ( double, double *, int );
extern double cephes_floor ( double );
extern double cephes_ldexp ( double, int );
extern int isnan ( double );
extern int isfinite ( double );
#else
double cephes_polevl(), cephes_p1evl(), cephes_floor(), cephes_ldexp();
int isnan(), isfinite();
#endif
extern double LOGE2, LOG2E, MAXLOG, MINLOG, MAXNUM;
#ifdef INFINITIES
extern double INFINITY;
#endif

double cephes_exp(x)
double x;
{
double px, xx;
int n;

#ifdef NANS
if( isnan(x) )
	return(x);
#endif
if( x > MAXLOG)
	{
#ifdef INFINITIES
	return( INFINITY );
#else
	cephes_mtherr( "exp", OVERFLOW );
	return( MAXNUM );
#endif
	}

if( x < MINLOG )
	{
#ifndef INFINITIES
	cephes_mtherr( "exp", UNDERFLOW );
#endif
	return(0.0);
	}

/* Express e**x = e**g 2**n
 *   = e**g e**( n loge(2) )
 *   = e**( g + n loge(2) )
 */
px = cephes_floor( LOG2E * x + 0.5 ); /* cephes_floor() truncates toward -infinity. */
n = px;
x -= px * C1;
x -= px * C2;

/* rational approximation for exponential
 * of the fractional part:
 * e**x = 1 + 2x P(x**2)/( Q(x**2) - P(x**2) )
 */
xx = x * x;
px = x * cephes_polevl( xx, P, 2 );
x =  px/( cephes_polevl( xx, Q, 3 ) - px );
x = 1.0 + 2.0 * x;

/* multiply by power of 2 */
x = cephes_ldexp( x, n );
return(x);
}
