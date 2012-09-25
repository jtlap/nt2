
/* @(#)w_sinh.c 1.3 95/01/18 */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 */

/* 
 * wrapper sinh(x)
 */

#include "fdlibm.h"

#ifdef __STDC__
	double fd_sinh(double x)		/* wrapper sinh */
#else
	double fd_sinh(x)			/* wrapper sinh */
	double x;
#endif
{
#ifdef _IEEE_LIBM
	return fd___ieee754_sinh(x);
#else
	double z; 
	z = fd___ieee754_sinh(x);
	if(_LIB_VERSION == _IEEE_) return z;
	if(!fd_finite(z)&&fd_finite(x)) {
	    return fd___kernel_standard(x,x,25); /* sinh overflow */
	} else
	    return z;
#endif
}
