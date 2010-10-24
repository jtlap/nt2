/*							chdtrl.c
 *
 *	Chi-square distribution
 *
 *
 *
 * SYNOPSIS:
 *
 * long double df, x, y, cephes_chdtrl();
 *
 * y = cephes_chdtrl( df, x );
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
 *	y = chdtr( v, x ) = igam( v/2.0, x/2.0 ).
 *
 *
 * The arguments must both be positive.
 *
 *
 *
 * ACCURACY:
 *
 * See igam().
 *
 * ERROR MESSAGES:
 *
 *   message         condition      value returned
 * chdtr domain   x < 0 or v < 1        0.0
 */
/*							cephes_chdtrcl()
 *
 *	Complemented Chi-square distribution
 *
 *
 *
 * SYNOPSIS:
 *
 * long double v, x, y, cephes_chdtrcl();
 *
 * y = cephes_chdtrcl( v, x );
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
 *	y = chdtr( v, x ) = igamc( v/2.0, x/2.0 ).
 *
 *
 * The arguments must both be positive.
 *
 *
 *
 * ACCURACY:
 *
 * See igamc().
 *
 * ERROR MESSAGES:
 *
 *   message         condition      value returned
 * chdtrc domain  x < 0 or v < 1        0.0
 */
/*							cephes_chdtril()
 *
 *	Inverse of complemented Chi-square distribution
 *
 *
 *
 * SYNOPSIS:
 *
 * long double df, x, y, cephes_chdtril();
 *
 * x = cephes_chdtril( df, y );
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
 *    x/2 = igami( df/2, y );
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

/*								chdtr() */


/*
Cephes Math Library Release 2.3:  March, 1995
Copyright 1984, 1995 by Stephen L. Moshier
*/

#include "mconf.h"
#ifdef ANSIPROT
extern long double cephes_igamcl ( long double, long double );
extern long double cephes_igaml ( long double, long double );
extern long double cephes_igamil ( long double, long double );
#else
long double cephes_igamcl(), cephes_igaml(), cephes_igamil();
#endif

long double cephes_chdtrcl(df,x)
long double df, x;
{

if( (x < 0.0L) || (df < 1.0L) )
	{
	cephes_mtherr( "chdtrcl", DOMAIN );
	return(0.0L);
	}
return( cephes_igamcl( 0.5L*df, 0.5L*x ) );
}



long double cephes_chdtrl(df,x)
long double df, x;
{

if( (x < 0.0L) || (df < 1.0L) )
	{
	cephes_mtherr( "chdtrl", DOMAIN );
	return(0.0L);
	}
return( cephes_igaml( 0.5L*df, 0.5L*x ) );
}



long double cephes_chdtril( df, y )
long double df, y;
{
long double x;

if( (y < 0.0L) || (y > 1.0L) || (df < 1.0L) )
	{
	cephes_mtherr( "chdtril", DOMAIN );
	return(0.0L);
	}

x = cephes_igamil( 0.5L * df, y );
return( 2.0L * x );
}
