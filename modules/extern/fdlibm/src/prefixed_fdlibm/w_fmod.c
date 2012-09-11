
/* @(#)w_fmod.c 1.3 95/01/18 */
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
 * wrapper fmod(x,y)
 */

#include "fdlibm.h"


#ifdef __STDC__
	double fd_fmod(double x, double y)	/* wrapper fmod */
#else
	double fd_fmod(x,y)		/* wrapper fmod */
	double x,y;
#endif
{
#ifdef _IEEE_LIBM
	return fd___ieee754_fmod(x,y);
#else
	double z;
	z = fd___ieee754_fmod(x,y);
	if(_LIB_VERSION == _IEEE_ ||fd_isnan(y)||fd_isnan(x)) return z;
	if(y==0.0) {
	        return fd___kernel_standard(x,y,27); /* fmod(x,0) */
	} else
	    return z;
#endif
}
