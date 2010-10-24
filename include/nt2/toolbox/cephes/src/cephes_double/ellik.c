/*							ellik.c
 *
 *	Incomplete elliptic integral of the first kind
 *
 *
 *
 * SYNOPSIS:
 *
 * double phi, m, y, cephes_ellik();
 *
 * y = cephes_ellik( phi, m );
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
 *              | |    cephes_sqrt( 1 - m sin t )
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
 *    IEEE     -10,10       200000      7.4e-16     1.0e-16
 *
 *
 */


/*
Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 2000 by Stephen L. Moshier
*/

/*	Incomplete elliptic integral of first kind	*/

#include "mconf.h"
#ifdef ANSIPROT
extern double cephes_sqrt ( double );
extern double fabs ( double );
extern double cephes_log ( double );
extern double cephes_tan ( double );
extern double cephes_atan ( double );
extern double cephes_floor ( double );
extern double cephes_ellpk ( double );
double cephes_ellik ( double, double );
#else
double cephes_sqrt(), fabs(), cephes_log(), cephes_tan(), cephes_atan(), cephes_floor(), cephes_ellpk();
double cephes_ellik();
#endif
extern double PI, PIO2, MACHEP, MAXNUM;

double cephes_ellik( phi, m )
double phi, m;
{
double a, b, c, e, temp, t, K;
int d, mod, sign, npio2;

if( m == 0.0 )
	return( phi );
a = 1.0 - m;
if( a == 0.0 )
	{
	if( fabs(phi) >= PIO2 )
		{
		cephes_mtherr( "ellik", SING );
		return( MAXNUM );
		}
	return(  cephes_log(  cephes_tan( (PIO2 + phi)/2.0 )  )   );
	}
npio2 = cephes_floor( phi/PIO2 );
if( npio2 & 1 )
	npio2 += 1;
if( npio2 )
	{
	K = cephes_ellpk( a );
	phi = phi - npio2 * PIO2;
	}
else
	K = 0.0;
if( phi < 0.0 )
	{
	phi = -phi;
	sign = -1;
	}
else
	sign = 0;
b = cephes_sqrt(a);
t = cephes_tan( phi );
if( fabs(t) > 10.0 )
	{
	/* Transform the amplitude */
	e = 1.0/(b*t);
	/* ... but avoid multiple recursions.  */
	if( fabs(e) < 10.0 )
		{
		e = cephes_atan(e);
		if( npio2 == 0 )
			K = cephes_ellpk( a );
		temp = K - cephes_ellik( e, m );
		goto done;
		}
	}
a = 1.0;
c = cephes_sqrt(m);
d = 1;
mod = 0;

while( fabs(c/a) > MACHEP )
	{
	temp = b/a;
	phi = phi + cephes_atan(t*temp) + mod * PI;
	mod = (phi + PIO2)/PI;
	t = t * ( 1.0 + temp )/( 1.0 - temp * t * t );
	c = ( a - b )/2.0;
	temp = cephes_sqrt( a * b );
	a = ( a + b )/2.0;
	b = temp;
	d += d;
	}

temp = (cephes_atan(t) + mod * PI)/(d * a);

done:
if( sign < 0 )
	temp = -temp;
temp += npio2 * K;
return( temp );
}
