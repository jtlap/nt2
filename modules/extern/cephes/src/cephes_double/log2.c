/*							log2.c
 *
 *	Base 2 logarithm
 *
 *
 *
 * SYNOPSIS:
 *
 * double x, y, cephes_log2();
 *
 * y = cephes_log2( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns the base 2 logarithm of x.
 *
 * The argument is separated into its exponent and fractional
 * parts.  If the exponent is between -1 and +1, the base e
 * logarithm of the fraction is approximated by
 *
 *     cephes_log(1+x) = x - 0.5 x**2 + x**3 P(x)/Q(x).
 *
 * Otherwise, setting  z = 2(x-1)/x+1),
 * 
 *     cephes_log(x) = z + z**3 P(z)/Q(z).
 *
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE      0.5, 2.0    30000       2.0e-16     5.5e-17
 *    IEEE      cephes_exp(+-700)  40000       1.3e-16     4.6e-17
 *
 * In the tests over the interval [exp(+-700)], the logarithms
 * of the random arguments were uniformly distributed.
 *
 * ERROR MESSAGES:
 *
 * log2 singularity:  x = 0; returns -INFINITY
 * log2 domain:       x < 0; returns NAN
 */

/*
Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1995, 2000 by Stephen L. Moshier
*/

#include "mconf.h"
static char fname[] = {"log2"};

/* Coefficients for cephes_log(1+x) = x - x**2/2 + x**3 P(x)/Q(x)
 * 1/cephes_sqrt(2) <= x < cephes_sqrt(2)
 */
static double P[] = {
 1.01875663804580931796E-4,
 4.97494994976747001425E-1,
 4.70579119878881725854E0,
 1.44989225341610930846E1,
 1.79368678507819816313E1,
 7.70838733755885391666E0,
};
static double Q[] = {
/* 1.00000000000000000000E0, */
 1.12873587189167450590E1,
 4.52279145837532221105E1,
 8.29875266912776603211E1,
 7.11544750618563894466E1,
 2.31251620126765340583E1,
};
#define LOG2EA 0.44269504088896340735992

/* Coefficients for cephes_log(x) = z + z**3 P(z)/Q(z),
 * where z = 2(x-1)/(x+1)
 * 1/cephes_sqrt(2) <= x < cephes_sqrt(2)
 */

static double R[3] = {
-7.89580278884799154124E-1,
 1.63866645699558079767E1,
-6.41409952958715622951E1,
};
static double S[3] = {
/* 1.00000000000000000000E0,*/
-3.56722798256324312549E1,
 3.12093766372244180303E2,
-7.69691943550460008604E2,
};
/* cephes_log2(e) - 1 */
#define LOG2EA 0.44269504088896340735992

#ifdef ANSIPROT
extern double cephes_frexp ( double, int * );
extern double cephes_ldexp ( double, int );
extern double cephes_polevl ( double, double *, int );
extern double cephes_p1evl ( double, double *, int );
extern int isnan ( double );
extern int isfinite ( double );
#else
double cephes_frexp(), cephes_ldexp(), cephes_polevl(), cephes_p1evl();
int isnan(), isfinite();
#endif
#define SQRTH 0.70710678118654752440
extern double LOGE2, INFINITY, NAN;

double cephes_log2(x)
double x;
{
int e;
double y;
VOLATILE double z;
#ifdef DEC
short *q;
#endif

#ifdef NANS
if( isnan(x) )
	return(x);
#endif
#ifdef INFINITIES
if( x == INFINITY )
	return(x);
#endif
/* Test for domain */
if( x <= 0.0 )
	{
	if( x == 0.0 )
	        {
		cephes_mtherr( fname, SING );
		return( -INFINITY );
	        }
	else
	        {
		cephes_mtherr( fname, DOMAIN );
		return( NAN );
	        }
	}

/* separate mantissa from exponent */

#ifdef DEC
q = (short *)&x;
e = *q;			/* short containing exponent */
e = ((e >> 7) & 0377) - 0200;	/* the exponent */
*q &= 0177;	/* strip exponent from x */
*q |= 040000;	/* x now between 0.5 and 1 */
#endif

/* Note, frexp is used so that denormal numbers
 * will be handled properly.
 */
#ifdef IBMPC
x = cephes_frexp( x, &e );
/*
q = (short *)&x;
q += 3;
e = *q;
e = ((e >> 4) & 0x0fff) - 0x3fe;
*q &= 0x0f;
*q |= 0x3fe0;
*/
#endif

/* Equivalent C language standard library function: */
#ifdef UNK
x = cephes_frexp( x, &e );
#endif

#ifdef MIEEE
x = cephes_frexp( x, &e );
#endif


/* logarithm using cephes_log(x) = z + z**3 P(z)/Q(z),
 * where z = 2(x-1)/x+1)
 */

if( (e > 2) || (e < -2) )
{
if( x < SQRTH )
	{ /* 2( 2x-1 )/( 2x+1 ) */
	e -= 1;
	z = x - 0.5;
	y = 0.5 * z + 0.5;
	}	
else
	{ /*  2 (x-1)/(x+1)   */
	z = x - 0.5;
	z -= 0.5;
	y = 0.5 * x  + 0.5;
	}

x = z / y;
z = x*x;
y = x * ( z * cephes_polevl( z, (double*)R, 2 ) / cephes_p1evl( z, (double*)S, 3 ) );
goto ldone;
}



/* logarithm using cephes_log(1+x) = x - .5x**2 + x**3 P(x)/Q(x) */

if( x < SQRTH )
	{
	e -= 1;
	x = cephes_ldexp( x, 1 ) - 1.0; /*  2x - 1  */
	}	
else
	{
	x = x - 1.0;
	}

z = x*x;
#if DEC
y = x * ( z * cephes_polevl( x, (double*)P, 5 ) / cephes_p1evl( x, (double*)Q, 6 ) ) - cephes_ldexp( z, -1 );
#else
y = x * ( z * cephes_polevl( x, (double*)P, 5 ) / cephes_p1evl( x, (double*)Q, 5 ) ) - cephes_ldexp( z, -1 );
#endif

ldone:

/* Multiply log of fraction by cephes_log2(e)
 * and base 2 exponent by 1
 *
 * ***CAUTION***
 *
 * This sequence of operations is critical and it may
 * be horribly defeated by some compiler optimizers.
 */
z = y * LOG2EA;
z += x * LOG2EA;
z += y;
z += x;
z += e;
return( z );
}
