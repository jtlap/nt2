
/* @(#)w_sqrt.c 1.3 95/01/18 */
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
 * wrapper sqrt(x)
 */

#include "fdlibm.h"

#ifdef __STDC__
	double fd_sqrt(double x)		/* wrapper sqrt */
#else
	double fd_sqrt(x)			/* wrapper sqrt */
	double x;
#endif
{
#ifdef _IEEE_LIBM
	return fd___ieee754_sqrt(x);
#else
	double z;
	z = fd___ieee754_sqrt(x);
	if(_LIB_VERSION == _IEEE_ || fd_isnan(x)) return z;
	if(x<0.0) {
	    return fd___kernel_standard(x,x,26); /* sqrt(negative) */
	} else
	    return z;
#endif
}
