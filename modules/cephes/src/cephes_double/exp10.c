/*							exp10.c
 *
 *	Base 10 exponential function
 *      (Common antilogarithm)
 *
 *
 *
 * SYNOPSIS:
 *
 * double x, y, cephes_exp10();
 *
 * y = cephes_exp10( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns 10 raised to the x power.
 *
 * Range reduction is accomplished by expressing the argument
 * as 10**x = 2**n 10**f, with |f| < 0.5 cephes_log10(2).
 * The Pade' form
 *
 *    1 + 2x P(x**2)/( Q(x**2) - P(x**2) )
 *
 * is used to approximate 10**f.
 *
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE     -307,+307    30000       2.2e-16     5.5e-17
 * Test result from an earlier version (2.1):
 *    DEC       -38,+38     70000       3.1e-17     7.0e-18
 *
 * ERROR MESSAGES:
 *
 *   message         condition      value returned
 * exp10 underflow    x < -MAXL10        0.0
 * exp10 overflow     x > MAXL10       MAXNUM
 *
 * DEC arithmetic: MAXL10 = 38.230809449325611792.
 * IEEE arithmetic: MAXL10 = 308.2547155599167.
 *
 */

/*
Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1991, 2000 by Stephen L. Moshier
*/


#include "mconf.h"

static double P[] = {
 4.09962519798587023075E-2,
 1.17452732554344059015E1,
 4.06717289936872725516E2,
 2.39423741207388267439E3,
};
static double Q[] = {
/* 1.00000000000000000000E0,*/
 8.50936160849306532625E1,
 1.27209271178345121210E3,
 2.07960819286001865907E3,
};
/* static double LOG102 = 3.01029995663981195214e-1; */
static double LOG210 = 3.32192809488736234787e0;
static double LG102A = 3.01025390625000000000E-1;
static double LG102B = 4.60503898119521373889E-6;
/* static double MAXL10 = 38.230809449325611792; */
static double MAXL10 = 308.2547155599167;

#ifdef ANSIPROT
extern double cephes_floor ( double );
extern double cephes_ldexp ( double, int );
extern double cephes_polevl ( double, void *, int );
extern double cephes_p1evl ( double, void *, int );
extern int isnan ( double );
extern int isfinite ( double );
#else
double cephes_floor(), cephes_ldexp(), cephes_polevl(), cephes_p1evl();
int isnan(), isfinite();
#endif
extern double MAXNUM;
#ifdef INFINITIES
extern double INFINITY;
#endif

double cephes_exp10(x)
double x;
{
double px, xx;
short n;

#ifdef NANS
if( isnan(x) )
	return(x);
#endif
if( x > MAXL10 )
	{
#ifdef INFINITIES
	return( INFINITY );
#else
	cephes_mtherr( "exp10", OVERFLOW );
	return( MAXNUM );
#endif
	}

if( x < -MAXL10 )	/* Would like to use MINLOG but can't */
	{
#ifndef INFINITIES
	cephes_mtherr( "exp10", UNDERFLOW );
#endif
	return(0.0);
	}

/* Express 10**x = 10**g 2**n
 *   = 10**g 10**( n cephes_log10(2) )
 *   = 10**( g + n cephes_log10(2) )
 */
px = cephes_floor( LOG210 * x + 0.5 );
n = px;
x -= px * LG102A;
x -= px * LG102B;

/* rational approximation for exponential
 * of the fractional part:
 * 10**x = 1 + 2x P(x**2)/( Q(x**2) - P(x**2) )
 */
xx = x * x;
px = x * cephes_polevl( xx, P, 3 );
x =  px/( cephes_p1evl( xx, Q, 3 ) - px );
x = 1.0 + cephes_ldexp( x, 1 );

/* multiply by power of 2 */
x = cephes_ldexp( x, n );

return(x);
}
