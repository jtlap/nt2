/*							clogf.c
 *
 *	Complex natural logarithm
 *
 *
 *
 * SYNOPSIS:
 *
 * void cephes_clogf();
 * cmplxf z, w;
 *
 * cephes_clogf( &z, &w );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns complex logarithm to the base e (2.718...) of
 * the complex argument x.
 *
 * If z = x + iy, r = sqrt( x**2 + y**2 ),
 * then
 *       w = log(r) + i arctan(y/x).
 * 
 * The arctangent ranges from -PI to +PI.
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE      -10,+10     30000       1.9e-6       6.2e-8
 *
 * Larger relative error can be observed for z near 1 +i0.
 * In IEEE arithmetic the peak absolute error is 3.1e-7.
 *
 */

#include "mconf.h"
extern float MAXNUMF, MACHEPF, PIF, PIO2F;
#ifdef ANSIC
float cephes_cabsf(cmplxf *), cephes_sqrtf(float), cephes_logf(float), cephes_atan2f(float, float);
float cephes_expf(float), cephes_sinf(float), cephes_cosf(float);
float cephes_coshf(float), cephes_sinhf(float), cephes_asinf(float);
float cephes_ctansf(cmplxf *), cephes_redupif(float);
void cephes_cchshf( float, float *, float * );
void cephes_caddf( cmplxf *, cmplxf *, cmplxf * );
void cephes_csqrtf( cmplxf *, cmplxf * );
#else
float cephes_cabsf(), cephes_sqrtf(), cephes_logf(), cephes_atan2f();
float cephes_expf(), cephes_sinf(), cephes_cosf();
float cephes_coshf(), cephes_sinhf(), cephes_asinf();
float cephes_ctansf(), cephes_redupif();
void cephes_cchshf(), cephes_csqrtf(), cephes_caddf();
#endif

#define fabsf(x) ( (x) < 0 ? -(x) : (x) )

void cephes_clogf( z, w )
register cmplxf *z, *w;
{
float p, rr;

/*rr = cephes_sqrtf( z->r * z->r  +  z->i * z->i );*/
rr = cephes_cabsf(z);
p = cephes_logf(rr);
#if ANSIC
rr = cephes_atan2f( z->i, z->r );
#else
rr = cephes_atan2f( z->r, z->i );
if( rr > PIF )
	rr -= PIF + PIF;
#endif
w->i = rr;
w->r = p;
}
/*							cephes_cexpf()
 *
 *	Complex exponential function
 *
 *
 *
 * SYNOPSIS:
 *
 * void cephes_cexpf();
 * cmplxf z, w;
 *
 * cephes_cexpf( &z, &w );
 *
 *
 *
 * DESCRIPTION:
 *
 * Returns the exponential of the complex argument z
 * into the complex result w.
 *
 * If
 *     z = x + iy,
 *     r = exp(x),
 *
 * then
 *
 *     w = r cos y + i r sin y.
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE      -10,+10     30000       1.4e-7      4.5e-8
 *
 */

void cephes_cexpf( z, w )
register cmplxf *z, *w;
{
float r;

r = cephes_expf( z->r );
w->r = r * cephes_cosf( z->i );
w->i = r * cephes_sinf( z->i );
}
/*							cephes_csinf()
 *
 *	Complex circular sine
 *
 *
 *
 * SYNOPSIS:
 *
 * void cephes_csinf();
 * cmplxf z, w;
 *
 * cephes_csinf( &z, &w );
 *
 *
 *
 * DESCRIPTION:
 *
 * If
 *     z = x + iy,
 *
 * then
 *
 *     w = sin x  cosh y  +  i cos x sinh y.
 *
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE      -10,+10     30000       1.9e-7      5.5e-8
 *
 */

void cephes_csinf( z, w )
register cmplxf *z, *w;
{
float ch, sh;

cephes_cchshf( z->i, &ch, &sh );
w->r = cephes_sinf( z->r ) * ch;
w->i = cephes_cosf( z->r ) * sh;
}



/* calculate cosh and sinh */

#ifdef ANSIC
void cephes_cchshf( float xx, float *c, float *s )
#else
void cephes_cchshf( xx, c, s )
double xx;
float *c, *s;
#endif
{
float x, e, ei;

x = xx;
if( fabsf(x) <= 0.5f )
	{
	*c = cephes_coshf(x);
	*s = cephes_sinhf(x);
	}
else
	{
	e = cephes_expf(x);
	ei = 0.5f/e;
	e = 0.5f * e;
	*s = e - ei;
	*c = e + ei;
	}
}

/*							cephes_ccosf()
 *
 *	Complex circular cosine
 *
 *
 *
 * SYNOPSIS:
 *
 * void cephes_ccosf();
 * cmplxf z, w;
 *
 * cephes_ccosf( &z, &w );
 *
 *
 *
 * DESCRIPTION:
 *
 * If
 *     z = x + iy,
 *
 * then
 *
 *     w = cos x  cosh y  -  i sin x sinh y.
 *
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE      -10,+10     30000       1.8e-7       5.5e-8
 */

void cephes_ccosf( z, w )
register cmplxf *z, *w;
{
float ch, sh;

cephes_cchshf( z->i, &ch, &sh );
w->r = cephes_cosf( z->r ) * ch;
w->i = -cephes_sinf( z->r ) * sh;
}
/*							cephes_ctanf()
 *
 *	Complex circular tangent
 *
 *
 *
 * SYNOPSIS:
 *
 * void cephes_ctanf();
 * cmplxf z, w;
 *
 * cephes_ctanf( &z, &w );
 *
 *
 *
 * DESCRIPTION:
 *
 * If
 *     z = x + iy,
 *
 * then
 *
 *           sin 2x  +  i sinh 2y
 *     w  =  --------------------.
 *            cos 2x  +  cosh 2y
 *
 * On the real axis the denominator is zero at odd multiples
 * of PI/2.  The denominator is evaluated by its Taylor
 * series near these points.
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE      -10,+10     30000       3.3e-7       5.1e-8
 */

void cephes_ctanf( z, w )
register cmplxf *z, *w;
{
float d;

d = cephes_cosf( 2.0f * z->r ) + cephes_coshf( 2.0f * z->i );

if( fabsf(d) < 0.25f )
	d = cephes_ctansf(z);

if( d == 0.0f )
	{
	cephes_mtherr( "ctanf", OVERFLOW );
	w->r = MAXNUMF;
	w->i = MAXNUMF;
	return;
	}

w->r = cephes_sinf( 2.0f * z->r ) / d;
w->i = cephes_sinhf( 2.0f * z->i ) / d;
}
/*							cephes_ccotf()
 *
 *	Complex circular cotangent
 *
 *
 *
 * SYNOPSIS:
 *
 * void cephes_ccotf();
 * cmplxf z, w;
 *
 * cephes_ccotf( &z, &w );
 *
 *
 *
 * DESCRIPTION:
 *
 * If
 *     z = x + iy,
 *
 * then
 *
 *           sin 2x  -  i sinh 2y
 *     w  =  --------------------.
 *            cosh 2y  -  cos 2x
 *
 * On the real axis, the denominator has zeros at even
 * multiples of PI/2.  Near these points it is evaluated
 * by a Taylor series.
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE      -10,+10     30000       3.6e-7       5.7e-8
 * Also tested by ctan * ccot = 1 + i0.
 */

void cephes_ccotf( z, w )
register cmplxf *z, *w;
{
float d;


d = cephes_coshf(2.0f * z->i) - cephes_cosf(2.0f * z->r);

if( fabsf(d) < 0.25f )
	d = cephes_ctansf(z);

if( d == 0.0f )
	{
	cephes_mtherr( "ccotf", OVERFLOW );
	w->r = MAXNUMF;
	w->i = MAXNUMF;
	return;
	}

d = 1.0f/d;
w->r = cephes_sinf( 2.0f * z->r ) * d;
w->i = -cephes_sinhf( 2.0f * z->i ) * d;
}

/* Program to subtract nearest integer multiple of PI */
/* extended precision value of PI: */

static double DP1 =  3.140625;
static double DP2 =  9.67502593994140625E-4;
static double DP3 =  1.509957990978376432E-7;


#ifdef ANSIC
float cephes_redupif(float xx)
#else
float cephes_redupif(xx)
double xx;
#endif
{
float x, t;
long i;

x = xx;
t = x/PIF;
if( t >= 0.0f )
	t += 0.5f;
else
	t -= 0.5f;

i = t;	/* the multiple */
double dt = i;
 t = (((double)x - dt * DP1) - dt * DP2) - dt * DP3;
return(t);
}

/*  Taylor series expansion for cosh(2y) - cos(2x)	*/

float cephes_ctansf(z)
cmplxf *z;
{
float f, x, x2, y, y2, rn, t, d;

x = fabsf( 2.0f * z->r );
y = fabsf( 2.0f * z->i );

x = cephes_redupif(x);

x = x * x;
y = y * y;
x2 = 1.0f;
y2 = 1.0f;
f = 1.0f;
rn = 0.0f;
d = 0.0f;
do
	{
	rn += 1.0f;
	f *= rn;
	rn += 1.0f;
	f *= rn;
	x2 *= x;
	y2 *= y;
	t = y2 + x2;
	t /= f;
	d += t;

	rn += 1.0f;
	f *= rn;
	rn += 1.0f;
	f *= rn;
	x2 *= x;
	y2 *= y;
	t = y2 - x2;
	t /= f;
	d += t;
	}
while( fabsf(t/d) > MACHEPF );
return(d);
}
/*							cephes_casinf()
 *
 *	Complex circular arc sine
 *
 *
 *
 * SYNOPSIS:
 *
 * void cephes_casinf();
 * cmplxf z, w;
 *
 * cephes_casinf( &z, &w );
 *
 *
 *
 * DESCRIPTION:
 *
 * Inverse complex sine:
 *
 *                               2
 * w = -i clog( iz + csqrt( 1 - z ) ).
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE      -10,+10     30000       1.1e-5      1.5e-6
 * Larger relative error can be observed for z near zero.
 *
 */

void cephes_casinf( z, w )
cmplxf *z, *w;
{
float x, y;
static cmplxf ca, ct, zz, z2;
/*
float cn, n;
static float a, b, s, t, u, v, y2;
static cmplxf sum;
*/

x = z->r;
y = z->i;

if( y == 0.0f )
	{
	if( fabsf(x) > 1.0f )
		{
		w->r = PIO2F;
		w->i = 0.0f;
		cephes_mtherr( "casinf", DOMAIN );
		}
	else
		{
		w->r = cephes_asinf(x);
		w->i = 0.0f;
		}
	return;
	}

/* Power series expansion */
/*
b = cephes_cabsf(z);
if( b < 0.125 )
{
z2.r = (x - y) * (x + y);
z2.i = 2.0 * x * y;

cn = 1.0;
n = 1.0;
ca.r = x;
ca.i = y;
sum.r = x;
sum.i = y;
do
	{
	ct.r = z2.r * ca.r  -  z2.i * ca.i;
	ct.i = z2.r * ca.i  +  z2.i * ca.r;
	ca.r = ct.r;
	ca.i = ct.i;

	cn *= n;
	n += 1.0;
	cn /= n;
	n += 1.0;
	b = cn/n;

	ct.r *= b;
	ct.i *= b;
	sum.r += ct.r;
	sum.i += ct.i;
	b = fabsf(ct.r) + fabsf(ct.i);
	}
while( b > MACHEPF );
w->r = sum.r;
w->i = sum.i;
return;
}
*/


ca.r = x;
ca.i = y;

ct.r = -ca.i;	/* iz */
ct.i = ca.r;

	/* sqrt( 1 - z*z) */
/* cmul( &ca, &ca, &zz ) */
zz.r = (ca.r - ca.i) * (ca.r + ca.i);	/*x * x  -  y * y */
zz.i = 2.0f * ca.r * ca.i;

zz.r = 1.0f - zz.r;
zz.i = -zz.i;
cephes_csqrtf( &zz, &z2 );

cephes_caddf( &z2, &ct, &zz );
cephes_clogf( &zz, &zz );
w->r = zz.i;	/* mult by 1/i = -i */
w->i = -zz.r;
return;
}
/*							cephes_cacosf()
 *
 *	Complex circular arc cosine
 *
 *
 *
 * SYNOPSIS:
 *
 * void cephes_cacosf();
 * cmplxf z, w;
 *
 * cephes_cacosf( &z, &w );
 *
 *
 *
 * DESCRIPTION:
 *
 *
 * w = arccos z  =  PI/2 - arcsin z.
 *
 *
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE      -10,+10     30000       9.2e-6       1.2e-6
 *
 */

void cephes_cacosf( z, w )
cmplxf *z, *w;
{

cephes_casinf( z, w );
w->r = PIO2F  -  w->r;
w->i = -w->i;
}
/*							catan()
 *
 *	Complex circular arc tangent
 *
 *
 *
 * SYNOPSIS:
 *
 * void catan();
 * cmplxf z, w;
 *
 * catan( &z, &w );
 *
 *
 *
 * DESCRIPTION:
 *
 * If
 *     z = x + iy,
 *
 * then
 *          1       (    2x     )
 * Re w  =  - arctan(-----------)  +  k PI
 *          2       (     2    2)
 *                  (1 - x  - y )
 *
 *               ( 2         2)
 *          1    (x  +  (y+1) )
 * Im w  =  - log(------------)
 *          4    ( 2         2)
 *               (x  +  (y-1) )
 *
 * Where k is an arbitrary integer.
 *
 *
 *
 * ACCURACY:
 *
 *                      Relative error:
 * arithmetic   domain     # trials      peak         rms
 *    IEEE      -10,+10     30000        2.3e-6      5.2e-8
 *
 */

void cephes_catanf( z, w )
cmplxf *z, *w;
{
float a, t, x, x2, y;

x = z->r;
y = z->i;

if( (x == 0.0f) && (y > 1.0f) )
	goto ovrf;

x2 = x * x;
a = 1.0f - x2 - (y * y);
if( a == 0.0f )
	goto ovrf;

#if ANSIC
t = 0.5f * cephes_atan2f( 2.0f * x, a );
#else
t = 0.5f * cephes_atan2f( a, 2.0f * x );
#endif
w->r = cephes_redupif( t );

t = y - 1.0f;
a = x2 + (t * t);
if( a == 0.0f )
	goto ovrf;

t = y + 1.0f;
a = (x2 + (t * t))/a;
w->i = 0.25f*cephes_logf(a);
return;

ovrf:
cephes_mtherr( "catanf", OVERFLOW );
w->r = MAXNUMF;
w->i = MAXNUMF;
}
