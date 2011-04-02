
/* @(#)w_log.c 1.3 95/01/18 */
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
 * wrapper log(x)
 */

#include "fdlibm.h"


#ifdef __STDC__
	double fd_log(double x)		/* wrapper log */
#else
	double fd_log(x)			/* wrapper log */
	double x;
#endif
{
#ifdef _IEEE_LIBM
	return fd___ieee754_log(x);
#else
	double z;
	z = fd___ieee754_log(x);
	if(_LIB_VERSION == _IEEE_ || fd_isnan(x) || x > 0.0) return z;
	if(x==0.0)
	    return fd___kernel_standard(x,x,16); /* log(0) */
	else 
	    return fd___kernel_standard(x,x,17); /* log(x<0) */
#endif
}
