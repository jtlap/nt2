/*							cephes_igamif()
 *
 *      Inverse of complemented imcomplete gamma integral
 *
 *
 *
 * SYNOPSIS:
 *
 * float a, x, y, cephes_igamif();
 *
 * x = cephes_igamif( a, y );
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
 * Tested for a ranging from 0 to 100 and x from 0 to 1.
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE      0,100         5000       1.0e-5      1.5e-6
 *
 */

/*
Cephes Math Library Release 2.2:  July, 1992
Copyright 1984, 1987, 1992 by Stephen L. Moshier
Direct inquiries to 30 Frost Street, Cambridge, MA 02140
*/

#include "mconf.h"

extern float MACHEPF, MAXLOGF;

#define fabsf(x) ( (x) < 0 ? -(x) : (x) )

#ifdef ANSIC
float cephes_igamcf(float, float);
float cephes_ndtrif(float), cephes_expf(float), cephes_logf(float), cephes_sqrtf(float), cephes_lgamf(float);
#else
float cephes_igamcf();
float cephes_ndtrif(), cephes_expf(), cephes_logf(), cephes_sqrtf(), cephes_lgamf();
#endif


#ifdef ANSIC
float cephes_igamif( float aa, float yy0 )
#else
float cephes_igamif( aa, yy0 )
double aa, yy0;
#endif
{
float a, y0, d, y, x0, lgm;
int i;

if( yy0 > 0.5)
	cephes_mtherr( "igamif", PLOSS );

a = aa;
y0 = yy0;
/* approximation to inverse function */
d = 1.0/(9.0*a);
y = ( 1.0 - d - cephes_ndtrif(y0) * cephes_sqrtf(d) );
x0 = a * y * y * y;

lgm = cephes_lgamf(a);

for( i=0; i<10; i++ )
	{
	if( x0 <= 0.0 )
		{
		cephes_mtherr( "igamif", UNDERFLOW );
		return(0.0);
		}
	y = cephes_igamcf(a,x0);
/* compute the derivative of the function at this point */
	d = (a - 1.0) * cephes_logf(x0) - x0 - lgm;
	if( d < -MAXLOGF )
		{
		cephes_mtherr( "igamif", UNDERFLOW );
		goto done;
		}
	d = -cephes_expf(d);
/* compute the step to the next approximation of x */
	if( d == 0.0 )
		goto done;
	d = (y - y0)/d;
	x0 = x0 - d;
	if( i < 3 )
		continue;
	if( fabsf(d/x0) < (2.0 * MACHEPF) )
		goto done;
	}

done:
return( x0 );
}
