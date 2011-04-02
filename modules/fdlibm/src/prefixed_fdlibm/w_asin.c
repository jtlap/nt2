
/* @(#)w_asin.c 1.3 95/01/18 */
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

/* 
 * wrapper asin(x)
 */


#include "fdlibm.h"


#ifdef __STDC__
	double fd_asin(double x)		/* wrapper asin */
#else
	double fd_asin(x)			/* wrapper asin */
	double x;
#endif
{
#ifdef _IEEE_LIBM
	return fd___ieee754_asin(x);
#else
	double z;
	z = fd___ieee754_asin(x);
	if(_LIB_VERSION == _IEEE_ || fd_isnan(x)) return z;
	if(fd_fabs(x)>1.0) {
	        return fd___kernel_standard(x,x,2); /* asin(|x|>1) */
	} else
	    return z;
#endif
}
