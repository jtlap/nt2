/*							ellpjl.c
 *
 *	Jacobian Elliptic Functions
 *
 *
 *
 * SYNOPSIS:
 *
 * long double u, m, sn, cn, dn, phi;
 * int cephes_ellpjl();
 *
 * cephes_ellpjl( u, m, _&sn, _&cn, _&dn, _&phi );
 *
 *
 *
 * DESCRIPTION:
 *
 *
 * Evaluates the Jacobian elliptic functions sn(u|m), cn(u|m),
 * and dn(u|m) of parameter m between 0 and 1, and real
 * argument u.
 *
 * These functions are periodic, with quarter-period on the
 * real axis equal to the complete elliptic integral
 * ellpk(1.0-m).
 *
 * Relation to incomplete elliptic integral:
 * If u = ellik(phi,m), then sn(u|m) = sin(phi),
 * and cn(u|m) = cos(phi).  Phi is called the amplitude of u.
 *
 * Computation is by means of the arithmetic-geometric mean
 * algorithm, except when m is within 1e-12 of 0 or 1.  In the
 * latter case with m close to 1, the approximation applies
 * only for phi < pi/2.
 *
 * ACCURACY:
 *
 * Tested at random points with u between 0 and 10, m between
 * 0 and 1.
 *
 *            Absolute error (* = relative error):
 * arithmetic   function   # trials      peak         rms
 *    IEEE      sn          10000       1.7e-18     2.3e-19
 *    IEEE      cn          20000       1.6e-18     2.2e-19
 *    IEEE      dn          10000       4.7e-15     2.7e-17
 *    IEEE      phi         10000       4.0e-19*    6.6e-20*
 *
 * Accuracy deteriorates when u is large.
 *
 */

/*
Cephes Math Library Release 2.3:  November, 1995
Copyright 1984, 1987, 1995 by Stephen L. Moshier
*/

#include "mconf.h"
#ifdef ANSIPROT
extern long double cephes_sqrtl ( long double );
extern long double cephes_fabsl ( long double );
extern long double cephes_sinl ( long double );
extern long double cephes_cosl ( long double );
extern long double cephes_asinl ( long double );
extern long double cephes_tanhl ( long double );
extern long double cephes_sinhl ( long double );
extern long double cephes_coshl ( long double );
extern long double cephes_atanl ( long double );
extern long double cephes_expl ( long double );
#else
long double cephes_sqrtl(), cephes_fabsl(), cephes_sinl(), cephes_cosl(), cephes_asinl(), cephes_tanhl();
long double cephes_sinhl(), cephes_coshl(), cephes_atanl(), cephes_expl();
#endif
extern long double PIO2L, MACHEPL;

int cephes_ellpjl( u, m, sn, cn, dn, ph )
long double u, m;
long double *sn, *cn, *dn, *ph;
{
long double ai, b, phi, t, twon;
long double a[9], c[9];
int i;


/* Check for special cases */

if( m < 0.0L || m > 1.0L )
	{
	cephes_mtherr( "ellpjl", DOMAIN );
	*sn = 0.0L;
	*cn = 0.0L;
	*ph = 0.0L;
	*dn = 0.0L;
	return(-1);
	}
if( m < 1.0e-12L )
	{
	t = cephes_sinl(u);
	b = cephes_cosl(u);
	ai = 0.25L * m * (u - t*b);
	*sn = t - ai*b;
	*cn = b + ai*t;
	*ph = u - ai;
	*dn = 1.0L - 0.5L*m*t*t;
	return(0);
	}

if( m >= 0.999999999999L )
	{
	ai = 0.25L * (1.0L-m);
	b = cephes_coshl(u);
	t = cephes_tanhl(u);
	phi = 1.0L/b;
	twon = b * cephes_sinhl(u);
	*sn = t + ai * (twon - u)/(b*b);
	*ph = 2.0L*cephes_atanl(cephes_expl(u)) - PIO2L + ai*(twon - u)/b;
	ai *= t * phi;
	*cn = phi - ai * (twon - u);
	*dn = phi + ai * (twon + u);
	return(0);
	}


/*	A. G. M. scale		*/
a[0] = 1.0L;
b = cephes_sqrtl(1.0L - m);
c[0] = cephes_sqrtl(m);
twon = 1.0L;
i = 0;

while( cephes_fabsl(c[i]/a[i]) > MACHEPL )
	{
	if( i > 7 )
		{
		cephes_mtherr( "ellpjl", OVERFLOW );
		goto done;
		}
	ai = a[i];
	++i;
	c[i] = 0.5L * ( ai - b );
	t = cephes_sqrtl( ai * b );
	a[i] = 0.5L * ( ai + b );
	b = t;
	twon *= 2.0L;
	}

done:

/* backward recurrence */
phi = twon * a[i] * u;
do
	{
	t = c[i] * cephes_sinl(phi) / a[i];
	b = phi;
	phi = 0.5L * (cephes_asinl(t) + phi);
	}
while( --i );

*sn = cephes_sinl(phi);
t = cephes_cosl(phi);
*cn = t;
*dn = t/cephes_cosl(phi-b);
*ph = phi;
return(0);
}
