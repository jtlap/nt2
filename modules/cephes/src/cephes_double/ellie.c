/*							ellie.c
 *
 *	Incomplete elliptic integral of the second kind
 *
 *
 *
 * SYNOPSIS:
 *
 * double phi, m, y, cephes_ellie();
 *
 * y = cephes_ellie( phi, m );
 *
 *
 *
 * DESCRIPTION:
 *
 * Approximates the integral
 *
 *
 *                phi
 *                 -
 *                | |
 *                |                   2
 * E(phi_\m)  =    |    cephes_sqrt( 1 - m sin t ) dt
 *                |
 *              | |    
 *               -
 *                0
 *
 * of amplitude phi and modulus m, using the arithmetic -
 * geometric mean algorithm.
 *
 *
 *
 * ACCURACY:
 *
 * Tested at random arguments with phi in [-10, 10] and m in
 * [0, 1].
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    DEC        0,2         2000       1.9e-16     3.4e-17
 *    IEEE     -10,10      150000       3.3e-15     1.4e-16
 *
 *
 */


/*
Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1993, 2000 by Stephen L. Moshier
*/

/*	Incomplete elliptic integral of second kind	*/
#include "mconf.h"
extern double PI, PIO2, MACHEP;
#ifdef ANSIPROT
extern double cephes_sqrt ( double );
extern double fabs ( double );
extern double cephes_log ( double );
extern double cephes_sin ( double x );
extern double cephes_tan ( double x );
extern double cephes_atan ( double );
extern double cephes_floor ( double );
extern double cephes_ellpe ( double );
extern double cephes_ellpk ( double );
double cephes_ellie ( double, double );
#else
double cephes_sqrt(), fabs(), cephes_log(), cephes_sin(), cephes_tan(), cephes_atan(), cephes_floor();
double cephes_ellpe(), cephes_ellpk(), cephes_ellie();
#endif

double cephes_ellie( phi, m )
double phi, m;
{
double a, b, c, e, temp;
double lphi, t, E;
int d, mod, npio2, sign;

if( m == 0.0 )
	return( phi );
lphi = phi;
npio2 = cephes_floor( lphi/PIO2 );
if( npio2 & 1 )
	npio2 += 1;
lphi = lphi - npio2 * PIO2;
if( lphi < 0.0 )
	{
	lphi = -lphi;
	sign = -1;
	}
else
	{
	sign = 1;
	}
a = 1.0 - m;
E = cephes_ellpe( a );
if( a == 0.0 )
	{
	temp = cephes_sin( lphi );
	goto done;
	}
t = cephes_tan( lphi );
b = cephes_sqrt(a);
/* Thanks to Brian Fitzgerald <fitzgb@mml0.meche.rpi.edu>
   for pointing out an instability near odd multiples of pi/2.  */
if( fabs(t) > 10.0 )
	{
	/* Transform the amplitude */
	e = 1.0/(b*t);
	/* ... but avoid multiple recursions.  */
	if( fabs(e) < 10.0 )
		{
		e = cephes_atan(e);
		temp = E + m * cephes_sin( lphi ) * cephes_sin( e ) - cephes_ellie( e, m );
		goto done;
		}
	}
c = cephes_sqrt(m);
a = 1.0;
d = 1;
e = 0.0;
mod = 0;

while( fabs(c/a) > MACHEP )
	{
	temp = b/a;
	lphi = lphi + cephes_atan(t*temp) + mod * PI;
	mod = (lphi + PIO2)/PI;
	t = t * ( 1.0 + temp )/( 1.0 - temp * t * t );
	c = ( a - b )/2.0;
	temp = cephes_sqrt( a * b );
	a = ( a + b )/2.0;
	b = temp;
	d += d;
	e += c * cephes_sin(lphi);
	}

temp = E / cephes_ellpk( 1.0 - m );
temp *= (cephes_atan(t) + mod * PI)/(d * a);
temp += e;

done:

if( sign < 0 )
	temp = -temp;
temp += npio2 * E;
return( temp );
}
