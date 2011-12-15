/*							ellikf.c
 *
 *	Incomplete elliptic integral of the first kind
 *
 *
 *
 * SYNOPSIS:
 *
 * float phi, m, y, cephes_ellikf();
 *
 * y = cephes_ellikf( phi, m );
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
 * F(phi\m)  =    |    ------------------
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
 * Tested at random points with phi in [0, 2] and m in
 * [0, 1].
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE      0,2         10000       2.9e-7      5.8e-8
 *
 *
 */


/*
Cephes Math Library Release 2.2:  July, 1992
Copyright 1984, 1987, 1992 by Stephen L. Moshier
Direct inquiries to 30 Frost Street, Cambridge, MA 02140
*/

/*	Incomplete elliptic integral of first kind	*/

#include "mconf.h"
extern float PIF, PIO2F, MACHEPF;

#define fabsf(x) ( (x) < 0 ? -(x) : (x) )

#ifdef ANSIC
float cephes_sqrtf(float), cephes_logf(float), cephes_sinf(float), cephes_tanf(float), cephes_atanf(float);
#else
float cephes_sqrtf(), cephes_logf(), cephes_sinf(), cephes_tanf(), cephes_atanf();
#endif


#ifdef ANSIC
float cephes_ellikf( float phia, float ma )
#else
float cephes_ellikf( phia, ma )
double phia, ma;
#endif
{
float phi, m, a, b, c, temp;
float t;
int d, mod, sign;

phi = phia;
m = ma;
if( m == 0.0f )
	return( phi );
if( phi < 0.0f )
	{
	phi = -phi;
	sign = -1;
	}
else
	sign = 0;
a = 1.0f;
b = 1.0f - m;
if( b == 0.0f )
	return(  cephes_logf(  cephes_tanf( 0.5f*(PIO2F + phi) )  )   );
b = cephes_sqrtf(b);
c = cephes_sqrtf(m);
d = 1;
t = cephes_tanf( phi );
mod = (phi + PIO2F)/PIF;

while( fabsf(c/a) > MACHEPF )
	{
	temp = b/a;
	phi = phi + cephes_atanf(t*temp) + mod * PIF;
	mod = (phi + PIO2F)/PIF;
	t = t * ( 1.0f + temp )/( 1.0f - temp * t * t );
	c = ( a - b )/2.0f;
	temp = cephes_sqrtf( a * b );
	a = ( a + b )/2.0f;
	b = temp;
	d += d;
	}

temp = (cephes_atanf(t) + mod * PIF)/(d * a);
if( sign < 0 )
	temp = -temp;
return( temp );
}
