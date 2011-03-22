/*							betaf.c
 *
 *	Beta function
 *
 *
 *
 * SYNOPSIS:
 *
 * float a, b, y, cephes_betaf();
 *
 * y = cephes_betaf( a, b );
 *
 *
 *
 * DESCRIPTION:
 *
 *                   -     -
 *                  | (a) | (b)
 * beta( a, b )  =  -----------.
 *                     -
 *                    | (a+b)
 *
 * For large arguments the logarithm of the function is
 * evaluated using lgam(), then exponentiated.
 *
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE       0,30       10000       4.0e-5      6.0e-6
 *    IEEE       -20,0      10000       4.9e-3      5.4e-5
 *
 * ERROR MESSAGES:
 *
 *   message         condition          value returned
 * betaf overflow   log(beta) > MAXLOG       0.0
 *                  a or b <0 integer        0.0
 *
 */

/*							beta.c	*/


/*
Cephes Math Library Release 2.2:  July, 1992
Copyright 1984, 1987 by Stephen L. Moshier
Direct inquiries to 30 Frost Street, Cambridge, MA 02140
*/

#include "mconf.h"

#define fabsf(x) ( (x) < 0 ? -(x) : (x) )

#define MAXGAM 34.84425627277176174


extern float MAXLOGF, MAXNUMF;
extern int sgngamf;

#ifdef ANSIC
float cephes_gammaf(float), cephes_lgamf(float), cephes_expf(float), cephes_floorf(float);
#else
float cephes_gammaf(), cephes_lgamf(), cephes_expf(), cephes_floorf();
#endif

#ifdef ANSIC
float cephes_betaf( float aa, float bb )
#else
float cephes_betaf( aa, bb )
double aa, bb;
#endif
{
float a, b, y;
int sign;

sign = 1;
a = aa;
b = bb;
if( a <= 0.0 )
	{
	if( a == cephes_floorf(a) )
		goto over;
	}
if( b <= 0.0 )
	{
	if( b == cephes_floorf(b) )
		goto over;
	}


y = a + b;
if( fabsf(y) > MAXGAM )
	{
	y = cephes_lgamf(y);
	sign *= sgngamf; /* keep track of the sign */
	y = cephes_lgamf(b) - y;
	sign *= sgngamf;
	y = cephes_lgamf(a) + y;
	sign *= sgngamf;
	if( y > MAXLOGF )
		{
over:
		cephes_mtherr( "betaf", OVERFLOW );
		return( sign * MAXNUMF );
		}
	return( sign * cephes_expf(y) );
	}

y = cephes_gammaf(y);
if( y == 0.0 )
	goto over;

if( a > b )
	{
	y = cephes_gammaf(a)/y;
	y *= cephes_gammaf(b);
	}
else
	{
	y = cephes_gammaf(b)/y;
	y *= cephes_gammaf(a);
	}

return(y);
}
