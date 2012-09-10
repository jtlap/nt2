/*							asinhf.c
 *
 *	Inverse hyperbolic sine
 *
 *
 *
 * SYNOPSIS:
 *
 * float x, y, cephes_asinhf();
 *
 * y = cephes_asinhf( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns inverse hyperbolic sine of argument.
 *
 * If |x| < 0.5, the function is approximated by a rational
 * form  x + x**3 P(x)/Q(x).  Otherwise,
 *
 *     asinh(x) = log( x + sqrt(1 + x*x) ).
 *
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE     -3,3        100000       2.4e-7      4.1e-8
 *
 */

/*						asinh.c	*/

/*
Cephes Math Library Release 2.2:  June, 1992
Copyright 1984, 1987, 1988, 1992 by Stephen L. Moshier
Direct inquiries to 30 Frost Street, Cambridge, MA 02140
*/

/* Single precision inverse hyperbolic sine
 * test interval: [-0.5, +0.5]
 * trials: 10000
 * peak relative error: 8.8e-8
 * rms relative error: 3.2e-8
 */
#include "mconf.h"
extern float LOGE2F;

#ifdef ANSIC
float cephes_logf( float );
float cephes_sqrtf( float );

float cephes_asinhf( float xx )
#else
float cephes_logf(), cephes_sqrtf();

float cephes_asinhf(xx)
double xx;
#endif
{
float x, z;

if( xx < 0.0f )
	x = -xx;
else
	x = xx;

if( x > 1500.0f )
	{
	z = cephes_logf(x) + LOGE2F;
	goto done;
	}
z = x * x;
if( x < 0.5f )
	{
	z =
	((( 2.0122003309E-2f * z
	  - 4.2699340972E-2f) * z
	  + 7.4847586088E-2f) * z
	  - 1.6666288134E-1f) * z * x
	  + x;
	}
else
	{
	z = cephes_sqrtf( z + 1.0f );
	z = cephes_logf( x + z );
	}
done:
if( xx < 0 )
	z = -z;
return( z );
}

