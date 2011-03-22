

/* @(#)w_pow.c 1.3 95/01/18 */
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
 * wrapper pow(x,y) return x**y
 */

#include "fdlibm.h"


#ifdef __STDC__
	double fd_pow(double x, double y)	/* wrapper pow */
#else
	double fd_pow(x,y)			/* wrapper pow */
	double x,y;
#endif
{
#ifdef _IEEE_LIBM
	return  fd___ieee754_pow(x,y);
#else
	double z;
	z=fd___ieee754_pow(x,y);
	if(_LIB_VERSION == _IEEE_|| fd_isnan(y)) return z;
	if(fd_isnan(x)) {
	    if(y==0.0) 
	        return fd___kernel_standard(x,y,42); /* pow(NaN,0.0) */
	    else 
		return z;
	}
	if(x==0.0){ 
	    if(y==0.0)
	        return fd___kernel_standard(x,y,20); /* pow(0.0,0.0) */
	    if(fd_finite(y)&&y<0.0)
	        return fd___kernel_standard(x,y,23); /* pow(0.0,negative) */
	    return z;
	}
	if(!fd_finite(z)) {
	    if(fd_finite(x)&&fd_finite(y)) {
	        if(fd_isnan(z))
	            return fd___kernel_standard(x,y,24); /* pow neg**non-int */
	        else 
	            return fd___kernel_standard(x,y,21); /* pow overflow */
	    }
	} 
	if(z==0.0&&fd_finite(x)&&fd_finite(y))
	    return fd___kernel_standard(x,y,22); /* pow underflow */
	return z;
#endif
}
