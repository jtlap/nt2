
/* @(#)w_acos.c 1.3 95/01/18 */
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
 * wrap_acos(x)
 */

#include "fdlibm.h"


#ifdef __STDC__
	double fd_acos(double x)		/* wrapper acos */
#else
	double fd_acos(x)			/* wrapper acos */
	double x;
#endif
{
#ifdef _IEEE_LIBM
	return fd___ieee754_acos(x);
#else
	double z;
	z = fd___ieee754_acos(x);
	if(_LIB_VERSION == _IEEE_ || fd_isnan(x)) return z;
	if(fd_fabs(x)>1.0) {
	        return fd___kernel_standard(x,x,1); /* acos(|x|>1) */
	} else
	    return z;
#endif
}
