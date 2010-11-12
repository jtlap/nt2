/*							cephes_igamil()
 *
 *      Inverse of complemented imcomplete gamma integral
 *
 *
 *
 * SYNOPSIS:
 *
 * long double a, x, y, cephes_igamil();
 *
 * x = cephes_igamil( a, y );
 *
 *
 *
 * DESCRIPTION:
 *
 * Given y, the function finds x such that
 *
 *  igamc( a, x ) = y.
 *
 * It is valid in the right-hand tail of the distribution, y < 0.5.
 * Starting with the approximate value
 *
 *         3
 *  x = a t
 *
 *  where
 *
 *  t = 1 - d - ndtri(y) sqrt(d)
 * 
 * and
 *
 *  d = 1/9a,
 *
 * the routine performs up to 10 Newton iterations to find the
 * root of igamc(a,x) - y = 0.
 *
 *
 * ACCURACY:
 *
 * Tested for a ranging from 0.5 to 30 and x from 0 to 0.5.
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    DEC       0,0.5         3400       8.8e-16     1.3e-16
 *    IEEE      0,0.5        10000       1.1e-14     1.0e-15
 *
 */

/*
Cephes Math Library Release 2.3:  March, 1995
Copyright 1984, 1995 by Stephen L. Moshier
*/

#include "mconf.h"

extern long double MACHEPL, MAXNUML, MAXLOGL, MINLOGL;
#ifdef ANSIPROT
extern long double cephes_ndtril ( long double );
extern long double cephes_expl ( long double );
extern long double cephes_fabsl ( long double );
extern long double cephes_logl ( long double );
extern long double cephes_sqrtl ( long double );
extern long double cephes_lgaml ( long double );
extern long double cephes_igamcl ( long double, long double );
#else
long double cephes_ndtril(), cephes_expl(), cephes_fabsl(), cephes_logl(), cephes_sqrtl(), cephes_lgaml();
long double cephes_igamcl();
#endif

long double cephes_igamil( a, y0 )
long double a, y0;
{
long double x0, x1, x, yl, yh, y, d, lgm, dithresh;
int i, dir;

if( y0 > 0.5)
	cephes_mtherr( "igamil", PLOSS );

/* bound the solution */
x0 = MAXNUML;
yl = 0.0L;
x1 = 0.0L;
yh = 1.0L;
dithresh = 4.0 * MACHEPL;

/* approximation to inverse function */
d = 1.0L/(9.0L*a);
y = ( 1.0L - d - cephes_ndtril(y0) * cephes_sqrtl(d) );
x = a * y * y * y;

lgm = cephes_lgaml(a);

for( i=0; i<10; i++ )
	{
	if( x > x0 || x < x1 )
		goto ihalve;
	y = cephes_igamcl(a,x);
	if( y < yl || y > yh )
		goto ihalve;
	if( y < y0 )
		{
		x0 = x;
		yl = y;
		}
	else
		{
		x1 = x;
		yh = y;
		}
/* compute the derivative of the function at this point */
	d = (a - 1.0L) * cephes_logl(x0) - x0 - lgm;
	if( d < -MAXLOGL )
		goto ihalve;
	d = -cephes_expl(d);
/* compute the step to the next approximation of x */
	d = (y - y0)/d;
	x = x - d;
	if( i < 3 )
		continue;
	if( cephes_fabsl(d/x) < dithresh )
		goto done;
	}

/* Resort to interval halving if Newton iteration did not converge. */
ihalve:

d = 0.0625L;
if( x0 == MAXNUML )
	{
	if( x <= 0.0L )
		x = 1.0L;
	while( x0 == MAXNUML )
		{
		x = (1.0L + d) * x;
		y = cephes_igamcl( a, x );
		if( y < y0 )
			{
			x0 = x;
			yl = y;
			break;
			}
		d = d + d;
		}
	}
d = 0.5L;
dir = 0;

for( i=0; i<400; i++ )
	{
	x = x1  +  d * (x0 - x1);
	y = cephes_igamcl( a, x );
	lgm = (x0 - x1)/(x1 + x0);
	if( cephes_fabsl(lgm) < dithresh )
		break;
	lgm = (y - y0)/y0;
	if( cephes_fabsl(lgm) < dithresh )
		break;
	if( x <= 0.0L )
		break;
	if( y > y0 )
		{
		x1 = x;
		yh = y;
		if( dir < 0 )
			{
			dir = 0;
			d = 0.5L;
			}
		else if( dir > 1 )
			d = 0.5L * d + 0.5L; 
		else
			d = (y0 - yl)/(yh - yl);
		dir += 1;
		}
	else
		{
		x0 = x;
		yl = y;
		if( dir > 0 )
			{
			dir = 0;
			d = 0.5L;
			}
		else if( dir < -1 )
			d = 0.5L * d;
		else
			d = (y0 - yl)/(yh - yl);
		dir -= 1;
		}
	}
if( x == 0.0L )
	cephes_mtherr( "igamil", UNDERFLOW );

done:
return( x );
}
