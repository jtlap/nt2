
/* @(#)w_hypot.c 1.3 95/01/18 */
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
 * wrapper hypot(x,y)
 */

#include "fdlibm.h"


#ifdef __STDC__
	double fd_hypot(double x, double y)/* wrapper hypot */
#else
	double fd_hypot(x,y)		/* wrapper hypot */
	double x,y;
#endif
{
#ifdef _IEEE_LIBM
	return fd___ieee754_hypot(x,y);
#else
	double z;
	z = fd___ieee754_hypot(x,y);
	if(_LIB_VERSION == _IEEE_) return z;
	if((!fd_finite(z))&&fd_finite(x)&&fd_finite(y))
	    return fd___kernel_standard(x,y,4); /* hypot overflow */
	else
	    return z;
#endif
}
