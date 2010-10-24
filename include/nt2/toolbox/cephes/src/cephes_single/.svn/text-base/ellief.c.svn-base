/*							ellief.c
 *
 *	Incomplete elliptic integral of the second kind
 *
 *
 *
 * SYNOPSIS:
 *
 * float phi, m, y, cephes_ellief();
 *
 * y = cephes_ellief( phi, m );
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
 * E(phi\m)  =    |    sqrt( 1 - m sin t ) dt
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
 * Tested at random arguments with phi in [0, 2] and m in
 * [0, 1].
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE       0,2        10000       4.5e-7      7.4e-8
 *
 *
 */


/*
Cephes Math Library Release 2.2:  July, 1992
Copyright 1984, 1987, 1992 by Stephen L. Moshier
Direct inquiries to 30 Frost Street, Cambridge, MA 02140
*/

/*	Incomplete elliptic integral of second kind	*/

#include "mconf.h"

extern float PIF, PIO2F, MACHEPF;

#define fabsf(x) ( (x) < 0 ? -(x) : (x) )

#ifdef ANSIC
float cephes_sqrtf(float), cephes_logf(float), cephes_sinf(float), cephes_tanf(float), cephes_atanf(float);
float cephes_ellpef(float), cephes_ellpkf(float);
#else
float cephes_sqrtf(), cephes_logf(), cephes_sinf(), cephes_tanf(), cephes_atanf();
float cephes_ellpef(), cephes_ellpkf();
#endif


#ifdef ANSIC
float cephes_ellief( float phia, float ma )
#else
float cephes_ellief( phia, ma )
double phia, ma;
#endif
{
float phi, m, a, b, c, e, temp;
float lphi, t;
int d, mod;

phi = phia;
m = ma;
if( m == 0.0 )
	return( phi );
if( m == 1.0 )
	return( cephes_sinf(phi) );
lphi = phi;
if( lphi < 0.0 )
	lphi = -lphi;
a = 1.0;
b = 1.0 - m;
b = cephes_sqrtf(b);
c = cephes_sqrtf(m);
d = 1;
e = 0.0;
t = cephes_tanf( lphi );
mod = (lphi + PIO2F)/PIF;

while( fabsf(c/a) > MACHEPF )
	{
	temp = b/a;
	lphi = lphi + cephes_atanf(t*temp) + mod * PIF;
	mod = (lphi + PIO2F)/PIF;
	t = t * ( 1.0 + temp )/( 1.0 - temp * t * t );
	c = 0.5 * ( a - b );
	temp = cephes_sqrtf( a * b );
	a = 0.5 * ( a + b );
	b = temp;
	d += d;
	e += c * cephes_sinf(lphi);
	}

b = 1.0 - m;
temp = cephes_ellpef(b)/cephes_ellpkf(b);
temp *= (cephes_atanf(t) + mod * PIF)/(d * a);
temp += e;
if( phi < 0.0 )
	temp = -temp;
return( temp );
}
