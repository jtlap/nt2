/*							ellikl.c
 *
 *	Incomplete elliptic integral of the first kind
 *
 *
 *
 * SYNOPSIS:
 *
 * long double phi, m, y, cephes_ellikl();
 *
 * y = cephes_ellikl( phi, m );
 *
 *
 *
 * DESCRIPTION:
 *
 * Approximates the integral
 *
 *
 *
 *                phi
 *                 -
 *                | |
 *                |           dt
 * F(phi_\m)  =    |    ------------------
 *                |                   2
 *              | |    sqrt( 1 - m sin t )
 *               -
 *                0
 *
 * of amplitude phi and modulus m, using the arithmetic -
 * geometric mean algorithm.
 *
 *
 *
 *
 * ACCURACY:
 *
 * Tested at random points with m in [0, 1] and phi as indicated.
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE     -10,10        30000      3.6e-18     4.1e-19
 *
 *
 */


/*
Cephes Math Library Release 2.3:  November, 1995
Copyright 1984, 1987, 1995 by Stephen L. Moshier
*/

/*	Incomplete elliptic integral of first kind	*/

#include "mconf.h"
#ifdef ANSIPROT
extern long double cephes_sqrtl ( long double );
extern long double cephes_fabsl ( long double );
extern long double cephes_logl ( long double );
extern long double cephes_tanl ( long double );
extern long double cephes_atanl ( long double );
extern long double cephes_floorl ( long double );
extern long double cephes_ellpkl ( long double );
long double cephes_ellikl ( long double, long double );
#else
long double cephes_sqrtl(), cephes_fabsl(), cephes_logl(), cephes_tanl(), cephes_atanl(), cephes_floorl(), cephes_ellpkl();
long double cephes_ellikl();
#endif
extern long double PIL, PIO2L, MACHEPL, MAXNUML;

long double cephes_ellikl( phi, m )
long double phi, m;
{
long double a, b, c, e, temp, t, K;
int d, mod, sign, npio2;

if( m == 0.0L )
	return( phi );
a = 1.0L - m;
if( a == 0.0L )
	{
	if( cephes_fabsl(phi) >= PIO2L )
		{
		cephes_mtherr( "ellikl", SING );
		return( MAXNUML );
		}
	return(  cephes_logl(  cephes_tanl( 0.5L*(PIO2L + phi) )  )   );
	}
npio2 = cephes_floorl( phi/PIO2L );
if( npio2 & 1 )
	npio2 += 1;
if( npio2 )
	{
	K = cephes_ellpkl( a );
	phi = phi - npio2 * PIO2L;
	}
else
	K = 0.0L;
if( phi < 0.0L )
	{
	phi = -phi;
	sign = -1;
	}
else
	sign = 0;
b = cephes_sqrtl(a);
t = cephes_tanl( phi );
if( cephes_fabsl(t) > 10.0L )
	{
	/* Transform the amplitude */
	e = 1.0L/(b*t);
	/* ... but avoid multiple recursions.  */
	if( cephes_fabsl(e) < 10.0L )
		{
		e = cephes_atanl(e);
		if( npio2 == 0 )
			K = cephes_ellpkl( a );
		temp = K - cephes_ellikl( e, m );
		goto done;
		}
	}
a = 1.0L;
c = cephes_sqrtl(m);
d = 1;
mod = 0;

while( cephes_fabsl(c/a) > MACHEPL )
	{
	temp = b/a;
	phi = phi + cephes_atanl(t*temp) + mod * PIL;
	mod = (phi + PIO2L)/PIL;
	t = t * ( 1.0L + temp )/( 1.0L - temp * t * t );
	c = 0.5L * ( a - b );
	temp = cephes_sqrtl( a * b );
	a = 0.5L * ( a + b );
	b = temp;
	d += d;
	}

temp = (cephes_atanl(t) + mod * PIL)/(d * a);

done:
if( sign < 0 )
	temp = -temp;
temp += npio2 * K;
return( temp );
}
