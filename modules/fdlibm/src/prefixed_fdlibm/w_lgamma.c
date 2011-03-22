
/* @(#)w_lgamma.c 1.3 95/01/18 */
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

/* double lgamma(double x)
 * Return the logarithm of the Gamma function of x.
 *
 * Method: call fd___ieee754_lgamma_r
 */

#include "fdlibm.h"

extern int signgam;

#ifdef __STDC__
	double fd_lgamma(double x)
#else
	double fd_lgamma(x)
	double x;
#endif
{
#ifdef _IEEE_LIBM
	return fd___ieee754_lgamma_r(x,&signgam);
#else
        double y;
        y = fd___ieee754_lgamma_r(x,&signgam);
        if(_LIB_VERSION == _IEEE_) return y;
        if(!fd_finite(y)&&fd_finite(x)) {
            if(fd_floor(x)==x&&x<=0.0)
                return fd___kernel_standard(x,x,15); /* lgamma pole */
            else
                return fd___kernel_standard(x,x,14); /* lgamma overflow */
        } else
            return y;
#endif
}             
