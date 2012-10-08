#define _IEEE_LIBM
// THIS IS A NT2 ADDING TO AVOID NATIVE CALLS
//#undef _IEEE_LIBM
/////////////////////////////////////////////
/* @(#)fdlibm.h 1.5 04/04/22 */
/*
 * ====================================================
 * Copyright (C) 2004 by Sun Microsystems, Inc. All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 */

/* Sometimes it's necessary to define __LITTLE_ENDIAN explicitly
   but these catch some common cases. */

#if defined(i386) || defined(i486) || \
	defined(intel) || defined(x86) || defined(i86pc) || \
	defined(__alpha) || defined(__osf__)
#define __LITTLE_ENDIAN
#endif

/* #ifdef __LITTLE_ENDIAN */
/* #define __HI(x) *(1+(int*)&x) */
/* #define __LO(x) *(int*)&x */
/* #define __HIp(x) *(1+(int*)x) */
/* #define __LOp(x) *(int*)x */
/* #else */
/* #define __HI(x) *(int*)&x */
/* #define __LO(x) *(1+(int*)&x) */
/* #define __HIp(x) *(int*)x */
/* #define __LOp(x) *(1+(int*)x) */
/* #endif */

#ifdef __LITTLE_ENDIAN
#define __lo 0
#define __hi 1
#else
#define __lo 1
#define __hi 0
#endif

static inline int fd___HI(double x)
{
  typedef union { double d; int ii[2];}  fd_u;
  fd_u u;
  u.d=x;
  return u.ii[__hi];
}

static inline int fd___LO(double x)
{
  typedef union { double d; int ii[2];}  fd_u;
  fd_u u;
  u.d=x;
  return u.ii[__lo];
}

static inline void fd__set_LO(double *x, int l)
{
  typedef union { double d; int ii[2];}  fd_u;
  fd_u u;
  u.d = *x;
  u.ii[__lo]=l;
  *x=u.d;
}

static inline void fd__set_HI(double *x, int h)
{
  typedef union { double d; int ii[2];}  fd_u;
  fd_u u;
  u.d = *x;
  u.ii[__hi]=h;
  *x=u.d;
}



#ifdef __STDC__
#define	__P(p)	p
#else
#define	__P(p)	()
#endif

/*
 * ANSI/POSIX
 */

extern int signgam;

#define	MAXFLOAT	((float)3.40282346638528860e+38)

enum fdversion {fdlibm_ieee = -1, fdlibm_svid, fdlibm_xopen, fdlibm_posix};

#define _LIB_VERSION_TYPE enum fdversion
#define _LIB_VERSION _fdlib_version  

/* if global variable _LIB_VERSION is not desirable, one may 
 * change the following to be a constant by: 
 *	#define _LIB_VERSION_TYPE const enum version
 * In that case, after one initializes the value _LIB_VERSION (see
 * s_lib_version.c) during compile time, it cannot be modified
 * in the middle of a program
 */ 
extern  _LIB_VERSION_TYPE  _LIB_VERSION;

#define _IEEE_  fdlibm_ieee
#define _SVID_  fdlibm_svid
#define _XOPEN_ fdlibm_xopen
#define _POSIX_ fdlibm_posix

struct exception {
	int type;
	char *name;
	double arg1;
	double arg2;
	double retval;
};

#define	HUGE		MAXFLOAT

/* 
 * set X_TLOSS = pi*2**52, which is possibly defined in <values.h>
 * (one may replace the following line by "#include <values.h>")
 */

#define X_TLOSS		1.41484755040568800000e+16 

#define	DOMAIN		1
#define	SING		2
#define	OVERFLOW	3
#define	UNDERFLOW	4
#define	TLOSS		5
#define	PLOSS		6

/*
 * ANSI/POSIX
 */
extern double fd_acos __P((double));
extern double fd_asin __P((double));
extern double fd_atan __P((double));
extern double fd_atan2 __P((double, double));
extern double fd_cos __P((double));
extern double fd_sin __P((double));
extern double fd_tan __P((double));

extern double fd_cosh __P((double));
extern double fd_sinh __P((double));
extern double fd_tanh __P((double));

extern double fd_exp __P((double));
extern double fd_frexp __P((double, int *));
extern double fd_ldexp __P((double, int));
extern double fd_log __P((double));
extern double fd_log10 __P((double));
extern double fd_modf __P((double, double *));

extern double fd_pow __P((double, double));
extern double fd_sqrt __P((double));

extern double fd_ceil __P((double));
extern double fd_fabs __P((double));
extern double fd_floor __P((double));
extern double fd_fmod __P((double, double));

extern double fd_erf __P((double));
extern double fd_erfc __P((double));
extern double fd_gamma __P((double));
extern double fd_hypot __P((double, double));
extern int fd_isnan __P((double));
extern int fd_finite __P((double));
extern double fd_j0 __P((double));
extern double fd_j1 __P((double));
extern double fd_jn __P((int, double));
extern double fd_lgamma __P((double));
extern double fd_y0 __P((double));
extern double fd_y1 __P((double));
extern double fd_yn __P((int, double));

extern double fd_acosh __P((double));
extern double fd_asinh __P((double));
extern double fd_atanh __P((double));
extern double fd_cbrt __P((double));
extern double fd_logb __P((double));
extern double fd_nextafter __P((double, double));
extern double fd_remainder __P((double, double));
#ifdef _SCALB_INT
extern double fd_scalb __P((double, int));
#else
extern double fd_scalb __P((double, double));
#endif

extern int matherr __P((struct exception *));

/*
 * IEEE Test Vector
 */
extern double fd_significand __P((double));

/*
 * Functions callable from C, intended to support IEEE arithmetic.
 */
extern double fd_copysign __P((double, double));
extern int fd_ilogb __P((double));
extern double fd_rint __P((double));
extern double fd_scalbn __P((double, int));

/*
 * BSD math library entry points
 */
extern double fd_expm1 __P((double));
extern double fd_log1p __P((double));

/*
 * Reentrant version of gamma & lgamma; passes signgam back by reference
 * as the second argument; user must allocate space for signgam.
 */
#ifdef _REENTRANT
extern double fd_gamma_r __P((double, int *));
extern double fd_lgamma_r __P((double, int *));
#endif	/* _REENTRANT */

/* ieee style elementary functions */
extern double fd___ieee754_sqrt __P((double));			
extern double fd___ieee754_acos __P((double));			
extern double fd___ieee754_acosh __P((double));			
extern double fd___ieee754_log __P((double));			
extern double fd___ieee754_atanh __P((double));			
extern double fd___ieee754_asin __P((double));			
extern double fd___ieee754_atan2 __P((double,double));			
extern double fd___ieee754_exp __P((double));
extern double fd___ieee754_cosh __P((double));
extern double fd___ieee754_fmod __P((double,double));
extern double fd___ieee754_pow __P((double,double));
extern double fd___ieee754_lgamma_r __P((double,int *));
extern double fd___ieee754_gamma_r __P((double,int *));
extern double fd___ieee754_lgamma __P((double));
extern double fd___ieee754_gamma __P((double));
extern double fd___ieee754_log10 __P((double));
extern double fd___ieee754_sinh __P((double));
extern double fd___ieee754_hypot __P((double,double));
extern double fd___ieee754_j0 __P((double));
extern double fd___ieee754_j1 __P((double));
extern double fd___ieee754_y0 __P((double));
extern double fd___ieee754_y1 __P((double));
extern double fd___ieee754_jn __P((int,double));
extern double fd___ieee754_yn __P((int,double));
extern double fd___ieee754_remainder __P((double,double));
extern int    fd___ieee754_rem_pio2 __P((double,double*));
#ifdef _SCALB_INT
extern double fd___ieee754_scalb __P((double,int));
#else
extern double fd___ieee754_scalb __P((double,double));
#endif

/* fdlibm kernel function */
extern double fd___kernel_standard __P((double,double,int));	
extern double fd___kernel_sin __P((double,double,int));
extern double fd___kernel_cos __P((double,double));
extern double fd___kernel_tan __P((double,double,int));
extern int    fd___kernel_rem_pio2 __P((double*,double*,int,int,int,const int*));
