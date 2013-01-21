/*							unityl.c
 *
 * Relative error approximations for function arguments near
 * unity.
 *
 *    cosm1(x) = cos(x) - 1
 *
 */

#include "mconf.h"
#ifdef ANSIPROT
extern long double cephes_cosl ( long double );
extern long double cephes_polevll ( long double, long double *, int );
extern long double cephes_p1evll ( long double,  long double *, int );
#else
long double cephes_cosl(), cephes_polevll(), cephes_p1evll();
#endif


/* cosm1(x) = cos(x) - 1  */

static long double coscof[7] = {
 4.7377507964246204691685E-14L,
-1.1470284843425359765671E-11L,
 2.0876754287081521758361E-9L,
-2.7557319214999787979814E-7L,
 2.4801587301570552304991E-5L,
-1.3888888888888872993737E-3L,
 4.1666666666666666609054E-2L,
};

extern long double PIO4L;

long double cephes_cosm1l(x)
long double x;
{
long double xx;

if( (x < -PIO4L) || (x > PIO4L) )
	return( cephes_cosl(x) - 1.0L );
xx = x * x;
xx = -0.5L*xx + xx * xx * cephes_polevll( xx, coscof, 6 );
return xx;
}
