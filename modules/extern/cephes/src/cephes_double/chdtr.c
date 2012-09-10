/*							chdtr.c
 *
 *	Chi-square distribution
 *
 *
 *
 * SYNOPSIS:
 *
 * double df, x, y, cephes_chdtr();
 *
 * y = cephes_chdtr( df, x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns the area under the left hand tail (from 0 to x)
 * of the Chi square probability density function with
 * v degrees of freedom.
 *
 *
 *                                  inf.
 *                                    -
 *                        1          | |  v/2-1  -t/2
 *  P( x | v )   =   -----------     |   t      e     dt
 *                    v/2  -       | |
 *                   2    | (v/2)   -
 *                                   x
 *
 * where x is the Chi-square variable.
 *
 * The incomplete gamma integral is used, according to the
 * formula
 *
 *	y = cephes_chdtr( v, x ) = cephes_igam( v/2.0, x/2.0 ).
 *
 *
 * The arguments must both be positive.
 *
 *
 *
 * ACCURACY:
 *
 * See cephes_igam().
 *
 * ERROR MESSAGES:
 *
 *   message         condition      value returned
 * chdtr domain   x < 0 or v < 1        0.0
 */
/*							cephes_chdtrc()
 *
 *	Complemented Chi-square distribution
 *
 *
 *
 * SYNOPSIS:
 *
 * double v, x, y, cephes_chdtrc();
 *
 * y = cephes_chdtrc( v, x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns the area under the right hand tail (from x to
 * infinity) of the Chi square probability density function
 * with v degrees of freedom:
 *
 *
 *                                  inf.
 *                                    -
 *                        1          | |  v/2-1  -t/2
 *  P( x | v )   =   -----------     |   t      e     dt
 *                    v/2  -       | |
 *                   2    | (v/2)   -
 *                                   x
 *
 * where x is the Chi-square variable.
 *
 * The incomplete gamma integral is used, according to the
 * formula
 *
 *	y = cephes_chdtr( v, x ) = cephes_igamc( v/2.0, x/2.0 ).
 *
 *
 * The arguments must both be positive.
 *
 *
 *
 * ACCURACY:
 *
 * See cephes_igamc().
 *
 * ERROR MESSAGES:
 *
 *   message         condition      value returned
 * chdtrc domain  x < 0 or v < 1        0.0
 */
/*							cephes_chdtri()
 *
 *	Inverse of complemented Chi-square distribution
 *
 *
 *
 * SYNOPSIS:
 *
 * double df, x, y, cephes_chdtri();
 *
 * x = cephes_chdtri( df, y );
 *
 *
 *
 *
 * DESCRIPTION:
 *
 * Finds the Chi-square argument x such that the integral
 * from x to infinity of the Chi-square density is equal
 * to the given cumulative probability y.
 *
 * This is accomplished using the inverse gamma integral
 * function and the relation
 *
 *    x/2 = cephes_igami( df/2, y );
 *
 *
 *
 *
 * ACCURACY:
 *
 * See igami.c.
 *
 * ERROR MESSAGES:
 *
 *   message         condition      value returned
 * chdtri domain   y < 0 or y > 1        0.0
 *                     v < 1
 *
 */

/*								cephes_chdtr() */


/*
Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 2000 by Stephen L. Moshier
*/

#include "mconf.h"
#ifdef ANSIPROT
extern double cephes_igamc ( double, double );
extern double cephes_igam ( double, double );
extern double cephes_igami ( double, double );
#else
double cephes_igamc(), cephes_igam(), cephes_igami();
#endif

double cephes_chdtrc(df,x)
double df, x;
{

if( (x < 0.0) || (df < 1.0) )
	{
	cephes_mtherr( "chdtrc", DOMAIN );
	return(0.0);
	}
return( cephes_igamc( df/2.0, x/2.0 ) );
}



double cephes_chdtr(df,x)
double df, x;
{

if( (x < 0.0) || (df < 1.0) )
	{
	cephes_mtherr( "chdtr", DOMAIN );
	return(0.0);
	}
return( cephes_igam( df/2.0, x/2.0 ) );
}



double cephes_chdtri( df, y )
double df, y;
{
double x;

if( (y < 0.0) || (y > 1.0) || (df < 1.0) )
	{
	cephes_mtherr( "chdtri", DOMAIN );
	return(0.0);
	}

x = cephes_igami( 0.5 * df, y );
return( 2.0 * x );
}
