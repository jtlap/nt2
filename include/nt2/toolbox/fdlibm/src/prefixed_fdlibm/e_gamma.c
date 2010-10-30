
/* @(#)e_gamma.c 1.3 95/01/18 */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 *
 */

/* fd___ieee754_gamma(x)
 * Return the logarithm of the Gamma function of x.
 *
 * Method: call fd___ieee754_gamma_r
 */

#include "fdlibm.h"

extern int signgam;

#ifdef __STDC__
	double fd___ieee754_gamma(double x)
#else
	double fd___ieee754_gamma(x)
	double x;
#endif
{
	return fd___ieee754_gamma_r(x,&signgam);
}
