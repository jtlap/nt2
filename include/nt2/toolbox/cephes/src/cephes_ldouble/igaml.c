/*							igaml.c
 *
 *	Incomplete gamma integral
 *
 *
 *
 * SYNOPSIS:
 *
 * long double a, x, y, cephes_igaml();
 *
 * y = cephes_igaml( a, x );
 *
 *
 *
 * DESCRIPTION:
 *
 * The function is defined by
 *
 *                           x
 *                            -
 *                   1       | |  -t  a-1
 *  igam(a,x)  =   -----     |   e   t   dt.
 *                  -      | |
 *                 | (a)    -
 *                           0
 *
 *
 * In this implementation both arguments must be positive.
 * The integral is evaluated by either a power series or
 * continued fraction expansion, depending on the relative
 * values of a and x.
 *
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    DEC       0,30         4000       4.4e-15     6.3e-16
 *    IEEE      0,30        10000       3.6e-14     5.1e-15
 *
 */
/*							cephes_igamcl()
 *
 *	Complemented incomplete gamma integral
 *
 *
 *
 * SYNOPSIS:
 *
 * long double a, x, y, cephes_igamcl();
 *
 * y = cephes_igamcl( a, x );
 *
 *
 *
 * DESCRIPTION:
 *
 * The function is defined by
 *
 *
 *  igamc(a,x)   =   1 - igam(a,x)
 *
 *                            inf.
 *                              -
 *                     1       | |  -t  a-1
 *               =   -----     |   e   t   dt.
 *                    -      | |
 *                   | (a)    -
 *                             x
 *
 *
 * In this implementation both arguments must be positive.
 * The integral is evaluated by either a power series or
 * continued fraction expansion, depending on the relative
 * values of a and x.
 *
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    DEC       0,30         2000       2.7e-15     4.0e-16
 *    IEEE      0,30        60000       1.4e-12     6.3e-15
 *
 */

/*
Cephes Math Library Release 2.3:  March, 1995
Copyright 1985, 1995 by Stephen L. Moshier
*/

#include "mconf.h"
#ifdef ANSIPROT
extern long double cephes_lgaml ( long double );
extern long double cephes_expl ( long double );
extern long double cephes_logl ( long double );
extern long double cephes_fabsl ( long double );
extern long double cephes_gammal ( long double );
long double cephes_igaml ( long double, long double );
long double cephes_igamcl ( long double, long double );
#else
long double cephes_lgaml(), cephes_expl(), cephes_logl(), cephes_fabsl(), cephes_igaml(), cephes_gammal();
long double cephes_igamcl();
#endif

#define BIG 9.223372036854775808e18L
#define MAXGAML 1755.455L
extern long double MACHEPL, MINLOGL;

long double cephes_igamcl( a, x )
long double a, x;
{
long double ans, c, yc, ax, y, z, r, t;
long double pk, pkm1, pkm2, qk, qkm1, qkm2;

if( (x <= 0.0L) || ( a <= 0.0L) )
	return( 1.0L );

if( (x < 1.0L) || (x < a) )
	return( 1.0L - cephes_igaml(a,x) );

ax = a * cephes_logl(x) - x - cephes_lgaml(a);
if( ax < MINLOGL )
	{
	cephes_mtherr( "igamcl", UNDERFLOW );
	return( 0.0L );
	}
ax = cephes_expl(ax);

/* continued fraction */
y = 1.0L - a;
z = x + y + 1.0L;
c = 0.0L;
pkm2 = 1.0L;
qkm2 = x;
pkm1 = x + 1.0L;
qkm1 = z * x;
ans = pkm1/qkm1;

do
	{
	c += 1.0L;
	y += 1.0L;
	z += 2.0L;
	yc = y * c;
	pk = pkm1 * z  -  pkm2 * yc;
	qk = qkm1 * z  -  qkm2 * yc;
	if( qk != 0.0L )
		{
		r = pk/qk;
		t = cephes_fabsl( (ans - r)/r );
		ans = r;
		}
	else
		t = 1.0L;
	pkm2 = pkm1;
	pkm1 = pk;
	qkm2 = qkm1;
	qkm1 = qk;
	if( cephes_fabsl(pk) > BIG )
		{
		pkm2 /= BIG;
		pkm1 /= BIG;
		qkm2 /= BIG;
		qkm1 /= BIG;
		}
	}
while( t > MACHEPL );

return( ans * ax );
}



/* left tail of incomplete gamma function:
 *
 *          inf.      k
 *   a  -x   -       x
 *  x  e     >   ----------
 *           -     -
 *          k=0   | (a+k+1)
 *
 */

long double cephes_igaml( a, x )
long double a, x;
{
long double ans, ax, c, r;

if( (x <= 0.0L) || ( a <= 0.0L) )
	return( 0.0L );

if( (x > 1.0L) && (x > a ) )
	return( 1.0L - cephes_igamcl(a,x) );

ax = a * cephes_logl(x) - x - cephes_lgaml(a);
if( ax < MINLOGL )
	{
	cephes_mtherr( "igaml", UNDERFLOW );
	return( 0.0L );
	}
ax = cephes_expl(ax);

/* power series */
r = a;
c = 1.0L;
ans = 1.0L;

do
	{
	r += 1.0L;
	c *= x/r;
	ans += c;
	}
while( c/ans > MACHEPL );

return( ans * ax/a );
}
