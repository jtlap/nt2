/*							asinl.c
 *
 *	Inverse circular sine, long double precision
 *
 *
 *
 * SYNOPSIS:
 *
 * double x, y, cephes_asinl();
 *
 * y = cephes_asinl( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns radian angle between -pi/2 and +pi/2 whose sine is x.
 *
 * A rational function of the form x + x**3 P(x**2)/Q(x**2)
 * is used for |x| in the interval [0, 0.5].  If |x| > 0.5 it is
 * transformed by the identity
 *
 *    asin(x) = pi/2 - 2 asin( sqrt( (1-x)/2 ) ).
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE     -1, 1        30000       2.7e-19     4.8e-20
 *
 *
 * ERROR MESSAGES:
 *
 *   message         condition      value returned
 * asinl domain        |x| > 1           NANL
 *
 */
/*							cephes_acosl()
 *
 *	Inverse circular cosine, long double precision
 *
 *
 *
 * SYNOPSIS:
 *
 * double x, y, cephes_acosl();
 *
 * y = cephes_acosl( x );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns radian angle between -pi/2 and +pi/2 whose cosine
 * is x.
 *
 * Analytically, acos(x) = pi/2 - asin(x).  However if |x| is
 * near 1, there is cancellation error in subtracting asin(x)
 * from pi/2.  Hence if x < -0.5,
 *
 *    acos(x) =	 pi - 2.0 * asin( sqrt((1+x)/2) );
 *
 * or if x > +0.5,
 *
 *    acos(x) =	 2.0 * asin(  sqrt((1-x)/2) ).
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE      -1, 1       30000       1.4e-19     3.5e-20
 *
 *
 * ERROR MESSAGES:
 *
 *   message         condition      value returned
 * acosl domain        |x| > 1           NANL
 */

/*							asin.c	*/

/*
Cephes Math Library Release 2.7:  May, 1998
Copyright 1984, 1990, 1998 by Stephen L. Moshier
*/

#include "mconf.h"

#ifdef UNK
static long double P[] = {
 3.7769340062433674871612E-3L,
-6.1212919176969202969441E-1L,
 5.9303993515791417710775E0L,
-1.8631697621590161441592E1L,
 2.3314603132141795720634E1L,
-1.0087146579384916260197E1L,
};
static long double Q[] = {
/* 1.0000000000000000000000E0L,*/
-1.5684335624873146511217E1L,
 7.8702951549021104258866E1L,
-1.7078401170625864261444E2L,
 1.6712291455718995937376E2L,
-6.0522879476309497128868E1L,
};
#endif

#ifdef IBMPC
static short P[] = {
0x59d1,0x3509,0x7009,0xf786,0x3ff6, XPD
0xbe97,0x93e6,0x7fab,0x9cb4,0xbffe, XPD
0x8bf5,0x6810,0xd4dc,0xbdc5,0x4001, XPD
0x9bd4,0x8d86,0xb77b,0x950d,0xc003, XPD
0x3b0f,0x9e25,0x4ea5,0xba84,0x4003, XPD
0xea38,0xc6a9,0xf3cf,0xa164,0xc002, XPD
};
static short Q[] = {
/*0x0000,0x0000,0x0000,0x8000,0x3fff,*/
0x1229,0x8516,0x09e9,0xfaf3,0xc002, XPD
0xb5c3,0xf36f,0xe943,0x9d67,0x4005, XPD
0xe11a,0xbe0f,0xb4fd,0xaac8,0xc006, XPD
0x4c69,0x1355,0x7754,0xa71f,0x4006, XPD
0xded7,0xa9fe,0x6db7,0xf217,0xc004, XPD
};
#endif

#ifdef MIEEE
static long P[] = {
0x3ff60000,0xf7867009,0x350959d1,
0xbffe0000,0x9cb47fab,0x93e6be97,
0x40010000,0xbdc5d4dc,0x68108bf5,
0xc0030000,0x950db77b,0x8d869bd4,
0x40030000,0xba844ea5,0x9e253b0f,
0xc0020000,0xa164f3cf,0xc6a9ea38,
};
static long Q[] = {
/*0x3fff0000,0x80000000,0x00000000,*/
0xc0020000,0xfaf309e9,0x85161229,
0x40050000,0x9d67e943,0xf36fb5c3,
0xc0060000,0xaac8b4fd,0xbe0fe11a,
0x40060000,0xa71f7754,0x13554c69,
0xc0040000,0xf2176db7,0xa9feded7,
};
#endif
#ifdef NANS
extern long double NANL;
#endif
#ifdef ANSIPROT
extern long double cephes_ldexpl ( long double, int );
extern long double cephes_sqrtl ( long double );
extern long double cephes_polevll ( long double, long double *, int );
extern long double cephes_p1evll ( long double, long double *, int );
long double cephes_asinl ( long double );
#else
long double cephes_ldexpl(), cephes_sqrtl(), cephes_polevll(), cephes_p1evll();
long double cephes_asinl();
#endif

long double cephes_asinl(x)
long double x;
{
long double a, p, z, zz;
short sign, flag;
extern long double PIO2L;

if( x > 0 )
	{
	sign = 1;
	a = x;
	}
else
	{
	sign = -1;
	a = -x;
	}

if( a > 1.0L )
	{
	cephes_mtherr( "asinl", DOMAIN );
#ifdef NANS
	return( NANL );
#else
	return( 0.0L );
#endif
	}

if( a < 1.0e-10L )
	{
	z = a;
	goto done;
	}

if( a > 0.5L )
	{
	zz = 0.5L -a;
	zz = cephes_ldexpl( zz + 0.5L, -1 );
	z = cephes_sqrtl( zz );
	flag = 1;
	}
else
	{
	z = a;
	zz = z * z;
	flag = 0;
	}

p = zz * cephes_polevll( zz, P, 5)/cephes_p1evll( zz, Q, 5);
z = z * p + z;
if( flag != 0 )
	{
	z = z + z;
	z = PIO2L - z;
	}
done:
if( sign < 0 )
	z = -z;
return(z);
}


extern long double PIO2L, PIL;

long double cephes_acosl(x)
long double x;
{

if( x < -1.0L )
	goto domerr;

if( x < -0.5L) 
	return( PIL - 2.0L * cephes_asinl( cephes_sqrtl(0.5L*(1.0L+x)) ) );

if( x > 1.0L )
	{
domerr:	cephes_mtherr( "acosl", DOMAIN );
#ifdef NANS
	return( NANL );
#else
	return( 0.0L );
#endif
	}

if( x > 0.5L )
	return( 2.0L * cephes_asinl(  cephes_sqrtl(0.5L*(1.0L-x) ) ) );

return( PIO2L - cephes_asinl(x) );
}
