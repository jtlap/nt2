/*							cephes_incbif()
 *
 *      Inverse of imcomplete beta integral
 *
 *
 *
 * SYNOPSIS:
 *
 * float a, b, x, y, cephes_incbif();
 *
 * x = cephes_incbif( a, b, y );
 *
 *
 *
 * DESCRIPTION:
 *
 * Given y, the function finds x such that
 *
 *  incbet( a, b, x ) = y.
 *
 * the routine performs up to 10 Newton iterations to find the
 * root of incbet(a,b,x) - y = 0.
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 *                x     a,b
 * arithmetic   domain  domain  # trials    peak       rms
 *    IEEE      0,1     0,100     5000     2.8e-4    8.3e-6
 *
 * Overflow and larger errors may occur for one of a or b near zero
 *  and the other large.
 */


/*
Cephes Math Library Release 2.2:  July, 1992
Copyright 1984, 1987, 1992 by Stephen L. Moshier
Direct inquiries to 30 Frost Street, Cambridge, MA 02140
*/

#include "mconf.h"

extern float MACHEPF, MINLOGF;

#define fabsf(x) ( (x) < 0 ? -(x) : (x) )

#ifdef ANSIC
float cephes_incbetf(float, float, float);
float cephes_ndtrif(float), cephes_expf(float), cephes_logf(float), cephes_sqrtf(float), cephes_lgamf(float);
#else
float cephes_incbetf();
float cephes_ndtrif(), cephes_expf(), cephes_logf(), cephes_sqrtf(), cephes_lgamf();
#endif

#ifdef ANSIC
float cephes_incbif( float aaa, float bbb, float yyy0 )
#else
float cephes_incbif( aaa, bbb, yyy0 )
double aaa, bbb, yyy0;
#endif
{
float aa, bb, yy0, a, b, y0;
float d, y, x, x0, x1, lgm, yp, di;
int i, rflg;


aa = aaa;
bb = bbb;
yy0 = yyy0;
if( yy0 <= 0 )
	return(0.0);
if( yy0 >= 1.0 )
	return(1.0);

/* approximation to inverse function */

yp = -cephes_ndtrif(yy0);

if( yy0 > 0.5 )
	{
	rflg = 1;
	a = bb;
	b = aa;
	y0 = 1.0 - yy0;
	yp = -yp;
	}
else
	{
	rflg = 0;
	a = aa;
	b = bb;
	y0 = yy0;
	}


if( (aa <= 1.0) || (bb <= 1.0) )
	{
	y = 0.5 * yp * yp;
	}
else
	{
	lgm = (yp * yp - 3.0)* 0.16666666666666667;
	x0 = 2.0/( 1.0/(2.0*a-1.0)  +  1.0/(2.0*b-1.0) );
	y = yp * cephes_sqrtf( x0 + lgm ) / x0
		- ( 1.0/(2.0*b-1.0) - 1.0/(2.0*a-1.0) )
		* (lgm + 0.833333333333333333 - 2.0/(3.0*x0));
	y = 2.0 * y;
	if( y < MINLOGF )
		{
		x0 = 1.0;
		goto under;
		}
	}

x = a/( a + b * cephes_expf(y) );
y = cephes_incbetf( a, b, x );
yp = (y - y0)/y0;
if( fabsf(yp) < 0.1 )
	goto newt;

/* Resort to interval halving if not close enough */
x0 = 0.0;
x1 = 1.0;
di = 0.5;

for( i=0; i<20; i++ )
	{
	if( i != 0 )
		{
		x = di * x1  + (1.0-di) * x0;
		y = cephes_incbetf( a, b, x );
		yp = (y - y0)/y0;
		if( fabsf(yp) < 1.0e-3 )
			goto newt;
		}

	if( y < y0 )
		{
		x0 = x;
		di = 0.5;
		}
	else
		{
		x1 = x;
		di *= di;
		if( di == 0.0 )
			di = 0.5;
		}
	}

if( x0 == 0.0 )
	{
under:
	cephes_mtherr( "incbif", UNDERFLOW );
	goto done;
	}

newt:

x0 = x;
lgm = cephes_lgamf(a+b) - cephes_lgamf(a) - cephes_lgamf(b);

for( i=0; i<10; i++ )
	{
/* compute the function at this point */
	if( i != 0 )
		y = cephes_incbetf(a,b,x0);
/* compute the derivative of the function at this point */
	d = (a - 1.0) * cephes_logf(x0) + (b - 1.0) * cephes_logf(1.0-x0) + lgm;
	if( d < MINLOGF )
		{
		x0 = 0.0;
		goto under;
		}
	d = cephes_expf(d);
/* compute the step to the next approximation of x */
	d = (y - y0)/d;
	x = x0;
	x0 = x0 - d;
	if( x0 <= 0.0 )
		{
		x0 = 0.0;
		goto under;
		}
	if( x0 >= 1.0 )
		{
		x0 = 1.0;
		goto under;
		}
	if( i < 2 )
		continue;
	if( fabsf(d/x0) < 256.0 * MACHEPF )
		goto done;
	}

done:
if( rflg )
	x0 = 1.0 - x0;
return( x0 );
}
