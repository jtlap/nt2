/*							gdtr.c
 *
 *	Gamma distribution function
 *
 *
 *
 * SYNOPSIS:
 *
 * double a, b, x, y, cephes_gdtr();
 *
 * y = cephes_gdtr( a, b, x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns the integral from zero to x of the gamma probability
 * density function:
 *
 *
 *                x
 *        b       -
 *       a       | |   b-1  -at
 * y =  -----    |    t    e    dt
 *       -     | |
 *      | (b)   -
 *               0
 *
 *  The incomplete gamma integral is used, according to the
 * relation
 *
 * y = cephes_igam( b, ax ).
 *
 *
 * ACCURACY:
 *
 * See cephes_igam().
 *
 * ERROR MESSAGES:
 *
 *   message         condition      value returned
 * gdtr domain         x < 0            0.0
 *
 */
/*							gdtrc.c
 *
 *	Complemented gamma distribution function
 *
 *
 *
 * SYNOPSIS:
 *
 * double a, b, x, y, cephes_gdtrc();
 *
 * y = cephes_gdtrc( a, b, x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns the integral from x to infinity of the gamma
 * probability density function:
 *
 *
 *               inf.
 *        b       -
 *       a       | |   b-1  -at
 * y =  -----    |    t    e    dt
 *       -     | |
 *      | (b)   -
 *               x
 *
 *  The incomplete gamma integral is used, according to the
 * relation
 *
 * y = cephes_igamc( b, ax ).
 *
 *
 * ACCURACY:
 *
 * See cephes_igamc().
 *
 * ERROR MESSAGES:
 *
 *   message         condition      value returned
 * gdtrc domain         x < 0            0.0
 *
 */

/*							cephes_gdtr()  */


/*
Cephes Math Library Release 2.8:  June, 2000
Copyright 1984, 1987, 1995, 2000 by Stephen L. Moshier
*/

#include "mconf.h"
#ifdef ANSIPROT
extern double cephes_igam ( double, double );
extern double cephes_igamc ( double, double );
#else
double cephes_igam(), cephes_igamc();
#endif

double cephes_gdtr( a, b, x )
double a, b, x;
{

if( x < 0.0 )
	{
	cephes_mtherr( "gdtr", DOMAIN );
	return( 0.0 );
	}
return(  cephes_igam( b, a * x )  );
}



double cephes_gdtrc( a, b, x )
double a, b, x;
{

if( x < 0.0 )
	{
	cephes_mtherr( "gdtrc", DOMAIN );
	return( 0.0 );
	}
return(  cephes_igamc( b, a * x )  );
}
