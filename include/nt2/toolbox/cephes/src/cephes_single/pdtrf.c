/*							pdtrf.c
 *
 *	Poisson distribution
 *
 *
 *
 * SYNOPSIS:
 *
 * int k;
 * float m, y, cephes_pdtrf();
 *
 * y = cephes_pdtrf( k, m );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns the sum of the first k terms of the Poisson
 * distribution:
 *
 *   k         j
 *   --   -m  m
 *   >   e    --
 *   --       j!
 *  j=0
 *
 * The terms are not summed directly; instead the incomplete
 * gamma integral is employed, according to the relation
 *
 * y = pdtr( k, m ) = igamc( k+1, m ).
 *
 * The arguments must both be positive.
 *
 *
 *
 * ACCURACY:
 *
 *        Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE       0,100       5000       6.9e-5      8.0e-6
 *
 */
/*							cephes_pdtrcf()
 *
 *	Complemented poisson distribution
 *
 *
 *
 * SYNOPSIS:
 *
 * int k;
 * float m, y, cephes_pdtrcf();
 *
 * y = cephes_pdtrcf( k, m );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns the sum of the terms k+1 to infinity of the Poisson
 * distribution:
 *
 *  inf.       j
 *   --   -m  m
 *   >   e    --
 *   --       j!
 *  j=k+1
 *
 * The terms are not summed directly; instead the incomplete
 * gamma integral is employed, according to the formula
 *
 * y = pdtrc( k, m ) = igam( k+1, m ).
 *
 * The arguments must both be positive.
 *
 *
 *
 * ACCURACY:
 *
 *        Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE       0,100       5000       8.4e-5      1.2e-5
 *
 */
/*							cephes_pdtrif()
 *
 *	Inverse Poisson distribution
 *
 *
 *
 * SYNOPSIS:
 *
 * int k;
 * float m, y, cephes_pdtrf();
 *
 * m = cephes_pdtrif( k, y );
 *
 *
 *
 *
 * DESCRIPTION:
 *
 * Finds the Poisson variable x such that the integral
 * from 0 to x of the Poisson density is equal to the
 * given probability y.
 *
 * This is accomplished using the inverse gamma integral
 * function and the relation
 *
 *    m = igami( k+1, y ).
 *
 *
 *
 *
 * ACCURACY:
 *
 *        Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE       0,100       5000       8.7e-6      1.4e-6
 *
 * ERROR MESSAGES:
 *
 *   message         condition      value returned
 * pdtri domain    y < 0 or y >= 1       0.0
 *                     k < 0
 *
 */

/*
Cephes Math Library Release 2.2:  July, 1992
Copyright 1984, 1987, 1992 by Stephen L. Moshier
Direct inquiries to 30 Frost Street, Cambridge, MA 02140
*/

#include "mconf.h"

#ifdef ANSIC
float cephes_igamf(float, float), cephes_igamcf(float, float), cephes_igamif(float, float);
#else
float cephes_igamf(), cephes_igamcf(), cephes_igamif();
#endif


#ifdef ANSIC
float cephes_pdtrcf( int k, float mm )
#else
float cephes_pdtrcf( k, mm )
int k;
double mm;
#endif
{
float v, m;

m = mm;
if( (k < 0) || (m <= 0.0) )
	{
	cephes_mtherr( "pdtrcf", DOMAIN );
	return( 0.0 );
	}
v = k+1;
return( cephes_igamf( v, m ) );
}



#ifdef ANSIC
float cephes_pdtrf( int k, float mm )
#else
float cephes_pdtrf( k, mm )
int k;
double mm;
#endif
{
float v, m;

m = mm;
if( (k < 0) || (m <= 0.0) )
	{
	cephes_mtherr( "pdtr", DOMAIN );
	return( 0.0 );
	}
v = k+1;
return( cephes_igamcf( v, m ) );
}


#ifdef ANSIC
float cephes_pdtrif( int k, float yy )
#else
float cephes_pdtrif( k, yy )
int k;
double yy;
#endif
{
float v, y;

y = yy;
if( (k < 0) || (y < 0.0) || (y >= 1.0) )
	{
	cephes_mtherr( "pdtrif", DOMAIN );
	return( 0.0 );
	}
v = k+1;
v = cephes_igamif( v, y );
return( v );
}
