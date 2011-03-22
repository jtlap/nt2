
/*							btdtrl.c
 *
 *	Beta distribution
 *
 *
 *
 * SYNOPSIS:
 *
 * long double a, b, x, y, cephes_btdtrl();
 *
 * y = cephes_btdtrl( a, b, x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns the area from zero to x under the beta density
 * function:
 *
 *
 *                          x
 *            -             -
 *           | (a+b)       | |  a-1      b-1
 * P(x)  =  ----------     |   t    (1-t)    dt
 *           -     -     | |
 *          | (a) | (b)   -
 *                         0
 *
 *
 * The mean value of this distribution is a/(a+b).  The variance
 * is ab/[(a+b)^2 (a+b+1)].
 *
 * This function is identical to the incomplete beta integral
 * function, cephes_incbetl(a, b, x).
 *
 * The complemented function is
 *
 * 1 - P(1-x)  =  cephes_incbetl( b, a, x );
 *
 *
 * ACCURACY:
 *
 * See incbetl.c.
 *
 */

/*								cephes_btdtrl() */


/*
Cephes Math Library Release 2.0:  April, 1987
Copyright 1984, 1995 by Stephen L. Moshier
Direct inquiries to 30 Frost Street, Cambridge, MA 02140
*/
#include "mconf.h"
#ifdef ANSIPROT
extern long double cephes_incbetl ( long double, long double, long double );
#else
long double cephes_incbetl();
#endif

long double cephes_btdtrl( a, b, x )
long double a, b, x;
{

return( cephes_incbetl( a, b, x ) );
}
